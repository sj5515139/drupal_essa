<?php
/**
 *Implements page callback function - manage_optional_subject()
 */
function manage_optional_subject($form, &$form_state, $class){
	$session = variable_get('essa_sid');
	$class_table = 'essa_'.$session.'_class_list';
	$optional_subject_pair_table = 'essa_'.$session.'_optional_subject_pair';

	$form['msg'] = array(
		'#type' => 'markup',
		'#markup' => '<h3><b>Optional subject pairing for class</b> <b style = "color: green;">'.$class.'</b>.</h3>'
	);
	$option = array();

	$class_sub_table = 'essa_'.$session.'_subjects_'.mod_sub_string($class);
	$subjects = db_query("SELECT * FROM {$class_sub_table} WHERE type = :t;", array(':t' => 'Optional'));
	foreach($subjects as $subject){
		//dsm($subject->sub_id);
		$option[$subject->sub_id] = $subject->sub_name;
	}
	//dsm($option);

	if($option != NULL){
		//dsm('dhbf');
		$form['pair_name'] = array(
			'#type' => 'textfield',
			'#title' => 'Pair Name',
			'#required' => TRUE,
		);

		$form['optional_subject'] = array(
			'#type' => 'checkboxes',
			'#title' => 'Select optional subjects',
			'#options' => $option,
			'#required' => TRUE,
		);
		$ops_row = array();
		$op_subjects = db_query("SELECT * FROM {$optional_subject_pair_table} WHERE class = :cl;", array(':cl' => $class));
		foreach($op_subjects as $ops){
			$ops_row[$ops->pair_name] = array(
				'#tree' =>TRUE,
				$ops->pair_name => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: center !important;">'. $ops->pair_name .'</h3>',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: center !important;">'. $ops->sub_1 .'</h3>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: center !important;">'. $ops->sub_2 .'</h3>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: center !important;">'. $ops->sub_3 .'</h3>',
					),
					'c5' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: center !important;">'. $ops->sub_4 .'</h3>',
					),
					'c6' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: center !important;">'. $ops->sub_5 .'</h3>',
					),
				),
			);
		}
		$form['sec_wrapper']['marks_wrapper']['mw']['fm_tab'] = array(
			'#theme' => 'op_table',
			'rows' => $ops_row,
		);
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Save',
			'#submit' => array('optional_subject_list_ajax_submit'),
		);

	}else{
		//dsm('hvb');
		$form['error'] = array(
			'#type' => 'markup',
			'#markup' => '<h3 style = "color: red;">No optional subject created.</h3>',
		);
	}

	$form['class'] = array(
		'#type' => 'value',
		'#value' => $class,
	);

	return $form;
}

/**
 *Implements ajax callback optional_subject_list_ajax_submit.
 */
function optional_subject_list_ajax_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$optional_subject_pair_table = 'essa_'.$session.'_optional_subject_pair';
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	$notification_table = 'essa_'.$session.'_notifications';
	global $user;
	//dsm($form_state);

	$class_sub_table = 'essa_'.$session.'_subjects_'.mod_sub_string($form_state['values']['class']);
	$subjects = db_query("SELECT * FROM {$class_sub_table} WHERE type = :t;", array(':t' => 'Optional'));
	$num = 1;
	foreach($form_state['values']['optional_subject'] as $k => $v){
		if($v != '0'){
			db_merge($optional_subject_pair_table)
			->key(array('class' => $form_state['values']['class'], 'pair_name' => $form_state['values']['pair_name']))
			->fields(array(
				'class' => $form_state['values']['class'],
				'pair_name' => $form_state['values']['pair_name'],
				'sub_'.$num => $v,
			))
			->execute();
			$num++;
		}
	}

	drupal_set_message($form_state['values']['pair_name'].' created successfully.');

	//sending system alert
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'Optional subject pair '.$form_state['values']['pair_name'].' was cretaed for class '.$form_state['values']['class'],
		'priority' => 'L',
		'module' => 'school_master',
		'source_url' => 'admin/settings/classes/class-teacher',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
}

/**
 * Theme callback for the form table.
*/ 
function theme_op_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Pair Name'), t('Subject 1'), t('Subject 2'), t('Subject 3'), t('Subject 4'), t('Subject 5'));
  
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



/**
 *Implements ajax callback.
 */
function optional_subject_list_ajax($form, &$form_state){
	//dsm($form_state);
	return $form['subject_wrapper'];
}