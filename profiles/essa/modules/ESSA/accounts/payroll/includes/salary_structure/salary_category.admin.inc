<?php
/**
 *Implements page callback function - salary_category
 */
function salary_category($form, &$form_state, $sal_id){
	$session_id = (string)variable_get('essa_sid');
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$x = '<i class = "fa fa-pencil"></i>';
  $y = '<i class = "fa fa-calculator"></i>';
  
	$salary_head = db_query("
    SELECT * from {$sal_detail_table} where sal_id = :sal_id;", array(':sal_id' => $sal_id)
  );
  foreach($salary_head as $sh){
		if($sh->is_deduction == 0){
			$row[] = array(
			  '#tree' =>TRUE,
			  $sh -> sal_id => array(  //Generating unique array id for every form element
				  'c1' =>array(
			      '#type' => 'markup',
				    '#markup' => '<h3>'. $sh -> sal_head .'</h3>',
				  ),
			    'c2' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.$sh -> particular.'</h3>',
				  ),
				  'c3' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.$sh->depends_on.'</h3>',
			    ),
					'c4' =>array(
				    '#type' => 'markup',
						'#markup' => '<h3>'.$sh->amount.'</h3>',
			    ),
			    'c5' =>array(
			      '#type' => 'markup',
				    '#markup' => '<h3>'.$sh -> percent.'</h3>',
				  ),
			    'c6' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.l($x, 'admin/accounts/payroll/salary_structure/'.$sal_id.'/'.$sh->sal_head, array('html' => TRUE)).'</h3>',
				  ),
				  $sh->sal_id.'/'.$sh->sal_head =>array(
			      '#type' => 'submit',
			      '#submit' => array('delete_sh'),
			      '#value' => 'Delete',
						'#name' => $sh->sal_id.'/'.$sh->sal_head,
				    '#prefix' => '<div id = "delete_sh">',
				    '#suffix' => '</div>',
			    ),
			  ),
			);
		}else{
			$row[] = array(
			  '#tree' =>TRUE,
			  $sh -> sal_id => array(  //Generating unique array id for every form element
				  'c1' =>array(
			      '#type' => 'markup',
				    '#markup' => '<h3 style = "color: RED">'. $sh -> sal_head .'</h3>',
				  ),
			    'c2' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3 style = "color: RED">'.$sh -> particular.'</h3>',
				  ),
				  'c3' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3 style = "color: RED">'.$sh->depends_on.'</h3>',
			    ),
					'c4' =>array(
				    '#type' => 'markup',
						'#markup' => '<h3 style = "color: RED">'.$sh->amount.'</h3>',
			    ),
			    'c5' =>array(
			      '#type' => 'markup',
				    '#markup' => '<h3 style = "color: RED">'.$sh -> percent.'</h3>',
				  ),
			    'c6' =>array(
			      '#type' => 'markup',
			      '#markup' => '<h3>'.l($x, 'admin/accounts/payroll/salary_structure/'.$sal_id.'/'.$sh->sal_head, array('html' => TRUE)).'</h3>',
				  ),
				  $sh->sal_id.'/'.$sh->sal_head =>array(
			      '#type' => 'submit',
			      '#submit' => array('delete_sh'),
			      '#value' => 'Delete',
						'#name' => $sh->sal_id.'/'.$sh->sal_head,
				    '#prefix' => '<div id = "delete_sh">',
				    '#suffix' => '</div>',
			    ),
			  ),
			);
		}
		//dsm($sh->sal_id.'/'.$sh->sal_head);
	}
	
	if(!isset($row)){
    drupal_set_message('No Salary Heads has been created yet.', $type = 'error');
    $row = array();
  }
	
	$form['sal_head_table'] = array(
    '#theme' => 'sal_head_table',
    'rows' => $row,
  );
	
	$form['ins'] = array(
		'#type' => 'markup',
		'#markup' => '<h4><b>NOTE: </b>Rows marked in <span style = "color:RED">RED</span> are deductions.',
	);
	return $form;
}

function delete_sh($form, &$form_state){
	$arr = explode('/', $form_state['triggering_element']['#name'],2);
	$sal_id = $arr[0];
	$sal_head = $arr[1];
	global $user;
	variable_set('del_sh_sal_id'.$user->uid, $sal_id);
	variable_set('del_sh_sal_head'.$user->uid, $sal_head);
	$flag = 0;
	
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$emp_sal_table = 'essa_'.$session_id.'_pr_emp_sal';
	$salary_head = db_query("
    SELECT * from {$sal_detail_table} where sal_id = :sal_id;", array(':sal_id' => $sal_id)
  );
  foreach($salary_head as $sh){
		if($sh->depends_on == $sal_head){
			$flag = 1;
		}
	}
	
	if($flag == 1){
		drupal_set_message('There are salary heads that depends upon "'.$sal_head.'". Please remove the dependencies before you delete this salary head.','error');
	}else{
		$url = url('delete-sal-head'.$sal_id, array('absolute' => TRUE));
		$form_state['redirect'] = $url;
	}
}

/**
 *Implements delete confirm page callback
 */
function delete_sal_head_pagecallback(){
	return drupal_get_form('delete_sal_head_confirm');
}

/**
 *Implments confirm logic for delete salary structure.
 */
function delete_sal_head_confirm($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	global $user;
	$sal_id = variable_get('del_sh_sal_id'.$user->uid);
	
	$heading = t('Are you sure to delete this Salary Head?');
	$caption = '<h3>This action can\'t be undone. After deletion, this salary head will be removed from all employee\'s account linked with this salary category.</h3>';
	
	$cancel_path = 'admin/accounts/payroll/salary_structure/'.$sal_id;
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

/**
 *Implments submit logic for delete salary structure.
 */
function delete_sal_head_confirm_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$emp_sal_table = 'essa_'.$session_id.'_pr_emp_sal';
	global $user;
	$sal_id = variable_get('del_sh_sal_id'.$user->uid);
	$sal_head = variable_get('del_sh_sal_head'.$user->uid);
		
	db_delete($sal_detail_table)
		->condition(db_and()
				->condition('sal_id', $sal_id, '=')
				->condition('sal_head', $sal_head, '=')
			)
		->execute();
		
	db_delete($emp_sal_table)
		->condition(db_and()
				->condition('sal_id', $sal_id, '=')
				->condition('sal_head', $sal_head, '=')
			)
		->execute();
	
	$url = url('admin/accounts/payroll/salary_structure/'.$sal_id, array('absolute' => TRUE));
  $form_state['redirect'] = $url;
	
	drupal_set_message('The salary head '.$sal_head.' was deleted successfully!!!','status');
	drupal_flush_all_caches();
}


/**
 *Theme function
 */
function theme_sal_head_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Salary Head'), t('Particulars'), t('Depends on'), t('Amount'),t('Percent'), t(''), t(''));
  
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