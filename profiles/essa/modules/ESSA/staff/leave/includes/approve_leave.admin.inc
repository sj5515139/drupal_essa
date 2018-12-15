<?php

/**
 *Implements page callback function()
 */
function approve_leave_form($form = array(), &$form_state){
  $session_id = (string)variable_get('essa_sid');
  $leave_type_table = 'essa_'.$session_id.'_leave_types';
	$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
  $staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	global $user;
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
		$uid = $lm->uid;
	}
	$lm_emp_id  = db_query(
		"SELECT * from $staff_master_table where uid = :uid;", array(':uid' => $user->uid)
	);
	foreach($lm_emp_id as $lei){
		$emp_id = $lei->emp_id;
	}
	
	$leave_principal_role = db_query(
		"SELECT * from role where name = 'Principal';"
	);
	foreach($leave_principal_role as $lmr){
		$p_rid = $lmr->rid;
 	}
	
	$leave_moderators = db_query(
		"SELECT * from users_roles where uid = :uid;", array(':uid' => $user->uid)
	);
	foreach($leave_moderators as $lm){
		if($lm->rid == $lm_rid){
			$leaves = db_query(
				"SELECT * from $leave_history_table where status = 'Pending with Moderator' and leave_moderator = :lm;", array(':lm' => $emp_id)
			);
			foreach($leaves as $leave){
				$lm_emp_id  = db_query(
					"SELECT * from $staff_master_table where emp_id = :ei;", array(':ei' => $leave->emp_id)
				);
				foreach($lm_emp_id as $lei){
					$name = $lei->fname.' '.$lei->lname;
				}
				$row[] = array(
				  '#tree' =>TRUE,
				  $leave -> emp_id.'%'.$leave -> leave_id => array(
						$leave -> emp_id.'%'.$leave -> req_timestamp =>array(
				      '#type' => 'checkbox',
							'#options' => $leave -> emp_id.'%'.$leave->req_timestamp,
				    ),
						'c1' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'. $leave -> emp_id .'</h3>',
				    ),
				    'c2' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$name.'</h3>',
				    ),
				    'c3' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> leave_id.'</h3>',
				    ),
				    'c4' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.date('d-m-Y',$leave->from_date).'</h3>',
				    ),
				    'c5' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.date('d-m-Y',$leave->to_date).'</h3>',
				    ),
				    'c7' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> no_of_days.'</h3>',
				    ),
				    'c8' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> no_of_working_days.'</h3>',
				    ),
						'c9' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> reason.'</h3>',
							'#prefix' => '<div class = "leave_reason">',
				      '#suffix' => '</div>',
				    ),
				    'approve'.$leave -> emp_id.$leave -> req_timestamp =>array(
				      '#type' => 'submit',
				      '#submit' => array('approve_leave'),
				      '#value' => 'Approve',
							'#name' => $leave -> emp_id.'%'.$leave->req_timestamp,
				      '#prefix' => '<div class = "approve_leave">',
				      '#suffix' => '</div>',
				    ),
						'reject'.$leave -> emp_id.$leave -> req_timestamp =>array(
				      '#type' => 'submit',
				      '#submit' => array('reject_leave'),
				      '#value' => 'Reject',
							'#name' => $leave -> emp_id.'%'.$leave->req_timestamp,
				      '#prefix' => '<div class = "reject_leave">',
				      '#suffix' => '</div>',
				    ),
				  ),
				);
				$form['lts'] = array(
			    '#theme' => 'leave_moderator_action_table',
			    'rows' => $row,
			  );
			}
		}elseif($lm->rid == $p_rid){
			
			$leaves = db_query(
				"SELECT * from $leave_history_table where status = 'Pending with Principal';"
			);
			foreach($leaves as $leave){
				$lm_emp_id  = db_query(
					"SELECT * from $staff_master_table where emp_id = :ei;", array(':ei' => $leave->emp_id)
				);
				foreach($lm_emp_id as $lei){
					$name = $lei->fname.' '.$lei->lname;
				}
					$row_pending[] = array(
					  '#tree' =>TRUE,
					  $leave -> emp_id.'%'.$leave -> req_timestamp => array(  //Generating unique array id for every form element
							$leave -> emp_id.'%'.$leave -> req_timestamp =>array(
					      '#type' => 'checkbox',
								'#options' => $leave -> emp_id.'%'.$leave->req_timestamp,
						  ),
						  'c1' =>array(
					      '#type' => 'markup',
					      '#markup' => '<h3>'. $leave -> emp_id .'</h3>',
					    ),
					    'c2' =>array(
					      '#type' => 'markup',
						    '#markup' => '<h3>'.$name.'</h3>',
							),
						  'c3' =>array(
						    '#type' => 'markup',
						    '#markup' => '<h3>'.$leave -> leave_id.'</h3>',
						  ),
						  'c4' =>array(
						    '#type' => 'markup',
						    '#markup' => '<h3>'.date('d-m-Y',$leave->from_date).'</h3>',
							),
						  'c5' =>array(
						    '#type' => 'markup',
						    '#markup' => '<h3>'.date('d-m-Y',$leave->to_date).'</h3>',
						  ),
						  'c7' =>array(
						    '#type' => 'markup',
					      '#markup' => '<h3>'.$leave -> no_of_days.'</h3>',
						  ),
						  'c8' =>array(
					      '#type' => 'markup',
					      '#markup' => '<h3>'.$leave -> no_of_working_days.'</h3>',
					    ),
							'c9' =>array(
					      '#type' => 'markup',
					      '#markup' => '<h3>'.$leave -> reason.'</h3>',
								'#prefix' => '<div class = "leave_reason">',
						    '#suffix' => '</div>',
						  ),
							'c10' =>array(
					      '#type' => 'markup',
					      '#markup' => '<h3>'.$leave -> status_remark.'</h3>',
								'#prefix' => '<div class = "leave_reason">',
					      '#suffix' => '</div>',
					    ),
						  'approve'.$leave -> emp_id.$leave -> req_timestamp =>array(
						    '#type' => 'submit',
					      '#submit' => array('approve_leave'),
					      '#value' => 'Approve',
								'#name' => $leave -> emp_id.'%'.$leave->req_timestamp,
					      '#prefix' => '<div class = "approve_leave">',
					      '#suffix' => '</div>',
					    ),
							'reject'.$leave -> emp_id.$leave -> req_timestamp =>array(
						    '#type' => 'submit',
					      '#submit' => array('reject_leave'),
					      '#value' => 'Reject',
								'#name' => $leave -> emp_id.'%'.$leave->req_timestamp,
					      '#prefix' => '<div class = "reject_leave">',
					      '#suffix' => '</div>',
					    ),
						),
					);
				
				$form['lfs1'] = array(
					'#type' => 'fieldset',
					'#title' => 'Pending with Principal',
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
				);
				$form['lfs1']['pending_with_principal'] = array(
			    '#theme' => 'leave_principal_pending_table',
			    'rows' => $row_pending,
			  );
			}
			
			$leaves = db_query(
				"SELECT * from $leave_history_table where status = 'Approved By Moderator';"
			);
			foreach($leaves as $leave){
				$lm_emp_id  = db_query(
					"SELECT * from $staff_master_table where emp_id = :ei;", array(':ei' => $leave->emp_id)
				);
				foreach($lm_emp_id as $lei){
					$name = $lei->fname.' '.$lei->lname;
				}
				$row_approved[] = array(
				  '#tree' =>TRUE,
				  $leave -> emp_id.'%'.$leave -> req_timestamp => array(  //Generating unique array id for every form element
						$leave -> emp_id.'%'.$leave -> req_timestamp =>array(
				      '#type' => 'checkbox',
							'#options' => $leave -> emp_id.'%'.$leave->req_timestamp,
				    ),
				    'c1' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'. $leave -> emp_id .'</h3>',
				    ),
				    'c2' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$name.'</h3>',
				    ),
				    'c3' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> leave_id.'</h3>',
				    ),
				    'c7' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> no_of_days.'</h3>',
				    ),
				    'c9' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> reason.'</h3>',
							'#prefix' => '<div class = "leave_reason">',
				      '#suffix' => '</div>',
				    ),
						'c10' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> status_remark.'</h3>',
							'#prefix' => '<div class = "leave_reason">',
				      '#suffix' => '</div>',
				    ),
						'c11' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> remark_moderator.'</h3>',
							'#prefix' => '<div class = "leave_reason">',
				      '#suffix' => '</div>',
				    ),
						'c12' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.date('d-m-Y',$leave->moderator_timestamp).'</h3>',
							'#prefix' => '<div class = "leave_reason">',
				      '#suffix' => '</div>',
				    ),
				    'approve'.$leave -> emp_id.$leave -> req_timestamp =>array(
				      '#type' => 'submit',
				      '#submit' => array('approve_leave'),
				      '#value' => 'Approve',
							'#name' => $leave -> emp_id.'%'.$leave->req_timestamp,
				      '#prefix' => '<div class = "approve_leave">',
				      '#suffix' => '</div>',
				    ),
						'reject'.$leave -> emp_id.$leave -> req_timestamp =>array(
				      '#type' => 'submit',
				      '#submit' => array('reject_leave'),
				      '#value' => 'Reject',
							'#name' => $leave -> emp_id.'%'.$leave->req_timestamp,
				      '#prefix' => '<div class = "reject_leave">',
				      '#suffix' => '</div>',
				    ),
				  ),
				);
				
				$form['lfs2'] = array(
					'#type' => 'fieldset',
					'#title' => 'Approved By Moderator',
					'#collapsible' => TRUE,
					'#collapsed' => TRUE,
				);
				$form['lfs2']['principal_approved'] = array(
				  '#theme' => 'leave_principal_approval_table',
				  'rows' => $row_approved,
				);
			}
				
			$leaves = db_query(
				"SELECT * from $leave_history_table where status = 'Rejected By Moderator';"
			);
			foreach($leaves as $leave){
				$lm_emp_id  = db_query(
					"SELECT * from $staff_master_table where emp_id = :ei;", array(':ei' => $leave->emp_id)
				);
				foreach($lm_emp_id as $lei){
					$name = $lei->fname.' '.$lei->lname;
				}
				$row_rejected[] = array(
				  '#tree' =>TRUE,
				  $leave -> emp_id.'%'.$leave -> req_timestamp => array(  //Generating unique array id for every form element
						$leave -> emp_id.'%'.$leave -> req_timestamp =>array(
				      '#type' => 'checkbox',
							'#options' => $leave -> emp_id.'%'.$leave->req_timestamp,
				    ),
				    'c1' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'. $leave -> emp_id .'</h3>',
				    ),
				    'c2' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$name.'</h3>',
				    ),
				    'c3' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> leave_id.'</h3>',
				    ),
				    'c7' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> no_of_days.'</h3>',
				    ),
				    'c9' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> reason.'</h3>',
							'#prefix' => '<div class = "leave_reason">',
				      '#suffix' => '</div>',
				    ),
						'c10' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> status_remark.'</h3>',
							'#prefix' => '<div class = "leave_reason">',
				      '#suffix' => '</div>',
				    ),
						'c11' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> remark_moderator.'</h3>',
							'#prefix' => '<div class = "leave_reason">',
				      '#suffix' => '</div>',
				    ),
						'c12' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.date('d-m-Y',$leave->moderator_timestamp).'</h3>',
							'#prefix' => '<div class = "leave_reason">',
				      '#suffix' => '</div>',
				    ),
				    'approve'.$leave -> emp_id.$leave -> req_timestamp =>array(
				      '#type' => 'submit',
				      '#submit' => array('approve_leave'),
				      '#value' => 'Approve',
							'#name' => $leave -> emp_id.'%'.$leave->req_timestamp,
				      '#prefix' => '<div class = "approve_leave">',
				      '#suffix' => '</div>',
				    ),
						'reject'.$leave -> emp_id.$leave -> req_timestamp =>array(
				      '#type' => 'submit',
				      '#submit' => array('reject_leave'),
				      '#value' => 'Reject',
							'#name' => $leave -> emp_id.'%'.$leave->req_timestamp,
				      '#prefix' => '<div class = "reject_leave">',
				      '#suffix' => '</div>',
				    ),
				  ),
				);
				
				$form['lfs3'] = array(
					'#type' => 'fieldset',
					'#title' => 'Rejected By Moderator',
					'#collapsible' => TRUE,
					'#collapsed' => TRUE,
				);
				
				$form['lfs3']['principal_rejected'] = array(
			    '#theme' => 'leave_principal_rejected_table',
			    'rows' => $row_rejected,
			  );
			}
				
			$leaves = db_query(
				"SELECT * from $leave_history_table where status = 'Pending with Moderator';"
			);
			foreach($leaves as $leave){
				$lm_emp_id  = db_query(
					"SELECT * from $staff_master_table where emp_id = :ei;", array(':ei' => $leave->emp_id)
				);
				foreach($lm_emp_id as $lei){
					$name = $lei->fname.' '.$lei->lname;
				}
				$row_pending_moderator[] = array(
				  '#tree' =>TRUE,
				  $leave -> emp_id.'%'.$leave -> req_timestamp => array(  //Generating unique array id for every form element
						$leave -> emp_id.'%'.$leave -> req_timestamp =>array(
				      '#type' => 'checkbox',
							'#options' => $leave -> emp_id.'%'.$leave->req_timestamp,
				    ),
				    'c1' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'. $leave -> emp_id .'</h3>',
				    ),
				    'c2' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$name.'</h3>',
				    ),
				    'c3' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> leave_id.'</h3>',
				    ),
				    'c4' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.date('d-m-Y',$leave->from_date).'</h3>',
				    ),
				    'c5' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.date('d-m-Y',$leave->to_date).'</h3>',
				    ),
				    'c7' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> no_of_days.'</h3>',
				    ),
				    'c8' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> no_of_working_days.'</h3>',
				    ),
						'c9' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> reason.'</h3>',
							'#prefix' => '<div class = "leave_reason">',
				      '#suffix' => '</div>',
				    ),
						'c10' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3>'.$leave -> status_remark.'</h3>',
							'#prefix' => '<div class = "leave_reason">',
				      '#suffix' => '</div>',
				    ),
				    'approve'.$leave -> emp_id.$leave -> req_timestamp =>array(
				      '#type' => 'submit',
				      '#submit' => array('approve_leave'),
				      '#value' => 'Approve',
							'#name' => $leave -> emp_id.'%'.$leave->req_timestamp,
				      '#prefix' => '<div class = "approve_leave">',
				      '#suffix' => '</div>',
				    ),
						'reject'.$leave -> emp_id.$leave -> req_timestamp =>array(
				      '#type' => 'submit',
				      '#submit' => array('reject_leave'),
				      '#value' => 'Reject',
							'#name' => $leave -> emp_id.'%'.$leave->req_timestamp,
				      '#prefix' => '<div class = "reject_leave">',
				      '#suffix' => '</div>',
				    ),
				  ),
				);
				
				$form['lfs4'] = array(
					'#type' => 'fieldset',
					'#title' => 'Pending with Moderator',
					'#collapsible' => TRUE,
					'#collapsed' => TRUE,
				);
				$form['lfs4']['principal_pending'] = array(
			    '#theme' => 'leave_principal_pending_table',
			    'rows' => $row_pending_moderator,
			  );
			}
		}
	}
	
	if(isset($row) || isset($row_pending_moderator) || isset($row_rejected) || isset($row_approved) || isset($row_pending)){
		$form['approve_selected'] = array(
			'#type' => 'submit',
			'#value' => 'Approve Selected',
			'#submit' => array('approve_selected'),
		);
		$form['approve_all'] = array(
			'#type' => 'submit',
			'#value' => 'Approve All',
			'#submit' => array('approve_all'),
		);
	}else{
		drupal_set_message('There are no pending leave application.','status');
	}
	
	return $form;
}

function approve_selected($form, &$form_state){
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k=>$v){
				if($v[$k] == 1){
					$string = explode('%',$k);
					$emp_id = $string[0];
					$req_timestamp = $string[1];
					
					global $base_url;
					$base_url = $base_url.'/admin/staff/leave/approve_leave';
					$form_state['redirect'] = $base_url;
					
					global $user;
					$session_id = (string)variable_get('essa_sid');
					$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
					$leave_type_table = 'essa_'.$session_id.'_leave_types';
					$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
					$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
					$application_time = date('m/d/Y h:i:s');
					$timestamp = strtotime($application_time);
					
					db_update($leave_history_table)
						->fields(array(
							'status' => 'Approved',
							'status_remark' => 'Principal',
							'status_principal' => 'Approved',
							'principal_timestamp' => $timestamp,
							))
						->condition(db_and()
						  ->condition('emp_id', $emp_id)
						  ->condition('req_timestamp', $req_timestamp)
						)
						->execute();
					
					$leaves = db_query(
						"SELECT * from $leave_history_table where emp_id = :emp_id and req_timestamp = :rt;", array(':emp_id' => $emp_id, ':rt' => $req_timestamp)
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
							"SELECT * from $leave_staff_table where emp_id = :emp_id and leave_id = :li;", array(':emp_id' => $emp_id, ':li' => $leave_id)
						);
						foreach($leaves as $leave){
							db_update($leave_staff_table)
								->fields(array(
										$k => $leave->$k + $count[$k],
									))
								->condition(db_and()
								  ->condition('emp_id', $emp_id)
								  ->condition('leave_id', $leave_id)
								)
								->execute();
						}
					}
					
					$leaves = db_query(
						"SELECT * from $leave_staff_table where emp_id = :emp_id and leave_id = :li;", array(':emp_id' => $emp_id, ':li' => $leave_id)
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
							  ->condition('emp_id', $emp_id)
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
							  ->condition('emp_id', $emp_id)
							  ->condition('leave_id', $leave_id)
							)
							->execute();
					}
					
					//*******Suraj********//
					$tti_uid = NULL;
					$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
					$employee = db_query("SELECT * FROM {$staff_master_table} WHERE emp_id = :emp;",array(':emp' => $emp_id));
					foreach($employee as $emp){
						$emp_uid = $emp->uid;
					}
					$staff_emp_id = db_query(
						"SELECT * from $staff_master_table where uid = :uid;", array(':uid' => $user->uid)
					);
					foreach($staff_emp_id as $sei){
						$name = $sei->fname.' '.$sei->lname;
					}
					$date = date('m/d/Y',$req_timestamp);
					//sending message to employee 
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
					$leave_dates = db_query("SELECT * FROM {$leave_history_table} WHERE emp_id = :emp AND req_timestamp = :time;", array(':emp' => $emp_id, ':time' =>$req_timestamp));
					foreach($leave_dates as $l_date){
						$leave_from = date('m/d/Y',$l_date->from_date);
						$leave_to = date('m/d/Y',$l_date->to_date);
					}
					$module = 'leave';
					$recipients= array();
					$recipients[] = user_load($tti_uid);
					$msg_subject = 'Employee ID '.$emp_id.' will be on leave from '.$leave_from.' to '.$leave_to.'.';
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
						'message' => 'Leave application of Employee ID '.$emp_id.' was approved by Principal '.$name.'.',
						'priority' => 'L',
						'module' => 'leave',
						'source_url' => 'leave/approve',
						'timestamp' => $strtodate,
						'source_uid' => $user->uid,
					))
					->execute();
					//*******Suraj********//
				}
			}
		}
	}
	drupal_set_message('Leave application/s were approved.','status');
}

function approve_all($form, &$form_state){
	
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k=>$v){
				$string = explode('%',$k);
				$emp_id = $string[0];
				$req_timestamp = $string[1];
				
				global $base_url;
				$base_url = $base_url.'/admin/staff/leave/approve_leave';
				$form_state['redirect'] = $base_url;
				
				global $user;
				$session_id = (string)variable_get('essa_sid');
				$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
				$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
				$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
				$application_time = date('m/d/Y h:i:s');
				$timestamp = strtotime($application_time);
				
				db_update($leave_history_table)
					->fields(array(
						'status' => 'Approved',
						'status_remark' => 'Principal',
						'status_principal' => 'Approved',
						'principal_timestamp' => $timestamp,
						))
					->condition(db_and()
					  ->condition('emp_id', $emp_id)
					  ->condition('req_timestamp', $req_timestamp)
					)
					->execute();
					
					
					
				$leaves = db_query(
					"SELECT * from $leave_history_table where emp_id = :emp_id and req_timestamp = :rt;", array(':emp_id' => $emp_id, ':rt' => $req_timestamp)
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
				
				foreach($count as $key=>$value){
					$leaves = db_query(
						"SELECT * from $leave_staff_table where emp_id = :emp_id and leave_id = :li;", array(':emp_id' => $emp_id, ':li' => $leave_id)
					);
					foreach($leaves as $leave){
						db_update($leave_staff_table)
							->fields(array(
									$key => $leave->$key + $count[$key],
								))
							->condition(db_and()
							  ->condition('emp_id', $emp_id)
							  ->condition('leave_id', $leave_id)
							)
							->execute();
					}
				}
				
				$leaves = db_query(
					"SELECT * from $leave_staff_table where emp_id = :emp_id and leave_id = :li;", array(':emp_id' => $emp_id, ':li' => $leave_id)
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
						  ->condition('emp_id', $emp_id)
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
						  ->condition('emp_id', $emp_id)
						  ->condition('leave_id', $leave_id)
						)
						->execute();
				}
				$tti_uid = NULL;
				//*******Suraj********//
				$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
				$employee = db_query("SELECT * FROM {$staff_master_table} WHERE emp_id = :emp;",array(':emp' => $emp_id));
				foreach($employee as $emp){
					$emp_uid = $emp->uid;
				}
				$staff_emp_id = db_query(
					"SELECT * from $staff_master_table where uid = :uid;", array(':uid' => $user->uid)
				);
				foreach($staff_emp_id as $sei){
					$name = $sei->fname.' '.$sei->lname;
				}
				$date = date('m/d/Y',$req_timestamp);
				//sending message to employee 
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
				$leave_dates = db_query("SELECT * FROM {$leave_history_table} WHERE emp_id = :emp AND req_timestamp = :time;", array(':emp' => $emp_id, ':time' =>$req_timestamp));
				foreach($leave_dates as $l_date){
					$leave_from = date('m/d/Y',$l_date->from_date);
					$leave_to = date('m/d/Y',$l_date->to_date);
				}
				$module = 'leave';
				$recipients= array();
				$recipients[] = user_load($tti_uid);
				$msg_subject = 'Employee ID '.$emp_id.' will be on leave from '.$leave_from.' to '.$leave_to.'.';
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
					'message' => 'Leave application of Employee ID '.$emp_id.' was approved by Principal '.$name.'.',
					'priority' => 'L',
					'module' => 'leave',
					'source_url' => 'leave/approve',
					'timestamp' => $strtodate,
					'source_uid' => $user->uid,
				))
				->execute();
				//*******Suraj********//
			}
		}
	}
	drupal_set_message('Leave applications were approved.','status');
}

function approve_leave($form, &$form_state){
	global $user;
	variable_set('leave_'.$user->uid, $form_state['triggering_element']['#name']);
	//dsm($form_state['triggering_element']['#name']);
	global $base_url;
	$base_url = $base_url.'/admin/staff/leave/approve_leave';
	$custom_url =  (urldecode(url($base_url, array('query' => array('destination' => '#overlay=leave/approve')))));
	$form_state['redirect'] = $custom_url;
	overlay_trigger_refresh();
}

function reject_leave($form, &$form_state){
	global $user;
	variable_set('leave_'.$user->uid, $form_state['triggering_element']['#name']);
	
	global $base_url;
	$base_url = $base_url.'/admin/staff/leave/approve_leave';
	$custom_url =  (urldecode(url($base_url, array('query' => array('destination' => '#overlay=leave/reject')))));
	$form_state['redirect'] = $custom_url;
	overlay_trigger_refresh();
}

/**
 *Theme function
 */
function theme_leave_principal_approval_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t(''),t('Emp ID'),t('Name'), t('Leave ID'),t('No. of Days'),t('Reason'),t('Approved By'),t('Moderator\'s Remark'),t('Approved on'),t(''),t(''));
  
  // Setup the structure to be rendered and returned.
  $content = array(
    '#theme' => 'table',
    '#rows' => array(),
    '#header' => $header,
  );
  
  // Traverse each row.  @see element_chidren().
  foreach (element_children($rows) as $row_index) {
    $row = array();
    // Traverse each column in the row.  @see element_children().
    foreach (element_children($rows[$row_index]) as $col_index) {
      // Traverse each column in the row.  @see element_children().
      foreach (element_children($rows[$row_index][$col_index]) as $col_index1) {
      // Render the column form element.
        $row[] = drupal_render($rows[$row_index][$col_index][$col_index1]);
      }
    }
    // Add the row to the table.
    $content['#rows'][] = $row;
  }

  // Redner the table and return.
  return drupal_render($content);

}

/**
 *Theme function
 */
function theme_leave_principal_rejected_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t(''),t('Emp ID'),t('Name'), t('Leave ID'),t('No. of Days'),t('Reason'),t('Rejected By'),t('Moderator\'s Remark'),t('Rejected on'),t(''),t(''));
  
  // Setup the structure to be rendered and returned.
  $content = array(
    '#theme' => 'table',
    '#rows' => array(),
    '#header' => $header,
  );
  
  // Traverse each row.  @see element_chidren().
  foreach (element_children($rows) as $row_index) {
    $row = array();
    // Traverse each column in the row.  @see element_children().
    foreach (element_children($rows[$row_index]) as $col_index) {
      // Traverse each column in the row.  @see element_children().
      foreach (element_children($rows[$row_index][$col_index]) as $col_index1) {
      // Render the column form element.
        $row[] = drupal_render($rows[$row_index][$col_index][$col_index1]);
      }
    }
    // Add the row to the table.
    $content['#rows'][] = $row;
  }

  // Redner the table and return.
  return drupal_render($content);

}

/**
 *Theme function
 */
function theme_leave_principal_pending_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t(''),t('Emp ID'),t('Name'), t('Leave ID'), t('From Date'), t('To Date'),t('No. of Days'),t('No. of Working Days'),t('Reason'),t('Pending With'),t(''),t(''));
  
  // Setup the structure to be rendered and returned.
  $content = array(
    '#theme' => 'table',
    '#rows' => array(),
    '#header' => $header,
  );
  
  // Traverse each row.  @see element_chidren().
  foreach (element_children($rows) as $row_index) {
    $row = array();
    // Traverse each column in the row.  @see element_children().
    foreach (element_children($rows[$row_index]) as $col_index) {
      // Traverse each column in the row.  @see element_children().
      foreach (element_children($rows[$row_index][$col_index]) as $col_index1) {
      // Render the column form element.
        $row[] = drupal_render($rows[$row_index][$col_index][$col_index1]);
      }
    }
    // Add the row to the table.
    $content['#rows'][] = $row;
  }

  // Redner the table and return.
  return drupal_render($content);

}

/**
 *Theme function
 */
function theme_leave_moderator_action_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t(''), t('Emp ID'),t('Name'), t('Leave ID'), t('From Date'), t('To Date'),t('No. of Days'),t('No. of Working Days'),t('Reason'),t(''),t(''));
  
  // Setup the structure to be rendered and returned.
  $content = array(
    '#theme' => 'table',
    '#rows' => array(),
    '#header' => $header,
  );
  
  // Traverse each row.  @see element_chidren().
  foreach (element_children($rows) as $row_index) {
    $row = array();
    // Traverse each column in the row.  @see element_children().
    foreach (element_children($rows[$row_index]) as $col_index) {
      // Traverse each column in the row.  @see element_children().
      foreach (element_children($rows[$row_index][$col_index]) as $col_index1) {
      // Render the column form element.
        $row[] = drupal_render($rows[$row_index][$col_index][$col_index1]);
      }
    }
    // Add the row to the table.
    $content['#rows'][] = $row;
  }

  // Redner the table and return.
  return drupal_render($content);

}