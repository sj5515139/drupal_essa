<?php

/**
 *Implements callback function for sub_teacher_alloc
 */
function sub_teacher_alloc($form, &$form_state, $class){
	$session = variable_get('essa_sid');
	
	$class_table = 'essa_'.$session.'_class_list';
	
	
	$class_term = taxonomy_get_term_by_name($class);
	foreach($class_term as $ct){
		$tid = $ct->tid;
	}
	
	//$sections = array('--Select--');
	$sec = taxonomy_get_children($tid);
	foreach($sec as $s){
		$sections[] = $s->name;
	}
	
	$form['sec'] = array(
		'#type' => 'select',
		'#title' => 'Select a Section for class '.$class,
		'#options' => drupal_map_assoc($sections),
		'#required' => TRUE,
		'#ajax' => array(
		  'event' => 'change',
		  'callback' => 'subject_list_ajax',
		  'wrapper' => 'subject_wrapper',
		  'method' => 'replace',
		  'effect' => 'fade',
		),
	);
	
	
	$form['subject_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "subject_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['class'] = array(
		'#type' => 'value',
		'#value' => $class,
	);
	
	if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
		$sub_teacher_table = 'essa_'.$session.'_subject_teacher_table';
		$staff_table = 'essa_'.$session.'_master_staff_table';
		$class_sub_table = 'essa_'.$session.'_subjects_'.mod_sub_string($form_state['values']['class']);
		$emp = array();
		$employees = db_query("SELECT * FROM {$staff_table} WHERE type = :t OR type =:tc AND status = 1;", array(':t' => 'Teaching', ':tc' => 'teaching'));
		foreach($employees as $employee){
			$emp[] = $employee->emp_id;
		}
		
		$subjects = db_query("SELECT * FROM {$class_sub_table}");
		foreach($subjects as $subject){
			$default_data = db_query("SELECT * FROM {$sub_teacher_table} WHERE class =:c AND section = :sec AND subject = :sub;", array(':c' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'], ':sub' => $subject->sub_id));
			foreach($default_data as $dd){
				$staffs = db_query("SELECT * FROM {$staff_table} WHERE emp_id = :e AND status = 1;", array(':e' => $dd->teacher));
				foreach($staffs as $staff){
					$teacher = $staff->fname.' '.$staff->lname.' ('.$staff->nickname.')';
				}
			}
			
			if($teacher != NULL){
				$row[$form_state['values']['class'].$form_state['values']['sec'].$subject->sub_id] = array(
					'#tree' =>TRUE,
					$subject->sub_id => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$subject->sub_name.'</h3>',
						),
						'c2' =>array(
							'#type' => 'textfield',
							'#autocomplete_path' => 'teachers/autocomplete',
							'#size' => 20,
							'#default_value' => $teacher,
						),
					),
				);
			}else{
				$row[$form_state['values']['class'].$form_state['values']['sec'].$subject->sub_id] = array(
					'#tree' =>TRUE,
					$subject->sub_id => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$subject->sub_name.'</h3>',
						),
						'c2' =>array(
							'#type' => 'textfield',
							'#autocomplete_path' => 'teachers/autocomplete',
							'#size' => 20,
						),
					),
				);
			}
			$teacher = NULL;
		}
		if($emp != NULL){
			if(isset($row)){
				$form['subject_wrapper']['subject'] = array(
					'#theme' => 'subject_teacher_table',
					'rows' => $row,
				);
				$form['subject_wrapper']['submit'] = array(
					'#type' => 'submit',
					'#value' => 'Save',
					'#submit' => array('subject_list_ajax_submit'),
				);
			}else{
				global $base_url;
				$url = $base_url.'/admin/settings/subjects/'.$form_state['values']['class'];
				$form['subject_wrapper']['subject'] = array(
					'#type' => 'markup',
					'#markup' => '<h3 style = "color: red;"> No subject are created yet for class '.$form_state['values']['class'].'-'.$form_state['values']['sec'].'. Click <a href = "'.$url.'"><u>here</u></a> to create. </h3>',
				);
			}
		}else{
			global $base_url;
			$url1 = $base_url.'/admin/staff/recruitment';
			$form['subject_wrapper']['emp'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 style = "color: red;"> No teachers in the system. Add teachers <a href = "'.$url1.'">here</a>. </h3>',
			);
		}
	}
	
	return $form;
}

/**
 *Implements validate function sub_teacher_alloc_validate().
 */
function sub_teacher_alloc_validate($form, &$form_state){
	$session = variable_get('essa_sid');
	$staff_table = 'essa_'.$session.'_master_staff_table';
	global $user;
	
	$staffs = db_query("SELECT * FROM {$staff_table} WHERE status = 1");
	foreach($staffs as $staff){
		$staff_list[] = $staff->fname.' '.$staff->lname.' ('.$staff->nickname.')';
	}
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				$class_sub_table = 'essa_'.$session.'_subjects_'.mod_sub_string($form_state['values']['class']);
				$sub_name = db_query("SELECT * FROM {$class_sub_table} WHERE sub_id = :si;", array(':si' => $k));
				foreach($sub_name as $sn){
					$subject_name = $sn->sub_name;
				}
				
				if(!empty($v['c2'])){
					if($v['c2'] != NULL && !in_array($v['c2'],$staff_list)){
						drupal_set_message('Employee "'.$v['c2'].'" is not present in the system assigned for subject '.$subject_name.'.','error');
					}
				}
			}
		}
	}
	
}

/**
 *Implements callback function subject_list_ajax_submit().
 */
function subject_list_ajax_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	$sub_teacher_table = 'essa_'.$session_id.'_subject_teacher_table';
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	$emp = array();
	global $user;
	global $base_url;
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				$sub_teacher = db_query("SELECT * FROM {$sub_teacher_table} WHERE class =:c AND section = :sec AND subject = :sub;", array(':c' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'], ':sub' => $k));
				foreach($sub_teacher as $st){
					$emp[] = $st->teacher;
				}
				
				if(!empty($v['c2']) || $v['c2'] != NULL){
					preg_match('#\((.*?)\)#', $v['c2'], $match);
					$staff_db = db_query(
						"SELECT * from {$staff_table} where nickname = :nickname AND status = 1;",  array(':nickname' => $match[1])
					);
					foreach($staff_db as $staff){
						$emp_id = $staff->emp_id;
						$emp_uid = $staff->uid;
					}
				
					db_merge($sub_teacher_table)
					->key(array('class' => $form_state['values']['class'], 'section' => $form_state['values']['sec'], 'subject' => $k))
					->fields(array(
						'class' => $form_state['values']['class'],
						'section' => $form_state['values']['sec'],
						'subject' => $k,
						'teacher' => $emp_id,
					))
					->execute();
					
					$class_sub_table = 'essa_'.$session_id.'_subjects_'.mod_sub_string($form_state['values']['class']);
					$sub_name = db_query("SELECT * FROM {$class_sub_table} WHERE sub_id = :si;", array(':si' => $k));
					foreach($sub_name as $sn){
						$subject_name = $sn->sub_name;
					}
					
					$class = mod_sub_string($form_state['values']['class']).'-'.mod_sub_string($form_state['values']['sec']);
					
					if(!in_array($emp_id, $emp)){
						//sending message
						$module = 'school_master';
						$recipients= array();
						$recipients[] = user_load($emp_uid);
						$msg_subject = 'Appointment as Subject Teacher';
						$msg_body = 'You have been appointed as teacher of subject '.$subject_name.' for class '.$class.'.';
						$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
						$msg_body = $msg_body.' <br>'.$footer;
						privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
						
						$employee_email = db_query("SELECT * FROM {$staff_table} WHERE uid = :uid AND status = 1;", array(':uid' => $emp_uid));
						foreach($employee_email as $ee){
							$emp_email = $ee->email;
						}
						
						//Sending email to employee.
						if($emp_email != NULL){
	
							// Set hook_mail parameters.
							
							$email = $emp_email;
							
							$body = 'You have been appointed as teacher of subject '.$subject_name.' for class '.$class.'.';
							$footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
							//dsm($body);
							$params = array(
							  'subject' => 'Appointment as Subject Teacher',
							  'body' => $body."\n".$footer,
							);

							// Send out the e-mail.
							drupal_mail('school_master', 'Essa', $emp_email, language_default(), $params);
						}
						
						
						//sending system alert
						$created_date = date("Y-m-d H:i:s");
						$strtodate = strtotime($created_date);
						db_insert($sys_alert_table)
						->fields(array(
							'message' => $emp_id.' was alloted for subject '.$subject_name.' for  class '.$class.'.',
							'priority' => 'L',
							'module' => 'school_master',
							'source_url' => 'subject/teacher/allocation',
							'timestamp' => $strtodate,
							'source_uid' => $user->uid,
						))
						->execute();
						if($emp == NULL){
							//sending message to the time table incharge
							$r_id = db_query("SELECT * FROM {role} WHERE name = :name;", array(':name' => 'Time Table Incharge'));
							foreach($r_id as $rid){
								$u_id = db_query("SELECT * FROM {users_roles} WHERE rid = :rid;", array(':rid' => $rid->rid));
								foreach($u_id as $u){
									$module = 'school_master';
									$recipients= array();
									$recipients[] = user_load($u->uid);
									$msg_subject = 'Teacher have been alloted for class '.$class.'.';
									$msg_body = 'Teacher have been alloted for class '.$class.' , please update the time table accordingly. Click <a href = "'.$base_url.'/admin/time_table/create/'.mod_sub_string($form_state['values']['class']).'/'.mod_sub_string($form_state['values']['sec']).'">here</a> to change.';
									$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
									$msg_body = $msg_body.' <br>'.$footer;
									privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
									
									$timetable_incharge_email = db_query("SELECT * FROM {$staff_table} WHERE uid = :uid AND status = 1;", array(':uid' => $u->uid));
									foreach($timetable_incharge_email as $tte){
										$tti_email = $tte->email;
									}
									
									//Sending email to timetable_incharge.
									if($tti_email != NULL){
				
										// Set hook_mail parameters.
										
										$email = $tti_email;
										
										$body = 'Teacher have been alloted for class '.$class.' , please update the time table accordingly. Click <a href = "'.$base_url.'/admin/time_table/create/'.mod_sub_string($form_state['values']['class']).'/'.mod_sub_string($form_state['values']['sec']).'">here</a> to change.';
										$footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
										//dsm($body);
										$params = array(
										  'subject' => 'Teacher have been alloted for class '.$class.'.',
										  'body' => $body."\n".$footer,
										);

										// Send out the e-mail.
										drupal_mail('school_master', 'Essa', $tti_email, language_default(), $params);
									}
									
								}
							}
						}else{
							$r_id = db_query("SELECT * FROM {role} WHERE name = :name;", array(':name' => 'Time Table Incharge'));
							foreach($r_id as $rid){
								$u_id = db_query("SELECT * FROM {users_roles} WHERE rid = :rid;", array(':rid' => $rid->rid));
								foreach($u_id as $u){
									$module = 'school_master';
									$recipients= array();
									$recipients[] = user_load($u->uid);
									$msg_subject = 'Teacher list have been modified for class '.$class.'.';
									$msg_body = 'Teacher list have been modified for class '.$class.' , please update the time table accordingly. Click <a href = "'.$base_url.'/admin/time_table/create/'.mod_sub_string($form_state['values']['class']).'/'.mod_sub_string($form_state['values']['sec']).'">here</a> to change.';
									$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
									$msg_body = $msg_body.' <br>'.$footer;
									privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
									
									
									$timetable_incharge_email = db_query("SELECT * FROM {$staff_table} WHERE uid = :uid AND status = 1;", array(':uid' => $u->uid));
									foreach($timetable_incharge_email as $tte){
										$tti_email = $tte->email;
									}
									
									//Sending email to timetable_incharge.
									if($tti_email != NULL){
				
										// Set hook_mail parameters.
										
										$email = $tti_email;
										
										$body = 'Teacher list have been modified for class '.$class.' , please update the time table accordingly. Click <a href = "'.$base_url.'/admin/time_table/create/'.mod_sub_string($form_state['values']['class']).'/'.mod_sub_string($form_state['values']['sec']).'">here</a> to change.';
										$footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
										//dsm($body);
										$params = array(
										  'subject' => 'Teacher list have been modified for class '.$class.'.',
										  'body' => $body."\n".$footer,
										);

										// Send out the e-mail.
										drupal_mail('school_master', 'Essa', $tti_email, language_default(), $params);
									}
									
								}
							}
						}
					}
				}
			}
		}
	}
}

/**
 *Implements ajax callback.
 */
function display_sections_ajax($form, &$form_state){
	//dsm($form_state);
	return $form['sec_wrapper'];
}

/**
 *Implements ajax callback.
 */
function subject_list_ajax($form, &$form_state){
	//dsm($form_state);
	$form_state['rebuild'] = TRUE;
	return $form['subject_wrapper'];
}


/**
 *Theme function student_passout_table()
 */
function theme_subject_teacher_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	$header = array(t('Subject'),t('Teacher'));
	
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