<?php

function upload_marks($form, &$form_state, $term_id, $exam_code){
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
		$form['term_id'] = array(
			'#type' => 'value',
			'#value' => $term_id,
		);
		
		$form['exam_code'] = array(
			'#type' => 'value',
			'#value' => $exam_code,
		);
		
		$ec = db_query("SELECT * FROM {$master_exam_table} where term = :t and exam_code = :ec",
							array(':t' => $term_id, ':ec' => $exam_code));
		foreach($ec as $ex){
			$class_from = $ex->class_from;
			$class_to = $ex->class_to;
		}
		$class_list = array('--Select--');
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
		$classes = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
			array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
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
					'callback' => 'display_subject_ajax',
					'wrapper' => 'sub_wrapper',
					'method' => 'replace',
					'effect' => 'fade',
				),
				'#default_value' => $this_sec,
				'#disabled' => TRUE,
			);
			
			$form_state['values']['sec'] = $this_sec;
			if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
				$subject_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
				$sub_op = array('--Select--');
				$subjects = db_query(
					"SELECT * from $subject_table;"
				);
				foreach($subjects as $subject){
					$sub_op[$subject->sub_id] = $subject->sub_name;
				}
				$form['sub_wrapper']['subj'] = array(
					'#type' => 'select',
					'#title' => 'Select a Subject',
					'#options' => $sub_op,
					'#ajax' => array(
						'event' => 'change',
						'callback' => 'display_marks_ajax',
						'wrapper' => 'marks_wrapper',
						'method' => 'replace',
						'effect' => 'fade',
					),
				);
					
				if(isset($form_state['values']['subj']) && $form_state['values']['subj'] != '--Select--'){
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
					if($flag == 1){
						drupal_set_message('Result has been generated for this exam. To edit the uploaded marks, you will need permission from exam co-ordinator.','success');
						$def_marks = array();
						$field = $form_state['values']['subj'];
						$examcode = clean_exam_code_string($exam_code);
						$table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$examcode.'_'.$form_state['values']['class'];
						if(!db_field_exists($table, $field)){
							global $base_url;
							$url = $base_url.'/admin/exam/'.$term_id.'/'.$exam_code;
							drupal_set_message('This subject was created after exam creation. Please use <a href = "'.$url.'">"Rebuild"</a> option to include the subject for this exam.','error');
						}else{
							$students = db_query(
								"SELECT * from $master_student_table where class = :cl and section = :sec order by roll_no;",
								array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
							);
							foreach($students as $st){
								$subject_marks = db_query(
									"SELECT * from $table where adm_no = :an;", array(':an' => $st->adm_no)
								);
								foreach($subject_marks as $sm){
									$def_marks = $sm->$form_state['values']['subj'];
								}
								$op_subjects = db_query(
									"SELECT * from $subject_table where sub_id = :si;", array(':si' => $form_state['values']['subj'])
								);
								foreach($op_subjects as $ops){
									if($ops->type == 'Optional'){
										$op_students = db_query(
											"SELECT * from $op_subj_student_table where class_id = :cl and section = :sec and sub_id = :s;",
											array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'], ':s' => $form_state['values']['subj'])
										);
										foreach($op_students as $os){
											if($os->adm_no == $st->adm_no){
												$row[$st->adm_no] = array(
													'#tree' =>TRUE,
													$st->adm_no => array(  //Generating unique array id for every form element
														'c1' =>array(
															'#type' => 'markup',
															'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
														),
														'cr' =>array(
															'#type' => 'markup',
															'#markup' => '<h3 style = "text-align: left !important;">'. !is_null($st->exam_roll_no)?$st->exam_roll_no:$st->roll_no .'</h3>',
														),
														'c2' =>array(
															'#type' => 'markup',
															'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
														),
														$form_state['values']['subj'] =>array(
															'#type' => 'textfield',
															'#size' => 10,
															'#default_value' => $def_marks,
															'#disabled' => TRUE,
														),
													),
												);
											}
										}
									}else{
										$row[$st->adm_no] = array(
											'#tree' =>TRUE,
											$st->adm_no => array(  //Generating unique array id for every form element
												'c1' =>array(
													'#type' => 'markup',
													'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
												),
												'cr' =>array(
													'#type' => 'markup',
													'#markup' => '<h3 style = "text-align: left !important;">'.is_null($st->exam_roll_no)?$st->exam_roll_no:$st->roll_no .'</h3>',
												),
												'c2' =>array(
													'#type' => 'markup',
													'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
												),
												$form_state['values']['subj'] =>array(
													'#type' => 'textfield',
													'#size' => 10,
													'#default_value' => $def_marks,
													'#disabled' => TRUE,
												),
											),
										);
									}
								}
							}
							
							$full_marks = db_query("SELECT * FROM {$full_marks_table} where term_id = :t and exam_code = :ec and class = :cl and subject_id = :si",
								array(':t' => $term_id, ':ec' => $exam_code, ':cl' => $this_class, ':si' => $form_state['values']['subj']));
							foreach($full_marks as $fm){
								$sub_full_marks = $fm->full_marks;
							}
							$form['marks_wrapper'][$form_state['values']['subj']] = array(
								'#type' => 'textfield',
								'#title' => 'Enter full marks - ',
								'#size' => 10,
								'#required' => TRUE,
								'#default_value' => $sub_full_marks,
								'#disabled' => TRUE,
							);
							variable_set('upload_marks_sub'.$user->uid, $form_state['values']['subj']);
							$form['marks_wrapper']['tab'] = array(
								'#theme' => 'student_marks_table',
								'rows' => $row,
							);
							$form['marks_wrapper']['save'] = array(
								'#type' => 'submit',
								'#value' => 'Save',
							);
						}	
					}else{
						$def_marks = array();
						$field = $form_state['values']['subj'];
						$examcode = clean_exam_code_string($exam_code);
						$table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$examcode.'_'.$form_state['values']['class'];
						if(!db_field_exists($table, $field)){
							global $base_url;
							$url = $base_url.'/admin/exam/'.$term_id.'/'.$exam_code;
							drupal_set_message('This subject was created after exam creation. Please use <a href = "'.$url.'">"Rebuild"</a> option to include the subject for this exam.','error');
						}else{
							$students = db_query(
								"SELECT * from $master_student_table where class = :cl and section = :sec order by exam_roll_no;",
								array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
							);
							foreach($students as $st){
								$subject_marks = db_query(
									"SELECT * from $table where adm_no = :an;", array(':an' => $st->adm_no)
								);
								foreach($subject_marks as $sm){
									$def_marks = $sm->$form_state['values']['subj'];
								}
								$op_subjects = db_query(
									"SELECT * from $subject_table where sub_id = :si;", array(':si' => $form_state['values']['subj'])
								);
								foreach($op_subjects as $ops){
									if($ops->type == 'Optional'){
										$op_students = db_query(
											"SELECT * from $op_subj_student_table where class_id = :cl and section = :sec and sub_id = :s;",
											array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'], ':s' => $form_state['values']['subj'])
										);
										foreach($op_students as $os){
											if($os->adm_no == $st->adm_no){
												$row[$st->adm_no] = array(
													'#tree' =>TRUE,
													$st->adm_no => array(  //Generating unique array id for every form element
														'c1' =>array(
															'#type' => 'markup',
															'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
														),
														'cr' =>array(
															'#type' => 'markup',
															'#markup' => '<h3 style = "text-align: left !important;">'. !is_null($st->exam_roll_no)?$st->exam_roll_no:$st->roll_no .'</h3>',
														),
														'c2' =>array(
															'#type' => 'markup',
															'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
														),
														$form_state['values']['subj'] =>array(
															'#type' => 'textfield',
															'#size' => 10,
															'#default_value' => $def_marks,
														),
													),
												);
											}
										}
									}else{
										$row[$st->adm_no] = array(
											'#tree' =>TRUE,
											$st->adm_no => array(  //Generating unique array id for every form element
												'c1' =>array(
													'#type' => 'markup',
													'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
												),
												'cr' =>array(
													'#type' => 'markup',
													'#markup' => '<h3 style = "text-align: left !important;">'. !is_null($st->exam_roll_no)?$st->exam_roll_no:$st->roll_no .'</h3>',
												),
												'c2' =>array(
													'#type' => 'markup',
													'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
												),
												$form_state['values']['subj'] =>array(
													'#type' => 'textfield',
													'#size' => 10,
													'#default_value' => $def_marks,
												),
											),
										);
									}
								}
							}
							
							$full_marks = db_query("SELECT * FROM {$full_marks_table} where term_id = :t and exam_code = :ec and class = :cl and subject_id = :si",
								array(':t' => $term_id, ':ec' => $exam_code, ':cl' => $this_class, ':si' => $form_state['values']['subj']));
							foreach($full_marks as $fm){
								$sub_full_marks = $fm->full_marks;
							}
							$form['marks_wrapper'][$form_state['values']['subj']] = array(
								'#type' => 'textfield',
								'#title' => 'Enter full marks - ',
								'#size' => 10,
								'#required' => TRUE,
								'#default_value' => $sub_full_marks,
							);
							
							$form['marks_wrapper']['help'] = array(
								'#type' => 'markup',
								'#markup' => '<h4>NOTE: Leave the field blank for the students you want to mark as absent.<h4>'
							);
							variable_set('upload_marks_sub'.$user->uid, $form_state['values']['subj']);
							$form['marks_wrapper']['tab'] = array(
								'#theme' => 'student_marks_table',
								'rows' => $row,
							);
							$form['marks_wrapper']['save'] = array(
								'#type' => 'submit',
								'#value' => 'Save',
							);
						}	
					}
				}
			}
		}
	}else{
		$form['term_id'] = array(
			'#type' => 'value',
			'#value' => $term_id,
		);
		
		$form['exam_code'] = array(
			'#type' => 'value',
			'#value' => $exam_code,
		);
		
		$ec = db_query("SELECT * FROM {$master_exam_table} where term = :t and exam_code = :ec",
							array(':t' => $term_id, ':ec' => $exam_code));
		foreach($ec as $ex){
			$class_from = $ex->class_from;
			$class_to = $ex->class_to;
		}
		$class_list = array('--Select--');
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
		$classes = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
			array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
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
					'callback' => 'display_subject_ajax',
					'wrapper' => 'sub_wrapper',
					'method' => 'replace',
					'effect' => 'fade',
				),
			);
			
			if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
				$subject_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
				$sub_op = array('--Select--');
				$subjects = db_query(
					"SELECT * from $subject_table;"
				);
				foreach($subjects as $subject){
					$sub_op[$subject->sub_id] = $subject->sub_name;
				}
				$form['sub_wrapper']['subj'] = array(
					'#type' => 'select',
					'#title' => 'Select a Subject',
					'#options' => $sub_op,
					'#ajax' => array(
						'event' => 'change',
						'callback' => 'display_marks_ajax',
						'wrapper' => 'marks_wrapper',
						'method' => 'replace',
						'effect' => 'slide',
					),
				);
					
				if(isset($form_state['values']['subj']) && $form_state['values']['subj'] != '--Select--'){
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
					
					if($flag == 1){
						drupal_set_message('Result has been generated for this exam. To edit the uploaded marks, you will need permission from exam co-ordinator.','success');
						$field = $form_state['values']['subj'];
						$examcode = clean_exam_code_string($exam_code);
						$table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$examcode.'_'.$form_state['values']['class'];
						if(!db_field_exists($table, $field)){
							global $base_url;
							$url = $base_url.'/admin/exam/'.$term_id.'/'.$exam_code;
							drupal_set_message('This subject was created after exam creation. Please use <a href = "'.$url.'">"Rebuild"</a> option to include the subject for this exam.','error');
						}else{
							$students = db_query(
								"SELECT * from $master_student_table where class = :cl and section = :sec order by exam_roll_no;",
								array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
							);
							foreach($students as $st){
								$subject_marks = db_query(
									"SELECT * from $table where adm_no = :an;", array(':an' => $st->adm_no)
								);
								foreach($subject_marks as $sm){
									$def_marks = $sm->$form_state['values']['subj'];
								}
								$op_subjects = db_query(
									"SELECT * from $subject_table where sub_id = :si;", array(':si' => $form_state['values']['subj'])
								);
								foreach($op_subjects as $ops){
									if($ops->type == 'Optional'){
										$op_students = db_query(
											"SELECT * from $op_subj_student_table where class_id = :cl and section = :sec and sub_id = :s;",
											array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'], ':s' => $form_state['values']['subj'])
										);
										foreach($op_students as $os){
											if($os->adm_no == $st->adm_no){
												$row[$st->adm_no] = array(
													'#tree' =>TRUE,
													$st->adm_no => array(  //Generating unique array id for every form element
														'c1' =>array(
															'#type' => 'markup',
															'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
														),
														'cr' =>array(
															'#type' => 'markup',
															'#markup' => '<h3 style = "text-align: left !important;">'. !is_null($st->exam_roll_no)?$st->exam_roll_no:$st->roll_no .'</h3>',
														),
														'c2' =>array(
															'#type' => 'markup',
															'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
														),
														$form_state['values']['subj'] =>array(
															'#type' => 'textfield',
															'#size' => 10,
															'#default_value' => $def_marks,
															'#disabled' => TRUE,
														),
													),
												);
											}
										}
									}else{
										$row[$st->adm_no] = array(
											'#tree' =>TRUE,
											$st->adm_no => array(  //Generating unique array id for every form element
												'c1' =>array(
													'#type' => 'markup',
													'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
												),
												'cr' =>array(
													'#type' => 'markup',
													'#markup' => '<h3 style = "text-align: left !important;">'. !is_null($st->exam_roll_no)?$st->exam_roll_no:$st->roll_no .'</h3>',
												),
												'c2' =>array(
													'#type' => 'markup',
													'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
												),
												$form_state['values']['subj'] =>array(
													'#type' => 'textfield',
													'#size' => 10,
													'#default_value' => $def_marks,
													'#disabled' => TRUE,
												),
											),
										);
									}
								}
							}
							
							$full_marks = db_query("SELECT * FROM {$full_marks_table} where term_id = :t and exam_code = :ec and class = :cl and subject_id = :si",
								array(':t' => $term_id, ':ec' => $exam_code, ':cl' => $form_state['values']['class'], ':si' => $form_state['values']['subj']));
							foreach($full_marks as $fm){
								$sub_full_marks = $fm->full_marks;
							}
							
							$form['marks_wrapper'][$form_state['values']['subj']] = array(
								'#type' => 'textfield',
								'#title' => 'Enter full marks - ',
								'#size' => 10,
								'#required' => TRUE,
								'#default_value' => $sub_full_marks,
								'#disabled' => TRUE,
							);
							
							$subjects = db_query(
								"SELECT * from $subject_table WHERE sub_id = :si;", array(':si' => $form_state['values']['subj'])
							);
							foreach($subjects as $subject){
								$sub_name = $subject->sub_name;
							}
							
							variable_set('upload_marks_sub'.$user->uid, $form_state['values']['subj']);
							$form['marks_wrapper']['tab'] = array(
								'#theme' => 'student_marks_table',
								'rows' => $row,
							);
							
							$form['marks_wrapper']['save'] = array(
								'#type' => 'submit',
								'#value' => 'Save',
							);
						}	
					}else{
						$field = $form_state['values']['subj'];
						$examcode = clean_exam_code_string($exam_code);
						$table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$examcode.'_'.$form_state['values']['class'];
						if(!db_field_exists($table, $field)){
							global $base_url;
							$url = $base_url.'/admin/exam/'.$term_id.'/'.$exam_code;
							drupal_set_message('This subject was created after exam creation. Please use <a href = "'.$url.'">"Rebuild"</a> option to include the subject for this exam.','error');
						}else{
							$students = db_query(
								"SELECT * from $master_student_table where class = :cl and section = :sec order by exam_roll_no;",
								array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
							);
							foreach($students as $st){
								$subject_marks = db_query(
									"SELECT * from $table where adm_no = :an;", array(':an' => $st->adm_no)
								);
								foreach($subject_marks as $sm){
									$def_marks = $sm->$form_state['values']['subj'];
								}
								$op_subjects = db_query(
									"SELECT * from $subject_table where sub_id = :si;", array(':si' => $form_state['values']['subj'])
								);
								foreach($op_subjects as $ops){
									if($ops->type == 'Optional'){
										$op_students = db_query(
											"SELECT * from $op_subj_student_table where class_id = :cl and section = :sec and sub_id = :s;",
											array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'], ':s' => $form_state['values']['subj'])
										);
										foreach($op_students as $os){
											if($os->adm_no == $st->adm_no){
												$row[$st->adm_no] = array(
													'#tree' =>TRUE,
													$st->adm_no => array(  //Generating unique array id for every form element
														'c1' =>array(
															'#type' => 'markup',
															'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
														),
														'cr' =>array(
															'#type' => 'markup',
															'#markup' => '<h3 style = "text-align: left !important;">'. !is_null($st->exam_roll_no)?$st->exam_roll_no:$st->roll_no .'</h3>',
														),
														'c2' =>array(
															'#type' => 'markup',
															'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
														),
														$form_state['values']['subj'] =>array(
															'#type' => 'textfield',
															'#size' => 10,
															'#default_value' => $def_marks,
														),
													),
												);
											}
										}
									}else{
										$row[$st->adm_no] = array(
											'#tree' =>TRUE,
											$st->adm_no => array(  //Generating unique array id for every form element
												'c1' =>array(
													'#type' => 'markup',
													'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
												),
												'cr' =>array(
													'#type' => 'markup',
													'#markup' => '<h3 style = "text-align: left !important;">'. !is_null($st->exam_roll_no)?$st->exam_roll_no:$st->roll_no .'</h3>',
												),
												'c2' =>array(
													'#type' => 'markup',
													'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
												),
												$form_state['values']['subj'] =>array(
													'#type' => 'textfield',
													'#size' => 10,
													'#default_value' => $def_marks,
												),
											),
										);
									}
								}
							}
							
							$full_marks = db_query("SELECT * FROM {$full_marks_table} where term_id = :t and exam_code = :ec and class = :cl and subject_id = :si",
								array(':t' => $term_id, ':ec' => $exam_code, ':cl' => $form_state['values']['class'], ':si' => $form_state['values']['subj']));
							foreach($full_marks as $fm){
								$sub_full_marks = $fm->full_marks;
							}
							
							$form['marks_wrapper'][$form_state['values']['subj']] = array(
								'#type' => 'textfield',
								'#title' => 'Enter full marks - ',
								'#size' => 10,
								'#required' => TRUE,
								'#default_value' => $sub_full_marks,
							);
							
							$form['marks_wrapper']['help'] = array(
								'#type' => 'markup',
								'#markup' => '<h4>NOTE: Leave the field blank for the students you want to mark as absent.<h4>'
							);
							
							$subjects = db_query(
								"SELECT * from $subject_table WHERE sub_id = :si;", array(':si' => $form_state['values']['subj'])
							);
							foreach($subjects as $subject){
								$sub_name = $subject->sub_name;
							}
							
							variable_set('upload_marks_sub'.$user->uid, $form_state['values']['subj']);
							$form['marks_wrapper']['tab'] = array(
								'#theme' => 'student_marks_table',
								'rows' => $row,
							);
							
							$form['marks_wrapper']['save'] = array(
								'#type' => 'submit',
								'#value' => 'Save',
							);
						}	
					}
				}
			}
		}
	}
	return $form;
}


function upload_marks_validate($form, &$form_state){
	$full_marks = $form_state['values'][$form_state['values']['subj']];
	foreach($form_state['values'] as $key=>$val){
		if(is_array($val)){
			foreach($val as $adm_no => $v){
				if($v[$form_state['values']['subj']] != NULL){
					if($v[$form_state['values']['subj']] > $full_marks){
						form_set_error('c3','You cannot enter marks greater than full marks for - '.$adm_no);
					}
				}
			}
		}
	}
}

function upload_marks_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$full_marks_table = 'essa_'.$session_id.'_exam_full_marks';
	$exam_marks_upload_status_table = 'essa_'.$session_id.'_exam_marks_upload_status';
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$class = $form_state['values']['class'];
	$sec = $form_state['values']['sec'];
	$subj_id = $form_state['values']['subj'];
	$full_marks = $form_state['values'][$form_state['values']['subj']];
	$marks_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($exam_code).'_'.$class;
	$grade_table = 'essa_'.$session_id.'_exam_grade_settings';
	$this_exam = db_query(
		"SELECT * from $master_exam_table where term = :ti and exam_code = :ex;", array(':ti' => $term_id, ':ex' => $exam_code)
	);
	foreach($this_exam as $exam){
		$weight = $exam->weight;
	}
	
	foreach($form_state['values'] as $key=>$val){
		if(is_array($val)){
			foreach($val as $adm_no => $v){
				if($v[$form_state['values']['subj']] != NULL){
					$cf = ($v[$form_state['values']['subj']]/$full_marks)*$weight;
					$percent = ($v[$form_state['values']['subj']]/$full_marks)*100;
					$marks = round($percent);
					$grades = db_query("
						SELECT * from {$grade_table};"
					);
					foreach($grades as $gr){
						if($marks >= $gr->marks_from && $marks <= $gr->marks_to){
							$grade = $gr->grade;
							$grade_point = $gr->grade_point;
						}
					}
					db_merge($full_marks_table)
						->key(array('term_id' => $term_id, 'exam_code' => $exam_code, 'class' => $class, 'subject_id' => $subj_id))
						->fields (array(
							'term_id' => $term_id,
							'exam_code' => $exam_code,
							'class' => $class,
							'subject_id' => $subj_id,
							'full_marks' => $full_marks
						)
					)
					->execute();
					
					
					db_merge($marks_table)
						->key(array('adm_no' => $adm_no))
						->fields (array(
							'adm_no' => $adm_no,
							'section' => $sec,
							$subj_id => $v[$form_state['values']['subj']],
							'cf_'.$subj_id => $cf,
							'grade_'.$subj_id => $grade,
							'grade_point_'.$subj_id => $grade_point,
						)
					)
					->execute();
				}else{
					db_merge($marks_table)
						->key(array('adm_no' => $adm_no))
						->fields (array(
							'adm_no' => $adm_no,
							'section' => $sec,
							$subj_id => NULL,
							'cf_'.$subj_id => NULL,
							'grade_'.$subj_id => NULL,
							'grade_point_'.$subj_id => NULL,
						)
					)
					->execute();	
				}
			}
		}
	}
	
	global $user;
	db_merge($exam_marks_upload_status_table)
		->key(array('term_id' => $term_id, 'exam_code' => $exam_code, 'class' => $class, 'sec' => $sec,'sub_id' => $subj_id))
		->fields (array(
				'term_id' => $term_id,
				'exam_code' => $exam_code,
				'class' => $class,
				'sec' => $sec,
				'sub_id' => $subj_id,
				'upload_status' => TRUE,
				'timestamp' => time(),
				'uid' => $user->uid,
			)
		)
	->execute();
	drupal_set_message('Marks has been successfully uploaded.','status');
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
function display_subject_ajax($form, &$form_state){
	return $form['sub_wrapper'];
}

/**
 *Implements ajax callback.
 */
function display_sections_ajax($form, &$form_state){
	//dsm($form_state);
	return $form;
}

/**
 *Theme function
 */
function theme_student_marks_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	global $user;
	$sub_names = variable_get('upload_marks_sub'.$user->uid);
  $header = array(t('Adm No.'), t('Roll No.'), t('Name'), $sub_names);
	
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