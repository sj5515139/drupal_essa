<?php

/**
 *Implements hook_views_data().
 */
function lib_sys_views_data() {
  $session_id = (string)variable_get('essa_sid');
  
  //-------------------------------------------------------------Fee Frequency------------------------------------------------------------
  $data['essa_'.$session_id.'_lib_issue']['table']['group'] = t('Library Issue Record');
  
  $data['essa_'.$session_id.'_lib_issue']['table']['base'] = array(
    'field' => 'Library Issue Records',
    'title' => t('Issue No.'), 
    'help' => t('This View contains the all the types of frequencies for fee collection, along with the due dates.'), 
    'weight' => -10,
  );
  
	$data['essa_'.$session_id.'_lib_issue']['issue_no'] = array(
    'title' => t('Issue No.'), 
    'help' => t('Issue No.'), 
    'field' => array(
        'handler' => 'views_handler_field_node',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_string',
    ),
  );
	
	$data['essa_'.$session_id.'_lib_issue']['acc_no'] = array(
    'title' => t('Acc No.'), 
    'help' => t('Acc No.'), 
    'field' => array(
        'handler' => 'views_handler_field_node',
    ),
    'sort' => array(
        'handler' => 'views_handler_sort',
    ),
    'filter' => array(
        'handler' => 'views_handler_filter_string',
    ),
  );
	
  $data['essa_'.$session_id.'_lib_issue']['user_id'] = array(
    'title' => t('User ID'), 
    'help' => t('User ID.'), 
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
	
	$data['essa_'.$session_id.'_lib_issue']['return_no'] = array(
    'title' => t('Return no.'), 
    'help' => t('Return no.'), 
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
	
	$data['essa_'.$session_id.'_lib_issue']['issue_date'] = array(
    'title' => t('Issue date'), 
    'help' => t('Issue date.'), 
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
  
	$data['essa_'.$session_id.'_lib_issue']['return_date'] = array(
    'title' => t('Return date'), 
    'help' => t('Return date.'), 
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
	
	$data['essa_'.$session_id.'_lib_issue']['fine'] = array(
    'title' => t('Fine'), 
    'help' => t('Fine'), 
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
	
	$data['essa_'.$session_id.'_lib_issue']['status'] = array(
    'title' => t('Status'), 
    'help' => t('Status.'), 
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
	
	$data['essa_'.$session_id.'_lib_issue']['uid'] = array(
    'title' => t('UID'), 
    'help' => t('UID.'), 
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
	
	$data['essa_'.$session_id.'_lib_issue']['issued_by_uid'] = array(
    'title' => t('Issued By UID'), 
    'help' => t('Issued By UID.'), 
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
	
	$data['essa_'.$session_id.'_lib_issue']['nid'] = array(
    'title' => t('NID'), 
    'help' => t('NID.'), 
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
	
	$data['essa_'.$session_id.'_lib_issue']['issued_by'] = array(
    'title' => t('Issued By'), 
    'help' => t('Issued By.'), 
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
	
	$data['essa_'.$session_id.'_lib_issue']['timestamp'] = array(
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
	
	$data['essa_'.$session_id.'_lib_issue']['title'] = array(
    'title' => t('Book Title'), 
    'help' => t('Book Title.'), 
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