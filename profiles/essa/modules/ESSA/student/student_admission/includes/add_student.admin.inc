<?php

/**
* Implementing hook_form
*/ 
function addstudent_form($form, &$form_state){

  $form = array();
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
	
	
  module_load_include('inc', 'hierarchical_select', 'includes/common');
	
	$config = sa_hs_setting();
	$form['class'] =  array(
    '#title' => t('Select a Class - '),
    '#type' => 'hierarchical_select',
    '#config' => $config,
		'#required' => TRUE,
  );
	
  $form['ad'] =  array(
		'#title' => 'Admission Details',
		'#type' => 'fieldset',
	);
	$form['ad']['adm_no'] = array(
		'#title' => 'Admission No.',
		'#type' => 'textfield',
		'#size' => 20,
		'#required' => TRUE,
	);
	$form['ad']['doa'] = array(
	  '#title' => 'Date of Admission',
	  '#type' => 'date_popup',
		'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
		'#date_format' => 'd-m-Y',
	  '#date_year_range' => '-20:0',
	  '#required' => TRUE,
	);
	
	$form['ad']['sibling'] = array(
		'#type' => 'radios',
		'#title' => t('Sibling in this school'),
		'#options' => drupal_map_assoc(array('YES', 'NO')),
	);
	
	$form['ad']['sb'] = array(
			'#type' => 'fieldset',
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
			'#states' => array(
				'visible' => array(
				  ':input[name = "sibling"]' => array('value' => 'YES'),
				),
			),
		);
	
	$form['ad']['sb']['adm'] = array(
		'#type' => 'textfield',
		'#title' => t('Admission No.'),
		'#size' => 20,
	);
	
	$form['pd'] = array(
		'#type' => 'fieldset',
		'#title' => 'Personal Details',
	);
	$form['pd']['first_name'] = array(
	  '#title' => 'Name of Student',
		'#attributes' => array('placeholder' => 'First Name'),
	  '#type' => 'textfield',
	  '#size' => 20,
	  '#required' => TRUE,
	);
	$form['pd']['middle_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Middle Name'),
	);
	$form['pd']['last_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Last Name'),
	);
	$form['pd']['f_first_name'] = array(
	  '#title' => 'Father\'s Name',
		'#attributes' => array('placeholder' => 'First Name'),
	  '#type' => 'textfield',
		'#size' => 20,
	  '#required' => TRUE,
	);
	$form['pd']['f_middle_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Middle Name'),
	);
	$form['pd']['f_last_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Last Name'),
	);
	$form['pd']['m_first_name'] = array(
	  '#title' => 'Mother\'s Name',
		'#attributes' => array('placeholder' => 'First Name'),
	  '#type' => 'textfield',
	  '#size' => 20,
		'#required' => TRUE,
	);
	$form['pd']['m_middle_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Middle Name'),
	);
	$form['pd']['m_last_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Last Name'),
	);
	
	$form['pd']['gender'] = array(
	  '#title' => 'Gender',
		'#prefix' => '<br>',
	  '#type' => 'radios',
	  '#options' => array('male' => 'Male', 'female' => 'Female'),
	);
	$form['pd']['dob'] = array(
	  '#title' => 'Date of Birth',
	  '#type' => 'date_popup',
		'#attributes' => array('placeholder' => 'dd/mm/yy'),
		'#date_format' => 'd-m-Y',
	  '#date_year_range' => '-30:-4',
	  '#required' => TRUE,
	);
	$form['pd']['nationality'] = array(
		'#title' => 'Nationality',
		'#type' => 'textfield',
		'#size' => 20,
	);	
	$form['pd']['religion'] = array(
		'#title' => 'Religion',
		'#type' => 'textfield',
		'#size' => 20,
	);
	$form['pd']['sc'] = array(
		'#title' => 'SC/ST',
		'#type' => 'radios',
		'#options' => drupal_map_assoc(array('YES', 'NO')),
	);
	$form['pd']['mother_tongue'] = array(
		'#title' => 'Mother Tongue',
		'#type' => 'textfield',
		'#size' => 20,
	);  
	
	$form['cd'] = array(
		'#type' => 'fieldset',
		'#title' => t('Contact Details'),
	);
	$form['cd']['email'] = array(
		'#title' => 'Student\'s Email',
		'#type' => 'textfield',
		'#size' => 50,
		'#rules' => array(
	      'email',
    ),
		//'#required' => TRUE,
	);
	$form['cd']['pemail'] = array(
		'#title' => 'Parent\'s Email',
		'#type' => 'textfield',
		'#size' => 50,
		'#rules' => array(
	      'email',
    ),
		//'#required' => TRUE,
	);
	$form['cd']['pa'] = array(
		'#type' => 'fieldset',
		'#title' => 'Residential Address',
	);
	$form['cd']['pa']['line1'] = array(
		'#type' => 'textfield',
		'#title' => t('Line1'),
		'#resizable' => FALSE,
		'#size' => 30,
	);
	$form['cd']['pa']['line2'] = array(
		'#type' => 'textfield',
		'#title' => t('Line2'),
		'#resizable' => FALSE,
		'#size' => 30,
	);
	$form['cd']['pa']['city'] = array(
		'#title' => 'City',
		'#type' => 'textfield',
		'#size' => 20,
	);
	$form['cd']['pa']['state'] = array(
		'#title' => 'State',
		'#type' => 'textfield',
		'#size' => 20,
	);
	$form['cd']['pa']['pin'] = array(
		'#title' => 'Pincode',
		'#type' => 'textfield',
		'#size' => 20,
	);
	$form['cd']['pa']['country'] = array(
		'#title' => 'Country',
		'#type' => 'textfield',
		'#size' => 20,
	);
	$form['cd']['pa']['phone'] = array(
		'#title' => 'Phone no.',
		'#type' => 'textfield',
		'#size' => 20,
	);
	$form['cd']['pa']['fax'] = array(
		'#title' => 'FAX no.',
		'#type' => 'textfield',
		'#size' => 20,
	);
	
	$form['cd']['sara'] = array(
		'#type' => 'checkbox',
		'#title' => 'Correspondence Address same as Residential Address.',
		'#ajax' => array(
      'event' => 'change',
      'callback' => 'set_ca_ajax',
      'wrapper' => 'ca_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
	);
	
	$form['cd']['ca'] = array(
		'#type' => 'fieldset',
		'#title' => 'Correspondence Address',
		'#prefix' => '<div id = "ca_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['cd']['ca']['caline1'] = array(
		'#type' => 'textfield',
		'#title' => t('Line1'),
		'#resizable' => FALSE,
		'#size' => 30,
	);
	$form['cd']['ca']['caline2'] = array(
		'#type' => 'textfield',
		'#title' => t('Line2'),
		'#resizable' => FALSE,
		'#size' => 30,
	);
	$form['cd']['ca']['cacity'] = array(
		'#title' => 'City',
		'#type' => 'textfield',
		'#size' => 20,
	);
	$form['cd']['ca']['castate'] = array(
		'#title' => 'State',
		'#type' => 'textfield',
		'#size' => 20,
	);
	$form['cd']['ca']['capin'] = array(
		'#title' => 'Pincode',
		'#type' => 'textfield',
		'#size' => 20,
	);
	$form['cd']['ca']['cacountry'] = array(
		'#title' => 'Country',
		'#type' => 'textfield',
		'#size' => 20,
	);
	$form['cd']['ca']['caphone'] = array(
		'#title' => 'Phone no.',
		'#type' => 'textfield',
		'#size' => 20,
	);
	$form['cd']['ca']['cafax'] = array(
		'#title' => 'FAX no.',
		'#type' => 'textfield',
		'#size' => 20,
	);
	
	$form['cd']['ec'] = array(
		'#type' => 'fieldset',
		'#title' => 'Emergency Contact No.',
	);
	$form['cd']['ec']['ec1'] = array(
		'#type' => 'textfield',
		'#size' => 15,
		'#attributes' => array('placeholder' => 'Contact No.1'),
	);
	$form['cd']['ec']['ec2'] = array(
		'#type' => 'textfield',
		'#size' => 15,
		'#attributes' => array('placeholder' => 'Contact No.2'),
	);
	$form['cd']['ec']['ec3'] = array(
		'#type' => 'textfield',
		'#size' => 15,
		'#attributes' => array('placeholder' => 'Contact No.3'),
	);
	$form['cd']['ec']['ec4'] = array(
		'#type' => 'textfield',
		'#size' => 15,
		'#attributes' => array('placeholder' => 'Contact No.4'),
	);
	
	$form['fi'] = array(
		'#type' => 'fieldset',
		'#title' => 'Family Info',
	);
	$family_info = array('Name', 'Educational Qualification', 'Occupation', 'Designation', 'Annual Income', 'Age', 'Nationality', 'Institution', 'Office Address', 'Telephone No.');
	foreach($family_info as $info){
    //dsm($info);
    $row[] = array(
      '#tree' =>TRUE,
      $info => array(  //Generating unique array id for every form element
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$info.'</h3>',
        ),
        'c2' =>array(
          '#type' => 'textfield',
					'#size' => 25,
        ),
        'c3' =>array(
					'#type' => 'textfield',
					'#size' => 25,
        ),
      ),
    );
  }
  
  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['fi']['class'] = array(
    '#theme' => 'family_info_table',
    'rows' => $row,
  );
	
	$form['medical_history'] = array(
	  '#title' => 'Medical History',
	  '#type' => 'fieldset',
	);
	$form['medical_history']['blood_group'] = array(
		'#type' => 'select',
		'#title' => t('Blood Group'),
		'#options' => drupal_map_assoc(array('A+', 'A-', 'B+', 'B-', 'AB+', 'AB-', 'O+', 'O-')),
	);
	$form['medical_history']['im'] = array(
	  '#type' => 'fieldset',
		'#title' => t('Immunization Status'),
	);
	$form['medical_history']['im']['immunization'] = array(
		'#type' => 'checkboxes',
		'#options' => drupal_map_assoc(array('BCG', 'Measles', 'OPV', 'MMR', 'DPT', 'Typhoid', 'Booster for OPV', 'Booster for DPT', 'Hepatitis-B', 'Any Other')),
	);
	$form['medical_history']['birth_history'] = array(
		'#type' => 'textarea',
		'#title' => t('Birth History/ History of major illness of disorder, if any'),
	);
	$form['medical_history']['allergy'] = array(
	  '#type' => 'radios',
	  '#title' => 'Allergy to any Item/Drug',
	  '#options' => array('yes' => t('Yes'), 'no' => t('No')),
		'#default_value' => 'no',
	);
	$form['medical_history']['text'] = array(
	  '#type' => 'textfield',
	  '#attributes' => array('placeholder' => array('Specify the Item/Drug')),
	  '#states' => array(
      'visible' => array(   // action to take.
        ':input[name="allergy"]' => array('value' => t('yes')),
      )
		),
	);
	$form['medical_history']['disease'] = array(
	  '#type' => 'checkboxes',
		'#options' => drupal_map_assoc(array('Epilepsy', 'Bronchial Asthma/Bronchospasm', 'Skin Disease', 'Eye/ENT problem', 'Any Surgery Undergone',)),
	);
	
	/*
	$form['doc'] = array(
		'#title' => 'Documents',
	  '#type' => 'fieldset',
	);
	$form['doc']['upload'] = array(
		'#type' => 'plupload',
		'#title' => t('Upload Student Documents here'),
		'#description' => t('You can upload scanned copy of all documents here. You can also place them in appropriate folders(refer user manual).'),
	);
	*/
	
	$form['doc']['cl'] = array(
		'#type' => 'fieldset',
		'#title' => 'Documents Checklist',
	);
	$form['doc']['cl']['checklist'] = array(
		'#type' => 'checkboxes',
		'#options' => drupal_map_assoc(array('Medical Form', 'Birth/Transfer Certificate', 'Transportation Form', 'PTA Form', 'Admission Fee')),
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
	
  return $form;
}

/**
 *Implements ajax callback - set_ca_ajax.
 */
function set_ca_ajax($form, &$form_state){
	$form['cd']['ca'] = array(
		'#type' => 'fieldset',
		'#title' => 'Correspondence Address',
		'#prefix' => '<div id = "ca_wrapper">',
		'#suffix' => '</div>',
	);
	
	$test = 'Test';
	
	$form['cd']['ca']['caline1'] = array(
		'#type' => 'textfield',
		'#title' => t('Line1'),
		'#resizable' => FALSE,
		'#size' => 30,
		'#value' => $form_state['values']['line1'],
	);
	$form['cd']['ca']['caline2'] = array(
		'#type' => 'textfield',
		'#title' => t('Line2'),
		'#resizable' => FALSE,
		'#size' => 30,
		'#value' => $form_state['values']['line2'],
	);
	$form['cd']['ca']['cacity'] = array(
		'#title' => 'City',
		'#type' => 'textfield',
		'#size' => 20,
		'#value' => $form_state['values']['city'],
	);
	$form['cd']['ca']['castate'] = array(
		'#title' => 'State',
		'#type' => 'textfield',
		'#size' => 20,
		'#value' => $form_state['values']['state'],
	);
	$form['cd']['ca']['capin'] = array(
		'#title' => 'Pincode',
		'#type' => 'textfield',
		'#size' => 20,
		'#value' => $form_state['values']['pin'],
	);
	$form['cd']['ca']['cacountry'] = array(
		'#title' => 'Country',
		'#type' => 'textfield',
		'#size' => 20,
		'#value' => $form_state['values']['country'],
	);
	$form['cd']['ca']['caphone'] = array(
		'#title' => 'Phone no.',
		'#type' => 'textfield',
		'#size' => 20,
		'#value' => $form_state['values']['phone'],
	);
	$form['cd']['ca']['cafax'] = array(
		'#title' => 'FAX no.',
		'#type' => 'textfield',
		'#size' => 20,
		'#value' => $form_state['values']['fax'],
	);
	
	return $form['cd']['ca'];
}

/**
 *Implements form validation function.
 */
function addstudent_form_validate($form, &$form_state){
	//dsm($form_state['values']['class'][0]);
	if($form_state['values']['class'][0] == NULL || !isset($form_state['values']['class'][1])){
		form_set_error('class', 'Please select a class to proceed.');
	}
	
	$adm_no = array();
	$session_id = (string)variable_get('essa_sid');
	
	$users = db_query("
    SELECT * from users;"
  );
  foreach($users as $user){
		$adm_no[] = $user->name;
	}
	
	
	
	if(in_array($form_state['values']['adm_no'], $adm_no)){
		form_set_error('adm_no', t('Admission No. is already present in the system.'));
	}

  //if(!ctype_alpha($form_state['values']['first_name']) || ($form_state['values']['first_name'] == NULL)) {
  //  form_set_error('first_name', t('Name field should not be empty or have a numeric value'));
  //}
  //
  //if(!ctype_alpha($form_state['values']['last_name']) || ($form_state['values']['last_name'] == NULL)) {
  //  form_set_error('last_name', t('Name field should not be empty or have a numeric value'));
  //}
  //
  //if(!ctype_alpha($form_state['values']['f_first_name']) || ($form_state['values']['f_first_name'] == NULL)) {
  //  form_set_error('f_first_name', t('Name field should not be empty or have a numeric value'));
  //}
  //
  //if(!ctype_alpha($form_state['values']['f_last_name']) || ($form_state['values']['f_last_name'] == NULL)) {
  //  form_set_error('f_last_name', t('Name field should not be empty or have a numeric value'));
  //}
  //
  //if(!ctype_alpha($form_state['values']['m_first_name']) || ($form_state['values']['m_first_name'] == NULL)) {
  //  form_set_error('m_first_name', t('Name field should not be empty or have a numeric value'));
  //}
  //
  //if(!ctype_alpha($form_state['values']['m_last_name']) || ($form_state['values']['m_last_name'] == NULL)) {
  //  form_set_error('m_last_name', t('Name field should not be empty or have a numeric value'));
  //}
  //
	if ($form_state['values']['email'] != NULL){
		if (!valid_email_address($form_state['values']['email'])){
		  form_set_error('email' , t('Email address does not seem to be valid'));
		}
	}

	if ($form_state['values']['pemail'] != NULL){
		if (!valid_email_address($form_state['values']['pemail'])){
		  form_set_error('pemail' , t('Email address does not seem to be valid'));
		}
	}
	
	/*
  if ($form_state['values']['pin'] != NULL){
    if(!ctype_digit($form_state['values']['pin']) || strlen($form_state['values']['pin']) != 6){
      form_set_error('pin' , t('Pincode provided seems to be incorrect'));
    }
  }

  if ($form_state['values']['capin'] != NULL){
    if(!ctype_digit($form_state['values']['capin']) || strlen($form_state['values']['capin']) != 6){
      form_set_error('capin' , t('Pincode provided seems to be incorrect'));
    }
  }

  $str1 = substr($form_state['values']['phone'],0,1);
  $strrem1 = substr($form_state['values']['phone'], 1);
  if ($form_state['values']['phone'] != NULL){
    if ($str1 == '0'){
      if (!ctype_digit($form_state['values']['phone']) ||       strlen($strrem1) != 10){
        form_set_error('phone' , t('Phone No. provided seems to be incorrect'));
      }
    }elseif($str1 == '+'){
      if (!ctype_digit($strrem1) || strlen($strrem1) > 13){
        form_set_error('phone', t('Phone No. provided seems to be incorrect'));
      }
    }else {
      if (!ctype_digit($form_state['values']['phone']) ||       strlen($form_state['values']['phone']) != 10){
        form_set_error('phone' , t('Phone No. provided seems to be incorrect'));
      }
    }
  }
  $str2 = substr($form_state['values']['caphone'],0,1);
  $strrem2 = substr($form_state['values']['caphone'], 1);
	if ($form_state['values']['caphone'] != NULL){
    if ($str2 == '0'){
      if (!ctype_digit($form_state['values']['caphone']) ||       strlen($strrem2) != 10){
        form_set_error('caphone' , t('Phone No. provided seems to be incorrect'));
      }
    }elseif($str2 == '+'){
      if (!ctype_digit($strrem2) || strlen($strrem2) > 13){
        form_set_error('caphone', t('Phone No. provided seems to be incorrect'));
      }
    }else {
      if (!ctype_digit($form_state['values']['caphone']) ||       strlen($form_state['values']['caphone']) != 10){
        form_set_error('caphone' , t('Phone No. provided seems to be incorrect'));
      }
    }
  }

  $str3 = substr($form_state['values']['caphone'],0,1);
  $strrem3 = substr($form_state['values']['caphone'], 1);
  if ($form_state['values']['ec1'] != NULL){
    if ($str3 == '0'){
      if (!ctype_digit($form_state['values']['ec1']) ||       strlen($strrem3) != 10){
        form_set_error('ec1' , t('Phone No. provided seems to be incorrect'));
      }
    }elseif($str3 == '+'){
      if (!ctype_digit($strrem3) || strlen($strrem3) > 13){
        form_set_error('ec1', t('Phone No. provided seems to be incorrect'));
      }
    }else {
      if (!ctype_digit($form_state['values']['ec1']) ||       strlen($form_state['values']['ec1']) != 10){
        form_set_error('ec1' , t('Phone No. provided seems to be incorrect'));
      }
    }
  }
  if ($form_state['values']['ec1'] != NULL){
    if(!ctype_digit($form_state['values']['ec1']) || strlen($form_state['values']['ec1']) != 10){
      form_set_error('ec1' , t('Phone No. provided seems to be incorrect'));
    }
  }

  if ($form_state['values']['ec2'] != NULL){
    if(!ctype_digit($form_state['values']['ec2']) || strlen($form_state['values']['ec2']) != 10){
      form_set_error('ec2' , t('Phone No. provided seems to be incorrect'));
    }
  }

  if ($form_state['values']['ec3'] != NULL){
    if(!ctype_digit($form_state['values']['ec3']) || strlen($form_state['values']['ec3']) != 10){
      form_set_error('ec3' , t('Phone No. provided seems to be incorrect'));
    }
  }

  if ($form_state['values']['ec4'] != NULL){
    if(!ctype_digit($form_state['values']['ec4']) || strlen($form_state['values']['ec4']) != 10){
      form_set_error('ec4' , t('Phone No. provided seems to be incorrect'));
    }
  }

  if ($form_state['values'][5]['Age']['c2'] != NULL){
      if(!ctype_digit($form_state['values'][5]['Age']['c2'])){
        form_set_error("[5]['Age']['c2']", t('Age is not in correct format'));
      }
  }
  if ($form_state['values'][5]['Age']['c3'] != NULL){
    if(!ctype_digit($form_state['values'][5]['Age']['c3'])){
      form_set_error("[5]['Age']['c3']", t('Age is not in correct format'));
    }
  }
	
	// validation for student picture upload
	$session = (string)variable_get('essa_sid');
	$class = taxonomy_term_load($form_state['values']['class'][0]);
	$section = taxonomy_term_load($form_state['values']['class'][1]);
	$table = 'essa_'.$session.'_'.clean_classes($class->name).'_'.$section->name;
	
	$st_pic = db_query("
	  SELECT * from {$table}"
	);
	foreach($st_pic as $s_pic){
	  $pic = $s_pic -> s_photo;
	}
  $file = file_save_upload('s_pic', array(
      'file_validate_is_image' => array(),
      'file_validate_extensions' => array('png gif jpg jpeg'),
  ));
  if ($file) {
    if ($file = file_move($file, 'public://students/')) {
      $form_state['values']['s_pic'] = $file;
      $GLOBALS['pic'] = $form_state['values']['s_pic'];
			//$GLOBALS['pic_uri'] = $form_state['values']['s_pic'] -> uri;
      unset($form_state['values']['file']);
      $file->status = FILE_STATUS_PERMANENT;
      // Save file status.
      file_save($file);
    }else {
      form_set_error('s_pic', t('Failed to write the uploaded file the site\'s file folder.'));
    }
  }
  */
}
/**
 *Implements addstudent_form submit function
 */
function addstudent_form_submit($form, &$form_state){
	//dsm($form_state);
	$session = (string)variable_get('essa_sid');
	$class = taxonomy_term_load($form_state['values']['class'][0]);
	$section = taxonomy_term_load($form_state['values']['class'][1]);
	$table = 'essa_'.$session.'_'.'master_student_table';
	
	if(db_table_exists($table)){
		db_insert($table)
			->fields (array(
				'class' => $class->name,
				'section' => $section->name,
				'adm_no' => $form_state['values']['adm_no'],
				'doa' => $form_state['values']['doa'],
				'is_sibling' => $form_state['values']['sibling'],
				'sibling_adm_no' => $form_state['values']['adm'],
				'student_name' => $form_state['values']['first_name'].' '.$form_state['values']['middle_name'].' '.$form_state['values']['last_name'],
				'first_name' => $form_state['values']['first_name'],
				'middle_name' => $form_state['values']['middle_name'],
				'last_name' => $form_state['values']['last_name'],
				'father_name' => $form_state['values']['f_first_name'].' '.$form_state['values']['f_middle_name'].' '.$form_state['values']['f_last_name'],
				'f_first_name' => $form_state['values']['f_first_name'],
				'f_middle_name' => $form_state['values']['f_middle_name'],
				'f_last_name' => $form_state['values']['f_last_name'],
				'mother_name' => $form_state['values']['m_first_name'].' '.$form_state['values']['m_middle_name'].' '.$form_state['values']['m_last_name'],
				'm_first_name' => $form_state['values']['m_first_name'],
				'm_middle_name' => $form_state['values']['m_middle_name'],
				'm_last_name' => $form_state['values']['m_last_name'],
				'gender' => $form_state['values']['gender'],
				'dob' => $form_state['values']['dob'],
				'nationality' => $form_state['values']['nationality'],
				'religion' => $form_state['values']['religion'],
				'sc' => $form_state['values']['sc'],
				'mother_tongue' => $form_state['values']['mother_tongue'],
				's_email' => $form_state['values']['email'],
				'p_email' => $form_state['values']['pemail'],
				'r_line1' => $form_state['values']['line1'],
				'r_line2' => $form_state['values']['line2'],
				'r_city' => $form_state['values']['city'],
				'r_state' => $form_state['values']['state'],
				'r_pincode' => $form_state['values']['pin'],
				'r_country' => $form_state['values']['country'],
				'r_phone' => $form_state['values']['phone'],
				'r_fax' => $form_state['values']['fax'],
				'c_line1' => $form_state['values']['caline1'],
				'c_line2' => $form_state['values']['caline2'],
				'c_city' => $form_state['values']['cacity'],
				'c_state' => $form_state['values']['castate'],
				'c_pincode' => $form_state['values']['capin'],
				'c_country' => $form_state['values']['cacountry'],
				'c_phone' => $form_state['values']['caphone'],
				'c_fax' => $form_state['values']['cafax'],
				'ec1' => $form_state['values']['ec1'],
				'ec2' => $form_state['values']['ec2'],
				'ec3' => $form_state['values']['ec3'],
				'ec4' => $form_state['values']['ec4'],
				'fi_f_name' => $form_state['values'][0]['Name']['c2'],
				'fi_m_name' => $form_state['values'][0]['Name']['c3'],
				'fi_f_qualification' => $form_state['values'][1]['Educational Qualification']['c2'],
				'fi_m_qualification' => $form_state['values'][1]['Educational Qualification']['c3'],
				'fi_f_occupation' => $form_state['values'][2]['Occupation']['c2'],
				'fi_m_occupation' => $form_state['values'][2]['Occupation']['c3'],
				'fi_f_designation' => $form_state['values'][3]['Designation']['c2'],
				'fi_m_designation' => $form_state['values'][3]['Designation']['c3'],
				'fi_f_annual_income' => $form_state['values'][4]['Annual Income']['c2'],
				'fi_m_annual_income' => $form_state['values'][4]['Annual Income']['c3'],
				'fi_f_age' => (int)$form_state['values'][5]['Age']['c2'],
				'fi_m_age' => (int)$form_state['values'][5]['Age']['c3'],
				'fi_f_nationality' => $form_state['values'][6]['Nationality']['c2'],
				'fi_m_nationality' => $form_state['values'][6]['Nationality']['c3'],
				'fi_f_institution' => $form_state['values'][7]['Institution']['c2'],
				'fi_m_institution' => $form_state['values'][7]['Institution']['c3'],
				'fi_f_office_add' => $form_state['values'][8]['Office Address']['c2'],
				'fi_m_office_add' => $form_state['values'][8]['Office Address']['c3'],
				'fi_f_phone' => $form_state['values'][9]['Telephone No.']['c2'],
				'fi_m_phone' => $form_state['values'][9]['Telephone No.']['c3'],
				'blood_group' => $form_state['values']['blood_group'],
				'immu_bcg' => $form_state['values']['immunization']['BCG'],
				'immu_measles' => $form_state['values']['immunization']['Measles'],
				'immu_opv' => $form_state['values']['immunization']['OPV'],
				'immu_mmr' => $form_state['values']['immunization']['MMR'],
				'immu_typhoid' => $form_state['values']['immunization']['Typhoid'],
				'immu_opv_booster' => $form_state['values']['immunization']['Booster for OPV'],
				'immu_hep_b' => $form_state['values']['immunization']['Hepatitis-B'],
				'immu_any_other' => $form_state['values']['immunization']['Any Other'],
				'immu_dpt' => $form_state['values']['immunization']['DPT'],
				'immu_dpt_booster' => $form_state['values']['immunization']['Booster for DPT'],
				'birth_history' => $form_state['values']['birth_history'],
				'is_allergy' => $form_state['values']['allergy'],
				'allergic_to' => $form_state['values']['text'],
				'epilepsy' => $form_state['values']['disease']['Epilepsy'],
				'asthma' => $form_state['values']['disease']['Bronchial Asthma/Bronchospasm'],
				'skin_desease' => $form_state['values']['disease']['Skin Disease'],
				'eye' => $form_state['values']['disease']['Eye/ENT problem'],
				'surgery' => $form_state['values']['disease']['Any Surgery Undergone'],
				'doc_med' => $form_state['values']['checklist']['Medical Form'],
				'doc_birth' => $form_state['values']['checklist']['Birth/Transfer Certificate'],
				'doc_trans' => $form_state['values']['checklist']['Transportation Form'],
				'doc_pta' => $form_state['values']['checklist']['PTA Form'],
				'doc_ad_fee' => $form_state['values']['checklist']['Admission Fee'],
				'exam_roll_no' => '',
				'status' => 1,
			)
		)	
		->execute();
	}
	
	$rid = db_query("select rid from role where name = 'Parent'");
	foreach($rid as $role_id){
		foreach($role_id as $p_role){
			$p_rid = $p_role;
		}
	}
	
	$rid = db_query("select rid from role where name = 'Student'");
	foreach($rid as $role_id){
		foreach($role_id as $s_role){
			$s_rid = $s_role;
		}
	}
	
	$edit_student = array(
		'name' => $form_state['values']['adm_no'],
	  'pass' => $form_state['values']['adm_no'],
	  'mail' => $form_state['values']['email'],
		'init' => $form_state['values']['email'], 
	  'status' => 1, 
	  'access' => REQUEST_TIME,
		'roles' => array($s_rid => 'Student'),
	);
	user_save('', $edit_student);
		
	$edit_parent = array(
		'name' => 'p'.'_'.$form_state['values']['adm_no'], 
	  'pass' => $form_state['values']['adm_no'],
	  'mail' => $form_state['values']['pemail'],
		'init' => $form_state['values']['pemail'], 
	  'status' => 1, 
		'access' => REQUEST_TIME,
		'roles' => array($p_rid => 'Parent'),
	);
	user_save('', $edit_parent);
	$uid = db_query("select * from users where name = :user", array(':user' => 'p'.'_'.$form_state['values']['adm_no']));
	foreach($uid as $puid){
		$parent_uid = $puid -> uid;
	}
		
	$uid = db_query("select * from users where name = :user", array(':user' => $form_state['values']['adm_no']));
	foreach($uid as $puid){
		$student_uid = $puid -> uid;
	}
	
	db_update($table)
		->fields (array(
			'uid' => $student_uid,
			'puid' => $parent_uid
			))
		->condition('adm_no', $form_state['values']['adm_no'], '=')
		->execute();
			
	//profile picture for student
  $account_st = user_load($student_uid);
  $account_pa = user_load($parent_uid);
/*	
	db_insert('essa_'.$session.'_master_student_table')
		->fields (array(
			'adm_no' => $form_state['values']['adm_no'],
			'uid' => $student_uid,
			'puid' => $parent_uid,
			'status' => 1,
			'first_name' => $form_state['values']['first_name'],
			'last_name' => $form_state['values']['last_name'],
			'class' => $class->name,
			'section' => $section->name,
		)
	)	
	->execute();
*/	
	
	// $roll_no = 1;
	// $students = db_query("
		// SELECT * from {$table} where class = :class and section =:sec order by first_name, middle_name, last_name;",array(':class' =>$class->name, ':sec' => $section->name)
	// );
	// foreach($students as $student){
		// //dsm('ok');
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
	$node->title = $form_state['values']['adm_no'];
	$node->filedepot_folder_desc[LANGUAGE_NONE][0]['value'] = 'This is folder is for each student, here you can save documents and files related to each student.';
	$node->parentfolder = $folder_id;
	$node->inherit = 1;
	node_save($node);
	
	$folders = db_query("
    SELECT * from filedepot_categories where name = :name;", array(':name' => $form_state['values']['adm_no'])
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
	$node->title = $form_state['values']['adm_no'];
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
	
	
	//*******Suraj********//
	if($flag = 1){
		$sys_alert_table = 'essa_'.$session.'_system_alert';
		global $user;
		drupal_set_message('Student '.$form_state['values']['adm_no'].' - '.$form_state['values']['first_name'].' '.$form_state['values']['middle_name'].' '.$form_state['values']['last_name'].' has been successfully registered for the class '.$class->name.'-'.$section->name.'.','status');
		
		//sending message to student
		$module = 'Students';
		$recipients= array();
		$recipients[] = user_load($student_uid);
		$msg_subject = 'Welcome to ESSA';
		$msg_body = 'You have been successfully added to the school management system -  ESSA. <br> Your credentials are mentioned below. <br> Login using the given username and password. <br> You can change your password at any time after your first login. <br> Admission No: '.$form_state['values']['adm_no'].'<br> Name: '.$form_state['values']['first_name'].' '.$form_state['values']['last_name'].'<br> Username: '.$form_state['values']['adm_no'].'<br> Password: '.$form_state['values']['adm_no'];
		$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
		$msg_body = $msg_body.' <br>'.$footer;
		privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
		
		//sending message to parent
		$module = 'Students';
		$recipients= array();
		$recipients[] = user_load($parent_uid);
		$msg_subject = 'Welcome to ESSA';
		$msg_body = 'Sir/Mam, <br> You have been successfully added to the school management system -  ESSA. <br> Your credentials are mentioned below. <br> Login using the given username and password. <br> You can change your password at any time after your first login. <br> Admission No: '.$form_state['values']['adm_no'].'<br> Name: '.$form_state['values']['first_name'].' '.$form_state['values']['last_name'].'<br> Username: p_'.$form_state['values']['adm_no'].'<br> Password: '.$form_state['values']['adm_no'];
		$footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
		$msg_body = $msg_body.' <br>'.$footer;
		privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
		
		//sending system alert
		$created_date = date("Y-m-d H:i:s");
		$strtodate = strtotime($created_date);
		db_insert($sys_alert_table)
		->fields(array(
		'message' => 'Student '.$form_state['values']['adm_no'].' - '.$form_state['values']['first_name'].' '.$form_state['values']['middle_name'].' '.$form_state['values']['last_name'].' has been registered for the class '.$class->name.'-'.$section->name.'.',
		'priority' => 'L',
		'module' => 'Students',
		'source_url' => 'admin/students/admission/student_admission',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
		))
		->execute();
	}
	//*******Suraj********//
	
	drupal_cron_run();
}