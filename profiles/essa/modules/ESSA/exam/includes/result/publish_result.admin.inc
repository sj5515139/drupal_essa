<?php
/**
 *Implements page callback function generate_result
 */
function publish_result($form, &$form_state, $term_id, $exam_code){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$term_table = 'essa_'.$session_id.'_exam_terms';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$grade_table = 'essa_'.$session_id.'_exam_grade_settings';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
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
			
	$form['exam_code'] = array(
		'#type' => 'value',
		'#value' => $exam_code,
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
	
	$exams = db_query(
		"SELECT * from $master_exam_table where term = :ti and exam_code = :ec;", array(':ti' => $term_id, ':ec'=>$exam_code)
	);
	foreach($exams as $ex){
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
				"SELECT * from $master_student_table where class = :cl and section = :sec order by exam_roll_no;",
				array(':cl' => $cl->class_id, ':sec' => $sec)
			);
			
			$flag =0;
			$exam_state = db_query(
				"SELECT * from $exam_status_table where term_id = :ti and exam_code = :ec and class = :cl and sec = :sec;",
				array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $cl->class_id, ':sec' => $sec)
			);
			foreach($exam_state as $es){
				if($es->generate_result_status == TRUE){
					$flag =1;
				}
			}
			if($flag == 1){
				foreach($students as $st){
					$form[$cl->class_id]['ht'][$sec] = array(
						'#type' => 'fieldset',
						'#title' => $cl->class_id.'-'.$sec,
						'#collapsible' => FALSE,
						'#collapsed' => FALSE,
					);
					$fm_row['full_marks'] = array(
						'#tree' =>TRUE,
						'full_marks' => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: left !important;">Full Marks</h3>',
							),
						),
					);
					$row[$st->adm_no] = array(
						'#tree' =>TRUE,
						$st->adm_no => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->adm_no .'</h3>',
							),
							'cer' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->exam_roll_no .'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->student_name .'</h3>',
							),
						),
					);
					$weight_row[$st->adm_no] = array(
						'#tree' =>TRUE,
						$st->adm_no => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->adm_no .'</h3>',
							),
							'cer' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->exam_roll_no .'</h3>',
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
							'cer' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->exam_roll_no .'</h3>',
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
							'cer' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->exam_roll_no .'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;">'. $st->student_name .'</h3>',
							),
						),
					);
					$total = 0;
					$fm_total = 0;
					$cf_total = 0;
					$sub_names = array();
					$sub_id = NULL;
					$subjects = db_query(
						"SELECT * from $subject_table;"
					);
					foreach($subjects as $subject){
						$fm_def = NULL;
						$full_marks_table = 'essa_'.$session_id.'_exam_full_marks';
						$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($exam_code).'_'.$cl->class_id;
						$marks = db_query(
							"SELECT * from $marks_table where adm_no = :an;", array(':an' => $st->adm_no)
						);
						foreach($marks as $mark){
							$sub_id = $subject->sub_id;
							$total = $total+$mark->$sub_id;
							$st_marks = $mark->$sub_id;
							$cf_col = 'cf_'.$sub_id;
							$st_cf_marks = $mark->$cf_col;
							if($st_cf_marks != NULL){
								$st_cf_marks = round($st_cf_marks);
							}
							$cf_total = $cf_total+round($st_cf_marks);
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
										if($st_marks == NULL){
											$st_marks = '<span style = "color: RED;">AB</span>';
											$st_cf_marks = '<span style = "color: RED;">AB</span>';
											$st_grade = '<span style = "color: RED;">AB</span>';
										 $st_grade_point = '<span style = "color: RED;">AB</span>';
										}
										$full_marks = db_query(
											"SELECT * from $full_marks_table where term_id = :ti and exam_code = :ec and class = :cl and subject_id = :si;",
											array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $cl->class_id, ':si' => $subject->sub_id)
										);
										foreach($full_marks as $fm){
											$fm_total = $fm_total + $fm->full_marks;
										}
									}
								}else{
									if($st_marks == NULL){
										$st_marks = '<span style = "color: RED;">AB</span>';
										$st_cf_marks = '<span style = "color: RED;">AB</span>';
										$st_grade = '<span style = "color: RED;">AB</span>';
										$st_grade_point = '<span style = "color: RED;">AB</span>';
									}
									$full_marks = db_query(
										"SELECT * from $full_marks_table where term_id = :ti and exam_code = :ec and class = :cl and subject_id = :si;",
										array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $cl->class_id, ':si' => $subject->sub_id)
									);
									foreach($full_marks as $fm){
										$fm_total = $fm_total + $fm->full_marks;
									}
								}
							}
						}
						
						if($st_grade == "D"){
							$sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: #FF8C00; color: WHITE; padding: 3px; width: 30px;"><b>'.$st_marks.'</b></span></h3>',
							);
							
							$cf_sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: #FF8C00;color: WHITE; padding: 3px;#FF8C00: 30px;"><b>'.($st_cf_marks).'</b></span></h3>',
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
							
							$cf_sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: RED;color: WHITE; padding: 3px;width: 30px;"><b>'.($st_cf_marks).'</b></span></h3>',
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
							
							$cf_sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: GREEN;color: WHITE; padding: 3px;width: 30px;"><b>'.($st_cf_marks).'</b></span></h3>',
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
							
							$cf_sub_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center; display: inline-block;"><b>'.($st_cf_marks).'</b></span></h3>',
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
						$weight_row[$st->adm_no][$st->adm_no][] =  $cf_sub_col[$st->adm_no];
						$grade_row[$st->adm_no][$st->adm_no][] =  $grade_sub_col[$st->adm_no];
						$grade_point_row[$st->adm_no][$st->adm_no][] =  $grade_point_sub_col[$st->adm_no];
					}
					if($sub_id != NULL){
						variable_set('upload_marks_sub'.$user->uid, $sub_names);
						$total_percent = round($total/$fm_total*100);
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
							$cf_total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: #FF8C00; color: WHITE; padding: 3px; width: 30px;"><b>'.$cf_total.'</b></span></h3>',
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
							$cf_total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: RED; color: WHITE; padding: 3px; width: 30px;"><b>'.$cf_total.'</b></span></h3>',
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
							$cf_total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3><span style = "text-align: center; display: inline-block; background: GREEN; color: WHITE; padding: 3px; width: 30px;"><b>'.$cf_total.'</b></span></h3>',
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
							$cf_total_col[$st->adm_no] = array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center; display: inline-block;"><b>'.($cf_total).'</b></span></h3>',
							);
						}
						$weight_row[$st->adm_no][$st->adm_no][] =  $cf_total_col[$st->adm_no];
						$row[$st->adm_no][$st->adm_no][] =  $total_col[$st->adm_no];
						$grade_row[$st->adm_no][$st->adm_no][] =  $grade_total_col[$st->adm_no];
						$grade_point_row[$st->adm_no][$st->adm_no][] =  $gp_total_col[$st->adm_no];
						$subjects = db_query(
							"SELECT * from $subject_table;"
						);
						foreach($subjects as $subject){
							$fm_def = NULL;
							$full_marks_table = 'essa_'.$session_id.'_exam_full_marks';
							$full_marks = db_query(
								"SELECT * from $full_marks_table where term_id = :ti and exam_code = :ec and class = :cl and subject_id = :si;",
								array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $cl->class_id, ':si' => $subject->sub_id)
							);
							foreach($full_marks as $fm){
								$fm_def = $fm->full_marks;
							}
							if(isset($fm_def) != NULL){
								$fm_def = $fm->full_marks;
							}else{
								$fm_def = NULL;
							}
							
							$fm_col[$subject->sub_id] = array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: center !important;"><b>'.$fm_def.'</b></span></h3>',
							);
							$fm_row['full_marks']['full_marks'][] =  $fm_col[$subject->sub_id];
						}
						
						$form[$cl->class_id]['ht'][$sec]['mw'] = array(
							'#type' => 'fieldset',
							'#title' => 'Marks Obtained',
							'#collapsible' => TRUE,
							'#collapsed' => TRUE,
						);
						$form[$cl->class_id]['ht'][$sec]['mw']['fm_tab'] = array(
							'#theme' => 'pr_full_marks_table',
							'rows' => $fm_row,
						);
						
						$form[$cl->class_id]['ht'][$sec]['mw']['tab'] = array(
							'#theme' => 'pr_student_marks_table',
							'rows' => $row,
						);
						
						$get_weight = db_query(
							"SELECT * from $master_exam_table where exam_code = :ec and term = :t;",
							array(':ec' => $exam_code, ':t' => $term_id)
						);
						foreach($get_weight as $gw){
							$weight = $gw->weight;
						}
						$form[$cl->class_id]['ht'][$sec]['cw'] = array(
							'#type' => 'fieldset',
							'#title' => 'Out of '.$weight,
							'#collapsible' => TRUE,
							'#collapsed' => TRUE,
						);
						$form[$cl->class_id]['ht'][$sec]['cw']['cf_tab'] = array(
							'#theme' => 'pr_student_cf_table',
							'rows' => $weight_row,
						);
						
						$form[$cl->class_id]['ht'][$sec]['gr'] = array(
							'#type' => 'fieldset',
							'#title' => 'Grade',
							'#collapsible' => TRUE,
							'#collapsed' => TRUE,
						);
						$form[$cl->class_id]['ht'][$sec]['gr']['gr_tab'] = array(
							'#theme' => 'pr_student_grade_table',
							'rows' => $grade_row,
						);
						
						$form[$cl->class_id]['ht'][$sec]['gp'] = array(
							'#type' => 'fieldset',
							'#title' => 'Grade Point',
							'#collapsible' => TRUE,
							'#collapsed' => TRUE,
						);
						$form[$cl->class_id]['ht'][$sec]['gp']['gp_tab'] = array(
							'#theme' => 'pr_student_gp_table',
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
						$sub_op = array('--Select--');
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
								'callback' => 'display_graph_ajax',
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
								'callback' => 'display_grade_graph_ajax',
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
						
						$form[$cl->class_id]['ht'][$sec]['color_code'] = array(
							'#type' => 'markup',
							'#markup' => '<div style = "width: 50%; float: right;">
								<h4 style = "text-align: right;"><span style = "text-align: center; display: inline-block; background: GREEN;color: GREEN; padding: 3px;">3</span> - Grade A1 &nbsp;&nbsp;
								<span style = "text-align: center; display: inline-block; background: #FF8C00;color: #FF8C00; padding: 3px;">3</span> - Grade D &nbsp;&nbsp;
								<span style = "text-align: center; display: inline-block; background: RED;color: RED; padding: 3px;">3</span> - Grade E1, Grade E2</h4>
							</div>',
						);
						
						$form[$cl->class_id]['ht'][$sec]['cancel'] = array(
							'#type' => 'submit',
							'#value' => 'Send for Review',
							'#submit' => array('send_for_review'),
							'#name' => $cl->class_id.'-'.$sec,
						);	
					}
				}	
			}else{
				$form[$cl->class_id]['ht'][$sec] = array(
					'#type' => 'fieldset',
					'#title' => $cl->class_id.'-'.$sec,
					'#collapsible' => FALSE,
					'#collapsed' => FALSE,
				);
				
				$form[$cl->class_id]['ht'][$sec]['text'] = array(
					'#type' => 'markup',
					'#markup' => 'Result has not been generated for class '.$cl->class_id.'-'.$sec,
				);
			}
			$sec++;
		}
	}
	$sub_names = array_unique($sub_names);
	
	$format = 'd-m-Y';
	$form['date'] = array(
		'#type' => 'date_select',
		'#title' => 'Publish on(Date & Time)',
		'#default_value' => NULL, 
		'#date_format' => $format,
		'#date_label_position' => 'within', 
		'#date_timezone' => 'asia/kolkata', 
		'#date_increment' => 5,
	);
	
	
	if(variable_get('downloads'.$term_id) == TRUE){
		$form['fs'] = array(
			'#type' => 'fieldset',
			'#title' => 'Downloads',
			'#collapsible' => TRUE,
			'#collapsed' => TRUE,
		);
		foreach($classes as $cl){
			$sec = 'A';
			for($i = 1; $i <= $cl->no_of_sec; $i++){
				$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$cl->class_id.'_'.$sec.'.csv';
				
				$form['fs']['download'.$cl->class_id.$sec] = array(
					'#type' => 'markup',
					'#markup' => '<h3>'.l(t('Download Term Result - '.$cl->class_id.'-'.$sec), $path).'</h3>',
				);
				$sec++;
			}
		}
	}
	$form['save'] = array(
		'#type' => 'submit',
		'#value'  => 'Publish',
		'#submit' => array('publish'),
	);
	
	$form['generate_term_result'] = array(
		'#type' => 'submit',
		'#value'  => 'Generate Term Result',
		'#submit' => array('generate_term_result'),
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value'  => 'Publish Now',
		'#submit' => array('publish_now'),
	);
	
	$term = db_query("SELECT * FROM $term_table WHERE id = :ti;", array(':ti' => $term_id));
	foreach($term as $t){
		$term_name = $t->term_name;
	}
	
	$form['msg'] = array(
		'#type' => 'markup',
		'#markup' => '<h5>"Generate Term Result" button is used for the last exam of '.$term_name.'</h5>',
	);
	return $form;
}

function generate_term_result($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$grade_table = 'essa_'.$session_id.'_exam_grade_settings';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
	
	variable_set('downloads'.$term_id, TRUE);
	$exams = db_query(
		"SELECT * from $master_exam_table where term = :ti;", array(':ti' => $term_id)
	);
	foreach($exams as $ex){
		$class_from = $ex->class_from;
		$class_to = $ex->class_to;
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
		foreach($class_list as $c){
			$classes[] = $c;
		}
		foreach($classes as $cl){
			$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($ex->exam_code).'_'.$cl->class_id;
			$subject_table = 'essa_'.$session_id.'_subjects_'.$cl->class_id;
			$student_marks = db_query("SELECT * FROM {$marks_table};");
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
	
	$weight_total = 0;
	$exams = db_query(
		"SELECT * from $master_exam_table where term = :ti;", array(':ti' => $term_id)
	);
	foreach($exams as $ex){
		$weight_total = $weight_total+$ex->weight;
		$class_from = $ex->class_from;
		$class_to = $ex->class_to;
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
			$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($ex->exam_code).'_'.$cl->class_id;
			$subject_table = 'essa_'.$session_id.'_subjects_'.$cl->class_id;
			$student_marks = db_query("SELECT * FROM {$marks_table};");
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
							$term_total[$sm->adm_no][$subject->sub_id] = $term_total[$sm->adm_no][$subject->sub_id] + $sm->$cf_col;
							$data[$sm->adm_no][$sub_col][$ex->exam_code] = round($sm->$cf_col);
							$header[$sm->adm_no][$sub_col][$ex->exam_code] = $ex->exam_code.'#'.$subject->sub_name;
							$flag = 1;
							$sub_count++;
							$ex_sub[$sm->adm_no][$subject->sub_id] = $subject->sub_name;
							$data_gp[$sm->adm_no][$ex->exam_code][$sub_col] = round($sm->$cf_col);
						}
						if($flag == 0){
							$sub_col = $subject->sub_id;
							$header[$sm->adm_no][$sub_col][$ex->exam_code] = $ex->exam_code.'#'.$subject->sub_name;
							$data[$sm->adm_no][$sub_col][$ex->exam_code] = '';
						}
					}else{
						$sub_count++;
						$sub_col = $subject->sub_id;
						$cf_col = 'cf_'.$subject->sub_id;
						$term_total[$sm->adm_no][$subject->sub_id] = $term_total[$sm->adm_no][$subject->sub_id] + $sm->$cf_col;
						$data[$sm->adm_no][$sub_col][$ex->exam_code] = round($sm->$cf_col);
						$data_gp[$sm->adm_no][$ex->exam_code][$sub_col] = round($sm->$cf_col);
						$header[$sm->adm_no][$sub_col][$ex->exam_code] = $ex->exam_code.'#'.$subject->sub_name;
						$ex_sub[$sm->adm_no][$subject->sub_id] = $subject->sub_name;
					}
				}
			}
		}
	}
	
	include_once(drupal_get_path('module', 'exam') . '/pChart/class/pData.class.php');
	include_once(drupal_get_path('module', 'exam') . '/pChart/class/pDraw.class.php');
	include_once(drupal_get_path('module', 'exam') . '/pChart/class/pImage.class.php');
	include_once(drupal_get_path('module', 'exam') . '/pChart/class/pPie.class.php');
	foreach($data_gp as $adm_no => $rec){
		$MyData = new pData();
		foreach($rec as $sub_id => $marks){
			$MyData->loadPalette(drupal_get_path('module', 'exam') . "/pChart/palettes/blind.color",TRUE);
			$MyData->addPoints($marks,$sub_id);
			//$MyData->setSerieTicks($sub_id,4);
			$MyData->setAxisName(0,"Marks");
		}
		
		$MyData->addPoints($ex_sub[$adm_no],"Labels");
		$MyData->setSerieDescription("Labels","Subjects");
	  $MyData->setAbscissa("Labels");
		//dsm($MyData);
		 /* Create the pChart object */
		 $myPicture = new pImage(700,230,$MyData);
		
		 /* Draw the background */
		 $Settings = array("R"=>255, "G"=>255, "B"=>255, "Dash"=>0, "DashR"=>190, "DashG"=>203, "DashB"=>107);
		 $myPicture->drawFilledRectangle(0,0,700,230,$Settings);
		
		 /* Overlay with a gradient */
		 $Settings = array("StartR"=>255, "StartG"=>255, "StartB"=>255, "EndR"=>255, "EndG"=>255, "EndB"=>255, "Alpha"=>0);
		 $myPicture->drawGradientArea(0,0,700,230,DIRECTION_VERTICAL,$Settings);
		 $myPicture->drawGradientArea(0,0,700,20,DIRECTION_VERTICAL,array("StartR"=>0,"StartG"=>0,"StartB"=>0,"EndR"=>50,"EndG"=>50,"EndB"=>50,"Alpha"=>80));
		
		 /* Add a border to the picture */
		 $myPicture->drawRectangle(0,0,699,229,array("R"=>0,"G"=>0,"B"=>0));
		 
		 /* Write the picture title */
		 $myPicture->setFontProperties(array(
							"FontName" => drupal_get_path('module', 'exam') . '/pChart' . "/fonts/pf_arma_five.ttf",
							"FontSize" => 6));
		 $myPicture->drawText(10,13,"Subject Wise Marks Analysis",array("R"=>255,"G"=>255,"B"=>255));
		
		 /* Write the chart title */
		 $myPicture->setFontProperties(array(
							"FontName" => drupal_get_path('module', 'exam') . '/pChart' . "/fonts/Forgotte.ttf",
							"FontSize" => 11));
		 $myPicture->drawText(250,55,"Marks Analysis",array("FontSize"=>20,"Align"=>TEXT_ALIGN_BOTTOMMIDDLE));
		
		 /* Draw the scale and the 1st chart */
		 $myPicture->setGraphArea(60,60,670,190);
		 $myPicture->drawFilledRectangle(60,60,670,190,array("R"=>255,"G"=>255,"B"=>255,"Surrounding"=>-200,"Alpha"=>10));
		 $myPicture->drawScale(array("DrawSubTicks"=>FALSE,"Mode"=>SCALE_MODE_ADDALL));
		 $myPicture->setShadow(TRUE,array("X"=>1,"Y"=>1,"R"=>0,"G"=>0,"B"=>0,"Alpha"=>10));
		 $myPicture->setFontProperties(array(
							"FontName" => drupal_get_path('module', 'exam') . '/pChart' . "/fonts/pf_arma_five.ttf",
							"FontSize" => 6));
		 $myPicture->drawStackedBarChart(array("DisplayValues"=>TRUE,"DisplayColor"=>DISPLAY_AUTO,"Rounded"=>TRUE,"Surrounding"=>60));
		 $myPicture->setShadow(FALSE);
		
		 /* Write the chart legend */
		 $myPicture->drawLegend(510,205,array("Style"=>LEGEND_NOBORDER,"Mode"=>LEGEND_HORIZONTAL));
		
		
		 /* Render the picture (choose the best way) */
		 $myPicture->Render('sites/default/files/exam/'.$term_id.'/'.str_replace('/','#',$adm_no).'.png');
		
	}

	$fm_total = $weight_total * $sub_count;
	foreach ($data as $adm_no => $rec){
		$total = 0;
		$st_details = db_query("SELECT * FROM {$master_student_table} WHERE adm_no = :an;", array(':an' => $adm_no));
		foreach($st_details as $sd){
			$st_name = $sd->student_name;
		}
		foreach($rec as $sub_id => $line){
			$sub_total = 0;
			foreach($line as $marks){
				$data_csv[$adm_no][$adm_no] = $adm_no;
				$data_csv[$adm_no][$st_name] = $st_name;
				$data_csv[$adm_no][] = $marks;
				$sub_total = $sub_total + $marks;
			}
			$total = $total + $sub_total;
			if($sub_total == 0){
				$data_csv[$adm_no][] = '';
			}else{
				$data_csv[$adm_no][] = $sub_total;
			}
		}
		$data_csv[$adm_no]['total'] = $total;
		$total_percent = round($total/$fm_total*100);
		$grades = db_query("
			SELECT * from {$grade_table};"
		);
		foreach($grades as $gr){
			if($total_percent >= $gr->marks_from && $total_percent <= $gr->marks_to){
				$total_grade = $gr->grade;
				$data_csv[$adm_no]['total_grade'] = $total_grade;
				$total_grade_point = $gr->grade_point;
				$data_csv[$adm_no]['total_gp'] = $total_grade_point;
			}
		}
	}
	
	foreach ($header as $adm_no => $rec){
		foreach($rec as $sub_id => $line){
			foreach($line as $marks){
				$header_csv['adm_no'] = 'Adm No.';
				$header_csv['student_name'] = 'Student Name';
				$header_csv[$marks] = $marks;
			}
			$header_csv['total'.$marks] = $sub_id;
		}
	}
	$header_csv['total'] = 'Total';
	$header_csv['grade'] = 'Overall Grade';
	$header_csv['gp'] = 'Overall Grade Point';
	$delimiter = ',';
	$enclosure = '"';
	$sec = 'A';
	foreach($classes as $class){
		for($i = 1; $i <= $class->no_of_sec; $i++){
			$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$class->class_id.'_'.$sec.'.csv';
			$handle = fopen ($path,'w');
			fputcsv($handle, $header_csv, $delimiter, $enclosure);
			foreach ($data_csv as $adm_no => $rec){
				$students = db_query(
					"SELECT * from $master_student_table where adm_no = :an;",
					array(':an' => $adm_no)
				);
				foreach($students as $st){
					if($st->class == $class->class_id && $st->section == $sec){
						fputcsv($handle, $rec, $delimiter, $enclosure);
					}
				}
			}
			fclose($handle);
			$sec++;
		}
	}
	
	foreach($term_total as $adm_no => $val){
		foreach($val as $sub_id => $marks){
			$marks_1 = round($marks);
			$percent_1 = $marks_1/$weight_total*100;
			$percent_1 = round($percent_1);
			
			$marks_2 = $marks;
			$percent_2 = $marks_2/$weight_total*100;
			$percent_2 = round($percent_2);
			if($percent_2 - $percent_1 == 1){
				$percent = $percent_1 + 1;
				$marks = $marks + 1;
			}else{
				$percent = $percent_1;
			}
			
			$grades = db_query("
				SELECT * from {$grade_table};"
			);
			foreach($grades as $gr){
				if($percent >= $gr->marks_from && $percent <= $gr->marks_to){
					$grade = $gr->grade;
					$grade_point = $gr->grade_point;
					$students = db_query(
						"SELECT * from $master_student_table where adm_no = :an;",
							array(':an' => $adm_no)
					);
					foreach($students as $st){
						$class = $st->class;
						$sec = $st->section;
					}
					$term_marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$class;
					db_merge($term_marks_table)
						->key(array('adm_no' => $adm_no))
						->fields (array(
							'adm_no' => $adm_no,
							'section' => $sec,
							$sub_id => $marks,
							'grade_'.$sub_id => $grade,
							'grade_point_'.$sub_id => $grade_point,
						)
					)
					->execute();
				}
			}
		}
	}
	drupal_set_message('Term Result was generated successfully.','status');
}

function publish_now($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$grade_table = 'essa_'.$session_id.'_exam_grade_settings';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$class_status = array();
	$class_exam = array();
	$flag = 0;
	global $user;
	$exam_state = db_query(
		"SELECT * from $exam_status_table where term_id = :ti and exam_code = :ec;",
		array(':ti' => $term_id, ':ec' => $exam_code)
	);
	foreach($exam_state as $es){
		if($es->send_for_review == TRUE){
			drupal_set_message('Result of class - <b>'.$es->class.'</b> sec - <b>'.$es->sec.'</b> has been sent for review.','warning');
			$flag = 1;
		}
		$class_status[$es->class.'-'.$es->sec] = $es->class.'-'.$es->sec;
	}
	
	$exams = db_query(
		"SELECT * from $master_exam_table where term = :ti and exam_code = :ec;", array(':ti' => $term_id, ':ec'=>$exam_code)
	);
	foreach($exams as $ex){
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
		$sec = 'A';
		for($i = 1; $i <= $cl->no_of_sec; $i++){
			$class_exam[$cl->class_id.'-'.$sec] = $cl->class_id.'-'.$sec;
			$sec++;
		}
	}
	
	if($class_status != $class_exam){
		$flag = 1;
		$class_diff = array_diff($class_exam, $class_status);
		foreach($class_diff as $cd){
			drupal_set_message('Result of class - <b>'.$cd.'</b> is pending.','warning');
		}
	}
	
	if($flag == 0){
		foreach($classes as $cl){
			$sec = 'A';
			for($i = 1; $i <= $cl->no_of_sec; $i++){
				db_merge($exam_status_table)
					->key(array('term_id' => $term_id, 'exam_code' => $exam_code, 'class' => $cl->class_id, 'sec' => $sec,))
					->fields (array(
							'term_id' => $term_id,
							'exam_code' => $exam_code,
							'class' => $cl->class_id,
							'sec' => $sec,
							'timestamp' => time(),
							'uid' => $user->uid,
							'publish_result_status' => TRUE,
							'publish_on' => time(),
						)
					)
				->execute();
				
				$sec++;
			}
		}
		drupal_set_message('Results were published successfullly.','status');
	}else{
		drupal_set_message('We can\'t publish the result now','error');
	}
	menu_rebuild();
}

function publish($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$grade_table = 'essa_'.$session_id.'_exam_grade_settings';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$class_status = array();
	$class_exam = array();
	$flag = 0;
	
	if($form_state['values']['date'] == NULL){
		drupal_set_message('Please enter the date to publish the result.', 'error');
		$flag = 1;
	}
	$exam_state = db_query(
		"SELECT * from $exam_status_table where term_id = :ti and exam_code = :ec;",
		array(':ti' => $term_id, ':ec' => $exam_code)
	);
	foreach($exam_state as $es){
		if($es->send_for_review == TRUE){
			drupal_set_message('Result of class - <b>'.$es->class.'</b> sec - <b>'.$es->sec.'</b> has been sent for review.','warning');
			$flag = 1;
		}
		$class_status[$es->class.'-'.$es->sec] = $es->class.'-'.$es->sec;
	}
	
	$exams = db_query(
		"SELECT * from $master_exam_table where term = :ti and exam_code = :ec;", array(':ti' => $term_id, ':ec'=>$exam_code)
	);
	foreach($exams as $ex){
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
		$sec = 'A';
		for($i = 1; $i <= $cl->no_of_sec; $i++){
			$class_exam[$cl->class_id.'-'.$sec] = $cl->class_id.'-'.$sec;
			$sec++;
		}
	}
	
	if($class_status != $class_exam){
		$flag = 1;
		$class_diff = array_diff($class_exam, $class_status);
		foreach($class_diff as $cd){
			drupal_set_message('Result of class - <b>'.$cd.'</b> is pending.','warning');
		}
	}
	
	if($flag == 0){
		foreach($classes as $cl){
			$sec = 'A';
			for($i = 1; $i <= $cl->no_of_sec; $i++){
				$date = strtotime($form_state['values']['date']);
				$dt = date('d-M-Y',$date);
				drupal_set_message('Term Result will published on - '.$dt.'.', 'status');
				db_merge($exam_status_table)
					->key(array('term_id' => $term_id, 'exam_code' => $exam_code, 'class' => $cl->class_id, 'sec' => $sec,))
					->fields (array(
							'term_id' => $term_id,
							'exam_code' => $exam_code,
							'class' => $cl->class_id,
							'sec' => $sec,
							'timestamp' => time(),
							'uid' => $user->uid,
							'publish_result_status' => FALSE,
							'publish_on' => $date,
						)
					)
				->execute();
				
				$sec++;
			}
			drupal_set_message('Results will be published on - '.$dt.'.','status');
		}
	}else{
		drupal_set_message('We can\'t publish the result now','error');
	}
	menu_rebuild();
}

function send_for_review($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	
	$arr = explode('-',$form_state['triggering_element']['#name'], 2);
	$class = $arr[0];
	$sec = $arr[1];
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	db_merge($exam_status_table)
		->key(array('term_id' => $term_id, 'exam_code' => $exam_code, 'class' => $class, 'sec' => $sec,))
		->fields (array(
				'term_id' => $term_id,
				'exam_code' => $exam_code,
				'class' => $class,
				'sec' => $sec,
				'generate_result_status' => FALSE,
				'send_for_review' => TRUE,
			)
		)
	->execute();
	
}


function display_grade_graph_ajax($form, &$form_state){
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
	$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($exam_code).'_'.$class;
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


function display_graph_ajax($form, &$form_state){
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
	$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($exam_code).'_'.$class;
	
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
function theme_pr_student_marks_table(&$variables){
  // Get the useful values.
	$form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Adm No.'), t('Roll No.'), t('Name'));
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
function theme_pr_student_cf_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Adm No.'), t('Roll No.'), t('Name'));
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
function theme_pr_student_grade_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Adm No.'), t('Roll No.'), t('Name'));
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
function theme_pr_student_gp_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Adm No.'), t('Roll No.'), t('Name'));
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
function theme_pr_full_marks_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t(''));
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
	$header = array_merge($header, $sub_names);
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