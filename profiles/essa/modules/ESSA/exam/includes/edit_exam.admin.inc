<?php
/**
 * Implements callback function edit_exam()
 */
function edit_exam($form = array(), &$form_state, $exam_code){
	$session = variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session.'_exam_master';
	$exams = db_query("SELECT * FROM ($master_exam_table) WHERE exam_code = :exam;", array(':exam' => $exam_code));
	foreach($exams as $exam){
		$exam_name = $exam->exam_name;
		$date_from = $exam->date_from;
		$date_to = $exam->date_to;
		$class_from = $exam->class_from;
		$class_to = $exam->class_to;
		$sittings = $exam->no_of_sitting;
	}
	
	$form['exam_code'] = array(
		'#type' => 'textfield',
		'#title' => 'Exam Code',
		'#required' => TRUE,
		'#default_value' => $exam_code,
		'#disabled' => TRUE,
		'#size' => '20',
 	);
	$form['exam_name'] = array(
		'#type' => 'textfield',
		'#title' => 'Exam Name',
		'#required' => TRUE,
		'#default_value' => $exam_name,
		'#size' => '20',
 	);
	$form['date_from'] = array(
		'#type' => 'date_popup',
		'#size' => 15,
		'#date_label_position' => 'within',
		'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
		'#date_format' => 'd-m-Y',
		'#date_year_range' => '0:+1',
		'#title' => 'Date From',
		'#default_value' => $date_from,
 	);
	$form['date_to'] = array(
		'#type' => 'date_popup',
		'#size' => 15,
		'#date_label_position' => 'within',
		'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
		'#date_format' => 'd-m-Y',
		'#date_year_range' => '0:+1',
		'#title' => 'Date To',
		'#default_value' => $date_to,
 	);
	$session = variable_get('essa_sid');
	$class_list_table = 'essa_'.$session.'_class_list';
	$class_list = db_query("SELECT * FROM {$class_list_table} ORDER BY weight");
	$class = array('--Select--');
	foreach($class_list as $cl){
		$class[] = $cl->class_id;
	}
	$form['class_from'] = array(
		'#type' => 'select',
		'#title' => 'Class From',
		'#options' => drupal_map_assoc($class),
		'#default_value' => $class_from,
 	);
	$form['class_to'] = array(
		'#type' => 'select',
		'#title' => 'Class To',
		'#options' => drupal_map_assoc($class),
		'#default_value' => $class_to,
 	);
	
	$sit = array('0' => '1', '1' => '2', '2' => '3', '3' => '4', '4' => '5');
	$form['no_of_sitting'] = array(
		'#type' => 'select',
		'#title' => 'No. of Sitting(Per Day)',
		'#options' => drupal_map_assoc($sit),
		'#default_value' => $sittings,
 	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	return $form;
}

/**
 *Implements form validation function.
 */
function edit_exam_validate($form, &$form_state){
	$session = variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session.'_exam_master';
	$ec = db_query("SELECT * FROM {$master_exam_table}");
	$exam_code = array();
	foreach($ec as $e){
		$exam_code[] = $e->exam_code;
	}
	
	$date_from = strtotime($form_state['values']['date_from']);
	$date_to = strtotime($form_state['values']['date_to']);
	if($date_from > $date_to){
		form_set_error('date_to','Please check the dates entered.');
	}
	if($form_state['values']['class_from'] == '--Select--' && $form_state['values']['class_to'] != '--Select--'){
		form_set_error('class_from','Please select class from.');
	}
	if($form_state['values']['class_from'] != '--Select--' && $form_state['values']['class_to'] == '--Select--'){
		form_set_error('class_to','Please select class to.');
	}
}

/**
 * Implements submit function edit_exam_submit()
 */
function edit_exam_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session.'_exam_master';
	
	db_merge($master_exam_table)
	->key(array('exam_code' => $form_state['values']['exam_code']))
	->fields(array(
		'exam_code' => $form_state['values']['exam_code'],
		'exam_name' => $form_state['values']['exam_name'],
		'date_from' => $form_state['values']['date_from'],
		'date_to' => $form_state['values']['date_to'],
		'term' => $form_state['values']['term_id'],
		'no_of_sitting' => $form_state['values']['no_of_sitting'],
	))
	->execute();
	
	if($form_state['values']['class_from'] == '--Select--'){
		db_merge($master_exam_table)
		->key(array('exam_code' => $form_state['values']['exam_code']))
		->fields(array(
			'class_from' => NULL,
			)
		)
		->execute();
	}else{
		db_merge($master_exam_table)
		->key(array('exam_code' => $form_state['values']['exam_code']))
		->fields(array(
			'class_from' => $form_state['values']['class_from'],
			)
		)
		->execute();
	}
	if($form_state['values']['class_to'] == '--Select--'){
		db_merge($master_exam_table)
		->key(array('exam_code' => $form_state['values']['exam_code']))
		->fields(array(
			'class_to' => NULL,
			)
		)
		->execute();
	}else{
		db_merge($master_exam_table)
		->key(array('exam_code' => $form_state['values']['exam_code']))
		->fields(array(
			'class_to' => $form_state['values']['class_to'],
			)
		)
		->execute();
	}
	
	drupal_set_message($form_state['values']['exam_code'].' exam has been updated successfully. You can now create schedule <a href = "admin/exam/'.$form_state['values']['exam_code'].'/exam_schedule"><u>here</u></a>.','status');
}