<?php
/**
 * Implements callback function create_term()
 */
function create_term($form = array(), &$form_state){
	
	$form['help'] = array(
		'#type' => 'markup',
		'#markup' => '<h3><b>Note :- </b>Terms are collection of exams where the final result depends upon each other.</h3></b><h5><i>For eg.- 10% of FA - I, 10% of FA - II & 20% of SA - I constitutes as Term 1 & 10% of FA - III, 10% of FA - IV & 40% of SA - II makes Term 2. the terms can be further cumulated to provide the final result. Like Term 1 + Term 2 gives us Term 3/Final results.</i></b>'
	);
	
	$form['term_name'] = array(
		'#type' => 'textfield',
		'#title' => 'Term Name',
		'#required' => TRUE,
 	);
	
	$session = variable_get('essa_sid');
	$class_list_table = 'essa_'.$session.'_class_list';
	$class_list = db_query("SELECT * FROM {$class_list_table} ORDER BY weight");
	foreach($class_list as $cl){
		$class[] = $cl->class_id;
	}
	$form['class_from'] = array(
		'#type' => 'select',
		'#title' => 'Class From',
		'#options' => drupal_map_assoc($class),
		'#required' => TRUE,
 	);
	$form['class_to'] = array(
		'#type' => 'select',
		'#title' => 'Class To',
		'#options' => drupal_map_assoc($class),
		'#required' => TRUE,
 	);
	
	$session = variable_get('essa_sid');
	$term_table = 'essa_'.$session.'_exam_terms';
	$terms = db_query("SELECT * FROM {$term_table}");
	$options = array();
	foreach($terms as $term){
		$options[] = $term->term_name;
	}
	$option = array_merge(array('--Select--'),$options);
	$form['term1'] = array(
		'#type' => 'select',
		'#title' => 'Summation(if any)',
		'#options' => drupal_map_assoc($option),
 	);
	
	$form['term2'] = array(
		'#type' => 'select',
		'#title' => '+',
		'#options' => drupal_map_assoc($option),
 	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	return $form;
}

function create_term_validate($form, &$form_state){
	$session = variable_get('essa_sid');
	$term_table = 'essa_'.$session.'_exam_terms';
	$class_table = 'essa_'.$session.'_class_list';
	
	if($form_state['values']['class_from'] == '--Select--' && $form_state['values']['class_to'] != '--Select--'){
		form_set_error('class_from','Please select class from.');
	}
	if($form_state['values']['class_from'] != '--Select--' && $form_state['values']['class_to'] == '--Select--'){
		form_set_error('class_to','Please select class to.');
	}
	if($form_state['values']['term1'] != '--Select--' && $form_state['values']['term2'] == '--Select--'){
		form_set_error('term2','Please select Term 2.');
	}
	if($form_state['values']['term1'] == '--Select--' && $form_state['values']['term2'] != '--Select--'){
		form_set_error('term1','Please select Term 1.');
	}
	
	if($form_state['values']['term1'] != '--Select--'){
		$term_id1 = db_query("SELECT * FROM {$term_table} WHERE term_name = :tn;", array(':tn' => $form_state['values']['term1']));
		foreach($term_id1 as $ti1){
			$class_from = $ti1->class_from;
			$class_to = $ti1->class_to;
		}
		$c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_from));
		foreach($c_from_weight as $cfw){
			$cf_weight = $cfw->weight;
		}
		$c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_to));
		foreach($c_to_weight as $ctw){
			$ct_weight = $ctw->weight;
		}
		$classes = array();
		$class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
			array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
		foreach($class_list as $c){
			$classes_term1[] = $c;
		}
		
		$term_id2 = db_query("SELECT * FROM {$term_table} WHERE term_name = :tn;", array(':tn' => $form_state['values']['term2']));
		foreach($term_id2 as $ti2){
			$class_from = $ti2->class_from;
			$class_to = $ti2->class_to;
		}
		$c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_from));
		foreach($c_from_weight as $cfw){
			$cf_weight = $cfw->weight;
		}
		$c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_to));
		foreach($c_to_weight as $ctw){
			$ct_weight = $ctw->weight;
		}
		$classes = array();
		$class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
			array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
		foreach($class_list as $c){
			$classes_term2[] = $c;
		}
		
		($form_state['values']['class_from'] == '--Select--') ? $class_from = NULL: $class_from = $form_state['values']['class_from'];
		($form_state['values']['class_to'] == '--Select--') ? $class_to = NULL: $class_to = $form_state['values']['class_to'];
		$c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_from));
		foreach($c_from_weight as $cfw){
			$cf_weight = $cfw->weight;
		}
		$c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_to));
		foreach($c_to_weight as $ctw){
			$ct_weight = $ctw->weight;
		}
		$classes = array();
		$class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
			array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
		foreach($class_list as $c){
			$classes_this_term[] = $c;
		}
		
		if($classes_term1 != $classes_term2){
			form_set_error('class_term1','Classes in these two terms does not match. You can\'t add these two terms.');
		}elseif($classes_this_term != $classes_term1){
			form_set_error('class_to','Classes in selected class range does not matches the class range of the two selected terms. You can\'t add these two terms.');
		}	
	}
}
/**
 * Implements submit function create_term_submit()
 */
function create_term_submit($form = array(), &$form_state){
	$session = variable_get('essa_sid');
	$term_table = 'essa_'.$session.'_exam_terms';
	$class_table = 'essa_'.$session.'_class_list';
	//dsm($form_state);
	
	if($form_state['values']['term1'] == '--Select--'){
		$t_id1 = NULL;
	}else{
		$term_id1 = db_query("SELECT * FROM {$term_table} WHERE term_name = :tn;", array(':tn' => $form_state['values']['term1']));
		foreach($term_id1 as $ti1){
			$t_id1 = $ti1->id;
		}
	}
	
	if($form_state['values']['term2'] == '--Select--'){
		$t_id2 = NULL;
	}else{
		$term_id2 = db_query("SELECT * FROM {$term_table} WHERE term_name = :tn;", array(':tn' => $form_state['values']['term2']));
		foreach($term_id2 as $ti2){
			$t_id2 = $ti2->id;
		}
	}
	
	($form_state['values']['class_from'] == '--Select--') ? $class_from = NULL: $class_from = $form_state['values']['class_from'];
	($form_state['values']['class_to'] == '--Select--') ? $class_to = NULL: $class_to = $form_state['values']['class_to'];
	db_insert($term_table)
	->fields(array(
		'term_name' => $form_state['values']['term_name'],
		'term_1' => $t_id1,
		'term_2' => $t_id2,
		'class_from' => $class_from,
		'class_to' => $class_to,
	))
	->execute();
	
	$term_id = db_query("SELECT * FROM {$term_table} WHERE term_name = :tn;", array(':tn' => $form_state['values']['term_name']));
	foreach($term_id as $ti){
		$t_id = $ti->id;
	}
	
	if(!is_dir("sites/default/files/exam/".$t_id)){
		mkdir("sites/default/files/exam/".$t_id);
	}
	
	$c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_from));
	foreach($c_from_weight as $cfw){
		$cf_weight = $cfw->weight;
	}
	$c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_to));
	foreach($c_to_weight as $ctw){
		$ct_weight = $ctw->weight;
	}
	$classes = array();
	$class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
		array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
	foreach($class_list as $c){
		$classes[] = $c->class_id;
	}
	
	foreach($classes as $cl){
		$subject_table = 'essa_'.$session.'_subjects_'.$cl;
		$subjects = db_query("SELECT * FROM {$subject_table};");
		$schema['marks'] = array(
			'description' => 'TODO: please describe this table!',
			'fields' => array(
				'adm_no' => array(
					'description' => 'TODO: please describe this field!',
					'type' => 'varchar',
					'length' => '50',
					'not null' => FALSE,
				),
				'section' => array(
					'description' => 'TODO: please describe this field!',
					'type' => 'varchar',
					'length' => '50',
					'not null' => FALSE,
				),
			),
			'primary key' => array('adm_no'),
		);
		$fields = array();
		$grade_fields = array();
		foreach($subjects as $subject){
			$fields[$subject->sub_id] = array(
				'description' => 'TODO: please describe this field!',
				'type' => 'float',
				'not null' => FALSE,
			);
			$grade_fields[$subject->sub_id] = array(
				'description' => 'TODO: please describe this field!',
				'type' => 'varchar',
				'length' => '20',
				'not null' => FALSE,
			);
		}
		
		foreach($fields as $sub_id => $field){
			$schema['marks']['fields'][$sub_id] = $field;
			$schema['marks']['fields']['grade_point_'.$sub_id] = $field;
		}
		
		foreach($grade_fields as $sub_id => $gf){
			$schema['marks']['fields']['grade_'.$sub_id] = $gf;
		}
		
		$term_id = db_query("SELECT * FROM {$term_table} WHERE term_name = :tn;", array(':tn' => $form_state['values']['term_name']));
		foreach($term_id as $ti){
			$t_id = $ti->id;
		}
		$name_of_table = 'essa_'.$session.'_exam_'.$t_id.'_'.$cl;
		if(!db_table_exists($name_of_table)){
			db_create_table($name_of_table, $schema['marks']);
		}
	}
	
	global $base_url;
	if($form_state['values']['term1'] != '--Select--'){
		$url = $base_url.'/admin/exam/'.$t_id.'/generate-term-result';
		drupal_set_message('Term "'.$form_state['values']['term_name'].'" was created successfully!!! You can now generate the result <a href ="'.$url.'">here</a>.', 'status');
	}else{
		$url = $base_url.'/admin/exam/'.$t_id.'/create_term_exam';
		drupal_set_message('Term "'.$form_state['values']['term_name'].'" was created successfully!!! You can now create exams <a href ="'.$url.'">here</a>.', 'status');
	}
	global $user;
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	//sending system alert
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'Term "'.$form_state['values']['term_name'].'" has been created.',
		'priority' => 'M',
		'module' => 'Exam',
		'source_url' => 'admin/exam/create_term',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	menu_rebuild();
}