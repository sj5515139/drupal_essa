<?php

function today_student_attendance($form, &$form_state){
	
  $session = variable_get('essa_sid');
	$staff_table = 'essa_'.$session.'_master_staff_table';
  global $user;
  
  $staff_db = db_query(
		"SELECT * from {$staff_table} where uid = :uid",  array(':uid' => $user->uid)
	);
	foreach($staff_db as $staff){
		$nickname = $staff->nickname;
	}
  
  $ct_table = 'essa_'.$session.'_class_teacher';
  $ct_db = db_query(
		"SELECT * from {$ct_table} where teacher_nickname = :nn", array(':nn' => $nickname)
	);
  
  foreach($ct_db as $ct){
		$class = $ct -> class.' '.$ct -> section;
  }
  
  $ct_table = 'essa_'.$session.'_class_teacher';
  $ct_db = db_query(
		"SELECT * from {$ct_table} where teacher_nickname = :nn", array(':nn' => $nickname)
	);
  
  foreach($ct_db as $ct){
		$class = $ct -> class.' '.$ct -> section;
    $class_id = $ct -> class.'_'.$ct -> section;
  }
  
  //dsm(date("d/m/Y"));
  //dsm(date("D")."day");
  $st_table = 'essa_'.$session.'_master_student_table';
  $st_data = db_query(
		"SELECT * from {$st_table} where class = :class and section = :sec and status = 1 order by roll_no;",array(':class' => $ct->class, ':sec' => $ct->section)
	);
  
  $form['cls'] = array(
    '#type' => 'value',
    '#value' => $class_id,
  );
  
  $form['dt'] = array(
    '#type' => 'value',
    '#value' => date("Y/m/d"),
  );
  
	$form['ins'] = array(
    '#markup' => '<h4>NOTE: By default, all students are treated as present. Please mark the students who are absent, along with the reason(if available).</h4>'
  );
	
  $form['date'] = array(
    '#markup' => '<h1 id = "stu_att_title" style = "text-align: center;">Attendance - <b>'.strtoupper($class).'</b> on <b><i>'.date("d").'<sup>'.date("S").'</sup> '.date("M Y").'('.date("D")."day".')'.'</i></b></h1>'
  );
	$attendance_table = 'essa_'.$session.'_'.$class_id.'_attendance';
	$form['holiday'] = array(
		'#type' => 'radios',
		'#options' => drupal_map_assoc(array('Mark as Holiday', 'Reset')),
		'#default_value' => '<p id = "na">NA</p>',
		'#validated' => TRUE,
	);
	
	$form['r'] = array(
		'#type' => 'textarea',
		'#title' => 'Reason',
		'#states' => array(
			'visible' => array(
			  ':input[name = "holiday"]' => array('value' => 'Mark as Holiday'),
			),
		),
	);
  $date = date('Y_m_d');
	
  foreach($st_data as $data){
		$default =  NULL;
		$reason = NULL;
		$attendance_table = 'essa_'.$session.'_'.$class_id.'_attendance';
		$default_value = db_query("SELECT * FROM {$attendance_table} WHERE adm_no = :adm;", array(':adm' => $data->adm_no));
		foreach($default_value as $dv){
			if($dv->$date == 'A'){
				$default = 1;
			}
		}
		$attendance_reason_table = 'essa_'.$session.'_attendance_reason';
		$default_reason = db_query("SELECT * FROM {$attendance_reason_table} WHERE date = :date AND adm_no = :adm;", array(':date' => $date, ':adm' => $data->adm_no));
		foreach($default_reason as $dr){
			$reason = $dr->reason;
		}
    $row[] = array(
      '#tree' =>TRUE,
      $data -> adm_no => array(  //Generating unique array id for every form element
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$data -> adm_no.'</h3>',
        ),
        'c2' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$data -> roll_no.'</h3>',
        ),
        'c3' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$data -> first_name.' '. $data -> last_name.'</h3>',
        ),
        'c4' =>array(
          '#type' => 'checkbox',
					'#default_value' => $default,
        ),
        'c5' =>array(
          '#type' => 'textfield',
					'#default_value' => $reason,
        ),
      ),
    );
  }
  
  if(!isset($row)){
    drupal_set_message('There are no Student in the class. Please ask school administrator to update student\'s records.', $type = 'error');
    $row = array();
  }
  //Calling the theme function to build the custom table and display the form in tabular format.
	$form['fs'] = array(
		'#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		'#states' => array(
			'invisible' => array(
			  ':input[name = "holiday"]' => array('value' => 'Mark as Holiday'),
			),
		),
	);
  $form['fs']['class'] = array(
    '#theme' => 'attendance_table',
    'rows' => $row,
  );
  
  $form['submit'] =array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
	
	$session = variable_get('essa_sid');
	$bi_table = 'essa_'.$session.'_basicinfo';
  
  $bi_db = db_query(
		"SELECT * from {$bi_table}"
	);
	foreach($bi_db as $bi){
		$start_date = $bi->academicyearstart;
		$end_date = $bi->academicyearend;
	}
	
	if(date('Y-m-d') < $start_date || date('Y-m-d') > $end_date){
		drupal_set_message('The date in not in the range of academic year start and end date. Please contact system administrator in case you need assistance.');
	}else if( date('D',strtotime(date('Y-m-d'))) == 'Sun'){
		drupal_set_message('It\'s Sunday. Please contact system administrator in case you need assistance.');
	}else{
		return $form;
	}
}

/**
 *Implements validate function
 */
function today_student_attendance_validate($form, &$form_state){
	$session = variable_get('essa_sid');
	$bi_table = 'essa_'.$session.'_basicinfo';
  
  $bi_db = db_query(
		"SELECT * from {$bi_table}"
	);
	foreach($bi_db as $bi){
		$start_date = $bi->academicyearstart;
		$end_date = $bi->academicyearend;
	}
	
	if(date('Y-m-d') < $start_date){
		form_set_error('The date in <b>not in the range</b> of academic year start and end date. Please contact system administrator in case you need assistance.');
	}
	if(date('Y-m-d') > $end_date){
		form_set_error('ask_date','The date in <b>not in the range</b> of academic year start and end date. Please contact system administrator in case you need assistance.');
	}
	
	if(date('D') == 'Sun'){
		form_set_error('ask_date','You have selected a SUNDAY.');
	}
}

/**
 *Implements submit function
 */
function today_student_attendance_submit($form, &$form_state){
	global $user;
	$flag = 0;
	if($form_state['values']['holiday'] == 'Mark as Holiday'){
		$session = variable_get('essa_sid');
		$attendance_table = 'essa_'.$session.'_'.$form_state['values']['cls'].'_attendance';
		$reason_table = 'essa_'.$session.'_attendance_reason';
		$st_table = 'essa_'.$session.'_master_student_table';
		
		$value = array();
		$value =  explode('_',$form_state['values']['cls']);
		$class = $value[0];
		$sec = $value[1];
		
		foreach($form_state['values'] as $val){
		  if(is_array($val)){
				foreach($val as $k => $v){
					$student_db = db_query(
						"SELECT * from {$st_table} where adm_no = :an and class = :class and section = :sec and status = 1;", array(':an' => $k, ':class' => $class, ':sec' => $sec)
					);
					foreach($student_db as $student){
						$att_data = db_query(
							"SELECT * from {$attendance_table} where adm_no = :adm_no", array(':adm_no' => $k)
						);
						foreach($att_data as $data){
							$id = $data->id;
						}
						db_merge($attendance_table)
							->key(array('id' => isset($id) ? $id : NULL))
							->fields (array(
								'adm_no' => $k,
								'roll_no' => $student->roll_no,
								date('Y_m_d') => 'h',
							))
						->execute();
						$flag = 1;
					}
				}
			}
		}
		$reason_data = db_query(
		  "SELECT * from {$reason_table} where date = :date and adm_no = :adm_no", array(':adm_no' => $k, ':date' => date('Y_m_d'))
		);
		foreach($reason_data as $rdata){
			$id = $rdata->id;
		}
		db_merge($reason_table)
		  ->key(array('id' => isset($id) ? $id : NULL))
		  ->fields (array(
		    'date' => date('Y_m_d'),
		    'adm_no' => NULL,
		    'roll_no' => NULL,
	      'attendance' => 'h',
	      'reason' => $form_state['values']['r'],
		  )
		)
		->execute();
		$flag = 1;
		$form_state['rebuild'] = TRUE;
	}else{
		$session = variable_get('essa_sid');
		$attendance_table = 'essa_'.$session.'_'.$form_state['values']['cls'].'_attendance';
		$reason_table = 'essa_'.$session.'_attendance_reason';
		$st_table = 'essa_'.$session.'_master_student_table';
		
		$value = array();
		$value =  explode('_',$form_state['values']['cls']);
		$class = $value[0];
		$sec = $value[1];
		$absent = 0;
		$present = 1;
		$req_date = date('Y_m_d');
		foreach($form_state['values'] as $val){
			if(is_array($val)){
				foreach($val as $k => $v){
					$student_db = db_query(
						"SELECT * from {$st_table} where adm_no = :an and class = :class and section = :sec and status = 1;", array(':an' => $k, ':class' => $class, ':sec' => $sec)
					);
					foreach($student_db as $student){
						$att_data = db_query(
							"SELECT * from {$attendance_table} where adm_no = :adm_no", array(':adm_no' => $k)
						);
						foreach($att_data as $data){
							$id = $data->id;
						}
						if($v['c4'] != '1'){
							db_merge($attendance_table)
							->key(array('adm_no' => $k))
							->fields (array(
								'adm_no' => $k,
								'roll_no' => $student->roll_no,
								$req_date => 'P',//date('Y_m_d')
							))
							->execute();
							$flag = 1;
						}else{
							db_merge($attendance_table)
							->key(array('adm_no' => $k))
							->fields (array(
								'adm_no' => $k,
								'roll_no' => $student->roll_no,
								$req_date => 'A',//date('Y_m_d')
							))
							->execute();
							$absent = 1;
							$flag = 1;
						}
						if($v['c5'] != NULL){
							$reason_data = db_query(
								"SELECT * from {$reason_table} where date = :date and adm_no = :adm_no", array(':adm_no' => $k, ':date' => date('Y_m_d'))//date('Y_m_d')
							);
							foreach($reason_data as $rdata){
								$id = $rdata->id;
							}
							db_merge($reason_table)
							->key(array('id' => isset($id) ? $id : NULL))
							->fields (array(
								'date' => date('Y_m_d'),
								'adm_no' => $k,
								'roll_no' => $student->roll_no,
								'attendance' => $v['c4'],
								'reason' => $v['c5'],
							))
							->execute();
							$flag = 1;
						}
						
						//***********SURAJ************
						if($absent == 1){
							$date = date('Y_m_d');
							$parents = db_query("SELECT * FROM {$st_table} WHERE adm_no = :adm AND status = 1;", array(':adm' => $k));
							foreach($parents as $parent){
								$parent_uid = $parent->puid;
								$parent_email = $parent->p_email;
							}
							
							// if($parent_uid != NULL){
								// //sending message
								// $module = 'student_attendance';
								// $recipients= array();
								// $recipients[] = user_load($parent_uid);
								// $msg_subject = 'Absent Notice.';
								// $msg_body = 'Your ward were marked absent on '.$date.'.';
								// $footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
								// $msg_body = $msg_body.' <br>'.$footer;
								// privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
							// }
							
							// if($parent_email != NULL){
								// // Set hook_mail parameters.
							
								// $email = $parent_email;
								
								// $body = 'Your ward were marked absent on '.$date.'.';
								// $footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
								// //dsm($body);
								// $params = array(
								  // 'subject' => 'Absent Notice.',
								  // 'body' => $body."\n".$footer,
								// );

								// // Send out the e-mail.
								// drupal_mail('school_master', 'Essa', $parent_email, language_default(), $params);
							// }
						}
						
					}
				}
			}
		}
	}
	
	if($flag == 1){
		drupal_set_message('Attendance for '.$req_date.' was recorded successfully.');
		//removing notification for class teacher
		$notification_table = 'essa_'.$session.'_notifications';
		global $user;
		$url = 'admin/students/attendance/today-attendance';
		$notifications = db_query("SELECT * FROM {$notification_table} WHERE uid =:uid AND destination_url =:url;",array(':uid' => $user->uid, ':url' => $url));
		foreach($notifications as $notification){
			//dsm('ok');
			db_update($notification_table)
			->fields(array(
				'status' => '1',
			))
			->condition(db_and()
			->condition('uid', $user->uid)
			->condition('destination_url', $url))
			->execute();
		}
	}
	
}

/**
 * Theme callback for the form table.
 */
function theme_attendance_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Admission No'),t('Roll No'), t('Name'),t('Attendance'), t('Reason'));
  
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


