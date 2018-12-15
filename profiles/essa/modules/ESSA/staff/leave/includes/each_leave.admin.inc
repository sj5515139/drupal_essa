<?php
/**
 *Implements page callback function each_leave_form.
 */
function each_leave_form($form, &$form_state, $leave_id){
  $form = array();
  
  $form['leave_id'] = array(
    '#type' => 'value',
    '#value' => $leave_id,
  );
  $session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leaves = db_query("
    SELECT * from {$leave_table} where leave_id = :leave_id;
  ", array(':leave_id'=>$leave_id));
  
  foreach($leaves as $leave){
		$leave_id = $leave->leave_id;
		$post_type = $leave->post_type;
		$post_id = $leave->post_id;
    $leave_name = $leave->leave_name;
		$leave_type = $leave->leave_type;
    $leave_desc = $leave->leave_desc;
    $max_per_month = $leave -> max_per_month;
    $nod_per_year = $leave -> nod_per_year;
    $post_name = NULL;
		$at_a_stretch = $leave->min_stretch;
		$half_day_rule = $leave->half_day_rule;
    if($leave->post_id != NULL){
      $post = dnp_term_load($leave->post_id);
      $post_name = $post->name;
    }
  }
	
	if($post_id == NULL && $leave_id != 'OD' && $leave_id != 'SL' && $leave_id != 'LWP'){
		$form['leavetype'] = array(
			'#type' => 'value',
			'#value' => 'leave',
		);
		
		$form['id'] = array(
		  '#type' => 'textfield',
		  '#title' => 'Leave ID',
			'#description' => 'This must be unique.',
			'#default_value' => isset($leave_id)? $leave_id: NULL,
			'#required' => TRUE,
			'#ajax' => array(
		    'event' => 'blur',
		    'callback' => 'unique_id_ajax',
		    'wrapper' => 'ui_error',
		    'method' => 'append',
		    'effect' => 'fade',
		  ),
			'#disabled' => TRUE,
		);
		
		$form['ef']['t']['error'] = array(
			'#type' => 'container',
		  '#prefix' => '<div id = "ui_error">',
		  '#suffix' => '</div>',
		);
		
		$form['name'] = array(
		  '#type' => 'textfield',
		  '#title' => 'Leave Name',
			'#default_value' => isset($leave_name)? $leave_name: NULL,
		);
		
		$form['nod_year'] = array(
		  '#type' => 'textfield',
		  '#title' => t('No. of days(per year)'),
			'#default_value' => isset($nod_per_year)? $nod_per_year: NULL,
			'#required' => TRUE,
		);
		
		$form['desc'] = array(
		  '#type' => 'textarea',
		  '#title' => t('Leave Description'),
			'#default_value' => isset($leave_desc)? $leave_desc: NULL,
		  '#resizable' => FALSE,
		);
		
		$form['max_month'] = array(
		  '#type' => 'textfield',
		  '#title' => t('Max in a month'),
			'#default_value' => isset($max_per_month)? $max_per_month: NULL,
			'#description' => 'This sets a threshold for maximum no. of leave a staff can take in one month.(Leave it blank, if not required.)'
		);
		
		$form['at_a_stretch'] = array(
		  '#type' => 'textfield',
		  '#title' => t('Min at a stretch'),
			'#description' => 'This sets a threshold for minimum no. of leave a staff shall take at a stretch.(Leave it blank, if not required.)',
			'#default_value' => isset($at_a_stretch)? $at_a_stretch: NULL,
		);
		
		$form['half_day_rule'] = array(
			'#type' => 'textfield',
			'#title' => '<h3> half-day = 1 full day.</h3>',
			'#size' => 1,
			'#default_value' => isset($half_day_rule)? $half_day_rule: NULL,
		);
		
		$form['save'] = array(
		  '#type' => 'submit',
		  '#value' => t('Save'),
		);
		
		return $form;
	}elseif($post_id != NULL && $leave_type != NULL && $leave_id != 'OD' && $leave_id != 'SL' && $leave_id != 'LWP'){
		$form['leavetype'] = array(
			'#type' => 'value',
			'#value' => 'leave+post+leave_type',
		);
		$post_details = db_query("
	    SELECT * from dnp_term_data where tid = :tid;", array(':tid' => $post_id)
		);
		foreach($post_details as $pd){
			$this_post = $pd->name;
		}
		
		$form['help'] = array(
	    '#markup' => '<h3 style = "background: #008B8B; color: white; padding: 5px; font-weight: 400;">This will override the default leave type for mentioned post.</h3>',
	  );
		
		$form['post_academics'] =  array(
		  '#type' => 'markup',
		  '#markup' => '<h1 style = "text-align: right;">For the post - '.$this_post.'</h1>',
		);
		
		$session_id = (string)variable_get('essa_sid');
		$leave_table = 'essa_'.$session_id.'_leave_types';
		$leaves = db_query("
	    SELECT * from {$leave_table} where leave_type IS NULL and post_id IS NULL and leave_id <> 'OD' and leave_id <> 'SL' and leave_id <> 'LWP'"
		);
	  $leave_type_op[] = '--SELECT--';
	  foreach($leaves as $leave){
			$leave_type_op[] = $leave->leave_id;
	  }
		$form['leave_type'] = array(
			'#type' => 'select',
			'#title' => t('Select a leave type'),
			'#description' => t('The selected leave type will be overrriden with new values. If you leave this as "--SELECT--", a special leave type will be created for mentioned post.'),
			'#options' => drupal_map_assoc(array_unique(array_filter($leave_type_op))),
			'#default_value' => isset($leave_type)? $leave_type: NULL,
			'#disabled' => TRUE,
		);
		
		$form['id'] = array(
	    '#type' => 'textfield',
	    '#title' => 'Leave ID',
			'#states' => array(
				'visible' => array(
				  ':input[name = "leave_type"]' => array('value' => '--SELECT--'),
				),
			),
			'#default_value' => isset($leave_id)? $leave_id: NULL,
			'#disabled' => TRUE,
	  );
	  
	  $form['name'] = array(
	    '#type' => 'textfield',
	    '#title' => 'Leave Name',
			'#states' => array(
				'visible' => array(
				  ':input[name = "leave_type"]' => array('value' => '--SELECT--'),
				),
			),
			'#default_value' => isset($leave_name)? $leave_name: NULL,
	  );
	  
		$form['desc'] = array(
		  '#type' => 'textarea',
		  '#title' => t('Leave Description'),
		  '#resizable' => FALSE,
			'#default_value' => isset($leave_desc)? $leave_desc: NULL,
		);
		
		$form['nod_year'] = array(
		  '#type' => 'textfield',
		  '#title' => t('No. of days(per year)'),
			'#default_value' => isset($nod_per_year)? $nod_per_year: NULL,
		);
		
		$form['max_month'] = array(
		  '#type' => 'textfield',
		  '#title' => t('Max in a month'),
			'#description' => 'This sets a threshold for maximum no. of leave a staff can take in one month.(Leave it blank, if not required.)',
			'#default_value' => isset($max_per_month)? $max_per_month: NULL,
		);
		
		$form['at_a_stretch'] = array(
		  '#type' => 'textfield',
		  '#title' => t('Min at a stretch'),
			'#description' => 'This sets a threshold for minimum no. of leave a staff shall take at a stretch.(Leave it blank, if not required.)',
			'#default_value' => isset($at_a_stretch)? $at_a_stretch: NULL,
		);
		
		$form['half_day_rule'] = array(
			'#type' => 'textfield',
			'#title' => '<h3> half-day = 1 full day.</h3>',
			'#size' => 1,
			'#default_value' => isset($half_day_rule)? $half_day_rule: NULL,
		);
		
		$form['save'] = array(
		  '#type' => 'submit',
		  '#value' => t('Save'),
		);
		
		return $form;
	}elseif($post_id != NULL && $leave_type == NULL && $leave_id != 'OD' && $leave_id != 'SL' && $leave_id != 'LWP'){
		$form['leavetype'] = array(
			'#type' => 'value',
			'#value' => 'leave+post-leave_type',
		);
		
		$post_details = db_query("
	    SELECT * from dnp_term_data where tid = :tid;", array(':tid' => $post_id)
		);
		foreach($post_details as $pd){
			$this_post = $pd->name;
		}
		
		$form['help'] = array(
	    '#markup' => '<h3 style = "background: #008B8B; color: white; padding: 5px; font-weight: 400;">This will override the default leave type for mentioned post.</h3>',
	  );
		
		$form['post'] =  array(
		  '#type' => 'markup',
		  '#markup' => '<h1 style = "text-align: right;">For the post - '.$this_post.'</h1>',
		);
		
		$form['id'] = array(
	    '#type' => 'textfield',
	    '#title' => 'Leave ID',
			'#default_value' => isset($leave_id)? $leave_id: NULL,
			'#disabled' => TRUE,
	  );
	  
	  $form['name'] = array(
	    '#type' => 'textfield',
	    '#title' => 'Leave Name',
			'#states' => array(
				'visible' => array(
				  ':input[name = "leave_type"]' => array('value' => '--SELECT--'),
				),
			),
			'#default_value' => isset($leave_name)? $leave_name: NULL,
	  );
	  
		$form['desc'] = array(
		  '#type' => 'textarea',
		  '#title' => t('Leave Description'),
		  '#resizable' => FALSE,
			'#default_value' => isset($leave_desc)? $leave_desc: NULL,
		);
		
		$form['nod_year'] = array(
		  '#type' => 'textfield',
		  '#title' => t('No. of days(per year)'),
			'#default_value' => isset($nod_per_year)? $nod_per_year: NULL,
		);
		
		$form['max_month'] = array(
		  '#type' => 'textfield',
		  '#title' => t('Max in a month'),
			'#description' => 'This sets a threshold for maximum no. of leave a staff can take in one month.(Leave it blank, if not required.)',
			'#default_value' => isset($max_per_month)? $max_per_month: NULL,
		);
		
		$form['at_a_stretch'] = array(
		  '#type' => 'textfield',
		  '#title' => t('Min at a stretch'),
			'#description' => 'This sets a threshold for minimum no. of leave a staff shall take at a stretch.(Leave it blank, if not required.)',
			'#default_value' => isset($at_a_stretch)? $at_a_stretch: NULL,
		);
		
		$form['half_day_rule'] = array(
			'#type' => 'textfield',
			'#title' => '<h3> half-day = 1 full day.</h3>',
			'#size' => 1,
			'#default_value' => 2,
			'#default_value' => isset($half_day_rule)? $half_day_rule: NULL,
		);
		
		$form['save'] = array(
		  '#type' => 'submit',
		  '#value' => t('Save'),
		);
		
		return $form;
	}elseif($leave_id == 'OD'){
		$form['leavetype'] = array(
			'#type' => 'value',
			'#value' => 'OD',
		);
		
		$form['id'] = array(
      '#type' => 'textfield',
      '#title' => 'Leave ID',
      '#default_value' => t('OD'),
			'#disabled' => TRUE,
    );
    
    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => 'Leave Name',
      '#default_value' => t('On Duty'),
    );
    
    $form['desc'] = array(
      '#type' => 'textarea',
      '#title' => t('Leave Description'),
      '#default_value' => t('This is a special leave type. It will not be considered as Leave, the employee who applies for OD shall get prior approval from concerned authority.'),
    );
		
		$form['half_day_rule'] = array(
			'#type' => 'textfield',
			'#title' => '<h3> half-day = 1 full day.</h3>',
			'#size' => 1,
			'#default_value' => isset($half_day_rule)? $half_day_rule: NULL,
		);
    
    $form['save'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
		
		return $form;
	}elseif($leave_id == 'SL'){
		$form['leavetype'] = array(
			'#type' => 'value',
			'#value' => 'SL',
		);
		
		$form['id'] = array(
      '#type' => 'textfield',
      '#title' => 'Leave ID',
      '#default_value' => t('SL'),
			'#disabled' => TRUE,
    );
    
    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => 'Leave Name',
      '#default_value' => t('Special Leave'),
    );
    
    $form['desc'] = array(
      '#type' => 'textarea',
      '#title' => t('Leave Description'),
      '#default_value' => t('This is a special leave type. This leave type can be used for special purposes like Materninty Leave or Paternity Leave.'),
    );
		
		$form['half_day_rule'] = array(
			'#type' => 'textfield',
			'#title' => '<h3> half-day = 1 full day.</h3>',
			'#size' => 1,
			'#default_value' => isset($half_day_rule)? $half_day_rule: NULL,
		);
    
    $form['save'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
		
		return $form;
	}elseif($leave_id == 'LWP'){
		$form['leavetype'] = array(
			'#type' => 'value',
			'#value' => 'LWP',
		);
		
		$form['id'] = array(
      '#type' => 'textfield',
      '#title' => 'Leave ID',
      '#default_value' => t('LWP'),
			'#disabled' => TRUE,
    );
    
    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => 'Leave Name',
      '#default_value' => t('Leave Without Pay'),
    );
    
    $form['desc'] = array(
      '#type' => 'textarea',
      '#title' => t('Leave Description'),
      '#default_value' => t('This is a special leave type. This leave type can be used for emergency purposes when all other leave has exceeded the limits. But in this case salary will not be paid.'),
    );
    
		$form['half_day_rule'] = array(
			'#type' => 'textfield',
			'#title' => '<h3> half-day = 1 full day.</h3>',
			'#size' => 1,
			'#default_value' => isset($half_day_rule)? $half_day_rule: NULL,
		);
		
		$form['salary_deduction'] = array(
			'#type' => 'select',
			'#options' => drupal_map_assoc(array('Total Payable(i.e Earning - Deduction + Bonus/Incentive)','Total Earning','Total Payable - Bonus','Basic Salary')),
			'#title' => t('Salary Deduction On'),
			'#description' => t('Salary to be deducted(per day)'),
			'#default_value' => variable_get('lwp_deduction'),
		);
		
		$form['deduction_amount'] = array(
			'#type' => 'textfield',
			'#required' => TRUE,
			'#size' => 10,
			'#title' => t('Deduction Amount'),
			'#default_value' => variable_get('lwp_deduction_amount'),
		);
		
    $form['save'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
		
		return $form;
	}
}

/**
 *Implements submit function
 */
function each_leave_form_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$session_id = variable_get('essa_sid');
	$leave_table = 'essa_'.$session.'_leave_types';
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
		
	if($form_state['values']['leavetype'] == 'leave'){
		$leaves = db_query("
			SELECT * from {$leave_table} where leave_id = :lid;", array(':lid' => $form_state['values']['id'])
		);
		foreach($leaves as $leave){
			if($leave->nod_per_year != (int)$form_state['values']['nod_year']){
				$staffs = db_query("
				  SELECT * from {$leave_staff_table} where leave_id = :lid and total_leave = :tl;", array(':lid' => $form_state['values']['id'], ':tl' => $leave->nod_per_year)
				);
				foreach($staffs as $staff){
					$new_tl = (int)$form_state['values']['nod_year'];
					$new_leave_remaining = $new_tl - $staff->leave_taken;
					db_update($leave_staff_table)
						->fields(array(
							'total_leave' => $new_tl,
							'leave_remaining' => $new_leave_remaining,	
							))
						->condition(db_and()
						  ->condition('leave_id', $form_state['values']['id'])
							->condition('total_leave', $leave->nod_per_year)
						)
					->execute();
				}
			}
		}
		db_merge($leave_table)
		  ->key(array('leave_id' => $form_state['values']['id']))
		  ->fields (array(
		    'leave_id' => $form_state['values']['id'],
		    'leave_name' => $form_state['values']['name'],
		    'leave_desc' => $form_state['values']['desc'],
		    'max_per_month' => (int)$form_state['values']['max_month'],
				'min_stretch' => (int)$form_state['values']['at_a_stretch'],
		    'nod_per_year' => (int)$form_state['values']['nod_year'],
				'half_day_rule' => (int)$form_state['values']['half_day_rule'],
		  )
		)
		->execute();
	}
	
	if($form_state['values']['leavetype'] == 'leave+post+leave_type'){
		$leaves = db_query("
			SELECT * from {$leave_table} where leave_id = :lid;", array(':lid' => $form_state['values']['id'])
		);
		foreach($leaves as $leave){
			if($leave->nod_per_year != (int)$form_state['values']['nod_year']){
				$staffs = db_query("
				  SELECT * from {$leave_staff_table} where leave_id = :lid and total_leave = :tl;", array(':lid' => $leave->leave_type, ':tl' => $leave->nod_per_year)
				);
				foreach($staffs as $staff){
					$new_tl = (int)$form_state['values']['nod_year'];
					$new_leave_remaining = $new_tl - $staff->leave_taken;
					db_update($leave_staff_table)
						->fields(array(
							'total_leave' => $new_tl,
							'leave_remaining' => $new_leave_remaining,	
							))
						->condition(db_and()
						  ->condition('leave_id', $leave->leave_type)
							->condition('total_leave', $leave->nod_per_year)
						)
					->execute();
				}
			}
		}
		
		db_merge($leave_table)
		  ->key(array('leave_id' => $form_state['values']['id']))
		  ->fields (array(
		    'leave_id' => $form_state['values']['id'],
		    'leave_name' => $form_state['values']['name'],
		    'leave_desc' => $form_state['values']['desc'],
		    'max_per_month' => (int)$form_state['values']['max_month'],
				'min_stretch' => (int)$form_state['values']['at_a_stretch'],
		    'nod_per_year' => (int)$form_state['values']['nod_year'],
				'half_day_rule' => (int)$form_state['values']['half_day_rule'],
		  )
		)
		->execute();
	}
	
	if($form_state['values']['leavetype'] == 'leave+post-leave_type'){
		$leaves = db_query("
			SELECT * from {$leave_table} where leave_id = :lid;", array(':lid' => $form_state['values']['id'])
		);
		foreach($leaves as $leave){
			if($leave->nod_per_year != (int)$form_state['values']['nod_year']){
				$staffs = db_query("
				  SELECT * from {$leave_staff_table} where leave_id = :lid and total_leave = :tl;", array(':lid' => $form_state['values']['id'], ':tl' => $leave->nod_per_year)
				);
				foreach($staffs as $staff){
					$new_tl = (int)$form_state['values']['nod_year'];
					$new_leave_remaining = $new_tl - $staff->leave_taken;
					db_update($leave_staff_table)
						->fields(array(
							'total_leave' => $new_tl,
							'leave_remaining' => $new_leave_remaining,	
							))
						->condition(db_and()
						  ->condition('leave_id', $form_state['values']['id'])
							->condition('total_leave', $leave->nod_per_year)
						)
					->execute();
				}
			}
		}
		
		db_merge($leave_table)
		  ->key(array('leave_id' => $form_state['values']['id']))
		  ->fields (array(
		    'leave_id' => $form_state['values']['id'],
		    'leave_name' => $form_state['values']['name'],
		    'leave_desc' => $form_state['values']['desc'],
		    'max_per_month' => (int)$form_state['values']['max_month'],
				'min_stretch' => (int)$form_state['values']['at_a_stretch'],
		    'nod_per_year' => (int)$form_state['values']['nod_year'],
				'half_day_rule' => (int)$form_state['values']['half_day_rule'],
		  )
		)
		->execute();
	}
	
	if($form_state['values']['leavetype'] == 'OD'){
		$session = variable_get('essa_sid');
		$leave_table = 'essa_'.$session.'_leave_types';
		db_merge($leave_table)
		  ->key(array('leave_id' => $form_state['values']['id']))
		  ->fields (array(
		    'leave_id' => $form_state['values']['id'],
		    'leave_name' => $form_state['values']['name'],
		    'leave_desc' => $form_state['values']['desc'],
		  )
		)
		->execute();
	}
	
	if($form_state['values']['leavetype'] == 'SL'){
		$session = variable_get('essa_sid');
		$leave_table = 'essa_'.$session.'_leave_types';
		db_merge($leave_table)
		  ->key(array('leave_id' => $form_state['values']['id']))
		  ->fields (array(
		    'leave_id' => $form_state['values']['id'],
		    'leave_name' => $form_state['values']['name'],
		    'leave_desc' => $form_state['values']['desc'],
		  )
		)
		->execute();
	}
	
	if($form_state['values']['leavetype'] == 'LWP'){
		$session = variable_get('essa_sid');
		$leave_table = 'essa_'.$session.'_leave_types';
		db_merge($leave_table)
		  ->key(array('leave_id' => $form_state['values']['id']))
		  ->fields (array(
		    'leave_id' => $form_state['values']['id'],
		    'leave_name' => $form_state['values']['name'],
		    'leave_desc' => $form_state['values']['desc'],
		  )
		)
		->execute();
		
		variable_set('lwp_deduction', $form_state['values']['salary_deduction']);
		variable_set('lwp_deduction_amount', (int)$form_state['values']['deduction_amount']);
	}
	//*******Suraj********//
	drupal_set_message('Leave type '.$form_state['values']['name'].' - '.$form_state['values']['id'].' was successfully modified!!!');	
	drupal_cron_run();
}
