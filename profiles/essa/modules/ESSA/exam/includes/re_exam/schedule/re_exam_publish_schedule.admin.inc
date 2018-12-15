<?php
/**
 * Implements callback function publish_schedule_form()
 */
function re_exam_publish_schedule_form($form = array(), &$form_state, $term_id, $exam_code){
	$session_id = (string)variable_get('essa_sid');
	$class_list_table = 'essa_'.$session_id.'_class_list';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$schedule_table = 'essa_'.$session_id.'_exam_schedule';
	$re_exam_table = 'essa_'.$session_id.'_exam_re_exam';
	
	$class = db_query("SELECT * FROM {$master_exam_table} WHERE exam_code = :ec AND term =:t;", array(':ec' => $exam_code, ':t' => $term_id));
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
	
	// Attaches css and js from the field group module.
	$form['#attached']['css'] = array(
		drupal_get_path('module', 'field_group') . '/horizontal-tabs/horizontal-tabs.css',
	);
	$form['#attached']['js'] = array(
		drupal_get_path('module', 'field_group') . '/horizontal-tabs/horizontal-tabs.js',
	);
	 
	  // Defines the main tabs element.
	$form['tabs'] = array(
		'#type' => 'vertical_tabs',
		'#tree' => TRUE,
	);
	
	global $user;
	$prin =0;
	$principal_role = db_query("SELECT * FROM role WHERE name = 'Principal'");
	foreach($principal_role as $p_role){
		$p_rid = $p_role->rid;
	}
	
	$admin =0;
	$admin_role = db_query("SELECT * FROM role WHERE name = 'administrator'");
	foreach($admin_role as $a_role){
		$a_rid = $a_role->rid;
	}
	
	$ct_uid = array();
	$class_teacher_role = db_query("SELECT * FROM role WHERE name = 'Class Teacher'");
	foreach($class_teacher_role as $ct_role){
		$ct_rid = $ct_role->rid;
	}
	$class_teacher = 0;
	
	global $user;
	$ec_uid = array();
	$exam_controller_role = db_query("SELECT * FROM role WHERE name = 'Exam Controller'");
	foreach($exam_controller_role as $ec_role){
		$ec_rid = $ec_role->rid;
	}
	$exam_controller = 0;
	
	$user_rid = db_query("SELECT * FROM users_roles WHERE uid = :u;", array(':u' => $user->uid));
	foreach($user_rid as $r){
		$user_rd[] = $r->rid;
		foreach($user_rd as $u_rid){
			if($u_rid == $p_rid){
				$prin = 1;
			}elseif($u_rid == $a_rid){
				$admin = 1;
			}elseif($u_rid == $ct_rid){
				$class_teacher = 1;
			}elseif($u_rid == $ec_rid){
				$exam_controller = 1;
			}
		}
	}
	
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id,
	);
	
	$form['exam_code'] = array(
		'#type' => 'value',
		'#value' => $exam_code,
	);
	
	if($prin == 1){
		
		if(variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_status') == 'pending'){
		
			foreach($classes as $cl){
				$form['tabs'][$cl] = array(
					'#type' => 'fieldset',
					'#title' => t($cl),
				);
				$row = NULL;
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $term_id, ':ec' => 're_'.$exam_code, ':c' => $cl));
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
					$form['tabs'][$cl]['schedule'] = array(
						'#theme' => 're_exam_publish_schedule_table',
						'rows' => $row,
					);
				}
			}
			
			$default_date = variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_publish_date');
			
			$form['publish_date'] = array(
				'#type' => 'date_popup',
				'#title' => t('Publish Date'),
				'#default_value' => $default_date,
				'#required' => TRUE,
				'#date_format' => 'd/m/Y',
				'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
			);
			
			
			$form['save'] = array(
				'#type' => 'submit',
				'#value' => t('Publish'),
				'#submit' => array('principal_submit')
			);
			
			$form['reconsider'] = array(
				'#type' => 'submit',
				'#value' => t('reconsider'),
				'#submit' => array('reconsider'),
			);
			
		}elseif(variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_status') == 'publish'){
			foreach($classes as $cl){
				$form['tabs'][$cl] = array(
					'#type' => 'fieldset',
					'#title' => t($cl),
				);
				$row = NULL;
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $term_id, ':ec' => 're_'.$exam_code, ':c' => $cl));
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
					$form['tabs'][$cl]['schedule'] = array(
						'#theme' => 're_exam_publish_schedule_table',
						'rows' => $row,
					);
				}
			}
			
			$form['msg'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 style = "color:red;">Schedule was approved.</h3>',
			);
			
			$form['date'] = array(
				'#type' => 'markup',
				'#markup' => '<h3> Publish Date - '.variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_publish_date').'</h3>',
			);
			
		}else{
			$form['msg'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 style = "color:red;">No Schedule has been created yet.</h3>',
			);
		}
		
		
		
	}elseif($exam_controller == 1){
	
		if(variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_status') == NULL){
			
			foreach($classes as $cl){
				$form['tabs'][$cl] = array(
					'#type' => 'fieldset',
					'#title' => t($cl),
				);
				$row = NULL;
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $term_id, ':ec' => 're_'.$exam_code, ':c' => $cl));
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
					$form['tabs'][$cl]['schedule'] = array(
						'#theme' => 're_exam_publish_schedule_table',
						'rows' => $row,
					);
				}
			}
			
			$default_date = variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_publish_date');
			
			$form['publish_date'] = array(
				'#type' => 'date_popup',
				'#title' => t('Publish Date'),
				'#default_value' => $default_date,
				'#required' => TRUE,
				'#date_format' => 'd/m/Y',
				'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
			);
			
			
			$form['save1'] = array(
				'#type' => 'submit',
				'#value' => t('Send for principal Approval'),
				'#submit' => array('exam_submit')
			);		
			
			$form['save'] = array(
				'#type' => 'submit',
				'#value' => t('Publish'),
				'#submit' => array('principal_submit')
			);
			
		}else{
			if(variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_status') == 'pending'){
				$form['msg'] = array(
					'#type' => 'markup',
					'#markup' => '<h3 style = "color:red;">Schedule has been sent to Principal for Approval.</h3>',
				);
			}else{
				if(variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_status') == 'publish'){
					$form['msg'] = array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "color:red;">Schedule was approved.</h3>',
					);
				}
			}

			foreach($classes as $cl){
				$form['tabs'][$cl] = array(
					'#type' => 'fieldset',
					'#title' => t($cl),
				);
				$row = NULL;
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $term_id, ':ec' => 're_'.$exam_code, ':c' => $cl));
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
					$form['tabs'][$cl]['schedule'] = array(
						'#theme' => 're_exam_publish_schedule_table',
						'rows' => $row,
					);
				}
				
				$form['date'] = array(
					'#type' => 'markup',
					'#markup' => '<h3> Publish Date - '.variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_publish_date').'</h3>',
				);
			}
			
		}
	}elseif($admin == 1){
		if(variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_status') == NULL){
			
			foreach($classes as $cl){
				$form['tabs'][$cl] = array(
					'#type' => 'fieldset',
					'#title' => t($cl),
				);
				$row = NULL;
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $term_id, ':ec' => 're_'.$exam_code, ':c' => $cl));
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
					$form['tabs'][$cl]['schedule'] = array(
						'#theme' => 're_exam_publish_schedule_table',
						'rows' => $row,
					);
				}
			}
			
			$default_date = variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_publish_date');
			
			$form['publish_date'] = array(
				'#type' => 'date_popup',
				'#title' => t('Publish Date'),
				'#default_value' => $default_date,
				'#required' => TRUE,
				'#date_format' => 'd/m/Y',
				'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
			);
			
			
			$form['save1'] = array(
				'#type' => 'submit',
				'#value' => t('Send for principal Approval'),
				'#submit' => array('exam_submit')
			);		
			
			$form['save'] = array(
				'#type' => 'submit',
				'#value' => t('Publish'),
				'#submit' => array('principal_submit')
			);
			
			$form['reconsider'] = array(
				'#type' => 'submit',
				'#value' => t('reconsider'),
				'#submit' => array('reconsider'),
			);
			
		}else{
			if(variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_status') == 'pending'){
				$form['msg'] = array(
					'#type' => 'markup',
					'#markup' => '<h3 style = "color:red;">Schedule has been sent to Principal for Approval.</h3>',
				);
			}else{
				if(variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_status') == 'publish'){
					$form['msg'] = array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "color:red;">Schedule was approved.</h3>',
					);
				}
			}

			foreach($classes as $cl){
				$form['tabs'][$cl] = array(
					'#type' => 'fieldset',
					'#title' => t($cl),
				);
				$row = NULL;
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $term_id, ':ec' => 're_'.$exam_code, ':c' => $cl));
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
					$form['tabs'][$cl]['schedule'] = array(
						'#theme' => 're_exam_publish_schedule_table',
						'rows' => $row,
					);
				}
				
				$form['date'] = array(
					'#type' => 'markup',
					'#markup' => '<h3> Publish Date - '.variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_publish_date').'</h3>',
				);
			}
			
		}
	}else{
		if(variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_status') == 'publish'){
			foreach($classes as $cl){
				$form['tabs'][$cl] = array(
					'#type' => 'fieldset',
					'#title' => t($cl),
				);
				$row = NULL;
				$subject_table = 'essa_'.$session_id.'_subjects_'.$cl;
				$schedule = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c;", array(':t' => $term_id, ':ec' => 're_'.$exam_code, ':c' => $cl));
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
					$form['tabs'][$cl]['schedule'] = array(
						'#theme' => 're_exam_publish_schedule_table',
						'rows' => $row,
					);
				}
				
				$form['date'] = array(
					'#type' => 'markup',
					'#markup' => '<h3> Publish Date - '.variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_publish_date').'</h3>',
				);
			}	
		}else{
			$form['msg'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 style = "color:red;">No Schedule has been created yet.</h3>',
			);
		}
	}
	if($prin == 1 || $exam_controller == 1){
		if(variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_status') != NULL){
			$form['print_schedule'] = array(
				'#type' => 'submit',
				'#value' => t('Print Schedule'),
				'#submit' => array('print_schedule_form'),
			);
		}
	}else{
		if(variable_get($term_id.'_'.$exam_code.'_re_exam_schedule_status') == 'publish'){
			$form['print_schedule'] = array(
				'#type' => 'submit',
				'#value' => t('Print Schedule'),
				'#submit' => array('print_schedule_form'),
			);
		}
	}
	
	return $form;
}

/**
 *Callback function principal_submit()
 */
function principal_submit($form, &$form_state){
	variable_set($form_state['values']['term_id'].'_'.$form_state['values']['exam_code'].'_re_exam_schedule_publish_date', $form_state['values']['publish_date']);
	variable_set($form_state['values']['term_id'].'_'.$form_state['values']['exam_code'].'_re_exam_schedule_status', 'publish');
	
	$session_id = (string)variable_get('essa_sid');
	$class_list_table = 'essa_'.$session_id.'_class_list';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$schedule_table = 'essa_'.$session_id.'_exam_schedule';
	
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
	foreach($classes as $class){
		variable_set($form_state['values']['term_id'].$form_state['values']['exam_code'].$class.'_re_exam_result_generate_status', '1');
	}
	
	menu_rebuild();
}

/**
 *Callback function exam_submit()
 */
function exam_submit($form, &$form_state){
	variable_set($form_state['values']['term_id'].'_'.$form_state['values']['exam_code'].'_re_exam_schedule_publish_date', $form_state['values']['publish_date']);
	variable_set($form_state['values']['term_id'].'_'.$form_state['values']['exam_code'].'_re_exam_schedule_status', 'pending');
}

/**
 *Callback function reconsider()
 */
function reconsider($form, &$form_state){
	variable_set($form_state['values']['term_id'].'_'.$form_state['values']['exam_code'].'_re_exam_schedule_publish_date', $form_state['values']['publish_date']);
	variable_set($form_state['values']['term_id'].'_'.$form_state['values']['exam_code'].'_re_exam_schedule_status', NULL);
}

/**
 *Theme function theme_publish_schedule_table()
 */
function theme_re_exam_publish_schedule_table(&$variables){
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

/**
 * Implements callback function print_schedule_form()
 */
function print_schedule_form($form, &$form_state){
	global $base_url;
	$url = $base_url.'/admin/exam/'.$form_state['values']['term_id'].'/'.$form_state['values']['exam_code'].'/exam_schedule/#overlay=admin/exam/'.$form_state['values']['term_id'].'/'.$form_state['values']['exam_code'].'/print_schedule';
	$form_state['redirect'] = $url;
}