<?php

//--------------------------------------------------------------------ACADEMICS---------------------------------------------------------------------
function allocate_academics($form, &$form_state){
  $form = array();
  
  $voc = 'organisation_structure_academics';
  $vocabulary = dnp_vocabulary_machine_name_load($voc);
  
  $dnp = dnp_get_tree($vocabulary->vid);
  //dsm($dnp);
  
  $session = variable_get('essa_sid');
	$staff_table = 'essa_'.$session.'_master_staff_table';
  $staff_dept_table = 'essa_'.$session.'_staff_dept_academics';
  $staff_dept_db = db_query(
    "SELECT * from {$staff_dept_table}"
  );
  foreach($staff_dept_db as $sd){
    $staff_db = db_query(
    	"SELECT * from {$staff_table} where emp_id = :emp_id",  array(':emp_id' => $sd->emp_id)
    );
    foreach($staff_db as $staff){
      $default[$sd->dept_id.'_'.$sd->post_id] = $staff->fname.' '.$staff->lname.' ('.$staff->nickname.')';
    }
  }
	
	
	//******SURAJ******//
	$a_uid = array();
	$admin_rid = db_query("SELECT * FROM role WHERE name = 'administrator';");
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
		foreach($dnp as $d){
			$parent = dnp_get_parents($d->tid);
			foreach($parent as $depts){
				if($depts->type != "Post"){
					$dept = $depts->name;
					$dept_id = $depts->tid;
				}
			}
			if($d->type == "Post"){
				$row[$dept_id.'_'.$d->tid] = array(
					'#tree' =>TRUE,
					$d->tid => array(
						'c1' => array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$dept.'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$d -> name.'</h3>',
						),
						'c3' =>array(
							'#type' => 'textfield',
							'#default_value' => isset($default[$dept_id.'_'.$d->tid])?$default[$dept_id.'_'.$d->tid]:NULL,
							'#autocomplete_path' => 'teachers/autocomplete',
							'#size' => 25,
							'#disabled' =>TRUE,
						),
					),
				);
			}
		}
		$form['posts'] = array(
			'#theme' => 'dnp_academics_table',
			'rows' => $row,
		);
	}else{
		foreach($dnp as $d){
			$parent = dnp_get_parents($d->tid);
			foreach($parent as $depts){
				if($depts->type != "Post"){
					$dept = $depts->name;
					$dept_id = $depts->tid;
				}
			}
			if($d->type == "Post"){
				$row[$dept_id.'_'.$d->tid] = array(
					'#tree' =>TRUE,
					$d->tid => array(
						'c1' => array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$dept.'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$d -> name.'</h3>',
						),
						'c3' =>array(
							'#type' => 'textfield',
							'#default_value' => isset($default[$dept_id.'_'.$d->tid])?$default[$dept_id.'_'.$d->tid]:NULL,
							'#autocomplete_path' => 'teachers/autocomplete',
							'#size' => 25,
						),
					),
				);
			}
		}
		$form['posts'] = array(
			'#theme' => 'dnp_academics_table',
			'rows' => $row,
		);
		$form['save'] = array(
			'#type' => 'submit',
			'#value' => 'Save',
		);
	}
	//******SURAJ******//
  
  if(!isset($row)){
    drupal_set_message('There are no Departments and Post Configured. Please create them in "Home » Administration » Structure » Departments and Posts".', $type = 'error');
    $row = array();
  }
  //Calling the theme function to build the custom table and display the form in tabular format.
  return $form;
}

//******Suraj*****//
/**
 *Implements valiadte function allocate_academics_validate.
 */

function allocate_academics_validate($form, &$form_state){
	$session = variable_get('essa_sid');
	$staff_table = 'essa_'.$session.'_master_staff_table';
	$staff_list = db_query("SELECT * FROM {$staff_table}");
	$staffs = array();
	foreach($staff_list as $st_list){
		$staffs[] = $st_list->fname.' '.$st_list->lname.' ('.$st_list->nickname.')';
	}
	foreach($form_state['values'] as $key => $val){
		$dept_tid = explode('_', $key);
		if(is_array($val)){
			if($val[$dept_tid[1]]['c3'] != ''){
				if(!in_array($val[$dept_tid[1]]['c3'], $staffs)){
					form_set_error($val[$dept_tid[1]]['c3'],'Employee "'.$val[$dept_tid[1]]['c3'].'" is not present in the system.');
				}
			}
		}
	}
}
//******Suraj*****//


/**
 *Implements submit function allocate_academics_submit.
 */
function allocate_academics_submit($form, &$form_state){
	$form_state['rebuild'] = TRUE;
  $session = variable_get('essa_sid');
	$staff_table = 'essa_'.$session.'_master_staff_table';
  $staff_dept_table = 'essa_'.$session.'_staff_dept_academics';
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	global $base_url;
	global $user;
	
  foreach($form_state['values'] as $key => $val){
    if(is_array($val)){
      $id = NULL;
      $emp_id = '';
      $dept = '';
      $post = '';
      $dept_tid = explode('_', $key);
			
			if($val[$dept_tid[1]]['c3'] != ''){
				preg_match('#\((.*?)\)#', $val[$dept_tid[1]]['c3'], $match);
				$staff_db = db_query(
					"SELECT * from {$staff_table} where nickname = :nickname",  array(':nickname' => $match[1])
				);
				foreach($staff_db as $staff){
					$emp_id = $staff->emp_id;
					$uid = $staff->uid;
				}
				$dept = dnp_term_load($dept_tid[0]);
				$post = dnp_term_load($dept_tid[1]);
				
				$staff_dept_db = db_query(
					"SELECT * from {$staff_dept_table} where dept_id = :dept_id and post_id = :post_id",  array(':dept_id' => $dept_tid[0], ':post_id' => $dept_tid[1])
				);
				$emp = array();
				foreach($staff_dept_db as $sd){
				  $id = $sd->id;
					$emp[] = $sd->emp_id;
				}
				
				//******Suraj*****//
				
				global $base_url;
				global $user;
				
				if(!in_array($emp_id, $emp)){
					
					//sending system alert
					$created_date = date("Y-m-d H:i:s");
					$strtodate = strtotime($created_date);
					db_insert($sys_alert_table)
					->fields(array(
					'message' => $emp_id.' has been appointed as '.$post->name.', from '.$created_date.'.',
					'priority' => 'M',
					'module' => 'school_master',
					'source_url' => 'admin/settings/organisation_structure/allocate_academics',
					'timestamp' => $strtodate,
					'source_uid' => $user->uid,
					))
					->execute();
					
					//sending message
					$module = 'school_master';
					$recipients= array();
					$recipients[] = user_load($uid);
					$msg_subject = 'Appointment letter';
					$msg_body = 'We are pleased to inform that, you have been appointed as '.$post->name.', as on '.$created_date.'. Please find your appointment letter <a href = "#"><u>here</u></a>.<br><br> To Know your new salary structure click <a href ="#"><u>here</u></a>';
					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
					$msg_body = $msg_body.' <br>'.$footer;
					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
				}
				//******Suraj*****//
				
				if($emp_id != ''){
					$role = db_query(
						"SELECT * from role where name = :name",  array(':name' => $post->name)
					);
					foreach($role as $r){
						$rid = $r->rid;
					}
					$staff_dept_db = db_query(
						"SELECT * from {$staff_dept_table} where dept_id = :di", array(':di' => $dept_tid[0])
					);
					foreach($staff_dept_db as $sd){
						if($sd->emp_id != $emp_id){
							$emp_data = db_query("SELECT * FROM {$staff_table} WHERE emp_id = :emp;", array(':emp' => $sd->emp_id));
							foreach($emp_data as $ed){
								$n_emp_uid = $ed->uid;
							}
							db_delete('users_roles')
								->condition(db_and()
								->condition('uid',$n_emp_uid,'=')
								->condition('rid',$rid,'='))
								->execute();
						}
					}
				  db_merge($staff_dept_table)
				  	->key(array('id' => isset($id)? $id: NULL))
				  	->fields (array(
				      'emp_id' => $emp_id,
				      'dept_id' => $dept_tid[0],
				      'dept_name' => $dept->name,
				      'post_id' => $dept_tid[1],
				      'post_name' => $post->name,
				  	)
				  )
				  ->execute();
				}
				user_multiple_role_edit(array($uid), 'add_role', $rid);
				
			}else{//******Suraj******//
				$n_emp_id = NULL;
				$dept = dnp_term_load($dept_tid[0]);
				$post = dnp_term_load($dept_tid[1]);
				
				$new_data = db_query("SELECT * FROM {$staff_dept_table} WHERE dept_id = :dept_id and post_id = :post_id",  array(':dept_id' => $dept_tid[0], ':post_id' => $dept_tid[1]));
				foreach($new_data as $n_data){
					$n_emp_id = $n_data->emp_id;
				}
				
				$emp_data = db_query("SELECT * FROM {$staff_table} WHERE emp_id = :emp;", array(':emp' => $n_emp_id));
				foreach($emp_data as $ed){
					$n_emp_name = $ed->fname.' '.$ed->lname.'('.$ed->nickname.')';
					$n_emp_uid = $ed->uid;
				}
				
				if($n_emp_id != NULL){
					db_delete($staff_dept_table)
					->condition(db_and()
					->condition('dept_id',$dept_tid[0],'=')
					->condition('post_id',$dept_tid[1],'='))
					->execute();
					
					$role = db_query(
						"SELECT * from role where name = :name",  array(':name' => $post->name)
					);
					foreach($role as $r){
						$rid = $r->rid;
					}
					db_delete('users_roles')
					->condition(db_and()
					->condition('uid',$n_emp_uid,'=')
					->condition('rid',$rid,'='))
					->execute();
					
					//user_multiple_role_edit(array($n_emp_uid), 'delete_role', $rid);
					
					global $base_url;
					global $user;
					//sending system alert
					$created_date = date("Y-m-d H:i:s");
					$strtodate = strtotime($created_date);
					db_insert($sys_alert_table)
					->fields(array(
					'message' => $n_emp_id.'-'.$n_emp_name.' has been discountinued as '.$post->name.', from '.$created_date.'.',
					'priority' => 'M',
					'module' => 'school_master',
					'source_url' => 'admin/settings/organisation_structure/allocate_academics',
					'timestamp' => $strtodate,
					'source_uid' => $user->uid,
					))
					->execute();
					
					//sending message
					$module = 'school_master';
					$recipients= array();
					$recipients[] = user_load($n_emp_uid);
					$msg_subject = 'Post dis-continuation Letter';
					$msg_body = 'It is our painful duty to inform you that, your service as '.$post->name.' has been discontinued as on '.$created_date.'. Please find the revised salary structure <a href ="#"><u>here</u></a>.';
					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
					$msg_body = $msg_body.' <br>'.$footer;
					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
				}
				//******Suraj******//
			}
    }
  }
  drupal_set_message('Department & Posts have been successfully alloted.');
}

/**
 *Theme function
 */
function theme_dnp_academics_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	
	
	//******SURAJ******//
	$a_uid = array();
	$admin_rid = db_query("SELECT * FROM role WHERE name = 'administrator';");
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
		 $header = array(t('Department'), t('Post'),t('Allocated Staff'));
	}else{
		 $header = array(t('Department'), t('Post'),t('Select a Staff'));
	}
	//******SURAJ******//
  
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

//-------------------------------------------------------------------------ADMIN---------------------------------------------------------------------
//-------------------------------------------------------------------------ADMIN---------------------------------------------------------------------
//-------------------------------------------------------------------------ADMIN---------------------------------------------------------------------
//-------------------------------------------------------------------------ADMIN---------------------------------------------------------------------
//-------------------------------------------------------------------------ADMIN---------------------------------------------------------------------
function allocate_admin($form, &$form_state){
  $form = array();
  
  $voc = 'organisation_structure_admin';
  $vocabulary = dnp_vocabulary_machine_name_load($voc);
  
  $dnp = dnp_get_tree($vocabulary->vid);
  $session = variable_get('essa_sid');
	$staff_table = 'essa_'.$session.'_master_staff_table';
  $staff_dept_table = 'essa_'.$session.'_staff_dept_admin';
  $staff_dept_db = db_query(
    "SELECT * from {$staff_dept_table}"
  );
  foreach($staff_dept_db as $sd){
    $staff_db = db_query(
    	"SELECT * from {$staff_table} where emp_id = :emp_id",  array(':emp_id' => $sd->emp_id)
    );
    foreach($staff_db as $staff){
      $default[$sd->dept_id.'_'.$sd->post_id] = $staff->fname.' '.$staff->lname.' ('.$staff->emp_id.')';
    }
  }
	
	//******SURAJ******//
	$a_uid = array();
	$admin_rid = db_query("SELECT * FROM role WHERE name = 'administrator';");
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
		foreach($dnp as $d){
			$parent = dnp_get_parents($d->tid);
			foreach($parent as $depts){
				if($depts->type != "Post"){
					$dept = $depts->name;
					$dept_id = $depts->tid;
				}
			}
			if($d->type == "Post"){
				$row[$dept_id.'_'.$d->tid] = array(
					'#tree' =>TRUE,
					$d->tid => array(
						'c1' => array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$dept.'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$d -> name.'</h3>',
						),
						'c3' =>array(
							'#type' => 'textfield',
							'#default_value' => isset($default[$dept_id.'_'.$d->tid])?$default[$dept_id.'_'.$d->tid]:NULL,
							'#autocomplete_path' => 'staff/autocomplete',
							'#size' => 25,
							'#disabled' => TRUE,
						),
					),
				);
			}
		}
		$form['posts'] = array(
			'#theme' => 'dnp_academics_table',
			'rows' => $row,
		);
	}else{
		foreach($dnp as $d){
			$parent = dnp_get_parents($d->tid);
			foreach($parent as $depts){
				if($depts->type != "Post"){
					$dept = $depts->name;
					$dept_id = $depts->tid;
				}
			}
			if($d->type == "Post"){
				$row[$dept_id.'_'.$d->tid] = array(
					'#tree' =>TRUE,
					$d->tid => array(
						'c1' => array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$dept.'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$d -> name.'</h3>',
						),
						'c3' =>array(
							'#type' => 'textfield',
							'#default_value' => isset($default[$dept_id.'_'.$d->tid])?$default[$dept_id.'_'.$d->tid]:NULL,
							'#autocomplete_path' => 'staff/autocomplete',
							'#size' => 25,
						),
					),
				);
			}
		}
		$form['posts'] = array(
			'#theme' => 'dnp_academics_table',
			'rows' => $row,
		);
		$form['save'] = array(
			'#type' => 'submit',
			'#value' => 'Save',
		);
	}
	//******SURAJ******//
	
  
  if(!isset($row)){
    drupal_set_message('There are no Departments and Post Configured. Please create them in "Home » Administration » Structure » Departments and Posts".', $type = 'error');
    $row = array();
  }
  //Calling the theme function to build the custom table and display the form in tabular format.
  return $form;
}

//******Suraj*****//

/**
 *Implements valiadte function allocate_admin_validate.
 */

function allocate_admin_validate($form, &$form_state){
	$session = variable_get('essa_sid');
	$staff_table = 'essa_'.$session.'_master_staff_table';
	$staff_list = db_query("SELECT * FROM {$staff_table}");
	$staffs = array();
	foreach($staff_list as $st_list){
		$staffs[] = $st_list->fname.' '.$st_list->lname.' ('.$st_list->emp_id.')';
	}
	foreach($form_state['values'] as $key => $val){
		$dept_tid = explode('_', $key);
		if(is_array($val)){
			if($val[$dept_tid[1]]['c3'] != ''){
				if(!in_array($val[$dept_tid[1]]['c3'], $staffs)){
					form_set_error($val[$dept_tid[1]]['c3'],'Employee "'.$val[$dept_tid[1]]['c3'].'" is not present in the system.');
				}
			}
		}
	}
}
//******Suraj*****//

/**
 *Implements submit function allocate_academics_submit.
 */
function allocate_admin_submit($form, &$form_state){
  $form_state['rebuild'] = TRUE;
  $session = variable_get('essa_sid');
	$staff_table = 'essa_'.$session.'_master_staff_table';
  $staff_dept_table = 'essa_'.$session.'_staff_dept_admin';
	$sys_alert_table = 'essa_'.$session.'_system_alert';
  foreach($form_state['values'] as $key => $val){
    if(is_array($val)){
      $id = NULL;
      $emp_id = '';
      $dept = '';
      $post = '';
      $dept_tid = explode('_', $key);
			if($val[$dept_tid[1]]['c3'] != ''){
				preg_match('#\((.*?)\)#', $val[$dept_tid[1]]['c3'], $match);
				$staff_db = db_query(
					"SELECT * from {$staff_table} where emp_id = :id",  array(':id' => $match[1])
				);
				foreach($staff_db as $staff){
					$emp_id = $staff->emp_id;
					$uid = $staff->uid;
				}
				$dept = dnp_term_load($dept_tid[0]);
				$post = dnp_term_load($dept_tid[1]);
				
				$staff_dept_db = db_query(
					"SELECT * from {$staff_dept_table} where dept_id = :dept_id and post_id = :post_id",  array(':dept_id' => $dept_tid[0], ':post_id' => $dept_tid[1])
				);
				$emp = array();
				foreach($staff_dept_db as $sd){
				  $id = $sd->id;
					$emp[] = $sd->emp_id;
				}
				
				//******Suraj*****//
				
				global $base_url;
				global $user;
				if(!in_array($emp_id, $emp)){
					//sending system alert
						$created_date = date("Y-m-d H:i:s");
						$strtodate = strtotime($created_date);
						db_insert($sys_alert_table)
						->fields(array(
						'message' => $emp_id.' has been appointed as '.$post->name.', from '.$created_date.'.',
						'priority' => 'M',
						'module' => 'school_master',
						'source_url' => 'admin/settings/organisation_structure/allocate_academics',
						'timestamp' => $strtodate,
						'source_uid' => $user->uid,
					))
					->execute();
					
					//sending message
					$module = 'school_master';
					$recipients= array();
					$recipients[] = user_load($uid);
					$msg_subject = 'Appointment letter';
					$msg_body = 'We are pleased to inform that, you have been appointed as '.$post->name.', as on '.$created_date.'. Please find your appointment letter <a href = "#"><u>here</u></a>.<br><br> To Know your new salary structure click <a href ="#"><u>here</u></a>';
					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
					$msg_body = $msg_body.' <br>'.$footer;
					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
				}
				
				//******Suraj*****//
				
				if($emp_id != ''){
					$role = db_query(
						"SELECT * from role where name = :name",  array(':name' => $post->name)
					);
					foreach($role as $r){
						$rid = $r->rid;
					}
					$staff_dept_db = db_query(
						"SELECT * from {$staff_dept_table} where dept_id = :di", array(':di' => $dept_tid[0])
					);
					foreach($staff_dept_db as $sd){
						if($sd->emp_id != $emp_id){
							$emp_data = db_query("SELECT * FROM {$staff_table} WHERE emp_id = :emp;", array(':emp' => $sd->emp_id));
							foreach($emp_data as $ed){
								$n_emp_uid = $ed->uid;
							}
							db_delete('users_roles')
								->condition(db_and()
								->condition('uid',$n_emp_uid,'=')
								->condition('rid',$rid,'='))
								->execute();
						}
					}
				  db_merge($staff_dept_table)
				  	->key(array('id' => isset($id)? $id: NULL))
				  	->fields (array(
				      'emp_id' => $emp_id,
				      'dept_id' => $dept_tid[0],
				      'dept_name' => $dept->name,
				      'post_id' => $dept_tid[1],
				      'post_name' => $post->name,
				  	)
				  )
				  ->execute();
				}
				$role = db_query(
					"SELECT * from role where name = :name",  array(':name' => $post->name)
				);
				foreach($role as $r){
					$rid = $r->rid;
				}
				user_multiple_role_edit(array($uid), 'add_role', $rid);
			}else{//******Suraj******//
				$n_emp_id = NULL;
				$dept = dnp_term_load($dept_tid[0]);
				$post = dnp_term_load($dept_tid[1]);
				
				$new_data = db_query("SELECT * FROM {$staff_dept_table} WHERE dept_id = :dept_id and post_id = :post_id",  array(':dept_id' => $dept_tid[0], ':post_id' => $dept_tid[1]));
				foreach($new_data as $n_data){
					$n_emp_id = $n_data->emp_id;
				}
				
				$emp_data = db_query("SELECT * FROM {$staff_table} WHERE emp_id = :emp;", array(':emp' => $n_emp_id));
				foreach($emp_data as $ed){
					$n_emp_name = $ed->fname.' '.$ed->lname.'('.$ed->nickname.')';
					$n_emp_uid = $ed->uid;
				}
				
				if($n_emp_id != NULL){
					db_delete($staff_dept_table)
					->condition(db_and()
					->condition('dept_id',$dept_tid[0],'=')
					->condition('post_id',$dept_tid[1],'='))
					->execute();
					
					$role = db_query(
						"SELECT * from role where name = :name",  array(':name' => $post->name)
					);
					foreach($role as $r){
						$rid = $r->rid;
					}
					db_delete('users_roles')
					->condition(db_and()
					->condition('uid',$n_emp_uid,'=')
					->condition('rid',$rid,'='))
					->execute();
					
					//user_multiple_role_edit(array($n_emp_uid), 'delete_role', $rid);
					
					global $base_url;
					global $user;
					//sending system alert
					$created_date = date("Y-m-d H:i:s");
					$strtodate = strtotime($created_date);
					db_insert($sys_alert_table)
					->fields(array(
					'message' => $n_emp_id.'-'.$n_emp_name.' has been discountinued as '.$post->name.', from '.$created_date.'.',
					'priority' => 'M',
					'module' => 'school_master',
					'source_url' => 'admin/settings/organisation_structure/allocate_academics',
					'timestamp' => $strtodate,
					'source_uid' => $user->uid,
					))
					->execute();
					
					//sending message
					$module = 'school_master';
					$recipients= array();
					$recipients[] = user_load($n_emp_uid);
					$msg_subject = 'Post dis-continuation Letter';
					$msg_body = 'It is our painful duty to inform you that, your service as '.$post->name.' has been discontinued as on '.$created_date.'. Please find the revised salary structure <a href ="#"><u>here</u></a>.';
					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
					$msg_body = $msg_body.' <br>'.$footer;
					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
				}
				//******Suraj******//
			}
    }
  }
  drupal_set_message('Department & Posts have been successfully alloted');
}

/**
 *Theme function
 */
function theme_dnp_admin_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
 
	//******SURAJ******//
	$a_uid = array();
	$admin_rid = db_query("SELECT * FROM role WHERE name = 'administrator';");
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
		 $header = array(t('Department'), t('Post'),t('Allocated Staff'));
	}else{
		 $header = array(t('Department'), t('Post'),t('Select a Staff'));
	}
	//******SURAJ******//
  
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