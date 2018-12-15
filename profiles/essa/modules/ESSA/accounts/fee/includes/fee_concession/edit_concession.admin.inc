<?php
/**
 *Implements page callback function edit_con_form
 */
function edit_con_form($form = array(), &$form_state, $con_id){
  $session = (string)variable_get('essa_sid');
	$concession_table = 'essa_'.$session.'_fees_concession';
  $fees_table = 'essa_'.$session.'_fees_structure';
  
  $form['con_id'] = array(
    '#type' => 'value',
    '#value' => $con_id,
  );
  
	$concession = db_query("
    SELECT * from {$concession_table} where con_id = :ci;", array(':ci' => $con_id)
  );
  foreach($concession as $con){
    $name = $con->name;
    $fees = db_query("
    	SELECT * from {$fees_table} where fee_id = :fi;", array(':fi' => $con->fee_id)
    );
    foreach($fees as $fee){
      $particular = $fee->particulars;
    }
    $amount = $con->amount;
    $percent = $con->percent;
    $desc = $con->concession_desc;
  }
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Name',
    '#default_value' => isset($name)?$name:NULL,
    '#required' => TRUE,
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
  $form['fee'] = array(
    '#type' => 'select',
    '#title' => 'On Fee',
    '#default_value' => isset($particular)?$particular:NULL,
    '#options' => drupal_map_assoc($options),
    '#required' => TRUE,
  );
	
	$form['amount'] = array(
		'#type' => 'textfield',
		'#title' => 'Amount',
    '#default_value' => isset($amount)?$amount:NULL,
		'#size' => 10,
	);
	
	$form['percent'] = array(
		'#type' => 'textfield',
		'#title' => 'Percent',
    '#default_value' => isset($percent)?$percent:NULL,
		'#size' => 10,
	);
  
  $form['desc'] = array(
    '#type' => 'textarea',
    '#title' => 'Description',
    '#default_value' => isset($desc)?$desc:NULL,
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
function edit_con_form_validate($form, &$form_state){
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
}

/**
 *Implements submit function
 */
function edit_con_form_submit($form, &$form_state){
  $con_id = NULL;
  $session = (string)variable_get('essa_sid');
	$concession_table = 'essa_'.$session.'_fees_concession';
  
	$fees_table = 'essa_'.$session.'_fees_structure';
  $fees = db_query("
		SELECT * from {$fees_table} where particulars = :p;", array(':p' => $form_state['values']['fee'])
	);
  foreach($fees as $fee){
    $fee_id = $fee->fee_id;
  }
	
	db_merge($concession_table)
		->key(array('con_id' => $form_state['values']['con_id']))
		->fields (array(
			'name' => $form_state['values']['name'],
			'fee_id' => $fee_id,
			'amount' => $form_state['values']['amount']?$form_state['values']['amount']:NULL,
			'percent' => $form_state['values']['percent']?$form_state['values']['percent']:NULL,
			'concession_desc' => $form_state['values']['desc'],
		)
	)	
	->execute();
	
	drupal_set_message('The changes were made successfully!!!');
}