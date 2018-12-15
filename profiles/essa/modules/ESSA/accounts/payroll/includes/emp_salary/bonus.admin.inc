<?php

/**
 *Implments page callback function - bonus
 */
function bonus($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$emp_table = 'essa_'.$session_id.'_master_staff_table';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$emp_sal_table = 'essa_'.$session_id.'_pr_emp_sal';
	$batch_increment_table = 'essa_'.$session_id.'_pr_batch_increment';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	
	$form = array();
	
	$sal_type = db_query("
		SELECT * from {$sal_table};"
	);	
	foreach($sal_type as $st){
		$sal_options[] = $st->title;
	}
	
	$form['sal_cat'] = array(
		'#type' => 'select',
		'#title' => 'Salary Category',
		'#options' => drupal_map_assoc($sal_options),
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
		//'#description' => 'If no month is selected, this deductions will be allotted for current month.'
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	return $form;
}

/**
 *Implements page callback function - deductions
 */
function bonus_validate($form, &$form_state){
	if(!is_numeric($form_state['values']['amount'])){
		form_set_error('amount', 'Amount must be numeric.');
	}
}

/**
 *Implements page callback function - deductions
 */
function bonus_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$session = variable_get('essa_sid');
	$bonus_table = 'essa_'.$session.'_pr_bonus';
	$emp_table = 'essa_'.$session_id.'_master_staff_table';
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$sal_id = 0;
	
	$sal_type = db_query("
		SELECT * from {$sal_table} where title = :title;", array(':title' => $form_state['values']['sal_cat'])
	);	
	foreach($sal_type as $st){
		$sal_id = $st->sal_id;
	}
	foreach($form_state['values']['months'] as $mon => $val){
		if($val != '0'){
			if($sal_id != 0){
				db_insert($bonus_table)
				->fields (array(
						'particular' => $form_state['values']['particular'],
						'month' => $val,
						'sal_id' => $sal_id,
						'amount' => $form_state['values']['amount'],
					)
				)	
				->execute();
			}
		}
	}
	drupal_set_message('Bonus was implemented successfully!!!','status');
}