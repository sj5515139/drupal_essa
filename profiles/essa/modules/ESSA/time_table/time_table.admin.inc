<?php

function timetable($form = array(), &$form_state, $cl, $se){
	
	$class_sec = $cl.'_'.$se;
	$session = variable_get('essa_sid');
	$class_section_table = 'essa_'.$session.'_class_section';
	
	/*
	$class_sections = db_query(
		"SELECT sections from {$class_section_table}"
	);
  foreach($class_sections as $section){
		$sec[ 'time_table_'.$section->sections] = $section->sections;
	}
	$options = array(
		'title' => 'Select a section - ',
	);
	ctools_include('jump-menu');
	$form['jump'] = ctools_jump_menu(array(), $form_state, $sec, $options);
	*/
	$class_tt_table = 'essa_'.$session.'_time_table_'.$class_sec;
	$tt_data = db_query(
		"SELECT * from {$class_tt_table} order by day_weight"
	);
	foreach($tt_data as $data){
		$value[] = $data;
	}
	$form['db_table'] = array(
		'#type' => 'value',
		'#value' => $class_sec,
	);
	$day = array('MONDAY', 'TUESDAY', 'WEDNESDAY', 'THURSDAY', 'FRIDAY', 'SATURDAY');
	for($i = 0; $i < 6; $i++){
		$row[] = array(
      '#tree' =>TRUE,
			
      $i => array(  //Generating unique array id for every form element
				'c1' =>array(
          '#type' => 'markup',
					'#markup' => $day[$i],
        ),
        'c2' =>array(
          '#type' => 'textarea',
          '#resizable' => FALSE,
          '#prefix' => '<div id="div1" ondrop="drop(event)" ondragover="allowDrop(event)">',
          '#suffix' => '</div>',
					'#default_value' => isset($value[$i]->Period1)?$value[$i]->Period1:NULL,
        ),
        'c3' =>array(
          '#type' => 'textarea',
          '#resizable' => FALSE,
          '#prefix' => '<div id="div1" ondrop="drop(event)" ondragover="allowDrop(event)">',
          '#suffix' => '</div>',
					'#default_value' => isset($value[$i]->Period2)?$value[$i]->Period2:NULL,
        ),
				'c4' =>array(
          '#type' => 'textarea',
          '#resizable' => FALSE,
          '#prefix' => '<div id="div1" ondrop="drop(event)" ondragover="allowDrop(event)">',
          '#suffix' => '</div>',
					'#default_value' => isset($value[$i]->Period3)?$value[$i]->Period3:NULL,
				),
				'c5' =>array(
          '#type' => 'textarea',
          '#resizable' => FALSE,
          '#prefix' => '<div id="div1" ondrop="drop(event)" ondragover="allowDrop(event)">',
          '#suffix' => '</div>',
					'#default_value' => isset($value[$i]->Period4)?$value[$i]->Period4:NULL,
				),
				'c6' =>array(
          '#type' => 'textarea',
          '#resizable' => FALSE,
          '#prefix' => '<div id="div1" ondrop="drop(event)" ondragover="allowDrop(event)">',
          '#suffix' => '</div>',
					'#default_value' => isset($value[$i]->Period5)?$value[$i]->Period5:NULL,
				),
				'c7' =>array(
          '#type' => 'textarea',
          '#resizable' => FALSE,
          '#prefix' => '<div id="div1" ondrop="drop(event)" ondragover="allowDrop(event)">',
          '#suffix' => '</div>',
					'#default_value' => isset($value[$i]->Period6)?$value[$i]->Period6:NULL,
				),
				'c8' =>array(
          '#type' => 'textarea',
          '#resizable' => FALSE,
          '#prefix' => '<div id="div1" ondrop="drop(event)" ondragover="allowDrop(event)">',
          '#suffix' => '</div>',
					'#default_value' => isset($value[$i]->Period7)?$value[$i]->Period7:NULL,
				),
        'c9' =>array(
          '#type' => 'textarea',
          '#resizable' => FALSE,
          '#prefix' => '<div id="div1" ondrop="drop(event)" ondragover="allowDrop(event)">',
          '#suffix' => '</div>',
					'#default_value' => isset($value[$i]->Period8)?$value[$i]->Period8:NULL,
				),
      ),
    );
	}
	$form['for'] = array(
    '#type' => 'markup',
    '#markup' => '<h1 style = "text-align: center" id = "tt_title">'.'Time Table for '.'<strong>'.strtoupper($class_sec).'</strong>'.'</h1>',
  );
  
	$form['time_table'] = array(
    '#theme' => 'time_table_theme_table',
    'rows' => $row,
  );
	
	$form['help'] = array(
		'#type' => 'markup',
		'#markup' => '<p>Please Save the Time Table before you take the PDF.</p>'
	);
	
	$form['pdf']  = array(
		'#type' => 'submit',
		'#value' =>t('Download PDF'),
		'#submit' => array('downloadPDF'),
 	);
  
	$form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
	
	return $form;
}

/**
 *Function to generate PDF File for the datesheet.
 */
function downloadPDF($form, $form_state){
	//get_pdf_output($form, $form_state);
	require_once("profiles/essa\modules\Dependencies\ESSA\print\lib\dompdf\dompdf_config.inc.php");
	$session_id = variable_get('essa_sid');
	
	$class_tt_table = 'essa_'.$session_id.'_Time_Table_'.$form_state['values']['db_table'];
	$tt_data = db_query(
		"SELECT * from {$class_tt_table} order by day_weight"
	);
	foreach($tt_data as $data){
		$values[] = $data;
	}
	
	$page_size = 'A4';
	$po = 'landscape';
	
	$output = get_pdf_output($form, $form_state);
	$dompdf = new DOMPDF;
	$dompdf->load_html($output);
	$dompdf->set_paper($page_size, $po);
	$dompdf->render();
	// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
	$dompdf->stream("Time-Table_".$form_state['values']['db_table'].".pdf");
}


/**
 *Implements validate function.
 */
function timetable_validate($form, &$form_state){
	
}
/**
 *Implements submit function.
 */
function timetable_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$db_tt_table = 'essa_'.$session.'_time_table_'.$form_state['values']['db_table'];
	$sub_teacher_table = 'essa_'.$session.'_subject_teacher_table';
	$optional_pair_table = 'essa_'.$session.'_optional_subject_pair';
	
	$class_sec = explode('_', $form_state['values']['db_table']);
	$class = $class_sec[0];
	$sec = $class_sec[1];
	
	foreach($form_state['values'] as $arr){
		if(is_array($arr)){
			foreach($arr as $input_to => $input){
				if($input['c2'] != ''){
					update_class_tt('1', $class, $sec, $input['c2'], $input_to);
					preg_match('#\((.*?)\)#', $input['c2'], $match);
					if(isset($match[1])){
						$sub_id = $match[1];	
						if($sub_id != NULL){
							$tt_data = db_query(
								"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$sub_id)
							);
							foreach($tt_data as $td){
								update_teacher_tt($td->teacher, '1', $class,$sec, $sub_id, $input_to);
							}
						}
					}else{
						$op_data = db_query(
							"SELECT * from {$optional_pair_table} where class = :cl and pair_name = :pn;", array(':cl' => $class, ':pn' =>$input['c2'])
						);
						foreach($op_data as $od){
							for($i = 1; $i <= 5; $i++){
								$subj = 'sub_'.(string)$i;
								$tt_data = db_query(
									"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$od->$subj)
								);
								foreach($tt_data as $td){
									update_teacher_tt($td->teacher, '1', $class,$sec, $od->$subj, $input_to);
								}
							}
						}	
					}
				}
				
				if($input['c3'] != ''){
					update_class_tt('2', $class, $sec, $input['c3'], $input_to);
					preg_match('#\((.*?)\)#', $input['c3'], $match);
					if(isset($match[1])){
						$sub_id = $match[1];	
						if($sub_id != NULL){
							$tt_data = db_query(
								"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$sub_id)
							);
							foreach($tt_data as $td){
								update_teacher_tt($td->teacher, '2', $class,$sec, $sub_id, $input_to);
							}
						}
					}else{
						$op_data = db_query(
							"SELECT * from {$optional_pair_table} where class = :cl and pair_name = :pn;", array(':cl' => $class, ':pn' =>$input['c3'])
						);
						foreach($op_data as $od){
							
							for($i = 1; $i <= 5; $i++){
								$subj = 'sub_'.(string)$i;
								$tt_data = db_query(
									"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$od->$subj)
								);
								foreach($tt_data as $td){
									update_teacher_tt($td->teacher, '2', $class,$sec, $od->$subj, $input_to);
								}
							}
						}	
					}
				}
				
				if($input['c4'] != ''){
					update_class_tt('3', $class, $sec, $input['c4'], $input_to);
					preg_match('#\((.*?)\)#', $input['c4'], $match);
					if(isset($match[1])){
						$sub_id = $match[1];	
						if($sub_id != NULL){
							$tt_data = db_query(
								"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$sub_id)
							);
							foreach($tt_data as $td){
								update_teacher_tt($td->teacher, '3', $class,$sec, $sub_id, $input_to);
							}
						}
					}else{
						$op_data = db_query(
							"SELECT * from {$optional_pair_table} where class = :cl and pair_name = :pn;", array(':cl' => $class, ':pn' =>$input['c4'])
						);
						foreach($op_data as $od){
							
							for($i = 1; $i <= 5; $i++){
								$subj = 'sub_'.(string)$i;
								$tt_data = db_query(
									"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$od->$subj)
								);
								foreach($tt_data as $td){
									update_teacher_tt($td->teacher, '3', $class,$sec, $od->$subj, $input_to);
								}
							}
						}	
					}
				}
				
				if($input['c5'] != ''){
					update_class_tt('4', $class, $sec, $input['c5'], $input_to);
					preg_match('#\((.*?)\)#', $input['c5'], $match);
					if(isset($match[1])){
						$sub_id = $match[1];	
						if($sub_id != NULL){
							$tt_data = db_query(
								"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$sub_id)
							);
							foreach($tt_data as $td){
								update_teacher_tt($td->teacher, '4', $class,$sec, $sub_id, $input_to);
							}
						}
					}else{
						$op_data = db_query(
							"SELECT * from {$optional_pair_table} where class = :cl and pair_name = :pn;", array(':cl' => $class, ':pn' =>$input['c5'])
						);
						foreach($op_data as $od){
							
							for($i = 1; $i <= 5; $i++){
								$subj = 'sub_'.(string)$i;
								$tt_data = db_query(
									"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$od->$subj)
								);
								foreach($tt_data as $td){
									update_teacher_tt($td->teacher, '4', $class,$sec, $od->$subj, $input_to);
								}
							}
						}	
					}
				}
				
				if($input['c6'] != ''){
					update_class_tt('5', $class, $sec, $input['c6'], $input_to);
					preg_match('#\((.*?)\)#', $input['c6'], $match);
					if(isset($match[1])){
						$sub_id = $match[1];	
						if($sub_id != NULL){
							$tt_data = db_query(
								"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$sub_id)
							);
							foreach($tt_data as $td){
								update_teacher_tt($td->teacher, '5', $class,$sec, $sub_id, $input_to);
							}
						}
					}else{
						$op_data = db_query(
							"SELECT * from {$optional_pair_table} where class = :cl and pair_name = :pn;", array(':cl' => $class, ':pn' =>$input['c6'])
						);
						foreach($op_data as $od){
							
							for($i = 1; $i <= 5; $i++){
								$subj = 'sub_'.(string)$i;
								$tt_data = db_query(
									"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$od->$subj)
								);
								foreach($tt_data as $td){
									update_teacher_tt($td->teacher, '5', $class,$sec, $od->$subj, $input_to);
								}
							}
						}	
					}
				}
				
				if($input['c7'] != ''){
					update_class_tt('6', $class, $sec, $input['c7'], $input_to);
					preg_match('#\((.*?)\)#', $input['c7'], $match);
					if(isset($match[1])){
						$sub_id = $match[1];	
						if($sub_id != NULL){
							$tt_data = db_query(
								"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$sub_id)
							);
							foreach($tt_data as $td){
								update_teacher_tt($td->teacher, '6', $class,$sec, $sub_id, $input_to);
							}
						}
					}else{
						$op_data = db_query(
							"SELECT * from {$optional_pair_table} where class = :cl and pair_name = :pn;", array(':cl' => $class, ':pn' =>$input['c7'])
						);
						foreach($op_data as $od){
							
							for($i = 1; $i <= 5; $i++){
								$subj = 'sub_'.(string)$i;
								$tt_data = db_query(
									"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$od->$subj)
								);
								foreach($tt_data as $td){
									update_teacher_tt($td->teacher, '6', $class,$sec, $od->$subj, $input_to);
								}
							}
						}	
					}
				}
				
				if($input['c8'] != ''){
					update_class_tt('7', $class, $sec, $input['c8'], $input_to);
					preg_match('#\((.*?)\)#', $input['c8'], $match);
					if(isset($match[1])){
						$sub_id = $match[1];	
						if($sub_id != NULL){
							$tt_data = db_query(
								"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$sub_id)
							);
							foreach($tt_data as $td){
								update_teacher_tt($td->teacher, '7', $class,$sec, $sub_id, $input_to);
							}
						}
					}else{
						$op_data = db_query(
							"SELECT * from {$optional_pair_table} where class = :cl and pair_name = :pn;", array(':cl' => $class, ':pn' =>$input['c8'])
						);
						foreach($op_data as $od){
							
							for($i = 1; $i <= 5; $i++){
								$subj = 'sub_'.(string)$i;
								$tt_data = db_query(
									"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$od->$subj)
								);
								foreach($tt_data as $td){
									update_teacher_tt($td->teacher, '7', $class,$sec, $od->$subj, $input_to);
								}
							}
						}	
					}
				}
				
				if($input['c9'] != ''){
					update_class_tt('8', $class, $sec, $input['c9'], $input_to);
					preg_match('#\((.*?)\)#', $input['c9'], $match);
					if(isset($match[1])){
						$sub_id = $match[1];	
						if($sub_id != NULL){
							$tt_data = db_query(
								"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$sub_id)
							);
							foreach($tt_data as $td){
								update_teacher_tt($td->teacher, '8', $class,$sec, $sub_id, $input_to);
							}
						}
					}else{
						$op_data = db_query(
							"SELECT * from {$optional_pair_table} where class = :cl and pair_name = :pn;", array(':cl' => $class, ':pn' =>$input['c9'])
						);
						foreach($op_data as $od){
							
							for($i = 1; $i <= 5; $i++){
								$subj = 'sub_'.(string)$i;
								$tt_data = db_query(
									"SELECT * from {$sub_teacher_table} where class = :cl and section = :sec and subject = :sub;", array(':cl' => $class, ':sec' => $sec, ':sub' =>$od->$subj)
								);
								foreach($tt_data as $td){
									update_teacher_tt($td->teacher, '8', $class,$sec, $od->$subj, $input_to);
								}
							}
						}	
					}
				}
			}
		}
	}
	drupal_set_message('Time Table has been successfully updated.', 'status');
}

function update_class_tt($period, $class, $sec, $sub, $in_to){
	$session = variable_get('essa_sid');
	$db_tt_table = 'essa_'.$session.'_time_table_'.$class.'_'.$sec;
	
	db_update($db_tt_table) // Table name no longer needs {}
     ->fields(array(
			'Period'.$period => $sub,
		)
	)
  ->condition('day_weight', $in_to, '=')
  ->execute();
}

function update_teacher_tt($emp_id, $period, $class, $sec, $sub_id, $input_to){
	$session = variable_get('essa_sid');
	$teacher_tt_table = 'essa_'.$session.'_time_table_'.$emp_id;
	
	db_update($teacher_tt_table) // Table name no longer needs {}
		->fields(array(
			'Period'.$period.'_class' => $class.'-'.$sec,
			'Period'.$period.'_subject' => $sub_id,
		)
	)
	->condition('day_weight', $input_to, '=')
	->execute();
}

/**
 *Gets data from time_table db table to be used for PDF generation.
 */
function get_pdf_output($form, &$form_state){
	$session_id = variable_get('essa_sid');
	$subject_teacher_table = 'essa_'.$session_id.'_subject_teacher_table';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	
	$query = db_query("SELECT * FROM {$basic_info_table}");
	foreach($query as $q){
		$school_name = $q->nameofschool;
	}
	
	$teacher1_nn = NULL;
	$teacher2_nn = NULL;
	$teacher3_nn = NULL;
	$teacher4_nn = NULL;
	$teacher5_nn = NULL;
	$teacher6_nn = NULL;
	$teacher7_nn = NULL;
	$teacher8_nn = NULL;
	
	$class_tt_table = 'essa_'.$session_id.'_time_table_'.$form_state['values']['db_table'];
	$tt_data = db_query(
		"SELECT * from {$class_tt_table} order by day_weight"
	);
	foreach($tt_data as $data){
		$values[] = $data;
	}
	
	$class_sec = explode('_', $form_state['values']['db_table']);
	$class = $class_sec[0];
	$sec = $class_sec[1];
	
	$output = '<html>';
	$output .= '<head>';
	$output .= '<style>';
	$output .= 'table, th, td {
		border: 1px solid black;
		border-collapse: collapse;
		padding: 2px;
	}
	th{
		background: 	#708090;
		color: WHITE;
	}
	
	img{
		position:absolute;
		display:block;
		left:0%;
		-webkit-transform: translate(-50%, -50%);
	}';
	$output .= '</style>';
	$output .= '</head>';
	$output .= '<body>';
	
	$output .= '<h1 style = "display: inline-block; float: center; clear: both; text-align: center;	">'.$school_name.'</h1>';
	$output .= '</br></br><h3 style = "text-align: center;"> Time Table ('.$form_state['values']['db_table'].')</h3>';
	
	$output .= '<table border="1" style="width:100%">';
	$output .= '<tr><th>Day</th><th>Period1</th><th>Period2</th><th>Period3</th><th>Period4</th><th>Period5</th><th>Period6</th><th>Period7</th><th>Period8</th>';
	
	$output .= '</tr>';
	
	foreach($values as $value){
		$teacher1_nn = NULL;
		$teacher2_nn = NULL;
		$teacher3_nn = NULL;
		$teacher4_nn = NULL;
		$teacher5_nn = NULL;
		$teacher6_nn = NULL;
		$teacher7_nn = NULL;
		$teacher8_nn = NULL;
		
		$emp1 = NULL;
		$emp2 = NULL;
		$emp3 = NULL;
		$emp4 = NULL;
		$emp5 = NULL;
		$emp6 = NULL;
		$emp7 = NULL;
		$emp8 = NULL;
		
		$sub1 = explode('(',$value->Period1);
		if(isset($sub1[1]) != NULL){
			$sub1 = str_replace(')','', $sub1[1]);
		}
		
		$query  = db_query("SELECT * FROM {$subject_teacher_table} WHERE class =:cls AND section = :sec AND subject = :sub;", array(':cls' => $class, ':sec' => $sec, ':sub' => $sub1));
		foreach($query as $q){
			$emp1 = $q->teacher;
		}
		
		$sub2 = explode('(',$value->Period2);
		if(isset($sub2[1]) != NULL){
			$sub2 = str_replace(')','', $sub2[1]);
		}
		
		$query  = db_query("SELECT * FROM {$subject_teacher_table} WHERE class =:cls AND section = :sec AND subject = :sub;", array(':cls' => $class, ':sec' => $sec, ':sub' => $sub2));
		foreach($query as $q){
			$emp2 = $q->teacher;
		}
		
		$sub3 = explode('(',$value->Period3);
		if(isset($sub3[1]) != NULL){
			$sub3 = str_replace(')','', $sub3[1]);
		}
		
		$query  = db_query("SELECT * FROM {$subject_teacher_table} WHERE class =:cls AND section = :sec AND subject = :sub;", array(':cls' => $class, ':sec' => $sec, ':sub' => $sub3));
		foreach($query as $q){
			$emp3 = $q->teacher;
		}
		
		$sub4 = explode('(',$value->Period4);
		if(isset($sub4[1]) != NULL){
			$sub4 = str_replace(')','', $sub4[1]);
		}
		
		$query  = db_query("SELECT * FROM {$subject_teacher_table} WHERE class =:cls AND section = :sec AND subject = :sub;", array(':cls' => $class, ':sec' => $sec, ':sub' => $sub4));
		foreach($query as $q){
			$emp4 = $q->teacher;
		}
		
		$sub5 = explode('(',$value->Period5);
		if(isset($sub5[1]) != NULL){
			$sub5 = str_replace(')','', $sub5[1]);
		}
		
		$query  = db_query("SELECT * FROM {$subject_teacher_table} WHERE class =:cls AND section = :sec AND subject = :sub;", array(':cls' => $class, ':sec' => $sec, ':sub' => $sub5));
		foreach($query as $q){
			$emp5 = $q->teacher;
		}
		
		$sub6 = explode('(',$value->Period6);
		if(isset($sub6[1]) != NULL){
			$sub6 = str_replace(')','', $sub6[1]);
		}
		
		$query  = db_query("SELECT * FROM {$subject_teacher_table} WHERE class =:cls AND section = :sec AND subject = :sub;", array(':cls' => $class, ':sec' => $sec, ':sub' => $sub6));
		foreach($query as $q){
			$emp6 = $q->teacher;
		}
		
		$sub7 = explode('(',$value->Period7);
		if(isset($sub7[1]) != NULL){
			$sub7 = str_replace(')','', $sub7[1]);
		}
		
		$query  = db_query("SELECT * FROM {$subject_teacher_table} WHERE class =:cls AND section = :sec AND subject = :sub;", array(':cls' => $class, ':sec' => $sec, ':sub' => $sub7));
		foreach($query as $q){
			$emp7 = $q->teacher;
		}
		
		$sub8 = explode('(',$value->Period8);
		if(isset($sub8[1]) != NULL){
			$sub8 = str_replace(')','', $sub8[1]);
		}
		
		$query  = db_query("SELECT * FROM {$subject_teacher_table} WHERE class =:cls AND section = :sec AND subject = :sub;", array(':cls' => $class, ':sec' => $sec, ':sub' => $sub8));
		foreach($query as $q){
			$emp8 = $q->teacher;
		}
		
		
		$output .= '<tr>';
		$output .= '<td style = "text-align: center; background: #C0C0C0; color: WHITE">'.$value->day.'</td>';
		$staff_table = 'essa_'.$session_id.'_master_staff_table';
		
		if(isset($emp1)){
			$staff_data = db_query(
				"SELECT * from {$staff_table} where emp_id = :id", array(':id' => $emp1)
			);
			foreach($staff_data as $sd){
				$teacher1_nn = $sd->nickname;
			}	
		}else{
			$teacher1_nn = NULL;
		}
		$output .= '<td style = "text-align: center"><b>'.$value->Period1.'</b><br>'.$teacher1_nn.'</td>';
		
		if(isset($emp2)){
			$staff_data = db_query(
				"SELECT * from {$staff_table} where emp_id = :id", array(':id' => $emp2)
			);
			foreach($staff_data as $sd){
				$teacher2_nn = $sd->nickname;
			}
		}else{
			$teacher2_nn = NULL;
		}
		$output .= '<td style = "text-align: center"><b>'.$value->Period2.'</b><br>'.$teacher2_nn.'</td>';
		
		if(isset($emp3)){
			$staff_data = db_query(
				"SELECT * from {$staff_table} where emp_id = :id", array(':id' => $emp3)
			);
			foreach($staff_data as $sd){
				$teacher3_nn = $sd->nickname;
			}
		}else{
			$teacher3_nn = NULL;
		}
		$output .= '<td style = "text-align: center"><b>'.$value->Period3.'</b><br>'.$teacher3_nn.'</td>';
		
		if(isset($emp4)){
			$staff_data = db_query(
				"SELECT * from {$staff_table} where emp_id = :id", array(':id' => $emp4)
			);
			foreach($staff_data as $sd){
				$teacher4_nn = $sd->nickname;
			}
		}
		else{
			$teacher4_nn = NULL;
		}
		$output .= '<td style = "text-align: center"><b>'.$value->Period4.'</b><br>'.$teacher4_nn.'</td>';
		
		if(isset($emp5)){
			$staff_data = db_query(
				"SELECT * from {$staff_table} where emp_id = :id", array(':id' => $emp5)
			);
			foreach($staff_data as $sd){
				$teacher5_nn = $sd->nickname;
			}
		}else{
			$teacher5_nn = NULL;
		}
		$output .= '<td style = "text-align: center"><b>'.$value->Period5.'</b><br>'.$teacher5_nn.'</td>';
		
		if(isset($emp6)){
			$staff_data = db_query(
				"SELECT * from {$staff_table} where emp_id = :id", array(':id' => $emp6)
			);
			foreach($staff_data as $sd){
				$teacher6_nn = $sd->nickname;
			}
		}else{
			$teacher6_nn = '';
		}
		$output .= '<td style = "text-align: center"><b>'.$value->Period6.'</b><br>'.$teacher6_nn.'</td>';
		
		if(isset($emp7)){
			$staff_data = db_query(
				"SELECT * from {$staff_table} where emp_id = :id", array(':id' => $emp7)
			);
			foreach($staff_data as $sd){
				$teacher7_nn = $sd->nickname;
			}
		}else{
			$teacher7_nn = '';
		}
		$output .= '<td style = "text-align: center"><b>'.$value->Period7.'</b><br>'.$teacher7_nn.'</td>';
		
		if(isset($emp8)){
			$staff_data = db_query(
				"SELECT * from {$staff_table} where emp_id = :id", array(':id' => $emp8)
			);
			foreach($staff_data as $sd){
				$teacher8_nn = $sd->nickname;
			}
		}else{
			$teacher8_nn = '';
		}
		$output .= '<td style = "text-align: center"><b>'.$value->Period8.'</b><br>'.$teacher8_nn.'</td>';
		
		
		$output .= '</tr>';
	}
	$output .= '</table>';
	$output .= '</body>';
	$output .= '</html>';
	return $output;
}

/**
 * Theme callback for the form table.
*/ 
function theme_time_table_theme_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t(''),t('Period1'), t('Period2'),t('Period3'), t('Period4'), t('Period5'), t('Period6'), t('Period7'), t('Period8'));
  
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
 *Supporting function to clean_string the array id.
 */
function clean_string_tt($string) {
   $string = str_replace(' ', '-', $string); // Replaces all spaces with hyphens.
   return preg_replace('/[^A-Za-z0-9\-]/', '', $string); // Removes special chars.
}