<?php
/**
 *Implements page callback function - reject_leave
 */
function reject_leave($form, $form_state){
	$session_id = (string)variable_get('essa_sid');
  $leave_type_table = 'essa_'.$session_id.'_leave_types';
	$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
  $staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	global $user;
  
	$lv = variable_get('leave_'.$user->uid);
  $temp = explode("%", $lv, 2);
	$emp_id = $temp[0];
  $req_timestamp = $temp[1];
	
	$emp_leave_record = db_query(
		"SELECT * from $leave_history_table where emp_id = :ei and req_timestamp = :rt;", array(':ei' => $emp_id, ':rt' => $req_timestamp)
	);
	foreach($emp_leave_record as $elr){
		$leave_id = $elr->leave_id;
	}
  
	$form['emp_id'] = array(
		'#type' => 'value',
		'#value' => $emp_id,
	);
	
	$form['req_timestamp'] = array(
		'#type' => 'value',
		'#value' => $req_timestamp,
	);
	
  $leave_record = db_query(
		"SELECT * from $leave_type_table where leave_id = :li;", array(':li' => $leave_id)
	);
	foreach($leave_record as $lr){
		$max = $lr->max_per_month;
	}
  
  $form['back'] = array(
    '#type' => 'submit',
    '#value' => 'Back',
    '#submit' => array('go_back'),
		'#limit_validation_errors' => array(),
  );
  
	$emp_leave_record = db_query(
		"SELECT * from $leave_history_table where emp_id = :ei and req_timestamp = :rt;", array(':ei' => $emp_id, ':rt' => $req_timestamp)
	);
	foreach($emp_leave_record as $elr){
		//*******Suraj********//
		$staffs = db_query("SELECT * FROM {$staff_master_table} WHERE emp_id = :emp;", array(':emp' => $elr->emp_id));
		foreach($staffs as $staff){
			$staff_name = $staff->fname.' '.$staff->lname;
		}
		$form['staff_name'] = array(
			'#type' => 'value',
			'#value' => $staff_name,
		);
		$form['name'] = array(
			'#type' => 'markup',
			'#markup' => '<h3 style = "padding-top: 20px;"><b>Employee Name</b> <span style = "margin-left: 80px;">'.$staff_name.' </span></h3>',
		);
		//*******Suraj********//
		
		$row1[] = array(
      '#tree' =>TRUE,
      $elr -> leave_id.$elr->emp_id => array(  //Generating unique array id for every form element
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'. $elr -> leave_id .'</h3>',
        ),
        'c2' =>array(
          '#type' => 'markup',
					'#markup' => '<h3>'.date('d-m-Y', $elr -> from_date).'</h3>',
        ),
        'c3' =>array(
          '#type' => 'markup',
					'#markup' => '<h3>'.date('d-m-Y', $elr -> to_date).'</h3>',
        ),
        'c4' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$elr -> no_of_days.'</h3>',
        ),
        'c5' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$elr -> no_of_working_days.'</h3>',
        ),
        'c7' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.date('d-m-Y', $elr -> req_timestamp).'</h3>',
        ),
        'c8' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$elr -> status.'</h3>',
        ),
				'c9' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$elr -> status_remark.'</h3>',
        ),
      ),
    );
	}
	$form['this'] = array(
    '#theme' => 'leave_history_table',
    'rows' => $row1,
  );
	
	$emp_leave_record = db_query(
		"SELECT * from $leave_history_table where emp_id = :ei and req_timestamp = :rt;", array(':ei' => $emp_id, ':rt' => $req_timestamp)
	);
	foreach($emp_leave_record as $elr){
		if($elr->no_of_days > $max){
			$form['suggestion'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 class = "suggestion"><b> SUGESSTION: </b> This leave request violates the leave rule. As per leave rule a maximum of '.$max.' days leave can be requested. However, this request is of '.$elr->no_of_days.' days.</h3>',
			);
		}	
	}
	
	$form['remarks'] = array(
		'#type' => 'textarea',
		'#title' => 'Remarks',
	);
	
	$form['submit'] = array(
    '#type' => 'submit',
		'#value' => 'Reject',
		'#prefix' => '<div class = "reject_leave">',
		'#suffix' => '</div>',
  );
	
	$emp_leave_record = db_query(
		"SELECT * from $leave_history_table where emp_id = :ei and req_timestamp <> :rt;", array(':ei' => $emp_id, ':rt' => $req_timestamp)
	);
	foreach($emp_leave_record as $elr){
		$row[] = array(
      '#tree' =>TRUE,
      $elr -> leave_id.$elr->emp_id => array(  //Generating unique array id for every form element
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'. $elr -> leave_id .'</h3>',
        ),
        'c2' =>array(
          '#type' => 'markup',
					'#markup' => '<h3>'.date('d-m-Y', $elr -> from_date).'</h3>',
        ),
        'c3' =>array(
          '#type' => 'markup',
					'#markup' => '<h3>'.date('d-m-Y', $elr -> to_date).'</h3>',
        ),
        'c4' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$elr -> no_of_days.'</h3>',
        ),
        'c5' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$elr -> no_of_working_days.'</h3>',
        ),
        'c7' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.date('d-m-Y', $elr -> req_timestamp).'</h3>',
        ),
        'c8' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$elr -> status.'</h3>',
        ),
				'c9' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$elr -> status_remark.'</h3>',
        ),
      ),
    );
	}
	
	if(isset($row)){
		$form['leave_history'] = array(
			'#type' => 'markup',
			'#markup' => '<h2 style = "margin-top: 100px;"><b>Leave History</b></h2>',
		);
		
		$form['lts'] = array(
		  '#theme' => 'leave_history_table',
		  'rows' => $row,
		);	
	}
	
	return $form;
}

function go_back($form, &$form_state){
  //$current_path = current_path();
  global $base_url;
	$base_url = $base_url.'/admin/staff/leave/approve_leave';
  $form_state['redirect'] = $base_url;
}

function reject_leave_submit($form, &$form_state){
  //$current_path = current_path();
	$flag = 0;
	$session_id = (string)variable_get('essa_sid');
  $leave_type_table = 'essa_'.$session_id.'_leave_types';
	$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
  $staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	global $user;
	
	$employee = db_query("SELECT * FROM {$staff_master_table} WHERE emp_id = :emp;",array(':emp' => $form_state['values']['emp_id']));
	foreach($employee as $emp){
		$emp_uid = $emp->uid;
		$emp_mail = $emp->email;
	}
	$date = date('m/d/Y',$form_state['values']['req_timestamp']);
	global $base_url;
	$url = $base_url.'/user/'.$emp_uid.'/leave';
	
	$leave_moderator_role = db_query(
		"SELECT * from role where name = 'Leave Moderator';"
	);
	foreach($leave_moderator_role as $lmr){
		$lm_rid = $lmr->rid;
 	}
	$leave_moderators = db_query(
		"SELECT * from users_roles where rid = :rid and uid = :uid;", array(':rid' => $lm_rid,':uid' => $user->uid)
	);
	foreach($leave_moderators as $lm){
		global $base_url;
		$base_url = $base_url.'/admin/staff/leave/approve_leave';
		$form_state['redirect'] = $base_url;
		
		global $user;
		$session_id = (string)variable_get('essa_sid');
		$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
		$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
		
		$staff_emp_id = db_query(
			"SELECT * from $staff_master_table where uid = :uid;", array(':uid' => $user->uid)
		);
		foreach($staff_emp_id as $sei){
			$emp_id = $sei->emp_id;
			$name = $sei->fname.' '.$sei->lname;
		}
		$application_time = date('m/d/Y h:i:s');
		$timestamp = strtotime($application_time);
	
		db_update($leave_history_table)
		  ->fields(array(
				'status' => 'Rejected By Moderator',
				'status_remark' => $name,
				'status_moderator' => 'Rejected',
				'remark_moderator' => $form_state['values']['remarks'],
				'moderator_timestamp' => $timestamp,
				))
			->condition(db_and()
			  ->condition('emp_id', $form_state['values']['emp_id'])
			  ->condition('req_timestamp', $form_state['values']['req_timestamp'])
	    )
	    ->execute();
			$flag = 1;
	}
	
	$leave_principal_role = db_query(
		"SELECT * from role where name = 'Principal';"
	);
	foreach($leave_principal_role as $lmr){
		$p_rid = $lmr->rid;
 	}
	
	$principal = db_query(
		"SELECT * from users_roles where rid = :rid and uid = :uid;", array(':rid' => $p_rid,':uid' => $user->uid)
	);
	foreach($principal as $princi){
		global $base_url;
		$base_url = $base_url.'/admin/staff/leave/approve_leave';
		$form_state['redirect'] = $base_url;
		
		global $user;
		$session_id = (string)variable_get('essa_sid');
		$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
		$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
		
		$staff_emp_id = db_query(
			"SELECT * from $staff_master_table where uid = :uid;", array(':uid' => $user->uid)
		);
		foreach($staff_emp_id as $sei){
			$emp_id = $sei->emp_id;
			$name = $sei->fname.' '.$sei->lname;
		}
		$application_time = date('m/d/Y h:i:s');
		$timestamp = strtotime($application_time);
	
		db_update($leave_history_table)
		  ->fields(array(
				'status' => 'Rejected',
				'status_remark' => 'Principal',
				'status_principal' => 'Rejected',
				'remark_principal' => $form_state['values']['remarks'],
				'principal_timestamp' => $timestamp,
				))
	    ->condition(db_and()
	      ->condition('emp_id', $form_state['values']['emp_id'])
	      ->condition('req_timestamp', $form_state['values']['req_timestamp'])
	    )
	    ->execute();
			$flag = 2;
	}
	
	//*******Suraj********//
	
	if($flag == 1){
		//sending message to employee when leave is applied to leave moderator
		$module = 'leave';
		$recipients= array();
		$recipients[] = user_load($emp_uid);
		$msg_subject = 'Sorry! Your leave application was rejected by '.$name.'.';
		$msg_body = 'Your leave application dated '.$date.' has been rejected. To check details, click <a href = "'.$url.'"><u>here</a><u/u>';
		$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
		$msg_body = $msg_body.' <br>'.$footer;
		privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
		
		//sending system alert
		$sys_alert_table = 'essa_'.$session_id.'_system_alert';
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
			'message' => 'Leave application of Employee ID '.$form_state['values']['emp_id'].' was rejected by Leave Moderator '.$name.'.',
			'priority' => 'L',
			'module' => 'leave',
			'source_url' => 'leave/reject',
			'timestamp' => $strtodate,
			'source_uid' => $user->uid,
		))
		->execute();
		
		//Sending email to employee.
		if($emp_mail != NULL){
			$email = $emp_mail;

			$body = 'Your leave application dated '.$date.' has been rejected. To check details, click <a href = "'.$url.'"><u>here</a><u/u>';
			$footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
			//dsm($body);
			$params = array(
				'subject' => 'Sorry! Your leave application was rejected by '.$name.'.',
				'body' => $body."\n".$footer,
			);
			// Send out the e-mail.
			drupal_mail('leave', 'Essa', $email, language_default(), $params);
		}
		
	}
	
	if($flag == 2){
		//sending message to employee when leave is applied to principal
		$module = 'leave';
		$recipients= array();
		$recipients[] = user_load($emp_uid);
		$msg_subject = 'Sorry! Your leave application was rejected by '.$name.'.';
		$msg_body = 'Your leave application dated '.$date.' has been rejected. To check details, click <a href = "'.$url.'"><u>here</a><u/u>';
		$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
		$msg_body = $msg_body.' <br>'.$footer;
		privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
		
		//sending system alert
		$sys_alert_table = 'essa_'.$session_id.'_system_alert';
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
			'message' => 'Leave application of Employee ID '.$form_state['values']['emp_id'].' was rejected by Principal '.$name.'.',
			'priority' => 'L',
			'module' => 'leave',
			'source_url' => 'leave/reject',
			'timestamp' => $strtodate,
			'source_uid' => $user->uid,
		))
		->execute();
		
		//Sending email to employee.
		if($emp_mail != NULL){
			$email = $emp_mail;

			$body = 'Your leave application dated '.$date.' has been rejected. To check details, click <a href = "'.$url.'"><u>here</a><u/u>';
			$footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
			//dsm($body);
			$params = array(
				'subject' => 'Sorry! Your leave application was rejected by '.$name.'.',
				'body' => $body."\n".$footer,
			);
			// Send out the e-mail.
			drupal_mail('leave', 'Essa', $email, language_default(), $params);
		}
	}
	
	drupal_set_message('Leave application of employee '.$form_state['values']['emp_id'].' is rejected successfully', 'status');
	//*******Suraj********//
	
}