<?php
/**
 *Implements page callback - collection_staff
 */
function collection_staff($form = array(), &$form_state){
  
  $form['fs'] = array(
    '#type' => 'fieldset',
  );
  
  $form['fs']['emp_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Emp ID'),
    '#required' => TRUE,
  );
  
  $form['fs']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
  );
  
  $form['fs']['phone_no'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone No.'),
  );
  
  $form['fs']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email ID'),
  );
  
  $form['fs']['username'] = array(
    '#type' => 'textfield',
    '#title' => t('User Name'),
    '#required' => TRUE,
  );
  
  $form['fs']['confirm_password'] = array(
    '#type' => 'password_confirm',
    //'#title' => t('Confirm Password'),
    '#required' => TRUE,
  );
  
  $form['fs']['save'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
	
  return $form;
}

/**
 *Implements validate function.
 */
function collection_staff_validate($form, &$form_state){
  $session_id = (string)variable_get('essa_sid');
  $fee_staffs_table = 'essa_'.$session_id.'_fees_staff';
  
  $emp_id_check = NULL;
  $fees_staff = db_query("
    SELECT * from {$fee_staffs_table} where emp_id = :ei and type = 'Fees Collector';", array('ei' => $form_state['values']['emp_id'])
  );
	foreach($fees_staff as $fs){
    $emp_id_check = $fs->emp_id;
  }
  
  //Fees Collector
  
  if($emp_id_check != NULL){
    form_set_error('emp_id', 'This employee is already a Collection Staff');
  }
}

/**
 *Implements submit function.
 */
function collection_staff_submit($form, &$form_state){
  $session_id = (string)variable_get('essa_sid');
  $fee_staffs_table = 'essa_'.$session_id.'_fees_staff';
  
  $collector_role = db_query("
    SELECT * from role where name = 'Fees Collector';"
  );
	foreach($collector_role as $cr){
    $crid = $cr->rid;
  }
  
	$collection_staff = array(
		'name' => $form_state['values']['username'],
	  'pass' => $form_state['values']['confirm_password'],
	  'mail' => $form_state['values']['email'],
		'init' => $form_state['values']['email'], 
	  'status' => 1, 
	  'access' => REQUEST_TIME,
		'roles' => array($crid => 'Fees Collector'),
	);
	user_save('', $collection_staff);
  
  $uid = db_query("select * from users where name = :user", array(':user' => $form_state['values']['username']));
	foreach($uid as $cuid){
		$cs_uid = $cuid -> uid;
	}
  
  db_insert($fee_staffs_table)
		->fields (array(
			'uid' => $cs_uid,
			'emp_id' => $form_state['values']['emp_id'],
      'type' => 'Fees Collector',
			'name' => $form_state['values']['name'],
			'phone_no' => $form_state['values']['phone_no'],
      'email_id' => $form_state['values']['email'],
      'username' => $form_state['values']['username'],
		)
	)	
	->execute();
	
	drupal_set_message('A user has been created & permissions for collecting fees has been successfully allotted.','status');
}