<?php

/**
 *Implements page callback function
 */
function bus_stop_form($form, &$form_state, $route_id){
	$form = array();
	$session = variable_get('essa_sid');
  $bus_stop_table = 'essa_'.$session.'_bus_stops';
	
  $form['route_id'] = array(
		'#type' => 'value',
		'#value' => $route_id,
	);
	
	$term = taxonomy_term_load($route_id);
	
  $form['help'] = array(
		'#type' => 'markup',
		'#markup' => '<br><h3>'.'You are managing bus stops for Route - '.'<b>'.$term->name.'</b>.<span style = "font-size: 14px;"><em> Bus Stop Name must be unique.<em></span></h3>',
	);
	
	$count = 0;
	$bus_stops = db_query("
    SELECT * from {$bus_stop_table} where route_id = :route_id order by distance_from_school", array(':route_id' => $route_id)
  );
	foreach($bus_stops as $stop){
		$bus_stop_id[] = $stop->bus_stop_id;
		$stop_name[] = $stop->stop_name;
		$dfs[] = $stop->distance_from_school;
		$count++;
	}
  $l = variable_get('set_route_'.$route_id);
	
	//isset($l) ? $l++ && $limit = variable_get('set_route_'.$route_id, $l) : $limit = 10;
	if($count < 10){
		$limit = 10;
	}else{
		$limit = $count+1;
	}
	
	for($i = 0; $i < $limit; $i++){
		//-------------------------------------------------sets default vaues as empty string for all rows if DB entry is NULL----------------------------------
		$row[] = array(
      '#tree' =>TRUE,
			
      $i => array(  //Generating unique array id for every form element
				'c2' =>array(
          '#type' => 'textfield',
					'#size' => 30,
					'#default_value' => isset($stop_name[$i])?$stop_name[$i]:NULL,
        ),
        'c3' =>array(
          '#type' => 'textfield',
					'#size' => 10,
					'#default_value' => isset($dfs[$i])?$dfs[$i]:NULL,
        ),
      ),
    );
  }
  
	//-----------------------Calling the theme function to build the custom table and display the form in tabular format.-----------------------------
  $form['sub'][$route_id] = array(
    '#theme' => 'bus_stop_table',
    'rows' => $row,
  );
  
	$form['save_sub'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
//	
//	$form['reset'] = array(
//    '#type' => 'submit',
//    '#value' => t('Reset'),
//    '#submit' => array('reset_form'),
//  );
	
	$stop_terms = taxonomy_get_children(71);
	$bus_stops = db_query("
    SELECT * from {$bus_stop_table} where route_id = :route_id order by distance_from_school", array(':route_id' => $route_id)
  );
	foreach($bus_stops as $stop){
		$stop_names[] = $stop->stop_name;
	}
	
	foreach($stop_terms as $st){
		if(!in_array($st->name, $stop_names)){
			taxonomy_term_delete($st->tid);
		}
	}
	return $form;
}

/**
 *Submit function - adds more rows to the form.
 */
function add_more($form, &$form_state){
  $form_state['rebuild']  = TRUE;
  //dsm($form_state['values']['route_id']);
  $l = variable_get('set_route_'.$form_state['values']['route_id']);
  isset($l) ? $l++ && variable_set('set_route_'.$form_state['values']['route_id'], $l) : variable_set('set_route_'.$form_state['values']['route_id'], 10);
}

/**
 *Submit function - resets the form.
 */
//function reset_form($form, $form_state){
//	global $user;
//	variable_set('reset_route_'.$user->uid, $form_state['values']['route_id']);
//	$url = url('reset-route', array('absolute' => TRUE));
//	$form_state['redirect'] = $url;
//}s

/**
 *Impements submit functon fro bus_stop_form.
 */
function bus_stop_form_submit($form, &$form_state){
	$session = variable_get('essa_sid');
  $bus_stop_table = 'essa_'.$session.'_bus_stops';
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	global $base_url;
	global $user;
	
	$all_stops = array();
	//dsm($form_state);

	foreach($form_state['values'] as $value){
		if(is_array($value)){
			foreach($value as $val){
				if($val['c2'] != NULL){
					$all_stops[] = $val['c2']; 
					$tid = $term = taxonomy_term_load($form_state['values']['route_id']);
					$vid = taxonomy_vocabulary_machine_name_load('transport_vocab');
					if(_get_taxonomy_term_id_by_name($val['c2'], $tid->tid, $vid->vid) == FALSE) {
						$term1 = array(
							'name' => $val['c2'], 
							'parent' => $tid->tid, 
							'vid' => $vid->vid,
							'weight' => (int)$val['c3'],
						);
						$term1 = (object) $term1;
						taxonomy_term_save($term1);
					}
					$stop_tid = taxonomy_get_term_by_name($val['c2']);
					foreach($stop_tid as $stop){
						$stid = $stop->tid;
					}
					db_merge($bus_stop_table)
					->key(array('bus_stop_id' => $stid))
					->fields(array(
						'bus_stop_id' => $stid,
						'route_id' => $form_state['values']['route_id'],
						'stop_name' => $val['c2'],
						'route_tid' => $tid->tid,
						'stop_tid' => $stid,
						'distance_from_school' => (float)$val['c3'],
					))
					->execute();
				}
			}
		}
	}
	
	//*******Suraj********//
	//sending system alert
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
	'message' => 'Bus stops for route id '.$form_state['values']['route_id'].' were created!!!',
	'priority' => 'L',
	'module' => 'school_master',
	'source_url' => 'admin/settings/transport_setting/'.$form_state['values']['route_id'],
	'timestamp' => $strtodate,
	'source_uid' => $user->uid,
	))
	->execute();
	//*******Suraj********//
	
	
	$bus_stops = db_query("
    SELECT * from {$bus_stop_table} where route_id = :route_id order by distance_from_school", array(':route_id' => $form_state['values']['route_id'])
  );
	foreach($bus_stops as $stop){
		$stop_names[] = $stop->stop_name;
	}
  
	foreach($stop_names as $t){
		if(!in_array($t, $all_stops)){
			taxonomy_term_delete($t);
			db_delete($bus_stop_table)
			->condition(db_and()
					->condition('stop_name', $t, '=')
					->condition('route_id', $form_state['values']['route_id'], '=')
				)
			->execute();
			
			if(variable_get('set_route_'.$form_state['values']['route_id']) > 10){
				$l = variable_get('set_route_'.$form_state['values']['route_id']);
				$l--;
				variable_set('set_route_'.$form_state['values']['route_id'], $l);
			}
		}
	}
	drupal_set_message('Bus stops were created for route - '.$tid->name.'.', 'status');
}

/**
 * Get taxonomy term ID by term name.
 * 
 * @param string $termname
 * @param integer $vid
 */
function _get_taxonomy_term_id_by_name($termname, $tid, $vid) {
	$term_data = taxonomy_get_children($tid);
	$ch = array();
	if(empty($term_data)){
		return FALSE;
	}else{
		foreach($term_data as $data){
			$ch[] = $data->name;
		}
	}
	if(!in_array($termname, $ch)){
		return FALSE;
	}else{
		return TRUE;	
	}
}

/**
 * Theme callback for the form table.
 */
function theme_bus_stop_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Bus Stop Name'), t('Distance from School(in KMs)'));
  
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