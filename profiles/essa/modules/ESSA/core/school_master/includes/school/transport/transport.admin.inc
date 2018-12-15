<?php

/**
 *Implements page callback function - transport_form
 */
function transport_form($form, &$form_state){
  $form = array();
  $session_id = (string)variable_get('essa_sid');
	$bus_routes_table = 'essa_'.$session_id.'_bus_routes';
  $x = '<i class = "fa fa-pencil"></i>';
  
  $bus_routes = db_query("
    SELECT * from {$bus_routes_table};"
  );
	$row = array();
	$flag = 0;
  foreach($bus_routes as $br){
		$flag = 1;
		$row[] = array(
		  '#tree' =>TRUE,
		  $br -> route_id => array(  //Generating unique array id for every form element
			  'c1' =>array(
		      '#type' => 'markup',
			    '#markup' => '<h3>'. $br -> route_name .'</h3>',
			  ),
			  'c2' =>array(
		      '#type' => 'markup',
		      '#markup' => '<h3>'.$br -> bus_no.'</h3>',
			  ),
			  'c3' =>array(
			    '#type' => 'markup',
			    '#markup' => '<h3>'.$br->driver.'</h3>',
		    ),
				'c4' =>array(
			    '#type' => 'markup',
					'#markup' => '<h3>'.$br->helper.'</h3>',
			  ),
		    'c5' =>array(
		      '#type' => 'markup',
			    '#markup' => '<h3>'.l($x, 'edit_route/'.$br->route_id, array('html' => TRUE)).'</h3>',
			  ),
		    'c6' =>array(
		      '#type' => 'submit',
		      '#submit' => array('manage_stops'),
		      '#value' => 'Manage Stops',
					'#name' => $br->route_id,
			  ),
				$br->route_id =>array(
		      '#type' => 'submit',
		      '#submit' => array('delete_routes'),
		      '#value' => 'Delete',
					'#name' => $br->route_id,
				  '#prefix' => '<div id = "delete_br">',
				  '#suffix' => '</div>',
		    ),
		  ),
		);
	}
  if($flag == 1){
		$form['bus_routes_table'] = array(
			'#theme' => 'bus_routes_table',
			'rows' => $row,
		);
	}else{
		$form['error'] = array(
			'#type' => 'markup',
			'#markup' => '<h1 style = "color:red;">No Route has been created yet.</h1 >',
		);
	}
  
	
  return $form;
}

function edit_routes($form, &$form_state){
  global $user;
  global $base_url;
  variable_set('edit_route'.$user->uid, $form_state['triggering_element']['#name']);
  $route_id = $form_state['triggering_element']['#name'];
  $url = $base_url.'/admin/settings/transport_setting/#overlay='.'admin/settings/transport_setting/create_route';
  $form_state['redirect'] = $url;
}

function manage_stops($form, &$form_state){
  global $base_url;
  $route_id = $form_state['triggering_element']['#name'];
  $url = $base_url.'/admin/settings/transport_setting/#overlay='.'admin/settings/transport_setting/'.$route_id;
  $form_state['redirect'] = $url;
}

function delete_routes($form, &$form_state){
  global $user;
  variable_set('delete-route'.$user->uid, $form_state['triggering_element']['#name']);
	$url = url('delete-route', array('absolute' => TRUE));
	$form_state['redirect'] = $url;
}

function delete_route_pagecallback(){
	return drupal_get_form('delete_route_confirm');
}

function delete_route_confirm($form, &$form_state){
	$heading = t('Are you sure to delete this route.');
	$caption = '<h3>This action can\'t be undone. After deletion, this route along with all the stops will be deleted.</h3>';
	
	$cancel_path = 'admin/settings/transport_setting';
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

function delete_route_confirm_submit($form, &$form_state){
	global $user;
	$session_id = (string)variable_get('essa_sid');
  $route_table = 'essa_'.$session_id.'_bus_routes';
  $bus_stop_table = 'essa_'.$session_id.'_bus_stops';
  $route_id = variable_get('delete-route'.$user->uid);
  
	db_delete($route_table)
		->condition('route_id', $route_id)
		->execute();
		
	db_delete($bus_stop_table)
		->condition('route_id', $route_id)
		->execute();
	
  $stops = taxonomy_get_children(71);
  foreach($stops as $stop){
    taxonomy_term_delete($stop->tid);
  }
  
	$url = url('admin/settings/transport_setting', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
	drupal_set_message('The route & stops were deleted successfully.');
}

/**
 *Theme function
 */
function theme_bus_routes_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Route'), t('Bus No.'), t('Driver'), t('Helper'), t(''), t(''), t(''));
  
  // Setup the structure to be rendered and returned.
  $content = array(
    '#theme' => 'table',
    '#rows' => array(),
    '#header' => $header,
  );
  
  // Traverse each row.  @see element_chidren().
  foreach (element_children($rows) as $row_index) {
    $row = array();
    // Traverse each column in the row.  @see element_children().
    foreach (element_children($rows[$row_index]) as $col_index) {
      // Traverse each column in the row.  @see element_children().
      foreach (element_children($rows[$row_index][$col_index]) as $col_index1) {
      // Render the column form element.
        $row[] = drupal_render($rows[$row_index][$col_index][$col_index1]);
      }
    }
    // Add the row to the table.
    $content['#rows'][] = $row;
  }

  // Redner the table and return.
  return drupal_render($content);
}