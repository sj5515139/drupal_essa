<?php

function upload_di($form, &$form_state, $term_id, $exam_code){
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
	$di_table = 'essa_'.$session.'_di_indicators';
	$sa_table = 'essa_'.$session.'_di_sa';
	$di_section_table = 'essa_'.$session.'_di_group_section';
	$group_table = 'essa_'.$session.'_di_group_name';
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
	
	$grp_classes = array();
	$di_group = db_query("SELECT * FROM {$group_table};");
	foreach($di_group as $dg){
		$class_from = $dg->class_from;
		$class_to = $dg->class_to;
		$c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_from));
		foreach($c_from_weight as $cfw){
			$cf_weight = $cfw->weight;
		}
		$c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_to));
		foreach($c_to_weight as $ctw){
			$ct_weight = $ctw->weight;
		}
		
		$class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
			array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
		foreach($class_list as $c){
			$grp_classes[$dg->id][] = $c->class_id;
		}
	}
	
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
	
	if(isset($this_class)){
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
		
		$form['di_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "di_wrapper">',
			'#suffix' => '</div>',
		);
		
		$form['st_di_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "st_di_wrapper">',
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
					'callback' => 'display_di_ajax',
					'wrapper' => 'di_wrapper',
					'method' => 'replace',
					'effect' => 'fade',
				),
				'#default_value' => $this_sec,
				'#disabled' => TRUE,
			);
			
			foreach($grp_classes as $grp_id => $grp_cls){
				if(in_array($form_state['values']['class'], $grp_cls)){
					$this_grp = $grp_id;
				}
			}
			
			$form_state['values']['sec'] = $this_sec;
			if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
				$di_op = array('--Select--');
				$di_sections = db_query("SELECT * FROM {$di_section_table} where group_id = :gi;", array(':gi' => $this_grp));
				foreach($di_sections as $dis){
					$di_indicators = db_query("SELECT * FROM {$sa_table} where group_id = :gi and section_id= :si;",
							array(':gi' => $this_grp, ':si' => $dis->id));
					foreach($di_indicators as $diin){
						$di_op[$diin->title] = $diin->title;
						$di_field[$diin->title] = $this_grp.$dis->id.clean_exam_code_string($diin->sub_section).$diin->serial_no;
					}
				}	
				$form['di_wrapper']['di'] = array(
					'#type' => 'select',
					'#title' => 'Select a DI',
					'#options' => $di_op,
					'#ajax' => array(
						'event' => 'change',
						'callback' => 'display_st_di_ajax',
						'wrapper' => 'st_di_wrapper',
						'method' => 'replace',
						'effect' => 'slide',
					),
				);
				
				if(isset($form_state['values']['di']) && $form_state['values']['di'] != '--Select--'){
					$flag =0;
					variable_set('upload_di'.$user->uid, $form_state['values']['di']);
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
						drupal_set_message('Result has been generated for this exam. To edit the uploaded Descriptive Indicators, you will need permission from exam co-ordinator.','success');
						$field = $di_field[$form_state['values']['di']];
						$examcode = clean_exam_code_string($exam_code);
						$table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$examcode.'_'.$form_state['values']['class'].'_di';
						if(!db_field_exists($table, $field)){
							global $base_url;
							drupal_set_message('This descriptive indicator was created after exam creation. Please save the exam again to include it for this exam.','error');
						}else{
							$students = db_query(
								"SELECT * from $master_student_table where class = :cl and section = :sec order by roll_no;",
								array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
							);
							foreach($students as $st){
								$st_di_input = db_query(
									"SELECT * from $table where adm_no = :an;", array(':an' => $st->adm_no)
								);
								foreach($st_di_input as $sdi){
									$def_di = $sdi->$field;
								}
								$row[$st->adm_no] = array(
									'#tree' =>TRUE,
									$st->adm_no => array(  //Generating unique array id for every form element
										'c1' =>array(
											'#type' => 'markup',
											'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
										),
										'cr' =>array(
											'#type' => 'markup',
											'#markup' => '<h3 style = "text-align: left !important;">'. $st->roll_no .'</h3>',
										),
										'c2' =>array(
											'#type' => 'markup',
											'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
										),
										$form_state['values']['di'] =>array(
											'#type' => 'textfield',
											'#size' => 10,
											'#default_value' => $def_di,
											'#disabled' => TRUE,
										),
									),
								);
							}
							
							variable_set('upload_marks_sub'.$user->uid, $form_state['values']['subj']);
							$form['st_di_wrapper']['tab'] = array(
								'#theme' => 'student_di_table',
								'rows' => $row,
							);
							
							$form['st_di_wrapper']['save'] = array(
								'#type' => 'submit',
								'#value' => 'Save',
							);
						}	
					}else{
						$field = $di_field[$form_state['values']['di']];
						$examcode = clean_exam_code_string($exam_code);
						$table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$examcode.'_'.$form_state['values']['class'].'_di';
						if(!db_field_exists($table, $field)){
							global $base_url;
							drupal_set_message('This descriptive indicator was created after exam creation. Please save the exam again to include it for this exam.','error');
						}else{
							$students = db_query(
								"SELECT * from $master_student_table where class = :cl and section = :sec order by roll_no;",
								array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
							);
							foreach($students as $st){
								$st_di_input = db_query(
									"SELECT * from $table where adm_no = :an;", array(':an' => $st->adm_no)
								);
								foreach($st_di_input as $sdi){
									$def_di = $sdi->$field;
								}
								$row[$st->adm_no] = array(
									'#tree' =>TRUE,
									$st->adm_no => array(  //Generating unique array id for every form element
										'c1' =>array(
											'#type' => 'markup',
											'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
										),
										'cr' =>array(
											'#type' => 'markup',
											'#markup' => '<h3 style = "text-align: left !important;">'. $st->roll_no .'</h3>',
										),
										'c2' =>array(
											'#type' => 'markup',
											'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
										),
										$form_state['values']['di'] =>array(
											'#type' => 'textfield',
											'#size' => 10,
											'#default_value' => $def_di,
										),
									),
								);
							}
							
							variable_set('upload_marks_sub'.$user->uid, $form_state['values']['subj']);
							$form['st_di_wrapper']['tab'] = array(
								'#theme' => 'student_di_table',
								'rows' => $row,
							);
							
							$form['st_di_wrapper']['save'] = array(
								'#type' => 'submit',
								'#value' => 'Save',
							);
						}	
					}
				}
			}
		}
	}else{
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
		
		$form['di_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "di_wrapper">',
			'#suffix' => '</div>',
		);
		
		$form['st_di_wrapper'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "st_di_wrapper">',
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
					'callback' => 'display_di_ajax',
					'wrapper' => 'di_wrapper',
					'method' => 'replace',
					'effect' => 'fade',
				),
			);
			
			foreach($grp_classes as $grp_id => $grp_cls){
				if(in_array($form_state['values']['class'], $grp_cls)){
					$this_grp = $grp_id;
				}
			}
			
			if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
				$di_op = array('--Select--');
				$di_sections = db_query("SELECT * FROM {$di_section_table} where group_id = :gi;", array(':gi' => $this_grp));
				foreach($di_sections as $dis){
					$di_indicators = db_query("SELECT * FROM {$sa_table} where group_id = :gi and section_id= :si;",
							array(':gi' => $this_grp, ':si' => $dis->id));
					foreach($di_indicators as $diin){
						$di_op[$diin->title] = $diin->title;
						$di_field[$diin->title] = $this_grp.$dis->id.clean_exam_code_string($diin->sub_section).$diin->serial_no;
					}
				}	
				$form['di_wrapper']['di'] = array(
					'#type' => 'select',
					'#title' => 'Select a DI',
					'#options' => $di_op,
					'#ajax' => array(
						'event' => 'change',
						'callback' => 'display_st_di_ajax',
						'wrapper' => 'st_di_wrapper',
						'method' => 'replace',
						'effect' => 'slide',
					),
				);
				
				if(isset($form_state['values']['di']) && $form_state['values']['di'] != '--Select--'){
					$flag =0;
					variable_set('upload_di'.$user->uid, $form_state['values']['di']);
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
						drupal_set_message('Result has been generated for this exam. To edit the uploaded Descriptive Indicators, you will need permission from exam co-ordinator.','success');
						$field = $di_field[$form_state['values']['di']];
						$examcode = clean_exam_code_string($exam_code);
						$table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$examcode.'_'.$form_state['values']['class'].'_di';
						if(!db_field_exists($table, $field)){
							global $base_url;
							drupal_set_message('This descriptive indicator was created after exam creation. Please save the exam again to include it for this exam.','error');
						}else{
							$students = db_query(
								"SELECT * from $master_student_table where class = :cl and section = :sec order by roll_no;",
								array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
							);
							foreach($students as $st){
								$st_di_input = db_query(
									"SELECT * from $table where adm_no = :an;", array(':an' => $st->adm_no)
								);
								foreach($st_di_input as $sdi){
									$def_di = $sdi->$field;
								}
								$row[$st->adm_no] = array(
									'#tree' =>TRUE,
									$st->adm_no => array(  //Generating unique array id for every form element
										'c1' =>array(
											'#type' => 'markup',
											'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
										),
										'cr' =>array(
											'#type' => 'markup',
											'#markup' => '<h3 style = "text-align: left !important;">'. $st->roll_no .'</h3>',
										),
										'c2' =>array(
											'#type' => 'markup',
											'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
										),
										$form_state['values']['di'] =>array(
											'#type' => 'textfield',
											'#size' => 10,
											'#default_value' => $def_di,
											'#disabled' => TRUE,
										),
									),
								);
							}
							
							variable_set('upload_marks_sub'.$user->uid, $form_state['values']['subj']);
							$form['st_di_wrapper']['tab'] = array(
								'#theme' => 'student_di_table',
								'rows' => $row,
							);
							
							$form['st_di_wrapper']['save'] = array(
								'#type' => 'submit',
								'#value' => 'Save',
							);
						}
					}else{
						$field = $di_field[$form_state['values']['di']];
						$examcode = clean_exam_code_string($exam_code);
						$table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.$examcode.'_'.$form_state['values']['class'].'_di';
						if(!db_field_exists($table, $field)){
							global $base_url;
							drupal_set_message('This descriptive indicator was created after exam creation. Please save the exam again to include it for this exam.','error');
						}else{
							$students = db_query(
								"SELECT * from $master_student_table where class = :cl and section = :sec order by roll_no;",
								array(':cl' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
							);
							foreach($students as $st){
								$st_di_input = db_query(
									"SELECT * from $table where adm_no = :an;", array(':an' => $st->adm_no)
								);
								foreach($st_di_input as $sdi){
									$def_di = $sdi->$field;
								}
								$row[$st->adm_no] = array(
									'#tree' =>TRUE,
									$st->adm_no => array(  //Generating unique array id for every form element
										'c1' =>array(
											'#type' => 'markup',
											'#markup' => '<h3 style = "text-align: left !important;">'. $st->adm_no .'</h3>',
										),
										'cr' =>array(
											'#type' => 'markup',
											'#markup' => '<h3 style = "text-align: left !important;">'. $st->roll_no .'</h3>',
										),
										'c2' =>array(
											'#type' => 'markup',
											'#markup' => '<h3 style = "text-align: left !important;">'. $st->student_name .'</h3>',
										),
										$form_state['values']['di'] =>array(
											'#type' => 'textfield',
											'#size' => 10,
											'#default_value' => $def_di,
										),
									),
								);
							}
							
							variable_set('upload_marks_sub'.$user->uid, $form_state['values']['subj']);
							$form['st_di_wrapper']['tab'] = array(
								'#theme' => 'student_di_table',
								'rows' => $row,
							);
							
							$form['st_di_wrapper']['save'] = array(
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

/**
 *Implements validate function
 */
function upload_di_validate($form, &$form_state){
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
	$di_table = 'essa_'.$session.'_di_indicators';
	$sa_table = 'essa_'.$session.'_di_sa';
	$di_section_table = 'essa_'.$session.'_di_group_section';
	$group_table = 'essa_'.$session.'_di_group_name';
	$sub_names = array();
	
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$class = $form_state['values']['class'];
	$sec = $form_state['values']['sec'];
	$st_di_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($exam_code).'_'.$class.'_di';
	global $user;
	
	$grp_classes = array();
	$di_group = db_query("SELECT * FROM {$group_table};");
	foreach($di_group as $dg){
		$class_from = $dg->class_from;
		$class_to = $dg->class_to;
		$c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_from));
		foreach($c_from_weight as $cfw){
			$cf_weight = $cfw->weight;
		}
		$c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_to));
		foreach($c_to_weight as $ctw){
			$ct_weight = $ctw->weight;
		}
		
		$class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
			array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
		foreach($class_list as $c){
			$grp_classes[$dg->id][] = $c->class_id;
		}
	}
	
	foreach($grp_classes as $grp_id => $grp_cls){
		if(in_array($form_state['values']['class'], $grp_cls)){
			$this_grp = $grp_id;
		}
	}
	
	$di_sections = db_query("SELECT * FROM {$di_section_table} where group_id = :gi;", array(':gi' => $this_grp));
	foreach($di_sections as $dis){
		$sa_indicators = db_query("SELECT * FROM {$sa_table} where group_id = :gi and section_id= :si and title = :t;",
				array(':gi' => $this_grp, ':si' => $dis->id, ':t' => $form_state['values']['di']));
		foreach($sa_indicators as $sain){
			$di_indicators = db_query("SELECT * FROM {$di_table} where group_id = :gi and section_id= :si and serial_no = :sno;",
				array(':gi' => $this_grp, ':si' => $dis->id, ':sno' => $sain->serial_no));
			foreach($di_indicators as $diin){
				$grades[] = $diin->grade;
				$di_field = $this_grp.$dis->id.clean_exam_code_string($diin->sub_section).$diin->serial_no;
			}
		}
	}
		
	foreach($form_state['values'] as $key=>$val){
		if(is_array($val)){
			foreach($val as $adm_no => $v){
				if($v[$form_state['values']['di']] != NULL){
					if(!in_array($v[$form_state['values']['di']], $grades)){
						form_set_error('c3','You cannot enter DI grades other than what has been allocated for this set of descriptive indicators for - '.$adm_no);
					}
				}
			}
		}
	}
}

/**
 *Implements submit function
 */
function upload_di_submit($form, &$form_state){
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
	$di_table = 'essa_'.$session.'_di_indicators';
	$sa_table = 'essa_'.$session.'_di_sa';
	$di_section_table = 'essa_'.$session.'_di_group_section';
	$group_table = 'essa_'.$session.'_di_group_name';
	$sub_names = array();
	
	$term_id = $form_state['values']['term_id'];
	$exam_code = $form_state['values']['exam_code'];
	$class = $form_state['values']['class'];
	$sec = $form_state['values']['sec'];
	$st_di_table = 'essa_'.$session_id.'_exam_'.$term_id.'_'.clean_exam_code_string($exam_code).'_'.$class.'_di';
	global $user;
	
	$grp_classes = array();
	$di_group = db_query("SELECT * FROM {$group_table};");
	foreach($di_group as $dg){
		$class_from = $dg->class_from;
		$class_to = $dg->class_to;
		$c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_from));
		foreach($c_from_weight as $cfw){
			$cf_weight = $cfw->weight;
		}
		$c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $class_to));
		foreach($c_to_weight as $ctw){
			$ct_weight = $ctw->weight;
		}
		
		$class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
			array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
		foreach($class_list as $c){
			$grp_classes[$dg->id][] = $c->class_id;
		}
	}
	
	foreach($grp_classes as $grp_id => $grp_cls){
		if(in_array($form_state['values']['class'], $grp_cls)){
			$this_grp = $grp_id;
		}
	}
	
	$di_sections = db_query("SELECT * FROM {$di_section_table} where group_id = :gi;", array(':gi' => $this_grp));
	foreach($di_sections as $dis){
		$di_indicators = db_query("SELECT * FROM {$sa_table} where group_id = :gi and section_id= :si and title = :t;",
				array(':gi' => $this_grp, ':si' => $dis->id, ':t' => $form_state['values']['di']));
		foreach($di_indicators as $diin){
			$di_field = $this_grp.$dis->id.clean_exam_code_string($diin->sub_section).$diin->serial_no;
		}
	}
		
	foreach($form_state['values'] as $key=>$val){
		if(is_array($val)){
			foreach($val as $adm_no => $v){
				if($v[$form_state['values']['di']] != NULL){
					db_merge($st_di_table)
						->key(array('adm_no' => $adm_no))
						->fields (array(
							'adm_no' => $adm_no,
							'section' => $sec,
							$di_field => $v[$form_state['values']['di']]
						)
					)
					->execute();
				}
			}
		}
	}
}

/**
 *Implements ajax callback.
 */
function display_sections_ajax($form, &$form_state){
	//dsm($form_state);
	return $form;
}

/**
 *Implements ajax callback - display_student_ajax
 */
function display_di_ajax($form, &$form_state){
	return $form['di_wrapper'];
}

/**
 *Implements ajax callback - display_student_ajax
 */
function display_st_di_ajax($form, &$form_state){
	return $form['st_di_wrapper'];
}

/**
 *Theme function
 */
function theme_student_di_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	global $user;
	$sub_names = variable_get('upload_di'.$user->uid);
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