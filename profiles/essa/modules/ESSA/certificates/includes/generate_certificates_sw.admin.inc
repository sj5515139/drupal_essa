<?php
/**
 *Implements page callback - generate_certificates_sw
 */
function generate_certificates_sw($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  $options = array();
	$huri = NULL;
	$particulars = array();
	$fees_due_detail = array();
	global $base_url;
	$certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array(':title' => 'Transfer Certificate')
	);
	foreach($certificates as $certificate){
		$header_fid = db_query(
    	"SELECT * from file_managed where fid = :fid;", array(':fid' => $certificate->fid_header)
    );
		
		foreach($header_fid as $hf){
			$huri = $hf->uri;
		}
		//$content .= '<div><img src = "'.variable_get('file_public_path', conf_path() . '/files').$huri.'"></div>';	
	}
	if($huri != NULL){
		$huri = str_ireplace('public://', '/', $huri);
	}
	
  
  $certificates = db_query(
		"SELECT * from $certificate_table;"
	);
	foreach($certificates as $certificate){
    $options[] = $certificate->title;
  }
	
	$form['fs'] = array(
		'#type' => 'container',
	);
	
  $form['fs']['template'] = array(
    '#type' => 'select',
    '#title' => 'Select a Template',
    '#options' => drupal_map_assoc($options),
    '#required' => TRUE,
		'#ajax' => array(
      'event' => 'change',
      'callback' => 'get_page_settings',
      'wrapper' => 'page_settings',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
	
	$form['fs']['condition'] = array(
		'#type' => 'select',
		'#title' => 'Condition(if any)',
		'#options' => array('--Select--', 'If fee is due', 'If no fee is due'),
	);
  
  $form['fs']['student'] = array(
    '#type' => 'textfield',
    '#title' => 'Select a Student',
    '#autocomplete_path' => 'adm_no/autocomplete',
		'#required' => TRUE,
		'#size' => 15,
  );
  
	$form['fs']['note'] = array(
    '#type' => 'markup',
    '#markup' => '<h5><b>NOTE: </b>In case you have set custom replacement patterns, please provide data before you generate the certificates.</h5>',
  );
	
	if(!empty($form_state['values']['template'])){
		$session_id = (string)variable_get('essa_sid');
		$certificate_table = 'essa_'.$session_id.'_certificate_templates';
		$certificates = db_query(
			"SELECT * from $certificate_table where title = :title;", array(':title' => $form_state['values']['template'])
		);
		foreach($certificates as $certificate){
			$cer_id = $certificate -> cer_id;
		}
		
		$form['ps'] = array(
			'#type' => 'fieldset',
			'#title' => 'Page Settings',
			'#prefix' => '<div id = "page_settings">',
			'#suffix' => '</div>'
		);
		
		$page_format_def = variable_get('cer_setting_'.$cer_id.'_page_format');
		$form['ps']['page_format'] = array(
			'#type' => 'select',
			'#title' => 'Page Format',
			'#options' => array('1 Column', '2 Column', '3 Column'),
			'#value' => isset($page_format_def)? $page_format_def: 0,
		);
		
		$page_size_def = variable_get('cer_setting_'.$cer_id.'_page_size');
		$form['ps']['page_size'] = array(
			'#type' => 'select',
			'#title' => 'Page Size',
			'#options' => drupal_map_assoc(array('A4', 'Letter', 'Legal', 'Custom')),
			'#value' => isset($page_size_def)? $page_size_def: 'A4',
			'#ajax' => array(
			  'event' => 'change',
			  'callback' => 'get_custom_page_size',
			  'wrapper' => 'page_size',
			  'method' => 'replace',
			  'effect' => 'fade',
			),
		);
		
		if($page_size_def == 'Custom'){
			$form['ps']['ct'] = array(
				'#type' => 'fieldset',
				'#prefix' => '<div id = "page_size">',
				'#suffix' => '</div>',
			);
			
			$width_def = variable_get('cer_setting_'.$cer_id.'_width');
			$form['ps']['ct']['cwidth'] = array(
				'#type' => 'textfield',
				'#title' => 'Width(in inches)',
				'#size' => 3,
				'#value' => isset($width_def)? $width_def: NULL,
			);
			
			$height_def = variable_get('cer_setting_'.$cer_id.'_height');
			$form['ps']['ct']['cheight'] = array(
				'#type' => 'textfield',
				'#title' => 'Height(in inches)',
				'#size' => 3,
				'#value' => isset($height_def)? $height_def: NULL,
			);
		}
		if($form_state['input']['page_size'] == 'Custom'){
			$form['ps']['t'] = array(
				'#type' => 'fieldset',
				'#prefix' => '<div id = "page_size">',
				'#suffix' => '</div>',
			);
			
			$width_def = variable_get('cer_setting_'.$cer_id.'_width');
			$form['ps']['t']['width'] = array(
				'#type' => 'textfield',
				'#title' => 'Width(in inches)',
				'#size' => 3,
				'#value' => isset($width_def)? $width_def: NULL,
			);
			
			$height_def = variable_get('cer_setting_'.$cer_id.'_height');
			$form['ps']['t']['height'] = array(
				'#type' => 'textfield',
				'#title' => 'Height(in inches)',
				'#size' => 3,
				'#value' => isset($height_def)? $height_def: NULL,
			);
		}else{
			$form['ps']['t'] = array(
				'#type' => 'container',
				'#prefix' => '<div id = "page_size">',
				'#suffix' => '</div>',
			);
		}
		
		$page_orientation_def = variable_get('cer_setting_'.$cer_id.'_page_orientation');
		$form['ps']['page_orientation'] = array(
			'#type' => 'select',
			'#title' => 'Page Orientation',
			'#options' => drupal_map_assoc(array('Portrait', 'Landscape')),
			'#value' => !is_null($page_orientation_def)? $page_orientation_def: 'Portrait',
		);
		
		$form['ps']['note'] = array(
			'#type' => 'markup',
			'#markup' => '<h3>All margins are in inches</h3>',
		);
		
		for($i = 0; $i < 10; $i++){
			for($j = 0; $j < 10; $j++){
				$val[] = $i.'.'.$j;
			}	
		}
		
		$page_margin_top_def = variable_get('cer_setting_'.$cer_id.'_page_margin_top');
		$form['ps']['page_margin_top'] = array(
			'#type' => 'select',
			'#title' => 'Page Margin(Top)',
			'#options' => drupal_map_assoc($val),
			'#value' => !is_null($page_margin_top_def)? $page_margin_top_def: '0.1',
		);
		
		$page_margin_right_def = variable_get('cer_setting_'.$cer_id.'_page_margin_right');
		$form['ps']['page_margin_right'] = array(
			'#type' => 'select',
			'#title' => 'Page Margin(Right)',
			'#options' => drupal_map_assoc($val),
			'#value' => !is_null($page_margin_right_def)? $page_margin_right_def: '0.1',
		);
		
		$page_margin_bottom_def = variable_get('cer_setting_'.$cer_id.'_page_margin_bottom');
		$form['ps']['page_margin_bottom'] = array(
			'#type' => 'select',
			'#title' => 'Page Margin(Bottom)',
			'#options' => drupal_map_assoc($val),
			'#value' => !is_null($page_margin_bottom_def)? $page_margin_bottom_def: '0.1',
		);
		
		$page_margin_left_def = variable_get('cer_setting_'.$cer_id.'_page_margin_left');
		$form['ps']['page_margin_left'] = array(
			'#type' => 'select',
			'#title' => 'Page Margin(Left)',
			'#options' => drupal_map_assoc($val),
			'#value' => !is_null($page_margin_left_def)? $page_margin_left_def: '0.1',
		);
		
		$save_settings_def = variable_get('cer_setting_'.$cer_id.'_save_settings');
		if($save_settings_def == 1){
			$form['ps']['save_settings'] = array(
				'#type' => 'checkbox',
				'#title' => 'Save these settings.',
				'#description' => 'This will save the above settings for this certificate. Which you can use in generating future certificates.',
				'#value' => TRUE,
			);	
		}else{
			$form['ps']['save_settings'] = array(
				'#type' => 'checkbox',
				'#title' => 'Save these settings.',
				'#description' => 'This will save the above settings for this certificate. Which you can use in generating future certificates.',
				'#value' => FALSE,
			);	
		}
	}else{
		$form['ps'] = array(
			'#type' => 'fieldset',
			'#title' => 'Page Settings',
			'#prefix' => '<div id = "page_settings">',
			'#suffix' => '</div>',
			'#description' => 'Select a certificate template to edit page settings.'
		);
	}
	
	$form['fs']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Download'),
  );
	
	$form['fs']['rp'] = array(
		'#type' => 'submit',
		'#value' => 'Set/Edit Replacement Values',
		'#submit' => array('set_rp_submit'),
	);
	
	return $form;
}

/**
 *Implements ajax callback function - get_page_settings
 */
function get_page_settings(&$form, &$form_state){
	return $form['ps'];
}

/**
 *Implements ajax callback function - get_page_settings
 */
function get_custom_page_size(&$form, &$form_state){
	return $form['ps']['t'];
}

/**
 *Implements support function to set replacement values.
 */
function set_rp_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
	
	$certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array('title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$cer_id = $certificate->cer_id;	
	}
	global $user;
	variable_set('certificate_template-'.$user->uid, $cer_id);
	variable_set('certificate_adm_no-'.$user->uid, $form_state['values']['student']);
	global $base_url;
	$url = $base_url.'/admin/certificates/generate_certificates/student-wise/#overlay=set_rp';
	$custom_url =  urldecode($url);
	$form_state['redirect'] = $custom_url;
}

/**
 *Implements submit function
 */
function generate_certificates_sw_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  $student_table = 'essa_'.$session_id.'_master_student_table';
	$session_id = (string)variable_get('essa_sid');
	$fee_frequency_table = 'essa_'.$session_id.'_fees_frequency';
	$fee_due_table = 'essa_'.$session_id.'_fees_student_due';
	$fee_structure_table = 'essa_'.$session_id.'_fees_structure';
	$fee_student_payment = 'essa_'.$session_id.'_fees_student_payment';
  require_once("profiles/essa/modules/dependencies/essa/print/lib/dompdf/dompdf_config.inc.php");
	//dsm($form_state);
	
	$certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array(':title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$cer_id = $certificate -> cer_id;
	}
	
	if(isset($form_state['input']['save_settings']) == 1){
		variable_set('cer_setting_'.$cer_id.'_page_format', $form_state['input']['page_format']);
		variable_set('cer_setting_'.$cer_id.'_page_size', $form_state['input']['page_size']);
		if(isset($form_state['input']['cwidth'])){variable_set('cer_setting_'.$cer_id.'_width', $form_state['input']['cwidth']);}
		if(isset($form_state['input']['cheight'])){variable_set('cer_setting_'.$cer_id.'_height', $form_state['input']['cheight']);}
		if(isset($form_state['input']['width'])){variable_set('cer_setting_'.$cer_id.'_width', $form_state['input']['width']);}
		if(isset($form_state['input']['height'])){variable_set('cer_setting_'.$cer_id.'_height', $form_state['input']['height']);}
		variable_set('cer_setting_'.$cer_id.'_page_orientation', $form_state['input']['page_orientation']);
		variable_set('cer_setting_'.$cer_id.'_page_margin_top', $form_state['input']['page_margin_top']);
		variable_set('cer_setting_'.$cer_id.'_page_margin_right', $form_state['input']['page_margin_right']);
		variable_set('cer_setting_'.$cer_id.'_page_margin_bottom', $form_state['input']['page_margin_bottom']);
		variable_set('cer_setting_'.$cer_id.'_page_margin_left', $form_state['input']['page_margin_left']);
		variable_set('cer_setting_'.$cer_id.'_save_settings', $form_state['input']['save_settings']);
	}else{
		variable_del('cer_setting_'.$cer_id.'_page_format');
		variable_del('cer_setting_'.$cer_id.'_page_size');
		variable_del('cer_setting_'.$cer_id.'_page_orientation');
		variable_del('cer_setting_'.$cer_id.'_page_margin_top');
		variable_del('cer_setting_'.$cer_id.'_page_margin_right');
		variable_del('cer_setting_'.$cer_id.'_page_margin_bottom');
		variable_del('cer_setting_'.$cer_id.'_page_margin_left');
		variable_del('cer_setting_'.$cer_id.'_save_settings');
	}
	
	if($form_state['input']['condition'] == '1' || $form_state['input']['condition'] == '2'){
		$total_due = 0;
		
		$today = strtotime(date('d-m-Y'));
		$fees_structure = db_query(
			"SELECT * from $fee_structure_table;"
		);
		foreach($fees_structure as $fs){
			$results = db_select($fee_frequency_table, 'n')
				->fields('n')
				->condition('freq_id', $fs->freq_id, '=')
				->execute();
			$freq = $results->fetchAssoc();
			foreach($freq as $key => $value){
				if($value != NULL && $key != 'freq_id' && $key != 'freq_name' && $value < $today){
					$fees_due = db_query(
						"SELECT * from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $form_state['values']['student'])
					);
					foreach($fees_due as $fd){
						$total_due = $total_due + $fd->$key;
					}
				}
			}
		}
		
		//dsm($total_due);
		if($total_due > 0){
			if($form_state['input']['page_size'] == 'Custom'){
				//dsm('due');
				if(isset($form_state['input']['width']) && isset($form_state['input']['height'])){
					//$page_size = array(0,0, $form_state['values']['width'], $form_state['values']['height']);
					$w = $form_state['input']['width'] * 72;
					$h = $form_state['input']['height'] * 72;
					$page_size = array(0,0, $w, $h);
				}else{
					//$page_size = array(0,0, $form_state['values']['cwidth'], $form_state['values']['cheight']);
					$w = $form_state['input']['cwidth'] * 72;
					$h = $form_state['input']['cheight'] * 72;
					$page_size = array(0,0, $w, $h);
				}
			}else{
				$page_size = $form_state['input']['page_size'];
			}
			
			if($form_state['input']['page_orientation'] = 'Portrait'){
				$po = 'portrait';
			}else{
				$po = 'landscape';
			}
			
			$html = get_content($form, $form_state);
			$dompdf = new DOMPDF;
			$dompdf->load_html($html);
			$dompdf->set_paper($page_size, $po);
			$dompdf->render();
			// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
			$dompdf->stream($form_state['input']['template'].'_'.$form_state['input']['student'].".pdf", array('compress' => FALSE));
		}else{
			if($form_state['input']['page_size'] == 'Custom'){
				if(isset($form_state['input']['width']) && isset($form_state['input']['height'])){
					//$page_size = array(0,0, $form_state['values']['width'], $form_state['values']['height']);
					$w = $form_state['input']['width'] * 72;
					$h = $form_state['input']['height'] * 72;
					$page_size = array(0,0, $w, $h);
				}else{
					//$page_size = array(0,0, $form_state['values']['cwidth'], $form_state['values']['cheight']);
					$w = $form_state['input']['cwidth'] * 72;
					$h = $form_state['input']['cheight'] * 72;
					$page_size = array(0,0, $w, $h);
				}
			}else{
				$page_size = $form_state['input']['page_size'];
			}
			
			if($form_state['input']['page_orientation'] = 'Portrait'){
				$po = 'portrait';
			}else{
				$po = 'landscape';
			}
			
			$html = get_content($form, $form_state);
			$dompdf = new DOMPDF;
			$dompdf->load_html($html);
			$dompdf->set_paper($page_size, $po);
			$dompdf->render();
			// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
			//$dompdf->stream($form_state['values']['template'].'_'.$form_state['values']['student'].".pdf", array('compress' => FALSE));
		}
	}else{
		if($form_state['input']['page_size'] == 'Custom'){
			if(isset($form_state['input']['width']) && isset($form_state['input']['height'])){
				$w = $form_state['input']['width'] * 72;
				$h = $form_state['input']['height'] * 72;
				$page_size = array(0,0, $w, $h);	
			}else{
				$w = $form_state['input']['cwidth'] * 72;
				$h = $form_state['input']['cheight'] * 72;
				$page_size = array(0,0, $w, $h);	
			}
		}else{
			$page_size = $form_state['input']['page_size'];
		}
			
		if($form_state['input']['page_orientation'] == 'Portrait'){
			$po = 'portrait';
		}else{
			$po = 'landscape';
		}
		//dsm($form_state);
		//dsm('select');
		$html = get_content($form, $form_state);
		$dompdf = new DOMPDF; 
		$dompdf->load_html($html);
		$dompdf->set_paper($page_size, $po);
		$dompdf->render();
		// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
		$dompdf->stream($form_state['values']['template'].'_'.$form_state['values']['student'].".pdf", array('compress' => FALSE));
	}
	drupal_exit();
}

/**
 *Implements function to fetch html for pdf
 */
function get_content($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  
	$certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array(':title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$watermark_fid = db_query(
    	"SELECT * from file_managed where fid = :fid;", array(':fid' => $certificate->fid_watermark)
    );
    foreach($watermark_fid as $wf){
      $wuri = $wf->uri;
    }
  }
	
	if(isset($wuri) != NULL){
		$wuri = str_ireplace('public://', '/', $wuri);
	}
	if(isset($wuri)){
		$watermark_uri = variable_get('file_public_path', conf_path() . '/files').$wuri;
	}
	$w = (isset($watermark_uri) != NULL)?$watermark_uri:NULL;
	if($form_state['input']['page_format'] == '0' && $form_state['input']['page_size'] == 'A4'){
		if($form_state['input']['page_orientation'] == 'Portrait'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 8.3 - ((float)$right + (float)$left);
		}else{
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 11.7 - ((float)$top + (float)$bottom);
		}
		
		$content = '<html>';
		$content .= '<head><style>
			table{
				table-layout: fixed;
				width: '.$width.'in;
			}
			
			.fee-due-table{
				border: 0px solid black;
				width:100%;
			}
			
			th{
				background: 	#708090;
				color: WHITE;
			}
			
			.fee-due-table td{
				padding: 7px;
				text-align: center;
			}
			
			td{
				padding: 0.01in;
			}
			
			img{
			  width:100%;
			}
					
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
				page-break-after: always;
			}
			
			body {
				background: url('.$w.');
		    background-repeat: no-repeat;
		    background-attachment: fixed;
		    background-position: center; 
			}
			@page { margin: '.$top.'in '.$right.'in '.$bottom.'in '.$left.'in; }
			 
		</style></head>';
		$content .= '<body>';
		$content .= '<table>';
		$content .= '<tr>';
		$content .= '<td>';
		$content .= get_certificate($form, $form_state);
		$content .= '</td>';
		$content .= '</tr>';
		
		$content .= '</table>';
		$content .= '</body>';
		$content .= '</html>';
		
		return $content;
	}elseif($form_state['input']['page_format'] == '1' && $form_state['input']['page_size'] == 'A4'){
		if($form_state['input']['page_orientation'] == 'Portrait'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 8.3 - ((float)$right + (float)$left);
		}else{
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 11.7 - ((float)$top + (float)$bottom);
		}
		
		$content = '<html>';
		$content .= '<head><style>
			table{
				table-layout: fixed;
				width: '.$width.'in;
			}
			
			td{
				padding: 0.01in;
			}
			
			img{
			  width:100%;
			}
					
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
				page-break-after: always;
			}
			
			.content{
				background: url('.$w.');
		    background-repeat: no-repeat;
		    background-attachment: fixed;
		    background-position: center;
				width:50%;
				height:50%;
			}
			
			@page { margin: '.$top.'in '.$right.'in '.$bottom.'in '.$left.'in; }
			 
		</style></head>';
		$content .= '<body>';
		$content .= '<table>';
		$content .= '<tr>';
		$content .= '<td class = "content">';
		$content .= get_certificate($form, $form_state);
		$content .= '</td>';
		
		$content .= '<td>';
		$content .= '</td>';
		
		$content .= '</tr>';
		
		$content .= '</table>';
		$content .= '</body>';
		$content .= '</html>';
		
		return $content;
	}elseif($form_state['input']['page_format'] == '2' && $form_state['input']['page_size'] == 'A4'){
		if($form_state['input']['page_orientation'] == 'Portrait'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 8.3 - ((float)$right + (float)$left);
		}else{
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 11.7 - ((float)$top + (float)$bottom);
		}
		
		$content = '<html>';
		$content .= '<head><style>
		table{
				table-layout: fixed;
				width: '.$width.'in;
				height: auto;
			}
			
			td{
				padding: 0.01in;
			}
			
			img{
			  width:100%;
			}
			
			.content{
				background: url('.$w.');
		    background-repeat: no-repeat;
		    background-attachment: fixed;
		    background-position: center;
				width:50%;
				height:50%;
			}
			
			@page { margin: '.$top.'in '.$right.'in '.$bottom.'in '.$left.'in; }
			 
		</style></head>';
		$content .= '<body>';
		$content .= '<table>';
		$content .= '<tr>';
		$content .= '<td class = "content">';
		$content .= get_certificate($form, $form_state);
		$content .= '</td>';
		
		$content .= '<td class = "content">';
		$content .= '</td>';
		
		$content .= '<td class = "content">';
		$content .= '</td>';
		$content .= '</tr>';
		
		$content .= '</table>';
		$content .= '</body>';
		$content .= '</html>';
		
	}elseif($form_state['input']['page_format'] == '0' && ($form_state['input']['page_size'] == 'Letter' || $form_state['input']['page_size'] == 'Legal')){
		if($form_state['input']['page_orientation'] == 'Portrait' && $form_state['input']['page_size'] == 'Letter'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 8.5 - ((float)$right + (float)$left);
		}elseif($form_state['input']['page_orientation'] != 'Portrait' && $form_state['input']['page_size'] == 'Letter'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 11.0 - ((float)$top + (float)$bottom);
		}elseif($form_state['input']['page_orientation'] == 'Portrait' && $form_state['input']['page_size'] == 'Legal'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 8.5 - ((float)$top + (float)$bottom);
		}elseif($form_state['input']['page_orientation'] != 'Portrait' && $form_state['input']['page_size'] == 'Legal'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 14.0 - ((float)$top + (float)$bottom);
		}
		
		$content = '<html>';
		$content .= '<head><style>
		table{
				table-layout: fixed;
				width: '.$width.'in;
			}
			
			td{
				padding: 0.01in;
			}
			
			img{
			  width:100%;
			}
					
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
				page-break-after: always;
			}
			
			body {
				background: url('.$w.');
		    background-repeat: no-repeat;
		    background-attachment: fixed;
		    background-position: center; 
			}
			
			@page { margin: '.$top.'in '.$right.'in '.$bottom.'in '.$left.'in; }
			 
		</style></head>';
		$content .= '<body>';
		$content .= '<table>';
		$content .= '<tr>';
		$content .= '<td>';
		$content .= get_certificate($form, $form_state);
		$content .= '</td>';
		
		$content .= '</tr>';
		
		$content .= '</table>';
		$content .= '</body>';
		$content .= '</html>';
	}elseif($form_state['input']['page_format'] == '1' && ($form_state['input']['page_size'] == 'Letter' || $form_state['input']['page_size'] == 'Legal')){
		if($form_state['input']['page_orientation'] == 'Portrait' && $form_state['input']['page_size'] == 'Letter'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 8.5 - ((float)$right + (float)$left);
		}elseif($form_state['input']['page_orientation'] != 'Portrait' && $form_state['input']['page_size'] == 'Letter'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 11.0 - ((float)$top + (float)$bottom);
		}elseif($form_state['input']['page_orientation'] == 'Portrait' && $form_state['input']['page_size'] == 'Legal'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 8.5 - ((float)$top + (float)$bottom);
		}elseif($form_state['input']['page_orientation'] != 'Portrait' && $form_state['input']['page_size'] == 'Legal'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 14.0 - ((float)$top + (float)$bottom);
		}
		$content = '<html>';
		$content .= '<head><style>
		table{
				table-layout: fixed;
				width: '.$width.'in;
			}
			
			td{
				padding: 0.01in;
			}
			
			img{
			  width:100%;
			}
					
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
				page-break-after: always;
			}
			
			.content{
				background: url('.$w.');
		    background-repeat: no-repeat;
		    background-attachment: fixed;
		    background-position: center; 
			}
			
			@page { margin: '.$top.'in '.$right.'in '.$bottom.'in '.$left.'in; }
			 
		</style></head>';
		$content .= '<body>';
		$content .= '<table>';
		
		$content .= '<tr>';
		$content .= '<td class = "content">';
		$content .= get_certificate($form, $form_state);
		$content .= '</td>';
		
		$content .= '<td>';
		$content .= '</td>';
		
		$content .= '</tr>';
		
		$content .= '</table>';
		$content .= '</body>';
		$content .= '</html>';
		
	}elseif($form_state['input']['page_format'] == '2' && ($form_state['input']['page_size'] == 'Letter' || $form_state['input']['page_size'] == 'Legal')){
		if($form_state['input']['page_orientation'] == 'Portrait' && $form_state['input']['page_size'] == 'Letter'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 8.5 - ((float)$right + (float)$left);
		}elseif($form_state['input']['page_orientation'] != 'Portrait' && $form_state['input']['page_size'] == 'Letter'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 11.0 - ((float)$top + (float)$bottom);
		}elseif($form_state['input']['page_orientation'] == 'Portrait' && $form_state['input']['page_size'] == 'Legal'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 8.5 - ((float)$top + (float)$bottom);
		}elseif($form_state['input']['page_orientation'] != 'Portrait' && $form_state['input']['page_size'] == 'Legal'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 14.0 - ((float)$top + (float)$bottom);
		}
		
		$content = '<html>';
		$content .= '<head><style>
		table{
				table-layout: fixed;
				width: '.$width.'in;
			}
			
			td{
				padding: 0.01in;
			}
			
			img{
			  width:100%;
			}
					
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
				page-break-after: always;
			}
			
			.content{
				background: url('.$w.');
		    background-repeat: no-repeat;
		    background-attachment: fixed;
		    background-position: center; 
			}
			
			@page { margin: '.$top.'in '.$right.'in '.$bottom.'in '.$left.'in; }
			
		</style></head>';
		$content .= '<body>';
		$content .= '<table>';
		$content .= '<tr>';
		$content .= '<td class = "content">';
		$content .= get_certificate($form, $form_state);
		$content .= '</td>';
		
		$content .= '<td>';
		$content .= '</td>';
		
		$content .= '<td>';
		$content .= '</td>';
		$content .= '</tr>';
		
		$content .= '</table>';
		$content .= '</body>';
		$content .= '</html>';
		
	}elseif($form_state['input']['page_format'] == '0' && $form_state['input']['page_size'] == 'Custom'){
		if($form_state['input']['page_orientation'] == 'Portrait'){
			if(isset($form_state['input']['cwidth'])){$cerw = $form_state['input']['cwidth'];}
			if(isset($form_state['input']['width'])){$cerw = $form_state['input']['width'];}
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = $cerw - ((float)$right + (float)$left);
		}else{
			if(isset($form_state['input']['cheight'])){$cerh = $form_state['input']['cheight'];}
			if(isset($form_state['input']['height'])){$cerh = $form_state['input']['height'];}
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = $cerh - ((float)$top + (float)$bottom);
		}
		
		$content = '<html>';
		$content .= '<head><style>
		table{
				table-layout: fixed;
				width: '.$width.'in;
			}
			
			td{
				padding: 0.01in;
			}
			
			img{
			  width:100%;
			}
					
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
				page-break-after: always;
			}
			
			body {
				background: url('.$w.');
		    background-repeat: no-repeat;
		    background-attachment: fixed;
		    background-position: center; 
			}
			
			@page { margin: '.$top.'in '.$right.'in '.$bottom.'in '.$left.'in; }
			 
		</style></head>';
		$content .= '<body>';
		$content .= '<table>';
		$content .= '<tr>';
		$content .= '<td>';
		$content .= get_certificate($form, $form_state);
		$content .= '</td>';
		
		$content .= '</tr>';
		
		$content .= '</table>';
		$content .= '</body>';
		$content .= '</html>';
	}elseif($form_state['input']['page_format'] == '1' && $form_state['input']['page_size'] == 'Custom'){
		if($form_state['input']['page_orientation'] == 'Portrait'){
			if(isset($form_state['input']['cwidth'])){$cerw = $form_state['input']['cwidth'];}
			if(isset($form_state['input']['width'])){$cerw = $form_state['input']['width'];}
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = $cerw - ((float)$right + (float)$left);
		}else{
			if(isset($form_state['input']['cheight'])){$cerh = $form_state['input']['cheight'];}
			if(isset($form_state['input']['height'])){$cerh = $form_state['input']['height'];}
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = $cerh - ((float)$top + (float)$bottom);
		}
		
		$content = '<html>';
		$content .= '<head><style>
		table{
				table-layout: fixed;
				width: '.$width.'in;
			}
			
			td{
				padding: 0.01in;
			}
			
			img{
			  width:100%;
			}
					
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
				page-break-after: always;
			}
			
			.content{
				background: url('.$w.');
		    background-repeat: no-repeat;
		    background-attachment: fixed;
		    background-position: center;
			}
			
			@page { margin: '.$top.'in '.$right.'in '.$bottom.'in '.$left.'in; }
		</style></head>';
		$content .= '<body>';
		$content .= '<table>';
		$content .= '<tr>';
		$content .= '<td class = "content">';
		$content .= get_certificate($form, $form_state);
		$content .= '</td>';
		
		$content .= '<td>';
		$content .= '</td>';
		
		$content .= '</tr>';
		
		$content .= '</table>';
		$content .= '</body>';
		$content .= '</html>';
		
	}elseif($form_state['input']['page_format'] == '2' && $form_state['input']['page_size'] == 'Custom'){
		if($form_state['input']['page_orientation'] == 'Portrait'){
			if(isset($form_state['input']['cwidth'])){$cerw = $form_state['input']['cwidth'];}
			if(isset($form_state['input']['width'])){$cerw = $form_state['input']['width'];}
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = $cerw - ((float)$right + (float)$left);
		}else{
			if(isset($form_state['input']['cheight'])){$cerh = $form_state['input']['cheight'];}
			if(isset($form_state['input']['height'])){$cerh = $form_state['input']['height'];}
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = $cerh - ((float)$top + (float)$bottom);
		}
		
		$content = '<html>';
		$content .= '<head><style>
		table{
				table-layout: fixed;
				width: '.$width.'in;
			}
			
			td{
				padding: 0.01in;
			}
			
			img{
			  width:100%;
			}
					
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
				page-break-after: always;
			}
			
			.content{
				background: url('.$w.');
		    background-repeat: no-repeat;
		    background-attachment: fixed;
		    background-position: center; 
			}
			
			@page { margin: '.$top.'in '.$right.'in '.$bottom.'in '.$left.'in; }
			
		</style></head>';
		$content .= '<body>';
		$content .= '<table>';
		$content .= '<tr>';
		$content .= '<td class = "content">';
		$content .= get_certificate($form, $form_state);
		$content .= '</td>';
		
		$content .= '<td>';
		$content .= '</td>';
		
		$content .= '<td>';
		$content .= '</td>';
		
		$content .= '</tr>';
		
		$content .= '</table>';
		$content .= '</body>';
		$content .= '</html>';
		
	}
	return $content;
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  $student_table = 'essa_'.$session_id.'_master_student_table';
	$session_id = (string)variable_get('essa_sid');
	$fee_frequency_table = 'essa_'.$session_id.'_fees_frequency';
	$fee_due_table = 'essa_'.$session_id.'_fees_student_due';
	$fee_structure_table = 'essa_'.$session_id.'_fees_structure';
	$fee_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$options = array();
	return $content;
}

function get_certificate($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  $student_table = 'essa_'.$session_id.'_master_student_table';
	$session_id = (string)variable_get('essa_sid');
	$fee_frequency_table = 'essa_'.$session_id.'_fees_frequency';
	$fee_due_table = 'essa_'.$session_id.'_fees_student_due';
	$fee_structure_table = 'essa_'.$session_id.'_fees_structure';
	$fee_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$fee_history_table = 'essa_'.$session_id.'_fees_payment_history';
  $options = array();
  global $base_url;
	$content = '';
	//dsm($certificate_table);
	//dsm($form_state['values']['template']);
	
	$certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array(':title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$header_fid = db_query(
    	"SELECT * from file_managed where fid = :fid;", array(':fid' => $certificate->fid_header)
    );
		
		foreach($header_fid as $hf){
			$huri = $hf->uri;
		}
		
		if(isset($huri) != NULL){
			$huri = str_ireplace('public://', '/', $huri);
		}
		
    $watermark_fid = db_query(
    	"SELECT * from file_managed where fid = :fid;", array(':fid' => $certificate->fid_watermark)
    );
    foreach($watermark_fid as $wf){
      $wuri = $wf->uri;
    }
		
		$cer_id = $certificate->cer_id;
		$sr_no = variable_get('cer_id-'.$cer_id);
  }
	
	if(isset($wuri) != NULL){
		$wuri = str_ireplace('public://', '/', $wuri);
	}
	
  $certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array(':title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		if(isset($huri) != NULL){
			$content = '<div><img src = "'.variable_get('file_public_path', conf_path() . '/files').$huri.'"></div>';
			//$content = '<h1>'.$base_url.'/'.variable_get('file_public_path', conf_path() . '/files').$huri.'</h1>';
			//dpm($content);
		}
		
		$student_detail = db_query(
			"SELECT * from $student_table where adm_no = :an;", array(':an' => $form_state['values']['student'])
		);
		foreach($student_detail as $sd){
			$body = $certificate->body;
			$body = str_ireplace('[sr_no]', $sr_no, $body);
			$body = str_ireplace('[student_name]', $sd->student_name, $body);
			$body = str_ireplace('[student_first_name]', $sd->first_name, $body);
			$body = str_ireplace('[student_last_name]', $sd->last_name, $body);
			$body = str_ireplace('[father_name]', $sd->father_name, $body);
			$body = str_ireplace('[father_first_name]', $sd->f_first_name, $body);
			$body = str_ireplace('[father_last_name]', $sd->f_last_name, $body);
			$body = str_ireplace('[mother_name]', $sd->mother_name, $body);
			$body = str_ireplace('[mother_first_name]', $sd->m_first_name, $body);
			$body = str_ireplace('[mother_last_name]', $sd->m_last_name, $body);
			$body = str_ireplace('[adm_no]', $form_state['values']['student'], $body);
			$body = str_ireplace('[class]', $sd->class, $body);
			$body = str_ireplace('[roll_no]', $sd->roll_no, $body);
			$body = str_ireplace('[section]', $sd->section, $body);
			$body = str_ireplace('[class_section]', $sd->class.' - '.$sd->section, $body);
			$body = str_ireplace('[doa]', $sd->doa, $body);
			$body = str_ireplace('[dob]', $sd->dob, $body);
			$total_due = 0;
			$total_paid = 0;
			$today = strtotime(date('d-m-Y'));
			$fees_structure = db_query(
				"SELECT * from $fee_structure_table;"
			);
			foreach($fees_structure as $fs){
				$results = db_select($fee_frequency_table, 'n')
					->fields('n')
					->condition('freq_id', $fs->freq_id, '=')
					->execute();
				$freq = $results->fetchAssoc();
				foreach($freq as $key => $value){
					if($value != NULL && $key != 'freq_id' && $key != 'freq_name' && $value < $today){
						$fees_due = db_query(
							"SELECT $key from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $form_state['values']['student'])
						);
						foreach($fees_due as $fd){
							$total_due = $total_due + $fd->$key;
						}
						$fees_paid = db_query(
							"SELECT * from $fee_student_payment where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $form_state['values']['student'])
						);
						foreach($fees_paid as $fp){
							$total_paid = $total_paid + $fp->amount;
						}
					}
				}
			}
		}
		$body = str_ireplace('[session]', str_replace('_', '-', $session_id), $body);
		$body = str_ireplace('[tfd]', $total_due, $body);
		$body = str_ireplace('[tph]', $total_paid, $body);
		
		$total = 0;
		$fees_structure = db_query(
			"SELECT * from $fee_structure_table;"
		);
		foreach($fees_structure as $fs){
			$per_fee_due[$fs->fee_id] = 0;
			$results = db_select($fee_frequency_table, 'n')
				->fields('n')
				->condition('freq_id', $fs->freq_id, '=')
				->execute();
			$freq = $results->fetchAssoc();
			foreach($freq as $key => $value){
				if($value != NULL && $key != 'freq_id' && $key != 'freq_name' && $value < $today){
					$fees_due = db_query(
						"SELECT $key from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':an' => $form_state['values']['student'], ':fi' => $fs->fee_id)
					);
					foreach($fees_due as $fd){
						if($fd->$key != 0){
							$fees_detail = db_query(
								"SELECT * from $fee_structure_table where fee_id = :fi;", array(':fi' => $fs->fee_id)
							);
							foreach($fees_detail as $fed){
								$particulars[$fed->fee_id] = $fed->particulars;
							}
							$per_fee_due[$fs->fee_id] = $per_fee_due[$fs->fee_id] + $fd->$key;
						}
					}
				}
			}
		}
		$fd_table = '<table class = "fee-due-table" style = "width:100%;">';
		$fd_table .= '<tr>';
		$fd_table .= '<th style = "background: 	#708090; color: WHITE;">'.'</th>';
		foreach($particulars as $p){
			$fd_table .= '<th style = "background: 	#708090; color: WHITE;">'.$p.'</th>';
		}
		$fd_table .= '</tr>';
		
		$fees_structure = db_query(
			"SELECT * from $fee_structure_table;"
		);
		foreach($fees_structure as $fs){
			$results = db_select($fee_frequency_table, 'n')
				->fields('n')
				->condition('freq_id', $fs->freq_id, '=')
				->execute();
			$freq = $results->fetchAssoc();
			foreach($freq as $key => $value){
				if($value != NULL && $key != 'freq_id' && $key != 'freq_name' && $value < $today){
					$fees_due = db_query(
						"SELECT * from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $form_state['values']['student'])
					);
					foreach($fees_due as $fd){
						if($fd->$key != 0){
							$fees_due_detail[$key][$fd->fee_id] = $fd-> $key;
						}
					}
				}
			}
		}
		foreach($fees_due_detail as $mon => $val){
			$fd_table .= '<tr>';
			$fd_table .= '<td style = "padding: 7px; text-align: center;">'.$mon.'</td>';
			foreach($val as $fee_id => $amt){
				if($amt != 0){
					$fd_table .= '<td style = "padding: 7px; text-align: center;">'.$amt.'</td>';
				}
			}
			$fd_table .= '</tr>';
		}
		
		$fd_table .= '<tr>';
		$fd_table .= '<th style = "background: 	#708090; color: WHITE;">'.'Total'.'</th>';
		foreach($per_fee_due as $pfd){
			if($pfd != 0){
				$fd_table .= '<th style = "background: 	#708090; color: WHITE;">'.$pfd.'</th>';
			}
		}
		$fd_table .= '<tr>';
		$fd_table .= '</table>';
		
		$body = str_ireplace('[fdd]', $fd_table, $body);
		
		$fh_table = '<table class = "fee-due-table" style = "width:100%;">';
		$fh_table .= '<tr>';
		$fh_table .= '<th style = "background: 	#708090; color: WHITE;">Payment Date</th>';
		$fh_table .= '<th style = "background: 	#708090; color: WHITE;">Amount</th>';
		$fh_table .= '</tr>';
		
		$fee_history = db_query("SELECT * FROM {$fee_history_table} WHERE adm_no = :adm;", array(':adm' => $form_state['values']['student']));
		foreach($fee_history as $fh){
			$fh_table .= '<tr>';
			$fh_table .= '<td style = "padding: 7px; text-align: center;">'.date('d-m-Y',$fh->payment_date).'</td>';
			$fh_table .= '<td style = "padding: 7px; text-align: center;">'.$fh->amount.'</td>';
			$fh_table .= '</tr>';
		}
		
		$fh_table .= '</table>';
		$body = str_ireplace('[fph]', $fh_table, $body);
		$basic_info_table = 'essa_'.$session_id.'_basicinfo';
		$basic_info = db_query(
    	"SELECT * from $basic_info_table;"
    );
		foreach($basic_info as $bi){
			$body = str_ireplace('[school_name]', $bi->nameofschool, $body);
			$body = str_ireplace('[scn]', $bi->school_code, $body);
			$body = str_ireplace('[affiliation_no]', $bi->affiliation_no, $body);
			$body = str_ireplace('[board]', $bi->board, $body);
			$acs = strtotime($bi->academicyearstart);
			$body = str_ireplace('[acsm]', date('M-Y', $acs), $body);
			$ace = strtotime($bi->academicyearend);
			$body = str_ireplace('[acem]', date('M-Y', $ace), $body);
		}
		$rp_certificates = db_query(
      "SELECT * from $certificate_table;"
    );
		foreach($rp_certificates as $rpc){
			$certificate_rv_table = 'essa_'.$session_id.'_certificates_replacement_values';
			$replacement_values = db_query(
			  "SELECT * from $certificate_rv_table;"
			);
			foreach($replacement_values as $rv){
				$body = str_ireplace($rpc->rp_string1, $rv->rp_value1, $body);
				$body = str_ireplace($rpc->rp_string2, $rv->rp_value2, $body);
				$body = str_ireplace($rpc->rp_string3, $rv->rp_value3, $body);
				$body = str_ireplace($rpc->rp_string4, $rv->rp_value4, $body);
				$body = str_ireplace($rpc->rp_string5, $rv->rp_value5, $body);
			}	
		}
		
		
		$body = str_ireplace('[today_date]', date('d/m/Y'), $body);
		$content .= $body;
		$content .= '<div id = "cer_footer">'.$certificate->footer.'</div>';
  }
	
	$sr_no++;
	variable_set('cer_id-'.$cer_id,$sr_no);
  return $content;
}