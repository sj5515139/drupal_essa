<?php
function display_leave($form, &$form_state, $uid){
	$session_id = (string)variable_get('essa_sid');
	$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
	$leave_staff_history_table = 'essa_'.$session_id.'_leave_staff_history';
  
	$form['uid'] = array(
		'#type' => 'value',
		'#value' => $uid,
	);
  
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Back',
		'#submit' => array('go_back'),
	);
  
	$form['save1'] = array(
		'#type' => 'submit',
		'#value' => 'Apply Leave',
		'#submit' => array('apply_leave'),
	);
	
	$form['save2'] = array(
		'#type' => 'submit',
		'#value' => 'My Application',
		'#submit' => array('application'),
	);
  
	$form['leave_summary'] = array(
		'#type' => 'markup',
		'#markup' => '<h1 style = "margin-top: 20px;">Leave Summary</h1>'
	);
  
	$staff = db_query("
		SELECT * from {$staff_master_table} where uid = :uid;", array(':uid' => $uid)
	);
	foreach($staff as $s){
		$emp_id = $s->emp_id;
	}
	$leave_detail = db_query("
		SELECT * from {$leave_staff_table} where emp_id = :emp_id;", array(':emp_id' => $emp_id)
	);
	$row = array();
	foreach($leave_detail as $leave){
		if($leave->leave_status != '0'){
			$row[$leave->leave_id] = array(
				'#tree' =>TRUE,
				$leave->leave_id => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => $leave->leave_id,
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->total_leave.'</h3>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->leave_taken.'</h3>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$leave->leave_remaining.'</h3>',
					),
				),
			);
		}
	}
  
	$bi_table = 'essa_'.$session_id.'_basicinfo';
	$bi_db = db_query(
		"SELECT * from {$bi_table}"
	);
	foreach($bi_db as $bi){
		$strDateFrom = $bi->academicyearstart;
		$strDateTo = $bi->academicyearend;
	}
	$start    = new DateTime($strDateFrom);
	$start->modify('first day of this month');
	$end      = new DateTime($strDateTo);
	$end->modify('first day of next month');
	$interval = DateInterval::createFromDateString('1 month');
	$period   = new DatePeriod($start, $interval, $end);
	$aryRange=array();
	foreach ($period as $dt) {
		array_push($aryRange,$dt->format("Y_m"));
	}
  
	$leave_detail = db_query("
		SELECT * from {$leave_staff_table} where emp_id = :emp_id;", array(':emp_id' => $emp_id)
	);
	foreach($leave_detail as $leave){
		if($leave->leave_status != '0'){
			foreach($aryRange as $dates){
				$col[$leave->leave_id][$dates] =  array(
					'#type' => 'markup',
					'#markup' => '<h3>'.$leave->$dates.'</h3>',
				);
			}
		}
	}
	$leave_detail = db_query("
		SELECT * from {$leave_staff_table} where emp_id = :emp_id;", array(':emp_id' => $emp_id)
	);
	foreach($leave_detail as $leave){
		if($leave->leave_status != '0'){
			foreach($aryRange as $dates){
				array_push($row[$leave->leave_id][$leave->leave_id],$col[$leave->leave_id][$dates]);
			}
		}
	}
  
	$form['leave summary'] = array(
		'#theme' => 'leave_display_theme_table',
		'rows' => $row,
	);
  
	$form['leave_history'] = array(
		'#type' => 'markup',
		'#markup' => '<h1 style = "margin-top: 20px;">Leave History</h1>'
	);
  
	$leave_detail = db_query("
		SELECT * from {$leave_staff_history_table} where emp_id = :emp_id order by req_timestamp desc;", array(':emp_id' => $emp_id)
	);
	$history_row = array();
	foreach($leave_detail as $leave){
		$history_row[$leave->req_timestamp] = array(
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
			),
		);
	}
  
	$form['leave history'] = array(
		'#theme' => 'leave_history_theme_table',
    	'rows' => $history_row,
	);
  return $form;
}

function go_back($form, &$form_state){
	//$current_path = current_path();
	global $base_url;
	$url = $base_url.'/user/'.$form_state['values']['uid'];
	$form_state['redirect'] = $url;
}

function apply_leave($form, &$form_state){
  //$current_path = current_path();
  global $base_url;
	$url = $base_url.'/user/'.$form_state['values']['uid'].'/leave#overlay=admin/staff/leave/apply_leave';
  $form_state['redirect'] = $url;
}

function application($form, &$form_state){
	//$current_path = current_path();
	global $base_url;
	$url = $base_url.'/user/'.$form_state['values']['uid'].'/leave#overlay=user/'.$form_state['values']['uid'].'/leave/application';
	$form_state['redirect'] = $url;
}

/**
 * Theme callback for the form table.
*/ 
function theme_leave_history_theme_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  
  $header = array(t('Leave ID'),t('Requested on'), t('No. of Days'),t('No. of working Days'), t('From Date'), t('To date'), t('Reason'), t('Status'), t('Status Moderator'), t('Remark Moderator'), t('Status Principal'), t('Remark Principal'));
  
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
 * Theme callback for the form table.
*/ 
function theme_leave_display_theme_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  
  $session_id = (string)variable_get('essa_sid');
  $bi_table = 'essa_'.$session_id.'_basicinfo';
  $bi_db = db_query(
		"SELECT * from {$bi_table}"
	);
  foreach($bi_db as $bi){
    $strDateFrom = $bi->academicyearstart;
    $strDateTo = $bi->academicyearend;
  }
  $start    = new DateTime($strDateFrom);
	$start->modify('first day of this month');
	$end      = new DateTime($strDateTo);
	$end->modify('first day of next month');
	$interval = DateInterval::createFromDateString('1 month');
	$period   = new DatePeriod($start, $interval, $end);
	$aryRange=array();
	foreach ($period as $dt) {
		array_push($aryRange,$dt->format("M-Y"));
	}
	
  $header = array(t('Leave ID'),t('Total Leave'), t('Leave Taken'),t('Leave Remaining'));
  $header = array_merge($header, $aryRange);
  
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