<?php
/**
 * @file
 * fee_page.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function fee_page_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'fee_page';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_structure';
  $view->human_name = 'Fee Page';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Fee Page';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'amount' => 'amount',
    'applies_to' => 'applies_to',
    'class_from' => 'class_from',
    'class_to' => 'class_to',
    'distance_from' => 'distance_from',
    'distance_to' => 'distance_to',
    'facility' => 'facility',
    'fee_id_1' => 'fee_id_1',
    'freq_id' => 'freq_id',
    'frequency' => 'frequency',
    'is_hostel' => 'is_hostel',
    'optional_sub' => 'optional_sub',
    'particulars' => 'particulars',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'amount' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'applies_to' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'class_from' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'class_to' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'distance_from' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'distance_to' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'facility' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'fee_id_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'freq_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'frequency' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'is_hostel' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'optional_sub' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'particulars' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Fee Structure: Fee Id */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  /* Field: Fee Structure: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  /* Field: Fee Structure: Applies to */
  $handler->display->display_options['fields']['applies_to']['id'] = 'applies_to';
  $handler->display->display_options['fields']['applies_to']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['applies_to']['field'] = 'applies_to';
  /* Field: Fee Structure: Frequency */
  $handler->display->display_options['fields']['frequency']['id'] = 'frequency';
  $handler->display->display_options['fields']['frequency']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['frequency']['field'] = 'frequency';
  /* Field: Fee Structure: Class From */
  $handler->display->display_options['fields']['class_from']['id'] = 'class_from';
  $handler->display->display_options['fields']['class_from']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['class_from']['field'] = 'class_from';
  /* Field: Fee Structure: Class To */
  $handler->display->display_options['fields']['class_to']['id'] = 'class_to';
  $handler->display->display_options['fields']['class_to']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['class_to']['field'] = 'class_to';
  /* Field: Fee Structure: Optional Subject */
  $handler->display->display_options['fields']['optional_sub']['id'] = 'optional_sub';
  $handler->display->display_options['fields']['optional_sub']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['optional_sub']['field'] = 'optional_sub';
  /* Field: Fee Structure: Facility */
  $handler->display->display_options['fields']['facility']['id'] = 'facility';
  $handler->display->display_options['fields']['facility']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['facility']['field'] = 'facility';
  /* Field: Fee Structure: Distance From */
  $handler->display->display_options['fields']['distance_from']['id'] = 'distance_from';
  $handler->display->display_options['fields']['distance_from']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['distance_from']['field'] = 'distance_from';
  /* Field: Fee Structure: Distance To */
  $handler->display->display_options['fields']['distance_to']['id'] = 'distance_to';
  $handler->display->display_options['fields']['distance_to']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['distance_to']['field'] = 'distance_to';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/fees';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Fees';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['fee_page'] = $view;

  return $export;
}
