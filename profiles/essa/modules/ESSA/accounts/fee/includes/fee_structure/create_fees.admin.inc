<?php

/**
 *Implements page callback function fee_structure.
 */
function create_fees($form, &$from_state){
  $form = array();
  $session_id = variable_get('essa_sid');
	$session = str_replace('_', '-', $session_id);
	$op = array();
	
	$form['help'] = array(
		'#type' => 'markup',
		'#markup' => '<h4>This Fee Structure applies to <b>'.$session.'</b> session.</h4>',
	);
	
  $form['particulars'] = array(
    '#type' => 'textfield',
    '#title' => t('Particulars'),
    '#required' => TRUE,
  );
  $freq_options = array();
  $session = variable_get('essa_sid');
	$table = 'essa_'.$session.'_fees_frequency';
	$freq = db_query("
    SELECT * from {$table}"
  );
  foreach($freq as $fr){
    $freq_options[] = $fr->freq_name;
  }
	
	global $base_url;
	$url = $base_url.'/admin/fees/fee_structure#overlay=admin/fees/fee_structure/set_frequency';
	if($freq_options == NULL){
		drupal_set_message('No frequency has been created. Please set frequencies, <a href = "'.$url.'">here</a>.', 'warning');
	}
  
	$form['frequency'] = array(
    '#type' => 'select',
    '#title' => t('Frequency'),
    '#options' => drupal_map_assoc($freq_options),
    '#required' => TRUE,
  );
	
  $form['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Amount(in Rupees)'),
    '#size' => 10,
    '#required' => TRUE,
  );
  
  $form['applies_to'] = array(
    '#type' => 'radios',
    '#title' => t('Applies to'),
    '#options' => drupal_map_assoc(array('All' , 'Class-wise' , 'Optional', 'Facility-Wise')),
		'#default_value' => 'All',
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
	
	$form['op'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name = "applies_to"]' => array('value' => 'Optional'),
      ),
    ),
  );
	
	$session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	foreach($classes as $class){
		$subject_table[] = 'essa_'.$session_id.'_subjects_'.$class->class_id;
	}
	
	foreach($subject_table as $table){
		$optional_subjects = db_query("
		  SELECT sub_id from {$table} where type = 'Optional';
		");
		
		foreach($optional_subjects as $sub){
			$op[] = $sub->sub_id;
		}
	}
	
	$form['op']['sub_class_from'] = array(
    '#type' => 'select',
    '#title' => t('Class From'),
    '#options' => drupal_map_assoc($options),
  );
  
  $form['op']['sub_class_to'] = array(
    '#type' => 'select',
    '#title' => t('Class To'),
    '#options' => drupal_map_assoc($options),
  );
	
	$form['op']['optional'] = array(
    '#type' => 'select',
    '#title' => t('Select an optional Subject to apply this fees - '),
    '#options' => drupal_map_assoc(array_unique($op)),
  );
	
  $form['fw'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name = "applies_to"]' => array('value' => 'Facility-Wise'),
      ),
    ),
  );
	
	$form['fw']['fw_op'] = array(
		'#type' => 'select',
		'#title' => t('Select a Facility'),
		'#options' => drupal_map_assoc(array('--Select--', 'Hostel' , 'Transport')),
	);
	
	$form['fw']['hs'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name = "fw_op"]' => array('value' => 'Hostel'),
      ),
    ),
  );
	
	$form['fw']['hs']['hs_is_hostel'] = array(
		'#type' => 'radios',
    '#title' => t('Applies To'),
    '#options' => array('Yes' => 'Boarder', 'No' => 'Day-Scholar'),
	);
	
	$form['fw']['hs']['hs_class_from'] = array(
		'#type' => 'select',
    '#title' => t('Class From'),
    '#options' => drupal_map_assoc($options),
	);
	
	$form['fw']['hs']['hs_class_to'] = array(
		'#type' => 'select',
    '#title' => t('Class To'),
    '#options' => drupal_map_assoc($options),
	);
	
	$form['fw']['tr'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name = "fw_op"]' => array('value' => 'Transport'),
      ),
    ),
  );
	
	for($i = 0; $i<100; $i++){
		$distance[] = $i;
	}
	
	$form['fw']['tr']['distance_from'] = array(
		'#type' => 'select',
    '#title' => t('Distance From'),
    '#options' => drupal_map_assoc($distance),
	);
	
	$form['fw']['tr']['distance_to'] = array(
		'#type' => 'select',
    '#title' => t('Distance To'),
    '#options' => drupal_map_assoc($distance),
	);
	
	
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 *Implements the submit function for create_fees.
 */
function create_fees_submit($form, &$form_state){
	//dsm($form_state);
	$session = variable_get('essa_sid');
	$table = 'essa_'.$session.'_'.'fees_structure';
	$freq_table = 'essa_'.$session.'_fees_frequency';
	$freq = db_query("
    SELECT * from {$freq_table} where freq_name = :freq", array(':freq' => $form_state['values']['frequency'])
  );
  foreach($freq as $fr){
    $freq_id = $fr->freq_id;
  }
  
	db_insert($table)
		->fields (array(
			'particulars' => $form_state['values']['particulars'],
			'frequency' => $form_state['values']['frequency'],
      'freq_id' => $freq_id,
			'amount' => $form_state['values']['amount'],
			'applies_to' => $form_state['values']['applies_to'],
      
		)
	)	
	->execute();
	
  
	$fee_id = db_query("
		SELECT fee_id from {$table};
	");
	
	foreach($fee_id as $id){
		$update_id = $id->fee_id;
	}
	
	//'All' , 'Class-wise' , 'Optional'
	if($form_state['values']['applies_to'] == 'Class-wise'){
		db_update($table) // Table name no longer needs {}
			->fields(array(
					'class_from' => $form_state['values']['class_from'],
					'class_to' => $form_state['values']['class_to'],
				))
			-> condition('fee_id', $update_id, '=')
			->execute();
	}elseif($form_state['values']['applies_to'] == 'Optional'){
		db_update($table) // Table name no longer needs {}
			->fields(array(
					'class_from' => $form_state['values']['sub_class_from'],
					'class_to' => $form_state['values']['sub_class_to'],
					'optional_sub' => $form_state['values']['optional'],
				))
			-> condition('fee_id', $update_id, '=')
			->execute();
	}
	
	if($form_state['values']['applies_to'] == 'Facility-Wise'){
		if($form_state['values']['fw_op'] == 'Hostel'){
			db_update($table) // Table name no longer needs {}
				->fields(array(
						'facility' => $form_state['values']['fw_op'],
						'class_from' => $form_state['values']['hs_class_from'],
						'class_to' => $form_state['values']['hs_class_to'],
						'is_hostel' => $form_state['values']['hs_is_hostel']
					))
				-> condition('fee_id', $update_id, '=')
				->execute();
		}elseif($form_state['values']['fw_op'] == 'Transport'){
			db_update($table) // Table name no longer needs {}
				->fields(array(
						'facility' => $form_state['values']['fw_op'],
						'distance_from' => $form_state['values']['distance_from'],
						'distance_to' => $form_state['values']['distance_to'],
					))
				-> condition('fee_id', $update_id, '=')
				->execute();
		}
	}
	//***********SURAJ*************
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	global $user;
	//sending system alert
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => $form_state['values']['particulars'].' as fees has been created.',
		'priority' => 'L',
		'module' => 'fee',
		'source_url' => 'admin/fees/fee_structure/create_fees',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	drupal_set_message($form_state['values']['particulars'].' as fees has been created.','status');
	
	drupal_flush_all_caches();
}