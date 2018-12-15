<?php
/**
 * Implements callback function create_exam_schedule()
 */
function create_re_exam_schedule($form = array(), &$form_state, $term_id, $exam_code){
	$session_id = (string)variable_get('essa_sid');
	$class_list_table = 'essa_'.$session_id.'_class_list';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$exam_timing_table = 'essa_'.$session_id.'_exam_timing';
	$re_exam_table = 'essa_'.$session_id.'_exam_re_exam';
	
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
	}
	
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id,
	);
	
	$form['exam_code'] = array(
		'#type' => 'value',
		'#value' => $exam_code,
	);
	
	$form['class'] = array(
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
	
	$form['sec_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "sec_wrapper">',
		'#suffix' => '</div>',
	);
	
	if(isset($form_state['values']['class'])){
		if($form_state['values']['class'] != '--Select--'){
			$session_id = (string)variable_get('essa_sid');
			$subject_table = 'essa_'.$session_id.'_subjects_'.$form_state['values']['class'];
			//$timing_table = 'essa_'.$session_id.'_exam_timing';
			$master_exam_table = 'essa_'.$session_id.'_exam_master';
			$schedule_table = 'essa_'.$session_id.'_exam_schedule';
			
			$variable = variable_get($form_state['values']['term_id'].$form_state['values']['exam_code'].$form_state['values']['class'].'_result_generate_status');
			if(!isset($variable)){
				variable_set($form_state['values']['term_id'].$form_state['values']['exam_code'].$form_state['values']['class'].'_result_generate_status', NULL);
			}
			$option = array('0' => '--Select--');
			$flag = 0;
			$sittings = db_query("SELECT * FROM {$master_exam_table} WHERE exam_code = :ec AND term = :w;", array(':ec' => $form_state['values']['exam_code'], ':w' => $form_state['values']['term_id']));
			foreach($sittings as $sit){
				$date_from = date('Y-m-d',$sit->date_from);
				$date_to = date('Y-m-d',$sit->date_to);
				$sitting = $sit->no_of_sitting;
				if($sitting != NULL){
					if($sitting == '1'){
						$s = array('1' => '1');
						$flag = 1;
					}elseif($sitting == '2'){
						$s = array('1' => '1','2' => '2');
					}elseif($sitting == '3'){
						$s = array('1' => '1','2' =>'2', '3' =>'3');
					}elseif($sitting == '4'){
						$s = array('1' => '1','2' =>'2', '3' =>'3', '4' => '4');
					}elseif($sitting == '5'){
						$s =  array('1' => '1','2' =>'2', '3' =>'3', '4' => '4', '5' => '5');
					}
				}
			}
			//dsm($date_from);
			$date = getDatesFromRange($date_from ,$date_to, 'd-m-Y');
			
			$date = array_merge($option,$date);
			$option = array_merge($option,$s);
			$format = 'd-m-Y';
			if($flag == 1){
				$subjects = db_query("SELECT * FROM {$subject_table}");
				foreach($subjects as $sub){
					$d = NULL;
					$default_date = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c AND subject =:s;", array(':t' => $form_state['values']['term_id'], ':ec' => 're_'.$form_state['values']['exam_code'], ':c' => $form_state['values']['class'], ':s' => $sub->sub_id));
					foreach($default_date as $dd){
						$d = date('d-m-Y',$dd->date);
					}
					$format = 'H:i';
					$default_timing = db_query("SELECT * FROM {$exam_timing_table} WHERE term_id = :t AND exam_code = :ec AND class =:c AND sitting = 'Sitting 1';", array(':t' => $form_state['values']['term_id'], ':ec' => $form_state['values']['exam_code'], ':c' => $form_state['values']['class']));
					foreach($default_timing as $val){
						$tfh = date('H',$val->time_from);
						$tfm = date('i',$val->time_from);
						$tth = date('H',$val->time_to);
						$ttm = date('i',$val->time_to);
					}
					$time_from = array('hour' => $tfh, 'minute' => $tfm);
					$time_to = array('hour' => $tth, 'minute' => $ttm);
					//dsm($sub);
					$row[$sub->sub_id] = array(
						'#tree' =>TRUE,
						$sub->sub_id => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $sub->sub_name .'</h3>',
							),
							'c2' =>array(
								'#type' => 'select', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
								'#default_value' => isset($d)?$d:'--Select--', 
								'#options' => drupal_map_assoc($date),
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>Sitting 1</h3>',
							),
							'c4' =>array(
								'#type' => 'date_select', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
								'#default_value' => $time_from, 
								'#date_format' => $format,
								'#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
								'#date_timezone' => 'asia/kolkata', // Optional, if your date has a timezone other than the site timezone.
								'#date_increment' => 5, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.//'#prefix' => '<div id = "timing_wrapper">',
								//'#suffix' => '</div>',
							),
							'c5' =>array(
								'#type' => 'date_select', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
								'#default_value' => $time_to, 
							  '#date_format' => $format,
								'#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
							  '#date_timezone' => 'asia/kolkata', // Optional, if your date has a timezone other than the site timezone.
								'#date_increment' => 5, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.//'#prefix' => '<div id = "timing_wrapper">',
							),
						),
					);
				}
				$d = NULL;
				//dsm($row);
			}else{
				$format = 'H:i';
				$subjects = db_query("SELECT * FROM {$subject_table}");
				foreach($subjects as $sub){
					
					$default_date = db_query("SELECT * FROM {$schedule_table} WHERE term_id = :t AND exam_code = :ec AND class =:c AND subject =:s;", array(':t' => $form_state['values']['term_id'], ':ec' => $form_state['values']['exam_code'], ':c' => $form_state['values']['class'], ':s' => $sub->sub_id));
					foreach($default_date as $dd){
						$d = date('d-m-Y',$dd->date);
					}
					$row[$sub->sub_id] = array(
						'#tree' =>TRUE,
						$sub->sub_id => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $sub->sub_name .'</h3>',
							),
							'c2' =>array(
								'#type' => 'select', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
								'#default_value' => isset($d)?$d:NULL,
								'#options' => drupal_map_assoc($date),
								'#ajax' => array(
								  'event' => 'change',
								  'callback' => 'create_section_ajax',
								  'wrapper' => $sub->sub_id,
								  'method' => 'replace',
								  'effect' => 'fade',
								),
							),
							'c3' =>array(
								'#type' => 'select',
								'#options' => drupal_map_assoc($option),
							),
							'c4' =>array(
								'#type' => 'date_select', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
								//'#default_value' => $time_from, 
								'#date_format' => $format,
								'#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
								'#date_timezone' => 'asia/kolkata', // Optional, if your date has a timezone other than the site timezone.
								'#date_increment' => 5, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.//
								'#prefix' => '<div id = '.$sub->sub_id.'>',
								'#suffix' => '</div>',
							),
							'c5' =>array(
								'#type' => 'date_select', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
								//'#default_value' => $time_to, 
							  '#date_format' => $format,
								'#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
							  '#date_timezone' => 'asia/kolkata', // Optional, if your date has a timezone other than the site timezone.
								'#date_increment' => 5, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.//'#prefix' => '<div id = "timing_wrapper">',
							),
						),
					);
				}
				$d = NULL;
			}
			if(isset($row)){
				$form['sec_wrapper']['timing'] = array(
					'#theme' => 're_exam_schedule_table',
					'rows' => $row,
				);
				
				$form['sec_wrapper']['submit'] = array(
					'#type' => 'submit',
					'#value' => 'Save',
					'#submit' => array('display_schedule_ajax_submit'),
				);
			}else{
				
				global $base_url;
				$url = $base_url.'/admin/settings/subjects/'.$form_state['values']['class'];
				
				$form['sec_wrapper']['msg'] = array(
					'#type' => 'markup',
					'#markup' => '<h3 style = "color:RED;">No subjects are created yet for class '.$form_state['values']['class'].'. Click <a href = "'.$url.'">here</a> to create.</h3>',
				);
			}
		}
		global $user;
		variable_set('re_exam_schedule_class'.$user->uid, $form_state['values']['class']);
		variable_set('re_xam_schedule_term'.$user->uid, $term_id);
		variable_set('re_exam_schedule_exam'.$user->uid, $exam_code);
	}	
	
  return $form;
}

/**
 *Implements ajax callback - display_schedule_ajax_submit
 */
function display_schedule_ajax_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$schedule_table = 'essa_'.$session_id.'_exam_schedule';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				$flag = 0;
				$sittings = db_query("SELECT * FROM {$master_exam_table} WHERE exam_code = :ec AND term = :w;", array(':ec' => $form_state['values']['exam_code'], ':w' => $form_state['values']['term_id']));
				foreach($sittings as $sit){
					$sitting = $sit->no_of_sitting;
					if($sitting != NULL){
						if($sitting == '1'){
							$flag = 1;
						}
					}
				}
				if($flag == 1){
					if($v['c2'] != '--Select--'){
						$from = strtotime($v['c4']);
						$to = strtotime($v['c5']);
						db_merge($schedule_table)
						->key(array('term_id' => $form_state['values']['term_id'],'exam_code' => 're_'.$form_state['values']['exam_code'], 'class' => $form_state['values']['class'], 'subject' => $k))
						->fields(array(
							'term_id' => $form_state['values']['term_id'],
							'exam_code' => 're_'.$form_state['values']['exam_code'],
							'class' => $form_state['values']['class'],
							'subject' => $k,
							'date' => strtotime($v['c2']),
							'sitting' => 'Sitting 1',
							'time_from' => $from,
							'time_to' => $to,
						))
						->execute();
					}
				}else{
					if($v['c2'] != '--Select--'){
						$from = strtotime($v['c4']);
						$to = strtotime($v['c5']);
						db_merge($schedule_table)
						->key(array('term_id' => $form_state['values']['term_id'], 'exam_code' => 're_'.$form_state['values']['exam_code'], 'class' => $form_state['values']['class'], 'subject' => $k))
						->fields(array(
							'term_id' => $form_state['values']['term_id'],
							'exam_code' => 're_'.$form_state['values']['exam_code'],
							'class' => $form_state['values']['class'],
							'subject' => $k,
							'date' => strtotime($v['c2']),
							'sitting' => 'Sitting '.$v['c3'],
							'time_from' => $from,
							'time_to' => $to,
						))
						->execute();
					}
				}
				
			}
		}
	}
	
	drupal_set_message('Schedule has been created for class '.$form_state['values']['class'].'.','status');
	global $user;
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	//sending system alert
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'Schedule Has been created for class '.$form_state['values']['class'].'.',
		'priority' => 'M',
		'module' => 'Exam',
		'source_url' => 'admin/exam/'.$form_state['values']['term_id'].'/'.$form_state['values']['exam_code'].'/exam_schedule',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	
}

/**
 *Implements ajax callback.
 */
function display_sections_ajax($form, &$form_state){
	//dsm($form_state);
	return $form['sec_wrapper'];
}


/**
 *Theme function student_passout_table()
 */
function theme_re_exam_schedule_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	
	$session_id = (string)variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	
	$flag = 0;
	$sittings = db_query("SELECT * FROM {$master_exam_table} WHERE exam_code = :ec AND term = :w;", array(':ec' => $form_state['values']['exam_code'], ':w' => $form_state['values']['term_id']));
	foreach($sittings as $sit){
		$sitting = $sit->no_of_sitting;
		if($sitting != NULL){
			if($sitting == '1'){
				$flag = 1;
			}
		}
	}
	if($flag == 1){
		$header = array(t('Subject'),t('Select Date'), t('Select Sitting'), t('Time from'), t('Time to'));
	}else{
		$header = array(t('Subject'),t('Select Date'), t('Select Sitting'), t('Time from'), t('Time to'));
	}
	
	
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