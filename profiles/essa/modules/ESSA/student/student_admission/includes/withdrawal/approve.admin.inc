<?php
/**
 * Theme callback function approve_expulsion().
 */
function approve_expulsion($form, &$form_state, $value){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$student_withdrawal_table = 'essa_'.$session_id.'_student_withdrawal';
	$finance_time = date('m/d/Y h:i:s');
	$timestamp = strtotime($finance_time);
	//dsm($form_state);
	
	global $user;
	$fi_uid = array();
	$fee_incharge_role = db_query("SELECT * FROM role WHERE name = 'Fees Incharge'");
	foreach($fee_incharge_role as $fi_role){
		$fi_rid = $fi_role->rid;
	}
	$p_uid = array();
	$principal_role = db_query("SELECT * FROM role WHERE name = 'Principal'");
	foreach($principal_role as $p_role){
		$p_rid = $p_role->rid;
	}
	$user_rd = array();
	$feeincharge = 0;
	$prin = 0;
	$user_rid = db_query("SELECT * FROM users_roles WHERE uid = :u;", array(':u' => $user->uid));
	foreach($user_rid as $r){
		$user_rd[] = $r->rid;
		foreach($user_rd as $u_rid){
			if($u_rid == $fi_rid){
				$feeincharge = 1;
			}elseif($u_rid == $p_rid){
				$prin = 1;
			}
		}
	}
	//dsm($form_state['triggering_element']['#name']);
	//$string = explode('%',$form_state['triggering_element']['#name']);
	$string = explode('%',$value);
	$adm_no = $string[0];
	$req_timestamp = $string[1];
	$approve_time = date('m/d/Y h:i:s');
	$timestamp = strtotime($approve_time);
	
	$student_name = db_query("SELECT * FROM {$student_table} where adm_no = :adm;", array(':adm' => $adm_no));
	foreach($student_name as $st_name){
		$s_name = $st_name->student_name;
		$type = $st_name->type;
	}
	
	if($feeincharge == 1){
		//dsm($adm_no);
		db_update($student_withdrawal_table)
		->fields(array(
			'status_fin' => 'approved',
			'fin_timestamp' => $timestamp,
			'status' => 'Approved by Finance',
			'fin_uid' => $user->uid,
			))
		->condition(db_and()
			->condition('adm_no', $adm_no)
			->condition('status_timestamp', $req_timestamp)
		)
		->execute();
		global $base_url;
		$base_url = $base_url.'/admin/students/withdrawal/manage';
		$custom_url =  (urldecode(url($base_url)));
		$form_state['redirect'] = $base_url;
		
		if($type == 'expulsion'){
			drupal_set_message('The expulsion application of '.$adm_no.'-'.$s_name.' has been sent to Principal for approval.','status');
			
			//sending system alert
			global $user;
			$created_date = date("Y-m-d H:i:s");
			$strtodate = strtotime($created_date);
			db_insert($sys_alert_table)
			->fields(array(
				'message' => 'The Application for expulsion of '.$adm_no.'-'.$s_name.' has been sent to Principal for approval.',
				'priority' => 'M',
				'module' => 'withdrawal',
				'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
				'timestamp' => $strtodate,
				'source_uid' => $user->uid,
			))
			->execute();
		}elseif($type == 'passout'){
			drupal_set_message('The passout application of '.$adm_no.'-'.$s_name.' has been sent to Principal for approval.','status');
			
			//sending system alert
			global $user;
			$created_date = date("Y-m-d H:i:s");
			$strtodate = strtotime($created_date);
			db_insert($sys_alert_table)
			->fields(array(
				'message' => 'The Application for passout of '.$adm_no.'-'.$s_name.' has been sent to Principal for approval.',
				'priority' => 'M',
				'module' => 'withdrawal',
				'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
				'timestamp' => $strtodate,
				'source_uid' => $user->uid,
			))
			->execute();
		}elseif($type == 'withdrawal'){
			drupal_set_message('The withdrawal application of '.$adm_no.'-'.$s_name.' has been sent to Principal for approval.','status');
			
			//sending system alert
			global $user;
			$created_date = date("Y-m-d H:i:s");
			$strtodate = strtotime($created_date);
			db_insert($sys_alert_table)
			->fields(array(
				'message' => 'The Application for withdrawal of '.$adm_no.'-'.$s_name.' has been sent to Principal for approval.',
				'priority' => 'M',
				'module' => 'withdrawal',
				'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
				'timestamp' => $strtodate,
				'source_uid' => $user->uid,
			))
			->execute();
		}
		
		
	}elseif($prin == 1){
		//dsm($adm_no);
		$stud_info = db_query(
			"SELECT * from $student_table where adm_no = :adm_no;", array(':adm_no' => $adm_no)
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
		->condition('adm_no', $adm_no, '=')
		->execute();
		
		db_update($student_withdrawal_table)
		->fields(array(
			'status' => 'blocked',
			'status_uid' => $user->uid,
			))
		->condition(db_and()
			->condition('adm_no', $adm_no)
			->condition('status_timestamp', $req_timestamp)
		)
		->execute();
		global $base_url;
		$base_url = $base_url.'/admin/students/withdrawal/manage';
		$custom_url =  (urldecode(url($base_url)));
		$form_state['redirect'] = $base_url;
		
		if($type == 'expulsion'){
			drupal_set_message('Expulsion Application for '.$adm_no.'-'.$s_name.' has been Approved.','status');
			
			//sending system alert
			global $user;
			$created_date = date("Y-m-d H:i:s");
			$strtodate = strtotime($created_date);
			db_insert($sys_alert_table)
			->fields(array(
				'message' => 'Expulsion Application for '.$adm_no.'-'.$s_name.' has been approved.',
				'priority' => 'M',
				'module' => 'withdrawal',
				'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
				'timestamp' => $strtodate,
				'source_uid' => $user->uid,
			))
			->execute();
		}elseif($type == 'passout'){
			drupal_set_message('Passout Application for '.$adm_no.'-'.$s_name.' has been Approved.','status');
			
			//sending system alert
			global $user;
			$created_date = date("Y-m-d H:i:s");
			$strtodate = strtotime($created_date);
			db_insert($sys_alert_table)
			->fields(array(
				'message' => 'Passout Application for '.$adm_no.'-'.$s_name.' has been approved.',
				'priority' => 'M',
				'module' => 'withdrawal',
				'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
				'timestamp' => $strtodate,
				'source_uid' => $user->uid,
			))
			->execute();
		}elseif($type == 'withdrawal'){
			drupal_set_message('Withdrawal Application for '.$adm_no.'-'.$s_name.' has been Approved.','status');
			
			//sending system alert
			global $user;
			$created_date = date("Y-m-d H:i:s");
			$strtodate = strtotime($created_date);
			db_insert($sys_alert_table)
			->fields(array(
				'message' => 'Withdrawal Application for '.$adm_no.'-'.$s_name.' has been approved.',
				'priority' => 'M',
				'module' => 'withdrawal',
				'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
				'timestamp' => $strtodate,
				'source_uid' => $user->uid,
			))
			->execute();
		}
	}
}