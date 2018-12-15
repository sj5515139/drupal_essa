<?php

/**
 *Implements page call back.
 */
function staff_attendance($form, &$form_state){
	//******SURAJ******//
	$a_uid = array();
	$admin_rid = db_query("SELECT * FROM role WHERE name = 'Attendance Incharge' OR name = 'administrator';");
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
	
	if($flag != 1){
		$path = url('admin/staff/attendance/report', array('absolute' => TRUE));
		drupal_goto($path);
	}
	//******SURAJ******//
  $session = variable_get('essa_sid');
	$staff_table = 'essa_'.$session.'_master_staff_table';
	$session_id = (string)variable_get('essa_sid');
  $leave_type_table = 'essa_'.$session_id.'_leave_types';
	$leave_history_table = 'essa_'.$session_id.'_leave_staff_history';
  $staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	
	$date = strtotime(date('d-m-Y'));
	$leave_data = db_query(
		"SELECT * from {$leave_history_table} where status = 'Approved';"
	);
	
	foreach($leave_data as $ld){
		if($date >= $ld->from_date && $date <= $ld->to_date){
			$att[$ld->emp_id] = $ld->reason;
		}
	}
	
  $form['dt'] = array(
    '#type' => 'value',
    '#value' => date("Y/m/d"),
  );
	
	$form['ins'] = array(
    '#markup' => '<h4>NOTE: By default, all staffs are treated as present. Please mark the staffs who are absent, along with the reason(if available).</h4>'
  );
	
  $form['date'] = array(
    '#markup' => '<h1 id = "sta_att_title" style = "text-align: center;">Attendance - <b>'.'</b><b><i>'.'Staff'.' on <b><i>'.date("d").'<sup>'.date("S").'</sup> '.date("M Y").'('.date("D")."day".')'.'</i></b></h1>'
  );
	
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
  
  $staff_data = db_query(
		"SELECT * from {$staff_table} where status = 1;"
	);
  foreach($staff_data as $data){
		if(isset($att[$data->emp_id])){
			$row[] = array(
			  '#tree' =>TRUE,
			  $data -> emp_id => array(  //Generating unique array id for every form element
			    'c1' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.$data -> emp_id.'</h3>',
			    ),
			    'c2' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.$data -> fname.' '. $data -> lname.'</h3>',
			    ),
			    'c3' =>array(
			      '#type' => 'checkbox',
						'#default_value' => 1,
			    ),
			    'c4' =>array(
			      '#type' => 'textfield',
						'#default_value' => $att[$data->emp_id],
			    ),
			  ),
			);
		}else{
			$row[] = array(
			  '#tree' =>TRUE,
			  $data -> emp_id => array(  //Generating unique array id for every form element
			    'c1' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.$data -> emp_id.'</h3>',
			    ),
			    'c2' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.$data -> fname.' '. $data -> lname.'</h3>',
			    ),
			    'c3' =>array(
			      '#type' => 'checkbox',
			    ),
			    'c4' =>array(
			      '#type' => 'textfield',
			    ),
			  ),
			);
		}
  }
  
  if(!isset($row)){
    drupal_set_message('There are no Staff. Please ask school administrator to update student\'s records.', $type = 'error');
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
	
  $form['fs']['staff'] = array(
    '#theme' => 'staff_attendance_table',
    'rows' => $row,
  );
  
  $form['help'] = array(
    '#markup' => '<h6>"P" -- PRESENT, "A" -- ABSENT </h6>'
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
		dsm('The date in not in the range of academic year start and end date. Please contact system administrator in case you need assistance.');
	}else if( date('D',strtotime(date('Y-m-d'))) == 'Sun'){
		dsm('It\'s Sundays. Please contact system administrator in case you need assistance.');
	}else{
		return $form;
	}
}

/**
 *Implements validate function
 */
function staff_attendance_validate($form, &$form_state){
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
function staff_attendance_submit($form, &$form_state){
  //dsm($form_state);
	$flag = 0;
	$absent = 0;
	$date = date('Y_m_d');
  if($form_state['values']['holiday'] == 'Mark as Holiday'){
    $session = variable_get('essa_sid');
		$attendance_table = 'essa_'.$session.'_staff_attendance';
		$reason_table = 'essa_'.$session.'_staff_attendance_reason';
		$staff_table = 'essa_'.$session.'_'.'master_staff_table';
		foreach($form_state['values'] as $val){
		  if(is_array($val)){
		    foreach($val as $k => $v){
		      $student_db = db_query(
		      	"SELECT * from {$staff_table} where emp_id = :an", array(':an' => $k)
		      );
		      foreach($student_db as $student){
		        $att_data = db_query(
		        	"SELECT * from {$attendance_table} where emp_id = :emp_id", array(':emp_id' => $k)
		        );
		        foreach($att_data as $data){
		          $id = $data->id;
		        }
		        db_merge($attendance_table)
		          ->key(array('id' => isset($id) ? $id : NULL))
		          ->fields (array(
		              'emp_id' => $k,
		              date('Y_m_d') => 'h',//date('Y_m_d')
		            )
		          )
		          ->execute();
							$flag = 1;
		      }
		    }
		  }
		}
    $id = NULL;
		$reason_data = db_query(
		  "SELECT * from {$reason_table} where date = :date and emp_id = :emp_id", array(':emp_id' => $k, ':date' => date('Y_m_d'))
		);
	  foreach($reason_data as $rdata){
			$id = $rdata->id;
		}
		db_merge($reason_table)
		  ->key(array('id' => isset($id) ? $id : NULL))
		  ->fields (array(
		    'date' => date('Y_m_d'),
		    'emp_id' => NULL,
		    'attendance' => 'h',
	      'reason' => $form_state['values']['r'],
		  )
		)
		->execute();
		$flag = 1;
		$form_state['rebuild'] = TRUE;
	}else{
		$session = variable_get('essa_sid');
		$attendance_table = 'essa_'.$session.'_staff_attendance';
		$reason_table = 'essa_'.$session.'_staff_attendance_reason';
		$staff_table = 'essa_'.$session.'_'.'master_staff_table';
		foreach($form_state['values'] as $val){
		  if(is_array($val)){
		    foreach($val as $k => $v){
		      $student_db = db_query(
		      	"SELECT * from {$staff_table} where emp_id = :an", array(':an' => $k)
		      );
		      foreach($student_db as $student){
		        $att_data = db_query(
		        	"SELECT * from {$attendance_table} where emp_id = :emp_id", array(':emp_id' => $k)
		        );
		        foreach($att_data as $data){
		          $id = $data->id;
		        }
						
						if($v['c3'] != 1){
							db_merge($attendance_table)
		          ->key(array('emp_id' => $k))
		          ->fields (array(
		              'emp_id' => $k,
		              date('Y_m_d') => 'P',//date('Y_m_d')
		            )
		          )
		          ->execute();
							$flag = 1;
						}else{
							db_merge($attendance_table)
		          ->key(array('emp_id' => $k))
		          ->fields (array(
		              'emp_id' => $k,
		              date('Y_m_d') => 'A',//date('Y_m_d')
		            )
		          )
		          ->execute();
							$flag = 1;
							$absent = 1;
						}
		        if($v['c4'] != NULL){
		          $reason_data = db_query(
		          	"SELECT * from {$reason_table} where date = :date and emp_id = :emp_id", array(':emp_id' => $k, ':date' => date('Y_m_d'))//date('Y_m_d')
		          );
		          foreach($reason_data as $rdata){
		            $id = $rdata->id;
		          }
		          db_merge($reason_table)
		            ->key(array('id' => isset($id) ? $id : NULL))
		            ->fields (array(
		              'date' => date('Y_m_d'),
		              'emp_id' => $k,
		              'attendance' => 'A',
		              'reason' => $v['c4'],
		            )
		          )
		          ->execute();
							$flag = 1;
		        }
						//******Suraj*****//	
						if($absent == 1){
							$staff_table = 'essa_'.$session.'_master_staff_table';
							$st_data = db_query("SELECT * FROM {$staff_table} WHERE emp_id = :emp ;", array(':emp' => $k));
							foreach($st_data as $sd){
								$uid = $sd->uid;
							}
							//sending message
							$module = 'staff';
							$recipients= array();
							$recipients[] = user_load($uid);
							$msg_subject = 'Absent Notice';
							$msg_body = 'You were marked absent on '.$date.'. Please submit your leave application, <a href = "#"><u>here</u></a>.';
							$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
							$msg_body = $msg_body.' <br>'.$footer;
							privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
						}
		      }
		    }
		  }
		}
	}
	if($flag == 1){
		drupal_set_message('Attendence for '.$date.' was recorded successfully!!!');
		//removing notifications for attendance incharge
		$notification_table = 'essa_'.$session.'_notifications';
		global $user;
		$url = 'admin/staff/attendance';
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
		
	}//******Suraj*****//	
	
}

/**
 * Theme callback for the form table.
 */
function theme_staff_attendance_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('EmpID'), t('Name'),t('Attendance'), t('Reason'));
  
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
