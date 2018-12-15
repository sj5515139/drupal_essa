<?php

/**
 * Implementing the page callback from class_setup.module.
 * Creating the form for http://localhost/essa-dps1/class-section
 */
function class_section($form = array(), &$form_state){
	$session = (string)variable_get('essa_sid');
	$bi_table = 'essa_'.$session.'_basicinfo';

	//creating user- Principal;
	$rid = db_query("select rid from role where name = 'Principal'");
	foreach($rid as $role_id){
		foreach($role_id as $s_role){
			$s_rid = $s_role;
		}
	}
	$flag = 0;
	$users_name = db_query("SELECT * FROM {users} where name = :p;", array(':p' => 'principal'));
	foreach($users_name as $un){
		$flag = 1;
	}

	if($flag == 0){
		$emails = db_query("SELECT * FROM {$bi_table}");
		foreach($emails as $e){
			$email = $e->office_email;
		}
		$edit_student = array(
			'name' => 'principal',
			'pass' => 'principal',
			'mail' => $email,
			'init' => $email,
			'status' => 1,
			'access' => REQUEST_TIME,
			'roles' => array($s_rid => 'Principal'),
		);
		user_save('', $edit_student);
	}

	$roles = db_query(
    "SELECT * from role where name = 'authenticated user';"
  );
	foreach($roles as $role){
		$p_rid = $role->rid;
	}
	user_role_grant_permissions($p_rid, $permissions = array('access administration menu', 'access administration pages',
			'access coffee', 'use text format full_html', 'view keyboard shortcuts', 'access overlay', 'use advanced search'));


	$roles = db_query(
    "SELECT * from role where name = 'School Admin';"
  );
	foreach($roles as $role){
		$p_rid = $role->rid;
	}
	user_role_grant_permissions($p_rid, $permissions = array('access administration menu', 'access administration pages',
			'generate certificates', 'access coffee', 'access filedepot', 'use text format full_html', 'view keyboard shortcuts', 'access overlay',
			'school info', 'administer subject', 'administer transport settings', 'administer optional subjects', 'allocate houses', 'use advanced search',
			'administer students', 'create certificates', 'collect fees', 'administer fees', 'administer class', 'withdraw students', 'view_student_remarks',
			'student_remarks', 'administer shortcuts', 'approve_leave', 'administer_leave', 'administer staffs', 'resign', 'take_staff_attendance',
			'access reports', 'access staffs','apply_leave', 'write privatemsg', 'read privatemsg', 'delete privatemsg', 'use taskbar', 'use taskbar alert'));

	$roles = db_query(
    "SELECT * from role where name = 'Principal';"
  );
	foreach($roles as $role){
		$p_rid = $role->rid;
	}
	user_role_grant_permissions($p_rid, $permissions = array('access administration menu', 'access administration pages',
			'generate certificates', 'access coffee', 'access filedepot', 'use text format full_html', 'view keyboard shortcuts', 'access overlay',
			'school info', 'administer subject', 'administer transport settings', 'administer optional subjects', 'allocate houses', 'use advanced search',
			'administer students', 'create certificates', 'collect fees', 'administer fees', 'administer class', 'withdraw students', 'view_student_remarks',
			'student_remarks', 'administer shortcuts', 'approve_leave', 'administer_leave', 'administer staffs', 'resign', 'take_staff_attendance',
			'access reports', 'access staffs','apply_leave', 'write privatemsg', 'read privatemsg', 'delete privatemsg', 'use taskbar', 'use taskbar alert'));


	$roles = db_query(
    "SELECT * from role where name = 'Staff';"
  );
	foreach($roles as $role){
		$p_rid = $role->rid;
	}
	user_role_grant_permissions($p_rid, $permissions = array('access administration menu', 'access administration pages',
			'access coffee', 'access filedepot', 'use text format full_html', 'view keyboard shortcuts', 'access overlay', 'use advanced search',
			'administer shortcuts', 'resign','apply_leave', 'write privatemsg', 'read privatemsg', 'delete privatemsg', 'use taskbar', 'use taskbar alert'));
	//creating permission for principal;

	$roles = db_query(
    "SELECT * from role where name = 'Teacher';"
  );
	foreach($roles as $role){
		$p_rid = $role->rid;
	}
	user_role_grant_permissions($p_rid, $permissions = array('access students', 'student_remarks', 'view_student_remarks'));

	$roles = db_query(
    "SELECT * from role where name = 'Class Teacher';"
  );
	foreach($roles as $role){
		$p_rid = $role->rid;
	}
	user_role_grant_permissions($p_rid, $permissions = array('create bulletin content', 'delete own bulletin content', 'edit own bulletin content',
			'administer subject', 'administer optional subjects', 'allocate houses','take_attendance'));

	//creating permission for Fees Incharge;
	$roles = db_query(
    "SELECT * from role where name = 'Fees Incharge';"
  );
	foreach($roles as $role){
		$fi_rid = $role->rid;
	}
	user_role_grant_permissions($fi_rid, $permissions = array('access administration menu', 'access administration pages', 'generate certificates', 'access coffee', 'access filedepot', 'use text format full_html', 'view keyboard shortcuts', 'access overlay', 'school info', 'administer subject', 'administer transport settings', 'administer optional subjects', 'allocate houses', 'use advanced search', 'administer students', 'perform backup', 'access backup and migrate', 'restore from backup', 'create certificates', 'administer fees', 'collect fees', 'administer class', 'withdraw students', 'administer shortcuts'));

	//creating permission for Fees Collector;
	$roles = db_query(
    "SELECT * from role where name = 'Fees Collector';"
  );
	foreach($roles as $role){
		$fc_rid = $role->rid;
	}
	user_role_grant_permissions($fc_rid, $permissions = array('access administration menu', 'access administration pages', 'generate certificates', 'access coffee', 'access filedepot', 'use text format full_html', 'view keyboard shortcuts', 'access overlay', 'school info', 'administer subject', 'administer transport settings', 'administer optional subjects', 'allocate houses', 'use advanced search', 'administer students', 'collect fees', 'administer shortcuts'));

	$roles = db_query(
    "SELECT * from role where name = 'Time Table Incharge';"
  );
	foreach($roles as $role){
		$p_rid = $role->rid;
	}
	user_role_grant_permissions($p_rid, $permissions = array('administer time table'));


	$roles = db_query(
    "SELECT * from role where name = 'Student Moderator';"
  );
	foreach($roles as $role){
		$p_rid = $role->rid;
	}
	user_role_grant_permissions($p_rid, $permissions = array('withdraw students', 'administer students', 'access students', 'administer student details'));

	$roles = db_query(
		"SELECT * from role where name = 'Leave Moderator';"
	);
	foreach($roles as $role){
		$p_rid = $role->rid;
	}
	user_role_grant_permissions($p_rid, $permissions = array('approve_leave', 'administer_leave', 'leave_moderator'));

	$roles = db_query(
    "SELECT * from role where name = 'Transport Head';"
  );
	foreach($roles as $role){
		$p_rid = $role->rid;
	}
	user_role_grant_permissions($p_rid, $permissions = array('administer transport settings'));

	$roles = db_query(
    "SELECT * from role where name = 'Payroll Manager';"
  );
	foreach($roles as $role){
		$p_rid = $role->rid;
	}
	user_role_grant_permissions($p_rid, $permissions = array('manage salary', 'administer payroll'));

	$roles = db_query(
		"SELECT * from role where name = 'Attendance Incharge';"
	);
	foreach($roles as $role){
		$p_rid = $role->rid;
	}
	user_role_grant_permissions($p_rid, $permissions = array('take_staff_attendance'));


	$session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	foreach($classes as $class){
		$default[$class->class_id] = $class->no_of_sec;
	}

  $form['help'] = array(
    '#type' => 'markup',
    '#markup' => '<h1> Create sections for each class. </h1>',
  );

  $classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
  //Creating from elements that will be displayed in table format.
  foreach($classes as $class){
    //dsm($class);
    $row[] = array(
      '#tree' =>TRUE,
      $class -> class_id => array(  //Generating unique array id for every form element
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$class -> class_id.'</h3>',
        ),
        'c2' =>array(
          '#type' => 'select',
          '#options' => drupal_map_assoc(array('1','2','3','4','5','6','7','8')),
          '#required' => TRUE,
          '#default_value' => $default[$class->class_id],
        ),
      ),
    );
  }

  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['class'] = array(
    '#theme' => 'class_section_table',
    'rows' => $row,
  );

  //Adding the submit buttons
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 *Ajax callback function the populates the 'Sections Created' column dynamically.
 */
function create_section_ajax($form, &$form_state){

  //using triggering_element to capture the event origin.
  $ch1 = $form_state['triggering_element']['#value'];
  $str = $form_state['triggering_element']['#name'];

  //Getting the (html div id)  to regenerate the form wrapper.
  $div_id = trim($str,"[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16][][c2]");

  //outputting the created_section to appropriate column
  foreach($form_state['values'] as $key => $val){
    if(is_array($val)){
      foreach($val as $key => $val){
        switch($ch1){
          case "1":
            $form['created_section'] = array(
              '#type' => 'markup',
              '#markup' => '<h3>'.$div_id.' - A'.'</h3>',
              '#prefix' => '<div id = '.clean_string($div_id).'>',
              '#suffix' => '</div>',
             );
             break;
          case "2":
            $form['created_section'] = array(
              '#type' => 'markup',
              '#markup' => '<h3>'.$div_id.' - A, '.$div_id.' -  B'.'</h3>',
              '#prefix' => '<div id = '.clean_string($div_id).'>',
              '#suffix' => '</div>',
             );
            break;
          case "3":
            $form['created_section'] = array(
              '#type' => 'markup',
              '#markup' => '<h3>'.$div_id.' - A, '.$div_id.' -  B, '.$div_id.' -  C'.'</h3>',
              '#prefix' => '<div id = '.clean_string($div_id).'>',
              '#suffix' => '</div>',
            );
            break;
          case "4":
            $form['created_section'] = array(
              '#type' => 'markup',
              '#markup' => '<h3>'.$div_id.' - A, '.$div_id.' -  B, '.$div_id.' -  C, '.$div_id.' -  D'.'</h3>',
              '#prefix' => '<div id = '.clean_string($div_id).'>',
              '#suffix' => '</div>',
            );
            break;
          case "5":
            $form['created_section'] = array(
              '#type' => 'markup',
              '#markup' => '<h3>'.$div_id.' - A, '.$div_id.' -  B, '.$div_id.' -  C, '.$div_id.' -  D, '.$div_id.' -  E'.'</h3>',
              '#prefix' => '<div id = '.clean_string($div_id).'>',
              '#suffix' => '</div>',
            );
            break;
					case "6":
            $form['created_section'] = array(
              '#type' => 'markup',
              '#markup' => '<h3>'.$div_id.' - A, '.$div_id.' -  B, '.$div_id.' -  C, '.$div_id.' -  D, '.$div_id.' -  E, '.$div_id.' -  F'.'</h3>',
              '#prefix' => '<div id = '.clean_string($div_id).'>',
              '#suffix' => '</div>',
            );
            break;
					case "7":
            $form['created_section'] = array(
              '#type' => 'markup',
              '#markup' => '<h3>'.$div_id.' - A, '.$div_id.' -  B, '.$div_id.' -  C, '.$div_id.' -  D, '.$div_id.' -  E, '.$div_id.' -  F, '.$div_id.' -  G'.'</h3>',
              '#prefix' => '<div id = '.clean_string($div_id).'>',
              '#suffix' => '</div>',
            );
            break;
					case "8":
            $form['created_section'] = array(
              '#type' => 'markup',
              '#markup' => '<h3>'.$div_id.' - A, '.$div_id.' -  B, '.$div_id.' -  C, '.$div_id.' -  D, '.$div_id.' -  E, '.$div_id.' -  F, '.$div_id.' -  G, '.$div_id.' -  H'.'</h3>',
              '#prefix' => '<div id = '.clean_string($div_id).'>',
              '#suffix' => '</div>',
            );
            break;
        }
      }
    }
  }
  return $form['created_section'];
}

/**
 * Theme callback for the form table.
 */
function theme_class_section_table(&$variables) {
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Name of class'), t('No. of section'));

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
 *SUBMIT FUNCTION
 *Creating a button the traverse the setup wizard. This one goes to the next step i.e. _______________
 *Also saving the data in DB & creating table for each section.
 */
function class_section_submit($form , &$form_state){
  $schema['time_table'] = array(
  'description' => 'TODO: please describe this table!',
  'fields' => array(
    'day_weight' => array(
       'description' => 'TODO: please describe this field!',
       'type' => 'int',
       'length' => '11',
       'not null' => FALSE,
      ),
    'day' => array(
      'description' => 'TODO: please describe this field!',
      'type' => 'varchar',
      'length' => '15',
      'not null' => TRUE,
      'default' => '',
    ),
		'Period1' => array(
      'description' => 'TODO: please describe this field!',
      'type' => 'varchar',
      'length' => '50',
      'not null' => FALSE,
    ),
		'Period2' => array(
      'description' => 'TODO: please describe this field!',
      'type' => 'varchar',
      'length' => '50',
      'not null' => FALSE,
    ),
		'Period3' => array(
      'description' => 'TODO: please describe this field!',
      'type' => 'varchar',
      'length' => '50',
      'not null' => FALSE,
    ),
		'Period4' => array(
      'description' => 'TODO: please describe this field!',
      'type' => 'varchar',
      'length' => '50',
      'not null' => FALSE,
    ),
		'Period5' => array(
      'description' => 'TODO: please describe this field!',
      'type' => 'varchar',
      'length' => '50',
      'not null' => FALSE,
    ),
		'Period6' => array(
      'description' => 'TODO: please describe this field!',
      'type' => 'varchar',
      'length' => '50',
      'not null' => FALSE,
    ),
		'Period7' => array(
      'description' => 'TODO: please describe this field!',
      'type' => 'varchar',
      'length' => '50',
      'not null' => FALSE,
    ),
		'Period8' => array(
      'description' => 'TODO: please describe this field!',
      'type' => 'varchar',
      'length' => '50',
      'not null' => FALSE,
    ),
	),
  'primary key' => array('day'),
  );

	$session = (string)variable_get('essa_sid');
	$schema['attendance'] = array(
    'description' => 'TODO: please describe this table!',
    'fields' => array(
      'id' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'serial',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
      'adm_no' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'varchar',
        'length' => '50',
        'not null' => FALSE,
      ),
      'roll_no' => array(
        'description' => 'TODO: please describe this field!',
        'type' => 'int',
        'length' => '10',
        'not null' => FALSE,
      ),
    ),
    'primary key' => array('id'),
  );

	$bi_table = 'essa_'.$session.'_basicinfo';
  $bi_db = db_query(
		"SELECT * from {$bi_table}"
	);
  foreach($bi_db as $bi){
		if(isset($bi->academicyearstart) && isset($bi->academicyearend)){
			$strDateFrom = $bi->academicyearstart;
			$strDateTo = $bi->academicyearend;
		}else{
			drupal_set_message('First setup the School Information. ("admin/people/permissions")');
		}
  }

  $aryRange=array();
  $iDateFrom=mktime(1,0,0,substr($strDateFrom,5,2),     substr($strDateFrom,8,2),substr($strDateFrom,0,4));
  $iDateTo=mktime(1,0,0,substr($strDateTo,5,2),     substr($strDateTo,8,2),substr($strDateTo,0,4));

  if ($iDateTo>=$iDateFrom){
    array_push($aryRange,date('Y_m_d',$iDateFrom)); // first entry
    while ($iDateFrom<$iDateTo){
      $iDateFrom+=86400; // add 24 hours
      if(date('D',$iDateFrom) != 'Sun'){
        array_push($aryRange,date('Y_m_d',$iDateFrom));
      }
    }
  }
  foreach($aryRange as $dates){
    $date[$dates] = array(
      'description' => 'TODO: please describe this field!',
      'type' => 'varchar',
      'length' => '5',
      'not null' => TRUE,
      'default' => '',
    );
  }

  $schema['attendance']['fields'] = array_merge($schema['attendance']['fields'], $date);

  foreach($form_state['values'] as $class_key => $val){
    $session_id = (string)variable_get('essa_sid');
    $class_list = 'essa_'.$session_id.'_class_list';
    $section = 'essa_'.$session_id.'_class_section';

    if(is_array($val)){
      foreach($val as $k => $v){
        $class_update= db_update($class_list) // Table name no longer needs {}
          ->fields(array('no_of_sec' => $v['c2']))
          ->condition('class_id', $k, '=')
          ->execute();
      }
    }
  }

	foreach($form_state['values'] as $key => $val){
		$cs_id = NULL;
    $session_id = (string)variable_get('essa_sid');
		$section = 'essa_'.$session_id.'_class_section';
    if(is_array($val)){
      foreach($val as $class_key => $val){

        switch($val['c2']){
					//----------------------------------------------------------------------------------------------------1----------------------------------------
          case "1":
            $name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_A_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_A';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_A')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
						  ->fields (array(
						    'sections' => clean_string($class_key).'_A',
						    )
						  )
						->execute();
            break;

					//----------------------------------------------------------------------------------------------------2----------------------------------------
           case "2":
             $name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_A_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_A')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
							->fields (array(
							  'sections' => clean_string($class_key).'_A',
							  )
							)
						->execute();
	          $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_A';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }

            $name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_B_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_B')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
							->fields (array(
							  'sections' => clean_string($class_key).'_B',
							  )
							)
							->execute();
	          $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_B';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
            break;

						//----------------------------------------------------------------------------------------------------3----------------------------------------
            case "3":

							$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_A_attendance';
							if(!db_table_exists($name_of_table)){
							  db_create_table($name_of_table, $schema['attendance']);
							}
							$name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_A';
							$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_A')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
							  ->fields (array(
							    'sections' => clean_string($class_key).'_A',
						    )
						  )
							->execute();
							if(!db_table_exists($name_of_table)){
							  db_create_table($name_of_table, $schema['time_table']);
							  $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
							  foreach($day as $input){
							    $weight = day_weight();
							    foreach($weight as $key => $value){
							      if($input == $key){
							        $w = $value;
							      }
							    }
							    $tt_input = db_insert($name_of_table)
							    ->fields (array(
							      'day_weight' => $w,
							    	'day' => $input,
							    	)
							    )
							    ->execute();
							  }
							}
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_B')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
							->fields (array(
							  'sections' => clean_string($class_key).'_B',
							  )
							)
						->execute();
	          $name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_B_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_B';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_C_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_C';
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_C')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
							->fields (array(
							  'sections' => clean_string($class_key).'_C',
							  )
							)
							->execute();

            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_C';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
            break;

					//----------------------------------------------------------------------------------------------------4----------------------------------------
           case "4":
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_A_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_A')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
							->fields (array(
							  'sections' => clean_string($class_key).'_A',
							  )
							)
						->execute();
	          $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_A';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_B_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_B';
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_B')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
							->fields (array(
							  'sections' => clean_string($class_key).'_B',
							  )
							)
							->execute();
		        $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_B';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_C_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_C')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
							->fields (array(
							  'sections' => clean_string($class_key).'_C',
							  )
							)
							->execute();
				    $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_C';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_D_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_D';
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_D')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
							->fields (array(
							  'sections' => clean_string($class_key).'_D',
							  )
							)
							->execute();
		        $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_D';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
            break;

					//----------------------------------------------------------------------------------------------------5----------------------------------------
           case "5":
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_A_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
						}
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_A')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_A',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_A';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_B_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_B')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_B',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_B';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_C_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_C')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_C',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_C';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_D_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_D')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_D',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_D';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_E_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_E')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_E',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_E';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
            break;

					//----------------------------------------------------------------------------------------------------6----------------------------------------
					case "6":
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_A_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
						}

						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_A')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_A',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_A';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_B_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_B')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_B',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_B';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_C_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_C')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_C',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_C';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_D_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_D')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_D',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_D';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_E_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_E')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_E',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_E';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_F_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_F')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_F',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_F';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
            break;

					//----------------------------------------------------------------------------------------------------7----------------------------------------
					case "7":
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_A_attendance';

            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_A')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_A',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_A';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_B_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_B')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_B',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_B';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_C_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_C')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_C',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_C';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_D_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_D')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_D',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_D';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_E_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_E')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_E',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_E';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_F_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_F')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_F',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_F';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_G_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_G')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_G',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_G';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
            break;

					//----------------------------------------------------------------------------------------------------8----------------------------------------
					case "8":
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_A_attendance';

            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_A')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_A',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_A';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_B_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_B')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_B',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_B';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_C_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_C')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_C',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_C';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_D_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_D')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_D',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_D';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_E_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
            $secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_E')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_E',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_E';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_F_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_F')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_F',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_F';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_G_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_G')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_G',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_G';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
						$name_of_table = 'essa_'.$session_id.'_'.clean_string($class_key).'_H_attendance';
						if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['attendance']);
            }
						$secs = db_query("
						  SELECT * from {$section} where sections = :se;", array(':se' => clean_string($class_key).'_H')
						);
						foreach($secs as $sect){
							$cs_id = $sect->id;
						}
						db_merge($section)
							->key(array('id' => $cs_id))
              ->fields (array(
                'sections' => clean_string($class_key).'_H',
                )
              )
            ->execute();
            $name_of_table = 'essa_'.$session_id.'_time_table_'.clean_string($class_key).'_H';
            if(!db_table_exists($name_of_table)){
              db_create_table($name_of_table, $schema['time_table']);
              $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
              foreach($day as $input){
                $weight = day_weight();
                foreach($weight as $key => $value){
                  if($input == $key){
                    $w = $value;
                  }
                }
                $tt_input = db_insert($name_of_table)
                ->fields (array(
                  'day_weight' => $w,
                	'day' => $input,
                	)
                )
                ->execute();
              }
            }
            break;
				}
      }
    }
  }

	$vid = taxonomy_vocabulary_machine_name_load('class_vocab');
	foreach($form_state['values'] as $key => $val){
		$session_id = (string)variable_get('essa_sid');
    if(is_array($val)){
      foreach($val as $class_key => $val){
				switch($val['c2']){
					//---------------------------------------------------------------------------------------------------1-------------------------------
					case "1":
						$tid = taxonomy_get_term_by_name($class_key);
						foreach($tid as $id){
							//dsm($id);
							$vid = taxonomy_vocabulary_machine_name_load('class_vocab');
							//dsm(_get_taxonomy_term_id_by_name('A', $vid->vid));
							if(_get_taxonomy_term_id_by_name('A', $id->tid, $vid->vid) == FALSE) {
								$term1 = array(
								  'name' => 'A',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term1 = (object) $term1;
								taxonomy_term_save($term1);
							}
						}
					break;

				//---------------------------------------------------------------------------------------------------2-------------------------------
				case "2":
					$tid = taxonomy_get_term_by_name($class_key);
						foreach($tid as $id){
							//dsm($id);
							$vid = taxonomy_vocabulary_machine_name_load('class_vocab');
							//dsm(_get_taxonomy_term_id_by_name('A', $vid->vid));
							if(_get_taxonomy_term_id_by_name('A', $id->tid, $vid->vid) == FALSE) {
								$term1 = array(
								  'name' => 'A',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term1 = (object) $term1;
								taxonomy_term_save($term1);
							}
							if(_get_taxonomy_term_id_by_name('B', $id->tid, $vid->vid) == FALSE) {
								$term2 = array(
								  'name' => 'B',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term2 = (object) $term2;
								taxonomy_term_save($term2);
							}
						}
					break;

				//---------------------------------------------------------------------------------------------------3-------------------------------
				case "3":
					$tid = taxonomy_get_term_by_name($class_key);
						foreach($tid as $id){
							//dsm($id);
							$vid = taxonomy_vocabulary_machine_name_load('class_vocab');
							//dsm(_get_taxonomy_term_id_by_name('A', $vid->vid));
							if(_get_taxonomy_term_id_by_name('A', $id->tid, $vid->vid) == FALSE) {
								$term1 = array(
								  'name' => 'A',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term1 = (object) $term1;
								taxonomy_term_save($term1);
							}
							if(_get_taxonomy_term_id_by_name('B', $id->tid, $vid->vid) == FALSE) {
								$term2 = array(
								  'name' => 'B',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term2 = (object) $term2;
								taxonomy_term_save($term2);
							}
							if(_get_taxonomy_term_id_by_name('C', $id->tid, $vid->vid) == FALSE) {
								$term3 = array(
								  'name' => 'C',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term3 = (object) $term3;
								taxonomy_term_save($term3);
							}
						}
					break;

				//---------------------------------------------------------------------------------------------------4-------------------------------
				case "4":
					$tid = taxonomy_get_term_by_name($class_key);
						foreach($tid as $id){
							//dsm($id);
							$vid = taxonomy_vocabulary_machine_name_load('class_vocab');
							//dsm(_get_taxonomy_term_id_by_name('A', $vid->vid));
							if(_get_taxonomy_term_id_by_name('A', $id->tid, $vid->vid) == FALSE) {
								$term1 = array(
								  'name' => 'A',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term1 = (object) $term1;
								taxonomy_term_save($term1);
							}
							if(_get_taxonomy_term_id_by_name('B', $id->tid, $vid->vid) == FALSE) {
								$term2 = array(
								  'name' => 'B',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term2 = (object) $term2;
								taxonomy_term_save($term2);
							}
							if(_get_taxonomy_term_id_by_name('C', $id->tid, $vid->vid) == FALSE) {
								$term3 = array(
								  'name' => 'C',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term3 = (object) $term3;
								taxonomy_term_save($term3);
							}
							if(_get_taxonomy_term_id_by_name('D', $id->tid, $vid->vid) == FALSE) {
								$term4 = array(
								  'name' => 'D',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term4 = (object) $term4;
								taxonomy_term_save($term4);
							}
						}
					break;

				//---------------------------------------------------------------------------------------------------5-------------------------------
				case "5":
					$tid = taxonomy_get_term_by_name($class_key);
						foreach($tid as $id){
							//dsm($id);
							$vid = taxonomy_vocabulary_machine_name_load('class_vocab');
							//dsm(_get_taxonomy_term_id_by_name('A', $vid->vid));
							if(_get_taxonomy_term_id_by_name('A', $id->tid, $vid->vid) == FALSE) {
								$term1 = array(
								  'name' => 'A',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term1 = (object) $term1;
								taxonomy_term_save($term1);
							}
							if(_get_taxonomy_term_id_by_name('B', $id->tid, $vid->vid) == FALSE) {
								$term2 = array(
								  'name' => 'B',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term2 = (object) $term2;
								taxonomy_term_save($term2);
							}
							if(_get_taxonomy_term_id_by_name('C', $id->tid, $vid->vid) == FALSE) {
								$term3 = array(
								  'name' => 'C',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term3 = (object) $term3;
								taxonomy_term_save($term3);
							}
							if(_get_taxonomy_term_id_by_name('D', $id->tid, $vid->vid) == FALSE) {
								$term4 = array(
								  'name' => 'D',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term4 = (object) $term4;
								taxonomy_term_save($term4);
							}
							if(_get_taxonomy_term_id_by_name('E', $id->tid, $vid->vid) == FALSE) {
								$term5 = array(
								  'name' => 'E',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term5 = (object) $term5;
								taxonomy_term_save($term5);
							}
						}
					//---------------------------------------------------------------------------------------------------6-------------------------------
				case "6":
					$tid = taxonomy_get_term_by_name($class_key);
						foreach($tid as $id){
							//dsm($id);
							$vid = taxonomy_vocabulary_machine_name_load('class_vocab');
							//dsm(_get_taxonomy_term_id_by_name('A', $vid->vid));
							if(_get_taxonomy_term_id_by_name('A', $id->tid, $vid->vid) == FALSE) {
								$term1 = array(
								  'name' => 'A',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term1 = (object) $term1;
								taxonomy_term_save($term1);
							}
							if(_get_taxonomy_term_id_by_name('B', $id->tid, $vid->vid) == FALSE) {
								$term2 = array(
								  'name' => 'B',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term2 = (object) $term2;
								taxonomy_term_save($term2);
							}
							if(_get_taxonomy_term_id_by_name('C', $id->tid, $vid->vid) == FALSE) {
								$term3 = array(
								  'name' => 'C',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term3 = (object) $term3;
								taxonomy_term_save($term3);
							}
							if(_get_taxonomy_term_id_by_name('D', $id->tid, $vid->vid) == FALSE) {
								$term4 = array(
								  'name' => 'D',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term4 = (object) $term4;
								taxonomy_term_save($term4);
							}
							if(_get_taxonomy_term_id_by_name('E', $id->tid, $vid->vid) == FALSE) {
								$term5 = array(
								  'name' => 'E',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term5 = (object) $term5;
								taxonomy_term_save($term5);
							}
							if(_get_taxonomy_term_id_by_name('F', $id->tid, $vid->vid) == FALSE) {
								$term6 = array(
								  'name' => 'F',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term6 = (object) $term6;
								taxonomy_term_save($term6);
							}
						}
					break;
				//---------------------------------------------------------------------------------------------------7-------------------------------
				case "7":
					$tid = taxonomy_get_term_by_name($class_key);
						foreach($tid as $id){
							//dsm($id);
							$vid = taxonomy_vocabulary_machine_name_load('class_vocab');
							//dsm(_get_taxonomy_term_id_by_name('A', $vid->vid));
							if(_get_taxonomy_term_id_by_name('A', $id->tid, $vid->vid) == FALSE) {
								$term1 = array(
								  'name' => 'A',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term1 = (object) $term1;
								taxonomy_term_save($term1);
							}
							if(_get_taxonomy_term_id_by_name('B', $id->tid, $vid->vid) == FALSE) {
								$term2 = array(
								  'name' => 'B',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term2 = (object) $term2;
								taxonomy_term_save($term2);
							}
							if(_get_taxonomy_term_id_by_name('C', $id->tid, $vid->vid) == FALSE) {
								$term3 = array(
								  'name' => 'C',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term3 = (object) $term3;
								taxonomy_term_save($term3);
							}
							if(_get_taxonomy_term_id_by_name('D', $id->tid, $vid->vid) == FALSE) {
								$term4 = array(
								  'name' => 'D',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term4 = (object) $term4;
								taxonomy_term_save($term4);
							}
							if(_get_taxonomy_term_id_by_name('E', $id->tid, $vid->vid) == FALSE) {
								$term5 = array(
								  'name' => 'E',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term5 = (object) $term5;
								taxonomy_term_save($term5);
							}
							if(_get_taxonomy_term_id_by_name('F', $id->tid, $vid->vid) == FALSE) {
								$term6 = array(
								  'name' => 'F',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term6 = (object) $term6;
								taxonomy_term_save($term6);
							}
							if(_get_taxonomy_term_id_by_name('G', $id->tid, $vid->vid) == FALSE) {
								$term7 = array(
								  'name' => 'G',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term7 = (object) $term7;
								taxonomy_term_save($term7);
							}
						}
					break;
				//---------------------------------------------------------------------------------------------------8-------------------------------
				case "8":
					$tid = taxonomy_get_term_by_name($class_key);
						foreach($tid as $id){
							//dsm($id);
							$vid = taxonomy_vocabulary_machine_name_load('class_vocab');
							//dsm(_get_taxonomy_term_id_by_name('A', $vid->vid));
							if(_get_taxonomy_term_id_by_name('A', $id->tid, $vid->vid) == FALSE) {
								$term1 = array(
								  'name' => 'A',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term1 = (object) $term1;
								taxonomy_term_save($term1);
							}
							if(_get_taxonomy_term_id_by_name('B', $id->tid, $vid->vid) == FALSE) {
								$term2 = array(
								  'name' => 'B',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term2 = (object) $term2;
								taxonomy_term_save($term2);
							}
							if(_get_taxonomy_term_id_by_name('C', $id->tid, $vid->vid) == FALSE) {
								$term3 = array(
								  'name' => 'C',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term3 = (object) $term3;
								taxonomy_term_save($term3);
							}
							if(_get_taxonomy_term_id_by_name('D', $id->tid, $vid->vid) == FALSE) {
								$term4 = array(
								  'name' => 'D',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term4 = (object) $term4;
								taxonomy_term_save($term4);
							}
							if(_get_taxonomy_term_id_by_name('E', $id->tid, $vid->vid) == FALSE) {
								$term5 = array(
								  'name' => 'E',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term5 = (object) $term5;
								taxonomy_term_save($term5);
							}
							if(_get_taxonomy_term_id_by_name('F', $id->tid, $vid->vid) == FALSE) {
								$term6 = array(
								  'name' => 'F',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term6 = (object) $term6;
								taxonomy_term_save($term6);
							}
							if(_get_taxonomy_term_id_by_name('G', $id->tid, $vid->vid) == FALSE) {
								$term7 = array(
								  'name' => 'G',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term7 = (object) $term7;
								taxonomy_term_save($term7);
							}
							if(_get_taxonomy_term_id_by_name('H', $id->tid, $vid->vid) == FALSE) {
								$term8 = array(
								  'name' => 'H',
								  'description' => '',
								  'parent' => $id->tid,
								  'vid' => $vid->vid,
								);
								$term8 = (object) $term8;
								taxonomy_term_save($term8);
							}
						}
					break;
				}
			}
		}
	}

	cross_check_sections($form, $form_state);
	//*******Suraj********//
	drupal_set_message('Sections were created successfully!!!','status');
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	global $user;
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'New sections were created.',
		'priority' => 'M',
		'module' => 'school_master',
		'source_url' => 'admin/settings/classes/class-section',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	//*******Suraj********//
	if(variable_get('essa-sections') != 1){
		global $base_url;
		$form_state['redirect'] = $base_url;
	}

	variable_set('essa-sections', 1);
}

function cross_check_sections($form, &$form_state){
	//dsm($form_state);
	$output = array();
	$session_id = (string)variable_get('essa_sid');
	$vid = taxonomy_vocabulary_machine_name_load('class_vocab');
	$class_list = 'essa_'.$session_id.'_class_list';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	foreach($classes as $class){
		//dsm($class->no_of_sec);
		$tid = taxonomy_get_term_by_name($class->class_id);
		foreach($tid as $id){
			$term_data = taxonomy_get_children($id->tid);
			if(count($term_data) != $class->no_of_sec){
				$dif = count($term_data) - $class->no_of_sec;
				$output = array_slice($term_data, -$dif);
			}
		}
		//dsm($term_data);
		foreach($output as $del){
			taxonomy_term_delete($del->tid);
		}
	}
}
/**
 * Get taxonomy term ID by term name.
 *
 * @param string $termname
 * @param integer $vid
 */
function _get_taxonomy_term_id_by_name($termname, $tid, $vid) {
	$term_data = taxonomy_get_children($tid);
	$ch = array();
	if(empty($term_data)){
		return FALSE;
	}else{
		foreach($term_data as $data){
			$ch[] = $data->name;
		}
	}
	if(!in_array($termname, $ch)){
		return FALSE;
	}else{
		return TRUE;
	}
}

/**
 *Supporting function to clean_string the array id.
 */
function clean_string($string) {
   $string = str_replace(' ', '-', $string); // Replaces all spaces with hyphens.
   return preg_replace('/[^A-Za-z0-9\-]/', '', $string); // Removes special chars.
}

/**--------------------------------------------------------------------------------------------------------------------------------------------------------------
 *find_weights - to attach a weight for all class, to maintain the order of classes
 *--------------------------------------------------------------------------------------------------------------------------------------------------------------*/
function day_weight(){
  return array(
    'Monday' => 0,
    'Tuesday' => 1,
    'Wednesday' => 2,
    'Thursday' => 3,
    'Friday' => 4,
    'Saturday' => 5,
  );
}
