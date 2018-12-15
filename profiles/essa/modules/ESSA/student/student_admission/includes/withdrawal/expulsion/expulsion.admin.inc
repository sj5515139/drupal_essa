<?php
/**
 *Implements page callback function - expulsion_form
 */
function expulsion_form($form = array(), &$form_state){
	$form['adm_no'] = array(
		'#type' => 'textfield',
    '#title' => 'Admission No.',
    '#autocomplete_path' => 'adm_no/autocomplete',
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
function expulsion_form_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$student_withdrawal_table = 'essa_'.$session_id.'_student_withdrawal';
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	
	global $user;
	$prid = NULL;
	$principal = FALSE;
	$principal_role = db_query(
		"SELECT * from role where name = 'Principal';"
	);
	foreach($principal_role as $pr){
		$prid = $pr->rid;
	}
	
	$user_role = db_query(
		"SELECT * from users_roles where uid = :uid and rid = :rid;", array(':uid' => $user->uid, ':rid' => $prid)
	);
	foreach($user_role as $ur){
		$principal = TRUE;
	}
	
	$fi_uid = array();
	$fee_incharge_role = db_query("SELECT * FROM role WHERE name = 'Fees Incharge'");
	foreach($fee_incharge_role as $fi_role){
		$fi_rid = $fi_role->rid;
	}
	
	$user_rd = array();
	$feeincharge = 0;
	$user_rid = db_query("SELECT * FROM users_roles WHERE uid = :u;", array(':u' => $user->uid));
	foreach($user_rid as $r){
		$user_rd[] = $r->rid;
		foreach($user_rd as $u_rid){
			if($u_rid == $fi_rid){
				$feeincharge = 1;
			}
		}
	}
	
	$date = date('d-m-Y h:i:s');
	$timestamp = strtotime($date);
	global $user;
	
	if($principal == TRUE){
		$clear = student_clearance($form_state['values']['adm_no']);
		if($clear == 0){
			$stud_info = db_query(
				"SELECT * from $student_table where adm_no = :adm_no;", array(':adm_no' => $form_state['values']['adm_no'])
			);
			foreach($stud_info as $si){
				$uid = $si->uid;
				$puid = $si->puid;
			}
			
			db_update('users')
				->fields (array(
					'status' => 0,
					))
				->condition('uid', $uid, '=')
				->execute();
				
			db_update('users')
				->fields (array(
					'status' => 0,
					))
				->condition('uid', $puid, '=')
				->execute();
			
			db_update($student_table)
				->fields (array(
					'status' => 0,
					))
				->condition('adm_no', $form_state['values']['adm_no'], '=')
				->execute();
			
			
			
			db_insert($student_withdrawal_table)
				->fields (array(
					'adm_no' => $form_state['values']['adm_no'],
					'type' => 'expulsion',
					'reason' => $form_state['values']['reason'],
					'status_fin' => NULL,
					'status_fin_reason' => NULL,
					'fin_timestamp' => NULL,
					'fin_uid' => NULL,
					'status' => 'blocked',
					'status_reason' => $form_state['values']['reason'],
					'status_timestamp' => $timestamp,
					'status_uid' => $user->uid,
				)
			)	
			->execute();
			drupal_set_message($form_state['values']['adm_no'].' has been expelled from the school.','status');
			
			//sending system alert
			global $user;
			$created_date = date("Y-m-d H:i:s");
			$strtodate = strtotime($created_date);
			db_insert($sys_alert_table)
			->fields(array(
				'message' => $form_state['values']['adm_no'].' has been expelled from the school.',
				'priority' => 'M',
				'module' => 'withdrawal',
				'source_url' => 'admin/students/withdrawal/expulsion',
				'timestamp' => $strtodate,
				'source_uid' => $user->uid,
			))
			->execute();
		}else{
			db_insert($student_withdrawal_table)
				->fields (array(
					'adm_no' => $form_state['values']['adm_no'],
					'type' => 'expulsion',
					'reason' => $form_state['values']['reason'],
					'status_fin' => NULL,
					'status_fin_reason' => NULL,
					'fin_timestamp' => NULL,
					'fin_uid' => NULL,
					'status' => 'Approved by principal',
					'status_reason' => $form_state['values']['reason'],
					'status_timestamp' => $timestamp,
					'status_uid' => $user->uid,
				)
			)	
			->execute();
			drupal_set_message('Expulsion application for admission number '.$form_state['values']['adm_no'].' has been sent to Finance for review as there was dues against the student.','status');
			
			//sending system alert
			global $user;
			$created_date = date("Y-m-d H:i:s");
			$strtodate = strtotime($created_date);
			db_insert($sys_alert_table)
			->fields(array(
				'message' => 'Expulsion application for admission number '.$form_state['values']['adm_no'].' has been sent to Finance for review as there was dues against the student.',
				'priority' => 'M',
				'module' => 'withdrawal',
				'source_url' => 'admin/students/withdrawal/expulsion',
				'timestamp' => $strtodate,
				'source_uid' => $user->uid,
			))
			->execute();
		}	
	}elseif($feeincharge == 1){
		db_insert($student_withdrawal_table)
			->fields (array(
			  'adm_no' => $form_state['values']['adm_no'],
				'type' => 'expulsion',
				'reason' => $form_state['values']['reason'],
				'status_fin' => 'approved',
				'status_fin_reason' => NULL,
				'fin_timestamp' => NULL,
				'fin_uid' => NULL,
				'status' => 'Approved by Finance',
				'status_reason' => $form_state['values']['reason'],
				'status_timestamp' => $timestamp,
				'status_uid' => $user->uid,
			)
		)	
		->execute();
		drupal_set_message('Expulsion application for admission number '.$form_state['values']['adm_no'].' has been sent to principal for approval.','status');
		
		//sending system alert
			global $user;
			$created_date = date("Y-m-d H:i:s");
			$strtodate = strtotime($created_date);
			db_insert($sys_alert_table)
			->fields(array(
				'message' => 'Expulsion application for admission number '.$form_state['values']['adm_no'].' has been sent to principal for approval.',
				'priority' => 'M',
				'module' => 'withdrawal',
				'source_url' => 'admin/students/withdrawal/expulsion',
				'timestamp' => $strtodate,
				'source_uid' => $user->uid,
			))
		->execute();
		
	}else{
		$date = date('d-m-Y h:i:s');
		$timestamp = strtotime($date);
		global $user;
		db_insert($student_withdrawal_table)
			->fields (array(
			  'adm_no' => $form_state['values']['adm_no'],
				'type' => 'expulsion',
				'reason' => $form_state['values']['reason'],
				'status_fin' => NULL,
				'status_fin_reason' => NULL,
				'fin_timestamp' => NULL,
				'fin_uid' => NULL,
				'status' => 'pending',
				'status_reason' => $form_state['values']['reason'],
				'status_timestamp' => $timestamp,
				'status_uid' => $user->uid,
			)
		)	
		->execute();
		drupal_set_message('Expulsion application for admission number '.$form_state['values']['adm_no'].' has been sent to Finance for approval.','status');
		
		//sending system alert
			global $user;
			$created_date = date("Y-m-d H:i:s");
			$strtodate = strtotime($created_date);
			db_insert($sys_alert_table)
			->fields(array(
				'message' => 'Expulsion application for admission number '.$form_state['values']['adm_no'].' has been sent to Finance for approval.',
				'priority' => 'M',
				'module' => 'withdrawal',
				'source_url' => 'admin/students/withdrawal/expulsion',
				'timestamp' => $strtodate,
				'source_uid' => $user->uid,
			))
		->execute();
	}

	drupal_flush_all_caches();
}
/**
 *Implements ajax callback
 */
function ex_student_detail_ajax($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	variable_set('fee_adm_no_error', NULL);
	$stud_detail = db_query(
		"SELECT * from $student_table where adm_no = :adm_no;", array(':adm_no' => $form_state['values']['adm_no'])
	);
	$clear = student_clearance($form_state['values']['adm_no']);	
	
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
		
		global $base_url;
		$url = $base_url.'/expulsion/'.$form_state['values']['adm_no'].'@clearance';
		
		if($clear == 1){
			$form['fs']['msg'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 style ="color:red;">The student has some dues, click <a href = "'.$url.'">here</a> to check.</h3>',
				'#validated' => TRUE,
			);
		}
		
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