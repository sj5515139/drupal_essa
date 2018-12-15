<?php
$total = 0;  
/**
 *Implements page callback function - student_fee_collection
 */
function student_fee_collection($form, &$form_state, $adm_no){
  $session_id = (string)variable_get('essa_sid');
	$row = array();
  $student_table = 'essa_'.$session_id.'_master_student_table';
  $fees_student_table = 'essa_'.$session_id.'_fees_student_table';
  $fees_table = 'essa_'.$session_id.'_fees_structure';
  $fees_freq = 'essa_'.$session_id.'_fees_frequency';
  $fees_student = 'essa_'.$session_id.'_fees_student';
  $fees_student_due = 'essa_'.$session_id.'_fees_student_due';
  $basic_info_table = 'essa_'.$session_id.'_basicinfo';
  $options = variable_get('fee_options');
	//variable_set('fee_options', NULL);
  
  $form['adm_no'] = array(
    '#type' => 'value',
    '#value' => $adm_no,
  );
  
  
  $students = db_query(
		"SELECT * from $student_table where adm_no = :an AND status = 1;", array(':an' => $adm_no)
	);
	foreach($students as $student){
		//dsm($student);
		$name = $student->first_name.' '.$student->last_name;
		$class = $student->class.' - '.$student->section;
	}
  
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
    $total = 0;
		
    foreach($columns as $col){
      $form['db'] = array(
      	'#type' => 'fieldset'
      );
      $form['db']['adm_no'] = array(
        '#type' => 'markup',
        '#markup' => '<h2 style = "float:left; margin-right: 60px; margin-left: 60px;">Admission No - <span style = "font-weight: 700;">'.$adm_no.'</span><h2>',
      );
      $form['db']['name'] = array(
        '#type' => 'markup',
        '#markup' => '<h2 style = "float:left; margin-right: 60px;">Name - <span style = "font-weight: 700;">'.$name.'</span><h2>',
      );
      $form['db']['class'] = array(
        '#type' => 'markup',
        '#markup' => '<h2>Class - <span style = "font-weight: 700;">'.$class.'</span><h2>',
      );
			
			
			
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
            		'#markup' => '<h3>'. $particular .'</h3>',
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
    $fine_row['fine'] = array(
      '#tree' =>TRUE,
      'fine' => array(
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'. 'Fine(if any)' .'</h3>',
        ),
        'c2' =>array(
          '#type' => 'textfield',
          '#size' => 30,
          '#attributes' => array('placeholder' => 'Fine Details'),
        ),
				'c3' => array(
					'#type' => 'markup',
					'#markup' => '<p></p>',
				),
				/*
        'c3' =>array(
          '#type' => 'textfield',
          '#size' => 10,
          '#attributes' => array('placeholder' => 'Fine Amount'),
          '#ajax' => array(
            'event' => 'blur',
            'callback' => 'recalculate_total_tobepaid',
            'wrapper' => 'total_tobepaid',
            'method' => 'replace',
            'effect' => 'fade',
          ),
        ),
				*/
        'c4' =>array(
          '#type' => 'textfield',
          '#size' => 10,
          '#attributes' => array('placeholder' => 'Amount Paid'),
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
    $row = array_merge($row, $fine_row);
    
    $form['sum'] = array(
      '#type' => 'value',
      '#value' => $total,
    );
    
    $def_dt = date('Y-m-d');
		$total_row['total'] = array(
      '#tree' =>TRUE,                    
      'total' => array(
        'c1' =>array(
					'#type' => 'date_popup',
					'#title' => t('Payment Date'),
					'#size' => 15,
					'#date_label_position' => 'within',
					'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
					'#date_format' => 'd-m-Y',
					'#default_value' => $def_dt,
					'#date_year_range' => '0:+1',
					'#required' => TRUE,
        ),
        'c2' =>array(
          '#type' => 'markup',
          '#markup' => '<h3 style = "text-align: right;">'. 'Total - ' .'</h3>',
        ),
        'c3' =>array(
          '#type' => 'textfield',
          '#size' => 10,
          '#disabled' => TRUE,
          '#default_value' => $total,
          '#prefix' => '<div id = "total_tobepaid">',
          '#suffix' => '</div>',
        ),
        'c4' =>array(
          '#type' => 'textfield',
          '#size' => 10,
          '#disabled' => TRUE,
          '#default_value' => $total,
          '#prefix' => '<div id = "total">',
          '#suffix' => '</div>',
        ),
      ),
    );
    $row = array_merge($row, $total_row);
    $form['lts'] = array(
      '#theme' => 'student_fee_payment_table',
      'rows' => $row,
    );
		
    $form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Submit'),
			'#submit' => array('payment_dl'),
		);
  }else{
    $binfo = db_query("
      SELECT * from {$basic_info_table};
    ");
    foreach($binfo as $info){
    	$start_date = $info->academicyearstart;
    	$end_date = $info->academicyearend;
    }
    $start = new DateTime($start_date);
    $start->modify('first day of this month');
    $dt = str_replace('_','-',date('M_Y'));
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
		
    foreach($columns as $col){
      $form['db'] = array(
      	'#type' => 'fieldset'
      );
      $form['db']['adm_no'] = array(
        '#type' => 'markup',
        '#markup' => '<h2 style = "float:left; margin-right: 60px; margin-left: 60px;">Admission No - <span style = "font-weight: 700;">'.$adm_no.'</span><h2>',
      );
      $form['db']['name'] = array(
        '#type' => 'markup',
        '#markup' => '<h2 style = "float:left; margin-right: 60px;">Name - <span style = "font-weight: 700;">'.$name.'</span><h2>',
      );
      $form['db']['class'] = array(
        '#type' => 'markup',
        '#markup' => '<h2>Class - <span style = "font-weight: 700;">'.$class.'</span><h2>',
      );
			
			
			
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
            		'#markup' => '<h3>'. $particular .'</h3>',
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
    $fine_row['fine'] = array(
      '#tree' =>TRUE,
      'fine' => array(
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'. 'Fine(if any)' .'</h3>',
        ),
        'c2' =>array(
          '#type' => 'textfield',
          '#size' => 30,
          '#attributes' => array('placeholder' => 'Fine Details'),
        ),
				'c3' => array(
					'#type' => 'markup',
					'#markup' => '<p></p>',
				),
				/*
        'c3' =>array(
          '#type' => 'textfield',
          '#size' => 10,
          '#attributes' => array('placeholder' => 'Fine Amount'),
          '#ajax' => array(
            'event' => 'blur',
            'callback' => 'recalculate_total_tobepaid',
            'wrapper' => 'total_tobepaid',
            'method' => 'replace',
            'effect' => 'fade',
          ),
        ),
				*/
        'c4' =>array(
          '#type' => 'textfield',
          '#size' => 10,
          '#attributes' => array('placeholder' => 'Amount Paid'),
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
    $row = array_merge($row, $fine_row);
    
    $form['sum'] = array(
      '#type' => 'value',
      '#value' => $total,
    );
    
		$def_dt = date('d-m-Y');
    $total_row['total'] = array(
      '#tree' =>TRUE,                    
      'total' => array(
        'c1' =>array(
					'#type' => 'date_popup',
					'#title' => t('Payment Date'),
					'#size' => 15,
					'#date_label_position' => 'within',
					'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
					'#date_format' => 'd-m-Y',
					'#default_value' => $def_dt,
					'#date_year_range' => '0:+1',
					'#required' => TRUE,
        ),
        'c2' =>array(
          '#type' => 'markup',
          '#markup' => '<h3 style = "text-align: right;">'. 'Total - ' .'</h3>',
        ),
        'c3' =>array(
          '#type' => 'textfield',
          '#size' => 10,
          '#disabled' => TRUE,
          '#default_value' => $total,
          '#prefix' => '<div id = "total_tobepaid">',
          '#suffix' => '</div>',
        ),
        'c4' =>array(
          '#type' => 'textfield',
          '#size' => 10,
          '#disabled' => TRUE,
          '#default_value' => $total,
          '#prefix' => '<div id = "total">',
          '#suffix' => '</div>',
        ),
      ),
    );
    $row = array_merge($row, $total_row);
    $form['lts'] = array(
      '#theme' => 'student_fee_payment_table',
      'rows' => $row,
    );
		
    $form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Submit'),
			'#submit' => array('payment_dl'),
		);
  }
  
  //dsm($form);
  return $form;
}

/*
function student_fee_collection_validate($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
  $fees_table = 'essa_'.$session_id.'_fees_student';
	$flag_error = 0;
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				if($k != 'fine' && $k != 'total'){
					$arr = explode("-", $k, 2);
					$fee_id = $arr[0];
					$col = $arr[1];
					$fees = db_query("
					  SELECT * from {$fees_table} where fee_id = :fi;", array(':fi' => $fee_id)
					);
					foreach($fees as $fee){
						if($v['c4'] > $fee->$col){
							$flag_error = 1;
						}
					}
				}
			}
		}
	}
	if($flag_error == 1){
		form_set_error('c4','Payment amount cannot be more than amout assigned for that fees.');
	}
}
*/
function payment_dl($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
  $fees_student_table = 'essa_'.$session_id.'_fees_student_table';
  $fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$payment_history = 'essa_'.$session_id.'_fees_payment_history';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	
	$pay_dt = strtotime($form_state['values']['total']['total']['c1']);
	db_insert($payment_history)
		->fields (array(
			'adm_no' => $form_state['values']['adm_no'],
			'payment_date' => $pay_dt,
			'amount' => $form_state['values']['total']['total']['c4']
		)
	)	
	->execute();
	
	$ph = db_query("
		SELECT * from {$payment_history} where adm_no = :an and payment_date = :pd and amount = :am;", array(':an' => $form_state['values']['adm_no'], ':pd' => $pay_dt, ':am' => $form_state['values']['total']['total']['c4'])
	);
	foreach($ph as $p){
		$receipt_no = $p->id;
	}
	
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				if($k != 'fine' && $k != 'total'){
					$arr = explode("-", $k, 2);
					$fee_id = $arr[0];
					$col = $arr[1];
					$payment_date = strtotime($form_state['values']['total']['total']['c1']);
					db_merge($fees_student_payment)
						->key(array('fee_id' => $fee_id,'adm_no' => $form_state['values']['adm_no']))
						->fields (array(
							'fee_id' => $fee_id,
							'adm_no' => $form_state['values']['adm_no'],
							$col => $v['c4'],
							$col.'_payment_date' => $payment_date,
							$col.'_payment_id' => $receipt_no,
						)
					)
					->execute();
					
					$studs = db_query("
					  SELECT * from {$fees_student_due} where adm_no = :an and $col = $col;", array(':an' => $form_state['values']['adm_no'])
					);
					foreach($studs as $stud){
						if($stud->fee_id == $fee_id){
							$update = $stud->$col - $v['c4'];
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
	
	$fine_dt = strtotime($form_state['values']['total']['total']['c1']);
	$fine_col = date('M_Y', $fine_dt);
	
	if($form_state['values']['fine']['fine']['c2'] != NULL){
		db_insert($fees_student_fine)
			->fields (array(
				'adm_no' => $form_state['values']['adm_no'],
				'particulars' => $form_state['values']['fine']['fine']['c2'],
				$fine_col => $form_state['values']['fine']['fine']['c4'],
				$col.'_payment_id' => $receipt_no,
			)
		)	
		->execute();	
	}
	
}

function recalculate_total_tobepaid($form, &$form_state){
  $total = $form_state['values']['sum'] + $form_state['values']['fine']['fine']['c3'];  
  $form['lts']['rows']['total']['total']['c3']['#value'] = $total;//$stud->fee_id.'_'.$col;//$form_state['values'][$stud->fee_id.'_'.$col][$stud->fee_id.'_'.$col]['c4'];
  return $form['lts']['rows']['total']['total']['c3'];
}

function recalculate_total($form, &$form_state){
  
  $session_id = (string)variable_get('essa_sid');
  $student_table = 'essa_'.$session_id.'_master_student_table';
  $fees_student_table = 'essa_'.$session_id.'_fees_student_table';
  $fees_table = 'essa_'.$session_id.'_fees_structure';
  $fees_freq = 'essa_'.$session_id.'_fees_frequency';
  $fees_student = 'essa_'.$session_id.'_fees_student';
  $fees_student_due = 'essa_'.$session_id.'_fees_student_due';
  $basic_info_table = 'essa_'.$session_id.'_basicinfo';
  $options = variable_get('fee_options');
  //variable_set('fee_options', NULL);
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
  $total = $total + $form_state['values']['fine']['fine']['c4'];  
  //isset($form_state['values']['fine']['fine']['c4'])
  /*
  if($form_state['triggering_element']['#array_parents'][2]=='fine'){
    $total = $total + $form_state['triggering_element']['#value'];  
  }
  */
  $form['lts']['rows']['total']['total']['c4']['#value'] = $total;//$stud->fee_id.'_'.$col;//$form_state['values'][$stud->fee_id.'_'.$col][$stud->fee_id.'_'.$col]['c4'];
  return $form['lts']['rows']['total']['total']['c4'];
  //return dsm($form_state);
}

/**
 *Theme function
 */
function theme_student_fee_payment_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Particulars'),t('Month'), t('Amount(In INR)'), t('Amount Paid'));
  
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