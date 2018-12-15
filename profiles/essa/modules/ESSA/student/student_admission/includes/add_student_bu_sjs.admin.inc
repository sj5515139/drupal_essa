<?php

/**
 *Implements page callback function - addstudent_bu_form
 */
function addstudent_bu_sjs_form($form, &$form_state){
	
	$session = variable_get('essa_sid');
	
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
  $path = drupal_get_path('module','student_admission').'/template/student_bu.xls';
  //dsm($path);
  
  $form['browser'] = array(
    '#type' => 'fieldset',
    '#title' => t('Student'),
    '#description' => t("Upload a CSV file. Please fill all the fields marked with * in the .csv file. Admission no., Student's and Parent's email ID is particularly important. Here, you can upload bulk for all classes at one go."),
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

function roman_class($i){
  switch($i){
    case 'UKG':
        return 'UKG';
    case 'LKG':
      return 'LKG';
    case 1:
      return 'I';
    case 2:
      return 'II';
    case 3:
      return 'III';
    case 4:
      return 'IV';
    case 5:
      return 'V';
    case 6:
      return 'VI';
    case 7:
      return 'VII';
    case 8:
      return 'VIII';
    case 9:
      return 'IX';
    case 10:
      return 'X';
  }
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
}

function add_student_csv_submit($form, &$form_state) {
	$session = variable_get('essa_sid');
  $table = array();
  $adm_no = array();
  
	if(1){
		$line_max = variable_get('user_import_line_max', 1000);
		ini_set('auto_detect_line_endings', true);
		$filepath = $form_state['values']['file_upload']->destination;
		$handle = @fopen($filepath, "r");
		$flag = true;
		$num = 0;
		while(! feof($handle)){
		  if($flag){
		    $csv = fgetcsv($handle);
		    $flag = false; continue;
		  }
		  $csv = fgetcsv($handle);
		  
			$adm_no = variable_get('esaa_st_adm_no');
			$doa = variable_get('esaa_st_doa');
			$gender = variable_get('esaa_st_gender');
			$s_first_name = variable_get('esaa_st_fname');
			$s_middle_name = variable_get('esaa_st_mname');
			$s_last_name = variable_get('esaa_st_lname');
			$class = variable_get('esaa_st_class');
			$section = variable_get('esaa_st_sec');
			$dob = variable_get('esaa_st_dob');
			$phone1 = variable_get('esaa_st_phone1');
			$phone2 = variable_get('esaa_st_phone2');
			$phone3 = variable_get('esaa_st_phone3');
			$phone4 = variable_get('esaa_st_phone4');
			$phone5 = variable_get('esaa_st_phone5');
			$semail = variable_get('esaa_st_s_email');
			$pemail = variable_get('esaa_st_p_email');
			$f_first_name = variable_get('esaa_st_f_fname');
			$f_middle_name = variable_get('esaa_st_f_mname');
			$f_last_name = variable_get('esaa_st_f_lname');
			$m_first_name = variable_get('esaa_st_m_fname');
			$m_middle_name = variable_get('esaa_st_m_mname');
			$m_last_name = variable_get('esaa_st_m_lname');
			$line1 = variable_get('esaa_st_line1');
			$line2 = variable_get('esaa_st_line2');
			$city = variable_get('esaa_st_city');
			$state = variable_get('esaa_st_state');
			$pincode = variable_get('esaa_st_pincode');
			$country = variable_get('esaa_st_country');
			$sc_st = variable_get('esaa_st_scst');
			$blood_group = variable_get('esaa_st_blood_group');
			$boarder = variable_get('esaa_st_boarder');
		  
		  
			$in_adm_no = isset($csv[$adm_no])?$csv[$adm_no]:NULL;
			$in_doa = isset($csv[$doa])?$csv[$doa]:NULL;
			$in_gender  = isset($csv[$gender])?$csv[$gender]:NULL;
			$in_s_first_name = isset($csv[$s_first_name])?$csv[$s_first_name]:NULL;
			$in_s_middle_name = isset($csv[$s_middle_name])?$csv[$s_middle_name]:NULL;
			$in_s_last_name = isset($csv[$s_last_name])?$csv[$s_last_name]:NULL;
			$in_class = isset($csv[$class])?$csv[$class]:NULL;
			$in_section = isset($csv[$section])?$csv[$section]:NULL;
			$in_dob = isset($csv[$dob])?$csv[$dob]:NULL;
			$in_phone1 = isset($csv[$phone1])?$csv[$phone1]:NULL;
			$in_phone2 = isset($csv[$phone2])?$csv[$phone2]:NULL;
			$in_phone3 = isset($csv[$phone3])?$csv[$phone3]:NULL;
			$in_phone4 = isset($csv[$phone4])?$csv[$phone4]:NULL;
			$in_phone5 = isset($csv[$phone5])?$csv[$phone5]:NULL;
			$in_semail = isset($csv[$semail])?$csv[$semail]:NULL;
			$in_pemail = isset($csv[$pemail])?$csv[$pemail]:NULL;
			$in_f_first_name = isset($csv[$f_first_name])?$csv[$f_first_name]:NULL;
			$in_f_middle_name = isset($csv[$f_middle_name])?$csv[$f_middle_name]:NULL;
			$in_f_last_name = isset($csv[$f_last_name])?$csv[$f_last_name]:NULL;
			$in_m_first_name = isset($csv[$m_first_name])?$csv[$m_first_name]:NULL;
			$in_m_middle_name = isset($csv[$m_middle_name])?$csv[$m_middle_name]:NULL;
			$in_m_last_name = isset($csv[$m_last_name])?$csv[$m_last_name]:NULL;
			$in_line1 = isset($csv[$line1])?$csv[$line1]:NULL;
			$in_line2 = isset($csv[$line2])?$csv[$line2]:NULL;
			$in_city = isset($csv[$city])?$csv[$city]:NULL;
			$in_state = isset($csv[$state])?$csv[$state]:NULL;
			$in_pincode = isset($csv[$pincode])?$csv[$pincode]:NULL;
			$in_country = isset($csv[$country])?$csv[$country]:NULL;
			$in_scst = isset($csv[$sc_st])?$csv[$sc_st]:NULL;
			$in_blood_group = isset($csv[$blood_group])?$csv[$blood_group]:NULL;
			$in_boarder = isset($csv[$boarder])?$csv[$boarder]:NULL;
		  
		  
			
			if(!empty($in_class)){
				if(is_numeric($in_class)){
					$cls = roman_class($in_class);
					if($in_section == ' ' || $in_section == NULL){
						$sec = 'A';
					}else{
						$sec = $in_section;
					}
				}else{
					$cls = $in_class;
					if($in_section == ' ' || $in_section == NULL){
						$sec = 'A';
					}else{
						$sec = $in_section;
					}
				}
				
				$adm_no = array();
				$student_master_table = 'essa_'.$session.'_master_student_table';
				$prev_input = db_query("select * from $student_master_table");
				foreach($prev_input as $input){
					$adm_no[] = $input->adm_no;
				}
				
				if(!in_array($in_adm_no, $adm_no)){
					
					db_merge('essa_'.$session.'_master_student_table')
						->key(array('adm_no' => $in_adm_no))
						->fields (array(
							'class' => $cls,
							'section' => $sec,
							'adm_no' => $in_adm_no,
							'doa' => $in_doa,
							'student_name' => $in_s_first_name.' '.$in_s_middle_name.' '.$in_s_last_name,
							'first_name' => $in_s_first_name,
							'middle_name' => $in_s_middle_name,
							'last_name' => $in_s_last_name,
							'father_name' => $in_f_first_name.' '.$in_f_middle_name.' '.$in_f_last_name,
							'f_first_name' => $in_f_first_name,
							'f_middle_name' => $in_f_middle_name,
							'f_last_name' => $in_f_last_name,
							'mother_name' => $in_m_first_name.' '.$in_m_middle_name.' '.$in_m_last_name,
							'm_first_name' => $in_m_first_name,
							'm_middle_name' => $in_m_last_name,
							'm_last_name' => $in_m_last_name,
							'gender' => $in_gender,
							'dob' => $in_dob,
							's_email' => $in_semail,
							'p_email' => $in_pemail,
							'r_line1' => $in_line1,
							'r_line2' => $in_line2,
							'r_city' => $in_city,
							'r_state' => $in_state,
							'r_pincode' => $in_pincode,
							'r_country' => $in_country,
							'r_phone' => $in_phone1,
							'ec1' => $in_phone2,
							'ec2' => $in_phone3,
							'ec3' => $in_phone4,
							'ec4' => $in_phone5,
							'sc' => $in_scst,
							'blood_group' => $in_blood_group,
							'is_hostel' => $in_boarder,
							'status' => 1,
						)
					)
					->execute();
					$num++;
					
					$stud_name = '';
					$uid = db_query("select * from users where name = :user", array(':user' => $in_adm_no));
					foreach($uid as $puid){
						$stud_name = $puid->name;
					}
					
					if($stud_name != $in_adm_no){
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
							'name' => $in_adm_no,
							'pass' => $in_adm_no,
							'mail' => $in_semail,
							'init' => $in_semail,
							'status' => 1,
							'access' => REQUEST_TIME,
							'roles' => array($student =>'Student'),
						);
						user_save('', $edit_student);
						
						$edit_parent = array(
							'name' => 'p'.'_'.$in_adm_no,
							'pass' => $in_adm_no,
							'mail' => $in_pemail,
							'init' => $in_pemail,
							'status' => 1,
							'access' => REQUEST_TIME,
							'roles' => array($parent => 'Parent'),
						);
						user_save('', $edit_parent);
					}
					
					$uid = db_query("select * from users where name = :user", array(':user' => 'p'.'_'.$in_adm_no));
					foreach($uid as $puid){
						$parent_uid = $puid -> uid;
					}
					$uid = db_query("select * from users where name = :user", array(':user' => $in_adm_no));
					foreach($uid as $puid){
						$student_uid = $puid -> uid;
					}
					
					db_update($student_master_table)
					->fields (array(
						'uid' => $student_uid,
						'puid' => $parent_uid,
					))
					->condition('adm_no', $in_adm_no, '=')
					->execute();
					
					$students = db_query("
						SELECT * from {$student_master_table} where class = :class and section =:sec order by first_name, middle_name, last_name;",array(':class' =>$cls, ':sec' => $sec)
					);
					
					//$roll_no = 1;
					//foreach($students as $student){
					//	
					//	db_update('essa_'.$session.'_master_student_table') // Table name no longer needs {}
					//		->fields(array('roll_no' => $roll_no))
					//		-> condition('adm_no', $student->adm_no, '=')
					//		->execute();
					//	$roll_no++;
					//}
					
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
					$node->title = check_plain($in_adm_no);
					$node->filedepot_folder_desc[LANGUAGE_NONE][0]['value'] = 'This is folder is for each student, here you can save documents and files related to each student.';
					$node->parentfolder = $folder_id;
					$node->inherit = 1;
					node_save($node);
					
					$folders = db_query("
						SELECT * from filedepot_categories where name = :name;", array(':name' => $in_adm_no)
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
					$node->title = check_plain($in_adm_no);
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
					
					// //******Suraj*****//
					// //sending message to student
					$module = 'Students';
					$recipients= array();
					$recipients[] = user_load($student_uid);
					$msg_subject = 'Welcome to ESSA';
					$msg_body = 'You have been successfully added to the school management system -  ESSA. <br> Your credentials are mentioned below. <br> Login using the given username and password. <br> You can change your password at any time after your first login. <br> Admission No: '.$in_adm_no.'<br> Name: '.$in_s_first_name.' '.$in_s_middle_name.' '.$in_s_last_name.'<br> Username: '.$in_adm_no.'<br> Password: '.$in_adm_no;
					$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
					$msg_body = $msg_body.' </br>'.$footer;
					privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
					
					dsm($parent_uid);
					dsm($student_uid);
					// //sending message to parent
					// $module = 'Students';
					// $recipients= array();
					// $recipients[] = user_load($parent_uid);
					// $msg_subject = 'Welcome to ESSA';
					// $msg_body = 'Sir/Mam, <br> You have been successfully added to the school management system -  ESSA. <br> Your credentials are mentioned below. <br> Login using the given username and password. <br> You can change your password at any time after your first login. <br> Admission No: '.$in_adm_no.'<br> Name: '.$in_s_first_name.' '.$in_s_middle_name.' '.$in_s_last_name.'<br> Username: p_'.$in_adm_no.'<br> Password: '.$in_adm_no;
					// $footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
					// $msg_body = $msg_body.' <br>'.$footer;
					// privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
					
					
					$sys_alert_table = 'essa_'.$session.'_system_alert';
					global $user;
					//sending system alert
					$created_date = date("Y-m-d H:i:s");
					$strtodate = strtotime($created_date);
					db_insert($sys_alert_table)
					->fields(array(
						'message' => 'Student '.$in_adm_no.' - '.$in_s_first_name.' '.$in_s_middle_name.' '.$in_s_last_name.' has been registered for the class '.$cls.'-'.$sec.'.',
						'priority' => 'L',
						'module' => 'Students',
						'source_url' => 'admin/students/admission/student_admission_bulk_upload',
						'timestamp' => $strtodate,
						'source_uid' => $user->uid,
					))
					->execute();
					// //******Suraj'.$csv[4].' '.$csv[5].' '.$csv[6].'					
				}
				
			}
		}
		
	}
	drupal_set_message('No. of rows processed = '. $num, 'status');
	//generate_roll_no();
	drupal_cron_run();
}

/**
 *Function to generate roll_no
 */
function generate_roll_no(){
	$session = variable_get('essa_sid');
	$student_master_table = 'essa_'.$session.'_master_student_table';
	$sec_table = 'essa_'.$session.'_class_section';
	$class = db_query("
						SELECT * from {$sec_table};"
					);
	foreach($class as $cl){
		$arr = explode('_',$cl->sections);
		$students = db_query("
			SELECT * from {$student_master_table} where class = :class and section =:sec order by adm_no;",array(':class' =>$arr[0], ':sec' => $arr[1])
		);
		$roll_no = 1;
		foreach($students as $student){
						
			db_update('essa_'.$session.'_master_student_table') // Table name no longer needs {}
				->fields(array('roll_no' => $roll_no))
				-> condition('adm_no', $student->adm_no, '=')
				->execute();
			$roll_no++;
		}
	}
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
