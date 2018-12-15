<?php
/**
 * Implements callback function today_arrangement()
 */
function arrangement_history($form = array(), &$form_state){
	
	
	$session = variable_get('essa_sid');
	$tt_arrangement_table = 'essa_'.$session.'_time_table_arrangement';
	$arrangement = db_query("SELECT * FROM {$tt_arrangement_table}");
	foreach($arrangement as $ar){
		$date = date('Y-m-d',$ar->date);
		//dsm($date);
		$row[] = array(
			'#tree' =>TRUE,
			$ar->id => array(  //Generating unique array id for every form element
				'c1' =>array(
					'#type' => 'markup',
					'#markup' => '<h3>'.$date.'</h3>',
				),
				'c2' =>array(
					'#type' => 'markup',
					'#markup' => '<h3>'.$ar->class.'</h3>',
				),
				'c3' =>array(
					'#type' => 'markup',
					'#markup' => '<h3>'.$ar->period.'</h3>',
				),
				'c4' =>array(
					'#type' => 'markup',
					'#markup' => '<h3>'.$ar->teacher.'</h3>',
				),
			),
		);
	}
	if(isset($row)){
		$form['today_time_table'] = array(
			'#theme' => 'arrangement_history_table',
			'rows' => $row,
		);
	}else{
		$form['sd_wrapper']['msg'] = array(
			'#type' => 'markup',
			'#markup' => '</br><h3 style ="color: red;">There is no arrangement created yet.</h3>',
		);
	}
	return $form;
}


/**
 * Theme callback for the form table.
*/ 
function theme_arrangement_history_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Date'), t('Class'), t('Period'), t('Teacher'));
  
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


