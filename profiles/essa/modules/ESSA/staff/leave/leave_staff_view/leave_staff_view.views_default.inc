<?php
/**
 * @file
 * leave_staff_view.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function leave_staff_view_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'leave_staff_view';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_leave_staff';
  $view->human_name = 'Leave Staff View';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Leave Staff View';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'emp_id' => 'emp_id',
    'leave_id' => 'leave_id',
    'total_leave' => 'total_leave',
    'max_per_month' => 'max_per_month',
    'min_stretch' => 'min_stretch',
    'leave_taken' => 'leave_taken',
    'leave_remaining' => 'leave_remaining',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'emp_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'leave_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'total_leave' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'max_per_month' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'min_stretch' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'leave_taken' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'leave_remaining' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: essa_2016_17_leave_staff: emp_id */
  $handler->display->display_options['fields']['emp_id']['id'] = 'emp_id';
  $handler->display->display_options['fields']['emp_id']['table'] = 'essa_2016_17_leave_staff';
  $handler->display->display_options['fields']['emp_id']['field'] = 'emp_id';
  $handler->display->display_options['fields']['emp_id']['label'] = '';
  $handler->display->display_options['fields']['emp_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['emp_id']['element_label_colon'] = FALSE;
  /* Field: essa_2016_17_leave_staff: leave_id */
  $handler->display->display_options['fields']['leave_id']['id'] = 'leave_id';
  $handler->display->display_options['fields']['leave_id']['table'] = 'essa_2016_17_leave_staff';
  $handler->display->display_options['fields']['leave_id']['field'] = 'leave_id';
  $handler->display->display_options['fields']['leave_id']['label'] = '';
  $handler->display->display_options['fields']['leave_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['leave_id']['element_label_colon'] = FALSE;
  /* Field: essa_2016_17_leave_staff: total_leave */
  $handler->display->display_options['fields']['total_leave']['id'] = 'total_leave';
  $handler->display->display_options['fields']['total_leave']['table'] = 'essa_2016_17_leave_staff';
  $handler->display->display_options['fields']['total_leave']['field'] = 'total_leave';
  $handler->display->display_options['fields']['total_leave']['label'] = '';
  $handler->display->display_options['fields']['total_leave']['exclude'] = TRUE;
  $handler->display->display_options['fields']['total_leave']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['total_leave']['separator'] = '';
  /* Field: essa_2016_17_leave_staff: max_per_month */
  $handler->display->display_options['fields']['max_per_month']['id'] = 'max_per_month';
  $handler->display->display_options['fields']['max_per_month']['table'] = 'essa_2016_17_leave_staff';
  $handler->display->display_options['fields']['max_per_month']['field'] = 'max_per_month';
  $handler->display->display_options['fields']['max_per_month']['label'] = '';
  $handler->display->display_options['fields']['max_per_month']['exclude'] = TRUE;
  $handler->display->display_options['fields']['max_per_month']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['max_per_month']['separator'] = '';
  /* Field: essa_2016_17_leave_staff: min_stretch */
  $handler->display->display_options['fields']['min_stretch']['id'] = 'min_stretch';
  $handler->display->display_options['fields']['min_stretch']['table'] = 'essa_2016_17_leave_staff';
  $handler->display->display_options['fields']['min_stretch']['field'] = 'min_stretch';
  $handler->display->display_options['fields']['min_stretch']['label'] = '';
  $handler->display->display_options['fields']['min_stretch']['exclude'] = TRUE;
  $handler->display->display_options['fields']['min_stretch']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['min_stretch']['separator'] = '';
  /* Field: essa_2016_17_leave_staff: leave_taken */
  $handler->display->display_options['fields']['leave_taken']['id'] = 'leave_taken';
  $handler->display->display_options['fields']['leave_taken']['table'] = 'essa_2016_17_leave_staff';
  $handler->display->display_options['fields']['leave_taken']['field'] = 'leave_taken';
  $handler->display->display_options['fields']['leave_taken']['label'] = '';
  $handler->display->display_options['fields']['leave_taken']['exclude'] = TRUE;
  $handler->display->display_options['fields']['leave_taken']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['leave_taken']['separator'] = '';
  /* Field: essa_2016_17_leave_staff: leave_remaining */
  $handler->display->display_options['fields']['leave_remaining']['id'] = 'leave_remaining';
  $handler->display->display_options['fields']['leave_remaining']['table'] = 'essa_2016_17_leave_staff';
  $handler->display->display_options['fields']['leave_remaining']['field'] = 'leave_remaining';
  $handler->display->display_options['fields']['leave_remaining']['label'] = '';
  $handler->display->display_options['fields']['leave_remaining']['exclude'] = TRUE;
  $handler->display->display_options['fields']['leave_remaining']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['leave_remaining']['separator'] = '';
  /* Field: essa_2016_17_leave_staff: leave_status */
  $handler->display->display_options['fields']['leave_status']['id'] = 'leave_status';
  $handler->display->display_options['fields']['leave_status']['table'] = 'essa_2016_17_leave_staff';
  $handler->display->display_options['fields']['leave_status']['field'] = 'leave_status';
  $handler->display->display_options['fields']['leave_status']['label'] = '';
  $handler->display->display_options['fields']['leave_status']['exclude'] = TRUE;
  $handler->display->display_options['fields']['leave_status']['element_label_colon'] = FALSE;
  /* Field: Views: Views Conditional */
  $handler->display->display_options['fields']['views_conditional_1']['id'] = 'views_conditional_1';
  $handler->display->display_options['fields']['views_conditional_1']['table'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional_1']['field'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional_1']['label'] = 'Employee ID';
  $handler->display->display_options['fields']['views_conditional_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_conditional_1']['if'] = 'leave_status';
  $handler->display->display_options['fields']['views_conditional_1']['condition'] = '2';
  $handler->display->display_options['fields']['views_conditional_1']['equalto'] = '0';
  $handler->display->display_options['fields']['views_conditional_1']['then'] = '[emp_id]';
  $handler->display->display_options['fields']['views_conditional_1']['strip_tags'] = 0;
  /* Field: Views: Views Conditional */
  $handler->display->display_options['fields']['views_conditional']['id'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional']['table'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional']['field'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional']['label'] = 'Leave ID';
  $handler->display->display_options['fields']['views_conditional']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_conditional']['if'] = 'leave_status';
  $handler->display->display_options['fields']['views_conditional']['condition'] = '2';
  $handler->display->display_options['fields']['views_conditional']['equalto'] = '0';
  $handler->display->display_options['fields']['views_conditional']['then'] = '[leave_id]';
  $handler->display->display_options['fields']['views_conditional']['strip_tags'] = 0;
  /* Field: Views: Views Conditional */
  $handler->display->display_options['fields']['views_conditional_2']['id'] = 'views_conditional_2';
  $handler->display->display_options['fields']['views_conditional_2']['table'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional_2']['field'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional_2']['label'] = 'Total Leave';
  $handler->display->display_options['fields']['views_conditional_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_conditional_2']['if'] = 'leave_status';
  $handler->display->display_options['fields']['views_conditional_2']['condition'] = '2';
  $handler->display->display_options['fields']['views_conditional_2']['equalto'] = '0';
  $handler->display->display_options['fields']['views_conditional_2']['then'] = '[total_leave]';
  $handler->display->display_options['fields']['views_conditional_2']['strip_tags'] = 0;
  /* Field: Views: Views Conditional */
  $handler->display->display_options['fields']['views_conditional_3']['id'] = 'views_conditional_3';
  $handler->display->display_options['fields']['views_conditional_3']['table'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional_3']['field'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional_3']['label'] = 'Max in a month';
  $handler->display->display_options['fields']['views_conditional_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_conditional_3']['if'] = 'leave_status';
  $handler->display->display_options['fields']['views_conditional_3']['condition'] = '2';
  $handler->display->display_options['fields']['views_conditional_3']['equalto'] = '0';
  $handler->display->display_options['fields']['views_conditional_3']['then'] = '[max_per_month]';
  $handler->display->display_options['fields']['views_conditional_3']['strip_tags'] = 0;
  /* Field: Views: Views Conditional */
  $handler->display->display_options['fields']['views_conditional_4']['id'] = 'views_conditional_4';
  $handler->display->display_options['fields']['views_conditional_4']['table'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional_4']['field'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional_4']['label'] = 'Max in a month';
  $handler->display->display_options['fields']['views_conditional_4']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_conditional_4']['if'] = 'leave_status';
  $handler->display->display_options['fields']['views_conditional_4']['condition'] = '2';
  $handler->display->display_options['fields']['views_conditional_4']['equalto'] = '0';
  $handler->display->display_options['fields']['views_conditional_4']['then'] = '[min_stretch]';
  $handler->display->display_options['fields']['views_conditional_4']['strip_tags'] = 0;
  /* Field: Views: Views Conditional */
  $handler->display->display_options['fields']['views_conditional_5']['id'] = 'views_conditional_5';
  $handler->display->display_options['fields']['views_conditional_5']['table'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional_5']['field'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional_5']['label'] = 'Leave Taken';
  $handler->display->display_options['fields']['views_conditional_5']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_conditional_5']['if'] = 'leave_status';
  $handler->display->display_options['fields']['views_conditional_5']['condition'] = '2';
  $handler->display->display_options['fields']['views_conditional_5']['equalto'] = '0';
  $handler->display->display_options['fields']['views_conditional_5']['then'] = '[leave_taken]';
  $handler->display->display_options['fields']['views_conditional_5']['strip_tags'] = 0;
  /* Field: Views: Views Conditional */
  $handler->display->display_options['fields']['views_conditional_6']['id'] = 'views_conditional_6';
  $handler->display->display_options['fields']['views_conditional_6']['table'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional_6']['field'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional_6']['label'] = 'Leave Remaining';
  $handler->display->display_options['fields']['views_conditional_6']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_conditional_6']['if'] = 'leave_status';
  $handler->display->display_options['fields']['views_conditional_6']['condition'] = '2';
  $handler->display->display_options['fields']['views_conditional_6']['equalto'] = '0';
  $handler->display->display_options['fields']['views_conditional_6']['then'] = '[leave_remaining]';
  $handler->display->display_options['fields']['views_conditional_6']['strip_tags'] = 0;
  /* Filter criterion: essa_2016_17_leave_staff: emp_id */
  $handler->display->display_options['filters']['emp_id']['id'] = 'emp_id';
  $handler->display->display_options['filters']['emp_id']['table'] = 'essa_2016_17_leave_staff';
  $handler->display->display_options['filters']['emp_id']['field'] = 'emp_id';
  $handler->display->display_options['filters']['emp_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['emp_id']['expose']['operator_id'] = 'emp_id_op';
  $handler->display->display_options['filters']['emp_id']['expose']['label'] = 'Employee ID';
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
    19 => 0,
    22 => 0,
    23 => 0,
    24 => 0,
  );
  /* Filter criterion: essa_2016_17_leave_staff: leave_id */
  $handler->display->display_options['filters']['leave_id']['id'] = 'leave_id';
  $handler->display->display_options['filters']['leave_id']['table'] = 'essa_2016_17_leave_staff';
  $handler->display->display_options['filters']['leave_id']['field'] = 'leave_id';
  $handler->display->display_options['filters']['leave_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['leave_id']['expose']['operator_id'] = 'leave_id_op';
  $handler->display->display_options['filters']['leave_id']['expose']['label'] = 'Leave ID';
  $handler->display->display_options['filters']['leave_id']['expose']['operator'] = 'leave_id_op';
  $handler->display->display_options['filters']['leave_id']['expose']['identifier'] = 'leave_id';
  $handler->display->display_options['filters']['leave_id']['expose']['remember_roles'] = array(
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
    19 => 0,
    22 => 0,
    23 => 0,
    24 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/staff/leave/settings/staff_leave';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Staff Leave';
  $handler->display->display_options['menu']['description'] = 'Staff Leave';
  $handler->display->display_options['menu']['weight'] = '-97';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['leave_staff_view'] = $view;

  return $export;
}
