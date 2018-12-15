<?php

/**
 *Implements page callback function - passout_form
 */
function passout_form($form, &$form_state){
	
	//dsm(variable_get('nonsense'));
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$student_withdrawal_table = 'essa_'.$session_id.'_student_withdrawal';
	
	$class_list = array('--Select--');
	$classes = db_query(
		"SELECT * from $class_table order by weight;"
	);
	foreach($classes as $cl){
		$class_list[] = $cl->class_id;
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
			  'callback' => 'display_student_ajax',
			  'wrapper' => 'sec_wrapper',
			  'method' => 'replace',
			  'effect' => 'fade',
			),
		);
		
		if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
			$student_table = 'essa_'.$session_id.'_'.'master_student_table';
			
			if(db_table_exists($student_table)){
				$header = array(
					'adm_no' => 'Adm No.',
					'roll_no' => 'Roll No.',
					'name' => 'Name',
				);
				$students = db_query(
					"SELECT * from $student_table where class = :class AND section = :sec order by roll_no;", array(':class' => $form_state['values']['class'], ':sec' => $form_state['values']['sec'])
				);
				foreach($students as $student){
					//dsm($student);
					$options[$student->adm_no] = array(
					  'adm_no' => $student->adm_no,
					  'roll_no' => $student->roll_no,
						'name' => $student->student_name,
					);
					
					//$def_val = db_query(
					//	"SELECT * from $student_withdrawal_table where adm_no = :an and type = 'passout';", array(':an' => $student->adm_no)
					//);
					//foreach($def_val as $dv){
					//	$prev[$dv->adm_no] = array(
					//	  'adm_no' => $student->adm_no,
					//	  'roll_no' => $student->roll_no,
					//		'name' => $student->student_name,
					//	);
					//}
				}
				//$options = array_diff_key($options, $prev);
			}
			$default = drupal_map_assoc($default);
			$form['sec_wrapper']['students'] = array(
				'#type' => 'tableselect',
			  '#header' => $header,
			  '#options' => $options,
				'#empty' => t('No Students.'),
				//'#default_value' => $default,
			);
			
			$form['sec_wrapper']['save'] = array(
				'#type' => 'button',
				'#name' => 'name',
				'#value' => t('Submit'),
				'#executes_submit_callback' => TRUE,
			);
		}
	}	
	return $form;
}

/**
 *Implements submit function - passout_form
 */
function passout_form_submit($form, &$form_state){
	
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$student_withdrawal_table = 'essa_'.$session_id.'_student_withdrawal';
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	
	$date = date('d-m-Y h:i:s');
	$timestamp = strtotime($date);
	global $user;	
	foreach($form_state['values'] as $key => $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				if($v !== 0){
					db_merge($student_withdrawal_table)
						->fields (array(
						  'adm_no' => $v,
							'type' => 'passout',
							'reason' => NULL,
							'status_fin' => NULL,
							'status_fin_reason' => NULL,
							'fin_timestamp' => NULL,
							'fin_uid' => NULL,
							'status' => 'pending',
							'status_reason' => NULL,
							'status_timestamp' => $timestamp,
							'status_uid' => $user->uid,
						)
					)	
					->execute();
				}
			}
		}
	}
	
	drupal_set_message('Passout application for selected students of '.$form_state['values']['class'].'-'.$form_state['values']['section'].' has been sent to Finance for approval.', 'status');
	//sending system alert
	global $user;
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'Passout application for selected students of '.$form_state['values']['class'].'-'.$form_state['values']['section'].' has been sent to Finance for approval.',
		'priority' => 'M',
		'module' => 'withdrawal',
		'source_url' => 'admin/students/withdrawal/passout',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	drupal_flush_all_caches();
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
function display_student_ajax($form, &$form_state){
	return $form;
}

/*
	$config = sa_hs_setting();
	$form['class'] =  array(
    '#title' => t('Select a Class - '),
    '#type' => 'hierarchical_select',
    '#config' => $config,
		'#required' => TRUE,
  );
	
	$form['list'] = array(
		'#type' => 'submit',
		'#value' => 'List Students',
		'#ajax' => array(
      'event' => 'click',
      'callback' => 'display_students_ajax',
      'wrapper' => 'class_student_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
	);
	
	$form['class_student_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "class_student_wrapper">',
		'#suffix' => '</div>',
	);
	
	dsm($form_state);
	
	if(!empty($form_state['values']['class'])){
		dsm('gr8');
	}
	
	*/