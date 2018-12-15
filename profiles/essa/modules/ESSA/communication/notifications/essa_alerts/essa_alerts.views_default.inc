<?php
/**
 * @file
 * essa_alerts.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function essa_alerts_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'essa_alerts';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_system_alert';
  $view->human_name = 'ESSA Alerts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'ESSA Alerts';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'message' => 'message',
    'timestamp' => 'timestamp',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: essa_2016_17_system_alert: id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'essa_2016_17_system_alert';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  /* Field: essa_2016_17_system_alert: message */
  $handler->display->display_options['fields']['message']['id'] = 'message';
  $handler->display->display_options['fields']['message']['table'] = 'essa_2016_17_system_alert';
  $handler->display->display_options['fields']['message']['field'] = 'message';
  $handler->display->display_options['fields']['message']['label'] = 'Alert';
  /* Field: essa_2016_17_system_alert: timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'essa_2016_17_system_alert';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Date';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'privatemsg_current_day';
  /* Sort criterion: essa_2016_17_system_alert: timestamp */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'essa_2016_17_system_alert';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Filter criterion: essa_2016_17_system_alert: priority */
  $handler->display->display_options['filters']['status']['id'] = 'priority';
  $handler->display->display_options['filters']['status']['table'] = 'essa_2016_17_system_alert';
  $handler->display->display_options['filters']['status']['field'] = 'priority';
  $handler->display->display_options['filters']['status']['value'] = 'L';

  /* Display: High alert */
  $handler = $view->new_display('block', 'High alert', 'block');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: essa_2016_17_system_alert: priority */
  $handler->display->display_options['filters']['status']['id'] = 'priority';
  $handler->display->display_options['filters']['status']['table'] = 'essa_2016_17_system_alert';
  $handler->display->display_options['filters']['status']['field'] = 'priority';
  $handler->display->display_options['filters']['status']['value'] = 'H';

  /* Display: Medium alerts */
  $handler = $view->new_display('block', 'Medium alerts', 'block_1');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: essa_2016_17_system_alert: priority */
  $handler->display->display_options['filters']['status']['id'] = 'priority';
  $handler->display->display_options['filters']['status']['table'] = 'essa_2016_17_system_alert';
  $handler->display->display_options['filters']['status']['field'] = 'priority';
  $handler->display->display_options['filters']['status']['value'] = 'M';

  /* Display: Low alerts */
  $handler = $view->new_display('block', 'Low alerts', 'block_2');
  $export['essa_alerts'] = $view;

  return $export;
}
