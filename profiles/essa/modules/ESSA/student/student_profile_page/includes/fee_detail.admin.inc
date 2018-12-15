<?php

function display_fee_detail($form, &$form_state, $uid){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_table = 'essa_'.$session_id.'_fees_student_table';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_freq_table = 'essa_'.$session_id.'_fees_frequency';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fees_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	$payment_history = 'essa_'.$session_id.'_fees_payment_history';
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
  $basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	global $user;
	
	$form['uid'] = array(
    '#type' => 'value',
    '#value' => $uid,
  );
  
	$student = db_query("
		SELECT * from {$student_table} where uid = :uid;", array(':uid' => $uid)
	);
	foreach($student as $s){
    $adm_no = $s->adm_no;
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
  
	$form['adm_no'] = array(
		'#type' => 'value',
		'#value' => $adm_no,
	);
 	
	$total = 0;
	$sp = new stdClass();
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
		foreach($columns as $col){
			$total_fine = $total_fine + $sf->$col;
		}
	}
	
	$form['fee_summary'] = array(
		'#type' => 'markup',
		'#markup' => '<div style = "line-height: 0.8em; width: 100%;"><h2 style = "width: 250px; float: left;">Total fee paid till date - </h2><h2><b>'.$total.'</b> INR</h2><h2 style = "width: 250px; float: left;">Total due till date - </h2><h2><b>'.$total_due.'</b> INR</h2><h2 style = "width: 250px; float: left;">Total fine paid till date - </h2><h2><b>'.$total_fine.'</b> INR</h2></div>',
	);
	
	//----------------------------------------------------Due Detail---------------------------------------
	$student_due = db_query("
    SELECT * from {$fees_student_due} where adm_no = :an;", array(':an' => $adm_no)
  );
	foreach($student_due as $sd){
		foreach($columns as $col){
			if($sd->$col != 0 && $sd->$col != NULL){
				$fee_detail = db_query("
				  SELECT * from {$fees_table} where fee_id = :fid;", array(':fid' => $sd->fee_id)
				);
				foreach($fee_detail as $fd){
					$particulars = $fd->particulars;
					$freq_id = $fd->freq_id;
				}
				$due_date = db_query("
				  SELECT * from {$fees_freq_table} where freq_id = :fid;", array(':fid' => $freq_id)
				);
				foreach($due_date as $dd){
					$due_dt = date('d-M-Y',$dd->$col);
				}
				
				$due_row[$sd->fee_id.$col] = array(
					'#tree' =>TRUE,
					$sd->fee_id => array(  //Generating unique array id for every form element
						'c1' =>array(
						  '#type' => 'markup',
						  '#markup' => '<h3>'. $particulars.'</h3>',
						),
						'c2' =>array(
						  '#type' => 'markup',
						  '#markup' => '<h3>'. $col.'</h3>',
						),
						'c3' =>array(
						  '#type' => 'markup',
						  '#markup' => '<h3>'.$due_dt.'</h3>',
						),
				    'c4' =>array(
							'#type' => 'markup',
				      '#markup' => '<h3>'.$sd->$col.'</h3>',
				    ),
				  ),
				);
			}
		}
		$form['dd'] = array(
			'#type' => 'fieldset',
			'#title' => 'Due Detail',
			'#collapsed' => FALSE,
			'#collapsible' => TRUE,
		);
		
		$form['dd'][$sd->fee_id] = array(
			'#theme' => 'display_due_table',
			'rows' => $due_row,
		);
	}
	
	
	
	//-------------------------------Payment Details-------------------------------------
	$form['pf'] = array(
		'#type' => 'fieldset',
		'#title' => 'Payment History',
		'#collapsed' => TRUE,
		'#collapsible' => TRUE,
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
      ),
    );
		
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
						'#disabled' => TRUE,
          ),
        ),
      );
    }
    
		$fine_row = array();
		foreach($columns as $col){
      $x = $col.'_payment_id';
      $student_fine_detail = db_query("
        SELECT * from {$fees_student_fine} where $x = :pid;", array(':pid' => $sp->id)
      );
      foreach($student_fine_detail as $sfd){
				if($sfd->$col != NULL){
					$total = $total + $sfd->$col;
					$fine_row['fine#'.$sp->id.'-'.$sfd->id.'/'.$col] = array(
            '#tree' =>TRUE,
            'fine#'.$sp->id.'-'.$spd->fee_id.'/'.$col => array(  //Generating unique array id for every form element
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
                '#markup' => '<h3 style = "text-align: right;">'.$col.'</h3>',
              ),
              'c7' => array(
                '#type' => 'textfield',
                '#value' => $sfd->$col,
								'#size' => 10,
								'#disabled' => TRUE,
              ),
            ),
          );
        }
      }
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
      ),
    );
		
		$row = array_merge($row, $detail_row);
		$row = array_merge($row, $fine_row);
		$row = array_merge($row, $total_row);
		$form['pf'][$sp->id] = array(
			'#theme' => 'display_payment_history_table',
			'rows' => $row,
		);
		
		$total_row = $detail_row = $row = $fine_row = NULL;
  }
	
	return $form;	
}

/**
 *Theme function
 */
function theme_display_payment_history_table(&$variables){
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

/**
 *Theme function
 */
function theme_display_due_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Particulars'), t('Month'), t('Due Date'), t('Amount'));
  
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