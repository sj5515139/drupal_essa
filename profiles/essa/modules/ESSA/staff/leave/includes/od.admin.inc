<?php

/**
 *Implements page callback od_form
 */
function od_form($form, &$form_state){
  $form = array();
  
  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => 'Leave ID',
    '#default_value' => t('OD'),
  );
  
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Leave Name',
    '#default_value' => t('On Duty'),
  );
  
  $form['desc'] = array(
    '#type' => 'textarea',
    '#title' => t('Leave Description'),
    '#default_value' => t('This is a special leave type. It will not be considered as Leave, the employee who applies for OD shall get prior approval from concerned authority.'),
  );
	
	$form['half_day'] = array(
		'#type' => 'radios',
		'#title' => 'Half-Day',
		'#descrition' => 'Can staffs take half-day leave along this leave type',
		'#options' => drupal_map_assoc(array('Yes', 'No')),
		'#default_value' => 'Yes',
	);
	
	$form['half_day_rule'] = array(
		'#type' => 'textfield',
		'#title' => '<h3> half-day = 1 full day.</h3>',
		'#size' => 1,
		'#default_value' => 2,
		'#states' => array(
			'visible' => array(
			  ':input[name = "half_day"]' => array('value' => 'Yes'),
			),
		),
  );
  
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}

/**
 *Implements submit function
 */
function od_form_submit($form, &$form_state){
  $session = variable_get('essa_sid');
	$leave_table = 'essa_'.$session.'_leave_types';
  
  db_merge($leave_table)
    ->key(array('leave_id' => $form_state['values']['id']))
    ->fields (array(
      'leave_id' => $form_state['values']['id'],
      'leave_name' => $form_state['values']['name'],
      'leave_desc' => $form_state['values']['desc'],
    )
  )
  ->execute();
}