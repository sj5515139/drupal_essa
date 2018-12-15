<?php
/**
 *Implements page callback function - create_concession
 */
function create_concession($form = array(), &$form_state){
  
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Name',
    '#required' => TRUE,
		'#description' => 'Name of the concession must be unique.'
  );
  
  $session_id = (string)variable_get('essa_sid');
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees = db_query("
    SELECT * from {$fees_table};
  ");
	$options = array();
  foreach($fees as $fee){
    $options[] = $fee->particulars;
  }
  //**********SURAJ************
	global $base_url;
	$url = $base_url.'#overlay=admin/fees/fee_structure/create_fees';
	if($options == NULL){
		drupal_set_message('No fees has been created. Please create fees, <a href = "'.$url.'">here</a>.', 'warning');
	}
  //**********SURAJ************
  
  $form['fee'] = array(
    '#type' => 'select',
    '#title' => 'On Fee',
    '#options' => drupal_map_assoc($options),
    '#required' => TRUE,
  );
	
	$form['amount'] = array(
		'#type' => 'textfield',
		'#title' => 'Amount',
		'#size' => 10,
	);
	
	$form['percent'] = array(
		'#type' => 'textfield',
		'#title' => 'Percent',
		'#size' => 10,
	);
  
  $form['desc'] = array(
    '#type' => 'textarea',
    '#title' => 'Description',
  );
  
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Create'),
  );
  return $form;
}

/**
 *Implements validate function
 */
function create_concession_validate($form, &$form_state){
	
	if($form_state['values']['amount'] == NULL && $form_state['values']['percent'] == NULL){
		form_set_error('amount' , 'Both amount and percent can\'t be empty.');
	}
	
	if($form_state['values']['amount'] != NULL){
		if(!is_numeric($form_state['values']['amount'])){
			form_set_error('amount' , 'Amount must be numeric.');
		}elseif($form_state['values']['amount'] <= 0){
			form_set_error('amount' , 'Amount can\'t be less than or equal to zero.');
		}
	}
	
	if($form_state['values']['amount'] != NULL && $form_state['values']['percent'] != NULL){
		form_set_error('amount' , 'Both amount and percent can\'t be alloted. You need to select any one.');
	}
	
	$session_id = (string)variable_get('essa_sid');
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees = db_query("
    SELECT * from {$fees_table} where particulars = :p;", array(':p' => $form_state['values']['fee'])
  );
	foreach($fees as $fee){
		if($form_state['values']['amount'] > $fee->amount){
			form_set_error('amount','Concession amount can\'t be more than the fee amount.');
		}
	}
	
	if($form_state['values']['percent'] > 100){
		form_set_error('percent','Percent can\'t be greater than 100% in this case.');
	}
	
	if($form_state['values']['amount'] == NULL){
		if(!is_numeric($form_state['values']['percent'])){
			form_set_error('percent' , 'Percent must be numeric.');
		}
		if($form_state['values']['percent'] <= 0){
			form_set_error('percent','Percent can\'t be 0% or less.');
		}
	}
	
	$con_name = array();
	$session = (string)variable_get('essa_sid');
	$concession_table = 'essa_'.$session.'_fees_concession';
	$concession = db_query("
		SELECT * from {$concession_table};"
	);
	foreach($concession as $con){
		$con_name[] = $con->name;
	}
	
	if(in_array($form_state['values']['name'], $con_name)){
		form_set_error('name','Name must be unique.');
	}
}

/**
 *Implements submit function
 */
function create_concession_submit($form, &$form_state){
  $con_id = NULL;
  $session = (string)variable_get('essa_sid');
	$concession_table = 'essa_'.$session.'_fees_concession';
  $fees_table = 'essa_'.$session.'_fees_structure';
  $fees = db_query("
		SELECT * from {$fees_table} where particulars = :p;", array(':p' => $form_state['values']['fee'])
	);
  foreach($fees as $fee){
    $fee_id = $fee->fee_id;
		db_insert($concession_table)
			->fields (array(
				'name' => $form_state['values']['name'],
				'fee_id' => $fee_id,
				'amount' => $form_state['values']['amount']?$form_state['values']['amount']:NULL,
				'percent' => $form_state['values']['percent']?$form_state['values']['percent']:NULL,
				'concession_desc' => $form_state['values']['desc'],
			)
		)	
		->execute();
  }
	
	drupal_set_message($form_state['values']['name'].' as concession has been created.');
	//***********SURAJ*************
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	global $user;
	//sending system alert
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => $form_state['values']['name'].' as concession has been created.',
		'priority' => 'M',
		'module' => 'fee',
		'source_url' => 'admin/fees/concession/create-concession',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	
}
