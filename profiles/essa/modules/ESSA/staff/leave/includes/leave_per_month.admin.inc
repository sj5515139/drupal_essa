<?php
/**
 *Implements page callback function each_leave_form.
 */
function leave_per_month($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	$leave_half_day = 'essa_'.$session_id.'_leave_half_day';
	$row = array();
	$bi_table = 'essa_'.$session_id.'_basicinfo';
  $bi_db = db_query(
		"SELECT * from {$bi_table}"
	);
  foreach($bi_db as $bi){
    $strDateFrom = $bi->academicyearstart;
    $strDateTo = $bi->academicyearend;
  }
  $start    = new DateTime($strDateFrom);
	$start->modify('first day of this month');
	$end      = new DateTime($strDateTo);
	$end->modify('first day of next month');
	$interval = DateInterval::createFromDateString('1 month');
	$period   = new DatePeriod($start, $interval, $end);
	$aryRange=array();
	foreach ($period as $dt) {
		array_push($aryRange,$dt->format("Y_m"));
	}
	$options = array('--Select--');
	foreach($aryRange as $dates){
		$options[] = $dates;
	}
	$form['cntt'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "get_emp">',
		'#suffix' => '</div>',
	);
	
	$form['cntt']['month'] = array(
		'#type' => 'select',
		'#title' => 'Select a month',
		'#options' => drupal_map_assoc($options),
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'get_emp_ajax',
      'wrapper' => 'get_emp',
      'method' => 'replace',
      'effect' => 'fade',
    ),
	);
	
	$form['ltd'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "leave_detail">',
		'#suffix' => '</div>',
	);
	
	if(isset($form_state['values']['month']) && $form_state['values']['month'] != '--Select--'){
		
		$month = $form_state['values']['month'];
		$form['cntt']['emp_id'] = array(
			'#type' => 'textfield',
			'#title' => 'Enter Employee Id',
			'#ajax' => array(
				'event' => 'blur',
				'callback' => 'get_emp_leave_ajax',
				'wrapper' => 'leave_detail',
				'method' => 'replace',
				'effect' => 'fade',
			),
			'#autocomplete_path' => 'leave_staff/autocomplete',
		);
		$form['cntt']['save'] = array(
			'#type' => 'submit',
			'#value' => 'Download Sheet',
			'#submit' => array('download_sheet'),
		);
		if(isset($form_state['values']['emp_id']) && $form_state['values']['emp_id'] != NULL){
			$use = user_load_by_name($form_state['values']['emp_id']);
			if($use != NULL){
				$employees[] = $form_state['values']['emp_id'];
				foreach($employees as $emp_id){
					$emp_row[] = array(
						'#tree' =>TRUE,
						$emp_id => array(  //Generating unique array id for every form element 
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $emp_id.'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3></h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3></h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3></h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3></h3>',
							),
						),
					);
					
					$staff_leaves = db_query("SELECT * FROM {$leave_staff_table} WHERE emp_id = :emp AND leave_status IS NULL ORDER BY leave_id", array(':emp' => $emp_id));
					foreach($staff_leaves as $sl){
						$half_days = NULL;
						$leave_remaining = NULL;
						$query = db_query("SELECT * FROM {$leave_half_day} WHERE emp_id =:eid AND leave_id =:lid;", array(':eid' => $emp_id, ':lid' => $sl->leave_id));
						foreach($query as $q){
							$half_days = $q->$month;
						}
						
						if(strpos($sl->leave_remaining, '.')){
							$value = explode('.', $sl->leave_remaining);
							$data = $value[1];
							if($data == '5' || $data == '33'){
								$leave_remaining = $value[0].' and 1 Half day';
							}elseif($data == '67'){
								$leave_remaining = $value[0].' and 2 Half days';
							}
						}else{
							$leave_remaining = $sl->$month;
						}
						
						$leave_row[] = array(
							'#tree' =>TRUE,
							$sl->leave_id => array(  //Generating unique array id for every form element 
								'c0' =>array(
									'#type' => 'markup',
									'#markup' => '<h3></h3>',
								),
								'c1' =>array(
									'#type' => 'markup',
									'#markup' => '<h3>'. $sl->leave_id.'</h3>',
								),
								'c2' =>array(
									'#type' => 'markup',
									'#markup' => '<h3>'. $sl->$month.'</h3>',
								),
								'c3' =>array(
									'#type' => 'markup',
									'#markup' => '<h3>'. $half_days.'</h3>',
								),
								'c4' =>array(
									'#type' => 'markup',
									'#markup' => '<h3>'.$leave_remaining.'</h3>',
								),
							),
						);
					}
					$row = array_merge($emp_row, $leave_row);
					
					$form['ltd'][$emp_id] = array(
						'#theme' => 'leave_per_month_table',
						'rows' => $row,
					);
					$emp_row = $leave_row= NULL;
				}
			}else{
				drupal_set_message('Please Enter a Valid Employee ID.', 'warning');
			}
		}else{
			$staff_leaves = db_query("SELECT * FROM {$leave_staff_table}");
			foreach($staff_leaves as $sl){
				$employees[] = $sl->emp_id;
				$employees = array_unique($employees);
			}
			
			foreach($employees as $emp_id){				
				$emp_row[] = array(
					'#tree' =>TRUE,
					$emp_id => array(  //Generating unique array id for every form element 
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $emp_id.'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3></h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3></h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3></h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3></h3>',
						),
					),
				);
				
				
				$staff_leaves = db_query("SELECT * FROM {$leave_staff_table} WHERE emp_id = :emp AND leave_status IS NULL ORDER BY leave_id", array(':emp' => $emp_id));
				foreach($staff_leaves as $sl){
					$half_days = NULL;
					$query = db_query("SELECT * FROM {$leave_half_day} WHERE emp_id =:eid AND leave_id =:lid;", array(':eid' => $emp_id, ':lid' => $sl->leave_id));
					foreach($query as $q){
						$half_days = $q->$month;
					}
					
					if(strpos($sl->leave_remaining, '.')){
						$value = explode('.', $sl->leave_remaining);
						$data = $value[1];
						if($data == '5' || $data == '33'){
							$leave_remaining = $value[0].' and 1 Half day';
						}elseif($data == '67'){
							$leave_remaining = $value[0].' and 2 Half days';
						}
					}else{
						$leave_remaining = $sl->$month;
					}
					
					$leave_row[] = array(
						'#tree' =>TRUE,
						$sl->leave_id => array(  //Generating unique array id for every form element 
							'c0' =>array(
								'#type' => 'markup',
								'#markup' => '<h3></h3>',
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $sl->leave_id.'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $sl->$month.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $half_days.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$leave_remaining.'</h3>',
							),
						),
					);
				}
				$row = array_merge($emp_row, $leave_row);
				if(isset($row)){
					$form['ltd'][$emp_id] = array(
						'#theme' => 'leave_per_month_table',
						'rows' => $row,
					);
				}
				$emp_row = $leave_row= NULL;
			}
		}
	}
  return $form;
}

/*
** Implements ajax function leave_types_ajax()
*/
function download_sheet($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	$leave_half_day = 'essa_'.$session_id.'_leave_half_day';
	
	$month = $form_state['values']['month'];
	$month_name = str_replace('_', '-',$month);
	$month_name = strtotime($month_name);
	$month_name = date('M-Y', $month_name);
	
	$staff_leaves = db_query("SELECT * FROM {$leave_staff_table}");
	foreach($staff_leaves as $sl){
		$employees[] = $sl->emp_id;
		$employees = array_unique($employees);
	}
	
	
	$output = '<html>';
	$output .= '<head>';
	$output .= '<style>';
	$output .= '
		table{
			border: 3px solid black;
			width: 11.5in;
		}
		th{
			background: #708090;
			color: WHITE;
			border: 1px solid black;
		}
		td{
			padding: 7px;
			border: 1px solid black;
		}
		#cer_footer{
			position: absolute;
			bottom:0.5cm;
		}
		
		@page { margin:0.1in 0.1in 0.1in 0.1in; }
	';
	$output .= '</style>';
	$output .= '</head>';
	$output .= '<body>';
	$output .= '<h3 style ="text-align:center;">Leave Details For the Month of '.$month_name.'</h3>';
	$output .= '<h3><b>Note:- </b> Blank fields indicates that the leave is disabled for the particular employee. HD - Half Day.</h3>';
	$output .= '<table style = " text-align:center;">';
	$output .= '<tr>';
	$output .= '<th rowspan ="2">Emp ID</th>';
	$output .= '<th rowspan ="2">Emp Name</th>';
	$leaves = db_query("SELECT * FROM {$leave_table}");
	foreach($leaves as $lv){
		$output .= '<th>'.$lv->leave_id.'</th>';
	}
	$output .= '</tr>';
	$output .= '<tr>';
	// $output .= '<th></th>';
	// $output .= '<th></th>';
	$leaves = db_query("SELECT * FROM {$leave_table}");
	foreach($leaves as $lv){
		$output .= '<th>
		<table style="width: 100%; text-align:center; border:none;">
		<tr>';
		$output .= '<td style="width: 50%;">Leave Taken</td>';
		if($lv->leave_id == 'CL'){
			$output .= '<td style="width: 50%;">HD</td>';
		}
		
		$output .= '<td style="width: 50%;">Leave Remaining</td>
		</tr></table></th>';
	}
	$output .= '</tr>';
	
	foreach($employees as $emp_id){
		$emp_names = db_query("SELECT * FROM {$staff_table} WHERE emp_id = :emp;", array(':emp' => $emp_id));
		foreach($emp_names as $en){
			$e_name= $en->fname.' '.$en->lname;
		}
		$output .= '<tr>';
		$output .= '<td>'.$emp_id.'</td>';
		$output .= '<td>'.$e_name.'</td>';
		
		$leaves = db_query("SELECT * FROM {$leave_staff_table} WHERE emp_id = :emp ORDER BY leave_id", array(':emp' => $emp_id));
		foreach($leaves as $lv){
			$half_days = NULL;
			$query = db_query("SELECT * FROM {$leave_half_day} WHERE emp_id =:eid AND leave_id =:lid;", array(':eid' => $emp_id, ':lid' => $lv->leave_id));
			foreach($query as $q){
				$half_days = $q->$month;
			}
			$output .= '<td>
			<table style="width: 100%; border: none; text-align:center;">
			<tr>';
			if($lv->leave_status == NULL){
				if($lv->$month != NULL){
					if(strpos($lv->$month, '.')){
						$value = explode('.', $from_count);
						$data = $value[1];
						
						if($value[0] == 0){
							if($data = '5'){
								$output .= '<td style="width: 50%;">1/2 HD</td>';
							}elseif($data = '33'){
								$output .= '<td style="width: 50%;">1/3 HD</td>';
							}elseif($data = '67'){
								$output .= '<td style="width: 50%;">2/3 HD</td>';
							}
						}else{
							if($data = '5'){
								$output .= '<td style="width: 50%;">'.$value[0].' & 1/2 HD</td>';
							}elseif($data = '33'){
								$output .= '<td style="width: 50%;">'.$value[0].' & 1/3 HD</td>';
							}elseif($data = '67'){
								$output .= '<td style="width: 50%;">'.$value[0].' & 2/3 HD</td>';
							}
						}
					}else{					
						$output .= '<td style="width: 50%;">'.$lv->$month.'</td>';
					}
				}else{
					$output .= '<td style="width: 50%;">-</td>';
				}
				
				if($lv->leave_id == 'CL'){
					if($lv->$month != NULL){
						$output .= '<td style="width: 50%;">'.$half_days.'</td>';
					}else{
						$output .= '<td style="width: 50%;">-</td>';
					}
				}
				
				if($lv->leave_remaining != NULL){
					if(strpos($lv->leave_remaining, '.')){
						$value = explode('.', $lv->leave_remaining);
						$data = $value[1];
						
						if($data = '5'){
							$output .= '<td style="width: 50%;">'.$value[0].' & 1/2 HD</td>';
						}elseif($data = '33'){
							$output .= '<td style="width: 50%;">'.$value[0].' & 1/3 HD</td>';
						}elseif($data = '67'){
							$output .= '<td style="width: 50%;">'.$value[0].' & 2/3 HD</td>';
						}
						
					}else{
						$output .= '<td style="width: 50%;">'.$lv->leave_remaining.'</td>';
					}
				}else{
					$output .= '<td style="width: 50%;">-</td>';
				}
			}
			$output .= '</tr>
			</table>
			</td>';
			
		}
		
		$output .= '</tr>';
	}
	$output .= '</table>';
	$output .= '</body>';
	
	$path_print = db_query("
		SELECT * from field_data_field_path;"
	);
	foreach($path_print as $path){
		$path_to_print_module = $path->field_path_value;
	}
	require_once($path_to_print_module);
	
	$page_size = 'A4';
	if($form_state['values']['page_format'] == 'Portrait'){
		$po = 'portrait';
	}else{
		$po = 'landscape';
	}
	
	
	$content = $output;
	$dompdf = new DOMPDF;
	$dompdf->load_html($output);
	$dompdf->set_paper($page_size, $po);
	$dompdf->render();
	// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
	$dompdf->stream('Leave Details('.$month_name.')'.".pdf");
}

/*
** Implements ajax function leave_types_ajax()
*/
function get_emp_ajax($form, &$form_state){
	return array($form['cntt'],$form['ltd']);
}

/*
** Implements ajax function leave_types_ajax()
*/
function get_emp_leave_ajax($form, &$form_state){
	return $form['ltd'];
}

/*
**Theme callback for the form table.
*/ 
function theme_leave_per_month_table(&$variables) {
	// Get the useful values.
	$form = $variables['form'];
	$rows = $form['rows'];
  $header = array(t('Employee ID'), t('Leave ID'), t('Leave Taken'), t('Half Day'), t('Leave Remaining'));
	
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