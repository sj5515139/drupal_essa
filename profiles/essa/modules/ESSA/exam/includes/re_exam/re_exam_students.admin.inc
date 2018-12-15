<?php
/*
*Implements callback function re_exam_students()
*/
function re_exam_students($form, $form_state, $term_id, $exam_code){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
	$master_staff_table = 'essa_'.$session_id.'_master_staff_table';
	$class_teacher_table = 'essa_'.$session_id.'_class_teacher';
	$full_marks_table = 'essa_'.$session_id.'_exam_full_marks';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$re_exam_table = 'essa_'.$session_id.'_exam_re_exam';
	$sub_names = array();
	global $user;
	
	$nickname = NULL;
	$this_user = db_query(
		"SELECT * from $master_staff_table where uid = :uid;", array(':uid' => $user->uid)
	);
	foreach($this_user as $tu){
		$this_emp_id = $tu->emp_id;
		$nickname = $tu->nickname;
	}
	
	$class_teacher = db_query(
		"SELECT * from $class_teacher_table where teacher_nickname = :nn;", array(':nn' => $nickname)
	);
	foreach($class_teacher as $ct){
		$this_class = $ct->class;
		$this_sec = $ct->section;
	}
	
	if(isset($this_class)){
		$form['term_id'] = array(
			'#type' => 'value',
			'#value' => $term_id,
		);
		
		$form['exam_code'] = array(
			'#type' => 'value',
			'#value' => $exam_code,
		);
		
		$ec = db_query("SELECT * FROM {$master_exam_table} where term = :t and exam_code = :ec",
		array(':t' => $term_id, ':ec' => $exam_code));
		foreach($ec as $ex){
			$class_from = $ex->class_from;
			$class_to = $ex->class_to;
		}
		$class_list = array('--Select--');
		$cf_weight = NULL;
		$ct_weight = NULL;
		$c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_from));
		foreach($c_from_weight as $cfw){
			$cf_weight = $cfw->weight;
		}
		$c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_to));
		foreach($c_to_weight as $ctw){
			$ct_weight = $ctw->weight;
		}
		$classes = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
			array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
		foreach($classes as $c){
			$class_list[] = $c->class_id;
		}
		
		$form['sec_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "sec_wrapper">',
			'#suffix' => '</div>',
		);
		$form['student_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "student_wrapper">',
			'#suffix' => '</div>',
		);
		
		$form['sec_wrapper']['class'] = array(
			'#type' => 'select',
			'#title' => 'Select a Class',
			'#options' => drupal_map_assoc($class_list),
			'#ajax' => array(
				'event' => 'change',
				'callback' => 'display_sections_ajax',
				'wrapper' => 'sec_wrapper',
				'method' => 'replace',
				'effect' => 'fade',
			),
			'#default_value' => $this_class,
			'#disabled' => TRUE,
		);
		
		$form_state['values']['class'] = $this_class;
		if(isset($form_state['values']['class'])){
			$class_term = taxonomy_get_term_by_name($form_state['values']['class']);
			foreach($class_term as $ct){
				$tid = $ct->tid;
			}
			
			$sections = array('--Select--');
			$sec = taxonomy_get_children($tid);
			foreach($sec as $s){
				$sections[] = $s->name;
			}
			
			$form['sec_wrapper']['sec'] = array(
				'#type' => 'select',
				'#title' => 'Select a Section',
				'#options' => drupal_map_assoc($sections),
				'#ajax' => array(
					'event' => 'change',
					'callback' => 'display_student_ajax',
					'wrapper' => 'student_wrapper',
					'method' => 'replace',
					'effect' => 'fade',
				),
				'#default_value' => $this_sec,
				'#disabled' => TRUE,
			);
			
			$form_state['values']['sec'] = $this_sec;
			if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
				
				$student_table = 'essa_'.$session_id.'_'.'master_student_table';
			
				if(db_table_exists($student_table)){
					$header = array(
						'adm_no' => 'Adm No.',
						'roll_no' => 'Exam Roll No.',
						'name' => 'Name',
					);
					$students = db_query(
						"SELECT * from $student_table where class = :class AND section = :sec order by exam_roll_no;", array(':class' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
					);
					foreach($students as $st){
						$default = FALSE;	
						$default_students = db_query("SELECT * FROM {$re_exam_table} WHERE term_id = :tid AND exam_code = :ec AND adm_no = :an AND status = 1;", array(':tid' => $term_id, ':ec' => $exam_code, ':an' => $st->adm_no));
						foreach($default_students as $ds){
							$default = $ds->adm_no;
						}
						if($default != NULL){
							$default =TRUE;
						}
						//dsm($default);
						$row[$st->adm_no] = array(
							'#tree' =>TRUE,
							$st->adm_no => array(  //Generating unique array id for every form element
								$st->adm_no =>array(
									'#type' => 'checkbox',
									'#default_value' => $default,
								),
								'c1' =>array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
								),
								'c2' =>array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "text-align: left !important;">'.$st->exam_roll_no.'</h3>',
								),
								'c3' =>array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "text-align: left !important;">'.$st->student_name.'</h3>',
								),
							),
						);
					}
				}
				
				$form['student_wrapper']['students'] = array(
					'#theme' => 're_exam_students_table',
					'rows' => $row,
				);
				
				$form['student_wrapper']['save'] = array(
					'#type' => 'button',
					'#name' => 'name',
					'#value' => t('Submit'),
					'#executes_submit_callback' => TRUE,
				);
				
			}
		}
	}else{
		$form['term_id'] = array(
			'#type' => 'value',
			'#value' => $term_id,
		);
		
		$form['exam_code'] = array(
			'#type' => 'value',
			'#value' => $exam_code,
		);
		
		$ec = db_query("SELECT * FROM {$master_exam_table} where term = :t and exam_code = :ec",
		array(':t' => $term_id, ':ec' => $exam_code));
		foreach($ec as $ex){
			$class_from = $ex->class_from;
			$class_to = $ex->class_to;
		}
		$class_list = array('--Select--');
		$cf_weight = NULL;
		$ct_weight = NULL;
		$c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_from));
		foreach($c_from_weight as $cfw){
			$cf_weight = $cfw->weight;
		}
		$c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_to));
		foreach($c_to_weight as $ctw){
			$ct_weight = $ctw->weight;
		}
		$classes = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
			array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
		foreach($classes as $c){
			$class_list[] = $c->class_id;
		}
		
		$form['sec_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "sec_wrapper">',
			'#suffix' => '</div>',
		);
		
		$form['student_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "student_wrapper">',
			'#suffix' => '</div>',
		);
		
		$form['sec_wrapper']['class'] = array(
			'#type' => 'select',
			'#title' => 'Select a Class',
			'#options' => drupal_map_assoc($class_list),
			'#ajax' => array(
				'event' => 'change',
				'callback' => 'display_sections_ajax',
				'wrapper' => 'sec_wrapper',
				'method' => 'replace',
				'effect' => 'fade',
			),
		);
		
		if(isset($form_state['values']['class'])){
			$class_term = taxonomy_get_term_by_name($form_state['values']['class']);
			foreach($class_term as $ct){
				$tid = $ct->tid;
			}
			
			$sections = array('--Select--');
			$sec = taxonomy_get_children($tid);
			foreach($sec as $s){
				$sections[] = $s->name;
			}
			
			$form['sec_wrapper']['sec'] = array(
				'#type' => 'select',
				'#title' => 'Select a Section',
				'#options' => drupal_map_assoc($sections),
				'#ajax' => array(
					'event' => 'change',
					'callback' => 'display_student_ajax',
					'wrapper' => 'student_wrapper',
					'method' => 'replace',
					'effect' => 'fade',
				),
			);
			
			if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
				
				$student_table = 'essa_'.$session_id.'_'.'master_student_table';
			
				if(db_table_exists($student_table)){
					$header = array(
						'adm_no' => 'Adm No.',
						'roll_no' => 'Exam Roll No.',
						'name' => 'Name',
					);
					$students = db_query(
						"SELECT * from $student_table where class = :class AND section = :sec order by exam_roll_no;", array(':class' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
					);
					foreach($students as $st){
						$default = FALSE;	
						$default_students = db_query("SELECT * FROM {$re_exam_table} WHERE term_id = :tid AND exam_code = :ec AND adm_no = :an AND status = 1;", array(':tid' => $term_id, ':ec' => $exam_code, ':an' => $st->adm_no));
						foreach($default_students as $ds){
							$default = $ds->adm_no;
						}
						if($default != NULL){
							$default =TRUE;
						}
						//dsm($default);
						$row[$st->adm_no] = array(
							'#tree' =>TRUE,
							$st->adm_no => array(  //Generating unique array id for every form element
								$st->adm_no =>array(
									'#type' => 'checkbox',
									'#default_value' => $default,
								),
								'c1' =>array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
								),
								'c2' =>array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "text-align: left !important;">'.$st->exam_roll_no.'</h3>',
								),
								'c3' =>array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "text-align: left !important;">'.$st->student_name.'</h3>',
								),
							),
						);
					}
				}
				
				$form['student_wrapper']['students'] = array(
					'#theme' => 're_exam_students_table',
					'rows' => $row,
				);
				
				$form['student_wrapper']['save'] = array(
					'#type' => 'button',
					'#name' => 'name',
					'#value' => t('Submit'),
					'#executes_submit_callback' => TRUE,
				);
				
			}
		}
	}
	return $form;	
}

/**
 *Implements submit function - re_exam_students_submit
 */
function re_exam_students_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$re_exam_table = 'essa_'.$session_id.'_exam_re_exam';
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	
	$date = date('d-m-Y h:i:s');
	$timestamp = strtotime($date);
	global $user;	
	foreach($form_state['values'] as $key => $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				foreach($v as $adm_no  => $checked){
					if($checked != 0){
						db_merge($re_exam_table)
							->key(array('term_id' => $form_state['values']['term_id'], 'exam_code' => $form_state['values']['exam_code'], 'adm_no' => $adm_no))
							->fields (array(
								'term_id' => $form_state['values']['term_id'],
								'exam_code' => $form_state['values']['exam_code'],
								'adm_no' => $adm_no,
								'class' => $form_state['values']['class'],
								'section' => $form_state['values']['sec'],
								'status' => '1',
							)
						)	
						->execute();
					}else{
						db_merge($re_exam_table)
							->key(array('term_id' => $form_state['values']['term_id'], 'exam_code' => $form_state['values']['exam_code'], 'adm_no' => $adm_no))
							->fields (array(
								'status' => '0',
							)
						)	
						->execute();
					}
				}
			}
		}
	}
	
	drupal_set_message('Students were selected for Re-exam of class '.$form_state['values']['class'].'-'.$form_state['values']['sec'].'.', 'status');
	//sending system alert
	global $user;
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'Students were selected for Re-exam of class '.$form_state['values']['class'].'-'.$form_state['values']['sec'].'.',
		'priority' => 'M',
		'module' => 're_exam',
		'source_url' => 'admin/exam/'.$form_state['values']['term_id'].'/'.$form_state['values']['exam_code'].'/re_exam/students',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
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
function display_student_ajax($form, &$form_state){
	//dsm($form_state);
	return $form['student_wrapper'];
}
/**
 *Theme function
 */
function theme_re_exam_students_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	global $user;
	$sub_names = variable_get('upload_marks_sub'.$user->uid);
  $header = array(t('Adm No.'), t('Roll No.'), t('Name'), $sub_names);
	
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