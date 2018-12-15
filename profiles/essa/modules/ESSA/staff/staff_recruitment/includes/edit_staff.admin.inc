<?php

function edit_staff_form($form, $form_state, $user){
  $form = array();
  
  $session_id = (string)variable_get('essa_sid');
	$staff_table = 'essa_'.$session_id.'_master_staff_table';
	$staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    $emp_id = $staff->emp_id;
    $doj = $staff->joining_date;
    $type = $staff->type;
  }
  
  $form['ef'] = array(
    '#type' => 'fieldset',
  );

  $form['ef']['emp_id'] = array(
    '#type' => 'textfield',
    '#title' => 'Employee ID',
    '#default_value' => isset($emp_id)? $emp_id: NULL,
		'#disabled' => TRUE,
  );

	$form['ef']['jd'] = array(
    '#title' => 'Date of Joining',
	  '#type' => 'date_popup',
		'#attributes' => array('placeholder' => 'dd/mm/yy'),
		'#date_format' => 'd-m-Y',
	  '#date_year_range' => '-30:0',
	  '#required' => TRUE,
    '#default_value' => isset($doj)? $doj: NULL,
  );

  $form['ef']['type'] = array(
    '#type' => 'radios',
    '#title' => t('Type'),
    '#options' => drupal_map_assoc(array('Teaching', 'Non-Teaching')),
		'#validated' => TRUE,
    '#default_value' => isset($type)? $type: NULL,
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
  
  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    if($type == 'Teaching'){
      $grade = $staff->grade;
      $subject = $staff->subject;
      $nickname = $staff->nickname;
    }
  }

  $sal_type = array();
 	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$salary_type = db_query("
    SELECT * from {$sal_table};"
  );
	foreach($salary_type as $st){
		$sal_type[] = $st->title;
	}

  $form['ef']['t']['grade'] = array(
    '#type' => 'select',
    '#title' => t('Grade'),
    '#options' => drupal_map_assoc($sal_type),
		'#validated' => TRUE,
		'#description' => 'This will define the salary structure of the employee.',
		'#default_value' => isset($grade)? $grade: NULL,
  );

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
    '#default_value' => isset($nickname)? $nickname: NULL,
  );

	$form['ef']['t']['error'] = array(
		'#type' => 'container',
    '#prefix' => '<div id = "nn_error">',
    '#suffix' => '</div>',
	);

  $form['ef']['t']['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject Applied For'),
    '#default_value' => isset($subject)? $subject: NULL,
  );

  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    if($type != 'Teaching'){
      $nt_grade = $staff->nt_grade;
    }
  }

  $form['ef']['nt'] = array(
		'#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		'#states' => array(
			'visible' => array(
			  ':input[name = "type"]' => array('value' => 'Non-Teaching'),
			),
		),
	);

  $form['ef']['nt']['nt_grade'] = array(
    '#type' => 'select',
    '#title' => t('Grade'),
    '#options' => drupal_map_assoc($sal_type),
		'#validated' => TRUE,
		'#description' => 'This will define the salary structure of the employee.',
		'#default_value' => isset($nt_grade)? $nt_grade: NULL,
  );

  $form['pd'] = array(
    '#type' => 'fieldset',
    '#title' => t('Personal Detail'),
  );

  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    $fname = $staff->fname;
    $lname = $staff->lname;
    $dob = $staff->dob;
    $gender = $staff->gender;
    $ms = $staff->marital_status;
    $pob = $staff->place_of_birth;
    $pob_state = $staff->pob_state;
    $pob_nationality = $staff->pob_nationality;
  }
  
	$form['pd']['first_name'] = array(
	  '#title' => 'Name',
		'#attributes' => array('placeholder' => 'First Name'),
	  '#type' => 'textfield',
	  '#size' => 20,
	  '#required' => TRUE,
    '#default_value' => isset($fname)? $fname: NULL,
	);
	$form['pd']['last_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Last Name'),
	  '#required' => TRUE,
    '#default_value' => isset($lname)? $lname: NULL,
	);
	$form['pd']['dob'] = array(
    '#title' => 'Date of Birth',
	  '#type' => 'date_popup',
		'#attributes' => array('placeholder' => 'dd/mm/yy'),
		'#date_format' => 'd-m-Y',
	  '#date_year_range' => '-70:-4',
	  '#required' => TRUE,
    '#default_value' => isset($dob)? $dob: NULL,
  );
	$form['pd']['gender'] = array(
	  '#type' => 'select',
		'#title' => t('Gender'),
		'#options' => drupal_map_assoc(array('M', 'F')),
		'#validated' => TRUE,
    '#default_value' => isset($gender)? $gender: NULL,
	);

  $form['pd']['marital'] = array(
    '#type' => 'radios',
    '#title' => t('Marital Status'),
    '#options' => drupal_map_assoc(array('Married', 'Unmarried')),
    '#default_value' => isset($ms)? $ms: NULL,
  );

  $form['pd']['pob'] = array(
    '#type' => 'textfield',
    '#title' => t('Place of Birth'),
    '#default_value' => isset($pob)? $pob: NULL,
  );

  $form['pd']['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#default_value' => isset($pob_state)? $pob_state: NULL,
  );

  $form['pd']['nationality'] = array(
    '#type' => 'textfield',
    '#title' => t('Nationality'),
    '#default_value' => isset($pob_nationality)? $pob_nationality: NULL,
  );

  $form['cd'] = array(
		'#type' => 'fieldset',
		'#title' => t('Contact Details'),
	);
  
  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    $email = $staff->email;
    $tn = $staff->phone_no;
    $mn = $staff->mobile_no;
    $ca_line1 = $staff->ca_line1;
    $ca_line2 = $staff->ca_line2;
    $ca_city = $staff->ca_city;
    $ca_state = $staff->ca_state;
    $ca_pin = $staff->ca_pincode;
    $ca_country = $staff->ca_country;
  }
	$form['cd']['email'] = array(
		'#title' => 'Email',
		'#type' => 'textfield',
		'#size' => 50,
		'#rules' => array(
	      'email',
    ),
		'#required' => TRUE,
    '#default_value' => isset($email)? $email: NULL,
	);
	$form['cd']['phone'] = array(
		'#title' => 'Telephone No.',
		'#type' => 'textfield',
		'#size' => 50,
		//'#required' => TRUE,
    '#default_value' => isset($tn)? $tn: NULL,
	);
  $form['cd']['mobile'] = array(
		'#title' => 'Mobile No.',
		'#type' => 'textfield',
		'#size' => 50,
		'#required' => TRUE,
    '#default_value' => isset($mn)? $mn: NULL,
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
    '#default_value' => isset($ca_line1)? $ca_line1: NULL,
	);
	$form['cd']['pa']['line2'] = array(
		'#type' => 'textfield',
		'#title' => t('Line2'),
		'#resizable' => FALSE,
		'#size' => 40,
    '#default_value' => isset($ca_line2)? $ca_line2: NULL,
	);
	$form['cd']['pa']['city'] = array(
		'#title' => 'City',
		'#type' => 'textfield',
		'#size' => 20,
    '#default_value' => isset($ca_city)? $ca_city: NULL,
	);
	$form['cd']['pa']['state'] = array(
		'#title' => 'State',
		'#type' => 'textfield',
		'#size' => 20,
    '#default_value' => isset($ca_state)? $ca_state: NULL,
	);
	$form['cd']['pa']['pin'] = array(
		'#title' => 'Pincode',
		'#type' => 'textfield',
		'#size' => 20,
    '#default_value' => isset($ca_pin)? $ca_pin: NULL,
	);
	$form['cd']['pa']['country'] = array(
		'#title' => 'Country',
		'#type' => 'textfield',
		'#size' => 20,
    '#default_value' => isset($ca_pin)? $ca_country: NULL,
	);

  $form['fi'] = array(
    '#type' => 'fieldset',
    '#title' => t('Family Info'),
  );
  
  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    $name[1][1] = $staff->child1_name;
    $sex[1][1] = $staff->child1_sex;
    $age[1][1] = $staff->child1_age;
    $name[2][2] = $staff->child2_name;
    $sex[2][2] = $staff->child2_sex;
    $age[2][2] = $staff->child2_age;
    $name[3][3] = $staff->child3_name;
    $sex[3][3] = $staff->child3_sex;
    $age[3][3] = $staff->child3_age;
  }
  
  $family_info = drupal_map_assoc(array('1', '2', '3'));
	foreach($family_info as $info){
    $row[$info] = array(
      '#tree' =>TRUE,
      $info => array(  //Generating unique array id for every form element
        'c_c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$info.'</h3>',
        ),
        'c_c2' =>array(
          '#type' => 'textfield',
          '#default_value' => isset($name[$info][$info])? $name[$info][$info]: NULL,
        ),
        'c_c3' =>array(
					'#type' => 'select',
          '#options' => drupal_map_assoc(array('M', 'F')),
					'#validated' => TRUE,
          '#default_value' => isset($sex[$info][$info])? $sex[$info][$info]: NULL,
        ),
        'c_c4' =>array(
					'#type' => 'textfield',
					'#validated' => TRUE,
          '#default_value' => isset($age[$info][$info])? $age[$info][$info]: NULL,
        ),
      ),
    );
  }
  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['fi']['child'] = array(
    '#theme' => 'staff_family_info_table',
    'rows' => $row,
  );

  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    $sp_name = $staff->sp_name;
    $sp_profession = $staff->sp_profession;
    $sp_native_place = $staff->sp_native_place;
  }
  $form['fi']['spd'] = array(
    '#type' => 'fieldset',
    '#title' => t('Spouse/Parents Details'),
  );

  $form['fi']['spd']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($sp_name)? $sp_name: NULL,
  );

  $form['fi']['spd']['profession'] = array(
    '#type' => 'textfield',
    '#title' => t('Profession'),
    '#default_value' => isset($sp_profession)? $sp_profession: NULL,
  );

  $form['fi']['spd']['native'] = array(
    '#type' => 'textfield',
    '#title' => t('Native Place'),
    '#default_value' => isset($sp_profession)? $sp_profession: NULL,
  );
  
  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    $name['Father']['Father'] = $staff->f_name;
    $occupation['Father']['Father'] = $staff->f_occupation;
    $address['Father']['Father'] = $staff->f_address;
    $phone['Father']['Father'] = $staff->f_phone;
    $name['Mother']['Mother'] = $staff->m_name;
    $occupation['Mother']['Mother'] = $staff->m_occupation;
    $address['Mother']['Mother'] = $staff->m_address;
    $phone['Mother']['Mother'] = $staff->m_phone;
    $name['Spouse']['Spouse'] = $staff->s_name;
    $occupation['Spouse']['Spouse'] = $staff->s_occupation;
    $address['Spouse']['Spouse'] = $staff->s_address;
    $phone['Spouse']['Spouse'] = $staff->s_phone;
  }
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
          '#default_value' => isset($name[$info1][$info1])? $name[$info1][$info1]: NULL,
        ),
        'sp_c3' =>array(
					'#type' => 'textfield',
          '#size' => 20,
          '#default_value' => isset($occupation[$info1][$info1])? $occupation[$info1][$info1]: NULL,
        ),
        'sp_c4' =>array(
					'#type' => 'textfield',
          '#default_value' => isset($address[$info1][$info1])? $address[$info1][$info1]: NULL,
        ),
        'sp_c5' =>array(
					'#type' => 'textfield',
          '#size' => 20,
          '#default_value' => isset($phone[$info1][$info1])? $phone[$info1][$info1]: NULL,
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
  
  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    $discipline['aq1']['aq1'] = $staff->hs_discipline;
    $school['aq1']['aq1'] = $staff->hs_school;
    $board['aq1']['aq1'] = $staff->hs_board;
    $py['aq1']['aq1'] = $staff->hs_passing_year;
    $marks['aq1']['aq1'] = $staff->hs_marks;
    $div['aq1']['aq1'] = $staff->hs_div;
    
    $discipline['aq2']['aq2'] = $staff->inter_discipline;
    $school['aq2']['aq2'] = $staff->inter_school;
    $board['aq2']['aq2'] = $staff->inter_board;
    $py['aq2']['aq2'] = $staff->inter_passing_year;
    $marks['aq2']['aq2'] = $staff->inter_marks;
    $div['aq2']['aq2'] = $staff->inter_div;
    
    $discipline['aq3']['aq3'] = $staff->grad_discipline;
    $school['aq3']['aq3'] = $staff->grad_school;
    $board['aq3']['aq3'] = $staff->grad_board;
    $py['aq3']['aq3'] = $staff->grad_passing_year;
    $marks['aq3']['aq3'] = $staff->grad_marks;
    $div['aq3']['aq3'] = $staff->grad_div;
    
    $discipline['aq4']['aq4'] = $staff->pgrad_discipline;
    $school['aq4']['aq4'] = $staff->pgrad_school;
    $board['aq4']['aq4'] = $staff->pgrad_board;
    $py['aq4']['aq4'] = $staff->pgrad_passing_year;
    $marks['aq4']['aq4'] = $staff->pgrad_marks;
    $div['aq4']['aq4'] = $staff->pgrad_div;
    
    $discipline['aq5']['aq5'] = $staff->bed_discipline;
    $school['aq5']['aq5'] = $staff->bed_school;
    $board['aq5']['aq5'] = $staff->bed_board;
    $py['aq5']['aq5'] = $staff->bed_passing_year;
    $marks['aq5']['aq5'] = $staff->bed_marks;
    $div['aq5']['aq5'] = $staff->bed_div;
    
    $discipline['aq6']['aq6'] = $staff->ao_discipline;
    $school['aq6']['aq6'] = $staff->ao_school;
    $board['aq6']['aq6'] = $staff->ao_board;
    $py['aq6']['aq6'] = $staff->ao_passing_year;
    $marks['aq6']['aq6'] = $staff->ao_marks;
    $div['aq6']['aq6'] = $staff->ao_div;
  }
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
          '#size' => 20,
          '#default_value' => isset($discipline[$aq_key][$aq_key])? $discipline[$aq_key][$aq_key]: NULL,
        ),
        'aq_c3' =>array(
					'#type' => 'textfield',
          '#size' => 20,
          '#default_value' => isset($school[$aq_key][$aq_key])? $school[$aq_key][$aq_key]: NULL,
        ),
        'aq_c4' =>array(
					'#type' => 'textfield',
          '#size' => 20,
          '#default_value' => isset($board[$aq_key][$aq_key])? $board[$aq_key][$aq_key]: NULL,
        ),
        'aq_c5' =>array(
					'#type' => 'date_select',
          '#date_label_position' => 'within',
          '#date_format' => 'y',
          '#default_value' => $date,
          '#date_year_range' => '-70:-4',
          '#default_value' => isset($py[$aq_key][$aq_key])? $py[$aq_key][$aq_key]: NULL,
        ),
        'aq_c6' =>array(
					'#type' => 'textfield',
          '#size' => 10,
          '#default_value' => isset($marks[$aq_key][$aq_key])? $marks[$aq_key][$aq_key]: NULL,
        ),
        'aq_c7' =>array(
					'#type' => 'textfield',
          '#size' => 10,
          '#default_value' => isset($div[$aq_key][$aq_key])? $div[$aq_key][$aq_key]: NULL,
        ),
      ),
    );
  }
  
  
  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['aq']['fms'] = array(
    '#theme' => 'aq_info_table',
    'rows' => $row2,
  );
  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    $scholarship = $staff->scholarship;
    $research = $staff->research;
    $activities = $staff->activities;
    $sports = $staff->sports;
  }
  $form['aq']['scholarship'] = array(
    '#type' => 'textfield',
    '#title' => t('Scholarship/Awards/Honours'),
    '#default_value' => isset($scholarship)? $scholarship: NULL,
  );

  $form['aq']['research'] = array(
    '#type' => 'textfield',
    '#title' => t('Research Work/Publications'),
    '#default_value' => isset($research)? $research: NULL,
  );

  $form['aq']['activities'] = array(
    '#type' => 'textfield',
    '#title' => t('Co-curricular Activities'),
    '#default_value' => isset($activities)? $activities: NULL,
  );

  $form['aq']['games'] = array(
    '#type' => 'textfield',
    '#title' => t('Sports/Games/Outdoor Activities'),
    '#default_value' => isset($sports)? $sports: NULL,
  );

  $form['aq']['pil'] = array(
    '#type' => 'fieldset',
    '#title' => t('Proficiency in Languages'),
  );
  
  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    $lang['a']['a'] = $staff->lang1;
    $mt['a']['a'] = $staff->lang1_mothertongue;
    $read['a']['a'] = $staff->lang1_read;
    $write['a']['a'] = $staff->lang1_write;
    $speak['a']['a'] = $staff->lang1_speak;
    
    $lang['b']['b'] = $staff->lang2;
    $mt['b']['b'] = $staff->lang2_mothertongue;
    $read['b']['b'] = $staff->lang2_read;
    $write['b']['b'] = $staff->lang2_write;
    $speak['b']['b'] = $staff->lang2_speak;
    
    $lang['c']['c'] = $staff->lang3;
    $mt['c']['c'] = $staff->lang3_mothertongue;
    $read['c']['c'] = $staff->lang3_read;
    $write['c']['c'] = $staff->lang3_write;
    $speak['c']['c'] = $staff->lang3_speak;
    
    $lang['d']['d'] = $staff->lang4;
    $mt['d']['d'] = $staff->lang4_mothertongue;
    $read['d']['d'] = $staff->lang4_read;
    $write['d']['d'] = $staff->lang4_write;
    $speak['d']['d'] = $staff->lang4_speak;
  }
  $data3 = drupal_map_assoc(array('a', 'b', 'c', 'd'));
	foreach($data3 as $info3){
    //dsm($info);
    $row3[$info3] = array(
      '#tree' =>TRUE,
      $info3 => array(  //Generating unique array id for every form element
        'pl_c1' =>array(
          '#type' => 'textfield',
          '#size' => 20,
          '#default_value' => isset($lang[$info3][$info3])? $lang[$info3][$info3]: NULL,
        ),
        'pl_c2' =>array(
          '#type' => 'checkbox',
          '#default_value' => isset($mt[$info3][$info3])? $mt[$info3][$info3]: NULL,
        ),
        'pl_c3' =>array(
					'#type' => 'checkbox',
          '#default_value' => isset($read[$info3][$info3])? $read[$info3][$info3]: NULL,
        ),
        'pl_c4' =>array(
					'#type' => 'checkbox',
          '#default_value' => isset($write[$info3][$info3])? $write[$info3][$info3]: NULL,
        ),
        'pl_c5' =>array(
					'#type' => 'checkbox',
          '#default_value' => isset($speak[$info3][$info3])? $speak[$info3][$info3]: NULL,
        ),
      ),
    );
  }
  
  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    $comp = $staff->comp;
  }
  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['aq']['pil']['lang'] = array(
    '#theme' => 'lang_info_table',
    'rows' => $row3,
  );

  $form['aq']['comp'] = array(
    '#type' => 'textfield',
    '#title' => 'Knowledge of Computers',
    '#default_value' => isset($comp)? $comp: NULL,
  );

  $form['in'] = array(
    '#type' => 'fieldset',
    '#title' => t('Interests'),
  );
  
  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    $aca['i1']['i1'] = $staff->i1_academics;
    $act['i1']['i1'] = $staff->i1_activities;
    $sp['i1']['i1'] = $staff->i1_sports;
    
    $aca['i2']['i2'] = $staff->i2_academics;
    $act['i2']['i2'] = $staff->i2_activities;
    $sp['i2']['i2'] = $staff->i2_sports;
    
    $aca['i3']['i3'] = $staff->i3_academics;
    $act['i3']['i3'] = $staff->i3_activities;
    $sp['i3']['i3'] = $staff->i3_sports;
  }
  $data4 = drupal_map_assoc(array('i1', 'i2', 'i3'));
	foreach($data4 as $info4){
    //dsm($info);
    $row4[$info4] = array(
      '#tree' =>TRUE,
      $info4 => array(  //Generating unique array id for every form element
        'i_c2' =>array(
          '#type' => 'textfield',
          '#size' => 40,
          '#default_value' => isset($aca[$info4][$info4])? $aca[$info4][$info4]: NULL,
        ),
        'i_c3' =>array(
					'#type' => 'textfield',
          '#size' => 40,
					'#validated' => TRUE,
          '#default_value' => isset($act[$info4][$info4])? $act[$info4][$info4]: NULL,
        ),
        'i_c4' =>array(
					'#type' => 'textfield',
          '#size' => 40,
          '#default_value' => isset($sp[$info4][$info4])? $sp[$info4][$info4]: NULL,
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
  
  $staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
    $ins['pe1']['pe1'] = $staff->p1_institution;
    $from['pe1']['pe1'] = $staff->p1_from;
		$time = strtotime($from['pe1']['pe1']);
		$newformat_from['pe1']['pe1'] = date('Y-m-d',$time);
    $to['pe1']['pe1'] = $staff->p1_to;
		$time = strtotime($to['pe1']['pe1']);
		$newformat_to['pe1']['pe1'] = date('Y-m-d',$time);
    $pos['pe1']['pe1'] = $staff->p1_position;
    $sub['pe1']['pe1'] = $staff->p1_subjects;
    $dut['pe1']['pe1'] = $staff->p1_duties;
    $ass['pe1']['pe1'] = $staff->p1_assignment;
    
    $ins['pe2']['pe2'] = $staff->p2_institution;
    $from['pe2']['pe2'] = $staff->p2_from;
		$time = strtotime($from['pe2']['pe2']);
		$newformat_from['pe2']['pe2'] = date('Y-m-d',$time);
    $to['pe2']['pe2'] = $staff->p2_to;
		$time = strtotime($to['pe2']['pe2']);
		$newformat_to['pe2']['pe2'] = date('Y-m-d',$time);
    $pos['pe2']['pe2'] = $staff->p2_position;
    $sub['pe2']['pe2'] = $staff->p2_subjects;
    $dut['pe2']['pe2'] = $staff->p2_duties;
    $ass['pe2']['pe2'] = $staff->p2_assignment;
    
    $ins['pe3']['pe3'] = $staff->p3_institution;
    $from['pe3']['pe3'] = $staff->p3_from;
		$time = strtotime($from['pe3']['pe3']);
		$newformat_from['pe3']['pe3'] = date('Y-m-d',$time);
    $to['pe3']['pe3'] = $staff->p3_to;
		$time = strtotime($to['pe3']['pe3']);
		$newformat_to['pe3']['pe3'] = date('Y-m-d',$time);
    $pos['pe3']['pe3'] = $staff->p3_position;
    $sub['pe3']['pe3'] = $staff->p3_subjects;
    $dut['pe3']['pe3'] = $staff->p3_duties;
    $ass['pe3']['pe3'] = $staff->p3_assignment;
  }
  $data5 = drupal_map_assoc(array('pe1', 'pe2', 'pe3'));
	foreach($data5 as $info5){
    //dsm($info);
    $row5[$info5] = array(
      '#tree' =>TRUE,
      $info5 => array(  //Generating unique array id for every form element
        'pe_c1' =>array(
          '#type' => 'textfield',
          '#size' => 20,
          '#default_value' => isset($ins[$info5][$info5])? $ins[$info5][$info5]: NULL,
        ),
        'pe_c2' =>array(
          '#type' => 'date_popup',
          '#attributes' => array('placeholder' => 'dd/mm/yy'),
          '#date_format' => 'Y-m-d',
          '#date_year_range' => '-50:0',
          '#size' => 20,
					'#validated' => TRUE,
          '#default_value' => isset($newformat_from[$info5][$info5])? $newformat_from[$info5][$info5]: NULL,
        ),
        'pe_c3' =>array(
					'#type' => 'date_popup',
          '#attributes' => array('placeholder' => 'dd/mm/yy'),
          '#date_format' => 'Y-m-d',
          '#date_year_range' => '-50:0',
          '#size' => 20,
					'#validated' => TRUE,
          '#default_value' => isset($newformat_to[$info5][$info5])? $newformat_to[$info5][$info5]: NULL,
        ),
        'pe_c4' =>array(
					'#type' => 'textfield',
          '#size' => 20,
          '#default_value' => isset($pos[$info5][$info5])? $pos[$info5][$info5]: NULL,
        ),
        'pe_c5' =>array(
					'#type' => 'textfield',
          '#size' => 20,
          '#default_value' => isset($sub[$info5][$info5])? $sub[$info5][$info5]: NULL,
        ),
        'pe_c6' =>array(
					'#type' => 'textfield',
          '#size' => 20,
          '#default_value' => isset($dut[$info5][$info5])? $dut[$info5][$info5]: NULL,
        ),
        'pe_c7' =>array(
					'#type' => 'textfield',
          '#size' => 20,
          '#default_value' => isset($ass[$info5][$info5])?  $ass[$info5][$info5]: NULL,
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
	
	$staffs = db_query("
    SELECT * from {$staff_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($staffs as $staff){
		$passport = $staff->passport_no;
		$pan = $staff->pan_card_no;
		$dl = $staff->dl_no;
		$ac_no = $staff->aadhar_card_no;
		$vi = $staff->voter_id_no;
  }
  $form['id']['passport'] = array(
    '#title' => t('Passport No.'),
    '#type' => 'textfield',
		'#default_value' => isset($passport)?  $passport: NULL,
  );

  $form['id']['pan'] = array(
    '#title' => t('PAN Card No.'),
    '#type' => 'textfield',
		'#default_value' => isset($pan)?  $pan: NULL,
  );

  $form['id']['dl'] = array(
    '#title' => t('Driving Licence No.'),
    '#type' => 'textfield',
		'#default_value' => isset($dl)?  $dl: NULL,
  );

  $form['id']['aadhar'] = array(
    '#title' => t('Aadhar Card No.'),
    '#type' => 'textfield',
		'#default_value' => isset($ac_no)?  $ac_no: NULL,
  );

  $form['id']['voter'] = array(
    '#title' => t('Voter ID No.'),
    '#type' => 'textfield',
		'#default_value' => isset($vi)?  $vi: NULL,
  );
	
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 *Implements validate function for addstaff_form.
 */
function edit_staff_form_validate($form, &$form_state){
	/*
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
	*/

  if(!ctype_alpha($form_state['values']['first_name']) || ($form_state['values']['first_name'] == NULL)) {
    form_set_error('first_name', t('Name field should not be empty or have a numeric value'));
  }
  if(!ctype_alpha($form_state['values']['last_name']) || ($form_state['values']['last_name'] == NULL)) {
    form_set_error('last_name', t('Name field should not be empty or have a numeric value'));
  }

  if (!valid_email_address($form_state['values']['email'])){
    form_set_error('email' , t('Email address does not seem to be valid'));
  }

/*
  $str1 = substr($form_state['values']['phone'],0,1);
  $strrem1 = substr($form_state['values']['phone'], 1);


  if ($form_state['values']['phone'] != NULL){
    if ($str1 == '0'){
      if (!ctype_digit($form_state['values']['phone']) ||       strlen($strrem1) != 10){
        form_set_error('phone' , t('Phone No. provided seems to be incorrect'));
      }
    }
    elseif($str1 == '+'){
      if (!ctype_digit($strrem1) || strlen($strrem1) > 13){
        form_set_error('phone', t('Phone No. provided seems to be incorrect'));
      }
    }

    else {
      if (!ctype_digit($form_state['values']['phone']) ||       strlen($form_state['values']['phone']) != 10){
        form_set_error('phone' , t('Phone No. provided seems to be incorrect'));
      }
    }
  }
*/
  $str2 = substr($form_state['values']['mobile'],0,1);
  $strrem2 = substr($form_state['values']['mobile'], 1);


  if ($form_state['values']['mobile'] != NULL){
    if ($str2 == '0'){
      if (!ctype_digit($form_state['values']['mobile']) ||       strlen($strrem2) != 10){
        form_set_error('mobile' , t('Phone No. provided seems to be incorrect'));
      }
    }
    elseif($str2 == '+'){
      if (!ctype_digit($strrem2) || strlen($strrem2) > 13){
        form_set_error('mobile', t('Phone No. provided seems to be incorrect'));
      }
    }
    else {
      if (!ctype_digit($form_state['values']['mobile']) ||      strlen($form_state['values']['mobile']) != 10){
        form_set_error('mobile' , t('Phone No. provided seems to be incorrect'));
        }
      }
    }
/*
  if ($form_state['values'][1][1]['c_c4'] != NULL){
    if(!ctype_digit($form_state['values'][1][1]['c_c4'])){
        form_set_error("[1][1]['c_c4']", t('Age is not in correct format'));
    }
  }
  if ($form_state['values'][2][2]['c_c4'] != NULL){
    if(!ctype_digit($form_state['values'][2][2]['c_c4'])){
        form_set_error("[2][2]['c_c4']", t('Age is not in correct format'));
    }
  }

  if ($form_state['values'][2][2]['c_c4'] != NULL){
    if(!ctype_digit($form_state['values'][2][2]['c_c4'])){
        form_set_error("[2][2]['c_c4']", t('Age is not in correct format'));
    }
  }
  if ($form_state['values'][3][3]['c_c4'] != NULL){
    if(!ctype_digit($form_state['values'][3][3]['c_c4'])){
        form_set_error("[3][3]['c_c4']", t('Age is not in correct format'));
    }
  }

  $str3 = substr($form_state['values']['Mother']['Mother']['sp_c5'],0,1);
  $strrem3 = substr($form_state['values']['Mother']['Mother']['sp_c5'], 1);
  if ($form_state['values']['Mother']['Mother']['sp_c5'] != NULL){
    if ($str3 == '0'){
      if(!ctype_digit($form_state['values']['Mother']['Mother']['sp_c5']) || strlen($strrem3) != 10){
        form_set_error("['sp_c5']" , t('Phone No. provided seems to be incorrect'));
      }
    }
    elseif($str3 == '+'){
      if (!ctype_digit($strrem3) || strlen($strrem3) > 13){
        form_set_error("['sp_c5']", t('Phone No. provided seems to be incorrect'));
      }
    }
    else {
      if (!ctype_digit($form_state['values']['Mother']['Mother']['sp_c5']) || strlen($form_state['values']['Mother']['Mother']['sp_c5']) != 10){
        form_set_error("['sp_c5']" , t('Phone No. provided seems to be incorrect'));
      }
    }
  }

  $str4 = substr($form_state['values']['Father']['Father']['sp_c5'],0,1);
  $strrem4 = substr($form_state['values']['Father']['Father']['sp_c5'], 1);
  if ($form_state['values']['Father']['Father']['sp_c5'] != NULL){
    if ($str4 == '0'){
      if(!ctype_digit($form_state['values']['Father']['Father']['sp_c5']) || strlen($strrem4) != 10){
        form_set_error("['sp_c5']" , t('Phone No. provided seems to be incorrect'));
      }
    }
    elseif($str4 == '+'){
      if (!ctype_digit($strrem4) || strlen($strrem4) > 13){
        form_set_error("['sp_c5']", t('Phone No. provided seems to be incorrect'));
      }
    }
    else {
      if (!ctype_digit($form_state['values']['Father']['Father']['sp_c5']) || strlen($form_state['values']['Father']['Father']['sp_c5']) != 10){
        form_set_error("['sp_c5']" , t('Phone No. provided seems to be incorrect'));
      }
    }

  }

  $str5 = substr($form_state['values']['Spouse']['Spouse']['sp_c5'],0,1);
  $strrem5 = substr($form_state['values']['Spouse']['Spouse']['sp_c5'], 1);
  if ($form_state['values']['Spouse']['Spouse']['sp_c5'] != NULL){
    if ($str5 == '0'){
      if(!ctype_digit($form_state['values']['Spouse']['Spouse']['sp_c5']) || strlen($strrem5) != 10){
        form_set_error("['sp_c5']" , t('Phone No. provided seems to be incorrect'));
      }
    }
    elseif($str5 == '+'){
      if (!ctype_digit($strrem5) || strlen($strrem5) > 13){
        form_set_error("['sp_c5']", t('Phone No. provided seems to be incorrect'));
      }
    }
    else {
      if (!ctype_digit($form_state['values']['Spouse']['Spouse']['sp_c5']) || strlen($form_state['values']['Spouse']['Spouse']['sp_c5']) != 10){
        form_set_error("['sp_c5']" , t('Phone No. provided seems to be incorrect'));
      }
    }
  }

  if ($form_state['values']['aq1']['aq1']['aq_c6'] != NULL){
      if(!ctype_digit($form_state['values']['aq1']['aq1']['aq_c6']) || (int)$form_state['values']['aq1']['aq1']['aq_c6'] > 100){
        form_set_error("['aq_c6']", t('Check the marks entered'));
      }
  }

  if ($form_state['values']['aq2']['aq2']['aq_c6'] != NULL){
      if(!ctype_digit($form_state['values']['aq2']['aq2']['aq_c6']) || (int)$form_state['values']['aq2']['aq2']['aq_c6'] > 100){
        form_set_error("['aq2']['aq2']['aq_c6']", t('Check the marks entered'));
      }
  }
  if ($form_state['values']['aq3']['aq3']['aq_c6'] != NULL){
    if(!ctype_digit($form_state['values']['aq3']['aq3']['aq_c6']) || (int)$form_state['values']['aq3']['aq3']['aq_c6'] > 100){
        form_set_error("['aq3']['aq3']['aq_c6']", t('Check the marks entered'));
    }
  }
  if ($form_state['values']['aq4']['aq4']['aq_c6'] != NULL){
    if(!ctype_digit($form_state['values']['aq4']['aq4']['aq_c6']) || (int)$form_state['values']['aq4']['aq4']['aq_c6'] > 100){
        form_set_error("['aq4']['aq4']['aq_c6']", t('Check the marks entered'));
    }
  }
  if ($form_state['values']['aq5']['aq5']['aq_c6'] != NULL){
    if(!ctype_digit($form_state['values']['aq5']['aq5']['aq_c6']) || (int)$form_state['values']['aq5']['aq5']['aq_c6'] > 100){
        form_set_error("['aq5']['aq5']['aq_c6']", t('Check the marks entered'));
    }
  }
  if ($form_state['values']['aq6']['aq6']['aq_c6'] != NULL){
    if(!ctype_digit($form_state['values']['aq6']['aq6']['aq_c6']) || (int)$form_state['values']['aq6']['aq6']['aq_c6'] > 100){
        form_set_error("['aq_c6']", t('Check the marks entered'));
    }
  }
  */
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
 *Implements submit function for addstaff_form.
 */
function edit_staff_form_submit($form, &$form_state){
	//dsm($form_state);
	drupal_set_message('Employee records has been edited successfully!!!','status');
	$session = variable_get('essa_sid');
	$table = 'essa_'.$session.'_master_staff_table';

	$fe_id = db_merge($table)
		->key(array('emp_id' => $form_state['values']['emp_id']))
    ->fields (array(
			'emp_id' => $form_state['values']['emp_id'],
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
				'grade' => $form_state['values']['grade'],
				'nickname' => $form_state['values']['nickname'],
				'subject' => $form_state['values']['subject'],
			))
		->condition('emp_id', $form_state['values']['emp_id'], '=')
		->execute();
	}else{
		db_update($table)
			->fields (array(
				'nt_grade' => $form_state['values']['nt_grade'],
			))
		->condition('emp_id', $form_state['values']['emp_id'], '=')
		->execute();
	}
}
