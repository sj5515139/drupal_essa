<?php
/**
 *Implements page callback function
 */
function delete_adjustment($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment_table = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_adjustement_table = 'essa_'.$session_id.'_fees_student_adjustement';
	$fees_student_fine_table = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history_table = 'essa_'.$session_id.'_fees_payment_history';
	$fee_student_advance_table = 'essa_'.$session_id.'_fees_student_advance';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$advance_table = 'essa_'.$session_id.'_fees_student_advance';
	$concession_table = 'essa_'.$session_id.'_fees_concession';
	$fine_table = 'essa_'.$session_id.'_fees_student_fine';
	
	$form['help'] = array(
		'#type' => 'markup',
		'#markup' => '<h3>In case Receipt No. & Concession Type both are blank, it is a case of rebate/exemption, where no payment information was processed.</h3>',
	);
	
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
	
	$form['filter']['mn'] = array(
		'#type' => 'fieldset',
	);
	$form['filter']['mn']['receipt_no'] = array(
		'#type' => 'textfield',
    '#title' => t('Receipt No.'),
		'#size' => 10,
	);
	
	$form['filter']['apply'] = array(
		'#type' => 'button',
		'#ajax' => array(
      'event' => 'click',
      'callback' => 'apply_adj_filter_ajax',
      'wrapper' => 'sd_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#value' => 'Apply',
	);
	
	if(!isset($form_state['values'])){
		$adjustments = db_query(
			"SELECT * from $fees_student_adjustement_table;"
		);
		foreach($adjustments as $adjustment){
			$con_id = NULL;
			$receipt_no = NULL;
			$con_name = NULL;
			$fee_student_payment = db_query(
				"SELECT * from $fees_student_payment_table where fee_id = :fi and adm_no = :an and month = :mon;",
				array(':fi' => $adjustment->to_fee_id, ':an' => $adjustment->adm_no, ':mon' => $adjustment->month)
			);
			foreach($fee_student_payment as $fsp){
				$receipt_no = $fsp->receipt_no;
			}
			
			$fee_student_fine = db_query(
				"SELECT * from $fees_student_fine_table where id = :fi and adm_no = :an and month = :mon;",
				array(':fi' => $adjustment->to_fine_id, ':an' => $adjustment->adm_no, ':mon' => $adjustment->month)
			);
			foreach($fee_student_fine as $fsf){
				$receipt_no = $fsf->receipt_no;
			}
			if(substr($adjustment->fee_id, 0, 1) == 'c'){
				$con_id = substr($adjustment->fee_id, 1);
			}
			
			$student_data = db_query("
				SELECT * from {$student_table} where adm_no = :an", array(':an' => $adjustment->adm_no)
			);
			foreach($student_data as $sd){
				$name = $sd->student_name;
				$class = $sd->class;
				$sec = $sd->section;
			}
			
			$fee_data = db_query("
				SELECT * from {$fees_table} where fee_id = :fi", array(':fi' => $adjustment->to_fee_id)
			);
			foreach($fee_data as $fd){
				$ad_name = $fd->particulars;
			}
			
			$fine_data = db_query("
				SELECT * from {$fine_table} where id = :fi", array(':fi' => $adjustment->to_fine_id)
			);
			foreach($fine_data as $fd){
				$ad_name = $fd->particulars;
			}
			
			$row[$adjustment->id] = array(
				'#tree' =>TRUE,
				$adjustment->id => array(  //Generating unique array id for every form element
					'c0' => array(
						'#type' => 'checkbox',
					),
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $adjustment->adm_no .'</h3>',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $name .'</h3>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $class.'-'.$sec.'</h3>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $receipt_no.'</h3>',
					),
					'c5' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $adjustment->fee_id .'</h3>',
					),
					'c6' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $ad_name .'</h3>',
					),
					'c7' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $adjustment->amount .'</h3>',
					),
				),
			);	
		}
	}else{
		$filter_adm_no = array();
		$filter_class = array();
		$filter_sec = array();
		$filter_receipt_no = array();
		$master = array();
		$query=db_select($fees_student_adjustement_table,'sat');
		$query->join($student_table,'st','sat.adm_no = st.adm_no');
		$query
      ->fields('sat',array('id','adm_no'));
		$result= $query->execute();
    foreach($result as $r){
			$master[$r->id.'#'.$r->adm_no] = $r->id;
		}
		
		if($form_state['values']['adm_no'] != NULL){
			$query=db_select($fees_student_adjustement_table,'sat');
			$query->join($student_table,'st','sat.adm_no = st.adm_no');
			$query->condition('sat.adm_no',$form_state['values']['adm_no'])
				->fields('sat',array('id','adm_no'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_adm_no[$r->id.'#'.$r->adm_no] = $r->id;
			}
			$master = array_intersect_key($master, $filter_adm_no);
		}
		
		if($form_state['values']['class_filter'] != '--Select--'){
			$query=db_select($fees_student_adjustement_table,'sat');
			$query->join($student_table,'st','sat.adm_no = st.adm_no');
			$query->condition('st.class',$form_state['values']['class_filter'])
				->fields('sat',array('id','adm_no'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_class[$r->id.'#'.$r->adm_no] = $r->id;
			}
			$master = array_intersect_key($master, $filter_class);
		}
		
		if($form_state['values']['sec_filter'] != '--Select--'){
			$query=db_select($fees_student_adjustement_table,'sat');
			$query->join($student_table,'st','sat.adm_no = st.adm_no');
			$query->condition('st.section',$form_state['values']['sec_filter'])
				->fields('sat',array('id','adm_no'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_sec[$r->id.'#'.$r->adm_no] = $r->id;
			}
			$master = array_intersect_key($master, $filter_sec);
		}
		
		if($form_state['values']['receipt_no'] != NULL){
			$query=db_select($fees_student_adjustement_table,'sat');
			$query->join($student_table,'st','sat.adm_no = st.adm_no');
			$query->join($fees_student_payment_table,'spt','sat.adm_no = st.adm_no and sat.fee_id = spt.fee_id and sat.month = spt.month');
			$query->condition('spt.receipt_no',$form_state['values']['receipt_no'])
				->fields('sat',array('id','adm_no'))
				->fields('spt',array('receipt_no'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_receipt_no[$r->id.'#'.$r->adm_no] = $r->id;
			}
			$master = array_intersect_key($master, $filter_receipt_no);
		}
		
		foreach($master as $id){
			$adjustments = db_query(
				"SELECT * from $fees_student_adjustement_table where id = :id;", array(':id' => $id)
			);
			foreach($adjustments as $adjustment){
				$con_id = NULL;
				$receipt_no = NULL;
				$con_name = NULL;
				$fee_student_payment = db_query(
					"SELECT * from $fees_student_payment_table where fee_id = :fi and adm_no = :an and month = :mon;",
					array(':fi' => $adjustment->to_fee_id, ':an' => $adjustment->adm_no, ':mon' => $adjustment->month)
				);
				foreach($fee_student_payment as $fsp){
					$receipt_no = $fsp->receipt_no;
				}
				
				$fee_student_fine = db_query(
					"SELECT * from $fees_student_fine_table where id = :fi and adm_no = :an and month = :mon;",
					array(':fi' => $adjustment->to_fine_id, ':an' => $adjustment->adm_no, ':mon' => $adjustment->month)
				);
				foreach($fee_student_fine as $fsf){
					$receipt_no = $fsf->receipt_no;
				}
				if(substr($adjustment->fee_id, 0, 1) == 'c'){
					$con_id = substr($adjustment->fee_id, 1);
				}
				
				$student_data = db_query("
					SELECT * from {$student_table} where adm_no = :an", array(':an' => $adjustment->adm_no)
				);
				foreach($student_data as $sd){
					$name = $sd->student_name;
					$class = $sd->class;
					$sec = $sd->section;
				}
				
				$fee_data = db_query("
					SELECT * from {$fees_table} where fee_id = :fi", array(':fi' => $adjustment->to_fee_id)
				);
				foreach($fee_data as $fd){
					$ad_name = $fd->particulars;
				}
				
				$fine_data = db_query("
					SELECT * from {$fine_table} where id = :fi", array(':fi' => $adjustment->to_fine_id)
				);
				foreach($fine_data as $fd){
					$ad_name = $fd->particulars;
				}
				
				$row[$adjustment->id] = array(
					'#tree' =>TRUE,
					$adjustment->id => array(  //Generating unique array id for every form element
						'c0' => array(
							'#type' => 'checkbox',
						),
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $adjustment->adm_no .'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $name .'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $class.'-'.$sec.'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $receipt_no.'</h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $adjustment->fee_id .'</h3>',
						),
						'c6' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $ad_name .'</h3>',
						),
						'c7' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $adjustment->amount .'</h3>',
						),
					),
				);	
			}
		}
	}
	
	if(!isset($row)){
		drupal_set_message('No adjustments has been made.','warning');
		$row = array();
	}
	
	$form['lts'] = array(
	  '#theme' => 'remove_adjustment_table',
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

function apply_adj_filter_ajax($form, &$form_state){
	return $form['lts'];
}

/**
 *Implements submit function
 */
function delete_adjustment_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student_due_table = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment_table = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_adjustement_table = 'essa_'.$session_id.'_fees_student_adjustement';
	$fees_student_fine_table = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history_table = 'essa_'.$session_id.'_fees_payment_history';
	$fee_student_advance_table = 'essa_'.$session_id.'_fees_student_advance';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$fine_table = 'essa_'.$session_id.'_fees_student_fine';
	$advance_table = 'essa_'.$session_id.'_fees_student_advance';
	$concession_table = 'essa_'.$session_id.'_fees_concession';
	
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				if($v['c0'] == 1){
					$adjustments = db_query(
						"SELECT * from $fees_student_adjustement_table where id = :id;", array(':id' => $k)
					);
					foreach($adjustments as $ad){
						$adm_no = $ad->adm_no;
						$amt = $ad->amount;
						if($ad->to_fee_id != NULL){
							//This is case of advance adjustment
							if(substr($ad->fee_id, 0, 1) == 'c'){
								//This is the case of con advance adjustment
								$con_id = substr($ad->fee_id, 1);
								$month = $ad->month;
								$to_fee_id = $ad->to_fee_id;
								
								$fee_student_payment = db_query(
									"SELECT * from $fees_student_payment_table where fee_id = :fi and adm_no = :an and month = :mon;",
									array(':fi' => $ad->to_fee_id, ':an' => $ad->adm_no, ':mon' => $ad->month)
								);
								foreach($fee_student_payment as $fsp){
									$receipt_no = $fsp->receipt_no;
								}
								
								$fee_student_due = db_query(
									"SELECT * from $fees_student_due_table where fee_id = :fi and adm_no = :an;",
									array(':fi' => $ad->to_fee_id, ':an' => $ad->adm_no)
								);
								foreach($fee_student_due as $fsd){
									$new_amt = $fsd->$month + $amt;
								}
								db_merge($fees_student_due_table)
									->key(array('fee_id' => $to_fee_id, 'adm_no' => $adm_no))
									->fields (array(
										$month => $new_amt,
									)
								)
								->execute();
								
								$fee_student_advance = db_query(
									"SELECT * from $fee_student_advance_table where fee_id = :fi and adm_no = :an and receipt_no = :rn;",
									array(':fi' => 'c'.$con_id, ':an' => $ad->adm_no, ':rn' => $receipt_no)
								);
								foreach($fee_student_advance as $fsa){
									$new_adv_amt = $fsa->amount_remaining + $amt;
								}
								db_merge($fee_student_advance_table)
									->key(array('fee_id' => 'c'.$con_id, 'adm_no' => $adm_no))
									->fields (array(
										'amount_remaining' => $new_adv_amt,
									)
								)
								->execute();
								
								db_delete($fees_student_payment_table)
								->condition(db_and()
										->condition('fee_id', $to_fee_id)
										->condition('adm_no', $adm_no)
										->condition('month', $month)
										->condition('receipt_no', $receipt_no)
									)
								->execute();
								
								db_delete($fees_student_adjustement_table)
									->condition('id', $k)
										->execute();
							}else{
								//This is case of fee advance adjustment
								$to_fee_id = $ad->to_fee_id;
								$month = $ad->month;
								$fee_student_payment = db_query(
									"SELECT * from $fees_student_payment_table where fee_id = :fi and adm_no = :an and month = :mon;",
									array(':fi' => $ad->to_fee_id, ':an' => $ad->adm_no, ':mon' => $ad->month)
								);
								foreach($fee_student_payment as $fsp){
									$receipt_no = $fsp->receipt_no;
								}
								
								$fee_student_due = db_query(
									"SELECT * from $fees_student_due_table where fee_id = :fi and adm_no = :an;",
									array(':fi' => $ad->to_fee_id, ':an' => $ad->adm_no)
								);
								foreach($fee_student_due as $fsd){
									$new_amt = $fsd->$month + $amt;
								}
								db_merge($fees_student_due_table)
									->key(array('fee_id' => $to_fee_id, 'adm_no' => $adm_no))
									->fields (array(
										$month => $new_amt,
									)
								)
								->execute();
								
								$fee_student_advance = db_query(
									"SELECT * from $fee_student_advance_table where fee_id = :fi and adm_no = :an and receipt_no = :rn;",
									array(':fi' => $ad->fee_id, ':an' => $ad->adm_no, ':rn' => $receipt_no)
								);
								foreach($fee_student_advance as $fsa){
									$new_adv_amt = $fsa->amount_remaining + $amt;
								}
								db_merge($fee_student_advance_table)
									->key(array('fee_id' => $ad->fee_id, 'adm_no' => $adm_no))
									->fields (array(
										'amount_remaining' => $new_adv_amt,
									)
								)
								->execute();
								
								db_delete($fees_student_payment_table)
								->condition(db_and()
										->condition('fee_id', $to_fee_id)
										->condition('adm_no', $adm_no)
										->condition('month', $month)
										->condition('receipt_no', $receipt_no)
									)
								->execute();
								
								db_delete($fees_student_adjustement_table)
									->condition('id', $k)
										->execute();
							}
						}elseif($ad->to_fine_id != NULL){
							if(substr($ad->fee_id, 0, 1) == 'c'){
								//This is the case of con advance adjustment
								$con_id = substr($ad->fee_id, 1);
								$month = $ad->month;
								$to_fine_id = $ad->to_fine_id;
								
								$fee_student_fine_payment = db_query(
									"SELECT * from $fees_student_fine_table where id = :fi and adm_no = :an;",
									array(':fi' => $ad->to_fine_id, ':an' => $ad->adm_no)
								);
								foreach($fee_student_fine_payment as $fsp){
									$receipt_no = $fsp->receipt_no;
									$new_amt = $fsp->amount_paid - $amt;
								}
								
								db_merge($fees_student_fine_table)
									->key(array('id' => $to_fine_id, 'adm_no' => $adm_no))
									->fields (array(
										'amount_paid' => $new_amt,
									)
								)
								->execute();
								
								$fee_student_advance = db_query(
									"SELECT * from $fee_student_advance_table where fee_id = :fi and adm_no = :an and receipt_no = :rn;",
									array(':fi' => 'c'.$con_id, ':an' => $ad->adm_no, ':rn' => $receipt_no)
								);
								foreach($fee_student_advance as $fsa){
									$new_adv_amt = $fsa->amount_remaining + $amt;
								}
								db_merge($fee_student_advance_table)
									->key(array('fee_id' => 'c'.$con_id, 'adm_no' => $adm_no))
									->fields (array(
										'amount_remaining' => $new_adv_amt,
									)
								)
								->execute();
								
								db_delete($fees_student_adjustement_table)
									->condition('id', $k)
										->execute();
							}else{
								//This is case of fee advance adjustment
								//This is the case of con advance adjustment
								$con_id = substr($ad->fee_id, 1);
								$month = $ad->month;
								$to_fine_id = $ad->to_fine_id;
								
								$fee_student_fine_payment = db_query(
									"SELECT * from $fees_student_fine_table where id = :fi and adm_no = :an;",
									array(':fi' => $ad->to_fine_id, ':an' => $ad->adm_no)
								);
								foreach($fee_student_fine_payment as $fsp){
									$receipt_no = $fsp->receipt_no;
									$new_amt = $fsp->amount_paid - $amt;
								}
								
								db_merge($fees_student_fine_table)
									->key(array('id' => $to_fine_id, 'adm_no' => $adm_no))
									->fields (array(
										'amount_paid' => $new_amt,
									)
								)
								->execute();
								
								$fee_student_advance = db_query(
									"SELECT * from $fee_student_advance_table where fee_id = :fi and adm_no = :an and receipt_no = :rn;",
									array(':fi' => $ad->fee_id, ':an' => $ad->adm_no, ':rn' => $receipt_no)
								);
								foreach($fee_student_advance as $fsa){
									$new_adv_amt = $fsa->amount_remaining + $amt;
								}
								db_merge($fee_student_advance_table)
									->key(array('fee_id' => $ad->fee_id, 'adm_no' => $adm_no))
									->fields (array(
										'amount_remaining' => $new_adv_amt,
									)
								)
								->execute();
								
								db_delete($fees_student_adjustement_table)
									->condition('id', $k)
										->execute();
							}
						}else{
							//This is case of rebate
							$month = $ad->month;
							$to_fee_id = $ad->to_fee_id;
							//This is the case of con advance adjustment
							$month = $ad->month;
							$to_fee_id = $ad->to_fee_id;
							$fee_student_due = db_query(
								"SELECT * from $fees_student_due_table where fee_id = :fi and adm_no = :an;",
								array(':fi' => $ad->to_fee_id, ':an' => $ad->adm_no)
							);
							foreach($fee_student_due as $fsd){
								$new_amt = $fsd->$month + $amt;
							}
							db_merge($fees_student_due_table)
								->key(array('fee_id' => $to_fee_id, 'adm_no' => $adm_no))
								->fields (array(
									$month => $new_amt,
								)
							)
							->execute();
							
							db_delete($fees_student_adjustement_table)
								->condition('id', $k)
								->execute();
						}
					}
				}
			}
		}
	}
}

/**
 *Theme function
 */
function theme_remove_adjustment_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t(''), t('Adm No.'),t('Name'), t('Class'), t('Receipt No.'), t('Advance ID'), t('Adjusted to'), t('Amount Adjusted'));
  
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