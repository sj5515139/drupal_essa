<?php
 
/**
 *Implements page callback - leave_page.
 */
function leave_page($form, &$form_state){
	//******SURAJ******//
	$a_uid = array();
	$admin_rid = db_query("SELECT * FROM role WHERE name = 'administrator' OR name = 'Leave Moderator' OR name = 'Principal';");
	foreach($admin_rid as $a_rid){
		$ar = db_query("SELECT * FROM users_roles WHERE rid = :rid;", array(':rid' => $a_rid->rid));
		foreach($ar as $u){
			$a_uid[] = $u->uid;
		}
	}
	global $user;
	$flag = 0;
	foreach($a_uid as $au){
		if($au == $user->uid){
			$flag = 1;
		}
	}
	if($flag != 1){
		drupal_goto("admin/staff/leave/apply_leave");
	}else{
		$session_id = (string)variable_get('essa_sid');
		$leave_table = 'essa_'.$session_id.'_leave_types';
		
		db_merge($leave_table)
			->key(array('leave_id' => 'SL'))
			->fields (array(
				'leave_id' => 'SL',
				'leave_name' => 'Special Leave',
				'leave_desc' => 'This is a special leave type. This leave type can be used for special purposes like Materninty Leave or Paternity Leave.',
				'half_day_rule' => (int)2,
			)
		)
		->execute();
		
		db_merge($leave_table)
			->key(array('leave_id' => 'OD'))
			->fields (array(
				'leave_id' => 'OD',
				'leave_name' => 'On Duty',
				'leave_desc' => 'This is a special leave type. It will not be considered as Leave, the employee who applies for OD shall get prior approval from concerned authority.',
				'half_day_rule' => (int)2,
			)
		)
		->execute();
		
		db_merge($leave_table)
			->key(array('leave_id' => 'LWP'))
			->fields (array(
				'leave_id' => 'LWP',
				'leave_name' => 'Leave Without Pay',
				'leave_desc' => 'This leave type can be used in emergency cases, under the type there will be deduction of salary. So, Please choose carefully.',
				'half_day_rule' => (int)2,
			)
		)
		->execute();
		
		$form['help'] = array(
			'#type' => 'markup',
			'#markup' => '<p>NOTE: If "max no. of days/month" is 0, it means no rule applies to it & employee can apply for any number of day\'s leave.</p>'
		);
		
		$x = '<i class = "fa fa-pencil"></i>';
		$leaves = db_query("
			SELECT * from {$leave_table};
		");
		foreach($leaves as $leave){
			$post_name = NULL;
			if($leave->post_id != NULL){
				$post = dnp_term_load($leave->post_id);
				$post_name = $post->name;
			}
			
			if($leave->leave_id == 'OD' || $leave->leave_id == 'SL' || $leave->leave_id == 'LWP'){
				$row[] = array(
					'#tree' =>TRUE,
					$leave -> leave_id => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $leave -> leave_id .'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$leave -> leave_name.'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$post_name.'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$leave -> nod_per_year.'</h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$leave -> max_per_month.'</h3>',
						),
						'c7' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$leave -> half_day_rule.'</h3>',
						),
						'c8' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.l($x, 'admin/staff/leave/settings/'.$leave->leave_id, array('html' => TRUE)).'</h3>',
						),
						$leave -> leave_id =>array(
							'#type' => 'markup',
							'#markup' => '<h3></h3>',
						),
					),
				);
				
			}else{
				$row[] = array(
					'#tree' =>TRUE,
					$leave -> leave_id => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $leave -> leave_id .'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$leave -> leave_name.'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$post_name.'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$leave -> nod_per_year.'</h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$leave -> max_per_month.'</h3>',
						),
						'c7' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$leave -> half_day_rule.'</h3>',
						),
						'c8' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.l($x, 'admin/staff/leave/settings/'.$leave->leave_id, array('html' => TRUE)).'</h3>',
						),
						$leave -> leave_id =>array(
							'#type' => 'submit',
							'#submit' => array('delete_leave_type'),
							'#value' => 'Delete ',
							'#name' => $leave->leave_id,
							'#prefix' => '<div id = "delete_leave">',
							'#suffix' => '</div>',
						),
					),
				);
				
			}
		}
		
		if(!isset($row)){
			drupal_set_message('There are no Leaves creates yet. Please create Leaves.', $type = 'error');
			$row = array();
		}
		//Calling the theme function to build the custom table and display the form in tabular format.
		$form['lts'] = array(
			'#theme' => 'leave_type_table',
			'rows' => $row,
		);
	}
	//******SURAJ******//
	
	
  return $form;
}

function delete_leave_type($form, &$form_state){
	variable_set('del_leave_id', $form_state['triggering_element']['#name']);
	
	$url = url('delete-leave', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
}

function delete_leave_pagecallback(){
	return drupal_get_form('delete_leave_confirm');
}

function delete_leave_confirm($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leave_id = variable_get('del_leave_id');
	
	$heading = t('Delete Leave - '.$leave_id);
	$caption = '<h3>This action can\'t be undone.</h3>';
	
	$cancel_path = 'admin/staff/leave/settings';
	$yes = t('Delete Leave');
	$no = t('Cancel');
	return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

function delete_leave_confirm_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$leave_table = 'essa_'.$session_id.'_leave_types';
	$leave_staff_table = 'essa_'.$session_id.'_leave_staff';
	
	$leave_id = variable_get('del_leave_id');
	$leaves = db_query("
    SELECT * from {$leave_table} where leave_id = :lid;", array(':lid' => $leave_id)
  );
	foreach($leaves as $leave){
		if($leave->post_id != NULL && $leave->leave_type != NULL){
			$staffs = db_query("
			  SELECT * from {$leave_staff_table} where leave_id = :lid and total_leave = :tl;", array(':lid' => $leave->leave_type, ':tl' => $leave->nod_per_year)
			);
			foreach($staffs as $staff){
				$total_leaves = db_query("
				  SELECT * from {$leave_table} where leave_id = :lid;", array(':lid' => $leave->leave_type)
				);
				foreach($total_leaves as $tl){
					$new_tl = $tl->nod_per_year;
				}
				$new_leave_remaining = $new_tl - $staff->leave_taken;
				db_update($leave_staff_table)
					->fields(array(
						'total_leave' => $new_tl,
						'leave_remaining' => $new_leave_remaining,	
						))
					->condition(db_and()
					  ->condition('leave_id', $leave->leave_type)
						->condition('total_leave', $leave->nod_per_year)
					)
					->execute();
			}
		}
		
		if($leave->post_id != NULL && $leave->leave_type == NULL){
			$staffs = db_query("
			  SELECT * from {$leave_staff_table} where leave_id = :lid;", array(':lid' => $leave->leave_id)
			);
			foreach($staffs as $staff){
				db_update($leave_staff_table)
					->fields(array(
						'leave_status' => '0',	
						))
					->condition('leave_id', $leave->leave_id)
					->execute();
			}
		}
		
		if($leave->post_id == NULL){
			$staffs = db_query("
			  SELECT * from {$leave_staff_table} where leave_id = :lid and total_leave = :tl;", array(':lid' => $leave->leave_id, ':tl' => $leave->nod_per_year)
			);
			foreach($staffs as $staff){
				dsm($staff);
				$total_leaves = db_query("
				  SELECT * from {$leave_table} where leave_id = :lid;", array(':lid' => $leave->leave_id)
				);
				foreach($total_leaves as $tl){
					$new_tl = $tl->nod_per_year;
				}
				$new_leave_remaining = $new_tl - $staff->leave_taken;
				db_update($leave_staff_table)
					->fields(array(
						'leave_status' => '0',	
					))
					->condition(db_and()
					  ->condition('leave_id', $leave->leave_id)
						->condition('total_leave', $leave->nod_per_year)
					)
					->execute();
			}
		}
	}
	db_delete($leave_table)
		->condition('leave_id', $leave_id)
		->execute();
	
	$url = url('admin/staff/leave/settings', array('absolute' => TRUE));
  $form_state['redirect'] = $url;
	drupal_flush_all_caches();
}

/**
 *Theme function
 */
function theme_leave_type_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Leave ID'),t('Leave Name'), t('Post'), t('Days/year'), t('Max Days/month'),t('Half Day'),t(''),t(''));
  
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