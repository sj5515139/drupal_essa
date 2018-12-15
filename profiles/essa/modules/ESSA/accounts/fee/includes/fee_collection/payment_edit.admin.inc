<?php
/**
 *Implements page callback function - fee_payment
 */
function payment_history_edit($form, &$form_state){
  $form['history_adm_no'] = array(
    '#type' => 'textfield',
    '#title' => t('Admission No.'),
    '#size' => 10,
		'#autocomplete_path' => 'adm_no/autocomplete',
		'#required' => TRUE,
  );
	
  $form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Edit',
		'#prefix' => '<div id = "edit-payment">',
		'#suffix' => '</div>'
	);
  
	return $form;
}

function payment_history_edit_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$stud_table = 'essa_'.$session_id.'_master_student_table';
	
	$stud_info = db_query(
		"SELECT * from $student_table where adm_no = :adm_no AND status = 1;", array(':adm_no' => $form_state['values']['history_adm_no'])
	);
	foreach($stud_info as $si){
		$test = $si->adm_no;
	}
	
	if(isset($test)){
		global $user;
		variable_set('fee_adm_no_edit_'.$user->uid, $form_state['values']['history_adm_no']);
		$url = 'edit-fee';
		$form_state['redirect'] = $url;
	}else{
		drupal_set_message('Entered admission no. is not present in the system.','error');
	}
}

function payment_history_table($form, &$form_state){
  $session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student_table';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history = 'essa_'.$session_id.'_fees_payment_history';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
  $basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	global $user;
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Commit',
		'#submit' => array('payment_history_table_submit'),
	);
	
	$binfo = db_query("
    SELECT * from {$basic_info_table};
  ");
  foreach($binfo as $info){
  	$start_date = $info->academicyearstart;
  }
	
	$end_date = date('d-m-Y');
  $start = new DateTime($start_date);
  $start->modify('first day of this month');
  $dt = str_replace('_','-',$end_date);
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
  
  $adm_no = variable_get('fee_adm_no_edit_'.$user->uid);
	$form['adm_no'] = array(
		'#type' => 'value',
		'#value' => $adm_no,
	);
 	
	$sinfo = db_query("
    SELECT * from {$student_table} where adm_no = :an AND status = 1;", array(':an' => $adm_no)
  ); 
  foreach($sinfo as $info){
		$name = $info->first_name.' '.$info->last_name;
		$class = $info->class.' - '.$info->section;
	}
  
	$form['student_info'] = array(
		'#type' => 'markup',
		'#markup' => '<div style = "line-height: 0.8em; float: right; margin-right: 30px;"><h2>You are editing payment history of - </h2><p style = "float: left; width: 100px;">Adm No.</p><h2>'.$adm_no.'</h2><p style = "float: left; width: 100px;">Name</p><h2>'.$name.'</h2><p style = "float: left; width: 100px;">Class</p><h2>'.$class.'</h2></div>',
	);
	
	$total = 0;
	$student_payment = db_query("
    SELECT * from {$payment_history} where adm_no = :an;", array(':an' => $adm_no)
  );
  foreach($student_payment as $sp){
		$total = $total + $sp->amount;
	}
	
	$total_due = 0;
	$student_due = db_query("
    SELECT * from {$fees_student_due} where adm_no = :an;", array(':an' => $adm_no)
  );
	foreach($student_due as $sd){
		foreach($columns as $col){
			$total_due = $total_due + $sd -> $col;
		}
	}
  
	$total_fine = 0;
	$student_fine = db_query("
    SELECT * from {$fees_student_fine} where adm_no = :an;", array(':an' => $adm_no)
  );
  foreach($student_fine as $sf){
		$total_fine = $total_fine + $sf->amount_paid;
	}
	
	$form['fee_summary'] = array(
		'#type' => 'markup',
		'#markup' => '<div style = "line-height: 0.8em; float: left; width: 40%; margin-left: 30px;"><h2 style = "width: 250px; float: left;">Total fee paid till date - </h2><h2><b>'.$total.'</b> INR</h2><h2 style = "width: 250px; float: left;">Total due till date - </h2><h2><b>'.$total_due.'</b> INR</h2><h2 style = "width: 250px; float: left;">Total fine paid till date - </h2><h2><b>'.$total_fine.'</b> INR</h2></div>',
	);
	
  $def_dt = date('d-m-Y');
	$format = 'd-m-Y';
  $student_payment = db_query("
    SELECT * from {$payment_history} where adm_no = :an;", array(':an' => $adm_no)
  );
  foreach($student_payment as $sp){
		
		$total = 0;
		$row[$sp->id] = array(
      '#tree' =>TRUE,
      $sp->id => array(  //Generating unique array id for every form element
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'. $sp->id.'</h3>',
        ),
        'c2' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'. $sp->uid.'</h3>',
        ),
        'c3' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$sp->amount.'</h3>',
        ),
        'c4' =>array(
					'#type' => 'markup',
          '#markup' => '<h3>'.date('d-m-Y', $sp->payment_date).'</h3>',
        ),
        'c5' =>array(
          '#type' => 'value',
          '#value' => $sp->amount,
        ),
        'c6' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
        'c7' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
				'c8' => array(
          '#type' => 'submit',
          '#value' => 'Delete',
					'#name' => $sp->id,
			    '#prefix' => '<div id = "delete_fee">',
			    '#suffix' => '</div>',
					'#submit' => array('delete_fee_history'),
        ),
      ),
    );
		
		$particulars = NULL;
		$detail_row = array();
    $student_payment_detail = db_query("
      SELECT * from {$fees_student_payment} where receipt_no = :rid;", array(':rid' => $sp->id)
    );
		foreach($student_payment_detail as $spd){
			$fee_detail = db_query("
			  SELECT * from {$fees_table} where fee_id = :fid;", array(':fid' => $spd->fee_id)
			);
			foreach($fee_detail as $fd){
				$particulars = $fd->particulars;
			}
			$total = $total + $spd->amount;
			if($particulars == NULL){
				$particulars = '<span style = "color: RED;">Deleted fee</span>';
				$detail_row[$sp->id.'-'.$spd->fee_id.'/'.$spd->month] = array(
					'#tree' =>TRUE,
					$sp->id.'-'.$spd->fee_id.'/'.$spd->month => array(  //Generating unique array id for every form element
				    'c1' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3></h3>',
				    ),
				    'c2' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3></h3>',
				    ),
				    'c3' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3></h3>',
				    ),
				    'c4' => array(
				      '#type' => 'markup',
				      '#markup' => '<h3></h3>',
				    ),
				    'c5' => array(
				      '#type' => 'markup',
				      '#markup' => '<h3 style = "text-align: left;">'.$particulars.'</h3>',
				    ),
				    'c6' => array(
				      '#type' => 'markup',
				      '#markup' => '<h3 style = "text-align: right;color: RED;">'.$spd->month.'</h3>',
				    ),
				    'c7' => array(
				      '#type' => 'textfield',
				      '#value' => $spd->amount,
				      '#size' => 10,
							'#ajax' => array(
								'event' => 'blur',
							  'callback' => 'recalculate_total',
								'wrapper' => 'total'.$sp->id,
							  'method' => 'replace',
							  'effect' => 'fade',
							),
							'#disabled' => TRUE,
				    ),
						'c8' => array(
				      '#type' => 'markup',
				      '#markup' => '<h3></h3>',
				    ),
				  ),
				);
			}else{
				$detail_row[$sp->id.'-'.$spd->fee_id.'/'.$spd->month] = array(
					'#tree' =>TRUE,
					$sp->id.'-'.$spd->fee_id.'/'.$spd->month => array(  //Generating unique array id for every form element
				    'c1' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3></h3>',
				    ),
				    'c2' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3></h3>',
				    ),
				    'c3' =>array(
				      '#type' => 'markup',
				      '#markup' => '<h3></h3>',
				    ),
				    'c4' => array(
				      '#type' => 'markup',
				      '#markup' => '<h3></h3>',
				    ),
				    'c5' => array(
				      '#type' => 'markup',
				      '#markup' => '<h3 style = "text-align: left;">'.$particulars.'</h3>',
				    ),
				    'c6' => array(
				      '#type' => 'markup',
				      '#markup' => '<h3 style = "text-align: right;">'.$spd->month.'</h3>',
				    ),
				    'c7' => array(
				      '#type' => 'textfield',
				      '#value' => $spd->amount,
				      '#size' => 10,
							'#ajax' => array(
								'event' => 'blur',
							  'callback' => 'recalculate_total',
								'wrapper' => 'total'.$sp->id,
							  'method' => 'replace',
							  'effect' => 'fade',
							),
				    ),
						'c8' => array(
				      '#type' => 'markup',
				      '#markup' => '<h3></h3>',
				    ),
				  ),
				);
			}
			
			$particulars = NULL;
    }
		
		$advance_row = array();
		$remaining_advance_row = array();
		$existing_advance = 0;
		$existing_advance_remaining = 0;
		$fees_advance = 'essa_'.$session_id.'_fees_student_advance';
		$student_advance = db_query("
			SELECT * from {$fees_advance} where adm_no = :an and receipt_no = :rn;", array(
				':an' => $adm_no, ':rn' => $sp->id)
		);
		foreach($student_advance as $sa){
			$existing_advance = $existing_advance + $sa->amount;
			$existing_advance_remaining = $existing_advance_remaining +$sa->amount_remaining;
		}
		if($existing_advance != 0){
			$advance_row['advance'.$sp->id] = array(
				'#tree' =>TRUE,
				'advance'.$sp->id => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3></h3>',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3></h3>',
						),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3></h3>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h3></h3>',
					),
					'c5' =>array(
						'#type' => 'markup',
						'#markup' => '<h3></h3>',
					),
					'c6' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: right;">Advance - </h3>',
					),
					'c7' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$existing_advance.'</h3>',
					),
					'c8' =>array(
						'#type' => 'markup',
						'#markup' => '<h3></h3>',
					),
				),
			);
			
			$remaining_advance_row['remaining_advance'.$sp->id] = array(
				'#tree' =>TRUE,
				'remaining_advance'.$sp->id => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3></h3>',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3></h3>',
						),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3></h3>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h3></h3>',
					),
					'c5' =>array(
						'#type' => 'markup',
						'#markup' => '<h3></h3>',
					),
					'c6' =>array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "text-align: right;">Advance Remaining - </h3>',
					),
					'c7' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.$existing_advance_remaining.'</h3>',
					),
					'c8' =>array(
						'#type' => 'markup',
						'#markup' => '<h3></h3>',
					),
				),
			);	
		}
		
    
		$fine_row = array();
		$student_fine_detail = db_query("
      SELECT * from {$fees_student_fine} where receipt_no = :pid;", array(':pid' => $sp->id)
    );
    foreach($student_fine_detail as $sfd){
			$total = $total + $sfd->amount_paid;
      $fine_row['fine#'.$sp->id.'-'.$sfd->id] = array(
        '#tree' =>TRUE,
        'fine#'.$sp->id.'-'.$sfd->id => array(  //Generating unique array id for every form element
          'c1' =>array(
            '#type' => 'markup',
            '#markup' => '<h3></h3>',
          ),
          'c2' =>array(
            '#type' => 'markup',
            '#markup' => '<h3></h3>',
          ),
          'c3' =>array(
            '#type' => 'markup',
            '#markup' => '<h3></h3>',
          ),
          'c4' => array(
		        '#type' => 'markup',
            '#markup' => '<h3></h3>',
          ),
          'c5' => array(
            '#type' => 'markup',
            '#markup' => '<h3 style = "text-align: left;">'.$sfd->particulars.'</h3>',
          ),
          'c6' => array(
            '#type' => 'markup',
            '#markup' => '<h3 style = "text-align: right;">'.$sfd->month.'</h3>',
          ),
          'c7' => array(
            '#type' => 'textfield',
            '#value' => $sfd->amount_paid,
						'#size' => 10,
						'#ajax' => array(
							'event' => 'blur',
						  'callback' => 'recalculate_total',
						  'wrapper' => 'total'.$sp->id,
						  'method' => 'replace',
							'effect' => 'fade',
						),
          ),
					'c8' => array(
					  '#type' => 'submit',
					  '#value' => 'Delete',
						'#name' => $sfd->id,
					  '#prefix' => '<div id = "delete_fine">',
					  '#suffix' => '</div>',
						'#submit' => array('delete_fine'),
					),
        ),
      );
    }
    
		$total_row['total'.$sp->id] = array(
      '#tree' =>TRUE,
      'total'.$sp->id => array(  //Generating unique array id for every form element
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
        'c2' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
        'c3' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
        'c4' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
        'c5' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
        'c6' =>array(
          '#type' => 'markup',
          '#markup' => '<h3 style = "text-align: right;">Total - </h3>',
        ),
        'c7' =>array(
          '#type' => 'markup',
					'#markup' => '<h3 style = "text-align: left;">'.$total.'</h3>',
					'#prefix' => '<div id = "total'.$sp->id.'">',
					'#suffix' => '</div>',
					'#name' => $sp->id,
        ),
				'c8' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
      ),
    );
		
		$format = 'd-m-Y';
		$def_dt = date('d-m-Y');
		$new_date['date'.$sp->id] = array(
      '#tree' =>TRUE,
      'date'.$sp->id => array(  //Generating unique array id for every form element
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
        'c2' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
        'c3' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
        'c4' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
        'c5' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
        'c6' =>array(
          '#type' => 'markup',
          '#markup' => '<h3 style = "text-align: right; font-size: 14px;">New Payment Date</h3>',
        ),
        'c7' =>array(
					'#type' => 'date_popup',
					'#size' => 15,
					'#date_label_position' => 'within',
					'#attributes' => array('placeholder' => 'dd-mm-yyyy'),
					'#date_format' => 'd-m-Y',
					'#default_value' => $def_dt,
					'#date_year_range' => '0:+1',
        ),
				'c8' =>array(
          '#type' => 'markup',
          '#markup' => '<h3></h3>',
        ),
      ),
    );
    
		$row = array_merge($row, $detail_row);
		$row = array_merge($row, $fine_row);
		$row = array_merge($row, $total_row);
		$row = array_merge($row, $advance_row);
		$row = array_merge($row, $remaining_advance_row);
		$row = array_merge($row, $new_date);
		$form[$sp->id] = array(
			'#theme' => 'edit_payment_history_table',
			'rows' => $row,
		);
		
		$total_row = $detail_row = $row = $new_date = $fine_row = NULL;
  }
	
	return $form;
}

function recalculate_total($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history = 'essa_'.$session_id.'_fees_payment_history';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	global $user;
	variable_set('fee_error'.$user->uid,NULL);
	$total = 0;
	$arr = explode("-", $form_state['triggering_element']['#name'], 2);
	if((substr($arr[0], 0, 4)) !== 'fine'){
		$pay_id = $arr[0];
	}else{
		$arr1 = explode("#", $arr[0], 2);
		$pay_id = $arr1[1];
	}
	
	foreach($form_state['input'] as $key => $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				$arr = explode("-", $k, 2);
				if((substr($arr[0], 0, 4)) !== 'fine'){
					$pay_id_key = $arr[0];
				}else{
					$arr1 = explode("#", $arr[0], 2);
					$pay_id_key = $arr1[1];
				}
				if($pay_id === $pay_id_key){
					if(is_numeric($v['c7'])){
						$total = $total + $v['c7'];
					}
				}
			}
		}
	}
		
	foreach($form_state['input'] as $key => $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				$arr = explode("-", $k, 2);
				if((substr($arr[0], 0, 4)) !== 'fine'){
					$pay_id_key = $arr[0];
				}else{
					$arr1 = explode("#", $arr[0], 2);
					$pay_id_key = $arr1[1];
				}
				if((substr($arr[0], 0, 4)) !== 'fine' && $pay_id === $pay_id_key){
					preg_match('~-(.*?)/~', $k, $fee_id);
					$id = $fee_id[1];
					$arr = explode("/", $k, 2);
					$col = $arr[1];
					$stud_fees = db_query("
						SELECT * from {$fees_student_table} where adm_no = :an and fee_id = :fi;",
						array(':an' => $form_state['values']['adm_no'], ':fi' => $id)
					);
					foreach($stud_fees as $sf){
						if($v['c7'] > $sf->$col){
							variable_set('fee_error'.$user->uid,'error');
							$form['fs'] = array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "color: RED;"> You can\'t enter an amount greater than the alloted amount. </h3>',
								'#prefix' => '<div id = "total'.$pay_id.'">',
								'#suffix' => '</div>',
								'#validated' => TRUE,
							);
							return $form['fs'];
						}else{
							variable_set('fee_error'.$user->uid,NULL);
						}
						if($v['c7'] < 0){
							variable_set('fee_error'.$user->uid,'error');
							$form['fs'] = array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "color: RED;"> You can\'t enter negative numbers. </h3>',
									'#prefix' => '<div id = "total'.$pay_id.'">',
									'#suffix' => '</div>',
									'#validated' => TRUE,
							);
							return $form['fs'];
						}else{
							variable_set('fee_error'.$user->uid,NULL);
						}
					}
				}elseif((substr($arr[0], 0, 4)) == 'fine'){
					$stud_fine = db_query("
						SELECT * from {$fees_student_fine} where adm_no = :an and id = :fi;", array(':an' => $form_state['values']['adm_no'], ':fi' => $arr[1])
					);
					foreach($stud_fine as $sf){
						if($v['c7'] > $sf->amount_to_be_paid){
							variable_set('fee_error'.$user->uid,'error');
							$form['fs'] = array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "color: RED;"> You can\'t enter an amount greater than the alloted amount. </h3>',
								'#prefix' => '<div id = "total'.$pay_id.'">',
								'#suffix' => '</div>',
								'#validated' => TRUE,
							);
							return $form['fs'];
						}else{
							variable_set('fee_error'.$user->uid,NULL);
						}
						if($v['c7'] < 0){
							variable_set('fee_error'.$user->uid,'error');
							$form['fs'] = array(
									'#type' => 'markup',
									'#markup' => '<h3 style = "color: RED;"> You can\'t enter negative numbers. </h3>',
									'#prefix' => '<div id = "total'.$pay_id.'">',
									'#suffix' => '</div>',
									'#validated' => TRUE,
							);
							return $form['fs'];
						}else{
							variable_set('fee_error'.$user->uid,NULL);
						}
					}
				}
			}
		}
	}
	$err = variable_get('fee_error'.$user->uid);
	if($err == 'error'){
		
	}else{
		$form['total'] = array(
			'#type' => 'markup',
			'#markup' => '<h3 style = "text-align: left;">'.$total.'</h3>',
			'#prefix' => '<div id = "total'.$pay_id.'">',
			'#suffix' => '</div>',
			'#name' => $pay_id,
		);
	}
	return $form['total'];
}

/**
 *Implements submit function
 */
function payment_history_table_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history_table = 'essa_'.$session_id.'_fees_payment_history';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$adm_no = $form_state['values']['adm_no'];
	global $user;
	
	$receipts = array();
	$payment_history = db_query("
		SELECT * from {$payment_history_table} where adm_no = :an;", array(':an' => $adm_no)
	);
	foreach($payment_history as $ph){
		$receipts[] = $ph->id;
	}
	
	$fee_payments = array();
	$fines = array();
	$advances = array();
	$dates = array();
	foreach($form_state['input'] as $key => $val){
		$arr = explode("-", $key, 2);
		if(in_array($arr[0], $receipts)){
			$fee_payments[] = $val;
		}
		if(substr($key, 0, 4) == 'fine'){
			$fines[] = $val;
		}
		if(substr($key, 0, 4) == 'date'){
			$dates[] = $val;
		}
	}
	
	foreach($fee_payments as $payments){
		foreach($payments as $key => $val){
			$arr = explode('-', $key, 2);
			$receipt_no = $arr[0];
			$arr1 = explode('/', $arr[1], 2);
			$fee_id = $arr1[0];
			$month = $arr1[1];
			$stud_fees = db_query("
				SELECT * from {$fees_student_table} where adm_no = :an and fee_id = :fi;", array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id)
			);
			foreach($stud_fees as $sf){
				$fee_detail = db_query("
				  SELECT * from {$fees_table} where fee_id = :fi;", array(':fi' => $fee_id)
				);
				foreach($fee_detail as $fd){
					$fee = $fd->particulars;
				}
				if($val['c7'] > $sf->$month){
					variable_set('fee_error'.$user->uid,'error');\
					drupal_set_message('<h3 style = "color: RED;"> You can\'t enter an amount greater than the alloted amount.
						You have enter wrong amount for receipt_no - <b>'.$receipt_no.'</b>, fee - <b>'.$fee.'</b>', 'error');
				}
				if($val['c7'] < 0){
					variable_set('fee_error'.$user->uid,'error');
					drupal_set_message('<h3 style = "color: RED;"> You can\'t enter negative numbers.
						You have enter wrong amount for receipt_no - <b>'.$receipt_no.'</b>, fee - <b>'.$fee.'</b>', 'error');
				}
			}
		}
	}
	
	foreach($fines as $fine){
		foreach($fine as $key => $val){
			$arr = explode('-', $key, 2);
			$fine_id = $arr[1];
			$arr1 = explode('#', $arr[0], 2);
			$receipt_no = $arr1[1];
			$stud_fine = db_query("
				SELECT * from {$fees_student_fine} where adm_no = :an and id = :fi;",
				array(':an' => $form_state['values']['adm_no'], ':fi' => $fine_id)
			);
			foreach($stud_fine as $sf){
				if($val['c7'] > $sf->amount_to_be_paid){
					variable_set('fee_error'.$user->uid,'error');\
					drupal_set_message('<h3 style = "color: RED;"> You can\'t enter an amount greater than the alloted amount.
						You have enter wrong amount for receipt_no - <b>'.$receipt_no.'</b>, fine - <b>'.$sf->particulars.'</b>,
						month - <b>'.$month.'</b></h3>', 'error');
				}
				if($val['c7'] < 0){
					variable_set('fee_error'.$user->uid,'error');
					drupal_set_message('<h3 style = "color: RED;"> You can\'t enter negative numbers.
						You have enter wrong amount for receipt_no - <b>'.$receipt_no.'</b>, fee - <b>'.$fee.'</b>,
						month - <b>'.$month.'</b></h3>', 'error');
				}
			}
		}
	}
	
	$err = variable_get('fee_error'.$user->uid);
	if($err != 'error'){
		foreach($fee_payments as $payments){
			foreach($payments as $key => $val){
				$arr = explode('-', $key, 2);
				$receipt_no = $arr[0];
				$arr1 = explode('/', $arr[1], 2);
				$fee_id = $arr1[0];
				$month = $arr1[1];
				$student_fee_payment = db_query("
				  SELECT * from {$fees_student_payment} where adm_no = :an and receipt_no =  :rn and fee_id = :fi and month = :mon;",
					array(':an' => $adm_no, ':rn' => $receipt_no, ':fi' => $fee_id, ':mon' => $month)
				);
				foreach($student_fee_payment as $sfp){
					if($val['c7'] < $sfp->amount){
						$new_amt = $sfp->amount - $val['c7'];
						db_merge($fees_student_payment)
							->key(array('fee_id' => $fee_id,'adm_no' => $form_state['values']['adm_no'],'month' => $month, 'receipt_no' => $receipt_no))
							->fields (array(
								'amount' => $val['c7'],
							)
						)
						->execute();
						
						$this_payment_history = db_query("
							SELECT * from {$payment_history_table} where id = :rn;", array(':rn' => $receipt_no)
						);
						foreach($this_payment_history as $tph){
							$new_payment = $tph->amount - $new_amt;
							db_merge($payment_history_table)
								->key(array('id' => $receipt_no))
								->fields (array(
									'amount' => $new_payment,
								)
							)
							->execute();
						}
						
						db_merge($fees_student_due)
							->key(array('fee_id' => $fee_id,'adm_no' => $form_state['values']['adm_no']))
							->fields (array(
								$month => $new_amt,
							)
						)
						->execute();
					}else{
						$new_amt = $val['c7'] - $sfp->amount;
						db_merge($fees_student_payment)
							->key(array('fee_id' => $fee_id,'adm_no' => $form_state['values']['adm_no'],'month' => $month, 'receipt_no' => $receipt_no))
							->fields (array(
								'amount' => $val['c7'],
							)
						)
						->execute();
						
						$this_payment_history = db_query("
							SELECT * from {$payment_history_table} where id = :rn;", array(':rn' => $receipt_no)
						);
						foreach($this_payment_history as $tph){
							$new_payment = $tph->amount + $new_amt;
							db_merge($payment_history_table)
								->key(array('id' => $receipt_no))
								->fields (array(
									'amount' => $new_payment,
								)
							)
							->execute();
						}
						
						$current_due = db_query("
							SELECT * from {$fees_student_due} where fee_id = :fi and adm_no = :an;", array(':fi' => $fee_id, ':an' => $form_state['values']['adm_no'])
						);
						foreach($current_due as $cd){
							$new_due = $cd->$month - $new_amt;
						}
						db_merge($fees_student_due)
							->key(array('fee_id' => $fee_id,'adm_no' => $form_state['values']['adm_no']))
							->fields (array(
								$month => $new_due,
							)
						)
						->execute();
					}
				}
			}
		}
		
		// Fine Edit Submit
		foreach($fines as $fine){
			foreach($fine as $key => $val){
				$arr = explode('-', $key, 2);
				$fine_id = $arr[1];
				$arr1 = explode('#', $arr[0], 2);
				$receipt_no = $arr1[1];
				$stud_fine = db_query("
					SELECT * from {$fees_student_fine} where adm_no = :an and id = :fi;",
					array(':an' => $form_state['values']['adm_no'], ':fi' => $fine_id)
				);
				foreach($stud_fine as $stf){
					if($val['c7'] < $stf->amount_paid){
						$new_amt = $stf->amount_paid - $val['c7'];
						db_merge($fees_student_fine)
							->key(array('id' => $fine_id,'adm_no' => $form_state['values']['adm_no']))
							->fields (array(
								'amount_paid' => $val['c7'],
							)
						)
						->execute();
						
						$this_payment_history = db_query("
							SELECT * from {$payment_history_table} where id = :rn;", array(':rn' => $receipt_no)
						);
						foreach($this_payment_history as $tph){
							$new_payment = $tph->amount - $new_amt;
							db_merge($payment_history_table)
								->key(array('id' => $receipt_no))
								->fields (array(
									'amount' => $new_payment,
								)
							)
							->execute();
						}
					}else{
						$new_amt = $val['c7'] - $stf->amount_paid;
						db_merge($fees_student_fine)
							->key(array('id' => $fine_id,'adm_no' => $form_state['values']['adm_no']))
							->fields (array(
								'amount_paid' => $val['c7'],
							)
						)
						->execute();
						
						$this_payment_history = db_query("
							SELECT * from {$payment_history_table} where id = :rn;", array(':rn' => $receipt_no)
						);
						foreach($this_payment_history as $tph){
							$new_payment = $tph->amount + $new_amt;
							db_merge($payment_history_table)
								->key(array('id' => $receipt_no))
								->fields (array(
									'amount' => $new_payment,
								)
							)
							->execute();
						}
					}
				}
			}
		}
		
		//Editing dates
		foreach($dates as $date){
			foreach($date as $key => $val){
				$receipt_no = substr($key, 4);
				if($val['c7']['date'] != NULL){
					$pay_dt = strtotime($val['c7']['date']);
					if($pay_dt > strtotime(date('d-m-Y'))){
						drupal_set_message('You can\'t take payment in future date.','error');
					}else{
						db_merge($payment_history_table)
							->key(array('id' => $receipt_no))
							->fields (array(
									'payment_date' => $pay_dt,
								)
							)
						->execute();
					}
				}
			}
		}
		drupal_set_message('Transactions were edited successfully.');
	}
}


function delete_fee_history($form, &$form_state){
	global $user;
	variable_set('delete-payment-adm_no'.$user->uid, $form_state['values']['adm_no']);
	variable_set('delete-payment-receipt_no'.$user->uid, $form_state['triggering_element']['#name']);
	$session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history = 'essa_'.$session_id.'_fees_payment_history';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$fees_advance = 'essa_'.$session_id.'_fees_student_advance';
	$fees_student_adjustement = 'essa_'.$session_id.'_fees_student_adjustement';
	
	$flag = 0;
	$stud_advance = db_query("
		SELECT * from {$fees_advance} where receipt_no = :rn;", array(':rn' => $form_state['triggering_element']['#name'])
	);
	foreach($stud_advance as $sa){
		if($sa->amount != $sa->amount_remaining){
			$flag = 1;
		}
	}
	
	if($flag == 1){
		global $base_url;
		$url = $base_url.'/admin/fees/payment/adjustments/delete';
		drupal_set_message('This transaction cannot be deleted because advance has been adjusted. Delete corresponding adjustment first, <a href = "'.$url.'">here</a>.','warning');
	}else{
		$url = url('delete-fee', array('absolute' => TRUE));
		$form_state['redirect'] = $url;
	}
}

function delete_fee_pagecallback(){
	return drupal_get_form('delete_fee_confirm');
}

function delete_fee_confirm($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leave_id = variable_get('del_leave_id');
	
	$heading = t('Are you sure to delete this collection.');
	$caption = '<h3>This action can\'t be undone.</h3>';
	
	$cancel_path = 'edit-fee';
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

function delete_fee_confirm_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history = 'essa_'.$session_id.'_fees_payment_history';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$fees_advance = 'essa_'.$session_id.'_fees_student_advance';
	$fees_student_adjustement = 'essa_'.$session_id.'_fees_student_adjustement';
	
	global $user;
	$flag = 0;
	$adm_no = variable_get('delete-payment-adm_no'.$user->uid);
	$receipt_no = variable_get('delete-payment-receipt_no'.$user->uid);
	if($form_state['triggering_element']['#value'] == 'Delete'){
		$student_fee_due = db_query("
		  SELECT * from {$fees_student_due} where adm_no = :an;", array(':an' => $adm_no)
		);
		foreach($student_fee_due as $sfd){
			$student_fee_payment = db_query("
			  SELECT * from {$fees_student_payment} where adm_no = :an and receipt_no =  :rn;", array(':an' => $adm_no, ':rn' => $receipt_no)
			);
			foreach($student_fee_payment as $sfp){
				if($sfd->fee_id == $sfp->fee_id){
					$col = $sfp->month;
					$amount = $sfp->amount + $sfd->$col;
					db_update($fees_student_due) // Table name no longer needs {}
					->fields(array(
							$col => $amount,
						))
					->condition(db_and()
							-> condition('fee_id', $sfp->fee_id, '=')
							->condition('adm_no', $adm_no)
						)
					->execute();
				}
			}
		}
		
		db_delete($payment_history)
		->condition('id', $receipt_no)
		->execute();
		
		db_delete($fees_advance)
		->condition('receipt_no', $receipt_no)
		->execute();
	
		db_delete($fees_student_payment)
			->condition('receipt_no', $receipt_no)
			->execute();
		
		db_update($fees_student_fine) // Table name no longer needs {}
		->fields(array(
				'amount_paid' => 0,
				'receipt_no' => NULL,
			))
		-> condition('receipt_no', $receipt_no, '=')
		->execute();
	}
	$url = url('edit-fee', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
	drupal_set_message('The fee collection was deleted successfully.','status');
}

function delete_fine($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history = 'essa_'.$session_id.'_fees_payment_history';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	
	global $user;
	variable_set('delete-fine-fine_id'.$user->uid, $form_state['triggering_element']['#name']);
	$fine_id = $form_state['triggering_element']['#name'];
	$student_fine = db_query("
		SELECT * from {$fees_student_fine} where id = :fi;", array(':fi' => $fine_id)
	);
	foreach($student_fine as $sf){
		$receipt_no = $sf->receipt_no;
	}
	variable_set('delete-fine-amount'.$user->uid, $form_state['values']['fine#'.$receipt_no.'-'.$fine_id]['fine#'.$receipt_no.'-'.$fine_id]['c7']);
	
	//$form_state['values']['fine#'.$receipt_no.'-'.$fine_id]['fine#'.$receipt_no.'-'.$fine_id]['c7']
	$url = url('delete-fine', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
}

function delete_fine_pagecallback(){
	return drupal_get_form('delete_fine_confirm');
}

function delete_fine_confirm($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leave_id = variable_get('del_leave_id');
	
	$heading = t('Are you sure to delete this fine?');
	$caption = '<h3>This action can\'t be undone.</h3>';
	
	$cancel_path = 'edit-fee';
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

function delete_fine_confirm_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history = 'essa_'.$session_id.'_fees_payment_history';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	global $user;
	$fine_id = variable_get('delete-fine-fine_id'.$user->uid);
	$fine_amount = variable_get('delete-fine-amount'.$user->uid);
	
	$student_fine = db_query("
		SELECT * from {$fees_student_fine} where id = :fi;", array(':fi' => $fine_id)
	);
	foreach($student_fine as $sf){
		$receipt_no = $sf->receipt_no;
	}
	
	$student_payment = db_query("
		SELECT * from {$payment_history} where id = :id;", array(':id' => $receipt_no)
	);
	foreach($student_payment as $sp){
		$new_amount = $sp->amount - $fine_amount;
	}
	db_update($payment_history) // Table name no longer needs {}
		->fields(array(
				'amount' => $new_amount,
			))
		-> condition('id', $receipt_no, '=')
		->execute();
	
	db_update($fees_student_fine) // Table name no longer needs {}
		->fields(array(
				'amount_paid' => 0,
				'receipt_no' => NULL,
			))
		-> condition('id', $fine_id, '=')
		->execute();
		
	if($new_amount == 0){
		db_delete($payment_history)
			->condition('id', $receipt_no)
			->execute();
	}
	
	$url = url('edit-fee', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
	
	drupal_set_message('The fine was deleted successfully.','status');
}

/**
 *Theme function
 */
function theme_edit_payment_history_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Receipt No'), t('Entered By'), t('Total'), t('Payment Date'), t('Particulars'), t('Month'), t('Amount'),t(''));
  
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