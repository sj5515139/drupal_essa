<?php
/**
 * Implements callback function create_exam_schedule()
 */
function create_exam_schedule($form = array(), &$form_state, $term_id, $exam_code, $class){
	$session_id = (string)variable_get('essa_sid');
	$schedule_table = 'essa_'.$session_id.'_exam_schedule';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	
	$subjects  = db_query("SELECT * FROM {$schedule_table} WHERE exam_code = :ec AND class = :c;", array(':ec' => $exam_code, ':c' => $class));
	foreach($subjects as $sub){
		$flag = 0;
		$sittings = db_query("SELECT * FROM {$master_exam_table} WHERE exam_code = :ec AND term = :w;", array(':ec' => $exam_code, ':w' => $term_id));
		foreach($sittings as $sit){
			$sitting = $sit->no_of_sitting;
			if($sitting != NULL){
				if($sitting == '1'){
					$flag = 1;
				}
			}
		}
		$format = 'H:i';
		if($flag == 1){
			$time = db_query("SELECT * FROM {$timing_table} WHERE exam_code = :ec AND class = :c AND sitting = :s;", array(':ec' => $exam_code, ':c' => $class, ':s' => $sub->sitting));
			foreach($time as $t){
				$time_from = date($format, $t->time_from);
				$time_to = date($format, $t->time_to);
			}
			$subject_table = 'essa_'.$session_id.'_subjects_'.$class;
			$subject_name = db_query("SELECT * FROM {$subject_table} WHERE sub_id =:s;", array(':s' => $sub->subject));
			foreach($subject_name as $sn){
				$sub_name = $sn->sub_name;
			}
			$row[$sub->subject] = array(
				'#tree' =>TRUE,
				$sub->subject => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $sub_name .'</h3>',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'.date('d-m-Y',$sub->date) .'</h3>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $sub->sitting .'</h3>',
					),
					'c4' =>array(
						'#type' => 'date_select', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
						'#default_value' => $time_from, 
					  '#date_format' => $format,
						'#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
					  '#date_timezone' => 'asia/kolkata', // Optional, if your date has a timezone other than the site timezone.
						'#date_increment' => 5, 
					),
					'c5' =>array(
						'#type' => 'date_select', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
						'#default_value' => $time_to, 
					  '#date_format' => $format,
						'#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
					  '#date_timezone' => 'asia/kolkata', // Optional, if your date has a timezone other than the site timezone.
						'#date_increment' => 5, 
					),
				),
			);
		}else{
			$time = db_query("SELECT * FROM {$timing_table} WHERE exam_code = :ec AND class = :c AND sitting = :s;", array(':ec' => $exam_code, ':c' => $class, ':s' => $sub->sitting));
			foreach($time as $t){
				$time_from = date($format, $t->time_from);
				$time_to = date($format, $t->time_to);
			}
			$subject_table = 'essa_'.$session_id.'_subjects_'.$class;
			$subject_name = db_query("SELECT * FROM {$subject_table} WHERE sub_id =:s;", array(':s' => $sub->subject));
			foreach($subject_name as $sn){
				$sub_name = $sn->sub_name;
			}
			$row[$sub->subject] = array(
				'#tree' =>TRUE,
				$sub->subject => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $sub_name .'</h3>',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. date('d-m-Y',$sub->date) .'</h3>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $sub->sitting .'</h3>',
					),
					'c4' =>array(
						'#type' => 'date_select', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
						'#default_value' => $time_from, 
					  '#date_format' => $format,
						'#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
					  '#date_timezone' => 'asia/kolkata', // Optional, if your date has a timezone other than the site timezone.
						'#date_increment' => 5, 
					),
					'c5' =>array(
						'#type' => 'date_select', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
						'#default_value' => $time_to, 
					  '#date_format' => $format,
						'#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
					  '#date_timezone' => 'asia/kolkata', // Optional, if your date has a timezone other than the site timezone.
						'#date_increment' => 5, 
					),
				),
			);
			
		}
	}
	$form['timing'] = array(
		'#theme' => 'set_time_table',
		'rows' => $row,
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Save'
	);
	$form['term_id'] = array(
		'#type' => 'value',
		'#value' => $term_id,
	);
	
	$form['exam_code'] = array(
		'#type' => 'value',
		'#value' => $exam_code,
	);
	return $form;
}

/**
 *Theme function set_time_table()
 */
function theme_set_time_table(&$variables){
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
		$header = array(t('Subject'),t('Date'),t('Sitting'),t('Time From'),t('Time To'));
	}else{
		$header = array(t('Subject'),t('Date'),t('Sitting'),t('Time From'),t('Time To'));
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