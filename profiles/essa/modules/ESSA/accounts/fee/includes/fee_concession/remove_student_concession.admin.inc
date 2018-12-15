<?php

/**
 *Implements page callback function - remove_concession
 */
function remove_concession($form, &$form_state){
	$session = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	$session = (string)variable_get('essa_sid');
	$fees_frequency = 'essa_'.$session.'_fees_frequency';
	$fees_student_table = 'essa_'.$session.'_fees_student';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	$fee_structure = 'essa_'.$session.'_fees_structure';
	$fees_student_payment = 'essa_'.$session.'_fees_student_payment';
	$fees_advance = 'essa_'.$session.'_fees_student_advance';
	$student_table = 'essa_'.$session.'_master_student_table';
	
	$row = array();
	$session = variable_get('essa_sid');
	$fine_table = 'essa_'.$session.'_fees_student_fine';
	$student_table = 'essa_'.$session.'_master_student_table';
	$session = (string)variable_get('essa_sid');
	$basic_info_table = 'essa_'.$session.'_basicinfo';
	$class_table = 'essa_'.$session.'_class_list';
	
	$form['filter'] = array(
		'#type' => 'fieldset',
		'#title' => 'Filter By - ',
	);
	
	$form['filter']['ad'] = array(
		'#type' => 'fieldset',
	);
	
	$form['filter']['ad']['adm_no'] = array(
		'#type' => 'textfield',
    '#title' => t('Admission No.'),
    '#size' => 10,
		'#autocomplete_path' => 'adm_no/fee_autocomplete',
	);
	
	$cl_op = array('--Select--');
	$classes = db_query(
		"SELECT * from $class_table order by weight;"
	);
	foreach($classes as $cl){
		$cl_op[] = $cl->class_id;
	}
	
	$form['filter']['cs'] = array(
		'#type' => 'fieldset',
	);
	$sec = drupal_map_assoc(array('--Select--', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'));
	$form['filter']['cs']['class_filter'] = array(
		'#type' => 'select',
    '#title' => t('Class'),
    '#options' => drupal_map_assoc($cl_op),
	);
	
	$form['filter']['cs']['sec_filter'] = array(
		'#type' => 'select',
    '#title' => t('Section'),
    '#options' => drupal_map_assoc($sec),
	);
	
	$con_types = array('--Select--');
	$concession = db_query("
		SELECT * from {$concession_table};"
	);
	foreach($concession as $con){
		$con_types[$con->con_id] = $con->name;
	}
	
	$form['filter']['mn'] = array(
		'#type' => 'fieldset',
	);
	$form['filter']['mn']['con_type'] = array(
		'#type' => 'select',
    '#title' => t('Concession Type'),
		'#options' => $con_types,
	);
	
	$form['filter']['apply'] = array(
		'#type' => 'button',
		'#ajax' => array(
      'event' => 'click',
      'callback' => 'apply_con_filter_ajax',
      'wrapper' => 'sd_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#value' => 'Apply',
	);
	
	if(!isset($form_state['values'])){
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
		
		$student_concession = db_query("
			SELECT * from {$student_concession_table};"
		);
		foreach($student_concession as $sc){
			$concession = db_query("
				SELECT * from {$concession_table} where con_id = :ci", array(':ci' => $sc->con_id)
			);
			foreach($concession as $con){
				$fee_id = $con->fee_id;
				$con_name = $con->name;
			}
			$fee_freq = db_query("
				SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
			);
			foreach($fee_freq as $ff){
				$freq_id = $ff->freq_id;
				$fee_amt = $ff->amount;
			}
			
			$student_data = db_query("
				SELECT * from {$student_table} where adm_no = :an AND status = 1", array(':an' => $sc->adm_no)
			);
			foreach($student_data as $sd){
				$name = $sd->student_name;
				$class = $sd->class;
				$sec = $sd->section;
			}
			
			$months = array();
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
			
			$total_concession = 0;
			foreach($months as $mon){
				$total_concession = $total_concession + $sc->$mon;
			}
			
			$row[$sc ->con_id.':'.$sc->adm_no] = array(
				'#tree' =>TRUE,
				$sc ->con_id.':'.$sc->adm_no => array(  //Generating unique array id for every form element
					'c0' => array(
						'#type' => 'checkbox',
					),
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $sc->adm_no .'</h3>',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $name .'</h3>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $class .'</h3>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $sec .'</h3>',
					),
					'cc' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $con_name .'</h3>',
					),
					'c5' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $fee_amt .'</h3>',
					),
					'c6' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $sc->amount .'</h3>',
					),
					'c7' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $sc->percentage .'</h3>',
					),
					'c8' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $total_concession .'</h3>',
					),
				),
			);	
		}
	}else{
		$filter_adm_no = array();
		$filter_class = array();
		$filter_sec = array();
		$filter_class_from = array();
		$filter_class_to = array();
		$filter_month = array();
		$filter_particulars = array();
		$master = array();
		$query=db_select($student_concession_table,'sct');
		$query->join($student_table,'st','sct.adm_no = st.adm_no');
		$query->join($concession_table,'ct','sct.con_id = ct.con_id');
		$query
      ->fields('sct',array('con_id','adm_no'))
      ->fields('st',array('student_name', 'class', 'section'))
			->fields('ct',array('name'));
		$result= $query->execute();
    foreach($result as $r){
			$master[$r->con_id.'#'.$r->adm_no] = $r->con_id;
		}
		
		if($form_state['values']['adm_no'] != NULL){
			$query=db_select($student_concession_table,'sct');
			$query->join($student_table,'st','sct.adm_no = st.adm_no');
			$query->join($concession_table,'ct','sct.con_id = ct.con_id');
			$query->condition('sct.adm_no',$form_state['values']['adm_no'])
				->fields('sct',array('con_id','adm_no'))
				->fields('st',array('student_name', 'class', 'section'))
				->fields('ct',array('name'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_adm_no[$r->con_id.'#'.$r->adm_no] = $r->con_id;
			}
			$master = array_intersect_key($master, $filter_adm_no);
		}
		
		if($form_state['values']['class_filter'] != '--Select--'){
			$query=db_select($student_concession_table,'sct');
			$query->join($student_table,'st','sct.adm_no = st.adm_no');
			$query->join($concession_table,'ct','sct.con_id = ct.con_id');
			$query->condition('st.class',$form_state['values']['class_filter'])
				->fields('sct',array('con_id','adm_no'))
				->fields('st',array('student_name', 'class', 'section'))
				->fields('ct',array('name'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_class[$r->con_id.'#'.$r->adm_no] = $r->con_id;
			}
			$master = array_intersect_key($master, $filter_class);
		}
		
		
		if($form_state['values']['sec_filter'] != '--Select--'){
			$query=db_select($student_concession_table,'sct');
			$query->join($student_table,'st','sct.adm_no = st.adm_no');
			$query->join($concession_table,'ct','sct.con_id = ct.con_id');
			$query->condition('st.section',$form_state['values']['sec_filter'])
				->fields('sct',array('con_id','adm_no'))
				->fields('st',array('student_name', 'class', 'section'))
				->fields('ct',array('name'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_sec[$r->con_id.'#'.$r->adm_no] = $r->con_id;
			}
			$master = array_intersect_key($master, $filter_sec);
		}
		
		if($form_state['values']['con_type'] != 0){
			$query=db_select($student_concession_table,'sct');
			$query->join($student_table,'st','sct.adm_no = st.adm_no');
			$query->join($concession_table,'ct','sct.con_id = ct.con_id');
			$query->condition('sct.con_id',$form_state['values']['con_type'])
				->fields('sct',array('con_id','adm_no'))
				->fields('st',array('student_name', 'class', 'section'))
				->fields('ct',array('name'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_con_id[$r->con_id.'#'.$r->adm_no] = $r->con_id;
			}
			$master = array_intersect_key($master, $filter_con_id);
		}
		
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
		foreach($master as $key=>$val){
			$arr = explode('#', $key, 2);
			$con_id = $arr[0];
			$adm_no = $arr[1];
			$student_concession = db_query("
				SELECT * from {$student_concession_table} where adm_no = :an and con_id = :ci;", array(':an' => $adm_no, ':ci' => $con_id)
			);
			foreach($student_concession as $sc){
				$concession = db_query("
					SELECT * from {$concession_table} where con_id = :ci", array(':ci' => $sc->con_id)
				);
				foreach($concession as $con){
					$fee_id = $con->fee_id;
					$con_name = $con->name;
				}
				$fee_freq = db_query("
					SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
				);
				foreach($fee_freq as $ff){
					$freq_id = $ff->freq_id;
					$fee_amt = $ff->amount;
				}
				
				$student_data = db_query("
					SELECT * from {$student_table} where adm_no = :an AND status = 1", array(':an' => $sc->adm_no)
				);
				foreach($student_data as $sd){
					$name = $sd->student_name;
					$class = $sd->class;
					$sec = $sd->section;
				}
				
				$months = array();
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
				
				$total_concession = 0;
				foreach($months as $mon){
					$total_concession = $total_concession + $sc->$mon;
				}
				
				$row[$sc ->con_id.':'.$sc->adm_no] = array(
					'#tree' =>TRUE,
					$sc ->con_id.':'.$sc->adm_no => array(  //Generating unique array id for every form element
						'c0' => array(
							'#type' => 'checkbox',
						),
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $sc->adm_no .'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $name .'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $class .'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $sec .'</h3>',
						),
						'cc' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $con_name .'</h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $fee_amt .'</h3>',
						),
						'c6' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $sc->amount .'</h3>',
						),
						'c7' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $sc->percentage .'</h3>',
						),
						'c8' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $total_concession .'</h3>',
						),
					),
				);	
			}
		}
	}
	
	$form['lts'] = array(
		'#theme' => 'student_con_table',
		'rows' => $row,
		'#prefix' => '<div id = "sd_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['delete'] = array(
		'#type' => 'submit',
		'#value' => 'delete',
	);
	return $form;
}

function apply_con_filter_ajax($form, &$form_state){
	return $form['lts'];
}

/**
 *Implements page callback function - remove_concession
 */
function remove_concession_submit($form, &$form_state){
	$session = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	$session = (string)variable_get('essa_sid');
	$fees_frequency = 'essa_'.$session.'_fees_frequency';
	$fees_student_table = 'essa_'.$session.'_fees_student';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	$fee_structure = 'essa_'.$session.'_fees_structure';
	$fees_student_payment = 'essa_'.$session.'_fees_student_payment';
	$fees_advance = 'essa_'.$session.'_fees_student_advance';
	$student_table = 'essa_'.$session.'_master_student_table';
	$basic_info_table = 'essa_'.$session.'_basicinfo';
	$fees_student_adjustement = 'essa_'.$session.'_fees_student_adjustement';
	$advance_table = 'essa_'.$session.'_fees_student_advance';
	
	$binfo = db_query("
		SELECT * from {$basic_info_table};
	");
	foreach($binfo as $info){
		$start_date = $info->academicyearstart;
		$end_date = $info->academicyearend;
	}
	$start = new DateTime($start_date);
	$start->modify('first day of this month');
	$end = new DateTime($end_date);
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
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				if($v['c0'] == 1){
					$arr = explode(':', $k);
					$con_id = $arr[0];
					$adm_no = $arr[1];
					
					$flag = 0;
					$success_flag = 0;
					$get_advance = db_query("
						SELECT * from {$fees_student_adjustement} where fee_id = :fi and adm_no = :an;", array(':fi' => 'c'.$con_id, ':an' => $adm_no)
					);
					foreach($get_advance as $ga){
						$flag = 1;
					}
					if($flag == 1){
						global $base_url;
						$url = $base_url.'/admin/fees/payment/adjustments/delete';
						drupal_set_message('Concession for admission_no - <b>'.$adm_no.'</b> cannot be deleted because advance has been adjusted. Delete corresponding adjustment first, <a href = "'.$url.'">here</a>.','warning');
					}else{
						$get_con_id = db_query("
							SELECT * from {$concession_table} where con_id = :ci;", array(':ci' => $con_id)
						);
						foreach($get_con_id as $gci){
							$fee_id = $gci->fee_id;
							$con_name = $gci->name;
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
							
							foreach($fee_ids as $fid){
								$fee_student_due = db_query("
									SELECT * from {$student_due_table} where fee_id = :fi and adm_no = :an;", array(':fi' => $fid, ':an' => $adm_no)
								);
								foreach($fee_student_due as $fsd){
									foreach($columns as $col){
										$fee_student_concession = db_query("
											SELECT * from {$student_concession_table} where con_id = :ci and adm_no = :an;", array(':ci' => $con_id, ':an' => $adm_no)
										);
										foreach($fee_student_concession as $fsc){
											if($fsd->$col <= $fsc->$col){
												$new_due = 0;
											}else{
												$new_due = $fsd->$col + $fsc->$col;	
											}
											
											db_merge($student_due_table)
												->key(array('fee_id' => $fid, 'adm_no' => $adm_no))
												->fields (array(
													$col => $new_due,
												)
											)		
											->execute();
										}
									}
								}
							}
							
							
							$adv_pay = variable_get('adv_con/'.$adm_no);
							foreach($adv_pay as $feid => $arr){
								foreach($arr as $paymon => $arr1){
									foreach($arr1 as $rno => $adv_amount){
										$student_payment = db_query("
											SELECT * from {$fees_student_payment} where adm_no = :an and fee_id = :fi and month = :mon and receipt_no = :rn;",
											array(':an' => $adm_no, ':fi' => $feid, ':mon' => $paymon, ':rn' => $rno)
										);
										foreach($student_payment as $sp){
											$new_amt = $sp->amount+$adv_amount;
											db_merge($fees_student_payment)
												->key(array('adm_no' => $adm_no,
															'fee_id' => $feid, 'month' => $paymon, 'receipt_no' => $rno))
												->fields (array(
													'amount' => $new_amt,
												)
											)		
											->execute();
										}
									}
								}
							}
							
							db_delete($student_concession_table)
								->condition(db_and()
										->condition('con_id', $con_id)
										->condition('adm_no', $adm_no)
									)
								->execute();
								
							$adv_pay = variable_get('adv_con/'.'XII-A-8');
							
							db_delete($fees_advance)
								->condition(db_and()
										->condition('fee_id', 'c'.$con_id)
										->condition('adm_no', $adm_no)
									)
								->execute();
							$success_flag = 1;
						}
					}
				}
			}
		}
	}
	
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				if($v['c0'] == 1){
					$arr = explode(':', $k);
					$con_id = $arr[0];
				}
			}
		}
	}
	$get_con_id = db_query("
		SELECT * from {$concession_table} where con_id = :ci;", array(':ci' => $con_id)
	);
	foreach($get_con_id as $gci){
		$fee_id = $gci->fee_id;
		$con_name = $gci->name;
	}
	
	if($success_flag == 1){
		drupal_set_message('Concession '.$con_name.' has been successfully deleted from '.$adm_no.'.', 'status');
	}
	
	//***********SURAJ*************
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	global $user;
	//sending system alert
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'Concession '.$con_name.' has been successfully deleted from '.$adm_no.'.',
		'priority' => 'H',
		'module' => 'fee',
		'source_url' => 'admin/fees/concession/delete-concession',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
}

/**
 *Theme function
 */
function theme_student_con_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t(''), t('Adm No.'),t('Name'), t('Class'), t('Sec'), t('Concession Type'), t('Fee Amount'), t('Amount'),t('Percent'), t('Total Concession'));
  
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