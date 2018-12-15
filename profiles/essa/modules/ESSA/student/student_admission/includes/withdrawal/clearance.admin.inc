<?php
/**
 *Implements page callback function - clearance_form
 */
function clearance_form($form = array(), &$form_state, $value){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$student_withdrawal_table = 'essa_'.$session_id.'_student_withdrawal';
	$fee_due_table = 'essa_'.$session_id.'_fees_student_due';
	$fine_table = 'essa_'.$session_id.'_fees_student_fine';
	$fees_frequency = 'essa_'.$session_id.'_fees_frequency';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$lib_issue_table = 'essa_'.$session_id.'_lib_issue';
	$fee_frequency_table = 'essa_'.$session_id.'_fees_frequency';
	$fee_structure_table = 'essa_'.$session_id.'_fees_structure';
	
	$value = explode('@',$value);
	$adm_no = $value[0];
	//dsm($adm_no);
	$current_month = date('M-Y');
	$cm = strtotime($current_month);
	$fee_due_flag = 0;
	$fine_due_flag = 0;
	$book_due_flag = 0;
	
	$student_details = db_query("SELECT * FROM {$student_table} WHERE adm_no = :an;", array(':an' => $adm_no));
	foreach($student_details as $st){
		$s_name = $st->student_name;
		$class = $st->class.'-'.$st->section;
		$roll_no = $st->roll_no;
	}
	
	global $base_url;
	//$url = $base_url.'/admin/students/withdrawal/manage';
	//'<p class = "back_button">'.l(t('Back'), $url).'</p>
	$form['back'] = array(
		'#type' => 'markup',
		'#markup' => '<p class = "back_button"><a href="javascript:history.go(-1)">Back</a></p>',
	);
	
	$form['name'] = array(
		'#type' => 'markup',
		'#markup' => '<h3>Admission No - '.$adm_no.'</br>Student Name - '.$s_name.'</br>Class - '.$class.'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Roll No - '.$roll_no.'</h3>',
	);
	
	$content = '<html>';
	$content .= '<head><style>
		table{
			table-layout: fixed;
		}
		
		.fee-due-table{
			border: 0px solid black;
			width:100%;
		}
		
		th{
			background: 	#708090;
			color: WHITE;
			text-align: center;	
		}
			
		.fee-due-table td{
			padding: 7px;
			text-align: center;
		}
			
		#cer_footer{
			position: absolute;
			bottom:0.5cm;
			page-break-after: always;
			text-align: center;	
		}
		
		body {
		   background-repeat: no-repeat;
		   background-attachment: fixed;
		   background-position: center; 
		}
	</style></head>';
	
	//*****************Checking for fees dues
	$student_detail = db_query(
		"SELECT * from $student_table where adm_no = :an;", array(':an' => $adm_no)
	);
	foreach($student_detail as $sd){
		$body = '';
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
				}
			}
		}
	}
	
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
					"SELECT $key from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':an' => $adm_no, ':fi' => $fs->fee_id)
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
	$fd_table .= '<th style = "background: 	#708090; color: WHITE; text-align: center;">'.'</th>';
	foreach($particulars as $p){
		$fd_table .= '<th style = "background: 	#708090; color: WHITE; text-align: center;">'.$p.'</th>';
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
					"SELECT * from $fee_due_table where adm_no = :an and fee_id = :fi;", array(':fi' => $fs->fee_id, ':an' => $adm_no)
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
				$fee_due_flag = 1;
				$fd_table .= '<td style = "padding: 7px; text-align: center;">'.$amt.'</td>';
			}
		}
		$fd_table .= '</tr>';
	}
	
	$fd_table .= '<tr>';
	$fd_table .= '<th style = "background: 	#708090; color: WHITE;">'.'Total'.'</th>';
	foreach($per_fee_due as $pfd){
		if($pfd != 0){
			$fd_table .= '<th style = "background: 	#708090; color: WHITE; text-align: center;">'.$pfd.'</th>';
		}
	}
	$fd_table .= '<tr>';
	$fd_table .= '</table></br>';
	
	//dsm($fd_table);
	if($fee_due_flag == 1){
		$form['msg'] = array(
			'#type' => 'markup',
			'#markup' => '<h3><b>Fees Due Details</b></br></h3>',
		);
		$form['table'] = array(
			'#type' => 'markup',
			'#markup' => $fd_table,
		);
	}
	
	//*****************Checking for fine dues
	$months = array();
	$dues = db_query("SELECT * FROM {$fee_due_table} WHERE adm_no = :an;", array(':an' => $adm_no));
	foreach($dues as $due){
		unset($due->fee_id);
		unset($due->adm_no);
		//$m[] = str_replace("-", "_", $due);
		foreach($due as $k=>$d){
			//dsm($k);
			$m = str_replace("_","-",$k);
			$month = strtotime($m);
			if($month <= $cm){
				$month = date('M-Y',$month);
				$month = str_replace("-","_",$month);
				$months[] = $month;
			}
		}
	}
	
	
	
	$student_fine_due = array();
	foreach($months as $mon){
		$fines = db_query("SELECT * FROM {$fine_table} WHERE adm_no = :an and month = :m;", array(':an' => $adm_no, ':m' => $mon));
		foreach($fines as $fine){
			if($fine->amount_to_be_paid != $fine->amount_paid){
				$fine_due_flag = 1;
				$dd[$fine->month][$fine->amount_to_be_paid] = $fine->amount_paid;
			}
		}
	}
	
	$k_total = 0;
	$v_total = 0;
	foreach($dd as $mon=>$atp){
		foreach($atp as $k => $v){
			$k_total = $k_total + $k;
			$v_total = $v_total + $v;
		}
	}
	//dsm($k_total);
	//dsm($dd);//dsm($amount);
	$fin_table = '<table class = "fee-due-table" style = "width:100%; text-align: center;">';
	$fin_table .= '<tr>';
	$fin_table .= '<th style = "background: #708090; text-align: center; color: WHITE;">Months</th>';	
	$fin_table .= '<th style = "background: #708090; text-align: center; color: WHITE;">Amount to be paid</th>';
	$fin_table .= '<th style = "background: #708090; text-align: center; color: WHITE;">Amount Paid</th>';
	$fin_table .= '</tr>';
	
	
	
	foreach($dd as $mon=>$atp){
		$fin_table .= '<tr>';
		$fin_table .= '<td style = "padding: 7px; text-align: center;">'.$mon.'</td>';
		foreach($atp as $k => $v){
			//$k_total[] = $k_total + $k;
			//$v_total[] = $v_total + $v;
			$fin_table .= '<td style = "padding: 7px; text-align: center;">'.$k.'</td>';
			$fin_table .= '<td style = "padding: 7px; text-align: center;">'.$v.'</td>';
		}
		$fin_table .= '</tr>';
		
	}
	$fin_table .= '<tr>';
	$fin_table .= '<th style = "background: #708090; color: WHITE;">'.'Total'.'</th>';
	$fin_table .= '<th style = "background: #708090; color: WHITE; text-align: center;">'.$k_total.'</th>';
	$fin_table .= '<th style = "background: #708090; color: WHITE; text-align: center;">'.$v_total.'</th>';
	$fin_table .= '</tr>';
	$fin_table .= '</table></br>';
	
	if($fine_due_flag == 1){
		$form['msg2'] = array(
			'#type' => 'markup',
			'#markup' => '<h3><b>Fine Due Details</b></br></h3>',
		);
		
		$form['table2'] = array(
			'#type' => 'markup',
			'#markup' => $fin_table,
		);
	}
	
	
	
	//*****************Checking for book dues
	$book_table = '<table class = "fee-due-table" style = "width:100%; text-align: center;">';
	$book_table .= '<tr>';
	$book_table .= '<th style = "background: #708090; text-align: center; color: WHITE;">Issue Number</th>';	
	$book_table .= '<th style = "background: #708090; text-align: center; color: WHITE;">Acc Number</th>';
	$book_table .= '<th style = "background: #708090; text-align: center; color: WHITE;">Issue Date</th>';
	$book_table .= '</tr>';
	
	$book_table .= '<tr>';
	$books = db_query("SELECT * FROM {$lib_issue_table} WHERE user_id = :an;", array(':an' => $adm_no));
	foreach($books as $book){
		if($book->status != 'closed'){
			$book_due_flag = 1;
			$issue_date = date('d-m-Y',$book->issue_date);
			$book_table .= '<td style = "padding: 7px; text-align: center;">'.$book->issue_no.'</td>';
			$book_table .= '<td style = "padding: 7px; text-align: center;">'.$book->acc_no.'</td>';
			$book_table .= '<td style = "padding: 7px; text-align: center;">'.$issue_date.'</td>';
			
		}
		$book_table .= '</tr>';
	}
	$book_table .= '</table></br>';
	
	if($book_due_flag == 1){
		$form['msg3'] = array(
			'#type' => 'markup',
			'#markup' => '<h3><b>Books Due Details</b></br></h3>',
		);
		
		$form['table3'] = array(
			'#type' => 'markup',
			'#markup' => $book_table,
		);
	}
	
	return $form;
}