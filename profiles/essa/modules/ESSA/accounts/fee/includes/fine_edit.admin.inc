<?php
/**
 *Implements page callback function - fine_edit
 */
function fine_edit($form, &$form_state){
	$session = variable_get('essa_sid');
	$fine_table = 'essa_'.$session.'_fees_student_fine';
	$student_table = 'essa_'.$session.'_master_student_table';
	$session = (string)variable_get('essa_sid');
	$basic_info_table = 'essa_'.$session.'_basicinfo';
	$class_table = 'essa_'.$session.'_class_list';
	
	$form['filter'] = array(
		'#type' => 'fieldset',
		'#title' => 'Filter By - ',
	);
	
	$form['filter']['ad'] = array(
		'#type' => 'fieldset',
	);
	
	$form['filter']['ad']['adm_no'] = array(
		'#type' => 'textfield',
    '#title' => t('Admission No.'),
    '#size' => 10,
		'#autocomplete_path' => 'adm_no/fee_autocomplete',
	);
	
	$cl_op = array('--Select--');
	$classes = db_query(
		"SELECT * from $class_table order by weight;"
	);
	foreach($classes as $cl){
		$cl_op[] = $cl->class_id;
	}
	
	$form['filter']['cs'] = array(
		'#type' => 'fieldset',
	);
	$sec = drupal_map_assoc(array('--Select--', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'));
	$form['filter']['cs']['class_filter'] = array(
		'#type' => 'select',
    '#title' => t('Class'),
    '#options' => drupal_map_assoc($cl_op),
	);
	
	$form['filter']['cs']['sec_filter'] = array(
		'#type' => 'select',
    '#title' => t('Section'),
    '#options' => drupal_map_assoc($sec),
	);
	
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
		$mon_options[] = $dt->format("M-Y");
	}
	
	$sel_options = array('--Select--' => '--Select--');
	foreach($mon_options as $mo){
		$m = str_replace('-', '_', $mo);
		$sel_options[$m] = $mo;
	}
	
	$form['filter']['mn'] = array(
		'#type' => 'fieldset',
	);
	$form['filter']['mn']['month'] = array(
		'#type' => 'select',
    '#title' => t('Month'),
		'#options' => $sel_options,
	);
	
	$fines = $particulars =array();
	$sel = array('--Select--' => '--Select--');
	$fine_detail = db_query(
		"SELECT * from $fine_table;"
	);
	foreach($fine_detail as $fd){
		if(substr($fd->particulars, 0, 7) != 'Library'){
			$particulars[] = $fd->particulars;
		}
	}
	$fines = array_unique($particulars);
	$fine_options = array_merge($sel, $fines);
	$form['filter']['pt'] = array(
		'#type' => 'fieldset',
	);
	$form['filter']['pt']['particulars'] = array(
		'#type' => 'select',
		'#options' => drupal_map_assoc($fine_options),
    '#title' => t('Particulars'),
	);
	
	$form['filter']['apply'] = array(
		'#type' => 'button',
		'#ajax' => array(
      'event' => 'click',
      'callback' => 'apply_filter_ajax',
      'wrapper' => 'sd_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#value' => 'Apply',
	);
	
	$form['note'] = array(
		'#type' => 'markup',
		'#markup' => 'NOTE: Delete will remove the complete fine, to edit the amount change the amount and click "Save" button which is below the table.',
	);
	
	if(!isset($form_state['values'])){
		$fine_detail = db_query(
			"SELECT * from $fine_table;"
		);
		foreach($fine_detail as $fd){
			if(substr($fd->particulars, 0, 7) != 'Library'){
				
				$students = db_query(
					"SELECT * from $student_table where adm_no = :an AND status = 1;", array(':an' => $fd->adm_no)
				);
				foreach($students as $st){
					$name = $st->student_name;
					$cl = $st->class;
					$sec = $st->section;
				}
				
				$mon = str_replace('_', '-', $fd->month);
				if($fd->receipt_no == NULL){
					$row[] = array(
						'#tree' =>TRUE,
						$fd->id => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $fd->id .'</h3>',
							),
							'c2' => array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $fd->adm_no .'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $name .'</h3>',
							),
							'cs' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $cl.' - '.$sec .'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $fd->particulars .'</h3>',
							),
							'c5' =>array(
								'#type' => 'select',
								'#options' => drupal_map_assoc($mon_options),
								'#default_value' => $mon,
							),
							'c6' =>array(
								'#type' => 'textfield',
								'#default_value' => $fd->amount_to_be_paid,
								'#size' => 10,
							),
							$fd->id =>array(
								'#type' => 'submit',
								'#submit' => array('delete_student_fine'),
								'#value' => 'Delete',
								'#name' => $fd->id,
								'#prefix' => '<div id = "delete_fine">',
								'#suffix' => '</div>',
							),
						),
					);
				}
			}
		}
	}else{
		$master = array();
		$query=db_select($fine_table,'ft');
		$query->join($student_table,'st','ft.adm_no = st.adm_no');
		$query
      ->fields('ft',array('id','adm_no','particulars', 'month', 'amount_to_be_paid', 'receipt_no'))
      ->fields('st',array('student_name', 'class', 'section'));
		$result= $query->execute();
    foreach($result as $r){
			$master[$r->id] = $r->id;
		}
		
		$filter_adm_no = array();
		$filter_class = array();
		$filter_sec = array();
		$filter_class_from = array();
		$filter_class_to = array();
		$filter_month = array();
		$filter_particulars = array();
		
		//dsm($form_state);
		if($form_state['values']['adm_no'] != NULL){
			$query=db_select($fine_table,'ft');
			$query->join($student_table,'st','ft.adm_no = st.adm_no');
			$query->condition('ft.adm_no',$form_state['values']['adm_no'])
				->fields('ft',array('id','adm_no','particulars', 'month', 'amount_to_be_paid', 'receipt_no'))
				->fields('st',array('student_name', 'class', 'section'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_adm_no[$r->id] = $r->id;
			}
			$master = array_intersect($master, $filter_adm_no);
		}
		
		if($form_state['values']['class_filter'] != '--Select--'){
			$query=db_select($fine_table,'ft');
			$query->join($student_table,'st','ft.adm_no = st.adm_no');
			$query->condition('st.class',$form_state['values']['class_filter'])
				->fields('ft',array('id','adm_no','particulars', 'month', 'amount_to_be_paid', 'receipt_no'))
				->fields('st',array('student_name', 'class', 'section'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_class[$r->id] = $r->id;
			}
			$master = array_intersect($master, $filter_class);
		}
		
		if($form_state['values']['sec_filter'] != '--Select--'){
			$query=db_select($fine_table,'ft');
			$query->join($student_table,'st','ft.adm_no = st.adm_no');
			$query->condition('st.section',$form_state['values']['sec_filter'])
				->fields('ft',array('id','adm_no','particulars', 'month', 'amount_to_be_paid', 'receipt_no'))
				->fields('st',array('student_name', 'class', 'section'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_sec[$r->id] = $r->id;
			}
			$master = array_intersect($master, $filter_sec);
		}
		
		if($form_state['values']['month'] != '--Select--'){
			$query=db_select($fine_table,'ft');
			$query->join($student_table,'st','ft.adm_no = st.adm_no');
			$query->condition('ft.month', $form_state['values']['month'])
				->fields('ft',array('id','adm_no','particulars', 'month', 'amount_to_be_paid', 'receipt_no'))
				->fields('st',array('student_name', 'class', 'section'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_month[$r->id] = $r->id;
			}
			$master = array_intersect($master, $filter_month);
		}
		
		if($form_state['values']['particulars'] != '--Select--'){
			$query=db_select($fine_table,'ft');
			$query->join($student_table,'st','ft.adm_no = st.adm_no');
			$query->condition('ft.particulars', $form_state['values']['particulars'])
				->fields('ft',array('id','adm_no','particulars', 'month', 'amount_to_be_paid', 'receipt_no'))
				->fields('st',array('student_name', 'class', 'section'));
			$result= $query->execute();
			foreach($result as $r){
				$filter_particulars[$r->id] = $r->id;
			}
			$master = array_intersect($master, $filter_particulars);
		}
		
		foreach($master as $filter_fine_id){
			$fine_detail = db_query(
				"SELECT * from $fine_table where id = :id;", array(':id' => $filter_fine_id)
			);
			foreach($fine_detail as $fd){
				$students = db_query(
					"SELECT * from $student_table where adm_no = :an AND status = 1;", array(':an' => $fd->adm_no)
				);
				foreach($students as $st){
					$name = $st->student_name;
					$cl = $st->class;
					$sec = $st->section;
				}
				
				$mon = str_replace('_', '-', $fd->month);
				if($fd->receipt_no == NULL && (substr($fd->particulars, 0, 7) != 'Library')){
					$row[] = array(
						'#tree' =>TRUE,
						$fd->id => array(  //Generating unique array id for every form element
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $fd->id .'</h3>',
							),
							'c2' => array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $fd->adm_no .'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $name .'</h3>',
							),
							'cs' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $cl.' - '.$sec .'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $fd->particulars .'</h3>',
							),
							'c5' =>array(
								'#type' => 'select',
								'#options' => drupal_map_assoc($mon_options),
								'#default_value' => $mon,
							),
							'c6' =>array(
								'#type' => 'textfield',
								'#default_value' => $fd->amount_to_be_paid,
								'#size' => 10,
							),
							$fd->id =>array(
								'#type' => 'submit',
								'#submit' => array('delete_student_fine'),
								'#value' => 'Delete',
								'#name' => $fd->id,
								'#prefix' => '<div id = "delete_fine">',
								'#suffix' => '</div>',
							),
						),
					);
				}
			}
		}
	}
	
	
	if(!isset($row)){
    drupal_set_message('No Fine has been applied.', $type = 'error');
    $row = array();
  }
	
	//Calling the theme function to build the custom table and display the form in tabular format.
  $form['lts'] = array(
    '#theme' => 'fine_table',
    'rows' => $row,
		'#prefix' => '<div id = "sd_wrapper">',
		'#suffix' => '</div>',
  );
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
		'#submit' => array('fine_edit_save'),
	);
	
	return $form;
}

function apply_filter_ajax($form, &$form_state){
	return $form['lts'];
}

/**
 *Implements submit logic
 */
function fine_edit_save($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	
	foreach($form_state['values'] as $key => $val){
		if(is_array($val)){
			foreach($val as $k => $v){
				$mon = str_replace('-', '_', $v['c5']);
				db_merge($fees_student_fine)
					->key(array('id' => $k))
					->fields (array(
						'month' => $mon,
						'amount_to_be_paid' => $v['c6'],
					)
				)
				->execute();
			}
		}
	}
	
	drupal_set_message('<h3 style = "color: GREEN; padding-top: 15px;"><b>Fine was successfully edited.</b></h3>','status');
}
/**
 *Implements delete logic
 */
function delete_student_fine($form, &$form_state){
	global $user;
	variable_set('delete-fine-id'.$user->uid, $form_state['triggering_element']['#name']);
	global $base_url;
	$url = url('delete-student-fine', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
}

function delete_student_fine_pagecallback(){
	return drupal_get_form('delete_student_fine_confirm');
}

function delete_student_fine_confirm($form, &$form_state){
	$heading = t('Are you sure to delete this fine from student\'s account?');
	$caption = '<h3>This action can\'t be undone.</h3>';
	
	$cancel_path = 'admin/fees/fine';
	$yes = t('Delete');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

function delete_student_fine_confirm_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$fees_student_fine = 'essa_'.$session_id.'_fees_student_fine';
	global $user;
	$fine_id = variable_get('delete-fine-id'.$user->uid);
	db_delete($fees_student_fine)
		->condition('id', $fine_id)
		->execute();
	
	$url = url('admin/fees/fine', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
	
	drupal_set_message('The fine was deleted successfully.','status');
}

/**
 *Theme function
 */
function theme_fine_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Fine ID'),t('Adm No.'), t('Name'), t('Class-Section'), t('Particulars'), t('Month'), t('Amount'), t(''));
  
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