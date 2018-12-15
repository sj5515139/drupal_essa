<?php
/**
 * @file
 * library_issue_report.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function library_issue_report_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'library_issue_record';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_lib_issue';
  $view->human_name = 'Library Issue Record';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Library Issue Record';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'acc_no' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'rewrite' => array(
          'filter_rewrite_values' => '',
          'secondary_label' => NULL,
          'collapsible_label' => NULL,
          'combine_rewrite' => NULL,
          'reset_label' => NULL,
          'bef_filter_description' => NULL,
          'any_label' => NULL,
        ),
        'secondary_label' => NULL,
        'collapsible_label' => NULL,
        'combine_rewrite' => NULL,
        'reset_label' => NULL,
        'filter_rewrite_values' => NULL,
      ),
      'secondary_label' => NULL,
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'user_id' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'rewrite' => array(
          'filter_rewrite_values' => '',
          'secondary_label' => NULL,
          'collapsible_label' => NULL,
          'combine_rewrite' => NULL,
          'reset_label' => NULL,
          'bef_filter_description' => NULL,
          'any_label' => NULL,
        ),
        'secondary_label' => NULL,
        'collapsible_label' => NULL,
        'combine_rewrite' => NULL,
        'reset_label' => NULL,
        'filter_rewrite_values' => NULL,
      ),
      'secondary_label' => NULL,
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'issue_date' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'rewrite' => array(
          'filter_rewrite_values' => '',
          'secondary_label' => NULL,
          'collapsible_label' => NULL,
          'combine_rewrite' => NULL,
          'reset_label' => NULL,
          'bef_filter_description' => NULL,
          'any_label' => NULL,
        ),
        'secondary_label' => NULL,
        'collapsible_label' => NULL,
        'combine_rewrite' => NULL,
        'reset_label' => NULL,
        'filter_rewrite_values' => NULL,
      ),
      'secondary_label' => NULL,
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'issued_by' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'rewrite' => array(
          'filter_rewrite_values' => '',
          'secondary_label' => NULL,
          'collapsible_label' => NULL,
          'combine_rewrite' => NULL,
          'reset_label' => NULL,
          'bef_filter_description' => NULL,
          'any_label' => NULL,
        ),
        'secondary_label' => NULL,
        'collapsible_label' => NULL,
        'combine_rewrite' => NULL,
        'reset_label' => NULL,
        'filter_rewrite_values' => NULL,
      ),
      'secondary_label' => NULL,
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'status' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'rewrite' => array(
          'filter_rewrite_values' => '',
          'secondary_label' => NULL,
          'collapsible_label' => NULL,
          'combine_rewrite' => NULL,
          'reset_label' => NULL,
          'bef_filter_description' => NULL,
          'any_label' => NULL,
        ),
        'secondary_label' => NULL,
        'collapsible_label' => NULL,
        'combine_rewrite' => NULL,
        'reset_label' => NULL,
        'filter_rewrite_values' => NULL,
      ),
      'secondary_label' => NULL,
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'secondary_label' => NULL,
    'collapsible_label' => NULL,
    'combine_rewrite' => NULL,
    'reset_label' => NULL,
    'bef_filter_description' => NULL,
    'any_label' => NULL,
    'filter_rewrite_values' => NULL,
  );
  $handler->display->display_options['exposed_form']['options']['input_required'] = 0;
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'filtered_html';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'issue_no' => 'issue_no',
    'fine' => 'fine',
    'issue_date' => 'issue_date',
    'issue_no_1' => 'issue_no_1',
    'return_date' => 'return_date',
    'return_no' => 'return_no',
    'status' => 'status',
    'user_id' => 'user_id',
    'issued_by' => 'issued_by',
    'issued_by_uid' => 'issued_by_uid',
    'timestamp' => 'timestamp',
    'uid' => 'uid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'issue_no' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'fine' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'issue_date' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'issue_no_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'return_date' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'return_no' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'user_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'issued_by' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'issued_by_uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Library Issue Record: Issue No. */
  $handler->display->display_options['fields']['issue_no']['id'] = 'issue_no';
  $handler->display->display_options['fields']['issue_no']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['issue_no']['field'] = 'issue_no';
  /* Field: Library Issue Record: UID */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  /* Field: Library Issue Record: User ID */
  $handler->display->display_options['fields']['user_id']['id'] = 'user_id';
  $handler->display->display_options['fields']['user_id']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['user_id']['field'] = 'user_id';
  $handler->display->display_options['fields']['user_id']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['user_id']['alter']['path'] = 'user/[uid]';
  /* Field: Library Issue Record: NID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Library Issue Record: Acc No. */
  $handler->display->display_options['fields']['acc_no']['id'] = 'acc_no';
  $handler->display->display_options['fields']['acc_no']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['acc_no']['field'] = 'acc_no';
  /* Field: Library Issue Record: Book Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]';
  /* Field: Library Issue Record: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Issued On';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'd-M-Y';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'privatemsg_current_day';
  /* Field: Library Issue Record: Issued By UID */
  $handler->display->display_options['fields']['issued_by_uid']['id'] = 'issued_by_uid';
  $handler->display->display_options['fields']['issued_by_uid']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['issued_by_uid']['field'] = 'issued_by_uid';
  $handler->display->display_options['fields']['issued_by_uid']['exclude'] = TRUE;
  /* Field: Library Issue Record: Issued By */
  $handler->display->display_options['fields']['issued_by']['id'] = 'issued_by';
  $handler->display->display_options['fields']['issued_by']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['issued_by']['field'] = 'issued_by';
  $handler->display->display_options['fields']['issued_by']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['issued_by']['alter']['path'] = 'user/[issued_by_uid]';
  /* Field: Library Issue Record: Return date */
  $handler->display->display_options['fields']['return_date']['id'] = 'return_date';
  $handler->display->display_options['fields']['return_date']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['return_date']['field'] = 'return_date';
  $handler->display->display_options['fields']['return_date']['date_format'] = 'custom';
  $handler->display->display_options['fields']['return_date']['custom_date_format'] = 'd-M-Y';
  $handler->display->display_options['fields']['return_date']['second_date_format'] = 'privatemsg_current_day';
  /* Field: Library Issue Record: Return no. */
  $handler->display->display_options['fields']['return_no']['id'] = 'return_no';
  $handler->display->display_options['fields']['return_no']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['return_no']['field'] = 'return_no';
  /* Field: Library Issue Record: Fine */
  $handler->display->display_options['fields']['fine']['id'] = 'fine';
  $handler->display->display_options['fields']['fine']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['fine']['field'] = 'fine';
  /* Field: Library Issue Record: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Filter criterion: Library Issue Record: Acc No. */
  $handler->display->display_options['filters']['acc_no']['id'] = 'acc_no';
  $handler->display->display_options['filters']['acc_no']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['filters']['acc_no']['field'] = 'acc_no';
  $handler->display->display_options['filters']['acc_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['acc_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['acc_no']['expose']['operator_id'] = 'acc_no_op';
  $handler->display->display_options['filters']['acc_no']['expose']['label'] = 'Acc No.';
  $handler->display->display_options['filters']['acc_no']['expose']['operator'] = 'acc_no_op';
  $handler->display->display_options['filters']['acc_no']['expose']['identifier'] = 'acc_no';
  $handler->display->display_options['filters']['acc_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    15 => 0,
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
    16 => 0,
    17 => 0,
    18 => 0,
    19 => 0,
  );
  /* Filter criterion: Library Issue Record: User ID */
  $handler->display->display_options['filters']['user_id']['id'] = 'user_id';
  $handler->display->display_options['filters']['user_id']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['filters']['user_id']['field'] = 'user_id';
  $handler->display->display_options['filters']['user_id']['operator'] = 'contains';
  $handler->display->display_options['filters']['user_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['user_id']['expose']['operator_id'] = 'user_id_op';
  $handler->display->display_options['filters']['user_id']['expose']['label'] = 'User ID';
  $handler->display->display_options['filters']['user_id']['expose']['operator'] = 'user_id_op';
  $handler->display->display_options['filters']['user_id']['expose']['identifier'] = 'user_id';
  $handler->display->display_options['filters']['user_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    15 => 0,
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
    16 => 0,
    17 => 0,
    18 => 0,
    19 => 0,
  );
  /* Filter criterion: Library Issue Record: Issue date */
  $handler->display->display_options['filters']['issue_date']['id'] = 'issue_date';
  $handler->display->display_options['filters']['issue_date']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['filters']['issue_date']['field'] = 'issue_date';
  $handler->display->display_options['filters']['issue_date']['exposed'] = TRUE;
  $handler->display->display_options['filters']['issue_date']['expose']['operator_id'] = 'issue_date_op';
  $handler->display->display_options['filters']['issue_date']['expose']['label'] = 'Issue date';
  $handler->display->display_options['filters']['issue_date']['expose']['operator'] = 'issue_date_op';
  $handler->display->display_options['filters']['issue_date']['expose']['identifier'] = 'issue_date';
  $handler->display->display_options['filters']['issue_date']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    15 => 0,
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
    16 => 0,
    17 => 0,
    18 => 0,
    19 => 0,
  );
  /* Filter criterion: Library Issue Record: Issued By */
  $handler->display->display_options['filters']['issued_by']['id'] = 'issued_by';
  $handler->display->display_options['filters']['issued_by']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['filters']['issued_by']['field'] = 'issued_by';
  $handler->display->display_options['filters']['issued_by']['exposed'] = TRUE;
  $handler->display->display_options['filters']['issued_by']['expose']['operator_id'] = 'issued_by_op';
  $handler->display->display_options['filters']['issued_by']['expose']['label'] = 'Issued By';
  $handler->display->display_options['filters']['issued_by']['expose']['operator'] = 'issued_by_op';
  $handler->display->display_options['filters']['issued_by']['expose']['identifier'] = 'issued_by';
  $handler->display->display_options['filters']['issued_by']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    15 => 0,
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
    16 => 0,
    17 => 0,
    18 => 0,
    19 => 0,
  );
  /* Filter criterion: Library Issue Record: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'essa_2016_17_lib_issue';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['status']['group_info']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['group_info']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Open',
      'operator' => '=',
      'value' => 'open',
    ),
    2 => array(
      'title' => 'Closed',
      'operator' => '=',
      'value' => 'closed',
    ),
    3 => array(
      'title' => '',
      'operator' => '=',
      'value' => '',
    ),
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/library/issue-report';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Issue Report';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['library_issue_record'] = $view;

  return $export;
}
