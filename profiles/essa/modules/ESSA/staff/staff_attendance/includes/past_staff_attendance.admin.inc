<?php
function past_staff_attendance($form, &$form_state){
	
	$session = variable_get('essa_sid');
	$staff_table = 'essa_'.$session.'_master_staff_table';
  
  $form['dt'] = array(
    '#type' => 'value',
    '#value' => date("Y/m/d"),
  );
  
	$form['ins'] = array(
    '#markup' => '<h4>NOTE: By default, all staffs are treated as present. Please mark the staffs who are absent, along with the reason(if available).</h4>'
  );
	
	$form['date'] = array(
    '#markup' => '<h1 id = "sta_att_title" style = "text-align: center;">Attendance - <b>'.'</b><b><i>'.'Staff'.'</sup> '.'</i></b></h1>'
  );
	
  $form['ask_date'] = array(
	  '#type' => 'date_popup',
		'#title' => t('Select a Date'),
	  '#date_format' => 'Y-m-d',
	  '#required' => TRUE,
	  '#attributes' => array('placeholder' => 'Select a Date'),
		'#date_year_range' => '-1:+1',
		'#ajax' => array(
      'event' => 'change',
      'callback' => 'past_staff_att_ajax',
      'wrapper' => 'past_staff_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
		),
	);
	
	$form['past_staff_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "past_staff_wrapper">',
		'#suffix' => '</div>',
	);
  
	if(isset($form_state['values']['ask_date'])){
		$staff_data = db_query(
			"SELECT * from {$staff_table} where status = 1;"
		);
		foreach($staff_data as $data){
		  $row[] = array(
		    '#tree' =>TRUE,
		    $data -> emp_id => array(  //Generating unique array id for every form element
		      'c1' =>array(
		        '#type' => 'markup',
		        '#markup' => '<h3>'.$data -> emp_id.'</h3>',
		      ),
		      'c2' =>array(
		        '#type' => 'markup',
		        '#markup' => '<h3>'.$data -> fname.' '. $data -> lname.'</h3>',
		      ),
		      'c3' =>array(
		        '#type' => 'checkbox',
		      ),
		      'c4' =>array(
		        '#type' => 'textfield',
		      ),
		    ),
		  );
		}
		if(!isset($row)){
		  drupal_set_message('There are no Student in the class. Please ask school administrator to update student\'s records.', $type = 'error');
		  $row = array();
		}
		
		//Calling the theme function to build the custom table and display the form in tabular format.
		$form['fs'] = array(
			'#type' => 'container',
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
			'#states' => array(
				'invisible' => array(
				  ':input[name = "holiday"]' => array('value' => 'Mark as Holiday'),
				),
			),
		);
		
		$form['fs']['holiday'] = array(
			'#type' => 'radios',
			'#options' => drupal_map_assoc(array('Mark as Holiday', 'Reset')),
			'#default_value' => '<p id = "na">NA</p>',
			'#validated' => TRUE,
		);
	
		$form['fs']['r'] = array(
			'#type' => 'textarea',
			'#title' => 'Reason',
			'#states' => array(
				'visible' => array(
				  ':input[name = "holiday"]' => array('value' => 'Mark as Holiday'),
				),
			),
		);
		
		$form['fs']['staff'] = array(
		  '#theme' => 'staff_attendance_table',
		  'rows' => $row,
		);
		
		$form['fs']['submit'] =array(
		  '#type' => 'submit',
		  '#value' => t('Save'),
		);
	}
  
	return $form;
}

function past_staff_att_ajax($form, &$form_state){
	return $form['fs'];
}

/**
 *Implements validate function
 */
function past_staff_attendance_validate($form, &$form_state){
	$session = variable_get('essa_sid');
	$bi_table = 'essa_'.$session.'_basicinfo';
  
  $bi_db = db_query(
		"SELECT * from {$bi_table}"
	);
	foreach($bi_db as $bi){
		$start_date = $bi->academicyearstart;
		$end_date = $bi->academicyearend;
	}
	$ask_date = strtotime($form_state['values']['ask_date']);
	$req_date = date('Y-m-d',$ask_date);
	$req_day = date('D',$ask_date);
	if($req_date < $start_date){
		form_set_error('ask_date','The date in <b>not in the range</b> of academic year start and end date. Please contact system administrator in case you need assistance.');
	}
	if($req_date > $end_date){
		form_set_error('ask_date','The date in <b>not in the range</b> of academic year start and end date. Please contact system administrator in case you need assistance.');
	}
	
	if($req_date > date('Y-m-d')){
		form_set_error('ask_date','You can\'t take attendance of future date.');
	}
	
	if($req_day == 'Sun'){
		form_set_error('ask_date','You have selected a SUNDAY.');
	}
}

/**
 *Implements submit function
 */
function past_staff_attendance_submit($form, &$form_state){
  //dsm($form_state);
  $ask_date = strtotime($form_state['values']['ask_date']);
	$req_date = date('Y_m_d',$ask_date);
	if($form_state['values']['holiday'] == 'Mark as Holiday'){
    $session = variable_get('essa_sid');
		$attendance_table = 'essa_'.$session.'_staff_attendance';
		$reason_table = 'essa_'.$session.'_staff_attendance_reason';
		$staff_table = 'essa_'.$session.'_'.'master_staff_table';
		foreach($form_state['values'] as $val){
		  if(is_array($val)){
		    foreach($val as $k => $v){
		      $student_db = db_query(
		      	"SELECT * from {$staff_table} where emp_id = :an", array(':an' => $k)
		      );
		      foreach($student_db as $student){
		        $att_data = db_query(
		        	"SELECT * from {$attendance_table} where emp_id = :emp_id", array(':emp_id' => $k)
		        );
		        foreach($att_data as $data){
		          $id = $data->id;
		        }
		        db_merge($attendance_table)
		          ->key(array('id' => isset($id) ? $id : NULL))
		          ->fields (array(
		              'emp_id' => $k,
		              $req_date => 'h',//date('Y_m_d')
		            )
		          )
		          ->execute();
		      }
		    }
		  }
		}
    $id = NULL;
		$reason_data = db_query(
		  "SELECT * from {$reason_table} where date = :date and emp_id = :emp_id", array(':emp_id' => $k, ':date' => date('Y_m_d'))
		);
	  foreach($reason_data as $rdata){
			$id = $rdata->id;
		}
		db_merge($reason_table)
		  ->key(array('id' => isset($id) ? $id : NULL))
		  ->fields (array(
		    'date' => date('Y_m_d'),
		    'emp_id' => NULL,
		    'attendance' => 'h',
	      'reason' => $form_state['values']['r'],
		  )
		)
		->execute();  
		$form_state['rebuild'] = TRUE;
	}else{
		$session = variable_get('essa_sid');
		$attendance_table = 'essa_'.$session.'_staff_attendance';
		$reason_table = 'essa_'.$session.'_staff_attendance_reason';
		$staff_table = 'essa_'.$session.'_'.'master_staff_table';
		foreach($form_state['values'] as $val){
		  if(is_array($val)){
		    foreach($val as $k => $v){
		      $student_db = db_query(
		      	"SELECT * from {$staff_table} where emp_id = :an", array(':an' => $k)
		      );
		      foreach($student_db as $student){
		        $att_data = db_query(
		        	"SELECT * from {$attendance_table} where emp_id = :emp_id", array(':emp_id' => $k)
		        );
		        foreach($att_data as $data){
		          $id = $data->id;
		        }
		        if($v['c3'] != '1'){
							db_merge($attendance_table)
		          ->key(array('emp_id' => $k))
		          ->fields (array(
		              'emp_id' => $k,
		              $req_date => 'P',//date('Y_m_d')
		            )
		          )
		          ->execute();	
						}else{
							db_merge($attendance_table)
		          ->key(array('emp_id' => $k))
		          ->fields (array(
		              'emp_id' => $k,
		              $req_date => 'A',//date('Y_m_d')
		            )
		          )
		          ->execute();	
						}
		        if($v['c4'] != NULL){
		          $reason_data = db_query(
		          	"SELECT * from {$reason_table} where date = :date and emp_id = :emp_id", array(':emp_id' => $k, ':date' => date('Y_m_d'))//date('Y_m_d')
		          );
		          foreach($reason_data as $rdata){
		            $id = $rdata->id;
		          }
		          db_merge($reason_table)
		            ->key(array('id' => isset($id) ? $id : NULL))
		            ->fields (array(
		              'date' => date('Y_m_d'),
		              'emp_id' => $k,
		              'attendance' => $v['c4'],
		              'reason' => $v['c5'],
		            )
		          )
		          ->execute();  
		        }
		      }
		    }
		  }
		}
	}
}

/**
 * Theme callback for the form table.
 */
function theme_staff_attendance_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Emp ID'), t('Name'),t('Attendance'), t('Reason'));
  
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


