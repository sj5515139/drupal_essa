<?php
/**
 *Implements page callback function - remarks_form.admin.inc.
 */
function remarks_form($form, &$form_state, $uid){
	$form['uid'] = array(
    '#type' => 'value',
    '#value' => $uid,
  );
	
	$session_id = (string)variable_get('essa_sid');
	$remarks_table = 'essa_'.$session_id.'_student_remarks';
	$remarks = db_query("
		SELECT * from {$remarks_table} where uid = :uid;", array(':uid' => $uid)
	);
	foreach($remarks as $remark){
		$row[] = array(
			'#tree' =>TRUE,
			$remark -> id => array(  //Generating unique array id for every form element
				'c1' => array(
					'#type' => 'markup',
					'#markup' => '<h3>'. $remark -> remarks .'</h3>',
				),
				'c2' =>array(
					'#type' => 'markup',
					'#markup' => '<h3>'.$remark -> remarks_by_emp_id.'</h3>',
				),
			),
		);		
	}
	
	if(isset($row)){
		$form['lts'] = array(
			'#theme' => 'remarks_table',
			'rows' => $row,
		);
	}
  
	$form['remarks'] = array(
		'#type' => 'textarea',
		'#title' => 'Remarks',
		'#required' => TRUE,
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	
	return $form;
}

/**
 *Implements submit function
 */
function remarks_form_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_master_table = 'essa_'.$session_id.'_master_student_table';
  $student_remarks_table = 'essa_'.$session_id.'_student_remarks';
	global $user;
	$today_date = strtotime(date('d-M-Y H:i:s'));
	
	$student = db_query("
		SELECT * from {$student_master_table} where uid = :uid;", array(':uid' => $form_state['values']['uid'])
	);
	foreach($student as $s){
    $adm_no = $s->adm_no;
  }
	db_insert($student_remarks_table)
	->fields(array(
		'adm_no' => $adm_no,
		'uid' => $form_state['values']['uid'],
		'remarks' => $form_state['values']['remarks'],
		'remarks_by_uid' => $user->uid,
		'remarks_by_emp_id' => $user->name,s
		'remarks_timestamp' => $today_date,
	))
	->execute();
}

/**
 *Theme function
 */
function theme_remarks_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Remarks'),t('By'));
  
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