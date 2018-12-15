<?php

/**
 *Implemens page callback function - edit_route
 */
function edit_route($form, &$form_state, $route_id){
	$form = array();
	$session_id = (string)variable_get('essa_sid');
	$bus_routes_table = 'essa_'.$session_id.'_bus_routes';
	
	$form['route_id'] = array(
		'#type' => 'value',
		'#value' => $route_id,
	);
	$bus_routes = db_query("
		SELECT * from {$bus_routes_table} where route_id = :ri;", array(':ri' => $route_id)
	);
	foreach($bus_routes as $br){
		$form['route_name'] = array(
		  '#type' => 'textfield',
			'#title' => t('Route'),
		  '#required' => TRUE,
			'#suffix' => '<script type="text/javascript">'
		      . 'jQuery(\'#edit-route-name\').focus();'
			    . '</script>',
			'#size' => 20,
			'#default_value' => $br->route_name,
			'#disabled' => TRUE,
		);
			
		$form['bus_no'] = array(
		  '#type' => 'textfield',
		  '#title' => t('Bus No.'),
			'#size' => 20,
			'#default_value' => $br->bus_no,
		);
			
		$form['driver'] = array(
		  '#type' => 'textfield',
		  '#title' => t('Driver'),
			'#size' => 20,
			'#default_value' => $br->driver,
		);
		
		$form['helper'] = array(
		  '#type' => 'textfield',
		  '#title' => t('Helper'),
			'#size' => 20,
			'#default_value' => $br->helper,
		);
			
		$form['route_desc'] = array(
		  '#type' => 'textarea',
		  '#title' => t('Description'),
			'#default_value' => $br->route_desc,
		);
	}
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	
	return $form;
}

function edit_route_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
  $route_table = 'essa_'.$session_id.'_bus_routes';
	
	db_merge($route_table)
		->key(array('route_id' => $form_state['values']['route_id']))
    -> fields(array(
			'route_name' => $form_state['values']['route_name'],
			'bus_no' => $form_state['values']['bus_no'],
			'driver' => $form_state['values']['driver'],
			'helper' => $form_state['values']['helper'],
      'route_desc' => $form_state['values']['route_desc'],
    )
  )
  ->execute();
}