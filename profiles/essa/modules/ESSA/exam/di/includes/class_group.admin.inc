<?php
/**
 *Implements page callback - class_group
 */
function class_group($form, &$form_state){
	$session = variable_get('essa_sid');
	$class_list_table = 'essa_'.$session.'_class_list';
	
	$form['group_name'] = array(
		'#type' => 'textfield',
		'#title' => 'Group Name',
		'#required' => TRUE,
	);
	$class_list = db_query("SELECT * FROM {$class_list_table} ORDER BY weight");
	foreach($class_list as $cl){
		$class[] = $cl->class_id;
	}
	$form['class_from'] = array(
		'#type' => 'select',
		'#title' => 'Class From',
		'#options' => drupal_map_assoc($class),
		'#required' => TRUE,
 	);
	$form['class_to'] = array(
		'#type' => 'select',
		'#title' => 'Class To',
		'#options' => drupal_map_assoc($class),
		'#required' => TRUE,
 	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	$grp_name = variable_get('di_group_name');
	return($form);
}

/**
 *Implements submit function
 */
function class_group_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$group_table = 'essa_'.$session.'_di_group_name';
	
	($form_state['values']['class_from'] == '--Select--') ? $class_from = NULL: $class_from = $form_state['values']['class_from'];
	($form_state['values']['class_to'] == '--Select--') ? $class_to = NULL: $class_to = $form_state['values']['class_to'];
	db_insert($group_table)
	->fields(array(
		'group_name' => $form_state['values']['group_name'],
		'class_from' => $class_from,
		'class_to' => $class_to,
	))
	->execute();
	menu_rebuild();
}
