<?php

/**
 *Implements page callback function - student_details
 */
function staff_details($form, &$form_state){
  $form = array();
  
  $form['staff_type'] =  array(
    '#title' => t('Select a type - '),
    '#type' => 'select',
    '#options' => drupal_map_assoc(array('Teaching', 'Non-Teaching')),
    '#ajax' => array(
      'event' => 'change',
      'callback' => 'display_staff_ajax',
      'wrapper' => 'staff_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#required' => TRUE,
  );
	
  $form['staff_wrapper'] = array(
    '#type' => 'container',
    '#prefix' => '<div id = "staff_wrapper">',
    '#suffix' => '</div>',
  );
  
  return $form;
}

function display_staff_ajax($form, &$form_state){
  $session_id = (string)variable_get('essa_sid');
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	$staffs = db_query("
    SELECT * from {$staff_table} where type = :type;", array(':type' => $form_state['values']['staff_type'])
  );
  foreach($staffs as $info){
    $row[$info->emp_id] = array(
      '#tree' =>TRUE,
      $info->emp_id => array(  //Generating unique array id for every form element
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$info->emp_id.'</h3>',
        ),
        'c2' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$info->fname.' '.$info->lname.'</h3>',
        ),
        'c3' =>array(
					'#type' => 'markup',
          '#markup' => '<h3>'.$info->joining_date.'</h3>',
        ),
        'c4' =>array(
					'#type' => 'markup',
          '#markup' => '<h3>'.$info->nickname.'</h3>',
        ),
        'c5' =>array(
					'#type' => 'markup',
          '#markup' => '<h3>'.$info->grade.'</h3>',
        ),
        'c6' =>array(
					'#type' => 'markup',
          '#markup' => '<h3>'.$info->phone_no.' , '.$info->mobile_no.'</h3>',
        ),
        'c7' =>array(
					'#type' => 'markup',
          '#markup' => '<h3>'.$info->email.'</h3>',
        ),
      ),
    );  
  }
  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['staff'] = array(
    '#theme' => 'staff_detail_table',
    'rows' => $row,
    '#prefix' => '<div id = "staff_wrapper">',
    '#suffix' => '</div>',
  );
  return $form['staff'];
}

/**
 * Theme callback for the form table.
 */
function theme_staff_detail_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('EmpID'), t('Name'),t('Joining Date'), t('NickName'), t('Grade'), t('Contact'),t('E-mail'));
  
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