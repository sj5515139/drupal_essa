<?php
/**
 *Implements page call back - staff_attendance_report
 */
function staff_attendance_report($form = array(), &$form_state){
  
  $session = variable_get('essa_sid');
	$bi_table = 'essa_'.$session.'_basicinfo';
  
  $bi_db = db_query(
		"SELECT * from {$bi_table}"
	);
	foreach($bi_db as $bi){
		$start_date = $bi->academicyearstart;
		$end_date = $bi->academicyearend;
	}
  $start    = new DateTime($start_date);
  $start->modify('first day of this month');
  $end      = new DateTime($end_date);
  $end->modify('first day of next month');
  $interval = DateInterval::createFromDateString('1 month');
  $period   = new DatePeriod($start, $interval, $end);
  foreach ($period as $dt) {
    $months[] = $dt->format("M-y");
  }
	
  $form['month'] = array(
    '#type' => 'select',
    '#title' => t('Select a month'),
    '#options' => drupal_map_assoc($months),
    '#required' => TRUE,
    '#ajax' => array(
      'event' => 'change',
      'callback' => 'staff_att_ajax',
      'wrapper' => 'wrapper',
      'method' => 'replace',
      'effect' => 'fade',
		),
  );
  
  $form['wrapper'] = array(
    '#prefix' => '<div id = "wrapper">',
    '#suffix' => '</div>',
  );
  
  return $form;
}

function staff_att_ajax($form, &$form_state){
	
	//******Suraj*****//	
	//removing notifications for attendance incharge
	$session = variable_get('essa_sid');
	$notification_table = 'essa_'.$session.'_notifications';
	global $user;
	$url = 'admin/staff/attendance/report';
	$notifications = db_query("SELECT * FROM {$notification_table} WHERE uid =:uid AND destination_url =:url;",array(':uid' => $user->uid, ':url' => $url));
	foreach($notifications as $notification){
		//dsm('ok');
		db_update($notification_table)
		->fields(array(
			'status' => '1',
		))
		->condition(db_and()
		->condition('uid', $user->uid)
		->condition('destination_url', $url))
		->execute();
	}
	//******Suraj*****//
	
	global $user;
	variable_set('leave_rep_mon'.$user->uid, "01-".$form_state['values']['month']);
	$start_date = "01-".$form_state['values']['month'];
	$start_time = strtotime($start_date);
	$end_time = strtotime(date('Y-m-t', strtotime($start_date)));
  for($i=$start_time; $i<=$end_time; $i+=86400){
    if(date('D', $i) != 'Sun'){
      $list[] = date('Y_m_d', $i);
    }
  }
	
  $session = variable_get('essa_sid');
	$attendance_table = 'essa_'.$session.'_'.'staff'.'_attendance';
	$staff_table = 'essa_'.$session.'_master_staff_table';
  $no_of_working_days = 0;
	$query = db_select($attendance_table, 'n');
	$query->fields('n', array('emp_id'));
	$results = $query->execute()->fetchAll();
	$count = count($results);
	foreach($list as $col){
    $student_att = db_query(
		  "SELECT emp_id, $col from {$attendance_table};"
		);
    foreach($student_att as $sa){
			if($sa->$col != NULL && $sa->$col != 'h'){
				$no_of_working_days = $no_of_working_days + 1;
				$dates[$col] = $col;
				$att[$sa->emp_id][$col] = $sa->$col;
			}
		}
	}
	foreach($att as $emp_id => $st){
		$no_of_days_present[$emp_id] = 0;
		foreach($dates as $dt){
			if($st[$dt] == 'P'){
				$no_of_days_present[$emp_id] = $no_of_days_present[$emp_id] + 1; 
			}
		}
	}
	
	$wd = $no_of_working_days/$count;
	foreach($no_of_days_present as $key=>$val){
		$avg_att[$key] = number_format((float) $val/$wd*100, 2, '.', '');
	}
	
  foreach($list as $col){
    $student_att = db_query(
		  "SELECT emp_id, $col from {$attendance_table};"
		);
    foreach($student_att as $sa){
			if($sa->$col == 'h'){
				$sa->$col = '';
			}
			$att_col[$sa->emp_id][$col] = array(
				'#type' => 'markup',
				'#markup' => '<h3>'.$sa->$col.'</h3>',
			);
    }
  }
  
	foreach($list as $col){
		$staff_data = db_query(
			"SELECT * from {$staff_table} where status = 1;"
		);
		
		foreach($staff_data as $sd){
			$staff_att = db_query(
			  "SELECT emp_id, $col from {$attendance_table} where emp_id = :ei;", array(':ei' => $sd->emp_id)
			);
			foreach($staff_att as $sa){
			  $row[$sa->emp_id] = array(
			    '#tree' =>TRUE,
			    $sa -> emp_id => array(  //Generating unique array id for every form element
			      'c1' =>array(
			        '#type' => 'markup',
			        '#markup' => '<h3>'.$sa->emp_id.'</h3>',
			      ),
						'no_of_days_present' => array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$no_of_days_present[$sa->emp_id].'</h3>',
						),
						'att_percent'  => array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$avg_att[$sa->emp_id].'</h3>',
						),
			    ),
			  );
			}  
		}
  }
  
	foreach($list as $col){
    $staff_data = db_query(
			"SELECT * from {$staff_table} where status = 1;"
		);
		
		foreach($staff_data as $sd){
			$staff_att = db_query(
			  "SELECT emp_id, $col from {$attendance_table} where emp_id = :ei;", array(':ei' => $sd->emp_id)
			);
			foreach($staff_att as $sa){
				$total_days[$sa->emp_id][$sa->emp_id] = array(
					'no_of_days_present' => array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$no_of_days_present[$sa->emp_id].'</h3>',
					),
				);
			}
		}
	}
	
  foreach($list as $col){
    $staff_data = db_query(
			"SELECT * from {$staff_table} where status = 1;"
		);
		
		foreach($staff_data as $sd){
			$staff_att = db_query(
			  "SELECT emp_id, $col from {$attendance_table} where emp_id = :ei;", array(':ei' => $sd->emp_id)
			);
			foreach($staff_att as $sa){
				$row[$sa->emp_id][$sa->emp_id][] =  $att_col[$sa->emp_id][$col];
			}
    }	
  }
	
	$form['staff'] = array(
    '#theme' => 'staff_att_table',
    'rows' => $row,
		'#prefix' => '<div id = "wrapper"><h4>Total no. of working days - '.$no_of_working_days/$count.'<h4>',
    '#suffix' => '</div>',
  );
  return $form['staff'];
}

/**
 * Theme callback for the form table.
 */
function theme_staff_att_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $head = array(t('Emp ID'),t('Present'),t('%'));
	
	global $user;
  $start_date = variable_get('leave_rep_mon'.$user->uid);
	$start_time = strtotime($start_date);
	$end_time = strtotime(date('Y-m-t', strtotime($start_date)));
  for($i=$start_time; $i<=$end_time; $i+=86400){
    if(date('D', $i) != 'Sun'){
      $list[] = date('d', $i);
    }
  }
  $session = variable_get('essa_sid');
	$attendance_table = 'essa_'.$session.'_'.'staff'.'_attendance';
  foreach($list as $col){
    $col_head[] = $col;
  }
  $header = array_merge($head, $col_head);
  
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