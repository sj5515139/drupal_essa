<?php
/**
 *Implements page callback function each_leave_form.
 */
function edit_staff_leave($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	
  $form['emp_id'] = array(
		'#type' => 'textfield',
		'#title' => 'Enter Employee Id',
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'leave_types_ajax',
      'wrapper' => 'leave_types',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#autocomplete_path' => 'leave_staff/autocomplete',
	);
	
	$form['cnt'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "leave_types">',
		'#suffix' => '</div>',
	);
	
	$form['ltd'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "leave_types_detail">',
		'#suffix' => '</div>',
	);
	
	if(isset($form_state['values']['emp_id']) && $form_state['values']['emp_id'] != NULL){
		$option = array('--Select--');
		$leave_types = db_query("SELECT * FROM {$leave_staff_table} WHERE emp_id = :emp;", array(':emp' => $form_state['values']['emp_id']));
		foreach($leave_types as $lt){
			$default = NULL;
			if($lt->leave_status == '0'){
				$default = 1;
			}
			
			$row[$lt->leave_id] = array(
				'#tree' =>TRUE,
				$lt->leave_id => array(  //Generating unique array id for every form element 
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $lt->leave_id.'</h3>',
					),
					'c2' =>array(
						'#type' => 'checkbox',
						'#size' => '10',
						'#default_value' => $default,
					),
					'c3' =>array(
						'#type' => 'textfield',
						'#size' => '10',
						'#default_value' => $lt->total_leave,
					),
					'c4' =>array(
						'#type' => 'textfield',
						'#size' => '10',
						'#default_value' => $lt->max_per_month,
					),
					'c5' =>array(
						'#type' => 'textfield',
						'#size' => '10',
						'#default_value' => $lt->min_stretch,
					),
				),
			);
		}
		if(isset($row)){
			$form['cnt']['tab'] = array(
				'#theme' => 'staff_leave_table',
				'rows' => $row,
			);
			$form['cnt']['msg'] = array(
				'#type' => 'markup',
				'#markup' => '<h3><b>Note:- </b>By default all leaves are enabled for all employees. <b>"Mark"</b> the <b>Leave Status</b> Field to <b>remove</b> leave for the particular employee.</h3>',
			);
			$form['cnt']['save'] = array(
				'#type' => 'submit',
				'#value' => 'Save',
			);
		}else{
			$form['cnt']['msg'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 style = "color:red;">Enter a Valid Employee ID.</h3>',
			);
		}
	}
  return $form;
}

/*
** Implements submit function edit_staff_leave_submit()
*/
function edit_staff_leave_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	
	$emp_id = $form_state['values']['emp_id'];
	
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $leave_id=>$value){
				$staff_leave_taken = db_query("SELECT leave_taken FROM {$leave_staff_table} WHERE emp_id = :emp AND leave_id = :li;", array(':emp' => $emp_id, ':li' => $leave_id));
				foreach($staff_leave_taken as $slt){
					$leave_taken = $slt->leave_taken;
				}
				if($value['c2'] == 1){
					db_merge($leave_staff_table)
					->key(array('emp_id' => $emp_id, 'leave_id' => $leave_id))
					->fields(array(
						'leave_status' => '0',
					))
					->execute();
				}else{
					db_merge($leave_staff_table)
					->key(array('emp_id' => $emp_id, 'leave_id' => $leave_id))
					->fields(array(
						'leave_status' => NULL,
					))
					->execute();
				}
				// if($value['c3'] != NULL){
					// db_merge($leave_staff_table)
					// ->key(array('emp_id' => $emp_id, 'leave_id' => $leave_id))
					// ->fields(array(
						// 'total_leave' => (int)$value['c3'],
						// 'leave_remaining' => (int)$value['c3'] - $leave_taken,
					// ))
					// ->execute();
				// }
				// if($value['c4'] != NULL){
					// db_merge($leave_staff_table)
					// ->key(array('emp_id' => $emp_id, 'leave_id' => $leave_id))
					// ->fields(array(
						// 'max_per_month' => (int)$value['c4'],
					// ))
					// ->execute();
				// }
				// if($value['c5'] != NULL){
					// db_merge($leave_staff_table)
					// ->key(array('emp_id' => $emp_id, 'leave_id' => $leave_id))
					// ->fields(array(
						// 'min_stretch' => (int)$value['c5'],
					// ))
					// ->execute();
				// }
				
			}
		}
	}
	
	drupal_set_message('Leave details is successfully updated for Employee '.$emp_id.'.', 'status');
	
	//sending system alert
		$sys_alert_table = 'essa_'.$session_id.'_system_alert';
		global $user;
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
			'message' => 'Leave details is updated for Employee '.$emp_id.'.',
			'priority' => 'H',
			'module' => 'leave',
			'source_url' => 'admin/staff/leave/settings/edit_staff_leave',
			'timestamp' => $strtodate,
			'source_uid' => $user->uid,
		))
		->execute();
	
}

/*
** Implements ajax function leave_types_ajax()
*/
function leave_types_ajax($form, &$form_state){
	return $form['cnt'];
}

/*
**Theme callback for the form table.
*/ 
function theme_staff_leave_table(&$variables) {
	// Get the useful values.
	$form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Leave ID'), t('Leave Status'), t('Total Leave'),t('Max Per Month'),t('Min Per Month'));
	
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