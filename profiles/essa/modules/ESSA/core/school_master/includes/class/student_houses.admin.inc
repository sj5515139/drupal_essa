<?php
function student_house_form($form, &$form_state, $class, $sec){
  $session = variable_get('essa_sid');
  $basic_info_table = 'essa_'.$session.'_basicinfo';
	
	$basic_info = db_query("
    SELECT * from {$basic_info_table};"
  );
	foreach($basic_info as $bi){
    $houses = array($bi->house1, $bi->house2, $bi->house3, $bi->house4);
  }
  
	if($bi->house1 != NULL || $bi->house2 != NULL || $bi->house3 != NULL || $bi->house4 != NULL){
		$form['class'] = array(
    '#type' => 'value',
    '#value' => $class,
  );
  
  $form['sec'] = array(
    '#type' => 'value',
    '#value' => $sec,
  );
  
  $form['back'] = array(
		'#type' => 'markup',
		'#markup' => '<p class = "back_button">'.l(t('Back'), 'admin/students/manage_houses/'.$class).'</p>',
	);
	
  $student_table = 'essa_'.$session.'_master_student_table';
	$studs = db_query("
    SELECT * from {$student_table} where class =:class AND section = :sec AND status = 1 order by roll_no;",array(':class' => $class, ':sec' => $sec)
  );
	$row = array();
	foreach($studs as $student){
		//dsm($student);
    $row[$student->adm_no] = array(
      '#tree' =>TRUE,
			
      $student->adm_no => array(  //Generating unique array id for every form element
				'c1' =>array(
          '#type' => 'markup',
					'#markup' => '<h3>'.$student->roll_no.'</h3>',
        ),
				'c2' =>array(
          '#type' => 'markup',
					'#markup' => '<h3>'.$student->adm_no.'</h3>',
        ),
				'c3' =>array(
          '#type' => 'markup',
					'#markup' => '<h3 style = "text-align: left;">'.$student->first_name.' '.$student->middle_name.' '.$student->last_name.'</h3>',
        ),
        'c4' =>array(
          '#type' => 'radios',
					'#options' => drupal_map_assoc($houses),
					'#default_value' => isset($student->house)?$student->house:NULL,
        ),
      ),
    );
  }
  
  $form['students_house'] = array(
    '#theme' => 'student_house_table',
    'rows' => $row,
  );
	
	$form['submit'] = array(
		'#type' => 'submit',
    '#value' => 'Save',
	);
	
	}else{
		$form['error'] = array(
		'#type' => 'markup',
		'#markup' => '<h1 style = "color:red;">No houses has been created yet.</h1 >',
	);
	}
	
  
  return $form;
}

function student_house_form_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$student_table = 'essa_'.$session.'_master_student_table';
	
	foreach($form_state['values'] as $v){
		if(is_array($v)){
			foreach($v as $key=>$val){
				db_merge($student_table)
					->key(array('adm_no' => $key))
					->fields (array(
						'house' => $val['c4'],
					)
				)
				->execute();
				
				//*******Suraj********//
				$sys_alert_table = 'essa_'.$session.'_system_alert';
				global $user;
				//sending system alert
				$created_date = date("Y-m-d H:i:s");
				$strtodate = strtotime($created_date);
				db_insert($sys_alert_table)
				->fields(array(
					'message' => 'House for students of class '.$form_state['values']['class'].' - '.$form_state['values']['sec'].' has been alloted.',
					'priority' => 'L',
					'module' => 'students',
					'source_url' => 'admin/students/manage_houses/'.$form_state['values']['class'].'/'.$form_state['values']['sec'],
					'timestamp' => $strtodate,
					'source_uid' => $user->uid,
				))
				->execute();
				//*******Suraj********//
				
			}
		}
	}
}
/**
 * Theme callback for the form table.
 */
function theme_student_house_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Roll No.'),t('Admission No.'),t('Name'),t('Select House'));
  
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
