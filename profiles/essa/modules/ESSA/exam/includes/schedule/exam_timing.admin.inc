<?php
/**
 *Implements page callback function - create_timing()
 */
function create_timing($form, &$form_state,$term_id, $exam_code){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	
	$class_list_table = 'essa_'.$session_id.'_class_list';
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
	
	$form['class'] = array(
		'#type' => 'select',
		'#title' => 'Select a Class',
		'#options' => drupal_map_assoc($classes),
		'#ajax' => array(
      'event' => 'change',
      'callback' => 'display_timing_ajax',
			'wrapper' => 'timing_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
	);
	
	$form['timing_wrapper'] = array(
    '#type' => 'container',
    '#prefix' => '<div id = "timing_wrapper">',
    '#suffix' => '</div>',
  );
	
	$form['exam_code'] = array(
		'#type' => 'value',
		'#value' => $exam_code,
		'#prefix' => '<div id = "timing_wrapper">',
    '#suffix' => '</div>',
	);
	
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id,
		'#prefix' => '<div id = "timing_wrapper">',
    '#suffix' => '</div>',
	);
	
	if(isset($form_state['values']['class']) && $form_state['values']['class'] != '--Select--'){
		$session_id = (string)variable_get('essa_sid');
		//$class = taxonomy_term_load($form_state['values']['class'][0]);
		//$section = taxonomy_term_load($form_state['values']['class'][1]);
		$timing_table = 'essa_'.$session_id.'_exam_timing';
		$master_exam_table = 'essa_'.$session_id.'_exam_master';
		$class_list_table = 'essa_'.$session_id.'_class_list';
		$s = array();
		//dsm($form_state['values']['exam_code']);
		$sittings = db_query("SELECT * FROM {$master_exam_table} WHERE term = :ti and exam_code = :ec;", array(':ti' => $form_state['values']['term_id'],':ec' => $form_state['values']['exam_code']));
		foreach($sittings as $sit){
			$sitting = $sit->no_of_sitting;
			if($sitting != NULL){
				if($sitting == '1'){
					$s = array('1');
				}elseif($sitting == '2'){
					$s = array('1','2');
				}elseif($sitting == '3'){
					$s = array('0' => '1','1' =>'2', '2' =>'3');
				}elseif($sitting == '4'){
					$s = array('0' => '1','1' =>'2', '2' =>'3', '3' => '4');
				}elseif($sitting == '5'){
					$s =  array('0' => '1','1' =>'2', '2' =>'3', '3' => '4', '4' => '5');
				}
			}
		}
		$row = array();
		$format = 'H:i';
		$session_id = (string)variable_get('essa_sid');
		$timing_table = 'essa_'.$session_id.'_exam_timing';
		foreach($s as $k){
			$tfh = NULL;
			$tfm = NULL;
			$tth = NULL;
			$ttm = NULL;
			$def_sittings = db_query("
				SELECT * FROM {$timing_table} WHERE term_id = :ti and exam_code = :ec and class = :cl and sitting = :si;",
				array(':ti' => $form_state['values']['term_id'],
					':ec' => $form_state['values']['exam_code'],
					':cl' => $form_state['values']['class'],
					':si' => 'Sitting '.$k,
				));
			foreach($def_sittings as $val){
				$tfh = date('H',$val->time_from);
				$tfm = date('i',$val->time_from);
				$tth = date('H',$val->time_to);
				$ttm = date('i',$val->time_to);
			}
			
			
			$time_from = array('hour' => $tfh, 'minute' => $tfm);
			$time_to = array('hour' => $tth, 'minute' => $ttm);
			$row[$form_state['values']['class'].'/'.$k] = array(
				'#tree' =>TRUE,
				$k => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>Sitting '.$k.'</h3>',
					),
					'c2' =>array(
						'#type' => 'date_select', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
						'#default_value' => $time_from, 
				    '#date_format' => $format,
						'#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
					  '#date_timezone' => 'asia/kolkata', // Optional, if your date has a timezone other than the site timezone.
						'#date_increment' => 5, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.//'#prefix' => '<div id = "timing_wrapper">',
						//'#suffix' => '</div>',
					),
					'c3' =>array(
						'#type' => 'date_select', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
						'#default_value' => $time_to, 
					  '#date_format' => $format,
						'#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
				    '#date_timezone' => 'asia/kolkata', // Optional, if your date has a timezone other than the site timezone.
						'#date_increment' => 5, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.//'#prefix' => '<div id = "timing_wrapper">',
						//'#prefix' => '<div id = "timing_wrapper">',
						//'#suffix' => '</div>',
					),
				),
			);		
		}
			
		//$classes = array_diff($classes, array($form_state['values']['class']));
		unset($classes[0]);
		
		$form['timing_wrapper']['timing'] = array(
			'#theme' => 'exam_timing_table',
			'rows' => $row,
		);
		
		foreach($classes1 as $cls){
			if(in_array($form_state['values']['class'], variable_get($cls))){
				$class_grp = variable_get($form_state['values']['term_id'].'-'.$form_state['values']['exam_code'].'-'.$form_state['values']['class']);
			}
		}
		//dsm(variable_get($form_state['values']['class']));
		foreach($class_grp as $cl){
			$def_class = db_query("
				SELECT * FROM {$timing_table} WHERE term_id = :ti and exam_code = :ec and class = :cl;",
				array(':ti' => $form_state['values']['term_id'],
					':ec' => $form_state['values']['exam_code'],
					':cl' => $cl
				));
			foreach($def_class as $val){
				$selected_classes[] = $val->class;
			}
		}
		$selected_classes = array_unique($selected_classes);
		
		$flag = 0;
		if(in_array($form_state['values']['class'], $selected_classes)){
			$flag = 1;
			$form['flag'] = array(
				'#type' => 'value',
				'#value' => 1,
			);
		}else{
			$flag = 0;
			$form['flag'] = array(
				'#type' => 'value',
				'#value' => 0,
			);
		}
		
		$form['timing_wrapper']['fs'] = array(
			'#type' => 'fieldset',
			'#title' => 'Same For Class',
		);
		
		if(($key = array_search($form_state['values']['class'], $classes)) !== false) {
	    unset($classes[$key]);
		}
		
		if($flag == 1){
			$form['timing_wrapper']['fs']['cls'][$form_state['values']['class']] = array(
				'#type' => 'checkboxes',
				'#options' => drupal_map_assoc($classes),
				'#default_value' => array_unique($selected_classes),
			);	
		}else{
			$form['timing_wrapper']['fs']['cls_nodef'] = array(
				'#type' => 'checkboxes',
				'#options' => drupal_map_assoc($classes),
				'#default_value' => array(),
			);
		}
		
		$form['timing_wrapper']['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Save',
			'#submit' => array('display_timing_ajax_submit'),
		);
	}
	
  return $form;
}

/**
 *Implements form validation function.
 */
function create_timing_validate($form, &$form_state){
	
}

/**
 *Implements submit function - display_timing_ajax
 */
function display_timing_ajax_submit($form, &$form_state){
	//dsm($form_state);
	$session_id = (string)variable_get('essa_sid');
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$master_exam_table = 'essa_'.$session_id.'_master_exam';
	$class_list_table = 'essa_'.$session_id.'_class_list';
	global $user;
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	if($form_state['values']['flag'] == 1){
		$class = $form_state['values'][$form_state['values']['class']];
		$class_group[] = $class;
	}else{
		$class = $form_state['values']['cls_nodef'];
		$class_group[] = $class;
	}
	//dsm($class_group);
	
	$this_grp[] = $form_state['values']['class'];
	foreach($class_group as $val){
		foreach($val as $k => $v){
			if($v != '0'){
				$this_grp[] = $v;
			}
		}
	}
	foreach($this_grp as $tg){
		variable_set($form_state['values']['term_id'].'-'.$form_state['values']['exam_code'].'-'.$tg, $this_grp);
	}
	$classes[] = $form_state['values']['class'];
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				
				if(is_array($v)){
					$sitting_val = 'Sitting '.$k;
					$from = strtotime($v['c2']);
					$to = strtotime($v['c3']);
				}
				
				if((int)$from != 0 && (int)$to != 0){
					db_merge($timing_table)
						->key(array('term_id' =>$form_state['values']['term_id'], 'exam_code' => $form_state['values']['exam_code'], 'class' => $form_state['values']['class'], 'sitting' => $sitting_val ))
						->fields(array(
							'term_id' =>$form_state['values']['term_id'],
							'exam_code' => $form_state['values']['exam_code'],
							'class' => $form_state['values']['class'],
							'sitting' => $sitting_val,
							'time_from' => (int)$from,
							'time_to' => (int)$to,
						))
						->execute();	
				}
				//sending system alert
				$created_date = date("Y-m-d H:i:s");
				$strtodate = strtotime($created_date);
				db_insert($sys_alert_table)
				->fields(array(
					'message' => 'Timing for Exam '.$form_state['values']['exam_code'].' class '.$form_state['values']['class'].' was created.',
					'priority' => 'M',
					'module' => 'Exam',
					'source_url' => 'admin/exam/create_exam',
					'timestamp' => $strtodate,
					'source_uid' => $user->uid,
				))
				->execute();
			}
			foreach($class as $c){
				if($c != '0'){
					//dsm($c);
					if((int)$from != 0 && (int)$to != 0){
						db_merge($timing_table)
							->key(array('term_id' =>$form_state['values']['term_id'], 'exam_code' => $form_state['values']['exam_code'], 'class' => $c, 'sitting' => $sitting_val))
							->fields(array(
								'term_id' =>$form_state['values']['term_id'],
								'exam_code' => $form_state['values']['exam_code'],
								'class' => $c,
								'sitting' => $sitting_val,
								'time_from' => (int)$from,
								'time_to' => (int)$to,
						))
						->execute();
					}
					
					$classes = variable_get($form_state['values']['term_id'].'-'.$form_state['values']['exam_code'].'-'.$form_state['values']['class']);
					if(!in_array($c, $classes)){
						db_delete($timing_table)
							->condition('term_id', $form_state['values']['term_id'])
							->condition('exam_code', $form_state['values']['exam_code'])
							->condition('class', $c)
							->execute();
						variable_del($form_state['values']['term_id'].'-'.$form_state['values']['exam_code'].'-'.$c);
					}
					//sending system alert
					$created_date = date("Y-m-d H:i:s");
					$strtodate = strtotime($created_date);
					db_insert($sys_alert_table)
					->fields(array(
						'message' => 'Timing of Exam '.$form_state['values']['exam_code'].' for class '.$c.' was set.',
						'priority' => 'M',
						'module' => 'Exam',
						'source_url' => 'admin/exam/create_exam',
						'timestamp' => $strtodate,
						'source_uid' => $user->uid,
					))
					->execute();
				}
			}
		}
	}
	
	
	drupal_set_message('Timing was recorded successfully.','status');
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
function display_timing_ajax($form, &$form_state){
	return $form['timing_wrapper'];
}



/**
 *Theme function student_passout_table()
 */
function theme_exam_timing_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	$header = array(t('Sitting'),t('Time From'), t('Time To'));
	
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
