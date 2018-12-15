<?php
/**
 * Implements callback function today_arrangement()
 */
function today_arrangement($form = array(), &$form_state){
	
	$date = date('Y-m-d');
	$day = date('l');
	
	$form['for'] = array(
    '#type' => 'markup',
    '#markup' => '<h1 style = "text-align: center" id = "tt_title">'.'Class Arrangement for '.'<strong>'.strtoupper($day).' - '.$date.'</strong>'.'</h1>',
  );
	
	$session = variable_get('essa_sid');
	$tt_arrangement_table = 'essa_'.$session.'_time_table_arrangement';
	$today_arrangement = db_query("SELECT * FROM {$tt_arrangement_table} where date = :d;", array(':d' => strtotime($date)));
	
	foreach($today_arrangement as $ta){
		$row[] = array(
			'#tree' =>TRUE,
			$ta->id => array(  //Generating unique array id for every form element
				'c1' =>array(
					'#type' => 'markup',
					'#markup' => '<h3>'.$ta->class.'</h3>',
				),
				'c2' =>array(
					'#type' => 'markup',
					'#markup' => '<h3>'.$ta->period.'</h3>',
				),
				'c3' =>array(
					'#type' => 'markup',
					'#markup' => '<h3>'.$ta->subject.'</h3>',
				),
				'c4' =>array(
					'#type' => 'markup',
					'#markup' => '<h3>'.$ta->teacher.'</h3>',
				),
			),
		);
	}
	if(isset($row)){
		$form['today_time_table'] = array(
			'#theme' => 'today_arrangement_table',
			'rows' => $row,
		);
	}else{
		$form['sd_wrapper']['msg'] = array(
			'#type' => 'markup',
			'#markup' => '</br><h3 style ="color: red;">There is no arrangement for today.</h3>',
		);
	}
	
	$form['fs'] = array(
		'#type' => 'fieldset',
		'#title' => 'Create Arrangement for today',
	);

	module_load_include('inc', 'hierarchical_select', 'includes/common');
	
	$config = sa_hs_setting();
	$form['fs']['class'] =  array(
    '#title' => t('Class'),
    '#type' => 'hierarchical_select',
    '#config' => $config,
		'#required' => TRUE,
  );
	
	$form['fs']['period'] = array(
	  '#title' => 'Period',
	  '#type' => 'select',
		'#options' => drupal_map_assoc(array('1','2','3','4','5','6','7','8')),
		'#required' => TRUE,
	);
	
	
	$form['fs']['teacher'] = array(
		'#type' => 'textfield',
		'#autocomplete_path' => 'teachers/autocomplete',
		'#size' => 10,
		'#title' => 'Teacher',
		'#required' => TRUE,
	);
	
	$form['fs']['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	
	
	return $form;
}


/**
 *Implements ajax callback function - get_class_ajax()
 */
function get_teacher_ajax($form, &$form_state){
	//dsm($form_state);
	return $form['sd_wrapper'];
}

/**
 *Implements submit function - get_ajax_submit
 */
function today_arrangement_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$tt_arrangement_table = 'essa_'.$session.'_time_table_arrangement';
	$staff_table = 'essa_'.$session.'_master_staff_table';
	$class = taxonomy_term_load($form_state['values']['class'][0]);
	$sec = taxonomy_term_load($form_state['values']['class'][1]);
	
	
	$date = date('Y-m-d');
	$cls = $class->name.'_'.$sec->name;
	$class_timetable = 'essa_'.$session.'_time_table_'.$cls;
	$id  = NULL;
	$id1  = NULL;
	$id2 = NULL;
	$id3 = NULL;
	$sub_id = NULL;
	//dsm($cls);
	preg_match('#\((.*?)\)#', $form_state['values']['teacher'], $match);
	$staff_db = db_query(
		"SELECT * from {$staff_table} where nickname = :nickname",  array(':nickname' => $match[1])
	);
	foreach($staff_db as $staff){
		$emp_id = $staff->emp_id;
	}
	$day = date('l');
	$period = 'Period'.$form_state['values']['period'];
	$subject = db_query("SELECT * FROM {$class_timetable} where day = :d  order by day_weight;", array(':d' => $day));
	foreach($subject as $sub){
		$sub_id = $sub->$period;
 	}
	
	$sub_id = explode('(', $sub_id);
	if($sub_id[1] != NULL){
		$sub_id = str_replace(')','',$sub_id[1]);
	}
	
	$default1 = db_query("SELECT * FROM {$tt_arrangement_table} WHERE class = :c AND period = :p;", array(':c' => $cls, ':p' => 'Period '.$form_state['values']['period']));
	foreach($default1 as $d1){
		$id1 = $d1->id;
	}
	
	$default2 = db_query("SELECT * FROM {$tt_arrangement_table} WHERE class = :c AND teacher = :t;", array(':c' => $cls, ':t' => $emp_id));
	foreach($default2 as $d2){
		$id2 = $d2->id;
	}
	
	$default3 = db_query("SELECT * FROM {$tt_arrangement_table} WHERE period = :p AND teacher = :t;", array(':p' => 'Period '.$form_state['values']['period'], ':t' => $emp_id));
	foreach($default3 as $d3){
		$id3 = $d3->id;
	}
	
	if($id1 != NULL){
		db_merge($tt_arrangement_table)
		->key(array('id' => $id1))
		->fields(array(
			'teacher' => $emp_id,
		))
		->execute();
	}elseif($id2 != NULL){
		db_merge($tt_arrangement_table)
		->key(array('id' => $id2))
		->fields(array(
			'period' => 'Period '.$form_state['values']['period'],
		))
		->execute();
	}elseif($id3 != NULL){
		db_merge($tt_arrangement_table)
		->key(array('id' => $id3))
		->fields(array(
			'class' => $cls,
		))
		->execute();
	}else{
		db_merge($tt_arrangement_table)
		->key(array('date' => strtotime($date), 'class' => $cls, 'period' => $form_state['values']['period']))
		->fields(array(
			'date' => strtotime($date),
			'class' => $cls,
			'period' => 'Period '.$form_state['values']['period'],
			'teacher' => $emp_id,
			'subject' => $sub_id
		))
		->execute();
	}
	
}


/**
 * Theme callback for the form table.
*/ 
function theme_today_arrangement_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Class'), t('Period'),  t('Subject'), t('Teacher'));
  
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


