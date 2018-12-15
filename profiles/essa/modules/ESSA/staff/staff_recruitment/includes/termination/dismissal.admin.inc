<?php
/**
 *Implements page callback function - expulsion_form
 */
function dismissal_form($form = array(), &$form_state){
	$form['emp_id'] = array(
		'#type' => 'textfield',
    '#title' => 'Emp ID',
    '#autocomplete_path' => 'emp_id/autocomplete',
		'#id' => 'emp_id',
		'#required' => TRUE,
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'staff_detail_ajax',
      'wrapper' => 'staff_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#size' => 15,
		'#prefix' => '<p style = "width: 50%;"></p>',
	);
	
	$form['staff_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "staff_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['line break'] = array(
		'#type' => 'markup',
		'#markup' => '<p><br><br><br></p>',
	);
	
	$form['wef'] = array(
		'#title' => 'With Effect From',
	  '#type' => 'date_popup',
		'#attributes' => array('placeholder' => 'dd-mm-yy'),
		'#date_format' => 'd-m-Y',
	  '#date_year_range' => '-30:0',
	  '#required' => TRUE,
	);
	
	$form['reason'] = array(
		'#type' => 'textarea',
		'#title' => t('Reason'),
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	
	return $form;
}

/**
 *Implements submit function
 */
function dismissal_form_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	$staff_resignation_table = 'essa_'.$session_id.'_staff_resignation';
	
	global $user;
	$prid = NULL;
	$principal = FALSE;
	$principal_role = db_query(
		"SELECT * from role where name = 'Principal';"
	);
	foreach($principal_role as $pr){
		$prid = $pr->rid;
	}
	
	$user_role = db_query(
		"SELECT * from users_roles where uid = :uid and rid = :rid;", array(':uid' => $user->uid, ':rid' => $prid)
	);
	foreach($user_role as $ur){
		$principal = TRUE;
	}
	
	if($principal == TRUE){
		$staff_info = db_query(
			"SELECT * from $staff_table where emp_id = :emp_id;", array(':emp_id' => $form_state['values']['emp_id'])
		);
		foreach($staff_info as $si){
			$uid = $si->uid;
		}
		
		db_update('users')
			->fields (array(
				'status' => 0,
				))
			->condition('name', $form_state['values']['emp_id'], '=')
			->execute();
		
		db_update($staff_table)
			->fields (array(
				'status' => 0,
				))
			->condition('emp_id', $form_state['values']['emp_id'], '=')
			->execute();
		
		$date = date('d-m-Y h:i:s');
		$timestamp = strtotime($date);
		global $user;
		
		db_insert($staff_resignation_table)
			->fields (array(
			  'emp_id' => $form_state['values']['emp_id'],
				'type' => 'dismissal',
				'reason' => $form_state['values']['reason'],
				'status_fin' => NULL,
				'status_fin_reason' => NULL,
				'fin_timestamp' => NULL,
				'fin_uid' => NULL,
				'status' => 'blocked',
				'status_reason' => $form_state['values']['reason'],
				'status_timestamp' => $timestamp,
				'status_uid' => $user->uid,
			)
		)	
		->execute();
	}else{
		$date = date('d-m-Y h:i:s');
		$timestamp = strtotime($date);
		global $user;
		db_insert($staff_resignation_table)
			->fields (array(
			  'emp_id' => $form_state['values']['emp_id'],
				'type' => 'dismissal',
				'reason' => $form_state['values']['reason'],
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
/**
 *Implements ajax callback
 */
function staff_detail_ajax($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	
	$staff_info = db_query(
		"SELECT * from $staff_table where emp_id = :emp_id;", array(':emp_id' => $form_state['values']['emp_id'])
	);
	foreach($staff_info as $si){
		$name = $si->fname.' '.$si->lname;
		$type = $si->type;
		$doj = $si->joining_date;
 	}
	
	if(isset($name)){
		$form['fs'] = array(
			'#type' => 'markup',
			'#markup' => '<p style = "float:left; width: 90px;">Name: </p><h4><b>'.$name.'</b></h4><p style = "float:left;width: 90px;"> Type: </p><h4><b>'.$type.'</b></h4><p style = "float:left; width: 90px;">Joining Date: <h4><b>'.$doj.'</b></h4>',
			'#prefix' => '<div id = "staff_wrapper">',
			'#suffix' => '</div>',
			'#validated' => TRUE,
		);	
	}else{
		$form['fs'] = array(
			'#type' => 'markup',
			'#markup' => '<h4 style = "float:left; width: 200px; color: RED">Please enter a valid employee ID.</h4>',
			'#prefix' => '<div id = "staff_wrapper">',
			'#suffix' => '</div>',
			'#validated' => TRUE,
		);	
	}
	
	return $form['fs'];
}