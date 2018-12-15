<?php
/**
 *Implements page callback function generate_result
 */
function generate_result($form, &$form_state, $term_id, $exam_code){	
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$grade_table = 'essa_'.$session_id.'_exam_grade_settings';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
	$master_staff_table = 'essa_'.$session_id.'_master_staff_table';
	$class_teacher_table = 'essa_'.$session_id.'_class_teacher';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
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
	
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id,
	);
		
	$form['exam_code'] = array(
		'#type' => 'value',
		'#value' => $exam_code,
	);
		
	if(isset($this_class)){
		$class_list = array('--Select--');
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
		$ex_class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
			array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
		foreach($ex_class_list as $c){
			$class_list[] = $c->class_id;
		}
		
		$form['sec_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "sec_wrapper">',
			'#suffix' => '</div>',
		);
		
		$form['sec_wrapper']['class'] = array(
			'#type' => 'textfield',
			'#title' => 'Class',
			'#default_value' => $this_class,
			'#disabled' => TRUE,
			'#size' => 8,
		);
		
		$form['sec_wrapper']['marks_wrapper'] = array(
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
			
			$form['sec_wrapper']['marks_wrapper']['sec'] = array(
				'#type' => 'textfield',
				'#title' => 'Section',
				'#default_value' => $this_sec,
				'#disabled' => TRUE,
				'#size' => 8,
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
			
			$form_state['values']['sec'] = $this_sec;
			if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
				$form_state['values']['term_id'] = $term_id;
				$form_state['values']['exam_code'] = $exam_code;
				create_download($form, $form_state);
				$subject_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
				$students = db_query(
					"SELECT * from $master_student_table where class = :cl and section = :sec order by exam_roll_no;",
					array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
				);
				foreach($students as $st){
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
					$st_grade = NULL;
					$st_marks = NULL;
					$st_cf_marks = NULL;
					$st_grade_point = NULL;
					$cf_total = 0;
					$subjects = db_query(
						"SELECT * from $subject_table;"
					);
					foreach($subjects as $subject){
						$fm_def = NULL;
						$full_marks_table = 'essa_'.$session_id.'_exam_full_marks';
						$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($exam_code).'_'.$form_state['values']['class'];
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
											array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $form_state['values']['class'], ':si' => $subject->sub_id)
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
										array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $form_state['values']['class'], ':si' => $subject->sub_id)
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
							'#markup' => '<h3 style = "text-align: center; display: inline-block;"><b>'.round($cf_total).'</b></span></h3>',
						);
					}
					$weight_row[$st->adm_no][$st->adm_no][] =  $cf_total_col[$st->adm_no];
					$row[$st->adm_no][$st->adm_no][] =  $total_col[$st->adm_no];
					$grade_row[$st->adm_no][$st->adm_no][] =  $grade_total_col[$st->adm_no];
					$grade_point_row[$st->adm_no][$st->adm_no][] =  $gp_total_col[$st->adm_no];
				}
				$subjects = db_query(
					"SELECT * from $subject_table;"
				);
				foreach($subjects as $subject){
					$fm_def = NULL;
					$full_marks_table = 'essa_'.$session_id.'_exam_full_marks';
					$full_marks = db_query(
						"SELECT * from $full_marks_table where term_id = :ti and exam_code = :ec and class = :cl and subject_id = :si;",
						array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $form_state['values']['class'], ':si' => $subject->sub_id)
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
				
				$form['sec_wrapper']['marks_wrapper']['vt'] = array(
					'#type' => 'vertical_tabs',
				);
				$form['sec_wrapper']['marks_wrapper']['mw'] = array(
					'#type' => 'fieldset',
					'#title' => 'Marks Obtained',
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
					'#group' => 'vt'
				);
				$form['sec_wrapper']['marks_wrapper']['mw']['fm_tab'] = array(
					'#theme' => 'full_marks_table',
					'rows' => $fm_row,
				);
				$form['sec_wrapper']['marks_wrapper']['mw']['tab'] = array(
					'#theme' => 'student_marks_table',
					'rows' => $row,
				);
				$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$exam_code.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'.csv';
				$form['sec_wrapper']['marks_wrapper']['mw']['download_marks'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>'.l(t('Download'), $path).'</h3>',
				);
				
				$get_weight = db_query(
					"SELECT * from $master_exam_table where exam_code = :ec and term = :t;",
					array(':ec' => $exam_code, ':t' => $term_id)
				);
				foreach($get_weight as $gw){
					$weight = $gw->weight;
				}
				$form['sec_wrapper']['marks_wrapper']['cw'] = array(
					'#type' => 'fieldset',
					'#title' => 'Out of '.$weight,
					'#collapsible' => TRUE,
					'#collapsed' => TRUE,
					'#group' => 'vt'
				);
				$form['sec_wrapper']['marks_wrapper']['cw']['cf_tab'] = array(
					'#theme' => 'student_cf_table',
					'rows' => $weight_row,
				);
				$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$exam_code.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'_cf'.'.csv';
				$form['sec_wrapper']['marks_wrapper']['cw']['download_cf_marks'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>'.l(t('Download'), $path).'</h3>',
				);
				
				$form['sec_wrapper']['marks_wrapper']['gr'] = array(
					'#type' => 'fieldset',
					'#title' => 'Grade',
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
					'#group' => 'vt'
				);
				$form['sec_wrapper']['marks_wrapper']['gr']['gr_tab'] = array(
					'#theme' => 'student_grade_table',
					'rows' => $grade_row,
				);
				$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$exam_code.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'_grade'.'.csv';
				$form['sec_wrapper']['marks_wrapper']['gr']['download_grade'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>'.l(t('Download'), $path).'</h3>',
				);
				
				$form['sec_wrapper']['marks_wrapper']['gp'] = array(
					'#type' => 'fieldset',
					'#title' => 'Grade Point',
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
					'#group' => 'vt'
				);
				$form['sec_wrapper']['marks_wrapper']['gp']['gp_tab'] = array(
					'#theme' => 'student_gp_table',
					'rows' => $grade_point_row,
				);
				$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$exam_code.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'_gp'.'.csv';
				$form['sec_wrapper']['marks_wrapper']['gp']['download_gp_marks'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>'.l(t('Download'), $path).'</h3>',
				);
				
				$form['sec_wrapper']['marks_wrapper']['gph'] = array(
					'#type' => 'fieldset',
					'#title' => 'Graphical Analysis(per subject)',
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
					'#group' => 'vt'
				);
				
				$subject_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
				$sub_op = array('--Select--');
				$subjects = db_query(
					"SELECT * from $subject_table;"
				);
				foreach($subjects as $subject){
					$sub_op[$subject->sub_id] = $subject->sub_name;
				}
				$form['sec_wrapper']['marks_wrapper']['gph']['subj'] = array(
					'#type' => 'select',
					'#title' => 'Select a Subject',
					'#options' => $sub_op,
					'#ajax' => array(
						'event' => 'change',
						'callback' => 'display_graph_ajax',
						'wrapper' => 'graph_wrapper',
						'method' => 'replace',
						'effect' => 'fade',
					),
				);
				
				$form['sec_wrapper']['marks_wrapper']['gph']['graph_wrapper'] = array(
					'#type' => 'container',
					'#prefix' => '<div id = "graph_wrapper">',
					'#suffix' => '</div>',
				);
				
				$form['sec_wrapper']['marks_wrapper']['ggph'] = array(
					'#type' => 'fieldset',
					'#title' => 'Grade Analysis(per subject)',
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
					'#group' => 'vt'
				);
				
				$form['sec_wrapper']['marks_wrapper']['ggph']['grade_subj'] = array(
					'#type' => 'select',
					'#title' => 'Select a Subject',
					'#options' => $sub_op,
					'#ajax' => array(
						'event' => 'change',
						'callback' => 'display_grade_graph_ajax',
						'wrapper' => 'grade_graph_wrapper',
						'method' => 'replace',
						'effect' => 'fade',
					),
				);
				
				$form['sec_wrapper']['marks_wrapper']['ggph']['grade_graph_wrapper'] = array(
					'#type' => 'container',
					'#prefix' => '<div id = "grade_graph_wrapper">',
					'#suffix' => '</div>',
				);
				
				$form['sec_wrapper']['marks_wrapper']['color_code'] = array(
					'#type' => 'markup',
					'#markup' => '<div style = "width: 50%; float: right;">
						<h4 style = "text-align: right;"><span style = "text-align: center; display: inline-block; background: GREEN;color: GREEN; padding: 3px;">3</span> - Grade A1 &nbsp;&nbsp;
						<span style = "text-align: center; display: inline-block; background: #FF8C00;color: #FF8C00; padding: 3px;">3</span> - Grade D &nbsp;&nbsp;
						<span style = "text-align: center; display: inline-block; background: RED;color: RED; padding: 3px;">3</span> - Grade E1, Grade E2</h4>
					</div>',
				);
				
				$flag =0;
				$exam_state = db_query(
					"SELECT * from $exam_status_table where term_id = :ti and exam_code = :ec and class = :cl and sec = :sec;",
					array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
				);
				foreach($exam_state as $es){
					if($es->generate_result_status == TRUE){
						$flag =1;
					}
				}
				if($flag == 0){
					$form['sec_wrapper']['marks_wrapper']['msg'] = array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "color: RED"><b>After generating the result you won\'t be able to edit marks for this exam. Please confirm all marks records before clicking on "Generate" button.</b></h3>',
					);
					$form['sec_wrapper']['marks_wrapper']['save'] = array(
						'#type' => 'submit',
						'#value' => 'Generate',
					);
					$form['sec_wrapper']['marks_wrapper']['generate_term_result'] = array(
						'#type' => 'submit',
						'#value'  => 'Generate Term Result',
						'#submit' => array('generate_term_result'),
					);
				}else{
					$form['sec_wrapper']['marks_wrapper']['msg'] = array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "color: GREEN"><b>Result has been successfully generated for this exam.</b></h3>',
					);
					$form['sec_wrapper']['marks_wrapper']['generate_term_result'] = array(
						'#type' => 'submit',
						'#value'  => 'Generate Term Result',
						'#submit' => array('generate_term_result'),
					);
				}
				if(variable_get('result_'.$term_id) == TRUE){
					$form['fs'] = array(
						'#type' => 'fieldset',
						'#title' => 'Download Term Result',
						'#collapsible' => TRUE,
						'#collapsed' => TRUE,
					);
					$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'.csv';
					$form['fs']['download'.$form_state['values']['class'].$form_state['values']['sec']] = array(
						'#type' => 'markup',
						'#markup' => '<h3>'.l(t('Download - '.$form_state['values']['class'].'-'.$form_state['values']['sec']), $path).'</h3>',
					);
				}
			}
		}
		$sub_names = array_unique($sub_names);
		variable_set('upload_marks_sub'.$user->uid, $sub_names);
	}else{
		//******************************************This code is for exam dept***************************************
		//******************************************This code is for exam dept***************************************
		//******************************************This code is for exam dept***************************************
		//******************************************This code is for exam dept***************************************
		//******************************************This code is for exam dept***************************************
		//******************************************This code is for exam dept***************************************
		//******************************************This code is for exam dept***************************************
		//******************************************This code is for exam dept***************************************
		$form['term_id'] = array(
			'#type' => 'value',
			'#value' => $term_id,
		);
		
		$form['exam_code'] = array(
			'#type' => 'value',
			'#value' => $exam_code,
		);
		$class_list = array('--Select--');
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
		$ex_class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
			array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
		foreach($ex_class_list as $c){
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
					'callback' => 'display_marks_ajax',
					'wrapper' => 'marks_wrapper',
					'method' => 'replace',
					'effect' => 'fade',
				),
			);
			
			$form['sec_wrapper']['marks_wrapper'] = array(
				'#type' => 'container',
				'#prefix' => '<div id = "marks_wrapper">',
				'#suffix' => '</div>',
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
			if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
				create_download($form, $form_state);
				$subject_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
				$students = db_query(
					"SELECT * from $master_student_table where class = :cl and section = :sec order by exam_roll_no;",
					array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
				);
				foreach($students as $st){
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
								'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
							),
						),
					);
					$total = 0;
					$fm_total = 0;
					$cf_total = 0;
					$subjects = db_query(
						"SELECT * from $subject_table;"
					);
					foreach($subjects as $subject){
						$fm_def = NULL;
						$full_marks_table = 'essa_'.$session_id.'_exam_full_marks';
						$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($exam_code).'_'.$form_state['values']['class'];
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
											array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $form_state['values']['class'], ':si' => $subject->sub_id)
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
										array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $form_state['values']['class'], ':si' => $subject->sub_id)
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
							'#markup' => '<h3 style = "text-align: center; display: inline-block;"><b>'.round($cf_total).'</b></span></h3>',
						);
					}
					$weight_row[$st->adm_no][$st->adm_no][] =  $cf_total_col[$st->adm_no];
					$row[$st->adm_no][$st->adm_no][] =  $total_col[$st->adm_no];
					$grade_row[$st->adm_no][$st->adm_no][] =  $grade_total_col[$st->adm_no];
					$grade_point_row[$st->adm_no][$st->adm_no][] =  $gp_total_col[$st->adm_no];
				}
				$subjects = db_query(
					"SELECT * from $subject_table;"
				);
				foreach($subjects as $subject){
					$fm_def = NULL;
					$full_marks_table = 'essa_'.$session_id.'_exam_full_marks';
					$full_marks = db_query(
						"SELECT * from $full_marks_table where term_id = :ti and exam_code = :ec and class = :cl and subject_id = :si;",
						array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $form_state['values']['class'], ':si' => $subject->sub_id)
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
				
				$form['sec_wrapper']['marks_wrapper']['vt'] = array(
					'#type' => 'vertical_tabs',
				);
				$form['sec_wrapper']['marks_wrapper']['mw'] = array(
					'#type' => 'fieldset',
					'#title' => 'Marks Obtained',
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
					'#group' => 'vt'
				);
				$form['sec_wrapper']['marks_wrapper']['mw']['fm_tab'] = array(
					'#theme' => 'full_marks_table',
					'rows' => $fm_row,
				);
				$form['sec_wrapper']['marks_wrapper']['mw']['tab'] = array(
					'#theme' => 'student_marks_table',
					'rows' => $row,
				);
				$form['sec_wrapper']['marks_wrapper']['mw']['tab'] = array(
					'#theme' => 'student_marks_table',
					'rows' => $row,
				);
				$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$exam_code.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'.csv';
				$form['sec_wrapper']['marks_wrapper']['mw']['download_marks'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>'.l(t('Download'), $path).'</h3>',
				);
				
				$get_weight = db_query(
					"SELECT * from $master_exam_table where exam_code = :ec and term = :t;",
					array(':ec' => $exam_code, ':t' => $term_id)
				);
				foreach($get_weight as $gw){
					$weight = $gw->weight;
				}
				$form['sec_wrapper']['marks_wrapper']['cw'] = array(
					'#type' => 'fieldset',
					'#title' => 'Out of '.$weight,
					'#collapsible' => TRUE,
					'#collapsed' => TRUE,
					'#group' => 'vt'
				);
				$form['sec_wrapper']['marks_wrapper']['cw']['cf_tab'] = array(
					'#theme' => 'student_cf_table',
					'rows' => $weight_row,
				);
				$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$exam_code.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'_cf'.'.csv';
				$form['sec_wrapper']['marks_wrapper']['cw']['download_cf_marks'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>'.l(t('Download'), $path).'</h3>',
				);
				
				$form['sec_wrapper']['marks_wrapper']['gr'] = array(
					'#type' => 'fieldset',
					'#title' => 'Grade',
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
					'#group' => 'vt'
				);
				$form['sec_wrapper']['marks_wrapper']['gr']['gr_tab'] = array(
					'#theme' => 'student_grade_table',
					'rows' => $grade_row,
				);
				$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$exam_code.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'_grade'.'.csv';
				$form['sec_wrapper']['marks_wrapper']['gr']['download_grade'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>'.l(t('Download'), $path).'</h3>',
				);
				
				$form['sec_wrapper']['marks_wrapper']['gp'] = array(
					'#type' => 'fieldset',
					'#title' => 'Grade Point',
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
					'#group' => 'vt'
				);
				$form['sec_wrapper']['marks_wrapper']['gp']['gp_tab'] = array(
					'#theme' => 'student_gp_table',
					'rows' => $grade_point_row,
				);
				$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$exam_code.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'_gp'.'.csv';
				$form['sec_wrapper']['marks_wrapper']['gp']['download_gp_marks'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>'.l(t('Download'), $path).'</h3>',
				);
				
				$form['sec_wrapper']['marks_wrapper']['gph'] = array(
					'#type' => 'fieldset',
					'#title' => 'Graphical Analysis(per subject)',
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
					'#group' => 'vt'
				);
				
				$subject_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
				$sub_op = array('--Select--');
				$subjects = db_query(
					"SELECT * from $subject_table;"
				);
				foreach($subjects as $subject){
					$sub_op[$subject->sub_id] = $subject->sub_name;
				}
				$form['sec_wrapper']['marks_wrapper']['gph']['subj'] = array(
					'#type' => 'select',
					'#title' => 'Select a Subject',
					'#options' => $sub_op,
					'#ajax' => array(
						'event' => 'change',
						'callback' => 'display_graph_ajax',
						'wrapper' => 'graph_wrapper',
						'method' => 'replace',
						'effect' => 'fade',
					),
				);
				
				$form['sec_wrapper']['marks_wrapper']['gph']['graph_wrapper'] = array(
					'#type' => 'container',
					'#prefix' => '<div id = "graph_wrapper">',
					'#suffix' => '</div>',
				);
				
				$form['sec_wrapper']['marks_wrapper']['ggph'] = array(
					'#type' => 'fieldset',
					'#title' => 'Grade Analysis(per subject)',
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
					'#group' => 'vt'
				);
				
				$form['sec_wrapper']['marks_wrapper']['ggph']['grade_subj'] = array(
					'#type' => 'select',
					'#title' => 'Select a Subject',
					'#options' => $sub_op,
					'#ajax' => array(
						'event' => 'change',
						'callback' => 'display_grade_graph_ajax',
						'wrapper' => 'grade_graph_wrapper',
						'method' => 'replace',
						'effect' => 'fade',
					),
				);
				
				$form['sec_wrapper']['marks_wrapper']['ggph']['grade_graph_wrapper'] = array(
					'#type' => 'container',
					'#prefix' => '<div id = "grade_graph_wrapper">',
					'#suffix' => '</div>',
				);
				
				$form['sec_wrapper']['marks_wrapper']['color_code'] = array(
					'#type' => 'markup',
					'#markup' => '<div style = "width: 50%; float: right;">
						<h4 style = "text-align: right;"><span style = "text-align: center; display: inline-block; background: GREEN;color: GREEN; padding: 3px;">3</span> - Grade A1 &nbsp;&nbsp;
						<span style = "text-align: center; display: inline-block; background: #FF8C00;color: #FF8C00; padding: 3px;">3</span> - Grade D &nbsp;&nbsp;
						<span style = "text-align: center; display: inline-block; background: RED;color: RED; padding: 3px;">3</span> - Grade E1, Grade E2</h4>
					</div>',
				);
				
				$form['sec_wrapper']['marks_wrapper']['msg'] = array(
					'#type' => 'markup',
					'#markup' => '<h3 style = "color: RED"><b>After generating the result you won\'t be able to edit marks for this exam. Please confirm all marks records before clicking on "Generate" button.</b></h3>',
				);
				$flag =0;
				$exam_state = db_query(
					"SELECT * from $exam_status_table where term_id = :ti and exam_code = :ec and class = :cl and sec = :sec;",
					array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
				);
				foreach($exam_state as $es){
					if($es->generate_result_status == TRUE){
						$flag =1;
					}
				}
				if($flag == 0){
					$form['sec_wrapper']['marks_wrapper']['msg'] = array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "color: RED"><b>After generating the result you won\'t be able to edit marks for this exam. Please confirm all marks records before clicking on "Generate" button.</b></h3>',
					);
					$form['sec_wrapper']['marks_wrapper']['save'] = array(
						'#type' => 'submit',
						'#value' => 'Generate',
					);

					$form['sec_wrapper']['marks_wrapper']['generate_term_result'] = array(
						'#type' => 'submit',
						'#value'  => 'Generate Term Result',
						'#submit' => array('generate_term_result'),
					);
					
				}else{
					$form['sec_wrapper']['marks_wrapper']['msg'] = array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "color: GREEN"><b>Result has been successfully generated for this exam.</b></h3>',
					);
				}
				if(variable_get('result_'.$term_id) == TRUE){
					$form['sec_wrapper']['marks_wrapper']['fs'] = array(
						'#type' => 'fieldset',
						'#title' => 'Download Term Result',
						'#collapsible' => TRUE,
						'#collapsed' => TRUE,
					);
					$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'.csv';
					$form['sec_wrapper']['marks_wrapper']['fs']['download'.$cl->class_id.$sec] = array(
						'#type' => 'markup',
						'#markup' => '<h3>'.l(t('Download - '.$form_state['values']['class'].'-'.$form_state['values']['sec']), $path).'</h3>',
					);
				}
			}
		}
		$sub_names = array_unique($sub_names);
		variable_set('upload_marks_sub'.$user->uid, $sub_names);	
	}
	
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
	$exam_term_table = 'essa_'.$session_id.'_exam_terms';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
	$class = $form_state['values']['class'];
	$sec = $form_state['values']['sec'];
	
	variable_set('downloads'.$term_id, TRUE);
	$exams = db_query(
		"SELECT * from $master_exam_table where term = :ti;", array(':ti' => $term_id)
	);
	foreach($exams as $ex){
		$class_list = db_query("SELECT * FROM {$class_table} WHERE class_id = :ci",
			array(':ci' => $class));
		foreach($class_list as $c){
			$classes[] = $c;
		}
		
		foreach($classes as $cl){
			$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($ex->exam_code).'_'.$cl->class_id;
			$subject_table = 'essa_'.$session_id.'_subjects_'.$cl->class_id;
			$student_marks = db_query("SELECT * FROM {$marks_table} where section = :sec;", array(':sec' => $sec));
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
		$class_list = db_query("SELECT * FROM {$class_table} WHERE class_id = :ci",
			array(':ci' => $class));
		foreach($class_list as $c){
			$classes[] = $c;
		}
		foreach($classes as $cl){
			$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($ex->exam_code).'_'.$cl->class_id;
			$subject_table = 'essa_'.$session_id.'_subjects_'.$cl->class_id;
			$student = db_query("SELECT * FROM {$master_student_table} ORDER BY exam_roll_no");
			foreach($student as $st){
				$student_marks = db_query("SELECT * FROM {$marks_table} where section = :sec and adm_no = :an;", array(':sec' => $sec, ':an' => $st->adm_no));
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
		$st_name = db_query("SELECT * FROM {$master_student_table} WHERE adm_no = :an;", array(':an' => $adm_no));
		foreach($st_name as $stn){
			$student_name = $stn->student_name;
			$exam_roll_no = $stn->exam_roll_no;
		}
		$total = 0;
		foreach($rec as $sub_id => $line){
			$sub_total = 0;
			foreach($line as $marks){
				$data_csv[$adm_no][$adm_no] = $adm_no;
				$data_csv[$adm_no][$student_name] = $student_name;
				$data_csv[$adm_no][$exam_roll_no] = $exam_roll_no;
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
				$header_csv['exam_roll_no'] = 'Exam Roll No.';
				$header_csv[$marks] = $marks;
			}
			$header_csv['total'.$marks] = $sub_id;
		}
	}
	$header_csv['total'] = 'Total';
	$header_csv['grade'] = 'Overall Grade';
	$header_csv['gp'] = 'Overall Grade Point';
	
	$basic = db_query("SELECT * FROM {$basic_info_table}");
	foreach($basic as $bc){
		$school_name = $bc->nameofschool;
	}
	
	$terms = db_query("SELECT * FROM {$exam_term_table} WHERE id = :id;", array(':id' => $term_id));
	foreach($terms as $term){
		$term_name = $term->term_name;
	}
	
	$columns = count($header_csv);
	$m = 0;
	$middleval = floor(($columns-1)/2);
	$sc_header = array();
	$exam_header = array('Exam : '.$exam_code.'('.$term_name.')');
	while($columns>$m){
		if($columns%2){
			$odd = $middleval;
		}else{
      $even = $columns/2;
		}
		if($columns%2){
			if($m == $odd){
				$sc_header[$m] = $school_name;
			}else{
				$sc_header[$m] = '';
			}
		}else{
			if($m == $even){
				$sc_header[$m] = $school_name;
			}else{
				$sc_header[$m] = '';
			}
		}
		$m++;
	}
	
	$delimiter = ',';
	$enclosure = '"';
	$sec = 'A';
	foreach($classes as $class){
		for($i = 1; $i <= $class->no_of_sec; $i++){
			$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$class->class_id.'_'.$sec.'.csv';
			$handle = fopen ($path,'w');
			fputcsv($handle, $sc_header, $delimiter, $enclosure);
			fputcsv($handle, $exam_header, $delimiter, $enclosure);	
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
	//dsm($term_total);
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
	variable_set('result_'.$term_id, TRUE);
}


/**
 *Function to create downloadable excel sheet
 */
function create_download($form, &$form_state){
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$class = $form_state['values']['class'];
	$sec = $form_state['values']['sec'];
	$session_id = (string)variable_get('essa_sid');
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$exam_marks_upload_status_table = 'essa_'.$session_id.'_exam_marks_upload_status';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$exam_term_table = 'essa_'.$session_id.'_exam_terms';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$grade_table = 'essa_'.$session_id.'_exam_grade_settings';
	$full_marks_table = 'essa_'.$session_id.'_exam_full_marks';
	$subject_table = 'essa_'.$session_id.'_subjects_'.$class;
	$header = array();
	$students = db_query(
		"SELECT * from $master_student_table where class = :cl and section = :sec ORDER BY exam_roll_no;",
			array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
	);
	foreach($students as $st){
		$student_name = $st->student_name;
		$exam_roll_no = $st->exam_roll_no;
		$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($exam_code).'_'.$class;
		$marks = db_query(
			"SELECT * from $marks_table where adm_no = :an;", array(':an' => $st->adm_no)
		);
		foreach($marks as $mark){
			$total = 0;
			$fm_total = 0;
			$total_cf = 0;
			$subjects = db_query(
				"SELECT * from $subject_table;"
			);
			foreach($subjects as $subject){
				$header['adm_no'] = 'Adm No.';
				$header['student_name'] = 'Student Name';
				$header['exam_roll_no'] = 'Exam Roll No';
				$header[$subject->sub_id] = $subject->sub_name;
				$data[$mark->adm_no][$mark->adm_no] = $mark->adm_no;
				$data[$mark->adm_no][$student_name] = $student_name;
				$data[$mark->adm_no][$exam_roll_no] = $exam_roll_no;
				$data_cf[$mark->adm_no][$mark->adm_no] = $mark->adm_no;
				$data_cf[$mark->adm_no][$student_name] = $student_name;
				$data_cf[$mark->adm_no][$exam_roll_no] = $exam_roll_no;
				$data_grade[$mark->adm_no][$mark->adm_no] = $mark->adm_no;
				$data_grade[$mark->adm_no][$student_name] = $student_name;
				$data_grade[$mark->adm_no][$exam_roll_no] = $exam_roll_no;
				$data_gp[$mark->adm_no][$mark->adm_no] = $mark->adm_no;
				$data_gp[$mark->adm_no][$student_name] = $student_name;
				$data_gp[$mark->adm_no][$exam_roll_no] = $exam_roll_no;
				if($subject->type == 'Optional'){
					$flag = 0;
					$op_students = db_query(
						"SELECT * from $op_subj_student_table where adm_no = :an and sub_id = :s;",
						array(':an' => $st->adm_no, ':s' => $subject->sub_id)
					);
					foreach($op_students as $os){
						$sub_col = $subject->sub_id;
						$data[$mark->adm_no][$sub_col] = $mark->$sub_col.'';
						$total = $total+$mark->$sub_col;
						$cf_col = 'cf_'.$subject->sub_id;
						$data_cf[$mark->adm_no][$sub_col] = round($mark->$cf_col).'';
						$total_cf = $total_cf+round($mark->$cf_col);
						$grade_col = 'grade_'.$subject->sub_id;
						$data_grade[$mark->adm_no][$sub_col] = $mark->$grade_col.'';
						$grade_point_col = 'grade_point_'.$subject->sub_id;
						$data_gp[$mark->adm_no][$sub_col] = $mark->$grade_point_col.'';
						$flag = 1;
						
						$full_marks = db_query(
							"SELECT * from $full_marks_table where term_id = :ti and exam_code = :ec and class = :cl and subject_id = :si;",
							array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $form_state['values']['class'], ':si' => $subject->sub_id)
						);
						foreach($full_marks as $fm){
							$fm_total = $fm_total + $fm->full_marks;
						}
					}
					if($flag == 0){
						$sub_col = $subject->sub_id;
						$data[$mark->adm_no][$sub_col] = '';
						$cf_col = 'cf_'.$subject->sub_id;
						$data_cf[$mark->adm_no][$sub_col] = '';
						$grade_col = 'grade_'.$subject->sub_id;
						$data_grade[$mark->adm_no][$sub_col] = '';
						$grade_point_col = 'grade_point_'.$subject->sub_id;
						$data_gp[$mark->adm_no][$sub_col] = '';
					}
				}else{
					$sub_col = $subject->sub_id;
					$total = $total+$mark->$sub_col;
					$data[$mark->adm_no][$sub_col] = $mark->$sub_col.'';
					$cf_col = 'cf_'.$subject->sub_id;
					$data_cf[$mark->adm_no][$sub_col] = round($mark->$cf_col).'';
					$total_cf = $total_cf+round($mark->$cf_col);
					$grade_col = 'grade_'.$subject->sub_id;
					$data_grade[$mark->adm_no][$sub_col] = $mark->$grade_col.'';
					$grade_point_col = 'grade_point_'.$subject->sub_id;
					$data_gp[$mark->adm_no][$sub_col] = $mark->$grade_point_col.'';
					$full_marks = db_query(
						"SELECT * from $full_marks_table where term_id = :ti and exam_code = :ec and class = :cl and subject_id = :si;",
						array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $form_state['values']['class'], ':si' => $subject->sub_id)
					);
					foreach($full_marks as $fm){
						$fm_total = $fm_total + $fm->full_marks;
					}
				}
				$total_marks[$mark->adm_no] = $total;
				$total_cf_marks[$mark->adm_no] = $total_cf;
			}
		}
	}
	
	$grade_header = $header;
	$header['total'] = 'Total';
	foreach($total_marks as $adm_no => $tm){
		$data[$adm_no]['total'.$adm_no] = $tm.'';
		$total_percent = round($tm/$fm_total*100);
		$grades = db_query("
			SELECT * from {$grade_table};"
		);
		foreach($grades as $gr){
			if($total_percent >= $gr->marks_from && $total_percent <= $gr->marks_to){
				$data_grade[$adm_no]['total'.$adm_no] = $gr->grade;
				$data_gp[$adm_no]['total'.$adm_no] = $gr->grade_point;
			}
		}
	}
	
	foreach($total_cf_marks as $adm_no => $tm){
		$data_cf[$adm_no]['total'.$adm_no] = round($tm).'';
	}
	$delimiter = ',';
	$enclosure = '"';
	$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$exam_code.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'.csv';
	$handle = fopen ($path,'w');
	
	$basic = db_query("SELECT * FROM {$basic_info_table}");
	foreach($basic as $bc){
		$school_name = $bc->nameofschool;
	}
	
	$terms = db_query("SELECT * FROM {$exam_term_table} WHERE id = :id;", array(':id' => $term_id));
	foreach($terms as $term){
		$term_name = $term->term_name;
	}
	
	$columns = count($header);
	$i = 0;
	$middleval = floor(($columns-1)/2);
	$sc_header = array();
	$exam_header = array('Exam : '.$exam_code.'('.$term_name.')');
	while($columns>$i){
		if($columns%2){
			$odd = $middleval;
		}else{
      $even = $columns/2;
		}
		if($columns%2){
			if($i == $odd){
				$sc_header[$i] = $school_name;
			}else{
				$sc_header[$i] = '';
			}
		}else{
			if($i == $even){
				$sc_header[$i] = $school_name;
			}else{
				$sc_header[$i] = '';
			}
		}
		$i++;
	}
	
	fputcsv($handle, $sc_header, $delimiter, $enclosure);
	fputcsv($handle, $exam_header, $delimiter, $enclosure);
	
	fputcsv($handle, $header, $delimiter, $enclosure);
	foreach ($data as $adm_no => $line){
		fputcsv($handle, $line, $delimiter, $enclosure);
	}
	fclose($handle);
	
	$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$exam_code.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'_cf'.'.csv';
	$handle = fopen ($path,'w');
	fputcsv($handle, $sc_header, $delimiter, $enclosure);
	fputcsv($handle, $exam_header, $delimiter, $enclosure);
	fputcsv($handle, $header, $delimiter, $enclosure);
	foreach ($data_cf as $adm_no => $line){
		fputcsv($handle, $line, $delimiter, $enclosure);
	}
	fclose($handle);
	
	$grade_header[] = 'Overall Grade';
	$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$exam_code.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'_grade'.'.csv';
	$handle = fopen ($path,'w');
	fputcsv($handle, $sc_header, $delimiter, $enclosure);
	fputcsv($handle, $exam_header, $delimiter, $enclosure);
	fputcsv($handle, $header, $delimiter, $enclosure);
	foreach ($data_grade as $adm_no => $line){
		fputcsv($handle, $line, $delimiter, $enclosure);
	}
	fclose($handle);
	
	$path = drupal_get_path('module','exam').'/downloads/'.$term_id.'_'.$exam_code.'_'.$form_state['values']['class'].'_'.$form_state['values']['sec'].'_gp'.'.csv';
	$handle = fopen ($path,'w');
	fputcsv($handle, $sc_header, $delimiter, $enclosure);
	fputcsv($handle, $exam_header, $delimiter, $enclosure);
	fputcsv($handle, $header, $delimiter, $enclosure);
	foreach ($data_gp as $adm_no => $line){
		fputcsv($handle, $line, $delimiter, $enclosure);
	}
	fclose($handle);
}

/**
 *Implements page callback function generate_result
 */
function generate_result_submit($form, &$form_state){
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$class = $form_state['values']['class'];
	$sec = $form_state['values']['sec'];
	$sub_id = $form_state['values']['grade_subj'];
	$session_id = (string)variable_get('essa_sid');
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$exam_marks_upload_status_table = 'essa_'.$session_id.'_exam_marks_upload_status';
	$subject_table = 'essa_'.$session_id.'_subjects_'.$class;
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
	
	$upload_status = array();
	$class_sub = array();
	$upload_state = db_query(
		"SELECT * from $exam_marks_upload_status_table where term_id = :ti and exam_code = :ec and class = :cl and sec = :sec;",
		array(':ti' => $term_id, ':ec' => $exam_code, ':cl' => $class, ':sec' => $sec)
	);
	foreach($upload_state as $us){
		$upload_status[$us->sub_id] = $us->sub_id;
	}
	
	$subjects = db_query(
		"SELECT * from $subject_table;"
	);
	foreach($subjects as $subject){
		$class_sub[$subject->sub_id] = $subject->sub_id;
	}
	
	$flag = 0;
	if($upload_status != $class_sub){
		$sub_diff = array_diff($class_sub, $upload_status);
		foreach($sub_diff as $sd){
			drupal_set_message('Marks for subject - <b>'.$sd.'</b> has not been uploaded.','warning');
		}
		$flag = 1;
	}
	
	if($flag == 1){
		drupal_set_message('Result can\'t be generated now.Please upload & verify all the marks.','error');
	}else{
		global $user;
		db_merge($exam_status_table)
			->key(array('term_id' => $term_id, 'exam_code' => $exam_code, 'class' => $class, 'sec' => $sec,))
			->fields (array(
					'term_id' => $term_id,
					'exam_code' => $exam_code,
					'class' => $class,
					'sec' => $sec,
					'timestamp' => time(),
					'uid' => $user->uid,
					'generate_result_status' => TRUE,
					'send_for_review' => FALSE,
				)
			)
		->execute();
		variable_set($form_state['values']['term_id'].$form_state['values']['exam_code'].$class.'_result_generate_status', '0');
		drupal_set_message('The result for class - <b>'.$class.'</b> Section - <b>'.$sec.'</b> was successfully generated','status');
		
		$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($exam_code).'_'.$class;
		$marks = db_query(
			"SELECT * from $marks_table;"
		);
		foreach($marks as $mark){
			$subjects = db_query(
				"SELECT * from $subject_table;"
			);
			$subject_table = 'essa_'.$session_id.'_subjects_'.$class;
			foreach($subjects as $subject){
				$op_subjects = db_query(
					"SELECT * from $subject_table where sub_id = :si;", array(':si' => $subject->sub_id)
				);
				foreach($op_subjects as $ops){
					if($ops->type == 'Optional'){
						$op_students = db_query(
							"SELECT * from $op_subj_student_table where adm_no = :an and sub_id = :s;",
							array(':an' => $mark->adm_no, ':s' => $subject->sub_id)
						);
						foreach($op_students as $os){
							$sub_id = $subject->sub_id;
							$cf_col = 'cf_'.$sub_id;
							$st_cf[$mark->adm_no][$sub_id] = round($mark->$cf_col);
							$ex_sub[$mark->adm_no][$sub_id] = $subject->sub_name;
						}
					}else{
						$sub_id = $subject->sub_id;
						$cf_col = 'cf_'.$sub_id;
						$st_cf[$mark->adm_no][$sub_id] = round($mark->$cf_col);
						$ex_sub[$mark->adm_no][$sub_id] = $subject->sub_name;
					}
				}
			}
		}
		
		include_once(drupal_get_path('module', 'exam') . '/pChart/class/pData.class.php');
		include_once(drupal_get_path('module', 'exam') . '/pChart/class/pDraw.class.php');
		include_once(drupal_get_path('module', 'exam') . '/pChart/class/pImage.class.php');
		include_once(drupal_get_path('module', 'exam') . '/pChart/class/pPie.class.php');
		$exams = db_query(
			"SELECT * from $master_exam_table where exam_code = :ec;", array(':ec' => $exam_code)
		);
		foreach($exams as $ex){
			$weight = $ex->weight;
		}
		foreach($st_cf as $adm_no => $marks){
			error_reporting(0);
			$path = drupal_get_path('module', 'exam') . '/pChart/class/pData.class.php';
			 /* Create and populate the pData object */
			 $MyData = new pData(); 
			 $MyData->loadPalette(drupal_get_path('module', 'exam') . "/pChart/palettes/navy.color",TRUE);
			 $MyData->addPoints($marks, 'marks');
			 $MyData->setAxisName(0,"Marks");
			 $MyData->addPoints($ex_sub[$adm_no],"Labels");
			 $MyData->setSerieDescription("Labels","Subjects");
			 $MyData->setAbscissa("Labels");
			 /* Create the pChart object */
			 $myPicture = new pImage(700,230,$MyData);
			//dsm($MyData);
			 /* Draw the background */
			 $Settings = array("R"=>0, "G"=>0, "B"=>0, "Dash"=>0, "DashR"=>0, "DashG"=>0, "DashB"=>0);
			 $myPicture->drawFilledRectangle(0,0,700,230,$Settings);
			
			 /* Overlay with a gradient */
			 $Settings = array("StartR"=>255, "StartG"=>255, "StartB"=>255, "EndR"=>255, "EndG"=>255, "EndB"=>255, "Alpha"=>255);
			 $myPicture->drawGradientArea(0,0,700,230,DIRECTION_VERTICAL,$Settings);
			 $myPicture->drawGradientArea(0,0,700,20,DIRECTION_VERTICAL,array("StartR"=>0,"StartG"=>0,"StartB"=>0,"EndR"=>50,"EndG"=>50,"EndB"=>50,"Alpha"=>80));
			
			 /* Add a border to the picture */
			 $myPicture->drawRectangle(0,0,699,229,array("R"=>200,"G"=>200,"B"=>50));
			 
			 /* Write the picture title */ 
			 $myPicture->setFontProperties(array(
					"FontName" => drupal_get_path('module', 'exam') . '/pChart' . "/fonts/Silkscreen.ttf",
					"FontSize" => 6));
			 $myPicture->drawText(10,13,"Subject wise Performance Graph",array("R"=>255,"G"=>255,"B"=>255));
			
			 /* Write the chart title */
			 $myPicture->setFontProperties(array(
					"FontName" => drupal_get_path('module', 'exam') . '/pChart' . "/fonts/Forgotte.ttf",
					"FontSize" => 9));
			 $myPicture->drawText(155,55,"Marks(out of - ".$weight.")",array("FontSize"=>20,"Align"=>TEXT_ALIGN_BOTTOMMIDDLE));
			
			 /* Draw the scale and the 1st chart */
			 $myPicture->setGraphArea(60,60,670,190);
			 $myPicture->drawFilledRectangle(60,60,670,190,array("R"=>255,"G"=>255,"B"=>255,"Surrounding"=>-100,"Alpha"=>10));
			 $myPicture->setFontProperties(array(
					"FontName" => drupal_get_path('module', 'exam') . '/pChart' . "/fonts/pf_arma_five.ttf",
					"FontSize" => 6));
			 $myPicture->drawScale(array("DrawSubTicks"=>TRUE));
			 $myPicture->setShadow(TRUE,array("X"=>1,"Y"=>1,"R"=>0,"G"=>0,"B"=>0,"Alpha"=>10));
			 $myPicture->drawBarChart();
			 $myPicture->setShadow(TRUE);
			
			 /* Write the chart legend */
			 //$myPicture->drawLegend(600,210,array("Style"=>LEGEND_NOBORDER,"Mode"=>LEGEND_HORIZONTAL));
			 
			 $myPicture->setShadow(TRUE,array("X"=>1,"Y"=>1,"R"=>0,"G"=>0,"B"=>0,"Alpha"=>10));
			 
			 $myPicture->setFontProperties(array(
					"FontName" => drupal_get_path('module', 'exam') . '/pChart' . "/fonts/Forgotte.ttf",
					"FontSize" => 11));
			
			 /* Write a label over the chart */
			 /* Write a label over the chart */
			 $LabelSettings = array("TitleMode"=>LABEL_TITLE_BACKGROUND,"DrawSerieColor"=>FALSE,"TitleR"=>255,"TitleG"=>255,"TitleB"=>255);
			 $myPicture->Render('sites/default/files/exam/'.$term_id.'/'.$exam_code.'/'.str_replace('/','#',$adm_no).'.png');
		}
	}
	menu_rebuild();
}

/**
 *Function to display graphical grade analysis per subject
 */
function display_grade_graph_ajax($form, &$form_state){
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$class = $form_state['values']['class'];
	$sec = $form_state['values']['sec'];
	$sub_id = $form_state['values']['grade_subj'];
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
	
	$form['sec_wrapper']['marks_wrapper']['ggph']['grade_graph_wrapper']['grade_column'] =  array(
		'#theme' => 'visualization',
		'#options' => $options_column,
	);
	return $form['sec_wrapper']['marks_wrapper']['ggph']['grade_graph_wrapper'];
}

/**
 *Function to display graphical analysis per subject
 */
function display_graph_ajax($form, &$form_state){
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$class = $form_state['values']['class'];
	$sec = $form_state['values']['sec'];
	$sub_id = $form_state['values']['subj'];
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
	
	$form['sec_wrapper']['marks_wrapper']['gph']['graph_wrapper']['column'] =  array(
		'#theme' => 'visualization',
		'#options' => $options_column,
	);
	return $form['sec_wrapper']['marks_wrapper']['gph']['graph_wrapper'];
}

/**
 *Implements ajax callback - display_student_ajax
 */
function display_marks_ajax($form, &$form_state){
	return $form['sec_wrapper']['marks_wrapper'];
}

/**
 *Implements ajax callback.
 */
function display_sections_ajax($form, &$form_state){
	//dsm($form_state);
	return $form['sec_wrapper'];
}

/**
 *Theme function
 */
function theme_student_marks_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Adm No.'), t('Exam Roll No.'), t('Name'));
	global $user;
	$sub_names = array();
	$sub_names = variable_get('upload_marks_sub'.$user->uid);
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
function theme_student_cf_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Adm No.'), t('Exam Roll No.'), t('Name'));
	global $user;
	$sub_names = array();
	$sub_names = variable_get('upload_marks_sub'.$user->uid);
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
function theme_student_grade_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Adm No.'), t('Exam Roll No.'), t('Name'));
	global $user;
	$sub_names = array();
	$sub_names = variable_get('upload_marks_sub'.$user->uid);
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
function theme_student_gp_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Adm No.'), t('Exam Roll No.'), t('Name'));
	global $user;
	$sub_names = array();
	$sub_names = variable_get('upload_marks_sub'.$user->uid);
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
function theme_full_marks_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t(''));
	global $user;
	$sub_names = array();
	$sub_names = variable_get('upload_marks_sub'.$user->uid);
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