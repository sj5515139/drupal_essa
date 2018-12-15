<?php

/**
 *Implements pagecallback function - tnc
 */
function tnc($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$tnc_table = 'essa_'.$session_id.'_pr_tnc';
	
	$tnc = db_query("
    SELECT * from {$tnc_table};"
  );
	foreach($tnc as $t){
		if($t->title == 'Loan'){
			$loan = $t->body;	
		}else{
			$advance = $t->body;
		}
	}
	
	$form['loan'] = array(
		'#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('T&C (Loan)'),
		'#default_value' => $loan,
		'#rows' => 10,
	);
	
	$form['advance'] = array(
		'#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => 'T&C (Advance)',
		'#default_value' => $advance,
		'#rows' => 10,
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
function tnc_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$tnc_table = 'essa_'.$session_id.'_pr_tnc';
	
	db_merge($tnc_table)
		->key(array('title' => 'loan'))
		->fields (array(
			'title' => 'Loan',
			'body' => $form_state['values']['loan']['value'],
		)
	)	
	->execute();
	
	db_merge($tnc_table)
		->key(array('title' => 'advance'))
		->fields (array(
			'title' => 'Advance',
			'body' => $form_state['values']['advance']['value'],
		)
	)	
	->execute();
}