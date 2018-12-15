<?php

/**
 *Page callback function - edit_term_exam
 */
function edit_term_exam($form = array(), &$form_state, $term_id, $exam_code){
	global $base_url;
	$session = variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session.'_exam_master';
	$ec = db_query("SELECT * FROM {$master_exam_table} where term = :t and exam_code = :ec",
						array(':t' => $term_id, ':ec' => $exam_code));
	foreach($ec as $ex){
		$form['help'] = array(
			'#type' => 'markup',
			'#markup' => '<h4>To "rebuild" your exam and include new subjects use the "Rebuild" button below. But make sure after adding the subject you click <b>"Rebuild"</b> button.</h4>'
		);
		$form['term_id'] = array(
			'#type' => 'value',
			'#value' => $term_id,
		);
		$form['exam_code'] = array(
			'#type' => 'textfield',
			'#title' => 'Exam Code',
			'#required' => TRUE,
			'#size' => '20',
			'#disabled' => TRUE,
			'#default_value' => $exam_code,
		);
		$form['exam_name'] = array(
			'#type' => 'textfield',
			'#title' => 'Exam Name',
			'#required' => TRUE,
			'#size' => '20',
			'#default_value' => $ex->exam_name,
		);
		$def_dt = date('Y-m-d');
		$date_from = NULL;
		$date_to = NULL;
		if($ex->date_from != NULL){
			$date_from = date('Y-m-d', $ex->date_from);
		}
		$form['date_from'] = array(
			'#type' => 'date_popup',
			'#size' => 15,
			'#date_label_position' => 'within',
			'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
			'#date_format' => 'd-m-Y',
			'#date_year_range' => '0:+1',
			'#title' => 'Date From',
			'#default_value' => $date_from,
		);
		if($ex->date_to != NULL){
			$date_to = date('Y-m-d', $ex->date_to);
		}
		$form['date_to'] = array(
			'#type' => 'date_popup',
			'#size' => 15,
			'#date_label_position' => 'within',
			'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
			'#date_format' => 'd-m-Y',
			'#date_year_range' => '0:+1',
			'#title' => 'Date To',
			'#default_value' => $date_to,
		);
		$session = variable_get('essa_sid');
		$class_list_table = 'essa_'.$session.'_class_list';
		$class_list = db_query("SELECT * FROM {$class_list_table} ORDER BY weight");
		$class = array(NULL => '--Select--');
		foreach($class_list as $cl){
			$class[] = $cl->class_id;
		}
		$form['class_from'] = array(
			'#type' => 'select',
			'#title' => 'Class From',
			'#options' => drupal_map_assoc($class),
			'#default_value' => $ex->class_from,
			'#disabled' => TRUE,
		);
		$form['class_to'] = array(
			'#type' => 'select',
			'#title' => 'Class To',
			'#options' => drupal_map_assoc($class),
			'#default_value' => $ex->class_to,
			'#disabled' => TRUE,
		);
		
		$form['weight'] = array(
			'#type' => 'textfield',
			'#title' => 'Weight(%age)',
			'#size' => '10',
			'#required' => TRUE,
			'#default_value' => $ex->weight,
		);
		$sittings = array('0' => '1', '1' => '2', '2' => '3', '3' => '4', '4' => '5');
		$form['no_of_sitting'] = array(
			'#type' => 'select',
			'#title' => 'No. of Sitting(Per Day)',
			'#options' => drupal_map_assoc($sittings),
			'#default_value' => $ex->no_of_sitting,
		);
		
		if(variable_get('di_status') == TRUE){
			$form['di_status'] = array(
				'#type' => 'checkbox',
				'#title' => 'Include Descriptive Indicators?',
				'#default_value' => $ex->di_status,
			);
		}
		
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Save',
		);
	}
	$form['rebuild'] = array(
		'#type' => 'submit',
		'#value' => 'Rebuild',
		'#submit' => array('rebuild_db'),
	);
	
	global $user;
	
	$flag = 0;
	$ec_role = db_query(
		"SELECT * from role where name = 'Exam Controller' or name = 'Principal';"
	);
	foreach($ec_role as $ecr){
		$ec_rid = $ecr->rid;
 	}
	$ec_role = db_query(
		"SELECT * from users_roles where rid = :rid and uid = :uid;", array(':rid' => $ec_rid,':uid' => $user->uid)
	);
	foreach($ec_role as $ecrole){
		$flag = 1;
	}
	
	if($flag == 0){
		$form['delete'] = array(
			'#type' => 'submit',
			'#value' => 'Delete',
			'#submit' => array('delete_exam'),
		);	
	}
	
	
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id,
	);
	
	
	return $form;
}

/**
 *Implements submit function
 */
function edit_term_exam_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session.'_exam_master';
	$class_table = 'essa_'.$session.'_class_list';
	$term_id = $form_state['values']['term_id'];
	($form_state['values']['class_from'] == '--Select--') ? $class_from = NULL: $class_from = $form_state['values']['class_from'];
	($form_state['values']['class_to'] == '--Select--') ? $class_to = NULL: $class_to = $form_state['values']['class_to'];
	db_merge($master_exam_table)
		->key(array('term' => $term_id, 'exam_code' => $form_state['values']['exam_code']))
		->fields(array(
			'exam_code' => $form_state['values']['exam_code'],
			'exam_name' => $form_state['values']['exam_name'],
			'date_from' => strtotime($form_state['values']['date_from']),
			'date_to' => strtotime($form_state['values']['date_to']),
			'term' => $form_state['values']['term_id'],
			'no_of_sitting' => $form_state['values']['no_of_sitting'],
			'class_from' => $class_from,
			'class_to' => $class_to,
			'weight' => (float)$form_state['values']['weight'],
			'di_status' => $form_state['values']['di_status'],
		))
	->execute();
	
	
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
	$classes = array();
	$class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
		array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
	foreach($class_list as $c){
		$classes[] = $c->class_id;
	}
	
	foreach($classes as $cl){
		$subject_table = 'essa_'.$session.'_subjects_'.$cl;
		$subjects = db_query("SELECT * FROM {$subject_table};");
		$schema['marks'] = array(
			'description' => 'TODO: please describe this table!',
			'fields' => array(
				'adm_no' => array(
					'description' => 'TODO: please describe this field!',
					'type' => 'varchar',
					'length' => '50',
					'not null' => FALSE,
				),
				'section' => array(
					'description' => 'TODO: please describe this field!',
					'type' => 'varchar',
					'length' => '50',
					'not null' => FALSE,
				),
			),
			'primary key' => array('adm_no'),
		);
		$fields = array();
		$grade_fields = array();
		foreach($subjects as $subject){
			$fields[$subject->sub_id] = array(
				'description' => 'TODO: please describe this field!',
				'type' => 'float',
				'not null' => FALSE,
			);
			$grade_fields[$subject->sub_id] = array(
				'description' => 'TODO: please describe this field!',
				'type' => 'varchar',
				'length' => '20',
				'not null' => FALSE,
			);
		}
		
		foreach($fields as $sub_id => $field){
			$schema['marks']['fields'][$sub_id] = $field;
			$schema['marks']['fields']['cf_'.$sub_id] = $field;
			$schema['marks']['fields']['grade_point_'.$sub_id] = $field;
		}
		
		foreach($grade_fields as $sub_id => $gf){
			$schema['marks']['fields']['grade_'.$sub_id] = $gf;
		}
		
		$exam_code = clean_exam_code_string($form_state['values']['exam_code']);
		$name_of_table = 'essa_'.$session.'_exam_'.$form_state['values']['term_id'].'_'.$exam_code.'_'.$cl;
		if(!db_table_exists($name_of_table)){
			db_create_table($name_of_table, $schema['marks']);
		}
		
		if($form_state['values']['di_status'] == 1){
			create_edit_di_db_table($form, $form_state);
		}
	}
	menu_rebuild();
	drupal_set_message($form_state['values']['exam_code'].' exam has been edited successfully.','status');
}

function create_edit_di_db_table($form, &$form_state){
	$session = variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session.'_exam_master';
	$class_table = 'essa_'.$session.'_class_list';
	$exam_term_table = 'essa_'.$session.'_exam_terms';
	$di_table = 'essa_'.$session.'_di_indicators';
	$sa_table = 'essa_'.$session.'_di_sa';
	$di_section_table = 'essa_'.$session.'_di_group_section';
	$group_table = 'essa_'.$session.'_di_group_name';
	$grp_classes = array();
	$cf_weight = NULL;
	$ct_weight = NULL;
	$exam_term = db_query("SELECT * FROM {$exam_term_table} WHERE id =:id;", array(':id' => $form_state['values']['term_id']));
	foreach($exam_term as $et){
		$class_from = $et->class_from;
		$class_to = $et->class_to;
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
		$classes[] = $c->class_id;
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
	
	if(empty($grp_classes)){
		drupal_set_message('This class has no descriptive indicators. Please create and rebuild exam.','error');
	}
	
	foreach($classes as $cl){
		foreach($grp_classes as $grp_id => $grp_cls){
			if(in_array($cl, $grp_cls)){
				$this_grp = $grp_id;
			}
		}
		$di_sections = db_query("SELECT * FROM {$di_section_table} where group_id = :gi;", array(':gi' => $this_grp));
		foreach($di_sections as $dis){
			$di_indicators = db_query("SELECT * FROM {$di_table} where group_id = :gi and section_id= :si;",
					array(':gi' => $this_grp, ':si' => $dis->id));
			foreach($di_indicators as $diin){
				$col_names[$this_grp.$dis->id.clean_exam_code_string($diin->sub_section).$diin->serial_no] = $this_grp.$dis->id.clean_exam_code_string($diin->sub_section).$diin->serial_no;
			}
		}
		$schema['di'] = array(
			'description' => 'TODO: please describe this table!',
			'fields' => array(
				'adm_no' => array(
					'description' => 'TODO: please describe this field!',
					'type' => 'varchar',
					'length' => '50',
					'not null' => FALSE,
				),
				'section' => array(
					'description' => 'TODO: please describe this field!',
					'type' => 'varchar',
					'length' => '50',
					'not null' => FALSE,
				),
			),
			'primary key' => array('adm_no'),
		);
		
		foreach($col_names as $cn){
			$fields[$cn] = array(
				'description' => 'TODO: please describe this field!',
				'type' => 'varchar',
				'length' => '50',
				'not null' => FALSE,
			);
		}
		
		foreach($fields as $cn => $field){
			$schema['di']['fields'][$cn] = $field;
		}
		
		$exam_code = clean_exam_code_string($form_state['values']['exam_code']);
		$name_of_table = 'essa_'.$session.'_exam_'.$form_state['values']['term_id'].'_'.$exam_code.'_'.$cl.'_di';
		if(!db_table_exists($name_of_table)){
			db_create_table($name_of_table, $schema['di']);
		}else{
			db_drop_table($name_of_table);
			db_create_table($name_of_table, $schema['di']);
		}
	}
}

/**
 *Implements rebuild function
 */
function rebuild_db($form, &$form_state){
	$session = variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session.'_exam_master';
	$class_table = 'essa_'.$session.'_class_list';
	($form_state['values']['class_from'] == '--Select--') ? $class_from = NULL: $class_from = $form_state['values']['class_from'];
	($form_state['values']['class_to'] == '--Select--') ? $class_to = NULL: $class_to = $form_state['values']['class_to'];
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
		$classes[] = $c->class_id;
	}
	
	foreach($classes as $cl){
		$exam_code = clean_exam_code_string($form_state['values']['exam_code']);
		$table = 'essa_'.$session.'_exam_'.$form_state['values']['term_id'].'_'.$exam_code.'_'.$cl;
		$subject_table = 'essa_'.$session.'_subjects_'.$cl;
		$subjects = db_query("SELECT * FROM {$subject_table};");
		foreach($subjects as $subject){
			$field = $subject->sub_id;
			$spec = array(
				'description' => 'TODO: please describe this field!',
				'type' => 'float',
				'not null' => FALSE,
			);
			$grade_spec = array(
				'description' => 'TODO: please describe this field!',
				'type' => 'varchar',
				'length' => '20',
				'not null' => FALSE,
			);
			
			if(!db_field_exists($table, $field)){
				$grade_field = 'grade_'.$subject->sub_id;
				$grade_point_field = 'grade_point_'.$subject->sub_id;
				$cf_field = 'cf_'.$subject->sub_id;
				db_add_field($table, $field, $spec);
				db_add_field($table, $grade_field, $grade_spec);
				db_add_field($table, $grade_point_field, $spec);
				db_add_field($table, $cf_field, $spec);
			}
			
			$table = 'essa_'.$session.'_exam_'.$form_state['values']['term_id'].'_'.$cl;
			if(!db_field_exists($table, $field)){
				$grade_field = 'grade_'.$subject->sub_id;
				$grade_point_field = 'grade_point_'.$subject->sub_id;
				$cf_field = 'cf_'.$subject->sub_id;
				db_add_field($table, $field, $spec);
				db_add_field($table, $grade_field, $grade_spec);
				db_add_field($table, $grade_point_field, $spec);
				db_add_field($table, $cf_field, $spec);
			}
		}
	}
	
	drupal_set_message('Exam was Rebuild','status');
}

function delete_exam($form, &$form_state){
	global $user;
	variable_set('delete-exam_code'.$user->uid, $form_state['values']['exam_code']);
	variable_set('delete-term_id'.$user->uid, $form_state['values']['term_id']);
	$url = url('delete-exam', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
}

function delete_exam_pagecallback(){
	return drupal_get_form('delete_exam_confirm');
}

function delete_exam_confirm($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	global $user;
	$term_id = variable_get('delete-term_id'.$user->uid);
	$exam_code = variable_get('delete-exam_code'.$user->uid);
	
	$heading = t('Are you sure to delete this Exam.');
	$caption = '<h3>This action can\'t be undone.</h3>';
	
	$cancel_path = 'admin/exam/'.$term_id.'/'.$exam_code;
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

/**
 *Implements delete function
 */
function delete_exam_confirm_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session.'_exam_master';
	$imp_date_table = 'essa_'.$session.'_exam_imp_dates';
	$class_table = 'essa_'.$session.'_class_list';
	global $user;
	$term_id = variable_get('delete-term_id'.$user->uid);
	$exam_code = variable_get('delete-exam_code'.$user->uid);
	
	$ec = db_query("SELECT * FROM {$master_exam_table} where term = :t and exam_code = :ec",
						array(':t' => $term_id, ':ec' => $exam_code));
	foreach($ec as $ex){
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
		$classes[] = $c->class_id;
	}
	
	foreach($classes as $cl){
		$ex_code = clean_exam_code_string($exam_code);
		$table = 'essa_'.$session.'_exam_'.$term_id.'_'.$ex_code.'_'.$cl;
		$new_name = 'essa_'.$session.'_exam_'.$term_id.'_'.$ex_code.'_'.$cl.'_deleted';
		if(db_table_exists($new_name)){
			
			db_drop_table($new_name);
		}
		db_rename_table($table, $new_name);
	}
	
	db_delete($master_exam_table)
		->condition('exam_code', $exam_code)
		->execute();
		
		db_delete($imp_date_table)
		->condition('exam_code', $exam_code)
		->execute();
	
	global $base_url;
	$url = $base_url.'/admin/exam/'.$term_id.'/create_term_exam';
	$form_state['redirect'] = $url;
	menu_rebuild();
}