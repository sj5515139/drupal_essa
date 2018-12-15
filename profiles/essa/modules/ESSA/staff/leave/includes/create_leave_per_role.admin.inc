<?php

/**
 *Implements page callback od_form
 */
function role_leave_form($form, &$form_state){
  $form = array();
  
  $form['help'] = array(
    '#markup' => '<h3 style = "background: #008B8B; color: white; padding: 5px; font-weight: 400;">This will override the default leave type for mentioned post.</h3>',
  );
  
	$session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leaves = db_query("
    SELECT * from {$leave_table} where leave_type IS NULL and post_id IS NULL and leave_id <> 'OD' and leave_id <> 'SL' and leave_id <> 'SL'"
	);
  $leave_type[] = '--SELECT--';
  foreach($leaves as $leave){
		$leave_type[] = $leave->leave_id;
  }
	$form['leave_type'] = array(
		'#type' => 'select',
		'#title' => t('Select a leave type'),
		'#description' => t('The selected leave type will be overrriden with new values. If you leave this as "--SELECT--", a special leave type will be created for mentioned post.'),
		'#options' => drupal_map_assoc(array_unique(array_filter($leave_type))),
	);
	
  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => 'Leave ID',
		'#states' => array(
			'visible' => array(
			  ':input[name = "leave_type"]' => array('value' => '--SELECT--'),
			),
		),
  );
  
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Leave Name',
		'#states' => array(
			'visible' => array(
			  ':input[name = "leave_type"]' => array('value' => '--SELECT--'),
			),
		),
  );
  
	$form['post_type'] = array(
    '#type' => 'select',
    '#title' => t('Select post type'),
    '#options' => drupal_map_assoc(array('Academics', 'Admin')),
		'#required' => TRUE,
  );
  
  $form['ac'] = array(
    '#type' => 'fieldset',
    '#states' => array(
			'visible' => array(
			  ':input[name = "post_type"]' => array('value' => 'Academics'),
			),
		),
  );
	
	$options_academic = array();
	$academic_post = db_query("
    SELECT * from dnp_term_data where vid = 1 and type = 'Post'"
	);
	foreach($academic_post as $ap){
		$options_academic[] = $ap->name;
	}
	
	$form['ac']['post_academics'] =  array(
    '#title' => t('Select Posts - (Academic)'),
    '#type' => 'checkboxes',
    '#options' => drupal_map_assoc($options_academic),
  );
  
  $form['ad'] = array(
    '#type' => 'fieldset',
    '#states' => array(
			'visible' => array(
			  ':input[name = "post_type"]' => array('value' => 'Admin'),
			),
		),
  );
	
	$options_admin = array();
	$admin_post = db_query("
    SELECT * from dnp_term_data where vid = 2 and type = 'Post'"
	);
	foreach($admin_post as $ap){
		$options_admin[] = $ap->name;
	}
	
	$form['ad']['post_admin'] =  array(
    '#title' => t('Select Posts - (Admin)'),
    '#type' => 'checkboxes',
    '#options' => drupal_map_assoc($options_admin),
  );
  
  $form['desc'] = array(
    '#type' => 'textarea',
    '#title' => t('Leave Description'),
    '#resizable' => FALSE,
  );
  
  $form['nod_year'] = array(
    '#type' => 'textfield',
    '#title' => t('No. of days(per year)')
  );
	
	$form['max_month'] = array(
    '#type' => 'textfield',
    '#title' => t('Max in a month'),
		'#description' => 'This sets a threshold for maximum no. of leave a staff can take in one month.(Leave it blank, if not required.)'
  );
	
	$form['at_a_stretch'] = array(
    '#type' => 'textfield',
    '#title' => t('Min at a stretch'),
		'#description' => 'This sets a threshold for minimum no. of leave a staff shall take at a stretch.(Leave it blank, if not required.)'
  );
	
	$form['half_day_rule'] = array(
		'#type' => 'textfield',
		'#title' => '<h3> half-day = 1 full day.</h3>',
		'#size' => 1,
		'#default_value' => 2,
	);
  
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
	
	$post = dnp_get_term_by_name('Principal','organisation_structure_admin');
  return $form;
}

/**
 *Implements submit function
 
function role_leave_form_validate($form, &$form_state){
  $post_academics = $post_admin = NULL;
	
		if($form_state['values']['post_type'] == 'Academics'){
			if($form_state['values']['post_academics'][0] != NULL){
		  $post_academics = dnp_term_load($form_state['values']['post_academics'][0]);
		}
		if($post_academics->type != 'Post'){
		  form_set_error('post_academics','Inappropriate Selection! Please select a post.');
		}
	}else{
		if($form_state['values']['post_admin'][0] != NULL){
		  $post_admin = dnp_term_load($form_state['values']['post_admin'][0]);
		}
		if($post_admin->type != 'Post'){
		  form_set_error('post_academics','Inappropriate Selection! Please select an admin post.');
		}
	}
}
/**
 *Implements submit function
 */
function role_leave_form_submit($form, &$form_state){
	//dsm($form_state);
	$session = variable_get('essa_sid');
	$leave_table = 'essa_'.$session.'_leave_types';
	
	if($form_state['values']['post_type'] == 'Academics'){
		foreach($form_state['values']['post_academics'] as $pac){
			if($pac != '0'){
				$vocab = 'organisation_structure_academics';
				$post = dnp_get_term_by_name($pac,$vocab);
				foreach($post as $p){
					$post_id = $p->tid;
				}
				if($form_state['values']['leave_type'] == "--SELECT--"){
					$leave_type = NULL;
					$leave_id = $form_state['values']['id'].'-'.$post_id;
					$leave_name = $form_state['values']['name'];
				}else{
					$leave_type = $form_state['values']['leave_type'];
					$leave_id = $form_state['values']['leave_type'].'-'.$post_id;
					$leaves = db_query("
					  SELECT * from {$leave_table} where leave_id = :leave_id;", array(':leave_id' => $leave_type)
					);
					foreach($leaves as $leave){
						$leave_name = $leave -> leave_name;
					}
				}
				db_merge($leave_table)
					->key(array('leave_id' => $leave_id))
					->fields (array(
						'leave_id' => $leave_id,
						'leave_type' => $leave_type,
						'post_type' => $form_state['values']['post_type'],
				    'post_id' => $post_id,
				    'leave_name' => $leave_name,
				    'leave_desc' => $form_state['values']['desc'],
						'max_per_month' => (int)$form_state['values']['max_month'],
						'min_stretch' => (int)$form_state['values']['at_a_stretch'],
						'nod_per_year' => (int)$form_state['values']['nod_year'],
						'half_day_rule' => (int)$form_state['values']['half_day_rule'],
				  )
				)
				->execute();
			}
		}
	}elseif($form_state['values']['post_type'] == 'Admin'){
		foreach($form_state['values']['post_admin'] as $pad){
			if($pad != '0'){
				$vocab = 'organisation_structure_admin';
				$post = dnp_get_term_by_name($pad,$vocab);
				foreach($post as $p){
					$post_id = $p->tid;
				}
				if($form_state['values']['leave_type'] == "--SELECT--"){
					$leave_type = NULL;
					$leave_id = $form_state['values']['id'].'-'.$post_id;
					$leave_name = $form_state['values']['name'];
				}else{
					$leave_type = $form_state['values']['leave_type'];
					$leave_id = $form_state['values']['leave_type'].'-'.$post_id;
					$leaves = db_query("
					  SELECT * from {$leave_table} where leave_id = :leave_id;", array(':leave_id' => $leave_type)
					);
					foreach($leaves as $leave){
						$leave_name = $leave -> leave_name;
					}
				}
				db_merge($leave_table)
					->key(array('leave_id' => $leave_id))
					->fields (array(
						'leave_id' => $leave_id,
						'leave_type' => $leave_type,
						'post_type' => $form_state['values']['post_type'],
				    'post_id' => $post_id,
				    'leave_name' => $leave_name,
				    'leave_desc' => $form_state['values']['desc'],
						'max_per_month' => (int)$form_state['values']['max_month'],
						'min_stretch' => (int)$form_state['values']['at_a_stretch'],
						'nod_per_year' => (int)$form_state['values']['nod_year'],
						'half_day_rule' => (int)$form_state['values']['half_day_rule'],
				  )
				)
				->execute();
			}
		}
	}
	menu_rebuild();
}
	/*
	 
	 db_merge($leave_table)
					->key(array('leave_id' => $leave_id))
					->fields (array(
						'leave_id' => $leave_id,
						'leave_type' => $leave_type,
						'post_type' => $form_state['values']['post_type'],
				    'post_id' => $post,
				    'leave_name' => $leave_name,
				    'leave_desc' => $form_state['values']['desc'],
				    'nod_per_month' => (int)$form_state['values']['nod_month'],
				    'nod_per_year' => (int)$form_state['values']['nod_year'],
				  )
				)
				->execute();
	 
  if($form_state['values']['post_academics'][0] != NULL){
    $post = $form_state['values']['post_academics'][0];
  }else{
    $post = $form_state['values']['post_admin'][0];
  }
  
  $session = variable_get('essa_sid');
	$leave_table = 'essa_'.$session.'_leave_types';
	if($form_state['values']['leave_type'] == "--SELECT--"){
		$leave_type = NULL;
		$leave_id = $form_state['values']['id'];
		$leave_name = $form_state['values']['name'];
	}else{
		$leave_type = $form_state['values']['leave_type'];
		$leave_id = $form_state['values']['leave_type'].'-'.$post;
		$leaves = db_query("
		  SELECT * from {$leave_table} where leave_id = :leave_id;", array(':leave_id' => $leave_type)
		);
		foreach($leaves as $leave){
			$leave_name = $leave -> leave_name;
		}
	}
  db_merge($leave_table)
    ->key(array('leave_id' => $leave_id))
    ->fields (array(
      'leave_id' => $leave_id,
			'leave_type' => $leave_type,
			'post_type' => $form_state['values']['post_type'],
      'post_id' => $post,
      'leave_name' => $leave_name,
      'leave_desc' => $form_state['values']['desc'],
      'nod_per_month' => (int)$form_state['values']['nod_month'],
      'nod_per_year' => (int)$form_state['values']['nod_year'],
    )
  )
  ->execute();
	
	
	$schema['leave_type'] = array(
    'description' => 'TODO: please describe this table!',
    'fields' => array(
			'id' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'serial',
	      'unsigned' => TRUE,
	      'not null' => TRUE,
	    ),
      'req_timestamp' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'varchar',
        'length' => '50',
        'not null' => FALSE,
      ),
      'leave_id' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'varchar',
        'length' => '50',
        'not null' => FALSE,
      ),
      'emp_id' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'varchar',
        'length' => '50',
        'not null' => FALSE,
      ),
			'from_date' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
			'to_date' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'varchar',
        'length' => '100',
        'not null' => FALSE,
      ),
      'no_of_days' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'int',
        'length' => '11',
        'not null' => FALSE,
      ),
			'half_day' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'varchar',
        'length' => '11',
        'not null' => FALSE,
      ),
			'reason' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
			'status' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'varchar',
        'length' => '30',
        'not null' => FALSE,
      ),
			'status_reason' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'varchar',
        'length' => '500',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('id'),
  );
	
	if($leave_type != NULL){
		$name_of_table = 'essa_'.$session.'_leave_'.$leave_type;
	}else{
		$name_of_table = 'essa_'.$session.'_leave_'.$leave_id;
	}
	if(!db_table_exists($name_of_table)){
		db_create_table($name_of_table, $schema['leave_type']);
	}
}

function clt_academics_hs_setting(){
	// Load category based in vocabulary machine name
	$voc = 'organisation_structure_academics';//replace this with the taxonomy term
  $vocabulary = dnp_vocabulary_machine_name_load($voc);
	//dsm($vocabulary);
  
	$config = array(
		'module' => 'hs_dnp',
    'params' => array(
				'vid' => (int) $vocabulary->vid,
				'exclude_tid' => NULL,
				'root_term' => NULL,
				'entity_count_for_node_type' => NULL,
      ),
		'config_id'       => 'taxonomy-2',
		'save_lineage'    => 0,
		'enforce_deepest' => 0,
		'entity_count'    => 0,
		'require_entity'  => 0,
		'resizable'       => 0,
		'render_flat_select' => 0,
		'level_labels' => array(
		  'status' => 1,
		  'labels' => array(
		    0 => '--Select--',
		    1 => '--Select--',
				2 => '--Select--',
				3 => '--Select--',
				4 => '--Select--',
				5 => '--Select--',
				6 => '--Select--',
				7 => '--Select--',
				8 => '--Select--',
				9 => '--Select--',
		  ),
		),
		'dropbox' => array(
		  'status'    => 0,
		),
		'editability' => array(
		  'status' => 0,
		  'item_types' => array(
		    0 => '',
		    1 => '',
		  ),
		  'allowed_levels' => array(
		    0 => 1,
		    1 => 1,
				2 => 1,
				3 => 1,
				4 => 1,
				5 => 1,
				6 => 1,
				7 => 1,
				8 => 1,
				9 => 1,
		  ),
		  'allow_new_levels' => 0,
		  'max_levels'       => 1,
		),
	);
	
	return $config;
}

function clt_admin_hs_setting(){
	// Load category based in vocabulary machine name
	$voc = 'organisation_structure_admin';//replace this with the taxonomy term
  $vocabulary = dnp_vocabulary_machine_name_load($voc);
	//dsm($vocabulary);
  
	$config = array(
		'module' => 'hs_dnp',
    'params' => array(
				'vid' => (int) $vocabulary->vid,
				'exclude_tid' => NULL,
				'root_term' => NULL,
				'entity_count_for_node_type' => NULL,
      ),
		'config_id'       => 'taxonomy-2',
		'save_lineage'    => 0,
		'enforce_deepest' => 0,
		'entity_count'    => 0,
		'require_entity'  => 0,
		'resizable'       => 0,
		'render_flat_select' => 0,
		'level_labels' => array(
		  'status' => 1,
		  'labels' => array(
		    0 => '--Select--',
		    1 => '--Select--',
				2 => '--Select--',
				3 => '--Select--',
				4 => '--Select--',
				5 => '--Select--',
				6 => '--Select--',
				7 => '--Select--',
				8 => '--Select--',
				9 => '--Select--',
		  ),
		),
		'dropbox' => array(
		  'status'    => 0,
		),
		'editability' => array(
		  'status' => 0,
		  'item_types' => array(
		    0 => '',
		    1 => '',
		  ),
		  'allowed_levels' => array(
		    0 => 1,
		    1 => 1,
				2 => 1,
				3 => 1,
				4 => 1,
				5 => 1,
				6 => 1,
				7 => 1,
				8 => 1,
				9 => 1,
		  ),
		  'allow_new_levels' => 0,
		  'max_levels'       => 1,
		),
	);
	
	return $config;
}