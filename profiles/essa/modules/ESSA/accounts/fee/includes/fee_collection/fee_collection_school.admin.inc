<?php

/**
 *Implements Page callback function - select_adm_no
 */
function fee_collection_school($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_freq = 'essa_'.$session_id.'_fees_frequency';
	$fees_student_table = 'essa_'.$session_id.'_fees_student_table';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_freq = 'essa_'.$session_id.'_fees_frequency';
	$fees_student = 'essa_'.$session_id.'_fees_student';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$fees_advance = 'essa_'.$session_id.'_fees_student_advance';
	$fine_table = 'essa_'.$session_id.'_fees_student_fine';
	
	$form['mode'] = array(
		'#type' => 'markup',
		'#markup' => '<h5>School Collection</h5>',
 	);
	
	$form['adm_no'] = array(
    '#type' => 'textfield',
		'#autocomplete_path' => 'adm_no/fee_autocomplete',
    '#title' => t('Admission No.'),
    '#size' => 10,
		'#id' => 'adm_no',
		'#prefix' => '<div class = "collection_form">',
		'#required' => TRUE,
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'student_detail_with_adv_ajax',
      'wrapper' => 'sd_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#suffix' => '<script type="text/javascript">'
      . 'jQuery(\'input#adm_no\').focus();'
      . '</script>',
  );
	
	global $user;
	$format = 'd-m-Y';
	$set_dt = variable_get('pay_dt'.$user->uid);
	if(isset($set_dt)){
		$def_dt = date('Y-m-d', variable_get('pay_dt'.$user->uid));
	}else{
		$def_dt = date('m/d/Y');
	}
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
		$columns_list[] = $dt->format("M_Y");
	}
	foreach($columns_list as $col){
		$options[] = $col;
	}
	$options = array_unique($options);
	foreach($options as $def){
		$default = $def[0];
	}
	$form['from'] = array(
		'#type' => 'select',
		'#title' => t('From'),
		'#options' => drupal_map_assoc($options),
		'#required' => TRUE,
		'#default_value' => $default,
	);
	
	$form['options'] = array(
		'#type' => 'select',
		'#title' => t('To'),
		'#options' => drupal_map_assoc($options),
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'fee_head_fill',
      'wrapper' => 'fee_head',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#required' => TRUE,
	);
	
	$form['pay_date'] = array(
		'#type' => 'date_select',
		'#title' => t('Payment Date'),
		'#default_value' => $def_dt, 
		'#date_format' => $format,
		'#date_year_range' => '0:+1',
		'#date_label_position' => 'within',
		'#required' => TRUE,
	);
	
	$form['sd_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "sd_wrapper">',
		'#suffix' => '</div></div>',
	);
	
	$form['lts'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "fee_head">',
		'#suffix' => '</div>',
	);
	
	if(!empty($form_state['values']['adm_no']) && !empty($form_state['values']['options'])){
		$adm_no = $form_state['values']['adm_no'];
	  $binfo = db_query("
      SELECT * from {$basic_info_table};
    ");
    foreach($binfo as $info){
    	$start_date = $info->academicyearstart;
    	$end_date = $info->academicyearend;
    }
		$from_dt = str_replace('_','-',$form_state['values']['from']);
    $start = new DateTime($from_dt);
    $start->modify('first day of this month');
    $dt = str_replace('_','-',$form_state['values']['options']);
    $end = new DateTime($dt);
    $end->modify('first day of next month');
    $interval = DateInterval::createFromDateString('1 month');
    $period = new DatePeriod($start, $interval, $end);
    foreach ($period as $dt) {
    	$mon_range[] = $dt->format("M_Y");
    }
    
    foreach($mon_range as $mrl){
      $dt = str_replace('_','-',$mrl);
      $months[] = strtotime($dt);
    }
    foreach($months as $m){
      $columns[] = date('M_Y', $m);
    }
		
    $total = 0;
		$row = array();
    $each_fee = array();
		$studs = db_query("
		  SELECT * from {$fees_student_due} where adm_no = :an order by fee_id asc;", array(':an' => $adm_no)
		);
    foreach($studs as $stud){
			//$each_fee[$stud->fee_id] = 0;
			foreach($columns as $col){
        if($stud->$col != 0){
					$each_fee[$stud->fee_id] = $each_fee[$stud->fee_id] + $stud->$col;
					$total = $total + $stud->$col;
				}
			}
		}
		
		arsort($each_fee);
		$row = array();
		foreach($each_fee as $fee_id => $amt){
			$fees = db_query(
				"SELECT * from $fees_table where fee_id = :fi;", array(':fi' => $fee_id)
			);
			foreach($fees as $fee){
				$particular = $fee->particulars;
			}
			
			$row[$fee_id] = array(
			  '#tree' =>TRUE,
		    $fee_id => array(  //Generating unique array id for every form element
		      'c1' =>array(
		        '#type' => 'markup',
			      '#markup' => '<h3 style = "text-align: left !important;">'. $particular .'</h3>',
			    ),
					'c3' =>array(
		        '#type' => 'markup',
			      '#markup' => '<h3 style = "text-align: left !important;">'. $amt .'</h3>',
			    ),
			    'c2' =>array(
			      '#type' => 'textfield',
		        '#size' => 10,
		        '#value' => $amt,
		        '#ajax' => array(
			        'event' => 'blur',
			        'callback' => 'calculate_total',
			        'wrapper' => 'fee_total',
			        'method' => 'replace',
			        'effect' => 'fade',
		        ),
		      ),
		    ),
			);
		}
		
		$each_fine = array();
		$fine_amt_due = 0;
		
		$today = strtotime(date('d-m-Y'));
		$stud_fine = db_query("
		  SELECT * from {$fine_table} where adm_no = :an;", array(':an' => $adm_no)
		);
    foreach($stud_fine as $stf){
			if($stf->collection_date < $today){
				$fine_amt_due = $fine_amt_due + ($stf->amount_to_be_paid - $stf -> amount_paid);
			}
		}
		$total = $total + $fine_amt_due;
		
		$fine_row['fine'] = array(
		  '#tree' =>TRUE,
		  'fine' => array(
			  'c1' =>array(
		      '#type' => 'markup',
			    '#markup' => '<h3 style = "text-align: left !important;">'.'Fine(till - '.date('d-m-Y').')'.'</h3>',
			  ),
				'c3' =>array(
		      '#type' => 'markup',
		      '#markup' => '<h3 style = "text-align: left !important;">'. $fine_amt_due .'</h3>',
		    ),
			  'c2' =>array(
			    '#type' => 'textfield',
		      '#size' => 10,
	        '#value' => $fine_amt_due,
	        '#ajax' => array(
			      'event' => 'blur',
			      'callback' => 'calculate_total',
			      'wrapper' => 'fee_total',
			      'method' => 'replace',
		        'effect' => 'fade',
	        ),
		    ),
			),
		);
		$row = array_merge($row, $fine_row);
		
		$total_row['total'] = array(
		  '#tree' =>TRUE,
		  'total' => array(
			  'c1' =>array(
			    '#type' => 'markup',
		      '#markup' => '<h3 style = "text-align: right !important;"></h3>',
		    ),
				'c3' =>array(
			    '#type' => 'markup',
		      '#markup' => '<h3 style = "text-align: right !important;">Total</h3>',
		    ),
			  'c2' =>array(
			    '#type' => 'markup',
					'#markup' => '<h3 style = "text-align: left;">'.$total.'</h3>',
					'#prefix' => '<div id = "fee_total">',
					'#suffix' => '</div>',
			  ),
			),
		);
		$row = array_merge($row, $total_row);
		$form['lts']['tab'] = array(
			'#theme' => 'fee_collection_table',
			'rows' => $row,
		);
		
		$form['lts']['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Submit',
		);
	}
	
	return $form;
}

/**
 *Implements ajax callback
 */
function fee_head_fill($form, &$form_state){
	$form_state['rebuild'] = TRUE;
	return $form['lts'];
}

/**
 *Implements ajax callback - calculate_total
 *
 */
function calculate_total($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
  $fees_table = 'essa_'.$session_id.'_fees_structure';
	$total = 0;
	
	$fee_list = array('fine');
	$fees = db_query(
		"SELECT * from $fees_table;"
	);
	foreach($fees as $fee){
		$fee_list[] = $fee->fee_id;
	}
	foreach($form_state['input'] as $key => $value){
		if(is_array($value)){
			foreach($value as $k=>$v){
				if(in_array($k, $fee_list)){
					if(is_numeric($v['c2'])){
						$total = $total + $v['c2'];
					}
				}
			}
		}
	}
	
	$form['total'] = array(
		'#type' => 'markup',
		'#markup' => '<h3 style = "text-align: left;">'.$total.'</h3>',
		'#prefix' => '<div id = "fee_total">',
		'#suffix' => '</div>',
	);
	
	return $form['total'];
}

/**
 *Implements validate function
 */
function fee_collection_school_validate($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fine_table = 'essa_'.$session_id.'_fees_student_fine';
	$today = strtotime(date('d-m-Y'));
	$fine_amt_due = 0;
	$stud_fine = db_query("
		SELECT * from {$fine_table} where adm_no = :an;", array(':an' => $form_state['values']['adm_no'])
	);
  foreach($stud_fine as $stf){
		if($stf->collection_date < $today){
			$fine_amt_due = $fine_amt_due + ($stf->amount_to_be_paid - $stf -> amount_paid);
		}
	}
		
	foreach($form_state['input'] as $key => $value){
		if(is_array($value)){
			foreach($value as $k=>$v){
				if(is_array($v)){
					$amt_paid = $v['c2'];
					if($k == 'fine'){
						if($amt_paid > $fine_amt_due){
							variable_set('fee_fine_error', 'error');
						}else{
							variable_set('fee_fine_error', NULL);
						}
					}
				}
			}
		}
	}
}

/**
 *Implements submit function
 */
function fee_collection_school_submit($form, &$form_state){
	$fine_error = variable_get('fee_fine_error');
	if($fine_error == 'error'){
		drupal_set_message('<h3 style = "color: RED; padding-top: 15px;"><b>Fine collected cannot be greater than the fine amount.</b></h3>', 'error');
	}else{
		$session_id = (string)variable_get('essa_sid');
		$fees_table = 'essa_'.$session_id.'_fees_structure';
		$fees_freq = 'essa_'.$session_id.'_fees_frequency';
		$fees_student_table = 'essa_'.$session_id.'_fees_student_table';
		$fees_student = 'essa_'.$session_id.'_fees_student';
		$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
		$fees_advance = 'essa_'.$session_id.'_fees_student_advance';
		$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
		$payment_history = 'essa_'.$session_id.'_fees_payment_history';
		$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
		$basic_info_table = 'essa_'.$session_id.'_basicinfo';
		$fine_table = 'essa_'.$session_id.'_fees_student_fine';
		$sys_alert_table = 'essa_'.$session_id.'_system_alert';
		$total = 0;
		$amount_remaining = 0;
		$amount_paid = 0;
		$advance = array();
		global $user;
		
		$fee_list = array('fine');
		$fees = db_query(
			"SELECT * from $fees_table;"
		);
		foreach($fees as $fee){
			$fee_list[] = $fee->fee_id;
		}
		foreach($form_state['input'] as $key => $value){
			if(is_array($value)){
				foreach($value as $k=>$v){
					if(in_array($k, $fee_list)){
						if(is_numeric($v['c2'])){
								$total = $total + $v['c2'];
						}
					}
				}
			}
		}
		
		$date = $form_state['values']['pay_date'];
		$pay_dt = strtotime($date);
		variable_set('pay_dt'.$user->uid, $pay_dt);
		
		db_insert($payment_history)
			->fields (array(
					'adm_no' => $form_state['values']['adm_no'],
					'payment_date' => $pay_dt,
					'amount' => $total,
					'uid' => $user->uid,
					'type' => 'School',
				)
			)	
			->execute();
			
		$ph = db_query("
			SELECT * from {$payment_history} where adm_no = :an and payment_date = :pd and amount = :am;", array(':an' => $form_state['values']['adm_no'], ':pd' => $pay_dt, ':am' => $total)
		);
		foreach($ph as $p){
			$receipt_no = $p->id;
		}
		
		$binfo = db_query("
			SELECT * from {$basic_info_table};
		");
		foreach($binfo as $info){
			$start_date = $info->academicyearstart;
			$end_date = $info->academicyearend;
		}
		
		
		$from_dt = str_replace('_','-',$form_state['values']['from']);
		$start = new DateTime($from_dt);
		$start->modify('first day of this month');
		$dt = str_replace('_','-',$form_state['values']['options']);
		$end = new DateTime($dt);
		$end->modify('first day of next month');
		$interval = DateInterval::createFromDateString('1 month');
		$period = new DatePeriod($start, $interval, $end);
		foreach ($period as $dt) {
			$mon_range[] = $dt->format("M_Y");
		}
			
		foreach($mon_range as $mrl){
			$dt = str_replace('_','-',$mrl);
			$months[] = strtotime($dt);
		}
		foreach($months as $m){
			$columns[] = date('M_Y', $m);
		}
		
		//dsm($form_state);
		$total_amt_paid = 0;
		foreach($form_state['input'] as $key => $value){
			if(is_array($value)){
				foreach($value as $k=>$v){
					if(is_array($v)){
						$amt_paid = $v['c2'];
						if(in_array($k, $fee_list) && $k != 'fine'){
							if(is_numeric($v['c2'])){
								$student_due = db_query("
									SELECT * from {$fees_student_due} where adm_no = :an and fee_id = :fi;", array(':an' => $form_state['values']['adm_no'], ':fi' => $k)
								);
								foreach($student_due as $sd){
									foreach($columns as $col){
										if($sd->$col != NULL){
											if($amt_paid > 0){
												if($amt_paid > $sd->$col){
													$due = 0;
													$paid = $sd->$col;
												}else{
													$due = $sd->$col - $amt_paid;
													$paid = $amt_paid;
												}
												$amt_paid = $amt_paid - $sd->$col;
												
												if($paid > 0){
													db_insert($fees_student_payment)
														->fields (array(
															'fee_id' => $k,
															'month' => $col,
															'adm_no' => $form_state['values']['adm_no'],
															'receipt_no' => $receipt_no,
															'amount' => $paid,
														)
													)
													->execute();	
												}
												
												db_merge($fees_student_due)
													->key(array('fee_id' => $k,'adm_no' => $form_state['values']['adm_no']))
													->fields (array(
														$col => $due,
													)
												)
												->execute();
											}
										}
									}
								}
								if($amt_paid > 0){
									$past_amt = NULL;
									$past_student_advance = db_query("
										SELECT * from {$fees_advance} where adm_no = :an and fee_id = :fi and receipt_no = :rn;", array(
											':an' => $form_state['values']['adm_no'], ':fi' => $k, ':rn' => $receipt_no)
									);
									foreach($past_student_advance as $psa){
										$past_amt = $psa->amount;
										$past_amt_remaining = $psa->amount_remaining;
									}
									
									if($past_amt != NULL){
										$amt_paid = $amt_paid + $past_amt;
										$amt_remaining = $amt_paid + $past_amt_remaining;
									}else{
										$amt_paid = $amt_paid;
										$amt_remaining = $amt_paid;
									}
									db_merge($fees_advance)
										->key(array('fee_id' => $k,'adm_no' => $form_state['values']['adm_no'], 'receipt_no' => $receipt_no))
										->fields (array(
											'fee_id' => $k,
											'adm_no' => $form_state['values']['adm_no'],
											'receipt_no' => $receipt_no,
											'amount' => $amt_paid,
											'amount_remaining' => $amt_remaining,
										)
									)
									->execute();
								}
							}
						}else{
							$today = strtotime(date('d-m-Y'));
							$stud_fine = db_query("
								SELECT * from {$fine_table} where adm_no = :an;", array(':an' => $form_state['values']['adm_no'])
							);
							foreach($stud_fine as $stf){
								$fine_remaining = $stf->amount_to_be_paid - $stf->amount_paid;
								if($stf->collection_date < $today && $fine_remaining > 0){
									//$fine_amt_due = $fine_amt_due + ($stf->amount_to_be_paid - $stf -> amount_paid);
									if($amt_paid > 0){
										if($amt_paid > $fine_remaining){
											$fine_due = 0;
											$fine_paid = $fine_remaining;
										}else{
											$fine_due = $fine_remaining - $amt_paid;
											$fine_paid = $amt_paid;
										}
										$fine_paid = $fine_paid + $stf->amount_paid;
										$amt_paid = $amt_paid - $fine_paid;
										
										db_merge($fine_table)
											->key(array('id' => $stf->id))
											->fields (array(
												'amount_paid' => $fine_paid,
												'receipt_no' => $receipt_no,
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
		}
	}
	
	$first = reset($columns);
  $last = end($columns);
	//drupal_set_message('The payment was processed successfullly.','status');
	//***********SURAJ***********
	if($first == $last){
		drupal_set_message('Fees has been paid for '.$form_state['values']['adm_no'].' for the month '.$first,'status');
		
		//sending system alert
		global $user;
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
			'message' => 'Fees has been paid for '.$form_state['values']['adm_no'].' for the month '.$first,
			'priority' => 'M',
			'module' => 'fee',
			'source_url' => 'admin/fees/payment/collection',
			'timestamp' => $strtodate,
			'source_uid' => $user->uid,
		))
		->execute();
		
	}else{
		drupal_set_message('Fees has been paid for '.$form_state['values']['adm_no'].' for the months between '.$first.' to '.$last,'status');
		
		//sending system alert
		global $user;
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
			'message' => 'Fees has been paid for '.$form_state['values']['adm_no'].' for the months between '.$first.' to '.$last,
			'priority' => 'M',
			'module' => 'fee',
			'source_url' => 'admin/fees/payment/collection',
			'timestamp' => $strtodate,
			'source_uid' => $user->uid,
		))
		->execute();
	}
	//***********SURAJ***********
}

/**
 *Theme function
 */
function theme_fee_collection_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Particulars'), t('Amount Due'), t('Amount Paid'));
  
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
 *Implements ajax callback
 */
function student_detail_with_adv_ajax($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$stud_table = 'essa_'.$session_id.'_master_student_table';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	
	variable_set('fee_adm_no_error', NULL);
	$stud_info = db_query(
		"SELECT * from $student_table where adm_no = :adm_no AND status = 1;", array(':adm_no' => $form_state['values']['adm_no'])
	);
	foreach($stud_info as $si){
		$class = $si->class;
		$sec = $si->section;
		$stud_table = 'essa_'.$session_id.'_'.$class.'_'.$sec;
	}
	
	if(!empty($form_state['values']['adm_no'])){
		$stud_detail = db_query(
			"SELECT * from $student_table WHERE status = 1;"
		);
		foreach($stud_detail as $sd){
			if($sd->adm_no == $form_state['values']['adm_no']){
				$name = $sd->student_name;
				$roll_no = $sd->roll_no;
			}
		}
		
		if(isset($name)){
			$form['fs'] = array(
				'#type' => 'container',
				'#prefix' => '<div id = "sd_wrapper">',
				'#suffix' => '</div></div>',
			);
			
			$form['fs']['ds'] = array(
				'#type' => 'markup',
				'#markup' => '<p style = "float:left; width: 50px;">Name: </p><h4><b>'.$name.'</b></h4><p style = "float:left;width: 50px;"> Class: </p><h4><b>'.$class.' - '.$sec.'</b></h4><p style = "float:left; width: 50px;">Roll No. <h4><b>'.$roll_no.'</b></h4>',
				'#validated' => TRUE,
			);
			
			$session_id = (string)variable_get('essa_sid');
			$advance_table = 'essa_'.$session_id.'_fees_student_advance';
			
			$advance = db_query(
				"SELECT * from $advance_table where adm_no = :an and amount_remaining <> 0;", array(':an' => $form_state['values']['adm_no'])
			);
			
			foreach($advance as $ad){
				$amt_remaining[$ad->fee_id] = $amt_remaining[$ad->fee_id] + $ad->amount_remaining;
			}
			$advance = db_query(
				"SELECT * from $advance_table where adm_no = :an and amount_remaining > 0;", array(':an' => $form_state['values']['adm_no'])
			);
			
			foreach($advance as $ad){
				$particular = '';
				$fee_ids = db_query("
          SELECT * from {$fees_table} where fee_id = :fi;", array(':fi' => $ad->fee_id)
        );
        foreach($fee_ids as $id){
          $particular = $id->particulars;
        }
        
				if($particular == ''){
					$particular = 'Advance against concession';
				}
        
				$row[$ad->fee_id] = array(
		      '#tree' =>TRUE,
		      $ad->fee_id => array(  //Generating unique array id for every form element
		       'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'. $ad->fee_id .'</h3>',
						),
					 'c2' =>array(
		          '#type' => 'markup',
		          '#markup' => '<h4 style = "text-align: left !important; padding-top: 15px;">'. $particular .'</h4>',
		        ),
						'c3' =>array(
		          '#type' => 'markup',
		          '#markup' => '<h3 style = "text-align: left !important;">'. $amt_remaining[$ad->fee_id] .'</h3>',
		        ),
		      ),
		    );
			}
			
			if(isset($row)){
				$form['fs']['adfs'] = array(
					'#type' => 'fieldset',
					'#title' => 'Advance',
				); 
				
				$form['fs']['adfs']['help'] = array(
					'#type' => 'markup',
					'#markup' => 'To adjust the advance amount goto '.l('adjustment page.', 'admin/fees/payment/adjustments', array('target' => '_blank')),
				);
				
				$form['fs']['adfs']['advance_tab'] = array(
					'#theme' => 'advance_table',
					'rows' => $row,
					'#prefix' => '<div id = "adv_tab">',
					'#suffix' => '</div>',
				);
			}
			
			
			$session = (string)variable_get('essa_sid');
			$student_concession_table = 'essa_'.$session.'_fees_student_concession';
			$student_concession = db_query("
				SELECT * from {$student_concession_table} where adm_no = :n;",
				array(':n' => $form_state['values']['adm_no'])
			);
			foreach($student_concession as $sc){
				$con_flag = 1;
			}
			if($con_flag == 1){
				global $base_url;
				$url = $base_url.'/admin/fees/reports/concession-detail';
				$form['fs']['concesssion'] = array(
					'#type' => 'markup',
					'#markup' => '<h5><span style = "color:RED"><b>***This student has concession applied. </span><a href = "'.$url.'">Check concession, here.</a></b><h5>',
				);
			}
		}else{
			$form['fs'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 style = "color: RED;"> Entered admission no. <b>'.$form_state['values']['adm_no'].'</b> is not present in the system. </h3>',
				'#prefix' => '<div id = "sd_wrapper">',
				'#suffix' => '</div></div>',
				'#validated' => TRUE,
			);
			variable_set('fee_adm_no_error', 'error');
		}
		return $form['fs'];
	}
}