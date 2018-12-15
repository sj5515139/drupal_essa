<?php
/**
 *Implements page callback function optional_subject_form
 */
function student_sub_form($form = array(), &$form_state, $class, $sec, $subj){
  $session = variable_get('essa_sid');
  $student_table = 'essa_'.$session.'_master_student_table';
  $op_sub_table = 'essa_'.$session.'_optional_subject_student';
	$class_sub_table = 'essa_'.$session.'_subjects_'.$class;
	$op_sub_pair_table = 'essa_'.$session.'_optional_subject_pair';
	$notification_table = 'essa_'.$session.'_notifications';
	$staff_table = 'essa_'.$session.'_master_staff_table';
	
	//******SURAJ******//
	//******Removing Notifications******//
	global $base_url;
	global $user;
	$url = 'admin/students/manage_optional_subjects/'.$class.'/'.$sec.'/'.$subj;

	$class_subject = db_query(
		"SELECT * FROM {$class_sub_table} WHERE sub_id = :sub_id;", array(':sub_id' => $subj)
	);
	foreach($class_subject as $cs){
		$sub_name = $cs->sub_name;
	}
	$msg = 'Students have been alloted to subject '.$sub_name.' for class '.$class.' - '.$sec.'.';
	$notifications = db_query("SELECT * FROM {$notification_table} WHERE uid =:uid AND destination_url =:url AND message = :msg;",array(':uid' => $user->uid, ':url' => $url, ':msg' => $msg));
	foreach($notifications as $notification){
		//dsm('ok');
		db_update($notification_table)
		->fields(array(
			'status' => '1',
		))
		->condition(db_and()
		->condition('uid', $user->uid)
		->condition('destination_url', $url)
		->condition('message', $msg))
		->execute();
	}

	$students = db_query("
    SELECT * FROM {$student_table} where status = 1;"
  );
	$adm_no = array();
  foreach($students as $student){
		//dsm($student->adm_no);
		$adm_no[] = $student->adm_no;
	}
	foreach($adm_no as $an){
		$msg1 = $an.' has been removed from subject '.$sub_name;
		//dsm($msg1);
		$notifications = db_query("SELECT * FROM {$notification_table} WHERE uid =:uid AND destination_url =:url AND message = :msg;",array(':uid' => $user->uid, ':url' => $url, ':msg' => $msg1));
		foreach($notifications as $notification){
			//dsm('ok');
			db_update($notification_table)
			->fields(array(
				'status' => '1',
			))
			->condition(db_and()
			->condition('uid', $user->uid)
			->condition('destination_url', $url)
			->condition('message', $msg1))
			->execute();
		}
	}
	$flag = 0;
	$r_id = db_query("SELECT * FROM {role} WHERE name = :name;", array(':name' => 'Class Teacher'));
	foreach($r_id as $rid){
		$u_id = db_query("SELECT * FROM {users_roles} WHERE rid = :rid;", array(':rid' => $rid->rid));
			foreach($u_id as $u){
				if($u->uid == $user->uid){
					$flag = 1;
				}
		}
	}

	//******SURAJ******//

	$default = array();
  $students = db_query("
    SELECT * from {$op_sub_table} where sub_id = :si", array(':si' => $subj)
  );
  foreach($students as $student){
    $default[$student->adm_no][$student->adm_no] = TRUE;
  }

  $form['class'] = array(
    '#type' => 'value',
    '#value' => $class,
  );

  $form['sec'] = array(
    '#type' => 'value',
    '#value' => $sec,
  );

  $form['subj'] = array(
    '#type' => 'value',
    '#value' => $subj,
  );

  $form['back'] = array(
		'#type' => 'markup',
		'#markup' => '<p class = "back_button">'.l(t('Back'), 'admin/students/manage_optional_subjects/'.$class.'/'.$sec).'</p>',
	);
	
	$sub = array();
	$op_subject = db_query(
		"SELECT * FROM {$op_sub_pair_table} where class = :cl;", array(':cl' => $class)
	);
	foreach($op_subject as $os){
		if($os->sub_1 !=  NULL){
			$sub[$os->sub_1] = $os->pair_name;
		}
		if($os->sub_2 !=  NULL){
			$sub[$os->sub_2] = $os->pair_name;
		}
		if($os->sub_3 !=  NULL){
			$sub[$os->sub_3] = $os->pair_name;
		}
		if($os->sub_4 !=  NULL){
			$sub[$os->sub_4] = $os->pair_name;
		}
		if($os->sub_5 !=  NULL){
			$sub[$os->sub_5] = $os->pair_name;
		}
		if($os->sub_1 ==  $subj){
			$this_pair_name = $os->pair_name;
		}
		if($os->sub_2 ==  $subj){
			$this_pair_name = $os->pair_name;
		}
		if($os->sub_3 ==  $subj){
			$this_pair_name = $os->pair_name;
		}
		if($os->sub_4 ==  $subj){
			$this_pair_name = $os->pair_name;
		}
		if($os->sub_5 ==  $subj){
			$this_pair_name = $os->pair_name;
		}
	}
	
	unset($sub[$subj]);
	foreach($sub as $s=>$pair_name){
		if($pair_name != $this_pair_name){
			unset($sub[$s]);
		}
	}
	
	$students = db_query("
    SELECT * from {$student_table} where class = :class and section = :sec and status = 1 order by roll_no;",array(':class' => $class, ':sec' => $sec)
  );
  $row = array();
  foreach($students as $student){
		$flag = 0;
		foreach($sub as $s=>$pair_name){
			$op_students = db_query("
				SELECT * from {$op_sub_table} where sub_id = :si and adm_no = :an", array(':si' => $s, ':an' => $student->adm_no)
			);
			foreach($op_students as $op_student){
				$flag = 1;
				break;
			}
			if($flag == 1){
				$row[$student->adm_no] = array(
					'#tree' =>TRUE,
					$student->adm_no => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'checkbox',
							'#checkall' => 'unique-class-for-each-checkboxes-column',
							'#default_value' => isset($default[$student->adm_no][$student->adm_no])?$default[$student->adm_no][$student->adm_no]:FALSE,
							'#disabled' => TRUE,
						),
						'ca' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$student->adm_no.'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$student->roll_no.'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$student->student_name.'</h3>',
						),
					),
				);	
			}else{
				$row[$student->adm_no] = array(
					'#tree' =>TRUE,
					$student->adm_no => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'checkbox',
							'#checkall' => 'unique-class-for-each-checkboxes-column',
							'#default_value' => isset($default[$student->adm_no][$student->adm_no])?$default[$student->adm_no][$student->adm_no]:FALSE,
						),
						'ca' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$student->adm_no.'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$student->roll_no.'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$student->student_name.'</h3>',
						),
					),
				);	
			}
		}
  }
  $form['fs']['students'] = array(
    '#theme' => 'student_table',
    'rows' => $row,
  );


  $form['fs']['save'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  return $form;
}

function student_sub_form_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$op_sub_table = 'essa_'.$session_id.'_optional_subject_student';
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	$notification_table = 'essa_'.$session_id.'_notifications';
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	$sub_teacher_table = 'essa_'.$session_id.'_subject_teacher_table';

	global $user;

	foreach($form_state['values'] as $input){
		if(is_array($input)){
			foreach($input as $key=>$in){
				$flag = 0;
				$msg_flag = 0;
				$students = db_query("
				  SELECT * from {$op_sub_table} where class_id = :class_id and section = :sec and sub_id = :sub_id;", array(':class_id' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'], ':sub_id' => $form_state['values']['subj'])
				);
				foreach($students as $student){
					if($student->adm_no == $key){
						$flag = 1;
						$id = $student->id;
					}
				}
				if($flag == 0){
					if($in['c1'] != 0){
						db_insert($op_sub_table)
						-> fields(array(
							'class_id' => $form_state['values']['class'],
							'section' => $form_state['values']['sec'],
							'sub_id' => $form_state['values']['subj'],
							'adm_no' => $key,
						  ))
						->execute();
					}
				}else{
					if($in['c1'] == 0){
						db_delete($op_sub_table)
						->condition('adm_no', $key)
						->execute();
						$msg_flag = 1;
					}
				}

				//*******Suraj********//
				if($msg_flag == 0 && $flag != 1){
					//dsm('1');
					$class_sub_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
					$class_subject = db_query(
						"SELECT * from {$class_sub_table} WHERE sub_id = :sub_id;", array(':sub_id' => $form_state['values']['subj'])
					);
					foreach($class_subject as $cs){
						$sub_name = $cs->sub_name;
					}

					$class_subject = db_query(
						"SELECT * from {$sub_teacher_table} WHERE class = :c AND section = :s AND subject = :sub_id;", array(':c' => $form_state['values']['class'], ':s' => $form_state['values']['sec'],':sub_id' => $form_state['values']['subj'])
					);
					foreach($class_subject as $cs){
						$emp = $cs->teacher;
					}
					if(isset($emp)){
						$created_date = date("Y-m-d H:i:s");
						$strtodate = strtotime($created_date);
	
						$staffs_uid = db_query("SELECT * FROM {$staff_table} WHERE emp_id = :emp_id AND status = 1;", array(':emp_id' => $emp));
						foreach($staffs_uid as $s_uid){
							if($in['c1'] != 0){
								//dsm('2');
								//Sending Notification
								/*
								db_insert($notification_table)
								->fields(array(
									'uid' => $s_uid->uid,
									'message' => 'Students have been alloted to subject '.$sub_name.' for class '.$form_state['values']['class'].' - '.$form_state['values']['sec'].'.',
									'status' => '0',
									'module' => 'students',
									'source_url' => 'admin/students/manage_optional_subjects/'.$form_state['values']['class'].'/'.$form_state['values']['sec'].'/'.$form_state['values']['subj'],
									'destination_url' => 'admin/students/manage_optional_subjects/'.$form_state['values']['class'].'/'.$form_state['values']['sec'].'/'.$form_state['values']['subj'],
									'timestamp' => $strtodate,
									'source_uid' => $user->uid,
								))
								->execute();
								*/
							}
						}
	
						if($in['c1'] != 0){
							//sending system alert
							//dsm('ok');
							$created_date = date("Y-m-d H:i:s");
							$strtodate = strtotime($created_date);
							db_insert($sys_alert_table)
							->fields(array(
								'message' => $key.' has opted for subject '.$form_state['values']['subj'].'.',
								'priority' => 'L',
								'module' => 'students',
								'source_url' => 'admin/students/manage_optional_subjects/'.$form_state['values']['class'].'/'.$form_state['values']['sec'].'/'.$form_state['values']['subj'],
								'timestamp' => $strtodate,
								'source_uid' => $user->uid,
							))
							->execute();
						}	
					}
				}else{
					$class_sub_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
					if($msg_flag == 1){
						$class_subject = db_query(
							"SELECT * from {$class_sub_table} WHERE sub_id = :sub_id;", array(':sub_id' => $form_state['values']['subj'])
						);
						foreach($class_subject as $cs){
							$sub_name = $cs->sub_name;
						}

						$class_subject = db_query(
							"SELECT * from {$sub_teacher_table} WHERE class = :c AND section = :s AND subject = :sub_id;", array(':c' => $form_state['values']['class'], ':s' => $form_state['values']['sec'],':sub_id' => $form_state['values']['subj'])
						);
						foreach($class_subject as $cs){
							$emp = $cs->teacher;
						}

						$created_date = date("Y-m-d H:i:s");
						$strtodate = strtotime($created_date);
						$teacher = 0;

						$staffs_uid = db_query("SELECT * FROM {$staff_table} WHERE emp_id = :emp_id AND status = 1;", array(':emp_id' => $emp));
						foreach($staffs_uid as $s_uid){
							$emp_uid = $s_uid->uid;
						}
						if($in['c1'] == 0){
							//Sending Notification
							/*
							db_insert($notification_table)
							->fields(array(
								'uid' => $emp_uid,
								'message' => $key.' has been removed from subject '.$sub_name,
								'status' => '0',
								'module' => 'students',
								'source_url' => 'admin/students/manage_optional_subjects/'.$form_state['values']['class'].'/'.$form_state['values']['sec'].'/'.$form_state['values']['subj'],
								'destination_url' => 'admin/students/manage_optional_subjects/'.$form_state['values']['class'].'/'.$form_state['values']['sec'].'/'.$form_state['values']['subj'],
								'timestamp' => $strtodate,
								'source_uid' => $user->uid,
							))
							->execute();
						*/

							//sending system alert
							//dsm('ok');
							$created_date = date("Y-m-d H:i:s");
							$strtodate = strtotime($created_date);
							db_insert($sys_alert_table)
							->fields(array(
								'message' => $key.' has been removed from subject '.$form_state['values']['subj'].'.',
								'priority' => 'L',
								'module' => 'students',
								'source_url' => 'admin/students/manage_optional_subjects/'.$form_state['values']['class'].'/'.$form_state['values']['sec'].'/'.$form_state['values']['subj'],
								'timestamp' => $strtodate,
								'source_uid' => $user->uid,
							))
							->execute();
						}
					}
				}
				//*******Suraj********//

			}
		}
	}
	drupal_set_message('Students were allotted optional subject successfully.');
}

/**
 * Theme callback for the form table.
 */
function theme_student_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Select Student'), t('Adm No.'), t('Roll No'),t('Name'));

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
  /*

		$weight = find_weight();
      foreach($weight as $key => $value){
        if($input == $key){
          $w = $value;
        }
      }
    if($input != '0'){
			db_merge($class_list)
				->key(array('class_id' => $k))
        -> fields(array(
          'class_id' => $k,
          'weight' => $w,
          'class_set_id' => '',
      ))
      ->execute();

			$vid = taxonomy_vocabulary_machine_name_load('class_vocab');
			if(_get_taxonomy_term_id_by_name($input, $vid->vid) == false) {
        taxonomy_term_save(
            (object) array(
                'name' => $input,
                'vid' => $vid->vid,
								'weight' => $w,
            )
        );
			}
    }else{
			db_query("DELETE FROM {$class_list} WHERE class_id = :d", array(':d' => $k));
			db_query("DELETE FROM {taxonomy_term_data} WHERE name = :d", array(':d' => $k));
		}








	$class_list_table = 'essa_'.$session.'_class_list';
	$class_list = array();


  $session = variable_get('essa_sid');
	$class_list_table = 'essa_'.$session.'_class_list';
	$class_list = array();

	$class_list_db = db_query(
		"SELECT class_id,weight from {$class_list_table} order by weight"
	);

  foreach($class_list_db as $class){
    $voc = 'class_vocab';//replace this with the taxonomy term
		$vocabulary = taxonomy_vocabulary_machine_name_load($voc);
		$terms = taxonomy_get_tree($vocabulary->vid);
		foreach($terms as $term){
      if($term->name == $class->class_id){
        $sec = taxonomy_get_children($term->tid);
        dsm($sec);
      }
		}
  }

  $form['title'] = array(
		'#markup' => '<h2 id = "bulk_title" style = "margin-top: 3px;"> Select a class & section </h2>',
	);

  module_load_include('inc', 'hierarchical_select', 'includes/common');

	$config = sa_hs_ops_setting();
	$form['class'] =  array(
    '#type' => 'hierarchical_select',
    '#config' => $config,
		'#required' => TRUE,
    '#ajax' => array(
            'event' => 'change',
            'callback' => 'test_ajax',
            'wrapper' => 'wrapper',
            'method' => 'replace',
            'effect' => 'fade',
          ),
  );


  $form['go'] = array(
    '#type' => 'button',
    '#value' => 'Go',
    '#ajax' => array(
      'event' => 'click',
      'callback' => 'sub_select_ajax',
      'wrapper' => 'sub_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['container'] =  array(
    '#type' => 'container',
    '#prefix' => '<br><br><div id = "sub_wrapper">',
    '#suffix' => '</div>'
  );

  /*
  $subjects = db_query("
    SELECT * from {$sub_table} where type = 'Optional';
  ");
	foreach($subjects as $sub){
		$subj[] = $sub->sub_name;
	}

  $form['fs'] = array(
    '#type' => 'fieldset',

  );

  $form['fs']['select_sub'] = array(
    '#type' => 'select',
    '#title' => t('Select a Subject'),
    '#required' => TRUE,
    '#options' => drupal_map_assoc($subj),
  );

  $student_table = 'essa_'.$session.'_'.$class->name.'_'.$section->name;
  $students = db_query("
    SELECT * from {$student_table} WHERE status = 1 order by roll_no;
  ");

  foreach($students as $student){
    $row[] = array(
      '#tree' =>TRUE,

      $student->roll_no => array(  //Generating unique array id for every form element
				'c1' =>array(
          '#type' => 'checkbox'
        ),
        'c2' =>array(
          '#type' => 'markup',
					'#markup' => '<h3>'.$student->roll_no.'</h3>',
        ),
        'c3' =>array(
          '#type' => 'markup',
					'#markup' => '<h3>'.$student->first_name.' '.$student->last_name.'</h3>',
        ),
      ),
    );
  }
  $form['fs']['students'] = array(
    '#theme' => 'student_table',
    'rows' => $row,
  );


  $form['fs']['save'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    '#submit' => array('save_students'),
  );
  */
  /*
  return $form;
}

function sub_select_ajax($form, &$form_state){
  $session = variable_get('essa_sid');
  $class['class'] = taxonomy_term_load($form_state['values']['class'][0]);
	$class['section'] = taxonomy_term_load($form_state['values']['class'][1]);

  return dsm($class);
}

function save_students($form, &$form_state){
  dsm($form_state);
}
*/
