<?php
/**
 * Implements callback function create_exam()
 */
function arrangement_form($form = array(), &$form_state){
	$form['date'] = array(
		'#type' => 'date_popup',
		'#size' => 15,
		'#date_label_position' => 'within',
		'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
		'#date_format' => 'd-m-Y',
		'#date_year_range' => '0:+1',
		'#title' => 'Select a Date',
		'#ajax' => array(
		  'event' => 'change',
		  'callback' => 'get_class_ajax',
		  'wrapper' => 'sd_wrapper',
		  'method' => 'replace',
		  'effect' => 'fade',
		),
 	);
	
	$form['sd_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "sd_wrapper">',
		'#suffix' => '</div></div>',
	);
	
	if(isset($form_state['values']['date']) && $form_state['values']['date'] != NULL){
		
		$date = strtotime($form_state['values']['date']);
		$absent_staff = array();
		$session = variable_get('essa_sid');
		$staff_table = 'essa_'.$session.'_master_staff_table';
		$staff_attendance_table ='essa_'.$session.'_staff_attendance';
		$class_section_table = 'essa_'.$session.'_class_section';
		$leave_table = 'essa_'.$session.'_leave_staff_history';
		$tt_arrangement_table = 'essa_'.$session.'_time_table_arrangement';
		$staff_leave = db_query("SELECT * FROM {$leave_table} WHERE $date BETWEEN from_date AND to_date AND status_principal =:s;", array(':s' => 'Approved'));
		foreach($staff_leave as $sl){
			$absent_staff[] = $sl->emp_id;
		}
		//dsm($absent_staff);
		$day = date('l',$date);
		foreach($absent_staff as $as){
			$tt_table = 'essa_'.$session.'_time_table_'.clean_teacher_insert($as);
			$tt_data = db_query("SELECT * FROM {$tt_table} WHERE day =:d ORDER BY day_weight;", array(':d' => $day));
			foreach($tt_data as $td){
				//dsm($td);
				if($td->Period1_class != NULL){
					//dsm('chmcb');
					$data[] = array('class'=>$td->Period1_class, 'period'=>'Period 1', 'subject' => $td->Period1_subject, 'teacher' => $as);
				}
				if($td->Period2_class != NULL){
					//dsm('chmcb');
					$data[] = array('class'=>$td->Period2_class, 'period'=>'Period 2', 'subject' => $td->Period2_subject, 'teacher' => $as);
				}
				if($td->Period3_class != NULL){
					//dsm('chmcb');
					$data[] = array('class'=>$td->Period3_class, 'period'=>'Period 3', 'subject' => $td->Period3_subject, 'teacher' => $as);
				}
				if($td->Period4_class != NULL){
					//dsm('chmcb');
					$data[] = array('class'=>$td->Period4_class, 'period'=>'Period 4', 'subject' => $td->Period4_subject, 'teacher' => $as);
				}
				if($td->Period5_class != NULL){
					//dsm('chmcb');
					$data[] = array('class'=>$td->Period5_class, 'period'=>'Period 5', 'subject' => $td->Period5_subject, 'teacher' => $as);
				}
				if($td->Period6_class != NULL){
					//dsm('chmcb');
					$data[] = array('class'=>$td->Period6_class, 'period'=>'Period 6', 'subject' => $td->Period6_subject, 'teacher' => $as);
				}
				if($td->Period7_class != NULL){
					//dsm('chmcb');
					$data[] = array('class'=>$td->Period7_class, 'period'=>'Period 7', 'subject' => $td->Period7_subject, 'teacher' => $as);
				}
				if($td->Period8_class != NULL){
					//dsm('chmcb');
					$data[] = array('class'=>$td->Period8_class, 'period'=>'Period 8', 'subject' => $td->Period8_subject, 'teacher' => $as);
				}
			}
		}
		//$data = array_unique($data);
		$teachers = db_query("SELECT * FROM ($staff_table) WHERE type = :type OR type = :type2;", array(':type' => 'Teaching', ':type2' => 'teaching'));
		foreach($teachers as $t){
			$teacher[] = $t->emp_id;
		}
		$teacher = array_diff($teacher, $absent_staff);
		$staff1[] = ('--Select--');
		$staff2[] = ('--Select--');
		$staff3[] = ('--Select--');
		$staff4[] = ('--Select--');
		$staff5[] = ('--Select--');
		$staff6[] = ('--Select--');
		$staff7[] = ('--Select--');
		$staff8[] = ('--Select--');
		foreach($teacher as $th){
			$tchr_tt_table = 'essa_'.$session.'_time_table_'. clean_teacher_insert($th);
			$tchr_tt_db = db_query(
				"SELECT * from {$tchr_tt_table} where day = :dw order by day_weight;", array(':dw' => $day)
			);
			foreach($tchr_tt_db as $tchr){
				//dsm($tchr);
				//dsm($th);
				if($tchr->Period1_class == NULL){
					$staff1[] = $th;
				}
				if($tchr->Period2_class == NULL){
					$staff2[] = $th;
				}
				if($tchr->Period3_class == NULL){
					$staff3[] = $th;
				}
				if($tchr->Period4_class == NULL){
					$staff4[] = $th;
				}
				if($tchr->Period5_class == NULL){
					$staff5[] = $th;
				}
				if($tchr->Period6_class == NULL){
					$staff6[] = $th;
				}
				if($tchr->Period7_class == NULL){
					$staff7[] = $th;
				}
				if($tchr->Period8_class == NULL){
					$staff8[] = $th;
				}
			}
		}
		//dsm($data);
		foreach($data as $d){
			if($d['period'] == 'Period 1'){
				$option = $staff1;
			}elseif($d['period'] == 'Period 2'){
				$option = $staff2;
			}elseif($d['period'] == 'Period 3'){
				$option = $staff3;
			}elseif($d['period'] == 'Period 4'){
				$option = $staff4;
			}elseif($d['period'] == 'Period 5'){
				$option = $staff5;
			}elseif($d['period'] == 'Period 6'){
				$option = $staff6;
			}elseif($d['period'] == 'Period 7'){
				$option = $staff7;
			}elseif($d['period'] == 'Period 8'){
				$option = $staff8;
			}
			
			$default_data = db_query("SELECT * FROM {$tt_arrangement_table} where date = :d and class = :c and period =:p;", array(':d' => $date, ':c' => $d['class'], ':p' => $d['period']));
			foreach($default_data as $dd){
				$default_teacher = $dd->teacher;
			}
			
			$row[] = array(
				'#tree' =>TRUE,
				$d['class'].'%'.$d['period'].'%'.$d['subject'] => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$d['class'].'</h3>',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$d['period'].'</h3>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$d['subject'].'</h3>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$d['teacher'].'</h3>',
						),
					'c5' =>array(
						'#type' => 'select',
						'#options' => drupal_map_assoc($option),
						'#default_value' => $default_teacher,
					),
				),
			);
			
			
		}
		if(isset($row)){
			$form['sd_wrapper']['arrangement'] = array(
				'#theme' => 'arrangement_table',
				'rows' => $row,
			);
			
			$form['sd_wrapper']['submit'] = array(
				'#type' => 'submit',
				'#value' => 'Save',
				'#submit' => array('get_ajax_submit'),
			);
		}else{
			$form['sd_wrapper']['msg'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 style ="color: red;">There are no arrangements for the date '.$form_state['values']['date'].'</h3>',
			);
		}
	}
	return $form;
}
/**
 *Implements ajax callback function - get_class_ajax()
 */
function get_class_ajax($form, &$form_state){
	//dsm($form_state);
	return $form['sd_wrapper'];
}

/**
 *Implements submit function - get_ajax_submit
 */
function get_ajax_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$tt_arrangement_table = 'essa_'.$session.'_time_table_arrangement';
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				//dsm($k);
				$data = explode('%',$k);
				//dsm($data);
				db_merge($tt_arrangement_table)
				->key(array('date' => strtotime($form_state['values']['date']),'class' => $data[0],'period' => $data[1],'subject' => $data[2]))
				->fields(array(
					'date' => strtotime($form_state['values']['date']),
					'class' => $data[0],
					'period' => $data[1],
					'subject' => $data[2],
				))
				->execute();
				if($v['c5'] != '--Select--'){
					db_merge($tt_arrangement_table)
					->key(array('date' => strtotime($form_state['values']['date']),'class' => $data[0],'period' => $data[1],'subject' => $data[2]))
					->fields(array(
						'teacher' => $v['c5'],
					))
					->execute();
				}
			}
		}
	}
	drupal_set_message("Arrangement of classes done successfully.");
}


/**
 * Theme callback for the form table.
*/ 
function theme_arrangement_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Class'), t('Period'), t('Subject'), t('Teacher'), t('Arrangement'));
  
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


