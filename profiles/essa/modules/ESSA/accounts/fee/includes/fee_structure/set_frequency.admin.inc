<?php

/**
 *Implements page callback function - set_frequency
 */
function set_frequency($form = array(), &$form_state){
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Frequency'),
		'#description' => 'Name of the frequency must be unique.',
		'#required' => TRUE,
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
		$options[] = $dt->format("M-Y");
	}
  
  $form['select_freq'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select Months'),
    '#options' => drupal_map_assoc($options),
    '#checkall' => TRUE,
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
    '#value'=> t('Submit'),
  );
	
  return $form;
}

/**
 *Implements validate function.
 */
function set_frequency_validate($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$freq_table = 'essa_'.$session_id.'_fees_frequency';
	
	$frq_name = array();
	$frequency = db_query("
		SELECT * from {$freq_table};"
	);
	foreach($frequency as $freq){
		$frq_name[] = $freq->freq_name;
	}
	
	if(in_array($form_state['values']['name'], $frq_name)){
		form_set_error('name', 'Frequency name - '.$form_state['values']['name'].' already exists. Please set a unique name for frequency.');
	}
}

/**
 *Implements submit function.
 */
function set_frequency_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$table = 'essa_'.$session.'_fees_frequency';
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	
	db_insert($table)
		->fields (array(
			'freq_name' => $form_state['values']['name'],
		)
	)	
	->execute();
  
  $freq = db_query("
    SELECT * from {$table} where freq_name = :fn;", array(':fn' => $form_state['values']['name'])
  );
  foreach($freq as $fr){
    $freq_id = $fr->freq_id;
  }
  
  foreach($form_state['values'] as $val){
    if(is_array($val)){
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
					
					db_update($table) // Table name no longer needs {}
          ->fields(array(
            $col => $deadline,
      		))
          -> condition('freq_id', $freq_id, '=')
          ->execute();
        }
      }
    }
  }
	//********SURAJ************
	drupal_set_message('Frequency '.$form_state['values']['name'].' has been created.','status');
	//sending system alert
	global $user;
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'Frequency '.$form_state['values']['name'].' has been created.',
		'priority' => 'L',
		'module' => 'fee',
		'source_url' => 'admin/fees/fee_structure/set_frequency',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	
}