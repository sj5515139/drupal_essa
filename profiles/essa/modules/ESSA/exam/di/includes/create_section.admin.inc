<?php
/**
 *Implements page callback function - create_section.
 */
function create_section($form, &$form_state, $group_id){
	$form['group_id'] = array(
		'#type' => 'value',
		'#value' => $group_id
	);
	$form['section_id'] = array(
		'#type' => 'textfield',
		'#title' => 'Section ID',
		'#required' => TRUE,
	);
	
	$form['section_name'] = array(
		'#type' => 'textfield',
		'#title' => 'Section Name',
		'#required' => TRUE,
	);
	
	$form['is_marksheet'] = array(
		'#type' => 'checkbox',
		'#title' => 'Is Marksheet?'
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	return $form;
}

/**
 *Implements submit function.
 */
function create_section_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$group_table = 'essa_'.$session.'_di_group_section';
	
	db_insert($group_table)
	->fields(array(
		'section_id' => $form_state['values']['section_id'],
		'section_name' => $form_state['values']['section_name'],
		'is_marksheet' => $form_state['values']['is_marksheet'],
		'group_id' => $form_state['values']['group_id'],
	))
	->execute();
	
	menu_rebuild();
}