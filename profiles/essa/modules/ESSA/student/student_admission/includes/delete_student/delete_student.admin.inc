<?php
/**
 *Implements page callback function - delete_student
 */
function delete_student($form, $form_state){
	global $user;
	if(variable_get('delete_student'.$user->uid) != NULL){
		$form['adm_no'] = array(
			'#type' => 'textfield',
			'#title' => 'Admission No.',
			'#default_value' => variable_get('delete_student'.$user->uid),
			'#autocomplete_path' => 'adm_no/autocomplete',
			'#id' => 'adm_no',
			'#required' => TRUE,
			'#ajax' => array(
				'event' => 'blur',
				'callback' => 'student_detail_ajax',
				'wrapper' => 'ex_sd_wrapper',
				'method' => 'replace',
				'effect' => 'fade',
			),
			'#size' => 15,
			'#prefix' => '<p style = "width: 50%;"></p>',
		);
	}else{
		$form['adm_no'] = array(
			'#type' => 'textfield',
			'#title' => 'Admission No.',
			'#autocomplete_path' => 'adm_no/autocomplete',
			'#id' => 'adm_no',
			'#required' => TRUE,
			'#ajax' => array(
				'event' => 'blur',
				'callback' => 'student_detail_ajax',
				'wrapper' => 'ex_sd_wrapper',
				'method' => 'replace',
				'effect' => 'fade',
			),
			'#size' => 15,
			'#prefix' => '<p style = "width: 50%;"></p>',
		);
	}
	
	$form['ex_sd_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "ex_sd_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['line break'] = array(
		'#type' => 'markup',
		'#markup' => '<p><br><br><br></p>',
	);
	
	$form['delete'] = array(
    '#type' => 'submit',
    '#value' => 'Delete',
		'#submit' => array('confirm_delete'),
  );
	variable_set('delete_student'.$user->uid, NULL);
	//dsm($adm_no);
	return $form;
}

/**
 *Implements callback function confirm_delete()
 */
function confirm_delete($form, $form_state){
	global $user;
	variable_set('delete_adm_no'.$user->uid, $form_state['values']['adm_no']);
	global $base_url;
	$url = $base_url.'/delete_student';
  drupal_goto($url);
	//$form_state['redirect'] = $url;
}

function delete_student_pagecallback(){
	return drupal_get_form('delete_student_confirm');
}

function delete_student_confirm($form, &$form_state){
	global $user;
	$heading = t('Are you sure to delete this student?');
	$caption = '<h3><b>It will delete all the data of this student from the system permanently.</b></h3>';
	//dsm(variable_get('delete_adm_no'.$user->uid));
	$cancel_path = 'admin/students/admission/delete_student';
	variable_set('delete_student'.$user->uid, variable_get('delete_adm_no'.$user->uid));
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

function delete_student_confirm_submit($form, &$form_state){
	global $user;
	variable_set('delete_student'.$user->uid, NULL);
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	$fees_student = 'essa_'.$session_id.'_fees_student';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_payment_history = 'essa_'.$session_id.'_fees_payment_history';
	$fees_adjustment = 'essa_'.$session_id.'_fees_student_adjustement';
	$fees_advance = 'essa_'.$session_id.'_fees_student_advance';
	$fees_student_concession = 'essa_'.$session_id.'_fees_student_concession';
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	
	$adm_no = variable_get('delete_adm_no'.$user->uid);
	//dsm($adm_no);
	$student = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;", array(':adm' => $adm_no));
	foreach($student as $st){
		$st_uid = $st->uid;
		$stp_uid = $st->puid;
		//dsm($st);
	}
	
	
	db_delete($fees_student_fine)
	->condition('id', $adm_no)
	->execute();
	
	db_delete($fees_payment_history)
	->condition('adm_no', $adm_no)
	->execute();
	
	db_delete($fees_student)
	->condition('adm_no', $adm_no)
	->execute();
	
	db_delete($fees_adjustment)
	->condition('adm_no', $adm_no)
	->execute();
	
	db_delete($fees_advance)
	->condition('adm_no', $adm_no)
	->execute();
	
	db_delete($fees_student_concession)
	->condition('adm_no', $adm_no)
	->execute();
	
	db_delete($fees_student_due)
	->condition('adm_no', $adm_no)
	->execute();
	
	db_delete($fees_student_fine)
	->condition('adm_no', $adm_no)
	->execute();
	
	db_delete($fees_student_payment)
	->condition('adm_no', $adm_no)
	->execute();
	
	db_delete($student_table)
	->condition('adm_no', $adm_no)
	->execute();
	
	user_delete($st_uid);
	user_delete($stp_uid);
	
	
	drupal_set_message($adm_no.' has been successfully deleted from the system.','status');
	
	//sending system alert
	global $user;
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => $adm_no.' has been deleted from the system.',
		'priority' => 'H',
		'module' => 'student_admission',
		'source_url' => 'admin/students/admission/delete_student',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	
	global $base_url;
	$url = $base_url.'/admin/students/admission/delete_student';
  drupal_goto($url);
}

/**
 *Implements ajax callback
 */
function student_detail_ajax($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$stud_detail = db_query(
		"SELECT * from $student_table where adm_no = :adm_no;", array(':adm_no' => $form_state['values']['adm_no'])
	);
	
	foreach($stud_detail as $sd){
		if($sd->adm_no == $form_state['values']['adm_no']){
			$class = $sd->class;
			$sec = $sd->section;
			$name = $sd->student_name;
			$roll_no = $sd->roll_no;
		}
	}
	
	if(isset($name)){
		$form['fs'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "ex_sd_wrapper">',
			'#suffix' => '</div></div>',
		);
		$form['fs']['detail'] = array(
			'#type' => 'markup',
			'#markup' => '<p style = "float:left; width: 50px;">Name: </p><h4><b>'.$name.'</b></h4><p style = "float:left;width: 50px;"> Class: </p><h4><b>'.$class.' - '.$sec.'</b></h4><p style = "float:left; width: 50px;">Roll No. <h4><b>'.$roll_no.'</b></h4>',
			'#validated' => TRUE,
		);
		
		
		
	}else{
		$form['fs'] = array(
			'#type' => 'markup',
			'#markup' => '<h4 style = "float:left; width: 200px; color: RED;">Please enter a valid admission no.</h4>',
			'#prefix' => '<div id = "ex_sd_wrapper">',
			'#suffix' => '</div></div>',
			'#validated' => TRUE,
		);	
	}
	
	return $form['fs'];
}
