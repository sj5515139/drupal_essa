<?php
/**
 *Implements page cllback function - settings
 */
function settings($form, &$form_state){
	$session = variable_get('essa_sid');
	$grade_table = 'essa_'.$session.'_exam_grade_settings';
	$count = 1;

	for($i = 1;$i<=10;$i++){
		$grades = db_query("
			SELECT * from {$grade_table} where id = :id;", array(':id' => $i)
		);
		foreach($grades as $gr){
			$row[$gr->id] = array(
				'#tree' =>TRUE,
				$gr->id => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'textfield',
						'#size' => 10,
						'#default_value' => $gr->grade,
					),
					'c2' =>array(
						'#type' => 'textfield',
						'#size' => 10,
						'#default_value' => $gr->marks_from,
					),
					'c3' =>array(
						'#type' => 'textfield',
						'#size' => 10,
						'#default_value' => $gr->marks_to,
					),
					'c4' =>array(
						'#type' => 'textfield',
						'#size' => 10,
						'#default_value' => $gr->grade_point,
					),
				),
			);
			$count = $count + 1;
		}
	}
	
	if($count > 1){
		for($i = $count;$i<=$count;$i++){
			$row[$i] = array(
				'#tree' =>TRUE,
				$i => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'textfield',
						'#size' => 10,
					),
					'c2' =>array(
						'#type' => 'textfield',
						'#size' => 10,
					),
					'c3' =>array(
						'#type' => 'textfield',
						'#size' => 10,
					),
					'c4' =>array(
						'#type' => 'textfield',
						'#size' => 10,
					),
				),
			);
		}
	}else{
		for($i = 1;$i<=10;$i++){
			$row[$i] = array(
				'#tree' =>TRUE,
				$i => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'textfield',
						'#size' => 10,
					),
					'c2' =>array(
						'#type' => 'textfield',
						'#size' => 10,
					),
					'c3' =>array(
						'#type' => 'textfield',
						'#size' => 10,
					),
					'c4' =>array(
						'#type' => 'textfield',
						'#size' => 10,
					),
				),
			);
		}
	}
	$form['tab'] = array(
		'#theme' => 'settings_table',
		'rows' => $row,
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save'
	);
	return $form;
}

function settings_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$grade_table = 'essa_'.$session.'_exam_grade_settings';
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $v){
				$gr_id = NULL;
				$grades = db_query("
					SELECT * from {$grade_table} where grade = :gr;", array(':gr' => $v['c1'])
				);
				foreach($grades as $gr){
					$gr_id = $gr->id;
				}
				if($v['c1'] != NULL){
					db_merge($grade_table)
						->key(array('id' => $gr_id))
						->fields (array(
							'grade' => $v['c1'],
							'marks_from' => $v['c2'],
							'marks_to' => $v['c3'],
							'grade_point' => $v['c4'],
						)
					)
					->execute();		
				}
			}
		}
	}
	drupal_set_message('The grade settings were saved successfully.','status');
}

/**
 *Theme function
 */
function theme_settings_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	global $user;
	$header = array(t('Grade'), t('Marks From(in %)'), t('Marks To(in %)'), t('Grade Point'));
	
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