<?php
/**
 * Implements hook_views_data().
 */
function withdrawal_views_data(){
	$session_id = (string)variable_get('essa_sid');
	$student_withdrawal_table = 'essa_'.$session_id.'_student_withdrawal';
  $data = array();
	$data[$student_withdrawal_table]['table']['group'] = t('Withdrawal Students');
  $data[$student_withdrawal_table]['table']['base'] = array(
		'field' => 'adm_no',
    'title' => t('Admission No.'),
    'help' => t('This view contains the details of withdrawal students.'),
  );
  
  // The Adm_no field
	$data[$student_withdrawal_table]['adm_no'] = array(
		'title' => t('Admission No'),
		'help' => t('Admission No.'),
		'field' => array(
			'handler' => 'views_handler_field_numeric',
			'click sortable' => true,
		),
		'sort' => array(
			'handler' => 'views_handler_sort_string',
		),
		'filter' => array(
			'handler' => 'views_handler_filter_string',
		),
	);

	// The Type field
	$data[$student_withdrawal_table]['type'] = array(
		'title' => t('Type'),
		'help' => t('Type.'),
		'field' => array(
			'handler' => 'views_handler_field',
			'click sortable' => false,
		),
		'sort' => array(
			'handler' => 'views_handler_sort_string',
		),
		'filter' => array(
			'handler' => 'views_handler_filter_string',
		),
	);
	
	// The Subject field
	$data[$student_withdrawal_table]['subject'] = array(
		'title' => t('Subject'),
		'help' => t('Subject.'),
		'field' => array(
			'handler' => 'views_handler_field',
			'click sortable' => false,
		),
		'sort' => array(
			'handler' => 'views_handler_sort_string',
		),
		'filter' => array(
			'handler' => 'views_handler_filter_string',
		),
	);

	// The Reason field
	$data[$student_withdrawal_table]['reason'] = array(
		'title' => t('Reason'),
		'help' => t('Reason.'),
		'field' => array(
			'handler' => 'views_handler_field',
			'click sortable' => false,
		),
		'sort' => array(
			'handler' => 'views_handler_sort_string',
		),
		'filter' => array(
			'handler' => 'views_handler_filter_string',
		),
	);
	
	// The status_fin field
	$data[$student_withdrawal_table]['status_fin'] = array(
		'title' => t('Finanace Status'),
		'help' => t('Finanace Status.'),
		'field' => array(
			'handler' => 'views_handler_field',
			'click sortable' => false,
		),
		'sort' => array(
			'handler' => 'views_handler_sort_string',
		),
		'filter' => array(
			'handler' => 'views_handler_filter_string',
		),
	);
	
	// The status_fin_reason field
	$data[$student_withdrawal_table]['status_fin_reason'] = array(
		'title' => t('Finanace Reason'),
		'help' => t('Finanace Reason.'),
		'field' => array(
			'handler' => 'views_handler_field',
			'click sortable' => false,
		),
		'sort' => array(
			'handler' => 'views_handler_sort_string',
		),
		'filter' => array(
			'handler' => 'views_handler_filter_string',
		),
	);
	
	// The fin_timestamp field
	$data[$student_withdrawal_table]['fin_timestamp'] = array(
		'title' => t('Finanace Date'),
		'help' => t('Finanace Date.'),
		'field' => array(
			'handler' => 'views_handler_field_date',
			'click sortable' => false,
		),
		'sort' => array(
			'handler' => 'views_handler_sort_date',
		),
		'filter' => array(
			'handler' => 'views_handler_filter_date',
		),
	);
	
	// The fin_uid field
	$data[$student_withdrawal_table]['fin_uid'] = array(
		'title' => t('Finanace UID'),
		'help' => t('Finanace UID.'),
		'field' => array(
			'handler' => 'views_handler_field',
			'click sortable' => false,
		),
		'sort' => array(
			'handler' => 'views_handler_sort_string',
		),
		'filter' => array(
			'handler' => 'views_handler_filter_string',
		),
	);
	
	// The status field
	$data[$student_withdrawal_table]['status'] = array(
		'title' => t('Status'),
		'help' => t('Status.'),
		'field' => array(
			'handler' => 'views_handler_field',
			'click sortable' => false,
		),
		'sort' => array(
			'handler' => 'views_handler_sort_string',
		),
		'filter' => array(
			'handler' => 'views_handler_filter_string',
		),
	);
	
	// The status_reason field
	$data[$student_withdrawal_table]['status_reason'] = array(
		'title' => t('Status Reason'),
		'help' => t('Status Reason.'),
		'field' => array(
			'handler' => 'views_handler_field',
			'click sortable' => false,
		),
		'sort' => array(
			'handler' => 'views_handler_sort_string',
		),
		'filter' => array(
			'handler' => 'views_handler_filter_string',
		),
	);
	
	// The status_timestamp field
	$data[$student_withdrawal_table]['status_timestamp'] = array(
		'title' => t('Status Date'),
		'help' => t('Status Date.'),
		'field' => array(
			'handler' => 'views_handler_field_date',
			'click sortable' => false,
		),
		'sort' => array(
			'handler' => 'views_handler_sort_date',
		),
		'filter' => array(
			'handler' => 'views_handler_filter_date',
		),
	);
	
	// The status_uid field
	$data[$student_withdrawal_table]['status_uid'] = array(
		'title' => t('Status UID'),
		'help' => t('Status UID.'),
		'field' => array(
			'handler' => 'views_handler_field',
			'click sortable' => false,
		),
		'sort' => array(
			'handler' => 'views_handler_sort_string',
		),
		'filter' => array(
			'handler' => 'views_handler_filter_string',
		),
	);
	
  return $data;

}