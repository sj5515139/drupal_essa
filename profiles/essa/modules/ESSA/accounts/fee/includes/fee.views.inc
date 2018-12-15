<?php

/**
 *Implements hook_views_data().
 */
function fee_views_data() {
  $session_id = (string)variable_get('essa_sid');
  
  //-------------------------------------------------------------Fee Frequency------------------------------------------------------------
  $data['essa_'.$session_id.'_fees_frequency']['table']['group'] = t('Fee Frequencies');
  
  $data['essa_'.$session_id.'_fees_frequency']['table']['base'] = array(
    'field' => 'freq_id',
    'title' => t('Fee Frequencies'), 
    'help' => t('This View contains the all the types of frequencies for fee collection, along with the due dates.'), 
    'weight' => -10,
  );
  
	$data['essa_'.$session_id.'_fees_frequency']['freq_id'] = array(
    'title' => t('Frequency ID'), 
    'help' => t('Frequency ID.'), 
    'field' => array(
        'handler' => 'views_handler_field_node',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
  );
	
  $data['essa_'.$session_id.'_fees_frequency']['freq_name'] = array(
    'title' => t('Frequency'), 
    'help' => t('Frequency Type.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
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
		$columns[] = $dt->format("M_Y");
	}
	foreach($columns as $col){
		$data['essa_'.$session_id.'_fees_frequency'][$col] = array(
      'title' => t($col), 
      'help' => t('This contains the due date for each month.'), 
      'field' => array(
			    'handler' => 'views_handler_field_date',
			),
			'sort' => array(
			    'handler' => 'views_handler_sort_date',
			),
			'filter' => array(
		    'handler' => 'views_handler_filter_date',
			),
    );
	}
  
  //-------------------------------------------------------------Fee Structure------------------------------------------------------------
  $data['essa_'.$session_id.'_fees_structure']['table']['group'] = t('Fee Structure');
  
  $data['essa_'.$session_id.'_fees_structure']['table']['base'] = array(
    'field' => 'fee_id',
    'title' => t('Fee Structure'), 
    'help' => t('This View contains the all the types of fees details.'), 
    'weight' => -10,
  );
  
  $data['essa_'.$session_id.'_fees_structure']['fee_id'] = array(
    'title' => t('Fee Id'), 
    'help' => t('Fee IDs.'),
		'field' => array(
        'handler' => 'views_handler_field_node',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_structure']['particulars'] = array(
    'title' => t('Particulars'), 
    'help' => t('Particulars.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_structure']['freq_id'] = array(
    'title' => t('Freq ID'), 
    'help' => t('Freq ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
		'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_frequency',
      'base field' => 'freq_id', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Frequency'),
    ),
  );
  
  $data['essa_'.$session_id.'_fees_structure']['frequency'] = array(
    'title' => t('Frequency'), 
    'help' => t('Frequency.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_structure']['amount'] = array(
    'title' => t('Amount'), 
    'help' => t('Amount.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_structure']['applies_to'] = array(
    'title' => t('Applies to'), 
    'help' => t('Applies to.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_structure']['facility'] = array(
    'title' => t('Facility'), 
    'help' => t('Facility.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_structure']['is_hostel'] = array(
    'title' => t('Is Hostel'), 
    'help' => t('Is Hostel.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_structure']['class_from'] = array(
    'title' => t('Class From'), 
    'help' => t('Class From.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_structure']['class_to'] = array(
    'title' => t('Class To'), 
    'help' => t('Class To.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_structure']['distance_from'] = array(
    'title' => t('Distance From'), 
    'help' => t('Distance From.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_structure']['distance_to'] = array(
    'title' => t('Distance To'), 
    'help' => t('Distance To.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_structure']['optional_sub'] = array(
    'title' => t('Optional Subject'), 
    'help' => t('Optional Subject.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  //-------------------------------------------------------------Fee Student------------------------------------------------------------
  $data['essa_'.$session_id.'_fees_student']['table']['group'] = t('Fee Student');
  
  $data['essa_'.$session_id.'_fees_student']['table']['base'] = array(
    'field' => 'fee_id',
    'title' => t('Fee Student'), 
    'help' => t('This View contains the student fee linkage.'), 
    'weight' => -10,
  );
	
	$data['essa_'.$session_id.'_fees_student_due']['table']['join'] = array(
    'essa_'.$session_id.'_fees_student_due' => array(
      'left_field' => 'fee_id',
      'field' => 'fee_id',
    ),
		'essa_'.$session_id.'_fees_student_due' => array(
      'left_field' => 'adm_no',
      'field' => 'adm_no',
    ),
	);
  
  $data['essa_'.$session_id.'_fees_student']['fee_id'] = array(
    'title' => t('Fee Id'), 
    'help' => t('Fee IDs.'),
		'field' => array(
        'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
    'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_student_due',
      'base field' => 'fee_id', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Due'),
    ),
  );
  
  $data['essa_'.$session_id.'_fees_student']['adm_no'] = array(
    'title' => t('Admission No.'), 
    'help' => t('Admission No.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
		/*'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_student_due',
      'base field' => 'adm_no', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Due'),
    ),*/
  );
	
	$data['essa_'.$session_id.'_fees_student']['concession'] = array(
    'title' => t('Concession'), 
    'help' => t('Concession.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
	/*
  $data['essa_'.$session_id.'_fees_student']['fee_id'] = array(
    'title' => t('Fee ID.'), 
    'help' => t('Fee ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  */
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
		$columns[] = $dt->format("M_Y");
	}
	foreach($columns as $col){
		$data['essa_'.$session_id.'_fees_student'][$col] = array(
      'title' => t($col.'-amt'), 
      'help' => t('This contains the due date for each month.'), 
      'field' => array(
        'handler' => 'views_handler_field', 
        'click sortable' => TRUE,
      ), 
      'sort' => array(
        'handler' => 'views_handler_sort',
      ), 
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ), 
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
    );
	}
  
  //-------------------------------------------------------------Fee Student Payment------------------------------------------------------------
  $data['essa_'.$session_id.'_fees_student_payment']['table']['group'] = t('Fee Student Payment');
  
  $data['essa_'.$session_id.'_fees_student_payment']['table']['base'] = array(
    'field' => 'fee_id',
    'title' => t('Fee Student Payment'), 
    'help' => t('This View contains the student fee linkage.'), 
    'weight' => -10,
  );
  
  $data['essa_'.$session_id.'_fees_student_payment']['fee_id'] = array(
    'title' => t('Fee ID'), 
    'help' => t('Fee ID.'),
		'field' => array(
        'handler' => 'views_handler_field_node',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
    'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_structure',
      'base field' => 'fee_id', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Structure'),
    ),
  );
  
  $data['essa_'.$session_id.'_fees_student_payment']['adm_no'] = array(
    'title' => t('Admission No.'), 
    'help' => t('Admission No.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
		'relationship' => array(
        'base' => 'essa_'.$session_id.'_master_student_table',
        'field' => 'adm_no',
        'handler' => 'views_handler_relationship',
        'label' => t('Student Table'),
    ),
  );
	
	$data['essa_'.$session_id.'_fees_student_payment']['receipt_no'] = array(
    'title' => t('Receipt No.'), 
    'help' => t('Receipt No.'), 
    'field' => array(
	    'handler' => 'views_handler_field_numeric',
		),
		'sort' => array(
			'handler' => 'views_handler_sort_numeric',
		),
		'filter' => array(
		  'handler' => 'views_handler_filter_numeric',
		),
		'relationship' => array(
        'base' => 'essa_'.$session_id.'_fees_payment_history',
        'field' => 'receipt_no',
        'handler' => 'views_handler_relationship',
        'label' => t('Payment Table'),
    ),
  );
	
	$data['essa_'.$session_id.'_fees_student_payment']['month'] = array(
    'title' => t('Month'), 
    'help' => t('Month.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
	
	$data['essa_'.$session_id.'_fees_student_payment']['amount'] = array(
    'title' => t('Amount'), 
    'help' => t('This contains the amount for each month.'), 
    'field' => array(
	    'handler' => 'views_handler_field_numeric',
		),
		'sort' => array(
			'handler' => 'views_handler_sort_numeric',
		),
		'filter' => array(
		  'handler' => 'views_handler_filter_numeric',
		),
  );
		
	/*
  $data['essa_'.$session_id.'_fees_student_payment']['fee_id'] = array(
    'title' => t('Fee ID.'), 
    'help' => t('Fee ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
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
		$columns[] = $dt->format("M_Y");
	}
	foreach($columns as $col){
		$data['essa_'.$session_id.'_fees_student_payment'][$col] = array(
      'title' => t($col), 
      'help' => t('This contains the due date for each month.'), 
      'field' => array(
        'handler' => 'views_handler_field', 
        'click sortable' => TRUE,
      ), 
      'sort' => array(
        'handler' => 'views_handler_sort',
      ), 
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ), 
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    );
    $data['essa_'.$session_id.'_fees_student_payment'][$col.'_payment_date'] = array(
      'title' => t('Payment Date -'.$col), 
      'help' => t('This contains the due date for each month.'), 
      'field' => array(
			    'handler' => 'views_handler_field_date',
			),
			'sort' => array(
			    'handler' => 'views_handler_sort_date',
			),
			'filter' => array(
		    'handler' => 'views_handler_filter_date',
			),
    );
		$data['essa_'.$session_id.'_fees_student_payment'][$col.'_payment_id'] = array(
      'title' => t('Payment ID -'.$col), 
      'help' => t('This contains the due date for each month.'), 
      'field' => array(
		    'handler' => 'views_handler_field_node',
			),
			'sort' => array(
			    'handler' => 'views_handler_sort',
			),
			'filter' => array(
			    'handler' => 'views_handler_filter_numeric',
			),
			'relationship' => array(
			  'base' => 'essa_'.$session_id.'_fees_payment_history',
			  'base field' => 'id', // The name of the field on the joined table.
			  'handler' => 'views_handler_relationship', 
			  'label' => t('Reciept No.'.$col),
			),
    );
	}
  */
  //-------------------------------------------------------------Fee Student Due------------------------------------------------------------
  $data['essa_'.$session_id.'_fees_student_due']['table']['group'] = t('Fee Student Due');
  
  $data['essa_'.$session_id.'_fees_student_due']['table']['base'] = array(
    'field' => 'fee_id',
    'title' => t('Fee Student Due'), 
    'help' => t('This View contains the student fee linkage.'), 
    'weight' => -10,
  );
	
	$data['essa_'.$session_id.'_fees_student_due']['table']['join'] = array(
    'essa_'.$session_id.'_fees_structure' => array(
      'left_field' => 'fee_id',
      'field' => 'fee_id',
    ),
		'essa_'.$session_id.'_master_student_table' => array(
      'left_field' => 'adm_no',
      'field' => 'adm_no',
    ),
	);
  
	
	$data['essa_'.$session_id.'_fees_student_due']['fee_id'] = array(
    'title' => t('Fee ID'),
    'help' => t('The Fee ID.'),
    'field' => array(
        'handler' => 'views_handler_field_node',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
    'relationship' => array(
        'base' => 'essa_'.$session_id.'_fees_structure',
        'field' => 'fee_id',
        'handler' => 'views_handler_relationship',
        'label' => t('Fee Structure'),
    ),
	);
	
	/*
	$data['essa_'.$session_id.'_fees_student_due']['adm_no'] = array(
    'title' => t('Adm No'),
    'help' => t('The Adm No.'),
    'field' => array(
        'handler' => 'views_handler_field_node',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_string',
    ),
    'relationship' => array(
        'base' => 'essa_'.$session_id.'_master_student_table',
        'field' => 'adm_no',
        'handler' => 'views_handler_relationship',
        'label' => t('Student Table'),
    ),
	);

	/*
  $data['essa_'.$session_id.'_fees_student_due']['fee_id'] = array(
    'title' => t('IDs'), 
    'help' => t('IDs.'),
    'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_structure',
      'base field' => 'fee_id', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Structure'),
    ),
  );
  */
  $data['essa_'.$session_id.'_fees_student_due']['adm_no'] = array(
    'title' => t('Admission No.'), 
    'help' => t('Admission No.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'relationship' => array(
        'base' => 'essa_'.$session_id.'_master_student_table',
        'field' => 'adm_no',
        'handler' => 'views_handler_relationship',
        'label' => t('Student Table'),
    ),
  );
	
	$data['essa_'.$session_id.'_fees_student_due']['fee_id']['adm_no'] = array(
    'title' => t('Fee ID'),
    'help' => t('The Fee ID.'),
    'field' => array(
        'handler' => 'views_handler_field_node',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
    'relationship' => array(
        'base' => 'essa_'.$session_id.'_fees_student',
        'field' => array('fee_id','adm_no'),
        'handler' => 'views_handler_relationship',
        'label' => t('Fee Structure'),
    ),
	);
	
	/*
  $data['essa_'.$session_id.'_fees_student_due']['fee_id'] = array(
    'title' => t('Fee ID.'), 
    'help' => t('Fee ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  */
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
		$columns[] = $dt->format("M_Y");
	}
	foreach($columns as $col){
		$data['essa_'.$session_id.'_fees_student_due'][$col] = array(
      'title' => t($col), 
      'help' => t('This contains the due date for each month.'), 
      'field' => array(
        'handler' => 'views_handler_field_numeric', 
        'click sortable' => TRUE,
      ), 
      'sort' => array(
        'handler' => 'views_handler_sort',
      ), 
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ), 
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
    );
	}
  
  //-------------------------------------------------------------Fee Student Fine------------------------------------------------------------
  $data['essa_'.$session_id.'_fees_student_fine']['table']['group'] = t('Fee Student Fine');
  
  $data['essa_'.$session_id.'_fees_student_fine']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Fee Student Fine'), 
    'help' => t('This View contains the student fee linkage.'), 
    'weight' => -10,
  );
  
  $data['essa_'.$session_id.'_fees_student_fine']['id'] = array(
    'title' => t('IDs'), 
    'help' => t('IDs.'),
    'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_student',
      'base field' => 'id', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Student'),
    ),
  );
  
  $data['essa_'.$session_id.'_fees_student_fine']['adm_no'] = array(
    'title' => t('Admission No.'), 
    'help' => t('Admission No.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_student_fine']['fee_id'] = array(
    'title' => t('Fee ID.'), 
    'help' => t('Fee ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
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
		$columns[] = $dt->format("M_Y");
	}
	foreach($columns as $col){
		$data['essa_'.$session_id.'_fees_student_fine'][$col] = array(
      'title' => t($col), 
      'help' => t('This contains the due date for each month.'), 
      'field' => array(
        'handler' => 'views_handler_field', 
        'click sortable' => TRUE,
      ), 
      'sort' => array(
        'handler' => 'views_handler_sort',
      ), 
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ), 
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    );
	}
  
  //-------------------------------------------------------------Fee Payment History------------------------------------------------------------
  $data['essa_'.$session_id.'_fees_payment_history']['table']['group'] = t('Fee Payment History');
  
  $data['essa_'.$session_id.'_fees_payment_history']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Fee Payment History'), 
    'help' => t('This View contains the student fee linkage.'), 
    'weight' => -10,
  );
  
	$data['essa_'.$session_id.'_fees_payment_history']['id'] = array(
    'title' => t('ID'), 
    'help' => t('ID.'), 
    'field' => array(
        'handler' => 'views_handler_field_node',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
  );
	
	/*
  $data['essa_'.$session_id.'_fees_payment_history']['id'] = array(
    'title' => t('IDs'), 
    'help' => t('IDs.'),
    'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_student_payment',
      'base field' => 'id', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Student'),
    ),
  );
  */
  $data['essa_'.$session_id.'_fees_payment_history']['adm_no'] = array(
    'title' => t('Admission No.'), 
    'help' => t('Admission No.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
		'relationship' => array(
        'base' => 'essa_'.$session_id.'_master_student_table',
        'field' => 'adm_no',
        'handler' => 'views_handler_relationship',
        'label' => t('Student Table'),
    ),
  );
  
  $data['essa_'.$session_id.'_fees_payment_history']['payment_date'] = array(
    'title' => t('Payment Date'), 
    'help' => t('Payment Date.'), 
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'date_views_filter_handler_simple',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_payment_history']['amount'] = array(
    'title' => t('Amount'), 
    'help' => t('Amount.'), 
    'field' => array(
        'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
  );
	
	$data['essa_'.$session_id.'_fees_payment_history']['uid'] = array(
    'title' => t('UID'), 
    'help' => t('UID.'), 
    'field' => array(
        'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
		'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_staff',
      'base field' => 'uid', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Staff'),
    ),
  );
	
	$data['essa_'.$session_id.'_fees_payment_history']['edit_uid'] = array(
    'title' => t('Edit UID'), 
    'help' => t('Edit UID.'), 
    'field' => array(
        'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
		'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_staff',
      'base field' => 'uid', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Edit Staff'),
    ),
  );
  
  //-------------------------------------------------------------Fee Concession------------------------------------------------------------
  $data['essa_'.$session_id.'_fees_concession']['table']['group'] = t('Fee Concession');
  
  $data['essa_'.$session_id.'_fees_concession']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Fee Concession'), 
    'help' => t('This View contains the student fee linkage.'), 
    'weight' => -10,
  );
  
  $data['essa_'.$session_id.'_fees_concession']['con_id'] = array(
    'title' => t('IDs'), 
    'help' => t('IDs.'),
		'field' => array(
        'handler' => 'views_handler_field_node',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_concession']['name'] = array(
    'title' => t('Name'), 
    'help' => t('Concession Name.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_concession']['fee_id'] = array(
    'title' => t('Fee ID'), 
    'help' => t('Fee ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
		'relationship' => array(
        'base' => 'essa_'.$session_id.'_fees_student_due',
        'field' => 'fee_id',
        'handler' => 'views_handler_relationship',
        'label' => t('Student Due'),
    ),
  );
  
	$data['essa_'.$session_id.'_fees_concession']['amount'] = array(
    'title' => t('Amount'), 
    'help' => t('Amount.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'field' => array(
        'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_concession']['percentage'] = array(
    'title' => t('Percentage'), 
    'help' => t('Percentage.'), 
    'field' => array(
        'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
  );
	
  $data['essa_'.$session_id.'_fees_concession']['concession_desc'] = array(
    'title' => t('Concession Description'), 
    'help' => t('Concession Description.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  //-------------------------------------------------------------Fee Student Concession------------------------------------------------------------
  $data['essa_'.$session_id.'_fees_student_concession']['table']['group'] = t('Fee Student Concession');
  
  $data['essa_'.$session_id.'_fees_student_concession']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Fee Student Concession'), 
    'help' => t('This View contains the student fee linkage.'), 
    'weight' => -10,
  );
  
  $data['essa_'.$session_id.'_fees_student_concession']['con_id'] = array(
    'title' => t('IDs'), 
    'help' => t('IDs.'),
		'field' => array(
        'handler' => 'views_handler_field_node',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
    'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_concession',
      'base field' => 'con_id', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Concession'),
    ),
  );
  
  $data['essa_'.$session_id.'_fees_student_concession']['adm_no'] = array(
    'title' => t('Admission No'), 
    'help' => t('Admission No.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
		'relationship' => array(
        'base' => 'essa_'.$session_id.'_master_student_table',
        'field' => 'adm_no',
        'handler' => 'views_handler_relationship',
        'label' => t('Student Table'),
    ),
  );
  
  $data['essa_'.$session_id.'_fees_student_concession']['amount'] = array(
    'title' => t('Amount'), 
    'help' => t('Amount.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'field' => array(
        'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_student_concession']['percentage'] = array(
    'title' => t('Percentage'), 
    'help' => t('Percentage.'), 
    'field' => array(
        'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
  );
  
  //-------------------------------------------------------------Fee Exemption------------------------------------------------------------
  $data['essa_'.$session_id.'_fees_student_adjustement']['table']['group'] = t('Fee Exemption');
  
  $data['essa_'.$session_id.'_fees_student_adjustement']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Fee Exemption'), 
    'help' => t('This View contains the student fee linkage.'), 
    'weight' => -10,
  );
  
  $data['essa_'.$session_id.'_fees_student_adjustement']['id'] = array(
    'title' => t('IDs'), 
    'help' => t('IDs.'),
    'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_student',
      'base field' => 'id', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Student'),
    ),
  );
  
  $data['essa_'.$session_id.'_fees_student_adjustement']['adm_no'] = array(
    'title' => t('Admission No'), 
    'help' => t('Admission No.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
		'relationship' => array(
        'base' => 'essa_'.$session_id.'_master_student_table',
        'field' => 'adm_no',
        'handler' => 'views_handler_relationship',
        'label' => t('Student Table'),
    ),
  );
  
  $data['essa_'.$session_id.'_fees_student_adjustement']['to_fee_id'] = array(
    'title' => t('Fee ID'), 
    'help' => t('Fee ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
		'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_structure',
      'base field' => 'fee_id', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Structure'),
    ),
  );
  
  $data['essa_'.$session_id.'_fees_student_adjustement']['month'] = array(
    'title' => t('Month'), 
    'help' => t('Month.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_student_adjustement']['amount'] = array(
    'title' => t('Amount'), 
    'help' => t('Amount.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  
	$data['essa_'.$session_id.'_fees_student_adjustement']['reason'] = array(
    'title' => t('Reason'), 
    'help' => t('Reason.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
	
	$data['essa_'.$session_id.'_fees_student_adjustement']['uid'] = array(
    'title' => t('UID'), 
    'help' => t('UID.'), 
    'field' => array(
        'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
		'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_staff',
      'base field' => 'uid', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Staff'),
    ),
  );
	
	$data['essa_'.$session_id.'_fees_student_adjustement']['edit_uid'] = array(
    'title' => t('Edit UID'), 
    'help' => t('Edit UID.'), 
    'field' => array(
        'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_numeric',
    ),
		'relationship' => array(
      'base' => 'essa_'.$session_id.'_fees_staff',
      'base field' => 'uid', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship', 
      'label' => t('Fee Edit Staff'),
    ),
  );
	
	//-------------------------------------------------------------Fee staff------------------------------------------------------------
  $data['essa_'.$session_id.'_fees_staff']['table']['group'] = t('Fees Staff');
  
  $data['essa_'.$session_id.'_fees_staff']['table']['base'] = array(
    'field' => 'uid',
    'title' => t('Fee Staff'), 
    'help' => t('This View contains the student fee linkage.'), 
    'weight' => -10,
  );
  
  $data['essa_'.$session_id.'_fees_staff']['uid'] = array(
    'title' => t('Staff UID'), 
    'help' => t('Staff UID.'),
  );
  
  $data['essa_'.$session_id.'_fees_staff']['emp_id'] = array(
    'title' => t('Emp ID'), 
    'help' => t('Emp ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_staff']['type'] = array(
    'title' => t('Fee ID'), 
    'help' => t('Fee ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_staff']['name'] = array(
    'title' => t('Name'), 
    'help' => t('Name.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_staff']['phone_no'] = array(
    'title' => t('Phone No.'), 
    'help' => t('Phone no.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
	$data['essa_'.$session_id.'_fees_staff']['email_id'] = array(
    'title' => t('Email ID'), 
    'help' => t('Email ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
	
	//-------------------------------------------------------------Fee staff------------------------------------------------------------
  $data['essa_'.$session_id.'_fees_staff']['table']['group'] = t('Fees Edit Staff');
  
  $data['essa_'.$session_id.'_fees_staff']['table']['base'] = array(
    'field' => 'uid',
    'title' => t('Fee Edit Staff'), 
    'help' => t('This View contains the student fee linkage.'), 
    'weight' => -10,
  );
  
  $data['essa_'.$session_id.'_fees_staff']['uid'] = array(
    'title' => t('Staff UID'), 
    'help' => t('Staff UID.'),
  );
  
  $data['essa_'.$session_id.'_fees_staff']['emp_id'] = array(
    'title' => t('Emp ID'), 
    'help' => t('Emp ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_staff']['type'] = array(
    'title' => t('Fee ID'), 
    'help' => t('Fee ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_staff']['name'] = array(
    'title' => t('Name'), 
    'help' => t('Name.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['essa_'.$session_id.'_fees_staff']['phone_no'] = array(
    'title' => t('Phone No.'), 
    'help' => t('Phone no.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
	$data['essa_'.$session_id.'_fees_staff']['email_id'] = array(
    'title' => t('Email ID'), 
    'help' => t('Email ID.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
	
  return $data;
}
