<?php
/**
 *Implements page callback function - concession
 */
function student_concession_es($form = array(), &$form_state){
	$session = (string)variable_get('essa_sid');
	$concession_table = 'essa_'.$session.'_fees_concession';
  $form['help'] = array(
		'#type' => 'markup',
		'#markup' => '<h2 style = "color: MAROON;"><strong>NOTE: </strong>In case of entire session, any previous payment will be deleted.</h2>',
	);
	
  $form['adm_no'] = array(
    '#type' => 'textfield',
    '#title' => t('Admission No.'),
    '#autocomplete_path' => 'adm_no/autocomplete',
    '#size' => 30,
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'display_student_detail',
      'wrapper' => 'sd_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#id' => 'adm_no',
    '#required' => TRUE,
  );
	
	$form['sd_wrapper'] = array(
    '#type' => 'container',
    '#prefix' => '<div id = "sd_wrapper" style = "width: 20%; float: right;">',
    '#suffix' => '</div>',
  );
  
  $options = array();
  $concession = db_query("
		SELECT * from {$concession_table}"
	);
	foreach($concession as $con){
		$options[] = $con->name;
	}
	
	 //**********SURAJ************
	global $base_url;
	$url = $base_url.'#overlay=admin/fees/concession/create-concession';
	if($options == NULL){
		drupal_set_message('No Concession has been created. Please create concession, <a href = "'.$url.'">here</a>.', 'warning');
	}
  //**********SURAJ************
	
  $form['con_type'] = array(
    '#type' => 'select',
    '#title' => 'Select concession type',
    '#options' => drupal_map_assoc($options),
    '#ajax' => array(
      'event' => 'change',
      'callback' => 'display_con',
      'wrapper' => 'con',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#required' => TRUE,
  );
  
  $form['fs'] = array(
    '#type' => 'fieldset',
    '#prefix' => '<div id = "con">',
    '#suffix' => '</div>',
  );
  $form['fs']['amount'] = array(
    '#type' => 'textfield',
    '#title' => 'Amount',
    '#size' => 10,
  );
  $form['fs']['percent'] = array(
    '#type' => 'textfield',
    '#title' => 'Percent',
    '#size' => 10,
  );
	
	$form['save'] = array(
    '#type' => 'submit',
    '#value' => 'Save'
  );
	
	return $form;
}

function student_concession_es_validate($form, &$form_state){
	if($form_state['values']['amount'] == NULL && $form_state['values']['percent'] == NULL){
		form_set_error('amount' , 'Both amount and percent can\'t be empty.');
	}
	
	if($form_state['values']['amount'] != NULL){
		if(!is_numeric($form_state['values']['amount'])){
			form_set_error('amount' , 'Amount must be numeric.');
		}elseif($form_state['values']['amount'] <= 0){
			form_set_error('amount' , 'Amount can\'t be less than or equal to zero.');
		}
	}
	
	if($form_state['values']['amount'] != NULL && $form_state['values']['percent'] != NULL){
		form_set_error('amount' , 'Both amount and percent can\'t be alloted. You need to select any one.');
	}
	
	$session = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	$concession = db_query("
		SELECT * from {$concession_table} where name = :n", array(':n' => $form_state['values']['con_type'])
	);
	foreach($concession as $con){
    $con_id = $con->con_id;
		$con_name = $con->name;
		$fee_id = $con->fee_id;
  }
  
	$session_id = (string)variable_get('essa_sid');
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees = db_query("
    SELECT * from {$fees_table} where fee_id = :id;", array(':id' => $fee_id)
  );
	foreach($fees as $fee){
		if($form_state['values']['amount'] > $fee->amount){
			form_set_error('amount','Concession amount can\'t be more than the fee amount.');
		}
	}
	
	if($form_state['values']['percent'] > 100){
		form_set_error('percent','Percent can\'t be greater than 100% in this case.');
	}
	
	if(!is_numeric($form_state['values']['percent']) && $form_state['values']['percent'] != NULL){
		form_set_error('percent' , 'Percent must be numeric.');
		if($form_state['values']['percent'] <= 0){
			form_set_error('percent','Percent can\'t be 0% or less.');
		}
	}
	
	global $base_url;
	$url = $base_url.'/admin/fees/concession/delete-concession';
	$flag = 0;
	$student_concession = db_query("
		SELECT * from {$student_concession_table} where adm_no = :n and con_id = :ci;",
		array(':n' => $form_state['values']['adm_no'], ':ci' => $con_id)
	);
	foreach($student_concession as $sc){
		$flag = 1;
	}
	if($flag == 1){
		form_set_error('adm_no', 'This concession has already been applied to this student. You must first delete this concession from this student. Delete student concession, <a href = "'.$url.'">here</a>.');
	}
}

function student_concession_es_submit($form, &$form_state){
	$session = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	$session = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	$fees_frequency = 'essa_'.$session.'_fees_frequency';
	$fees_student_table = 'essa_'.$session.'_fees_student';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	$fee_structure = 'essa_'.$session.'_fees_structure';
	$fees_student_payment = 'essa_'.$session.'_fees_student_payment';
	$fees_advance = 'essa_'.$session.'_fees_student_advance';
	
	$concession = db_query("
		SELECT * from {$concession_table} where name = :n", array(':n' => $form_state['values']['con_type'])
	);
	foreach($concession as $con){
    $con_id = $con->con_id;
		$con_name = $con->name;
		$fee_id = $con->fee_id;
  }
	$fees_con_id = db_query("
		SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
	);
	foreach($fees_con_id as $fee){
		$get_fee_detail = db_query("
			SELECT * from {$fee_structure} where particulars = :p", array(':p' => $fee->particulars)
		);
		foreach($get_fee_detail as $gfd){
			$fee_ids[] = $gfd->fee_id;
		}
	}

	//---------------get freq-----------
	$fee_freq = db_query("
		SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
	);
	foreach($fee_freq as $ff){
		$freq_id = $ff->freq_id;
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
			$months[] = $key;
		}
	}
	
	$flag = 0;
	foreach($fee_ids as $fee_id){
		$student_concession = db_query("
			SELECT * from {$fees_student_table} where adm_no = :an and fee_id = :fi", array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id)
		);
		foreach($student_concession as $sc){
		  foreach($freq as $key=>$fr){
				$fee_amount = db_query("
					SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
				);
				foreach($fee_amount as $fa){
				  $amt = $fa->amount;
				}
				$flag = 1;
				if($form_state['values']['amount'] != NULL){
					$con_amt = $form_state['values']['amount'];
				}else{
					$con_amt = ($form_state['values']['percent']/100)*$amt;
				}
			}
		}
	}
	
	$mons = $months;
	
	if($flag == 1){
		foreach($mons as $fee_mon){
			db_merge($student_concession_table)
				->key(array('con_id' => $con_id, 'adm_no' => $form_state['values']['adm_no']))
				->fields (array(
					$fee_mon => $con_amt,
					'con_id' => $con_id,
					'adm_no' => $form_state['values']['adm_no'],
					'name' =>  $con_name,
					'amount' => $form_state['values']['amount']?$form_state['values']['amount']:NULL,
					'percentage' => $form_state['values']['percent']?$form_state['values']['percent']:NULL,
				)
			)	
			->execute();
		}
			//---------update student_due table
		$advance = array();
		$adv = array();
		foreach($fee_ids as $fee_id){
			$student_concession = db_query("
				SELECT * from {$fees_student_table} where adm_no = :an and fee_id = :fi", array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id)
			);
			foreach($student_concession as $sc){
				foreach($mons as $key){
					$fee_amount = db_query("
						SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
					);
					foreach($fee_amount as $fa){
						$amt = $fa->amount;
					}
					if($form_state['values']['amount'] != NULL){
						$new_amt = $amt - $form_state['values']['amount'];
					}else{
						$new_amt = $amt - ($form_state['values']['percent']/100)*$amt;
					}
					
					if($form_state['values']['amount'] != NULL){
						$con_amt = $form_state['values']['amount'];
					}else{
						$con_amt = ($form_state['values']['percent']/100)*$amt;
					}
					if($new_amt < 0){
						$new_amt = 0;
					}
					
					$student_payment = db_query("
						SELECT * from {$fees_student_payment} where adm_no = :an and fee_id = :fi and month = :mon;",
						array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id, ':mon' => $key)
					);
					foreach($student_payment as $sp){
						$receipt_no = $sp->receipt_no;
						$new_amt = $new_amt - $sp->amount;
						if($new_amt < 0){
							$num = abs($new_amt);
							$advance[$receipt_no] = $advance[$receipt_no] + $num;
							$new_amt = 0;
							$new_pay = 0;
							$student_payment = db_query("
								SELECT * from {$fees_student_payment} where adm_no = :an and fee_id = :fi and month = :mon;",
								array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id, ':mon' => $key)
							);
							foreach($student_payment as $sp){
								$new_pay = $sp->amount - $num;
								$adv[$fee_id][$key][$receipt_no] = $num;
								variable_set('adv_con/'.$form_state['values']['adm_no'], $adv);
								db_merge($fees_student_payment)
									->key(array('adm_no' => $form_state['values']['adm_no'], 'fee_id' => $fee_id, 'month' => $key, 'receipt_no' => $receipt_no))
									->fields (array(
										'amount' => $new_pay,
									)
								)		
								->execute();
							}
						}
					}
					db_merge($student_due_table)
						->key(array('fee_id' => $fee_id, 'adm_no' => $form_state['values']['adm_no']))
						->fields (array(
						$key => $new_amt,
						)
					)		
					->execute();
					/*
					db_merge($fees_student_payment)
						->key(array('adm_no' => $form_state['values']['adm_no'], 'fee_id' => $fee_id, 'month' => $key))
						->fields (array(
							'amount' => $new_pay,
						)
					)		
					->execute();
					*/
				}
			}
		}
		
		variable_set('adv_con/'.$form_state['values']['adm_no'], $adv);
		if(isset($receipt_no) != NULL){
			foreach($advance as $receipt_no => $adv){
				db_merge($fees_advance)
					->key(array('fee_id' => 'c'.$con_id, 'adm_no' => $form_state['values']['adm_no'], 'receipt_no' => $receipt_no))
					->fields (array(
						'fee_id' => 'c'.$con_id,
						'adm_no' => $form_state['values']['adm_no'],
						'receipt_no' => $receipt_no,
						'amount' => $adv,
						'amount_remaining' => $adv,
					)
				)
				->execute();
			}
		}
		
		
		drupal_set_message('Concession '.$form_state['values']['con_type'].' has been applied to student '.$form_state['values']['adm_no'].'.','status');
		
		//***********SURAJ*************
		$sys_alert_table = 'essa_'.$session.'_system_alert';
		global $user;
		//sending system alert
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
			'message' => 'Concession '.$form_state['values']['con_type'].' has been applied to student '.$form_state['values']['adm_no'].'.',
			'priority' => 'H',
			'module' => 'fee',
			'source_url' => 'admin/fees/concession/student-concession-entire-session',
			'timestamp' => $strtodate,
			'source_uid' => $user->uid,
		))
		->execute();
	}else{
		drupal_set_message('This concession is not applicable for this student, because the concession is appilied to a fee type that is not assigned to this student.', 'warning');
	}
}


/**
 *Implements page callback function - concession
 */
function student_concession_fnm($form = array(), &$form_state){
	$session = (string)variable_get('essa_sid');
	$concession_table = 'essa_'.$session.'_fees_concession';
  $form['adm_no'] = array(
    '#type' => 'textfield',
    '#title' => t('Admission No.'),
    '#autocomplete_path' => 'adm_no/autocomplete',
    '#size' => 30,
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'display_student_detail',
      'wrapper' => 'sd_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#id' => 'adm_no',
    '#required' => TRUE,
  );
	
	$form['sd_wrapper'] = array(
    '#type' => 'container',
    '#prefix' => '<div id = "sd_wrapper" style = "width: 20%; float: right;">',
    '#suffix' => '</div>',
  );
  
  $options = array();
  $concession = db_query("
		SELECT * from {$concession_table}"
	);
	foreach($concession as $con){
		$options[] = $con->name;
	}
	
	//**********SURAJ************
	global $base_url;
	$url = $base_url.'#overlay=admin/fees/concession/create-concession';
	if($options == NULL){
		drupal_set_message('No Concession has been created. Please create concession, <a href = "'.$url.'">here</a>.', 'warning');
	}
	//**********SURAJ************
	
	$form['con_type'] = array(
		'#type' => 'select',
		'#title' => 'Select concession type',
		'#options' => drupal_map_assoc($options),
		'#ajax' => array(
		  'event' => 'change',
		  'callback' => 'display_con',
		  'wrapper' => 'con',
		  'method' => 'replace',
		  'effect' => 'fade',
		),
		'#required' => TRUE,
	);
	
	$form['fs'] = array(
    '#type' => 'fieldset',
    '#prefix' => '<div id = "con">',
    '#suffix' => '</div>',
  );
  $form['fs']['amount'] = array(
    '#type' => 'textfield',
    '#title' => 'Amount',
    '#size' => 10,
  );
  $form['fs']['percent'] = array(
    '#type' => 'textfield',
    '#title' => 'Percent',
    '#size' => 10,
  );
	
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
		$mon_options[] = $dt->format("M-Y");
	}
  
  $form['select_freq'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select Months'),
    '#options' => drupal_map_assoc($mon_options),
    '#checkall' => 'unique-class-for-each-checkboxes-column',
  );
	
	$form['save'] = array(
    '#type' => 'submit',
    '#value' => 'Save'
  );
	
	$session = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	$session = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	$fees_frequency = 'essa_'.$session.'_fees_frequency';
	$fees_student_table = 'essa_'.$session.'_fees_student';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	$fee_structure = 'essa_'.$session.'_fees_structure';
	
	$fee_id  = 1;
	
	return $form;
}

/**
 *Implements validate function
 */
function student_concession_fnm_validate($form, &$form_state){
	if($form_state['values']['amount'] == NULL && $form_state['values']['percent'] == NULL){
		form_set_error('amount' , 'Both amount and percent can\'t be empty.');
	}
	
	if($form_state['values']['amount'] != NULL){
		if(!is_numeric($form_state['values']['amount'])){
			form_set_error('amount' , 'Amount must be numeric.');
		}elseif($form_state['values']['amount'] <= 0){
			form_set_error('amount' , 'Amount can\'t be less than or equal to zero.');
		}
	}
	
	if($form_state['values']['amount'] != NULL && $form_state['values']['percent'] != NULL){
		form_set_error('amount' , 'Both amount and percent can\'t be alloted. You need to select any one.');
	}
	
	$session = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	$concession = db_query("
		SELECT * from {$concession_table} where name = :n", array(':n' => $form_state['values']['con_type'])
	);
	foreach($concession as $con){
    $con_id = $con->con_id;
		$con_name = $con->name;
		$fee_id = $con->fee_id;
  }
  
	$session_id = (string)variable_get('essa_sid');
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees = db_query("
    SELECT * from {$fees_table} where fee_id = :id;", array(':id' => $fee_id)
  );
	foreach($fees as $fee){
		if($form_state['values']['amount'] > $fee->amount){
			form_set_error('amount','Concession amount can\'t be more than the fee amount.');
		}
	}
	
	if($form_state['values']['percent'] > 100){
		form_set_error('percent','Percent can\'t be greater than 100% in this case.');
	}
	
	if(!is_numeric($form_state['values']['percent']) && $form_state['values']['percent'] != NULL){
		form_set_error('percent' , 'Percent must be numeric.');
		if($form_state['values']['percent'] <= 0){
			form_set_error('percent','Percent can\'t be 0% or less.');
		}
	}
	
	global $base_url;
	$url = $base_url.'/admin/fees/concession/delete-concession';
	$flag = 0;
	$student_concession = db_query("
		SELECT * from {$student_concession_table} where adm_no = :n and con_id = :ci;",
		array(':n' => $form_state['values']['adm_no'], ':ci' => $con_id)
	);
	foreach($student_concession as $sc){
		$flag = 1;
	}
	if($flag == 1){
		form_set_error('adm_no', 'This concession has already been applied to this student. You must first delete this concession from this student. Delete student concession, <a href = "'.$url.'">here</a>.');
	}
}

function student_concession_fnm_submit($form, &$form_state){
	$session = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	$session = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	$fees_frequency = 'essa_'.$session.'_fees_frequency';
	$fees_student_table = 'essa_'.$session.'_fees_student';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	$fee_structure = 'essa_'.$session.'_fees_structure';
	$fees_student_payment = 'essa_'.$session.'_fees_student_payment';
	$fees_advance = 'essa_'.$session.'_fees_student_advance';
	
	$concession = db_query("
		SELECT * from {$concession_table} where name = :n", array(':n' => $form_state['values']['con_type'])
	);
	foreach($concession as $con){
    $con_id = $con->con_id;
		$con_name = $con->name;
		$fee_id = $con->fee_id;
  }
	$fees_con_id = db_query("
		SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
	);
	foreach($fees_con_id as $fee){
		$get_fee_detail = db_query("
			SELECT * from {$fee_structure} where particulars = :p", array(':p' => $fee->particulars)
		);
		foreach($get_fee_detail as $gfd){
			$fee_ids[] = $gfd->fee_id;
		}
	}

	//---------------get freq-----------
	$fee_freq = db_query("
		SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
	);
	foreach($fee_freq as $ff){
		$freq_id = $ff->freq_id;
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
			$months[] = $key;
		}
	}
	
	$flag = 0;
	foreach($fee_ids as $fee_id){
		$student_concession = db_query("
			SELECT * from {$fees_student_table} where adm_no = :an and fee_id = :fi", array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id)
		);
		foreach($student_concession as $sc){
		  foreach($freq as $key=>$fr){
				$fee_amount = db_query("
					SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
				);
				foreach($fee_amount as $fa){
				  $amt = $fa->amount;
				}
				$flag = 1;
				if($form_state['values']['amount'] != NULL){
					$con_amt = $form_state['values']['amount'];
				}else{
					$con_amt = ($form_state['values']['percent']/100)*$amt;
				}
			}
		}
	}
	
	foreach($form_state['values'] as $val){
    if(is_array($val)){
      foreach($val as $k=>$v){
				if($v != '0'){
					$mon = str_replace('-', '_', $v);
					if(in_array($mon, $months)){
						$mons[] = $mon;
					}
				}
			}
		}
	}
	
	if($flag == 1){
		foreach($mons as $fee_mon){
			db_merge($student_concession_table)
				->key(array('con_id' => $con_id, 'adm_no' => $form_state['values']['adm_no']))
				->fields (array(
					$fee_mon => $con_amt,
					'con_id' => $con_id,
					'adm_no' => $form_state['values']['adm_no'],
					'name' =>  $con_name,
					'amount' => $form_state['values']['amount']?$form_state['values']['amount']:NULL,
					'percentage' => $form_state['values']['percent']?$form_state['values']['percent']:NULL,
				)
			)	
			->execute();
		}
			//---------update student_due table
		$advance = array();
		$adv = array();
		foreach($fee_ids as $fee_id){
			$student_concession = db_query("
				SELECT * from {$fees_student_table} where adm_no = :an and fee_id = :fi", array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id)
			);
			foreach($student_concession as $sc){
				foreach($mons as $key){
					$fee_amount = db_query("
						SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
					);
					foreach($fee_amount as $fa){
						$amt = $fa->amount;
					}
					if($form_state['values']['amount'] != NULL){
						$new_amt = $amt - $form_state['values']['amount'];
					}else{
						$new_amt = $amt - ($form_state['values']['percent']/100)*$amt;
					}
					
					if($form_state['values']['amount'] != NULL){
						$con_amt = $form_state['values']['amount'];
					}else{
						$con_amt = ($form_state['values']['percent']/100)*$amt;
					}
					if($new_amt < 0){
						$new_amt = 0;
					}
					
					$student_payment = db_query("
						SELECT * from {$fees_student_payment} where adm_no = :an and fee_id = :fi and month = :mon;",
						array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id, ':mon' => $key)
					);
					foreach($student_payment as $sp){
						$receipt_no = $sp->receipt_no;
						$new_amt = $new_amt - $sp->amount;
						if($new_amt < 0){
							$num = abs($new_amt);
							$advance[$receipt_no] = $advance[$receipt_no] + $num;
							$new_amt = 0;
							$new_pay = 0;
							$student_payment = db_query("
								SELECT * from {$fees_student_payment} where adm_no = :an and fee_id = :fi and month = :mon;",
								array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id, ':mon' => $key)
							);
							foreach($student_payment as $sp){
								$new_pay = $sp->amount - $num;
								$adv[$fee_id][$key][$receipt_no] = $num;
								variable_set('adv_con/'.$form_state['values']['adm_no'], $adv);
								db_merge($fees_student_payment)
									->key(array('adm_no' => $form_state['values']['adm_no'], 'fee_id' => $fee_id, 'month' => $key, 'receipt_no' => $receipt_no))
									->fields (array(
										'amount' => $new_pay,
									)
								)		
								->execute();
							}
						}
					}
					db_merge($student_due_table)
						->key(array('fee_id' => $fee_id, 'adm_no' => $form_state['values']['adm_no']))
						->fields (array(
						$key => $new_amt,
						)
					)		
					->execute();
					/*
					db_merge($fees_student_payment)
						->key(array('adm_no' => $form_state['values']['adm_no'], 'fee_id' => $fee_id, 'month' => $key))
						->fields (array(
							'amount' => $new_pay,
						)
					)		
					->execute();
					*/
				}
			}
		}
		
		variable_set('adv_con/'.$form_state['values']['adm_no'], $adv);
		if(isset($receipt_no) != NULL){
			foreach($advance as $receipt_no => $adv){
				db_merge($fees_advance)
					->key(array('fee_id' => 'c'.$con_id, 'adm_no' => $form_state['values']['adm_no'], 'receipt_no' => $receipt_no))
					->fields (array(
						'fee_id' => 'c'.$con_id,
						'adm_no' => $form_state['values']['adm_no'],
						'receipt_no' => $receipt_no,
						'amount' => $adv,
						'amount_remaining' => $adv,
					)
				)
				->execute();
			}
		}
		
		
		drupal_set_message('Concession '.$form_state['values']['con_type'].' has been applied to student '.$form_state['values']['adm_no'].'.','status');
		
		//***********SURAJ*************
		$sys_alert_table = 'essa_'.$session.'_system_alert';
		global $user;
		//sending system alert
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
			'message' => 'Concession '.$form_state['values']['con_type'].' has been applied to student '.$form_state['values']['adm_no'].'.',
			'priority' => 'H',
			'module' => 'fee',
			'source_url' => 'admin/fees/concession/student-concession-entire-session',
			'timestamp' => $strtodate,
			'source_uid' => $user->uid,
		))
		->execute();
	}else{
		drupal_set_message('This concession is not applicable for this student, because the concession is appilied to a fee type that is not assigned to this student.', 'warning');
	}
}

function display_con($form, &$form_state){
  $session = (string)variable_get('essa_sid');
	$concession_table = 'essa_'.$session.'_fees_concession';
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	
	$concession = db_query("
		SELECT * from {$concession_table} where name = :n", array(':n' => $form_state['values']['con_type'])
	);
	foreach($concession as $con){
		$amount = $con->amount;
    $percent = $con->percent;
		$con_id = $con->con_id;
	}
	
	$student_concession = db_query("
		SELECT * from {$student_concession_table} where adm_no = :an and con_id = :ci;", array(':an' => $form_state['values']['adm_no'], 'ci' => $con_id)
	);
	foreach($student_concession as $sc){
		$sc_amount = $sc->amount;
    $sc_percent = $sc->percentage;
	}
	
	if($sc_amount != NULL){
		$form['fs']['amount']['#value'] = $sc_amount;	
	}else{
		$form['fs']['amount']['#value'] = $amount;
	}
  
	if($sc_amount == NULL && $amount == NULL){
		if($sc_percent != NULL){
			$form['fs']['percent']['#value'] = $sc_percent;
		}else{
			$form['fs']['percent']['#value'] = $percent;
		}
	}
  
  if($amount != NULL){
    return $form['fs'];
  }else{
    return $form['fs'];
  }
}

/**
 *Implements ajax callback
 */
function display_student_detail($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$stud_table = 'essa_'.$session_id.'_master_student_table';
	variable_set('fee_adm_no_error', NULL);
	$stud_info = db_query(
		"SELECT * from $student_table where adm_no = :adm_no;", array(':adm_no' => $form_state['values']['adm_no'])
	);
	foreach($stud_info as $si){
		$class = $si->class;
		$sec = $si->section;
	}
	
	if(!empty($form_state['values']['adm_no'])){
		$stud_detail = db_query(
			"SELECT * from $stud_table;"
		);
		foreach($stud_detail as $sd){
			if($sd->adm_no == $form_state['values']['adm_no']){
				$name = $sd->student_name;
				$roll_no = $sd->roll_no;
			}
		}
		
		if(isset($name)){
			$form['fs'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 style = "float:left; width: 300px;">Name: </h3><h4><b>'.$name.'</b></h4><h3 style = "float:left;width: 300px;"> Class: </h3><h4><b>'.$class.' - '.$sec.'</b></h4><h3 style = "float:left; width: 300px;">Roll No. </h3><h4><b>'.$roll_no.'</b></h4>',
				'#prefix' => '<div id = "sd_wrapper">',
				'#suffix' => '</div></div>',
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
