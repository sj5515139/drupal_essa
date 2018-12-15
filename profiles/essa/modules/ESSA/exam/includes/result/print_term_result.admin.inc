<?php

function print_term_result($form, &$form_state, $term_id){
	$session_id = (string)variable_get('essa_sid');
	$session = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
	$master_staff_table = 'essa_'.$session_id.'_master_staff_table';
	$class_teacher_table = 'essa_'.$session_id.'_class_teacher';
	$full_marks_table = 'essa_'.$session_id.'_exam_full_marks';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$term_table = 'essa_'.$session.'_exam_terms';
	
	$class_list_table = 'essa_'.$session_id.'_class_list';
	$terms_table = 'essa_'.$session_id.'_exam_terms';
	$di_group_name_table = 'essa_'.$session_id.'_di_group_name';
	$di_group_section_table = 'essa_'.$session_id.'_di_group_section';
	$di_sa_table = 'essa_'.$session_id.'_di_sa';
	$di_indicators_table = 'essa_'.$session_id.'_di_indicators';
	$sub_names = array();
	global $user;
	
	$terms = db_query("SELECT * FROM {$term_table} where id = :t", array(':t' => $term_id));
	foreach($terms as $ex){
		$class_from = $ex->class_from;
		$class_to = $ex->class_to;
	}
	
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
	$option = array('--Select--');
	$classes = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
		array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
	foreach($classes as $c){
		$class_list[] = $c->class_id;
	}
	$class = array_merge($option,$class_list);
	//dsm($class);
	$form['print_class'] = array(
		'#type' => 'radios',
		'#title' => 'Print Report Card',
		'#required' => TRUE,
		'#options' => drupal_map_assoc(array('Class-wise', 'Student-wise')),
		'#default_value' => 'Class-wise',
	);
	
	$form['class'] = array(
		'#title' => 'Select a Class',
		'#type' => 'select',
		'#options' => drupal_map_assoc($class),
		'#ajax' => array(
			'event' => 'change',
			'callback' => 'display_sections_ajax',
			'wrapper' => 'sec_wrapper',
			'method' => 'replace',
			'effect' => 'fade',
		),
		'#states' => array(
			'visible' => array(
				':input[name="print_class"]' => array('value' => 'Class-wise'),
			),
		),
	);
	
	$form['adm_no'] = array(
		'#title' => 'Enter Adm No.',
		'#autocomplete_path' => 'exam_student_autocomplete',
		'#type' => 'textfield',
		'#ajax' => array(
			'event' => 'change',
			'callback' => 'display_print_ajax',
			'wrapper' => 'print_wrapper',
			'method' => 'replace',
			'effect' => 'fade',
		),
		'#states' => array(
			'visible' => array(
				':input[name="print_class"]' => array('value' => 'Student-wise'),
			),
		),
	);
	
	$form['sec_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "sec_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['print_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "print_wrapper">',
		'#suffix' => '</div>',
	);
	
	if(isset($form_state['values']['class']) && $form_state['values']['class'] != '--Select--'){
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
				'callback' => 'display_print_ajax',
				'wrapper' => 'print_wrapper',
				'method' => 'replace',
				'effect' => 'fade',
			),
			'#states' => array(
				'visible' => array(
					':input[name="print_class"]' => array('value' => 'Class-wise'),
				),
			),
		);
	}
	
	if(isset($form_state['values']['sec']) || (isset($form_state['values']['adm_no']) && $form_state['values']['adm_no'] != NULL)){
		$form['print_wrapper']['page_format'] = array(
			'#type' => 'radios',
			'#title' => 'Page Format',
			'#required' => TRUE,
			'#options' => drupal_map_assoc(array('Portrait', 'Landscape')),
			'#default_value' => 'Portrait',
		);
		
		$form['print_wrapper']['save'] = array(
			'#type' => 'submit',
			'#value' => 'Print',
		);
	}
	
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id
	);
	return $form;
}

/**
 *Implements validate function
 */
function print_term_result_validate($form, &$form_state){
	if($form_state['values']['print_class'] == 'Class-wise'){
		if(isset($form_state['values']['class']) && $form_state['values']['class'] == '--Select--'){
			form_set_error('class', 'Please select a class');
		}
	}else{
		if(isset($form_state['values']['adm_no']) && $form_state['values']['adm_no'] == NULL){
			form_set_error('class', 'Please enter a valid Admission No.');
		}
	}
}

/**
 *Implements submit function
 */
function print_term_result_submit($form, &$form_state){
	if($form_state['values']['page_format'] == 'Portrait'){
		$po = 'portrait';
	}else{
		$po = 'landscape';
	}
	require_once("profiles/essa/modules/dependencies/essa/print/lib/dompdf/dompdf_config.inc.php");
	$html = get_content($form, $form_state);
	$dompdf = new DOMPDF;
	$dompdf->load_html($html);
	$dompdf->set_paper($page_size, $po);
	$dompdf->render();
	// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
	$dompdf->stream('Report Card'.'_'.$form_state['input']['class'].'_'.$form_state['values']['sec'].".pdf", array('compress' => FALSE));
}

function get_content($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$grade_table = 'essa_'.$session_id.'_exam_grade_settings';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$term_id = $form_state['values']['term_id'];
	$op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
	$term_table = 'essa_'.$session_id.'_exam_terms';
	$class_list_table = 'essa_'.$session_id.'_class_list';
	$terms_table = 'essa_'.$session_id.'_exam_terms';
	$di_group_name_table = 'essa_'.$session_id.'_di_group_name';
	$di_group_section_table = 'essa_'.$session_id.'_di_group_section';
	$di_sa_table = 'essa_'.$session_id.'_di_sa';
	$di_indicators_table = 'essa_'.$session_id.'_di_indicators';
	$sub_names = array();
	global $user;
	if($form_state['values']['print_class'] == 'Class-wise'){
		$top = 0.2;
		$right = 0.2;
		$bottom = 0.2;
		$left = 0.2;
		$width = 8.3 - ((float)$right + (float)$left);
		$watermark_uri = variable_get('file_public_path', conf_path() . '/files/bg4.jpg');
		$w = $watermark_uri;
		
		$exams = db_query(
			"SELECT * from $master_exam_table where term = :ti;", array(':ti' => $term_id)
		);
		foreach($exams as $ex){
			// $class_from = $ex->class_from;
			// $class_to = $ex->class_to;
			// $c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_from));
			// foreach($c_from_weight as $cfw){
				// $cf_weight = $cfw->weight;
			// }
			// $c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_to));
			// foreach($c_to_weight as $ctw){
				// $ct_weight = $ctw->weight;
			// }
			// $classes = array();
			// $class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
				// array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
			// foreach($class_list as $c){
				// $classes[] = $c;
			// }
			$classes[] = $form_state['values']['class'];
			$section = $form_state['values']['sec'];
			foreach($classes as $cl){
				$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($ex->exam_code).'_'.$cl;
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$student_marks = db_query("SELECT * FROM {$marks_table} WHERE section = :s;", array(':s' => $section));
				foreach($student_marks as $sm){
					$subjects = db_query(
						"SELECT * from $subject_table;"
					);
					foreach($subjects as $subject){
						if($subject->type == 'Optional'){
							$op_students = db_query(
								"SELECT * from $op_subj_student_table where adm_no = :an and sub_id = :s;",
									array(':an' => $sm->adm_no, ':s' => $subject->sub_id)
							);
							foreach($op_students as $os){
								$cf_col = 'cf_'.$subject->sub_id;
								$term_total[$sm->adm_no][$subject->sub_id] = 0;
							}
						}else{
							$cf_col = 'cf_'.$subject->sub_id;
							$term_total[$sm->adm_no][$subject->sub_id] = 0;
						}
					}
				}
			}
		}
		
		$exam_count = 0;
		$weight_total = 0;
		$exams = db_query(
			"SELECT * from $master_exam_table where term = :ti;", array(':ti' => $term_id)
		);
		foreach($exams as $ex){
			$exam_count++;
			$exam_name[$ex->exam_code] = $ex->weight;
			$weight_total = $weight_total+$ex->weight;
			// $class_from = $ex->class_from;
			// $class_to = $ex->class_to;
			// $c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_from));
			// foreach($c_from_weight as $cfw){
				// $cf_weight = $cfw->weight;
			// }
			// $c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_to));
			// foreach($c_to_weight as $ctw){
				// $ct_weight = $ctw->weight;
			// }
			// $classes = array();
			// $class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
				// array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
			// foreach($class_list as $c){
				// $classes[] = $c;
			// }
			$classes[] = $form_state['values']['class'];
			$section = $form_state['values']['sec'];
			foreach($classes as $cl){
				$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($ex->exam_code).'_'.$cl;
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$student_marks = db_query("SELECT * FROM {$marks_table} WHERE section = :s;", array(':s' => $section));
				foreach($student_marks as $sm){
					$sub_count = 0;
					$subjects = db_query(
						"SELECT * from $subject_table;"
					);
					foreach($subjects as $subject){
						if($subject->type == 'Optional'){
							$flag = 0;
							$op_students = db_query(
								"SELECT * from $op_subj_student_table where adm_no = :an and sub_id = :s;",
									array(':an' => $sm->adm_no, ':s' => $subject->sub_id)
							);
							foreach($op_students as $os){
								$sub_col = $subject->sub_id;
								$cf_col = 'cf_'.$subject->sub_id;
								$term_total[$sm->adm_no][$subject->sub_id] = $term_total[$sm->adm_no][$subject->sub_id] + round($sm->$cf_col);
								$data[$sm->adm_no][$sub_col][$ex->exam_code] = round($sm->$cf_col);
								$header[$sm->adm_no][$sub_col][$ex->exam_code] = $ex->exam_code.'#'.$subject->sub_name;
								$flag = 1;
								$sub_count++;
								$ex_sub[$sm->adm_no][$subject->sub_id] = $subject->sub_name;
								$data_gp[$sm->adm_no][$ex->exam_code][$sub_col] = round($sm->$cf_col);
							}
						}else{
							$sub_count++;
							$sub_col = $subject->sub_id;
							$cf_col = 'cf_'.$subject->sub_id;
							$term_total[$sm->adm_no][$subject->sub_id] = $term_total[$sm->adm_no][$subject->sub_id] + round($sm->$cf_col);
							$data[$sm->adm_no][$sub_col][$ex->exam_code] = round($sm->$cf_col);
							$data_gp[$sm->adm_no][$ex->exam_code][$sub_col] = round($sm->$cf_col);
							$header[$sm->adm_no][$sub_col][$ex->exam_code] = $ex->exam_code.'#'.$subject->sub_name;
							$ex_sub[$sm->adm_no][$subject->sub_id] = $subject->sub_name;
						}
					}
				}
			}
		}
		
		$terms = db_query(
			"SELECT * from $term_table where id = :ti;", array(':ti' => $term_id)
		);
		foreach($terms as $term){
			$term_name = $term->term_name;
		}
		//$adm_no = str_replace('/','#',$st->adm_no);
		//$graph = variable_get('file_public_path', conf_path().'/files/exam/'.'1'.'/'.$adm_no.'.png');
		//dsm($graph);
		$content = '<html>';
		$content .= '<head><style>
			#marksheet{
				table-layout: fixed;
				width: '.$width.'in;
				margin-top: 0.5in;
				margin-bottom: 0.5in;
			}
			
			.marks_table{
				table-layout: fixed;
				width: '.$width.'in;
				margin-top: 0.5in;
				margin-bottom: 0.07in;
			}
			
			#marksheet th{
				background: #D2691E;
				padding: 0.05in;
				color: WHITE;
				border: 1px white solid;
			}
			
			#marksheet td{
				padding: 15px;
				text-align: center;
			}
			
			img{
				width:100%;
			}
					
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
				page-break-after: always;
			}
			
			#session{
				text-align: center;
				background: #4B0082;
				padding-top: 0.08in;
				padding-bottom: 0.08in;
				width: 50%;
				color: WHITE;
			}
			
			body {
				background: none;
				background-repeat: no-repeat;
				background-attachment: fixed;
				background-position: center;
				background-color:#FFFAF0;
			}
			@page { margin: '.$top.'in '.$right.'in '.$bottom.'in '.$left.'in; }
			 
		</style></head>';
		$content .= '<body>';
		
		foreach ($data as $adm_no => $rec){
			$content .= '<div>';
			$header = variable_get('file_public_path', conf_path() . '/files/header.jpg');
			$content .= '<img src = "'.$header.'">';
			
			$content .= '<div id = "session" style= "margin-left: 26%; font-size: 80px;">Session - <b>'.str_replace('_','-',$session_id).'</b></div>';
			$students = db_query(
				"SELECT * from $master_student_table where adm_no = :an;", array(':an' => $adm_no)
			);
			foreach($students as $st){
				$content .= '</table>';
				$content .= '<table style = "padding: 0.06in;" class = "marks_table">';
				$content .= '<tr>';
				$content .= '<td colspan = "3"><p style= " font-size: 60px;">Name of Student - <b>'.$st->student_name.'</b></p></td>';
				$content .= '</tr>';
				$content .= '<tr>';
				$content .= '<td style= " font-size: 60px;">Class - <b>'.$st->class.'</b></td>';
				$content .= '<td style= " font-size: 60px;">Sec - <b>'.$st->section.'</b></td>';
				$content .= '<td style= " font-size: 60px;">Roll No. - <b>'.$st->roll_no.'</b></td>';
				$content .= '</tr>';
				$content .= '<tr>';
				$content .= '<td colspan = "3"><p style= " font-size: 60px;">Admission No. - <b>'.$st->adm_no.'</b></p></td>';
				$content .= '</tr>';
				$content .= '</table>';
				$content .= '<div style = "page-break-after: always;"></div>';
			}
			
			
			$di_groups = db_query("SELECT * FROM {$di_group_name_table}");
			foreach($di_groups as $dig){
				$c_from = $dig->class_from;
				$c_to = $dig->class_to;
				
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
				
				if(in_array($st->class, $classes)){
					$di_group_name = $dig->group_name;
					$di_group_id = $dig->id;
				}
			}
			$di_group_sections = db_query("SELECT * FROM {$di_group_section_table} WHERE group_id = :gi;", array(':gi' => $di_group_id));
			$item = 1;
			$exams = db_query("SELECT * FROM {$master_exam_table} WHERE term = :t AND di_status = :ds;", array(':t' => $term_id, ':ds' => '1'));
			foreach($exams as $exam){
				foreach($di_group_sections as $digs){dsm($item);	
					if($item != 1){
						$content .= '<div style = "page-break-after: always;"></div>';
					}
					$section_id = $digs->id;
					$content .= '<table style = "width:100%;"><tr><td style = "width:15%; padding-left:20px;"><h2 style ="border: 1px solid green; background-color:green; border-radius:10px; color:White;">'.$digs->section_id.'</h2></td><td style = "padding-left:20px; width:85%;"><h2 style ="color:red;">:'.$digs->section_name.'</h2></td></tr></table>';
					//$content .= '<div style = "display:flex;"><h2 style =" border: 1px solid green; background-color:green; border-radius:10px; color:White;">&nbsp;&nbsp&nbsp;'.$digs->section_id.'&nbsp;&nbsp;</h2>&nbsp;&nbsp;<h2 style ="color:red;">:&nbsp;&nbsp;'.$digs->section_name.'</h2></div>';
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if($digs->is_marksheet == 1){
						
						$content .= '<table style = "border: 0.02in inset black;" class = marks_table id = "marksheet">';
						$content .= '<tr>';
						$content .= '<th>S.No</th>';
						$content .= '<th></th>';
						$content .= '<th colspan = "'.$exam_count.'">'.$term_name.'</th>';
						$content .= '<th></th>';
						$content .= '</tr>';
						
						$content .= '<tr>';
						$content .= '<th></th>';
						$content .= '<th>Subjects</th>';
						foreach($exam_name as $en => $weight){
							$content .= '<th>'.$en.'('.$weight.')'.'</th>';
						}
						$content .= '<th>Total</th>';
						$content .= '</tr>';
						$sno = 1;
						foreach($rec as $sub_id => $line){
							$content .= '<tr>';
							$content .= '<td>'.$sno.'</td>';
							
							$students = db_query(
								"SELECT * from $master_student_table where adm_no = :an;", array(':an' => $adm_no)
							);
							foreach($students as $st){
								$subject_table = 'essa_'.$session_id.'_subjects_'.$st->class;
								$subjects = db_query(
									"SELECT * from $subject_table where sub_id = :si;", array(':si' => $sub_id)
								);
								foreach($subjects as $subject){
									$content .= '<th>'.$subject->sub_name.'</th>';
								}
							}$total = 0;
							foreach($line as $exam_code => $marks){
								$content .= '<td>'.$marks.'</td>';
								$total = $total+round($marks);
							}
							$content .= '<td>'.$total.'</td>';
							
							$content .= '</tr>';
							$sno++;
						}
						
						$content .= '</table>';
						$gr_adm_no = str_replace('/','#',$adm_no);
						$graph_path = variable_get('file_public_path', conf_path() . '/files/exam/'.$term_id.'/'.$gr_adm_no.'.png');
						$content .= '<div><img src = "'.$graph_path.'"></div>';	
						//$content .= '<div><img src = "'.$graph_path.'" style = "page-break-after: always;"></div>';	
						
					}
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					$di_sub_sections = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si;", array(':gi' => $di_group_id, ':si' => $section_id));
					$sub_section = NULL;
					foreach($di_sub_sections as $diss){
						if($sub_section != $diss->sub_section_title){
							$content .= '<table style = "width:100%;"><tr	><td style = "width:12%;"><h2 style ="color:red;">'.$diss->sub_section.'</h2></td><td style = "width:88%; padding-left:30px;"><h2 style ="color:blue;">:'.$diss->sub_section_title.'</h2></td></tr></table>';
							//$content .= '<div style = "display:flex;"><h2 style ="color:red;">'.$diss->sub_section.'</h2>&nbsp;&nbsp;&nbsp;<h2 style ="color:blue;">:&nbsp;&nbsp;'.$diss->sub_section_title.'</h2></div>';
							$content .= '<table style ="width:100%; border:1px solid red; background-color:#F5DF6D;">';
							$content .= '<tr>';
							$content .= '<th style ="color:yellow; background-color:green; width:15%">S.No.</th>';
							$content .= '<th style ="color:White; background-color:maroon; width:65%">Descriptive Indicators</th>';
							$content .= '<th style ="color:yellow; background-color:green; width:20%"	>Grade</th>';
							$content .= '</tr>';
						
							$serial_nos = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND sub_section_title = :sst;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sst' => $diss->sub_section_title));
							foreach($serial_nos as $sn){
								$content .= '<tr>
								<td style ="border:1px solid red; float:top; text-align:centre; background-color: rgba(236, 164, 45, 0.71);"><b>'.$sn->serial_no.'</b></td>
								<td style ="border:1px solid red;">
								<table style ="width:100%;">
								<tr><td style ="border:1px solid green; text-align:centre; color:purple; background-color:#F3BFF3; width:15%"><b>Grade</b></td><td style ="border:1px solid green; color:purple; background-color:#F3BFF3; width:85%; padding-left:30px;	"><b>'.$sn->title.'</b></td></tr>';
								$indicators = db_query("SELECT * FROM {$di_indicators_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND serial_no = :sn;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sn' => $sn->serial_no));
								foreach($indicators as $indic){
									$content .= '<tr>
									<td style ="border:1px solid green; color:green; text-align:center;"><b>'.$indic->grade.'</b></td>
									<td style ="border:1px solid green; text-align:left; padding-left:30px;">'.$indic->di.'</td>
									</tr>';
								}
								$content .= '</table></td>';
								$content .= '<td style ="border:1px solid red;">
								<table style ="width:100%; float:top; border:1px solid red;">
								<tr>';
						
								$di_grade_table = 'essa_'.$session_id.'_exam_'.$term->	id.'_'.clean_exam_code_string($exam->exam_code).'_'.$st->class.'_di';
								$di_field = $di_group_id.$section_id.clean_exam_code_string($diss->sub_section).$sn->serial_no;
								$content .= '<th style = "background-color: #0D0D2B; color:white;">'.$exam->exam_code.'</th></tr>';
								$student_grades = db_query("SELECT * FROM {$di_grade_table} WHERE adm_no = :an;", array(':an' => $adm_no));
								foreach($student_grades as $stg){
									$content .= '<tr>
									<td style ="text-align:center; color:black;">'.$stg->$di_field.'</td>
									</tr>';
								}
								
								$content .= '</table>
								</td>';
								$content .= '</tr>';
							}
							$content .= '</table></br>';
							$flag= 0;
							$serial_nos = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND sub_section_title = :sst;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sst' => $diss->sub_section_title));
							foreach($serial_nos as $sn){
								$di_sa = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND serial_no = :sn;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sn' => $sn->serial_no));
								foreach($di_sa as $disa){
									if($disa->sa != NULL){
										$flag=1;
									}
								}
							}
							
							if($flag == 1){
								$content .= '<table style = width:100%;><tr><td style = "width:22%;"><h4 style ="border: 1px solid purple; background-color:purple; border-radius:10px; color:White;">Suggested Activities : </h4></td></tr>';
							}
							
							$serial_nos = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND sub_section_title = :sst;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sst' => $diss->sub_section_title));
							foreach($serial_nos as $sn){
								$di_sa = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND serial_no = :sn;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sn' => $sn->serial_no));
								foreach($di_sa as $disa){
									if($disa->sa != NULL){
										$content .= '<tr><td style ="color:red; width:auto;"><h5><b><i>'.$disa->title.':</i></b></h5></td><td><h5>'.$disa->sa.'<h5></td></tr>';
									}
								}
							}
							$content .= '</table>';
						}
						$sub_section = $diss->sub_section_title;
					}
					$item++;
				}
			}
			$content .= '<div style = "page-break-after: always;"></div>';
			$content .= '</div>';
		}
		$content .= '</body>';
		$content .= '</html>';
	}else{
		$adm_no = $form_state['values']['adm_no'];
		$term_id = $form_state['values']['term_id'];
		
		$st_class = db_query("SELECT * FROM {$master_student_table} WHERE adm_no = :an;", array(':an'  => $adm_no));
		foreach($st_class as $sc){
			$class = $sc->class;
		}
		
		$top = 0.2;
		$right = 0.2;
		$bottom = 0.2;
		$left = 0.2;
		$width = 8.3 - ((float)$right + (float)$left);
		$watermark_uri = variable_get('file_public_path', conf_path() . '/files/bg4.jpg');
		$w = $watermark_uri;
		
		$exams = db_query(
			"SELECT * from $master_exam_table where term = :ti;", array(':ti' => $term_id)
		);
		foreach($exams as $ex){
			$classes[] = $class;
			foreach($classes as $cl){
				$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($ex->exam_code).'_'.$cl;
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$student_marks = db_query("SELECT * FROM {$marks_table}  WHERE adm_no = :an;", array(':an'  => $adm_no));
				foreach($student_marks as $sm){
					$subjects = db_query(
						"SELECT * from $subject_table;"
					);
					foreach($subjects as $subject){
						if($subject->type == 'Optional'){
							$op_students = db_query(
								"SELECT * from $op_subj_student_table where adm_no = :an and sub_id = :s;",
									array(':an' => $sm->adm_no, ':s' => $subject->sub_id)
							);
							foreach($op_students as $os){
								$cf_col = 'cf_'.$subject->sub_id;
								$term_total[$sm->adm_no][$subject->sub_id] = 0;
							}
						}else{
							$cf_col = 'cf_'.$subject->sub_id;
							$term_total[$sm->adm_no][$subject->sub_id] = 0;
						}
					}
				}
			}
		}
		
		$exam_count = 0;
		$weight_total = 0;
		$exams = db_query(
			"SELECT * from $master_exam_table where term = :ti;", array(':ti' => $term_id)
		);
		foreach($exams as $ex){
			$exam_count++;
			$exam_name[$ex->exam_code] = $ex->weight;
			$weight_total = $weight_total+$ex->weight;
			$classes[] = $class;
			foreach($classes as $cl){
				$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($ex->exam_code).'_'.$cl;
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$student_marks = db_query("SELECT * FROM {$marks_table} WHERE adm_no = :an;", array(':an'  => $adm_no));
				foreach($student_marks as $sm){
					$sub_count = 0;
					$subjects = db_query(
						"SELECT * from $subject_table;"
					);
					foreach($subjects as $subject){
						if($subject->type == 'Optional'){
							$flag = 0;
							$op_students = db_query(
								"SELECT * from $op_subj_student_table where adm_no = :an and sub_id = :s;",
									array(':an' => $sm->adm_no, ':s' => $subject->sub_id)
							);
							foreach($op_students as $os){
								$sub_col = $subject->sub_id;
								$cf_col = 'cf_'.$subject->sub_id;
								$term_total[$sm->adm_no][$subject->sub_id] = $term_total[$sm->adm_no][$subject->sub_id] + round($sm->$cf_col);
								$data[$sm->adm_no][$sub_col][$ex->exam_code] = round($sm->$cf_col);
								$header[$sm->adm_no][$sub_col][$ex->exam_code] = $ex->exam_code.'#'.$subject->sub_name;
								$flag = 1;
								$sub_count++;
								$ex_sub[$sm->adm_no][$subject->sub_id] = $subject->sub_name;
								$data_gp[$sm->adm_no][$ex->exam_code][$sub_col] = round($sm->$cf_col);
							}
						}else{
							$sub_count++;
							$sub_col = $subject->sub_id;
							$cf_col = 'cf_'.$subject->sub_id;
							$term_total[$sm->adm_no][$subject->sub_id] = $term_total[$sm->adm_no][$subject->sub_id] + round($sm->$cf_col);
							$data[$sm->adm_no][$sub_col][$ex->exam_code] = round($sm->$cf_col);
							$data_gp[$sm->adm_no][$ex->exam_code][$sub_col] = round($sm->$cf_col);
							$header[$sm->adm_no][$sub_col][$ex->exam_code] = $ex->exam_code.'#'.$subject->sub_name;
							$ex_sub[$sm->adm_no][$subject->sub_id] = $subject->sub_name;
						}
					}
				}
			}
		}
		
		$terms = db_query(
			"SELECT * from $term_table where id = :ti;", array(':ti' => $term_id)
		);
		foreach($terms as $term){
			$term_name = $term->term_name;
		}
		//$adm_no = str_replace('/','#',$st->adm_no);
		//$graph = variable_get('file_public_path', conf_path().'/files/exam/'.'1'.'/'.$adm_no.'.png');
		//dsm($graph);
		$content = '<html>';
		$content .= '<head><style>
			#marksheet{
				table-layout: fixed;
				width: '.$width.'in;
				margin-top: 0.5in;
				margin-bottom: 0.5in;
			}
			
			.marks_table{
				table-layout: fixed;
				width: '.$width.'in;
				margin-top: 0.5in;
				margin-bottom: 0.07in;
			}
			
			#marksheet th{
				background: #D2691E;
				padding: 0.05in;
				color: WHITE;
				border: 1px white solid;
			}
			
			#marksheet td{
				padding: 15px;
				text-align: center;
			}
			
			img{
				width:100%;
			}
					
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
				page-break-after: always;
			}
			
			#session{
				text-align: center;
				background: #4B0082;
				padding-top: 0.08in;
				padding-bottom: 0.08in;
				width: 50%;
				color: WHITE;
			}
			
			body {
				background: none;
				background-repeat: no-repeat;
				background-attachment: fixed;
				background-position: center;
				background-color:#FFFAF0;
			}
			@page { margin: '.$top.'in '.$right.'in '.$bottom.'in '.$left.'in; }
			 
		</style></head>';
		$content .= '<body>';
		
		foreach ($data as $adm_no => $rec){
			$header = variable_get('file_public_path', conf_path() . '/files/header.jpg');
			$content .= '<img src = "'.$header.'">';
			
			$content .= '<div id = "session" style= "margin-left: 26%; font-size: 80px;">Session - <b>'.str_replace('_','-',$session_id).'</b></div>';
			$students = db_query(
				"SELECT * from $master_student_table where adm_no = :an;", array(':an' => $adm_no)
			);
			foreach($students as $st){
				$address = NULL;
				if($st->r_line1 != NULL){
					$address = $st->r_line1;
				}
				if($st->r_line2 != NULL){
					$address = $st->r_line1.', '.$st->r_line2;
				}
				if($st->r_city != NULL){
					$address = $st->r_line1.', '.$st->r_line2.', '.$st->r_city;
				}
				if($st->r_state != NULL){
					$address = $st->r_line1.', '.$st->r_line2.', '.$st->r_city.', '.$st->r_state;
				}
				if($st->r_pincode != NULL){
					$address = $st->r_line1.', '.$st->r_line2.', '.$st->r_city.', '.$st->r_state.', '.$st->r_pincode;
				}
				$content .= '</table>';
				$content .= '<table style = "padding: 0.06in;" class = "marks_table">';
				$content .= '<tr>';
				$content .= '<td colspan = "3"><p style= " font-size: 60px;">Name of Student - <b>'.$st->student_name.'</b></p></td>';
				$content .= '</tr>';
				$content .= '<tr>';
				$content .= '<td style= " font-size: 60px;">Class - <b>'.$st->class.'</b></td>';
				$content .= '<td style= " font-size: 60px;">Sec - <b>'.$st->section.'</b></td>';
				$content .= '<td style= " font-size: 60px;">Roll No. - <b>'.$st->roll_no.'</b></td>';
				$content .= '</tr>';
				$content .= '<tr>';
				$content .= '<td colspan = "3"><p style= " font-size: 60px;">Admission No. - <b>'.$st->adm_no.'</b></p></td>';
				$content .= '</tr>';
				$content .= '<tr>';
				$content .= '<td colspan = "3"><p style= " font-size: 60px;">Date of Birth - <b>'.$st->dob.'</b></p></td>';
				$content .= '</tr>';
				$content .= '<tr>';
				$content .= '<td colspan = "3"><p style= " font-size: 60px;">'."Mother's".' Name - <b>'.$st->mother_name.'</b></p></td>';
				$content .= '</tr>';
				$content .= '<tr>';
				$content .= '<td colspan = "3"><p style= " font-size: 60px;">'."Father's".' Name - <b>'.$st->father_name.'</b></p></td>';
				$content .= '</tr>';
				$content .= '<tr>';
				$content .= '<td colspan = "3"><p style= " font-size: 60px;">Residential Address - <b>'.$st->address.'</b></p></td>';
				$content .= '</tr>';
				$content .= '<tr>';
				$content .= '<td colspan = "3"><p style= " font-size: 60px;">Mobile No. - <b>'.$st->r_phone.'</b></p></td>';
				$content .= '</tr>';
				$content .= '<tr>';
				$content .= '<td colspan = "3"><p style= " font-size: 60px;">Email Id - <b>'.$st->s_email.'</b></p></td>';
				$content .= '</tr>';
				$content .= '</table>';
				$content .= '<div style = "page-break-after: always;"></div>';
			}
			
			
			$di_groups = db_query("SELECT * FROM {$di_group_name_table}");
			foreach($di_groups as $dig){
				$c_from = $dig->class_from;
				$c_to = $dig->class_to;
				
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
				
				if(in_array($st->class, $classes)){
					$di_group_name = $dig->group_name;
					$di_group_id = $dig->id;
				}
			}
			$di_group_sections = db_query("SELECT * FROM {$di_group_section_table} WHERE group_id = :gi;", array(':gi' => $di_group_id));
			$item = 1;
			$exams = db_query("SELECT * FROM {$master_exam_table} WHERE term = :t AND di_status = :ds;", array(':t' => $term_id, ':ds' => '1'));
			foreach($exams as $exam){
				foreach($di_group_sections as $digs){	
					if($item != 1){
						$content .= '<div style = "page-break-after: always;"></div>';
					}
					$section_id = $digs->id;
					$content .= '<table style = "width:100%;"><tr><td style = "width:15%; padding-left:20px;"><h2 style ="border: 1px solid green; background-color:green; border-radius:10px; color:White;">'.$digs->section_id.'</h2></td><td style = "padding-left:20px; width:85%;"><h2 style ="color:red;">:'.$digs->section_name.'</h2></td></tr></table>';
					//$content .= '<div style = "display:flex;"><h2 style =" border: 1px solid green; background-color:green; border-radius:10px; color:White;">&nbsp;&nbsp&nbsp;'.$digs->section_id.'&nbsp;&nbsp;</h2>&nbsp;&nbsp;<h2 style ="color:red;">:&nbsp;&nbsp;'.$digs->section_name.'</h2></div>';
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if($digs->is_marksheet == 1){
						
						$content .= '<table style = "border: 0.02in inset black;" class = marks_table id = "marksheet">';
						$content .= '<tr>';
						$content .= '<th>S.No</th>';
						$content .= '<th></th>';
						$content .= '<th colspan = "'.$exam_count.'">'.$term_name.'</th>';
						$content .= '<th></th>';
						$content .= '</tr>';
						
						$content .= '<tr>';
						$content .= '<th></th>';
						$content .= '<th>Subjects</th>';
						foreach($exam_name as $en => $weight){
							$content .= '<th>'.$en.'('.$weight.')'.'</th>';
						}
						$content .= '<th>Total</th>';
						$content .= '</tr>';
						$sno = 1;
						$total = 0;
						foreach($rec as $sub_id => $line){
							$content .= '<tr>';
							$content .= '<td>'.$sno.'</td>';
							
							$students = db_query(
								"SELECT * from $master_student_table where adm_no = :an;", array(':an' => $adm_no)
							);
							foreach($students as $st){
								$subject_table = 'essa_'.$session_id.'_subjects_'.$st->class;
								$subjects = db_query(
									"SELECT * from $subject_table where sub_id = :si;", array(':si' => $sub_id)
								);
								foreach($subjects as $subject){
									$content .= '<th>'.$subject->sub_name.'</th>';
								}
							}$total = 0;
							foreach($line as $exam_code => $marks){
								$content .= '<td>'.$marks.'</td>';
								$total = $total+round($marks);
							}
							$content .= '<td>'.$total.'</td>';
							
							$content .= '</tr>';
							$sno++;
						}
						
						$content .= '</table>';
						$gr_adm_no = str_replace('/','#',$adm_no);
						$graph_path = variable_get('file_public_path', conf_path() . '/files/exam/'.$term_id.'/'.$gr_adm_no.'.png');
						$content .= '<div><img src = "'.$graph_path.'"></div>';	
						//$content .= '<div><img src = "'.$graph_path.'" style = "page-break-after: always;"></div>';	
						
					}
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					$di_sub_sections = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si;", array(':gi' => $di_group_id, ':si' => $section_id));
					$sub_section = NULL;
					foreach($di_sub_sections as $diss){
						if($sub_section != $diss->sub_section_title){
							$content .= '<table style = "width:100%;"><tr	><td style = "width:12%;"><h2 style ="color:red;">'.$diss->sub_section.'</h2></td><td style = "width:88%; padding-left:30px;"><h2 style ="color:blue;">:'.$diss->sub_section_title.'</h2></td></tr></table>';
							//$content .= '<div style = "display:flex;"><h2 style ="color:red;">'.$diss->sub_section.'</h2>&nbsp;&nbsp;&nbsp;<h2 style ="color:blue;">:&nbsp;&nbsp;'.$diss->sub_section_title.'</h2></div>';
							$content .= '<table style ="width:100%; border:1px solid red; background-color:#F5DF6D;">';
							$content .= '<tr>';
							$content .= '<th style ="color:yellow; background-color:green; width:15%">S.No.</th>';
							$content .= '<th style ="color:White; background-color:maroon; width:65%">Descriptive Indicators</th>';
							$content .= '<th style ="color:yellow; background-color:green; width:20%"	>Grade</th>';
							$content .= '</tr>';
						
							$serial_nos = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND sub_section_title = :sst;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sst' => $diss->sub_section_title));
							foreach($serial_nos as $sn){
								$content .= '<tr>
								<td style ="border:1px solid red; float:top; text-align:centre; background-color: rgba(236, 164, 45, 0.71);"><b>'.$sn->serial_no.'</b></td>
								<td style ="border:1px solid red;">
								<table style ="width:100%;">
								<tr><td style ="border:1px solid green; text-align:centre; color:purple; background-color:#F3BFF3; width:15%"><b>Grade</b></td><td style ="border:1px solid green; color:purple; background-color:#F3BFF3; width:85%; padding-left:30px;	"><b>'.$sn->title.'</b></td></tr>';
								$indicators = db_query("SELECT * FROM {$di_indicators_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND serial_no = :sn;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sn' => $sn->serial_no));
								foreach($indicators as $indic){
									$content .= '<tr>
									<td style ="border:1px solid green; color:green; text-align:center;"><b>'.$indic->grade.'</b></td>
									<td style ="border:1px solid green; text-align:left; padding-left:30px;">'.$indic->di.'</td>
									</tr>';
								}
								$content .= '</table></td>';
								$content .= '<td style ="border:1px solid red;">
								<table style ="width:100%; float:top; border:1px solid red;">
								<tr>';
						
								$di_grade_table = 'essa_'.$session_id.'_exam_'.$term->	id.'_'.clean_exam_code_string($exam->exam_code).'_'.$st->class.'_di';
								$di_field = $di_group_id.$section_id.clean_exam_code_string($diss->sub_section).$sn->serial_no;
								$content .= '<th style = "background-color: #0D0D2B; color:white;">'.$exam->exam_code.'</th></tr>';
								$student_grades = db_query("SELECT * FROM {$di_grade_table} WHERE adm_no = :an;", array(':an' => $adm_no));
								foreach($student_grades as $stg){
									$content .= '<tr>
									<td style ="text-align:center; color:black;">'.$stg->$di_field.'</td>
									</tr>';
								}
								
								$content .= '</table>
								</td>';
								$content .= '</tr>';
							}
							$content .= '</table></br>';
							$flag= 0;
							$serial_nos = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND sub_section_title = :sst;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sst' => $diss->sub_section_title));
							foreach($serial_nos as $sn){
								$di_sa = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND serial_no = :sn;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sn' => $sn->serial_no));
								foreach($di_sa as $disa){
									if($disa->sa != NULL){
										$flag=1;
									}
								}
							}
							
							if($flag == 1){
								$content .= '<table style = width:100%;><tr><td style = "width:22%;"><h4 style ="border: 1px solid purple; background-color:purple; border-radius:10px; color:White;">Suggested Activities : </h4></td></tr>';
							}
							
							$serial_nos = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND sub_section_title = :sst;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sst' => $diss->sub_section_title));
							foreach($serial_nos as $sn){
								$di_sa = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND serial_no = :sn;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sn' => $sn->serial_no));
								foreach($di_sa as $disa){
									if($disa->sa != NULL){
										$content .= '<tr><td style ="color:red; width:auto;"><h5><b><i>'.$disa->title.':</i></b></h5></td><td><h5>'.$disa->sa.'<h5></td></tr>';
									}
								}
							}
							$content .= '</table>';
						}
						$sub_section = $diss->sub_section_title;
					}
					$item++;
				}
			}
		}
		$content .= '</body>';
		$content .= '</html>';
	}
	return $content;
}
/**
 *Ajax callback
 */
function display_sections_ajax($form, &$form_state){
	return $form['sec_wrapper'];
}
/**
 *Ajax callback
 */
function display_print_ajax($form, &$form_state){
	return $form['print_wrapper'];
}