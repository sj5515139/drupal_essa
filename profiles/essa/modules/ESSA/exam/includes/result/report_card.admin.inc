<?php

function report_card($form, &$form_state, $term_id, $exam_code){
	$session_id = (string)variable_get('essa_sid');
	$class_table = 'essa_'.$session_id.'_class_list';
	$terms_table = 'essa_'.$session_id.'_exam_terms';
	$timing_table = 'essa_'.$session_id.'_exam_timing';
	$class_list_table = 'essa_'.$session_id.'_class_list';
	$master_exam_table = 'essa_'.$session_id.'_exam_master';
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$op_subj_student_table = 'essa_'.$session_id.'_optional_subject_student';
	$master_staff_table = 'essa_'.$session_id.'_master_staff_table';
	$class_teacher_table = 'essa_'.$session_id.'_class_teacher';
	$full_marks_table = 'essa_'.$session_id.'_exam_full_marks';
	$exam_status_table = 'essa_'.$session_id.'_exam_status';
	$terms_table = 'essa_'.$session_id.'_exam_terms';
	$di_group_name_table = 'essa_'.$session_id.'_di_group_name';
	$di_group_section_table = 'essa_'.$session_id.'_di_group_section';
	$di_sa_table = 'essa_'.$session_id.'_di_sa';
	$di_indicators_table = 'essa_'.$session_id.'_di_indicators';
	$sub_names = array();
	global $user;
	
	$adm_no = 'NUR-A-1';
	$content = '';
	$student_details = db_query("SELECT * FROM {$master_student_table} WHERE adm_no = :an;", array(':an' => $adm_no));
	foreach($student_details as $sd){
		$student_name = $sd->student_name;
		$father_name = $sd->father_name;
		$mother_name = $sd->mother_name;
		$class = $sd->class;
		$section = $sd->section;
		$roll = $sd->roll_no;
		$dob = $sd->dob;
		$address = NULL;
		if($sd->r_line1 != NULL){
			$address = $sd->r_line1;
		}
		if($sd->r_line2 != NULL){
			$address = $sd->r_line1.', '.$sd->r_line2;
		}
		if($sd->r_city != NULL){
			$address = $sd->r_line1.', '.$sd->r_line2.', '.$sd->r_city;
		}
		if($sd->r_state != NULL){
			$address = $sd->r_line1.', '.$sd->r_line2.', '.$sd->r_city.', '.$sd->r_state;
		}
		if($sd->r_pincode != NULL){
			$address = $sd->r_line1.', '.$sd->r_line2.', '.$sd->r_city.', '.$sd->r_state.', '.$sd->r_pincode;
		}
		$phone = $sd->r_phone;
		$email = $sd->s_email;
		$house = $sd->house;
	}
	$bi_table = 'essa_'.$session_id.'_basicinfo';
	$bi_db = db_query(
		"SELECT * from {$bi_table}"
	);
	foreach($bi_db as $bi){
		$start_date = $bi->academicyearstart;
		$end_date = $bi->academicyearend;
	}
	//dsm($start_date);	
	// $start_date = "01-Apr";
	// $start_time = strtotime($start_date);
	// //$end_time = strtotime("+1 month", $start_time);
	// $end_time = strtotime(date('d-m-Y'));
  // for($i=$start_time; $i<$end_time; $i+=86400){
    // if(date('D', $i) != 'Sun'){
      // $list[] = date('Y_m_d', $i);
    // }
  // }
  // $session = variable_get('essa_sid');
	
  // $no_of_working_days = 0;
	// $query = db_select($attendance_table, 'n');
	// $query->fields('n', array('adm_no'));
	// $results = $query->execute()->fetchAll();
	// $count = count($results);
	// foreach($list as $col){
    // $student_att = db_query(
		  // "SELECT adm_no, $col from {$attendance_table} WHERE adm_no = :an;", array(':an' => $adm_no)
		// );
    // foreach($student_att as $sa){
			// if($sa->$col != NULL && $sa->$col != 'h'){
				// $no_of_working_days = $no_of_working_days + 1;
				// $dates[$col] = $col;
				// $att[$sa->adm_no][$col] = $sa->$col;
			// }
		// }
	// }
	// foreach($att as $adm_no => $st){
		// $no_of_days_present[$adm_no] = 0;
		// foreach($dates as $dt){
			// if($st[$dt] == 'P'){
				// $no_of_days_present[$adm_no] = $no_of_days_present[$adm_no] + 1; 
			// }
		// }
	// }
	if(variable_get('publish_term_result_'.$term_id) == TRUE){
		$exam_status_table = 'essa_'.$session_id.'_exam_status';
		$publish_dates = db_query("SELECT * FROM {$exam_status_table} WHERE term_id =:tid and exam_code = :ec;", array(':tid' => $term_id, ':ec' => $exam_code));
		foreach($publish_dates as $pd){
			$publish_date = $pd->publish_on;
			$publish_date = date('d-m-Y', $publish_date);
		}
		//dsm($publish_date);
		$attendance_table = 'essa_'.$session_id.'_'.$class.'_'.$section.'_attendance';
		$from_date = '01-05-2016';
		$to_date = $publish_date;
		$format = 'Y-m-d';
		$date = getDatesFromRange($from_date,$to_date, $format);
		foreach($date as $d){
			$d = strtotime($d);
			if(date('D',$d) != 'Sun'){
				$dates[]  = date('Y_m_d', $d);
			}
		}
		
		//dsm($date);
		$total_days = db_query("SELECT * FROM {$attendance_table}");
		foreach($total_days as $td){
			foreach($dates as $d){
				if($td->$d != NULL){
					$total_working_days[] = $td->$d;
				}
			}
		}
		
		$total_days = db_query("SELECT * FROM {$attendance_table} WHERE adm_no = :an;", array(':an' => $adm_no));
		foreach($total_days as $td){
			foreach($dates as $d){
				if($td->$d == 'P'){
					$total_present_days[] = $td->$d;
				}
			}
		}
		$working_days = 0;
		foreach($total_working_days as $twd){
			$working_days = $working_days + count($twd);
		}
		
		$present_days = array_count_values($total_present_days);
		//dsm($present_days['P']);
		
	}
	//dsm($no_of_working_days);
	//dsm($no_of_days_present);
	
	$content = '<html>';
	$content .= '<head><style>
	table{
		
	}
	
	.fee-due-table{
		border: 0px solid black;
		width:100%;
	}
	.underlined{
		text-decoration: underline;
		text-decoration-style: dotted;
		text-decoration-color: red;
	}
	th{
		background: 	#708090;
		color: WHITE;
		text-align: center;	
	}
		
	.fee-due-table td{
		padding: 7px;
		text-align: center;
	}
		
	#cer_footer{
		position: absolute;
		bottom:0.5cm;
		page-break-after: always;
		text-align: center;	
	}
	
	body {
	 background-repeat: no-repeat;
	 background-attachment: fixed;
	 background-position: center; 
	}
	</style></head>';
	

	// **********************************Student Details**********************************************************************
	// $content .= '<div>';
	// $content .= '<table style = "width:100%; float:left;">';
	// $content .= '<tr>';
	// $content .= '<td style= "font-size: 60px;">Name of the Student - </td>';
	// $content .= '<td><h3 style="border-bottom: 1px dotted black;">'.$student_name.'</h3></td>';
	// $content .= '</tr>';
	// $content .= '<tr>';
	// $content .= '<td style= "font-size: 60px;">Class - <b style="border-bottom: 1px dotted black;">'.$class.'</b></td>';	
	// $content .= '<td style= "font-size: 60px;">Section - <b style="border-bottom: 1px dotted black;">'.$section.'</b></td>';	
	// $content .= '<td style= "font-size: 60px;">Roll - <b style="border-bottom: 1px dotted black;">'.$roll.'</b></td>';
	// $content .= '</tr>';
	// $content .= '<tr>';
	// $content .= '<td style= "font-size: 60px;" colspan = "3">Roll - <b style="border-bottom: 1px dotted black;">'.$house.'</b></td>';
	// $content .= '</tr>';
	// $content .= '<tr>';
	// $content .= '<td style= "font-size: 60px;" colspan = "3">Admission No. - <b style="border-bottom: 1px dotted black;">'.$adm_no.'</b></td>';
	// $content .= '</tr>';
	// $content .= '<tr>';
	// $content .= '<td style= "font-size: 60px;" colspan = "3">Date Of Birth No. - <b style="border-bottom: 1px dotted black;">'.$dob.'</b></td>';	
	// $content .= '</tr>';
	// $content .= '<tr>';
	// $content .= '<td style= "font-size: 60px;" colspan = "3">'."Mother's".' Name - <b style="border-bottom: 1px dotted black;">'.$mother_name.'</b></td>';
	// $content .= '</tr>';
	// $content .= '<tr>';
	// $content .= '<td style= "font-size: 60px;" colspan = "3">'."Father's".' Name - <b style="border-bottom: 1px dotted black;">'.$father_name.'</b></td>';	
	// $content .= '</tr>';
	// $content .= '<tr>';
	// $content .= '<td style= "font-size: 60px;" colspan = "3">Residential Address - <b style="border-bottom: 1px dotted black;">'.$address.'</b></td>';	
	// $content .= '</tr>';
	// $content .= '<tr>';
	// $content .= '<td style= "font-size: 60px;" colspan = "3">Mobile No. - <b style="border-bottom: 1px dotted black;">'.$phone.'</b></td>';
	// $content .= '</tr>';
	// $content .= '<tr>';
	// $content .= '<td style= "font-size: 60px;" colspan = "3">Email Id - <b style="border-bottom: 1px dotted black;">'.$email.'</b></td>';
	// $content .= '</tr>';
	// $content .= '</table></br></br></br></br></br></br></br></br></br></br></br>';
	// $content .= '</div>';
	// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// *********************************************Student Attendance*****************************************************************
	$content .= '<div>';
	$content .= '<table style = "width:100%;">';
	$content .= '<tr>';
	$content .= '<th style ="text-align:left;">Attendance</th>';
	
	$t1 = NULL;
	$t2 = NULL;
	$term_names = db_query("SELECT * FROM $terms_table} WHERE id =:id;",array(':id' => $term_id));
	foreach($term_names as $tn){
		$term_name = $tn->term_name;
	}
	
	$content .= '<th style ="text-align:left;">'.$term_name.'</th>';
	
	$content .= '<th style ="text-align:left;">Total</th>';
	$content .= '</tr>';
	
	$content .= '<tr>';
	$content .= '<td>Total attendance of the student</td>';
	$content .= '<td>'.$present_days['P'].'</td>';
	$content .= '</tr>';
	
	$content .= '<tr>';
	$content .= '<td>Total working days</td>';
	$content .= '<td>'.$working_days.'</td>';
	$content .= '</tr>';
	
	$content .= '</table>';
	$content .= '</div>';
	// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	// $di_groups = db_query("SELECT * FROM {$di_group_name_table}");
	// foreach($di_groups as $dig){
		// $c_from = $dig->class_from;
		// $c_to = $dig->class_to;
		
		// if($c_from == NULL){
			// $cf_weight = 0;
		// }else{
			// $c_from_weight = db_query("SELECT * FROM {$class_list_table} WHERE class_id =:c;", array(':c' => $c_from));
			// foreach($c_from_weight as $cfw){
				// $cf_weight = $cfw->weight;
			// }
		// }
		
		// if($c_to == NULL){
			// $ct_weight = 16;
		// }else{
			// $c_to_weight = db_query("SELECT * FROM {$class_list_table} WHERE class_id =:c;", array(':c' => $c_to));
			// foreach($c_to_weight as $ctw){
				// $ct_weight = $ctw->weight;
			// }
		// }
		// $class_list = db_query("SELECT * FROM {$class_list_table} WHERE weight BETWEEN $cf_weight AND $ct_weight ORDER BY weight");
		// foreach($class_list as $c){
			// $classes[] = $c->class_id;
		// }
		
		// if(in_array($class, $classes)){
			// $di_group_name = $dig->group_name;
			// $di_group_id = $dig->id;
		// }
	// }
	// $sections = array();
	// $di_group_sections = db_query("SELECT * FROM {$di_group_section_table} WHERE group_id = :gi;", array(':gi' => $di_group_id));
	// $terms = db_query("SELECT * FROM {$terms_table}");
	// foreach($terms as $term){
		// $exams = db_query("SELECT * FROM {$master_exam_table} WHERE term = :t AND di_status = :ds;", array(':t' => $term->id, ':ds' => '1'));
		// foreach($exams as $exam){
			// foreach($di_group_sections as $digs){
				// $section_id = $digs->id;
				// $content .= '<table style = "width:100%;"><tr><td style = "width:15%; padding-left:20px;"><h2 style ="border: 1px solid green; background-color:green; border-radius:10px; color:White;">'.$digs->section_id.'</h2></td><td style = "padding-left:20px; width:85%;"><h2 style ="color:red;">:'.$digs->section_name.'</h2></td></tr></table>';
				// //$content .= '<div style = "display:flex;"><h2 style =" border: 1px solid green; background-color:green; border-radius:10px; color:White;">&nbsp;&nbsp&nbsp;'.$digs->section_id.'&nbsp;&nbsp;</h2>&nbsp;&nbsp;<h2 style ="color:red;">:&nbsp;&nbsp;'.$digs->section_name.'</h2></div>';
				// if($digs->is_marksheet == 1){
					
				// }
				
				// $di_sub_sections = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si;", array(':gi' => $di_group_id, ':si' => $section_id));
				// $sub_section = NULL;
				// foreach($di_sub_sections as $diss){
					// if($sub_section != $diss->sub_section_title){
						// $content .= '<table style = "width:100%;"><tr	><td style = "width:12%;"><h2 style ="color:red;">'.$diss->sub_section.'</h2></td><td style = "width:88%; padding-left:30px;"><h2 style ="color:blue;">:'.$diss->sub_section_title.'</h2></td></tr></table>';
						// //$content .= '<div style = "display:flex;"><h2 style ="color:red;">'.$diss->sub_section.'</h2>&nbsp;&nbsp;&nbsp;<h2 style ="color:blue;">:&nbsp;&nbsp;'.$diss->sub_section_title.'</h2></div>';
						// $content .= '<table style ="width:100%; border:1px solid red; background-color:#F5DF6D;">';
						// $content .= '<tr>';
						// $content .= '<th style ="color:yellow; background-color:green; width:15%">S.No.</th>';
						// $content .= '<th style ="color:White; background-color:maroon; width:65%">Descriptive Indicators</th>';
						// $content .= '<th style ="color:yellow; background-color:green; width:20%"	>Grade</th>';
						// $content .= '</tr>';
					
						// $serial_nos = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND sub_section_title = :sst;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sst' => $diss->sub_section_title));
						// foreach($serial_nos as $sn){
							// $content .= '<tr>
							// <td style ="border:1px solid red; float:top; text-align:centre; background-color: rgba(236, 164, 45, 0.71);"><b>'.$sn->serial_no.'</b></td>
							// <td style ="border:1px solid red;">
							// <table style ="width:100%;">
							// <tr><td style ="border:1px solid green; text-align:centre; color:purple; background-color:#F3BFF3; width:15%"><b>Grade</b></td><td style ="border:1px solid green; color:purple; background-color:#F3BFF3; width:85%; padding-left:30px;	"><b>'.$sn->title.'</b></td></tr>';
							// $indicators = db_query("SELECT * FROM {$di_indicators_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND serial_no = :sn;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sn' => $sn->serial_no));
							// foreach($indicators as $indic){
								// $content .= '<tr>
								// <td style ="border:1px solid green; color:green; text-align:center;"><b>'.$indic->grade.'</b></td>
								// <td style ="border:1px solid green; text-align:left; padding-left:30px;">'.$indic->di.'</td>
								// </tr>';
							// }
							// $content .= '</table></td>';
							// $content .= '<td style ="border:1px solid red;">
							// <table style ="width:100%; float:top; border:1px solid red;">
							// <tr>';
					
							// $di_grade_table = 'essa_'.$session_id.'_exam_'.$term->	id.'_'.clean_exam_code_string($exam->exam_code).'_'.$class.'_di';
							// $di_field = $di_group_id.$section_id.clean_exam_code_string($diss->sub_section).$sn->serial_no;
							// $content .= '<th style = "background-color: #0D0D2B;">'.$exam->exam_code.'</th></tr>';
							// $student_grades = db_query("SELECT * FROM {$di_grade_table} WHERE adm_no = :an;", array(':an' => $adm_no));
							// foreach($student_grades as $stg){
								// $content .= '<tr>
								// <td style ="	text-align:center;">'.$stg->$di_field.'</td>
								// </tr>';
							// }
							
							// $content .= '</table>
							// </td>';
							// $content .= '</tr>';
						// }
						// $content .= '</table>';
						// $flag= 0;
						// $serial_nos = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND sub_section_title = :sst;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sst' => $diss->sub_section_title));
						// foreach($serial_nos as $sn){
							// $di_sa = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND serial_no = :sn;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sn' => $sn->serial_no));
							// foreach($di_sa as $disa){
								// if($disa->sa != NULL){
									// $flag=1;
								// }
							// }
						// }
						
						// if($flag == 1){
							// $content .= '<table style = width:100%;><tr colspan = "2"><td style ="background-color:purple; border-radius:10px; color:White; width:12%;">Suggested Activities : </td></tr>';
						// }
						
						// $serial_nos = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND sub_section_title = :sst;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sst' => $diss->sub_section_title));
						// foreach($serial_nos as $sn){
							// $di_sa = db_query("SELECT * FROM {$di_sa_table} WHERE group_id= :gi AND section_id = :si AND sub_section =:ss AND serial_no = :sn;", array(':gi' => $di_group_id, ':si' => $section_id, ':ss' => $diss->sub_section, ':sn' => $sn->serial_no));
							// foreach($di_sa as $disa){
								// if($disa->sa != NULL){
									// $content .= '<tr><td style ="color:red;"><h5><b><i>'.$disa->title.':</i></b></h5></td><td><h5>'.$disa->sa.'<h5></td></tr>';
								// }
							// }
						// }
						// $content .= '</table>';
					// }
					// $sub_section = $diss->sub_section_title;
				// }
			// }
		// }
	// }
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	$content .= '</body></html>';
	
	$html = '<html>';
	$html .= '<head></head>';
	$html .= '<body>';
	$html .= '<table style ="width:100%; border:1px solid black;">';
	$html .= '<tr><td style ="border:1px solid red;">S.No.</td><td style ="border:1px solid red;">Indicators</td><td style ="border:1px solid red;">Grade</td></tr>';
	$html .= '<tr>
	<td style ="border:1px solid red;">01</td>
	<td>
	<table style ="width:100%; border:1px solid black;">
	<tr><td style ="border:1px solid green;">Grade</td><td style ="border:1px solid green;">Skills</td></tr>
	<tr><td style ="border:1px solid green;">A</td><td style ="border:1px solid green;">vfkjjjx</td></tr>
	<tr><td style ="border:1px solid green;">B</td><td style ="border:1px solid green;">gojfdlgjdkf</td></tr>
	<tr><td style ="border:1px solid green;">C</td><td style ="border:1px solid green;">gojfdlgjdkf</td></tr>
	</table>
	</td>
	<td style ="border:1px solid red;">
	<table style ="width:100%; border:1px solid blue; float:top;">
	<tr><th>SA1</th><th>SA2</th></tr>
	<tr><td>A</td><td>B</td></tr>
	<tr><td>A</td><td>B</td></tr>
	<tr><td>A</td><td>B</td></tr>
	</table>
	</td>
	</tr>';
	$html .= '</table>';
	$html .= '</body>';
	$html .= '</html>';
	
	
	$form['markup'] = array(
		'#type' => 'markup',
		'#markup' => $content,
	);
	
	
	$path_print = db_query("
		SELECT * from field_data_field_path;"
	);
	foreach($path_print as $path){
		$path_to_print_module = $path->field_path_value;
	}
	require_once($path_to_print_module);
	
	// $page_size = 'A4';
	// $po = 'portrait';
	// $dompdf = new DOMPDF;
	// $dompdf->load_html($content);
	// $dompdf->set_paper($page_size, $po);
	// $dompdf->render();
	// // This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
	// $dompdf->stream($adm_no."_Report_card.pdf", array('compress' => FALSE));
	return $form;
}

function return_dates($from_date, $to_date){
	$from_date = new DateTime($from_date);
	$to_date = new DateTime($to_date,'+1 day');
	$date_range = new DatePeriod($from_date, new DateInterval('P1D'), $to_date);
	foreach($date_range as $dr){
		$dates = $dr->format('d-m-Y');
	}
	return $dates;
}