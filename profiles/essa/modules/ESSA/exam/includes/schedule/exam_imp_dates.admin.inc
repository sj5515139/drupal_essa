<?php
/**
 *Implements page callback function - create_imp_dates()
 */
function create_imp_dates($form, &$form_state, $term_id,  $exam_code){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$class_list_table = 'essa_'.$session_id.'_class_list';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$imp_date_table = 'essa_'.$session_id.'_exam_imp_dates';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	
	
	$class = db_query("SELECT * FROM {$master_exam_table} WHERE exam_code = :ec AND term =:t;", array(':ec' => $exam_code, ':t' => $term_id));
	foreach($class as $cl){
		$c_from = $cl->class_from;
		$c_to = $cl->class_to;
	}
	
	if($c_from == NULL){
		$cf_weight = 0;
	}else{
		$c_from_weight = db_query("SELECT * FROM {$class_list_table} WHERE class_id =:c;", array(':c' => $c_from));
		foreach($c_from_weight as $cfw){
			$cf_weight = $cfw->weight;
		}
	}
	
	if($c_to == NULL){
		$ct_weight = 16;
	}else{
		$c_to_weight = db_query("SELECT * FROM {$class_list_table} WHERE class_id =:c;", array(':c' => $c_to));
		foreach($c_to_weight as $ctw){
			$ct_weight = $ctw->weight;
		}
	}
	$classes = array('--Select--');
	$class_list = db_query("SELECT * FROM {$class_list_table} WHERE weight BETWEEN $cf_weight AND $ct_weight ORDER BY weight");
	foreach($class_list as $c){
		$classes[] = $c->class_id;
		$classes1[] = $c->class_id;
	}
	
	$form['sec_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "sec_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['sec_wrapper']['class'] = array(
		'#type' => 'select',
		'#title' => 'Select a Class',
		'#options' => drupal_map_assoc($classes),
		'#ajax' => array(
		  'event' => 'change',
		  'callback' => 'display_sections_ajax',
		  'wrapper' => 'sec_wrapper',
		  'method' => 'replace',
		  'effect' => 'fade',
		),
	);
	
	$form['date_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "date_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['exam_code'] = array(
		'#type' => 'value',
		'#value' => $exam_code,
	);
	
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id,
	);
	
	if(isset($form_state['values']['class'])){
		$class_term = taxonomy_get_term_by_name($form_state['values']['class']);
		foreach($class_term as $ct){
			$tid = $ct->tid;
		}
		
		$sections = array('--Select--');
		$sec = taxonomy_get_children($tid);
		foreach($sec as $s){
			$sections[] = $s->name;
		}
		
		$form['sec_wrapper']['sec'] = array(
			'#type' => 'select',
			'#title' => 'Select a Section',
			'#options' => drupal_map_assoc($sections),
			'#ajax' => array(
			  'event' => 'change',
			  'callback' => 'display_date_ajax',
			  'wrapper' => 'date_wrapper',
			  'method' => 'replace',
			  'effect' => 'fade',
			),
		);
		
		if(isset($form_state['values']['sec']) && $form_state['values']['sec'] != '--Select--'){
			
			$form['date_wrapper']['imp_dates'] = array(
				'#type' => 'fieldset',
				'#title' => 'Important Dates'
			);
			
			$format = 'd-m-Y';
			
			$dates = db_query("SELECT * FROM {$imp_date_table} WHERE term_id = :t AND exam_code =:ec AND class = :c;", array(':t' => $form_state['values']['term_id'], ':ec' => $form_state['values']['exam_code'], ':c' => $form_state['values']['class']));
			foreach($dates as $date){
				
				$row[$date->title] = array(
					'#tree' =>TRUE,
					$date->title => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $date->title .'</h3>',
						),
						'c2' =>array(
							'#type' => 'date_select',
							'#default_value' => NULL, 
							'#date_format' => $format,
							'#date_label_position' => 'within', 
							'#date_timezone' => 'asia/kolkata', 
							'#date_increment' => 5,
						),
						'c3' => array(
							'#type' => 'select',
							'#options' => drupal_map_assoc(array('0 day', '1 day', '2 days', 'Now')),
						),
						'c4' =>array(
							'#type' => 'checkboxes',
							'#options' => drupal_map_assoc(array('Students', 'Teachers', 'Principal', 'Parents')),
						),
					),
				);
				
			}
			
			$form['date_wrapper']['imp_dates']['date_table'] = array(
				'#theme' => 'imp_date_table',
				'rows' => $row,
			);
			
			
			$class = db_query("SELECT * FROM {$master_exam_table} WHERE exam_code = :ec;", array(':ec' => $exam_code));
			foreach($class as $cl){
				$c_from = $cl->class_from;
				$c_to = $cl->class_to;
				//dsm($c_to);
			}
			
			$c_from_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $c_from));
			foreach($c_from_weight as $cfw){
				$cf_weight = $cfw->weight;
			}
			$c_to_weight = db_query("SELECT * FROM {$class_table} WHERE class_id =:c;", array(':c' => $c_to));
			foreach($c_to_weight as $ctw){
				$ct_weight = $ctw->weight;
			}
			$classes = array();
			$class_list = db_query("SELECT * FROM {$class_table} WHERE weight BETWEEN :cfw AND :ctw ORDER BY weight",
				array(':cfw' => $cf_weight, ':ctw' => $ct_weight));
			foreach($class_list as $c){
				$classes[] = $c->class_id;
			}
			
			$form['date_wrapper']['imp_dates']['fs'] = array(
				'#type' => 'fieldset',
				'#title' => 'Same For Class'
			);
			$form['date_wrapper']['imp_dates']['fs']['cls'] = array(
				'#type' => 'checkboxes',
				'#options' => drupal_map_assoc($classes),
			);
			$form['date_wrapper']['submit'] = array(
				'#type' => 'submit',
				'#value' => 'Save',
				'#submit' => array('display_date_ajax_submit'),
			);
			$form['date_wrapper']['add_more'] = array(
				'#type' => 'submit',
				'#value' => 'Add More',
				'#submit' => array('add_more_submit'),
			);
		}
	}	
	
	return $form;
}

/**
 *Implements submit function - display_date_ajax_submit
 */
function display_date_ajax_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$imp_date_table = 'essa_'.$session_id.'_exam_imp_dates';
	$master_exam_table = 'essa_'.$session_id.'_master_exam';
	$classes = $form_state['values']['cls'];
	unset($form_state['values']['cls']);
	//dsm($form_state);
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				
				
				db_merge($imp_date_table)
				->key(array('term_id' => $form_state['values']['term_id'], 'exam_code' => $form_state['values']['exam_code'], 'class' => $form_state['values']['class'], 'title' => $k))
				->fields(array(
					'deadline' => $v['c2'],
				))
				->execute();
				
				foreach($v['c4'] as $a=> $b){
					if($a == 'Students' && $b == 1){
						db_merge($imp_date_table)
						->key(array('term_id' => $form_state['values']['term_id'], 'exam_code' => $form_state['values']['exam_code'], 'class' => $form_state['values']['class'], 'title' => $k))
						->fields(array(
							'student' => '1',
						))
						->execute();
					}elseif($a == 'parents' && $b == 1){
						db_merge($imp_date_table)
						->key(array('term_id' => $form_state['values']['term_id'], 'exam_code' => $form_state['values']['exam_code'], 'class' => $form_state['values']['class'], 'title' => $k))
						->fields(array(
							'parent' => '1',
						))
						->execute();
					}elseif($a == 'Principal' && $b == 1){
						db_merge($imp_date_table)
						->key(array('term_id' => $form_state['values']['term_id'], 'exam_code' => $form_state['values']['exam_code'], 'class' => $form_state['values']['class'], 'title' => $k))
						->fields(array(
							'principal' => '1',
						))
						->execute();
					}elseif($a == 'Teachers' && $b == 1){
						db_merge($imp_date_table)
						->key(array('term_id' => $form_state['values']['term_id'], 'exam_code' => $form_state['values']['exam_code'], 'class' => $form_state['values']['class'], 'title' => $k))
						->fields(array(
							'teachers' => '1',
						))
						->execute();
					}
					
				}
			}
		}
	}
	
	
	
	
}


/**
 *Implements submit function - add_more_submit
 */
function add_more_submit($form, &$form_state){
	global $base_url;
	$url = $base_url.'/admin/exam/'.$form_state['values']['term_id'].'/'.$form_state['values']['exam_code'].'/'.$form_state['values']['class'].'/add_more_dates';
	$form_state['redirect'] = $url;
}


/**
 *Implements ajax callback.
 */
function display_sections_ajax($form, &$form_state){
	//dsm($form_state);
	return $form;
}

/**
 *Implements ajax callback - display_student_ajax
 */
function display_date_ajax($form, &$form_state){
	return $form['date_wrapper'];
}

/**
 *Theme function student_passout_table()
 */
function theme_imp_date_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	
	$header = array(t('Title'),t('Date'), t('Notify Before'), t('Notify To'));

	
	
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