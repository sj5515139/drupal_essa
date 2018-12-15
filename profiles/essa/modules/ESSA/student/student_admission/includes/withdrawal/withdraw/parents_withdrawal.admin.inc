<?php

/**
 *Implements page callback - parent_withdrawal_form
 */
function parent_withdrawal_form($form = array(), &$form_state){
	$form['subject'] = array(
		'#type' => 'textfield',
		'#title' => 'Subject',
	);
	
	$form['body'] = array(
		'#type' => 'textarea',
		'#title' => 'Body',
		'#rows' => 15,
		'#required' => TRUE,
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Submit',
	);
	return $form;
}

/**
 *Implements page callback - parent_withdrawal_form
 */
function parent_withdrawal_form_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$student_withdrawal_table = 'essa_'.$session_id.'_student_withdrawal';
	global $user;
	$student = db_query(
		"SELECT * from $student_table where puid = :uid;", array(':uid' => $user->uid)
	);
	foreach($student as $st){
		$adm_no = $st->adm_no;
	}
	
	$date = date('d-m-Y h:i:s');
	$timestamp = strtotime($date);
	db_insert($student_withdrawal_table)
		->fields (array(
		  'adm_no' => $adm_no,
			'type' => 'withdrawal',
			'subject' => $form_state['values']['subject'],
			'reason' => $form_state['values']['body'],
			'status_fin' => NULL,
			'status_fin_reason' => NULL,
			'fin_timestamp' => NULL,
			'fin_uid' => NULL,
			'status' => 'pending',
			'status_reason' => 'NULL',
			'status_timestamp' => $timestamp,
			'status_uid' => $user->uid,
		)
	)	
	->execute();
}