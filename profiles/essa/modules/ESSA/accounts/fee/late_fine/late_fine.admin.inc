<?php

/**
 *Implements page callback function - late_fine
 */
function late_fine($form=array(), &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	foreach($classes as $class){
		$cl_options[] = $class->class_id;
	}
  
	$form['help'] = array(
		'#type' => 'markup',
		'#markup' => '<h4><b>NOTE:</b>To set fine amount for each months separaterly, leave the fine amount for all months blank.
		Remember to fill all the amount columns. If left blank no fine will be applied for that month.</h4>',
	);
	
  $form['class_from'] = array(
    '#type' => 'select',
    '#title' => t('Class From'),
    '#options' => drupal_map_assoc($cl_options),
		'#required' => TRUE,
  );
  
  $form['class_to'] = array(
    '#type' => 'select',
    '#title' => t('Class To'),
    '#options' => drupal_map_assoc($cl_options),
		'#required' => TRUE,
  );
	
	$form['amount'] = array(
		'#type' => 'textfield',
		'#title' => 'Fine Amount for all months',
		'#description' => '(per day)',
		'#size' => 12,
	);
	
	$form['deadline'] = array(
		'#title' => t('Set Collection Date for all Months'),
    '#type' => 'date_select',
		'#date_label_position' => 'within',
		'#date_format' => 'd',
    '#default_value' => date('d'),
	);
	
	$form['or'] = array(
		'#type' => 'markup',
		'#markup' => '<h1 style = "padding-top: 4px !important;"><b>OR</b></h1><h2>Select deadlines for individual months -</h2> '
	);
	
	$options = array();
	$session = (string)variable_get('essa_sid');
	$basic_info_table = 'essa_'.$session.'_basicinfo';
	$binfo = db_query("
    SELECT * from {$basic_info_table};
  ");
	foreach($binfo as $info){
		$start_date = $info->academicyearstart;
		$end_date = $info->academicyearend;
	}
  $start = new DateTime($start_date);
	$start->modify('first day of this month');
	$end      = new DateTime($end_date);
	$end->modify('first day of next month');
	$interval = DateInterval::createFromDateString('1 month');
	$period   = new DatePeriod($start, $interval, $end);
	foreach ($period as $dt) {
		$options[] = $dt->format("M-Y");
	}
	
	foreach($options as $mon){
		$row[$mon] = array(
			'#tree' =>TRUE,
			$mon => array(  //Generating unique array id for every form element
		    'c1' =>array(
		      '#type' => 'markup',
		      '#markup' => '<h3 style = "text-align: left !important;">'. $mon .'</h3>',
			  ),
				'c2' => array(
					'#type' => 'date_select',
					'#date_label_position' => 'within',
					'#date_format' => 'd',
					'#default_value' => date('d'),
				),
				'c3' => array(
					'#type' => 'textfield',
					'#size' => 10,
				),
			),
		);
	}
	
	$form['lts'] = array(
		'#theme' => 'late_fine_table',
		'rows' => $row,
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	return $form;
}

/**
 *Implements submit function.
 */
function late_fine_submit($form, &$form_state){
	$values = array();
	if($form_state['values']['amount'] == NULL){
		foreach($form_state['values'] as $key){
			if(is_array($key)){
				foreach($key as $mon=>$deadline){
					$col = str_replace('-', '_', $mon);
					$due_dt = $deadline['c2'].'-'.$mon;
					$due_dt = strtotime($due_dt);
					$values[$col][$due_dt] = $deadline['c3'];
				}
			}
		}	
	}else{
		foreach($form_state['values'] as $key){
			if(is_array($key)){
				foreach($key as $mon=>$deadline){
					$col = str_replace('-', '_', $mon);
					$due_dt = $form_state['values']['deadline'].'-'.$mon;
					$due_dt = strtotime($due_dt);
					$values[$col][$due_dt] = $form_state['values']['amount'];
				}
			}
		}
	}
	
	$session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$classes = db_query("
    SELECT * from {$class_list} where class_id = :ci;", array(':ci' => $form_state['values']['class_from'])
  );
	foreach($classes as $class){
		$class_from_weight = $class->weight;
	}
	
	$classes = db_query("
    SELECT * from {$class_list} where class_id = :ci;", array(':ci' => $form_state['values']['class_to'])
  );
	foreach($classes as $class){
		$class_to_weight = $class->weight;
	}
	
	$class_input = array();
	$classes = db_query("
    SELECT * from {$class_list} where weight between :cfw and :ctw;", array(':cfw' => $class_from_weight, ':ctw' => $class_to_weight)
  );
	foreach($classes as $class){
		$class_input[] = $class->class_id;
	}
	
	foreach($class_input as $ci){
		variable_set('late_fine_due_date/'.$ci, $values);
	}
}

/**
 *Theme function
 */
function theme_late_fine_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Month'), t('Deadline'), t('Amount'));
  
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
