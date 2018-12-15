<?php

/**
 *Implements hook_views_data().
 */
function student_profile_page_views_data() {
	$session_id = (string)variable_get('essa_sid');
	$student_master_table = 'essa_'.$session_id.'_master_student_table';
  $student_remarks_table = 'essa_'.$session_id.'_student_remarks';
	
	$data[$student_remarks_table]['table']['group'] = t('Student Remarks');
  
  $data[$student_remarks_table]['table']['base'] = array(
    'field' => 'id',
    'title' => t('Student Remarks'), 
    'help' => t('This View contains the student fee linkage.'), 
    'weight' => -10,
  );
  
  $data[$student_remarks_table]['id'] = array(
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
  
  $data[$student_remarks_table]['adm_no'] = array(
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
	
	$data[$student_remarks_table]['uid'] = array(
    'title' => t('Student UID'), 
    'help' => t('Student UID'), 
    'field' => array(
	    'handler' => 'views_handler_field_numeric',
		),
		'sort' => array(
			'handler' => 'views_handler_sort_numeric',
		),
		'filter' => array(
		  'handler' => 'views_handler_filter_numeric',
		),
		'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
	
	$data[$student_remarks_table]['remarks'] = array(
    'title' => t('Remarks'), 
    'help' => t('Remarks.'), 
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
	
	$data[$student_remarks_table]['remarks_by_uid'] = array(
    'title' => t('Remarks By UID'), 
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
	
	$data[$student_remarks_table]['remarks_by_emp_id'] = array(
    'title' => t('Remarks EMP ID'), 
    'help' => t('Remarks. EMP ID'), 
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
	
	$data[$student_remarks_table]['remarks_timestamp'] = array(
    'title' => t('Timestamp'), 
    'help' => t('Timestamp.'), 
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
	
	return $data;
}