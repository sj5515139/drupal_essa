<?php
/**
 *Implements page callback function - edit_salary_head
 */
function edit_salary_head($form, &$form_state, $sal_id, $sal_head){
	$session_id = (string)variable_get('essa_sid');
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	
	$salary_head = db_query("
		SELECT * from {$sal_detail_table} where sal_id = :sal_id and sal_head = :sh;", array(':sal_id' => $sal_id, ':sh' => $sal_head)
	);
	foreach($salary_head as $sh){
		$particular = $sh->particular;
		$is_dependent_on = $sh->is_dependent_on;
		$depends_on = $sh->depends_on;
		$amount = $sh->amount;
		$percent = $sh->percent;
		$is_deduction = $sh->is_deduction;
	}
	
	$form['sal_id'] = array(
		'#type' => 'value',
		'#value' => $sal_id,
	);
	
	$form['sal_head'] = array(
		'#type' => 'value',
		'#value' => $sal_head,
	);
	
	$form['particular'] = array(
		'#type' => 'textfield',
		'#title' => 'Particulars',
		'#required' => TRUE,
		'#default_value' => isset($particular)? $particular: NULL,
	);
	
	$form['abb'] = array(
		'#type' => 'textfield',
		'#title' => 'Abbreviation',
		'#description' => 'This must be Unique.',
		'#disabled' => TRUE,
		'#required' => TRUE,
		'#default_value' => isset($sal_head)? $sal_head: NULL,
		'#size' => 10,
	);
	
	$form['dependent'] = array(
		'#type' => 'checkbox',
		'#title' => 'Is dependent on?',
		'#default_value' => isset($is_dependent_on)? $is_dependent_on: NULL,
	);
	
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
		'#default_value' => isset($depends_on)? $depends_on: NULL,
	);
	
	$form['amount'] = array(
		'#type' => 'textfield',
		'#title' => 'Amount',
		'#default_value' => isset($amount)? $amount: NULL,
		'#size' => 10,
		'#states' => array(
			'visible' => array(
			  ':input[name = "dependent"]' => array('checked' => FALSE),
			),
			'invisible' => array(
			  ':input[name = "dependent"]' => array('checked' => TRUE),
			),
		),
	);
	
	$form['percent'] = array(
		'#type' => 'textfield',
		'#title' => 'Percent',
		'#default_value' => isset($percent)? $percent: NULL,
		'#size' => 10,
		'#states' => array(
			'visible' => array(
			  ':input[name = "dependent"]' => array('checked' => TRUE),
			),
			'invisible' => array(
			  ':input[name = "dependent"]' => array('checked' => FALSE),
			),
		),
	);
	
	$form['deduction'] = array(
		'#type' => 'checkbox',
		'#title' => 'Is Deduction',
		'#default_value' => isset($is_deduction)? $is_deduction: NULL,
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
function edit_salary_head_validate($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	
	$salary_head = db_query("
		SELECT * from {$sal_detail_table} where sal_id = :sal_id and sal_head = :sh;", array(':sal_id' => $form_state['values']['sal_id'], ':sh' => $form_state['values']['sal_head'])
	);
	foreach($salary_head as $sh){
		$particular = $sh->particular;
		$is_dependent_on = $sh->is_dependent_on;
		$depends_on = $sh->depends_on;
		$amount = $sh->amount;
		$percent = $sh->percent;
		$is_deduction = $sh->is_deduction;
	}
	
	if($form_state['values']['amount'] < 0){
		form_set_error('amount', 'Amount can\'t be negative.');
	}
	
	if($form_state['values']['percent'] < 0){
		form_set_error('amount', 'Percents can\'t be negative.');
	}
	
	if($form_state['values']['dependent'] == 1){
		if($form_state['values']['amount'] != $amount && $form_state['values']['percent'] != $percent){
			form_set_error('amount', 'You can\'t edit both percent and amount. You enter either one, the other is calculated automatically.');
		}
		if($form_state['values']['dependent_on'] == $form_state['values']['sal_head']){
			form_set_error('dependent_on', 'The salary can\'t depend on itself. Please choose the dependent category carefully.');
		}
	}
	
	if($form_state['values']['dependent'] == 1 && $form_state['values']['percent'] == NULL){
		form_set_error('percent','Percent can\'t be blank.');
	}elseif($form_state['values']['dependent'] == 0 && $form_state['values']['amount'] == NULL){
		form_set_error('amount','Amount can\'t be blank.');
	}
}

/**
 *Implements submit function
 */
function edit_salary_head_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$table = 'essa_'.$session.'_'.'pr_salary_detail';
	
	if($form_state['values']['dependent'] == 0){
		db_update($table)
			->condition(db_and()
					->condition('sal_id', $form_state['values']['sal_id'])
					->condition('sal_head', $form_state['values']['sal_head'])
				)
			->fields (array(
				'particular' => $form_state['values']['particular'],
				'is_dependent_on' => $form_state['values']['dependent'],
				'amount' => $form_state['values']['amount'],
				'is_deduction' => $form_state['values']['deduction'],
			)
		)	
		->execute();
		
		$session_id = (string)variable_get('essa_sid');
		$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
		
		$dependent_head = db_query("
			SELECT * from {$sal_detail_table} where sal_id = :sal_id;", array(':sal_id' => $form_state['values']['sal_id'])
		);
		foreach($dependent_head as $dh){
			if($dh->depends_on == $form_state['values']['sal_head']){
				$new_amt = ($dh->percent/100)*$form_state['values']['amount'];
				//dsm($new_amt);
				db_update($table)
					->condition(db_and()
						->condition('sal_id', $form_state['values']['sal_id'])
						->condition('sal_head', $dh->sal_head)
					)
					->fields (array(
						'amount' => $new_amt,
					)
				)	
				->execute();
			}	
		}
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
		
		db_update($table)
			->condition(db_and()
				->condition('sal_id', $form_state['values']['sal_id'])
				->condition('sal_head', $form_state['values']['sal_head'])
			)
			->fields (array(
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
	
	drupal_cron_run();
	drupal_set_message('The salary head was created successfully','status');
}