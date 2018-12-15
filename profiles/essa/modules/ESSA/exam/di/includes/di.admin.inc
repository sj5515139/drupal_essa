<?php
/**
 *Implements page callback function - create_di
 */
function di($form, &$form_state, $group_id, $section_id, $sub_sec, $serial_no){
	$session = variable_get('essa_sid');
	$di_table = 'essa_'.$session.'_di_indicators';
	$sa_table = 'essa_'.$session.'_di_sa';
	
	$form['group_id'] = array(
		'#type' => 'value',
		'#value' => $group_id
	);
	
	$form['section_id'] = array(
		'#type' => 'value',
		'#value' => $section_id
	);
	
	$form['sub_sec'] = array(
		'#type' => 'value',
		'#value' => $sub_sec
	);
	
	$form['sub_sec'] = array(
		'#type' => 'textfield',
		'#title' => 'Sub-Section',
		'#size' => 5,
		'#default_value' => $sub_sec,
		'#disabled' => TRUE,
	);
	$dis = db_query("SELECT * FROM {$sa_table} where group_id = :gi and section_id = :si and sub_section = :ss and serial_no = :sno",
		array(':gi' => $group_id, ':si' => $section_id, ':ss' => $sub_sec, ':sno' => $serial_no));
	foreach($dis as $di){
		$sub_sec_title = $di->sub_section_title;
		$title = $di->title;
		$sa = $di->sa;
	}
	$form['sub_sec_title'] = array(
		'#type' => 'textfield',
		'#title' => 'Sub-Section Title',
		'#size' => 20,
		'#default_value' => $sub_sec_title,
	);
	
	$form['serial_no'] = array(
		'#type' => 'textfield',
		'#title' => 'Serial No.',
		'#size' => 5,
		'#default_value' => $serial_no,
	);
	
	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => 'Title',
		'#size' => 20,
		'#default_value' => $title,
	);
	
	$dis = db_query("SELECT * FROM {$di_table} where group_id = :gi and section_id = :si and sub_section = :ss and serial_no = :sno",
		array(':gi' => $group_id, ':si' => $section_id, ':ss' => $sub_sec, ':sno' => $serial_no));
	foreach($dis as $di){
		$row[$di->grade] = array(
			'#tree' =>TRUE,
			$di->grade => array(  //Generating unique array id for every form element
				'c1' =>array(
					'#type' => 'textfield',
					'#size' => 10,
					'#default_value' => $di->grade,
				),
				'c2' =>array(
					'#type' => 'textfield',
					'#default_value' => $di->di,
				),
			),
		);
		$flag = 1;
	}
	
	$row['new'] = array(
		'#tree' =>TRUE,
		'new' => array(  //Generating unique array id for every form element
			'c1' =>array(
				'#type' => 'textfield',
				'#size' => 10,
			),
			'c2' =>array(
				'#type' => 'textfield',
			),
		),
	);
	
	$form['tab'] = array(
		'#theme' => 'di_grade_table',
		'rows' => $row,
	);
	
	$form['sa'] = array(
		'#type' => 'textarea',
		'#title' => 'Suggestive Activities',
		'#default_value' => $sa,
	);
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save'
	);
	$form['delete'] = array(
		'#type' => 'submit',
		'#value' => 'Delete',
		'#submit' => array('delete_di'),
	);
	return $form;
}

/**
 *Implements delete logic
 */
function delete_di($form, &$form_state){
	$session = variable_get('essa_sid');
	$group_table = 'essa_'.$session.'_di_group_name';
	$section_table = 'essa_'.$session.'_di_group_section';
	$di_table = 'essa_'.$session.'_di_indicators';
	$sa_table = 'essa_'.$session.'_di_sa';
	$group_id = $form_state['values']['group_id'];
	$sec_id = $form_state['values']['section_id'];
	
	db_delete($di_table)
		->condition(db_and()
			->condition('group_id',$group_id,'=')
			->condition('section_id',$sec_id,'=')
			->condition('sub_section',$form_state['values']['sub_sec'],'=')
			->condition('serial_no',$form_state['values']['serial_no'],'='))
		->execute();
	
	db_delete($sa_table)
		->condition(db_and()
			->condition('group_id',$group_id,'=')
			->condition('section_id',$sec_id,'=')
			->condition('sub_section',$form_state['values']['sub_sec'],'=')
			->condition('serial_no',$form_state['values']['serial_no'],'='))
		->execute();
}

/**
 *Implements page callback function - create_di
 */
function di_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$group_table = 'essa_'.$session.'_di_group_name';
	$section_table = 'essa_'.$session.'_di_group_section';
	$di_table = 'essa_'.$session.'_di_indicators';
	$sa_table = 'essa_'.$session.'_di_sa';
	$group_id = $form_state['values']['group_id'];
	$sec_id = $form_state['values']['section_id'];
	$existing_grades = array();
	$dont_del = array();
	
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $di){
				if($di['c1'] != NULL){
					$di_id = NULL;
					$dis = db_query("
						SELECT * from {$di_table} where group_id = :gid and section_id = :si and sub_section = :ss and serial_no = :sno and grade = :gr;",
						array(':gid' => $group_id, ':si' => $sec_id, ':ss' => $form_state['values']['sub_sec'], ':sno' => $form_state['values']['serial_no'], ':gr' => $di['c1'])
					);
					foreach($dis as $d_i){
						$di_id = $d_i->id;
					}
					
					db_merge($di_table)
						->key(array('id' => $di_id))
						->fields(array(
							'group_id' => $group_id,
							'section_id' => $sec_id,
							'sub_section' => $form_state['values']['sub_sec'],
							'grade' => $di['c1'],
							'di' => $di['c2'],
							'serial_no' => $form_state['values']['serial_no'],
						))
					->execute();
				}
			}
		}
	}
	$dis = db_query("
		SELECT * from {$di_table} where group_id = :gid and section_id = :si and sub_section = :ss and serial_no = :sno;",
		array(':gid' => $group_id, ':si' => $sec_id, ':ss' => $form_state['values']['sub_sec'], ':sno' => $form_state['values']['serial_no'])
	);
	foreach($dis as $d_i){
		$existing_grades[$d_i->grade] = $d_i->grade;
	}
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $di){
				if($di['c1'] != NULL){
					if(in_array($di['c1'], $existing_grades)){
						$dont_del[$di['c1']] = $di['c1'];
					}
				}
			}
		}
	}
	
	$del = array_diff($existing_grades, $dont_del);
	foreach($del as $del_id){
		db_delete($di_table)
			->condition(db_and()
				->condition('group_id',$group_id,'=')
				->condition('section_id',$sec_id,'=')
				->condition('sub_section',$form_state['values']['sub_sec'],'=')
				->condition('serial_no',$form_state['values']['serial_no'],'=')
				->condition('grade',$del_id,'='))
			->execute();
	}
	db_merge($sa_table)
		->key(array('sub_section' => $form_state['values']['sub_sec'], 'group_id' => $group_id, 'section_id' => $sec_id))
		->fields(array(
			'sub_section' => $form_state['values']['sub_sec'],
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