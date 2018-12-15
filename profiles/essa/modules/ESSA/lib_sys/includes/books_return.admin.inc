<?php
/**
 *Implements page callback function - books_issue.
 */
function books_return($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$issue_table = 'essa_'.$session_id.'_lib_issue';
	
	$form['cnt']['uid'] = array(
		'#title' => 'Adm. no./Emp. ID',
		'#type' => 'textfield',
		'#autocomplete_path' => 'uid/autocomplete',
		'#size' => 30,
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'issue_detail_ajax',
      'wrapper' => 'issue_detail',
      'method' => 'replace',
      'effect' => 'fade',
    ),
	);
	
	$format = 'd-m-Y';
	$def_dt = date('d-m-Y');
	$form['return_date'] = array(
		'#type' => 'date_select',
		'#title' => t('Return Date'),
		'#default_value' => $def_dt, 
		'#date_format' => $format,
		'#date_year_range' => '0:+1',
		'#date_label_position' => 'within',
		'#required' => TRUE,
		'#validated' => TRUE,
	);
	
	$form['fs'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "issue_detail">',
		'#suffix' => '</div>',
	);
	if(!empty($form_state['values']['uid'])){
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
				$bk = node_load($book->entity_id);
				$title = $bk->title;
				$author = $bk->field_author1['und'][0]['value'];
			}
			$row[$ib->acc_no] = array(
				'#tree' =>TRUE,
				$ib->acc_no => array(  //Generating unique array id for every form element 
					'c1' =>array(
				    '#type' => 'checkbox',
						'#default_value' => 1,
					),
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
			
			$fine = variable_get('lib_fine_per_book');
			$issue_period = variable_get('lib_issue_period');
			$issue_date = date('Y-m-d', $issue_dat);
			$NewDate=date('Y-m-d', strtotime($issue_date. ' + '.$issue_period.' days'));
			if(strtotime($NewDate) < time()){
				$fine_days = time()-strtotime($NewDate);
				$no_of_days = floor($fine_days / (60 * 60 * 24));
				$fine_amt = $no_of_days*$fine;
			}	
			global $base_url;
			$url = $base_url.'/admin/library/fine/collection';
			if($no_of_days > 0){
				$form['fs']['msg'] = array(
					'#type' => 'markup',
					'#markup' => '<h3 style = "color:red;">The book '.$acc_no.' is returned after '.$no_of_days.' days of issued period. Click <a href = "'.$url.'" target = "blank">here</a> to collect fine for the amount of Rs. '.$fine_amt.'.</h3>',
				);
				//drupal_set_message('The book '.$key.' is returned after '.$no_of_days.' days of issued period. Click <a href = "'.$url.'" target = "blank">here</a> to collect fine for the amount of Rs. '.$fine_amt.'.', 'status');
			}else{
				$return_dt = $form_state['values']['return_date']['day'].'-'.$form_state['values']['return_date']['month'].'-'.$form_state['values']['return_date']['year'];
				
				$days = strtotime($return_dt) - strtotime($issue_date);
				$days = floor($days / (60 * 60 * 24));
				$form['fs']['msg'] = array(
					'#type' => 'markup',
					'#markup' => '<h3 style = "color:green;">The book '.$acc_no.' is returned after '.$days.' days of issued date.</h3>',
				);
			}
			
		}
		if(isset($row)){
			
			$form['fs']['tab'] = array(
				'#theme' => 'book_return_table',
				'rows' => $row,
			);
			$form['fs']['save'] = array(
				'#type' => 'submit',
				'#value' => 'Return',
			);
		}else{
			$form['fs']['msg'] = array(
				'#type' => 'markup',
				'#markup' => '<h3 style = "color:red;">There are no books to return along this student.</h3>',
			);
		}
	}
	return $form;
}

/**
 *Implements submit function - books_issue.
 */
function books_return_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$issue_table = 'essa_'.$session_id.'_lib_issue';
	$fine = variable_get('lib_fine_per_book');
	$issue_period = variable_get('lib_issue_period');
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
	
	
	
	$return_dt = $form_state['values']['return_date']['day'].'-'.$form_state['values']['return_date']['month'].'-'.$form_state['values']['return_date']['year'];
	$return_date = strtotime($return_dt);
	
	$issued_books =  db_query(
		"SELECT * from $issue_table where status = 'open' and user_id = :ui;", array(':ui' => $form_state['values']['uid'])
	);
	foreach($issued_books as $ib){
		$books[] = $ib->acc_no;
	}
	
	foreach($form_state['values'] as $key=>$value){
		if(in_array($key, $books)){
			if($value[$key]['c1'] == 1){
				$this_book = db_query(
					"SELECT * from $issue_table where acc_no = :ai  and user_id = :ui;", array(':ai' => $key, ':ui' => $form_state['values']['uid'])
				);
				foreach($this_book as $ib){
					$issue_no = $ib->issue_no;
				}		
				db_update($issue_table) // Table name no longer needs {}
          ->fields(array(
							'return_no' => 'r-'.$issue_no,
							'return_date' => $return_date,
							'status' => 'closed'
						))
        ->condition('issue_no', $issue_no, '=')
        ->execute();
				
				$iss_books =  db_query(
					"SELECT * from field_data_field_acc_no_ where field_acc_no__value = :acc_no;", array(':acc_no' => $key)
				);
				foreach($iss_books as $book){
					$bk = node_load($book->entity_id);
					node_object_prepare($bk);
					$bk->field_availability['und'][0]['tid'] = $available_tid;
					$bk = node_submit($bk);
					node_save($bk);
					$bk = node_load($book->entity_id);
				}
			}
		}
	}
	drupal_set_message('Book/s were returned successfully.', 'status');
}

function issue_detail_ajax($form, &$form_state){
	return $form['fs'];
}