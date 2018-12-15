<?php

function display_timetable($form, &$form_state, $uid){
  $session_id = (string)variable_get('essa_sid');
	$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $uid,
  );
  
	$form['back'] = array(
    '#type' => 'submit',
    '#value' => 'Back',
    '#submit' => array('go_back'),
  );
  
	$staff = db_query("
		SELECT * from {$staff_master_table} where uid = :uid;", array(':uid' => $uid)
	);
	foreach($staff as $s){
    $emp_id = $s->emp_id;
  }
  $tt_table = 'essa_'.$session_id.'_time_table_'.clean_teacher($emp_id);
  
  $staff_tt = db_query("
		SELECT * from {$tt_table} order by day_weight;"
	);
	foreach($staff_tt as $tt){
    $period1 = isset($tt->Period1_class)?$tt->Period1_class.'</br>'.$tt->Period1_subject:NULL;
    $period2 = isset($tt->Period2_class)?$tt->Period2_class.'</br>'.$tt->Period2_subject:NULL;
    $period3 = isset($tt->Period3_class)?$tt->Period3_class.'</br>'.$tt->Period3_subject:NULL;
    $period4 = isset($tt->Period4_class)?$tt->Period4_class.'</br>'.$tt->Period4_subject:NULL;
    $period5 = isset($tt->Period5_class)?$tt->Period5_class.'</br>'.$tt->Period5_subject:NULL;
    $period6 = isset($tt->Period6_class)?$tt->Period6_class.'</br>'.$tt->Period6_subject:NULL;
    $period7 = isset($tt->Period7_class)?$tt->Period7_class.'</br>'.$tt->Period7_subject:NULL;
    $period8 = isset($tt->Period8_class)?$tt->Period8_class.'</br>'.$tt->Period7_subject:NULL;
    
    $row[] = array(
      '#tree' =>TRUE,
			
      $tt->day_weight => array(  //Generating unique array id for every form element
				'c1' =>array(
          '#type' => 'markup',
					'#markup' => $tt->day,
        ),
        'c2' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period1.'</h3>',
        ),
        'c3' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period2.'</h3>',
        ),
				'c4' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period3.'</h3>',
				),
				'c5' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period4.'</h3>',
				),
				'c6' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period5.'</h3>',
				),
				'c7' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period6.'</h3>',
				),
				'c8' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period7.'</h3>',
				),
        'c9' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period8.'</h3>',
				),
      ),
    );
  }
  
  $form['time_table'] = array(
    '#theme' => 'teacher_time_table_theme_table',
    'rows' => $row,
  );
  
	$form['pdf']  = array(
		'#type' => 'submit',
		'#value' =>t('Download PDF'),
		'#submit' => array('get_teacher_timetable'),
 	);
	
  return $form;
}

function go_back($form, &$form_state){
  //$current_path = current_path();
  global $base_url;
	$url = $base_url.'/user/'.$form_state['values']['uid'];
  $form_state['redirect'] = $url;
}


/**
 *Gets data from time_table db table to be used for PDF generation.
 */
function get_teacher_timetable($form, &$form_state){
	$session_id = variable_get('essa_sid');
	$subject_teacher_table = 'essa_'.$session_id.'_subject_teacher_table';
	$staff_master_table = 'essa_'.$session_id.'_master_staff_table';
	$basic_info_table = 'essa_'.$session_id.'_basicinfo';
	
	$query = db_query("SELECT * FROM {$basic_info_table}");
	foreach($query as $q){
		$school_name = $q->nameofschool;
	}
	
	$output = '<html>';
	$output .= '<head>';
	$output .= '<style>';
	$output .= 'table, th, td {
		border: 1px solid black;
		border-collapse: collapse;
		padding: 2px;
		background-color: #ffff80;
		border: 1px solid #006600;
	}
	th{
		background: 	#006600;
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
	
	$staff = db_query("
		SELECT * from {$staff_master_table} where uid = :uid;", array(':uid' => $form_state['values']['uid'])
	);
	foreach($staff as $s){
    $emp_id = $s->emp_id;
  }
	
	$output .= '<h1 style = "display: inline-block; float: center; clear: both; text-align: center; color:#006600	">'.$school_name.'</h1>';
	$output .= '</br></br><h3 style = "text-align: center;">Time Table of '.$emp_id.'</h3>';
	
	$output .= '<table border="1" style="width:100%; text-align:center;">';
	$output .= '<tr><th>Days</th><th>Period1</th><th>Period2</th><th>Period3</th><th>Period4</th><th>Period5</th><th>Period6</th><th>Period7</th><th>Period8</th>';
	$output .= '</tr>';
	
  $tt_table = 'essa_'.$session_id.'_time_table_'.clean_teacher($emp_id);
  
  $staff_tt = db_query("
		SELECT * from {$tt_table} order by day_weight;"
	);
	foreach($staff_tt as $tt){
    $period1 = isset($tt->Period1_class)?$tt->Period1_class.'</br>'.$tt->Period1_subject:NULL;
    $period2 = isset($tt->Period2_class)?$tt->Period2_class.'</br>'.$tt->Period2_subject:NULL;
    $period3 = isset($tt->Period3_class)?$tt->Period3_class.'</br>'.$tt->Period3_subject:NULL;
    $period4 = isset($tt->Period4_class)?$tt->Period4_class.'</br>'.$tt->Period4_subject:NULL;
    $period5 = isset($tt->Period5_class)?$tt->Period5_class.'</br>'.$tt->Period5_subject:NULL;
    $period6 = isset($tt->Period6_class)?$tt->Period6_class.'</br>'.$tt->Period6_subject:NULL;
    $period7 = isset($tt->Period7_class)?$tt->Period7_class.'</br>'.$tt->Period7_subject:NULL;
    $period8 = isset($tt->Period8_class)?$tt->Period8_class.'</br>'.$tt->Period7_subject:NULL;
		
		$output .= '<tr>';
		$output .= '<td>'.$tt->day.'</td>';
		$output .= '<td>'.$period1.'</td>';
		$output .= '<td>'.$period2.'</td>';
		$output .= '<td>'.$period3.'</td>';
		$output .= '<td>'.$period4.'</td>';
		$output .= '<td>'.$period5.'</td>';
		$output .= '<td>'.$period6.'</td>';
		$output .= '<td>'.$period7.'</td>';
		$output .= '<td>'.$period8.'</td>';
		$output .= '</tr>';
	}
	
	$output .= '</table>';
	$output .= '</body>';
	$output .= '</html>';
	
	$path_print = db_query("
		SELECT * from field_data_field_path;"
	);
	foreach($path_print as $path){
		$path_to_print_module = $path->field_path_value;
	}
	require_once($path_to_print_module);
	
	$page_size = 'A4';
	$po = 'landscape';
	
	$content = $output;
	$dompdf = new DOMPDF;
	$dompdf->load_html($output);
	$dompdf->set_paper($page_size, $po);
	$dompdf->render();
	// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
	$dompdf->stream("Time-Table_".$emp_id.".pdf");
	
}

/**
 * Theme callback for the form table.
*/ 
function theme_teacher_time_table_theme_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Days'),t('Period1'), t('Period2'),t('Period3'), t('Period4'), t('Period5'), t('Period6'), t('Period7'), t('Period8'));
  
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
function clean_teacher($string) {
   $string = str_replace(' ', '_', $string);
	 $string = str_replace('-', '_', $string);
	 $string = str_replace('/', '_', $string);// Replaces all spaces with hyphens.
   return preg_replace('/[^A-Za-z0-9\-]/', '', $string); // Removes special chars.
}