<?php
function assign_roll($form, &$form_state){
	$session = variable_get('essa_sid');
  $student_table = 'essa_'.$session.'_master_student_table';
  $op_sub_table = 'essa_'.$session.'_optional_subject_student';
	$op_sub_pair_table = 'essa_'.$session.'_optional_subject_pair';
	$notification_table = 'essa_'.$session.'_notifications';
	$staff_table = 'essa_'.$session.'_master_staff_table';
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
	$sub_names = array();
	global $user;
	
	$class_list = array('--Select--');
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
		$classes = db_query("SELECT * FROM {$class_table} order by weight;");
		foreach($classes as $c){
			$class_list[] = $c->class_id;
		}
		
		$form['sec_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "sec_wrapper">',
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
		
		$form['sub_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "sub_wrapper">',
			'#suffix' => '</div>',
		);
		
		$form['marks_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "marks_wrapper">',
			'#suffix' => '</div>',
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
					'wrapper' => 'sub_wrapper',
					'method' => 'replace',
					'effect' => 'fade',
				),
				'#default_value' => $this_sec,
				'#disabled' => TRUE,
			);
			
			$form_state['values']['sec'] = $this_sec;
			if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
				$students = db_query(
					"SELECT * from $master_student_table where class = :cl and section = :sec order by roll_no;",
					array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
				);
				foreach($students as $student){
					$row[$student->adm_no] = array(
						'#tree' =>TRUE,
						$student->adm_no => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$student->adm_no.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$student->student_name.'</h3>',
							),
							'c4' => array(
								'#type' => 'textfield',
								'#size' => 8,
								'#default_value' => $student->roll_no,
							),
						),
					);		
				}
				
				$form['sub_wrapper']['students'] = array(
					'#theme' => 'assign_roll_no_table',
					'rows' => $row,
				);
				
				$form['sub_wrapper']['save'] = array(
					'#type' => 'submit',
					'#value' => 'Save',
				);
			}
		}
	}else{
		$classes = db_query("SELECT * FROM {$class_table} order by weight;");
		foreach($classes as $c){
			$class_list[] = $c->class_id;
		}
		
		$form['sec_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "sec_wrapper">',
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
		
		$form['sub_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "sub_wrapper">',
			'#suffix' => '</div>',
		);
		
		$form['marks_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "marks_wrapper">',
			'#suffix' => '</div>',
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
					'wrapper' => 'sub_wrapper',
					'method' => 'replace',
					'effect' => 'fade',
				),
			);
			
			

			
			if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
				$students = db_query(
					"SELECT * from $master_student_table where class = :cl and section = :sec order by roll_no;",
					array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
				);
				foreach($students as $student){
					$row[$student->adm_no] = array(
						'#tree' =>TRUE,
						$student->adm_no => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$student->adm_no.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$student->student_name.'</h3>',
							),
							'c4' => array(
								'#type' => 'textfield',
								'#size' => 8,
								'#default_value' => $student->roll_no,
							),
						),
					);		
				}
				
				$form['sub_wrapper']['students'] = array(
					'#theme' => 'assign_roll_no_table',
					'rows' => $row,
				);
				
				$form['sub_wrapper']['save'] = array(
					'#type' => 'submit',
					'#value' => 'Save',
				);
			}
		}
	}
	return $form;
}

/**
 *Implements submit function.
 */
function assign_roll_submit($form, &$form_state){
	$session = variable_get('essa_sid');
  $student_table = 'essa_'.$session.'_master_student_table';
	
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k=>$v){
				db_update('essa_'.$session.'_master_student_table') // Table name no longer needs {}
					->fields(array('roll_no' => $v['c4']))
					-> condition('adm_no', $k, '=')
					->execute();
			}
		}
	}
	drupal_set_message('Roll No was updated successfully for class '.$form_state['values']['class'].'-'.$form_state['values']['sec']);
}

/**
 * Theme callback for the form table.
 */
function theme_assign_roll_no_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Adm No.'),t('Name'), t('Roll No.'));

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
 *Implements ajax callback - display_student_ajax
 */
function display_marks_ajax($form, &$form_state){
	return $form['marks_wrapper'];
}

/**
 *Implements ajax callback - display_student_ajax
 */
function display_student_ajax($form, &$form_state){
	return $form['sub_wrapper'];
}

/**
 *Implements ajax callback.
 */
function display_sections_ajax($form, &$form_state){
	//dsm($form_state);
	return $form['sec_wrapper'];
}