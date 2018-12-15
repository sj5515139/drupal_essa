<?php
function add_staff_bu_form($form, &$form_state){
  $folder_list = array();
	$filedepot_table = 'filedepot_categories';
	if(db_table_exists($filedepot_table)){
		$folders = db_query("
		  SELECT * from {$filedepot_table};
		");
		foreach($folders as $folder){
			$folder_list[] = $folder->name;
		}
	}
	if(!in_array('Staff', $folder_list)){
		$node = new stdClass();
		$node->type = 'filedepot_folder';
		node_object_prepare($node);
		$node->language = LANGUAGE_NONE;
		$node->uid = 1;
		$node->title = check_plain('Staff');
		$node->filedepot_folder_desc[LANGUAGE_NONE][0]['value'] = 'This is folder contains folder for each staff, with folder name of empID.';
		$node->parentfolder = 0;
		$node->inherit = 1;
		node_save($node);
	}
  
  $form = array();
  $path = drupal_get_path('module','staff_recruitment').'/template/employee.xlsx';
  
  $form['browser'] = array(
    '#type' => 'fieldset',
    '#title' => t('Browser Upload'),
    '#collapsible' => TRUE,
    '#description' => t("Upload a CSV file."),
  );

  $form['browser']['download'] = array(
    '#type' => 'markup',
    '#markup' => l(t('Download a template'), $path),
  );

  $file_size = t('Maximum file size: !size MB.', array('!size' => file_upload_max_size()));

  $form['browser']['file_upload'] = array(
    '#type' => 'file',
    '#title' => t('CSV File'),
    '#size' => 40,
    '#description' => t('Select the CSV file to be imported.') . $file_size,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('add_staff_csv_submit'),
    '#validate' => array('add_staff_csv_validate'),
  );

  // set the form encoding type
  $form['#attributes']['enctype'] = "multipart/form-data";

  return $form;
}

/**
 *Implements csv_validate
 */
function add_staff_csv_validate($form, &$form_state) {
  // attempt to save the uploaded file
  $validators = array('file_validate_extensions' => array('csv'));
  $file = file_save_upload('file_upload', $validators);
$nn=array();
  // check file uploaded OK
  if (!$file) {
    form_set_error('file_upload', t('A file must be uploaded or selected from FTP updates.'));
  }
  else if($file->filemime != 'text/csv') {
    form_set_error('file_upload', t('The file must be of CSV type only.'));
  }
  else {
    // set files to form_state, to process when form is submitted
    $form_state['values']['file_upload'] = $file;
  }
	//*******Suraj********//
  $emp_id = array();
  $line_max = variable_get('user_import_line_max', 1000);
  ini_set('auto_detect_line_endings', true);
  $filepath = $form_state['values']['file_upload']->destination;
  $handle = @fopen($filepath, "r");
  $flag = true;
  $emp = 0;
	
  while(! feof($handle)){
    if($flag) {
      $csv = fgetcsv($handle);
      $flag = false; continue;
    }
    $session = variable_get('essa_sid');
    $table = 'essa_'.$session.'_master_staff_table';
    $csv = fgetcsv($handle);
    $prev_input = db_query("select * from $table");
    
    foreach($prev_input as $input){
      $emp_id[] = $input->emp_id;
			$nn[] = $input->nickname;
    }
		//dsm($nn);
		//dsm($csv[6]);
		//dsm($csv);
		if($csv[1] == NULL){
			$emp = 1;
		}elseif(!in_array($csv[1], $emp_id)){
			if(in_array($csv[6], $nn)){
				form_set_error('file_upload','Nickname '.$csv[6].' is already present in the system given for Employee '.$csv[1].'.');
			}
			if($csv[2] == NULL){
				form_set_error('file_upload','Date of joining can not be blank for Employee ID '.$csv[1].'.');
			}
			if($csv[3] == NULL){
				form_set_error('file_upload','Employee type can not be blank for Employee ID '.$csv[1].'.');
			}
			if($csv[4] == NULL){
				form_set_error('file_upload','Employee first name can not be blank for Employee ID '.$csv[1].'.');
			}
			if($csv[5] == NULL){
				form_set_error('file_upload','Employee last name can not be blank for Employee ID '.$csv[1].'.');
			}
		}
		
	}
	
	//*******Suraj********//
}

/**
 *Implements form_submit
 */
function add_staff_csv_submit($form, &$form_state) {
  $table = array();
  $emp_id = array();
  $line_max = variable_get('user_import_line_max', 1000);
  ini_set('auto_detect_line_endings', true);
  $filepath = $form_state['values']['file_upload']->destination;
  $handle = @fopen($filepath, "r");
  $flag = true;
  $num = 0;
  while(! feof($handle)){
    if($flag) {
      $csv = fgetcsv($handle);
      $flag = false; continue;
    }
    $session = variable_get('essa_sid');
    $table = 'essa_'.$session.'_master_staff_table';
    $csv = fgetcsv($handle);
    $prev_input = db_query("select * from $table");
    
    foreach($prev_input as $input){
      $emp_id[] = $input->emp_id;
    }
		if($csv[1] != NULL){
			if(!in_array($csv[1], $emp_id)){
				$fe_id = db_merge($table)
				->key(array('emp_id' => $csv[1]))
				->fields (array(
					'emp_id' => $csv[1],
					'status' => 1,
					'fname' => $csv[2],
					'lname' => $csv[3],
					'nickname' => $csv[4],
					'type' => $csv[5],
					'dob' => $csv[6],
					'joining_date' => $csv[7],
					'grade' => $csv[8],
					'mobile_no' => $csv[9],
					'phone_no' => $csv[10],
					'email' => $csv[11],
				))
				->execute();
				$num++;
				
				// CREATING ROLES FOR DEPENDING ON 'TYPE'
				$rid = db_query("select rid from role where name = 'Staff'");
				foreach($rid as $role_id){
					foreach($role_id as $s_role){
						$staff = $s_role;
					}
				}
				$rid = db_query("select rid from role where name = 'Teacher'");
				foreach($rid as $role_id){
					foreach($role_id as $s_role){
						$teacher = $s_role;
					}
				}
				
				if($csv[3] == 'teaching' || $csv[3] == 'Teaching'){
					$edit_staff = array(
						'name' => $csv[1],
						'pass' => $csv[1],
						'mail' => $csv[11],
						'init' => $csv[11],
						'status' => 1,
						'access' => REQUEST_TIME,
						'roles' => array($staff => 'Staff', $teacher => 'Teacher'),
					);
					user_save('', $edit_staff);
				}else{
					$edit_staff = array(
						'name' => $csv[1],
						'pass' => $csv[1],
						'mail' => $csv[8],
						'init' => $csv[8],
						'status' => 1,
						'access' => REQUEST_TIME,
						'roles' => array($staff => 'Staff'),
					);
					user_save('', $edit_staff);

				}
				$uid = db_query("select * from users where name = :user", array(':user' => $csv[1]));
				foreach($uid as $staffuid){
					$staff_uid = $staffuid -> uid;
				}
				db_update($table)
					->fields (array(
						'uid' => $staff_uid,
					)
				)
				->condition('emp_id', $csv[1], '=')
				->execute();
				
				$vid = taxonomy_vocabulary_machine_name_load('staff_uid_vocab');
				taxonomy_term_save(
					(object) array(
					'name' => $staff_uid,
					'vid' => $vid->vid,
					)
				);
				
				$vid = taxonomy_vocabulary_machine_name_load('staff_vocab');
				taxonomy_term_save(
					(object) array(
					'name' => $csv[1],
					'vid' => $vid->vid,
					)
				);
				
				$uid = db_query("select * from users where name = :user", array(':user' => $csv[1]));
				foreach($uid as $staffuid){
					$staff_uid = $staffuid -> uid;
				}
				
				$folder_id = '';
				$filedepot_table = 'filedepot_categories';
				if(db_table_exists($filedepot_table)){
					$folders = db_query("
						SELECT * from {$filedepot_table} where name = 'Staff';"
					);
					foreach($folders as $folder){
						$folder_id = $folder->cid;
					}
				}
				$node = new stdClass();
				$node->type = 'filedepot_folder';
				node_object_prepare($node);
				$node->language = LANGUAGE_NONE;
				$node->uid = 1;
				$node->title = check_plain($csv[1]);
				$node->filedepot_folder_desc[LANGUAGE_NONE][0]['value'] = 'This is folder is for each staff, here you can save documents and files related to each staff.';
				$node->parentfolder = $folder_id;
				$node->inherit = 1;
				node_save($node);
				
				db_update($table)
					->fields (array(
						'uid' => $staff_uid,
					))
				->condition('emp_id', $csv[1], '=')
				->execute();
				
				$folders = db_query("
					SELECT * from filedepot_categories where name = :name;", array(':name' => $csv[1])
				);
				foreach($folders as $folder){
					$folder_id = $folder->cid;
				}
				
				$path = 'sites/default/files/filedepot/'.$folder_id;
				$node = new stdClass();
				$node->type = 'dir_listing';
				node_object_prepare($node);
				$node->language = LANGUAGE_NONE;
				$node->uid = 1;
				$node->title = check_plain($csv[1]);
				$node->filedepot_folder_desc[LANGUAGE_NONE][0]['value'] = 'This is individual staff folder listing, this is mainly for display purposes.';
				$node->folder_path = $path;
				$node->folder_uploads = new stdClass();
				$node->folder_uploads->enabled = 1;
				$node->folder_uploads->allow_overwrite = 1;
				$node->folder_rights = new stdClass();
				$node->folder_rights->explore_subdirs = 1;
				$node->folder_rights->download_archive = 1;
				$node->folder_rights->create_folders = 1;
				$node->folder_rights->download_manager = 'Public';
				$node->folder_rights->force_download = 1;
				$node->folder_rights->forbidden_files = "descript.ion\nfile.bbs\n.git\nCSV\n.svn\n.htaccess";
				$node->folder_presentation = new stdClass();
				$node->folder_presentation->default_view = 'list-view';
				$node->folder_presentation->encoding = 'UTF-8';
				$node->folder_presentation->visible_columns = array("icon" => TRUE, "display-name" => TRUE, "size" => TRUE);
				node_save($node);
	
				
				$schema['time_table'] = array(
					'description' => 'TODO: please describe this table!',
					'fields' => array(
						'day_weight' => array(
						 'description' => 'TODO: please describe this field!',
						 'type' => 'int',
						 'not null' => FALSE,
						),
					'day' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '15',
						'not null' => TRUE,
					'default' => '',
					),
					'Period1_class' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period1_subject' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period2_class' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period2_subject' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period3_class' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period3_subject' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period4_class' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period4_subject' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period5_class' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period5_subject' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period6_class' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period6_subject' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period7_class' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period7_subject' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period8_class' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					'Period8_subject' => array(
						'description' => 'TODO: please describe this field!',
						'type' => 'varchar',
						'length' => '50',
						'not null' => FALSE,
					),
					),
					'primary key' => array('day'),
				);
				if($csv[5] == 'teaching' || $csv[5] == 'Teaching'){
					$name_of_table = 'essa_'.$session.'_time_table_'.clean_teacher($csv[1]);
					if(!db_table_exists($name_of_table)){
							db_create_table($name_of_table, $schema['time_table']);
							$day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
							foreach($day as $w => $input){
							db_insert($name_of_table)
							->fields (array(
								'day_weight' => $w,
								'day' => $input,
							))
							->execute();
						}
					}
				}
				//******Suraj*****//
				$sys_alert_table = 'essa_'.$session.'_system_alert';
				global $user;
				//sending system alert
				$created_date = date("Y-m-d H:i:s");
				$strtodate = strtotime($created_date);
				db_insert($sys_alert_table)
				->fields(array(
					'message' => 'Employee ID '.$csv[1].' has been added to the system.',
					'priority' => 'L',
					'module' => 'Staff',
					'source_url' => 'admin/staff/recruitment/employee_recruitment_bulk_upload',
					'timestamp' => $strtodate,
					'source_uid' => $user->uid,
				))
				->execute();
				//******Suraj*****//
			}
    }
  }
	drupal_set_message('No. of rows processed = '. $num, 'status');
}

/**________________________________________________clean_sub_string_uns()___________________________________________________
 *Supporting function to clean_string the array id.
 ----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
function clean_teacher($string) {
   $string = str_replace('-', '', $string); // Replaces all spaces with hyphens.
	 $string = str_replace(' ', '', $string);
   return preg_replace('/[^A-Za-z0-9\-]/', '', $string); // Removes special chars.
}
