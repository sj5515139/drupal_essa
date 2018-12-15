<?php

function class_teacher($form, &$form_state){
  $session = variable_get('essa_sid');
	$section_table = 'essa_'.$session.'_class_section';
	$class_list = array();


	//******Removing Notifications******//
	global $base_url;
	global $user;
	$path = current_path();
	//dsm($path);
	$url = 'admin/settings/classes';
	$notification_table = 'essa_'.$session.'_notifications';

	if($url == $path){
		$notifications = db_query("SELECT * FROM {$notification_table}");
		foreach($notifications as $notification){
			//dsm('ok');
			db_update($notification_table)
			->fields(array(
				'status' => '1',
			))
			->condition(db_and()
				->condition('uid', $user->uid)
				->condition('destination_url', $url)
			)
			->execute();
		}
	}
	//********************

	$voc = 'class_vocab';//replace this with the taxonomy term
  $vocabulary = taxonomy_vocabulary_machine_name_load($voc);
	$class_sec = taxonomy_get_tree($vocabulary->vid);
	foreach($class_sec as $cs){
		if($cs->parents[0] != 0){
			$cl = taxonomy_term_load($class);
			$section[$cl->name][] = $cs->name;
		}else{
			$class = $cs->tid;
		}
	}

	$class_list_db = db_query(
		"SELECT sections from {$section_table};"
	);

  $ct_table = 'essa_'.$session.'_class_teacher';
  $ct_db = db_query(
		"SELECT * from {$ct_table}"
	);

  foreach($ct_db as $ct){
		//dsm($ct);
    $default[$ct->class.'_'.$ct->section] = $ct->teacher_fname.' '. $ct->teacher_lname.' ('.$ct->teacher_nickname.')';
  }

	//******SURAJ******//
	$a_uid = array();
	$admin_rid = db_query("SELECT * FROM role WHERE name = 'administrator' OR name = 'Principal';");
	foreach($admin_rid as $a_rid){
		$ar = db_query("SELECT * FROM users_roles WHERE rid = :rid;", array(':rid' => $a_rid->rid));
		foreach($ar as $u){
			$a_uid[] = $u->uid;
		}
	}
	global $user;
	$flag = 0;
	foreach($a_uid as $au){
		if($au == $user->uid){
			$flag = 1;
		}
	}

	if($flag == 1){
		foreach($section as $cls => $sec){
			$form[$cls] = array(
				'#type' => 'fieldset',
				'#title' => $cls,
			);
			foreach($sec as $s){
				$form[$cls][$cls.'_'.$s] = array(
					'#type' => 'textfield',
					'#title' => t(strtoupper($s)),
					'#autocomplete_path' => 'teachers/autocomplete',
					'#default_value' => isset($default[$cls.'_'.$s])? $default[$cls.'_'.$s]: NULL,
					'#size' => 40,
				);
			}
		}

		$form['save'] = array(
			'#type' => 'submit',
			'#value' => t('Save'),
		);
	}else{
		foreach($section as $cls => $sec){
			$form[$cls] = array(
				'#type' => 'fieldset',
				'#title' => $cls,
			);
			foreach($sec as $s){
				$form[$cls][$cls.'_'.$s] = array(
					'#type' => 'textfield',
					'#title' => t(strtoupper($s)),
					'#autocomplete_path' => 'teachers/autocomplete',
					'#default_value' => isset($default[$cls.'_'.$s])? $default[$cls.'_'.$s]: NULL,
					'#size' => 40,
					'#disabled' => TRUE,
				);
			}
		}
	}



  return $form;
}

/**
 *Implements submit function
 */
function class_teacher_submit($form, &$form_state){
	
	// for new_session
	$options = variable_get('essa_session_setup_unmark');
	if(isset($options)){
		if(in_array('Class Teacher', $options)){
			unset($options['Class Teacher']);
			variable_set('essa_session_setup_unmark', $options);
			drupal_goto('form_redirect');
		}
	}
	
	$session = variable_get('essa_sid');
	$section_table = 'essa_'.$session.'_class_section';
  $staff_table = 'essa_'.$session.'_master_staff_table';
  $ct_table = 'essa_'.$session.'_class_teacher';
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	$notification_table = 'essa_'.$session.'_notifications';
	global $user;

	$ctr = array();
	$cts = array();
	$tnn = array();
	$flag = 0;

	$all_teachers = db_query(
		"SELECT * from {$staff_table} where type = 'Teaching';"
	);
  foreach($all_teachers as $t){
		$nn[] = $t->nickname;
	}

  $class_list_db = db_query(
		"SELECT sections from {$section_table}"
	);

  foreach($class_list_db as $cl){
    $class[] = $cl->sections;
  }

	$class_teacher = db_query(
		"SELECT * from {$ct_table}"
	);

	foreach($class_teacher as $ct){
		$cts[] = $ct -> teacher_nickname;
		$ctr[$ct->class.'_'.$ct->section] = $ct->id;
	}

	foreach($form_state['values'] as $cls => $val){
		if($val != NULL && in_array($cls, $class)){
      $class_list = explode('_', $cls);
      $cl = $class_list[0];
      $sec = $class_list[1];
      preg_match('#\((.*?)\)#', $val, $match);
			if(isset($match[1])){
				if(in_array($match[1], $nn)){
					$tnn[$cl.'_'.$sec] = $match[1];
				}else{
					drupal_set_message('Please enter a valid teacher from the list, for class - <b>'.$cl.' - '.$sec.'</b>.', 'error');
					$flag = 1;
				}
			}else{
				drupal_set_message('Please enter a valid teacher from the list, for class - <b>'.$cl.' - '.$sec.'</b>.', 'error');
				$flag = 1;
			}
		}
	}

	$dup = 0;
	foreach($tnn as $cs => $tn){
		$nn = $tn;
		foreach($tnn as $cs_check => $tn_check){
			if($nn == $tn_check && $cs != $cs_check){
				$dup = 1;
				$flag = 1;
				$dup_entries = $cs.' , ';
			}
		}
	}

	if($dup == 1){
		drupal_set_message('You can\'t allot same teacher as class teacher for more than one class.', 'error');
	}

	if($flag == 0){
		$session = variable_get('essa_sid');
		$section_table = 'essa_'.$session.'_class_section';
		$staff_table = 'essa_'.$session.'_master_staff_table';
		$ct_table = 'essa_'.$session.'_class_teacher';
		$ctr = array();

		$class_list_db = db_query(
			"SELECT sections from {$section_table}"
		);

		foreach($class_list_db as $cl){
		  $class[] = $cl->sections;
		}

		$class_teacher = db_query(
			"SELECT * from {$ct_table}"
		);

		foreach($class_teacher as $ct){
			$ctr[$ct->class.'_'.$ct->section] = $ct->id;
		}

		foreach($form_state['values'] as $cls => $val){
			if($val != NULL && in_array($cls, $class)){
		    $class_list = explode('_', $cls);
		    $cl = $class_list[0];
		    $sec = $class_list[1];
		    preg_match('#\((.*?)\)#', $val, $match);

				//******Suraj******//

				$prev_data = NULL;
				$previous_data = db_query("SELECT * FROM {$ct_table} WHERE class =:class AND section = :sec;", array(':class' => $cl, ':sec' => $sec));
				foreach($previous_data as $p_data){
					$prev_data = $p_data->teacher_nickname;
				}

				//******Suraj******//

		    $staff_db = db_query(
		    	"SELECT * from {$staff_table} where nickname = :nickname",  array(':nickname' => $match[1])
		    );
		    foreach($staff_db as $staff){
				$fname = $staff->fname;
				$lname = $staff->lname;
				$emp_id = $staff->emp_id;
				$uid = $staff->uid;
		    }
		    db_merge($ct_table)
					->key(array('id' => isset($ctr[$cls]) ? $ctr[$cls] : NULL))
					->fields (array(
						'class' => $cl,
						'section' => $sec,
						'teacher_nickname' => $match[1],
						'teacher_fname' => $fname,
						'teacher_lname' => $lname,
					)
				)
		    ->execute();

				//******Suraj******//

				$new_data = db_query("SELECT * FROM {$ct_table} WHERE class =:class AND section = :sec;", array(':class' => $cl, ':sec' => $sec));
				foreach($new_data as $n_data){
					$nd = $n_data->teacher_nickname;
					$n_emp_id = $emp_id;
					$n_name = $n_data->teacher_fname.' '.$n_data->teacher_lname;
				}

				//dsm($prev_data);dsm($nd);
				if($prev_data != $nd || $prev_data == NULL){
					//dsm($n_emp_id);
					//dsm($n_name);
					//dsm($cl);
					//dsm($sec);
					//Sending Message to class teacher
					global $base_url;
					$module = 'leave';
					$recipients= array();
					$recipients[] = user_load($uid);
					$msg_subject = 'Appointment as Class Teacher';
					$msg_body = 'You have been appointed as Class Teacher of '.$cl.' - '.$sec. '. Please login <a href ="'.$base_url.'">here</a>.';
					$footer = '<p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
					$msg_body = $msg_body.'<br>'.$footer;
					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());

					//sending system alert
					$created_date = date("Y-m-d H:i:s");
					$strtodate = strtotime($created_date);
					db_insert($sys_alert_table)
					->fields(array(
						'message' => $emp_id.' was appointed as class teacher for '.$cl.'-'.$sec,
						'priority' => 'L',
						'module' => 'school_master',
						'source_url' => 'admin/settings/classes/class-teacher',
						'timestamp' => $strtodate,
						'source_uid' => $user->uid,
					))
					->execute();


					$employee_email = db_query("SELECT * FROM {$staff_table} WHERE uid = :uid AND status = 1;", array(':uid' => $uid));
					foreach($employee_email as $e){
						$emp_email = $e->email;
					}

					//Sending email to employee.
					if($emp_email != NULL){

						// Set hook_mail parameters.

						$email = $emp_email;

						$body = 'You have been appointed as Class Teacher of '.$cl.' - '.$sec. '. Please login <a href ="'.$base_url.'">here</a>.';
						$footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
						//dsm($body);
						$params = array(
						  'subject' => 'Appointment as Class Teacher',
						  'body' => $body."\n".$footer,
						);
						// Send out the e-mail.
						drupal_mail('school_master', 'Essa', $emp_email, language_default(), $params);
					}

				}
				//******Suraj******//
		  }else{
				if(in_array($cls, $class)){
					$class_list = explode('_', $cls);
					$cl = $class_list[0];
					$sec = $class_list[1];
					$ctr_nn = NULL;

					//******Suraj******//

					//Sending System Alert
					$created_date = date("Y-m-d H:i:s");
					$strtodate = strtotime($created_date);
					db_insert($sys_alert_table)
					->fields(array(
						'message' => 'Class '.$cls.' was not allotted any class teacher.',
						'priority' => 'M',
						'module' => 'school_master',
						'source_url' => 'admin/settings/classes/class-teacher',
						'timestamp' => $strtodate,
						'source_uid' => $user->uid,
					))
					->execute();

					//Sending Notifiacation To Principal And Administration
					$admin_r_id = db_query("SELECT * FROM {role} WHERE name = :name OR name = :name1;", array(':name' => 'administrator', ':name1' => 'Principal'));
					foreach($admin_r_id as $rid){
						$u_id = db_query("SELECT * FROM {users_roles} WHERE rid = :rid;", array(':rid' => $rid->rid));
						foreach($u_id as $u){
							$uid = $u->uid;
							$msg_flag = 0;
							$msg = db_query("SELECT * FROM {$notification_table} WHERE uid = :uid AND message = :m AND status = :s;", array(':uid' => $uid, ':m' => 'Class '.$cls.' was not allotted any class teacher.', ':s' => '0'));
							foreach($msg as $m){
								if($m != NULL){
									$msg_flag = 1;
								}
							}
							if($msg_flag == 0){
								db_insert($notification_table)
								->fields(array(
									'uid' => $uid,
									'rid' => $rid->rid,
									'message' => 'Class '.$cls.' was not allotted any class teacher.',
									'status' => '0',
									'module' => 'school_master',
									'source_url' => 'admin/settings/classes/alot-class-teacher',
									'destination_url' => 'admin/settings/classes',
									'timestamp' => $strtodate,
									'source_uid' => $user->uid,
								))
								->execute();
							}
						}
					}

					//******Suraj******//

					$class_teacher = db_query(
						"SELECT * from {$ct_table} where class = :cl and section = :sec", array(':cl' => $cl, ':sec' => $sec)
					);

					foreach($class_teacher as $ct){
						$ctr_nn = $ct->teacher_nickname;
					}

					if(isset($ctr_nn)){
						$staff_db = db_query(
							"SELECT * from {$staff_table} where nickname = :nickname",  array(':nickname' => $ctr_nn)
						);
						foreach($staff_db as $staff){
						  $emp_id = $staff->emp_id;
						  $uid = $staff->uid;
						}

						if(isset($uid)){
							$class_teacher_role = db_query(
								"SELECT * from role where name = 'Class Teacher';"
							);
							foreach($class_teacher_role as $ctr){
								$rid = $ctr->rid;
							}
							db_delete('users_roles')
							->condition(db_and()
									->condition('uid', $uid)
									->condition('rid', $rid)
								)
							->execute();

							db_delete($ct_table)
								->condition(db_and()
									->condition('class', $cl)
									->condition('section', $sec)
								)
							->execute();
						}
					}
				}
			}
		}

		$class_teacher = db_query(
			"SELECT * from {$ct_table}"
		);
		foreach($class_teacher as $ct){
			$teachers = db_query(
				"SELECT * from {$staff_table} where nickname = :nn AND status = 1", array(':nn' => $ct->teacher_nickname)
			);
			foreach($teachers as $teacher){
				$uid = $teacher->uid;// User ID of user that you want to add role to.
				$role_name = 'Class Teacher'; // The name of the role to add.
				if ($role = user_role_load_by_name($role_name)) {
				  user_multiple_role_edit(array($uid), 'add_role', $role->rid);
				}
			}
		}

		menu_rebuild();
		drupal_set_message('Class teachers were alotted successfully.','status');

	}

}