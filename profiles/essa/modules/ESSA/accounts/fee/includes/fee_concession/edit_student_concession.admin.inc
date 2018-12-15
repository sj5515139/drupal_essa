<?php
/**
 *Implements page callback function edit_student_concession
 */
function edit_student_concession($form = array(), &$form_state){
	$session = (string)variable_get('essa_sid');
	$concession_table = 'essa_'.$session.'_fees_concession';
  
  $form['adm_no'] = array(
    '#type' => 'textfield',
    '#title' => t('Admission No.'),
    '#autocomplete_path' => 'adm_no/autocomplete',
    '#size' => 30,
		'#id' => 'adm_no',
    '#required' => TRUE,
  );
	
	$options = array();
  $concession = db_query("
		SELECT * from {$concession_table}"
	);
	foreach($concession as $con){
		$options[] = $con->name;
	}
  $form['con_type'] = array(
    '#type' => 'select',
    '#title' => 'Select concession type',
    '#options' => drupal_map_assoc($options),
    '#ajax' => array(
      'event' => 'change',
      'callback' => 'display_con',
      'wrapper' => 'con',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#required' => TRUE,
  );
  
  $form['fs'] = array(
    '#type' => 'fieldset',
    '#prefix' => '<div id = "con">',
    '#suffix' => '</div>',
  );
  $form['fs']['amount'] = array(
    '#type' => 'textfield',
    '#title' => 'Amount',
    '#size' => 10,
  );
  $form['fs']['percent'] = array(
    '#type' => 'textfield',
    '#title' => 'Percent',
    '#size' => 10,
  );
  
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => 'Save'
  );
	
	$form['delete'] = array(
    '#type' => 'submit',
    '#value' => 'Delete',
		'#submit' => array('delete_stud_con'),
  );
	
	return $form;
}

function delete_stud_con($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session_id.'_fees_student_concession';
	$concession_table = 'essa_'.$session_id.'_fees_concession';
	$fees_student_table = 'essa_'.$session_id.'_fees_student';
	$student_due_table = 'essa_'.$session_id.'_fees_student_due';
	$fee_structure = 'essa_'.$session_id.'_fees_structure';
	
	$concession = db_query("
		SELECT * from {$student_concession_table} where adm_no = :an and name = :n", array(':an' => $form_state['values']['adm_no'], ':n' => $form_state['values']['con_type'])
	);
	foreach($concession as $con){
		$con_id = $con->con_id;
	}
	db_delete($student_concession_table)
		->condition('con_id', $con_id)
		->condition('adm_no', $form_state['values']['adm_no'])
		->execute();
	
	$con_fee = db_query("
		SELECT * from {$concession_table} where con_id = :ci", array(':ci' => $con_id)
	);
	foreach($con_fee as $cf){
		$fee_id = $cf->fee_id;
	}
	
	$fee_amount = db_query("
    SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
  );
  foreach($fee_amount as $fa){
    $amt = $fa->amount;
  }
	
	$session = (string)variable_get('essa_sid');
	$fees_frequency = 'essa_'.$session.'_fees_frequency';
	
	$fee_freq = db_query("
		SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
	);
	foreach($fee_freq as $ff){
		$freq_id = $ff->freq_id;
	}
	
	$results = db_select($fees_frequency, 'n')
		->fields('n')
		->condition('freq_id', $freq_id, '=')
		->execute();
	$freq = $results->fetchAssoc();
	
	foreach($freq as $key=>$fr){
		if($fr != NULL && $key != 'freq_id' && $key != 'freq_name'){
			db_merge($fees_student_table)
				->key(array('fee_id' => $fee_id, 'adm_no' => $form_state['values']['adm_no']))
				->fields (array(
					$key => $amt,
				)
			)		
			->execute();
						
			db_merge($student_due_table)
				->key(array('fee_id' => $fee_id, 'adm_no' => $form_state['values']['adm_no']))
				->fields (array(
					$key => $amt,
				)
			)		
			->execute();
	}
}

function display_con($form, &$form_state){
  $session = (string)variable_get('essa_sid');
	$concession_table = 'essa_'.$session.'_fees_student_concession';
  $concession = db_query("
		SELECT * from {$concession_table} where adm_no = :an and name = :n", array(':an' => $form_state['values']['adm_no'], ':n' => $form_state['values']['con_type'])
	);
	foreach($concession as $con){
		$amount = $con->amount;
    $percent = $con->percentage;
	}
  $form['fs']['amount']['#value'] = $amount;
  $form['fs']['percent']['#value'] = $percent;
  if($amount != NULL){
    return $form['fs'];
  }else{
    return $form['fs'];
  }
}

function edit_student_concession_submit($form, &$form_state){
  $session = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
  $fee_structure = 'essa_'.$session.'_fees_structure';
  
  $concession = db_query("
		SELECT * from {$concession_table} where name = :n", array(':n' => $form_state['values']['con_type'])
	);
	foreach($concession as $con){
    $con_id = $con->con_id;
		$con_name = $con->name;
		$fee_id = $con->fee_id;
  }
  db_merge($student_concession_table)
		->key(array('con_id' => $con_id, 'adm_no' => $form_state['values']['adm_no']))
		->fields (array(
			'con_id' => $con_id,
			'adm_no' => $form_state['values']['adm_no'],
			'name' =>  $con_name,
			'amount' => $form_state['values']['amount']?$form_state['values']['amount']:NULL,
			'percentage' => $form_state['values']['percent']?$form_state['values']['percent']:NULL,
		)
	)	
	->execute();
	
	$session = (string)variable_get('essa_sid');
	$student_concession_table = 'essa_'.$session.'_fees_student_concession';
	$fees_frequency = 'essa_'.$session.'_fees_frequency';
	$fees_student_table = 'essa_'.$session.'_fees_student';
	$student_due_table = 'essa_'.$session.'_fees_student_due';
  $concession_table = 'essa_'.$session.'_fees_concession';
	
	$fee_freq = db_query("
		SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
	);
	foreach($fee_freq as $ff){
		$freq_id = $ff->amount;
	}
	
	$results = db_select($fees_frequency, 'n')
		->fields('n')
		->condition('freq_id', $freq_id, '=')
		->execute();
	$freq = $results->fetchAssoc();
  
	$student_concession = db_query("
		SELECT * from {$fees_student_table} where adm_no = :an and fee_id = :fi", array(':an' => $form_state['values']['adm_no'], ':fi' => $fee_id)
	);
	foreach($student_concession as $sc){
    foreach($freq as $key=>$fr){
				$fee_amount = db_query("
				  SELECT * from {$fee_structure} where fee_id = :fi", array(':fi' => $fee_id)
				);
				foreach($fee_amount as $fa){
				  $amt = $fa->amount;
				}
				if($fr != NULL && $key != 'freq_id' && $key != 'freq_name'){
					if($form_state['values']['amount'] != NULL){
						$new_amt = $amt - $form_state['values']['amount'];	
					}else{
						$new_amt = $amt - ($form_state['values']['percent']/100)*$amt;
					}
					
					db_merge($fees_student_table)
						->key(array('fee_id' => $fee_id, 'adm_no' => $form_state['values']['adm_no']))
						->fields (array(
							$key => $new_amt,
							'concession' => NULL,
						)
					)		
					->execute();
					
					db_merge($student_due_table)
						->key(array('fee_id' => $fee_id, 'adm_no' => $form_state['values']['adm_no']))
						->fields (array(
							$key => $new_amt,
						)
					)		
					->execute();
				}
			}
		}
  }
}