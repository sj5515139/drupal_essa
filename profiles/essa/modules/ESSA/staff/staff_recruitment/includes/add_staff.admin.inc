<?php

function addstaff_form($form, &$form_state){
	
	// $query = db_query("SELECT TABLE_NAME
	// FROM information_schema.TABLES WHERE TABLE_SCHEMA = :ts;", array(':ts' => 'essa-dps'));
	// foreach($query as $q){
		// foreach($q as $k=>$v){
			// dsm($v);
		// }
	// }
	
	// $to = "sj5515139@gmail.com";
	// $subject = "Hi!";
	// $body = "Hi,nnHow are you?";
	// if (mail($to, $subject, $body)) {
		// dsm("<p>Message successfully sent!</p>");
	// } else {
		// dsm("<p>Message delivery failed...</p>");
	// }
	
	
	// $email = 'sj5515139@gmail.com';
	
	// $body = "<p>Sir/Mam</p>, \n<p>You have been successfully added to the school management system -  ESSA. </p><p>Your credentials are mentioned below. \nLogin using the given username and password. \nYou can change your password at any time after your first login. \nEmp-ID: \nName: </p>";
	// $footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
	
	// $params = array(
		// 'subject' => 'Welcome to ESSA',
		// 'body' => 'hfghhjgjh',
	// );
	
	// drupal_mail('staff_recruitment','any_key', $email, language_default(), $params);
	
	// $session = variable_get('essa_sid');
	// $table = 'essa_'.$session.'_master_staff_table';
	// $staff = db_query("SELECT * FROM {$table} WHERE emp_id = :emp", array(':emp' =>'St-002'));
	// foreach($staff as $st){
		// $s_uid = $st->uid;
	// }
	
	// $module = 'staff';
	// $recipients= array();
	// $recipients[] = user_load($s_uid);
	// $msg_subject = 'Welcome to ESSA';
	// $msg_body = 'Sir/Mam, <br> You have been successfully added to the school management system -  ESSA. <br> ';
	// $footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
	// $msg_body = $msg_body.' <br>'.$footer;
	// privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
	
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
	if(!in_array('Staff', $folder_list)){
		$node = new stdClass();
		$node->type = 'filedepot_folder';
		node_object_prepare($node);
		$node->language = LANGUAGE_NONE;
		$node->uid = 1;
		$node->title = 'Staff';
		$node->filedepot_folder_desc[LANGUAGE_NONE][0]['value'] = 'This is folder contains folder for each staff, with folder name of empID.';
		$node->parentfolder = 0;
		$node->inherit = 1;
		node_save($node);
	}
	
	$form['ef'] = array(
    '#type' => 'fieldset',
  );

  $form['ef']['emp_id'] = array(
    '#type' => 'textfield',
    '#title' => 'Employee ID',
		'#size' => 15,
		'#required' => TRUE,
  );

	$form['ef']['jd'] = array(
    '#title' => 'Date of Joining',
	  '#type' => 'date_popup',
		'#attributes' => array('placeholder' => 'dd-mm-YYYY'),
		'#date_format' => 'd-m-Y',
	  '#date_year_range' => '-30:0',
	  '#required' => TRUE,
  );

  $form['ef']['type'] = array(
    '#type' => 'radios',
    '#title' => t('Type'),
    '#options' => drupal_map_assoc(array('Teaching', 'Non-Teaching')),
		'#validated' => TRUE,
		'#required' => TRUE,
  );

	$form['ef']['t'] = array(
		'#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		'#states' => array(
			'visible' => array(
			  ':input[name = "type"]' => array('value' => 'Teaching'),
			),
		),
	);
	
	$sal_type = array();
 	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$salary_type = db_query("
    SELECT * from {$sal_table};"
  );
	foreach($salary_type as $st){
		$sal_type[] = $st->title;
	}

  // $form['ef']['t']['grade'] = array(
    // '#type' => 'select',
    // '#title' => t('Salary Structure'),
    // '#options' => drupal_map_assoc($sal_type),
		// '#validated' => TRUE,
		// '#description' => 'This will define the salary structure of the employee.',
  // );

	$session_id = (string)variable_get('essa_sid');
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	$staffs = db_query("
    SELECT * from {$staff_table};
  ");

	$staff_nn = array();
	foreach($staffs as $staff){
		$staff_nn[] = $staff->nickname;
	}
	$form['staff_nn'] = array(
		'#type' => 'values',
		'#values' => $staff_nn,
	);

	$form['ef']['t']['nickname'] = array(
    '#type' => 'textfield',
    '#title' => 'Nick Name',
		'#description' => t('This must be unique for each Teacher.'),
		'#size' => 10,
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'nick_name_error_ajax',
      'wrapper' => 'nn_error',
      'method' => 'append',
      'effect' => 'fade',
    ),
  );

	$form['ef']['t']['error'] = array(
		'#type' => 'container',
    '#prefix' => '<div id = "nn_error">',
    '#suffix' => '</div>',
	);

  $form['ef']['t']['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject Applied For'),
  );

  // $form['ef']['nt'] = array(
		// '#type' => 'fieldset',
		// '#collapsible' => FALSE,
		// '#collapsed' => FALSE,
		// '#states' => array(
			// 'visible' => array(
			  // ':input[name = "type"]' => array('value' => 'Non-Teaching'),
			// ),
		// ),
	// );

  // $form['ef']['nt']['nt_grade'] = array(
    // '#type' => 'select',
    // '#title' => t('Salary Structure'),
    // '#options' => drupal_map_assoc($sal_type),
		// '#validated' => TRUE,
		// '#description' => 'This will define the salary structure of the employee.',
  // );

  $form['pd'] = array(
    '#type' => 'fieldset',
    '#title' => t('Personal Detail'),
  );
	
	/*
  $form['pd']['pic'] = array(
		'#type' => 'file',
		'#title' => t('Photograph'),
	);
	*/
	
	$form['pd']['first_name'] = array(
	  '#title' => 'Name',
		'#attributes' => array('placeholder' => 'First Name'),
	  '#type' => 'textfield',
	  '#size' => 20,
	  '#required' => TRUE,
	);
	$form['pd']['last_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Last Name'),
	);
	
	$form['pd']['dob'] = array(
    '#title' => 'Date of Birth',
	  '#type' => 'date_popup',
		'#attributes' => array('placeholder' => 'dd-mm-YYYY'),
		'#date_format' => 'd-m-Y',
	  '#date_year_range' => '-70:-4',
  );
	$form['pd']['gender'] = array(
	  '#type' => 'select',
		'#title' => t('Gender'),
		'#options' => drupal_map_assoc(array('M', 'F')),
		'#validated' => TRUE,
	);

  $form['pd']['marital'] = array(
    '#type' => 'radios',
    '#title' => t('Marital Status'),
    '#options' => drupal_map_assoc(array('Married', 'Unmarried')),
  );

  $form['pd']['pob'] = array(
    '#type' => 'textfield',
    '#title' => t('Place of Birth'),
  );

  $form['pd']['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
  );

  $form['pd']['nationality'] = array(
    '#type' => 'textfield',
    '#title' => t('Nationality'),
  );

	$form['cd'] = array(
		'#type' => 'fieldset',
		'#title' => t('Contact Details'),
	);
	$form['cd']['email'] = array(
		'#title' => 'Email',
		'#type' => 'textfield',
		'#size' => 50,
		'#rules' => array(
	      'email',
		),
	);
	$form['cd']['mobile'] = array(
		'#title' => 'Mobile No.',
		'#type' => 'textfield',
		'#size' => 50,
	);
	$form['cd']['phone'] = array(
		'#title' => 'Telephone No.',
		'#type' => 'textfield',
		'#size' => 50,
	);

	$form['cd']['pa'] = array(
		'#type' => 'fieldset',
		'#title' => 'Contact Address',
	);
	$form['cd']['pa']['line1'] = array(
		'#type' => 'textfield',
		'#title' => t('Line1'),
		'#resizable' => FALSE,
		'#size' => 40,
	);
	$form['cd']['pa']['line2'] = array(
		'#type' => 'textfield',
		'#title' => t('Line2'),
		'#resizable' => FALSE,
		'#size' => 40,
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

  $form['fi'] = array(
    '#type' => 'fieldset',
    '#title' => t('Family Info'),
  );

  $family_info = drupal_map_assoc(array('1', '2', '3'));
	foreach($family_info as $info){
    //dsm($info);
    $row[$info] = array(
      '#tree' =>TRUE,
      $info => array(  //Generating unique array id for every form element
        'c_c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3 style = "text-align: center;">'.$info.'</h3>',
        ),
        'c_c2' =>array(
          '#type' => 'textfield',
					'#size' => 15,
        ),
        'c_c3' =>array(
					'#type' => 'select',
          '#options' => drupal_map_assoc(array('M', 'F')),
					'#validated' => TRUE,
        ),
        'c_c4' =>array(
					'#type' => 'textfield',
					'#validated' => TRUE,
					'#size' => 3,
        ),
      ),
    );
  }

  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['fi']['child'] = array(
    '#theme' => 'staff_family_info_table',
    'rows' => $row,
  );


  $form['fi']['spd'] = array(
    '#type' => 'fieldset',
    '#title' => t('Spouse/Parents Details'),
  );

  $form['fi']['spd']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
  );

  $form['fi']['spd']['profession'] = array(
    '#type' => 'textfield',
    '#title' => t('Profession'),
  );

  $form['fi']['spd']['native'] = array(
    '#type' => 'textfield',
    '#title' => t('Native Place'),
  );

  $data1 = drupal_map_assoc(array('Father', 'Mother', 'Spouse'));
	foreach($data1 as $info1){
    //dsm($info);
    $row1[$info1] = array(
      '#tree' =>TRUE,
      $info1 => array(  //Generating unique array id for every form element
        'sp_c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$info1.'</h3>',
        ),
        'sp_c2' =>array(
          '#type' => 'textfield',
          '#size' => 20,
        ),
        'sp_c3' =>array(
					'#type' => 'textfield',
          '#size' => 10,
        ),
        'sp_c4' =>array(
					'#type' => 'textfield',
					'#size' => 30,
        ),
        'sp_c5' =>array(
					'#type' => 'textfield',
          '#size' => 7,
        ),
      ),
    );
  }

  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['fi']['spd']['fms'] = array(
    '#theme' => 'staff_fms_info_table',
    'rows' => $row1,
  );

  $form['aq'] = array(
    '#type' => 'fieldset',
    '#title' => t('Academic/Professional Qualifications'),
  );
  $date = date('Y-m-d H:i:s');
  $data2 = array('aq1' => 'High School', 'aq2' => 'Inter/+2', 'aq3' => 'Graduation', 'aq4' => 'Post-Graduation', 'aq5' => 'B.Ed', 'aq6' => 'Any Other');
	foreach($data2 as $aq_key => $info2){
    //dsm($info);
    $row2[$aq_key] = array(
      '#tree' =>TRUE,
      $aq_key => array(  //Generating unique array id for every form element
        'aq_c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$info2.'</h3>',
        ),
        'aq_c2' =>array(
          '#type' => 'textfield',
          '#size' => 15,
        ),
        'aq_c3' =>array(
					'#type' => 'textfield',
          '#size' => 15,
        ),
        'aq_c4' =>array(
					'#type' => 'textfield',
          '#size' => 15,
        ),
        'aq_c5' =>array(
					'#type' => 'date_select',
          '#date_label_position' => 'within',
          '#date_format' => 'y',
          '#default_value' => $date,
          '#date_year_range' => '-70:-4',
        ),
        'aq_c6' =>array(
					'#type' => 'textfield',
          '#size' => 3,
        ),
        'aq_c7' =>array(
					'#type' => 'textfield',
          '#size' => 3,
        ),
      ),
    );
  }

  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['aq']['fms'] = array(
    '#theme' => 'aq_info_table',
    'rows' => $row2,
  );

  $form['aq']['scholarship'] = array(
    '#type' => 'textfield',
    '#title' => t('Scholarship/Awards/Honours'),
  );

  $form['aq']['research'] = array(
    '#type' => 'textfield',
    '#title' => t('Research Work/Publications'),
  );

  $form['aq']['activities'] = array(
    '#type' => 'textfield',
    '#title' => t('Co-curricular Activities'),
  );

  $form['aq']['games'] = array(
    '#type' => 'textfield',
    '#title' => t('Sports/Games/Outdoor Activities'),
  );

  $form['aq']['pil'] = array(
    '#type' => 'fieldset',
    '#title' => t('Proficiency in Languages'),
  );
  $data3 = drupal_map_assoc(array('a', 'b', 'c', 'd'));
	foreach($data3 as $info3){
    //dsm($info);
    $row3[$info3] = array(
      '#tree' =>TRUE,
      $info3 => array(  //Generating unique array id for every form element
        'pl_c1' =>array(
          '#type' => 'textfield',
          '#size' => 20,
        ),
        'pl_c2' =>array(
          '#type' => 'checkbox',
        ),
        'pl_c3' =>array(
					'#type' => 'checkbox',
        ),
        'pl_c4' =>array(
					'#type' => 'checkbox',
        ),
        'pl_c5' =>array(
					'#type' => 'checkbox',
        ),
      ),
    );
  }

  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['aq']['pil']['lang'] = array(
    '#theme' => 'lang_info_table',
    'rows' => $row3,
  );

  $form['aq']['comp'] = array(
    '#type' => 'textfield',
    '#title' => 'Knowledge of Computers'
  );

  $form['in'] = array(
    '#type' => 'fieldset',
    '#title' => t('Interests'),
  );

  $data4 = drupal_map_assoc(array('i1', 'i2', 'i3'));
	foreach($data4 as $info4){
    //dsm($info);
    $row4[$info4] = array(
      '#tree' =>TRUE,
      $info4 => array(  //Generating unique array id for every form element
        'i_c2' =>array(
          '#type' => 'textfield',
          '#size' => 30,
        ),
        'i_c3' =>array(
					'#type' => 'textfield',
          '#size' => 30,
					'#validated' => TRUE,
        ),
        'i_c4' =>array(
					'#type' => 'textfield',
          '#size' => 30,
        ),
      ),
    );
  }

  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['in']['interest'] = array(
    '#theme' => 'interest_info_table',
    'rows' => $row4,
  );

  $form['pe'] = array(
    '#type' => 'fieldset',
    '#title' => t('Professional Experience'),
  );

  $data5 = drupal_map_assoc(array('pe1', 'pe2', 'pe3'));
	foreach($data5 as $info5){
    //dsm($info);
    $row5[$info5] = array(
      '#tree' =>TRUE,
      $info5 => array(  //Generating unique array id for every form element
        'pe_c1' =>array(
          '#type' => 'textfield',
          '#size' => 20,
        ),
        'pe_c2' =>array(
          '#type' => 'date_popup',
          '#attributes' => array('placeholder' => 'dd/mm/yy'),
          '#date_format' => 'd-m-Y',
          '#date_year_range' => '-50:0',
          '#size' => 10,
					'#validated' => TRUE,
        ),
        'pe_c3' =>array(
					'#type' => 'date_popup',
          '#attributes' => array('placeholder' => 'dd/mm/yy'),
          '#date_format' => 'd-m-Y',
          '#date_year_range' => '-50:0',
          '#size' => 10,
					'#validated' => TRUE,
        ),
        'pe_c4' =>array(
					'#type' => 'textfield',
          '#size' => 15,
        ),
        'pe_c5' =>array(
					'#type' => 'textfield',
          '#size' => 15,
        ),
        'pe_c6' =>array(
					'#type' => 'textfield',
          '#size' => 15,
        ),
        'pe_c7' =>array(
					'#type' => 'textfield',
          '#size' => 15,
        ),
      ),
    );
  }

  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['pe']['exp'] = array(
    '#theme' => 'exp_info_table',
    'rows' => $row5,
  );

	$form['id'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional Details(ID Proofs)'),
  );

  $form['id']['passport'] = array(
    '#title' => t('Passport No.'),
    '#type' => 'textfield',
  );

  $form['id']['pan'] = array(
    '#title' => t('PAN Card No.'),
    '#type' => 'textfield',
  );

  $form['id']['dl'] = array(
    '#title' => t('Driving Licence No.'),
    '#type' => 'textfield',
  );

  $form['id']['aadhar'] = array(
    '#title' => t('Aadhar Card No.'),
    '#type' => 'textfield',
  );

  $form['id']['voter'] = array(
    '#title' => t('Voter ID No.'),
    '#type' => 'textfield',
  );
	
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 *Implements ajax callback for nick_name_error_ajax.
 */
function nick_name_error_ajax($form, &$form_state){
	$nns = $form['staff_nn']['#values'];
	$nicknames = array();
	foreach($nns as $ns){
		$nicknames[] = $ns;
	}

	if(in_array($form_state['values']['nickname'], $nicknames)){
		drupal_set_message(t('The Nickname <span style = "font-size: 20px; font-weight: 400; color: RED;"><strong>"'.$form_state['values']['nickname'].'"</strong></span> is already present. Please select a new nickname.'), 'error');
		return '';
	}else{
		drupal_set_message(t('The Nickname <span style = "font-size: 20px; font-weight: 400; color: GREEN;"><strong>"'.$form_state['values']['nickname'].'"</strong></span> is accepted.'));
		return '';
	}
}

/**
 *Implements validate function for addstaff_form.
 */
function addstaff_form_validate($form, &$form_state){
	$session = variable_get('essa_sid');
	$table = 'essa_'.$session.'_master_staff_table';
	$staffs = db_query("SELECT * FROM {$table}");
	foreach($staffs as $staff){
		if($staff->emp_id == $form_state['values']['emp_id']){
			form_set_error('emp_id', t('Employee ID is already present in the system.'));
		}
	}
	
	if($form_state['values']['type'] == 'Teaching'){
		if($form_state['values']['nickname'] == ""){
			form_set_error('nickname', t('Please assign a unique nickname.'));
		}
	}

	$nns = $form['staff_nn']['#values'];
	$nicknames = array();
	foreach($nns as $ns){
		$nicknames[] = $ns;
	}

	if(($key = array_search("", $nicknames)) !== false) {
    unset($nicknames[$key]);
	}

	if($form_state['values']['type'] == 'Teaching'){
		if(in_array($form_state['values']['nickname'], $nicknames)){
			form_set_error('nickname', t('The Nickname <span style = "font-size: 20px; font-weight: 400; color: RED;"><strong>"'.$form_state['values']['nickname'].'"</strong></span> is already present. Please select a new nickname.'));
			return '';
		}
	}

  if ($form_state['values']['email'] != NULL && !valid_email_address($form_state['values']['email'])){
    form_set_error('email' , t('Email address does not seem to be valid'));
  }
}

/**
 *Implements submit function for addstaff_form.
 */
function addstaff_form_submit($form, &$form_state){
	$session = variable_get('essa_sid');
	$table = 'essa_'.$session.'_master_staff_table';

	$fe_id = db_insert($table)
    ->fields (array(
			'emp_id' => $form_state['values']['emp_id'],
			'status' => 1,
			'joining_date' => $form_state['values']['jd'],
			'type' => $form_state['values']['type'],
			'fname' => $form_state['values']['first_name'],
			'lname' => $form_state['values']['last_name'],
			'dob' => $form_state['values']['dob'],
			'gender' => $form_state['values']['gender'],
			'marital_status' => $form_state['values']['marital'],
			'place_of_birth' => $form_state['values']['pob'],
			'pob_state' => $form_state['values']['state'],
			'pob_nationality' => $form_state['values']['nationality'],
			'email' => $form_state['values']['email'],
			'phone_no' => $form_state['values']['phone'],
			'mobile_no' => $form_state['values']['mobile'],
			'ca_line1' => $form_state['values']['line1'],
			'ca_line2' => $form_state['values']['line2'],
			'ca_city' => $form_state['values']['city'],
			'ca_state' => $form_state['values']['state'],
			'ca_pincode' => $form_state['values']['pin'],
			'ca_country' => $form_state['values']['country'],
			'child1_name' => $form_state['values'][1][1]['c_c2'],
			'child1_sex' => $form_state['values'][1][1]['c_c3'],
			'child1_age' => (int)$form_state['values'][1][1]['c_c4'],
			'child2_name' => $form_state['values'][2][2]['c_c2'],
			'child2_sex' => $form_state['values'][2][2]['c_c3'],
			'child2_age' => (int)$form_state['values'][2][2]['c_c4'],
			'child3_name' => $form_state['values'][3][3]['c_c2'],
			'child3_sex' => $form_state['values'][3][3]['c_c3'],
			'child3_age' => (int)$form_state['values'][3][3]['c_c4'],
			'sp_name' => $form_state['values']['name'],
			'sp_profession' => $form_state['values']['profession'],
			'sp_native_place' => $form_state['values']['native'],
			'f_name' => $form_state['values']['Father']['Father']['sp_c2'],
			'f_occupation' => $form_state['values']['Father']['Father']['sp_c3'],
			'f_address' => $form_state['values']['Father']['Father']['sp_c4'],
			'f_phone' => $form_state['values']['Father']['Father']['sp_c5'],
			'm_name' => $form_state['values']['Mother']['Mother']['sp_c2'],
			'm_occupation' => $form_state['values']['Mother']['Mother']['sp_c3'],
			'm_address' => $form_state['values']['Mother']['Mother']['sp_c4'],
			'm_phone' => $form_state['values']['Mother']['Mother']['sp_c5'],
			's_name' => $form_state['values']['Spouse']['Spouse']['sp_c2'],
			's_occupation' => $form_state['values']['Spouse']['Spouse']['sp_c3'],
			's_address' => $form_state['values']['Spouse']['Spouse']['sp_c4'],
			's_phone' => $form_state['values']['Spouse']['Spouse']['sp_c5'],
			'hs_discipline' => $form_state['values']['aq1']['aq1']['aq_c2'],
			'hs_school' => $form_state['values']['aq1']['aq1']['aq_c3'],
			'hs_board' => $form_state['values']['aq1']['aq1']['aq_c4'],
			'hs_passing_year' => $form_state['values']['aq1']['aq1']['aq_c5'],
			'hs_marks' => $form_state['values']['aq1']['aq1']['aq_c6'],
			'hs_div' => $form_state['values']['aq1']['aq1']['aq_c7'],
			'inter_discipline' => $form_state['values']['aq2']['aq2']['aq_c2'],
			'inter_school' => $form_state['values']['aq2']['aq2']['aq_c3'],
			'inter_board' => $form_state['values']['aq2']['aq2']['aq_c4'],
			'inter_passing_year' => $form_state['values']['aq2']['aq2']['aq_c5'],
			'inter_marks' => $form_state['values']['aq2']['aq2']['aq_c6'],
			'inter_div' => $form_state['values']['aq2']['aq2']['aq_c7'],
			'grad_discipline' => $form_state['values']['aq3']['aq3']['aq_c2'],
			'grad_school' => $form_state['values']['aq3']['aq3']['aq_c3'],
			'grad_board' => $form_state['values']['aq3']['aq3']['aq_c4'],
			'grad_passing_year' => $form_state['values']['aq3']['aq3']['aq_c5'],
			'grad_marks' => $form_state['values']['aq3']['aq3']['aq_c6'],
			'grad_div' => $form_state['values']['aq3']['aq3']['aq_c7'],
			'pgrad_discipline' => $form_state['values']['aq4']['aq4']['aq_c2'],
			'pgrad_school' => $form_state['values']['aq4']['aq4']['aq_c3'],
			'pgrad_board' => $form_state['values']['aq4']['aq4']['aq_c4'],
			'pgrad_passing_year' => $form_state['values']['aq4']['aq4']['aq_c5'],
			'pgrad_marks' => $form_state['values']['aq4']['aq4']['aq_c6'],
			'pgrad_div' => $form_state['values']['aq4']['aq4']['aq_c7'],
			'bed_discipline' => $form_state['values']['aq5']['aq5']['aq_c2'],
			'bed_school' => $form_state['values']['aq5']['aq5']['aq_c3'],
			'bed_board' => $form_state['values']['aq5']['aq5']['aq_c4'],
			'bed_passing_year' => $form_state['values']['aq5']['aq5']['aq_c5'],
			'bed_marks' => $form_state['values']['aq5']['aq5']['aq_c6'],
			'bed_div' => $form_state['values']['aq5']['aq5']['aq_c7'],
			'ao_discipline' => $form_state['values']['aq6']['aq6']['aq_c2'],
			'ao_school' => $form_state['values']['aq6']['aq6']['aq_c3'],
			'ao_board' => $form_state['values']['aq6']['aq6']['aq_c4'],
			'ao_passing_year' => $form_state['values']['aq6']['aq6']['aq_c5'],
			'ao_marks' => $form_state['values']['aq6']['aq6']['aq_c6'],
			'ao_div' => $form_state['values']['aq6']['aq6']['aq_c7'],
			'scholarship' => $form_state['values']['scholarship'],
			'research' => $form_state['values']['research'],
			'activities' => $form_state['values']['activities'],
			'sports' => $form_state['values']['games'],
			'lang1' => $form_state['values']['a']['a']['pl_c1'],
			'lang1_mothertongue' => $form_state['values']['a']['a']['pl_c2'],
			'lang1_read' => $form_state['values']['a']['a']['pl_c3'],
			'lang1_write' => $form_state['values']['a']['a']['pl_c4'],
			'lang1_speak' => $form_state['values']['a']['a']['pl_c5'],
			'lang2' => $form_state['values']['b']['b']['pl_c1'],
			'lang2_mothertongue' => $form_state['values']['b']['b']['pl_c2'],
			'lang2_read' => $form_state['values']['b']['b']['pl_c3'],
			'lang2_write' => $form_state['values']['b']['b']['pl_c4'],
			'lang2_speak' => $form_state['values']['b']['b']['pl_c5'],
			'lang3' => $form_state['values']['c']['c']['pl_c1'],
			'lang3_mothertongue' => $form_state['values']['c']['c']['pl_c2'],
			'lang3_read' => $form_state['values']['c']['c']['pl_c3'],
			'lang3_write' => $form_state['values']['c']['c']['pl_c4'],
			'lang3_speak' => $form_state['values']['c']['c']['pl_c5'],
			'lang4' => $form_state['values']['d']['d']['pl_c1'],
			'lang4_mothertongue' => $form_state['values']['d']['d']['pl_c2'],
			'lang4_read' => $form_state['values']['d']['d']['pl_c3'],
			'lang4_write' => $form_state['values']['d']['d']['pl_c4'],
			'lang4_speak' => $form_state['values']['d']['d']['pl_c5'],
			'comp' => $form_state['values']['comp'],
			'i1_academics' => $form_state['values']['i1']['i1']['i_c2'],
			'i1_activities' => $form_state['values']['i1']['i1']['i_c3'],
			'i1_sports' => $form_state['values']['i1']['i1']['i_c4'],
			'i2_academics' => $form_state['values']['i2']['i2']['i_c2'],
			'i2_activities' => $form_state['values']['i2']['i2']['i_c3'],
			'i2_sports' => $form_state['values']['i2']['i2']['i_c4'],
			'i3_academics' => $form_state['values']['i3']['i3']['i_c2'],
			'i3_activities' => $form_state['values']['i3']['i3']['i_c3'],
			'i3_sports' => $form_state['values']['i3']['i3']['i_c4'],
			'p1_institution' => $form_state['values']['pe1']['pe1']['pe_c1'],
			'p1_from' => $form_state['values']['pe1']['pe1']['pe_c2']['date'],
			'p1_to' => $form_state['values']['pe1']['pe1']['pe_c3']['date'],
			'p1_position' => $form_state['values']['pe1']['pe1']['pe_c4'],
			'p1_subjects' => $form_state['values']['pe1']['pe1']['pe_c5'],
			'p1_duties' => $form_state['values']['pe1']['pe1']['pe_c6'],
			'p1_assignment' => $form_state['values']['pe1']['pe1']['pe_c7'],
			'p2_institution' => $form_state['values']['pe2']['pe2']['pe_c1'],
			'p2_from' => $form_state['values']['pe2']['pe2']['pe_c2']['date'],
			'p2_to' => $form_state['values']['pe2']['pe2']['pe_c3']['date'],
			'p2_position' => $form_state['values']['pe2']['pe2']['pe_c4'],
			'p2_subjects' => $form_state['values']['pe2']['pe2']['pe_c5'],
			'p2_duties' => $form_state['values']['pe2']['pe2']['pe_c6'],
			'p2_assignment' => $form_state['values']['pe2']['pe2']['pe_c7'],
			'p3_institution' => $form_state['values']['pe3']['pe3']['pe_c1'],
			'p3_from' => $form_state['values']['pe3']['pe3']['pe_c2']['date'],
			'p3_to' => $form_state['values']['pe3']['pe3']['pe_c3']['date'],
			'p3_position' => $form_state['values']['pe3']['pe3']['pe_c4'],
			'p3_subjects' => $form_state['values']['pe3']['pe3']['pe_c5'],
			'p3_duties' => $form_state['values']['pe3']['pe3']['pe_c6'],
			'p3_assignment' => $form_state['values']['pe3']['pe3']['pe_c7'],
			'passport_no' => $form_state['values']['passport'],
			'pan_card_no' => $form_state['values']['pan'],
			'dl_no' => $form_state['values']['dl'],
			'aadhar_card_no' => $form_state['values']['aadhar'],
			'voter_id_no' => $form_state['values']['voter'],
		)
	)
	->execute();

	if($form_state['values']['type'] == 'Teaching'){
		db_update($table)
			->fields (array(
				//'grade' => $form_state['values']['grade'],
				'nickname' => $form_state['values']['nickname'],
				'subject' => $form_state['values']['subject'],
			))
		->condition('emp_id', $form_state['values']['emp_id'], '=')
		->execute();
	}//else{
		// db_update($table)
			// ->fields (array(
				// 'nt_grade' => $form_state['values']['nt_grade'],
			// ))
		// ->condition('emp_id', $form_state['values']['emp_id'], '=')
		// ->execute();
	// }

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

	if($form_state['values']['type'] == 'Teaching'){
		$new_folder = 'public://school/Staff/Teaching/' . $form_state['values']['emp_id'];
		file_prepare_directory($new_folder, FILE_CREATE_DIRECTORY);
		$edit_staff = array(
		  'name' => $form_state['values']['emp_id'],
			'pass' => $form_state['values']['emp_id'],
		  'mail' => $form_state['values']['email'],
		  'init' => $form_state['values']['email'],
			'status' => 1,
		  'access' => REQUEST_TIME,
			'roles' => array($staff => 'Staff', $teacher => 'Teacher'),
		);
		user_save('', $edit_staff);
	}else{
		$new_folder = 'public://school/Staff/Non-Teaching/' . $form_state['values']['emp_id'];
		file_prepare_directory($new_folder, FILE_CREATE_DIRECTORY);
		$edit_staff = array(
		  'name' => $form_state['values']['emp_id'],
			'pass' => $form_state['values']['emp_id'],
		  'mail' => $form_state['values']['email'],
		  'init' => $form_state['values']['email'],
			'status' => 1,
		  'access' => REQUEST_TIME,
			'roles' => array($staff => 'Staff'),
		);
		user_save('', $edit_staff);
	}
	
	$vid = taxonomy_vocabulary_machine_name_load('staff_vocab');
	taxonomy_term_save(
		(object) array(
		 'name' => $form_state['values']['emp_id'],
		 'vid' => $vid->vid,
		)
	);
 
	$uid = db_query("select * from users where name = :user", array(':user' => $form_state['values']['emp_id']));
	foreach($uid as $staffuid){
		$staff_uid = $staffuid -> uid;
	}
	db_update($table)
		->fields (array(
			'uid' => $staff_uid,
		))
	->condition('emp_id', $form_state['values']['emp_id'], '=')
	->execute();
	
	$vid = taxonomy_vocabulary_machine_name_load('staff_uid_vocab');
  taxonomy_term_save(
  	(object) array(
    	 'name' => $staff_uid,
    	 'vid' => $vid->vid,
  	)
  );
	
	// Upload user picture for staff
	/*
  $account_st = user_load($staff_uid);
  $file = $form_state['values']['pic'];
  unset($form_state['values']['pic']);
	$file = file_save_upload('s_pic', array(
      'file_validate_is_image' => array(),
      'file_validate_extensions' => array('png gif jpg jpeg'),
  ));
  if ($file) {
		$file->status = FILE_STATUS_PERMANENT;
		file_save($file);
	
		$edit['picture'] = $file;
		user_save($account_st, $edit);
	}
	*/
	
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
	$node->title = $form_state['values']['emp_id'];
	$node->filedepot_folder_desc[LANGUAGE_NONE][0]['value'] = 'This is folder is for each staff, here you can save documents and files related to each staff.';
	$node->parentfolder = $folder_id;
	$node->inherit = 1;
	node_save($node);
	
	db_update($table)
		->fields (array(
			'uid' => $staff_uid,
		))
	->condition('emp_id', $form_state['values']['emp_id'], '=')
	->execute();
	
	$folders = db_query("
    SELECT * from filedepot_categories where name = :name;", array(':name' => $form_state['values']['emp_id'])
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
	$node->title = check_plain($form_state['values']['emp_id']);
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
	if($form_state['values']['type'] == 'Teaching'){
		$name_of_table = 'essa_'.$session.'_time_table_'.clean_teacher($form_state['values']['emp_id']);
		if(!db_table_exists($name_of_table)){
		  db_create_table($name_of_table, $schema['time_table']);
		  $day = array('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
		  foreach($day as $w => $input){
		    db_insert($name_of_table)
					->fields (array(
					  'day_weight' => $w,
					  'day' => $input,
					  )
					)
					->execute();
		  }
		}
	}
	//*******Suraj********//
	global $user;
	$sys_alert_table = 'essa_'.$session.'_system_alert';
	//sending system alert
	$created_date = date("Y-m-d H:i:s");
	$strtodate = strtotime($created_date);
	db_insert($sys_alert_table)
	->fields(array(
		'message' => 'Employee ID '.$form_state['values']['emp_id'].' has been added to the system.',
		'priority' => 'L',
		'module' => 'staff',
		'source_url' => 'admin/staff/recruitment/employee_recruitment',
		'timestamp' => $strtodate,
		'source_uid' => $user->uid,
	))
	->execute();
	
	//sending message
	// $module = 'staff';
	// $recipients= array();
	// $recipients[] = user_load($staff_uid);
	// $msg_subject = 'Welcome to ESSA';
	// $msg_body = 'Sir/Mam, <br> You have been successfully added to the school management system -  ESSA. <br> Your credentials are mentioned below. <br> Login using the given username and password <br> You can change your password at any time after your first login. <br> Emp-ID: '.$form_state['values']['emp_id'].'<br> Name: '.$form_state['values']['first_name'].' '.$form_state['values']['last_name'].'<br> Username: '.$form_state['values']['emp_id'].'<br> Password: '.$form_state['values']['emp_id'];
	// $footer = ' <p>This is a system generated mail. Do not reply to this message.<i>ESSA - Efficient & Simplified School Administartion.</i></p>';
	// $msg_body = $msg_body.' <br>'.$footer;
	// privatemsg_new_thread($recipients, $msg_subject, $msg_body, $options = array());
	
	drupal_set_message('Employee '.$form_state['values']['emp_id'].' - '.$form_state['values']['first_name'].' '.$form_state['values']['last_name'].' has been registered successfully!!!','status');
	
	if($form_state['values']['email'] != NULL){
		$email = $form_state['values']['email'];
		
		$body = "<p>Sir/Mam</p>, \n<p>You have been successfully added to the school management system -  ESSA. </p><p>Your credentials are mentioned below. \nLogin using the given username and password. \nYou can change your password at any time after your first login. \nEmp-ID: ".$form_state['values']['emp_id']."\nName: ".$form_state['values']['first_name']." ".$form_state['values']['last_name']."\nUsername: ".$form_state['values']['emp_id']."\nPassword: ".$form_state['values']['emp_id']."</p>";
		$footer = "<p>This is a system generated mail. Do not reply to this message.\n<i>ESSA - Efficient & Simplified School Administartion.</i></p>";
		
		$params = array(
		  'subject' => 'Welcome to ESSA',
		  'body' => $body."\n".$footer,
		);
		drupal_mail('leave', 'Essa', $email, language_default(), $params);
	}
}

/**
 *Supporting function to clean_string the array id.
 */
function clean_teacher($string) {
   $string = str_replace(' ', '_', $string);
	 $string = str_replace('-', '_', $string);
	 $string = str_replace('/', '_', $string);// Replaces all spaces with hyphens.
   return preg_replace('/[^A-Za-z0-9\-]/', '', $string); // Removes special chars.
}