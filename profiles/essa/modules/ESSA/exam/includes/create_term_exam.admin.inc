<?php
/**
 * Implements callback function create_exam()
 */
function create_term_exam($form = array(), &$form_state, $term_id){
	global $base_url;
	$form['help'] = array(
		'#type' => 'markup',
		'#markup' => '<h3><b>Note :- </b>These exams are inter-dependent and they cumulatively produces result for assigned term.
		</h3><h4>Please make sure all the <u><a href ="'.$base_url.'/admin/settings/subjects">subjects & respective teachers</a></u>
		are saved in the system. However, in case you forgot a subject, you can rebuild your exam using the "Rebuild" button in the exam menu link.
		But make sure after adding the subject you click <b>"Rebuild"</b> button.</h4>'
	);
	$form['exam_code'] = array(
		'#type' => 'textfield',
		'#title' => 'Exam Code',
		'#required' => TRUE,
		'#description' => 'It must be Unique.',
		'#size' => '20',
 	);
	$form['exam_name'] = array(
		'#type' => 'textfield',
		'#title' => 'Exam Name',
		'#required' => TRUE,
		'#size' => '20',
 	);
	$def_dt = date('Y-m-d');
	$form['date_from'] = array(
		'#type' => 'date_popup',
		'#size' => 15,
		'#date_label_position' => 'within',
		'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
		'#date_format' => 'd-m-Y',
		'#date_year_range' => '0:+1',
		'#title' => 'Date From',
 	);
	$form['date_to'] = array(
		'#type' => 'date_popup',
		'#size' => 15,
		'#date_label_position' => 'within',
		'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
		'#date_format' => 'd-m-Y',
		'#date_year_range' => '0:+1',
		'#title' => 'Date To',
 	);
	
	$form['weight'] = array(
		'#type' => 'textfield',
		'#title' => 'Weight(%age)',
		'#size' => '10',
		'#required' => TRUE,
 	);
	$sittings = array('0' => '1', '1' => '2', '2' => '3', '3' => '4', '4' => '5');
	$form['no_of_sitting'] = array(
		'#type' => 'select',
		'#title' => 'No. of Sitting(Per Day)',
		'#options' => drupal_map_assoc($sittings),
 	);
	
	if(variable_get('di_status') == TRUE){
		$form['di_status'] = array(
			'#type' => 'checkbox',
			'#title' => 'Include Descriptive Indicators?',
		);
	}
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id,
	);
	return $form;
}


/**
 *Implements form validation function.
 */
function create_term_exam_validate($form, &$form_state){
	$session = variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session.'_exam_master';
	$ec = db_query("SELECT * FROM {$master_exam_table} WHERE term = :t;",array(':t' => $form_state['values']['term_id']));
	$exam_code = array();
	foreach($ec as $e){
		$exam_code[] = $e->exam_code;
	}
	
	$ec = $form_state['values']['exam_code'];
	
	if(in_array($ec,$exam_code)){
		form_set_error('exam_code','Exam code must be unique. '.$ec.' is already created.');
	}
	$date_from = strtotime($form_state['values']['date_from']);
	$date_to = strtotime($form_state['values']['date_to']);
	if($date_from > $date_to){
		form_set_error('date_to','Please check the dates entered.');
	}
	if($form_state['values']['weight'] != NULL && !is_numeric($form_state['values']['weight'])){
		form_set_error('weight','Weight(%age) must be numeric.');
	}
}

/**
 * Implements submit function create_exam_submit()
 */
function create_term_exam_submit($form = array(), &$form_state){
	$session = variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session.'_exam_master';
	$class_table = 'essa_'.$session.'_class_list';
	$exam_term_table = 'essa_'.$session.'_exam_terms';
	
	$exam_term = db_query("SELECT * FROM {$exam_term_table} WHERE id =:id;", array(':id' => $form_state['values']['term_id']));
	foreach($exam_term as $et){
		$class_from = $et->class_from;
		$class_to = $et->class_to;
	}
	db_insert($master_exam_table)
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
	if(!is_dir("sites/default/files/exam/".$form_state['values']['term_id'].'/'.$form_state['values']['exam_code'])){
		mkdir("sites/default/files/exam/".$form_state['values']['term_id'].'/'.$form_state['values']['exam_code']);
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
		
		if($form_state['values']['di_status'] == 1){
			create_di_db_table($form, $form_state);
		}
		
		$exam_code = clean_exam_code_string($form_state['values']['exam_code']);
		$name_of_table = 'essa_'.$session.'_exam_'.$form_state['values']['term_id'].'_'.$exam_code.'_'.$cl;
		if(!db_table_exists($name_of_table)){
			db_create_table($name_of_table, $schema['marks']);
		}
		
		//**********Inserting the default dates in Imp Date table*****************
		$imp_date_table = 'essa_'.$session.'_exam_imp_dates';
		db_insert($imp_date_table)
		->fields(array(
			'term_id' => $form_state['values']['term_id'],
			'exam_code' => $form_state['values']['exam_code'],
			'class' => $cl,
			'title' => 'Date of submission of question paper'
		))
		->execute();
		
		db_insert($imp_date_table)
		->fields(array(
			'term_id' => $form_state['values']['term_id'],
			'exam_code' => $form_state['values']['exam_code'],
			'class' => $cl,
			'title' => 'Date of submission of checked answer sheet'
		))
		->execute();
		
		db_insert($imp_date_table)
		->fields(array(
			'term_id' => $form_state['values']['term_id'],
			'exam_code' => $form_state['values']['exam_code'],
			'class' => $cl,
			'title' => 'Date of result declaration'
		))
		->execute();
		//****************************************************************
	}
	
	global $user;
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	//sending system alert
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'Exam '.$form_state['values']['term_id'].' - '.$form_state['values']['exam_code'].' has been created.',
		'priority' => 'M',
		'module' => 'Exam',
		'source_url' => 'admin/exam/create_exam',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	
	global $base_url;
	$url = $base_url.'/admin/exam/'.$form_state['values']['exam_code'].'/exam_schedule';
	drupal_set_message($form_state['values']['exam_code'].' exam has been created successfully. You can now create schedule <a href = "'.$url.'">here</a>','status');
	menu_rebuild();
}

function create_di_db_table($form, &$form_state){
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
	$this_grp = NULL;
	$col_names = array();
	$fields = array();
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
		}
	}
}
