<?php

/** 
* Page callback function - basicinfo form
*/
function basicinfo_form($form, &$form_submit){
	$session_id = (string)variable_get('essa_sid');
  $basicinfo = 'essa_'.$session_id.'_basicinfo';
  $basic_info = db_query("
    SELECT * from {$basicinfo}"
  );
	foreach($basic_info as $info){
		$name_of_school = $info -> nameofschool;
		$slogan = $info -> slogan;
		$board = $info -> board;
		$affiliation_no = $info->affiliation_no;
		$school_code = $info->school_code;
		$state_board = $info -> state_board;
		$establishment_year = $info -> establishment_year;
		$hostel = $info -> hostel_facility;
		$transport = $info -> transport_facility;
		$house1 = $info -> house1;
		$house2 = $info -> house2;
		$house3 = $info -> house3;
		$house4 = $info -> house4;
		$contact = $info -> contactofschool;
		$website = $info -> website;
		$email = $info -> office_email;
		$fax = $info -> fax;
		$line1 = $info -> line1;
		$line2 = $info -> line2;
		$city = $info -> city;
		$state = $info -> state;
		$pin = $info -> pincode;
		$country = $info -> country;
		$financialyearstart = $info -> financialyearstart;
		$financialyearend = $info -> financialyearend;
		$academicyearstart = $info -> academicyearstart;
		$academicyearend = $info -> academicyearend;
		$notice_period = $info->notice_period;
	}
	
	//******SURAJ******//
	global $user;
	
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
	$user_rd = array();
	$prin = 0;
	$admin = 0;
	$user_rid = db_query("SELECT * FROM users_roles WHERE uid = :u;", array(':u' => $user->uid));
	foreach($user_rid as $r){
		$user_rd[] = $r->rid;
		foreach($user_rd as $u_rid){
			if($u_rid == $p_rid){
				$prin = 1;
			}elseif($u_rid == $a_rid){
				$admin = 1;
			}
		}
	}
	
	if($admin == 1 || $prin == 1){
		$form['ss'] = array(
			'#type' => 'fieldset',
			'#title' => t('School Settings'),
		);
		
		$form['ss']['nameofschool'] = array(
			'#title' => t('Name of School'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#default_value' => isset($name_of_school)? $name_of_school: NULL,
		);
		
		$form['ss']['slogan'] = array(
			'#type' => 'textfield',
			'#title' => t('Slogan of the School'),
			'#default_value' => isset($slogan)? $slogan: NULL,
		);
		
		$form['ss']['board'] = array(
			'#type' => 'select',
			'#title' => t('Board'),
			'#options' => drupal_map_assoc(array(
				t('C.B.S.E.'), t('I.C.S.E.'), t('State Board')
			)),
			'#attributes' => array('class' => array('gradingselectfield')),
			'#required' => TRUE,
			'#default_value' => isset($board)? $board: NULL,
		);
		
		$form['ss']['school_code'] = array(
			'#title' => t('School Code'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#default_value' => isset($school_code)? $school_code: NULL,
		);
		
		$form['ss']['affiliation_no'] = array(
			'#title' => t('Affiliation No.'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#default_value' => isset($affiliation_no)? $affiliation_no: NULL,
		);
		
		$form['ss']['sb'] = array(
			'#type' => 'fieldset',
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
			'#states' => array(
				'visible' => array(
					':input[name = "board"]' => array('value' => 'State Board'),
				),
			),
		);
		
		$form['ss']['sb']['name'] = array(
			'#type' => 'textfield',
			'#title' => t('Name of the Board'),
			'#default_value' => isset($state_board)? $state_board: NULL,
		);
		
		$form['ss']['establishment_year'] = array(
			'#type' => 'textfield',
			'#title' => t('Year of Establishment'),
			'#required' => TRUE,
			'#default_value' => isset($establishment_year)? $establishment_year: NULL,
		);
		
		$form['ss']['hostel'] = array(
			'#type' => 'radios',
			'#title' => t('Hostel Facility'),
			'#options' => drupal_map_assoc(array('YES', 'NO')),
			'#default_value' => isset($hostel)? $hostel: NULL,
		);
		
		$form['ss']['transport'] = array(
			'#type' => 'radios',
			'#title' => t('Transport Facility'),
			'#options' => drupal_map_assoc(array('YES', 'NO')),
			'#default_value' => isset($transport)? $transport: NULL,
		);
		
		$form['ss']['hs'] = array(
			'#type' => 'fieldset',
			'#title' => 'Name of Houses',
		);
		
		$form['ss']['hs']['house1'] = array(
			'#type' => 'textfield',
			'#size' => 10,
			'#attributes' => array('placeholder' => 'House 1'),
			'#default_value' => isset($house1)? $house1: NULL,
		);
		
		$form['ss']['hs']['house2'] = array(
			'#type' => 'textfield',
			'#size' => 10,
			'#attributes' => array('placeholder' => 'House 2'),
			'#default_value' => isset($house2)? $house2: NULL,
		);
		
		$form['ss']['hs']['house3'] = array(
			'#type' => 'textfield',
			'#size' => 10,
			'#attributes' => array('placeholder' => 'House 3'),
			'#default_value' => isset($house3)? $house3: NULL,
		);
		
		$form['ss']['hs']['house4'] = array(
			'#type' => 'textfield',
			'#size' => 10,
			'#attributes' => array('placeholder' => 'House 4'),
			'#default_value' => isset($house4)? $house4: NULL,
		);
		
		$form['ss']['ci'] = array(
			'#type' => 'fieldset',
			'#title' => 'Contact Information',
		);
		
		$form['ss']['ci']['contactofschool'] = array(
			'#title' => t('Contact Number'),
			'#type' => 'textfield',
			'#required' => TRUE,	  
			'#rules' => array(
				'numeric',
				'length[10,15]',
				),
			'#default_value' => isset($contact)? $contact: NULL,
		);
		
		$form['ss']['ci']['website'] = array(
			'#type' => 'textfield',
			'#title' => t('Official website'),
			'#rules' => array('email'),
			'#default_value' => isset($website)? $website: NULL,
		);
		
		$form['ss']['ci']['email'] = array(
			'#type' => 'textfield',
			'#title' => t('Official e-mail ID'),
			'#rules' => array('email'),
			'#default_value' => isset($email)? $email: NULL,
		);
		
		$form['ss']['ci']['fax'] = array(
			'#title' => t('FAX no.'),
			'#type' => 'textfield',
			'#rules' => array(
				'numeric',
				'length[10,15]',
			),
			'#default_value' => isset($fax)? $fax: NULL,
		);
		
		$form['ss']['ci']['ad'] = array(
			'#type' => 'fieldset',
			'#title' => t('Address'),
		);
		
		$form['ss']['ci']['ad']['line1'] = array(
			'#type' => 'textfield',
			'#title' => t('Line 1'),
			'#size' => 100,
			'#default_value' => isset($line1)? $line1: NULL,
		);
		
		$form['ss']['ci']['ad']['line2'] = array(
			'#type' => 'textfield',
			'#title' => t('Line 2'),
			'#size' => 100,
			'#default_value' => isset($line2)? $line2: NULL,
		);
		
		$form['ss']['ci']['ad']['City'] = array(
			'#type' => 'textfield',
			'#title' => t('City'),
			'#size' => 30,
			'#default_value' => isset($city)? $city: NULL,
		);
		
		$form['ss']['ci']['ad']['State'] = array(
			'#type' => 'textfield',
			'#title' => t('State'),
			'#size' => 30,
			'#default_value' => isset($state)? $state: NULL,
		);
		
		$form['ss']['ci']['ad']['pin'] = array(
			'#type' => 'textfield',
			'#title' => t('Pin Code'),
			'#size' => 10,
			'#default_value' => isset($pin)? $pin: NULL,
		);
		
		$form['ss']['ci']['ad']['country'] = array(
			'#type' => 'textfield',
			'#title' => t('Country'),
			'#size' => 30,
			'#default_value' => isset($country)? $country: NULL,
		);
		
		$form['ss']['general_setting'] = array(
			'#type' => 'fieldset',
			'#title' => 'General Settings',
		);
		
		$form['ss']['general_setting']['financialyear'] = array(
			'#title' => t('Financial Year'),
			'#type' => 'fieldset',
		);  
			
		$form['ss']['general_setting']['financialyear']['financialyearstart'] = array(
			'#type' => 'date_popup',
			'#title' => t('Start Date'),
			'#date_format' => 'd/m/Y',
			'#required' => TRUE,
			'#attributes' => array('placeholder' => 'From'),
			'#default_value' => isset($financialyearstart)? $financialyearstart: NULL,
			);
			
		$form['ss']['general_setting']['financialyear']['financialyearend'] = array(
			'#type' => 'date_popup',
			'#title' => t('End Date'),
			'#date_format' => 'd/m/Y',
			'#required' => TRUE,
			'#attributes' => array('placeholder' => 'To'),
			'#default_value' => isset($financialyearend)? $financialyearend: NULL,
		);
		
		$form['ss']['general_setting']['academicyear'] = array(
			'#title' => t('Academic Year'),
			'#type' => 'fieldset',  
		);  
		
		$form['ss']['general_setting']['academicyear']['academicyearstart'] = array(
			'#type' => 'date_popup',
			'#title' => t('Start Date'),
			'#date_format' => 'd/m/Y',
			'#required' => TRUE,
			'#attributes' => array('placeholder' => 'From'),
			'#default_value' => isset($academicyearstart)? $academicyearstart: NULL,
		);
		
		
		$form['ss']['general_setting']['academicyear']['academicyearend'] = array(
			'#type' => 'date_popup',
			'#title' => t('End Date'),
			'#date_format' => 'd/m/Y',
			'#required' => TRUE,
			'#attributes' => array('placeholder' => 'To'),
			'#default_value' => isset($academicyearend)? $academicyearend: NULL,
		);
		
		$form['ss']['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Save',
			'#validate' => array('basicinfo_form_validate'),
			'#submit' => array('basicinfo_form_submit'),
		);
		//$options = array();
		//$options = array('--Select--','7 days', '15 days', '1 Month', '2 Months');
		
		$form['ss']['general_setting']['notice_period']= array(
			'#type' => 'select',
			'#title' => 'Notice period for staff resingnation',
			'#options' => drupal_map_assoc(array('--Select--','7 days', '15 days', '1 Month', '2 Months')),
			'#required' => TRUE,
			'#default_value' => isset($notice_period)? $notice_period: NULL,
		);
		
	}else{
		$form['ss'] = array(
			'#type' => 'fieldset',
			'#title' => t('School Settings'),
			'#disabled' => TRUE,
		);
		
		$form['ss']['nameofschool'] = array(
			'#title' => t('Name of School'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#default_value' => isset($name_of_school)? $name_of_school: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['slogan'] = array(
			'#type' => 'textfield',
			'#title' => t('Slogan of the School'),
			'#default_value' => isset($slogan)? $slogan: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['board'] = array(
			'#type' => 'select',
			'#title' => t('Board'),
			'#options' => drupal_map_assoc(array(
				'C.B.S.E.', 'I.C.S.E.', 'State Board'
			)),
			'#attributes' => array('class' => array('gradingselectfield')),
			'#required' => TRUE,
			'#default_value' => isset($board)? $board: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['school_code'] = array(
			'#title' => t('School Code'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#default_value' => isset($school_code)? $school_code: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['affiliation_no'] = array(
			'#title' => t('Affiliation No.'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#default_value' => isset($affiliation_no)? $affiliation_no: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['sb'] = array(
			'#type' => 'fieldset',
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
			'#disabled' => TRUE,
			'#states' => array(
				'visible' => array(
					':input[name = "board"]' => array('value' => 'State Board'),
				),
			),
		);
		 
		$form['ss']['sb']['name'] = array(
			'#type' => 'textfield',
			'#title' => t('Name of the Board'),
			'#default_value' => isset($state_board)? $state_board: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['establishment_year'] = array(
			'#type' => 'textfield',
			'#title' => t('Year of Establishment'),
			'#required' => TRUE,
			'#default_value' => isset($establishment_year)? $establishment_year: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['hostel'] = array(
			'#type' => 'radios',
			'#title' => t('Hostel Facility'),
			'#options' => drupal_map_assoc(array('YES', 'NO')),
			'#default_value' => isset($hostel)? $hostel: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['transport'] = array(
			'#type' => 'radios',
			'#title' => t('Transport Facility'),
			'#options' => drupal_map_assoc(array('YES', 'NO')),
			'#default_value' => isset($transport)? $transport: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['hs'] = array(
			'#type' => 'fieldset',
			'#title' => 'Name of Houses',
			'#disabled' => TRUE,
		);
		
		$form['ss']['hs']['house1'] = array(
			'#type' => 'textfield',
			'#size' => 10,
			'#attributes' => array('placeholder' => 'House 1'),
			'#default_value' => isset($house1)? $house1: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['hs']['house2'] = array(
			'#type' => 'textfield',
			'#size' => 10,
			'#attributes' => array('placeholder' => 'House 2'),
			'#default_value' => isset($house2)? $house2: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['hs']['house3'] = array(
			'#type' => 'textfield',
			'#size' => 10,
			'#attributes' => array('placeholder' => 'House 3'),
			'#default_value' => isset($house3)? $house3: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['hs']['house4'] = array(
			'#type' => 'textfield',
			'#size' => 10,
			'#attributes' => array('placeholder' => 'House 4'),
			'#default_value' => isset($house4)? $house4: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['ci'] = array(
			'#type' => 'fieldset',
			'#title' => 'Contact Information',
			'#disabled' => TRUE,
		);
		
		$form['ss']['ci']['contactofschool'] = array(
			'#title' => t('Contact Number'),
			'#type' => 'textfield',
			'#required' => TRUE,	  
			'#rules' => array(
				'numeric',
				'length[10,15]',
				),
			'#default_value' => isset($contact)? $contact: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['ci']['website'] = array(
			'#type' => 'textfield',
			'#title' => t('Official website'),
			'#rules' => array('email'),
			'#default_value' => isset($website)? $website: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['ci']['email'] = array(
			'#type' => 'textfield',
			'#title' => t('Official e-mail ID'),
			'#rules' => array('email'),
			'#default_value' => isset($email)? $email: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['ci']['fax'] = array(
			'#title' => t('FAX no.'),
			'#type' => 'textfield',
			'#rules' => array(
				'numeric',
				'length[10,15]',
			),
			'#default_value' => isset($fax)? $fax: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['ci']['ad'] = array(
			'#type' => 'fieldset',
			'#title' => t('Address'),
			'#disabled' => TRUE,
		);
		$form['ss']['ci']['ad']['line1'] = array(
			'#type' => 'textfield',
			'#title' => t('Line 1'),
			'#size' => 100,
			'#default_value' => isset($line1)? $line1: NULL,
			'#disabled' => TRUE,
		);
		$form['ss']['ci']['ad']['line2'] = array(
			'#type' => 'textfield',
			'#title' => t('Line 2'),
			'#size' => 100,
			'#default_value' => isset($line2)? $line2: NULL,
			'#disabled' => TRUE,
		);
		$form['ss']['ci']['ad']['City'] = array(
			'#type' => 'textfield',
			'#title' => t('City'),
			'#size' => 30,
			'#default_value' => isset($city)? $city: NULL,
			'#disabled' => TRUE,
		);
		$form['ss']['ci']['ad']['State'] = array(
			'#type' => 'textfield',
			'#title' => t('State'),
			'#size' => 30,
			'#default_value' => isset($state)? $state: NULL,
			'#disabled' => TRUE,
		);
		$form['ss']['ci']['ad']['pin'] = array(
			'#type' => 'textfield',
			'#title' => t('Pin Code'),
			'#size' => 10,
			'#default_value' => isset($pin)? $pin: NULL,
			'#disabled' => TRUE,
		);
		$form['ss']['ci']['ad']['country'] = array(
			'#type' => 'textfield',
			'#title' => t('Country'),
			'#size' => 30,
			'#default_value' => isset($country)? $country: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['general_setting'] = array(
			'#type' => 'fieldset',
			'#title' => 'General Settings',
			'#disabled' => TRUE,
		);
		
		$form['ss']['general_setting']['financialyear'] = array(
			'#title' => t('Financial Year'),
			'#type' => 'fieldset',
			'#disabled' => TRUE,
		);  
		
		$form['ss']['general_setting']['financialyear']['financialyearstart'] = array(
			'#type' => 'date_popup',
			'#title' => t('Start Date'),
			'#date_format' => 'd/m/Y',
			'#required' => TRUE,
			'#attributes' => array('placeholder' => 'From'),
			'#default_value' => isset($financialyearstart)? $financialyearstart: NULL,
			'#disabled' => TRUE,
		);
			
		$form['ss']['general_setting']['financialyear']['financialyearend'] = array(
			'#type' => 'date_popup',
			'#title' => t('End Date'),
			'#date_format' => 'd/m/Y',
			'#required' => TRUE,
			'#attributes' => array('placeholder' => 'To'),
			'#default_value' => isset($financialyearend)? $financialyearend: NULL,
			'#disabled' => TRUE,
		);
		
		$form['ss']['general_setting']['academicyear'] = array(
			'#title' => t('Academic Year'),
			'#type' => 'fieldset',
			'#disabled' => TRUE,
		);  
		
		$form['ss']['general_setting']['academicyear']['academicyearstart'] = array(
			'#type' => 'date_popup',
			'#title' => t('Start Date'),
			'#date_format' => 'd/m/Y',
			'#required' => TRUE,
			'#attributes' => array('placeholder' => 'From'),
			'#default_value' => isset($academicyearstart)? $academicyearstart: NULL,
			'#disabled' => TRUE,
		);
		
		
		$form['ss']['general_setting']['academicyear']['academicyearend'] = array(
			'#type' => 'date_popup',
			'#title' => t('End Date'),
			'#date_format' => 'd/m/Y',
			'#required' => TRUE,
			'#attributes' => array('placeholder' => 'To'),
			'#default_value' => isset($academicyearend)? $academicyearend: NULL,
			'#disabled' => TRUE,
		);
		
		//$options[] = array('7 days', '15 days', '1 Month', '2 Months');
		
		$form['ss']['general_setting']['notice_period']= array(
			'#type' => 'select',
			'#title' => 'Notice period for staff resingnation',
			'#options' => drupal_map_assoc($array('--Select--','7 days', '15 days', '1 Month', '2 Months')),
			'#required' => TRUE,
			'#default_value' => isset($notice_period)? $notice_period: NULL,
			'#disabled' => TRUE,
		);
		
	}
	//******SURAJ******//
	
	return $form;
}

/**
 * Validate function
 */
function basicinfo_form_validate($form,&$form_state){
	/*
	$file = file_save_upload('file', array(
    // Validates file is really an image.
    'file_validate_is_image' => array(),
    // Validate extensions.
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));
  // If the file passed validation:
  if ($file) {
    // Move the file into the Drupal file system.
    if ($file = file_move($file, 'public://school/logo')) {
      // Save the file for use in the submit handler.
      $form_state['storage']['file'] = $file;
    }
    else {
      form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
    }
  }
  else {
    form_set_error('file', t('No file was uploaded.'));
  }
  */
	//*******Suraj********//
	$url = $form_state['values']['website'];
	if($url !=NULL){
		if (!preg_match("/\b(?:(?:https?|ftp):\/\/|www\.)[-a-z0-9+&@#\/%?=~_|!:,.;]*[-a-z0-9+&@#\/%=~_|]/i", $url)) {
			form_set_error('website',' Please enter a valid website.');
		}
	}
	$email = $form_state['values']['email'];
	if($email != NULL){
		if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
			form_set_error('email',' Please enter a valid email address.');
		}
	}
	if($form_state['values']['establishment_year'] > date('Y')){
		form_set_error('establishment_year',' Year of establishment should be current year or previous year.');
	}
	//*******Suraj********//
	if($form_state['values']['financialyearstart'] > $form_state['values']['financialyearend']){
		form_set_error('financialyearstart','Start Date is after end date. Please choose dates properly');
	}		
			
  if($form_state['values']['academicyearstart'] > $form_state['values']['academicyearend']){
		form_set_error('academicyearstart','Start Date is after end date. Please choose dates properly');
  }
}
    
/**
* Submit handler for the form basic_info
*/
function basicinfo_form_submit($form,&$form_state){
	$session_id = (string)variable_get('essa_sid');
  $basicinfo = 'essa_'.$session_id.'_basicinfo';
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	global $user;
  //dsm(drupal_map_assoc($form_state['values']['notice_period']));
  $fe_id = db_merge($basicinfo)
		->key(array('nameofschool' => $form_state['values']['nameofschool']))
    ->fields (array(
			'nameofschool' => $form_state['values']['nameofschool'],
			'slogan' => $form_state['values']['slogan'],
			'school_code' => $form_state['values']['school_code'],
			'affiliation_no' => $form_state['values']['affiliation_no'],
			'board' => $form_state['values']['board'],
			'state_board' => $form_state['values']['name'],
			'establishment_year' => $form_state['values']['establishment_year'],
			'hostel_facility' => $form_state['values']['hostel'],
			'transport_facility' => $form_state['values']['transport'],
			'house1' => $form_state['values']['house1'],
			'house2' => $form_state['values']['house2'],
			'house3' => $form_state['values']['house3'],
			'house4' => $form_state['values']['house4'],
			'contactofschool' => $form_state['values']['contactofschool'],
			'website' => $form_state['values']['website'],
			'office_email' => $form_state['values']['email'],
			'fax' => $form_state['values']['fax'],
			'line1' => $form_state['values']['line1'],
			'line2' => $form_state['values']['line2'],
			'city' => $form_state['values']['City'],
			'state' => $form_state['values']['State'],
			'pincode' => $form_state['values']['pin'],
			'country' => $form_state['values']['country'],
			'financialyearstart' => $form_state['values']['financialyearstart'],
			'financialyearend' => $form_state['values']['financialyearend'],
			'academicyearstart' => $form_state['values']['academicyearstart'],
			'academicyearend' => $form_state['values']['academicyearend'],
			'notice_period' => $form_state['values']['notice_period'],
		)
	)
	->execute();
	
	//*******Suraj********//
	drupal_set_message('The basic info of the school has been updated successfully!!!','status');
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'The basic info of the school was updated.',
		'priority' => 'H',
		'module' => 'school_master',
		'source_url' => 'admin/settings/basic_info',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	//*******Suraj********//
}

/**
* Altering Date Popup to remove labels and description for specific field
*/
function school_master_date_popup_process_alter(&$element, &$form_state, $context) {
  unset($element['date']['#description']);
  unset($element['date']['#title']);
	unset($element['time']['#title']);
	unset($element['time']['#description']);
  return $element;   
}
