<?php
/**
 * Implements callback function print_schedule()
 */
function print_schedule($form = array(), &$form_state, $term_id, $exam_code){
	
	$form['back'] = array(
		'#type' => 'markup',
		'#markup' => '<p class = "back_button"><a href="javascript:history.go(-1)">Back</a></p>',
	);
	
	$session_id = (string)variable_get('essa_sid');
	$class_list_table = 'essa_'.$session_id.'_class_list';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$schedule_table = 'essa_'.$session_id.'_exam_schedule';
	
	
	$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec;", array(':t' => $term_id, ':ec' => $exam_code));
	foreach($schedule as $sc){
		$classes[] = $sc->class;
	}
	
	$classes = array_unique($classes);
	
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id,
	);
	
	$form['exam_code'] = array(
		'#type' => 'value',
		'#value' => $exam_code,
	);
	
	$form['print_class'] = array(
		'#type' => 'radios',
		'#title' => 'Print Schedule For',
		'#required' => TRUE,
		'#options' => drupal_map_assoc(array('Class-wise', 'All Classes')),
		'#default_value' => 'All Classes',
	);
	
	$form['class'] = array(
		'#type' => 'checkboxes',
		'#title' => 'Select Class',
		'#options' => drupal_map_assoc($classes),
		'#states' => array(
			'visible' => array(
				':input[name="print_class"]' => array('value' => 'Class-wise'),
			),
		),
	);
	
	$form['page_format'] = array(
		'#type' => 'radios',
		'#title' => 'Page Format',
		'#required' => TRUE,
		'#options' => drupal_map_assoc(array('Portrait', 'Landscape')),
		'#default_value' => 'Landscape',
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => t('Print Schedule'),
		'#submit' => array('print_schedule_submit')
	);
	
	return $form;
}
/**
 * Implements callback function print_schedule()
 */
function print_schedule_submit($form, &$form_state){
	//dsm($form_state);
	
	$session_id = (string)variable_get('essa_sid');
	$class_list_table = 'essa_'.$session_id.'_class_list';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$schedule_table = 'essa_'.$session_id.'_exam_schedule';
	
	if($form_state['values']['print_class'] == 'All Classes'){
	
		$class = db_query("SELECT * FROM {$master_exam_table} WHERE exam_code = :ec AND term =:t;", array(':ec' => $form_state['values']['exam_code'], ':t' => $form_state['values']['term_id']));
		foreach($class as $cl){
			$c_from = $cl->class_from;
			$c_to = $cl->class_to;
		}
		
		if($c_from == NULL){
			$cf_weight = 0;
		}else{
			$c_from_weight = db_query("SELECT * FROM {$class_list_table} WHERE class_id =:c;", array(':c' => $c_from));
			foreach($c_from_weight as $cfw){
				$cf_weight = $cfw->weight;
			}
		}
		
		if($c_to == NULL){
			$ct_weight = 16;
		}else{
			$c_to_weight = db_query("SELECT * FROM {$class_list_table} WHERE class_id =:c;", array(':c' => $c_to));
			foreach($c_to_weight as $ctw){
				$ct_weight = $ctw->weight;
			}
		}
		
		$class_list = db_query("SELECT * FROM {$class_list_table} WHERE weight BETWEEN $cf_weight AND $ct_weight ORDER BY weight");
		foreach($class_list as $c){
			$classes[] = $c->class_id;
		}
		
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
				border: 1px solid black;
			}
			td{
				padding: 7px;
				border: 1px solid black;
			}
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
			}
			
			@page { margin:0.1in 0.1in 0.1in 0.1in; }
		';
		$output .= '</style>';
		$output .= '</head>';
		$output .= '<body>';
		$output .= '<h3 style = "text-align:center;">Schedule for Exam - '.$form_state['values']['exam_code'].'</h3>';
		
		foreach($classes as $cl){
			$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
			$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec;", array(':t' => $form_state['values']['term_id'], ':ec' => $form_state['values']['exam_code']));
			foreach($schedule as $sc){
				$cls[] = $sc->class;
			}
			if(in_array($cl, $cls)){
				$output .= '<h3>Class:- '.$cl.'</h3>';
				$output .= '<table style="width:100%; text-align: center;">';
				$output .= '<tr>';
				$output .= '<th>Subject</th>';
				$output .= '<th>Date</th>';
				$output .= '<th>Sitting</th>';
				$output .= '<th>Time From</th>';
				$output .= '<th>Time To</th>';
				$output .= '</tr>';
			
			
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $form_state['values']['term_id'], ':ec' => $form_state['values']['exam_code'], ':c' => $cl));
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
		}
		
		$path_print = db_query("
			SELECT * from field_data_field_path;"
		);
		foreach($path_print as $path){
			$path_to_print_module = $path->field_path_value;
		}
		require_once($path_to_print_module);
		
		$page_size = 'A4';
		if($form_state['values']['page_format'] == 'Portrait'){
			$po = 'portrait';
		}else{
			$po = 'landscape';
		}
		
		
		$content = $output;
		$dompdf = new DOMPDF;
		$dompdf->load_html($output);
		$dompdf->set_paper($page_size, $po);
		$dompdf->render();
		// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
		$dompdf->stream('['.$form_state['values']['exam_code']."]Schedule.pdf");
	}else{
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
		$output .= '<h3 style = "text-align:center;">Schedule for Exam - '.$form_state['values']['exam_code'].'</h3>';
		
		foreach($form_state['values']['class'] as $cl){
			if($cl != '0'){
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec;", array(':t' => $form_state['values']['term_id'], ':ec' => $form_state['values']['exam_code']));
				foreach($schedule as $sc){
					$cls[] = $sc->class;
				}
				if(in_array($cl, $cls)){
					$output .= '<h3>Class:- '.$cl.'</h3>';
					$output .= '<table style="width:100%; text-align: center;">';
					$output .= '<tr>';
					$output .= '<th>Subject</th>';
					$output .= '<th>Date</th>';
					$output .= '<th>Sitting</th>';
					$output .= '<th>Time From</th>';
					$output .= '<th>Time To</th>';
					$output .= '</tr>';
				
				
					$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
					$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $form_state['values']['term_id'], ':ec' => $form_state['values']['exam_code'], ':c' => $cl));
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
			}
				
			$path_print = db_query("
				SELECT * from field_data_field_path;"
			);
			foreach($path_print as $path){
				$path_to_print_module = $path->field_path_value;
			}
			require_once($path_to_print_module);
			
			$page_size = 'A4';
			if($form_state['values']['page_format'] == 'Portrait'){
				$po = 'portrait';
			}else{
				$po = 'landscape';
			}
			
			
			$content = $output;
			$dompdf = new DOMPDF;
			$dompdf->load_html($output);
			$dompdf->set_paper($page_size, $po);
			$dompdf->render();
			// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
			$dompdf->stream('['.$form_state['values']['exam_code']."]Schedule.pdf");
		}
	
	}
	
}