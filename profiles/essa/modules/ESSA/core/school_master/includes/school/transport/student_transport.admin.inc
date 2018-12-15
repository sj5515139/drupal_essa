<?php

/**
 *Implements page callback function - transport_form
 */
function student_transport_form($form, &$form_state, $class, $sec){
  $form = array();
  $session = variable_get('essa_sid');
	$student_master_table = 'essa_'.$session.'_master_student_table';
	$basic_info_table = 'essa_'.$session.'_basicinfo';
	
	$basic_info = db_query("
    SELECT * from {$basic_info_table};"
  );
	foreach($basic_info as $bi){
		$def_wef = $bi -> academicyearstart;
		$def_wet = $bi -> academicyearend;
	}
	
	$studs = db_query("
    SELECT * from {$student_master_table} where class = :class AND section = :sec and status = 1 order by roll_no;", array(':class'=>$class, ':sec'=>$sec)
  );
	foreach($studs as $stud){
		$stop_name[$stud->adm_no][$stud->adm_no] = $stud->stop_name;
		$trnsport_wef[$stud->adm_no][$stud->adm_no] = $stud->transport_wef;
		$trnsport_wet[$stud->adm_no][$stud->adm_no] = $stud->transport_wet;
	}
	
	$form['class'] = array(
    '#type' => 'value',
    '#value' => $class,
  );
  
  $form['sec'] = array(
    '#type' => 'value',
    '#value' => $sec,
  );
  
  $form['back'] = array(
		'#type' => 'markup',
		'#markup' => '<p class = "back_button">'.l(t('Back'), 'admin/students/manage_transport/'.$class).'</p>',
	);
	
	
  
  $students = db_query("
    SELECT * from {$student_master_table} where class = :class AND section = :sec and status = 1 order by roll_no;", array(':class'=>$class, ':sec'=>$sec)
  );
  
  module_load_include('inc', 'hierarchical_select', 'includes/common');
  $config = sm_bs_hs_setting();
	foreach($students as $student){
    $row[$student->adm_no] = array(
      '#tree' =>TRUE,
			
      $student->adm_no => array(  //Generating unique array id for every form element
				'c0' =>array(
          '#type' => 'markup',
					'#markup' => '<h3>'.$student->adm_no.'</h3>',
        ),
				'c1' =>array(
          '#type' => 'markup',
					'#markup' => '<h3>'.$student->roll_no.'</h3>',
        ),
        'c2' =>array(
          '#type' => 'markup',
					'#markup' => '<h3>'.$student->student_name.'</h3>',
        ),
				'c5' =>array(
          '#type' => 'textfield',
					'#disabled' => TRUE,
					'#size' => 15,
          '#default_value' => isset($stop_name[$student->adm_no][$student->adm_no])?$stop_name[$student->adm_no][$student->adm_no]:NULL,
        ),
        'c3' =>array(
          '#type' => 'hierarchical_select',
          '#config' => $config,
        ),
        'c4' => array(
          '#type' => 'date_popup',
          '#attributes' => array('placeholder' => 'dd/mm/yyyy'),
          '#date_format' => 'd-m-Y',
          '#date_year_range' => '-1:+1',
					'#default_value' => isset($trnsport_wef[$student->adm_no][$student->adm_no])?$trnsport_wef[$student->adm_no][$student->adm_no]:$def_wef,
        ),
				'c6' => array(
          '#type' => 'date_popup',
          '#attributes' => array('placeholder' => 'dd/mm/yyyy'),
          '#date_format' => 'd-m-Y',
          '#date_year_range' => '-1:+1',
					'#default_value' => isset($trnsport_wet[$student->adm_no][$student->adm_no])?$trnsport_wet[$student->adm_no][$student->adm_no]:$def_wet,
        ),
				'c7' => array(
          '#type' => 'submit',
          '#value' => t('Remove'),
					'#submit' => array('remove_bus'),
					'#name' => $student->roll_no,
        ),
      ),
    );
  }
	
	if(isset($row)){
		
		$form['note'] = array(
			'#type' => 'markup',
			'#markup' => '<h2>'.'NOTE: To change the "Date of Issue" and "Valid Upto" fields, you need to <span style = "color: RED;">reselect the bus stop.'.'</h2>',
		);
		
		$form['fs']['students'] = array(
			'#theme' => 'student_transport_table',
			'rows' => $row,
		);
		
		$form['fs']['bus_pass'] = array(
			'#type' => 'submit',
			'#value' => 'Generate Bus Pass',
			'#submit' => array('generate_bus_pass'),
		);
		
		$form['fs']['save'] = array(
			'#type' => 'submit',
			'#value' => 'Save',
		);
	}else{
		$form['msg'] = array(
			'#type' => 'markup',
			'#markup' => '<h3 style ="color: RED">There are no students in class '.$class.'-'.$sec.'</h3>',
		);
	}
  
  
  return $form;
}

/**
 *Implements remove function
 */
function remove_bus($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
  $student_table = 'essa_'.$session_id.'_master_student_table';
	db_update($student_table) // Table name no longer needs {}
		->fields(array(
			'is_transport' => 'No',
			'route_id' => NULL,
			'route_name' => NULL,
			'stop_id' => NULL,
			'stop_name' => NULL,
			'transport_wef' => NULL,
			'transport_wet' => NULL,
		))
		->condition('adm_no', $form_state['triggering_element']['#parents'][0], '=')
		->execute();
}

/**
 *Implements submit function
 */
function student_transport_form_submit($form, &$form_state){
  
	$session_id = (string)variable_get('essa_sid');
  $student_table = 'essa_'.$session_id.'_master_student_table';
	$stop_table = 'essa_'.$session_id.'_bus_stops';
	$route_table = 'essa_'.$session_id.'_bus_routes';
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	$transport = 0;
	$flag = 0;
	global $user;
	
	foreach($form_state['values'] as $value){
		if(is_array($value)){
			foreach($value as $key=>$val){
				if($val['c3'][0] != NULL){
					$stops = db_query("
					  SELECT * from {$stop_table} where bus_stop_id = :bsi;", array(':bsi' => $val['c3'][1])
					);
					foreach($stops as $stop){
						$routes = db_query("
						  SELECT * from {$route_table} where route_id = :ri;", array(':ri' => $stop->route_id)
						);
						foreach($routes as $route){
							$route_name = $route->route_name;
						}
						db_update($student_table) // Table name no longer needs {}
						->fields(array(
								'is_transport' => 'Yes',
								'route_id' => $stop->route_id,
								'route_name' => $route_name,
								'stop_id' => $stop->bus_stop_id,
								'stop_name' => $stop->stop_name,
								'transport_wef' => $val['c4'],
								'transport_wet' => $val['c6'],
							))
						->condition('adm_no', $key, '=')
						->execute();
						$flag = 1;
						//dsm($flag);
						//dsm($transport);
						//*******Suraj********//
						if($flag == 1 && $transport == 0){
							//sending system alert
							$created_date = date("Y-m-d H:i:s");
							$strtodate = strtotime($created_date);
							db_insert($sys_alert_table)
							->fields(array(
								'message' => $key.' has been registered for bus stop '.$stop->stop_name.' with reference to '.$val['c4'].' & valid upto '.$val['c6'].'.',
								'priority' => 'L',
								'module' => 'students',
								'source_url' => 'admin/students/manage_transport/'.$form_state['values']['class'].'/'.$form_state['values']['class'],
								'timestamp' => $strtodate,
								'source_uid' => $user->uid,
							))
							->execute();
							//*******Suraj********//
						}
						
						
					}
				}
			}
		}
	}
	drupal_set_message('Bus has been alloted to students.','status');
}

function generate_bus_pass($form, &$form_state){
	require_once("profiles/essa/modules/dependencies/essa/print/lib/dompdf/dompdf_config.inc.php");
	
	$output = get_bus_pass($form, $form_state);
	$dompdf = new DOMPDF;
	$dompdf->load_html($output);
	$dompdf->render();
	// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
	$dompdf->stream("bus_pass".$form_state['values']['class'].".pdf");
}

/**
 *Implements the function that returns the output for the bus pass
 */
function get_bus_pass($form, $form_state){
	$output = '<html>';
	$output .= '<head>';
	$output .= '<style>';
	$output .= '
		table{
			border: 0px solid black;
		}
		th{
			background: 	#708090;
			color: WHITE;
		}
		td{
			padding: 7px;
		}
		
		@page { margin:0.1in 0.1in 0.1in 0.1in; }
	';
	$output .= '</style>';
	$output .= '</head>';
	$output .= '<body>';
	
	$output .= '<table style="width:100%">';
	
	$session_id = variable_get('essa_sid');
	$student_master_table = 'essa_'.$session_id.'_master_student_table';
	$route_table = 'essa_'.$session_id.'_bus_routes';
	$studs = db_query("
    SELECT * from {$student_master_table} where class = :class AND section = :sec AND status = 1;", array(':class'=>$form_state['values']['class'], ':sec'=>$form_state['values']['sec'])
  );
	
	$count = 0;
	foreach($studs as $stud){
		if($stud->stop_id != 0){
			if($count == 0){
				$output .= '<tr style = "page-break-before: always;">';
				$count = 0;
			}
			$output .= '<td>';
			$output .= '<div id = "header" style = "position: relative; margin-bottom:0px !important; margin-left: 10px;"><img src='.variable_get('file_public_path', conf_path() . '/files').'/logo.png'.' alt = "header" width="114" height="120" style = "position:absolute; left:0%;">';
			$output .= '<h3 style = "text-align: center; margin-top:0px;">'.'ST. JOSEPH\'S SCHOOL, BGP<br>'.'<span style = "background: BLACK; color: white;padding: 2px 10px 2px 10px;">BUS PASS</span>'.'</h3></div>';
			//$output .= '<h4 style = "background: BLACK; color: white; text-align: center; margin-top:-7px; margin-bottom:-10px;">'.'BUS PASS'.'</h4>';
			$routes = db_query("
			  SELECT * from {$route_table} where route_id = :ri;", array(':ri'=> $stud->route_id)
			);
			foreach($routes as $route){
				$bus_no = $route->bus_no;
			}
			$output .= '<div style = "line-height:100%; padding-left: 8px;">';
			$output .= '<table style="width:100%">';
			$output .= '<tr>';
			$output .= '<td style = "">Bus No. - <span style = "border-bottom: 1px dotted black;">'.$bus_no.'</td>';
			$output .= '<td style = " ; text-align: right; background:#C0C0C0;" colspan = 2>Trip - '.strtoupper($stud->route_name).'</td>';
			$output .= '</tr>';
			$output .= '<tr>';
			$output .= '<td colspan = 3>Name. - <strong>'.strtoupper($stud->first_name).' '.strtoupper($stud->middle_name).' '.strtoupper($stud->last_name).'</strong></td>';
			$output .= '</tr>';
			$output .= '<tr>';
			$output .= '<td style = " ;">Adm. No. - '.strtoupper($stud->adm_no).'</td>';
			$output .= '<td style = " ;">Class - '.strtoupper($stud->class).' - '.strtoupper($stud->section).'</td>';
			$output .= '<td style = " ;">Roll No. - '.strtoupper($stud->roll_no).'</td>';
			$output .= '</tr>';
			$output .= '<tr>';
			$output .= '<td colspan = 3>Bus Stop - '.strtoupper($stud->stop_name).'</td>';
			$output .= '</tr>';
			$output .= '<tr>';
			$output .= '<td colspan = 3>Date of Issue-'.strtoupper($stud->transport_wef).'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Valid Upto-'.strtoupper($stud->transport_wet).'</td>';
			$output .= '</tr>';
			$output .= '</table>';
			$output .= '<p style = "font-size: 16px;"><i> Bus pass is necessary for the daily boarding of school bus. </i></p>';
			$output .= '<p style = "font-size: 16px;"><i> It will be checked at any time by the school authority. </i></p>';
			$output .= '<p style = "text-align: right;"><b> PRINCIPAL </b></p>';
			$output .= '</div>';
			$output .= '</td>';
			
			$count++;
			if($count == 2){
				$output .= '</tr>';
				$count = 0;
			}
		}
	}
	
	
	$output .= '</table>';
	
	$output .= '</body>';
	$output .= '</html>';
	return $output;
}

/**
 * Theme callback for the form table.
 */
function theme_student_transport_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Admission No'),t('Roll No'),t('Name'), t('Bus Stop'),t('Select a Bus Stop'),t('Date of Issue'),t('Valid Upto'),t(''));
  
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
function sm_bs_hs_setting(){
  // Load category based in vocabulary machine name
	$voc = 'transport_vocab';//replace this with the taxonomy term
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