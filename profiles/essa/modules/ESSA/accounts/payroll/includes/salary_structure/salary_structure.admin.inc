<?php

/**
 * Implements page callback function - salary_structure
 */
function salary_structure($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$x = '<i class = "fa fa-pencil"></i>';
	
	$salary_type = db_query("
    SELECT * from {$sal_table};"
  );
	foreach($salary_type as $st){
		$sal_heads[$st->sal_id] = '';
		$salary_head = db_query("
		  SELECT * from {$sal_detail_table} where sal_id = :sal_id;", array(':sal_id' => $st->sal_id)
		);
		foreach($salary_head as $sh){
			$sal_heads[$st->sal_id] .= $sh->sal_head.', ';
		}
		$sal_heads[$st->sal_id] = rtrim($sal_heads[$st->sal_id],", ");
		
		$row[] = array(
		  '#tree' =>TRUE,
		  $st -> sal_id => array(  //Generating unique array id for every form element
			  'c1' =>array(
			    '#type' => 'markup',
				  '#markup' => '<h3>'. $st -> title .'</h3>',
			  ),
		    'c2' =>array(
		      '#type' => 'markup',
			    '#markup' => '<h3>'.$sal_heads[$st->sal_id].'</h3>',
				),
			  'c3' =>array(
			    '#type' => 'markup',
			    '#markup' => '<h3>'.l($x, 'admin/accounts/payroll/salary_structure/'.$st->sal_id, array('html' => TRUE)).'</h3>',
			  ),
			  $st -> sal_id =>array(
		      '#type' => 'submit',
			    '#submit' => array('delete_sal'),
			    '#value' => 'Delete',
					'#name' => $st->sal_id,
			    '#prefix' => '<div id = "delete_sal">',
			    '#suffix' => '</div>',
		    ),
			),
		);
	}
  
	if(!isset($row)){
    drupal_set_message('No Salary Type has been created yet.', $type = 'error');
    $row = array();
  }else{
		$form['sal_table'] = array(
		  '#theme' => 'sal_type_table',
		  'rows' => $row,
		);
		
		$form['help'] = array(
			'#type' => 'markup',
			'#markup' => '<h3><b>NOTE:</b> You can either allot salary to employees by clicking on the button below, or after every 3 hours an automatic process will update the salaries of employees.</h3>',
		);
		
		$form['allot_sal'] = array(
			'#type' => 'submit',
			'#value' => 'Allot Salary',
			'#submit' => array('allot_sal'),
		);
	}
	
	return $form;
}

/**
 *Implements allot_sal function
 */
function allot_sal($form, &$form_state){
	drupal_set_message('The salary was alloted to employees successfully!!!','status');
	drupal_cron_run();
}

/**
 *Implements delete function
 */
function delete_sal($form, &$form_state){
	global $user;
	variable_set('del_sal_id'.$user->uid, $form_state['triggering_element']['#name']);
	
	$url = url('delete-sal-structure', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
}

/**
 *Implements delete confirm page callback
 */
function delete_sal_type_pagecallback(){
	return drupal_get_form('delete_sal_type_confirm');
}

/**
 *Implments confirm logic for delete salary structure.
 */
function delete_sal_type_confirm($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	
	$heading = t('Are you sure to delete this Salary Catergory?');
	$caption = '<h3>This action can\'t be undone. After deletion, this salary will be removed from all employee\'s account.</h3>';
	
	$cancel_path = 'admin/accounts/payroll/salary_structure';
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

/**
 *Implments submit logic for delete salary structure.
 */
function delete_sal_type_confirm_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$emp_sal_table = 'essa_'.$session_id.'_pr_emp_sal';
	$sal_id = variable_get('del_sal_id'.$user->uid);
	
	db_delete($sal_table)
		->condition('sal_id', $sal_id)
		->execute();
		
	db_delete($sal_detail_table)
		->condition('sal_id', $sal_id)
		->execute();
		
	db_delete($emp_sal_table)
		->condition('sal_id', $sal_id)
		->execute();
	
	$url = url('admin/accounts/payroll/salary_structure', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
	
	drupal_set_message('The salary category '.$sal_id.' was deleted successfully!!!','status');
	drupal_flush_all_caches();
}

	/*
	global $user;
	$session_id = (string)variable_get('essa_sid');
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_student = 'essa_'.$session_id.'_fees_student';
	$fees_student_due = 'essa_'.$session_id.'_fees_student_due';
	$fee_id = variable_get('delete-fee_id'.$user->uid);
	db_delete($fees_table)
		->condition('fee_id', $fee_id)
		->execute();
		
	db_delete($fees_student)
		->condition('fee_id', $fee_id)
		->execute();
		
	db_delete($fees_student_due)
		->condition('fee_id', $fee_id)
		->execute();
	
	$url = url('admin/fees/fee_structure', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
	drupal_set_message('The fees was deleted & removed from all student\'s account.');
}

/**
 *Theme function
 */
function theme_sal_type_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Salary Type'), t('Heads'), t(''), t(''));
  
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