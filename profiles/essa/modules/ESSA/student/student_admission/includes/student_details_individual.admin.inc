<?php
/**
 *Implements page callback function student_advanced_search
 */
function student_advanced_search($form, &$form_state){
  $form = array();
	$path = drupal_get_path('module', 'student_admission');
  drupal_add_js($path . '/keyboard_shortcut.js', 'file');
	
  $form['search_box'] = array(
    '#type' => 'textfield',
    '#title' => 'Search a Student',
    '#autocomplete_path' => 'individual_student_search/autocomplete',
  );
	
  $form['wrapper'] = array(
    '#type' => 'container',
    '#prefix' => '<div id = "student_wrapper">',
    '#suffix' => '</div>',
  );
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Search',
		'#ajax' => array(
      'event' => 'click',
      'callback' => 'student_data_ajax',
      'wrapper' => 'student_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
	);
	
  return $form;
}

function student_data_ajax($form, &$form_state){
  $session = variable_get('essa_sid');
  $index_table = 'essa_'.$session.'_student_index';
  $master_student_table = 'essa_'.$session.'_master_student_table';
  //$section_table = 'essa_'.$session.'_class_section';
  //$index_table = 'essa_'.$session.'_student_index';
  $recs =  db_query(
		"SELECT * from {$index_table} where records LIKE :rec", array(':rec' => '%'.$form_state['values']['search_box'].'%')
	);
	$row = array();
  foreach($recs as $rec){
    $student_rec =  db_query(
    	"SELECT * from {$master_student_table} where adm_no = :an", array(':an' => $rec->adm_no)
    );
    foreach($student_rec as $sr){
      $row[$sr->adm_no] = array(
        '#tree' =>TRUE,
        $sr->adm_no => array(  //Generating unique array id for every form element
          'c1' =>array(
            '#type' => 'markup',
            '#markup' => '<h3>'.$sr->adm_no.'</h3>',
          ),
          'c2' =>array(
            '#type' => 'markup',
            '#markup' => '<h3>'.$sr->roll_no.'</h3>',
          ),
          'c3' =>array(
        		'#type' => 'markup',
            '#markup' => '<h3>'.$sr->class.' - '.$sr->sec.'</h3>',
          ),
          'c4' =>array(
        		'#type' => 'markup',
            '#markup' => '<h3>'.l(t($sr->first_name.' '.$sr->middle_name.' '.$sr->last_name), 'user/'.$sr->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
          ),
          'c5' =>array(
        		'#type' => 'markup',
            '#markup' => '<h3>'.$sr->dob.'</h3>',
          ),
          'c6' =>array(
        		'#type' => 'markup',
            '#markup' => '<h3>'.$sr->doa.'</h3>',
          ),
          'c7' =>array(
          	'#type' => 'markup',
            '#markup' => '<h3>'.$sr->r_phone.' , '.$sr->c_phone.'</h3>',
          ),
        ),
      );
    }
  }
  $form['students'] = array(
    '#theme' => 'student_data_table',
    'rows' => $row,
    '#prefix' => '<div id = "student_wrapper">',
    '#suffix' => '</div>',
  );
	
  return $form['students'];
}

/**
 * Theme callback for the form table.
 */
function theme_student_data_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array( t('Admission No'),t('Roll No.'),t('Class'), t('Name'), t('Date Of Birth'), t('Date Of Admission'), t('Contact'));
  
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