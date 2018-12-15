<?php

/**
 *Implements page callback function - create_certificates
 */
function create_certificates($form = array(), &$form_state){
  
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
  );
  
  $form['header'] = array(
    '#type' => 'managed_file',
    '#name' => 'header',
    '#title' => t('Header'),
    '#size' => 40,
    //'#description' => t("Image should be less than 400 pixels wide and in JPG format."),
    '#upload_location' => 'public://certificates/header/',
    '#description' => 'Max width of the image shall be not more than 800px',
  );
  /*
  $form['header_text'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('Header Text'),
  );
  */
  $form['body'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('Body'),
  );
  
  $form['fs'] = array(
    '#type' => 'fieldset',
    '#title' => 'Replacement Patterns',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['fs']['rp'] = array(
    '#type' => 'markup',
    '#markup' => '
      <p>Using below replacement patterns will automatically replace them with appropriate values in the certificate. Replacement patterns are within the square brackets i.e. [ ], please copy(or type) the square brackets also along with the replacement string.</p>
      <p><i>NOTE: Please take due care to write the replacement patterns carefully. It is recommended that you copy and paste the patterns to avoid typing errors.</i></p>
      <p>WARNING: In case of any spelling mistake, the certificate will not be generated correctly.<p>
      <table>
      <tr>
      <td>[student_name] => Student\'s Name</td>
      <td>[adm_no] => Admission No.</td>
      <td>[today_date] => Today\'s Date</td>
      </tr>
      <tr>
      <td>[student_first_name] => Student\'s First Name</td>
      <td>[class] => Class</td>
      <td>[fph] => Fee Payment History</td>
      </tr>
      <tr>
      <td>[student_last_name] => Student\'s Last Name</td>
      <td>[section] => Section</td>
      <td>[tph] => Total Fee Paid</td>
      </tr>
      <tr>
      <td>[father_name] => Father\'s Name</td>
      <td>[class_section] => Class - Section</td>
      <td>[fdd] => Fee Due Detail</td>
      </tr>
      <tr>
      <td>[father_first_name] => Father\'s First Name</td>
      <td>[doa] => Date of Admission</td>
      <td>[tfd] => Total Fee Due</td>
      </tr>
      <tr>
      <td>[father_last_name] => Father\'s last Name</td>
      <td>[dob] => Date of Birth</td>
      <td>[board] => School\'s board</td>
      </tr>
      <tr>
      <td>[mother_name] => Mother\'s Name</td>
      <td>[session] => Session</td>
      <td>[acsm] => Academic Year Start month</td>
      </tr>
      <tr>
      <td>[mother_first_name] => Mother\'s First Name</td>
      <td>[scn] => School Code No</td>
      <td>[acem] => Academic Year End month</td>
      </tr>
      <tr>
      <td>[mother_last_name] => Mother\'s last Name</td>
      <td>[affiliation_no] => Affiliation No.</td>
      <td>[school_name] => Name of School</td>
      </tr>
      <tr>
      <td>[sr_no] => Serial no.</td>
      <td>[roll_no] => Roll No.</td>
      </tr>
      </table>
      <p>PS: The values will only be replaced if they are provided prior to certificate generation. In case of any discrepancies, first check if the data has been provided correctly. If the problem persists please feel free to get on touch with us.</p>
    '
  );
  
  $form['fs']['sr_no'] = array(
    '#type' => 'textfield',
    '#default_value' => 1,
    '#title' => 'Serial no. starts from - ',
    '#size' => 5,
  );
  /*
  $form['watermark'] = array(
    '#type' => 'managed_file',
    '#name' => 'header',
    '#title' => t('Water Mark'),
    '#size' => 40,
    //'#description' => t("Image should be less than 400 pixels wide and in JPG format."),
    '#upload_location' => 'public://certificates/watermark/',
    '#description' => 'Max width of the image shall be not more than 800px',
  );
  */
  /*
  $form['footer'] = array(
    '#type' => 'managed_file',
    '#title' => t('Footer'),
    '#title' => t('Footer'),
    '#size' => 40,
    //'#description' => t("Image should be less than 400 pixels wide and in JPG format."),
    '#upload_location' => 'public://header/',
  );
  */
  $form['footer_text'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('Footer Text'),
  );
  
  for($i=1; $i<=5; $i++){
		$row[$i] = array(
			'#tree' =>TRUE,
			$i => array(  //Generating unique array id for every form element
        'c1' =>array(
				  '#type' => 'markup',
          '#markup' => '<h2>'.$i.'</h2>',
				),
				'c2' =>array(
				  '#type' => 'textfield',
          '#size' => 20,
				),
				'c3' =>array(
				  '#type' => 'textfield',
          '#size' => 20,
				),
		  ),
		);
  }
  
  $form['fs']['rp_fs'] = array(
    '#type' => 'fieldset',
    '#title' => 'Create Custom Replacement Patterns.',
    '#description' => '<p>You can later fill in the values for these patterns and generate certificates accordingly. It is strongly suggested that you create the replacement patterns in the format - "["Replacement String"]", for example- [character]</p>',
  );
  $form['fs']['rp_fs']['rp_table'] = array(
    '#theme' => 'rp_table',
    'rows' => $row,
  );
	
  
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  //dsm(strtotime(date('d-m-Y')));
  //dsm($user);
  return $form;
}

/**
 *Implements validate function.
 */
function create_certificates_validate($form, &$form_state){
  $session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  $titles = array();
  $certificates = db_query(
		"SELECT * from $certificate_table;"
	);
  foreach($certificates as $certificate){
    $titles[] = $certificate->title;
  }
  
  if(in_array($form_state['values']['title'], $titles)){
    form_set_error('title', 'The title must be unique.');
  }
}
/**
 *Implements submit function.
 */
function create_certificates_submit($form, &$form_state){
  
  $session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  
  if ($form_state['values']['header'] != 0) {
    $file = file_load($form_state['values']['header']);
    $ext = explode('.', $file->filename);
    $file->filename = $form_state['values']['title'].'.'.$ext[1];
    $file->status = FILE_STATUS_PERMANENT;
    $header_filename = $file->filename;
    file_save($file);
  }
  
  /*
  if ($form_state['values']['watermark'] != 0) {
    $file = file_load($form_state['values']['watermark']);
    $ext = explode('.', $file->filename);
    $file->filename = $form_state['values']['title'].'_watermark'.'.'.$ext[1];
    $file->status = FILE_STATUS_PERMANENT;
    $watermark_filename = $file->filename;
    file_save($file);
  }
  */
  
  $header_fid = db_query(
		"SELECT * from file_managed where filename = :fn;", array(':fn' => $header_filename)
	);
  foreach($header_fid as $hf){
    $hfid = $hf->fid;
  }
  
  if(isset($watermark_filename)){
    $watermark_fid = db_query(
    	"SELECT * from file_managed where filename = :fn;", array(':fn' => $watermark_filename)
    );
    foreach($watermark_fid as $wf){
      $wfid = $wf->fid;
    }
  }
  
  GLOBAL $user;
  db_insert($certificate_table)
		->fields (array(
		  'title' => $form_state['values']['title'],
			'fid_header' => isset($hfid)?$hfid:NULL,
      'body' => $form_state['values']['body']['value'],
      'fid_watermark' => isset($wfid)?$wfid:NULL,
      'footer' => $form_state['values']['footer_text']['value'],
      'created_by' => $user->uid,
      'last_modified_by' => NULL,
      'created_time' => strtotime(date('d-m-Y')),
      'modified_time' => NULL,
      'rp_label1' => $form_state['values'][1][1]['c2'],
      'rp_string1' => $form_state['values'][1][1]['c3'],
      'rp_label2' => $form_state['values'][2][2]['c2'],
      'rp_string2' => $form_state['values'][2][2]['c3'],
      'rp_label3' => $form_state['values'][3][3]['c2'],
      'rp_string3' => $form_state['values'][3][3]['c3'],
      'rp_label4' => $form_state['values'][4][4]['c2'],
      'rp_string4' => $form_state['values'][4][4]['c3'],
      'rp_label5' => $form_state['values'][5][5]['c2'],
      'rp_string5'  => $form_state['values'][5][5]['c3'],
		)
	)	
	->execute();
  
  $certificates = db_query(
		"SELECT * from $certificate_table where title = :t;", array(':t' => $form_state['values']['title'])
	);
  foreach($certificates as $certificate){
    $id = $certificate->cer_id;
  }
  variable_set('cer_id-'.$id,array(1));
  
  $certificates = db_query(
		"SELECT * from $certificate_table where title = :t;", array(':t' => $form_state['values']['title'])
	);
  foreach($certificates as $certificate){
    $id = $certificate->cer_id;
  }
  variable_set('cer_id-'.$id,$form_state['values']['sr_no']);
  
  drupal_set_message('The certificate was created successfully!! You can now generate the certificates for student.');
  drupal_flush_all_caches();
}