<?php
/**
 *Implements page callback function - add_more_dates()
 */
function add_more_dates($form, &$form_state, $term_id, $exam_code, $class){
	
	$form['back'] = array(
		'#type' => 'markup',
		'#markup' => '<p class = "back_button"><a href="javascript:history.go(-1)">Back</a></p>',
	);
	
	$form['date'] = array(
		'#type' => 'textfield',
		'#title' => 'Title',
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	
	$form['exam_code'] = array(
		'#type' => 'value',
		'#value' => $exam_code,
	);
	
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id,
	);
	
	$form['class'] = array(
		'#type' => 'value',
		'#value' => $class,
	);
	
	return $form;
}

/**
 *Implements page callback function - add_more_dates_validate()
 */
function add_more_dates_validate($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$imp_date_table = 'essa_'.$session_id.'_exam_imp_dates';
	
	$dates = db_query("SELECT * FROM {$imp_date_table} WHERE term_id = :t AND exam_code =:ec AND class = :c;", array(':t' => $form_state['values']['term_id'], ':ec' => $form_state['values']['exam_code'], ':c' => $form_state['values']['class']));
	foreach($dates as $date){
		if($date->title == $form_state['values']['date']){
			form_set_error('date', 'This date is already present in the system.');	
		}
	}
}

/**
 *Implements page callback function - add_more_dates_submit()
 */
function add_more_dates_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$imp_date_table = 'essa_'.$session_id.'_exam_imp_dates';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	
	db_insert($imp_date_table)
	->fields(array(
	  'term_id' => $form_state['values']['term_id'],
	  'exam_code' => $form_state['values']['exam_code'],
	  'class' => $form_state['values']['class'],
	  'title' => $form_state['values']['date']
	))
	->execute();
}