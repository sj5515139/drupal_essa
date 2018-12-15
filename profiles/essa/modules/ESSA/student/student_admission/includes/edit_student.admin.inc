<?php
/**
 *Implements page callback function - edit_student_form
 */
function edit_student_form($form, &$form_state, $user){
  $form = array();
  module_load_include('inc', 'hierarchical_select', 'includes/common');
	
	$config = sa_hs_setting();
	
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$students = db_query("
    SELECT * from {$student_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($students as $student){
		$class = $student->class;
		$section = $student->section;
	}
	$form['this_class_id'] = array(
		'#type' => 'value',
		'#value' => $class,
	);
	$form['this_section'] = array(
		'#type' => 'value',
		'#value' => $section,
	);
	$students = db_query("
    SELECT * from {$student_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($students as $student){
		//dsm($student);
		$adm_no = $student->adm_no;
		$rollno = $student->roll_no;
		$doa = $student->doa;
		$house = $student->house;
		$is_hostel = $student->is_hostel;
		$room = $student->room;
		$is_sibling = $student-> is_sibling;
		$sibling_adm_no = $student->sibling_adm_no;
		$first_name = $student->first_name;
		$middle_name = $student->middle_name;
		$last_name = $student->last_name;
		$f_first_name = $student->f_first_name;
		$f_middle_name = $student->f_middle_name;
		$f_last_name = $student->f_last_name;
		$m_first_name = $student->m_first_name;
		$m_middle_name = $student->m_middle_name;
		$m_last_name = $student->m_last_name;
		$gender = $student->gender;
		$dob = $student->dob;
		$nationality = $student->nationality;
		$religion = $student->religion;
		$sc = $student->sc;
		$mother_tongue = $student->mother_tongue;
		$s_email = $student->s_email;
		$p_email = $student->p_email;
		$r_line1 = $student->r_line1;
		$r_line2 = $student->r_line2;
		$r_city = $student->r_city;
		$r_state = $student->r_state;
		$r_pincode = $student->r_pincode;
		$r_country = $student->r_country;
		$r_phone = $student->r_phone;
		$r_fax = $student->r_fax;
		$c_line1 = $student->c_line1;
		$c_line2 = $student->c_line2;
		$c_city = $student->c_city;
		$c_state = $student->c_state;
		$c_pincode = $student->c_pincode;
		$c_country = $student->c_country;
		$c_phone = $student->c_phone;
		$c_fax = $student->c_fax;
		$ec1 = $student->ec1;
		$ec2 = $student->ec2;
		$ec3 = $student->ec3;
		$ec4 = $student->ec4;
	}
	
	$form['class_detail'] =  array(
    '#type' => 'markup',
		'#markup' => '<div style = "text-align: center; font-weight: 700; "><h2 style = "font-weight: 700; float: left">'.t('Class - '.$class.' '.$section).'</h2>'.'<h2 style = "font-weight: 700;"> Roll No - '.$rollno.'</h2></div>',
  );
	
	$form['ad'] =  array(
		'#title' => 'Admission Details',
		'#type' => 'fieldset',
		'#default_value' => isset($doa)? $doa: NULL,
	);
	$form['ad']['adm_no'] = array(
		'#title' => 'Admission No.',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($adm_no)? $adm_no: NULL,
		'#disabled' => TRUE,
		//'#required' => TRUE,
	);
	
	$dt_oa = strtotime($doa);
	$def_doa = date('Y-m-d', $dt_oa);
	$form['ad']['doa'] = array(
	  '#title' => 'Date of Admission',
	  '#type' => 'date_popup',
		'#attributes' => array('placeholder' => 'dd/mm/yyyy'),
		'#date_format' => 'd-m-Y',
	  '#date_year_range' => '0:0',
		'#default_value' => isset($def_doa)? $def_doa: NULL,
	  //'#required' => TRUE,
	);
	
	$session_id = (string)variable_get('essa_sid');
  $basicinfo = 'essa_'.$session_id.'_basicinfo';
  $basic_info = db_query("
    SELECT * from {$basicinfo}"
  );
	foreach($basic_info as $info){
		$house_op[] = $info -> house1;
		$house_op[] = $info -> house2;
		$house_op[] = $info -> house3;
		$house_op[] = $info -> house4;
		$hostel = $info -> hostel_facility;
		$transport = $info -> transport_facility;
	}
	if(!isset($house_op)){
		$form['ad']['hos'] = array(
			'#type' => 'textfield',
			'#title' => t('Select a house'),
			'#suffix' => '<h2 id = "as_house">'.l(t('Create Houses First'), 'admin/settings/school_setting').'<h2>',
		);
	}else{
		$form['ad']['house'] = array(
			'#type' => 'select',
			'#title' => t('Select a house'),
			'#options' => drupal_map_assoc($house_op),
			'#default_value' => isset($house)? $house: NULL,
		);	
	}
	
	if(isset($hostel)? $hostel: 'YES' == 'YES'){
		$form['ad']['hostel'] = array(
			'#type' => 'radios',
			'#title' => t('Hostel'),
			'#options' => drupal_map_assoc(array('YES', 'NO')),
			'#default_value' => isset($is_hostel)? $is_hostel: NULL,
		);
		
		$form['ad']['hs'] = array(
			'#type' => 'fieldset',
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
			'#states' => array(
				'visible' => array(
				  ':input[name = "hostel"]' => array('value' => 'YES'),
				),
			),
		);
		
		$form['ad']['hs']['room'] = array(
			'#type' => 'textfield',
			'#title' => t('Room No.'),
			'#default_value' => isset($room)? $room: NULL,
		);
	}
	
	
	if(isset($transport)? $transport: 'YES' == 'YES'){
		$form['ad']['transport'] = array(
			'#type' => 'radios',
			'#title' => t('Transport'),
			'#options' => drupal_map_assoc(array('YES', 'NO')),
			'#default_value' => isset($is_transport)? $is_transport: NULL,
		);
	}
  
	$form['ad']['sibling'] = array(
		'#type' => 'radios',
		'#title' => t('Sibling in this school'),
		'#options' => drupal_map_assoc(array('YES', 'NO')),
		'#default_value' => isset($is_sibling)? $is_sibling: NULL,
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
		'#default_value' => isset($sibling_adm_no)? $sibling_adm_no: NULL,
	);
	
	$form['pd'] = array(
		'#type' => 'fieldset',
		'#title' => 'Personal Details',
	);
	$form['pd']['s'] = array(
		'#type' => 'fieldset',
	);
	$form['pd']['s']['s_pic'] = array(
		'#type' => 'file',
		'#title' => t('Student\'s Photograph'),
	);
	$form['pd']['s']['first_name'] = array(
	  '#title' => 'Name of Student',
		'#attributes' => array('placeholder' => 'First Name'),
	  '#type' => 'textfield',
	  '#size' => 20,
	  '#required' => TRUE,
		'#default_value' => isset($first_name)? $first_name: NULL,
	);
	$form['pd']['s']['middle_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Middle Name'),
		'#default_value' => isset($middle_name)? $middle_name: NULL,
	);
	$form['pd']['s']['last_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Last Name'),
		'#default_value' => isset($last_name)? $last_name: NULL,
	);
	$form['pd']['f'] = array(
		'#type' => 'fieldset',
	);
	$form['pd']['f']['f_first_name'] = array(
	  '#title' => 'Father\'s Name',
		'#attributes' => array('placeholder' => 'First Name'),
	  '#type' => 'textfield',
		'#size' => 20,
	  '#required' => TRUE,
		'#default_value' => isset($f_first_name)? $f_first_name: NULL,
	);
	$form['pd']['f']['f_middle_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Middle Name'),
		'#default_value' => isset($f_middle_name)? $f_middle_name: NULL,
	);
	$form['pd']['f']['f_last_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Last Name'),
	  '#required' => TRUE,
		'#default_value' => isset($f_last_name)? $f_last_name: NULL,
	);
	$form['pd']['m'] = array(
		'#type' => 'fieldset',
	);
	$form['pd']['m']['m_first_name'] = array(
	  '#title' => 'Mother\'s Name',
		'#attributes' => array('placeholder' => 'First Name'),
	  '#type' => 'textfield',
	  '#size' => 20,
		'#required' => TRUE,
		'#default_value' => isset($m_first_name)? $m_first_name: NULL,
	);
	$form['pd']['m']['m_middle_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Middle Name'),
		'#default_value' => isset($m_middle_name)? $m_middle_name: NULL,
	);
	$form['pd']['m']['m_last_name'] = array(
	  '#type' => 'textfield',
	  '#size' => 20,
		'#attributes' => array('placeholder' => 'Last Name'),
	  '#required' => TRUE,
		'#default_value' => isset($m_last_name)? $m_last_name: NULL,
	);
	
	$form['pd']['gender'] = array(
	  '#title' => 'Gender',
		'#prefix' => '<br>',
	  '#type' => 'radios',
	  '#options' => array('male' => 'Male', 'female' => 'Female'),
		'#default_value' => isset($gender)? $gender: NULL,
	);
	
	$dt_ob = strtotime($dob);
	$def_dob = date('Y-m-d', $dt_ob);
	$form['pd']['dob'] = array(
	  '#title' => 'Date of Birth',
	  '#type' => 'date_popup',
		'#attributes' => array('placeholder' => 'dd/mm/yy'),
		'#date_format' => 'd-m-Y',
	  '#date_year_range' => '-30:-4',
	  '#required' => TRUE,
		'#default_value' => isset($def_dob)? $def_dob: NULL,
	);
	$form['pd']['nationality'] = array(
		'#title' => 'Nationality',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($nationality)? $nationality: NULL,
	);	
	$form['pd']['religion'] = array(
		'#title' => 'Religion',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($religion)? $religion: NULL,
	);
	$form['pd']['sc'] = array(
		'#title' => 'SC/ST',
		'#type' => 'radios',
		'#options' => drupal_map_assoc(array('YES', 'NO')),
		'#default_value' => isset($sc)? $sc: NULL,
	);
	$form['pd']['mother_tongue'] = array(
		'#title' => 'Mother Tongue',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($mother_tongue)? $mother_tongue: NULL,
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
		'#default_value' => isset($s_email)? $s_email: NULL,
		//'#required' => TRUE,
	);
	$form['cd']['pemail'] = array(
		'#title' => 'Parent\'s Email',
		'#type' => 'textfield',
		'#size' => 50,
		'#rules' => array(
	      'email',
    ),
		'#default_value' => isset($p_email)? $p_email: NULL,
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
		'#size' => 35,
		'#default_value' => isset($r_line1)? $r_line1: NULL,
	);
	$form['cd']['pa']['line2'] = array(
		'#type' => 'textfield',
		'#title' => t('Line2'),
		'#resizable' => FALSE,
		'#size' => 35,
		'#default_value' => isset($r_line2)? $r_line2: NULL,
	);
	$form['cd']['pa']['city'] = array(
		'#title' => 'City',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($r_city)? $r_city: NULL,
	);
	$form['cd']['pa']['state'] = array(
		'#title' => 'State',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($r_state)? $r_state: NULL,
	);
	$form['cd']['pa']['pin'] = array(
		'#title' => 'Pincode',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($r_pincode)? $r_pincode: NULL,
	);
	$form['cd']['pa']['country'] = array(
		'#title' => 'Country',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($r_country)? $r_country: NULL,
	);
	$form['cd']['pa']['phone'] = array(
		'#title' => 'Phone no.',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($r_phone)? $r_phone: NULL,
	);
	$form['cd']['pa']['fax'] = array(
		'#title' => 'FAX no.',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($r_fax)? $r_fax: NULL,
	);
	$form['cd']['ca'] = array(
		'#type' => 'fieldset',
		'#title' => 'Correspondence Address',
	);
	$form['cd']['ca']['caline1'] = array(
		'#type' => 'textfield',
		'#title' => t('Line1'),
		'#resizable' => FALSE,
		'#size' => 35,
		'#default_value' => isset($c_line1)? $c_line1: NULL,
	);
	$form['cd']['ca']['caline2'] = array(
		'#type' => 'textfield',
		'#title' => t('Line2'),
		'#resizable' => FALSE,
		'#size' => 35,
		'#default_value' => isset($c_line2)? $c_line2: NULL,
	);
	$form['cd']['ca']['cacity'] = array(
		'#title' => 'City',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($c_city)? $c_city: NULL,
	);
	$form['cd']['ca']['castate'] = array(
		'#title' => 'State',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($c_state)? $c_state: NULL,
	);
	$form['cd']['ca']['capin'] = array(
		'#title' => 'Pincode',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($c_pincode)? $c_pincode: NULL,
	);
	$form['cd']['ca']['cacountry'] = array(
		'#title' => 'Country',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($c_country)? $c_country: NULL,
	);
	$form['cd']['ca']['caphone'] = array(
		'#title' => 'Phone no.',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($c_phone)? $c_phone: NULL,
	);
	$form['cd']['ca']['cafax'] = array(
		'#title' => 'FAX no.',
		'#type' => 'textfield',
		'#size' => 20,
		'#default_value' => isset($c_fax)? $c_fax: NULL,
	);
	
	$form['cd']['ec'] = array(
		'#type' => 'fieldset',
		'#title' => 'Emergency Contact No.',
	);
	$form['cd']['ec']['ec1'] = array(
		'#type' => 'textfield',
		'#size' => 19,
		'#attributes' => array('placeholder' => 'Emergency Contact No.1'),
		'#default_value' => isset($ec1)? $ec1: NULL,
	);
	$form['cd']['ec']['ec2'] = array(
		'#type' => 'textfield',
		'#size' => 19,
		'#attributes' => array('placeholder' => 'Emergency Contact No.2'),
		'#default_value' => isset($ec2)? $ec2: NULL,
	);
	$form['cd']['ec']['ec3'] = array(
		'#type' => 'textfield',
		'#size' => 19,
		'#attributes' => array('placeholder' => 'Emergency Contact No.3'),
		'#default_value' => isset($ec3)? $ec3: NULL,
	);
	$form['cd']['ec']['ec4'] = array(
		'#type' => 'textfield',
		'#size' => 19,
		'#attributes' => array('placeholder' => 'Emergency Contact No.4'),
		'#default_value' => isset($ec4)? $ec4: NULL,
	);
	
	$students = db_query("
    SELECT * from {$student_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($students as $student){
		
	}
	
	$form['fi'] = array(
		'#type' => 'fieldset',
		'#title' => 'Family Info',
	);
	$family_info = array('Name', 'Educational Qualification', 'Occupation',
											 'Designation', 'Annual Income', 'Age', 'Nationality', 'Institution', 'Office Address',
											 'Telephone No.');
	$students = db_query("
    SELECT * from {$student_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($students as $student){
		$father['Name']['Name'] = $student->fi_f_name;
		$mother['Name']['Name'] = $student->fi_m_name;
		$father['Educational Qualification']['Educational Qualification'] = $student->fi_f_qualification;
		$mother['Educational Qualification']['Educational Qualification'] = $student->fi_m_qualification;
		$father['Occupation']['Occupation'] = $student->fi_f_occupation;
		$mother['Occupation']['Occupation'] = $student->fi_m_occupation;
		$father['Designation']['Designation'] = $student->fi_f_designation;
		$mother['Designation']['Designation'] = $student->fi_m_designation;
		$father['Annual Income']['Annual Income'] = $student->fi_f_annual_income;
		$mother['Annual Income']['Annual Income'] = $student->fi_m_annual_income;
		$father['Age']['Age'] = $student->fi_f_age;
		$mother['Age']['Age'] = $student->fi_m_age;
		$father['Nationality']['Nationality'] = $student->fi_f_nationality;
		$mother['Nationality']['Nationality'] = $student->fi_m_nationality;
		$father['Institution']['Institution'] = $student->fi_f_institution;
		$mother['Institution']['Institution'] = $student->fi_m_institution;
		$father['Office Address']['Office Address'] = $student->fi_f_office_add;
		$mother['Office Address']['Office Address'] = $student->fi_m_office_add;
		$father['Telephone No.']['Telephone No.'] = $student->fi_f_phone;
		$mother['Telephone No.']['Telephone No.'] = $student->fi_m_phone;
	}
	foreach($family_info as $info){
    //dsm($info);
    $row[$info] = array(
      '#tree' =>TRUE,
      $info => array(  //Generating unique array id for every form element
        'c1' =>array(
          '#type' => 'markup',
          '#markup' => '<h3>'.$info.'</h3>',
        ),
        'c2' =>array(
          '#type' => 'textfield',
					'#default_value' => isset($father[$info][$info])? $father[$info][$info]: NULL,
        ),
        'c3' =>array(
					'#type' => 'textfield',
					'#default_value' => isset($mother[$info][$info])? $mother[$info][$info]: NULL,
        ),
      ),
    );
  }
  
  //Calling the theme function to build the custom table and display the form in tabular format.
  $form['fi']['class'] = array(
    '#theme' => 'family_info_table',
    'rows' => $row,
  );
	$students = db_query("
    SELECT * from {$student_table} where uid = :uid;", array(':uid' => $user)
  );
  foreach($students as $student){
		$blood_group = $student->blood_group;
		$def['immu_bcg'] = isset($student->immu_bcg)?$student->immu_bcg:NULL;
		$def['immu_opv'] = isset($student->immu_opv)?$student->immu_opv:NULL;
		$def['immu_dpt'] = isset($student->immu_dpt)?$student->immu_dpt:NULL;
		$def['immu_opv_booster'] = isset($student->immu_opv_booster)?$student->immu_opv_booster:NULL;
		$def['immu_dpt_booster'] = isset($student->immu_dpt_booster)?$student->immu_dpt_booster:NULL;
		$def['immu_measles'] = isset($student->immu_measles)?$student->immu_measles:NULL;
		$def['immu_mmr'] = isset($student->immu_mmr)?$student->immu_mmr:NULL;
		$def['immu_typhoid'] = isset($student->immu_typhoid)?$student->immu_typhoid:NULL;
		$def['immu_hep_b'] = isset($student->immu_hep_b)?$student->immu_hep_b:NULL;
		$def['immu_ao'] = isset($student->immu_any_other)?$student->immu_any_other:NULL;
		$bh = $student->birth_history;
		$is_allergy = $student->is_allergy;
		$allergic_to = $student->allergic_to;
		//$allergy = $student->allergy;
		$diseases['epilepsy'] = $student->epilepsy;
		$diseases['asthma'] = $student->asthma;
		$diseases['skin_desease'] = $student->skin_desease;
		$diseases['eye'] = $student->eye;
		$diseases['surgery'] = $student->surgery;
		$doc['doc_med'] = $student->doc_med;
		$doc['doc_birth'] = $student->doc_birth;
		$doc['doc_trans'] = $student->doc_trans;
		$doc['doc_pta'] = $student->doc_pta;
		$doc['doc_ad_fee'] = $student->doc_ad_fee;
	}
	$form['medical_history'] = array(
	  '#title' => 'Medical History',
	  '#type' => 'fieldset',
	);
	$form['medical_history']['blood_group'] = array(
		'#type' => 'select',
		'#title' => t('Blood Group'),
		'#options' => drupal_map_assoc(array('A+', 'A-', 'B+', 'B-', 'AB+', 'AB-', 'O+', 'O-')),
		'#default_value' => isset($blood_group)? $blood_group: NULL,
	);
	$form['medical_history']['im'] = array(
	  '#type' => 'fieldset',
		'#title' => t('Immunization Status'),
	);
	$form['medical_history']['im']['immunization'] = array(
		'#type' => 'checkboxes',
		'#options' => drupal_map_assoc(array('BCG', 'Measles', 'OPV', 'MMR', 'DPT', 'Typhoid', 'Booster for OPV', 'Booster for DPT', 'Hepatitis-B', 'Any Other')),
		'#default_value' => $def,
	);
	$form['medical_history']['birth_history'] = array(
		'#type' => 'textarea',
		'#title' => t('Birth History/ History of major illness of disorder, if any'),
		'#default_value' => isset($bh)? $bh: NULL,
	);
	$form['medical_history']['allergy'] = array(
	  '#type' => 'radios',
	  '#title' => 'Allergy to any Item/Drug',
	  '#options' => array('yes' => t('Yes'), 'no' => t('No')),
		'#default_value' =>isset($allergic_to)? $allergic_to: 'no',
	);
	$form['medical_history']['text'] = array(
	  '#type' => 'textfield',
	  '#attributes' => array('placeholder' => array('Specify the Item/Drug')),
	  '#states' => array(
      'visible' => array(   // action to take.
        ':input[name="allergy"]' => array('value' => t('yes')),
      )
		),
	'#default_value' =>isset($is_allergy)? $is_allergy: 'no',
	);
	$form['medical_history']['disease'] = array(
	  '#type' => 'checkboxes',
		'#options' => drupal_map_assoc(array('Epilepsy', 'Bronchial Asthma/Bronchospasm', 'Skin Disease', 'Eye/ENT problem', 'Any Surgery Undergone',)),
		'#default_value' => $diseases,
	);
	//dsm($form);
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
		'#default_value' => $doc,
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
	
  return $form;
}

function edit_student_form_validate($form, &$form_state){
	
}

function edit_student_form_submit($form, &$form_state){
	$session = (string)variable_get('essa_sid');
	$class = $form_state['values']['this_class_id'];
	$section = $form_state['values']['this_section'];
	
	$table = 'essa_'.$session.'_master_student_table';
	db_merge($table)
		->key(array('adm_no' => $form_state['values']['adm_no']))
		->fields (array(
			'adm_no' => $form_state['values']['adm_no'],
			'doa' => $form_state['values']['doa'],
			'house' => $form_state['values']['house'],
			'is_hostel' => $form_state['values']['hostel'],
			'room' => $form_state['values']['room'],
			'is_transport' => $form_state['values']['transport'],
			'is_sibling' => $form_state['values']['sibling'],
			'sibling_adm_no' => $form_state['values']['adm'],
			'student_name' => $form_state['values']['first_name'].' '.$form_state['values']['middle_name'].' '.$form_state['values']['last_name'],
			'first_name' => $form_state['values']['first_name'],
			'middle_name' => $form_state['values']['middle_name'],
			'last_name' => $form_state['values']['last_name'],
			'f_first_name' => $form_state['values']['f_first_name'],
			'f_middle_name' => $form_state['values']['f_middle_name'],
			'f_last_name' => $form_state['values']['f_last_name'],
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
			'fi_f_name' => $form_state['values']['Name']['Name']['c2'],
			'fi_m_name' => $form_state['values']['Name']['Name']['c3'],
			'fi_f_qualification' => $form_state['values']['Educational Qualification']['Educational Qualification']['c2'],
			'fi_m_qualification' => $form_state['values']['Educational Qualification']['Educational Qualification']['c3'],
			'fi_f_occupation' => $form_state['values']['Occupation']['Occupation']['c2'],
			'fi_m_occupation' => $form_state['values']['Occupation']['Occupation']['c3'],
			'fi_f_designation' => $form_state['values']['Designation']['Designation']['c2'],
			'fi_m_designation' => $form_state['values']['Designation']['Designation']['c3'],
			'fi_f_annual_income' => $form_state['values']['Annual Income']['Annual Income']['c2'],
			'fi_m_annual_income' => $form_state['values']['Annual Income']['Annual Income']['c3'],
			'fi_f_age' => (int)$form_state['values']['Age']['Age']['c2'],
			'fi_m_age' => (int)$form_state['values']['Age']['Age']['c3'],
			'fi_f_nationality' => $form_state['values']['Nationality']['Nationality']['c2'],
			'fi_m_nationality' => $form_state['values']['Nationality']['Nationality']['c3'],
			'fi_f_institution' => $form_state['values']['Institution']['Institution']['c2'],
			'fi_m_institution' => $form_state['values']['Institution']['Institution']['c3'],
			'fi_f_office_add' => $form_state['values']['Office Address']['Office Address']['c2'],
			'fi_m_office_add' => $form_state['values']['Office Address']['Office Address']['c3'],
			'fi_f_phone' => $form_state['values']['Telephone No.']['Telephone No.']['c2'],
			'fi_m_phone' => $form_state['values']['Telephone No.']['Telephone No.']['c3'],
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
			'is_hostel' => $form_state['values']['hostel'],
			'is_transport' => $form_state['values']['transport'],
		)
	)	
	->execute();
}
