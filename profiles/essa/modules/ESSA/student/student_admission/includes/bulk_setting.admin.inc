<?php
/**
 *Implements page call back suntion - books_bu_settings
 */
function bulk_settings($form, &$form_state){
	$form = array();
	
	$options['NULL'] = 'None';
	for($i=1;$i<32;$i++){
		$options[$i] = $i;
	}
	
	$def = variable_get('essa_st_default');
	if($def == 1){
		$form['adm_no'] = array(
			'#type' => 'select',
			'#title' => 'Adm. No.',
			'#options' => $options,
			'#default_value' => 1,
		);
		
		$form['doa'] = array(
			'#type' => 'select',
			'#title' => 'Date of Admission',
			'#options' => $options,
			'#default_value' => 2,
		);
		
		$form['gender'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Gender',
			'#default_value' => 3,
		);
		
		$form['s_first_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Student's First Name",
			'#default_value' => 4,
		);
		
		$form['s_middle_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Student's Middle Name",
			'#default_value' => 5,
		);
	
		$form['s_last_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Student's Last Name",
			'#default_value' => 6,
		);
		
		$form['class'] = array(
			'#type' => 'select',
			'#title' => 'Class',
			'#options' => $options,
			'#default_value' => 7,
		);
		
		$form['section'] = array(
			'#type' => 'select',
			'#title' => 'Section',
			'#options' => $options,
			'#default_value' => 8,
		);
	
		$form['dob'] = array(
			'#type' => 'select',
			'#title' => 'Date of Birth',
			'#options' => $options,
			'#default_value' => 9,
		);
	
		$form['phone1'] = array(
			'#type' => 'select',
			'#title' => 'Phone No. 1',
			'#options' => $options,
			'#default_value' => 10,
		);
		
		$form['phone2'] = array(
			'#type' => 'select',
			'#title' => 'Phone No. 2',
			'#options' => $options,
			'#default_value' => 11,
		);
		
		$form['phone3'] = array(
			'#type' => 'select',
			'#title' => 'Phone No. 3',
			'#options' => $options,
			'#default_value' => 12,
		);
		
		$form['phone4'] = array(
			'#type' => 'select',
			'#title' => 'Phone No. 4',
			'#options' => $options,
			'#default_value' => 13,
		);
		
		$form['phone5'] = array(
			'#type' => 'select',
			'#title' => 'Phone No. 5',
			'#options' => $options,
			'#default_value' => 14,
		);
	
		$form['s_email'] = array(
			'#type' => 'select',
			'#title' => "Student's Email ID",
			'#options' => $options,
			'#default_value' => 15,
		);
		
		$form['p_email'] = array(
			'#type' => 'select',
			'#title' => "Parent's Email ID",
			'#options' => $options,
			'#default_value' => 16,
		);
		
		
		$form['f_first_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Father's First Name",
			'#default_value' => 17,
		);
		
		$form['f_middle_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Father's Middle Name",
			'#default_value' => 18,
		);
	
		$form['f_last_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Father's Last Name",
			'#default_value' => 19,
		);
		
		$form['m_first_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Mother's First Name",
			'#default_value' => 20,
		);
		
		$form['m_middle_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Mother's Middle Name",
			'#default_value' => 21,
		);
		
		$form['m_last_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Mother's Last Name",
			'#default_value' => 22,
		);
		
		$form['line1'] = array(
			'#type' => 'select',
			'#title' => 'Address Line 1',
			'#options' => $options,
			'#default_value' => 23,
		);
		
		$form['line2'] = array(
			'#type' => 'select',
			'#title' => 'Address Line 2',
			'#options' => $options,
			'#default_value' => 24,
		);
		
		$form['city'] = array(
			'#type' => 'select',
			'#title' => 'Address City',
			'#options' => $options,
			'#default_value' => 25,
		);
		
		$form['state'] = array(
			'#type' => 'select',
			'#title' => 'Address State',
			'#options' => $options,
			'#default_value' => 26,
		);
		
		$form['pincode'] = array(
			'#type' => 'select',
			'#title' => 'Address Pincode',
			'#options' => $options,
			'#default_value' => 27,
		);
		
		$form['country'] = array(
			'#type' => 'select',
			'#title' => 'Address Country',
			'#options' => $options,
			'#default_value' => 28,
		);
		
		$form['sc_st'] = array(
			'#type' => 'select',
			'#title' => 'SC/ST',
			'#options' => $options,
			'#default_value' => 29,
		);
		
		$form['blood_group'] = array(
			'#type' => 'select',
			'#title' => 'Blood Group',
			'#options' => $options,
			'#default_value' => 30,
		);
		
		$form['boarder'] = array(
			'#type' => 'select',
			'#title' => 'Boarder',
			'#options' => $options,
			'#default_value' => 31 ,
		);
		
		
	}else{
		$adm_no = variable_get('essa_st_adm_no');
		$form['adm_no'] = array(
			'#type' => 'select',
			'#title' => 'Adm. No.',
			'#options' => $options,
			'#default_value' => isset($adm_no)?$adm_no:NULL,
		);
		
		$doa = variable_get('essa_st_doa');
		$form['doa'] = array(
			'#type' => 'select',
			'#title' => 'Date of Admission',
			'#options' => $options,
			'#default_value' => isset($doa)?$doa:NULL,
		);
		
		$gender = variable_get('essa_st_gender');
		$form['gender'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Gender',
			'#default_value' => isset($gender)?$gender:NULL,
		);
		
		$s_first_name = variable_get('essa_st_fname');
		$form['s_first_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Student's First Name",
			'#default_value' => isset($s_first_name)?$s_first_name:NULL,
		);
		
		$s_middle_name = variable_get('essa_st_mname');
		$form['s_middle_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Student's Middle Name",
			'#default_value' => isset($s_middle_name)?$s_middle_name:NULL,
		);
	
		$s_last_name = variable_get('essa_st_lname');
		$form['s_last_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Student's Last Name",
			'#default_value' => isset($s_last_name)?$s_last_name:NULL,
		);
		
		$class = variable_get('essa_st_class');
		$form['class'] = array(
			'#type' => 'select',
			'#title' => 'Class',
			'#options' => $options,
			'#default_value' => isset($class)?$class:NULL,
		);
		
		$section = variable_get('essa_st_section');
		$form['section'] = array(
			'#type' => 'select',
			'#title' => 'Section',
			'#options' => $options,
			'#default_value' => isset($section)?$section:NULL,
		);
	
		$dob = variable_get('essa_st_dob');
		$form['dob'] = array(
			'#type' => 'select',
			'#title' => 'Date of Birth',
			'#options' => $options,
			'#default_value' => isset($dob)?$dob:NULL,
		);
	
		$phone1 = variable_get('essa_st_phone1');
		$form['phone1'] = array(
			'#type' => 'select',
			'#title' => 'Phone No. 1',
			'#options' => $options,
			'#default_value' => isset($phone1)?$phone1:NULL,
		);
		
		
		$phone2 = variable_get('essa_st_phone2');
		$form['phone2'] = array(
			'#type' => 'select',
			'#title' => 'Phone No. 2',
			'#options' => $options,
			'#default_value' => isset($phone2)?$phone2:NULL,
		);
		
		$phone3 = variable_get('essa_st_phone3');
		$form['phone3'] = array(
			'#type' => 'select',
			'#title' => 'Phone No. 3',
			'#options' => $options,
			'#default_value' => isset($phone3)?$phone3:NULL,
		);
		
		$phone4 = variable_get('essa_st_phone4');
		$form['phone4'] = array(
			'#type' => 'select',
			'#title' => 'Phone No. 4',
			'#options' => $options,
			'#default_value' => isset($phone4)?$phone4:NULL,
		);
		
		$phone5 = variable_get('essa_st_phone5');
		$form['phone5'] = array(
			'#type' => 'select',
			'#title' => 'Phone No. 5',
			'#options' => $options,
			'#default_value' => isset($phone5)?$phone5:NULL,
		);
	
		$s_email = variable_get('essa_st_s_email');
		$form['s_email'] = array(
			'#type' => 'select',
			'#title' => "Student's Email ID",
			'#options' => $options,
			'#default_value' => isset($s_email)?$s_email:NULL,
		);
		
		$p_email = variable_get('essa_st_p_email');
		$form['p_email'] = array(
			'#type' => 'select',
			'#title' => "Parent's Email ID",
			'#options' => $options,
			'#default_value' => isset($p_email)?$p_email:NULL,
		);
		
		$f_first_name = variable_get('essa_st_f_fname');
		$form['f_first_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Father's First Name",
			'#default_value' => isset($f_first_name)?$f_first_name:NULL,
		);
		
		$f_middle_name = variable_get('essa_st_f_mname');
		$form['f_middle_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Father's Middle Name",
			'#default_value' => isset($f_middle_name)?$f_middle_name:NULL,
		);
	
		$f_last_name = variable_get('essa_st_f_lname');
		$form['f_last_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Father's Last Name",
			'#default_value' => isset($f_last_name)?$f_last_name:NULL,
		);
		
		$m_first_name = variable_get('essa_st_m_fname');
		$form['m_first_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Mother's First Name",
			'#default_value' => isset($m_first_name)?$m_first_name:NULL,
		);
		
		$m_middle_name = variable_get('essa_st_m_mname');
		$form['m_middle_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Mother's Middle Name",
			'#default_value' => isset($m_middle_name)?$m_middle_name:NULL,
		);
		
		$m_last_name = variable_get('essa_st_m_lname');
		$form['m_last_name'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => "Mother's Last Name",
			'#default_value' => isset($m_last_name)?$m_last_name:NULL,
		);		
		
		$line1 = variable_get('essa_st_line1');
		$form['line1'] = array(
			'#type' => 'select',
			'#title' => 'Address Line 1',
			'#options' => $options,
			'#default_value' => isset($line1)?$line1:NULL,
		);
		
		$line2 = variable_get('essa_st_line2');
		$form['line2'] = array(
			'#type' => 'select',
			'#title' => 'Address Line 2',
			'#options' => $options,
			'#default_value' => isset($line2)?$line2:NULL,
		);
		
		$city = variable_get('essa_st_city');
		$form['city'] = array(
			'#type' => 'select',
			'#title' => 'Address City',
			'#options' => $options,
			'#default_value' => isset($city)?$city:NULL,
		);
		
		$state = variable_get('essa_st_state');
		$form['state'] = array(
			'#type' => 'select',
			'#title' => 'Address State',
			'#options' => $options,
			'#default_value' => isset($state)?$state:NULL,
		);
		
		$pincode = variable_get('essa_st_pincode');
		$form['pincode'] = array(
			'#type' => 'select',
			'#title' => 'Address Pincode',
			'#options' => $options,
			'#default_value' => isset($pincode)?$pincode:NULL,
		);
		
		$country = variable_get('essa_st_country');
		$form['country'] = array(
			'#type' => 'select',
			'#title' => 'Address Country',
			'#options' => $options,
			'#default_value' => isset($country)?$country:NULL,
		);
		
		$sc_st = variable_get('essa_st_scst');
		$form['sc_st'] = array(
			'#type' => 'select',
			'#title' => 'SC/ST',
			'#options' => $options,
			'#default_value' => isset($sc_st)?$sc_st:NULL,
		);
		
		$blood_group = variable_get('essa_st_blood_group');
		$form['blood_group'] = array(
			'#type' => 'select',
			'#title' => 'Blood Group',
			'#options' => $options,
			'#default_value' => isset($blood_group)?$blood_group:NULL,
		);
		
		$boarder = variable_get('essa_st_boarder');
		$form['boarder'] = array(
			'#type' => 'select',
			'#title' => 'Boarder',
			'#options' => $options,
			'#default_value' => isset($boarder)?$boarder:NULL,
		);
		
	}
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	
	$form['set_none'] = array(
		'#type' => 'submit',
		'#value' => 'Flush Defaults',
		'#submit' => array('set_none_st'),
	);
	
	$form['set_default'] = array(
		'#type' => 'submit',
		'#value' => 'Set Defaults',
		'#submit' => array('set_default_st'),
	);
	return $form;
}

function set_default_st(){
	variable_set('essa_st_default', 1);
}

function set_none_st(){
	variable_set('essa_st_default', 0);
	variable_set('esaa_st_adm_no', NULL);
	variable_set('esaa_st_doa', NULL);
	variable_set('esaa_st_gender', NULL);
	variable_set('esaa_st_fname', NULL);
	variable_set('esaa_st_mname', NULL);
	variable_set('esaa_st_lname', NULL);
	variable_set('esaa_st_class', NULL);
	variable_set('esaa_st_sec', NULL);
	variable_set('esaa_st_dob', NULL);
	variable_set('esaa_st_phone1', NULL);
	variable_set('esaa_st_phone2', NULL);
	variable_set('esaa_st_phone3', NULL);
	variable_set('esaa_st_phone4', NULL);
	variable_set('esaa_st_phone5', NULL);
	variable_set('esaa_st_s_email', NULL);
	variable_set('esaa_st_p_email', NULL);
	variable_set('esaa_st_f_fname', NULL);
	variable_set('esaa_st_f_mname', NULL);
	variable_set('esaa_st_f_lname', NULL);
	variable_set('esaa_st_m_fname', NULL);
	variable_set('esaa_st_m_mname', NULL);
	variable_set('esaa_st_m_lname', NULL);
	variable_set('esaa_st_line1', NULL);
	variable_set('esaa_st_line2', NULL);
	variable_set('esaa_st_city', NULL);
	variable_set('esaa_st_state', NULL);
	variable_set('esaa_st_pincode', NULL);
	variable_set('esaa_st_country', NULL);
	variable_set('esaa_st_scst', NULL);
	variable_set('esaa_st_blood_group', NULL);
	variable_set('esaa_st_boarder', NULL);
}

/**
 *Implements validate suntion - books_bu_settings
 */
function bulk_settings_validate($form, &$form_state){
	if($form_state['values']['adm_no'] == 'NULL' && $form_state['triggering_element']['#value'] == 'Save'){
		form_set_error('adm_no', 'Admission no. can\'t be "None".');
	}
	
	if($form_state['values']['s_first_name'] == 'NULL'  && $form_state['triggering_element']['#value'] == 'Save'){
		form_set_error('s_first_name', 'Student\'s First Name can\'t be "None".');
	}
	
	if($form_state['values']['class'] == 'NULL'  && $form_state['triggering_element']['#value'] == 'Save'){
		form_set_error('class', 'Class can\'t be "None".');
	}
	
	if($form_state['values']['section'] == 'NULL'  && $form_state['triggering_element']['#value'] == 'Save'){
		form_set_error('section', 'Section can\'t be "None".');
	}
	
	$arr = array();
	foreach($form_state['input'] as $k => $val){
		$arr[$k] = $val;
	}
	$count = array_count_values($arr);
	variable_set('essa_st_error', 0);
	foreach($count as $v => $c){
		if($v != 'NULL'){
			if($c > 1){
				//dsm($v);
				variable_set('essa_st_error', 1);
			}
		}
	}
	
	
}

/**
 *Implements submit suntion - books_bu_settings
 */
function bulk_settings_submit($form, &$form_state){
	if(variable_get('essa_st_error') == 0){
		variable_set('esaa_st_adm_no', $form_state['values']['adm_no']);
		variable_set('esaa_st_doa', $form_state['values']['doa']);
		variable_set('esaa_st_gender', $form_state['values']['gender']);
		variable_set('esaa_st_fname', $form_state['values']['s_first_name']);
		variable_set('esaa_st_mname', $form_state['values']['s_middle_name']);
		variable_set('esaa_st_lname', $form_state['values']['s_last_name']);
		variable_set('esaa_st_class', $form_state['values']['class']);
		variable_set('esaa_st_sec', $form_state['values']['section']);
		variable_set('esaa_st_dob', $form_state['values']['dob']);
		variable_set('esaa_st_phone1', $form_state['values']['phone1']);
		variable_set('esaa_st_phone2', $form_state['values']['phone2']);
		variable_set('esaa_st_phone3', $form_state['values']['phone3']);
		variable_set('esaa_st_phone4', $form_state['values']['phone4']);
		variable_set('esaa_st_phone5', $form_state['values']['phone5']);
		variable_set('esaa_st_s_email', $form_state['values']['s_email']);
		variable_set('esaa_st_p_email', $form_state['values']['p_email']);
		variable_set('esaa_st_f_fname', $form_state['values']['f_first_name']);
		variable_set('esaa_st_f_mname', $form_state['values']['f_middle_name']);
		variable_set('esaa_st_f_lname', $form_state['values']['f_last_name']);
		variable_set('esaa_st_m_fname', $form_state['values']['m_first_name']);
		variable_set('esaa_st_m_mname', $form_state['values']['m_middle_name']);
		variable_set('esaa_st_m_lname', $form_state['values']['m_last_name']);
		variable_set('esaa_st_line1', $form_state['values']['line1']);
		variable_set('esaa_st_line2', $form_state['values']['line2']);
		variable_set('esaa_st_city', $form_state['values']['city']);
		variable_set('esaa_st_state', $form_state['values']['state']);
		variable_set('esaa_st_pincode', $form_state['values']['pincode']);
		variable_set('esaa_st_country', $form_state['values']['country']);
		variable_set('esaa_st_scst', $form_state['values']['sc_st']);
		variable_set('esaa_st_blood_group', $form_state['values']['blood_group']);
		variable_set('esaa_st_boarder', $form_state['values']['boarder']);
		variable_set('essa_st_default', 0);
		drupal_set_message('Settings for bulk upload was saved successfullly.','status');
	}else{
		drupal_set_message('You cannot match two fields to same column.', 'error');
	}
}