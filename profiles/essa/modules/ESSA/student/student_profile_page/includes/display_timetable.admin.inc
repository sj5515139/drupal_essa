<?php

function display_timetable($form, &$form_state, $uid){	
  $session_id = (string)variable_get('essa_sid');
	$student_master_table = 'essa_'.$session_id.'_master_student_table';
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $uid,
  );
	
	$form['back'] = array(
    '#type' => 'submit',
    '#value' => 'Back',
    '#submit' => array('go_back'),
  );
	
  $student = db_query("
		SELECT * from {$student_master_table} where uid = :uid;", array(':uid' => $uid)
	);
	foreach($student as $s){
    $class = $s->class;
    $section = $s->section;
  }
  $tt_table = 'essa_'.$session_id.'_time_table_'.$class.'_'.$section;
  $student_tt = db_query("
		SELECT * from {$tt_table} order by day_weight;"
	);
	foreach($student_tt as $tt){
    $period1 = isset($tt->Period1)?$tt->Period1:NULL;
    $period2 = isset($tt->Period2)?$tt->Period2:NULL;
    $period3 = isset($tt->Period3)?$tt->Period3:NULL;
    $period4 = isset($tt->Period4)?$tt->Period4:NULL;
    $period5 = isset($tt->Period5)?$tt->Period5:NULL;
    $period6 = isset($tt->Period6)?$tt->Period6:NULL;
    $period7 = isset($tt->Period7)?$tt->Period7:NULL;
    $period8 = isset($tt->Period8)?$tt->Period8:NULL;
		
		$period1 = explode('(', $period1);
		$period2 = explode('(', $period2);
		$period3 = explode('(', $period3);
		$period4 = explode('(', $period4);
		$period5 = explode('(', $period5);
		$period6 = explode('(', $period6);
		$period7 = explode('(', $period7);
		$period8 = explode('(', $period8);
    
    $row[] = array(
      '#tree' =>TRUE,
			
      $tt->day_weight => array(  //Generating unique array id for every form element
				'c1' =>array(
          '#type' => 'markup',
					'#markup' => $tt->day,
        ),
        'c2' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period1[0].'</h3>',
        ),
        'c3' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period2[0].'</h3>',
        ),
				'c4' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period3[0].'</h3>',
				),
				'c5' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period4[0].'</h3>',
				),
				'c6' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period5[0].'</h3>',
				),
				'c7' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period6[0].'</h3>',
				),
				'c8' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period7[0].'</h3>',
				),
        'c9' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$period8[0].'</h3>',
				),
      ),
    );
  }
  
  $form['time_table'] = array(
    '#theme' => 'student_time_table_theme_table',
    'rows' => $row,
  );
	
	
	$form['pdf']  = array(
		'#type' => 'submit',
		'#value' =>t('Download PDF'),
		'#submit' => array('get_student_timetable'),
 	);
  /*
  $form['back'] = array(
    '#type' => 'submit',
    '#value' => 'Back',
    '#submit' => array('go_back'),
  );
  */
  return $form;
}


/**
 *Gets data from time_table db table to be used for PDF generation.
 */
function get_student_timetable($form, &$form_state){
	$session_id = variable_get('essa_sid');
	$subject_teacher_table = 'essa_'.$session_id.'_subject_teacher_table';
	$student_master_table = 'essa_'.$session_id.'_master_student_table';
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
	
	$student = db_query("
		SELECT * from {$student_master_table} where uid = :uid;", array(':uid' =>$form_state['values']['uid'])
	);
	foreach($student as $s){
    $class = $s->class;
    $section = $s->section;
  }
  $tt_table = 'essa_'.$session_id.'_time_table_'.$class.'_'.$section;
  
	
	$output .= '<h1 style = "display: inline-block; float: center; clear: both; text-align: center; color:#006600	">'.$school_name.'</h1>';
	$output .= '</br></br><h3 style = "text-align: center;">Time Table of '.$class.'-'.$section.'</h3>';
	
	$output .= '<table border="1" style="width:100%; text-align:center;">';
	$output .= '<tr><th>Days</th><th>Period1</th><th>Period2</th><th>Period3</th><th>Period4</th><th>Period5</th><th>Period6</th><th>Period7</th><th>Period8</th>';
	$output .= '</tr>';
	
 
  $student_tt = db_query("
		SELECT * from {$tt_table} order by day_weight;"
	);
	foreach($student_tt as $tt){
    $period1 = isset($tt->Period1)?$tt->Period1:NULL;
    $period2 = isset($tt->Period2)?$tt->Period2:NULL;
    $period3 = isset($tt->Period3)?$tt->Period3:NULL;
    $period4 = isset($tt->Period4)?$tt->Period4:NULL;
    $period5 = isset($tt->Period5)?$tt->Period5:NULL;
    $period6 = isset($tt->Period6)?$tt->Period6:NULL;
    $period7 = isset($tt->Period7)?$tt->Period7:NULL;
    $period8 = isset($tt->Period8)?$tt->Period8:NULL;
		
		$period1 = explode('(', $period1);
		$period2 = explode('(', $period2);
		$period3 = explode('(', $period3);
		$period4 = explode('(', $period4);
		$period5 = explode('(', $period5);
		$period6 = explode('(', $period6);
		$period7 = explode('(', $period7);
		$period8 = explode('(', $period8);
		
		$output .= '<tr>';
		$output .= '<td>'.$tt->day.'</td>';
		$output .= '<td>'.$period1[0].'</td>';
		$output .= '<td>'.$period2[0].'</td>';
		$output .= '<td>'.$period3[0].'</td>';
		$output .= '<td>'.$period4[0].'</td>';
		$output .= '<td>'.$period5[0].'</td>';
		$output .= '<td>'.$period6[0].'</td>';
		$output .= '<td>'.$period7[0].'</td>';
		$output .= '<td>'.$period8[0].'</td>';
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


function go_back($form, &$form_state){
  //$current_path = current_path();
  global $base_url;
	$url = $base_url.'/user/'.$form_state['values']['uid'];
  $form_state['redirect'] = $url;
}

/**
 * Theme callback for the form table.
*/ 
function theme_student_time_table_theme_table(&$variables) {
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