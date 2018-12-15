<?php
/**
 *Implements page callback function- fine
 */
function fine($form, &$form_state){
	$sel_ect = array('--Select--');
	$fines = array();
	$fines = variable_get('essa_fine');
	$fines = array_merge($sel_ect, $fines);
	$form['fine_type'] = array(
		'#type' => 'select',
		'#title' => 'Fine Type',
		'#options' => $fines,
		'#default_value' => '0',
	);
	
	$form['new_fine'] = array(
		'#type' => 'textfield',
		'#size' => 20,
		'#attributes' => array('placeholder' => 'Create new fine type.'),
	);
	
	$form['amount'] = array(
		'#type' => 'textfield',
		'#title' => 'Amount',
		'#required' => TRUE,
	);
	
	$form['applies_to'] = array(
		'#type' => 'radios',
		'#title' => t('Applies to'),
		'#options' => drupal_map_assoc(array('All' , 'Student', 'Class-Section', 'Class-wise')),
		'#default_value' => 'Student',
		'#required' => TRUE,
	);
	
	$form['op'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name = "applies_to"]' => array('value' => 'Student'),
      ),
    ),
  );
	
	$form['op']['adm_no'] = array(
    '#type' => 'textfield',
		'#autocomplete_path' => 'adm_no/fee_autocomplete',
    '#title' => t('Admission No.'),
    '#size' => 10,
  );
	
	$form['cs'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name = "applies_to"]' => array('value' => 'Class-Section'),
      ),
    ),
  );
	
	$config = fee_hs_setting();
	$form['cs']['class'] =  array(
    '#title' => t('Select a Class - '),
    '#type' => 'hierarchical_select',
    '#config' => $config,
  );
  
  $form['cf'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name = "applies_to"]' => array('value' => 'Class-wise'),
      ),
    ),
  );
  
	$options = array('--Select--');
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	foreach($classes as $class){
		$options[] = $class->class_id;
	}
  
  $form['cf']['class_from'] = array(
    '#type' => 'select',
    '#title' => t('Class From'),
    '#options' => drupal_map_assoc($options),
  );
  
  $form['cf']['class_to'] = array(
    '#type' => 'select',
    '#title' => t('Class To'),
    '#options' => drupal_map_assoc($options),
  );
	
	$session = (string)variable_get('essa_sid');
	$basic_info_table = 'essa_'.$session.'_basicinfo';
	$binfo = db_query("
    SELECT * from {$basic_info_table};
  ");
	foreach($binfo as $info){
		$start_date = $info->academicyearstart;
		$end_date = $info->academicyearend;
	}
  $start = new DateTime($start_date);
	$start->modify('first day of this month');
	$end      = new DateTime($end_date);
	$end->modify('first day of next month');
	$interval = DateInterval::createFromDateString('1 month');
	$period   = new DatePeriod($start, $interval, $end);
	foreach ($period as $dt) {
		$mon_options[] = $dt->format("M-Y");
	}
  
  $form['for_mon'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select Months'),
    '#options' => drupal_map_assoc($mon_options),
    '#checkall' => 'unique-class-for-each-checkboxes-column',
  );
	
	$form['set_date'] = array(
    '#title' => t('Set Collection Date'),
    '#type' => 'date_select',
		'#date_label_position' => 'within',
		'#date_format' => 'd',
    '#default_value' => date('d'),
  );
	
	$form['eom'] = array(
		'#type' => 'radio',
		'#title' => 'Set last date of the month as collection date.'
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	
	return $form;
}

/**
 *Implements validate function.
 */
function fine_validate($form, &$form_state){
	$session = variable_get('essa_sid');
	$fine_table = 'essa_'.$session.'_fees_student_fine';
	$student_table = 'essa_'.$session.'_master_student_table';
	$class_table = 'essa_'.$session.'_class_list';
	$mons = array();
	
	foreach($form_state['values'] as $key => $val){
		if(is_array($val) && $key == 'for_mon'){
			foreach($val as $v){
				if($v != '0'){
					$mons[] = $v;
				}
			}
		}
	}
	if($form_state['values']['fine_type'] == '0' && $form_state['values']['new_fine'] == NULL){
		form_set_error('fine_type', '<h3 style = "color: RED; padding-top: 15px;"><b>Either select a fine type of create a new type.</b></h3>');
	}
	
	if(empty($mons)){
		form_set_error('for_mon', '<h3 style = "color: RED; padding-top: 15px;"><b>Select atleast one month to apply the fine.</b></h3>');
	}
	
	if($form_state['values']['applies_to'] == 'Student'){
		if($form_state['values']['adm_no'] == NULL){
			form_set_error('adm_no', '<h3 style = "color: RED; padding-top: 15px;"><b>Admission No. of the student is required.</b></h3>');
		}else{
			$flag = 0;
			$stud_detail = db_query(
				"SELECT * from $student_table where adm_no = :adm_no AND status = 1;", array(':adm_no' => $form_state['values']['adm_no'])
			);
			foreach($stud_detail as $sd){
				$flag =1;
			}
			if($flag == 0){
				form_set_error('adm_no', '<h3 style = "color: RED; padding-top: 15px;"> Entered admission no. <b>'.$form_state['values']['adm_no'].'</b> is not present in the system. </h3>');
			}
		}
	}
	
	if($form_state['values']['applies_to'] == 'Class-Section'){
		if(!isset($form_state['values']['class'][1])){
			form_set_error('class', '<h3 style = "color: RED; padding-top: 15px;"><b>Class-Section is required.</b></h3>');
		}
	}
	
	if($form_state['values']['applies_to'] == 'Class-wise'){
		if($form_state['values']['class_from'] == '--Select--'){
			form_set_error('class_from', '<h3 style = "color: RED; padding-top: 15px;"><b>Class From is required.</b></h3>');
		}
		
		if($form_state['values']['class_to'] == '--Select--'){
			form_set_error('class-to', '<h3 style = "color: RED; padding-top: 15px;"><b>Class To is required.</b></h3>');
		}
	}
}

/**
 *Implements submit function.
 */
function fine_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$fine_table = 'essa_'.$session.'_fees_student_fine';
	$student_table = 'essa_'.$session.'_master_student_table';
	$class_table = 'essa_'.$session.'_class_list';
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	$mons = array();
	
	if($form_state['values']['new_fine'] != '' || $form_state['values']['new_fine'] !=NULL){
		$fines = variable_get('essa_fine');
		$fines[$form_state['values']['new_fine']] = $form_state['values']['new_fine'];
		$new_fine = array_unique($fines);
		variable_set('essa_fine', $new_fine);
	}
	
	if($form_state['values']['fine_type'] == '0'){
		$fine_type = $form_state['values']['new_fine'];
 	}else{
		$fine_type = $form_state['values']['fine_type'];
	}
	
	foreach($form_state['values'] as $key => $val){
		if(is_array($val) && $key == 'for_mon'){
			foreach($val as $v){
				if($v != '0'){
					$col = str_replace('-', '_', $v);
					$eom = $form_state['values']['eom'];
					if($eom == 'on'){
						$dt = strtotime('1'.'-'.$v);
						$end_dt = date("Y-m-t", $dt);
						$deadline = strtotime($end_dt);
					}else{
						$deadline = strtotime($form_state['values']['set_date'].'-'.$v);	
					}
					$m = str_replace('-','_',$v);
					$mons[$m] = $deadline;
				}
			}
		}
	}
	
	if($form_state['values']['applies_to'] == 'All'){
		$students = db_query("
			SELECT * from {$student_table} WHERE status = 1;"
		);
		foreach($students as $st){
			foreach($mons as $mon=>$due_dt){
				db_insert($fine_table)
					->fields (array(
						'adm_no' => $st->adm_no,
						'particulars' => $fine_type,
						'month' => $mon,
						'collection_date' => $due_dt,
						'amount_to_be_paid' => $form_state['values']['amount'],
					)
				)	
				->execute();
			}
			
			
			//*********SURAJ***************
			//sending system alert
			global $user;
			$created_date = date("Y-m-d H:i:s");
			$strtodate = strtotime($created_date);
			db_insert($sys_alert_table)
			->fields(array(
				'message' => 'Fine '.$fine_type.' has been applied to '.$st->adm_no.'.',
				'priority' => 'M',
				'module' => 'fee',
				'source_url' => 'admin/fees/fine/apply-fine',
				'timestamp' => $strtodate,
				'source_uid' => $user->uid,
			))
			->execute();
			//*********SURAJ***************
		}
	}
	
	if($form_state['values']['applies_to'] == 'Student'){
		$adm_no = $form_state['values']['adm_no'];
		foreach($mons as $mon=>$due_dt){
			db_insert($fine_table)
				->fields (array(
					'adm_no' => $adm_no,
					'particulars' => $fine_type,
					'month' => $mon,
					'collection_date' => $due_dt,
					'amount_to_be_paid' => $form_state['values']['amount'],
				)
			)	
			->execute();
		}
		
		//*********SURAJ***************
		//sending system alert
		global $user;
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
			'message' => 'Fine '.$fine_type.' has been applied to '.$adm_no.'.',
			'priority' => 'M',
			'module' => 'fee',
			'source_url' => 'admin/fees/fine/apply-fine',
			'timestamp' => $strtodate,
			'source_uid' => $user->uid,
		))
		->execute();
		//*********SURAJ***************
	}
	
	if($form_state['values']['applies_to'] == 'Class-Section'){
		$class = taxonomy_term_load($form_state['values']['class'][0]);
		$section = taxonomy_term_load($form_state['values']['class'][1]);
		$sts = db_query("
			SELECT * from {$student_table} where class = :c and section = :sec AND status = 1;", array(':c' => $class->name, ':sec' => $section->name)
		);
		foreach($sts as $st){
			foreach($mons as $mon=>$due_dt){
				db_insert($fine_table)
					->fields (array(
						'adm_no' => $st->adm_no,
						'particulars' => $fine_type,
						'month' => $mon,
						'collection_date' => $due_dt,
						'amount_to_be_paid' => $form_state['values']['amount'],
					)
				)	
				->execute();
			}
			
			//*********SURAJ***************
			//sending system alert
			global $user;
			$created_date = date("Y-m-d H:i:s");
			$strtodate = strtotime($created_date);
			db_insert($sys_alert_table)
			->fields(array(
				'message' => 'Fine '.$fine_type.' has been applied to '.$st->adm_no.'.',
				'priority' => 'M',
				'module' => 'fee',
				'source_url' => 'admin/fees/fine/apply-fine',
				'timestamp' => $strtodate,
				'source_uid' => $user->uid,
			))
			->execute();
			//*********SURAJ***************
		}
	}
	
	if($form_state['values']['applies_to'] == 'Class-wise'){
		$classes = db_query("
			SELECT * from {$class_table} where class_id = :ci;", array(':ci' => $form_state['values']['class_from'])
		);
		foreach($classes as $class){
			$class_from_weight = $class->weight;
		}
		$classes = db_query("
			SELECT * from {$class_table} where class_id = :ci;", array(':ci' => $form_state['values']['class_to'])
		);
		foreach($classes as $class){
			$class_to_weight = $class->weight;
		}
		$cls = db_query("
			SELECT * from {$class_table} where weight BETWEEN :wf AND :wt order by weight;", array(':wf' => $class_from_weight, ':wt' => $class_to_weight)
		);
		foreach($cls as $cl){
			$sts = db_query("
			  SELECT * from {$student_table} where class = :c AND status = 1;", array(':c' => $cl->class_id)
			);
			foreach($sts as $st){
				foreach($mons as $mon=>$due_dt){
					db_insert($fine_table)
						->fields (array(
							'adm_no' => $st->adm_no,
							'particulars' => $fine_type,
							'month' => $mon,
							'collection_date' => $due_dt,
							'amount_to_be_paid' => $form_state['values']['amount'],
						)
					)	
					->execute();
				}
				
				//*********SURAJ***************
				//sending system alert
				global $user;
				$created_date = date("Y-m-d H:i:s");
				$strtodate = strtotime($created_date);
				db_insert($sys_alert_table)
				->fields(array(
					'message' => 'Fine '.$fine_type.' has been applied to '.$st->adm_no.'.',
					'priority' => 'M',
					'module' => 'fee',
					'source_url' => 'admin/fees/fine/apply-fine',
					'timestamp' => $strtodate,
					'source_uid' => $user->uid,
				))
				->execute();
				//*********SURAJ***************
				
			}
		}
	}
	
	drupal_set_message('<h3 style = "color: GREEN; padding-top: 15px;"><b>Fine was successfully applied to student(s).</b></h3>','status');
}

/**
 *Implements setting function for heirarchical select form class and section
 */
function fee_hs_setting(){
	// Load category based in vocabulary machine name
	$voc = 'class_vocab';//replace this with the taxonomy term
  $vocabulary = taxonomy_vocabulary_machine_name_load($voc);
	
	$config = array(
		'module' => 'hs_taxonomy',
    'params' => array(
				'vid' => (int) $vocabulary->vid,
				'exclude_tid' => NULL,
				'root_term' => NULL,
				'entity_count_for_node_type' => NULL,
      ),
		'config_id'       => 'taxonomy-2',
		'save_lineage'    => 1,
		'enforce_deepest' => 0,
		'entity_count'    => 0,
		'require_entity'  => 0,
		'resizable'       => 0,
		'render_flat_select' => 0,
		'level_labels' => array(
		  'status' => 1,
		  'labels' => array(
		    0 => '--Select--',
		    1 => '--Select--',
		  ),
		),
		'dropbox' => array(
		  'status'    => 0,
		),
		'editability' => array(
		  'status' => 0,
		  'item_types' => array(
		    0 => '',
		    1 => '',
		  ),
		  'allowed_levels' => array(
		    0 => 1,
		    1 => 1,
		  ),
		  'allow_new_levels' => 0,
		  'max_levels'       => 1,
		),
	);
	
	return $config;
}