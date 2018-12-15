<?php

/**
 *Implements page callback function fee_structure.
 */
function fee_structure($form, &$form_state){
	
	$form = array();
  $session_id = (string)variable_get('essa_sid');
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$freq_table = 'essa_'.$session_id.'_fees_frequency';
	
	$form['instructions'] = array(
    '#type' => 'markup',
    '#markup' => '<h2>***<strong>Instruction:</strong> First create frequency in which you collect fee. Thereafter, create fees..</h2>'
	);
	
	$columns = array('--SELECT--');
	$session = (string)variable_get('essa_sid');
	$basic_info_table = 'essa_'.$session.'_basicinfo';
	$binfo = db_query("
    SELECT * from {$basic_info_table};
  ");
	foreach($binfo as $info){
		$start_date = $info->academicyearstart;
		$end_date = $info->academicyearend;
	}
  $start = new DateTime($start_date);
	$start->modify('first day of this month');
	$end      = new DateTime($end_date);
	$end->modify('first day of next month');
	$interval = DateInterval::createFromDateString('1 month');
	$period   = new DatePeriod($start, $interval, $end);
	foreach ($period as $dt) {
		$columns[] = $dt->format("M_Y");
	}
	
	$x = '<i class = "fa fa-pencil"></i>';
  $y = '<i class = "fa fa-calculator"></i>';
	$fees = db_query("
    SELECT * from {$fees_table};
  ");
  foreach($fees as $fee){
		$amount = number_format((float)$fee->amount,2,'.',',');	
		$opsub = ($fee -> optional_sub != NULL)? $fee -> optional_sub: ' - ';
		$flag = variable_get('fee_flag');
		
		$date = strtotime(date('d-m-Y'));
		$col = date('M_Y');
		
		$frequency = db_query("
		  SELECT * from {$freq_table} where freq_id = :fi;", array(':fi' => $fee->freq_id)
		);
		foreach($frequency as $freq){
			if($freq->$col < $date){
				$nxt_deadline = date('d', $freq->$col).'-'.date('M-Y', strtotime('+1 month'));
			}else{
				$nxt_deadline = date('d-M-Y', $freq->$col);
			}
		}
		//dsm($flag);
		if($flag == 1){
			$row[] = array(
				'#tree' =>TRUE,
				$fee -> fee_id => array(  //Generating unique array id for every form element
					'c1' =>array(
					  '#type' => 'markup',
					  '#markup' => '<h3>'. $fee -> fee_id .'</h3>',
					),
					'c2' =>array(
					  '#type' => 'markup',
					  '#markup' => '<h3>'. $fee -> frequency .'</h3>',
					),
					'c3' =>array(
					  '#type' => 'markup',
					  '#markup' => '<h3>'.$fee -> particulars.'</h3>',
					),
					'c4' =>array(
					  '#type' => 'markup',
					  '#markup' => '<h3>'.$amount.'</h3>',
					),
					'c5' =>array(
					  '#type' => 'markup',
						'#markup' => '<h3>'.$nxt_deadline.'</h3>',
					),
					'c6' =>array(
					  '#type' => 'markup',
					  '#markup' => '<h3>'.$fee -> applies_to.'</h3>',
					),
					'c7' =>array(
					  '#type' => 'markup',
					  '#markup' => '<h3>'.$fee -> class_from.' - '.$fee -> class_to.'</h3>',
					),
					'c8' =>array(
					  '#type' => 'markup',
					  '#markup' => '<h3>'.$opsub.'</h3>',
					),
					'c9' =>array(
					  '#type' => 'markup',
					  '#markup' => '<h3>'.$fee -> distance_from.' - '.$fee -> distance_to.'</h3>',
					),
					'c10' =>array(
					  '#type' => 'select',
						'#options' => drupal_map_assoc($columns),
					),
			    $fee -> fee_id =>array(
			      '#type' => 'submit',
			      '#submit' => array('delete_fee'),
			      '#value' => 'Delete',
						'#name' => $fee->fee_id,
			      '#prefix' => '<div id = "delete_fee">',
			      '#suffix' => '</div>',
			    ),
			  ),
			);
		}/*
		 else{
			$row[] = array(
			  '#tree' =>TRUE,
			  $fee -> fee_id => array(  //Generating unique array id for every form element
			    'c1' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'. $fee -> fee_id .'</h3>',
			    ),
			    'c2' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'. $fee -> frequency .'</h3>',
			    ),
			    'c3' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.$fee -> particulars.'</h3>',
			    ),
			    'c4' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.$amount.'</h3>',
			    ),
					'c5' =>array(
			      '#type' => 'markup',
						//'#markup' => '<h3>'.$nxt_deadline.'</h3>',
			    ),
			    'c6' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.$fee -> applies_to.'</h3>',
			    ),
			    'c7' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.$fee -> class_from.' - '.$fee -> class_to.'</h3>',
			    ),
			    'c8' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.$opsub.'</h3>',
			    ),
			    'c9' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.$fee -> distance_from.' - '.$fee -> distance_to.'</h3>',
			    ),
			    'c10' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.l($x, 'admin/accounts/fees/fee_structure/list/'.$fee->fee_id, array('html' => TRUE)).'</h3>',
			    ),
			    $fee -> fee_id =>array(
			      '#type' => 'submit',
			      '#submit' => array('delete_fee'),
			      '#value' => 'Delete',
						'#name' => $fee->fee_id,
			      '#prefix' => '<div id = "delete_fee">',
			      '#suffix' => '</div>',
			    ),
			  ),
			);
		}
		*/
	}
	
	if(!isset($row)){
    drupal_set_message('No Fees created yet. Please create Fees.', $type = 'error');
    $row = array();
  }
	
	//Calling the theme function to build the custom table and display the form in tabular format.
  $form['lts'] = array(
    '#theme' => 'fee_table',
    'rows' => $row,
  );
	$form['note'] = array(
    '#type' => 'markup',
    '#markup' => '<h2>***<strong>NOTE:</strong>The fee types that has payment information can\'t be deleted.</h2>'
	);
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => t('Save Fee Structure'),
		'#submit' => array('save_fee_structure'),
	);
	
	
  /*
  $form['help'] = array(
    '#type' => 'markup',
    '#markup' => '<h3 id = "essa_fees_warning">NOTE: Set the Fee Structure Carefully. You cannot change it after you start taking payments.</h3><h4 id = "edit_fee">'.$x.' = Edit Fee</h4><h4>'.$y.' = Edit Due Date </h4>'
  );
	*/
  return $form;
}

function save_fee_structure(){
	variable_set('fee_flag',1);
	$session_id = (string)variable_get('essa_sid');
  $fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_freq = 'essa_'.$session_id.'_fees_frequency';
	$session = (string)variable_get('essa_sid');
	$basic_info_table = 'essa_'.$session.'_basicinfo';
	$binfo = db_query("
    SELECT * from {$basic_info_table};
  ");
	foreach($binfo as $info){
		$start_date = $info->academicyearstart;
		$end_date = $info->academicyearend;
	}
  $start = new DateTime($start_date);
	$start->modify('first day of this month');
	$end      = new DateTime($end_date);
	$end->modify('first day of next month');
	$interval = DateInterval::createFromDateString('1 month');
	$period   = new DatePeriod($start, $interval, $end);
	foreach ($period as $dt) {
		$csvs[] = $dt->format("M-Y");
		$columns[] = $dt->format("M_Y");
	}
	
	foreach($columns as $col){
		$csv = '';
		$data = array('Admn no.');
		$freq = db_query("
		  SELECT * from {$fees_freq} where $col = $col;"
		);
		foreach($freq as $fr){
			if($fr->$col != NULL){
				$fees = db_query("
				  SELECT * from {$fees_table} where freq_id = :fri;", array(':fri' => $fr->freq_id)
				);
				
				foreach($fees as $fee){
					if(!in_array($fee->particulars, $data)){
						$data[] = $fee->particulars;
					}
				}
			}
		}
		$data = array_merge($data, array('Fine(If any)'));
		$data = array_merge($data, array('Fine Amount Paid'));
		//$data = array_merge($data, array('Fine Paid'));
		$data = array_merge($data, array('Payment Date(dd-mm-yyyy)'));
		$count = count($data);
		foreach ($data as $record){
		  $csv.= $record.',';
		}
		if(file_exists ('public://fees/'.$col)){
			unlink('public://fees/'.$col.'.csv');
		}
		$csv_handler = fopen ('public://fees/'.$col.'.csv','w');
		fwrite ($csv_handler, $csv);
		fclose($csv_handler);
	}
	drupal_cron_run();
}

function delete_fee($form, &$form_state){
	global $user;
	$session_id = (string)variable_get('essa_sid');
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$payment_check = NULL;
	
	$fees = db_query("
		SELECT * from {$fees_student_payment} where fee_id = :fee_id;", array(':fee_id' => $form_state['triggering_element']['#name'])
	);
	foreach($fees as $fee){
		$payment_check = $fee->fee_id;
	}
	
	if($payment_check === NULL){
		variable_set('delete-fee_id'.$user->uid, $form_state['triggering_element']['#name']);
		$url = url('delete-fee-structure', array('absolute' => TRUE));
		$form_state['redirect'] = $url;
	}else{
		variable_set('delete-fee_id'.$user->uid, $form_state['triggering_element']['#name']);
		$url = url('delete-fee-structure-pay', array('absolute' => TRUE));
		$form_state['redirect'] = $url;
		foreach($form_state['values'] as $val){
			if(is_array($val)){
				foreach($val as $k => $v){
					if($k == $form_state['triggering_element']['#name']){
						variable_set('delete-fee_id-mon'.$user->uid, $v['c10']);
					}
				}
			}
		}
	}
}

function delete_fee_type_pagecallback(){
	return drupal_get_form('delete_fee_type_confirm');
}

function delete_fee_type_confirm($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	
	$heading = t('Are you sure to delete this collection.');
	$caption = '<h3>This action can\'t be undone. After deletion, this fee will be removed from all student\'s account.</h3>';
	
	$cancel_path = 'admin/fees/fee_structure';
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

function delete_fee_type_confirm_submit($form, &$form_state){
	global $user;
	$session_id = (string)variable_get('essa_sid');
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student = 'essa_'.$session_id.'_fees_student';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fee_id = variable_get('delete-fee_id'.$user->uid);
	db_delete($fees_table)
		->condition('fee_id', $fee_id)
		->execute();
		
	db_delete($fees_student)
		->condition('fee_id', $fee_id)
		->execute();
		
	db_delete($fees_student_due)
		->condition('fee_id', $fee_id)
		->execute();
	
	$url = url('admin/fees/fee_structure', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
	//drupal_set_message('The fees was deleted & removed from all student\'s account.');
}

function delete_fee_pay_type_pagecallback(){
	return drupal_get_form('delete_fee_pay_type_confirm');
}

function delete_fee_pay_type_confirm($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	
	$heading = t('Are you sure to delete this collection.');
	$caption = '<h3>This action can\'t be undone. After deletion, this fee will be removed from all student\'s account. However, payment information will remain intact. Any future due will be nullified.</h3>';
	
	$cancel_path = 'admin/fees/fee_structure';
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

function delete_fee_pay_type_confirm_submit($form, &$form_state){
	global $user;
	$session_id = (string)variable_get('essa_sid');
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student = 'essa_'.$session_id.'_fees_student';
	$fees_frequency = 'essa_'.$session_id.'_fees_frequency';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$student_due_table = 'essa_'.$session_id.'_fees_student_due';
	$fee_id = variable_get('delete-fee_id'.$user->uid);
	$mon = variable_get('delete-fee_id-mon'.$user->uid);
	
	$fees = db_query("
		SELECT * from {$fees_table} where fee_id = :fee_id;", array(':fee_id' => $fee_id)
	);
	foreach($fees as $fee){
		$particulars = $fee->particulars;
		$rename = $fee->particulars.'(deleted - '.$mon.')';
	}
	
	db_update($fees_table) // Table name no longer needs {}
		->fields(array(
			'particulars' => $rename,
		))
	-> condition('fee_id', $fee_id, '=')
	->execute();
	
	$fee_freq = db_query("
		SELECT * from {$fees_table} where fee_id = :fi", array(':fi' => $fee_id)
	);
	foreach($fee_freq as $ff){
		$freq_id = $ff->freq_id;
	}
	
	$session = (string)variable_get('essa_sid');
	$basic_info_table = 'essa_'.$session.'_basicinfo';
	$binfo = db_query("
    SELECT * from {$basic_info_table};
  ");
	foreach($binfo as $info){
		$end_date = $info->academicyearend;
	}
	
	$del_mon = str_replace('_', '-', $mon);
	$start_date = date('d-m-Y', strtotime($del_mon));
  $start = new DateTime($start_date);
	$start->modify('first day of this month');
	$end      = new DateTime($end_date);
	$end->modify('first day of next month');
	$interval = DateInterval::createFromDateString('1 month');
	$period   = new DatePeriod($start, $interval, $end);
	foreach ($period as $dt) {
		$columns[] = $dt->format("M_Y");
	}
	
	$results = db_select($fees_frequency, 'n')
		->fields('n')
		->condition('freq_id', $freq_id, '=')
		->execute();
	$freq = $results->fetchAssoc();
	unset($freq['freq_id']);
	unset($freq['freq_name']);
	foreach($freq as $key => $val){
		if($val != NULL){
			$months[$key] = $key;
		}
	}
	$mons = array_intersect($columns, $months);
	
	foreach($mons as $col){
		db_merge($student_due_table)
		->key(array('fee_id' => $fee_id))
		->fields (array(
				$col => 0,
			)
		)	
		->execute();
	}
	$url = url('admin/fees/fee_structure', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
	
	drupal_set_message('Fee - '.$particulars.' was successfully deleted from month - '.$mon, 'status');
}
/**
 *Theme function
 */
function theme_fee_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Fee ID'),t('Frequency'), t('Particulars'), t('Amount'), t('Next Deadline'),t('Applies To'), t('Class Range'), t('Optional Subject'), t('Distance Range'), t(''), t(''));
  
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