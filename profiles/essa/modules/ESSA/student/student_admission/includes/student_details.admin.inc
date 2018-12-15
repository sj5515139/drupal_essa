<?php

/**
 *Implements page callback function - student_details
 */
function student_details($form, &$form_state){
  $form = array();
  
  module_load_include('inc', 'hierarchical_select', 'includes/common');
	
	$config = sd_hs_setting();
	$form['class'] =  array(
    '#title' => t('Select a Class - '),
    '#type' => 'hierarchical_select',
    '#config' => $config,
		'#required' => TRUE,
  );
	
  $form['go'] = array(
    '#type' => 'submit',
    '#value' => 'GO',
    '#ajax' => array(
      'event' => 'click',
      'callback' => 'display_student_ajax',
      'wrapper' => 'student_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  
  $form['student_wrapper'] = array(
    '#type' => 'container',
    '#prefix' => '<div id = "student_wrapper">',
    '#suffix' => '</div>',
  );
  return $form;
}

function display_student_ajax($form, &$form_state){
  $class = taxonomy_term_load($form_state['values']['class'][0]);
	$section = taxonomy_term_load($form_state['values']['class'][1]);
  $session = (string)variable_get('essa_sid');
  $table = 'essa_'.$session.'_'.'master_student_table';
  
  $student_info = db_query("
    SELECT * from {$table} where class = :class AND section =:sec order by roll_no;",array(':class' => $class->name, ':sec' => $section->name)
  );
  
  foreach($student_info as $info){
    //dsm($info);
    $row[$info->roll_no] = array(
      '#tree' =>TRUE,
      $info->roll_no => array(  //Generating unique array id for every form element
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$info->roll_no.'</h3>',
        ),
        'c2' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$info->adm_no.'</h3>',
        ),
        'c3' =>array(
					'#type' => 'markup',
          '#markup' => '<h3>'.l(t($info->student_name), 'user/'.$info->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
        ),
        'c4' =>array(
					'#type' => 'markup',
          '#markup' => '<h3>'.$info->f_first_name.' '.$info->f_middle_name.' '.$info->f_last_name.'</h3>',
        ),
        'c5' =>array(
					'#type' => 'markup',
          '#markup' => '<h3>'.$info->m_first_name.' '.$info->m_middle_name.' '.$info->m_last_name.'</h3>',
        ),
        'c6' =>array(
					'#type' => 'markup',
          '#markup' => ($info->r_phone != NULL)?'<h3>'.$info->r_phone.' , '.$info->c_phone.'</h3>':'<h3>'.$info->c_phone.'</h3>',
        ),
        'c7' =>array(
					'#type' => 'markup',
          '#markup' => '<h3>'.$info->s_email.'</h3>',
        ),
        'c8' =>array(
					'#type' => 'markup',
          '#markup' => '<h3>'.$info->p_email.'</h3>',
        ),
      ),
    );
  }
  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['students'] = array(
    '#theme' => 'student_detail_table',
    'rows' => $row,
    '#prefix' => '<div id = "student_wrapper">',
    '#suffix' => '</div>',
  );
  return $form['students'];
}

/**
 * Theme callback for the form table.
 */
function theme_student_detail_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Roll No.'), t('Admission No'),t('Name'), t('Father\'s Name'), t('Mother\'s Name'), t('Contact'),t('Student E-mail'),t('Parent\'s Email'));
  
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
 *Implements setting function for heirarchical select form class and section
 */
function sd_hs_setting(){
	// Load category based in vocabulary machine name
	$voc = 'class_vocab';//replace this with the taxonomy term
  $vocabulary = taxonomy_vocabulary_machine_name_load($voc);
	//dsm($vocabulary);
  
	$config = array(
		'module' => 'hs_taxonomy',
    'params' => array(
				'vid' => (int) $vocabulary->vid,
				'exclude_tid' => NULL,
				'root_term' => NULL,
				'entity_count_for_node_type' => NULL,
      ),
		'config_id'       => 'taxonomy-2',
		'save_lineage'    => 1,
		'enforce_deepest' => 0,
		'entity_count'    => 0,
		'require_entity'  => 0,
		'resizable'       => 0,
		'render_flat_select' => 0,
		'level_labels' => array(
		  'status' => 1,
		  'labels' => array(
		    0 => '--Select--',
		    1 => '--Select--',
		  ),
		),
		'dropbox' => array(
		  'status'    => 0,
		),
		'editability' => array(
		  'status' => 0,
		  'item_types' => array(
		    0 => '',
		    1 => '',
		  ),
		  'allowed_levels' => array(
		    0 => 1,
		    1 => 1,
		  ),
		  'allow_new_levels' => 0,
		  'max_levels'       => 1,
		),
	);
	return $config;
}
