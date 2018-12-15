<?php
/**
 *Implements page callback function - fee_payment.
 */
function fee_payment($form = array(), &$form_state){
	$form['adm_no'] = array(
    '#type' => 'textfield',
    '#title' => t('Admission No.'),
    '#size' => 10,
		'#id' => 'adm_no',
		'#autocomplete_path' => 'adm_no/fee_autocomplete',
		'#prefix' => '<div class = "coll_form">',
		'#required' => TRUE,
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'student_detail_ajax',
      'wrapper' => 'sd_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#suffix' => '<script type="text/javascript">'
      . 'jQuery(\'input#adm_no\').focus();'
      . '</script>',
		'#attached' => drupal_add_css(
			'.coll_form{
			  width: 28%;
			  float: right;
			}'
		),
  );
	
	$options = get_options();
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
      'callback' => 'fee_fill',
      'wrapper' => 'fee_pay_tab',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#required' => TRUE,
	);
	
	global $user;
	$format = 'd-m-Y';
	
	$set_dt = variable_get('pay_dt'.$user->uid);
	if(isset($set_dt)){
		$def_dt = date('Y-m-d', variable_get('pay_dt'.$user->uid));
	}else{
		$def_dt = date('d-m-Y');
	}
	
	$form['pay_date'] = array(
		'#type' => 'date_select',
		'#title' => t('Payment Date'),
		'#default_value' => $def_dt, 
		'#date_format' => $format,
		'#date_year_range' => '0:+1',
		'#date_label_position' => 'within',
		'#required' => TRUE,
		'#validated' => TRUE,
	);
	
	$session_id = (string)variable_get('essa_sid');
  $fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_freq = 'essa_'.$session_id.'_fees_frequency';
	$fees_student_table = 'essa_'.$session_id.'_fees_student_table';
  $fees_table = 'essa_'.$session_id.'_fees_structure';
  $fees_freq = 'essa_'.$session_id.'_fees_frequency';
  $fees_student = 'essa_'.$session_id.'_fees_student';
  $fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fine_table = 'essa_'.$session_id.'_fees_student_fine';
  $basic_info_table = 'essa_'.$session_id.'_basicinfo';
  
	$fees = db_query(
		"SELECT * from $fees_table;"
	);
	
	foreach($fees as $fee){
		$fee_particulars[] = $fee->particulars;
	}
	$fee_count = count(array_unique($fee_particulars));
	$fee_particulars = array_unique($fee_particulars);
	$fee_particulars = array_values($fee_particulars);
	
	$form['sd_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "sd_wrapper">',
		'#suffix' => '</div></div>',
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
    
		$studs = db_query("
		  SELECT * from {$fees_student_due} where adm_no = :an order by fee_id asc;", array(':an' => $adm_no)
		);
    foreach($studs as $stud){
			foreach($columns as $col){
        if($stud->$col != 0){
					$total = $total + $stud->$col;
          $fee_ids = db_query("
            SELECT * from {$fees_table} where fee_id = :fi;", array(':fi' => $stud->fee_id)
          );
          foreach($fee_ids as $id){
            $particular = $id->particulars;
          }
          //dsm($particular);
          $row[$stud->fee_id.'-'.$col] = array(
            '#tree' =>TRUE,
            $stud->fee_id.'-'.$col => array(  //Generating unique array id for every form element
            	'c1' =>array(
            		'#type' => 'markup',
            		'#markup' => '<h3 style = "text-align: left !important;">'. $particular .'</h3>',
            	),
            	'c2' =>array(
            		'#type' => 'markup',
            		'#markup' => '<h3>'. str_replace('_','-',$col).'</h3>',
            	),
            	'c3' =>array(
            		'#type' => 'markup',
            		'#markup' => '<h3>'.$stud->$col.'</h3>',
            	),
            	'c4' =>array(
            		'#type' => 'textfield',
                '#size' => 10,
                '#default_value' => $stud->$col,
                //'#name' => $stud->$col,
                '#ajax' => array(
                  'event' => 'blur',
                  'callback' => 'recalculate_total',
                  'wrapper' => 'total',
                  'method' => 'replace',
                  'effect' => 'fade',
                ),
            	),
            ),
          );
        }
      }
    }
		$each_fine = array();
		$fine_amt_due = 0;
		
		$today = strtotime(date('d-m-Y'));
		$stud_fine = db_query("
		  SELECT * from {$fine_table} where adm_no = :an;", array(':an' => $adm_no)
		);
    foreach($stud_fine as $stf){
			if($stf->collection_date < $today){
				$fine_amt_due = ($stf->amount_to_be_paid - $stf -> amount_paid);
				$total = $total + $fine_amt_due;
				
				if($fine_amt_due > 0){
					$fine['fine'.$stf->id] = array(
						'#tree' =>TRUE,
						'fine'.$stf->id => array(
						  'c1' =>array(
            		'#type' => 'markup',
            		'#markup' => '<h3 style = "text-align: left !important;">'. $stf->particulars .'</h3>',
            	),
            	'c2' =>array(
            		'#type' => 'markup',
            		'#markup' => '<h3>'. str_replace('_','-',$stf->month).'</h3>',
            	),
            	'c3' =>array(
            		'#type' => 'markup',
            		'#markup' => '<h3>'.$fine_amt_due.'</h3>',
            	),
            	'c4' =>array(
            		'#type' => 'textfield',
                '#size' => 10,
                '#default_value' => $fine_amt_due,
                //'#name' => $stud->$col,
                '#ajax' => array(
                  'event' => 'blur',
                  'callback' => 'recalculate_total',
                  'wrapper' => 'total',
                  'method' => 'replace',
                  'effect' => 'fade',
                ),
            	),
					  ),
					);
				}
			}
		}
		
		if(isset($fine)){
			$row = array_merge($row, $fine);	
		}
    
    $form['lts'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "fee_pay_tab">',
			'#suffix' => '</div>',
		);
			
		$form['lts']['total'] = array(
			'#type' => 'textfield',
			'#title' => 'Total - ',
			'#size' => 20,
			'#prefix' => '<div id = "total">',
			'#suffix' => '</div>',
			'#default_value' => $total,
			'#disabled' => TRUE,
		);
		
		$form['lts']['tab'] = array(
			'#theme' => 'individual_payment_table',
			'rows' => $row,
		);
		
		$form['lts']['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Submit',
			'#prefix' => '<div id = "fee_save">',
			'#suffix' => '</div>',
		);
	}
		
	$form['container'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "fee_pay_tab">',
		'#suffix' => '</div>',
		'#attached' => drupal_add_css(
			'#fee_pay_tab{
			  width: 70%;
			}'
		),
	);
	
	return $form;
}

/**
 *Function to calculate total on ajax callback.
 */
function recalculate_total($form, &$form_state){
  $session_id = (string)variable_get('essa_sid');
  $student_table = 'essa_'.$session_id.'_master_student_table';
  $fees_student_table = 'essa_'.$session_id.'_fees_student_table';
  $fees_table = 'essa_'.$session_id.'_fees_structure';
  $fees_freq = 'essa_'.$session_id.'_fees_frequency';
  $fees_student = 'essa_'.$session_id.'_fees_student';
  $fees_student_due = 'essa_'.$session_id.'_fees_student_due';
  $basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$fine_table = 'essa_'.$session_id.'_fees_student_fine';
  $options = $form_state['values']['options'];
	
	if((substr($form_state['triggering_element']['#name'], 0, 4)) !== 'fine'){
		//$arr = explode('-', $form_state['triggering_element']['#name'],2);
		//$fee_id = $arr[0];
		//$arr1 = explode('[', $arr[1],2);
		//$col = $arr1[0];
		
		foreach($form_state['values'] as $val){
			if(is_array($val)){
				foreach($val as $k => $v){
					$arr = explode("-", $k, 2);
					$fee_id = $arr[0];
					$col = $arr[1];
					if($col != NULL){
						$stud_due = db_query("
						  SELECT * from {$fees_student_due} where adm_no = :an and fee_id = :fi;", array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id)
						);
						foreach($stud_due as $sd){
							if($v['c4'] > $sd->$col){
								variable_set('fee_payment_error', 'error');
								$form['fs'] = array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "color: RED;"> You can\'t collect an amount greater than the alloted amount or the amount due for that fee ID.</h3>',
									'#validated' => TRUE,
									'#prefix' => '<div id = "total" style = "width: 28%;">',
									'#suffix' => '</div>',
								);
								return $form['fs'];
							}else{
								variable_set('fee_payment_error', NULL);
							}
							if($v['c4'] < 0){
								variable_set('fee_payment_error', 'error');
								$form['fs'] = array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "color: RED;"> You can\'t enter negative numbers. </h3>',
									'#prefix' => '<div id = "total" style = "width: 28%;">',
									'#suffix' => '</div>',
									'#validated' => TRUE,
								);
								return $form['fs'];
							}else{
								variable_set('fee_payment_error', NULL);
							}
						}
					}
				}
			}
		}
	}else{
		foreach($form_state['values'] as $val){
			if(is_array($val)){
				foreach($val as $k => $v){
					if(substr($k, 0, 4) == 'fine'){
						$fine_id = substr($k, 4);
						$today = strtotime(date('d-m-Y'));
						$stud_fine = db_query("
							SELECT * from {$fine_table} where id = :id;", array(':id' => $fine_id)
						);
						foreach($stud_fine as $stf){
							$fine_remaining = $stf->amount_to_be_paid - $stf->amount_paid;
							if($v['c4'] > $fine_remaining){
								variable_set('fee_payment_error', 'error');
								$form['fs'] = array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "color: RED;"> You can\'t collect an amount greater than the alloted amount or the amount due for that fine ID.</h3>',
									'#validated' => TRUE,
									'#prefix' => '<div id = "total" style = "width: 28%;">',
									'#suffix' => '</div>',
								);
								return $form['fs'];
							}else{
								variable_set('fee_payment_error', NULL);
							}
							if($v['c4'] < 0){
								variable_set('fee_payment_error', 'error');
								$form['fs'] = array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "color: RED;"> You can\'t enter negative numbers. </h3>',
									'#prefix' => '<div id = "total" style = "width: 28%;">',
									'#suffix' => '</div>',
									'#validated' => TRUE,
								);
								return $form['fs'];
							}else{
								variable_set('fee_payment_error', NULL);
							}
						}
					}
				}
			}
		}
	}
	
	$total = 0;
  if($options != NULL){
    $binfo = db_query("
      SELECT * from {$basic_info_table};
    ");
    foreach($binfo as $info){
    	$start_date = $info->academicyearstart;
    	$end_date = $info->academicyearend;
    }
    $start = new DateTime($start_date);
    $start->modify('first day of this month');
    $dt = str_replace('_','-',$options);
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
    foreach($columns as $col){
      $studs = db_query("
        SELECT * from {$fees_student_due} where adm_no = :an and $col = $col;", array(':an' => $form_state['values']['adm_no'])
      );
      foreach($studs as $stud){
        $total = $total + $form_state['values'][$stud->fee_id.'-'.$col][$stud->fee_id.'-'.$col]['c4'];
      }
    }
  }
	
	$today = strtotime(date('d-m-Y'));
	$stud_fine = db_query("
	  SELECT * from {$fine_table} where adm_no = :an;", array(':an' => $form_state['values']['adm_no'])
	);
  foreach($stud_fine as $stf){
		if($stf->collection_date < $today){
			$fine_amt_due = ($stf->amount_to_be_paid - $stf -> amount_paid);
			if($fine_amt_due > 0){
				$total = $total + $form_state['values']['fine'.$stf->id]['fine'.$stf->id]['c4'];
			}
		}
	}
	
  //isset($form_state['values']['fine']['fine']['c4'])
  /*
  if($form_state['triggering_element']['#array_parents'][2]=='fine'){
    $total = $total + $form_state['triggering_element']['#value'];  
  }
  */
	$form['lts']['total']['#value'] = $total;//$stud->fee_id.'_'.$col;//$form_state['values'][$stud->fee_id.'_'.$col][$stud->fee_id.'_'.$col]['c4'];
	return $form['lts']['total'];
}

/**
 *Implements submit function
 */
function fee_payment_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history = 'essa_'.$session_id.'_fees_payment_history';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$fine_table = 'essa_'.$session_id.'_fees_student_fine';
	$options = $form_state['values']['options'];
	global $user;
	$date = $form_state['values']['pay_date']['day'].'-'.$form_state['values']['pay_date']['month'].'-'.$form_state['values']['pay_date']['year'];
	$pay_dt = strtotime($date);
	$today_date = strtotime(date('d-M-Y'));
	
	foreach($form_state['input'] as $key => $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				$arr = explode("-", $k, 2);
				if((substr($arr[0], 0, 4)) !== 'fine' && (substr($arr[0], 0, 4)) !== 'day' && (substr($arr[0], 0, 5)) !== 'month' && (substr($arr[0], 0, 4)) !== 'year'){
					$fee_id = $arr[0];
					$col = $arr[1];
					if($col != NULL){
						$stud_due = db_query("
						  SELECT * from {$fees_student_due} where adm_no = :an and fee_id = :fi;", array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id)
						);
						foreach($stud_due as $sd){
							if($v['c4'] > $sd->$col){
								variable_set('fee_payment_error', 'error');
							}
							if($v['c4'] < 0){
								variable_set('fee_payment_error', 'error');
							}
						}
					}
				}
			}
		}
	}
	
	if($pay_dt > $today_date){
		drupal_set_message('You can\'t take payment in future date.','error');
	}else{
		drupal_add_css(drupal_get_path('module', 'fee') . '/fees.css');
		$is_payment_error = variable_get('fee_payment_error');
		$is_adm_no_error = variable_get('fee_adm_no_error');
		
		if($is_payment_error != 'error' && $is_adm_no_error != 'error'){
			$total = 0;
			if($options != NULL){
			  $binfo = db_query("
			    SELECT * from {$basic_info_table};
			  ");
			  foreach($binfo as $info){
			  	$start_date = $info->academicyearstart;
			  	$end_date = $info->academicyearend;
			  }
			  $start = new DateTime($start_date);
			  $start->modify('first day of this month');
			  $dt = str_replace('_','-',$options);
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
			  foreach($columns as $col){
			    $studs = db_query("
			      SELECT * from {$fees_student_due} where adm_no = :an and $col = $col;", array(':an' => $form_state['values']['adm_no'])
			    );
			    foreach($studs as $stud){
						if(isset($form_state['values'][$stud->fee_id.'-'.$col][$stud->fee_id.'-'.$col]['c4'])){
							$total = $total + $form_state['values'][$stud->fee_id.'-'.$col][$stud->fee_id.'-'.$col]['c4'];
						}
			    }
			  }
			}
		
			$today = strtotime(date('d-m-Y'));
			$stud_fine = db_query("
			  SELECT * from {$fine_table} where adm_no = :an;", array(':an' => $form_state['values']['adm_no'])
			);
			foreach($stud_fine as $stf){
				if($stf->collection_date < $today){
					$fine_amt_due = ($stf->amount_to_be_paid - $stf -> amount_paid);
					if($fine_amt_due > 0){
						$total = $total + $form_state['values']['fine'.$stf->id]['fine'.$stf->id]['c4'];
					}
				}
			}
			
			$date = $form_state['values']['pay_date']['day'].'-'.$form_state['values']['pay_date']['month'].'-'.$form_state['values']['pay_date']['year'];
			$pay_dt = strtotime($date);
			variable_set('pay_dt'.$user->uid, $pay_dt);
			db_insert($payment_history)
				->fields (array(
						'adm_no' => $form_state['values']['adm_no'],
						'payment_date' => $pay_dt,
						'amount' => $total,
						'uid' => $user->uid,
					)
				)	
				->execute();
				
			$ph = db_query("
				SELECT * from {$payment_history} where adm_no = :an and payment_date = :pd and amount = :am;", array(':an' => $form_state['values']['adm_no'], ':pd' => $pay_dt, ':am' => $total)
			);
			foreach($ph as $p){
				$receipt_no = $p->id;
			}
			
			$fee_list = array('fine');
			$fees = db_query(
				"SELECT * from $fees_table;"
			);
			foreach($fees as $fee){
				$fee_list[] = $fee->fee_id;
			}
			foreach($form_state['input'] as $key => $val){
				if(is_array($val)){
					foreach($val as $k => $v){
						$arr = explode("-", $k, 2);
						if((substr($arr[0], 0, 4)) !== 'fine' && (substr($arr[0], 0, 4)) !== 'day' && (substr($arr[0], 0, 5)) !== 'month' && (substr($arr[0], 0, 4)) !== 'year'){
							$fee_id = $arr[0];
							$col = $arr[1];
							$amt_paid = $v['c4'];
							if(is_numeric($v['c4'])){
								$student_due = db_query("
									SELECT * from {$fees_student_due} where adm_no = :an and fee_id = :fi;", array(':an' => $form_state['values']['adm_no'], ':fi' => $k)
								);
								foreach($student_due as $sd){
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
														'fee_id' => $fee_id,
														'month' => $col,
														'adm_no' => $form_state['values']['adm_no'],
														'receipt_no' => $receipt_no,
														'amount' => $paid,
													)
												)
												->execute();	
											}
											
											db_merge($fees_student_due)
												->key(array('fee_id' => $fee_id,'adm_no' => $form_state['values']['adm_no']))
												->fields (array(
													$col => $due,
												)
											)
											->execute();
										}
									}
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
									if($form_state['values']['fine'.$stf->id]['fine'.$stf->id]['c4'] == NULL){
										$amt_paid = 0;
									}else{
										$amt_paid = $form_state['values']['fine'.$stf->id]['fine'.$stf->id]['c4'];
									}
									//$fine_amt_due = $fine_amt_due + ($stf->amount_to_be_paid - $stf -> amount_paid);
									db_merge($fine_table)
										->key(array('id' => $stf->id))
										->fields (array(
											'amount_paid' => $amt_paid,
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
		}else{
			drupal_set_message('The payment was not processed, due to error in values. Please check the values before submitting.', 'error');
			variable_set('fee_payment_error', NULL);
			variable_set('fee_adm_no_error', NULL);
		}
	}
}

/**
 *Implements ajax callback
 */
function fee_fill($form, &$form_state){
	return $form['lts'];
}

function calculate_fee_amount($adm_no, $month, &$particulars){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
  $fees_student_table = 'essa_'.$session_id.'_fees_student_table';
  $fees_table = 'essa_'.$session_id.'_fees_structure';
  $fees_freq = 'essa_'.$session_id.'_fees_frequency';
  $fees_student = 'essa_'.$session_id.'_fees_student';
  $fees_student_due = 'essa_'.$session_id.'_fees_student_due';
  $basic_info_table = 'essa_'.$session_id.'_basicinfo';
	
	foreach($particulars as $pr){
		$fees = db_query(
			"SELECT * from $fees_table where particulars = :pr;", array(':pr' => $pr)
		);
		foreach($fees as $fee){
			$fee_ids[$fee->particulars][] = $fee->fee_id;
		}
	}
  
	$binfo = db_query("
    SELECT * from {$basic_info_table};
  ");
  foreach($binfo as $info){
    $start_date = $info->academicyearstart;
    $end_date = $info->academicyearend;
  }
  $start = new DateTime($start_date);
  $start->modify('first day of this month');
  $dt = str_replace('_','-',$month);
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
	
	foreach($particulars as $p){
		if($p != 'Fine'){
			$total[$p] = 0;
			$fee_stu_due = db_query("
			  SELECT * from {$fees_student_due} where adm_no = :adm_no;", array(':adm_no' => $adm_no)
			);
			foreach($fee_stu_due as $fsd){
				if(in_array($fsd->fee_id, $fee_ids[$p])){
					foreach($columns as $col){
						$fee_due = db_query("
						  SELECT $col from {$fees_student_due} where adm_no = :adm_no and fee_id = :fee_id;", array(':adm_no' => $adm_no, ':fee_id' => $fsd->fee_id)
						);
						foreach($fee_due as $fd){
							$total[$p] = $total[$p] + $fd->$col;
						}
					}
				}
			}
		}
	}	
	return $total;
}

/**
 *Support function to provide options osf months for fee collection
 */
function get_options(){
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
		$options[] = $col;
	}
	$options = array_unique($options);
	return $options;
}

/**
 *Implements ajax callback
 */
function student_detail_ajax($form, &$form_state){
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
