<?php

/**
 *Implements page callback function - addstudent_bu_form
 */
function bank_collection($form, &$form_state){
	$form = array();
  //dsm($path);

  $form['browser'] = array(
    '#type' => 'fieldset',
    '#title' => t('Browser Upload'),
    '#description' => t("Upload a CSV file. Please fill the data carefully, the system will not be responsilble for incorrect data."),
  );

	$dir_list = db_query("
    SELECT * from node where type = 'dir_listing' and title = 'Fee Templates';
  ");
	foreach($dir_list as $dl){
		$url = 'node/'.$dl->nid;
	}
  $form['browser']['download'] = array(
    '#type' => 'markup',
    '#markup' => '<h3>'.l(t('Download templates'), $url).'</h3>',
  );

  $file_size = t('Maximum file size: !size MB.', array('!size' => file_upload_max_size()));

	$options = get_options();
	$form['browser']['options'] = array(
		'#type' => 'select',
		'#title' => t('Collection For'),
		'#options' => drupal_map_assoc($options),
	);
	
	
  $form['browser']['file_upload'] = array(
    '#type' => 'file',
    '#title' => t('CSV File'),
    '#size' => 40,
    '#description' => t('Select the CSV file to be imported. ') . $file_size,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

	// set the form encoding type
  $form['#attributes']['enctype'] = "multipart/form-data";

  return $form;
}

function bank_collection_validate($form, &$form_state) {
  // attempt to save the uploaded file
  $validators = array('file_validate_extensions' => array('csv'));
  $file = file_save_upload('file_upload', $validators);

  // check file uploaded OK
  if (!$file) {
    form_set_error('file_upload', t('A file must be uploaded or selected from FTP updates.'));
  }
  else if($file->filemime != 'text/csv') {
    form_set_error('file_upload', t('The file must be of CSV type only.'));
  }
  else {
    // set files to form_state, to process when form is submitted
    $form_state['values']['file_upload'] = $file;
  }
}

function bank_collection_submit($form, &$form_state){
	$line_max = variable_get('user_import_line_max', 1000);
	ini_set('auto_detect_line_endings', true);
	$filepath = $form_state['values']['file_upload']->destination;
	$handle = @fopen($filepath, "r");
	$flag = true;
	$num = 0;
	$session = (string)variable_get('essa_sid');
	$fees_table = 'essa_'.$session.'_fees_structure';
	$fees_student_due = 'essa_'.$session.'_fees_student_due';
	$fees_freq = 'essa_'.$session.'_fees_frequency';
	$fees_student_payment = 'essa_'.$session.'_fees_student_payment';
	$payment_history = 'essa_'.$session.'_fees_payment_history';
	$fees_student_fine = 'essa_'.$session.'_fees_student_fine';
	$fee_paid = array();
	global $user;
	
	$basic_info_table = 'essa_'.$session.'_basicinfo';
	$binfo = db_query("
    SELECT * from {$basic_info_table};
  ");
	foreach($binfo as $info){
		$start_date = $info->academicyearstart;
		$end_date = $info->academicyearend;
	}
  $start = new DateTime($start_date);
	$start->modify('first day of this month');
	$end      = new DateTime($end_date);
	$end->modify('first day of next month');
	$interval = DateInterval::createFromDateString('1 month');
	$period   = new DatePeriod($start, $interval, $end);
	foreach ($period as $dt) {
		$columns[] = $dt->format("M_Y");
	}
	foreach($columns as $col){
		switch($form_state['values']['options']){
			case $col:
				$freq = db_query("
				  SELECT * from {$fees_freq} where $col = $col;"
				);
				foreach($freq as $fr){
					if($fr->$col != NULL){
						$fees = db_query("
						  SELECT * from {$fees_table} where freq_id = :fri;", array(':fri' => $fr->freq_id)
						);
						
						foreach($fees as $fee){
							$fee_paid[] = $fee;
						}
					}	
				}
			break;
		}
	}
	//-----------------------------------------------fees Payment History---------------------------------------------------------------------
	while(! feof($handle)){
	  if($flag) {
			$csv = fgetcsv($handle);
			$flag = false; continue;
		}
		$csv = fgetcsv($handle);
		$input_data[] = $csv;
	}
	
	
	foreach($input_data as $id){
		//dsm(sizeof($csv));
		$fees = array_slice($id, 1, sizeof($csv)-4, true);
		$total = 0;
		foreach($fees as $fee){
			$total = $total + (int)$fee;
		}
		$total = $total + (int)$id[sizeof($id) - 2];
		
		//dsm($id);
		$pay_dt = strtotime(str_replace('/', '-',$id[sizeof($id) - 1]));
		//dsm(date('d-M-Y',$pay_dt));
		$receipt_no = NULL;
		$ph = db_query("
			SELECT * from {$payment_history} where adm_no = :an and payment_date = :pd and amount = :am;", array(':an' => $id[0], ':pd' => $pay_dt, ':am' => $total)
		);
		foreach($ph as $p){
			$receipt_no = $p->id;
		}
		db_merge($payment_history)
			->key(array('id' => $receipt_no))
			->fields (array(
				'adm_no' => $id[0],
				'payment_date' => $pay_dt,
				'amount' => $total,
				'uid' => $user->uid,
			)
		)	
		->execute();
	
		//-----------------------------------------------fees student payment---------------------------------------------------------------------
		$ph = db_query("
			SELECT * from {$payment_history} where adm_no = :an and payment_date = :pd and amount = :am;", array(':an' => $id[0], ':pd' => $pay_dt, ':am' => $total)
		);
		foreach($ph as $p){
			$receipt_no = $p->id;
		}
		$fee_no = 0;
		foreach($fee_paid as $fp){
			$fee_no++;
			db_merge($fees_student_payment)
				->key(array('fee_id' => $fp->fee_id,'adm_no' => $id[0]))
				->fields (array(
					'fee_id' => $fp->fee_id,
					'adm_no' => $id[0],
					'month' => $form_state['values']['options'],
					'amount' => $id[$fee_no],
					'receipt_no' => $receipt_no,
				)
			)
			->execute();
		}
		
		//-----------------------------------------------fees student fine---------------------------------------------------------------------
		if($id[sizeof($id) - 2] != NULL){
			db_insert($fees_student_fine)
				->fields (array(
					'adm_no' => $id[0],
					'particulars' => $id[sizeof($id) - 3],
					$form_state['values']['options'] => $id[sizeof($id) - 2],
					$form_state['values']['options'].'_payment_id' => $receipt_no,
				)
			)	
			->execute();	
		}
	}
	
	
	//-----------------------------------------------fees student due---------------------------------------------------------------------
	while(! feof($handle)){
	  if($flag) {
			$csv = fgetcsv($handle);
			$flag = false; continue;
		}
		$csv = fgetcsv($handle);
		$fee_no = 0;
		foreach($fee_paid as $fp){
			$fee_no++;
			$studs = db_query("
				SELECT * from {$fees_student_due} where adm_no = :an and fee_id = :fi;", array(':an' => $csv[0],':fi' => $fp->fee_id)
			);
			foreach($studs as $stud){
				$update = $stud->$form_state['values']['options'] - $csv[$fee_no];
				if($update > 0){
					db_merge($fees_student_due)
						->key(array('fee_id' => $fp->fee_id,'adm_no' => $csv[0]))
						->fields (array(
							$form_state['values']['options'] => $update,
						)
					)
					->execute();
				}else{
					db_merge($fees_student_due)
						->key(array('fee_id' => $fp->fee_id,'adm_no' => $csv[0]))
						->fields (array(
							$form_state['values']['options'] => 0,
						)
					)
					->execute();
				}
			}
		}
	}
	//-----------------------------------------------fees student due---------------------------------------------------------------------
}

function get_options(){
	$session_id = (string)variable_get('essa_sid');
  $fees_table = 'essa_'.$session_id.'_fees_structure';
	$fees_freq = 'essa_'.$session_id.'_fees_frequency';
	
	$session = (string)variable_get('essa_sid');
	$basic_info_table = 'essa_'.$session.'_basicinfo';
	$binfo = db_query("
    SELECT * from {$basic_info_table};
  ");
	foreach($binfo as $info){
		$start_date = $info->academicyearstart;
		$end_date = $info->academicyearend;
	}
  $start = new DateTime($start_date);
	$start->modify('first day of this month');
	$end      = new DateTime($end_date);
	$end->modify('first day of next month');
	$interval = DateInterval::createFromDateString('1 month');
	$period   = new DatePeriod($start, $interval, $end);
	foreach ($period as $dt) {
		$csvs[] = $dt->format("M-Y");
		$columns[] = $dt->format("M_Y");
	}
	foreach($columns as $col){
		$options[] = $col;
	}
	$options = array_unique($options);
	return $options;
}

/*
 $data = array();
		$data = array('Admn no.');
		$freq = db_query("
		  SELECT * from {$fees_freq} where $col = $col;"
		);
		foreach($freq as $fr){
			if($fr->$col != NULL){
				$fees = db_query("
				  SELECT * from {$fees_table} where freq_id = :fri;", array(':fri' => $fr->freq_id)
				);
				foreach($fees as $fee){
					$data[] = $fee->particulars;
				}	
			}
		}
		$data = array_merge($data, array('Total'));
		$data = array_merge($data, array('Payment Date(dd-mm-yyyy)'));
		$count = count($data);
		if($count != 3){
			foreach ($data as $record){
			  $options[] = $col;
			}
		}
		*/