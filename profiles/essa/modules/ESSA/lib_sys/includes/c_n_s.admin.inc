<?php
/**
 *Implements pagecallback function - c_n_s
 */
function c_n_s($form = array(), &$form_state){
  $form['no_of_cupboards'] = array(
    '#type' => 'textfield',
    '#title' => 'No. of Cupboards',
    '#required' => TRUE,
  );
  
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => 'Create',
    '#ajax' => array(
      'event' => 'click',
      'callback' => 'cupboard_create',
      'wrapper' => 'cupboard_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  
  $form['fs'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "cupboard_wrapper">',
		'#suffix' => '</div>',
	);
  return $form;
}

/**
 *Implements ajax callback function - cupboard_create
 */
function cupboard_create($form, &$form_state){
  $cupboard_id = 'A';
  for($i = 1; $i <= $form_state['values']['no_of_cupboards']; $i++){
    $row[$i] = array(
      '#tree' =>TRUE,
      $i => array(  //Generating unique array id for every form element
      	'c1' =>array(
        	'#type' => 'markup',
          '#markup' => '<h3 style = "text-align: left !important;">'. $cupboard_id .'</h3>',
        ),
        'c2' =>array(
      		'#type' => 'textfield',
          '#size' => 10,
        ),
      ),
    );
    ++$cupboard_id;
  }
    
  $form['fs']['cup_tab'] = array(
		'#theme' => 'cup_shelf_table',
		'rows' => $row,
	);
  
  $form['fs']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    '#submit' => array('save_cupboard'),
  );
  
  return $form['fs'];
}

/**
 *Implements validate function
 */
function c_n_s_validate($form, &$form_state){
  if(!is_numeric($form_state['values']['no_of_cupboards'])){
    form_set_error('no_of_cupboards','The entered value must be numeric.');
  }
}

/**
 * Theme callback for the form table.
*/ 
function theme_cup_shelf_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Cupboard ID'), 'No. of shelf');
  
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
