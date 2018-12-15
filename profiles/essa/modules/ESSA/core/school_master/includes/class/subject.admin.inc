<?php

/**
 *Implements callback function for subjects
 */
function subject_list_form($form, &$form_state){
	$session = variable_get('essa_sid');
	$class_list_table = 'essa_'.$session.'_class_list';
	$class_list = array();
  
	$class_list_db = db_query(
		"SELECT class_id from {$class_list_table} order by weight"
	);
	
  foreach($class_list_db as $class){
		$sub_l[ 'subjects/'.$class->class_id] = $class->class_id;
	}
	$options = array(
		'title' => 'Select a class - ',
	);
	ctools_include('jump-menu');
	$form['jump'] = ctools_jump_menu(array(), $form_state, $sub_l, $options);
	
	$form['sub'] = array(
		'#type' => 'markup',
		'#markup' => 'Select a Class to add subjects',
	);
	
	return $form;
}

/**
 *Implements callback function for each class to enter sunjects
 */
function subject_form($form, &$form_state, $class_sub){
	
	$session = variable_get('essa_sid');
	$class_list_table = 'essa_'.$session.'_class_list';
	$class_list = array();
  
	$class_sub_table = 'essa_'.$session.'_subjects_'.mod_sub_string($class_sub);
	
	$count = 0;
	$pre_saved_values = db_query(
		"SELECT * from {$class_sub_table}"
	);
	foreach($pre_saved_values as $val){
		$count++;
		$value[] = $val;
	}
	
	$form['class'] = array(
		'#type' => 'value',
		'#value' => $class_sub
	);
	
	$form['help'] = array(
		'#type' => 'markup',
		'#markup' => '<br><h3>'.'You are creating subjects for Class - '.'<b>'.$class_sub.'</b></h3>',
	);
	
	//----------------------------------------------sets the value for the loop - to generate the number of rows.-------------------------------------------
	if($count < 10){
		$limit = 10;
	}else{
		$limit = $count+1;
	}
	
	for($i = 0; $i < $limit; $i++){
		//-------------------------------------------------sets default vaues as empty string for all rows if DB entry is NULL----------------------------------
		if(!isset($value[$i])){
			$value[$i] = new StdClass;
			$value[$i]->sub_id = "";
			$value[$i]->sub_name = "";
			$value[$i]->type = "";
			$value[$i]->teacher1 = "";
			$value[$i]->teacher2 = "";
			$value[$i]->teacher3 = "";
			$value[$i]->teacher4 = "";
			$value[$i]->teacher5 = "";
		}
      $row[] = array(
      '#tree' =>TRUE,
			
      $i => array(  //Generating unique array id for every form element
				'c1' =>array(
          '#type' => 'textfield',
					'#size' => 8,
					'#default_value' => $value[$i]->sub_id,
        ),
        'c2' =>array(
          '#type' => 'textfield',
					'#size' => 18,
					'#default_value' => $value[$i]->sub_name,
        ),
        'c3' =>array(
          '#type' => 'select',
          '#options' => drupal_map_assoc(array(t('Compulsory'), t('Optional'))),
					'#default_value' => $value[$i]->type,
        ),
//				'c4' =>array(
//          '#type' => 'textfield',
//					'#autocomplete_path' => 'teachers/autocomplete',
//					'#size' => 10,
//					'#default_value' => $value[$i]->teacher1,
//				),
//				'c5' =>array(
//          '#type' => 'textfield',
//					'#autocomplete_path' => 'teachers/autocomplete',
//					'#size' => 10,
//					'#default_value' => $value[$i]->teacher2,
//				),
//				'c6' =>array(
//          '#type' => 'textfield',
//					'#autocomplete_path' => 'teachers/autocomplete',
//					'#size' => 10,
//					'#default_value' => $value[$i]->teacher3,
//				),
//				'c7' =>array(
//          '#type' => 'textfield',
//					'#autocomplete_path' => 'teachers/autocomplete',
//					'#size' => 10,
//					'#default_value' => $value[$i]->teacher4,
//				),
//				'c8' =>array(
//          '#type' => 'textfield',
//					'#autocomplete_path' => 'teachers/autocomplete',
//					'#size' => 10,
//					'#default_value' => $value[$i]->teacher5,
//				),
      ),
    );
  }
  
	//-----------------------Calling the theme function to build the custom table and display the form in tabular format.-----------------------------
  $form['sub'][$class_sub] = array(
    '#theme' => 'class_sub_table',
    'rows' => $row,
  );
  $form['container'] = array(
    '#type' => 'container',
    '#prefix' => '<div id = "create_subject">',
    '#suffix' => '</div>',
  );
	
	$form['save_manage'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
		'#submit' => array('save_manage'),
	);
//	
//	$form['add_more'] = array(
//    '#type' => 'submit',
//    '#value' => t('Add more'),
//    '#submit' => array('add_more'),
//  );
//	
//	$form['reset'] = array(
//    '#type' => 'submit',
//    '#value' => t('Reset'),
//    '#submit' => array('reset_form'),
//  );
	
	return $form;
}

/**
 *Submit function - adds more rows to the form.
 */
function add_more($form, &$form_state){
  $form_state['rebuild']  = TRUE;
  $l = variable_get('set_sub_i');
  $l++;
  variable_set('set_sub_i', $l);
}

/**
 *Submit function - resets the form.
 */
function reset_form($form, $form_state){
	variable_get('set_sub_i');
  variable_set('set_sub_i',10);
	
	//*******Suraj********//
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	global $base_url;
	//sending system alert
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
	'message' => 'Subject for  class '.mod_sub_string($form_state['values']['class']).' were reset.',
	'priority' => 'L',
	'module' => 'school_master',
	'source_url' => 'admin/settings/subjects/'.mod_sub_string($form_state['values']['class']),
	'timestamp' => $strtodate,
	'source_uid' => $user->uid,
	))
	->execute();
	//*******Suraj********//
	
}

/**
 *Implements the submit function to save the entries and continue to add subjects
 */
function save_manage($form, &$form_state){
	//*******Suraj********//
	global $user;
	global $base_url;
	$error = variable_get('subject_form_error'.$user->uid);
	
	//*******Suraj********//
	
	if(variable_get('subject_form_error'.$user->uid) != 'error'){
		$session = variable_get('essa_sid');
		$class_list_table = 'essa_'.$session.'_class_list';
		$staff_table = 'essa_'.$session.'_master_staff_table';
		$sys_alert_table = 'essa_'.$session.'_system_alert';
		$notification_table = 'essa_'.$session.'_notifications';
		
		global $base_url;
		
		$t1_emp_id = NULL;
		$t2_emp_id = NULL;
		$t3_emp_id = NULL;
		$t4_emp_id = NULL;
		$t5_emp_id = NULL;
		$sub_ids = array();
		$class_list = array();
		
		$class_sub_table = 'essa_'.$session.'_subjects_'.mod_sub_string($form_state['values']['class']);
		
		$class_subject = db_query(
			"SELECT * from {$class_sub_table}"
		);
		
		foreach($class_subject as $sub){
			$subj[$sub->sub_id] = $sub->id;
			$emp[] = $sub ->teacher1;
			$emp[] = $sub ->teacher2;
			$emp[] = $sub ->teacher3;
			$emp[] = $sub ->teacher4;
			$emp[] = $sub ->teacher5;
		}
		//dsm($form_state);
		foreach($form_state['values'] as $row){
			if(is_array($row)){
				foreach($row as $data){
					if(!empty($data['c1'])){
						$sub_id = $data['c1'];
						
						db_merge($class_sub_table)
							->key(array('id' => isset($subj[$data['c1']])? $subj[$data['c1']]: NULL))
							->fields (array(
								'sub_id' => $sub_id,
								'sub_name' => $data['c2'],
								'type' => $data['c3'],
								)
							)
							->execute();
							$sub_ids[$sub_id] = $sub_id;
					}
				}
			}
		}
		
		$existing_sub = array();
		$pre_saved_values = db_query(
			"SELECT * from {$class_sub_table}"
		);
		foreach($pre_saved_values as $val){
			$existing_sub[$val->sub_id] = $val->sub_id;
		}
		$to_del = array_diff($existing_sub, $sub_ids);
		
		foreach($to_del as $del){
			db_delete($class_sub_table)
				->condition('sub_id', $del)
				->execute();
		}
		
		menu_rebuild();
		variable_set('subject_form_error'.$user->uid, 'NULL');
		drupal_set_message('Subjects has been created successfully for class '.mod_sub_string($form_state['values']['class']).'.','status');
		
		//sending system alert
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
			'message' => 'Subjects for class'.mod_sub_string($form_state['values']['class']).' was created.',
			'priority' => 'L',
			'module' => 'school_master',
			'source_url' => 'admin/settings/classes/'.mod_sub_string($form_state['values']['class']),
			'timestamp' => $strtodate,
			'source_uid' => $user->uid,
		))
		->execute();
	}
}

/**Line 251
 //*******Suraj********
						
						//$t1_emp_id = $t2_emp_id = $t3_emp_id = $t4_emp_id = $t5_emp_id = NULL;
						//if(!empty($data['c4'])){
						//	//dsm($data['c4']);
						//	preg_match('#\((.*?)\)#', $data['c4'], $match);
						//	$staff_db = db_query(
						//		"SELECT * from {$staff_table} where nickname = :nickname",  array(':nickname' => $match[1])
						//	);
						//	foreach($staff_db as $staff){
						//		$t1_emp_id = $staff->emp_id;
						//		$t1_uid = $staff->uid;
						//		if(!in_array($data['c4'],$emp)){
						//			//sending message
						//			$module = 'school_master';
						//			$recipients= array();
						//			$recipients[] = user_load($t1_uid);
						//			$msg_subject = 'Appointment as Subject Teacher';
						//			$msg_body = 'You have been appointed as teacher of subject '.$data['c2'].' for class '.mod_sub_string($form_state['values']['class']).'.';
						//			$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
						//			$msg_body = $msg_body.' <br>'.$footer;
						//			privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
						//			//dsm($emp);
						//			//sending system alert
						//			$created_date = date("Y-m-d H:i:s");
						//			$strtodate = strtotime($created_date);
						//			db_insert($sys_alert_table)
						//			->fields(array(
						//				'message' => $t1_emp_id.' was alloted for subject '.$data['c2'].' for  class'.mod_sub_string($form_state['values']['class']).'.',
						//				'priority' => 'L',
						//				'module' => 'school_master',
						//				'source_url' => 'admin/settings/classes/'.mod_sub_string($form_state['values']['class']),
						//				'timestamp' => $strtodate,
						//				'source_uid' => $user->uid,
						//			))
						//			->execute();
						//			
						//			//sending message to the time table incharge
						//			$r_id = db_query("SELECT * FROM {role} WHERE name = :name;", array(':name' => 'Time Table Incharge'));
						//			foreach($r_id as $rid){
						//				$u_id = db_query("SELECT * FROM {users_roles} WHERE rid = :rid;", array(':rid' => $rid->rid));
						//				foreach($u_id as $u){
						//					$module = 'school_master';
						//					$recipients= array();
						//					$recipients[] = user_load($u->uid);
						//					$msg_subject = 'Teacher list have been modified for class '.mod_sub_string($form_state['values']['class']).'.';
						//					$msg_body = 'Teacher list have been modified for class '.mod_sub_string($form_state['values']['class']).' , please update the time table accordingly. Click <a href = "'.$base_url.'/admin/time_table/'.mod_sub_string($form_state['values']['class']).'">here</a> to change.';
						//					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
						//					$msg_body = $msg_body.' <br>'.$footer;
						//					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
						//				}
						//			}
						//		}
						//	}	
						//}       
						//
						//if(!empty($data['c5'])){
						//	preg_match('#\((.*?)\)#', $data['c5'], $match);
						//	$staff_db = db_query(
						//		"SELECT * from {$staff_table} where nickname = :nickname",  array(':nickname' => $match[1])
						//	);
						//	foreach($staff_db as $staff){
						//		$t2_emp_id = $staff->emp_id;
						//		$t2_uid = $staff->uid;
						//		if(!in_array($data['c5'],$emp)){
						//			//sending message
						//			$module = 'school_master';
						//			$recipients= array();
						//			$recipients[] = user_load($t2_uid);
						//			$msg_subject = 'Appointment as Subject Teacher';
						//			$msg_body = 'You have been appointed as teacher of subject '.$data['c2'].' for class '.mod_sub_string($form_state['values']['class']).'.';
						//			$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
						//			$msg_body = $msg_body.' <br>'.$footer;
						//			privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
						//			
						//			//sending system alert
						//			$created_date = date("Y-m-d H:i:s");
						//			$strtodate = strtotime($created_date);
						//			db_insert($sys_alert_table)
						//			->fields(array(
						//				'message' => $t2_emp_id.' was alloted for subject '.$data['c2'].' for class '.mod_sub_string($form_state['values']['class']).'.',
						//				'priority' => 'L',
						//				'module' => 'school_master',
						//				'source_url' => 'admin/settings/classes/'.mod_sub_string($form_state['values']['class']),
						//				'timestamp' => $strtodate,
						//				'source_uid' => $user->uid,
						//			))
						//			->execute();
						//			
						//			//sending message to the time table incharge
						//			$r_id = db_query("SELECT * FROM {role} WHERE name = :name;", array(':name' => 'Time Table Incharge'));
						//			foreach($r_id as $rid){
						//				$u_id = db_query("SELECT * FROM {users_roles} WHERE rid = :rid;", array(':rid' => $rid->rid));
						//				foreach($u_id as $u){
						//					$module = 'school_master';
						//					$recipients= array();
						//					$recipients[] = user_load($u->uid);
						//					$msg_subject = 'Teacher list have been modified for class '.mod_sub_string($form_state['values']['class']).'.';
						//					$msg_body = 'Teacher list have been modified for class '.mod_sub_string($form_state['values']['class']).' , please update the time table accordingly. Click <a href ="'.$base_url.'/admin/time_table/'.mod_sub_string($form_state['values']['class']).'">here</a> to change.';
						//					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
						//					$msg_body = $msg_body.' <br>'.$footer;
						//					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
						//				}
						//			}
						//		}
						//	}
						//}
						//
						//if(!empty($data['c6'])){
						//	preg_match('#\((.*?)\)#', $data['c6'], $match);
						//	$staff_db = db_query(
						//		"SELECT * from {$staff_table} where nickname = :nickname",  array(':nickname' => $match[1])
						//	);
						//	foreach($staff_db as $staff){
						//		$t3_emp_id = $staff->emp_id;
						//		$t3_uid = $staff->uid;
						//		if(!in_array($data['c6'],$emp)){
						//			//sending message
						//			$module = 'school_master';
						//			$recipients= array();
						//			$recipients[] = user_load($t3_uid);
						//			$msg_subject = 'Appointment as Subject Teacher';
						//			$msg_body = 'You have been appointed as teacher of subject '.$data['c2'].' for class '.mod_sub_string($form_state['values']['class']).'.';
						//			$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
						//			$msg_body = $msg_body.' <br>'.$footer;
						//			privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
						//			
						//			//sending system alert
						//			$created_date = date("Y-m-d H:i:s");
						//			$strtodate = strtotime($created_date);
						//			db_insert($sys_alert_table)
						//			->fields(array(
						//				'message' => $t3_emp_id.' was alloted for subject '.$data['c2'].' for class '.mod_sub_string($form_state['values']['class']).'.',
						//				'priority' => 'L',
						//				'module' => 'school_master',
						//				'source_url' => 'admin/settings/classes/'.mod_sub_string($form_state['values']['class']),
						//				'timestamp' => $strtodate,
						//				'source_uid' => $user->uid,
						//			))
						//			->execute();
						//			
						//			//sending message to the time table incharge
						//			$r_id = db_query("SELECT * FROM {role} WHERE name = :name;", array(':name' => 'Time Table Incharge'));
						//			foreach($r_id as $rid){
						//				$u_id = db_query("SELECT * FROM {users_roles} WHERE rid = :rid;", array(':rid' => $rid->rid));
						//				foreach($u_id as $u){
						//					$module = 'school_master';
						//					$recipients= array();
						//					$recipients[] = user_load($u->uid);
						//					$msg_subject = 'Teacher list have been modified for class '.mod_sub_string($form_state['values']['class']).'.';
						//					$msg_body = 'Teacher list have been modified for class '.mod_sub_string($form_state['values']['class']).' , please update the time table accordingly. Click <a href ="'.$base_url.'/admin/time_table/'.mod_sub_string($form_state['values']['class']).'">here</a> to change.';
						//					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
						//					$msg_body = $msg_body.' <br>'.$footer;
						//					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
						//				}
						//			}
						//		}
						//	}
						//}
						//
						//if(!empty($data['c7'])){
						//	preg_match('#\((.*?)\)#', $data['c7'], $match);
						//	$staff_db = db_query(
						//		"SELECT * from {$staff_table} where nickname = :nickname",  array(':nickname' => $match[1])
						//	);
						//	foreach($staff_db as $staff){
						//		$t4_emp_id = $staff->emp_id;
						//		$t4_uid = $staff->uid;
						//		if(!in_array($data['c7'],$emp)){
						//			//sending message
						//			$module = 'school_master';
						//			$recipients= array();
						//			$recipients[] = user_load($t4_uid);
						//			$msg_subject = 'Appointment as Subject Teacher';
						//			$msg_body = 'You have been appointed as teacher of subject '.$data['c2'].' for class '.mod_sub_string($form_state['values']['class']).'.';
						//			$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
						//			$msg_body = $msg_body.' <br>'.$footer;
						//			privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
						//			
						//			//sending system alert
						//			$created_date = date("Y-m-d H:i:s");
						//			$strtodate = strtotime($created_date);
						//			db_insert($sys_alert_table)
						//			->fields(array(
						//				'message' => $t4_emp_id.' was alloted for subject '.$data['c2'].' for class '.mod_sub_string($form_state['values']['class']).'.',
						//				'priority' => 'L',
						//				'module' => 'school_master',
						//				'source_url' => 'admin/settings/classes/'.mod_sub_string($form_state['values']['class']),
						//				'timestamp' => $strtodate,
						//				'source_uid' => $user->uid,
						//			))
						//			->execute();
						//			
						//			//sending message to the time table incharge
						//			$r_id = db_query("SELECT * FROM {role} WHERE name = :name;", array(':name' => 'Time Table Incharge'));
						//			foreach($r_id as $rid){
						//				$u_id = db_query("SELECT * FROM {users_roles} WHERE rid = :rid;", array(':rid' => $rid->rid));
						//				foreach($u_id as $u){
						//					$module = 'school_master';
						//					$recipients= array();
						//					$recipients[] = user_load($u->uid);
						//					$msg_subject = 'Teacher list have been modified for class '.mod_sub_string($form_state['values']['class']).'.';
						//					$msg_body = 'Teacher list have been modified for class '.mod_sub_string($form_state['values']['class']).' , please update the time table accordingly. Click <a href ="'.$base_url.'/admin/time_table/'.mod_sub_string($form_state['values']['class']).'">here</a> to change.';
						//					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
						//					$msg_body = $msg_body.' <br>'.$footer;
						//					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
						//				}
						//			}
						//		}
						//	}
						//}
						//
						//if(!empty($data['c8'])){
						//	preg_match('#\((.*?)\)#', $data['c8'], $match);
						//	$staff_db = db_query(
						//		"SELECT * from {$staff_table} where nickname = :nickname",  array(':nickname' => $match[1])
						//	);
						//	foreach($staff_db as $staff){
						//		$t5_emp_id = $staff->emp_id;
						//		$t5_uid = $staff->uid;
						//		if(!in_array($data['c8'],$emp)){
						//			//sending message
						//			$module = 'school_master';
						//			$recipients= array();
						//			$recipients[] = user_load($t5_uid);
						//			$msg_subject = 'Appointment as Subject Teacher';
						//			$msg_body = 'You have been appointed as teacher of subject '.$data['c2'].' for class '.mod_sub_string($form_state['values']['class'].'.');
						//			$footer = '<p> This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
						//			$msg_body = $msg_body.' <br>'.$footer;
						//			privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
						//			
						//			//sending system alert
						//			$created_date = date("Y-m-d H:i:s");
						//			$strtodate = strtotime($created_date);
						//			db_insert($sys_alert_table)
						//			->fields(array(
						//				'message' => $t5_emp_id.' was alloted for subject '.$data['c2'].' for class '.mod_sub_string($form_state['values']['class']).'.',
						//				'priority' => 'L',
						//				'module' => 'school_master',
						//				'source_url' => 'admin/settings/classes/'.mod_sub_string($form_state['values']['class']),
						//				'timestamp' => $strtodate,
						//				'source_uid' => $user->uid,
						//			))
						//			->execute();
						//			
						//			//sending message to the time table incharge
						//			$r_id = db_query("SELECT * FROM {role} WHERE name = :name;", array(':name' => 'Time Table Incharge'));
						//			foreach($r_id as $rid){
						//				$u_id = db_query("SELECT * FROM {users_roles} WHERE rid = :rid;", array(':rid' => $rid->rid));
						//				foreach($u_id as $u){
						//					$module = 'school_master';
						//					$recipients= array();
						//					$recipients[] = user_load($u->uid);
						//					$msg_subject = 'Teacher list have been modified for class '.mod_sub_string($form_state['values']['class']).'.';
						//					$msg_body = 'Teacher list have been modified for class '.mod_sub_string($form_state['values']['class']).' , please update the time table accordingly. Click <a href ="'.$base_url.'/admin/time_table/'.mod_sub_string($form_state['values']['class']).'">here</a> to change.';
						//					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
						//					$msg_body = $msg_body.' <br>'.$footer;
						//					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
						//				}
						//			}
						//		}
						//	}
						//}//dsm($data['c4']);
						////*******Suraj********
						//
						
 */
 

	//*******Suraj********//
/**
 *Implements validate function for subjects
 */
function subject_form_validate($form, &$form_state){
	global $user;
	$sub_list = array();
	variable_set('subject_form_error'.$user->uid, 'NULL');
	
	foreach($form_state['values'] as $row){
		if(is_array($row)){
		  foreach($row as $data){
				if(!empty($data['c1'])){
					$sub_list[]  = $data['c1'];
				}
				if(!empty($data['c2']) && empty($data['c1'])){
					drupal_set_message('Please eneter Subject Id for '.$data['c2'], 'error');
					variable_set('subject_form_error'.$user->uid, 'error');
				}
			}
		}
	}
	//dsm($sub_list);
	$a = array_count_values($sub_list);
	//dsm($a);
	foreach($a as $k => $v){
		if($v > 1){
			drupal_set_message('Subject Id should be unique, <b>'.$k.'</b> is repeated '.$v.' times.','error');
			variable_set('subject_form_error'.$user->uid, 'error');
		}
	}
	
	
	/* foreach($form_state['values'] as $row){
		if(is_array($row)){
		  foreach($row as $data){
				if(!empty($data['c1'])){
					if(in_array($data['c1'],$sub_list)){
						drupal_set_message('Subject Id for subject '.$data['c2'].' should be unique.','error');
					}
				}
			}
		}
	} */
/*	
	$session = variable_get('essa_sid');
	$class_list_table = 'essa_'.$session.'_class_list';
	$staff_table = 'essa_'.$session.'_master_staff_table';
	global $user;
	
	$staffs = db_query("SELECT * FROM {$staff_table}");
	foreach($staffs as $staff){
		$staff_list[] = $staff->fname.' '.$staff->lname.' ('.$staff->nickname.')';
	}
	variable_set('subject_form_error'.$user->uid, 'NULL');
	foreach($form_state['values'] as $row){
    if(is_array($row)){
      foreach($row as $data){
        if(!empty($data['c1'])){
					//dsm($data['c1']);
					//validating that atleast one employee must be alloted to each subject
					//if(empty($data['c4']) && empty($data['c5']) && empty($data['c6']) && empty($data['c7']) && empty($data['c8'])){
					//	drupal_set_message('No Teacher has been alloted to the subject id '.$data['c1'].'.','error');
					//	variable_set('subject_form_error'.$user->uid, 'error');
					//}
					/*
					//validating that an employee present in the system or not
					if($data['c4'] != NULL && !in_array($data['c4'],$staff_list)){
						drupal_set_message('Employee "'.$data['c4'].'" is not present in the system assigned for subject id '.$data['c1'].'  as Teacher 1.','error');
						variable_set('subject_form_error'.$user->uid, 'error');
					}
					if($data['c5'] != NULL && !in_array($data['c5'],$staff_list)){
						drupal_set_message('Employee "'.$data['c5'].'" is not present in the system assigned for subject id '.$data['c1'].'  as Teacher 2.','error');
						variable_set('subject_form_error'.$user->uid, 'error');
					}
					if($data['c6'] != NULL && !in_array($data['c6'],$staff_list)){
						drupal_set_message('Employee "'.$data['c6'].'" is not present in the system assigned for subject id '.$data['c1'].'  as Teacher 3.','error');
						variable_set('subject_form_error'.$user->uid, 'error');
					}
					if($data['c7'] != NULL && !in_array($data['c7'],$staff_list)){
						drupal_set_message('Employee "'.$data['c7'].'" is not present in the system assigned for subject id '.$data['c1'].'  as Teacher 4.','error');
						variable_set('subject_form_error'.$user->uid, 'error');
					}
					if($data['c8'] != NULL && !in_array($data['c8'],$staff_list)){
						drupal_set_message('Employee "'.$data['c8'].'" is not present in the system assigned for subject id '.$data['c1'].'  as Teacher 5.','error');
						variable_set('subject_form_error'.$user->uid, 'error');
					}
					
					
					
					//validating that each subject has 5 different teacher.
					if(!empty($data['c4']) && !empty($data['c5'])){
						if($data['c4'] == $data['c5']){
							drupal_set_message('Same teacher can not be assigned as Teacher 1 and Teacher 2 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c4']) && !empty($data['c6'])){
						if($data['c4'] == $data['c6']){
							drupal_set_message('Same teacher can not be assigned as Teacher 1 and Teacher 3 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c4']) && !empty($data['c7'])){
						if($data['c4'] == $data['c7']){
							drupal_set_message('Same teacher can not be assigned as Teacher 1 and Teacher 4 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c4']) && !empty($data['c8'])){
						if($data['c4'] == $data['c8']){
							drupal_set_message('Same teacher can not be assigned as Teacher 1 and Teacher 5 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c5']) && !empty($data['c4'])){
						if($data['c5'] == $data['c4']){
							drupal_set_message('Same teacher can not be assigned as Teacher 2 and Teacher 1 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c5']) && !empty($data['c6'])){
						if($data['c5'] == $data['c6']){
							drupal_set_message('Same teacher can not be assigned as Teacher 2 and Teacher 3 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c5']) && !empty($data['c7'])){
						if($data['c5'] == $data['c7']){
							drupal_set_message('Same teacher can not be assigned as Teacher 2 and Teacher 4 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c5']) && !empty($data['c8'])){
						if($data['c5'] == $data['c8']){
							drupal_set_message('Same teacher can not be assigned as Teacher 2 and Teacher 5 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c6']) && !empty($data['c4'])){
						if($data['c6'] == $data['c4']){
							drupal_set_message('Same teacher can not be assigned as Teacher 3 and Teacher 1 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c6']) && !empty($data['c5'])){
						if($data['c6'] == $data['c5']){
							drupal_set_message('Same teacher can not be assigned as Teacher 3 and Teacher 2 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c6']) && !empty($data['c7'])){
						if($data['c6'] == $data['c7']){
							drupal_set_message('Same teacher can not be assigned as Teacher 3 and Teacher 4 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c6']) && !empty($data['c8'])){
						if($data['c6'] == $data['c8']){
							drupal_set_message('Same teacher can not be assigned as Teacher 3 and Teacher 8 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c7']) && !empty($data['c4'])){
						if($data['c7'] == $data['c4']){
							drupal_set_message('Same teacher can not be assigned as Teacher 4 and Teacher 1 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c7']) && !empty($data['c5'])){
						if($data['c7'] == $data['c5']){
							drupal_set_message('Same teacher can not be assigned as Teacher 4 and Teacher 2 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c7']) && !empty($data['c6'])){
						if($data['c7'] == $data['c6']){
							drupal_set_message('Same teacher can not be assigned as Teacher 4 and Teacher 3 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c7']) && !empty($data['c8'])){
						if($data['c7'] == $data['c8']){
							drupal_set_message('Same teacher can not be assigned as Teacher 4 and Teacher 5 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c8']) && !empty($data['c4'])){
						if($data['c8'] == $data['c4']){
							drupal_set_message('Same teacher can not be assigned as Teacher 5 and Teacher 1 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c8']) && !empty($data['c5'])){
						if($data['c8'] == $data['c5']){
							drupal_set_message('Same teacher can not be assigned as Teacher 5 and Teacher 2 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c8']) && !empty($data['c6'])){
						if($data['c8'] == $data['c6']){
							drupal_set_message('Same teacher can not be assigned as Teacher 5 and Teacher 3 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					elseif(!empty($data['c8']) && !empty($data['c7'])){
						if($data['c8'] == $data['c7']){
							drupal_set_message('Same teacher can not be assigned as Teacher 5 and Teacher 4 for the subject id '.$data['c1'].'.','error');
							variable_set('subject_form_error'.$user->uid, 'error');
						}
					}
					
					
				}
			}
		}
	}
	*/
	
}
	//*******Suraj********//

/**
 * Theme callback for the form table.
 */
function theme_class_sub_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	
  $header = array(t('Subject ID'),t('Name of Subject'), t('Type'));
  
  //$header = array(t('Subject ID'),t('Name of Subject'), t('Type'),t('Assign Teacher1'), t('Assign Teacher2'), t('Assign Teacher3'), t('Assign Teacher4'), t('Assign Teacher5'));
  
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

