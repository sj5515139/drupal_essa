<?php

/**
 *Page callback function - delete_term_exam
 */
function delete_term_exam($form = array(), &$form_state, $term_id, $exam_code){
	global $base_url;
	$session = variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session.'_exam_master';
	
	global $user;
	variable_set('delete_term_exam'.$user->uid, $term_id.'%'.$exam_code);
	global $base_url;
	$url = $base_url.'/delete_exam';
  drupal_goto($url);
	
	return $form;
}

function delete_term_exam_pagecallback(){
	return drupal_get_form('delete_term_exam_confirm');
}

function delete_term_exam_confirm($form, &$form_state){
	global $user;
	$heading = t('Are you sure to delete this exam?');
	$caption = "<h3><b>This action can't be undone.</b></h3>";
	//dsm(variable_get('delete_adm_no'.$user->uid));
	$value = variable_get('delete_term_exam'.$user->uid);
	$value = explode('%', $value);
	$term_id = $value[0];
	$exam_code = $value[1];
	$cancel_path = 'admin/exam/';
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

function delete_term_exam_confirm_submit($form, &$form_state){
	global $user;
	$session = variable_get('essa_sid');
	$class_list_table = 'essa_'.$session.'_class_list';
	$imp_date_table = 'essa_'.$session.'_exam_imp_dates';
	$schedule_table = 'essa_'.$session.'_exam_schedule';
	$timing_table = 'essa_'.$session.'_exam_timing';
	$master_exam_table = 'essa_'.$session.'_exam_master';
	
	$value = variable_get('delete_term_exam'.$user->uid);
	$value = explode('%', $value);
	$term_id = $value[0];
	$exam_code = $value[1];
	
	db_delete($master_exam_table)
	->condition(db_and()
		->condition('term', $term_id)
		->condition('exam_code', $exam_code)
	)
	->execute();
	
	
	$class_list = db_query("SELECT * FROM {$class_list_table}");
	foreach($class_list as $cl){
		$classes[] = $cl->class_id;
	}
	foreach($classes as $class){
		$table = 'esaa_'.$session.'_'.$term_id.'_'.$exam_code.'_'.$class;
		db_drop_table($table);
	}
	
	db_delete($imp_date_table)
	->condition(db_and()
		->condition('term', $term_id)
		->condition('exam_code', $exam_code)
	)
	->execute();
	
	db_delete($schedule_table)
	->condition(db_and()
		->condition('term', $term_id)
		->condition('exam_code', $exam_code)
	)
	->execute();
	
	db_delete($timing_table)
	->condition(db_and()
		->condition('term', $term_id)
		->condition('exam_code', $exam_code)
	)
	->execute();
	
	global $user;
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	//sending system alert
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'Exam '.$form_state['values']['term_id'].' - '.$form_state['values']['exam_code'].' has been deleted.',
		'priority' => 'H',
		'module' => 'Exam',
		'source_url' => 'delete_exam',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	
	global $base_url;
	$url = $base_url.'/admin/exam';
  drupal_goto($url);
	drupal_set_message($exam_code.' was deleted successfully','status');
}