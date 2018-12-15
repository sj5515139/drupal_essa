<?php

/**
 *Implements page callback od_form
 */
function leave_form($form, &$form_state){
  $form = array();
  
  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => 'Leave ID',
		'#description' => 'This must be unique.',
		'#required' => TRUE,
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'unique_id_ajax',
      'wrapper' => 'ui_error',
      'method' => 'append',
      'effect' => 'fade',
    ),
  );
	
	$form['ef']['t']['error'] = array(
		'#type' => 'container',
    '#prefix' => '<div id = "ui_error">',
    '#suffix' => '</div>',
	);
	
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Leave Name',
  );
	
	$form['nod_year'] = array(
    '#type' => 'textfield',
    '#title' => t('No. of days(per year)'),
		'#required' => TRUE,
  );
  
  $form['desc'] = array(
    '#type' => 'textarea',
    '#title' => t('Leave Description'),
    '#resizable' => FALSE,
  );
  
  $form['max_month'] = array(
    '#type' => 'textfield',
    '#title' => t('Max in a month'),
		'#description' => 'This sets a threshold for maximum no. of leave a staff can take in one month.(Leave it blank, if not required.)'
  );
	
	$form['at_a_stretch'] = array(
    '#type' => 'textfield',
    '#title' => t('Min at a stretch'),
		'#description' => 'This sets a threshold for minimum no. of leave a staff shall take at a stretch.(Leave it blank, if not required.)'
  );
	
	$form['half_day_rule'] = array(
		'#type' => 'textfield',
		'#title' => '<h3> half-day = 1 full day.</h3>',
		'#size' => 1,
		'#default_value' => 2,
	);
	
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}

function unique_id_ajax($form, &$form_state){
	//$nns = $form['staff_nn']['#values'];
	$ui = array();
	
	$session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leaves = db_query(
    "SELECT * from {$leave_table};"
	);
  
  foreach($leaves as $leave){
		$ui[] = $leave->leave_id;
	}
	
	$flag = 0;
	foreach($ui as $id){
		if(strtolower($form_state['values']['id']) == strtolower($id)){
			$flag = 1;	
		}	
	}
	if($flag == 1){
		drupal_set_message(t('This ID - <span style = "font-size: 20px; font-weight: 400; color: RED;"><strong>"'.$form_state['values']['id'].'"</strong></span> is already present. Please change the ID.'), 'error');
		return '';
	}{
		//drupal_set_message(t('Great! We are good to go.'), 'status');
		return '';
	}
}

/**
 *Implements submit function
 */
function leave_form_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$leave_table = 'essa_'.$session.'_leave_types';
	$leave_staff_table = 'essa_'.$session.'_leave_staff';
	
  db_merge($leave_table)
    ->key(array('leave_id' => $form_state['values']['id']))
    ->fields (array(
      'leave_id' => $form_state['values']['id'],
      'leave_name' => $form_state['values']['name'],
      'leave_desc' => $form_state['values']['desc'],
      'max_per_month' => (int)$form_state['values']['max_month'],
			'min_stretch' => (int)$form_state['values']['at_a_stretch'],
      'nod_per_year' => (int)$form_state['values']['nod_year'],
			'half_day_rule' => (int)$form_state['values']['half_day_rule'],
    )
  )
  ->execute();
	
	//*******Suraj********//
	drupal_set_message('Leave type '.$form_state['values']['name'].' - '.$form_state['values']['id'].' was created successfully!!!');	
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	global $user;
	//sending system alert
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'Leave type '.$form_state['values']['name'].' - '.$form_state['values']['id'].' was created successfully.',
		'priority' => 'M',
		'module' => 'Leave',
		'source_url' => 'admin/staff/leave/settings/create_leave_type',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	//*******Suraj********//
	drupal_cron_run();
	menu_rebuild();
	
	
	$staffs = db_query("SELECT * FROM {$leave_staff_table}");
	foreach($staffs as $staff){
		db_merge($leave_staff_table)
		->key(array('emp_id' =>$staff->emp_id, 'leave_id' => $form_state['values']['id']))
		->fields(array(
		'max_per_month' => (int)$form_state['values']['max_month'],
		'min_stretch' => (int)$form_state['values']['at_a_stretch'],
		))
		->execute();
	}
}