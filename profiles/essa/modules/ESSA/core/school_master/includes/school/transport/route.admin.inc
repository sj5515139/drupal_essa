<?php

/**
 *Implements page callback function - create_route_form
 */
function create_route_form($form, &$form_state){
  $form = array();
  
  $form['route_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Route'),
    '#required' => TRUE,
		'#suffix' => '<script type="text/javascript">'
                 . 'jQuery(\'#edit-route-name\').focus();'
                 . '</script>',
  );
	
	$form['bus_no'] = array(
    '#type' => 'textfield',
    '#title' => t('Bus No.'),
  );
	
	$form['driver'] = array(
    '#type' => 'textfield',
    '#title' => t('Driver'),
  );
	
	$form['helper'] = array(
    '#type' => 'textfield',
    '#title' => t('Helper'),
  );
  
  $form['route_desc'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}

/**
 *Implements submit function for create_route_form()
 */
function create_route_form_submit($form, &$form_state){
  $session_id = (string)variable_get('essa_sid');
  $route_table = 'essa_'.$session_id.'_bus_routes';
  
	$vid = taxonomy_vocabulary_machine_name_load('transport_vocab');
	if(_get_taxonomy_term_id_by_name($form_state['values']['route_name'], $vid->vid) == false) {
    taxonomy_term_save(
      (object) array(
        'name' => $form_state['values']['route_name'],
        'vid' => $vid->vid,
      )
    );
	}
  
	$vid = taxonomy_vocabulary_machine_name_load('transport_vocab');
	if(_get_taxonomy_term_id_by_name($form_state['values']['route_name'], $vid->vid) == false) {
    taxonomy_term_save(
      (object) array(
        'name' => $form_state['values']['route_name'],
        'vid' => $vid->vid,
      )
    );
	}
	
	$term = taxonomy_get_term_by_name($form_state['values']['route_name']);
	foreach($term as $term){
		$route_id = $term->tid;
	}
	
  db_insert($route_table)
    -> fields(array(
			'route_id' => $route_id,
      'route_name' => $form_state['values']['route_name'],
			'bus_no' => $form_state['values']['bus_no'],
			'driver' => $form_state['values']['driver'],
			'helper' => $form_state['values']['helper'],
      'route_desc' => $form_state['values']['route_desc'],
    )
  )
  ->execute();
  
	//*******Suraj********//
	global $base_url;
  drupal_set_message('Bus route '.$form_state['values']['route_name'].' was successfully created. Manage <a href = "'.$base_url.'/admin/settings/transport_setting/'.$route_id.'">[<u>Bus Stop</u>]</a> now.');
  
	//sending system alert
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	global $user;
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
	'message' => 'Bus route '.$form_state['values']['route_name'].' was created.',
	'priority' => 'L',
	'module' => 'school_master',
	'source_url' => 'admin/settings/transport_setting/create_route',
	'timestamp' => $strtodate,
	'source_uid' => $user->uid,
	))
	->execute();
	//*******Suraj********//
	
  drupal_flush_all_caches();
}

/**
 * Get taxonomy term ID by term name.
 * 
 * @param string $termname
 * @param integer $vid
 */
function _get_taxonomy_term_id_by_name($termname, $vid) {
    return db_select('taxonomy_term_data', 't')
    ->fields('t', array('tid'))
    ->condition('t.name', $termname)
    ->condition('t.vid', $vid)
    ->execute()
    ->fetchField();
}