<?php
/**
 *Implements page callback function - incentive
 */
function incentive($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$emp_table = 'essa_'.$session_id.'_master_staff_table';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$emp_sal_table = 'essa_'.$session_id.'_pr_emp_sal';
	$batch_increment_table = 'essa_'.$session_id.'_pr_batch_increment';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	
	$form = array();
	
	$form['emp_id'] = array(
		'#type' => 'textfield',
		'#title' => 'Emp ID',
		'#autocomplete_path' => 'staff/autocomplete',
		'#size' => 35,
		'#required' => TRUE,
	);
	
	$form['particular'] = array(
		'#type' => 'textfield',
		'#title' => t('Particular'),
		'#required' => TRUE,
	);
	
	$form['desc'] = array(
		'#type' => 'textarea',
		'#title' => t('Description'),
	);
	
	$form['amount'] = array(
		'#type' => 'textfield',
		'#title' => t('Amount'),
		'#size' => 10,
		'#required' => TRUE,
	);
	
	$basic_info = db_query("
    SELECT * from {$basic_info_table};"
  );
	foreach($basic_info as $info){
		$fin_yr_st = $info->financialyearstart;
		$fin_yr_ed = $info->financialyearend;
	}
	
	$start    = (new DateTime($fin_yr_st))->modify('first day of this month');
	$end      = (new DateTime($fin_yr_ed))->modify('first day of next month');
	$interval = DateInterval::createFromDateString('1 month');
	$period   = new DatePeriod($start, $interval, $end);

	foreach ($period as $dt) {
	  $options[] = $dt->format("M, Y");
	}
	
	$form['months'] = array(
		'#type' => 'checkboxes',
		'#options' => drupal_map_assoc($options),
		'#title' => 'Select months',
		'#required' => TRUE,
		//'#description' => 'If no month is selected, this incentive will be allotted for current month.'
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	return $form;
}

/**
 *Implements page callback function - incentive
 */
function incentive_validate($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$emp_table = 'essa_'.$session_id.'_master_staff_table';
	
	$employee = db_query("
		SELECT * from {$emp_table} where status = 1;"
	);
	foreach($employee as $emp){
		$emp_ids[] = $emp->emp_id;
	}
	
	preg_match("/\(([^\)]*)\)/", $form_state['values']['emp_id'], $output);
	if(!isset($output[1])){
		$output[1] = $form_state['values']['emp_id'];
	}
	if(!in_array($output[1], $emp_ids)){
		form_set_error('emp_id', 'Select a valid employee from the list.');
	}
	
	if(!is_numeric($form_state['values']['amount'])){
		form_set_error('amount', 'Amount must be numeric.');
	}
}
/**
 *Implements page callback function - incentive
 */
function incentive_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$incentive_table = 'essa_'.$session.'_pr_incentive';
	
	preg_match("/\(([^\)]*)\)/", $form_state['values']['emp_id'], $output);
	foreach($form_state['values']['months'] as $mon => $val){
		if($val != '0'){
			db_insert($incentive_table)
				->fields (array(
					'particular' => $form_state['values']['particular'],
					'incentive_desc' => $form_state['values']['desc'],
					'emp_id' => $output[1],
					'month' => $val,
					'amount' => $form_state['values']['amount'],
				)
			)	
			->execute();
		}
	}
	
	drupal_set_message('Incentive was awarded successfully!!!','status');
}