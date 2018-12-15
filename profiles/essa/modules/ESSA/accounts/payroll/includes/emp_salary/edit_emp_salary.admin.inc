<?php
/**
 *Implements page callback - edit_emp_salary
 */
function edit_emp_salary($form = array(), &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$emp_table = 'essa_'.$session_id.'_master_staff_table';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$emp_sal_table = 'essa_'.$session_id.'_pr_emp_sal';
	global $user;
	$emp_id = variable_get('edit_emp_sal'.$user->uid);
	
	$form['emp_id'] = array(
		'#type' => 'value',
		'#value' => $emp_id, 
	);
	
	$employee = db_query("
		SELECT * from {$emp_table} where emp_id = :ei;", array(':ei' => $emp_id)
	);
	foreach($employee as $emp){
		$name = $emp->fname.' '.$emp->lname;
		
		$form['emp_id_markup'] = array(
			'#type' => 'markup',
			'#markup' => '<h3>Emp ID - <b>'.$emp_id.'</b></h3>',
		);
		
		$form['name'] = array(
			'#type' => 'markup',
			'#markup' => '<h3>Name - <b>'.$name.'</b></h3>',
		);
	}
	
	$employee = db_query("
		SELECT * from {$emp_sal_table} where emp_id = :ei;", array(':ei' => $emp_id)
	);
	foreach($employee as $emp){
		$sal_detail = db_query("
			SELECT * from {$sal_detail_table} where sal_id = :si and sal_head = :sh;", array(':si' => $emp->sal_id, ':sh' => $emp->sal_head)
		);
		foreach($sal_detail as $sd){
			$percent = $sd->percent;
		}
		
		if($percent == NULL){
			$row[$emp->sal_head] = array(
				'#tree' => TRUE,
				$emp->sal_head => array(
				  $emp->sal_head => array(
				    '#type' => 'markup',
				    '#markup' => '<h3>'. $emp->sal_head .'</h3>',
					),
					'amount/'.$emp->sal_head => array(
				    '#type' => 'textfield',
				    '#default_value' => $emp->amount,
						'#size' => 10,
					),
					'percent/'.$emp->sal_head => array(
				    '#type' => 'markup',
				    '#markup' => '<h3>'. $emp->percent .'</h3>',
					),
				),
			);
		}else{
			$row[$emp->sal_head] = array(
				'#tree' => TRUE,
				$emp->sal_head => array(
				  $emp->sal_head => array(
				    '#type' => 'markup',
				    '#markup' => '<h3>'. $emp->sal_head .'</h3>',
					),
					'amount/'.$emp->sal_head => array(
				    '#type' => 'markup',
				    '#markup' => '<h3>'. $emp->amount .'</h3>',
					),
					'percent/'.$emp->sal_head => array(
				    '#type' => 'textfield',
				    '#default_value' => $emp->percent,
						'#size' => 10,
					),
				),
			);
		}
	}
	
	$form['emp_sal_table'] = array(
	  '#theme' => 'edit_emp_sal_table',
		'rows' => $row,
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	return $form;
}

/**
 *Implements page callback - edit_emp_salary
 */
function edit_emp_salary_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$emp_table = 'essa_'.$session_id.'_master_staff_table';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$emp_sal_table = 'essa_'.$session_id.'_pr_emp_sal';
	
	foreach($form_state['values'] as $key=>$value){
		if(is_array($value)){
			foreach($value as $sal_head => $val){
				foreach($val as $type => $v){
					$arr = explode('/', $type, 2);
					$t = $arr[0];
					
					if($t == 'percent'){
						$employee = db_query("
							SELECT * from {$emp_sal_table} where emp_id = :ei and sal_head = :sh;", array(':ei' => $form_state['values']['emp_id'], ':sh' => $sal_head)
						);
						foreach($employee as $emp){
							$sal_detail = db_query("
								SELECT * from {$sal_detail_table} where sal_id = :si and sal_head = :sh;", array(':si' => $emp->sal_id, ':sh' => $sal_head)
							);
							foreach($sal_detail as $sd){
								$dependent_amt = $form_state['values'][$sd->depends_on][$sd->depends_on]['amount/'.$sd->depends_on];
								$new_amt = ($v/100) * $dependent_amt;
								db_merge($emp_sal_table)
								  ->key(array('emp_id' => $form_state['values']['emp_id'], 'sal_head' => $sal_head))
									->fields (array(
										'amount' => $new_amt,
										'percent' => $v,
									)
								)	
								->execute();
							}
						}
					}else{
						db_merge($emp_sal_table)
						  ->key(array('emp_id' => $form_state['values']['emp_id'], 'sal_head' => $sal_head))
							->fields (array(
								'amount' => $v,
							)
						)	
						->execute();
					}
				}
			}
		}
	}
	$form_state['redirect'] = 'admin/accounts/payroll/emp_sal';
}

/**
 *Theme function
 */
function theme_edit_emp_sal_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	$header = array(t('Salary Head'), t('Amount'), t('Percent'));
	
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
