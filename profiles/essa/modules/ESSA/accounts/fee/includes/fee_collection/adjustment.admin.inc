<?php
/**
 *Implements page callback function - fee_payment.
 */
function adjustment($form = array(), &$form_state){
	global $base_url;
	$url = $base_url.'/admin/fees/fine/edit-delete';
	$form['help'] = array(
		'#type' => 'markup',
		'#markup' => '<h3 style = "line-height: 1.2em;"><strong>NOTE:</strong>
		Adjustment is a special case, when the fee on a student is relaxed or exempted on recommendation of a competent authority.
		In this case the amount due will be removed from students account. But no payment information will be processed.
		You can also adjust advance payment(if any, using the given Advance ID). Enter the Advance id to adjust corresponding advance.
		Please enter "ex", if you want to give rebate.<b>You cannot exempt fine here. Only advance can be adjusted along fine.
		You can delete fine, <a href = "'.$url.'">here.</a></b>
		</h3>',
	); 
	
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
      'callback' => 'adjustment_student_detail_ajax',
      'wrapper' => 'sd_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#attached' => drupal_add_css(
			'.coll_form{
			  width: 28%;
			  float: right;
			}'
		),
  );
	
	$options = get_options();
	$form['options'] = array(
		'#type' => 'select',
		'#title' => t('Adjust For'),
		'#options' => drupal_map_assoc($options),
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'adjustment_fee_fill',
      'wrapper' => 'fee_pay_tab',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#required' => TRUE,
	);
	
	$form['reason'] = array(
		'#type' => 'textarea',
		'#title' => 'Reason',
		'#rows' => 2,
	);
	
	$session_id = (string)variable_get('essa_sid');
  $fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_freq = 'essa_'.$session_id.'_fees_frequency';
	$fees_student_table = 'essa_'.$session_id.'_fees_student_table';
  $fees_table = 'essa_'.$session_id.'_fees_structure';
	$fine_table = 'essa_'.$session_id.'_fees_student_fine';
  $fees_freq = 'essa_'.$session_id.'_fees_frequency';
  $fees_student = 'essa_'.$session_id.'_fees_student';
  $fees_student_due = 'essa_'.$session_id.'_fees_student_due';
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
		$advance_table = 'essa_'.$session_id.'_fees_student_advance';
		global $user;
		$today_date = strtotime(date('d-M-Y'));
		$flag = 0;
		
		$advance = db_query(
			"SELECT * from $advance_table where adm_no = :an;", array(':an' => $form_state['values']['adm_no'])
		);
		
		foreach($advance as $ad){
			$flag = 1;
		}
		
		if($flag == 0){
			$adm_no = $form_state['values']['adm_no'];
			$binfo = db_query("
			  SELECT * from {$basic_info_table};
			");
			foreach($binfo as $info){
				$start_date = $info->academicyearstart;
				$end_date = $info->academicyearend;
			}
			$start = new DateTime($start_date);
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
			$fine_row = array();
			foreach($columns as $col){
			  $studs = db_query("
			    SELECT * from {$fees_student_due} where adm_no = :an and $col = $col;", array(':an' => $adm_no)
			  );
			  foreach($studs as $stud){
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
			        	'c5' =>array(
			        		'#type' => 'textfield',
			            '#size' => 10,
			            '#default_value' => 0,
			            //'#name' => $stud->$col,
			            '#ajax' => array(
			              'event' => 'blur',
			              'callback' => 'recalculate_total',
			              'wrapper' => 'adjustment_total',
			              'method' => 'replace',
			              'effect' => 'fade',
			            ),
			        	),
			        ),
			      );
			    }
			  }
			}
			
			$form['lts'] = array(
				'#type' => 'container',
				'#prefix' => '<div id = "fee_pay_tab">',
			);
			
			$form['lts']['tab'] = array(
				'#theme' => 'adjustment_table',
				'rows' => $row,
			);
		}else{
			$adm_no = $form_state['values']['adm_no'];
			$binfo = db_query("
			  SELECT * from {$basic_info_table};
			");
			foreach($binfo as $info){
				$start_date = $info->academicyearstart;
				$end_date = $info->academicyearend;
			}
			$start = new DateTime($start_date);
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
			foreach($columns as $col){
			  $studs = db_query("
			    SELECT * from {$fees_student_due} where adm_no = :an and $col = $col;", array(':an' => $adm_no)
			  );
			  foreach($studs as $stud){
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
									'#size' => 5,
			        	),
			        	'c5' =>array(
			        		'#type' => 'textfield',
			            '#size' => 10,
			            '#default_value' => 0,
			            //'#name' => $stud->$col,
			            '#ajax' => array(
			              'event' => 'blur',
			              'callback' => 'recalculate_total',
			              'wrapper' => 'adjustment_total',
			              'method' => 'replace',
			              'effect' => 'fade',
			            ),
			        	),
			        ),
			      );
			    }
			  }
				
				$fine_row = array();
				$studs_fine = db_query("
			    SELECT * from {$fine_table} where adm_no = :an and month = :mon;", array(':an' => $adm_no, ':mon' => $col)
			  );
			  foreach($studs_fine as $sf){
			    if($sf->amount_paid < $sf->amount_to_be_paid){
						$amt_to_pay = $sf->amount_to_be_paid - $sf->amount_paid;
						$total = $total + $amt_to_pay;
			      
			      //dsm($particular);
			      $fine_row['fine'.$sf->id] = array(
			        '#tree' =>TRUE,
			        'fine'.$sf->id.'#'.$col => array(  //Generating unique array id for every form element
			        	'c1' =>array(
			        		'#type' => 'markup',
			        		'#markup' => '<h3 style = "text-align: left !important;">'. $sf->particulars .'</h3>',
			        	),
			        	'c2' =>array(
			        		'#type' => 'markup',
			        		'#markup' => '<h3>'. str_replace('_','-',$col).'</h3>',
			        	),
			        	'c3' =>array(
			        		'#type' => 'markup',
			        		'#markup' => '<h3>'.$amt_to_pay.'</h3>',
			        	),
								'c4' =>array(
			        		'#type' => 'textfield',
									'#size' => 5,
			        	),
			        	'c5' =>array(
			        		'#type' => 'textfield',
			            '#size' => 10,
			            '#default_value' => 0,
			            //'#name' => $stud->$col,
			            '#ajax' => array(
			              'event' => 'blur',
			              'callback' => 'recalculate_total',
			              'wrapper' => 'adjustment_total',
			              'method' => 'replace',
			              'effect' => 'fade',
			            ),
			        	),
			        ),
			      );
			    }
			  }
			}
			$form['lts'] = array(
				'#type' => 'container',
				'#prefix' => '<div id = "fee_pay_tab">',
			);
			$row = array_merge($row, $fine_row);
			
			$form['lts']['tab'] = array(
				'#theme' => 'advance_adjustment_table',
				'rows' => $row,
			);
		}
		
		$form['lts']['total'] = array(
			'#type' => 'textfield',
			'#title' => 'Total - ',
			'#size' => 20,
			'#prefix' => '<div id = "adjustment_total">',
			'#suffix' => '</div></div>',
			'#default_value' => 0,
			'#disabled' => TRUE,
		);
		
		$form['lts']['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Submit',
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
 *Implements submit function
 */
function adjustment_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_adjustement = 'essa_'.$session_id.'_fees_student_adjustement';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history = 'essa_'.$session_id.'_fees_payment_history';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$fine_table = 'essa_'.$session_id.'_fees_student_fine';
	$advance_table = 'essa_'.$session_id.'_fees_student_advance';
	global $user;
	$today_date = strtotime(date('d-M-Y'));
	$flag = 0;
	$adv = array();
	
	$advance = db_query(
		"SELECT * from $advance_table where adm_no = :an;", array(':an' => $form_state['values']['adm_no'])
	);	
	foreach($advance as $ad){
		$flag = 1;
		$adv[] = $ad->fee_id;
	}
	foreach($form_state['input'] as $key => $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				$arr = explode("-", $k, 2);
				if((substr($arr[0], 0, 4)) !== 'fine' && (substr($arr[0], 0, 4)) !== 'day'
					 && (substr($arr[0], 0, 5)) !== 'month' && (substr($arr[0], 0, 4)) !== 'year'){
					$fee_id = $arr[0];
					$col = $arr[1];
					if($col != NULL){
						$stud_due = db_query("
						  SELECT * from {$fees_student_due} where adm_no = :an and fee_id = :fi;", array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id)
						);
						foreach($stud_due as $sd){
							if($v['c5'] > $sd->$col){
								variable_set('fee_payment_error', 'error');
							}
							if($v['c5'] < 0){
								variable_set('fee_payment_error', 'error');
							}
						}
					}
				}elseif(substr($k, 0, 4) == 'fine'){
					global $base_url;
					$url = $base_url.'/admin/fees/fine/edit-delete';
					if($v['c5'] > 0){
						if($v['c4'] == NULL){
							drupal_set_message('You cannot exempt fine here. Only advance can be adjusted along fine. You can delete this fine, <a href = "'.$url.'">here.</a>', 'error');
							variable_set('fee_payment_error', 'error');
						}
						if(!in_array($v['c4'], $adv)){
							drupal_set_message('Please enter the Advance ID from the advance table displayed along side.','error');
							variable_set('fee_payment_error', 'error');
							$form_state['rebuild'] = TRUE;
						}
					}
					
					$arr = explode('#', $k, 2);
					$fine_id = substr($arr[0], 4);
					$mon = $arr[1];
					$studs_fine = db_query("
							SELECT * from {$fine_table} where adm_no = :an and month = :mon and id = :id;",
							array(':an' => $form_state['values']['adm_no'], ':mon' => $mon, ':id' => $fine_id)
					);
					foreach($studs_fine as $sf){
						if($sf->amount_paid < $sf->amount_to_be_paid){
							$amt_to_pay = $sf->amount_to_be_paid - $sf->amount_paid;
							if($form_state['values']['fine'.$sf->id]['fine'.$sf->id.'#'.$mon]['c5'] > $amt_to_pay){
								variable_set('fee_payment_error', 'error');
							}
							if($v['c5'] < 0){
								variable_set('fee_payment_error', 'error');
							}
						}
					}
				}
			}
		}
	}
	
	$is_payment_error = variable_get('fee_payment_error');
	$is_adm_no_error = variable_get('fee_adm_no_error');
	if($is_payment_error != 'error' && $is_adm_no_error != 'error'){
		variable_set('fee_payment_error', NULL);
		variable_set('fee_adm_no_error', NULL);
		$session_id = (string)variable_get('essa_sid');
		$fees_student_table = 'essa_'.$session_id.'_fees_student_table';
		$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
		$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
		$payment_history = 'essa_'.$session_id.'_fees_payment_history';
		$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
		$basic_info_table = 'essa_'.$session_id.'_basicinfo';
		global $user;
				
		$options = $form_state['values']['options'];
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
					if(isset($form_state['values'][$stud->fee_id.'-'.$col][$stud->fee_id.'-'.$col]['c5'])){
						$total = $total + $form_state['values'][$stud->fee_id.'-'.$col][$stud->fee_id.'-'.$col]['c5'];
					}
		    }
			}
		}
		$advance = db_query(
			"SELECT * from $advance_table where adm_no = :an;", array(':an' => $form_state['values']['adm_no'])
		);
		
		foreach($advance as $ad){
			$flag = 1;
			$adv[] = $ad->fee_id;
		}
		
		if($flag == 1){
			foreach($form_state['input'] as $key => $val){
				if(is_array($val)){
					foreach($val as $k => $v){
						if(substr($k, 0, 4) == 'fine'){
							$arr = explode('#', $k, 2);
							$fine_id = substr($arr[0], 4);
							$mon = $arr[1];
							
							if($v['c5'] != 0){
								if($v['c4'] != NULL){
									if(!in_array($v['c4'], $adv)){
										drupal_set_message('Please enter the Advance ID from the advance table displayed along side.','error');
										$form_state['rebuild'] = TRUE;
									}else{
										$amount = 0;
										$advance = db_query(
											"SELECT * from $advance_table where adm_no = :an and fee_id = :fi;",
											array(':an' => $form_state['values']['adm_no'], ':fi' => $v['c4'])
										);
										foreach($advance as $ad){
											$amount = $amount + $ad->amount_remaining;
											$receipt_no = $ad->receipt_no;
										}
										
										if($v['c5'] > $amount){
											drupal_set_message('You can\'t enter an amount greater than the advance.','error');
											$form_state['rebuild'] = TRUE;
										}else{
											$amt_remaining = 0;
											$advance = db_query(
												"SELECT * from $advance_table where adm_no = :an and fee_id = :fi;", array(
													':an' => $form_state['values']['adm_no'], ':fi' => $v['c4'])
											);
											foreach($advance as $ad){
												$amt_remaining = $amt_remaining + $ad->amount_remaining;
											}
											$amount_deducted = 0;
											$past_student_advance = db_query("
												SELECT * from {$advance_table} where adm_no = :an and fee_id = :fi;", array(
													':an' => $form_state['values']['adm_no'], ':fi' => $v['c4'])
											);
											foreach($past_student_advance as $psa){
												$new_remaining =  $v['c5'] - $psa->amount_remaining;
												if($new_remaining < 0){
													if($amount_deducted == 0){
														$amount_deducted = $v['c5'];
													}
													$ra = $psa->amount_remaining - $amount_deducted;
													
													db_update($advance_table) // Table name no longer needs {}
														->fields(array('amount_remaining' => $ra))
														->condition(db_and()
															->condition('adm_no', $form_state['values']['adm_no'])
															->condition('fee_id', $v['c4'])
															->condition('receipt_no', $psa->receipt_no)
														)
														->execute();
													
													$amt_paid = 0;
													$prev_fine = db_query("
														SELECT * from {$fees_student_fine} where id = :id;", array(
															':id' => $fine_id)
													);
													foreach($prev_fine as $find){
														$amt_paid  = $find->amount_paid + $v['c5'];
													}
													
													db_update($fees_student_fine) // Table name no longer needs {}
														->fields(array('amount_paid' => $amt_paid, 'receipt_no' => $receipt_no))
														->condition(db_and()
															->condition('id', $fine_id)
															->condition('month', $mon)
														)
														->execute();
													
													global $user;
													db_insert($fees_student_adjustement)
														->fields (array(
															'fee_id' => $v['c4'],
															'month' => $mon,
															'to_fee_id' => NULL,
															'to_fine_id' => $fine_id,
															'adm_no' => $form_state['values']['adm_no'],
															'reason' => $form_state['values']['reason'],
															'amount' => $v['c5'],
															'uid' => $user->uid,
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
							$arr = explode("-", $k, 2);
							$fee_id = $arr[0];
							$col = $arr[1];
							if($v['c5'] != 0){
								if($v['c4'] != 'ex' && $v['c4'] != NULL){
									if(!in_array($v['c4'], $adv)){
										drupal_set_message('Please enter the Advance ID from the advance table displayed along side.','error');
										$form_state['rebuild'] = TRUE;
									}else{
										$amount = 0;
										$advance = db_query(
											"SELECT * from $advance_table where adm_no = :an and fee_id = :fi;", array(':an' => $form_state['values']['adm_no'], ':fi' => $v['c4'])
										);
										foreach($advance as $ad){
											$amount = $amount + $ad->amount_remaining;
											$receipt_no = $ad->receipt_no;
										}
										if($v['c5'] > $amount){
											drupal_set_message('You can\'t enter an amount greater than the advance.','error');
											$form_state['rebuild'] = TRUE;
										}else{
											$amt_remaining = 0;
											$advance = db_query(
												"SELECT * from $advance_table where adm_no = :an and fee_id = :fi;", array(
													':an' => $form_state['values']['adm_no'], ':fi' => $v['c4'])
											);
											foreach($advance as $ad){
												$amt_remaining = $amt_remaining + $ad->amount_remaining;
											}
											$amount_deducted = 0;
											$past_student_advance = db_query("
												SELECT * from {$advance_table} where adm_no = :an and fee_id = :fi;", array(
													':an' => $form_state['values']['adm_no'], ':fi' => $v['c4'])
											);
											foreach($past_student_advance as $psa){
												$new_remaining =  $v['c5'] - $psa->amount_remaining;
												if($new_remaining > 0){
													$amount_deducted = $psa->amount_remaining;
													db_update($advance_table) // Table name no longer needs {}
														->fields(array('amount_remaining' => 0))
														->condition(db_and()
															->condition('adm_no', $form_state['values']['adm_no'])
															->condition('fee_id', $v['c4'])
															->condition('receipt_no', $psa->receipt_no)
														)
														->execute();
												}elseif($new_remaining < 0){
													if($amount_deducted == 0){
														$amount_deducted = $v['c5'];
													}
													$ra = $psa->amount_remaining - $amount_deducted;
													
													db_update($advance_table) // Table name no longer needs {}
														->fields(array('amount_remaining' => $ra))
														->condition(db_and()
															->condition('adm_no', $form_state['values']['adm_no'])
															->condition('fee_id', $v['c4'])
															->condition('receipt_no', $psa->receipt_no)
														)
														->execute();
												}
											}
											$studs = db_query("
												SELECT * from {$fees_student_due} where adm_no = :an and $col = $col;", array(':an' => $form_state['values']['adm_no'])
											);
											foreach($studs as $stud){
												if($stud->fee_id == $fee_id){
													$update = $stud->$col - $v['c5'];
													db_merge($fees_student_due)
														->key(array('fee_id' => $fee_id, 'adm_no' => $form_state['values']['adm_no']))
														->fields (array(
															$col => $update,
														)
													)
													->execute();
												}
											}
											
											$existing_amt = 0;
											$n_fee_student_payment = db_query(
												"SELECT * from $fees_student_payment where fee_id = :fi and adm_no = :an and month = :mon;",
												array(':fi' => $fee_id, ':an' => $form_state['values']['adm_no'], ':mon' => $col)
											);
											foreach($n_fee_student_payment as $fs){
												$existing_amt = $fs->amount;
											}
											$new_amt = $existing_amt + $v['c5'];
											
											db_merge($fees_student_payment)
												->key(array('fee_id' => $fee_id, 'adm_no' => $form_state['values']['adm_no'], 'month' => $col))
												->fields (array(
													'fee_id' => $fee_id,
													'month' => $col,
													'adm_no' => $form_state['values']['adm_no'],
													'receipt_no' => $receipt_no,
													'amount' => $new_amt,
												)
											)
											->execute();
											
											db_insert($fees_student_adjustement)
												->fields (array(
													'fee_id' => $v['c4'],
													'month' => $col,
													'to_fee_id' => $fee_id,
													'to_fine_id' => NULL,
													'adm_no' => $form_state['values']['adm_no'],
													'reason' => $form_state['values']['reason'],
													'amount' => $v['c5'],
													'uid' => $user->uid
												)
											)
											->execute();
										}
									}
								}elseif($v['c4'] == 'ex'){
									db_insert($fees_student_adjustement)
										->fields (array(
											'fee_id' => NULL,
											'to_fee_id' => $fee_id,
											'month' => $col,
											'adm_no' => $form_state['values']['adm_no'],
											'reason' => $form_state['values']['reason'],
											'amount' => $v['c5'],
											'uid' => $user->uid
										)
									)
									->execute();
									
									$studs = db_query("
										SELECT * from {$fees_student_due} where adm_no = :an and $col = $col;", array(':an' => $form_state['values']['adm_no'])
									);
									foreach($studs as $stud){
										if($stud->fee_id == $fee_id){
											$update = $stud->$col - $v['c5'];
											db_merge($fees_student_due)
												->key(array('fee_id' => $fee_id,'adm_no' => $form_state['values']['adm_no']))
												->fields (array(
													$col => $update,
												)
											)
											->execute();
										}
									}
								}elseif($v['c4'] == NULL){
									$form_state['rebuild'] = TRUE;
									drupal_set_message('You can\'t leave Advance ID blank. Please enter "ex", if you want to give rebate.','warning');
								}
							}
						}
					}
				}
			}
		}else{
			adjustment_db_entry($form, $form_state);
			drupal_set_message('The adjustment was processed successfullly.','status');
		}
	}else{
		drupal_set_message('The adjustment was not processed, due to error in values. Please check the values before submitting.', 'error');
		$form_state['rebuild'] = TRUE;
		variable_set('fee_payment_error', NULL);
		variable_set('fee_adm_no_error', NULL);
	}
}

/**
 *Implements DB entry
 */
function adjustment_db_entry($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_adjustement = 'essa_'.$session_id.'_fees_student_adjustement';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history = 'essa_'.$session_id.'_fees_payment_history';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$advance_table = 'essa_'.$session_id.'_fees_student_advance';
	global $user;
	$today_date = strtotime(date('d-M-Y'));
	$flag = 0;
	$adv = array();
	
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
							if($v['c5'] > $sd->$col){
								variable_set('fee_payment_error', 'error');
							}
							if($v['c5'] < 0){
								variable_set('fee_payment_error', 'error');
							}
						}
					}
				}
			}
		}
	}
		
	drupal_add_css(drupal_get_path('module', 'fee') . '/fees.css');
	$is_payment_error = variable_get('fee_payment_error');
	$is_adm_no_error = variable_get('fee_adm_no_error');
	if($is_payment_error != 'error' && $is_adm_no_error != 'error'){
		variable_set('fee_payment_error', NULL);
		variable_set('fee_adm_no_error', NULL);
		$session_id = (string)variable_get('essa_sid');
		$fees_student_table = 'essa_'.$session_id.'_fees_student_table';
		$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
		$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
		$payment_history = 'essa_'.$session_id.'_fees_payment_history';
		$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
		$basic_info_table = 'essa_'.$session_id.'_basicinfo';
		global $user;
				
		$options = $form_state['values']['options'];
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
					if(isset($form_state['values'][$stud->fee_id.'-'.$col][$stud->fee_id.'-'.$col]['c5'])){
						$total = $total + $form_state['values'][$stud->fee_id.'-'.$col][$stud->fee_id.'-'.$col]['c5'];
					}
		    }
			}
		}
		
		if($total != NULL && $total != 0){
			//$pay_dt = strtotime($form_state['values']['pay_date']);
			//
			//$ph = db_query("
			//	SELECT * from {$payment_history} where adm_no = :an and payment_date = :pd and amount = :am;", array(':an' => $form_state['values']['adm_no'], ':pd' => $pay_dt, ':am' => $total)
			//);
			//foreach($ph as $p){
			//	$receipt_no = $p->id;
			//}
			
			foreach($form_state['values'] as $val){
				if(is_array($val)){
					foreach($val as $k => $v){
						if($k != 'fine' && $k != 'total'){
							$arr = explode("-", $k, 2);
							$fee_id = $arr[0];
							$col = $arr[1];
							
							if($v['c5'] > 0){
								db_insert($fees_student_adjustement)
									->fields (array(
										'fee_id' => NULL,
										'to_fee_id' => $fee_id,
										'month' => $col,
										'adm_no' => $form_state['values']['adm_no'],
										'reason' => $form_state['values']['reason'],
										'amount' => $v['c5'],
										'uid' => $user->uid
									)
								)
								->execute();
							}
								
							$studs = db_query("
							  SELECT * from {$fees_student_due} where adm_no = :an and $col = $col;", array(':an' => $form_state['values']['adm_no'])
							);
							foreach($studs as $stud){
								if($stud->fee_id == $fee_id){
									$update = $stud->$col - $v['c5'];
									db_merge($fees_student_due)
										->key(array('fee_id' => $fee_id,'adm_no' => $form_state['values']['adm_no']))
										->fields (array(
											$col => $update,
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
			drupal_set_message('Nothing to process....', 'warning');
		}
	}else{
		$form_state['rebuild'] = TRUE;
		variable_set('fee_payment_error', NULL);
		variable_set('fee_adm_no_error', NULL);
	}
}

/**
 *Implements function to recalculate total.
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
							if($v['c5'] > $sd->$col){
								variable_set('fee_payment_error', 'error');
								$form['fs'] = array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "color: RED;"> You can\'t collect an amount greater than the alloted amount or the amount due for that fee ID.</h3>',
									'#prefix' => '<div id = "adjustment_total">',
									'#suffix' => '</div>',
									'#validated' => TRUE,
								);
								return $form['fs'];
							}else{
								variable_set('fee_payment_error', NULL);
							}
							if($v['c5'] < 0){
								variable_set('fee_payment_error', 'error');
								$form['fs'] = array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "color: RED;"> You can\'t enter negative numbers. </h3>',
									'#prefix' => '<div id = "adjustment_total">',
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
	}elseif((substr($form_state['triggering_element']['#name'], 0, 4)) == 'fine'){
		foreach($form_state['values'] as $val){
			if(is_array($val)){
				foreach($val as $k => $v){
					if(substr($k, 0, 4) == 'fine'){
						$arr = explode('#', $k, 2);
						$fine_id = substr($arr[0], 4);
						$mon = $arr[1];
						$studs_fine = db_query("
							SELECT * from {$fine_table} where adm_no = :an and month = :mon and id = :id;",
							array(':an' => $form_state['values']['adm_no'], ':mon' => $mon, ':id' => $fine_id)
						);
						foreach($studs_fine as $sf){
							if($sf->amount_paid < $sf->amount_to_be_paid){
								$amt_to_pay = $sf->amount_to_be_paid - $sf->amount_paid;
								if($form_state['values']['fine'.$sf->id]['fine'.$sf->id.'#'.$mon]['c5'] > $amt_to_pay){
									variable_set('fee_payment_error', 'error');
									$form['fs'] = array(
										'#type' => 'markup',
										'#markup' => '<h3 style = "color: RED;"> You can\'t collect an amount greater than the alloted amount or the amount due for that fine ID.
										</h3>',
										'#prefix' => '<div id = "adjustment_total">',
										'#suffix' => '</div>',
										'#validated' => TRUE,
									);
									
									return $form['fs'];
								}else{
									variable_set('fee_payment_error', NULL);
								}
								if($v['c5'] < 0){
									variable_set('fee_payment_error', 'error');
									$form['fs'] = array(
										'#type' => 'markup',
										'#markup' => '<h3 style = "color: RED;"> You can\'t enter negative numbers. </h3>',
										'#prefix' => '<div id = "adjustment_total">',
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
        $total = $total + $form_state['values'][$stud->fee_id.'-'.$col][$stud->fee_id.'-'.$col]['c5'];
      }
			
			$studs_fine = db_query("
				SELECT * from {$fine_table} where adm_no = :an and month = :mon;", array(':an' => $form_state['values']['adm_no'], ':mon' => $col)
			);
			foreach($studs_fine as $sf){
				$total = $total + $form_state['values']['fine'.$sf->id]['fine'.$sf->id.'#'.$col]['c5'];
			}
    }
  }
	
	$form['lts']['total']['#value'] = $total;//$stud->fee_id.'_'.$col;//$form_state['values'][$stud->fee_id.'_'.$col][$stud->fee_id.'_'.$col]['c4'];
	return $form['lts']['total'];
}

/**
 *Implements ajax callback
 */
function adjustment_student_detail_ajax($form, &$form_state){
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
				"SELECT * from $advance_table where adm_no = :an and amount_remaining <> 0;", array(':an' => $form_state['values']['adm_no'])
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
		          '#markup' => '<h3 style = "text-align: left !important;">'. $particular .'</h3>',
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
					'#markup' => '<p>Enter the Fee ID in the adjustement table to adjust the advance amount along a particular fee.<p>',
				);
				
				$form['fs']['adfs']['advance_tab'] = array(
					'#theme' => 'advance_table',
					'rows' => $row,
					'#prefix' => '<div id = "adv_tab">',
					'#suffix' => '</div>',
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

/**
 *Implements ajax callback
 */
function adjustment_fee_fill($form, &$form_state){
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