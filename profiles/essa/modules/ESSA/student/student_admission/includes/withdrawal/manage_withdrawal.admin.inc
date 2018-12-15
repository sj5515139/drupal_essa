<?php
/**
 *Implements page callback function - manage_withdrawal_form
 */
function manage_withdrawal_form($form = array(), &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$student_withdrawal_table = 'essa_'.$session_id.'_student_withdrawal';
	
	global $user;
	$fi_uid = array();
	$fee_incharge_role = db_query("SELECT * FROM role WHERE name = 'Fees Incharge'");
	foreach($fee_incharge_role as $fi_role){
		$fi_rid = $fi_role->rid;
	}
	$p_uid = array();
	$principal_role = db_query("SELECT * FROM role WHERE name = 'Principal'");
	foreach($principal_role as $p_role){
		$p_rid = $p_role->rid;
	}
	$s_uid = array();
	$staff_role = db_query("SELECT * FROM role WHERE name = 'staff'");
	foreach($staff_role as $s_role){
		$s_rid = $s_role->rid;
	}
	$a_uid = array();
	$admin_role = db_query("SELECT * FROM role WHERE name = 'administrator'");
	foreach($admin_role as $a_role){
		$a_rid = $a_role->rid;
	}
	$user_rd = array();
	$feeincharge = 0;
	$prin = 0;
	$staff = 0;
	$user_rid = db_query("SELECT * FROM users_roles WHERE uid = :u;", array(':u' => $user->uid));
	foreach($user_rid as $r){
		$user_rd[] = $r->rid;
		foreach($user_rd as $u_rid){
			if($u_rid == $fi_rid){
				$feeincharge = 1;
			}elseif($u_rid == $p_rid){
				$prin = 1;
			}elseif($u_rid == $s_rid || $u_rid == $a_rid){
				$staff = 1;
			}
			
		}
	}
	$x = '<i class = "fa fa-check"></i>';
	$y = '<i class = "fa fa-times"></i>';
	
	$form['group_expulsion'] = array(
		'#type'  => 'fieldset',
		'#title' => t('Expulsion'),
		'#group' => 'group_tabs',
		'#collapsible' => TRUE, 
		'#collapsed' => FALSE,
	);
	
	$form['group_expulsion']['withdrawal_desc'] = array(
		'#type' => 'markup',
		'#markup' => '<h3><strong>NOTE:</strong> This contains student who have been expelled/terminated by the institution. After Principal\'s approval TC & SLC can be generated for that student.</h3>',
		'#group' => 'group_expulsion',
	);
	
	$form['group_passout'] = array(
		'#type'  => 'fieldset',
		'#title' => t('Passouts'),
		'#group' => 'group_tabs',
		'#collapsible' => TRUE, 
		'#collapsed' => FALSE,
	);
	
	$form['group_passout']['withdrawal_desc'] = array(
		'#type' => 'markup',
		'#markup' => '<h3><strong>NOTE:</strong> This contains student who have successfully passed out from institution. Finance shall reviews their due and deposit. Thereafter, Principal\'s approval will be required for TC & SLC generation for that student.</h3>',
		'#group' => 'group_passout',
	);
	
	$form['group_withdrawal'] = array(
		'#type'  => 'fieldset',
		'#title' => t('Withdrawal'),
		'#group' => 'group_tabs',
		'#collapsible' => TRUE, 
		'#collapsed' => FALSE,
	);
	
	$form['group_withdrawal']['withdrawal_desc'] = array(
		'#type' => 'markup',
		'#markup' => '<h3><strong>NOTE:</strong> This contains the applications submitted by parents to withdraw their ward. This must be reviewed by finance to check for any due or deposit. Finally after Principal\'s approval TC & SLC can be generated for that student.</h3>',
		'#group' => 'group_withdrawal',
	);
	
	global $base_url;
	
	if($feeincharge == 1){
		$expulsion_students = db_query("SELECT * FROM {$student_withdrawal_table} WHERE type = :t AND status_fin IS NULL AND status = :s OR status = :s2;",array(':t' => 'expulsion', ':s' => 'pending', ':s2' => 'Approved by principal'));
		foreach($expulsion_students as $ex_student){
			$clear = student_clearance($ex_student->adm_no);
			if($clear == 0){
				$students = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
				foreach($students as $st){
					$row[] = array(
						'#tree' =>TRUE,
						$ex_student -> adm_no => array(  //Generating unique array id for every form element
							$ex_student -> adm_no.'%'.$ex_student -> status_timestamp =>array(
								'#type' => 'checkbox',
								'#options' => $ex_student -> adm_no.'%'.$ex_student -> status_timestamp,
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l(t($ex_student -> adm_no), 'user/'.$st->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st->student_name.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st->class.'-'.$st->section.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$ex_student -> reason.'</h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$ex_student -> status.'</h3>',
							),
							'c6' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$ex_student -> status_reason.'</h3>',
							),
							'c7' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.date('d-m-Y',$ex_student -> status_timestamp).'</h3>',
							),
							'c8' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l($x, 'expulsion/approve/'.$ex_student->adm_no.'%'.$ex_student->status_timestamp, array('html' => TRUE)).'</h3>',
							),
							'c9' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l($y, 'expulsion/reject/'.$ex_student->adm_no.'%'.$ex_student->status_timestamp, array('html' => TRUE)).'</h3>',
							),
						),
					);
				}
				
			}else{
				$url = $base_url.'/expulsion/'.$ex_student->adm_no.'@clearance';
				$students = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
				foreach($students as $st){
					$row[] = array(
						'#tree' =>TRUE,
						$ex_student -> adm_no => array(  //Generating unique array id for every form element
							'c0' =>array(
								'#type' => 'checkbox',
								'#options' => $ex_student -> adm_no.'%'.$ex_student -> status_timestamp,
								'#disabled' => TRUE,
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l(t($ex_student -> adm_no), 'user/'.$st->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st->student_name.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st->class.'-'.$st->section.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$ex_student -> reason.'</h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$ex_student -> status.'</h3>',
							),
							'c6' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$ex_student -> status_reason.'</h3>',
							),
							'c7' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.date('d-m-Y',$ex_student -> status_timestamp).'</h3>',
							),
							'c8' =>array(
								'#type' => 'markup',
								'#markup' => '',
							),
							'c9' =>array(
								'#type' => 'markup',
								'#markup' => '<h3><a href = "'.$url.'">Check Clearance</a></h3>',
							),
						),
					);
				}
				
			}
		}
		
		
		$passout_students = db_query("SELECT * FROM {$student_withdrawal_table} WHERE type = :t AND status = :s;", array(':t' => 'passout', ':s' => 'pending'));
		foreach($passout_students as $po_student){
			$clear = student_clearance($ex_student->adm_no);
			if($clear == 0){
				$students1 = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
				foreach($students1 as $st1){
					$passout_row[] = array(
						'#tree' =>TRUE,
						$po_student -> adm_no => array(  //Generating unique array id for every form element
							$po_student -> adm_no.'%'.$po_student -> status_timestamp =>array(
								'#type' => 'checkbox',
								'#options' => $po_student -> adm_no.'%'.$po_student -> status_timestamp,
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l(t($po_student -> adm_no), 'user/'.$st1->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st1->student_name.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st1->class.'-'.$st1->section.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$po_student -> status.'</h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$po_student -> status_reason.'</h3>',
							),
							'c6' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.date('d-m-Y',$po_student -> status_timestamp).'</h3>',
							),
							'c7' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l($x, 'expulsion/approve/'.$po_student->adm_no.'%'.$po_student->status_timestamp, array('html' => TRUE)).'</h3>',
							),
							'c8' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l($y, 'expulsion/reject/'.$po_student->adm_no.'%'.$po_student->status_timestamp, array('html' => TRUE)).'</h3>',
							),
						),
					);
				}
			}else{
				$url = $base_url.'/expulsion/'.$ex_student->adm_no.'@clearance';
				$students1 = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
				foreach($students1 as $st1){
					$passout_row[] = array(
						'#tree' =>TRUE,
						$po_student -> adm_no => array(  //Generating unique array id for every form element
							'c0' =>array(
								'#type' => 'checkbox',
								'#options' => $po_student -> adm_no.'%'.$po_student -> status_timestamp,
								'#disabled' => TRUE,
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l(t($po_student -> adm_no), 'user/'.$st1->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st1->student_name.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st1->class.'-'.$st1->section.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$po_student -> status.'</h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$po_student -> status_reason.'</h3>',
							),
							'c6' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.date('d-m-Y',$po_student -> status_timestamp).'</h3>',
							),
							'c7' =>array(
								'#type' => 'markup',
								'#markup' => '<h3><a href = "'.$url.'">Check Clearance</a></h3>',
							),
							'c8' =>array(
								'#type' => 'markup',
								'#markup' => '<h3><a href = "'.$url.'">Check Clearance</a></h3>',
							),
						),
					);
				}
				
			}
		}
		
		$withdrawal_students = db_query("SELECT * FROM {$student_withdrawal_table} WHERE type = :t AND status = :s;", array(':t' => 'withdrawal', ':s' => 'pending'));
		foreach($withdrawal_students as $wd_student){
			$clear = student_clearance($ex_student->adm_no);
			if($clear == 0){
				$students2 = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
				foreach($students2 as $st2){
					$withdrawal_row[][] = array(
						'#tree' =>TRUE,
						$wd_student -> adm_no => array(  //Generating unique array id for every form element
							$wd_student -> adm_no.'%'.$wd_student -> status_timestamp =>array(
								'#type' => 'checkbox',
								'#options' => $wd_student -> adm_no.'%'.$wd_student -> status_timestamp,
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l(t($wd_student -> adm_no), 'user/'.$st2->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st2->student_name.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st2->class.'-'.$st2->section.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$wd_student -> status.'</h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$wd_student -> status_reason.'</h3>',
							),
							'c6' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.date('d-m-Y',$wd_student -> status_timestamp).'</h3>',
							),
							'c7' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l($x, 'expulsion/approve/'.$wd_student->adm_no.'%'.$wd_student->status_timestamp, array('html' => TRUE)).'</h3>',
							),
							'c8' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l($y, 'expulsion/reject/'.$wd_student->adm_no.'%'.$wd_student->status_timestamp, array('html' => TRUE)).'</h3>',
							),
						),
					);
				}
			}else{
				$url = $base_url.'/expulsion/'.$ex_student->adm_no.'@clearance';
				$students2 = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
				foreach($students2 as $st2){
					$withdrawal_row[][] = array(
						'#tree' =>TRUE,
						$wd_student -> adm_no => array(  //Generating unique array id for every form element
							'c0' =>array(
								'#type' => 'checkbox',
								'#options' => $wd_student -> adm_no.'%'.$wd_student -> status_timestamp,
								'#disabled' => TRUE,
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l(t($wd_student -> adm_no), 'user/'.$st2->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st2->student_name.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st2->class.'-'.$st2->section.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$wd_student -> status.'</h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$wd_student -> status_reason.'</h3>',
							),
							'c6' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.date('d-m-Y',$wd_student -> status_timestamp).'</h3>',
							),
							'c7' =>array(
								'#type' => 'markup',
								'#markup' => '<h3><a href = "'.$url.'">Check Clearance</a></h3>',
							),
							'c8' =>array(
								'#type' => 'markup',
								'#markup' => '<h3><a href = "'.$url.'">Check Clearance</a></h3>',
							),
						),
					);
				}
			}
		}
	}elseif($prin == 1){
		$expulsion_students = db_query("SELECT * FROM {$student_withdrawal_table} WHERE type = :t AND status = :s",array(':t' => 'expulsion', ':s' => 'Approved by Finance'));
		foreach($expulsion_students as $ex_student){
			$clear = student_clearance($ex_student->adm_no);
			if($clear == 0){
				$students = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
				foreach($students as $st){
					$row[] = array(
						'#tree' =>TRUE,
						$ex_student -> adm_no => array(  //Generating unique array id for every form element
							$ex_student -> adm_no.'%'.$ex_student -> status_timestamp =>array(
								'#type' => 'checkbox',
								'#options' => $ex_student -> adm_no.'%'.$ex_student -> status_timestamp,
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. l(t($ex_student -> adm_no), 'user/'.$st->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st->student_name.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st->class.'-'.$st->section.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$ex_student -> reason.'</h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$ex_student -> status.'</h3>',
							),
							'c6' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$ex_student -> status_reason.'</h3>',
							),
							'c7' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.date('d-m-Y',$ex_student -> status_timestamp).'</h3>',
							),
							'c8' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l($x, 'expulsion/approve/'.$ex_student->adm_no.'%'.$ex_student->status_timestamp, array('html' => TRUE)).'</h3>',
							),
							'c9' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l($y, 'expulsion/reject/'.$ex_student->adm_no.'%'.$ex_student->status_timestamp, array('html' => TRUE)).'</h3>',
							),
						),
					);
				}				
			}else{
				$url = $base_url.'/expulsion/'.$ex_student->adm_no.'@clearance';
				$students = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
				foreach($students as $st){
					$row[] = array(
						'#tree' =>TRUE,
						$ex_student -> adm_no => array(  //Generating unique array id for every form element
							'c0' =>array(
								'#type' => 'checkbox',
								'#options' => $ex_student -> adm_no.'%'.$ex_student -> status_timestamp,
								'#disabled' => TRUE,
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'. l(t($ex_student -> adm_no), 'user/'.$st->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st->student_name.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st->class.'-'.$st->section.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$ex_student -> reason.'</h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$ex_student -> status.'</h3>',
							),
							'c6' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$ex_student -> status_reason.'</h3>',
							),
							'c7' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.date('d-m-Y',$ex_student -> status_timestamp).'</h3>',
							),
							'c8' =>array(
								'#type' => 'markup',
								'#markup' => '',
							),
							'c9' =>array(
								'#type' => 'markup',
								'#markup' => '<h3><a href = "'.$url.'">Check Clearance</a></h3>',
							),
						),
					);
				}
			}
		}
		
		$passout_students = db_query("SELECT * FROM {$student_withdrawal_table} WHERE type = :t AND status = :s;", array(':t' => 'passout', ':s' => 'Approved By Finance'));
		foreach($passout_students as $po_student){
			$clear = student_clearance($ex_student->adm_no);
			if($clear == 0){
				$students1 = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
				foreach($students1 as $st1){
					$passout_row[] = array(
						'#tree' =>TRUE,
						$po_student -> adm_no => array(  //Generating unique array id for every form element
							$po_student -> adm_no.'%'.$po_student -> status_timestamp =>array(
								'#type' => 'checkbox',
								'#options' => $po_student -> adm_no.'%'.$po_student -> status_timestamp,
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l(t($po_student -> adm_no), 'user/'.$st1->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st1->student_name.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st1->class.'-'.$st1->section.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$po_student -> status.'</h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$po_student -> status_reason.'</h3>',
							),
							'c6' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.date('d-m-Y',$po_student -> status_timestamp).'</h3>',
							),
							'c7' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l($x, 'expulsion/approve/'.$po_student->adm_no.'%'.$po_student->status_timestamp, array('html' => TRUE)).'</h3>',
							),
							'c8' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l($y, 'expulsion/reject/'.$po_student->adm_no.'%'.$po_student->status_timestamp, array('html' => TRUE)).'</h3>',
							),
						),
					);
				}
			}else{
				$url = $base_url.'/expulsion/'.$ex_student->adm_no.'@clearance';
				$students1 = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
				foreach($students1 as $st1){
					$passout_row[] = array(
						'#tree' =>TRUE,
						$po_student -> adm_no => array(  //Generating unique array id for every form element
							'c0' =>array(
								'#type' => 'checkbox',
								'#options' => $po_student -> adm_no.'%'.$po_student -> status_timestamp,
								'#disabled' => TRUE,
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l(t($po_student -> adm_no), 'user/'.$st1->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st1->student_name.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st1->class.'-'.$st1->section.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$po_student -> status.'</h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$po_student -> status_reason.'</h3>',
							),
							'c6' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.date('d-m-Y',$po_student -> status_timestamp).'</h3>',
							),
							'c7' =>array(
								'#type' => 'markup',
								'#markup' => '<h3><a href = "'.$url.'">Check Clearance</a></h3>',
							),
							'c8' =>array(
								'#type' => 'markup',
								'#markup' => '',
							),
						),
					);
				}
			}
		}
		
		$withdrawal_students = db_query("SELECT * FROM {$student_withdrawal_table} WHERE type = :t AND status = :s;", array(':t' => 'withdrawal', ':s' => 'Approved by Finance'));
		foreach($withdrawal_students as $wd_student){
			$clear = student_clearance($ex_student->adm_no);
			if($clear == 0){
				$students2 = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
				foreach($students2 as $st2){
					$withdrawal_row[] = array(
						'#tree' =>TRUE,
						$wd_student -> adm_no => array(  //Generating unique array id for every form element
							$wd_student -> adm_no.'%'.$wd_student -> status_timestamp =>array(
								'#type' => 'checkbox',
								'#options' => $wd_student -> adm_no.'%'.$wd_student -> status_timestamp,
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l(t($wd_student -> adm_no), 'user/'.$st2->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st2->student_name.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st2->class.'-'.$st2->section.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$wd_student -> status.'</h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$wd_student -> status_reason.'</h3>',
							),
							'c6' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.date('d-m-Y',$wd_student -> status_timestamp).'</h3>',
							),
							'c7' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l($x, 'expulsion/approve/'.$wd_student->adm_no.'%'.$wd_student->status_timestamp, array('html' => TRUE)).'</h3>',
							),
							'c8' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l($y, 'expulsion/reject/'.$wd_student->adm_no.'%'.$wd_student->status_timestamp, array('html' => TRUE)).'</h3>',
							),
						),
					);
				}
			}else{
				$url = $base_url.'/expulsion/'.$ex_student->adm_no.'@clearance';
				$students2 = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
				foreach($students2 as $st2){
					$withdrawal_row[] = array(
						'#tree' =>TRUE,
						$wd_student -> adm_no => array(  //Generating unique array id for every form element
							'c0' =>array(
								'#type' => 'checkbox',
								'#options' => $wd_student -> adm_no.'%'.$wd_student -> status_timestamp,
								'#disabled' => TRUE,
							),
							'c1' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.l(t($wd_student -> adm_no), 'user/'.$st2->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
							),
							'c2' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st2->student_name.'</h3>',
							),
							'c3' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$st2->class.'-'.$st2->section.'</h3>',
							),
							'c4' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$wd_student -> status.'</h3>',
							),
							'c5' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.$wd_student -> status_reason.'</h3>',
							),
							'c6' =>array(
								'#type' => 'markup',
								'#markup' => '<h3>'.date('d-m-Y',$wd_student -> status_timestamp).'</h3>',
							),
							'c7' =>array(
								'#type' => 'markup',
								'#markup' => '<h3><a href = "'.$url.'">Check Clearance</a></h3>',
							),
							'c8' =>array(
								'#type' => 'markup',
								'#markup' => '',
							),
						),
					);
				}
			}
		}
		
	}elseif($staff == 1){
		$expulsion_students = db_query("SELECT * FROM {$student_withdrawal_table} WHERE type = :t;",array(':t' => 'expulsion'));
		foreach($expulsion_students as $ex_student){
			$students = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
			foreach($students as $st){
				$row[] = array(
					'#tree' =>TRUE,
					$ex_student -> adm_no => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'. l(t($ex_student -> adm_no), 'user/'.$st->uid, array('attributes'=>array('target'=>'blank'))) .'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$st->student_name.'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$st->class.'-'.$st->section.'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$ex_student -> reason.'</h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$ex_student -> status.'</h3>',
						),
						'c6' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$ex_student -> status_reason.'</h3>',
						),
						'c7' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.date('d-m-Y',$ex_student -> status_timestamp).'</h3>',
						),
					),
				);
			}
		}
		
		$passout_students = db_query("SELECT * FROM {$student_withdrawal_table} WHERE type = :t;", array(':t' => 'passout'));
		foreach($passout_students as $po_student){
			$students1 = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
			foreach($students1 as $st1){
				$passout_row[] = array(
					'#tree' =>TRUE,
					$po_student -> adm_no => array(  //Generating unique array id for every form element
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.l(t($po_student -> adm_no), 'user/'.$st1->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$st1->student_name.'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$st1->class.'-'.$st1->section.'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$po_student -> status.'</h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$po_student -> status_reason.'</h3>',
						),
						'c6' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.date('d-m-Y',$po_student -> status_timestamp).'</h3>',
						),
					),
				);
			}
		}
		
		$withdrawal_students = db_query("SELECT * FROM {$student_withdrawal_table} WHERE type = :t;", array(':t' => 'withdrawal'));
		foreach($withdrawal_students as $wd_student){
			$students2 = db_query("SELECT * FROM {$student_table} WHERE adm_no = :adm;",array(':adm' => $ex_student->adm_no));
			foreach($students2 as $st2){
				$withdrawal_row[] = array(
					'#tree' =>TRUE,
					$wd_student -> adm_no => array(  //Generating unique array id for every form element
						$wd_student -> adm_no.'%'.$wd_student -> status_timestamp =>array(
							'#type' => 'checkbox',
							'#options' => $wd_student -> adm_no.'%'.$wd_student -> status_timestamp,
						),
						'c1' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.l(t($wd_student -> adm_no), 'user/'.$st2->uid, array('attributes'=>array('target'=>'blank'))).'</h3>',
						),
						'c2' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$st2->student_name.'</h3>',
						),
						'c3' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$st2->class.'-'.$st2->section.'</h3>',
						),
						'c4' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$wd_student -> status.'</h3>',
						),
						'c5' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.$wd_student -> status_reason.'</h3>',
						),
						'c6' =>array(
							'#type' => 'markup',
							'#markup' => '<h3>'.date('d-m-Y',$wd_student -> status_timestamp).'</h3>',
						),
					),
				);
			}
		}
	}
	
	if(isset($row)){
		$form['group_expulsion']['expulsion'] = array(
			'#theme' => 'student_expulsion_table',
			'rows' => $row,
		);
		if($feeincharge == 1 || $prin == 1){
			$form['group_expulsion']['approve_selected'] = array(
				'#type' => 'submit',
				'#value' => 'Approve Selected',
				'#submit' => array('approve_selected'),
			);
			$form['group_expulsion']['approve_all'] = array(
				'#type' => 'submit',
				'#value' => 'Approve All',
				'#submit' => array('approve_all'),
			);
			$form['group_expulsion']['reject_all_expulsion'] = array(
				'#type' => 'submit',
				'#value' => 'Reject All',
				'#submit' => array('reject_all_expulsion'),
			);
		}
	}else{
		$form['group_expulsion']['msg'] = array(
			'#type' => 'markup',
			'#markup' => '<h3 style = "color:Red;">There are no pending Expulsion application.</h3>',
		);
	}
	
	if(isset($passout_row)){
		$form['group_passout']['expulsion'] = array(
			'#theme' => 'student_passout_table',
			'rows' => $passout_row,
		);
		if($feeincharge == 1 || $prin == 1){
			$form['group_passout']['approve_selected'] = array(
				'#type' => 'submit',
				'#value' => 'Approve Selected',
				'#submit' => array('approve_selected'),
			);
			$form['group_passout']['approve_all'] = array(
				'#type' => 'submit',
				'#value' => 'Approve All',
				'#submit' => array('approve_all'),
			);
			$form['group_passout']['reject_all_passout'] = array(
				'#type' => 'submit',
				'#value' => 'Reject All',
				'#submit' => array('reject_all_passout'),
			);
		}
	}else{
		$form['group_passout']['msg'] = array(
			'#type' => 'markup',
			'#markup' => '<h3 style = "color:Red;">There are no pending Passout application.</h3>',
		);
	}
	
	if(isset($withdrawal_row)){
		$form['group_withdrawal']['expulsion'] = array(
			'#theme' => 'student_passout_table',
			'rows' => $passout_row,
		);
		if($feeincharge == 1 || $prin == 1){
			$form['group_withdrawal']['approve_selected'] = array(
				'#type' => 'submit',
				'#value' => 'Approve Selected',
				'#submit' => array('approve_selected'),
			);
			$form['group_withdrawal']['approve_all'] = array(
				'#type' => 'submit',
				'#value' => 'Approve All',
				'#submit' => array('approve_all'),
			);
			$form['group_withdrawal']['reject_all_withdrawal'] = array(
				'#type' => 'submit',
				'#value' => 'Reject All',
				'#submit' => array('reject_all_withdrawal'),
			);
		}
	}else{
		$form['group_withdrawal']['msg'] = array(
			'#type' => 'markup',
			'#markup' => '<h3 style = "color:Red;">There are no pending Withdrawal application.</h3>',
		);
	}
	
	$form['group_tabs'] = array(
    '#type'     => 'horizontal_tabs',
    '#attached' => array('library' => array(array('field_group', 'horizontal-tabs'))), // Converts fieldsets into tabs
  );
 	return $form;
}

/**
 *Implementing callback function approve_selected()
 */
function approve_selected($form, &$form_state){
	
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$student_withdrawal_table = 'essa_'.$session_id.'_student_withdrawal';
	$sys_alert_table = 'essa_'.$session_id.'_system_alert';
	
	global $user;
	$fi_uid = array();
	$fee_incharge_role = db_query("SELECT * FROM role WHERE name = 'Fees Incharge'");
	foreach($fee_incharge_role as $fi_role){
		$fi_rid = $fi_role->rid;
	}
	$p_uid = array();
	$principal_role = db_query("SELECT * FROM role WHERE name = 'Principal'");
	foreach($principal_role as $p_role){
		$p_rid = $p_role->rid;
	}
	$s_uid = array();
	$staff_role = db_query("SELECT * FROM role WHERE name = 'staff'");
	foreach($staff_role as $s_role){
		$s_rid = $s_role->rid;
	}
	$a_uid = array();
	$admin_role = db_query("SELECT * FROM role WHERE name = 'administrator'");
	foreach($admin_role as $a_role){
		$a_rid = $a_role->rid;
	}
	$user_rd = array();
	$feeincharge = 0;
	$prin = 0;
	$staff = 0;
	$user_rid = db_query("SELECT * FROM users_roles WHERE uid = :u;", array(':u' => $user->uid));
	foreach($user_rid as $r){
		$user_rd[] = $r->rid;
		foreach($user_rd as $u_rid){
			if($u_rid == $fi_rid){
				$feeincharge = 1;
			}elseif($u_rid == $p_rid){
				$prin = 1;
			}elseif($u_rid == $s_rid || $u_rid == $a_rid){
				$staff = 1;
			}
			
		}
	}
	$flag = 0;
	$none = 0;
	//dsm($form_state);
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			//dsm($val);
			foreach($val as $k=>$v){
				foreach($v as $a=>$b){
					//dsm($b);
					if($b == '1'){
						//dsm($a);
						$string = explode('%',$a);
						$adm_no = $string[0];
						$req_timestamp = $string[1];
						$approve_time = date('m/d/Y h:i:s');
						$timestamp = strtotime($approve_time);
						
						$student_name = db_query("SELECT * FROM {$student_table} where adm_no = :adm;", array(':adm' => $adm_no));
						foreach($student_name as $st_name){
							$s_name = $st_name->student_name;
						}
						
						if($feeincharge == 1){
							
							$st_details = db_query("SELECT * FROM {$student_withdrawal_table} WHERE adm_no = :an AND status_timestamp = :t;", array(':an' => $adm_no, ':t' => $req_timestamp));
							foreach($st_details as $sd){
								$status = $sd->status;
								$type = $sd->type;
							}
							
							if($status = 'Approved by principal'){
								db_update($student_withdrawal_table)
								->fields(array(
									'status_fin' => 'approved',
									'fin_timestamp' => $timestamp,
									'status' => 'blocked',
									'fin_uid' => $user->uid,
									))
								->condition(db_and()
									->condition('adm_no', $adm_no)
									->condition('status_timestamp', $req_timestamp)
								)
								->execute();
								$flag = 2;
								
								if($type == 'expulsion'){
									//sending system alert
									global $user;
									$created_date = date("Y-m-d H:i:s");
									$strtodate = strtotime($created_date);
									db_insert($sys_alert_table)
									->fields(array(
										'message' => 'Expulsion Application for '.$adm_no.'-'.$s_name.' has been approved by Finanace.',
										'priority' => 'M',
										'module' => 'withdrawal',
										'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
										'timestamp' => $strtodate,
										'source_uid' => $user->uid,
									))
									->execute();
								}
								
								if($type == 'passout'){
									//sending system alert
									global $user;
									$created_date = date("Y-m-d H:i:s");
									$strtodate = strtotime($created_date);
									db_insert($sys_alert_table)
									->fields(array(
										'message' => 'Passout Application for '.$adm_no.'-'.$s_name.' has been approved by Finanace.',
										'priority' => 'M',
										'module' => 'withdrawal',
										'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
										'timestamp' => $strtodate,
										'source_uid' => $user->uid,
									))
									->execute();
								}
								
								if($type == 'withdrawal'){
									//sending system alert
									global $user;
									$created_date = date("Y-m-d H:i:s");
									$strtodate = strtotime($created_date);
									db_insert($sys_alert_table)
									->fields(array(
										'message' => 'Withdrawal Application for '.$adm_no.'-'.$s_name.' has been approved by Finanace.',
										'priority' => 'M',
										'module' => 'withdrawal',
										'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
										'timestamp' => $strtodate,
										'source_uid' => $user->uid,
									))
									->execute();
								}
								
							}else{
								db_update($student_withdrawal_table)
								->fields(array(
									'status_fin' => 'approved',
									'fin_timestamp' => $timestamp,
									'status' => 'Approved by Finance',
									'fin_uid' => $user->uid,
									))
								->condition(db_and()
									->condition('adm_no', $adm_no)
									->condition('status_timestamp', $req_timestamp)
								)
								->execute();
								$flag = 1;
								
								if($type == 'expulsion'){
									//sending system alert
									global $user;
									$created_date = date("Y-m-d H:i:s");
									$strtodate = strtotime($created_date);
									db_insert($sys_alert_table)
									->fields(array(
										'message' => 'Expulsion Application for '.$adm_no.'-'.$s_name.' has been sent to Principal for approval.',
										'priority' => 'M',
										'module' => 'withdrawal',
										'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
										'timestamp' => $strtodate,
										'source_uid' => $user->uid,
									))
									->execute();
								}elseif($type == 'passout'){
									//sending system alert
									global $user;
									$created_date = date("Y-m-d H:i:s");
									$strtodate = strtotime($created_date);
									db_insert($sys_alert_table)
									->fields(array(
										'message' => 'Passout Application for '.$adm_no.'-'.$s_name.' has been sent to Principal for approval.',
										'priority' => 'M',
										'module' => 'withdrawal',
										'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
										'timestamp' => $strtodate,
										'source_uid' => $user->uid,
									))
									->execute();
								}elseif($type == 'withdrawal'){
									//sending system alert
									global $user;
									$created_date = date("Y-m-d H:i:s");
									$strtodate = strtotime($created_date);
									db_insert($sys_alert_table)
									->fields(array(
										'message' => 'Withdrawal Application for '.$adm_no.'-'.$s_name.' has been sent to Principal for approval.',
										'priority' => 'M',
										'module' => 'withdrawal',
										'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
										'timestamp' => $strtodate,
										'source_uid' => $user->uid,
									))
									->execute();
								}
							}
							//dsm($adm_no);
							
						}elseif($prin == 1){
							//dsm($adm_no);
							$stud_info = db_query(
								"SELECT * from $student_table where adm_no = :adm_no;", array(':adm_no' => $adm_no)
							);
							foreach($stud_info as $si){
								$uid = $si->uid;
								$puid = $si->puid;
							}
							
							db_update('users')
							->fields (array(
									'status' => 0,
								))
							->condition('uid', $uid, '=')
							->execute();
							
							db_update('users')
							->fields (array(
									'status' => 0,
								))
							->condition('uid', $puid, '=')
							->execute();
							
							db_update($student_table)
							->fields (array(
									'status' => 0,
								))
							->condition('adm_no', $adm_no, '=')
							->execute();
							
							db_update($student_withdrawal_table)
							->fields(array(
								'status' => 'blocked',
								'status_uid' => $user->uid,
								))
							->condition(db_and()
								->condition('adm_no', $adm_no)
								->condition('status_timestamp', $req_timestamp)
							)
							->execute();
							$flag = 1;
							
							if($type == 'expulsion'){
								//sending system alert
								global $user;
								$created_date = date("Y-m-d H:i:s");
								$strtodate = strtotime($created_date);
								db_insert($sys_alert_table)
								->fields(array(
									'message' => 'Expulsion Application for '.$adm_no.'-'.$s_name.' has been has been approved by Principal.',
									'priority' => 'M',
									'module' => 'withdrawal',
									'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
									'timestamp' => $strtodate,
									'source_uid' => $user->uid,
								))
								->execute();
							}elseif($type == 'passout'){
								//sending system alert
								global $user;
								$created_date = date("Y-m-d H:i:s");
								$strtodate = strtotime($created_date);
								db_insert($sys_alert_table)
								->fields(array(
									'message' => 'Passout Application for '.$adm_no.'-'.$s_name.' has been has been approved by Principal.',
									'priority' => 'M',
									'module' => 'withdrawal',
									'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
									'timestamp' => $strtodate,
									'source_uid' => $user->uid,
								))
								->execute();
							}elseif($type == 'withdrawal'){
								//sending system alert
								global $user;
								$created_date = date("Y-m-d H:i:s");
								$strtodate = strtotime($created_date);
								db_insert($sys_alert_table)
								->fields(array(
									'message' => 'Withdrawal Application for '.$adm_no.'-'.$s_name.' has been has been approved by Principal.',
									'priority' => 'M',
									'module' => 'withdrawal',
									'source_url' => 'expulsion/approve/'.$adm_no.'%'.$req_timestamp,
									'timestamp' => $strtodate,
									'source_uid' => $user->uid,
								))
								->execute();
							}
						}
						
					}else{
						$none = 1;
					}
				}
				
			}
		}
	}
	if($none == 1){
		drupal_set_message('No students are selected.', 'error');
	}
	
	if($feeincharge == 1 && $flag == 1){
		if($type == 'expulsion'){
			drupal_set_message('The Expulsion Application of the selected students has been sent to Principal for approval.','status');
		}elseif($type == 'passout'){
			drupal_set_message('The Passout Application of the selected students has been sent to Principal for approval.','status');
		}elseif($type == 'withdrawal'){
			drupal_set_message('The Withdrawal Application of the selected students has been sent to Principal for approval.','status');
		}
		
	}elseif($feeincharge == 1 && $flag == 2){
		if($type == 'expulsion'){
			drupal_set_message('The Expulsion Application of the selected students has been approved.','status');
		}elseif($type == 'passout'){
			drupal_set_message('The Passout Application of the selected students has been approved.','status');
		}elseif($type == 'withdrawal'){
			drupal_set_message('The Withdrawal Application of the selected students has been approved.','status');
		}
	}elseif($prin == 1 && $flag == 1){
		if($type == 'expulsion'){
			drupal_set_message('The Expulsion Application of the selected students has been approved.','status');
		}elseif($type == 'passout'){
			drupal_set_message('The Passout Application of the selected students has been approved.','status');
		}elseif($type == 'withdrawal'){
			drupal_set_message('The Withdrawal Application of the selected students has been approved.','status');
		}
	}
}


/**
 *Implementing callback function approve_all()
 */
function approve_all($form, &$form_state){
	
	$session_id = (string)variable_get('essa_sid');
	$student_table = 'essa_'.$session_id.'_master_student_table';
	$student_withdrawal_table = 'essa_'.$session_id.'_student_withdrawal';
	
	global $user;
	$fi_uid = array();
	$fee_incharge_role = db_query("SELECT * FROM role WHERE name = 'Fees Incharge'");
	foreach($fee_incharge_role as $fi_role){
		$fi_rid = $fi_role->rid;
	}
	$p_uid = array();
	$principal_role = db_query("SELECT * FROM role WHERE name = 'Principal'");
	foreach($principal_role as $p_role){
		$p_rid = $p_role->rid;
	}
	$s_uid = array();
	$staff_role = db_query("SELECT * FROM role WHERE name = 'staff'");
	foreach($staff_role as $s_role){
		$s_rid = $s_role->rid;
	}
	$a_uid = array();
	$admin_role = db_query("SELECT * FROM role WHERE name = 'administrator'");
	foreach($admin_role as $a_role){
		$a_rid = $a_role->rid;
	}
	$user_rd = array();
	$feeincharge = 0;
	$prin = 0;
	$staff = 0;
	$user_rid = db_query("SELECT * FROM users_roles WHERE uid = :u;", array(':u' => $user->uid));
	foreach($user_rid as $r){
		$user_rd[] = $r->rid;
		foreach($user_rd as $u_rid){
			if($u_rid == $fi_rid){
				$feeincharge = 1;
			}elseif($u_rid == $p_rid){
				$prin = 1;
			}elseif($u_rid == $s_rid || $u_rid == $a_rid){
				$staff = 1;
			}
			
		}
	}
	
	$flag = 0;
	
	foreach($form_state['values'] as $val){
		if(is_array($val)){
			foreach($val as $k=>$v){
				if(!isset($v['c0'])){
					foreach($v as $a => $b){
						$string = explode('%',$a);
						$adm_no = $string[0];
						$req_timestamp = $string[1];
						$approve_time = date('m/d/Y h:i:s');
						$timestamp = strtotime($approve_time);
						
						$student_name = db_query("SELECT * FROM {$student_table} where adm_no = :adm;", array(':adm' => $adm_no));
						foreach($student_name as $st_name){
							$s_name = $st_name->student_name;
						}
						
						if($feeincharge == 1){
							$st_details = db_query("SELECT * FROM {$student_withdrawal_table} WHERE adm_no = :an AND status_timestamp = :t;", array(':an' => $adm_no, ':t' => $req_timestamp));
							foreach($st_details as $sd){
								$status = $sd->status;
							}
							
							if($status = 'Approved by principal'){
								db_update($student_withdrawal_table)
								->fields(array(
									'status_fin' => 'approved',
									'fin_timestamp' => $timestamp,
									'status' => 'blocked',
									'fin_uid' => $user->uid,
									))
								->condition(db_and()
									->condition('adm_no', $adm_no)
									->condition('status_timestamp', $req_timestamp)
								)
								->execute();
								$flag = 2;
							}else{
							
								//dsm($adm_no);
								db_update($student_withdrawal_table)
								->fields(array(
									'status_fin' => 'approved',
									'fin_timestamp' => $timestamp,
									'status' => 'Approved by Finance',
									'fin_uid' => $user->uid,
									))
								->condition(db_and()
									->condition('adm_no', $adm_no)
									->condition('status_timestamp', $req_timestamp)
								)
								->execute();
								$flag = 1;
							}
						}elseif($prin == 1){
							//dsm($adm_no);
							$stud_info = db_query(
								"SELECT * from $student_table where adm_no = :adm_no;", array(':adm_no' => $adm_no)
							);
							foreach($stud_info as $si){
								$uid = $si->uid;
								$puid = $si->puid;
							}
							
							db_update('users')
							->fields (array(
									'status' => 0,
								))
							->condition('uid', $uid, '=')
							->execute();
							
							db_update('users')
							->fields (array(
									'status' => 0,
								))
							->condition('uid', $puid, '=')
							->execute();
							
							db_update($student_table)
							->fields (array(
									'status' => 0,
								))
							->condition('adm_no', $adm_no, '=')
							->execute();
							
							db_update($student_withdrawal_table)
							->fields(array(
								'status' => 'blocked',
								'status_uid' => $user->uid,
								))
							->condition(db_and()
								->condition('adm_no', $adm_no)
								->condition('status_timestamp', $req_timestamp)
							)
							->execute();
							$flag = 1;
						}
					}
				}
				
			}
		}
	}
	if($feeincharge == 1 && $flag = 1){
		drupal_set_message('All Withdrawal Application has been sent to Principal for Approval.','status');
	}elseif($feeincharge == 1 && $flag = 2){
		drupal_set_message('The Withdrawal Application Sent for '.$adm_no.'-'.$s_name.' has been Approved.','status');
	}elseif($prin == 1){
		drupal_set_message('All Withdrawal Application has been approved.','status');
	}
}


/**
 *Implementing callback function reject_all_expulsion()
 */
function reject_all_expulsion($form, &$form_state){
	global $base_url;
	$base_url = $base_url.'/reject_all_expulsion';
	$custom_url =  (urldecode(url($base_url)));
	$form_state['redirect'] = $base_url;
}

/**
 *Implementing callback function reject_all_passout()
 */
function reject_all_passout($form, &$form_state){
	
	global $base_url;
	$base_url = $base_url.'/reject_all_passout';
	$custom_url =  (urldecode(url($base_url)));
	$form_state['redirect'] = $base_url;
}

/**
 *Implementing callback function reject_all_withdrawal()
 */
function reject_all_withdrawal($form, &$form_state){
	
	global $base_url;
	$base_url = $base_url.'/reject_all_withdrawal';
	$custom_url =  (urldecode(url($base_url)));
	$form_state['redirect'] = $base_url;
}

/**
 *Theme function student_expulsion_table()
 */
function theme_student_expulsion_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	
	global $user;
	$fi_uid = array();
	$fee_incharge_role = db_query("SELECT * FROM role WHERE name = 'Fees Incharge'");
	foreach($fee_incharge_role as $fi_role){
		$fi_rid = $fi_role->rid;
	}
	$p_uid = array();
	$principal_role = db_query("SELECT * FROM role WHERE name = 'Principal'");
	foreach($principal_role as $p_role){
		$p_rid = $p_role->rid;
	}
	$user_rd = array();
	$feeincharge = 0;
	$prin = 0;
	$user_rid = db_query("SELECT * FROM users_roles WHERE uid = :u;", array(':u' => $user->uid));
	foreach($user_rid as $r){
		$user_rd[] = $r->rid;
		foreach($user_rd as $u_rid){
			if($u_rid == $fi_rid){
				$feeincharge = 1;
			}elseif($u_rid == $p_rid){
				$prin = 1;
			}
		}
	}
	
	
	
	if($feeincharge == 1 || $prin == 1){
		$header = array(t(''),t('Admission No'),t('Student Name'), t('Class'), t('Reason'), t('Status'), t('Status Reason'),t('Application Date'),t(''),t(''));
	}else{
		$header = array(t('Admission No'),t('Student Name'), t('Class'), t('Reason'), t('Status'), t('Status Reason'),t('Application Date'));
	}
	
  
  
  // Setup the structure to be rendered and returned.
  $content = array(
    '#theme' => 'table',
    '#rows' => array(),
    '#header' => $header,
  );
  
  // Traverse each row.  @see element_chidren().
  foreach (element_children($rows) as $row_index) {
    $row = array();
    // Traverse each column in the row.  @see element_children().
    foreach (element_children($rows[$row_index]) as $col_index) {
      // Traverse each column in the row.  @see element_children().
      foreach (element_children($rows[$row_index][$col_index]) as $col_index1) {
      // Render the column form element.
        $row[] = drupal_render($rows[$row_index][$col_index][$col_index1]);
      }
    }
    // Add the row to the table.
    $content['#rows'][] = $row;
  }

  // Redner the table and return.
  return drupal_render($content);

}

/**
 *Theme function student_passout_table()
 */
function theme_student_passout_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	
	global $user;
	$fi_uid = array();
	$fee_incharge_role = db_query("SELECT * FROM role WHERE name = 'Fees Incharge'");
	foreach($fee_incharge_role as $fi_role){
		$fi_rid = $fi_role->rid;
	}
	$p_uid = array();
	$principal_role = db_query("SELECT * FROM role WHERE name = 'Principal'");
	foreach($principal_role as $p_role){
		$p_rid = $p_role->rid;
	}
	$user_rd = array();
	$feeincharge = 0;
	$prin = 0;
	$user_rid = db_query("SELECT * FROM users_roles WHERE uid = :u;", array(':u' => $user->uid));
	foreach($user_rid as $r){
		$user_rd[] = $r->rid;
		foreach($user_rd as $u_rid){
			if($u_rid == $fi_rid){
				$feeincharge = 1;
			}elseif($u_rid == $p_rid){
				$prin = 1;
			}
		}
	}
	
	if($feeincharge == 1 || $prin == 1){
		$header = array(t(''),t('Admission No'),t('Student Name'), t('Class'), t('Status'), t('Status Reason'),t('Application Date'),t(''),t(''));
	}else{
		$header = array(t('Admission No'),t('Student Name'), t('Class'), t('Status'), t('Status Reason'),t('Application Date'));
	}
	
  
  
  // Setup the structure to be rendered and returned.
  $content = array(
    '#theme' => 'table',
    '#rows' => array(),
    '#header' => $header,
  );
  
  // Traverse each row.  @see element_chidren().
  foreach (element_children($rows) as $row_index) {
    $row = array();
    // Traverse each column in the row.  @see element_children().
    foreach (element_children($rows[$row_index]) as $col_index) {
      // Traverse each column in the row.  @see element_children().
      foreach (element_children($rows[$row_index][$col_index]) as $col_index1) {
      // Render the column form element.
        $row[] = drupal_render($rows[$row_index][$col_index][$col_index1]);
      }
    }
    // Add the row to the table.
    $content['#rows'][] = $row;
  }

  // Redner the table and return.
  return drupal_render($content);

}
