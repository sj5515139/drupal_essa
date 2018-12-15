<?php
/**
 *Implements page callback - add_salary_type
 */
function add_salary_type($form, &$form_state){
	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('Create new category'),
		'#required' => TRUE,
		'#size' => 20,
	);
	
	$form['submit'] = array(
		'#type' => 'submit' ,
		'#value' => 'Create',
	);
	
	return $form;
}
 
function add_salary_type_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$table = 'essa_'.$session.'_'.'pr_salary_structure';
	
	db_insert($table)
		->fields (array(
			'title' => $form_state['values']['title'],
		)
	)	
	->execute();
	
	menu_rebuild();
	drupal_set_message('The salary category was created successfully!!!','status');
}