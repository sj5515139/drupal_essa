<?php
function display_schedule($form, &$form_state, $student_uid){
  $form = array();
  $session_id = (string)variable_get('essa_sid');
  $class_table = 'essa_'.$session_id.'_class_list';
  $timing_table = 'essa_'.$session_id.'_exam_timing';
  $master_exam_table = 'essa_'.$session_id.'_exam_master';
  $grade_table = 'essa_'.$session_id.'_exam_grade_settings';
  $master_student_table = 'essa_'.$session_id.'_master_student_table';
  $op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
  $exam_status_table = 'essa_'.$session_id.'_exam_status';
  $term_table = 'essa_'.$session_id.'_exam_terms';
  $schedule_table = 'essa_'.$session_id.'_exam_schedule';
  
  // $form['term_id'] = array(
    // '#type' => 'value',
    // '#value' => $term_id,
  // );
  
  // $form['exam_code'] = array(
    // '#type' => 'value',
    // '#value' => $exam_code,
  // );
  
  $student = db_query("SELECT * FROM {$master_student_table} WHERE uid = :uid;", array(':uid' => $student_uid));
  foreach($student as $st){
    $class = $st->class;
    $section = $st->section;
  }
  
  $form['class'] = array(
    '#type' => 'value',
    '#value' => $class,
  );
 
  $row = NULL;
  $subject_table = 'essa_'.$session_id.'_subjects_'.$class;
  $exams = db_query("SELECT * FROM {$master_exam_table}");
  foreach($exams as $exam){
    $flag = 0;
		$flag2 = 0;
    $term_id = $exam->term;
    $exam_code = $exam->exam_code;
    if(variable_get($exam->term.$exam->exam_code.$class.'_result_generate_status') == '1'){
      $flag = 1;
    }
    if(variable_get($exam->term.'_'.$exam->exam_code.'_schedule_status') == 'publish' && $flag == 1){
    
			$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $term_id, ':ec' => $exam_code, ':c' => $class));
			foreach($schedule as $sc){
				
				$subjects = db_query("SELECT * FROM {$subject_table} WHERE sub_id = :si;", array(':si' => $sc->subject));
				foreach($subjects as $sub){
					$sub_name = $sub->sub_name;
				}
				$row[$sc->subject] = array(
					'#tree' =>TRUE,
					$sc->subject => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $sub_name .'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. date('d-m-Y', $sc->date) .'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$sc->sitting.'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. date('H:i', $sc->time_from) .'</h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. date('H:i', $sc->time_to) .'</h3>',
						),
					),
				);
			}
			
			if(isset($row)){
				$form['msg'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>Schedule of '.$exam_code.' exam.</h3>',
				);
				
				$form['msg2'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>Class '.$class.'-'.$section.'</h3>',
				);
				
				$form['schedule'] = array(
					'#theme' => 'student_schedule_table',
					'rows' => $row,
				);
				
				$form['date'] = array(
					'#type' => 'markup',
					'#markup' => '<h3> Publish Date - '.variable_get($term_id.'_'.$exam_code.'_schedule_publish_date').'</h3>',
				);
				
				$form['print_schedule'] = array(
					'#type' => 'submit',
					'#value' => t('Print Schedule'),
					'#submit' => array('print_schedule_form'),
				);
			}
			
    }
		
		if(variable_get($exam->term.$exam->exam_code.$class.'_re_exam_result_generate_status') == '1'){
      $flag2 = 1;
    }
    if(variable_get($exam->term.'_'.$exam->exam_code.'_re_exam_schedule_status') == 'publish' && $flag2 == 1){
    
			$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $term_id, ':ec' => 're_'.$exam_code, ':c' => $class));
			foreach($schedule as $sc){
				
				$subjects = db_query("SELECT * FROM {$subject_table} WHERE sub_id = :si;", array(':si' => $sc->subject));
				foreach($subjects as $sub){
					$sub_name = $sub->sub_name;
				}
				$row[$sc->subject] = array(
					'#tree' =>TRUE,
					$sc->subject => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $sub_name .'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. date('d-m-Y', $sc->date) .'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$sc->sitting.'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. date('H:i', $sc->time_from) .'</h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. date('H:i', $sc->time_to) .'</h3>',
						),
					),
				);
			}
			
			if(isset($row)){
				$form['msg'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>Schedule of '.$exam_code.' Re-Exam.</h3>',
				);
				
				$form['msg2'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>Class '.$class.'-'.$section.'</h3>',
				);
				
				$form['schedule'] = array(
					'#theme' => 'student_schedule_table',
					'rows' => $row,
				);
				
				$form['date'] = array(
					'#type' => 'markup',
					'#markup' => '<h3> Publish Date - '.variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_publish_date').'</h3>',
				);
				
				$form['print_schedule'] = array(
					'#type' => 'submit',
					'#value' => t('Print Schedule'),
					'#submit' => array('print_re_exam_schedule_form'),
				);
			}
		
		}
  }
  
  return $form;
}

/**
 * Implements callback function print_schedule_form()
 */
function print_schedule_form($form, &$form_state){
  $session_id = (string)variable_get('essa_sid');
  $class_table = 'essa_'.$session_id.'_class_list';
  $timing_table = 'essa_'.$session_id.'_exam_timing';
  $master_exam_table = 'essa_'.$session_id.'_exam_master';
  $grade_table = 'essa_'.$session_id.'_exam_grade_settings';
  $master_student_table = 'essa_'.$session_id.'_master_student_table';
  $op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
  $exam_status_table = 'essa_'.$session_id.'_exam_status';
  $term_table = 'essa_'.$session_id.'_exam_terms';
  $schedule_table = 'essa_'.$session_id.'_exam_schedule';
  
	$exams = db_query("SELECT * FROM {$master_exam_table}");
  foreach($exams as $exam){
    $flag = 0;
    $term_id = $exam->term;
    $exam_code = $exam->exam_code;
    if(variable_get($exam->term.$exam->exam_code.$form_state['values']['class'].'_result_generate_status') == '1'){
      $flag = 1;
    }
    if(variable_get($exam->term.'_'.$exam->exam_code.'_schedule_status') == 'publish' && $flag == 1){
	
			$output = '<html>';
			$output .= '<head>';
			$output .= '<style>';
			$output .= '
				table{
					border: 3px solid black;
					width: 11.5in;
				}
				th{
					background: #708090;
					color: WHITE;
				}
				td{
					padding: 7px;
				}
				#cer_footer{
					position: absolute;
					bottom:0.5cm;
					page-break-after: always;
				}
				
				@page { margin:0.1in 0.1in 0.1in 0.1in; }
			';
			$output .= '</style>';
			$output .= '</head>';
			$output .= '<body>';
			$output .= '<h3 style = "text-align:center;">Schedule for Exam - '.$exam_code.'</h3>';
			
			
			$subject_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
			$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec;", array(':t' => $term_id, ':ec' => $exam_code));
			foreach($schedule as $sc){
				$cls[] = $sc->class;
			}
			if(in_array($form_state['values']['class'], $cls)){
				$output .= '<h3>Class:- '.$form_state['values']['class'].'</h3>';
				$output .= '<table style="width:100%; text-align: center;">';
				$output .= '<tr>';
				$output .= '<th>Subject</th>';
				$output .= '<th>Date</th>';
				$output .= '<th>Sitting</th>';
				$output .= '<th>Time From</th>';
				$output .= '<th>Time To</th>';
				$output .= '</tr>';
			
			
				$subject_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
				$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $term_id, ':ec' => $exam_code, ':c' => $form_state['values']['class']));
				foreach($schedule as $sc){
					
					$subjects = db_query("SELECT * FROM {$subject_table} WHERE sub_id = :si;", array(':si' => $sc->subject));
					foreach($subjects as $sub){
						$sub_name = $sub->sub_name;
					}
					$date = date('d-m-Y', $sc->date);
					$time_from = date('H:i', $sc->time_from);
					$time_to = date('H:i', $sc->time_to);
					$output .= '<tr>';
					$output .= '<td>'.$sub_name.'</td>';
					$output .= '<td>'.$date.'</td>';
					$output .= '<td>'.$sc->sitting.'</td>';
					$output .= '<td>'.$time_from.'</td>';
					$output .= '<td>'.$time_to.'</td>';
					$output .= '</tr>';
				}
				
				$output .= '</table>';
				$output .= '<div id = "cer_footer"></div>';
			}
			
			$path_print = db_query("
				SELECT * from field_data_field_path;"
			);
			foreach($path_print as $path){
				$path_to_print_module = $path->field_path_value;
			}
			require_once($path_to_print_module);
			
			$page_size = 'A4';
			$po = 'landscape';
			
			
			
			$content = $output;
			$dompdf = new DOMPDF;
			$dompdf->load_html($output);
			$dompdf->set_paper($page_size, $po);
			$dompdf->render();
			// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
			$dompdf->stream('['.$exam_code."]Schedule.pdf");
			
		}
	}
}


/**
 * Implements callback function print_schedule_form()
 */
function print_re_exam_schedule_form($form, &$form_state){
  $session_id = (string)variable_get('essa_sid');
  $class_table = 'essa_'.$session_id.'_class_list';
  $timing_table = 'essa_'.$session_id.'_exam_timing';
  $master_exam_table = 'essa_'.$session_id.'_exam_master';
  $grade_table = 'essa_'.$session_id.'_exam_grade_settings';
  $master_student_table = 'essa_'.$session_id.'_master_student_table';
  $op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
  $exam_status_table = 'essa_'.$session_id.'_exam_status';
  $term_table = 'essa_'.$session_id.'_exam_terms';
  $schedule_table = 'essa_'.$session_id.'_exam_schedule';
  
	$exams = db_query("SELECT * FROM {$master_exam_table}");
  foreach($exams as $exam){
		$flag2 = 0;
    $term_id = $exam->term;
    $exam_code = $exam->exam_code;
    if(variable_get($exam->term.$exam->exam_code.$form_state['values']['class'].'_result_generate_status') == '1'){
      $flag2 = 1;
    }
    if(variable_get($exam->term.'_'.$exam->exam_code.'_re_exam_schedule_status') == 'publish' && $flag2 == 1){
	
			$output = '<html>';
			$output .= '<head>';
			$output .= '<style>';
			$output .= '
				table{
					border: 3px solid black;
					width: 11.5in;
				}
				th{
					background: #708090;
					color: WHITE;
				}
				td{
					padding: 7px;
				}
				#cer_footer{
					position: absolute;
					bottom:0.5cm;
					page-break-after: always;
				}
				
				@page { margin:0.1in 0.1in 0.1in 0.1in; }
			';
			$output .= '</style>';
			$output .= '</head>';
			$output .= '<body>';
			$output .= '<h3 style = "text-align:center;">Schedule for '.$exam->exam_code.' Re-Exam.</h3>';
			
			
			$subject_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
			$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec;", array(':t' => $exam->term, ':ec' => 're_'.$exam->exam_code));
			foreach($schedule as $sc){
				$cls[] = $sc->class;
			}
			if(in_array($form_state['values']['class'], $cls)){
				$output .= '<h3>Class:- '.$form_state['values']['class'].'</h3>';
				$output .= '<table style="width:100%; text-align: center;">';
				$output .= '<tr>';
				$output .= '<th>Subject</th>';
				$output .= '<th>Date</th>';
				$output .= '<th>Sitting</th>';
				$output .= '<th>Time From</th>';
				$output .= '<th>Time To</th>';
				$output .= '</tr>';
			
			
				$subject_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
				$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $exam->term, ':ec' => 're_'.$exam->exam_code, ':c' => $form_state['values']['class']));
				foreach($schedule as $sc){
					
					$subjects = db_query("SELECT * FROM {$subject_table} WHERE sub_id = :si;", array(':si' => $sc->subject));
					foreach($subjects as $sub){
						$sub_name = $sub->sub_name;
					}
					$date = date('d-m-Y', $sc->date);
					$time_from = date('H:i', $sc->time_from);
					$time_to = date('H:i', $sc->time_to);
					$output .= '<tr>';
					$output .= '<td>'.$sub_name.'</td>';
					$output .= '<td>'.$date.'</td>';
					$output .= '<td>'.$sc->sitting.'</td>';
					$output .= '<td>'.$time_from.'</td>';
					$output .= '<td>'.$time_to.'</td>';
					$output .= '</tr>';
				}
				
				$output .= '</table>';
				$output .= '<div id = "cer_footer"></div>';
			}
			
			$path_print = db_query("
				SELECT * from field_data_field_path;"
			);
			foreach($path_print as $path){
				$path_to_print_module = $path->field_path_value;
			}
			require_once($path_to_print_module);
			
			$page_size = 'A4';
			$po = 'landscape';
			
			
			
			$content = $output;
			$dompdf = new DOMPDF;
			$dompdf->load_html($output);
			$dompdf->set_paper($page_size, $po);
			$dompdf->render();
			// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
			$dompdf->stream('['.$exam->exam_code."] Re-Exam Schedule.pdf");
			
		}
	}
  
}

/**
 *Theme function theme_publish_schedule_table()
 */
function theme_student_schedule_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  
  
  $header = array(t('Subject'),t('Date'), t('Sitting'), t('Time from'), t('Time to'));
    
  
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