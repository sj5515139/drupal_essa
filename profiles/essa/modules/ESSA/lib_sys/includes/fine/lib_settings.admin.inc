<?php
/**
 *Implements page callback function - books_issue.
 */
 function lib_settings($form, &$form_state){
	$form = array();
	
	for($i = 1; $i<30; $i++){
		$op[$i] = $i;
	}
	
	$issue_period = variable_get('lib_issue_period');
	$form['issue_period'] = array(
		'#type' => 'select',
		'#title' => 'Issue Period(no. of days)',
		'#description' => 'Fine is applied per day after the issue period.',
		'#options' => $op,
		'#required' => TRUE,
		'#default_value' => $issue_period,
	);
	
	$fine_per_book = variable_get('lib_fine_per_book');
	$form['fine_per_book'] = array(
		'#type' => 'textfield',
		'#title' => 'Fine Amount(per book)',
		'#size' => 10,
		'#default_value' => $fine_per_book,
		'#required' => TRUE,
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Save'
	);
	return $form;
 }
 
 /**
 *Implements validate function - books_issue.
 */
function lib_settings_validate($form, &$form_state){
	
}

 /**
 *Implements page callback function - books_issue.
 */
function lib_settings_submit($form, &$form_state){
	variable_set('lib_issue_period', $form_state['values']['issue_period']);
	// if($form_state['values']['fine'] != NULL){
		// variable_set('lib_fine_per_issue', $form_state['values']['fine']);
	// }else{
		// variable_set('lib_fine_per_issue', NULL);
	// }
	if($form_state['values']['fine_per_book'] != NULL){
		variable_set('lib_fine_per_book', $form_state['values']['fine_per_book']);
	}else{
		variable_set('lib_fine_per_book', NULL);
	}
}