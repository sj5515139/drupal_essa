<?php

/**
 *Implements page_callback function
 */
function approve_leave($form, &$form_state){
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
    '#value' => 'Approve',
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

function approve_leave_submit($form, &$form_state){
	$flag = 0;
	$session_id = (string)variable_get('essa_sid');
  $leave_type_table = 'essa_'.$session_id.'_leave_types';
	$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
  $staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	global $user;
	
	global $user;
	$fi_uid = array();
	$leave_moderator_role = db_query("SELECT * FROM role WHERE name = 'Leave Moderator'");
	foreach($leave_moderator_role as $fi_role){
		$fi_rid = $fi_role->rid;
	}
	$p_uid = array();
	$principal_role = db_query("SELECT * FROM role WHERE name = 'Principal'");
	foreach($principal_role as $p_role){
		$p_rid = $p_role->rid;
	}
	
	$user_rd = array();
	$leave_moderator = 0;
	$prin = 0;
	
	$user_rid = db_query("SELECT * FROM users_roles WHERE uid = :u;", array(':u' => $user->uid));
	foreach($user_rid as $r){
		$user_rd[] = $r->rid;
		foreach($user_rd as $u_rid){
			if($u_rid == $fi_rid){
				$leave_moderator = 1;
			}elseif($u_rid == $p_rid){
				$prin = 1;
			}
		}
	}
	
//	$leave_moderator_role = db_query(
//		"SELECT * from role where name = 'Leave Moderator';"
//	);
//	foreach($leave_moderator_role as $lmr){
//		$lm_rid = $lmr->rid;
// 	}
//	$leave_moderators = db_query(
//		"SELECT * from users_roles where rid = :rid and uid = :uid;", array(':rid' => $lm_rid,':uid' => $user->uid)
//	);
	if($leave_moderator == 1){
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
				'status' => 'Approved By Moderator',
				'status_remark' => $name,
				'status_moderator' => 'Approved',
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
	
//	$leave_principal_role = db_query(
//		"SELECT * from role where name = 'Principal';"
//	);
//	foreach($leave_principal_role as $lmr){
//		$p_rid = $lmr->rid;
// 	}
//	
//	$principal = db_query(
//		"SELECT * from users_roles where rid = :rid and uid = :uid;", array(':rid' => $p_rid,':uid' => $user->uid)
//	);
	elseif($prin == 1){
		global $base_url;
		$base_url = $base_url.'/admin/staff/leave/approve_leave';
		$form_state['redirect'] = $base_url;
		
		global $user;
		$session_id = (string)variable_get('essa_sid');
		$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
		$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
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
				'status' => 'Approved',
				'status_remark' => 'Principal',
				'status_principal' => 'Approved',
				'remark_principal' => $form_state['values']['remarks'],
				'principal_timestamp' => $timestamp,
				))
	    ->condition(db_and()
	      ->condition('emp_id', $form_state['values']['emp_id'])
	      ->condition('req_timestamp', $form_state['values']['req_timestamp'])
	    )
	  ->execute();
		$flag = 2;
		
		$leaves = db_query(
			"SELECT * from $leave_history_table where emp_id = :emp_id and req_timestamp = :rt;", array(':emp_id' => $form_state['values']['emp_id'], ':rt' => $form_state['values']['req_timestamp'])
		);
		foreach($leaves as $leave){
			$leave_id = $leave->leave_id;
			$no_of_days = $leave->no_of_days;
			$from = $leave->from_date;
			$to = $leave->to_date;
		}
		
		$to = $to + 86400;
		$count = array();
		$begin = new DateTime(date('Y-m-d',$from));
		$end = new DateTime(date('Y-m-d',$to));
		$daterange = new DatePeriod($begin, new DateInterval('P1D'), $end);
		foreach($daterange as $dr){
			$count[$dr->format("Y_m")] = 0;
		}
		foreach($daterange as $dr){
			$count[$dr->format("Y_m")] = $count[$dr->format("Y_m")] + 1;
		}
		
		foreach($count as $k=>$v){
			$leaves = db_query(
				"SELECT * from $leave_staff_table where emp_id = :emp_id and leave_id = :li;", array(':emp_id' => $form_state['values']['emp_id'], ':li' => $leave_id)
			);
			foreach($leaves as $leave){
				db_update($leave_staff_table)
					->fields(array(
						$k => $leave->$k + $count[$k],
					))
					->condition(db_and()
						->condition('emp_id', $form_state['values']['emp_id'])
						->condition('leave_id', $leave_id)
					)
					->execute();
			}
		}
		
		$leaves = db_query(
			"SELECT * from $leave_staff_table where emp_id = :emp_id and leave_id = :li;", array(':emp_id' => $form_state['values']['emp_id'], ':li' => $leave_id)
		);
		foreach($leaves as $leave){
			$leave_remaining = $leave->leave_remaining;
			$leave_taken = $leave->leave_taken;
			$total_leave = $leave->total_leave;
		}
		
		if($total_leave != NULL){
			$new_leave_taken = $leave_taken + $no_of_days;
			$new_leave_remaining = $leave_remaining - $no_of_days;
			
			db_update($leave_staff_table)
				->fields(array(
					'leave_taken' => $new_leave_taken,
					'leave_remaining' => $new_leave_remaining,
				))
				->condition(db_and()
					->condition('emp_id', $form_state['values']['emp_id'])
					->condition('leave_id', $leave_id)
				)
				->execute();
			}else{
				$new_leave_taken = $leave_taken + $no_of_days;
				db_update($leave_staff_table)
					->fields(array(
						'leave_taken' => $new_leave_taken,
					))
					->condition(db_and()
						->condition('emp_id', $form_state['values']['emp_id'])
						->condition('leave_id', $leave_id)
					)
			->execute();
		}
	}
	
	//*******Suraj********//
	
	global $user;
	$staff_emp_id = db_query(
		"SELECT * from $staff_master_table where uid = :uid;", array(':uid' => $user->uid)
	);
	foreach($staff_emp_id as $sei){
		$name = $sei->fname.' '.$sei->lname;
	}
	
	$employee = db_query("SELECT * FROM {$staff_master_table} WHERE emp_id = :emp;",array(':emp' => $form_state['values']['emp_id']));
	foreach($employee as $emp){
		$emp_uid = $emp->uid;
	}
	$date = date('m/d/Y',$form_state['values']['req_timestamp']);
	if($flag == 1){
		//sending message to employee when leave is applied to leave moderator
		$module = 'leave';
		$recipients= array();
		$recipients[] = user_load($emp_uid);
		$msg_subject = 'Congratulation! Your leave has been approved by '.$name.'.';
		$msg_body = 'Your leave application dated '.$date.' has been approved. To check details, click <a href = ""><u>here</a><u/u>';
		$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
		$msg_body = $msg_body.' <br>'.$footer;
		privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
		
		//sending system alert
		$sys_alert_table = 'essa_'.$session_id.'_system_alert';
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
			'message' => 'Leave application of Employee ID '.$form_state['values']['emp_id'].' was approved by Leave Moderator '.$name.'.',
			'priority' => 'L',
			'module' => 'leave',
			'source_url' => 'leave/approve',
			'timestamp' => $strtodate,
			'source_uid' => $user->uid,
		))
		->execute();
	}
	$tti_uid = NULL;
	if($flag == 2){
		//sending message to employee when leave is applied to principal
		$module = 'leave';
		$recipients= array();
		$recipients[] = user_load($emp_uid);
		$msg_subject = 'Congratulation! Your leave has been approved by '.$name.'.';
		$msg_body = 'Your leave application dated '.$date.' has been approved. To check details, click <a href = ""><u>here</a><u/u>';
		$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
		$msg_body = $msg_body.' <br>'.$footer;
		privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
		
		//sending message to time table incharge when leave is approved by principal
		$tt_roles = db_query("SELECT * FROM role WHERE name = 'Time-Table Incharge' OR name = 'Time Table Incharge' OR name = 'TimeTable Incharge';");
		foreach($tt_roles as $ttr){
			$tt_incharge = db_query("SELECT * FROM users_roles where rid = :rid;", array(':rid' => $ttr->rid));
			foreach($tt_incharge as $tti){
				$tti_uid = $tti->uid;
			}
		}
		$leave_dates = db_query("SELECT * FROM {$leave_history_table} WHERE emp_id = :emp AND req_timestamp = :time;", array(':emp' => $form_state['values']['emp_id'], ':time' =>$form_state['values']['req_timestamp']));
		foreach($leave_dates as $l_date){
			$leave_from = date('m/d/Y',$l_date->from_date);
			$leave_to = date('m/d/Y',$l_date->to_date);
		}
		$module = 'leave';
		$recipients= array();
		$recipients[] = user_load($tti_uid);
		$msg_subject = 'Employee ID '.$form_state['values']['emp_id'].' will be on leave from '.$leave_from.' to '.$leave_to.'.';
		$msg_body = 'Please manage class arrangement <a href = ""><u>here</a><u/u>';
		$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
		$msg_body = $msg_body.' <br>'.$footer;
		privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
		
		//sending system alert
		$sys_alert_table = 'essa_'.$session_id.'_system_alert';
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
			'message' => 'Leave application of Employee ID '.$form_state['values']['emp_id'].' was approved by Principal '.$name.'.',
			'priority' => 'L',
			'module' => 'leave',
			'source_url' => 'leave/approve',
			'timestamp' => $strtodate,
			'source_uid' => $user->uid,
		))
		->execute();
	}
	//*******Suraj********//
	drupal_set_message('Leave application was approved.','status');
}

