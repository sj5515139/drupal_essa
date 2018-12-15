<?php

/**
 *Implements page callback - edit_leave
*/

function edit_leave($form, $form_state, $data){
	$data = explode('%', $data);
	$emp_id = $data[0];
	$req_timestamp = $data[1];
	
	$form['req_timestamp'] = array(
		'#type' => 'value',
		'#value' => $req_timestamp,
	);
	//drupal_set_message($req_timestamp);
	$session_id = (string)variable_get('essa_sid');
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leave_staff_history_table = 'essa_'.$session_id.'_leave_staff_history';
	$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	global $user;
	
	$leaves = db_query("SELECT * FROM {$leave_staff_history_table} WHERE emp_id = :e AND req_timestamp = :t;", array(':e' => $emp_id, ':t'=> $req_timestamp));
	foreach($leaves as $leave){
		$leave_type = $leave->leave_id;
		$start_date = $leave->from_date;
		$end_date = $leave->to_date;
		$working_days = $leave->no_of_working_days;
		$half_day = $leave->half_day;
		$reason = $leave->reason;
		if($leave->leave_moderator == NULL){
			$approval = 'Principal';
		}else{
			$approval = $leave->leave_moderator;
		}
	}
	
	$staff_leave_details = db_query(
		"SELECT * from $leave_staff_table where emp_id = :emp_id;", array(':emp_id' => $emp_id)
	);
	foreach($staff_leave_details as $sld){
		if($sld->leave_status != '0'){
			$leave_ids[] = $sld->leave_id;
		}
	}
	
	foreach($leave_ids as $lid){
		$staff_leave_names = db_query(
			"SELECT * from $leave_table where leave_id = :li OR leave_type = :lt;", array(':li' => $lid,':lt' => $lid)
		);
		foreach($staff_leave_names as $sln){
			if($sln->post_id != NULL){
				$l_id = explode('-',$sln->leave_id);
				$new_lid = $l_id[0];
				
				$options[$sln->leave_type] = $sln->leave_name.'('.$new_lid.')';	
			}else{
				$options[] = $sln->leave_name.'('.$sln->leave_id.')';
			}
		}
	}
	
	$form['leave'] = array(
		'#type' => 'select',
		'#title' => t('Select a Leave'),
		'#description' => 'First select a Leave type',
		'#required' => TRUE,
		'#options' => drupal_map_assoc($options),
		'#default_value' => $leave_type,
		'#ajax' => array(
			'event' => 'change',
			'callback' => 'display_leave_remaining',
			'wrapper' => 'ajax_wrapper',
			'method' => 'replace',
			'effect' => 'fade',
		),
	);
	
	if(isset($form_state['storage']['leave'])) {
		$form['leave']['#default_value'] = $form_state['storage']['leave'];
	}

	
	$form['ajax_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "ajax_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['from'] = array(
		'#type' => 'date_popup',
		'#title' => t('Start Date'),
		'#default_value' => date('Y-m-d',$start_date),
		'#date_format' => 'd/m/Y',
		'#required' => TRUE,
		'#attributes' => array('placeholder' => 'From'), 
	);
  
	$form['to'] = array(
		'#type' => 'date_popup',
		'#title' => t('End Date'),
		'#date_format' => 'd/m/Y',
		'#default_value' => date('Y-m-d',$end_date),
		'#required' => TRUE,
		'#attributes' => array('placeholder' => 'To'),
		'#ajax' => array(
			'event' => 'change',
			'callback' => 'leave_warning',
			'wrapper' => 'ajax_warning_wrapper',
			'method' => 'replace',
			'effect' => 'fade',
		),
	);
	
	$form['ajax_warning_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "ajax_warning_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['no_of_working_days'] = array(
		'#type' => 'textfield',
		'#title' => 'No. of Working Days',
		'#size' => 2,
		'#default_value' => $working_days,
		'#required' => TRUE,
		//'#default_value' => isset($form_state['storage']['no_of_working_days'])?$form_state['storage']['no_of_working_days']:NULL,
	);
  
	$form['half_day'] = array(
		'#type' => 'checkbox',
		'#title' => 'Half Day',
		'#default_value' => $half_day,
		//'#description' => '<p>If you apply for half day and total leave is more than one day, the last day of your leave will be considered as half day.</p>',
	);
	
	$form['reason'] = array(
		'#type' => 'textarea',
		'#title' => t('Reason'),
		'#attributes' => array('placeholder' => 'Not more than 150 words.'), 
		'#required' => TRUE,
		'#default_value' => $reason,
	);
	
	$uids  = array();
	$leave_moderator_role = db_query(
		"SELECT * from role where name = 'Leave Moderator';"
	);
	foreach($leave_moderator_role as $lmr){
		$rid = $lmr->rid;
 	}
	$leave_moderators = db_query(
		"SELECT * from users_roles where rid = :rid;", array(':rid' => $rid)
	);
	foreach($leave_moderators as $lm){
		$uids[] = $lm->uid;
	}
	
	$lms = array('-Select-','Principal');
	foreach($uids as $uid){
		$staff_lm = db_query(
			"SELECT * from $staff_master_table where uid = :uid;", array(':uid' => $uid)
		);
		foreach($staff_lm as $slm){
			$lms[] = $slm->fname.' '.$slm->lname.' ('.$slm->emp_id.')';
		}
	}
	
	$form['apply_to'] = array(
		'#type' => 'select',
		'#title' => 'Send for approval to',
		'#options' =>drupal_map_assoc($lms),
		'#required' => TRUE,
		'#default_value' => $approval,
		'#ajax' => array(
			'event' => 'change',
			'callback' => 'submit_leave_app',
			'wrapper' => 'submit_wrapper',
			'method' => 'replace',
			'effect' => 'fade',
		),
	);
	
	$form['submit_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "submit_wrapper">',
		'#suffix' => '</div>',
	);
	
  
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);
	
	return $form;
}


/**
 *Ajax callback to display leave remaining.
 */
function display_leave_remaining($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
  $leave_type_table = 'essa_'.$session_id.'_leave_types';
	$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
  $staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	$from = "(";
	$to = ")";
	$leave_id = getStringBetween($form_state['values']['leave'],$from,$to);
	
  $leave_record = db_query(
		"SELECT * from $leave_type_table where leave_id = :li;", array(':li' => $leave_id)
	);
  foreach($leave_record as $lr){
		
	}
  $emp_leave_record = db_query(
		"SELECT * from $leave_staff_table where leave_id = :li and emp_id = :ei;", array(':li' => $leave_id, ':ei' => $form_state['values']['emp_id'])
	);
	foreach($emp_leave_record as $elr){
		$leave_remaining = $elr->leave_remaining;
	}
	
	$form['fs_status'] = array(
		'#type' => 'markup', 
		'#markup' => '',
		'#prefix' => '<div id = "ajax_wrapper">',
		'#suffix' => '</div>',
	);
	
	if($leave_remaining != NULL){
		if($leave_remaining <= 0){
			$form['fs_status']['leave status'] = array(
				'#type' => 'markup', 
				'#markup' => '<h3 class = "leave_warning">You have no days of leave in your account. Please select another leave type.</h3>',
			);
		}else{
			$form['fs_status']['leave status'] = array(
					'#type' => 'markup', 
					'#markup' => '<h3 class = "leave_remaining">You have <span style = "color: #191970;">'.$leave_remaining.' days </span>of leave in your account.</h3>',
				);
			$leave_record = db_query(
				"SELECT * from $leave_type_table where leave_id = :li;", array(':li' => $leave_id)
			);
			foreach($leave_record as $lr){
				$max_per_month = $lr->max_per_month;
				$min_stretch = $lr->min_stretch;
			}
			
			if($max_per_month != NULL && $max_per_month != 0){
				$form['fs_status']['max'] = array(
					'#type' => 'markup', 
					'#markup' => '<h3 class = "leave_remaining">You can apply a maximum of <span style = "color: #191970;">'.$max_per_month.' days </span>in a month.</h3>',
				);
			}
			
			if($min_stretch != NULL && $min_stretch != 0){
				$form['fs_status']['min'] = array(
					'#type' => 'markup', 
					'#markup' => '<h3 class = "leave_remaining">You have to apply a minimum of <span style = "color: #191970;">'.$min_stretch.' days </span>at a stretch.</h3>',
				);
			}
		}
	}else{
		$form['fs_status']['leave status'] = array(
			'#type' => 'markup', 
			'#markup' => '<p> </p>',
		);
	}
	
	return $form['fs_status'];
}

/**
 *Ajax callback to display leave warning.
 */
function leave_warning($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$leave_type_table = 'essa_'.$session_id.'_leave_types';
	$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
  $staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	variable_set('leave_error', 0);
	
	$from = "(";
	$to = ")";
	$leave_id = getStringBetween($form_state['values']['leave'],$from,$to);
	
	global $user;
	$staff_emp_id = db_query(
		"SELECT * from $staff_master_table where uid = :uid;", array(':uid' => $user->uid)
	);
	foreach($staff_emp_id as $sei){
		$emp_id = $sei->emp_id;
	}
	
	$from_dt = strtotime($form_state['values']['from']);
	$to_dt = strtotime($form_state['values']['to']);
	$datediff = strtotime($form_state['values']['to']) - strtotime($form_state['values']['from']);
	$no_of_day = floor($datediff/(60*60*24))+1;
	
	
	
	$form['fs_warning'] = array(
		'#type' => 'markup', 
		'#markup' => '',
		'#prefix' => '<div id = "ajax_warning_wrapper">',
		'#suffix' => '</div>',
	);
	
	if($no_of_day == 1){
		$form['fs_warning']['no_of_days'] = array(
			'#type' => 'markup', 
			'#markup' => '<h3 class = "leave_remaining">You are applying leave for <span style = "color: #191970;">'.$no_of_day.' day</span>.</h3>',
		);	
	}else{
		$form['fs_warning']['no_of_days'] = array(
			'#type' => 'markup', 
			'#markup' => '<h3 class = "leave_remaining">You are applying leave for <span style = "color: #191970;">'.$no_of_day.' days</span>.</h3>',
		);
	}
	
	
	$leave_record = db_query(
		"SELECT * from $leave_type_table where leave_id = :li;", array(':li' => $leave_id)
	);
  foreach($leave_record as $lr){
		$max_per_month = $lr->max_per_month;
		$min_stretch = $lr->min_stretch;
	}
	
	if($min_stretch != 0 || $min_stretch != NULL){
		if($no_of_day < $min_stretch){
			$form['fs_warning']['min warning2'] = array(
				'#type' => 'markup', 
				'#markup' => '<h3 class = "leave_warning">You have to apply leave of atleast <span style = "color: #191970 !important;">'.$min_stretch.' days </span>.</h3>',
			);
			variable_set('leave_error', 1);
		}	
	}
	
	$leave_staff_record = db_query(
		"SELECT * from $leave_staff_table where leave_id = :li and emp_id = :ei;", array(':li' => $leave_id, ':ei' => $emp_id)
	);
  foreach($leave_staff_record as $lsr){
		$leave_remaining = $lsr->leave_remaining;
	}
	
	if($leave_remaining == 0 && $leave_remaining != NULL){
		$form['fs_warning']['leave warning no'] = array(
			'#type' => 'markup', 
			'#markup' => '<h3 class = "leave_warning">You have no leave remaining.</h3>',
		);
		variable_set('leave_error', 1);
	}
	
	if($no_of_day > $leave_remaining && $leave_remaining != NULL){
		$form['fs_warning']['leave warning days'] = array(
			'#type' => 'markup', 
			'#markup' => '<h3 class = "leave_warning">You have only <span style = "color: #191970 !important;">'.$leave_remaining.' days </span>leave remaining.</h3>',
		);
		variable_set('leave_error', 1);
	}
	
	if($no_of_day <= 0){
		$form['fs_warning']['leave warning neg'] = array(
			'#type' => 'markup', 
			'#markup' => '<h3 class = "leave_warning">You can\'t apply leave where "Start date" is after "End Date" .</h3>',
		);
		variable_set('leave_error', 1);
	}
	
	$from_month = date('Y_m',$from_dt);
	$to_month = date('Y_m',$to_dt);
	
	$leave_record = db_query(
		"SELECT * from $leave_staff_table where leave_id = :li and emp_id = :ei;", array(':li' => $leave_id, ':ei' => $emp_id)
	);
  foreach($leave_record as $lr){
		$from_count = $lr->$from_month;
		$to_count = $lr->$to_month;
	}
	if($from_month == $to_month){
		if($no_of_day > $max_per_month && $max_per_month != NULL){
			$form['fs_warning']['leave warning'] = array(
				'#type' => 'markup', 
				'#markup' => '<h3 class = "leave_warning">You have crossed the monthly leave limits for this month.</h3>',
			);
			variable_set('leave_error', 1);
		}
		
		if($from_count > 0){
			$new_no_of_days = $from_count + $no_of_day;
			
			if($new_no_of_days > $max_per_month && $max_per_month != NULL){
				$form['fs_warning']['leave warning remaining'] = array(
					'#type' => 'markup', 
					'#markup' => '<h3 class = "leave_warning"> You have already taken <span style = "color: #191970 !important;">'.$from_count.' days </span>leave in this month.</h3>',
				);
				variable_set('leave_error', 1);
			}	
		}
	}elseif($from_month != $to_month){
		
		$from_dt = strtotime($form_state['values']['from']);
		$month_end =  strtotime(date("Y-m-t", $from_dt));
		$datediff = $month_end - $from_dt;
		$no_of_day_from_mon = floor($datediff/(60*60*24))+1;
		
		$to_dt = strtotime($form_state['values']['to']);
		$month_start =  strtotime('01-'.date('m-Y', $to_dt));
		$datediff = $to_dt - $month_start;
		$no_of_day_to_mon = floor($datediff/(60*60*24))+1;
		
		if($no_of_day_from_mon == 1){
			$form['fs_warning']['no_of_days'] = array(
				'#type' => 'markup', 
				'#markup' => '<h3 class = "leave_remaining">You are applying leave for <span style = "color: #191970;">'.$no_of_day_from_mon.' day </span>in month of <span style = "color: #191970;">'.date('M-Y', $from_dt).'</span> & <span style = "color: #191970;">'.$no_of_day_to_mon.' days</span> in month of <span style = "color: #191970;">'.date('M-Y', $to_dt).'</span> i.e. a total of <span style = "color: #191970;">'.$no_of_day.' days </span>leave.</h3>',
			);	
		}else{
			$form['fs_warning']['no_of_days'] = array(
				'#type' => 'markup', 
				'#markup' => '<h3 class = "leave_remaining">You are applying leave for <span style = "color: #191970;">'.$no_of_day_from_mon.' days </span>in month of <span style = "color: #191970;">'.date('M-Y', $from_dt).'</span> & <span style = "color: #191970;">'.$no_of_day_to_mon.' days</span> in month of <span style = "color: #191970;">'.date('M-Y', $to_dt).'</span> i.e. a total of <span style = "color: #191970;">'.$no_of_day.' days </span>leave.</h3>',
			);	
		}
		
		$new_no_of_days_from = $from_count + $no_of_day_from_mon;
		$new_no_of_days_to = $to_count + $no_of_day_to_mon;
		if($no_of_day_from_mon > $max_per_month){
			$form['fs_warning']['leave warning from mon'] = array(
				'#type' => 'markup', 
				'#markup' => '<h3 class = "leave_warning"> You have applied for <span style = "color: #191970 !important;">'.$no_of_day_from_mon.' days</span> in month of '.date('M-Y', $from_dt).'</h3>',
			);
			variable_set('leave_error', 1);
		}
		
		if($no_of_day_to_mon > $max_per_month){
			$form['fs_warning']['leave warning to mon'] = array(
				'#type' => 'markup', 
				'#markup' => '<h3 class = "leave_warning"> You have applied for <span style = "color: #191970 !important;">'.$no_of_day_to_mon.' days</span> in month of '.date('M-Y', $to_dt).'</h3>',
			);
			variable_set('leave_error', 1);
		}
		
		if($from_count != 0){
			if($new_no_of_days_from > $max_per_month){
				$form['fs_warning']['leave warning prev leave from'] = array(
					'#type' => 'markup', 
					'#markup' => '<h3 class = "leave_warning"> You have already taken <span style = "color: #191970 !important;">'.$from_count.' days </span>leave in <span style = "color: #191970 !important;">'.date('M-Y', $from_dt).' </span>month.</h3>',
				);
				variable_set('leave_error', 1);
			}	
		}
		if($to_count != 0){
			if($new_no_of_days_to > $max_per_month){
				$form['fs_warning']['leave warning prev leave to'] = array(
					'#type' => 'markup', 
					'#markup' => '<h3 class = "leave_warning"> You have already taken <span style = "color: #191970 !important;">'.$to_count.' days </span>leave in <span style = "color: #191970 !important;">'.date('M-Y', $to_dt).'</span> month.</h3>',
				);
				variable_set('leave_error', 1);
			}
		}
	}
	
	return $form['fs_warning'];
}

function submit_leave_app($form, &$form_state){
	$form['submit_warning'] = array(
		'#type' => 'markup', 
		'#markup' => '',
		'#prefix' => '<div id = "submit_wrapper">',
		'#suffix' => '</div>',
	);
	
	if(variable_get('leave_error') == 1){
		if($form_state['values']['apply_to'] != '-Select-'){
			$form['submit_warning']['leave warning prev leave to'] = array(
				'#type' => 'markup', 
				'#markup' => '<h3 class = "leave_error"> ***Please comply with the leave rules.</h3>',
			);
		}else{
			$form['submit_warning']['leave warning prev leave to'] = array(
				'#type' => 'markup', 
				'#markup' => '',
			);
		}
	}else{
		if($form_state['values']['apply_to'] != '' || $form_state['values']['apply_to'] != '-Select-'){
			$form['submit_warning']['leave warning prev leave to'] = array(
				'#type' => 'markup', 
				'#markup' => '<h3 class = "leave_success"> You can submit the leave application for approval now.</h3>',
			);
		}else{
			$form['submit_warning']['leave warning prev leave to'] = array(
				'#type' => 'markup', 
				'#markup' => '',
			);
		}
	}
	
	return $form['submit_warning'];
}



/**
 *Implements submit function
 */
function edit_leave_submit($form, &$form_state){
	//drupal_set_message(variable_get('leave_error'));
	if(variable_get('leave_error') == 1){
		drupal_set_message('Your leave application was not submitted. Please comply to the leave rules.','error');
		$form_state['rebuild'] = TRUE;
	}else{
		$flag = 0;
		
		$session_id = (string)variable_get('essa_sid');
		$leave_type_table = 'essa_'.$session_id.'_leave_types';
		$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
		$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
		global $user;
		if($form_state['values']['apply_to'] != 'Principal'){
			global $user;
			$session_id = (string)variable_get('essa_sid');
			$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
			$leave_type_table = 'essa_'.$session_id.'_leave_types';
			$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
			$timestamp = $form_state['values']['req_timestamp'];
			$from_dt = strtotime($form_state['values']['from']);
			$to_dt = strtotime($form_state['values']['to']);
			$staff_emp_id = db_query(
				"SELECT * from $staff_master_table where uid = :uid;", array(':uid' => $user->uid)
			);
			foreach($staff_emp_id as $sei){
				$emp_id = $sei->emp_id;
				$emp_name = $sei->fname.' '.$sei->lname;
			}
			
			$datediff = strtotime($form_state['values']['to']) - strtotime($form_state['values']['from']);
			$no_of_day = floor($datediff/(60*60*24))+1;
			
			$from = "(";
			$to = ")";
			$leave_id = getStringBetween($form_state['values']['leave'],$from,$to);
			$leave_moderator = getStringBetween($form_state['values']['apply_to'],$from,$to);
			$staff_name = db_query(
				"SELECT * from $staff_master_table where emp_id = :ei;", array(':ei' => $leave_moderator)
			);
			foreach($staff_name as $sn){
				$name = $sn->fname.' '.$sn->lname;
			}
			
			$half_day = 0;
			if($form_state['values']['half_day'] == '1'){
				$leave_record = db_query(
					"SELECT * from $leave_type_table where leave_id = :li;", array(':li' => $leave_id)
				);
			  foreach($leave_record as $lr){
					$half_day_rule = $lr->half_day_rule;
					$half_day = 1;
				}
				
				$half_day_leave = 1/$half_day_rule;
				$no_of_day = ($no_of_day - 1) + $half_day_leave;
				$no_of_day = round($no_of_day, 2);
			}
			//drupal_set_message($timestamp);
			db_merge($leave_history_table)
				->key(array('emp_id' => $emp_id, 'req_timestamp' => $timestamp))
				->fields (array(
					'req_timestamp' => $timestamp,
					'leave_id' => $leave_id,
					'emp_id' => $emp_id,
					'from_date' => $from_dt,
					'to_date' => $to_dt,
					'no_of_days' => $no_of_day,
					'no_of_working_days' => $form_state['values']['no_of_working_days'],
					'reason' => $form_state['values']['reason'],
					'status' => 'Pending with Moderator',
					'status_remark' => $name,
					'leave_moderator' => $leave_moderator,
					'half_day' => $form_state['values']['half_day'],
				)
			)	
			->execute();
			$flag = 1;
		}
		
		if($form_state['values']['apply_to'] == 'Principal'){	
			global $user;
			$session_id = (string)variable_get('essa_sid');
			$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
			$leave_type_table = 'essa_'.$session_id.'_leave_types';
			$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
			$application_time = date('m/d/Y h:i:s');
			$timestamp = $form_state['values']['req_timestamp'];
			$from_dt = strtotime($form_state['values']['from']);
			$to_dt = strtotime($form_state['values']['to']);
			
			$staff_emp_id = db_query(
				"SELECT * from $staff_master_table where uid = :uid;", array(':uid' => $user->uid)
			);
			foreach($staff_emp_id as $sei){
				$emp_id = $sei->emp_id;
				$emp_name = $sei->fname.' '.$sei->lname;
			}
			
			$datediff = strtotime($form_state['values']['to']) - strtotime($form_state['values']['from']);
			$no_of_day = floor($datediff/(60*60*24))+1;
			
			$from = "(";
			$to = ")";
			$leave_id = getStringBetween($form_state['values']['leave'],$from,$to);
			$leave_moderator = getStringBetween($form_state['values']['apply_to'],$from,$to);
			$half_day = 0;
			if($form_state['values']['half_day'] == '1'){
				$leave_record = db_query(
					"SELECT * from $leave_type_table where leave_id = :li;", array(':li' => $leave_id)
				);
			  foreach($leave_record as $lr){
					$half_day_rule = $lr->half_day_rule;
					$half_day = 1;
				}
				
				$half_day_leave = 1/$half_day_rule;
				$no_of_day = ($no_of_day - 1) + $half_day_leave;
				$no_of_day = round($no_of_day, 2);
			}
			
			db_merge($leave_history_table)
				->key(array('emp_id' => $emp_id, 'req_timestamp' => $timestamp))
				->fields (array(
				  'req_timestamp' => $timestamp,
					'leave_id' => $leave_id,
					'emp_id' => $emp_id,
					'from_date' => $from_dt,
					'to_date' => $to_dt,
					'no_of_days' => $no_of_day,
					'no_of_working_days' => $form_state['values']['no_of_working_days'],
					'reason' => $form_state['values']['reason'],
					'status' => 'Pending with Principal',
					'status_remark' => 'Principal',
					'leave_moderator' => NULL,
					'half_day' => $form_state['values']['half_day'],
				)
			)	
			->execute();
			$flag = 2;
		}
		
		//*******Suraj********//
		global $base_url;
		$from_date = date('m/d/Y',$from_dt);
		$to_date = date('m/d/Y',$to_dt);
		if($flag == 1){
			//sending message to leave moderator
			$module = 'leave';
			$recipients= array();
			$recipients[] = user_load($lm_uid);
			$msg_subject = 'Employee ID '.$emp_id.' has modified leave application';
			$msg_body = $emp_name.' has applied for '.$leave_id.' from '.$from_date.' to '.$to_date.', stating "'.$form_state['values']['reason'].'". To take action, click <a href = "'.$base_url.'/admin/staff/leave/approve_leave"><u>here</u></a>';
			$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
			$msg_body = $msg_body.' <br>'.$footer;
			privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
			
			$email = db_query("SELECT * FROM {$staff_master_table} WHERE uid = :uid;", array(':uid' => $lm_uid));
			foreach($email as $e){
				$lm_email = $e->email;
			}
			
			//Sending email to leave_moderator.
			if($lm_email != NULL){
		
				// Set hook_mail parameters.
				
				$email = $lm_email;
					
				$body = $emp_name.' has applied for '.$leave_id.' from '.$from_date.' to '.$to_date.', stating "'.$form_state['values']['reason'].'". To take action, click <a href = "'.$base_url.'/admin/staff/leave/approve_leave"><u>here</u></a>';
				$footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
				//dsm($body);
				$params = array(
					'subject' => 'Employee ID '.$emp_id.' has modified leave application',
					'body' => $body."\n".$footer,
				);
				// Send out the e-mail.
				drupal_mail('leave', 'Essa', $email, language_default(), $params);
			}
			
		}
		if($flag == 2){
			$r_id = db_query("SELECT * FROM {role} WHERE name = :name;", array(':name' => 'Principal'));
			foreach($r_id as $rid){
				$u_id = db_query("SELECT * FROM {users_roles} WHERE rid = :rid;", array(':rid' => $rid->rid));
				foreach($u_id as $u){
					//sending message to principal
					$module = 'leave';
					$recipients= array();
					$recipients[] = user_load($u->uid);
					$msg_subject = 'Employee ID '.$emp_id.'has modified leave application';
					$msg_body = $emp_name.' has applied for '.$leave_id.' from '.$from_date.' to '.$to_date.', stating "'.$form_state['values']['reason'].'". To take action, click <a href = "'.$base_url.'/admin/staff/leave/approve_leave"><u>here</u></a>';
					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
					$msg_body = $msg_body.' <br>'.$footer;
					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
					
					
					$email = db_query("SELECT * FROM {$staff_master_table} WHERE uid = :uid;", array(':uid' => $u->uid));
					foreach($email as $e){
						$p_email = $e->email;
					}
					
					//Sending email to principal.
					if($p_email != NULL){
				
						// Set hook_mail parameters.
						
						$email = $p_email;
							
						$body = $emp_name.' has applied for '.$leave_id.' from '.$from_date.' to '.$to_date.', stating "'.$form_state['values']['reason'].'". To take action, click <a href = "'.$base_url.'/admin/staff/leave/approve_leave"><u>here</u></a>';
						$footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
						//dsm($body);
						$params = array(
							'subject' => 'Employee ID '.$emp_id.' has modified leave application',
							'body' => $body."\n".$footer,
						);
						// Send out the e-mail.
						drupal_mail('leave', 'Essa', $email, language_default(), $params);
					}
					
					
				}
			}
			
			
		}
		//sending message to the employee
		$module = 'leave';
		$recipients= array();
		$recipients[] = user_load($user->uid);
		$msg_subject = 'Leave application submitted';
		$msg_body = 'You have successfully applied for '.$leave_id.' from '.$from_date.' to '.$to_date.'. To edit, click <a href = ""><u>here</u></a>. To check the status, click <a = ""><u>here</u></a>.';
		$footer = ' <p>This is a system generated mail. Do not reply to this message. <i>ESSA - Efficient & Simplified School Administartion.</i></p>';
		$msg_body = $msg_body.' <br>'.$footer;
		privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
		
		//sending system alert
		$sys_alert_table = 'essa_'.$session_id.'_system_alert';
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
			'message' => 'Employee ID '.$emp_id.' submitted a leave application',
			'priority' => 'L',
			'module' => 'leave',
			'source_url' => 'admin/staff/leave/apply_leave',
			'timestamp' => $strtodate,
			'source_uid' => $user->uid,
		))
		->execute();
		
		global $base_url;
		global $user;
		$url = $base_url.'/user/'.$user->uid.'/leave/application';
		drupal_set_message('Your modified leave application was successfully submitted. Track your application status <a href ="'.$url.'">here</a>','status');
		
	}
	drupal_flush_all_caches();
}

/**
 *Implements support function to get the leave ID
 */
function getStringBetween($str,$from,$to){
  $sub = substr($str, strpos($str,$from)+strlen($from),strlen($str));
  return substr($sub,0,strpos($sub,$to));
}