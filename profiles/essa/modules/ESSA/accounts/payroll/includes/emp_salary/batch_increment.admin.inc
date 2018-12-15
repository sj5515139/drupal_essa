<?php

/**
 *Implements page callback - batch_increment.
 */
function batch_increment($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$emp_table = 'essa_'.$session_id.'_master_staff_table';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$emp_sal_table = 'essa_'.$session_id.'_pr_emp_sal';
	$batch_increment_table = 'essa_'.$session_id.'_pr_batch_increment';
	
	$basic_info = db_query("
		SELECT * from {$basic_info_table};"
	);
	foreach($basic_info as $bi){
		$establishment_year = '01-'.'01-'.$bi->establishment_year;
		$estab_year = $bi->establishment_year;
	}
	
	$current_year = date('Y');
	$this_year = $estab_year;
	$i = 0;
	$batches = array('--Select--');
	while($i == 0){
		$year = '01-'.'01-'.$this_year;
		$next_year = date("y", strtotime(date("Y-m-d", strtotime($year)) . " + 12 months"));
		$batches[] = $this_year.' - '.$next_year;
		$this_year = date("Y", strtotime(date("Y-m-d", strtotime($year)) . " + 12 months"));
		if($this_year == $current_year){
			$i = 1;
		}
	}
	
	$sal_options = array('--Select--');
	$sal_type = db_query("
		SELECT * from {$sal_table};"
	);	
	foreach($sal_type as $st){
		$sal_options[] = $st->title;
	}
	$form['sal_category'] = array(
		'#type' => 'select',
		'#title' => t('Select a Salary category'),
		'#options' => drupal_map_assoc($sal_options),
	);
	
	$form['batch'] = array(
		'#type' => 'select',
		'#title' => t('Select a Batch'),
		'#options' => drupal_map_assoc($batches),
		'#ajax' => array(
      'event' => 'change',
      'callback' => 'display_salary',
      'wrapper' => 'payroll_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
	);
	
	$row = array();
	if(!empty($form_state['values']['sal_category']) && !empty($form_state['values']['batch'])){
		$flag = 0;
		$sal_type = db_query("
			SELECT * from {$sal_table} where title = :title;", array(':title' => $form_state['values']['sal_category'])
		);	
		foreach($sal_type as $st){
			$sal_id = $st->sal_id;
		}
	
		$sal_type = db_query("
			SELECT * from {$batch_increment_table} where sal_id = :sal_id and batch = :batch;", array(':sal_id' => $sal_id, ':batch' => $form_state['values']['batch'])
		);
		foreach($sal_type as $st){
			if($st->percent_of != NULL){
				$row[$form_state['values']['batch'].$st->sal_head] = array(
					'#tree' => TRUE,
					$st->sal_head => array(
					  'c1' => array(
						  '#type' => 'markup',
						  '#markup' => '<h3>'. $st->sal_head .'</h3>',
						),
						'c2' => array(
					    '#type' => 'textfield',
					    '#default_value' => $st->amount,
							'#size' => 10,
							'#disabled' => TRUE,
						),
						'c3' => array(
						  '#type' => 'textfield',
					    '#default_value' => $st->percent,
							'#size' => 10,
						),
						'c4' => array(
						  '#type' => 'markup',
					    '#markup' => '<h3>'. $st->percent_of .'</h3>',
						),
					),
				);	
			}else{
				$flag = 1;
				$row[$form_state['values']['batch'].$st->sal_head] = array(
					'#tree' => TRUE,
					$st->sal_head => array(
					  'c1' => array(
						  '#type' => 'markup',
						  '#markup' => '<h3>'. $st->sal_head .'</h3>',
						),
						'c2' => array(
					    '#type' => 'textfield',
					    '#default_value' => $st->amount,
							'#size' => 10,
						),
						'c3' => array(
						  '#type' => 'textfield',
					    '#default_value' => $st->percent,
							'#size' => 10,
							'#disabled' => TRUE,
						),
						'c4' => array(
						  '#type' => 'markup',
					    '#markup' => '<h3>'. $st->percent_of .'</h3>',
						),
					),
				);	
			}
		}
		
		if($flag == 0){
			$sal_type = db_query("
				SELECT * from {$sal_detail_table} where sal_id = :sal_id;", array(':sal_id' => $sal_id)
			);
			foreach($sal_type as $st){
				if($st->depends_on != NULL){
					$row[$st->sal_head] = array(
						'#tree' => TRUE,
						$st->sal_head => array(
						  'c1' => array(
							  '#type' => 'markup',
							  '#markup' => '<h3>'. $st->sal_head .'</h3>',
							),
							'c2' => array(
						    '#type' => 'textfield',
						    '#default_value' => $st->amount,
								'#size' => 10,
								'#disabled' => TRUE,
							),
							'c3' => array(
							  '#type' => 'textfield',
							  '#default_value' => $st->percent,
								'#size' => 10,
							),
							'c4' => array(
							  '#type' => 'markup',
						    '#markup' => '<h3>'. $st->depends_on .'</h3>',
							),
						),
					);
				}else{
					$row[$st->sal_head] = array(
						'#tree' => TRUE,
						$st->sal_head => array(
						  'c1' => array(
								'#type' => 'markup',
							  '#markup' => '<h3>'. $st->sal_head .'</h3>',
							),
							'c2' => array(
						    '#type' => 'textfield',
						    '#default_value' => $st->amount,
								'#size' => 10,
							),
							'c3' => array(
								'#type' => 'textfield',
							  '#default_value' => $st->percent,
								'#size' => 10,
								'#disabled' => TRUE,
							),
							'c4' => array(
							  '#type' => 'markup',
						    '#markup' => '<h3>'. $st->depends_on .'</h3>',
							),
						),
					);
				}
			}
		}
	}
	
	$form['cnt'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "payroll_wrapper">',
		'#suffix' => '</div>',
	);
	
	if(isset($row)){
		$form['cnt']['batch_increment_table'] = array(
		  '#theme' => 'batch_increment_table',
			'rows' => $row,
		);
		
		$form['cnt']['save'] = array(
		  '#type' => 'submit',
			'#value' => 'Save',
		);
	}
	
	return $form;
}

/**
 *Implements submit function - batch_increment.
 */
function batch_increment_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$emp_sal_table = 'essa_'.$session_id.'_pr_emp_sal';
	$batch_increment_table = 'essa_'.$session_id.'_pr_batch_increment';
	
	$sal_type = db_query("
		SELECT * from {$sal_table} where title = :title;", array(':title' => $form_state['values']['sal_category'])
	);	
	foreach($sal_type as $st){
		$sal_id = $st->sal_id;
	}
		
	foreach($form_state['values'] as $key=>$val){
		if(is_array($val)){
			foreach($val as $k => $v){
				if($v['c3'] != NULL){
					$sal_detail = db_query("
						SELECT * from {$sal_detail_table} where sal_id = :si and sal_head = :sh;", array(':si' => $sal_id, ':sh' => $k)
					);	
					foreach($sal_detail as $sd){
						//dsm($sd->depends_on);
						$new_amt = ($v['c3']/100)*$form_state['values'][$sd->depends_on][$sd->depends_on]['c2'];
						
						db_merge($batch_increment_table)
							->key(array('sal_id' => $sal_id, 'batch' => $form_state['values']['batch'], 'sal_head' => $k))
							->fields (array(
								'sal_id' => $sal_id,
								'batch' => $form_state['values']['batch'],
								'sal_head' => $k,
								'amount' => $new_amt,
								'percent' => $v['c3'],
								'percent_of' => $sd->depends_on,
							)
						)	
						->execute();	
					}
				}else{
					db_merge($batch_increment_table)
						->key(array('sal_id' => $sal_id, 'batch' => $form_state['values']['batch'], 'sal_head' => $k))
						->fields (array(
							'sal_id' => $sal_id,
							'batch' => $form_state['values']['batch'],
							'sal_head' => $k,
							'amount' => $v['c2'],
							'percent' => NULL,
							'percent_of' => NULL,
						)
					)	
					->execute();	
				}
			}
		}
	}
}

/**
 *Implements ajax callback function - display_salary
 */
function display_salary($form, &$form_state){
	return $form['cnt'];
}

/**
 *Theme function
 */
function theme_batch_increment_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	$header = array(t('Salary Head'), t('Amount'), t('Percent'), t('Percent of'));
	
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