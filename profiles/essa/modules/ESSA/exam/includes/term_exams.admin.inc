<?php
/*
 * Implementing Callback function exam_form()
 */
function term_exams($form, $form_state, $term_id){
	$session = variable_get('essa_sid');
	$master_exam_table = 'essa_'.$session.'_exam_master';
	$term_table = 'essa_'.$session.'_exam_terms';
	
	global $user;
	$ec_uid = array();
	$exam_controller_role = db_query("SELECT * FROM role WHERE name = 'Exam Controller'");
	foreach($exam_controller_role as $ec_role){
		$ec_rid = $ec_role->rid;
	}
	$p_uid = array();
	$principal_role = db_query("SELECT * FROM role WHERE name = 'Principal'");
	foreach($principal_role as $p_role){
		$p_rid = $p_role->rid;
	}
	
	$a_uid = array();
	$admin_role = db_query("SELECT * FROM role WHERE name = 'administrator'");
	foreach($admin_role as $a_role){
		$a_rid = $a_role->rid;
	}
	
	$ct_uid = array();
	$class_teacher_role = db_query("SELECT * FROM role WHERE name = 'Class Teacher'");
	foreach($class_teacher_role as $ct_role){
		$ct_rid = $ct_role->rid;
	}
	
	$user_rd = array();
	$flag = 0;
	$class_teacher = 0;
	$term_exam = 0;
	$user_rid = db_query("SELECT * FROM users_roles WHERE uid = :u;", array(':u' => $user->uid));
	foreach($user_rid as $r){
		$user_rd[] = $r->rid;
		foreach($user_rd as $u_rid){
			if($u_rid == $ec_rid){
				$flag = 1;
			}elseif($u_rid == $p_rid){
				$flag = 1;
			}elseif($u_rid == $a_rid){
				$flag = 1;
			}elseif($u_rid == $ct_rid){
				$class_teacher = 1;
			}
			
		}
	}
	$term_list = array();
	$x = '<i class = "fa fa-pencil"></i>';
	$y = '<i class="fa fa-times" aria-hidden="true"></i>';
	//$z = '<i class ="fa fa-list-alt" aria-hidden="true"></i>';
	
	global $base_url;
	
	
	
	
	$terms = db_query("SELECT * FROM {$term_table} WHERE id = :t;", array(':t' => $term_id));
	foreach($terms as $term){
		$term_id = $term->id;
		$term_name = $term->term_name;		
		$create_exam_url = $base_url.'/admin/exam/'.$term_id.'/create_term_exam';
		
		$term_list[] = $term_id;
		$form[$term_id] = array(
			'#type' => 'fieldset',
			'#title' => $term_name.'('.$term->class_from.' - '.$term->class_to.')',
		);
	
	
		$exams = db_query("SELECT * FROM {$master_exam_table} WHERE status = 1 AND term = :t;", array(':t' => $term_id));
		foreach($exams as $exam){
			$edit_exam_url = $base_url.'/admin/exam/'.$term_id.'/'.$exam->exam_code.'/edit';
			$delete_exam_url = $base_url.'/admin/exam/'.$term_id.'/'.$exam->exam_code.'/delete';
			$upload_marks_url = $base_url.'/admin/exam/'.$term_id.'/'.$exam->exam_code.'/upload-marks';
			$generate_result_url = $base_url.'/admin/exam/'.$term_id.'/'.$exam->exam_code.'/generate-result';
			$publish_result_url = $base_url.'/admin/exam/'.$term_id.'/'.$exam->exam_code.'/publish-result';
			$create_schedule_url = $base_url.'/admin/exam/'.$term_id.'/'.$exam->exam_code.'/exam_schedule/create';
			$publish_schedule_url = $base_url.'/admin/exam/'.$term_id.'/'.$exam->exam_code.'/exam_schedule';
			
			if($flag == 1){
				$row[] = array(
					'#tree' =>TRUE,
					$exam->exam_code => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $exam->exam_code .'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$exam->exam_name.'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3><a href = "'.$upload_marks_url.'">Upload Marks</a></h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3><a href = "'.$generate_result_url.'">Generate Result</a></h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3><a href = "'.$create_schedule_url.'">Create/Edit Schedule</a></h3>',
						),
						'c6' =>array(
							'#type' => 'markup',
							'#markup' => '<h3><a href = "'.$publish_schedule_url.'">Publish Schedule</a></h3>',
						),
						'c7' =>array(
							'#type' => 'markup',
							'#markup' => '<h3><a href = "'.$publish_result_url.'">Publish Result</a></h3>',
						),
						'c8' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.l($x, $edit_exam_url, array('html' => TRUE)).l($y, $delete_exam_url, array('html' => TRUE)).'</h3>',
						),
					),
				);
			}elseif($class_teacher == 1){
				$row[] = array(
					'#tree' =>TRUE,
					$exam->exam_code => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $exam->exam_code .'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$exam->exam_name.'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3><a href = "'.$upload_marks_url.'">Upload Marks</a></h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3><a href = "'.$generate_result_url.'">Generate Result</a></h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3><a href = "'.$publish_schedule_url.'">Schedule</a></h3>',
						),
					),
				);
			}else{
					$row[] = array(
					'#tree' =>TRUE,
					$exam->exam_code => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $exam->exam_code .'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$exam->exam_name.'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3><a href = "'.$publish_schedule_url.'">Schedule</a></h3>',
						),
					),
				);
			}
		}
		
		if(isset($row)){
			$form[$term_id]['exam'] = array(
				'#theme' => 'term_exam_table',
				'rows' => $row,
			);
			if($flag == 1){
				$form['help'] = array(
					'#type' => 'markup',
					'#markup' => '<h3>'.$x.' - Edit Exam   '.$y.' - Delete Exam</h3>',
				);
			}
		}elseif($term_list == NULL){
			$form['msg'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 style = "color:Red;">No terms are created yet.Click <a href = "'.$create_exam_url.'">here</a> to create.</h3>',
			);
		}else{
			$form['msg'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 style = "color:Red;">No exams are created yet.Click <a href = "'.$create_exam_url.'">here</a> to create.</h3>',
			);
		}
		
	}
	
	return $form;
}

/**
 *Theme function student_passout_table()
 */
function theme_term_exam_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	
	global $user;
	$ec_uid = array();
	$exam_controller_role = db_query("SELECT * FROM role WHERE name = 'Exam Controller'");
	foreach($exam_controller_role as $ec_role){
		$ec_rid = $ec_role->rid;
	}
	$p_uid = array();
	$principal_role = db_query("SELECT * FROM role WHERE name = 'Principal'");
	foreach($principal_role as $p_role){
		$p_rid = $p_role->rid;
	}
	
	$a_uid = array();
	$admin_role = db_query("SELECT * FROM role WHERE name = 'administrator'");
	foreach($admin_role as $a_role){
		$a_rid = $a_role->rid;
	}
	
	$ct_uid = array();
	$class_teacher_role = db_query("SELECT * FROM role WHERE name = 'Class Teacher'");
	foreach($class_teacher_role as $ct_role){
		$ct_rid = $ct_role->rid;
	}
	
	$user_rd = array();
	$flag = 0;
	$class_teacher = 0;
	$term_exam = 0;
	$user_rid = db_query("SELECT * FROM users_roles WHERE uid = :u;", array(':u' => $user->uid));
	foreach($user_rid as $r){
		$user_rd[] = $r->rid;
		foreach($user_rd as $u_rid){
			if($u_rid == $ec_rid){
				$flag = 1;
			}elseif($u_rid == $p_rid){
				$flag = 1;
			}elseif($u_rid == $a_rid){
				$flag = 1;
			}elseif($u_rid == $ct_rid){
				$class_teacher = 1;
			}
			
		}
	}
  
	if($flag == 1){
		$header = array(t('Exam Code'),t('Exam Name'),t(''), t(''), t('Options/Actions'), t(''),t(''),t(''));
	}elseif($class_teacher == 1){
		$header = array(t('Exam Code'),t('Exam Name'),t(''), t('Options/Actions'), t(''));
	}else{
		$header = array(t('Exam Code'),t('Exam Name'),t('Schedule'));
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