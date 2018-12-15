<?php
/**
 *Implements page callback function generate_certificates
 */
function generate_certificates($form = array(), &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  $options = array();
  
  $certificates = db_query(
		"SELECT * from $certificate_table;"
	);
	foreach($certificates as $certificate){
    $options[] = $certificate->title;
  }
  $form['template'] = array(
    '#type' => 'select',
    '#title' => 'Select a Template',
    '#options' => drupal_map_assoc($options),
    '#required' => TRUE,
  );
	
	$form['condition'] = array(
		'#type' => 'select',
		'#title' => 'Condition(if any)',
		'#options' => array('--Select--', 'If fee is due', 'If no fee is due'),
	);
  
  $form['fs_c'] = array(
    '#type' => 'fieldset',
  );
  
  module_load_include('inc', 'hierarchical_select', 'includes/common');
  $config = cer_hs_setting();
	$form['fs_c']['class'] =  array(
    '#title' => t('Select a Class - '),
    '#type' => 'hierarchical_select',
    '#config' => $config,
  );
  
	$form['fs_s'] = array(
    '#type' => 'fieldset',
		'#prefix' => '<h3><strong>OR</strong></h3>',
  );
	
  $form['fs_s']['student'] = array(
    '#type' => 'textfield',
    '#title' => 'Select a Student',
    '#autocomplete_path' => 'adm_no/autocomplete',
  );
  //http://localhost/essa-sjs-new/certificates/header/header_sjs_1.png
  //http://localhost/essa-sjs-new/sites/default/files/certificates/header/header_sjs_1.png
	/*
	 '#ajax' => array(
      'event' => 'blur',
      'callback' => 'student_rec_ajax',
      'wrapper' => 'rec_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
		),
		*/
  
  $form['note'] = array(
    '#type' => 'markup',
    '#markup' => '<h5><b>NOTE:</b> Please select either a class or admission no. of the student.</h5><h5>In case you have set custom replacement patters, please provide data before you generate the certificates.</h5>',
  );
	
	$form['rp'] = array(
		'#type' => 'submit',
		'#value' => 'Set/Edit Replacement Values',
		'#submit' => array('set_rp_submit'),
	);
	
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Download'),
  );
  return $form;
}

function set_rp_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
	
	$certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array('title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$cer_id = $certificate->cer_id;	
	}
	variable_set('certificate_template', $cer_id);
	
	if($form_state['values']['student'] != NULL){
		variable_set('certificate_class', NULL);
		variable_set('certificate_section', NULL);
		variable_set('certificate_adm_no', $form_state['values']['student']);
		global $base_url;
		$url = $base_url.'/admin/certificates/generate_certificates/#overlay=admin/certificates/set_rp';
		$custom_url =  urldecode($url);
		$form_state['redirect'] = $custom_url;
	}else if(isset($form_state['values']['class'][0])){
		$class = taxonomy_term_load($form_state['values']['class'][0]);
		$section = taxonomy_term_load($form_state['values']['class'][1]);
		
		variable_set('certificate_class', $class->name);
		variable_set('certificate_section', $section->name);
		variable_set('certificate_adm_no', NULL);
		global $base_url;
		$url = $base_url.'/admin/certificates/generate_certificates/#overlay=admin/certificates/set_rp';
		$custom_url =  urldecode($url);
		$form_state['redirect'] = $custom_url;
	}else{
		drupal_set_message('Please provide Class & Section OR Admission no. of the student','error');
	}
}

/**
 *Implements submit function for generate_certificates
 */
function generate_certificates_submit($form, &$form_state){
  //dsm($form_state);
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  $student_table = 'essa_'.$session_id.'_master_student_table';
	$session_id = (string)variable_get('essa_sid');
	$fee_frequency_table = 'essa_'.$session_id.'_fees_frequency';
	$fee_due_table = 'essa_'.$session_id.'_fees_student_due';
	$fee_structure_table = 'essa_'.$session_id.'_fees_structure';
	$fee_student_payment = 'essa_'.$session_id.'_fees_student_payment';
  require_once("profiles/essa/modules/dependencies/essa/print/lib/dompdf/dompdf_config.inc.php");
	if($form_state['values']['student'] != NULL && $form_state['values']['template'] == 'Fee Defaulter'){
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
						"SELECT * from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $form_state['values']['student'])
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
		
		if($total_due != 0){
			$html = get_fd_content($form, $form_state);
			$dompdf = new DOMPDF;
			$dompdf->load_html($html);
			$dompdf->render();
			// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
			$dompdf->stream($form_state['values']['template'].'_'.$form_state['values']['student'].".pdf", array('compress' => FALSE));
		}else{
			drupal_set_message('There is no due for this student.');
		}
	}
	if($form_state['values']['student'] == NULL && $form_state['values']['template'] == 'Fee Defaulter'){
		$class = taxonomy_term_load($form_state['values']['class'][0]);
		$section = taxonomy_term_load($form_state['values']['class'][1]);
    $students = db_query(
    	"SELECT * from $student_table where class = :cl and section = :sec;", array(':cl' => $class->name, ':sec' => $section->name)
    );
    foreach($students as $student){
			$student_detail = db_query(
				"SELECT * from $student_table where adm_no = :an;", array(':an' => $student->adm_no)
			);
			foreach($student_detail as $sd){
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
								"SELECT $key from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $sd->adm_no)
							);
							foreach($fees_due as $fd){
								$total_due = $total_due + $fd->$key;
							}
							$fees_paid = db_query(
								"SELECT * from $fee_student_payment where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $sd->adm_no)
							);
							foreach($fees_paid as $fp){
								$total_paid = $total_paid + $fp->amount;
							}
						}
					}
					if($total_due != 0){
						$html .= get_fd_content_class($form, $form_state, $sd->adm_no);
					}
				}
			}
		}
		$dompdf = new DOMPDF;
		$dompdf->load_html($html);
		$dompdf->render();
		// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
		$dompdf->stream($form_state['values']['template'].'_'.$class->name.'_'.$section->name.".pdf", array('compress' => FALSE));
	}
	if($form_state['values']['student'] != NULL && $form_state['values']['template'] != 'Fee Defaulter'){
		$html = get_content($form, $form_state);
		
		$dompdf = new DOMPDF;
		$dompdf->load_html($html);
		$dompdf->set_paper('A4', 'portrait');
		$dompdf->render();
		// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
		$dompdf->stream($form_state['values']['template'].'_'.$form_state['values']['student'].".pdf", array('compress' => FALSE));
	}
	
	if($form_state['values']['student'] == NULL && $form_state['values']['template'] != 'Fee Defaulter'){
		$html = get_content_class($form, $form_state);
		$dompdf = new DOMPDF;
		$dompdf->load_html($html);
		$dompdf->render();
		// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
		$class = taxonomy_term_load($form_state['values']['class'][0]);
		$section = taxonomy_term_load($form_state['values']['class'][1]);
    
		$dompdf->stream($form_state['values']['template'].$class->name.'_'.$section->name.".pdf", array('compress' => FALSE));
	}
  /*
	$dompdf = new DOMPDF;
	$dompdf->load_html($html);
	$dompdf->render();
	$pdfoutput = $dompdf->output();
	$filename = 'sites/default/files/filedepot/'.$folder_id.'/'.'Time_Table_'.$form_state['values']['db_table'].'.pdf';
	$fp = fopen($filename, "w+");
	fwrite($fp, $pdfoutput);
	fclose($fp);
	*/
}

function get_fd_content($form, $form_state){
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  $student_table = 'essa_'.$session_id.'_master_student_table';
	$session_id = (string)variable_get('essa_sid');
	$fee_frequency_table = 'essa_'.$session_id.'_fees_frequency';
	$fee_due_table = 'essa_'.$session_id.'_fees_student_due';
	$fee_structure_table = 'essa_'.$session_id.'_fees_structure';
	$fee_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$options = array();
  
  $certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array('title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$header_fid = db_query(
    	"SELECT * from file_managed where fid = :fid;", array(':fid' => $certificate->fid_header)
    );
    foreach($header_fid as $hf){
      $huri = $hf->uri;
    }
		
    $watermark_fid = db_query(
    	"SELECT * from file_managed where fid = :fid;", array(':fid' => $certificate->fid_watermark)
    );
    foreach($watermark_fid as $wf){
      $wuri = $wf->uri;
    }
		
		$cer_id = $certificate->id;
		$sr_no = variable_get('cer_id-'.$certificate->id);
  }
	
  global $base_url;
	if(isset($wuri)){
		$wuri = str_ireplace('public://', '/', $wuri);
		$url = $base_url.$wuri;
	}
	
	if(isset($huri) != NULL){
		$huri = str_ireplace('public://', '/', $huri);
		$url = $base_url.$huri;	
	}
  $certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array(':title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$content = '<html>';
		$content .= '<head>';
		$content .= '<style>';
		$content .= '
		  body{
		    margin-left: 0.5in;
		    margin-right: 0.5in;
		    max-width: 100%;
		  }
		  
		  img{
		    width:100%;
		  }
			
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
				page-break-after: always;
			}
		
			table{
				border: 0px solid black;
				width:100%;
			}
			th{
				background: 	#708090;
				color: WHITE;
			}
			td{
				padding: 7px;
				text-align: center;
			}
			body {
				background: url(variable_get(\'file_public_path\', conf_path() . \'/files\').$wuri) 50% 0px no-repeat !important;
		    background: url(variable_get(\'file_public_path\', conf_path() . \'/files\').$wuri);
		    background-repeat: no-repeat;
		    background-attachment: fixed;
		    background-position: center; 
			}
			@page { margin:0.1in 0.1in 0.1in 0.1in; }
		';
		//dsm(variable_get('file_public_path', conf_path() . '/files').$wuri);
		$content .= '</style>';
		$content .= '</head>';
		$content .= '<body>';
		if(isset($huri) != NULL){
			$content .= '<div><img src = "'.variable_get('file_public_path', conf_path() . '/files').$huri.'"></div>';	
		}
		
		//$content .= '<div><img src = "'.variable_get('file_public_path', conf_path() . '/files').$wuri.'"align="middle"></div>';
		$student_detail = db_query(
			"SELECT * from $student_table where adm_no = :an;", array(':an' => $form_state['values']['student'])
		);
		foreach($student_detail as $sd){
			$body = $certificate->body;
			$body = str_ireplace('[student_name]', $sd->first_name.' '.$sd->last_name, $body);
			$body = str_ireplace('[sr_no]', $sr_no, $body);
			$body = str_ireplace('[student_first_name]', $sd->first_name, $body);
			$body = str_ireplace('[student_last_name]', $sd->last_name, $body);
			$body = str_ireplace('[father_name]', $sd->f_first_name.' '.$sd->f_last_name, $body);
			$body = str_ireplace('[father_first_name]', $sd->f_first_name, $body);
			$body = str_ireplace('[father_last_name]', $sd->f_last_name, $body);
			$body = str_ireplace('[mother_name]', $sd->m_first_name.' '.$sd->m_last_name, $body);
			$body = str_ireplace('[mother_first_name]', $sd->m_first_name, $body);
			$body = str_ireplace('[mother_last_name]', $sd->m_last_name, $body);
			$body = str_ireplace('[adm_no]', $form_state['values']['student'], $body);
			$body = str_ireplace('[class]', $student->class, $body);
			$body = str_ireplace('[section]', $student->section, $body);
			$body = str_ireplace('[class_section]', $student->class.' - '.$student->section, $body);
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
		
		$session_id = (string)variable_get('essa_sid');
		$fee_frequency_table = 'essa_'.$session_id.'_fees_frequency';
		$fee_due_table = 'essa_'.$session_id.'_fees_student_due';
		$fee_structure_table = 'essa_'.$session_id.'_fees_structure';
		$fee_student_payment = 'essa_'.$session_id.'_fees_student_payment';
		$today = strtotime(date('d-m-Y'));
		$total = 0;
		$total_paid = 0;
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
						"SELECT $key from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $form_state['values']['student'])
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
		
		$today = strtotime(date('d-m-Y'));
		$fd_table = '<table>';
		
		
		$fd_table .= '<tr>';
		$fd_table .= '<th>'.'</th>';
		foreach($particulars as $p){
			$fd_table .= '<th>'.$p.'</th>';
		}
		$fd_table .= '</tr>';
		$fees_structure = db_query(
			"SELECT * from $fee_structure_table;"
		);
		//foreach($fees_structure as $fs){
		$results = db_select($fee_frequency_table, 'n')
			->fields('n')
			->condition('freq_id', $fs->freq_id, '=')
			->execute();
		$freq = $results->fetchAssoc();
		//dsm($today);
		//dsm(date('d-m-Y',$today));
		foreach($freq as $key => $value){
			if($value != NULL && $key != 'freq_id' && $key != 'freq_name' && $value < $today){
				
				$fees_due = db_query(
					"SELECT $key from $fee_due_table where adm_no = :an;", array(':an' => $form_state['values']['student'])
				);
				$fd_table .= '<tr>';
				$fd_table .= '<td>'.str_replace('_',' ',$key).'</td>';
				//dsm($key);
				foreach($fees_due as $fd){
					$total = $total+$fd->$key;
					if($fd->$key != 0){
						$fee_due_detail = !is_null($fd->$key)?$fd->$key:' - ';
						$fd_table .= '<td>'.$fee_due_detail.'</td>';
					}
					//$due[]
				}
				$fees_paid = db_query(
					"SELECT * from $fee_student_payment where adm_no = :an;", array(':an' => $form_state['values']['student'])
				);
				foreach($fees_paid as $fp){
					$total_paid = $total_paid + $fp->amount;
				}
				$fd_table .= '</tr>';
			}
			//}
		}
		$fd_table .= '<tr>';
		$fd_table .= '<th>'.'Total'.'</th>';
		foreach($per_fee_due as $pfd){
			if($pfd != 0){
				$fd_table .= '<th>'.$pfd.'</th>';
			}
		}
		$fd_table .= '<tr>';
		$fd_table .= '</table>';
		
		$body = str_ireplace('[fdd]', $fd_table, $body);
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
		//$content .= '<div><img src = "'.variable_get('file_public_path', conf_path() . '/files').$wuri.'"></div>';
		$content .= '</body>';
		$content .= '</html>';	
  }
	
	$sr_no++;
	variable_set('cer_id-'.$cer_id,$sr_no);
  return $content;
}

/**
*Generates certificates for entire class
*/
function get_fd_content_class($form, $form_state, $adm_no){
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  $student_table = 'essa_'.$session_id.'_master_student_table';
	$fee_frequency_table = 'essa_'.$session_id.'_fees_frequency';
	$fee_due_table = 'essa_'.$session_id.'_fees_student_due';
	$fee_structure_table = 'essa_'.$session_id.'_fees_structure';
	$fee_student_payment = 'essa_'.$session_id.'_fees_student_payment';
	$class = taxonomy_term_load($form_state['values']['class'][0]);
	$section = taxonomy_term_load($form_state['values']['class'][1]);
    
  $options = array();
  
  $certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array('title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$header_fid = db_query(
    	"SELECT * from file_managed where fid = :fid;", array(':fid' => $certificate->fid_header)
    );
    foreach($header_fid as $hf){
      $huri = $hf->uri;
    }
		
    $watermark_fid = db_query(
    	"SELECT * from file_managed where fid = :fid;", array(':fid' => $certificate->fid_watermark)
    );
    foreach($watermark_fid as $wf){
      $wuri = $wf->uri;
    }
  }
  global $base_url;
  $wuri = str_ireplace('public://', '/', $wuri);
  //$url = $base_url.$wuri;
	
	if(isset($huri) != NULL){
		$huri = str_ireplace('public://', '/', $huri);
		$url = $base_url.$huri;	
	}
	
  $content = '<html>';
	$content .= '<head>';
	$content .= '<style>';
	$content .= '
    body{
      margin-left: 0.5in;
      margin-right: 0.5in;
      max-width: 100%;
    }
    
    img{
      width:100%;
    }
		
		#cer_footer{
			position: absolute;
			bottom:0.5cm;
			page-break-after: always;
		}
  
		table{
			border: 0px solid black;
		}
		th{
			background: 	#708090;
			color: WHITE;
		}
		td{
			padding: 7px;
			text-align: center;
		}
		
		@page { margin:0.1in 0.1in 0.1in 0.1in; }
	';
	$content .= '</style>';
	$content .= '</head>';
	$content .= '<body>';
	
  $certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array(':title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$class = taxonomy_term_load($form_state['values']['class'][0]);
		$section = taxonomy_term_load($form_state['values']['class'][1]);
    $students = db_query(
    	"SELECT * from $student_table where adm_no = :an;", array(':an' => $adm_no)
    );
    foreach($students as $student){
			$student_table = 'essa_'.$session_id.'_'.$class->name.'_'.$section->name;
			$student_detail = db_query(
				"SELECT * from $student_table where adm_no = :an;", array(':an' => $student->adm_no)
			);
			foreach($student_detail as $sd){
				if(isset($huri) != NULL){
					$content .= '<div><img src = "'.variable_get('file_public_path', conf_path() . '/files').$huri.'"></div>';	
				}
				$body = $certificate->body;
				$body = str_ireplace('[student_name]', $sd->first_name.' '.$sd->last_name, $body);
				$body = str_ireplace('[student_first_name]', $sd->first_name, $body);
				$body = str_ireplace('[student_last_name]', $sd->last_name, $body);
				$body = str_ireplace('[father_name]', $sd->f_first_name.' '.$sd->f_last_name, $body);
				$body = str_ireplace('[father_first_name]', $sd->f_first_name, $body);
				$body = str_ireplace('[father_last_name]', $sd->f_last_name, $body);
				$body = str_ireplace('[mother_name]', $sd->m_first_name.' '.$sd->m_last_name, $body);
				$body = str_ireplace('[mother_first_name]', $sd->m_first_name, $body);
				$body = str_ireplace('[mother_last_name]', $sd->m_last_name, $body);
				$body = str_ireplace('[adm_no]', $sd->adm_no, $body);
				$body = str_ireplace('[class]', $student->class, $body);
				$body = str_ireplace('[section]', $student->section, $body);
				$body = str_ireplace('[class_section]', $student->class.' - '.$student->section, $body);
				$body = str_ireplace('[doa]', $sd->doa, $body);
				$body = str_ireplace('[dob]', $sd->dob, $body);
			}
		}
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
						"SELECT $key from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $adm_no)
					);
					foreach($fees_due as $fd){
						$total_due = $total_due + $fd->$key;
					}
					$fees_paid = db_query(
						"SELECT $key from $fee_student_payment where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $adm_no)
					);
					foreach($fees_paid as $fp){
						$total_paid = $total_paid + $fp->$key;
					}
				}
			}
		}
			
		$body = str_ireplace('[session]', str_replace('_', '-', $session_id), $body);
		$body = str_ireplace('[tfd]', $total_due, $body);
		$body = str_ireplace('[tph]', $total_paid, $body);

		$session_id = (string)variable_get('essa_sid');
		$fee_frequency_table = 'essa_'.$session_id.'_fees_frequency';
		$fee_due_table = 'essa_'.$session_id.'_fees_student_due';
		$fee_structure_table = 'essa_'.$session_id.'_fees_structure';
		$fee_student_payment = 'essa_'.$session_id.'_fees_student_payment';
		$today = strtotime(date('d-m-Y'));
		$total = 0;
		$total_paid = 0;
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
						"SELECT $key from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $adm_no)
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
		
		$today = strtotime(date('d-m-Y'));
		$fd_table = '<table>';
		
		
		$fd_table .= '<tr>';
		$fd_table .= '<th>'.'</th>';
		foreach($particulars as $p){
			$fd_table .= '<th>'.$p.'</th>';
		}
		$fd_table .= '</tr>';
		$fees_structure = db_query(
			"SELECT * from $fee_structure_table;"
		);
		//foreach($fees_structure as $fs){
		$results = db_select($fee_frequency_table, 'n')
			->fields('n')
			->condition('freq_id', $fs->freq_id, '=')
			->execute();
		$freq = $results->fetchAssoc();
		//dsm($today);
		//dsm(date('d-m-Y',$today));
		foreach($freq as $key => $value){
			if($value != NULL && $key != 'freq_id' && $key != 'freq_name' && $value < $today){
				
				$fees_due = db_query(
					"SELECT $key from $fee_due_table where adm_no = :an;", array(':an' => $adm_no)
				);
				$fd_table .= '<tr>';
				$fd_table .= '<td>'.str_replace('_',' ',$key).'</td>';
				//dsm($key);
				foreach($fees_due as $fd){
					$total = $total+$fd->$key;
					if($fd->$key != 0){
						$fee_due_detail = !is_null($fd->$key)?$fd->$key:' - ';
						$fd_table .= '<td>'.$fee_due_detail.'</td>';
					}
					//$due[]
				}
				$fees_paid = db_query(
					"SELECT * from $fee_student_payment where adm_no = :an;", array(':an' => $adm_no)
				);
				foreach($fees_paid as $fp){
					$total_paid = $total_paid + $fp->amount;
				}
				$fd_table .= '</tr>';
			}
			//}
		}
		$fd_table .= '<tr>';
		$fd_table .= '<th>'.'Total'.'</th>';
		foreach($per_fee_due as $pfd){
			if($pfd != 0){
				$fd_table .= '<th>'.$pfd.'</th>';
			}
		}
		$fd_table .= '<tr>';
		$fd_table .= '</table>';
		
		$body = str_ireplace('[fdd]', $fd_table, $body);
		$session_id = (string)variable_get('essa_sid');
		$fee_frequency_table = 'essa_'.$session_id.'_fees_frequency';
		$fee_due_table = 'essa_'.$session_id.'_fees_student_due';
		$fee_structure_table = 'essa_'.$session_id.'_fees_structure';
		$fee_student_payment = 'essa_'.$session_id.'_fees_student_payment';
			
		$total = 0;
		$total_paid = 0;
				
		$today = strtotime(date('30-12-2017'));
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
						"SELECT $key from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $adm_no)
					);
					foreach($fees_due as $fd){
						$per_fee_due[$fs->fee_id] = $per_fee_due[$fs->fee_id] + $fd->$key;
					}
				}
			}
		}
		$today = strtotime(date('30-12-2017'));
		$fees_structure = db_query(
			"SELECT * from $fee_structure_table;"
		);
		$fd_table = '<table>';
			
		$fd_table .= '<tr>';
		$fd_table .= '<th>'.'</th>';
		foreach($fees_structure as $fs){
			$fd_table .= '<th>'.$fs->particulars.'</th>';
		}
		$fd_table .= '</tr>';
		$fees_structure = db_query(
			"SELECT * from $fee_structure_table;"
		);
		//foreach($fees_structure as $fs){
		$results = db_select($fee_frequency_table, 'n')
			->fields('n')
			->condition('freq_id', $fs->freq_id, '=')
			->execute();
		$freq = $results->fetchAssoc();
		foreach($freq as $key => $value){
			if($key != 'freq_id' && $key != 'freq_name' && $value < $today){
				$fees_due = db_query(
					"SELECT $key from $fee_due_table where adm_no = :an;", array(':an' => $adm_no)
				);
				$fd_table .= '<tr>';
				$fd_table .= '<td>'.str_replace('_',' ',$key).'</td>';
				foreach($fees_due as $fd){
					$total = $total+$fd->$key;
					$fee_due_detail = !is_null($fd->$key)?$fd->$key:' - ';
					$fd_table .= '<td>'.$fee_due_detail.'</td>';
				}
				$fees_paid = db_query(
					"SELECT $key from $fee_student_payment where adm_no = :an;", array(':an' => $adm_no)
				);
				foreach($fees_paid as $fp){
					$total_paid = $total_paid + $fp->$key;
				}
				$fd_table .= '</tr>';
			}
		}
		$fd_table .= '<tr>';
		$fd_table .= '<th>'.'Total'.'</th>';
		foreach($per_fee_due as $pfd){
			$fd_table .= '<th>'.$pfd.'</th>';
		}
		$fd_table .= '<tr>';
		$fd_table .= '</table>';
		
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
				"SELECT * from $certificate_rv_table where adm_no = :an;", array(':an' => $adm_no)
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
		//$content .= '<div><img src = "'.variable_get('file_public_path', conf_path() . '/files').$wuri.'"></div>';
	}
  
	$content .= '</body>';
	$content .= '</html>';	
	return $content;
}

function get_content($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  $student_table = 'essa_'.$session_id.'_master_student_table';
	$session_id = (string)variable_get('essa_sid');
	$fee_frequency_table = 'essa_'.$session_id.'_fees_frequency';
	$fee_due_table = 'essa_'.$session_id.'_fees_student_due';
	$fee_structure_table = 'essa_'.$session_id.'_fees_structure';
	$fee_student_payment = 'essa_'.$session_id.'_fees_student_payment';
  $options = array();
  
  $certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array('title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$header_fid = db_query(
    	"SELECT * from file_managed where fid = :fid;", array(':fid' => $certificate->fid_header)
    );
    foreach($header_fid as $hf){
      $huri = $hf->uri;
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
	$x = '5in';
  
	if(isset($huri) != NULL){
		$huri = str_ireplace('public://', '/', $huri);
		$url = $base_url.$huri;	
	}
	
	if(isset($wuri) != NULL){
		$wuri = str_ireplace('public://', '/', $wuri);
		$url = $base_url.$huri;	
	}
	//dsm($huri);
  $certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array(':title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$content = '<html>';
		$content .= '<head>';
		$content .= '<style>';
		$content .= '
		  body{
		    margin-left: 0.5in;
		    margin-right: 0.5in;
		    max-width: 100%;
		  }
		  
		  img{
		    width:100%;
		  }
			
			#cer_footer{
				position: absolute;
				bottom:0.5cm;
				page-break-after: always;
			}
		
			table{
				border: 0px solid black;
			}
			th{
				background: 	#708090;
				color: WHITE;
			}
			td{
				padding: 7px;
			}
			body {
				background-image: url('.variable_get('file_public_path', conf_path() . '/files').$wuri.');
				background-repeat: no-repeat;
		    background-attachment: fixed;
		    background-position: center; 
			}
			@page { margin:0.1in 0.1in 0.1in 0.1in; }
		';
		//dsm(variable_get('file_public_path', conf_path() . '/files').$wuri);
		$content .= '</style>';
		$content .= '</head>';
		$content .= '<body>';
		if(isset($huri) != NULL){
			$content .= '<div><img src = "'.variable_get('file_public_path', conf_path() . '/files').$huri.'"></div>';	
		}
		
		$student_detail = db_query(
			"SELECT * from $student_table where adm_no = :an;", array(':an' => $form_state['values']['student'])
		);
		foreach($student_detail as $sd){
			$body = $certificate->body;
			$body = str_ireplace('[sr_no]', $sr_no, $body);
			$body = str_ireplace('[student_name]', $sd->first_name.' '.$sd->last_name, $body);
			$body = str_ireplace('[student_first_name]', $sd->first_name, $body);
			$body = str_ireplace('[student_last_name]', $sd->last_name, $body);
			$body = str_ireplace('[father_name]', $sd->f_first_name.' '.$sd->f_last_name, $body);
			$body = str_ireplace('[father_first_name]', $sd->f_first_name, $body);
			$body = str_ireplace('[father_last_name]', $sd->f_last_name, $body);
			$body = str_ireplace('[mother_name]', $sd->m_first_name.' '.$sd->m_last_name, $body);
			$body = str_ireplace('[mother_first_name]', $sd->m_first_name, $body);
			$body = str_ireplace('[mother_last_name]', $sd->m_last_name, $body);
			$body = str_ireplace('[adm_no]', $form_state['values']['student'], $body);
			$body = str_ireplace('[class]', $sd->class, $body);
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
		//$content .= '<div><img src = "'.variable_get('file_public_path', conf_path() . '/files').$wuri.'"></div>';
		$content .= '</body>';
		$content .= '</html>';	
  }
	
	$sr_no++;
	variable_set('cer_id-'.$cer_id,$sr_no);
  return $content;
}

/**
*Generates certificates for entire class
*/
function get_content_class($form, $form_state){
	$session_id = (string)variable_get('essa_sid');
	$session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
  $student_table = 'essa_'.$session_id.'_master_student_table';
	$session_id = (string)variable_get('essa_sid');
	$fee_frequency_table = 'essa_'.$session_id.'_fees_frequency';
	$fee_due_table = 'essa_'.$session_id.'_fees_student_due';
	$fee_structure_table = 'essa_'.$session_id.'_fees_structure';
	$fee_student_payment = 'essa_'.$session_id.'_fees_student_payment';
  $options = array();
  
  $certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array('title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$header_fid = db_query(
    	"SELECT * from file_managed where fid = :fid;", array(':fid' => $certificate->fid_header)
    );
    foreach($header_fid as $hf){
      $huri = $hf->uri;
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
  global $base_url;
  $wuri = str_ireplace('public://', '/', $wuri);
  //$url = $base_url.$wuri;
	if(isset($huri) != NULL){
		$huri = str_ireplace('public://', '/', $huri);
		$url = $base_url.$huri;	
	}
  $content = '<html>';
	$content .= '<head>';
	$content .= '<style>';
	$content .= '
    body{
      margin-left: 0.5in;
      margin-right: 0.5in;
      max-width: 100%;
    }
    
    img{
      width:100%;
    }
		
		#cer_footer{
			position: absolute;
			bottom:0.5cm;
			page-break-after: always;
		}
  
		table{
			border: 0px solid black;
		}
		th{
			background: 	#708090;
			color: WHITE;
		}
		td{
			padding: 7px;
		}
		
		@page { margin:0.1in 0.1in 0.1in 0.1in; }
	';
	$content .= '</style>';
	$content .= '</head>';
	$content .= '<body>';
	
  $certificates = db_query(
		"SELECT * from $certificate_table where title = :title;", array(':title' => $form_state['values']['template'])
	);
	foreach($certificates as $certificate){
		$class = taxonomy_term_load($form_state['values']['class'][0]);
		$section = taxonomy_term_load($form_state['values']['class'][1]);
    $students = db_query(
    	"SELECT * from $student_table where class = :cl and section = :sec;", array(':cl' => $class->name, ':sec' => $section->name)
    );
    foreach($students as $student){
			$student_table = 'essa_'.$session_id.'_'.$class->name.'_'.$section->name;
			$student_detail = db_query(
				"SELECT * from $student_table where adm_no = :an;", array(':an' => $student->adm_no)
			);
			foreach($student_detail as $sd){
				if(isset($huri) != NULL){
					$content .= '<div><img src = "'.variable_get('file_public_path', conf_path() . '/files').$huri.'"></div>';	
				}
				$body = $certificate->body;
				$body = str_ireplace('[sr_no]', $sr_no, $body);
				$body = str_ireplace('[student_name]', $sd->first_name.' '.$sd->last_name, $body);
				$body = str_ireplace('[student_first_name]', $sd->first_name, $body);
				$body = str_ireplace('[student_last_name]', $sd->last_name, $body);
				$body = str_ireplace('[father_name]', $sd->f_first_name.' '.$sd->f_last_name, $body);
				$body = str_ireplace('[father_first_name]', $sd->f_first_name, $body);
				$body = str_ireplace('[father_last_name]', $sd->f_last_name, $body);
				$body = str_ireplace('[mother_name]', $sd->m_first_name.' '.$sd->m_last_name, $body);
				$body = str_ireplace('[mother_first_name]', $sd->m_first_name, $body);
				$body = str_ireplace('[mother_last_name]', $sd->m_last_name, $body);
				$body = str_ireplace('[adm_no]', $sd->adm_no, $body);
				$body = str_ireplace('[class]', $student->class, $body);
				$body = str_ireplace('[section]', $student->section, $body);
				$body = str_ireplace('[class_section]', $student->class.' - '.$student->section, $body);
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
								"SELECT $key from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $sd->adm_no)
							);
							foreach($fees_due as $fd){
								$total_due = $total_due + $fd->$key;
							}
							$fees_paid = db_query(
								"SELECT * from $fee_student_payment where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $sd->adm_no)
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
					"SELECT * from $certificate_rv_table where adm_no = :an;", array(':an' => $student->adm_no)
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
			//$content .= '<div><img src = "'.variable_get('file_public_path', conf_path() . '/files').$wuri.'"></div>';
			$sr_no++;
			variable_set('cer_id-'.$cer_id,$sr_no);
		}
  }
  
	$content .= '</body>';
	$content .= '</html>';	
	return $content;
}
/**
 *Implements setting function for heirarchical select form class and section
 */
function cer_hs_setting(){
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