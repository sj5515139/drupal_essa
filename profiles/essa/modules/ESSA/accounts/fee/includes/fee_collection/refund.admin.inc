<?php

/**
 *Implements page callback function -refund
 */
function refund($form = array(), &$form_state){
	$session_id = (string)variable_get('essa_sid');
  $fees_advance = 'essa_'.$session_id.'_fees_student_advance';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	
	$form['adm_no'] = array(
		'#type' => 'textfield',
    '#title' => t('Admission No.'),
    '#size' => 10,
		'#autocomplete_path' => 'adm_no/autocomplete',
		'#required' => TRUE,
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'show_advance',
      'wrapper' => 'show_advance',
      'method' => 'replace',
      'effect' => 'fade',
    ),
	);
	
	$form['ref'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "show_advance">',
		'#suffix' => '</div></div>',
	);
	
	if(!empty($form_state['values']['adm_no'])){
		$row = array();
		$adm_no = $form_state['values']['adm_no'];
		$studs = db_query("
		  SELECT * from {$fees_advance} where adm_no = :an order by fee_id asc;", array(':an' => $adm_no)
		);
    foreach($studs as $stud){
			$fees = db_query(
				"SELECT * from $fees_table where fee_id = :fi;", array(':fi' => $stud->fee_id)
			);
			foreach($fees as $fee){
				$particular = $fee->particulars;
			}
			$row[$stud->fee_id.'/'.$stud->receipt_no] = array(
			  '#tree' =>TRUE,
		    $stud->fee_id.'/'.$stud->receipt_no => array(  //Generating unique array id for every form element
		      'c1' =>array(
		        '#type' => 'markup',
			      '#markup' => '<h3 style = "text-align: left !important;">'. $stud->receipt_no .'</h3>',
			    ),
					'c2' =>array(
		        '#type' => 'markup',
			      '#markup' => '<h3 style = "text-align: left !important;">'. $particular .'</h3>',
			    ),
					'c3' =>array(
		        '#type' => 'markup',
			      '#markup' => '<h3 style = "text-align: left !important;">'. $stud->amount .'</h3>',
			    ),
					'c4' =>array(
		        '#type' => 'markup',
			      '#markup' => '<h3 style = "text-align: left !important;">'. $stud->amount_remaining .'</h3>',
			    ),
			    'c5' =>array(
			      '#type' => 'textfield',
		        '#size' => 10,
		        '#default_value' => $stud->amount_remaining,
		      ),
		    ),
			);
		}
		
		if($row != NULL){
			$form['ref']['tab'] = array(
				'#theme' => 'fee_advance_table',
				'rows' => $row,
			);	
		}else{
			$session_id = (string)variable_get('essa_sid');
			$student_table = 'essa_'.$session_id.'_master_student_table';
			$adm_no = NULL;
			$stud_info = db_query(
				"SELECT * from $student_table where adm_no = :adm_no AND status = 1;", array(':adm_no' => $form_state['values']['adm_no'])
			);
			foreach($stud_info as $si){
				$adm_no = $si->adm_no;
			}
			if($adm_no != NULL){
				drupal_set_message('There is no advance for this admission no.');
			}else{
				drupal_set_message('Entered admission no. is not present in the system.', 'error');
			}
		}
	}
	
	$form['remarks'] = array(
		'#type' => 'textarea',
		'#title' => 'Remarks',
	);
		
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Refund',
	);
	
	return $form;
}

/**
 *Implements validate function
 */
function refund_validate($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$stud_table = 'essa_'.$session_id.'_master_student_table';
	$fees_advance = 'essa_'.$session_id.'_fees_student_advance';
	
	variable_set('fee_adm_no_error', NULL);
	$stud_info = db_query(
		"SELECT * from $student_table where adm_no = :adm_no AND status = 1;", array(':adm_no' => $form_state['values']['adm_no'])
	);
	foreach($stud_info as $si){
		$class = $si->class;
		$sec = $si->section;
	}
	if(!empty($form_state['values']['adm_no'])){
		$stud_detail = db_query(
			"SELECT * from $stud_table WHERE status = 1;"
		);
		foreach($stud_detail as $sd){
			if($sd->adm_no == $form_state['values']['adm_no']){
				$name = $sd->student_name;
				$roll_no = $sd->roll_no;
			}
		}
		
		if(!isset($name)){
			form_set_error('adm_no', 'Entered admission no. is not present in the system.');
		}
	}
	
	foreach($form_state['values'] as $key => $value){
		if(is_array($value)){
			foreach($value as $k=>$v){
				$amt_paid = $v['c5'];
				$adm_no = $form_state['values']['adm_no'];
				$arr = explode("/", $k, 2);
				$fee_id = $arr[0];
				$receipt_no = $arr[1];
				$studs = db_query("
				  SELECT * from {$fees_advance} where adm_no = :an and fee_id = :fi and receipt_no = :rn order by fee_id asc;", array(':an' => $adm_no, ':fi' => $fee_id, ':rn' => $receipt_no)
				);
				foreach($studs as $stud){
					if($v['c5'] > $stud->amount_remaining){
						form_set_error('adm_no','You can\'t refund amount greater then the advance amount paid.');
					}
				}
			}
		}
	}
}

/**
 *Implements submit function
 */
function refund_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
  $fees_advance = 'essa_'.$session_id.'_fees_student_advance';
	$fees_refund = 'essa_'.$session_id.'_fees_refund';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	
	$date = date('d-m-Y H:i:s');
	$ref_dt = strtotime($date);
	
	foreach($form_state['values'] as $key => $value){
		if(is_array($value)){
			foreach($value as $k=>$v){
				$amt_paid = $v['c5'];
				$adm_no = $form_state['values']['adm_no'];
				$arr = explode("/", $k, 2);
				$fee_id = $arr[0];
				$receipt_no = $arr[1];
				$studs = db_query("
				  SELECT * from {$fees_advance} where adm_no = :an and fee_id = :fi and receipt_no = :rn order by fee_id asc;", array(':an' => $adm_no, ':fi' => $fee_id, ':rn' => $receipt_no)
				);
				foreach($studs as $stud){
					$amt_remaining = $stud->amount_remaining - $v['c5'];
					db_update($fees_advance) // Table name no longer needs {}
						->fields(array('amount_remaining' => $amt_remaining,
													 'refund_date' => $ref_dt,
													 'refund_remarks' => $form_state['values']['remarks']))
						->condition(db_and()
							->condition('adm_no', $adm_no)
							->condition('fee_id', $fee_id)
							->condition('receipt_no', $receipt_no)
						)
					->execute();
					
					//sending system alert
					global $user;
					$created_date = date("Y-m-d H:i:s");
					$strtodate = strtotime($created_date);
					db_insert($sys_alert_table)
					->fields(array(
						'message' => 'Amount '.$amt_remaining.' has been refunded to adm no '.$adm_no,
						'priority' => 'M',
						'module' => 'fee',
						'source_url' => 'admin/fees/payment/collection',
						'timestamp' => $strtodate,
						'source_uid' => $user->uid,
					))
					->execute();
					if($v['c5'] > 0){
						db_insert($fees_refund)
							->fields (array(
								'adm_no' => $adm_no,
								'refund_date' => $ref_dt,
								'refund_remarks' => $form_state['values']['remarks'],
								'amount' => $v['c5'],
								'receipt_no' => $receipt_no,
								'fee_id'  => $fee_id,
								'uid' => $user->uid,
							)
						)	
						->execute();
					}
				}
			}
		}
	}
	drupal_set_message('Refund was successfully processed.','status');
}

function show_advance($form, &$form_state){
	return $form['ref'];
}

/**
 *Theme function
 */
function theme_fee_advance_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Receipt No.'), t('Particular'), t('Original Amount'), t('Amount Remaining'), t('Refund Amount'));
  
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
