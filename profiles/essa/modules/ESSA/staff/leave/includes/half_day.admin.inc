<?php
 
/**
 *Implements page callback - leave_page.
 */
function half_day_form($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leave_types = array();
	$query = db_query("Select * FROM {$leave_table}");
	foreach($query as $q){
		$leave_types[] = $q->leave_id;
	}
	$form['leave'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select Leave Types'),
    '#required' => TRUE,
    '#options' => drupal_map_assoc($leave_types),
  );
	
	$form['msg1'] = array(
		'#type' => 'markup',
		'#markup' => '<h3>Rule for Teaching Staff</h3>',
  );
	
	$form['half_day_rule_teaching'] = array(
		'#type' => 'textfield',
		'#title' => '<h3> half-day = 1 full day.</h3>',
		'#size' => 1,
		'#default_value' => 2,
  );
	
	$form['msg2'] = array(
		'#type' => 'markup',
		'#markup' => '<h3>Rule for Admin Staff</h3>',
  );
	
	$form['half_day_rule_admin'] = array(
		'#type' => 'textfield',
		'#title' => '<h3> half-day = 1 full day.</h3>',
		'#size' => 1,
		'#default_value' => 3,
  );
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
  );
	
	return $form;
}

/**
 *Implements page callback - half_day_form_submit.
 */
function half_day_form_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	$leave_half_day = 'essa_'.$session_id.'_leave_half_day';
	
	foreach($form_state['values']['leave'] as $l){
		if($l != '0'){
			variable_set('half_day_rule_teaching_'.$l, $form_state['values']['half_day_rule_teaching']);
			variable_set('half_day_rule_admin_'.$l, $form_state['values']['half_day_rule_admin']);
			
			$query = db_query("SELECT * from $staff_master_table where status = 1");
			foreach($query as $q){
				db_merge($leave_half_day)
				->key(array('leave_id' => $l, 'emp_id' => $q->emp_id))
				->fields(array(
					'leave_id' => $l,
					'emp_id' => $q->emp_id,
				))
				->execute();
			}
			
		}
	}

	drupal_set_message('Half day rule is created successfully.', 'status');
}