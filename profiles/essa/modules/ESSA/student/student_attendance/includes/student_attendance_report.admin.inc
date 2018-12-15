<?php

/**
 *Implements pagecallback function - student_attendance_report_form
 */
function student_attendance_report_form($form = array(), &$form_state, $class, $sec){
	
	global $user;
	variable_set('att_report_month'.$user->uid, NULL);

  $session = variable_get('essa_sid');
	$bi_table = 'essa_'.$session.'_basicinfo';
  
  $form['cls'] = array(
    '#type' => 'value',
    '#value' => $class.'_'.$sec,
  );
  
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
      'callback' => 'student_att_ajax',
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

/**
 * Theme callback for the form table.
 */
function theme_st_att_table(&$variables) {
  // Get the useful values.
	global $user;
	$form = $variables['form'];
  $rows = $form['rows'];
  $head = array(t('Roll No.'),t('Present'),t('%'));
  $strDateFrom = "01-".variable_get('att_report_month'.$user->uid);
  $start_time = strtotime($strDateFrom);
  $end_time = strtotime("+1 month", $start_time);
  for($i=$start_time; $i<$end_time; $i+=86400){
    if(date('D', $i) != 'Sun'){
      $list[] = date('d', $i);
    }
  }
  $session = variable_get('essa_sid');
	$attendance_table = 'essa_'.$session.'_'.$form_state['values']['cls'].'_attendance';
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

function student_att_ajax($form, &$form_state){
	//dsm($form_state['values']['cls']);
	global $user;
	variable_set('att_report_month'.$user->uid, $form_state['values']['month']);
	//******Suraj*****//
	//removing notification for principal
	$session = variable_get('essa_sid');
	$cs = explode('_',$form_state['values']['cls']);
	$notification_table = 'essa_'.$session.'_notifications';
	global $user;
	$url = 'admin/students/attendance/report/'.$cs[0].'/'.$cs[1];
	$notifications = db_query("SELECT * FROM {$notification_table} WHERE destination_url =:url;",array(':url' => $url));
	foreach($notifications as $notification){
		//dsm('ok');
		db_update($notification_table)
		->fields(array(
			'status' => '1',
		))
		->condition(db_and()
		->condition('uid', $user->uid))
		->execute();
	}
	//******Suraj*****//
	
	$start_date = "01-".$form_state['values']['month'];
	$start_time = strtotime($start_date);
	$end_time = strtotime("+1 month", $start_time);
  for($i=$start_time; $i<$end_time; $i+=86400){
    if(date('D', $i) != 'Sun'){
      $list[] = date('Y_m_d', $i);
    }
  }
  
  $session = variable_get('essa_sid');
	$attendance_table = 'essa_'.$session.'_'.$form_state['values']['cls'].'_attendance';
  $no_of_working_days = 0;
	$query = db_select($attendance_table, 'n');
	$query->fields('n', array('adm_no'));
	$results = $query->execute()->fetchAll();
	$count = count($results);
	foreach($list as $col){
    $student_att = db_query(
		  "SELECT adm_no, $col from {$attendance_table};"
		);
    foreach($student_att as $sa){
			if($sa->$col != NULL && $sa->$col != 'h'){
				$no_of_working_days = $no_of_working_days + 1;
				$dates[$col] = $col;
				$att[$sa->adm_no][$col] = $sa->$col;
			}
		}
	}
	foreach($att as $adm_no => $st){
		$no_of_days_present[$adm_no] = 0;
		foreach($dates as $dt){
			if($st[$dt] == 'P'){
				$no_of_days_present[$adm_no] = $no_of_days_present[$adm_no] + 1; 
			}
		}
	}
	
	$wd = $no_of_working_days/$count;
	foreach($no_of_days_present as $key=>$val){
		$avg_att[$key] = number_format((float) $val/$wd*100, 2, '.', '');
	}
	
  foreach($list as $col){
    $student_att = db_query(
		  "SELECT adm_no, $col from {$attendance_table};"
		);
    foreach($student_att as $sa){
			if($sa->$col == 'h'){
				$sa->$col = '';
			}
			$att_col[$sa->adm_no][$col] = array(
				'#type' => 'markup',
				'#markup' => '<h3>'.$sa->$col.'</h3>',
			);
    }
  }
  
	
	foreach($list as $col){
    $student_att = db_query(
		  "SELECT roll_no, adm_no, $col from {$attendance_table} ORDER BY roll_no;"
		);
    foreach($student_att as $sa){
      $row[$sa->adm_no] = array(
        '#tree' =>TRUE,
        $sa -> adm_no => array(  //Generating unique array id for every form element
          'c1' =>array(
            '#type' => 'markup',
            '#markup' => '<h3>'.$sa->roll_no.'</h3>',
          ),
					'no_of_days_present' => array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$no_of_days_present[$sa->adm_no].'</h3>',
					),
					'att_percent'  => array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$avg_att[$sa->adm_no].'</h3>',
					),
        ),
      );
    }  
  }
  
	foreach($list as $col){
    $student_att = db_query(
		  "SELECT adm_no, $col from {$attendance_table};"
		);
    foreach($student_att as $sa){
			$total_days[$sa->adm_no][$sa->adm_no] = array(
				'no_of_days_present' => array(
					'#type' => 'markup',
					'#markup' => '<h3>'.$no_of_days_present[$sa->adm_no].'</h3>',
				),
			);
		}
	}
	
  foreach($list as $col){
    $student_att = db_query(
		  "SELECT roll_no, adm_no, $col from {$attendance_table};"
		);
    foreach($student_att as $sa){
	    $row[$sa->adm_no][$sa->adm_no][] =  $att_col[$sa->adm_no][$col];
    }
  }
	
	$form['class'] = array(
    '#theme' => 'st_att_table',
    'rows' => $row,
		'#prefix' => '<div id = "wrapper"><h4>Total no. of working days - '.$no_of_working_days/$count.'<h4>',
    '#suffix' => '</div>',
  );
  return $form['class'];
}
  /*
  $form['fs1'] = array(
    '#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
  );
  $form['fs1']['from_date'] = array(
    '#type' => 'date_popup',
		'#title' => t('From Date'),
	  '#date_format' => 'd/m/Y',
	  '#required' => TRUE,
		'#attributes' => array('placeholder' => 'From'),
		'#default_value' => isset($academicyearend)? $academicyearend: NULL,
    '#default_value' => date('d-m-Y'),
  );
  
  $form['fs1']['to_date'] = array(
    '#type' => 'date_popup',
		'#title' => t('To Date'),
	  '#date_format' => 'd/m/Y',
	  '#required' => TRUE,
		'#attributes' => array('placeholder' => 'To'),
		'#default_value' => isset($academicyearend)? $academicyearend: NULL,
    '#default_value' => date('d-m-Y'),
  );
  
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
	
  $form['fs2'] = array(
    '#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
  );
  
  $form['fs2']['month'] = array(
    '#type' => 'select',
    '#title' => t('Select a month'),
    '#options' => drupal_map_assoc($months),
  );
  
  $form['fs3'] = array(
    '#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
  );
  $form['fs3']['adm_no'] = array(
    '#type' => 'textfield',
    '#title' => 'Select a Student',
    '#size' => 25,
    '#autocomplete_path' => 'att_adm_no/autocomplete',
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Go',
    '#ajax' => array(
      'event' => 'click',
      'callback' => 'student_att_ajax',
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

function student_att_ajax($form, &$form_state){
  
}*/