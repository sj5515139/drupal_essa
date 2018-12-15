<?php

/**
 *Implements page callback function - addstudent_bu_form
 */
function addstudent_bu_form($form, &$form_state){
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
	if(!in_array('Student', $folder_list)){
		$node = new stdClass();
		$node->type = 'filedepot_folder';
		node_object_prepare($node);
		$node->language = LANGUAGE_NONE;
		$node->uid = 1;
		$node->title = check_plain('Student');
		$node->filedepot_folder_desc[LANGUAGE_NONE][0]['value'] = 'This is folder contains folder for each student, with folder name of admission no.';
		$node->parentfolder = 0;
		$node->inherit = 1;
		node_save($node);
	}
  $form = array();
  $path = drupal_get_path('module','student_admission').'/template/student_bu_class_wise.xls';
  //dsm($path);

	//$form['title'] = array(
	//	'#markup' => '<h2 id = "bulk_title" style = "margin-top: 3px;"> Select a class & section to upload students - </h2>',
	//);

  module_load_include('inc', 'hierarchical_select', 'includes/common');

	$config = sa_hs_bu_setting();
	$form['class'] =  array(
    '#type' => 'hierarchical_select',
    '#config' => $config,
		'#title' =>'Select a class & section to upload students',
		'#required' => TRUE,
  );

  $form['browser'] = array(
    '#type' => 'fieldset',
    '#title' => t('Browser Upload'),
    '#description' => t("Upload a CSV file. Please fill all the fields marked with * in the .csv file. Admission no., Student's and Parent's email ID is particularly important."),
  );

  $form['browser']['download'] = array(
    '#type' => 'markup',
    '#markup' => '<h3>'.l(t('Download a template'), $path).'</h3>',
  );

  $file_size = t('Maximum file size: !size MB.', array('!size' => file_upload_max_size()));

  $form['browser']['file_upload'] = array(
    '#type' => 'file',
    '#title' => t('CSV File'),
    '#size' => 40,
    '#description' => t('Select the CSV file to be imported. ') . $file_size,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('add_student_csv_submit'),
    '#validate' => array('add_student_csv_validate'),
  );

	// set the form encoding type
  $form['#attributes']['enctype'] = "multipart/form-data";

  return $form;
}


function add_student_csv_validate($form, &$form_state) {
  // attempt to save the uploaded file
  $validators = array('file_validate_extensions' => array('csv'));
  $file = file_save_upload('file_upload', $validators);

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
	
	$session = variable_get('essa_sid');
  $adm_no = array();
  //$class = taxonomy_term_load($form_state['values']['class'][0]);
  //$section = taxonomy_term_load($form_state['values']['class'][1]);
  $table = 'essa_'.$session.'_master_student_table';

	if(empty($form_state['values']['class'][0])){
		form_set_error('class','Select a class and section.');
	}
	if(empty($form_state['values']['class'][1])){
		form_set_error('class','Select a section.');
	}
 
	
	if(db_table_exists($table)){
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
		  $csv = fgetcsv($handle);
      
			$student_master_table = 'essa_'.$session.'_master_student_table';
			$prev_input = db_query("select * from $student_master_table");
			foreach($prev_input as $input){
				$adm_no[] = $input->adm_no;
			}
			if($csv[1] == NULL){
				//$emp = 1;
			}
			elseif(!in_array($csv[1], $adm_no)){
				if($csv[5] == NULL){
					form_set_error('file_upload','Student first name can not be blank for Admission No. '.$csv[1].'.');
				}
				if($csv[7] == NULL){
					form_set_error('file_upload','Student last name can not be blank for Admission No. '.$csv[1].'.');
				}
			}
		}
	}
}

function add_student_csv_submit($form, &$form_state) {
	$session = variable_get('essa_sid');
  $adm_no = array();
  $class = taxonomy_term_load($form_state['values']['class'][0]);
  $section = taxonomy_term_load($form_state['values']['class'][1]);
	$student_master_table = 'essa_'.$session.'_master_student_table';
  
  
	if(db_table_exists($student_master_table)){
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
		  $csv = fgetcsv($handle);
      
			
			$prev_input = db_query("select * from $student_master_table");
			foreach($prev_input as $input){
				$adm_no[] = $input->adm_no;
			}
			//dsm($csv);
			if(!empty($csv[1]) != NULL){
				if(!in_array($csv[1], $adm_no)){
					db_merge($student_master_table)
					->key(array('adm_no' => $csv[1]))
					->fields (array(
						'adm_no' => $csv[1],
						'doa' => $csv[2],
						'gender' => $csv[3],
						'student_name' => $csv[4].' '.$csv[5].' '.$csv[6],
						'first_name' => $csv[4],
						'middle_name' => $csv[5],
						'last_name' => $csv[6],
						'dob' => $csv[7],
						'r_phone' => $csv[8],
						'c_phone' => $csv[9],
						'ec1' => $csv[10],
						'ec2' => $csv[11],
						'ec3' => $csv[12],
						's_email' => $csv[13],
						'p_email' => $csv[14],
						'father_name' => $csv[15].' '.$csv[16].' '.$csv[17],
						'f_first_name' => $csv[15],
						'f_middle_name' => $csv[16],
						'f_last_name' => $csv[17],
						'mother_name' => $csv[18].' '.$csv[19].' '.$csv[20],
						'm_first_name' => $csv[18],
						'm_middle_name' => $csv[19],
						'm_last_name' => $csv[20],
						'c_line1' => $csv[21],
						'c_line2' => $csv[22],
						'c_city' => $csv[23],
						'c_state' => $csv[24],
						'c_pincode' => $csv[25],
						'c_country' => $csv[26],
						'sc' => $csv[27],
						'blood_group' => $csv[28],
						'is_hostel' => $csv[29],
						'status' => 1,
					))
					->execute();
					$num++;
					
					$stud_name = '';
					$uid = db_query("select * from users where name = :user", array(':user' => $csv[1]));
					foreach($uid as $puid){
						$stud_name = $puid->name;
					}
					
					if($stud_name != $csv[1]){
						$rid = db_query("select rid from role where name = 'Parent'");
						foreach($rid as $role_id){
							foreach($role_id as $p_role){
								$parent = $p_role;
							}
						}
						
						$rid = db_query("select rid from role where name = 'Student'");
						foreach($rid as $role_id){
							foreach($role_id as $s_role){
								$student = $s_role;
							}
						}
						
						$edit_student = array(
							'name' => $csv[1],
							'pass' => $csv[1],
							'mail' => $csv[13],
							'init' => $csv[13],
							'status' => 1,
							'access' => REQUEST_TIME,
							'roles' => array($student =>'Student'),
						);
						user_save('', $edit_student);
						
						$edit_parent = array(
							'name' => 'p'.'_'.$csv[1],
							'pass' => $csv[1],
							'mail' => $csv[14],
							'init' => $csv[14],
							'status' => 1,
							'access' => REQUEST_TIME,
							'roles' => array($parent => 'Parent'),
						);
						user_save('', $edit_parent);
					}
					
					$uid = db_query("select * from users where name = :user", array(':user' => 'p'.'_'.$csv[1]));
					foreach($uid as $puid){
						$parent_uid = $puid -> uid;
					}
					$uid = db_query("select * from users where name = :user", array(':user' => $csv[1]));
					foreach($uid as $puid){
						$student_uid = $puid -> uid;
					}
					db_update($student_master_table)
					->fields (array(
						'uid' => $student_uid,
						'puid' => $parent_uid,
					))
					->condition('adm_no', $csv[1], '=')
					->execute();
					
					$class = taxonomy_term_load($form_state['values']['class'][0]);
					$section = taxonomy_term_load($form_state['values']['class'][1]);
					
					db_merge('essa_'.$session.'_master_student_table')
					->key(array('adm_no' => $csv[1]))
					->fields (array(
						'adm_no' => $csv[1],
						'first_name' => $csv[4],
						'middle_name' => $csv[5],
						'last_name' => $csv[6],
						'uid' => $student_uid,
						'puid' => $parent_uid,
						'class' => $class->name,
						'section' => $section->name,
						'is_hostel' => $csv[29],
						)
					)
					->execute();
					
					$class = taxonomy_term_load($form_state['values']['class'][0]);
					$section = taxonomy_term_load($form_state['values']['class'][1]);
					
					$students = db_query("
						SELECT * from {$student_master_table} where class = :class and section =:sec order by first_name, middle_name, last_name;",array(':class' =>$class->name, ':sec' => $section->name)
					);
					
					// $roll_no = 1;
					// foreach($students as $student){
						
						// db_update('essa_'.$session.'_master_student_table') // Table name no longer needs {}
							// ->fields(array('roll_no' => $roll_no))
							// -> condition('adm_no', $student->adm_no, '=')
							// ->execute();
						// $roll_no++;
					// }
					$folder_id = '';
					$filedepot_table = 'filedepot_categories';
					if(db_table_exists($filedepot_table)){
						$folders = db_query("
							SELECT * from {$filedepot_table} where name = 'Student';"
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
					$node->filedepot_folder_desc[LANGUAGE_NONE][0]['value'] = 'This is folder is for each student, here you can save documents and files related to each student.';
					$node->parentfolder = $folder_id;
					$node->inherit = 1;
					node_save($node);
	
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
					//******Suraj*****//
					//sending message to student
					$module = 'Students';
					$recipients= array();
					$recipients[] = user_load($student_uid);
					$msg_subject = 'Welcome to ESSA';
					$msg_body = 'You have been successfully added to the school management system -  ESSA. <br> Your credentials are mentioned below. <br> Login using the given username and password. <br> You can change your password at any time after your first login. <br> Admission No: '.$csv[1].'<br> Name: '.$csv[4].' '.$csv[5].' '.$csv[6].'<br> Username: '.$csv[1].'<br> Password: '.$csv[1];
					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
					$msg_body = $msg_body.' <br>'.$footer;
					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
					
					//sending message to parent
					$module = 'Students';
					$recipients= array();
					$recipients[] = user_load($parent_uid);
					$msg_subject = 'Welcome to ESSA';
					$msg_body = 'Sir/Mam, <br> You have been successfully added to the school management system -  ESSA. <br> Your credentials are mentioned below. <br> Login using the given username and password. <br> You can change your password at any time after your first login. <br> Admission No: '.$csv[1].'<br> Name: '.$csv[4].' '.$csv[5].' '.$csv[6].'<br> Username: p_'.$csv[1].'<br> Password: '.$csv[1];
					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
					$msg_body = $msg_body.' <br>'.$footer;
					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
					
					
					$sys_alert_table = 'essa_'.$session.'_system_alert';
					global $user;
					//sending system alert
					$created_date = date("Y-m-d H:i:s");
					$strtodate = strtotime($created_date);
					db_insert($sys_alert_table)
					->fields(array(
						'message' => 'Student '.$csv[1].' - '.$csv[4].' '.$csv[5].' '.$csv[6].' has been registered for the class '.$class->name.'-'.$section->name.'.',
						'priority' => 'L',
						'module' => 'Students',
						'source_url' => 'admin/students/admission/student_admission_bulk_upload',
						'timestamp' => $strtodate,
						'source_uid' => $user->uid,
					))
					->execute();
					//******Suraj*****//
				}
				
			}
			
		}
		drupal_set_message('No. of rows processed = '. $num, 'status');
	}else{
		drupal_set_message('This class/section combination is not present in the system. Please create them before student admission - '.l(t('Manage Classes'), 'admin/administration/classes/class-setup').' OR '.l(t('Manage Section'), 'admin/administration/classes/class-section'));
	}
	
	drupal_cron_run();
}

/**
 *Supporting function to clean_string the array id.
 *//*
function clean_classes($string) {
   $string = str_replace('.', '', $string); // Replaces all spaces with hyphens.
	 $string = str_replace(' ', '', $string);
   return preg_replace('/[^A-Za-z0-9\-]/', '', $string); // Removes special chars.
}

/**
*Implements hierarchical select settings
*/
function sa_hs_bu_setting(){
	// Load category based in vocabulary machine name
	$voc = 'class_vocab';//replace this with the taxonomy term
  $vocabulary = taxonomy_vocabulary_machine_name_load($voc);
	//dsm($vocabulary);

	$config = array(
		'module' => 'hs_taxonomy',
    'params' => array(
				'vid' => (int) $vocabulary->vid,
				'exclude_tid' => NULL,
				'root_term' => NULL,
				'entity_count_for_node_type' => NULL,
      ),
		'config_id'       => 'taxonomy-2',
		'save_lineage'    => 1,
		'enforce_deepest' => 0,
		'entity_count'    => 0,
		'require_entity'  => 0,
		'resizable'       => 0,
		'render_flat_select' => 0,
		'level_labels' => array(
		  'status' => 1,
		  'labels' => array(
		    0 => '--Select--',
		    1 => '--Select--',
		  ),
		),
		'dropbox' => array(
		  'status'    => 0,
		),
		'editability' => array(
		  'status' => 0,
		  'item_types' => array(
		    0 => '',
		    1 => '',
		  ),
		  'allowed_levels' => array(
		    0 => 1,
		    1 => 1,
		  ),
		  'allow_new_levels' => 0,
		  'max_levels'       => 1,
		),
	);

	return $config;
}
