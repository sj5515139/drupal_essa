<?php
/**
 *Implements page callback function - delete_staff
 */
function delete_staff($form, $form_state){
	global $user;
	if(variable_get('delete_staff'.$user->uid) != NULL){
		$form['emp_id'] = array(
			'#type' => 'textfield',
			'#title' => 'Employee Id.',
			'#default_value' => variable_get('delete_staff'.$user->uid),
			'#autocomplete_path' => 'emp_id/autocomplete',
			'#id' => 'emp_id',
			'#required' => TRUE,
			'#ajax' => array(
				'event' => 'blur',
				'callback' => 'staff_detail_ajax',
				'wrapper' => 'ex_sd_wrapper',
				'method' => 'replace',
				'effect' => 'fade',
			),
			'#size' => 15,
			'#prefix' => '<p style = "width: 50%;"></p>',
		);
	}else{
		$form['emp_id'] = array(
			'#type' => 'textfield',
			'#title' => 'Employee Id.',
			'#autocomplete_path' => 'emp_id/autocomplete',
			'#id' => 'emp_id',
			'#required' => TRUE,
			'#ajax' => array(
				'event' => 'blur',
				'callback' => 'staff_detail_ajax',
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
		'#markup' => '<p><br></p>',
	);
	
	$form['delete'] = array(
    '#type' => 'submit',
    '#value' => 'Delete',
		'#submit' => array('confirm_delete'),
  );
	variable_set('delete_staff'.$user->uid, NULL);
	//dsm($emp_id);
	return $form;
}

/**
 *Implements callback function confirm_delete()
 */
function confirm_delete($form, $form_state){
	global $user;
	variable_set('delete_emp_id'.$user->uid, $form_state['values']['emp_id']);
	global $base_url;
	$url = $base_url.'/delete_staff';
  drupal_goto($url);
	//$form_state['redirect'] = $url;
}

function delete_staff_pagecallback(){
	return drupal_get_form('delete_staff_confirm');
}

function delete_staff_confirm($form, &$form_state){
	global $user;
	$heading = t('Are you sure to delete this employee?');
	$caption = '<h3><b>It will delete all the data of this employee from the system permanently.</b></h3>';
	//dsm(variable_get('delete_emp_id'.$user->uid));
	$cancel_path = 'admin/staff/recruitment/delete_staff';
	variable_set('delete_staff'.$user->uid, variable_get('delete_emp_id'.$user->uid));
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

function delete_staff_confirm_submit($form, &$form_state){
	global $user;
	$emp_id = variable_get('delete_emp_id'.$user->uid);
	variable_set('delete_staff'.$user->uid, NULL);
	$session_id = (string)variable_get('essa_sid');
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	$emp_timetable = 'essa_'.$session_id.'_time_table_'.$emp_id;
	$emp_salary_table = 'essa_'.$session_id.'_pr_emp_sal';
	$attendance_table = 'essa_'.$session_id.'_staff_attendance';
	$class_teacher_table = 'essa_'.$session_id.'_class_teacher';
	$staff_leave_table = 'essa_'.$session_id.'_leave_staff';
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	
	
	//dsm($emp_id);
	$staff = db_query("SELECT * FROM {$staff_table} WHERE emp_id = :adm;", array(':adm' => $emp_id));
	foreach($staff as $st){
		$st_uid = $st->uid;
		$st_nickname = $st->nickname;
	}
	
	db_delete($staff_leave_table)
	->condition('emp_id', $emp_id)
	->execute();
	
	if(isset($st_nickname)){
		db_delete($class_teacher_table)
		->condition('teacher_nickname', $st_nickname)
		->execute();
	}
	
	db_delete($attendance_table)
	->condition('emp_id', $emp_id)
	->execute();
	
	db_delete($emp_salary_table)
	->condition('emp_id', $emp_id)
	->execute();
	
	db_delete($staff_table)
	->condition('emp_id', $emp_id)
	->execute();
	
	db_drop_table($emp_timetable);
	user_delete($st_uid);
	
	
	drupal_set_message($emp_id.' has been successfully deleted from the system.','status');
	
	//sending system alert
	global $user;
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => $emp_id.' has been deleted from the system.',
		'priority' => 'H',
		'module' => 'staff_recruitment',
		'source_url' => 'admin/staff/recruitment/delete_staff',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	
	global $base_url;
	$url = $base_url.'/admin/staff/recruitment/delete_staff';
  drupal_goto($url);
}

/**
 *Implements ajax callback
 */
function staff_detail_ajax($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	$staff_detail = db_query(
		"SELECT * from $staff_table where emp_id = :emp_id;", array(':emp_id' => $form_state['values']['emp_id'])
	);
	
	foreach($staff_detail as $sd){
		if($sd->emp_id == $form_state['values']['emp_id']){
			$name = $sd->fname.' '.$sd->lname;
			$type = $sd->type;
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
			'#markup' => '<p style = "float:left; width: 50px;">Name: </p><h4><b>'.$name.'</b></h4><p style = "float:left; width: 50px;">Type. <h4><b>'.$type.'</b></h4>',
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
