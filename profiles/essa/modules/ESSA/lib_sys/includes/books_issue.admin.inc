<?php
/**
 *Implements page callback function - books_issue.
 */
function books_issue($form = array(), &$form_state){
	//$name = 0;
	$session_id = (string)variable_get('essa_sid');
	$master_student_table = 'essa_'.$session_id.'_master_student_table';
	$master_staff_table = 'essa_'.$session_id.'_master_staff_table';
	$issue_table = 'essa_'.$session_id.'_lib_issue';
	
	$form['cnt'] = array(
		'#type' => 'container',
	);
	
	$form['cnt']['acc_no'] = array(
		'#type' => 'textfield',
		'#title' => 'Acc. No.',
		'#size' => 10,
		'#ajax' => array(
      'event' => 'change',
      'callback' => 'show_book_detail_ajax',
      'wrapper' => 'book_detail',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		'#attached' => array(
			'js' => array(
				drupal_get_path('module', 'lib_sys') . '/add_book_focus.js'
			),
		),
	);
	
	$form['cnt']['uid'] = array(
		'#title' => 'Adm. no./Emp. ID',
		'#type' => 'textfield',
		'#size' => 20,
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'issue_return_detail_ajax',
      'wrapper' => 'issue_detail',
      'method' => 'replace',
      'effect' => 'fade',
    ),
		//'#autocomplete_path' => 'uid/autocomplete',
		// '#suffix' => '<script type="text/javascript">'
     // . 'jQuery(\'input#edit-uid\').focus();'
     // . '</script>',
	);
	$form['cnt']['new'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "user_detail" style = "float: left;">',
		'#suffix' => '</div>',
	);
	
	$format = 'd-m-Y';
	$def_dt = date('d-m-Y');
	$form['cnt']['issue_date'] = array(
		'#type' => 'date_select',
		'#title' => t('Issue Date'),
		'#default_value' => $def_dt, 
		'#date_format' => $format,
		'#date_year_range' => '0:+1',
		'#date_label_position' => 'within',
		'#required' => TRUE,
		'#validated' => TRUE,
	);
	
	$form['cnt']['save'] = array(
		'#type' => 'submit',
		'#value' => 'issue',
	);
	
	$form['cnt']['cancel'] = array(
		'#type' => 'submit',
		'#value' => 'Cancel',
		'#submit' => array('cancel_issue'),
	);
	
	$form['fs'] = array(
		'#type' => 'container',
		'#title' => 'Book Details',
		'#prefix' => '<div id = "book_detail">',
		'#suffix' => '</div>',
	);
	
	if(!empty($form_state['values']['acc_no']) && $form_state['triggering_element']['#value'] != 'Remove'){
		global $user;
		$arr = variable_get('book_issue'.$user->uid);
		
		$vocabulary = taxonomy_vocabulary_machine_name_load('book_availability');
		$terms = entity_load('taxonomy_term', FALSE, array('vid' => $vocabulary->vid));
		foreach($terms as $term){
			if($term->name == 'Available'){
				$available_tid = $term->tid;
			}
			if($term->name == 'Issued'){
				$issued_tid = $term->tid;
			}
		}
		
		$books =  db_query(
			"SELECT * from field_data_field_barcode_value where field_barcode_value_value = :bv;", array(':bv' => '0'.$form_state['values']['acc_no'])
		);
		foreach($books as $book){
			$bk = node_load($book->entity_id);
			if($bk->field_availability['und'][0]['tid'] == $issued_tid){
				drupal_set_message('This book has already been issued. Please process the return first.', 'warning');
			}else{
				$nw1 = $bk->field_acc_no_['und'][0]['value'];
			}
		}
		
		if(isset($nw1)){
			$arr[] = $nw1;	
		}else{
			$books =  db_query(
				"SELECT * from field_data_field_acc_no_ where field_acc_no__value = :acc_no;", array(':acc_no' => $form_state['values']['acc_no'])
			);
			foreach($books as $book){
				$bk = node_load($book->entity_id);
				if($bk->field_availability['und'][0]['tid'] == $issued_tid){
					drupal_set_message('This book has already been issued. Please process the return first.', 'warning');
				}else{
					$arr[] = $form_state['values']['acc_no'];
				}
			}
		}
		
		$selected_books = array_unique($arr);
		variable_set('book_issue'.$user->uid, $selected_books);
		
		foreach($selected_books as $val){
			$books =  db_query(
				"SELECT * from field_data_field_acc_no_ where field_acc_no__value = :acc_no;", array(':acc_no' => $val)
			);
			foreach($books as $book){
				$bk = node_load($book->entity_id);
				
				$row[$book->entity_id] = array(
					'#tree' =>TRUE,
					$book->entity_id => array(  //Generating unique array id for every form element 
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'. $bk->field_acc_no_['und'][0]['value'] .'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'. $bk->title .'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'. $bk->field_author1['und'][0]['value'] .'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'. $bk->field_publisher['und'][0]['value'] .'</h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'. $bk->field_year['und'][0]['value'] .'</h3>',
						),
						'c6' => array(
							'#type' => 'button',
							'#value' => 'Remove',
							'#name' => $bk->field_acc_no_['und'][0]['value'],
							'#ajax' => array(
								'event' => 'click',
								'callback' => 'delete_this_issue',
								'wrapper' => 'book_detail',
								'method' => 'replace',
								'effect' => 'fade',
							),
							'#prefix' => '<div id = "delete_issue">',
							'#suffix' => '</div>',
						),
					),
				);
			}
		}
		
		$form['fs']['tab'] = array(
			'#theme' => 'book_issue_table',
			'rows' => $row,
		);
	}elseif(!empty($form_state['values']['acc_no']) && $form_state['triggering_element']['#value'] == 'Remove'){
		global $user;
		$arr = variable_get('book_issue'.$user->uid);
		
		foreach($arr as $k=>$v){
			if(($key = array_search($form_state['triggering_element']['#name'], $arr)) !== false) {
				unset($arr[$key]);
			}
		}
		variable_set('book_issue'.$user->uid, $arr);
		global $user;
		$selected_books = array_unique(variable_get('book_issue'.$user->uid));
		foreach($selected_books as $val){
			$books =  db_query(
				"SELECT * from field_data_field_acc_no_ where field_acc_no__value = :acc_no;", array(':acc_no' => $val)
			);
			foreach($books as $book){
				$bk = node_load($book->entity_id);
				$row[$book->entity_id] = array(
					'#tree' =>TRUE,
					$book->entity_id => array(  //Generating unique array id for every form element 
						'c1' =>array(
					    '#type' => 'markup',
						  '#markup' => '<h3 style = "text-align: left !important;">'. $bk->field_acc_no_['und'][0]['value'] .'</h3>',
						),
				    'c2' =>array(
					    '#type' => 'markup',
						  '#markup' => '<h3 style = "text-align: left !important;">'. $bk->title .'</h3>',
						),
						'c3' =>array(
					    '#type' => 'markup',
						  '#markup' => '<h3 style = "text-align: left !important;">'. $bk->field_author1['und'][0]['value'] .'</h3>',
						),
						'c4' =>array(
					    '#type' => 'markup',
						  '#markup' => '<h3 style = "text-align: left !important;">'. $bk->field_publisher['und'][0]['value'] .'</h3>',
						),
						'c5' =>array(
					    '#type' => 'markup',
							'#markup' => '<h3 style = "text-align: left !important;">'. $bk->field_year['und'][0]['value'] .'</h3>',
						),
						'c6' => array(
							'#type' => 'button',
							'#value' => 'Remove',
							'#name' => $bk->field_acc_no_['und'][0]['value'],
							'#ajax' => array(
								'event' => 'click',
							  'callback' => 'delete_this_issue',
							  'wrapper' => 'book_detail',
							  'method' => 'replace',
							  'effect' => 'fade',
							),
							'#prefix' => '<div id = "delete_issue">',
							'#suffix' => '</div>',
						),
					),
				);
			}
		}
		
		$form['fs']['tab'] = array(
			'#theme' => 'book_issue_table',
			'rows' => $row,
		);
	}
	if(variable_get('issue_no') == NULL){
		variable_set('issue_no', 1);
	}
	
	$flag = 0;
	
	if(!empty($form_state['values']['uid'])){
		//dsm($form_state['values']['uid']);
		$uid_staff_name = db_query("SELECT * FROM {$master_staff_table} WHERE emp_id = :uid;", array(':uid' => $form_state['values']['uid']));
		foreach($uid_staff_name as $usn){
			$staff_name = $usn->fname.' '.$usn->lname;
			$staff_type = $usn->type;
		}
		$uid_student_name = db_query("SELECT * FROM {$master_student_table} WHERE adm_no = :uid;", array(':uid' => $form_state['values']['uid']));
		foreach($uid_student_name as $usn){
			$student_name = $usn->student_name;
			$class = $usn->class.'-'.$usn->section;
			$roll = $usn->roll_no;
		}
		//dsm($student_name);
		
		if(isset($staff_name)){
			$form['cnt']['new']['name'] = array(
				'#type' => 'markup',
				'#markup' => '<h3>Name : '.$staff_name.'</h3></br><h3>Type : '.$type.'</h3>',
			);
		}elseif(isset($student_name)){
			$form['cnt']['new']['name'] = array(
				'#type' => 'markup',
				'#markup' => '<h3>Name : '.$student_name.'</h3></br><h3>Class : '.$class.'</h3></br><h3>Roll No. : '.$roll.'</h3>',
			);
		}
		
		$issued_books =  db_query(
			"SELECT * from $issue_table where status = 'open' and user_id = :ui;", array(':ui' => $form_state['values']['uid'])
		);
		foreach($issued_books as $ib){
			$issue_no = $ib->issue_no;
			$acc_no = $ib->acc_no;
			$issue_dat = $ib->issue_date;
			$books =  db_query(
				"SELECT * from field_data_field_acc_no_ where field_acc_no__value = :acc_no;", array(':acc_no' => $acc_no)
			);
			foreach($books as $book){
				$flag = 1;
				$bk = node_load($book->entity_id);
				$title = $bk->title;
				$author = $bk->field_author1['und'][0]['value'];
			}
			$return_row[$ib->acc_no] = array(
				'#tree' =>TRUE,
				$ib->acc_no => array(  //Generating unique array id for every form element 
					'c2' =>array(
				    '#type' => 'markup',
					  '#markup' => '<h3 style = "text-align: left !important;">'. $issue_no .'</h3>',
					),
					'c3' =>array(
				    '#type' => 'markup',
					  '#markup' => '<h3 style = "text-align: left !important;">'. $acc_no .'</h3>',
					),
					'c4' =>array(
					  '#type' => 'markup',
					  '#markup' => '<h3 style = "text-align: left !important;">'. $title .'</h3>',
					),
					'c5' =>array(
				    '#type' => 'markup',
					  '#markup' => '<h3 style = "text-align: left !important;">'. $bk->field_author1['und'][0]['value'] .'</h3>',
					),
					'c6' =>array(
					  '#type' => 'markup',
					  '#markup' => '<h3 style = "text-align: left !important;">'. $bk->field_publisher['und'][0]['value'] .'</h3>',
					),
					'c7' =>array(
				    '#type' => 'markup',
						'#markup' => '<h3 style = "text-align: left !important;">'. $bk->field_year['und'][0]['value'] .'</h3>',
					),		
				),
			);
		}
	}
	$form['rfs'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "issue_detail">',
		'#suffix' => '</div>',
	);
	if($flag == 1){
		$form['rfs']['rtfs'] = array(
			'#type' => 'fieldset',
			'#title' => 'Return',
		);
		
		$form['rfs']['rtfs']['tab'] = array(
			'#theme' => 'return_history_table',
			'rows' => $return_row,
		);
	}
	return $form;
}

function issue_return_detail_ajax($form, &$form_state){
	return array($form['rfs'], $form['cnt']['new']); 
	//return $form['rfs'];
}

/**
 *Implements submit function for the issue form.
 */
function books_issue_submit($form = array(), &$form_state){
	global $user;
	//dsm(variable_get('book_issue'.$user->uid));
	//dsm($form_state);
	$session_id = (string)variable_get('essa_sid');
	$issue_table = 'essa_'.$session_id.'_lib_issue';
	$teacher_table = 'essa_'.$session_id.'_master_staff_table';
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$issue_no = variable_get('issue_no');
	$issue_dt = $form_state['values']['issue_date']['day'].'-'.$form_state['values']['issue_date']['month'].'-'.$form_state['values']['issue_date']['year'];
	$issue_date = strtotime($issue_dt);
	$vocabulary = taxonomy_vocabulary_machine_name_load('book_availability');
	$terms = entity_load('taxonomy_term', FALSE, array('vid' => $vocabulary->vid));
	foreach($terms as $term){
		if($term->name = 'Available'){
			$available_tid = $term->tid;
		}
		if($term->name = 'Issued'){
			$issued_tid = $term->tid;
		}
	}
	
	//$user_role = db_query("SELECT * FROM user_role WHERE uid = :uid;");
	
	$students =  db_query(
		"SELECT * from $student_table where adm_no = :adm_no;", array(':adm_no' => $form_state['values']['uid'])
	);
	foreach($students as $st){
		$uid = $st->uid;
	}
	
	$staffs =  db_query(
		"SELECT * from $teacher_table where emp_id = :emp_id;", array(':emp_id' => $form_state['values']['uid'])
	);
	foreach($staffs as $stf){
		$uid = $stf->uid;
	}
	//dsm($uid);
	$emp_id = '';
	$staffs =  db_query(
		"SELECT * from $teacher_table where uid = :uid;", array(':uid' => $user->uid)
	);
	foreach($staffs as $stf){
		$emp_id = $stf->emp_id;
	}
	foreach(variable_get('book_issue'.$user->uid) as $acc_no){
		$books =  db_query(
			"SELECT * from field_data_field_acc_no_ where field_acc_no__value = :acc_no;", array(':acc_no' => $acc_no)
		);
		foreach($books as $book){
			$bk = node_load($book->entity_id);
			$nid = $bk->nid;
			$book_title = $bk->title;
		}
		db_insert($issue_table)
      -> fields(array(
          'issue_no' => $issue_no,
          'acc_no' => $acc_no,
          'user_id' => $form_state['values']['uid'],
          'issue_date' => $issue_date,
					'fine' => 0,
					'status' => 'open',
					'uid' => $uid,
					'timestamp' => time(),
					'issued_by' => $emp_id,
					'issued_by_uid' => $user->uid,
					'nid' => $nid,
					'title' => $book_title,
        )
      )
    ->execute();
		
		$books =  db_query(
			"SELECT * from field_data_field_acc_no_ where field_acc_no__value = :acc_no;", array(':acc_no' => $acc_no)
		);
		foreach($books as $book){
			$bk = node_load($book->entity_id);
			node_object_prepare($bk);
			$bk->field_availability['und'][0]['tid'] = $issued_tid;
			$bk = node_submit($bk);
			node_save($bk);
			$bk = node_load($book->entity_id);
		}
	}
	$issue_no++;
	variable_set('issue_no', $issue_no);
	global $user;
	variable_set('book_issue'.$user->uid, array());
	drupal_set_message('Book/s were issued successfully to '.$form_state['values']['uid'].'.', 'status');
}

/**
 *Implements a function to cancel the current issue.
 */
function cancel_issue($form, &$form_state){
	global $user;
	variable_set('book_issue'.$user->uid, array());
	drupal_set_message('Last transaction was cancelled.', 'status');
}

/**
 *Function to add books to issue list.
 */
function show_book_detail_ajax(&$form, &$form_state){
	return $form['fs'];
}

/**
 *Function to delete books from current list
 */
function delete_this_issue($form, &$form_state){
	return $form['fs'];
}

/**
 *Function that returns user detial
 */
function show_user_detail_ajax($form, &$form_state){
	$session = variable_get('essa_sid');
	$teacher_table = 'essa_'.$session.'_master_staff_table';
	$student_table = 'essa_'.$session.'_master_student_table';
	global $base_url;
	$teachers =  db_query(
		"SELECT * from {$teacher_table} where emp_id = :ei", array(':ei' => $form_state['values']['uid'])
	);
	foreach($teachers as $teacher){
		//dsm($teacher);
	}
	
	$students =  db_query(
		"SELECT * from {$student_table} where adm_no = :an", array(':an' => $form_state['values']['uid']) 
	);
	foreach($students as $student){
		$url = $base_url.'/user/'.$student->uid;
		$form['cnt']['user_detail']['detail'] = array(
			'#type' => 'markup',
			'#markup' => '<a href = "'.$url.'">'.$student->first_name.' '.$student->last_name.'</a>',
		);
	}
	return $form['cnt']['user_detail']['detail'];
}