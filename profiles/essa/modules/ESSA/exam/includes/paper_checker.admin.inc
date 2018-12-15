<?php
/**
 *Implements page callback function - create_timing()
 */
function create_paper_checker_list($form, &$form_state, $term_id, $exam_code){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	
	$class_list = array('--Select--');
	$classes = db_query(
		"SELECT * from $class_table order by weight;"
	);
	foreach($classes as $cl){
		$class_list[] = $cl->class_id;
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
	
	$form['paper_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "paper_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['exam_code'] = array(
		'#type' => 'value',
		'#value' => $exam_code,
	);
	
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id,
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
			  'callback' => 'display_paper_checker_ajax',
			  'wrapper' => 'paper_wrapper',
			  'method' => 'replace',
			  'effect' => 'fade',
			),
		);
		
		if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
			$session_id = (string)variable_get('essa_sid');
			$timing_table = 'essa_'.$session_id.'_exam_timing';
			$master_exam_table = 'essa_'.$session_id.'_exam_master';
			$master_staff_table = 'essa_'.$session_id.'_master_staff_table';
			$paper_checker_table = 'essa_'.$session_id.'_exam_paper_checkers';
			$schedule_table = 'essa_'.$session_id.'_exam_schedule';
			$class_sub_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
			$subjects = db_query("SELECT * FROM {$schedule_table} WHERE exam_code =:ec AND class = :c;", array(':ec'=> $form_state['values']['exam_code'], ':c' => $form_state['values']['class']));
			foreach($subjects as $sub){
				$teacher = NULL;
				$emp_id = NULL;
				$subject_name = db_query("SELECT * FROM {$class_sub_table} WHERE sub_id = :si;", array(':si' => $sub->subject));
				foreach($subject_name as $sn){
					$sub_name = $sn->sub_name;
				}
				$paper_checker = db_query("SELECT * FROM {$paper_checker_table} WHERE term_id = :t AND exam_code = :ec AND
																	class = :c AND section = :s AND subject = :sub;",
					array(':t' => $form_state['values']['term_id'], ':ec' => $form_state['values']['exam_code'], ':c' => $form_state['values']['class'],
								':s' => $form_state['values']['sec'], ':sub' => $sub->subject));
				foreach($paper_checker as $pc){
					$emp_id = $pc->teacher;
				}
				
				$employee = db_query("SELECT * FROM {$master_staff_table} WHERE emp_id = :eid;", array(':eid' => $emp_id));
				foreach($employee as $emp){
					$teacher = $emp->fname.' '.$emp->lname.'('.$emp->nickname.')';
				}
				
				if($teacher == NULL){
					$row[$sub->subject] = array(
						'#tree' =>TRUE,
						$sub->subject => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$sub_name.'</h3>',
							),
							'c2' =>array(
								'#type' => 'textfield',
								'#autocomplete_path' => 'teachers/autocomplete',
								'#size' => 10,
							),
						),
					);
				}else{
					$row[$sub->subject] = array(
						'#tree' =>TRUE,
						$sub->subject => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$sub_name.'</h3>',
							),
							'c2' =>array(
								'#type' => 'textfield',
								'#autocomplete_path' => 'teachers/autocomplete',
								'#size' => 10,
								'#default_value' => $teacher,
							),
						),
					);
				}
				
				
				
			}
			if(isset($row)){
				$form['paper_wrapper']['paper_checker'] = array(
					'#theme' => 'paper_checker_table',
					'rows' => $row,
				);
				$form['paper_wrapper']['submit'] = array(
					'#type' => 'submit',
					'#value' => 'Save',
					'#submit' => array('display_paper_checker_ajax_submit'),
				);
			}else{
				
				global $base_url;
				$url = $base_url.'/admin/exam/'.$form_state['values']['term_id'].'/'.$form_state['values']['exam_code'].'/exam_schedule';
				
				$form['paper_wrapper']['msg'] = array(
					'#type' => 'markup',
					'#markup' => '<h3 style = "color:Red;">No schedule has been created yet for class '.$form_state['values']['class'].'. Click <a href = "'.$url.'">here</a> to create.</h3>',
				);
			}
		}
	}
	return $form;
}

/**
 *Implements callback function display_paper_checker_ajax_submit().
 */
function display_paper_checker_ajax_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$paper_checker_table = 'essa_'.$session_id.'_exam_paper_checkers';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				if(!empty($v['c2'])){
					preg_match('#\((.*?)\)#', $v['c2'], $match);
					$staff_db = db_query(
						"SELECT * from {$staff_table} where nickname = :nickname",  array(':nickname' => $match[1])
					);
					foreach($staff_db as $staff){
						$emp_id = $staff->emp_id;
					}
					
					db_merge($paper_checker_table)
					->key(array('term_id' => $form_state['values']['term_id'], 'exam_code' =>$form_state['values']['exam_code'], 'class' => $form_state['values']['class'], 'section' => $form_state['values']['sec'], 'subject' => $k))
					->fields(array(
						'term_id' => $form_state['values']['term_id'],
						'exam_code' => $form_state['values']['exam_code'],
						'class' => $form_state['values']['class'],
						'section' => $form_state['values']['sec'],
						'subject' => $k,
						'teacher' => $emp_id,
					))
					->execute();
				}
			}
		}
	}
	drupal_set_message('Paper Checker list was updated suceessfully for '.$form_state['values']['exam_code'].' exam.','status');
}

/**
 *Implements ajax callback.
 */
function display_sections_ajax($form, &$form_state){
	//dsm($form_state);
	return $form;
}

/**
 *Implements ajax callback - display_paper_checker_ajax
 */
function display_paper_checker_ajax($form, &$form_state){
	return $form['paper_wrapper'];
}


/**
 *Theme function student_passout_table()
 */
function theme_paper_checker_table(&$variables){
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