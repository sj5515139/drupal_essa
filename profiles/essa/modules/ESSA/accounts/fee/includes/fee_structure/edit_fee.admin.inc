<?php

/**
 *Implements page callback function - edit_fee_form
 */
function edit_fee_form($form, &$form_state, $fee_id){
  //dsm($fee_id);
  $form = array();
  $session_id = variable_get('essa_sid');
	$session = str_replace('_', '-', $session_id);
	$op = array();
  
  $form['fee_id'] = array(
    '#type' => 'value',
    '#value' => $fee_id,
  );
	
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees = db_query("
    SELECT * from {$fees_table} where fee_id = :fee_id;", array(':fee_id' => $fee_id)
  );
	
  foreach($fees as $fee){
    $particulars = $fee->particulars;
    $frequency = $fee->frequency;
    $amount = $fee->amount;
    $apt = $fee->applies_to;
    $cf = $fee->class_from;
    $ct = $fee->class_to;
    $ops = $fee->optional_sub;
		$facility = $fee->facility;
		$df = $fee->distance_from;
		$dt = $fee->distance_to;
		$is_hostel = $fee->is_hostel;
  }
	$form['help'] = array(
		'#type' => 'markup',
		'#markup' => '<h4>This Fee Structure applies to <b>'.$session.'</b> session.</h4>',
	);
	
  $form['particulars'] = array(
    '#type' => 'textfield',
    '#title' => t('Particulars'),
    '#required' => TRUE,
    '#default_value' => isset($particulars)?$particulars:NULL,
  );
  
	$form['frequency'] = array(
    '#type' => 'select',
    '#title' => t('Frequency'),
    '#options' => drupal_map_assoc(array('One-Time' , 'Annual' , 'Monthly' , 'Quaterly')),
    '#required' => TRUE,
    '#default_value' => isset($frequency)?$frequency:NULL,
  );
	
  $form['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Amount(in Rupees)'),
    '#size' => 10,
    '#required' => TRUE,
    '#default_value' =>isset($amount)?$amount:NULL,
  );
  
  $form['applies_to'] = array(
    '#type' => 'radios',
    '#title' => t('Applies to'),
    '#options' => drupal_map_assoc(array('All' , 'Class-wise' , 'Optional', 'Facility-Wise')),
		'#default_value' => 'All',
    '#default_value' =>isset($apt)?$apt:NULL,
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
    '#default_value' =>isset($cf)?$cf:NULL,
  );
  
  $form['cf']['class_to'] = array(
    '#type' => 'select',
    '#title' => t('Class To'),
    '#options' => drupal_map_assoc($options),
    '#default_value' =>isset($ct)?$ct:NULL,
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
    '#default_value' =>isset($cf)?$cf:NULL,
  );
  
  $form['op']['sub_class_to'] = array(
    '#type' => 'select',
    '#title' => t('Class To'),
    '#options' => drupal_map_assoc($options),
    '#default_value' =>isset($ct)?$ct:NULL,
  );
  
	$form['op']['optional'] = array(
    '#type' => 'select',
    '#title' => t('Select an optional Subject to apply this fees - '),
    '#options' => drupal_map_assoc(array_unique($op)),
    '#default_value' =>isset($ops)?$ops:NULL,
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
		'#default_value' =>isset($facility)?$facility:NULL,
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
		'#default_value' =>isset($is_hostel)?$is_hostel:NULL,
	);
	
	$form['fw']['hs']['hs_class_from'] = array(
		'#type' => 'select',
    '#title' => t('Class From'),
    '#options' => drupal_map_assoc($options),
		'#default_value' =>isset($cf)?$cf:NULL,
	);
	
	$form['fw']['hs']['hs_class_to'] = array(
		'#type' => 'select',
    '#title' => t('Class To'),
    '#options' => drupal_map_assoc($options),
		'#default_value' =>isset($ct)?$ct:NULL,
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
		'#default_value' =>isset($df)?$df:NULL,
	);
	
	$form['fw']['tr']['distance_to'] = array(
		'#type' => 'select',
    '#title' => t('Distance To'),
    '#options' => drupal_map_assoc($distance),
		'#default_value' =>isset($dt)?$dt:NULL,
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
function edit_fee_form_submit($form, &$form_state){
	//dsm($form_state);
	$session = variable_get('essa_sid');
	$table = 'essa_'.$session.'_'.'fees_structure';
	
	db_merge($table)
    ->key(array('fee_id' => $form_state['values']['fee_id']))
  	->fields (array(
			'particulars' => $form_state['values']['particulars'],
			'frequency' => $form_state['values']['frequency'],
			'amount' => $form_state['values']['amount'],
			'applies_to' => $form_state['values']['applies_to'],
		)
	)	
	->execute();
	
	if($form_state['values']['applies_to'] == 'Class-wise'){
		db_update($table) // Table name no longer needs {}
			->fields(array(
					'class_from' => $form_state['values']['class_from'],
					'class_to' => $form_state['values']['class_to'],
				))
			-> condition('fee_id', $form_state['values']['fee_id'], '=')
			->execute();
	}elseif($form_state['values']['applies_to'] == 'Optional'){
		db_update($table) // Table name no longer needs {}
			->fields(array(
					'class_from' => $form_state['values']['sub_class_from'],
					'class_to' => $form_state['values']['sub_class_to'],
					'optional_sub' => $form_state['values']['optional'],
				))
			-> condition('fee_id', $form_state['values']['fee_id'], '=')
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
				-> condition('fee_id', $form_state['values']['fee_id'], '=')
				->execute();
		}elseif($form_state['values']['fw_op'] == 'Transport'){
			db_update($table) // Table name no longer needs {}
				->fields(array(
						'facility' => $form_state['values']['fw_op'],
						'distance_from' => $form_state['values']['distance_from'],
						'distance_to' => $form_state['values']['distance_to'],
					))
				-> condition('fee_id', $form_state['values']['fee_id'], '=')
				->execute();
		}
	}
	//drupal_flush_all_caches();
	//manage_student_fee_table();
  //$form_state['redirect'] = 'admin/accounts/fees/fee_structure';
}
