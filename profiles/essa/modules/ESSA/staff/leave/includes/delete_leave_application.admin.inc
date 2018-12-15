<?php

/**
 *Implements page callback - edit_leave
*/

function delete_leave($form, $form_state, $data){
	$data = explode('%', $data);
	$emp_id = $data[0];
	$req_timestamp = $data[1];
	
	$session_id = (string)variable_get('essa_sid');
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leave_staff_history_table = 'essa_'.$session_id.'_leave_staff_history';
	$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	
	$principal = 0;
	$lm = 0;
	
	$leaves = db_query("SELECT * FROM {$leave_staff_history_table} WHERE emp_id = :eid AND req_timestamp = :t;", array(':eid' => $emp_id, ':t' => $req_timestamp));
	foreach($leaves as $leave){
		if($leave->leave_moderator == NULL){
			$principal = 1;
		}else{
			$lm = 1;
			$lm_id = $leave->leave_moderator;
		}
	}
	$date = date('d-m-Y');
	$apply_date = date('d-m-Y',$req_timestamp);
	if($principal == 1){
		$r_id = db_query("SELECT * FROM {role} WHERE name = :name;", array(':name' => 'Principal'));
		foreach($r_id as $rid){
			$u_id = db_query("SELECT * FROM {users_roles} WHERE rid = :rid;", array(':rid' => $rid->rid));
			foreach($u_id as $u){
				
				//Sending message to principal
				$module = 'leave';
				$recipients= array();
				$recipients[] = user_load($u->uid);
				$msg_subject = 'Leave Application cancelled by employee '.$emp_id;
				$msg_body = 'Leave application applied on '.$apply_date.' by employee '.$emp_id.' was cancelled on '.$date.'.';
				$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
				$msg_body = $msg_body.' <br>'.$footer;
				privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
									
				$principal_email = db_query("SELECT * FROM {$staff_table} WHERE uid = :uid AND status = 1;", array(':uid' => $u->uid));
				foreach($principal_email as $pe){
					$p_email = $pe->email;
				}
				
				//Sending email to principal.
				if($p_email != NULL){
			
					// Set hook_mail parameters.
					
					$email = $p_email;
						
					$body = 'Leave application applied on '.$apply_date.' by employee '.$emp_id.' was cancelled on '.$date.'.';
					$footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
					//dsm($body);
					$params = array(
						'subject' => 'Leave Application cancelled by employee '.$emp_id,
						'body' => $body."\n".$footer,
					);

					// Send out the e-mail.
					drupal_mail('leave', 'Essa', $email, language_default(), $params);
				}
			}
		}
	}
	if($lm == 1){
		$moderator = db_query("SELECT * FROM {$staff_master_table} WHERE emp_id = :eid;", array(':eid' => $lm_id));
		foreach($moderator as $m){
			$m_uid = $m->uid;
			$m_email = $m->email;
		}
		
		//sending message to leave_moderator
		$module = 'leave';
		$recipients= array();
		$recipients[] = user_load($m_uid);
		$msg_subject = 'Leave Application cancelled by employee '.$emp_id;
		$msg_body = 'Leave application applied on '.$apply_date.' by employee '.$emp_id.' was cancelled on '.$date.'.';
		$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
		$msg_body = $msg_body.' <br>'.$footer;
		privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
		
		//Sending email to leave_moderator.
		if($m_email != NULL){
	
			// Set hook_mail parameters.
			
			$email = $m_email;
				
			$body = 'Leave application applied on '.$apply_date.' by employee '.$emp_id.' was cancelled on '.$date.'.';
			$footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
			//dsm($body);
			$params = array(
				'subject' => 'Leave Application cancelled by employee '.$emp_id,
				'body' => $body."\n".$footer,
			);
			// Send out the e-mail.
			drupal_mail('leave', 'Essa', $email, language_default(), $params);
		}
	}
	
	db_delete($leave_staff_history_table)
	->condition(db_and()
		->condition('emp_id', $emp_id)
		->condition('req_timestamp', $req_timestamp)
	)
	->execute();
	
	global $user;
	global $base_url;
	$url = $base_url.'/user/'.$user->uid.'/leave';
	$form_state['redirect'] = $url;
	drupal_set_message('Leave apllication deleted successfully.');
}