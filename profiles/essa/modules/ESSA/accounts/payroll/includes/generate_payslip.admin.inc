<?php
/**
 *Implements page callback funtion - generate_payslip
 */
function generate_payslip($form, &$form_state, $month){
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$emp_table = 'essa_'.$session_id.'_master_staff_table';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$emp_sal_table = 'essa_'.$session_id.'_pr_emp_sal';
	$batch_increment_table = 'essa_'.$session_id.'_pr_batch_increment';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	$bonus_table = 'essa_'.$session_id.'_pr_bonus';
	$deduction_table = 'essa_'.$session_id.'_pr_deductions';
	$incentive_table = 'essa_'.$session_id.'_pr_incentive';
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
	
	// Attaches css and js from the field group module.
	$form['#attached']['css'] = array(
		drupal_get_path('module', 'field_group') . '/horizontal-tabs/horizontal-tabs.css',
	);
	$form['#attached']['js'] = array(
		drupal_get_path('module', 'field_group') . '/horizontal-tabs/horizontal-tabs.js',
	);
	 
	  // Defines the main tabs element.
	$form['tabs'] = array(
		'#type' => 'vertical_tabs',
		'#tree' => TRUE,
	);
	
	$month = '01'.$month;
	$month = str_replace(',','-',$month);
	$month = str_replace(' ','',$month);
	$month = strtotime($month);
	
	$month = date('Y_m', $month);
	
	
	
	$earning_salary_row = array();
	$deduction_salary_row = array();
	
	$employees = db_query("SELECT * FROM {$emp_table} WHERE status = 1");
	foreach($employees as $emp){
		$emp_id = $emp->emp_id;
		$emp_name = $emp->fname.' '.$emp->lname;
		
		$staff_leaves = db_query("SELECT * FROM {$leave_staff_table} WHERE emp_id = :eid AND leave_id = :lid;", array(':eid' => $emp_id, ':lid' => 'LWP'));
		foreach($staff_leaves as $st_leave){
			$leave = $st_leave->$month;
		}
	
		//dsm($leave);
		
		$form['tabs']['name'] = array(
			'#type' => 'markup',
			'#markup' => '<h3>Employee Name - '. $emp_name .'</h3>',
		);
		
		$form['tabs'][$emp_id] = array(
			'#type' => 'fieldset',
			'#title' => t($emp_id),
		);
		
		
		
		$emp_salary = db_query("SELECT * FROM {$emp_sal_table} WHERE emp_id = :eid;", array(':eid' => $emp_id));
		foreach($emp_salary as $emp_sal){
			
			$sal_detail = db_query("
				SELECT * from {$sal_detail_table} where sal_id = :si and sal_head = :sh;", array(':si' => $emp_sal->sal_id, ':sh' => $emp_sal->sal_head)
			);
			foreach($sal_detail as $sd){
				$deduction = $sd->is_deduction;
			}
			
			if($deduction == '0'){
				
				$earning_salary_row[$emp_sal->sal_head] = array(
					'#tree' => TRUE,
					$emp_sal->sal_head => array(
						$emp_sal->sal_head => array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $emp_sal->sal_head .'</h3>',
						),
						'amount/'.$emp_sal->sal_head => array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $emp_sal->amount .'</h3>',
						),
					),
				);
			}else{
				
				$deduction_salary_row[$emp_sal->sal_head] = array(
					'#tree' => TRUE,
					$emp_sal->sal_head => array(
						$emp_sal->sal_head => array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $emp_sal->sal_head .'</h3>',
						),
						'amount/'.$emp_sal->sal_head => array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $emp_sal->amount .'</h3>',
						),
					),
				);
			}
		}
		
		$form['tabs'][$emp_id]['earnings'] = array(
			'#type' => 'fieldset',
			'#title' => t('Earnings'),
		);
		
		$form['tabs'][$emp_id]['deductions'] = array(
			'#type' => 'fieldset',
			'#title' => t('Deductions'),
		);
		
		$form['tabs'][$emp_id]['earnings']['emp_sal_earnings_table'] = array(
			'#theme' => 'emp_sal_earnings_table',
			'rows' => $earning_salary_row,
		);
		
		$form['tabs'][$emp_id]['deductions']['emp_sal_deduction_table'] = array(
			'#theme' => 'emp_sal_deduction_table',
			'rows' => $deduction_salary_row,
		);
		
	}
	//dsm($row);
	
	return $form;
}

function generate_payslip_ajax($form, &$form_state){
	
	
	return $form['payslip_wrapper'];
}

/**
 *Theme function
 */
function theme_emp_sal_earnings_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	$header = array(t('Salary Head'), t('Amount'));
	
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
function theme_emp_sal_deduction_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	$header = array(t('Salary Head'), t('Amount'));
	
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