<?php
/*
** Implemnets callback function my_application()
*/
function my_application($form, &$form_state, $uid){
	$session_id = (string)variable_get('essa_sid');
	$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
	$leave_staff_history_table = 'essa_'.$session_id.'_leave_staff_history';
	
	$form['back'] = array(
		'#type' => 'markup',
		'#markup' => '<p class = "back_button"><a href="javascript:history.go(-1)">Back</a></p>',
	);
	
	$staff = db_query("
		SELECT * from {$staff_master_table} where uid = :uid;", array(':uid' => $uid)
	);
	foreach($staff as $s){
		$emp_id = $s->emp_id;
	}
	
	$leave_detail = db_query("
		SELECT * from {$leave_staff_history_table} where emp_id = :emp_id AND status = :s OR status = :st order by req_timestamp desc;", array(':emp_id' => $emp_id, ':s' => 'Pending with Principal', ':st' => 'Pending with Moderator')
	);
	$x = '<i class = "fa fa-pencil"></i>';
	$y = '<i class = "fa fa-times"></i>';
	
	//$application_row = array();
	foreach($leave_detail as $leave){
		if($leave->leave_moderator == NULL){
			$application_row[$leave->req_timestamp] = array(
				'#tree' =>TRUE,
				$leave->req_timestamp => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->leave_id.'</h3>',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.date('d-M-Y', $leave->req_timestamp).'</h3>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->no_of_days.'</h3>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->no_of_working_days.'</h3>',
					),
					'c5' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.date('d-M-Y', $leave->from_date).'</h3>',
					),
					'c6' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.date('d-M-Y', $leave->to_date).'</h3>',
					),
					'c7' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->reason.'</h3>',
					),
					'c8' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->status.'</h3>',
					),
					'c9' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->status_principal.'</h3>',
					),
					'c10' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->remark_principal.'</h3>',
					),
					'c11' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.l($x, 'user/'.$uid.'/leave/'.$emp_id.'%'.$leave->req_timestamp, array('html' => TRUE)).'</h3>',
					),
					'c12' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.l($y, 'user/'.$uid.'/leave/delete/'.$emp_id.'%'.$leave->req_timestamp, array('html' => TRUE)).'</h3>',
					),
				),
			);
			
			variable_set('moderator_flag'.$uid, 1);
		}else{
			$application_row[$leave->req_timestamp] = array(
				'#tree' =>TRUE,
				$leave->req_timestamp => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->leave_id.'</h3>',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.date('d-M-Y', $leave->req_timestamp).'</h3>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->no_of_days.'</h3>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->no_of_working_days.'</h3>',
					),
					'c5' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.date('d-M-Y', $leave->from_date).'</h3>',
					),
					'c6' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.date('d-M-Y', $leave->to_date).'</h3>',
					),
					'c7' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->reason.'</h3>',
					),
					'c8' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->status.'</h3>',
					),
					'c9' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->status_moderator.'</h3>',
					),
					'c10' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->remark_moderator.'</h3>',
					),
					'c11' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->status_principal.'</h3>',
					),
					'c12' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->remark_principal.'</h3>',
					),
					'c13' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.l($x, 'user/'.$uid.'/leave/'.$emp_id.'%'.$leave->req_timestamp, array('html' => TRUE)).'</h3>',
					),
					'c14' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.l($y, 'user/'.$uid.'/leave/delete/'.$emp_id.'%'.$leave->req_timestamp, array('html' => TRUE)).'</h3>',
					),
				),
			);
		}
	}
	
	if(isset($application_row)){
	
		$form['leave application'] = array(
			'#theme' => 'leave_application_table',
			'rows' => $application_row,
		);
		$form['msg'] = array(
			'#type' => 'markup',
			'#markup' => '<h3>'.$x.' - Edit Application,&nbsp;&nbsp;'.$y.' - Delete/Cancel Application.</h3>',
		);
	}else{
		$form['msg'] = array(
			'#type' => 'markup',
			'#markup' => '<h3 style = "color:Red;">There are no leave application.</h3>',
		);
	}
	return $form;
}
/*
**Theme callback for the form table.
*/ 
function theme_leave_application_table(&$variables) {
	// Get the useful values.
	$form = $variables['form'];
	$rows = $form['rows'];
	global $user;
	$moderator = 0;
	if(variable_get('moderator_flag'.$user->uid) == 1){
		$moderator = 1;
	}

	if($moderator != 1){
		$header = array(t('Leave ID'),t('Requested on'), t('No. of Days'),t('No. of working Days'), t('From Date'), t('To date'), t('Reason'), t('Status'), t('Status Principal'), t('Remark Principal'), t(''), t(''), t(''), t(''));
	}else{
		$header = array(t('Leave ID'),t('Requested on'), t('No. of Days'),t('No. of working Days'), t('From Date'), t('To date'), t('Reason'), t('Status'), t('Status Moderator'), t('Remark Moderator'), t('Status Principal'), t('Remark Principal'),t(''), t(''));
	}
	
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