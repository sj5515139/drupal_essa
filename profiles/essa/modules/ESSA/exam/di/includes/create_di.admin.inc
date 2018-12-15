<?php
/**
 *Implements page callback function - create_di
 */
function create_di($form, &$form_state, $group_id, $section_id){
	$session = variable_get('essa_sid');
	$di_section_table = 'essa_'.$session.'_di_group_section';
	$sa_table = 'essa_'.$session.'_di_sa';
	$form['group_id'] = array(
		'#type' => 'value',
		'#value' => $group_id
	);
	
	$form['section_id'] = array(
		'#type' => 'value',
		'#value' => $section_id
	);
	
	$sub_sec_op = array('--Select--');
	$di_sections = db_query("SELECT * FROM {$sa_table} where group_id = :gi and section_id = :si;", array(':gi' => $group_id, ':si' => $section_id));
	foreach($di_sections as $dis){
		$sub_sec_op[$dis->sub_section] = $dis->sub_section;
	}
	$form['sub_sec'] = array(
		'#type' => 'select',
		'#title' => 'Sub-Section',
		'#options' => $sub_sec_op,
	);
	
	$form['new_sub_sec'] = array(
		'#type' => 'textfield',
		'#size' => 10,
		'#attributes' => array('placeholder' => 'Add New'),
	);
	
	$form['sub_sec_title'] = array(
		'#type' => 'textfield',
		'#title' => 'Sub-Section Title',
		'#size' => 20,
	);
	
	$form['serial_no'] = array(
		'#type' => 'textfield',
		'#title' => 'Serial No.',
		'#size' => 5,
		'#required' => TRUE,
	);
	
	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => 'Title',
		'#size' => 20,
	);
	
	for($i = 1;$i<=10;$i++){
		$row[$i] = array(
			'#tree' =>TRUE,
			$i => array(  //Generating unique array id for every form element
				'c1' =>array(
					'#type' => 'textfield',
					'#size' => 10,
				),
				'c2' =>array(
					'#type' => 'textfield',
				),
			),
		);
	}
	
	$form['tab'] = array(
		'#theme' => 'di_grade_table',
		'rows' => $row,
	);
	
	$form['sa'] = array(
		'#type' => 'textarea',
		'#title' => 'Suggestive Activities',
	);
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save'
	);
	return $form;
}

/**
 *Implements page callback function - create_di
 */
function create_di_validate($form, &$form_state){
	if($form_state['values']['sub_sec'] == '0' && $form_state['values']['new_sub_sec'] == NULL){
		form_set_error('sub_sec','Sub-Section is required.');
	}
}
/**
 *Implements page callback function - create_di
 */
function create_di_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$group_table = 'essa_'.$session.'_di_group_name';
	$section_table = 'essa_'.$session.'_di_group_section';
	$di_table = 'essa_'.$session.'_di_indicators';
	$sa_table = 'essa_'.$session.'_di_sa';
	$group_id = $form_state['values']['group_id'];
	$sec_id = $form_state['values']['section_id'];
	
	if($form_state['values']['sub_sec'] != '0'){
		$sub_sec = $form_state['values']['sub_sec'];
	}else{
		$sub_sec = $form_state['values']['new_sub_sec'];
	}
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $di){
				if($di['c1'] != NULL){
					$di_id = NULL;
					$dis = db_query("
						SELECT * from {$di_table} where group_id = :gid and section_id = :si and sub_section = :ss and grade = :gr and serial_no = :sno;",
						array(':gid' => $group_id, ':si' => $sec_id, ':ss' => $sub_sec, ':gr' => $di['c1'], ':sno' => $form_state['values']['serial_no'])
					);
					foreach($dis as $d_i){
						$di_id = $d_i->id;
					}
					db_merge($di_table)
						->key(array('id' => $di_id))
						->fields(array(
							'group_id' => $group_id,
							'section_id' => $sec_id,
							'sub_section' => $sub_sec,
							'grade' => $di['c1'],
							'di' => $di['c2'],
							'serial_no' => $form_state['values']['serial_no'],
						))
					->execute();
				}
			}
		}
	}
	db_merge($sa_table)
		->key(array('sub_section' => $sub_sec, 'group_id' => $group_id, 'section_id' => $sec_id, 'serial_no' => $form_state['values']['serial_no']))
		->fields(array(
			'sub_section' => $sub_sec,
			'group_id' => $group_id,
			'section_id' => $sec_id,
			'serial_no' => $form_state['values']['serial_no'],
			'title' => $form_state['values']['title'],
			'sub_section_title' => $form_state['values']['sub_sec_title'],
			'sa' => $form_state['values']['sa'],
		))
	->execute();
	drupal_set_message('Descriptive Indicators were created successfully.','status');
	menu_rebuild();
}

/**
 *Theme function
 */
function theme_di_grade_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	global $user;
	$header = array(t('Grade'), t('Descriptive Indicators'));
	
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