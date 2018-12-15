<?php
/**
 *Implements page callback function - reject_withdrawal
 */
function reject_all_withdrawal($form, $form_state){
	$form['reason'] = array(
		'#title' => 'Reason(If Any)',
		'#type' => 'textarea',
	);
	$form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save'
  );
	return $form;
}

/**
 *Implements page callback function - reject_expulsion_submit
 */
function reject_all_withdrawal_submit($form, $form_state){
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
	
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$student_withdrawal_table = 'essa_'.$session_id.'_student_withdrawal';
	$approve_time = date('m/d/Y h:i:s');
	$timestamp = strtotime($approve_time);
	if($feeincharge == 1){
		$withdrawal_students = db_query("SELECT * FROM {$student_withdrawal_table} WHERE type = :t AND status = :s;", array(':t' => 'withdrawal', ':s' => 'pending'));
		foreach($withdrawal_students as $wd_student){
			db_update($student_withdrawal_table)
			->fields(array(
				'status_fin' => 'Rejected by Finance',
				'status' => 'Rejected by Finance',
				'fin_timestamp' => $timestamp,
				'status_fin_reason' => $form_state['values']['reason'],
				'status_reason' => $form_state['values']['reason'],
				'fin_uid' => $user->uid,
				))
			->condition(db_and()
				->condition('adm_no', $wd_student->adm_no)
				->condition('status_timestamp', $wd_student->status_timestamp)
			)
			->execute();
		}
	}elseif($prin == 1){
		$withdrawal_students = db_query("SELECT * FROM {$student_withdrawal_table} WHERE type = :t AND status = :s;", array(':t' => 'withdrawal', ':s' => 'Approved by Finance'));
		foreach($withdrawal_students as $wd_student){
			db_update($student_withdrawal_table)
			->fields(array(
				'status' => 'Rejected',
				'status_uid' => $user->uid,
				'status_reason' => $form_state['values']['reason'],
				))
			->condition(db_and()
				->condition('adm_no', $wd_student->adm_no)
				->condition('status_timestamp', $wd_student->status_timestamp)
			)
			->execute();
		}
	}
	global $base_url;
	$base_url = $base_url.'/admin/students/withdrawal/manage';
	$custom_url =  (urldecode(url($base_url)));
	$form_state['redirect'] = $base_url;
	drupal_set_message('All Withdrawal application were rejected successfully!!!', 'status');
}