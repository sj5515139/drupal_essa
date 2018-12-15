<?php
/**
 *Implements page callback function - edit_certificate
 */
function edit_certificates($form = array(), &$form_state, $cer_id){
  $session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
	$certificates = db_query(
		"SELECT * from $certificate_table where cer_id = :ci;", array(':ci' => $cer_id)
	);
  
	foreach($certificates as $certificate){
    $title = $certificate->title;
    $header_fid = db_query(
  		"SELECT * from file_managed where fid = :fid;", array(':fid' => $certificate->fid_header)
  	);
    foreach($header_fid as $hf){
      $header = $hf->fid;
    }
    $body = $certificate->body;
    $watermark_fid = db_query(
  		"SELECT * from file_managed where fid = :fid;", array(':fid' => $certificate->fid_watermark)
  	);
    foreach($watermark_fid as $wf){
      $watermark = $wf->fid;
    }
    $footer = $certificate->footer;
  }
  
	if(isset($watermark)){
		$form['water_mark_fid'] = array(
		  '#type' => 'value',
		  '#value' => $watermark,
		);	
	}
  
  $form['header_fid'] = array(
    '#type' => 'value',
    '#value' => $header
  );
  
  $form['cer_id'] = array(
    '#type' => 'value',
    '#value' => $cer_id
  );
  
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $title,
  );
  
	$form['header'] = array(
    '#type' => 'managed_file',
    '#name' => 'header',
    '#title' => t('Header'),
    '#size' => 40,
    '#upload_location' => 'public://certificates/header/',
    '#default_value' => isset($header) ? $header : NULL,
		'#description' => 'Max width of the image shall be not more than 800px',
    '#validated' => TRUE,
  );
  
  $form['body'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('Body'),
    '#default_value' => $body,
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
      <p><b><i>NOTE: Please take due care to write the replacement patterns carefully. It is recommended that you copy and paste the patterns to avoid typing errors.</i></b></p>
      <p>WARNING: In case of any spelling mistake, the certificate will not be generated correctly.<p>
      <table>
      <tr>
      <td><b>[student_name]</b> => Student\'s Name</td>
      <td><b>[adm_no]</b> => Admission No.</td>
      <td><b>[today_date]</b> => Today\'s Date</td>
      </tr>
      <tr>
      <td><b>[student_first_name]</b> => Student\'s First Name</td>
      <td><b>[class]</b> => Class</td>
      <td><b>[fph]</b> => Fee Payment History</td>
      </tr>
      <tr>
      <td><b>[student_last_name]</b> => Student\'s Last Name</td>
      <td><b>[section]</b> => Section</td>
      <td><b>[tph]</b> => Total Fee Paid</td>
      </tr>
      <tr>
      <td><b>[father_name]</b> => Father\'s Name</td>
      <td><b>[class_section]</b> => Class - Section</td>
      <td><b>[fdd]</b> => Fee Due Detail</td>
      </tr>
      <tr>
      <td><b>[father_first_name]</b> => Father\'s First Name</td>
      <td><b>[doa]</b> => Date of Admission</td>
      <td><b>[tfd]</b> => Total Fee Due</td>
      </tr>
      <tr>
      <td><b>[father_last_name]</b> => Father\'s last Name</td>
      <td><b>[dob]</b> => Date of Birth</td>
      <td><b>[board]</b> => School\'s board</td>
      </tr>
      <tr>
      <td><b>[mother_name]</b> => Mother\'s Name</td>
      <td><b>[session]</b> => Session</td>
      <td><b>[acsm]</b> => Academic Year Start month</td>
      </tr>
      <tr>
      <td><b>[mother_first_name]</b> => Mother\'s First Name</td>
      <td><b>[scn]</b> => School Code No</td>
      <td><b>[acem]</b> => Academic Year End month</td>
      </tr>
      <tr>
      <td><b>[mother_last_name]</b> => Mother\'s last Name</td>
      <td><b>[affiliation_no]</b> => Affiliation No.</td>
      <td><b>[school_name]</b> => Name of School</td>
      </tr>
      </table>
      <p>PS: The values will only be replaced if they are provided prior to certificate generation. In case of any discrepancies, first check if the data has been provided correctly. If the problem persists please feel free to get on touch with us.</p>
    '
  );
	
	$form['watermark'] = array(
    '#type' => 'managed_file',
    '#name' => 'watermark',
    '#title' => t('Water Mark'),
    '#size' => 40,
    '#upload_location' => 'public://certificates/header/',
    '#default_value' => isset($watermark)?$watermark:NULL,
		'#description' => 'Max width of the image shall be not more than 800px',
    '#validated' => TRUE,
  );
  
  $form['footer_text'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('Footer Text'),
    '#default_value' => $footer,
  );
  
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
	$default = array();
	$certificates = db_query(
		"SELECT * from $certificate_table where cer_id = :ci;", array(':ci' => $cer_id)
	);
  foreach($certificates as $certificate){
		$default[1][1]['label'] = $certificate->rp_label1;
		$default[2][2]['label'] = $certificate->rp_label2;
		$default[3][3]['label'] = $certificate->rp_label3;
		$default[4][4]['label'] = $certificate->rp_label4;
		$default[5][5]['label'] = $certificate->rp_label5;
		$default[1][1]['string'] = $certificate->rp_string1;
		$default[2][2]['string'] = $certificate->rp_string2;
		$default[3][3]['string'] = $certificate->rp_string3;
		$default[4][4]['string'] = $certificate->rp_string4;
		$default[5][5]['string'] = $certificate->rp_string5;
	}
    
	
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
					'#default_value' => isset($default[$i][$i]['label'])?$default[$i][$i]['label']:NULL,
				),
				'c3' =>array(
				  '#type' => 'textfield',
          '#size' => 20,
					'#default_value' => isset($default[$i][$i]['string'])?$default[$i][$i]['string']:NULL,
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
	
  return $form;
}

function edit_certificate_submit($form, &$form_state){
  GLOBAL $user;
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  
  if ($form_state['values']['header']['fid'] != $form_state['values']['water_mark_fid'] && $form_state['values']['header']['fid'] != 0) {
    $file = file_load($form_state['values']['header']['fid']);
    $ext = explode('.', $file->filename);
    $file->filename = $form_state['values']['title'].'.'.$ext[1];
		$file->status = FILE_STATUS_PERMANENT;
		file_save($file);
		$header_filename = $file->filename;
    
    $header_fid = db_query(
    	"SELECT * from file_managed where filename = :fn;", array(':fn' => $header_filename)
    );
    foreach($header_fid as $hf){
      $hfid = $hf->fid;
    }
    db_merge($certificate_table)
      ->key(array('cer_id' => $form_state['values']['cer_id']))
    	->fields (array(
    	  'fid_header' => $hfid,
    	)
    )	
    ->execute();
  }
  
  if ($form_state['values']['watermark'] != $form_state['values']['water_mark_fid'] && $form_state['values']['watermark']['fid'] != 0) {
    $file = file_load($form_state['values']['watermark']['fid']);
    $ext = explode('.', $file->filename);
    $file->filename = $form_state['values']['title'].'_watermark'.'.'.$ext[1];
		$file->status = FILE_STATUS_PERMANENT;
    file_save($file);
		
		$watermark_filename = $file->filename;
    $watermark_fid = db_query(
    	"SELECT * from file_managed where filename = :fn;", array(':fn' => $watermark_filename)
    );
    foreach($watermark_fid as $wf){
      $wfid = $wf->fid;
    }
    db_merge($certificate_table)
      ->key(array('cer_id' => $form_state['values']['cer_id']))
    	->fields (array(
    	  'fid_watermark' => $wfid,
    	)
    )	
    ->execute();
  }
  
  db_merge($certificate_table)
    ->key(array('cer_id' => $form_state['values']['cer_id']))
		->fields (array(
		  'title' => $form_state['values']['title'],
			'body' => $form_state['values']['body']['value'],
      'footer' => $form_state['values']['footer_text']['value'],
      //'created_by' => $user->uid,
      'last_modified_by' => $user->uid,
      //'created_time' => strtotime(date('d-m-Y')),
      'modified_time' => strtotime(date('d-m-Y')),
			'rp_label1' => isset($form_state['values'][1][1]['c2'])?$form_state['values'][1][1]['c2']:NULL,
      'rp_string1' => isset($form_state['values'][1][1]['c3'])?$form_state['values'][1][1]['c3']:NULL,
      'rp_label2' => isset($form_state['values'][2][2]['c2'])?$form_state['values'][2][2]['c2']:NULL,
      'rp_string2' => isset($form_state['values'][2][2]['c3'])?$form_state['values'][2][2]['c3']:NULL,
      'rp_label3' => isset($form_state['values'][3][3]['c2'])?$form_state['values'][3][3]['c2']:NULL,
      'rp_string3' => isset($form_state['values'][3][3]['c3'])?$form_state['values'][3][3]['c3']:NULL,
      'rp_label4' => isset($form_state['values'][4][4]['c2'])?$form_state['values'][4][4]['c2']:NULL,
      'rp_string4' => isset($form_state['values'][4][4]['c3'])?$form_state['values'][4][4]['c3']:NULL,
      'rp_label5' => isset($form_state['values'][5][5]['c2'])?$form_state['values'][5][5]['c2']:NULL,
      'rp_string5'  => isset($form_state['values'][5][5]['c3'])?$form_state['values'][5][5]['c3']:NULL,
		)
	)	
	->execute();
}