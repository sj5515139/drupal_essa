<?php
/**
 *Implements page callback function - concession
 */
function concession($form = array(), &$form_state){
  $session = (string)variable_get('essa_sid');
	$concession_table = 'essa_'.$session.'_fees_concession';
  $fees_table = 'essa_'.$session.'_fees_structure';
  
  $concession = db_query("
    SELECT * from {$concession_table};
  ");
	$x = '<i class = "fa fa-pencil"></i>';
  $y = '<i class = "fa fa-calculator"></i>';
  foreach($concession as $con){
    $fees_table = 'essa_'.$session.'_fees_structure';
    $fees = db_query("
      SELECT * from {$fees_table} where fee_id = :fi;", array(':fi' => $con->fee_id)
    );
    foreach($fees as $fee){
      $particular = $fee->particulars;
    }
    $row[] = array(
			'#tree' =>TRUE,
		  $con -> con_id => array(  //Generating unique array id for every form element
		    'c1' =>array(
		      '#type' => 'markup',
		      '#markup' => '<h3>'. $con -> con_id .'</h3>',
			  ),
			  'c2' =>array(
		      '#type' => 'markup',
		      '#markup' => '<h3>'. $con -> name .'</h3>',
		    ),
			  'c3' =>array(
			    '#type' => 'markup',
			    '#markup' => '<h3>'.$particular.'</h3>',
		    ),
		    'c4' =>array(
		      '#type' => 'markup',
			    '#markup' => '<h3>'.$con->amount.'</h3>',
			  ),
				'c5' =>array(
		      '#type' => 'markup',
					'#markup' => '<h3>'.$con->percent.'</h3>',
			  ),
			  'c6' =>array(
		      '#type' => 'markup',
		      '#markup' => '<h3>'.l($x, 'admin/fees/concession/list/'.$con->con_id, array('html' => TRUE)).'</h3>',
		    ),
			  $con -> con_id =>array(
			    '#type' => 'submit',
			    '#submit' => array('delete_con'),
		      '#value' => 'Delete',
					'#name' => $con->con_id,
		      '#prefix' => '<div id = "delete_con">',
			    '#suffix' => '</div>',
			  ),
		  ),
		);
  }
  
	if(isset($row)){
		$form['con'] = array(
		  '#theme' => 'concession_table',
		  'rows' => $row,
		);
	}else{
		drupal_set_message('No Concession has been created yet.', 'error');
	}
  
  return $form;
}

function delete_con($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$concession_table = 'essa_'.$session_id.'_fees_concession';
	$student_concession_table = 'essa_'.$session_id.'_fees_student_concession';
	$flag = 0;
	$fee_student_concession = db_query("
		SELECT * from {$student_concession_table} where con_id = :ci;", array(':ci' => $form_state['triggering_element']['#name'])
	);
	foreach($fee_student_concession as $fsc){
		$flag = 1;
	}
	
	if($flag == 1){
		global $base_url;
		$remove_url = $base_url.'/admin/fees/concession/delete-concession';
		drupal_set_message('This concession is still linked to student account\'s. First, <a href = "'.$remove_url.'">remove concession</a> and try again.','status');
	}else{
		global $user;
		variable_set('delete-con_id'.$user->uid, $form_state['triggering_element']['#name']);
		$url = url('delete-concession_type', array('absolute' => TRUE));
		$form_state['redirect'] = $url;
	}
}

function delete_concession($form, &$form_state){
	return drupal_get_form('delete_con_type_confirm');
	
}

function delete_con_type_confirm($form, &$form_state){
	$heading = t('Are you sure to delete this concession.');
	$caption = '<h3>This action can\'t be undone.</h3>';
	
	$cancel_path = 'admin/fees/concession';
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

function delete_con_type_confirm_submit($form, &$form_state){
	global $user;
	$con_id = variable_get('delete-con_id'.$user->uid);
	$session_id = (string)variable_get('essa_sid');
	$concession_table = 'essa_'.$session_id.'_fees_concession';
	db_delete($concession_table)
		->condition('con_id', $con_id)
		->execute();
	
	$url = url('admin/fees/concession', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
}

/**
 *Theme function
 */
function theme_concession_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Concession ID'),t('Name'), t('Fee'), t('Amount'), t('Percent'), t(''), t(''));
  
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