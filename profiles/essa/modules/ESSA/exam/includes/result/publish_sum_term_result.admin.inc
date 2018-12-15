<?php
/**
 *Implements page call back function- publish_term_result
 */
function publish_sum_term_result($form, &$form_state, $term_id){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$grade_table = 'essa_'.$session_id.'_exam_grade_settings';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
	$term_table = 'essa_'.$session_id.'_exam_terms';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$st_marks = NULL;
	$st_cf_marks = NULL;
	$st_grade = NULL;
	$st_grade_point = NULL;
	$grade_point_col = NULL;
	$sub_names = array();
	global $user;
	
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id,
	);
			
	$form['#attached']['css'] = array(
    drupal_get_path('module', 'field_group') . '/horizontal-tabs/horizontal-tabs.css',
  );
	
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'field_group') . '/horizontal-tabs/horizontal-tabs.js',
  );
	
	$form['vt'] = array(
		'#type' => 'horizontal_tabs',
	);
	
	$fm_total = 0;
	
	$total_weight = 0;
	$terms = db_query(
		"SELECT * from $term_table where id = :ti;", array(':ti' => $term_id)
	);
	foreach($terms as $term){
		$exams = db_query(
			"SELECT * from $master_exam_table where term = :ti;", array(':ti' => $term->term_1)
		);
		foreach($exams as $ex){
			$total_weight = $total_weight+$ex->weight;
		}
		$exams = db_query(
			"SELECT * from $master_exam_table where term = :ti;", array(':ti' => $term->term_2)
		);
		foreach($exams as $ex){
			$total_weight = $total_weight+$ex->weight;
		}
	}
	
	//$fm_total = $fm_total * $sub_count;
	$terms = db_query(
		"SELECT * from $term_table where id = :ti;", array(':ti' => $term_id)
	);
	foreach($terms as $ex){
		$class_from = $ex->class_from;
		$class_to = $ex->class_to;
	}
	$c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_from));
	foreach($c_from_weight as $cfw){
		$cf_weight = $cfw->weight;
	}
	$c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_to));
	foreach($c_to_weight as $ctw){
		$ct_weight = $ctw->weight;
	}
	$classes = array();
	$class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
		array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
	foreach($class_list as $c){
		$classes[] = $c;
	}
	foreach($classes as $cl){
		$form[$cl->class_id] = array(
			'#type' => 'fieldset',
			'#title' => $cl->class_id,
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
			'#group' => 'vt',
		);
		
		$form[$cl->class_id]['ht'] = array(
			'#type' => 'horizontal_tabs',
		);
		$sec = 'A';
		for($i = 1; $i <= $cl->no_of_sec; $i++){
			$row = $weight_row = $grade_row = $grade_point_row = $fm_row = array();
			$subject_table = 'essa_'.$session_id.'_subjects_'.$cl->class_id;
			$students = db_query(
				"SELECT * from $master_student_table where class = :cl and section = :sec;",
				array(':cl' => $cl->class_id, ':sec' => $sec)
			);
			
			$flag =1;
			if($flag == 1){
				foreach($students as $st){
					$form[$cl->class_id]['ht'][$sec] = array(
						'#type' => 'fieldset',
						'#title' => $cl->class_id.'-'.$sec,
						'#collapsible' => FALSE,
						'#collapsed' => FALSE,
					);
					$row[$st->adm_no] = array(
						'#tree' =>TRUE,
						$st->adm_no => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->adm_no .'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->student_name .'</h3>',
							),
						),
					);
					
					$grade_row[$st->adm_no] = array(
						'#tree' =>TRUE,
						$st->adm_no => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->adm_no .'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->student_name .'</h3>',
							),
						),
					);
					
					$grade_point_row[$st->adm_no] = array(
						'#tree' =>TRUE,
						$st->adm_no => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->adm_no .'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->student_name .'</h3>',
							),
						),
					);
					$total = 0;
					$sub_names = array();
					$sub_count = 0;
					$sub_id = NULL;
					$subjects = db_query(
						"SELECT * from $subject_table;"
					);
					foreach($subjects as $subject){
						$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$cl->class_id;
						$marks = db_query(
							"SELECT * from $marks_table where adm_no = :an;", array(':an' => $st->adm_no)
						);
						foreach($marks as $mark){
							$sub_id = $subject->sub_id;
							$total = $total+$mark->$sub_id;
							$total = round($total);
							$st_marks = $mark->$sub_id;
							if($st_marks != NULL){
								$st_marks = round($st_marks);
							}
							$grade_col = 'grade_'.$sub_id;
							$st_grade = $mark->$grade_col;
							$grade_point_col = 'grade_point_'.$sub_id;
							$st_grade_point = $mark->$grade_point_col;
							$op_subjects = db_query(
								"SELECT * from $subject_table where sub_id = :si;", array(':si' => $subject->sub_id)
							);
							foreach($op_subjects as $ops){
								if($ops->type == 'Optional'){
									$op_students = db_query(
										"SELECT * from $op_subj_student_table where adm_no = :an and sub_id = :s;",
										array(':an' => $st->adm_no, ':s' => $subject->sub_id)
									);
									foreach($op_students as $os){
										$sub_count = $sub_count+1;
										if($st_marks == NULL){
											$st_marks = '<span style = "color: RED;">AB</span>';
											$st_grade = '<span style = "color: RED;">AB</span>';
											$st_grade_point = '<span style = "color: RED;">AB</span>';
										}
									}
								}else{
									$sub_count = $sub_count+1;
									if($st_marks == NULL){
										$st_marks = '<span style = "color: RED;">AB</span>';
										$st_grade = '<span style = "color: RED;">AB</span>';
										$st_grade_point = '<span style = "color: RED;">AB</span>';
									}
								}
							}
						}
						
						if($st_grade == "D"){
							$sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: #FF8C00; color: WHITE; padding: 3px; width: 30px;"><b>'.$st_marks.'</b></span></h3>',
							);
							
							$grade_sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: #FF8C00;color: WHITE; padding: 3px;#FF8C00: 30px;"><b>'.$st_grade.'</b></span></h3>',
							);
							
							$grade_point_sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: #FF8C00;color: WHITE; padding: 3px;#FF8C00: 30px;"><b>'.$st_grade_point.'</b></span></h3>',
							);	
						}elseif($st_grade == "E1" || $st_grade == "E2"){
							$sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: RED;color: WHITE; padding: 3px;width: 30px;"><b>'.$st_marks.'</b></span></h3>',
							);
							
							$grade_sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: RED;color: WHITE; padding: 3px;width: 30px;"><b>'.$st_grade.'</b></span></h3>',
							);
							
							$grade_point_sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: RED;color: WHITE; padding: 3px;width: 30px;"><b>'.$st_grade_point.'</b></span></h3>',
							);	
						}elseif($st_grade == 'A1'){
							$sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: GREEN;color: WHITE; padding: 3px;width: 30px;"><b>'.$st_marks.'</b></span></h3>',
							);
							
							$grade_sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: GREEN;color: WHITE; padding: 3px;width: 30px;"><b>'.$st_grade.'</b></span></h3>',
							);
							
							$grade_point_sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: GREEN;color: WHITE; padding: 3px;width: 30px;"><b>'.$st_grade_point.'</b></span></h3>',
							);	
						}else{
							$sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center; display: inline-block;"><b>'.$st_marks.'</b></span></h3>',
							);
							
							$grade_sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center; display: inline-block;"><b>'.$st_grade.'</b></span></h3>',
							);
							
							$grade_point_sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center; display: inline-block;"><b>'.$st_grade_point.'</b></span></h3>',
							);	
						}
						$sub_names[] = $subject->sub_name;
						$row[$st->adm_no][$st->adm_no][] =  $sub_col[$st->adm_no];
						$grade_row[$st->adm_no][$st->adm_no][] =  $grade_sub_col[$st->adm_no];
						$grade_point_row[$st->adm_no][$st->adm_no][] =  $grade_point_sub_col[$st->adm_no];
					}
					if($sub_id != NULL){
						$fm_total = $total_weight*$sub_count;
						$total_percent = round($total/$fm_total*100);
						//dsm($total);
						//dsm($fm_total);
						$grades = db_query("
							SELECT * from {$grade_table};"
						);
						foreach($grades as $gr){
							if($total_percent >= $gr->marks_from && $total_percent <= $gr->marks_to){
								$total_grade = $gr->grade;
								$total_grade_point = $gr->grade_point;
							}
						}
						if($total_grade == "D"){
							$total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: #FF8C00; color: WHITE; padding: 3px; width: 30px;"><b>'.$total.'</b></span></h3>',
							);
							$grade_total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: #FF8C00; color: WHITE; padding: 3px; width: 30px;"><b>'.$total_grade.'</b></span></h3>',
							);
							$gp_total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: #FF8C00; color: WHITE; padding: 3px; width: 30px;"><b>'.$total_grade_point.'</b></span></h3>',
							);
						}elseif($total_grade == "E1" || $total_grade == "E2"){
							$total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: RED; color: WHITE; padding: 3px; width: 30px;"><b>'.$total.'</b></span></h3>',
							);
							$grade_total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: RED; color: WHITE; padding: 3px; width: 30px;"><b>'.$total_grade.'</b></span></h3>',
							);
							$gp_total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: RED; color: WHITE; padding: 3px; width: 30px;"><b>'.$total_grade_point.'</b></span></h3>',
							);
						}elseif($total_grade == 'A1'){
							$total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: GREEN; color: WHITE; padding: 3px; width: 30px;"><b>'.$total.'</b></span></h3>',
							);
							$grade_total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: GREEN; color: WHITE; padding: 3px; width: 30px;"><b>'.$total_grade.'</b></span></h3>',
							);
							$gp_total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: GREEN; color: WHITE; padding: 3px; width: 30px;"><b>'.$total_grade_point.'</b></span></h3>',
							);
						}else{
							$total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center; display: inline-block;"><b>'.$total.'</b></span></h3>',
							);
							$grade_total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center; display: inline-block;"><b>'.$total_grade.'</b></span></h3>',
							);
							$gp_total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center; display: inline-block;"><b>'.$total_grade_point.'</b></span></h3>',
							);
						}
						$row[$st->adm_no][$st->adm_no][] =  $total_col[$st->adm_no];
						$grade_row[$st->adm_no][$st->adm_no][] =  $grade_total_col[$st->adm_no];
						$grade_point_row[$st->adm_no][$st->adm_no][] =  $gp_total_col[$st->adm_no];
						
						$form[$cl->class_id]['ht'][$sec]['mw'] = array(
							'#type' => 'fieldset',
							'#title' => 'Marks',
							'#collapsible' => TRUE,
							'#collapsed' => TRUE,
						);
						
						$form[$cl->class_id]['ht'][$sec]['mw']['tab'] = array(
							'#theme' => 'ptr_student_marks_table',
							'rows' => $row,
						);
						
						$form[$cl->class_id]['ht'][$sec]['gr'] = array(
							'#type' => 'fieldset',
							'#title' => 'Grade',
							'#collapsible' => TRUE,
							'#collapsed' => TRUE,
						);
						$form[$cl->class_id]['ht'][$sec]['gr']['gr_tab'] = array(
							'#theme' => 'ptr_student_grade_table',
							'rows' => $grade_row,
						);
						
						$form[$cl->class_id]['ht'][$sec]['gp'] = array(
							'#type' => 'fieldset',
							'#title' => 'Grade Point',
							'#collapsible' => TRUE,
							'#collapsed' => TRUE,
						);
						$form[$cl->class_id]['ht'][$sec]['gp']['gp_tab'] = array(
							'#theme' => 'ptr_student_gp_table',
							'rows' => $grade_point_row,
						);
						
						$form[$cl->class_id]['ht'][$sec]['gph'] = array(
							'#type' => 'fieldset',
							'#title' => 'Graphical Analysis(per subject)',
							'#collapsible' => TRUE,
							'#collapsed' => TRUE,
						);
						
						$form[$cl->class_id]['ht'][$sec]['class'] = array(
							'#type' => 'value',
							'#value' => $cl->class_id
						);
						
						$form[$cl->class_id]['ht'][$sec]['sec'] = array(
							'#type' => 'value',
							'#value' => $sec
						);
						
						$subject_table = 'essa_'.$session_id.'_subjects_'.$cl->class_id;
						$sub_op = array('--Select--' => '--Select--');
						$subjects = db_query(
							"SELECT * from $subject_table;"
						);
						foreach($subjects as $subject){
							$sub_op[$subject->sub_id] = $subject->sub_name;
						}
						$form[$cl->class_id]['ht'][$sec]['gph']['subj'.$cl->class_id.$sec] = array(
							'#type' => 'select',
							'#title' => 'Select a Subject',
							'#options' => $sub_op,
							'#ajax' => array(
								'event' => 'change',
								'callback' => 'display_term_graph_ajax',
								'wrapper' => 'graph_wrapper'.$cl->class_id.$sec,
								'method' => 'replace',
								'effect' => 'fade',
							),
						);
						
						$form[$cl->class_id]['ht'][$sec]['gph']['graph_wrapper'] = array(
							'#type' => 'container',
							'#prefix' => '<div id = "graph_wrapper'.$cl->class_id.$sec.'">',
							'#suffix' => '</div>',
						);
						
						$form[$cl->class_id]['ht'][$sec]['ggph'] = array(
							'#type' => 'fieldset',
							'#title' => 'Grade Analysis(per subject)',
							'#collapsible' => TRUE,
							'#collapsed' => TRUE,
						);
						
						$form[$cl->class_id]['ht'][$sec]['ggph']['grade_subj'.$cl->class_id.$sec] = array(
							'#type' => 'select',
							'#title' => 'Select a Subject',
							'#options' => $sub_op,
							'#ajax' => array(
								'event' => 'change',
								'callback' => 'display_term_grade_graph_ajax',
								'wrapper' => 'grade_graph_wrapper'.$cl->class_id.$sec,
								'method' => 'replace',
								'effect' => 'fade',
							),
						);
						
						$form[$cl->class_id]['ht'][$sec]['ggph']['grade_graph_wrapper'] = array(
							'#type' => 'container',
							'#prefix' => '<div id = "grade_graph_wrapper'.$cl->class_id.$sec.'">',
							'#suffix' => '</div>',
						);
						
						$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$cl->class_id.'_'.$sec.'.csv';
						$form[$cl->class_id]['ht'][$sec]['download'] = array(
							'#type' => 'markup',
							'#markup' => '<h3>'.l(t('Download'), $path).'</h3>',
						);
						
						$form[$cl->class_id]['ht'][$sec]['color_code'] = array(
							'#type' => 'markup',
							'#markup' => '<div style = "width: 50%; float: right;">
								<h4 style = "text-align: right;"><span style = "text-align: center; display: inline-block; background: GREEN;color: GREEN; padding: 3px;">3</span> - Grade A1 &nbsp;&nbsp;
								<span style = "text-align: center; display: inline-block; background: #FF8C00;color: #FF8C00; padding: 3px;">3</span> - Grade D &nbsp;&nbsp;
								<span style = "text-align: center; display: inline-block; background: RED;color: RED; padding: 3px;">3</span> - Grade E1, Grade E2</h4>
							</div>',
						);
					}
				}	
			}
			$sec++;
		}
	}
	$sub_names = array_unique($sub_names);
	
	$format = 'd-m-Y';
	$form['date'] = array(
		'#type' => 'date_select',
		'#title' => 'Publish on(Date & Time)',
		'#default_value' => date('d-m-Y'), 
		'#date_format' => $format,
		'#date_label_position' => 'within', 
		'#date_timezone' => 'asia/kolkata', 
		'#date_increment' => 5,
	);
	
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value'  => 'Publish',
		'#submit' => array('publish_term'),
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value'  => 'Publish Now',
		'#submit' => array('publish_term_now'),
	);
	
	return $form;
}

function publish_term_now($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$grade_table = 'essa_'.$session_id.'_exam_grade_settings';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$term_id = $form_state['values']['term_id'];
	
	$class_status = array();
	$class_exam = array();
	$flag = 0;
	$exam_state = db_query(
		"SELECT * from $exam_status_table where term_id = :ti;",
		array(':ti' => $term_id)
	);
	foreach($exam_state as $es){
		if($es->generate_result_status != TRUE){
			drupal_set_message('Result of class - <b>'.$es->class.'</b> sec - <b>'.$es->sec.'</b> for <b>'.$es->exam_code.'</b> exam has been not been generated.','warning');
			$flag = 1;
		}
	}
	
	if($flag == 0){
		variable_set('publish_term_result_'.$term_id, TRUE);
		drupal_set_message('Term Result has been successfully published.', 'status');
	}
}

function publish_term($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$grade_table = 'essa_'.$session_id.'_exam_grade_settings';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$term_id = $form_state['values']['term_id'];
	
	$class_status = array();
	$class_exam = array();
	$flag = 0;
	$exam_state = db_query(
		"SELECT * from $exam_status_table where term_id = :ti;",
		array(':ti' => $term_id)
	);
	foreach($exam_state as $es){
		if($es->generate_result_status != TRUE){
			drupal_set_message('Result of class - <b>'.$es->class.'</b> sec - <b>'.$es->sec.'</b> for <b>'.$es->exam_code.'</b> exam has been not been generated.','warning');
			$flag = 1;
		}
	}
	
	if($flag == 0){
		variable_set('publish_term_result_'.$term_id, TRUE);
		variable_set('publish_term_result_on_'.$term_id, strtotime($form_state['values']['date']));
		$date = strtotime($form_state['values']['date']);
		$dt = date('d-M-Y',$date);
		drupal_set_message('Term Result will published on - '.$dt.'.', 'status');
	}
}

function display_term_grade_graph_ajax($form, &$form_state){
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$class = $form_state['triggering_element']['#array_parents'][0];
	$sec = $form_state['triggering_element']['#array_parents'][2];
	$sub_id = $form_state['values']['grade_subj'.$class.$sec];
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$class;
	$count = array();
	$students = db_query(
		"SELECT * from $master_student_table where class = :cl and section = :sec;",
		array(':cl' => $class, ':sec' => $sec)
	);
	foreach($students as $st){
		$marks = db_query(
			"SELECT * from $marks_table where adm_no = :an;", array(':an' => $st->adm_no)
		);
		foreach($marks as $mark){
			$col = 'grade_'.$sub_id;
			if($mark->$col != NULL){
				$count[$mark->$col] = $count[$mark->$col]+1;
			}
		}
	}
	
	foreach($count as $grade=>$no_of_student){
		$data[] = array('grades' => $grade, 'no_of_student' => $no_of_student);
	}
	
	$options_column = array(
    'title' => 'Grades',
    'fields' => array(
      'no_of_student' => array(
        'label' => t('No of Students'),
        'enabled' => TRUE,
      ),
    ),
    'xAxis' => array(
      'labelField' => 'grades',
    ),
    'data' => $data,
    'type' => 'column',
  );
	
	$form[$class]['ht'][$sec]['ggph']['grade_graph_wrapper']['grade_column'] =  array(
		'#theme' => 'visualization',
		'#options' => $options_column,
	);
	return $form[$class]['ht'][$sec]['ggph']['grade_graph_wrapper'];
}


function display_term_graph_ajax($form, &$form_state){
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$class = $form_state['triggering_element']['#array_parents'][0];
	$sec = $form_state['triggering_element']['#array_parents'][2];
	$sub_id = $form_state['values']['subj'.$class.$sec];
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$class;
	
	$students = db_query(
		"SELECT * from $master_student_table where class = :cl and section = :sec;",
		array(':cl' => $class, ':sec' => $sec)
	);
	foreach($students as $st){
		$marks = db_query(
			"SELECT * from $marks_table where adm_no = :an;", array(':an' => $st->adm_no)
		);
		foreach($marks as $mark){
			if($mark->$sub_id != NULL){
				$data[] = array('adm_no' => $st->adm_no, 'marks' => $mark->$sub_id);
			}
		}
	}
	
	$options_column = array(
    'title' => 'Marks',
    'fields' => array(
      'marks' => array(
        'label' => t('Marks'),
        'enabled' => TRUE,
      ),
    ),
    'xAxis' => array(
      'labelField' => 'adm_no',
    ),
    'data' => $data,
    'type' => 'line',
  );
	
	$form[$class]['ht'][$sec]['gph']['graph_wrapper']['column'] =  array(
		'#theme' => 'visualization',
		'#options' => $options_column,
	);
	return $form[$class]['ht'][$sec]['gph']['graph_wrapper'];
}

/**
 *Theme function
 */
function theme_ptr_student_marks_table(&$variables){
  // Get the useful values.
	$form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Adm No.'), t('Name'));
	global $user;
	$sub_names = array();
	$session_id = (string)variable_get('essa_sid');
	$subject_table = 'essa_'.$session_id.'_subjects_'.$form['#array_parents'][0];
	$subjects = db_query(
		"SELECT * from $subject_table;"
	);
	foreach($subjects as $subject){
		$sub_names[] = $subject->sub_name;
	}
	$total = array('Total');
	$header = array_merge($header, $sub_names);
	$header = array_merge($header, $total);
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
 *Theme function
 */
function theme_ptr_student_grade_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Adm No.'), t('Name'));
	global $user;
	$sub_names = array();
	$session_id = (string)variable_get('essa_sid');
	$subject_table = 'essa_'.$session_id.'_subjects_'.$form['#array_parents'][0];
	$subjects = db_query(
		"SELECT * from $subject_table;"
	);
	foreach($subjects as $subject){
		$sub_names[] = $subject->sub_name;
	}
	$total = array('Overall Grade');
	$header = array_merge($header, $sub_names);
	$header = array_merge($header, $total);
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
 *Theme function
 */
function theme_ptr_student_gp_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Adm No.'), t('Name'));
	global $user;
	$sub_names = array();
	$session_id = (string)variable_get('essa_sid');
	$subject_table = 'essa_'.$session_id.'_subjects_'.$form['#array_parents'][0];
	$subjects = db_query(
		"SELECT * from $subject_table;"
	);
	foreach($subjects as $subject){
		$sub_names[] = $subject->sub_name;
	}
	$total = array('Total');
	$header = array_merge($header, $sub_names);
	$header = array_merge($header, $total);
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