<?php
/**
 *Implements page callback function - readmission_form
 */
function readmission_form($form = array(), &$form_state){
	$form['adm_no'] = array(
		'#type' => 'textfield',
    '#title' => 'Admission No.',
		'#id' => 'adm_no',
		'#required' => TRUE,
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'ex_student_detail_ajax',
      'wrapper' => 'ex_sd_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#size' => 15,
		'#prefix' => '<p style = "width: 50%;"></p>',
		'#autocomplete_path' => 'readmission/autocomplete',
	);
	
	$form['ex_sd_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "ex_sd_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['line break'] = array(
		'#type' => 'markup',
		'#markup' => '<p><br><br><br></p>',
	);
	
	$form['reason'] = array(
		'#type' => 'textarea',
		'#title' => t('Reason'),
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	
	return $form;
}

/**
 *Implements submit function
 */
function readmission_form_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$student_withdrawal_table = 'essa_'.$session_id.'_student_withdrawal';
	
	global $user;
	
	$stud_info = db_query(
		"SELECT * from $student_table where adm_no = :adm_no;", array(':adm_no' => $form_state['values']['adm_no'])
	);
	foreach($stud_info as $si){
		$uid = $si->uid;
		$puid = $si->puid;
	}
	
	db_update('users')
	->fields (array(
		'status' => 1,
		))
	->condition('uid', $uid, '=')
	->execute();
	
	db_update('users')
	->fields (array(
		'status' => 1,
		))
	->condition('uid', $puid, '=')
	->execute();
	
	db_update($student_table)
	->fields (array(
		'status' => 1,
		))
	->condition('adm_no', $form_state['values']['adm_no'], '=')
	->execute();
	
	db_update($student_withdrawal_table)
	->fields(array(
		'status' => 'readmitted',
		'status_reason' => $form_state['values']['reason'],
		'status_uid' => $user->uid,
	))
	->condition('adm_no', $form_state['values']['adm_no'], '=')
	->execute();
	
	drupal_set_message('Admission No '.$form_state['values']['adm_no'].' has ben readmited successfully!!!', 'status');
}
/**
 *Implements ajax callback
 */
function ex_student_detail_ajax($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	variable_set('fee_adm_no_error', NULL);
	$stud_detail = db_query(
		"SELECT * from $student_table where adm_no = :adm_no and status = 0;", array(':adm_no' => $form_state['values']['adm_no'])
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
			'#type' => 'markup',
			'#markup' => '<p style = "float:left; width: 50px;">Name: </p><h4><b>'.$name.'</b></h4><p style = "float:left;width: 50px;"> Class: </p><h4><b>'.$class.' - '.$sec.'</b></h4><p style = "float:left; width: 50px;">Roll No. <h4><b>'.$roll_no.'</b></h4>',
			'#prefix' => '<div id = "ex_sd_wrapper">',
			'#suffix' => '</div></div>',
			'#validated' => TRUE,
		);	
	}else{
		$form['fs'] = array(
			'#type' => 'markup',
			'#markup' => '<h4 style = "float:left; width: 200px; color: RED;">Please enter an admission no. who has been blocked from the system.</h4>',
			'#prefix' => '<div id = "ex_sd_wrapper">',
			'#suffix' => '</div></div>',
			'#validated' => TRUE,
		);	
	}
	
	return $form['fs'];
}