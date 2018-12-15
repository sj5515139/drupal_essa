<?php
/**
 *Implements page callback function - salary_head
 */
function salary_head($form, &$form_state, $sal_id){
	$form['sal_id'] = array(
		'#type' => 'value',
		'#value' => $sal_id,
	);
	
	$form['particular'] = array(
		'#type' => 'textfield',
		'#title' => 'Particulars',
		'#required' => TRUE,
	);
	
	$form['abb'] = array(
		'#type' => 'textfield',
		'#title' => 'Abbreviation',
		'#description' => 'This must be Unique.',
		'#required' => TRUE,
		'#size' => 10,
	);
	
	$form['dependent'] = array(
		'#type' => 'checkbox',
		'#title' => 'Is dependent on?',
	);
	
	$options = array();
	
	$session_id = (string)variable_get('essa_sid');
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$salary_head = db_query("
    SELECT * from {$sal_detail_table} where is_dependent_on = 0;
  ");
	
  foreach($salary_head as $sh){
		$options[] = $sh->sal_head;
	}
	$form['dependent_on'] = array(
		'#type' => 'select',
		'#options' => drupal_map_assoc($options),
		'#title' => 'Depends on',
		'#states' => array(
			'visible' => array(
			  ':input[name = "dependent"]' => array('checked' => TRUE),
			),
			'invisible' => array(
			  ':input[name = "dependent"]' => array('checked' => FALSE),
			),
		),
	);
	
	$form['amount'] = array(
		'#type' => 'textfield',
		'#title' => 'Amount',
		'#states' => array(
			'visible' => array(
			  ':input[name = "dependent"]' => array('checked' => FALSE),
			),
			'invisible' => array(
			  ':input[name = "dependent"]' => array('checked' => TRUE),
			),
		),
		'#size' => 10,
	);
	
	$form['percent'] = array(
		'#type' => 'textfield',
		'#title' => 'Percent',
		'#states' => array(
			'visible' => array(
			  ':input[name = "dependent"]' => array('checked' => TRUE),
			),
			'invisible' => array(
			  ':input[name = "dependent"]' => array('checked' => FALSE),
			),
		),
		'#default_value' => NULL,
		'#size' => 10,
	);
	
	$form['deduction'] = array(
		'#type' => 'checkbox',
		'#title' => 'Is Deduction',
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	return $form;
}

/**
 *Implements validate function
 */
function salary_head_validate($form, &$form_state){
	if($form_state['values']['dependent'] == 1 && $form_state['values']['percent'] == NULL){
		form_set_error('percent','Percent can\'t be blank.');
	}elseif($form_state['values']['dependent'] == 0 && $form_state['values']['amount'] == NULL){
		form_set_error('amount','Amount can\'t be blank.');
	}
	
	$session_id = (string)variable_get('essa_sid');
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$salary_head = db_query("
	  SELECT * from {$sal_detail_table} where sal_id = :si and sal_head = :sh;", array(':sh' => $form_state['values']['dependent_on'], ':si' => $form_state['values']['sal_id'])
	);
	
	$key = array();
	foreach($salary_head as $sh){
		$key[] = $sh->sal_head;
	}
	
	if(in_array($form_state['values']['abb'], $key)){
		form_set_error('abb','Abbreviation must be unique.');
	}
	
	if($form_state['values']['amount'] < 0){
		form_set_error('amount', 'Amount can\'t be negative.');
	}
	
	if($form_state['values']['percent'] < 0){
		form_set_error('amount', 'Percents can\'t be negative.');
	}
}
/**
 *Implements submit function
 */
function salary_head_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$table = 'essa_'.$session.'_'.'pr_salary_detail';
	
	if($form_state['values']['dependent'] == 0){
		db_insert($table)
			->fields (array(
				'sal_id' => $form_state['values']['sal_id'],
				'sal_head' => $form_state['values']['abb'],
				'particular' => $form_state['values']['particular'],
				'is_dependent_on' => $form_state['values']['dependent'],
				'amount' => $form_state['values']['amount'],
				'is_deduction' => $form_state['values']['deduction'],
			)
		)	
		->execute();	
	}else{
		$session_id = (string)variable_get('essa_sid');
		$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
		$salary_head = db_query("
		  SELECT * from {$sal_detail_table} where sal_head = :sh and sal_id = :si;", array(':sh' => $form_state['values']['dependent_on'], ':si' => $form_state['values']['sal_id'])
		);
		
		foreach($salary_head as $sh){
			$amount = $sh->amount;
		}
		
		$this_amount = ($form_state['values']['percent']/100)*$amount;
	
		db_insert($table)
			->fields (array(
				'sal_id' => $form_state['values']['sal_id'],
				'sal_head' => $form_state['values']['abb'],
				'particular' => $form_state['values']['particular'],
				'is_dependent_on' => $form_state['values']['dependent'],
				'depends_on' => $form_state['values']['dependent_on'],
				'amount' => $this_amount,
				'percent' => $form_state['values']['percent'],
				'is_deduction' => $form_state['values']['deduction'],
			)
		)	
		->execute();	
	}
	menu_rebuild();
	drupal_cron_run();
	drupal_set_message('The salary head was created successfully','status');
}