<?php
function display_result($form, &$form_state, $student_uid){
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
	$class_list_table = 'essa_'.$session_id.'_class_list';
	$master_staff_table = 'essa_'.$session_id.'_master_staff_table';
	$class_teacher_table = 'essa_'.$session_id.'_class_teacher';
	$full_marks_table = 'essa_'.$session_id.'_exam_full_marks';
	$di_group_name_table = 'essa_'.$session_id.'_di_group_name';
	$di_group_section_table = 'essa_'.$session_id.'_di_group_section';
	$di_sa_table = 'essa_'.$session_id.'_di_sa';
	$di_indicators_table = 'essa_'.$session_id.'_di_indicators';
	$sub_names = array();
	global $user;
	
	$st_marks = array();
	$st_sum_term = array();
	$st_term = array();
	$st_exam = array();
	
	$exams = db_query(
		"SELECT * from $master_exam_table order by term;"
	);
	foreach($exams as $ex){
		$flag =0;
		$students = db_query(
			"SELECT * from $master_student_table where uid=:uid;",
			array(':uid' => $student_uid)
		);
		foreach($students as $st){
			$class = $st->class;
			$adm_no = $st->adm_no;
			$exam_state = db_query(
				"SELECT * from $exam_status_table where term_id = :ti and exam_code = :ec and class = :cl and sec = :sec;",
				array(':ti' => $ex->term, ':ec' => $ex->exam_code, ':cl' => $st->class, ':sec' => $st->section)
			);
			foreach($exam_state as $es){
				if($es->publish_result_status == TRUE){
					$st_exam[$ex->exam_code] = $ex->term;
					$weight = $ex->weight;
				}
			}
		}
		if(variable_get('publish_term_result_'.$ex->term) == TRUE){
			$st_term[$ex->term] = $ex->term;
		}
	}
	
	$terms = db_query(
		"SELECT * from $term_table;"
	);
	foreach($terms as $term){
		if($term->term_1 != NULL){
			if(variable_get('publish_term_result_'.$term->id) == TRUE){
				$st_sum_term[$term->id] = $term->id;
			}
		}
	}
	$form['#attached']['css'] = array(
    drupal_get_path('module', 'field_group') . '/horizontal-tabs/horizontal-tabs.css',
  );
	
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'field_group') . '/horizontal-tabs/horizontal-tabs.js',
  );
	$form['ht'] = array(
		'#type' => 'horizontal_tabs',
	);
	foreach($st_exam as $exam_code => $term_id){
		$terms = db_query("SELECT * FROM {$term_table} where id=:id", array(":id" => $term_id));
		foreach($terms as $term){
			$term_name = $term -> term_name;
		}
		$form[$term_id] = array(
			'#type' => 'fieldset',
			'#title' => $term_name,
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
			'#group' => 'ht',
		);
		
		$form[$term_id]['vt'] = array(
			'#type' => 'vertical_tabs',
		);
	}
	
	foreach($st_term as $term_id){
		$terms = db_query("SELECT * FROM {$term_table} where id=:id", array(":id" => $term_id));
		foreach($terms as $term){
			$term_name = $term -> term_name;
		}
		$form[$term_id]['vt']['term_result'] = array(
			'#type' => 'fieldset',
			'#title' => $term_name.' - Result',
			'#collapsible' => TRUE,
			'#collapsed' => FALSE,
		);
		$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$class;
		$marks = db_query(
			"SELECT * from $marks_table where adm_no = :an;", array(':an' => $adm_no)
		);
		foreach($marks as $mark){
			$subject_table = 'essa_'.$session_id.'_subjects_'.$class;
			$subjects = db_query(
				"SELECT * from $subject_table;"
			);
			foreach($subjects as $subject){
				$sub_id = $subject->sub_id;
				$st_marks[$term_id][$sub_id] = $mark->$sub_id;
				$grade_col = 'grade_'.$sub_id;
				$st_grade[$term_id][$sub_id] = $mark->$grade_col;
				$gp_col = 'grade_point_'.$sub_id;
				$st_grade_point[$term_id][$sub_id] = $mark->$gp_col;
			}
		}
	}
	
	$sub_count = 0;
	foreach($st_term as $term_id){
		$data = array();
		foreach($st_marks as $excode=>$marks){
			foreach($marks as $subject => $mark){
				if($mark != NULL){
					$data[] = array('subject' => $subject, 'marks' => $mark);
				}
				
				$op_subjects = db_query(
					"SELECT * from $subject_table where sub_id = :si;", array(':si' => $subject)
				);
				foreach($op_subjects as $ops){
					if($ops->type == 'Optional'){
						$op_students = db_query(
							"SELECT * from $op_subj_student_table where adm_no = :an and sub_id = :s;",
							array(':an' => $adm_no, ':s' => $subject)
						);
						foreach($op_students as $os){
							$std_marks[$subject] = $mark;
							$sub_count = $sub_count+1;
						}
					}else{
						$std_marks[$subject] = $mark;
						$sub_count = $sub_count+1;
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
					'labelField' => 'subject',
				),
				'data' => $data,
				'type' => 'column',
			);
			
			$form[$term_id]['vt']['term_result']['column'.$term_id] =  array(
				'#theme' => 'visualization',
				'#options' => $options_column,
			);
			$total = 0;
			foreach($std_marks as $st_subject=>$st_mark){
				$marks = db_query(
					"SELECT * from $marks_table where adm_no = :an;", array(':an' => $adm_no)
				);
				foreach($marks as $mark){
					$grade_col = 'grade_'.$st_subject;
					$st_grade = $mark->$grade_col;
					$gp_col = 'grade_point_'.$st_subject;
					$st_grade_point = $mark->$gp_col;
					$total = $total+round($st_mark); 
				}
				
				$fm_row[$st_subject] = array(
					'#tree' =>TRUE,
					$st_subject => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'.$st_subject.'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'.round($st_mark).'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'.$st_grade.'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'.$st_grade_point.'</h3>',
						),
					),
				);
			}
			$weight = 0;
			$exams = db_query(
				"SELECT * from $master_exam_table where term = :t;", array(':t' => $term_id)
			);
			foreach($exams as $ex){
				$weight = $weight + $ex->weight;
			}
			$fm_total = $sub_count*$weight;
			$total_percent = (round($total)/$fm_total*100);
			$grades = db_query("
				SELECT * from {$grade_table};"
			);
			foreach($grades as $gr){
				if($total_percent >= $gr->marks_from && $total_percent <= $gr->marks_to){
					$total_grade = $gr->grade;
					$total_grade_point = $gr->grade_point;
				}
			}
			$total_row['total'] = array(
				'#tree' =>TRUE,
				'total' => array(
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: left !important;">Total</h3>',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: left !important;">'.round($total).'</h3>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: left !important;">'.$total_grade.'</h3>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: left !important;">'.$total_grade_point.'</h3>',
					),
				),
			);
			$fm_row = array_merge($fm_row, $total_row);
			$form[$term_id]['vt']['term_result']['marks_tab'.$term_id] = array(
				'#theme' => 'this_student_marks_table',
				'rows' => $fm_row,
			);
			
			$options_column = array(
				'title' => 'Marks',
				'fields' => array(
					'marks' => array(
						'label' => t('Marks'),
						'enabled' => TRUE,
					),
				),
				'xAxis' => array(
					'labelField' => 'subject',
				),
				'data' => $data,
				'type' => 'pie',
			);
			
			$form[$term_id]['vt']['term_result']['pie'.$term_id] =  array(
				'#theme' => 'visualization',
				'#options' => $options_column,
				'#suffix' => '<script type="text/javascript">'
					. 'jQuery(\'.visualization-chart\').css( \'width\', \'100%\' );'
					. 'jQuery(\'.visualization-chart\').css( \'max-width\', \'1000px\' );'
					. '</script>',
			);
			
			$form[$term_id]['vt']['term_result']['report_card'] = array(
				'#type' => 'submit',
				'#value' => 'Download Report Card',
				'#submit' => array('print_report_card'),
				'#name' => $adm_no.'%'.$term_id,
			);
		}
	}
	
	//---------------------------Displaying Sum Term Result------------------------------
	//---------------------------Displaying Sum Term Result------------------------------
	//---------------------------Displaying Sum Term Result------------------------------
	//---------------------------Displaying Sum Term Result------------------------------
	//---------------------------Displaying Sum Term Result------------------------------
	//---------------------------Displaying Sum Term Result------------------------------
	//---------------------------Displaying Sum Term Result------------------------------
	$total_weight = 0;
	foreach($st_sum_term as $term_id){
		$terms = db_query(
			"SELECT * from $term_table where id = :ti;", array(':ti' => $term_id)
		);
		foreach($terms as $term){
			$term_sum[] = $term->term_1;
			$term_sum[] = $term->term_2;
		}
		
		foreach($term_sum as $term_sum_id){
			$exams = db_query(
				"SELECT * from $master_exam_table where term = :ti;", array(':ti' => $term_sum_id)
			);
			foreach($exams as $ex){
				$total_weight = $total_weight+$ex->weight;
			}
		}
		$terms = db_query("SELECT * FROM {$term_table} where id=:id", array(":id" => $term_id));
		foreach($terms as $term){
			$term_name = $term -> term_name;
		}
		
		$form[$term_id] = array(
			'#type' => 'fieldset',
			'#title' => $term_name,
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
			'#group' => 'ht',
		);
		
		$form[$term_id]['vt'] = array(
			'#type' => 'vertical_tabs',
		);
		$form[$term_id]['vt']['term_result'] = array(
			'#type' => 'fieldset',
			'#title' => $term_name.' - Result',
			'#collapsible' => TRUE,
			'#collapsed' => FALSE,
		);
		$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$class;
		$marks = db_query(
			"SELECT * from $marks_table where adm_no = :an;", array(':an' => $adm_no)
		);
		foreach($marks as $mark){
			$subject_table = 'essa_'.$session_id.'_subjects_'.$class;
			$subjects = db_query(
				"SELECT * from $subject_table;"
			);
			foreach($subjects as $subject){
				$sub_id = $subject->sub_id;
				$st_sum_marks[$term_id][$sub_id] = $mark->$sub_id;
				$grade_col = 'grade_'.$sub_id;
				$st_sum_grade[$term_id][$sub_id] = $mark->$grade_col;
				$gp_col = 'grade_point_'.$sub_id;
				$st_sum_grade_point[$term_id][$sub_id] = $mark->$gp_col;
			}
		}
	}
	
	$sub_count = 0;
	foreach($st_sum_term as $term_id){
		$data = array();
		foreach($st_sum_marks as $excode=>$marks){
			foreach($marks as $subject => $mark){
				if($mark != NULL){
					$data[] = array('subject' => $subject, 'marks' => $mark);
				}
				
				$op_subjects = db_query(
					"SELECT * from $subject_table where sub_id = :si;", array(':si' => $subject)
				);
				foreach($op_subjects as $ops){
					if($ops->type == 'Optional'){
						$op_students = db_query(
							"SELECT * from $op_subj_student_table where adm_no = :an and sub_id = :s;",
							array(':an' => $adm_no, ':s' => $subject)
						);
						foreach($op_students as $os){
							$std_marks[$subject] = $mark;
							$sub_count = $sub_count+1;
						}
					}else{
						$std_marks[$subject] = $mark;
						$sub_count = $sub_count+1;
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
					'labelField' => 'subject',
				),
				'data' => $data,
				'type' => 'column',
			);
			
			$form[$term_id]['vt']['term_result']['column'.$term_id] =  array(
				'#theme' => 'visualization',
				'#options' => $options_column,
			);
			$total = 0;
			foreach($std_marks as $st_subject=>$st_mark){
				$marks = db_query(
					"SELECT * from $marks_table where adm_no = :an;", array(':an' => $adm_no)
				);
				foreach($marks as $mark){
					$grade_col = 'grade_'.$st_subject;
					$st_grade = $mark->$grade_col;
					$gp_col = 'grade_point_'.$st_subject;
					$st_grade_point = $mark->$gp_col;
					$total = $total+round($st_mark); 
				}
				
				$fm_row[$st_subject] = array(
					'#tree' =>TRUE,
					$st_subject => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'.$st_subject.'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'.round($st_mark).'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'.$st_grade.'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'.$st_grade_point.'</h3>',
						),
					),
				);
			}
			
			$total_weight = $total_weight * $sub_count;
			$total_percent = (round($total)/$total_weight*100);
			$grades = db_query("
				SELECT * from {$grade_table};"
			);
			foreach($grades as $gr){
				if($total_percent >= $gr->marks_from && $total_percent <= $gr->marks_to){
					$total_grade = $gr->grade;
					$total_grade_point = $gr->grade_point;
				}
			}
			$total_row['total'] = array(
				'#tree' =>TRUE,
				'total' => array(
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: left !important;">Total</h3>',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: left !important;">'.round($total).'</h3>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: left !important;">'.$total_grade.'</h3>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: left !important;">'.$total_grade_point.'</h3>',
					),
				),
			);
			$fm_row = array_merge($fm_row, $total_row);
			$form[$term_id]['vt']['term_result']['marks_tab'.$term_id] = array(
				'#theme' => 'this_student_marks_table',
				'rows' => $fm_row,
			);
			
			$options_column = array(
				'title' => 'Marks',
				'fields' => array(
					'marks' => array(
						'label' => t('Marks'),
						'enabled' => TRUE,
					),
				),
				'xAxis' => array(
					'labelField' => 'subject',
				),
				'data' => $data,
				'type' => 'pie',
			);
			
			$form[$term_id]['vt']['term_result']['pie'.$term_id] =  array(
				'#theme' => 'visualization',
				'#options' => $options_column,
				'#suffix' => '<script type="text/javascript">'
					. 'jQuery(\'.visualization-chart\').css( \'width\', \'100%\' );'
					. 'jQuery(\'.visualization-chart\').css( \'max-width\', \'1000px\' );'
					. '</script>',
			);
		}
	}
	
	//---------------------------Displaying Exam Result------------------------------
	//---------------------------Displaying Exam Result------------------------------
	//---------------------------Displaying Exam Result------------------------------
	//---------------------------Displaying Exam Result------------------------------
	//---------------------------Displaying Exam Result------------------------------
	//---------------------------Displaying Exam Result------------------------------
	//---------------------------Displaying Exam Result------------------------------
	$st_marks = $st_grade = $st_grade_point =array();
	foreach($st_exam as $exam_code => $term_id){
		$form[$term_id]['vt'][$exam_code] = array(
			'#type' => 'fieldset',
			'#title' => $exam_code,
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
		);
		$content = '';
		$content = '<html>';
		$content .= '<head></head>
		<body>';
		$di_exam = db_query("SELECT * FROM {$master_exam_table} WHERE exam_code =:ec AND term = :t;", array(':ec' => $exam_code, ':t' => $term_id));
		foreach($di_exam as $die){
			if($die->di_status == 1){
				$form[$term_id]['vt'][$exam_code]['di'] = array(
					'#type' => 'fieldset',
					'#title' => 'DI',
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
				);
				
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
					
					if(in_array($class, $classes)){
						$di_group_name = $dig->group_name;
						$di_group_id = $dig->id;
					}
				}
				$sections = array();
				$di_group_sections = db_query("SELECT * FROM {$di_group_section_table} WHERE group_id = :gi;", array(':gi' => $di_group_id));
				
				foreach($di_group_sections as $digs){
					$section_id = $digs->id;
					//$content .= '<table style = "width:100%;"><tr><td style = "width:15%; padding-left:20px;"><h2 style ="border: 1px solid green; background-color:green; border-radius:10px; color:White;">'.$digs->section_id.'</h2></td><td style = "padding-left:20px; width:85%;"><h2 style ="color:red;">:'.$digs->section_name.'</h2></td></tr></table>';
					//$content .= '<div style = "display:flex;"><h2 style =" border: 1px solid green; background-color:green; border-radius:10px; color:White;">&nbsp;&nbsp&nbsp;'.$digs->section_id.'&nbsp;&nbsp;</h2>&nbsp;&nbsp;<h2 style ="color:red;">:&nbsp;&nbsp;'.$digs->section_name.'</h2></div>';
					if($digs->is_marksheet != 1){
						$content .= '<div style = "display:flex;"><h2 style =" border: 1px solid green; background-color:green; border-radius:10px; color:White;">&nbsp;&nbsp&nbsp;'.$digs->section_id.'&nbsp;&nbsp;</h2>&nbsp;&nbsp;<h2 style ="color:red;">:&nbsp;&nbsp;'.$digs->section_name.'</h2></div>';
					}
					
					$di_sub_sections = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si;", array(':gi' => $di_group_id, ':si' => $section_id));
					$sub_section = NULL;
					foreach($di_sub_sections as $diss){
						if($sub_section != $diss->sub_section_title){
							//$content .= '<table style = "width:100%;"><tr	><td style = "width:12%;"><h2 style ="color:red;">'.$diss->sub_section.'</h2></td><td style = "width:88%; padding-left:30px;"><h2 style ="color:blue;">:'.$diss->sub_section_title.'</h2></td></tr></table>';
							$content .= '<div style = "display:flex;"><h2 style ="color:red;">'.$diss->sub_section.'</h2>&nbsp;&nbsp;&nbsp;<h2 style ="color:blue;">:&nbsp;&nbsp;'.$diss->sub_section_title.'</h2></div>';
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
						
								$di_grade_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($exam_code).'_'.$class.'_di';
								$di_field = $di_group_id.$section_id.clean_exam_code_string($diss->sub_section).$sn->serial_no;
								$content .= '<th style = "background-color: #0D0D2B;">'.$exam_code.'</th></tr>';
								$student_grades = db_query("SELECT * FROM {$di_grade_table} WHERE adm_no = :an;", array(':an' => $adm_no));
								foreach($student_grades as $stg){
									$content .= '<tr>
									<td style ="	text-align:center;">'.$stg->$di_field.'</td>
									</tr>';
								}
								
								$content .= '</table>
								</td>';
								$content .= '</tr>';
							}
							$content .= '</table>';
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
								//$content .= '<table style = width:100%;><tr><td style ="background-color:purple; border-radius:10px; color:White; width:12%;">Suggested Activities : </td></tr>';
								$content .= '<div style = "display:flex"><h4 style ="background-color:purple; border-radius:10px; color:White;">&nbsp;&nbsp;&nbsp;Suggested Activities :&nbsp;&nbsp;&nbsp;<h4></div>';
							}
							
							$serial_nos = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND sub_section_title = :sst;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sst' => $diss->sub_section_title));
							foreach($serial_nos as $sn){
								$di_sa = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND serial_no = :sn;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sn' => $sn->serial_no));
								foreach($di_sa as $disa){
									if($disa->sa != NULL){
										//$content .= '<tr><td style ="color:red;"><h5><b><i>'.$disa->title.':</i></b></h5></td><td><h5>'.$disa->sa.'<h5></td></tr>';
										$content .= '<div style = "display:flex"><h5><b><i>'.$disa->title.':</i></b></h5></td><td><h5>&nbsp;&nbsp;&nbsp;'.$disa->sa.'<h5></div>';
									}
								}
							}
							$content .= '</table>';
						}
						$sub_section = $diss->sub_section_title;
					}
				}
				$content .= '</body></html>';
				
				$form[$term_id]['vt'][$exam_code]['di']['markup'] = array(
					'#type' => 'markup',
					'#markup' => $content,
				);
				
			}
		}
		
		$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($exam_code).'_'.$class;
		$marks = db_query(
			"SELECT * from $marks_table where adm_no = :an;", array(':an' => $adm_no)
		);
		foreach($marks as $mark){
			$subject_table = 'essa_'.$session_id.'_subjects_'.$class;
			$subjects = db_query(
				"SELECT * from $subject_table;"
			);
			foreach($subjects as $subject){
				$sub_id = $subject->sub_id;
				$st_marks[$exam_code][$sub_id] = $mark->$sub_id;
				$cf_col = 'cf_'.$sub_id;
				$st_cf[$exam_code][$sub_id] = $mark->$cf_col;
				$grade_col = 'grade_'.$sub_id;
				$st_grade[$exam_code][$sub_id] = $mark->$grade_col;
				$gp_col = 'grade_point_'.$sub_id;
				$st_grade_point[$exam_code][$sub_id] = $mark->$gp_col;
			}
		}
	}
	
	$sub_count = 0;
	foreach($st_exam as $exam_code => $term_id){
		$data = array();
		foreach($st_cf as $excode=>$marks){
			if($exam_code == $excode){
				foreach($marks as $subject => $mark){
					if($mark != NULL){
						$data[] = array('subject' => $subject, 'marks' => $mark);
					}
					$op_subjects = db_query(
						"SELECT * from $subject_table where sub_id = :si;", array(':si' => $subject)
					);
					foreach($op_subjects as $ops){
						if($ops->type == 'Optional'){
							$op_students = db_query(
								"SELECT * from $op_subj_student_table where adm_no = :an and sub_id = :s;",
								array(':an' => $adm_no, ':s' => $subject)
							);
							foreach($op_students as $os){
								$std_marks[$subject] = $mark;
								$sub_count = $sub_count+1;
							}
						}else{
							$std_marks[$subject] = $mark;
							$sub_count = $sub_count+1;
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
						'labelField' => 'subject',
					),
					'data' => $data,
					'type' => 'column',
				);
				
				$form[$term_id]['vt'][$exam_code]['column'.$exam_code] =  array(
					'#theme' => 'visualization',
					'#options' => $options_column,
					'#suffix' => '<script type="text/javascript">'
						. 'jQuery(\'.visualization-chart\').css( \'width\', \'100%\' );'
						. 'jQuery(\'.visualization-chart\').css( \'max-width\', \'1000px\' );'
						. '</script>',
				);
				$total = 0;
				foreach($std_marks as $st_subject=>$st_mark){
					$marks = db_query(
						"SELECT * from $marks_table where adm_no = :an;", array(':an' => $adm_no)
					);
					foreach($marks as $mark){
						$grade_col = 'grade_'.$st_subject;
						$st_grade = $mark->$grade_col;
						$gp_col = 'grade_point_'.$st_subject;
						$st_grade_point = $mark->$gp_col;
						$total = $total+round($st_mark); 
					}
					
					$fm_row[$st_subject] = array(
						'#tree' =>TRUE,
						$st_subject => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: left !important;">'.$st_subject.'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: left !important;">'.round($st_mark).'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: left !important;">'.$st_grade.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "text-align: left !important;">'.$st_grade_point.'</h3>',
							),
						),
					);
				}
				
				$exams = db_query(
					"SELECT * from $master_exam_table where exam_code = :ec;", array(':ec' => $exam_code)
				);
				foreach($exams as $ex){
					$weight = $ex->weight;
				}
				$fm_total = $sub_count*$weight;
				$total_percent = (round($total)/$fm_total*100);
				$grades = db_query("
					SELECT * from {$grade_table};"
				);
				foreach($grades as $gr){
					if($total_percent >= $gr->marks_from && $total_percent <= $gr->marks_to){
						$total_grade = $gr->grade;
						$total_grade_point = $gr->grade_point;
					}
				}
				$total_row['total'] = array(
					'#tree' =>TRUE,
					'total' => array(
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">Total</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'.round($total).'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'.$total_grade.'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'.$total_grade_point.'</h3>',
						),
					),
				);
				$fm_row = array_merge($fm_row, $total_row);
				$form[$term_id]['vt'][$exam_code]['marks_tab'] = array(
					'#theme' => 'this_student_marks_table',
					'rows' => $fm_row,
				);
				
				$options_column = array(
					'title' => 'Marks',
					'fields' => array(
						'marks' => array(
							'label' => t('Marks'),
							'enabled' => TRUE,
						),
					),
					'xAxis' => array(
						'labelField' => 'subject',
					),
					'data' => $data,
					'type' => 'pie',
				);
				
				$form[$term_id]['vt'][$exam_code]['pie'.$exam_code] =  array(
					'#theme' => 'visualization',
					'#options' => $options_column,
					'#suffix' => '<script type="text/javascript">'
						. 'jQuery(\'.visualization-chart\').css( \'width\', \'100%\' );'
						. 'jQuery(\'.visualization-chart\').css( \'max-width\', \'1000px\' );'
						. '</script>',
				);
			}
		}
	}
	
	return $form;
}

function print_report_card($form, $form_state){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$grade_table = 'essa_'.$session_id.'_exam_grade_settings';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
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
	
	$value = $form_state['triggering_element']['#name'];
	$value = explode('%', $value);
	$adm_no = $value[0];
	$term_id = $value[1];
	
	$terms = db_query("SELECT * FROM {$term_table} where id=:id", array(":id" => $term_id));
	foreach($terms as $term){
		$term_name = $term -> term_name;
	}
	
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
		///////////////////////////////////////STUDENT DETAILS////////////////////////////////////////////////////////////////////////////
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
			$class = $st->class;
			$section = $st->section;
		}
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		///////////////////////////////////////STUDENT ATTENDANCE//////////////////////////////////////////////////////////////////////////
		$exams = db_query(
			"SELECT * from $master_exam_table where term = :ti;", array(':ti' => $term_id)
		);
		foreach($exams as $ex){
			$exam_code = $ex->exam_code;
			if(variable_get('publish_term_result_'.$term_id) == TRUE){
				$bi_table = 'essa_'.$session_id.'_basicinfo';
				$bi_db = db_query(
					"SELECT * from {$bi_table}"
				);
				foreach($bi_db as $bi){
					$start_date = $bi->academicyearstart;
				}
				if(preg_match('/1/', $term_id) == 0 || preg_match('/I/', $term_id) == 0 || preg_match('/i/', $term_id) == 0 || preg_match('/ONE/', $term_id) == 0 || preg_match('/One/', $term_id) == 0 || preg_match('/first/', $term_id) == 0 || preg_match('/First/', $term_id) == 0){
					$from_date = $start_date;
				}else{
					$terms_data = db_query("SELECT * FROM $terms_table WHERE term_name LIKE :a;", array(':a' => '%1%'));//OR %I% OR %i% OR %one% OR %first% OR %First%
					foreach($terms_data as $td){
						$publish_dates = db_query("SELECT * FROM {$exam_status_table} WHERE term_id =:tid and exam_code = :ec;", array(':tid' => $td->id, ':ec' => $exam_code));
						foreach($publish_dates as $pd){
							$from_date = date('d-m-Y',$pd->publish_on);
						}
					}
				}
				
				$exam_status_table = 'essa_'.$session_id.'_exam_status';
				$publish_dates = db_query("SELECT * FROM {$exam_status_table} WHERE term_id =:tid and exam_code = :ec;", array(':tid' => $term_id, ':ec' => $exam_code));
				foreach($publish_dates as $pd){
					$publish_date = $pd->publish_on;
					$publish_date = date('d-m-Y', $publish_date);
				}
				//dsm($publish_date);
				$attendance_table = 'essa_'.$session_id.'_'.$class.'_'.$section.'_attendance';
				$to_date = $publish_date;
				$format = 'Y-m-d';
				$date = getDatesFromRange($from_date,$to_date, $format);
				foreach($date as $d){
					$d = strtotime($d);
					if(date('D',$d) != 'Sun'){
						$dates[]  = date('Y_m_d', $d);
					}
				}
				
				//dsm($date);
				$total_days = db_query("SELECT * FROM {$attendance_table}");
				foreach($total_days as $td){
					foreach($dates as $d){
						if($td->$d != NULL){
							$total_working_days[] = $td->$d;
						}
					}
				}
				
				$total_days = db_query("SELECT * FROM {$attendance_table} WHERE adm_no = :an;", array(':an' => $adm_no));
				foreach($total_days as $td){
					foreach($dates as $d){
						if($td->$d == 'P'){
							$total_present_days[] = $td->$d;
						}
					}
				}
				$working_days = 0;
				foreach($total_working_days as $twd){
					$working_days = $working_days + count($twd);
				}
				$present_days = array_count_values($total_present_days);
				
				$content .= '<div>';
				$content .= '<table style = "width:100%; border:1px solid green; background-color:#F5DF6D">';
				$content .= '<tr>';
				$content .= '<th style ="text-align:left; background-color: maroon; color:yellow; border:1px solid green;">Attendance</th>';
				
				$term_names = db_query("SELECT * FROM $terms_table} WHERE id =:id;",array(':id' => $term_id));
				foreach($term_names as $tn){
					$term_name = $tn->term_name;
				}
				
				$content .= '<th style ="text-align:left; background-color: maroon; color:yellow; border:1px solid green;">'.$term_name.'</th>';
				
				$content .= '<th style ="text-align:left; background-color: maroon; color:yellow; border:1px solid green;">Total</th>';
				$content .= '</tr>';
				
				$content .= '<tr>';
				$content .= '<td>Total attendance of the student</td>';
				$content .= '<td>'.$present_days['P'].'</td>';
				$content .= '</tr>';
				
				$content .= '<tr>';
				$content .= '<td>Total working days</td>';
				$content .= '<td>'.$working_days.'</td>';
				$content .= '</tr>';
				
				$content .= '</table>';
				$content .= '</div>';
				
			}
		}
		$content .= '<div style = "page-break-after: always;"></div>';
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	
	require_once("profiles/essa/modules/dependencies/essa/print/lib/dompdf/dompdf_config.inc.php");
	$html = $content;
	$dompdf = new DOMPDF;
	$dompdf->load_html($html);
	//$dompdf->set_paper($page_size, $po);
	$dompdf->render();
	// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
	$dompdf->stream($term_name.'_Report Card_'.$adm_no.".pdf", array('compress' => FALSE));
	
}

/**
 * Theme callback for the form table.
*/ 
function theme_this_student_marks_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Subject'), t('Marks'), t('Grade'), t('Grade Point'));
  
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