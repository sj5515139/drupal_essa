<?php

function past_student_attendance($form, &$form_state){
  $session = variable_get('essa_sid');
	$staff_table = 'essa_'.$session.'_master_staff_table';
  global $user;
  
  $staff_db = db_query(
		"SELECT * from {$staff_table} where uid = :uid",  array(':uid' => $user->uid)
	);
	foreach($staff_db as $staff){
		$nickname = $staff->nickname;
	}
  
  $ct_table = 'essa_'.$session.'_class_teacher';
  $ct_db = db_query(
		"SELECT * from {$ct_table} where teacher_nickname = :nn", array(':nn' => $nickname)
	);
  
  foreach($ct_db as $ct){
		$class = $ct -> class.' '.$ct -> section;
  }
  
  $ct_table = 'essa_'.$session.'_class_teacher';
  $ct_db = db_query(
		"SELECT * from {$ct_table} where teacher_nickname = :nn", array(':nn' => $nickname)
	);
  
  foreach($ct_db as $ct){
		$class = $ct -> class.' '.$ct -> section;
    $class_id = $ct -> class.'_'.$ct -> section;
  }
  
  //dsm(date("d/m/Y"));
  //dsm(date("D")."day");
  $form['cls'] = array(
    '#type' => 'value',
    '#value' => $class_id,
  );
  
  $form['dt'] = array(
    '#type' => 'value',
    '#value' => date("Y/m/d"),
  );
  
  $form['ask_date'] = array(
	  '#type' => 'date_popup',
		'#title' => t('Select a Date'),
	  '#date_format' => 'Y-m-d',
	  '#required' => TRUE,
	  '#attributes' => array('placeholder' => 'Select a Date'),
		'#date_year_range' => '-1:+1',
		//'#default_value' => isset($academicyearend)? $academicyearend: NULL,
	);
  
  $form['holiday'] = array(
		'#type' => 'radios',
		'#options' => drupal_map_assoc(array('Mark as Holiday', 'Reset')),
		'#default_value' => 'Reset',
		'#validated' => TRUE,
	);
	
	$form['ins'] = array(
    '#markup' => '<h4>NOTE: By default, all students are treated as present. Please mark the students who are absent, along with the reason(if available).</h4>'
  );
	
	$form['cl'] = array(
    '#markup' => '<h1 id = "stu_att_title" style = "text-align: center;">Attendance - <b>'.strtoupper($class).'</b></h1>'
  );
	
	$form['r'] = array(
		'#type' => 'textarea',
		'#title' => 'Reason',
		'#states' => array(
			'visible' => array(
			  ':input[name = "holiday"]' => array('value' => 'Mark as Holiday'),
			),
		),
	);
  
	$st_table = 'essa_'.$session.'_master_student_table';
  $st_data = db_query(
		"SELECT * from {$st_table} where class = :class and section = :sec order by roll_no;",array(':class' => $ct->class, ':sec' => $ct->section)
	);
  foreach($st_data as $data){
		$row[] = array(
      '#tree' =>TRUE,
      $data -> adm_no => array(  //Generating unique array id for every form element
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$data -> adm_no.'</h3>',
        ),
        'c2' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$data -> roll_no.'</h3>',
        ),
        'c3' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$data -> first_name.' '.$data -> middle_name.' '. $data -> last_name.'</h3>',
        ),
        'c4' =>array(
          '#type' => 'checkbox',
        ),
        'c5' =>array(
          '#type' => 'textfield',
        ),
      ),
    );
  }
  
  if(!isset($row)){
    drupal_set_message('There are no Student in the class. Please ask school administrator to update student\'s records.', $type = 'error');
    $row = array();
  }
	
	$form['fs'] = array(
		'#type' => 'fieldset',
		'#states' => array(
			'visible' => array(
			  ':input[name = "holiday"]' => array('value' => 'Reset'),
			),
		),
	);
	
  $form['fs']['class'] = array(
    '#theme' => 'past_attendance_table',
    'rows' => $row,
  );
	
	$form['submit'] =array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
	
	return $form;
}

/**
 *Implements validate function
 */
function past_student_attendance_validate($form, &$form_state){
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
	
	if($req_day == 'Sun'){
		form_set_error('ask_date','You have selected a SUNDAY.');
	}
}

/**
 *Implements submit function
 */
function past_student_attendance_submit($form, &$form_state){
	if($form_state['values']['holiday'] == 'Mark as Holiday'){
		$ask_date = strtotime($form_state['values']['ask_date']);
		$req_date = date('Y_m_d',$ask_date);
		
		$session = variable_get('essa_sid');
		$attendance_table = 'essa_'.$session.'_'.$form_state['values']['cls'].'_attendance';
		$reason_table = 'essa_'.$session.'_attendance_reason';
		$st_table = 'essa_'.$session.'_master_student_table';
		
		$value = array();
		$value =  explode('_',$form_state['values']['cls']);
		$class = $value[0];
		$sec = $value[1];
		$req_date = date('Y_m_d');
		
		foreach($form_state['values'] as $val){
		  if(is_array($val)){
		    foreach($val as $k => $v){
		      $student_db = db_query(
		      	"SELECT * from {$st_table} where adm_no = :an and class = :class and section = :sec and status = 1;", array(':an' => $k, ':class' => $class, ':sec' => $sec)
		      );
		      foreach($student_db as $student){
		        $att_data = db_query(
		        	"SELECT * from {$attendance_table} where adm_no = :adm_no", array(':adm_no' => $k)
		        );
		        foreach($att_data as $data){
		          $id = $data->id;
		        }
		        db_merge($attendance_table)
		          ->key(array('adm_no' => $k))
		          ->fields (array(
		              'adm_no' => $k,
		              'roll_no' => $student->roll_no,
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
		  "SELECT * from {$reason_table} where date = :date and adm_no = :adm_no", array(':adm_no' => $k, ':date' => $req_date)
		);
	  foreach($reason_data as $rdata){
			$id = $rdata->id;
		}
		db_merge($reason_table)
		  ->key(array('id' => isset($id) ? $id : NULL))
		  ->fields (array(
		    'date' => $req_date,
		    'adm_no' => NULL,
		    'roll_no' => NULL,
	      'attendance' => 'h',
	      'reason' => $form_state['values']['r'],
		  )
		)
		->execute();  
		$form_state['rebuild'] = TRUE;	
	}else{
		$ask_date = strtotime($form_state['values']['ask_date']);
		$req_date = date('Y_m_d',$ask_date);
		
		$session = variable_get('essa_sid');
		$attendance_table = 'essa_'.$session.'_'.$form_state['values']['cls'].'_attendance';
		$reason_table = 'essa_'.$session.'_attendance_reason';
		$st_table = 'essa_'.$session.'_master_student_table';
		
		$value = array();
		$value =  explode('_',$form_state['values']['cls']);
		$class = $value[0];
		$sec = $value[1];
		foreach($form_state['values'] as $val){
		  if(is_array($val)){
		    foreach($val as $k => $v){
		      $student_db = db_query(
		      	"SELECT * from {$st_table} where adm_no = :an and class = :class and section = :sec and status = 1;", array(':an' => $k, ':class' => $class, ':sec' => $sec)
		      );
		      foreach($student_db as $student){
		        $att_data = db_query(
		        	"SELECT * from {$attendance_table} where adm_no = :adm_no", array(':adm_no' => $k)
		        );
		        foreach($att_data as $data){
		          $id = $data->id;
		        }
						if($v['c4'] != '1'){
							db_merge($attendance_table)
		          ->key(array('adm_no' => $k))
		          ->fields (array(
		              'adm_no' => $k,
		              'roll_no' => $student->roll_no,
		              $req_date => 'P',//date('Y_m_d')
		            )
		          )
		          ->execute();	
						}else{
							db_merge($attendance_table)
		          ->key(array('adm_no' => $k))
		          ->fields (array(
		              'adm_no' => $k,
		              'roll_no' => $student->roll_no,
		              $req_date => 'A',//date('Y_m_d')
		            )
		          )
		          ->execute();	
						}
							
						if($v['c5'] != NULL){
							$id = NULL;
		          $reason_data = db_query(
		          	"SELECT * from {$reason_table} where date = :date and adm_no = :adm_no", array(':adm_no' => $k, ':date' => $req_date)
		          );
		          foreach($reason_data as $rdata){
								$id = $rdata->id;
		          }
							db_merge($reason_table)
		            ->key(array('id' => isset($id) ? $id : NULL))
		            ->fields (array(
		              'date' => $req_date,
		              'adm_no' => $k,
		              'roll_no' => $student->roll_no,
		              'attendance' => 'A',
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
function theme_past_attendance_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Admission No'),t('Roll No'), t('Name'),t('Attendance'), t('Reason'));
  
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