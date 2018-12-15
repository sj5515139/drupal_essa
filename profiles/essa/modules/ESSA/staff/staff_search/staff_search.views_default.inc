<?php
/**
 * @file
 * staff_search.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function staff_search_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'staff_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_master_staff_table';
  $view->human_name = 'Staff Search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Staff Search';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'type',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'uid' => 'uid',
    'emp_id' => 'emp_id',
    'fname' => 'fname',
    'lname' => 'fname',
    'dob' => 'dob',
    'type' => 'type',
    'ca_line1' => 'ca_line1',
    'ca_line2' => 'ca_line1',
    'ca_city' => 'ca_line1',
    'ca_state' => 'ca_line1',
    'ca_pincode' => 'ca_line1',
    'ca_country' => 'ca_line1',
    'email' => 'email',
    'mobile_no' => 'mobile_no',
    'phone_no' => 'mobile_no',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'emp_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'fname' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'lname' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'dob' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ca_line1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ', ',
      'empty_column' => 0,
    ),
    'ca_line2' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ca_city' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ca_state' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ca_pincode' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ca_country' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mobile_no' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'phone_no' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: essa_2016_17_master_staff_table: uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['separator'] = '';
  /* Field: essa_2016_17_master_staff_table: emp_id */
  $handler->display->display_options['fields']['emp_id']['id'] = 'emp_id';
  $handler->display->display_options['fields']['emp_id']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['emp_id']['field'] = 'emp_id';
  $handler->display->display_options['fields']['emp_id']['label'] = 'EMP ID';
  $handler->display->display_options['fields']['emp_id']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['emp_id']['alter']['path'] = 'user/[uid]';
  $handler->display->display_options['fields']['emp_id']['alter']['target'] = '_blank';
  /* Field: essa_2016_17_master_staff_table: fname */
  $handler->display->display_options['fields']['fname']['id'] = 'fname';
  $handler->display->display_options['fields']['fname']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['fname']['field'] = 'fname';
  $handler->display->display_options['fields']['fname']['label'] = 'Name';
  /* Field: essa_2016_17_master_staff_table: lname */
  $handler->display->display_options['fields']['lname']['id'] = 'lname';
  $handler->display->display_options['fields']['lname']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['lname']['field'] = 'lname';
  /* Field: essa_2016_17_master_staff_table: dob */
  $handler->display->display_options['fields']['dob']['id'] = 'dob';
  $handler->display->display_options['fields']['dob']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['dob']['field'] = 'dob';
  $handler->display->display_options['fields']['dob']['label'] = 'Date of Birth';
  /* Field: essa_2016_17_master_staff_table: type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = 'Type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  /* Field: essa_2016_17_master_staff_table: ca_line1 */
  $handler->display->display_options['fields']['ca_line1']['id'] = 'ca_line1';
  $handler->display->display_options['fields']['ca_line1']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['ca_line1']['field'] = 'ca_line1';
  $handler->display->display_options['fields']['ca_line1']['label'] = 'Correspondence Address';
  /* Field: essa_2016_17_master_staff_table: ca_line2 */
  $handler->display->display_options['fields']['ca_line2']['id'] = 'ca_line2';
  $handler->display->display_options['fields']['ca_line2']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['ca_line2']['field'] = 'ca_line2';
  /* Field: essa_2016_17_master_staff_table: ca_city */
  $handler->display->display_options['fields']['ca_city']['id'] = 'ca_city';
  $handler->display->display_options['fields']['ca_city']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['ca_city']['field'] = 'ca_city';
  /* Field: essa_2016_17_master_staff_table: ca_state */
  $handler->display->display_options['fields']['ca_state']['id'] = 'ca_state';
  $handler->display->display_options['fields']['ca_state']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['ca_state']['field'] = 'ca_state';
  /* Field: essa_2016_17_master_staff_table: ca_pincode */
  $handler->display->display_options['fields']['ca_pincode']['id'] = 'ca_pincode';
  $handler->display->display_options['fields']['ca_pincode']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['ca_pincode']['field'] = 'ca_pincode';
  /* Field: essa_2016_17_master_staff_table: ca_country */
  $handler->display->display_options['fields']['ca_country']['id'] = 'ca_country';
  $handler->display->display_options['fields']['ca_country']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['ca_country']['field'] = 'ca_country';
  /* Field: essa_2016_17_master_staff_table: email */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  $handler->display->display_options['fields']['email']['label'] = 'Email';
  /* Field: essa_2016_17_master_staff_table: mobile_no */
  $handler->display->display_options['fields']['mobile_no']['id'] = 'mobile_no';
  $handler->display->display_options['fields']['mobile_no']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['mobile_no']['field'] = 'mobile_no';
  $handler->display->display_options['fields']['mobile_no']['label'] = 'Contact Details';
  /* Field: essa_2016_17_master_staff_table: phone_no */
  $handler->display->display_options['fields']['phone_no']['id'] = 'phone_no';
  $handler->display->display_options['fields']['phone_no']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['fields']['phone_no']['field'] = 'phone_no';
  /* Filter criterion: essa_2016_17_master_staff_table: emp_id */
  $handler->display->display_options['filters']['emp_id']['id'] = 'emp_id';
  $handler->display->display_options['filters']['emp_id']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['filters']['emp_id']['field'] = 'emp_id';
  $handler->display->display_options['filters']['emp_id']['operator'] = 'contains';
  $handler->display->display_options['filters']['emp_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['emp_id']['expose']['operator_id'] = 'emp_id_op';
  $handler->display->display_options['filters']['emp_id']['expose']['label'] = 'EMP ID';
  $handler->display->display_options['filters']['emp_id']['expose']['operator'] = 'emp_id_op';
  $handler->display->display_options['filters']['emp_id']['expose']['identifier'] = 'emp_id';
  $handler->display->display_options['filters']['emp_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    16 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
    15 => 0,
    17 => 0,
    18 => 0,
  );
  /* Filter criterion: essa_2016_17_master_staff_table: fname */
  $handler->display->display_options['filters']['fname']['id'] = 'fname';
  $handler->display->display_options['filters']['fname']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['filters']['fname']['field'] = 'fname';
  $handler->display->display_options['filters']['fname']['operator'] = 'contains';
  $handler->display->display_options['filters']['fname']['exposed'] = TRUE;
  $handler->display->display_options['filters']['fname']['expose']['operator_id'] = 'fname_op';
  $handler->display->display_options['filters']['fname']['expose']['label'] = 'First Name';
  $handler->display->display_options['filters']['fname']['expose']['operator'] = 'fname_op';
  $handler->display->display_options['filters']['fname']['expose']['identifier'] = 'fname';
  $handler->display->display_options['filters']['fname']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    18 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    17 => 0,
    19 => 0,
    20 => 0,
  );
  /* Filter criterion: essa_2016_17_master_staff_table: type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'essa_2016_17_master_staff_table';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    18 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    17 => 0,
    19 => 0,
    20 => 0,
  );
  $handler->display->display_options['filters']['type']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['type']['group_info']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['group_info']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Teaching',
      'operator' => '=',
      'value' => 'Teaching',
    ),
    2 => array(
      'title' => 'Non-Teaching',
      'operator' => '=',
      'value' => 'Non-Teaching',
    ),
    3 => array(
      'title' => '',
      'operator' => '=',
      'value' => '',
    ),
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/staff/staff-search';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Search';
  $handler->display->display_options['menu']['weight'] = '-100';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['staff_search'] = $view;

  return $export;
}
