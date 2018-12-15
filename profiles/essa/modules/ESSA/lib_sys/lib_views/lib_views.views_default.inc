<?php
/**
 * @file
 * lib_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function lib_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'books';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'books';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'books';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['pager']['options']['effects']['type'] = 'fade';
  $handler->display->display_options['pager']['options']['effects']['speed'] = 'slow';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_bc' => 'field_bc',
    'field_acc_no_' => 'field_acc_no_',
    'field_author1' => 'field_author1',
    'field_author2' => 'field_author2',
    'field_author3' => 'field_author3',
    'field_category' => 'field_category',
    'field_cupboard' => 'field_cupboard',
    'field_date_of_purchase' => 'field_date_of_purchase',
    'field_language' => 'field_language',
    'field_page_no_' => 'field_page_no_',
    'field_shelf' => 'field_shelf',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_bc' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_acc_no_' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_author1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_author2' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_author3' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_category' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_cupboard' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_date_of_purchase' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_language' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_page_no_' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_shelf' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  /* Field: Content: Cover Image */
  $handler->display->display_options['fields']['field_cover_image']['id'] = 'field_cover_image';
  $handler->display->display_options['fields']['field_cover_image']['table'] = 'field_data_field_cover_image';
  $handler->display->display_options['fields']['field_cover_image']['field'] = 'field_cover_image';
  $handler->display->display_options['fields']['field_cover_image']['label'] = '';
  $handler->display->display_options['fields']['field_cover_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_cover_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_cover_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  /* Field: Content: Acc No. */
  $handler->display->display_options['fields']['field_acc_no_']['id'] = 'field_acc_no_';
  $handler->display->display_options['fields']['field_acc_no_']['table'] = 'field_data_field_acc_no_';
  $handler->display->display_options['fields']['field_acc_no_']['field'] = 'field_acc_no_';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  /* Field: Views: Views Conditional */
  $handler->display->display_options['fields']['views_conditional']['id'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional']['table'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional']['field'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional']['label'] = 'Date of Purchase';
  $handler->display->display_options['fields']['views_conditional']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_conditional']['if'] = 'field_date_of_purchase';
  $handler->display->display_options['fields']['views_conditional']['condition'] = '2';
  $handler->display->display_options['fields']['views_conditional']['equalto'] = 'Saturday, August 6, 2016';
  $handler->display->display_options['fields']['views_conditional']['then'] = '[field_date_of_purchase]';
  $handler->display->display_options['fields']['views_conditional']['strip_tags'] = 0;
  /* Field: Content: Author1 */
  $handler->display->display_options['fields']['field_author1']['id'] = 'field_author1';
  $handler->display->display_options['fields']['field_author1']['table'] = 'field_data_field_author1';
  $handler->display->display_options['fields']['field_author1']['field'] = 'field_author1';
  /* Field: Content: Author2 */
  $handler->display->display_options['fields']['field_author2']['id'] = 'field_author2';
  $handler->display->display_options['fields']['field_author2']['table'] = 'field_data_field_author2';
  $handler->display->display_options['fields']['field_author2']['field'] = 'field_author2';
  /* Field: Content: Author3 */
  $handler->display->display_options['fields']['field_author3']['id'] = 'field_author3';
  $handler->display->display_options['fields']['field_author3']['table'] = 'field_data_field_author3';
  $handler->display->display_options['fields']['field_author3']['field'] = 'field_author3';
  /* Field: Content: Category */
  $handler->display->display_options['fields']['field_category']['id'] = 'field_category';
  $handler->display->display_options['fields']['field_category']['table'] = 'field_data_field_category';
  $handler->display->display_options['fields']['field_category']['field'] = 'field_category';
  /* Field: Content: Language */
  $handler->display->display_options['fields']['field_language']['id'] = 'field_language';
  $handler->display->display_options['fields']['field_language']['table'] = 'field_data_field_language';
  $handler->display->display_options['fields']['field_language']['field'] = 'field_language';
  /* Field: Content: Page No. */
  $handler->display->display_options['fields']['field_page_no_']['id'] = 'field_page_no_';
  $handler->display->display_options['fields']['field_page_no_']['table'] = 'field_data_field_page_no_';
  $handler->display->display_options['fields']['field_page_no_']['field'] = 'field_page_no_';
  /* Field: Content: Cupboard */
  $handler->display->display_options['fields']['field_cupboard']['id'] = 'field_cupboard';
  $handler->display->display_options['fields']['field_cupboard']['table'] = 'field_data_field_cupboard';
  $handler->display->display_options['fields']['field_cupboard']['field'] = 'field_cupboard';
  /* Field: Content: Shelf */
  $handler->display->display_options['fields']['field_shelf']['id'] = 'field_shelf';
  $handler->display->display_options['fields']['field_shelf']['table'] = 'field_data_field_shelf';
  $handler->display->display_options['fields']['field_shelf']['field'] = 'field_shelf';
  /* Field: Content: bc */
  $handler->display->display_options['fields']['field_bc']['id'] = 'field_bc';
  $handler->display->display_options['fields']['field_bc']['table'] = 'field_data_field_bc';
  $handler->display->display_options['fields']['field_bc']['field'] = 'field_bc';
  $handler->display->display_options['fields']['field_bc']['label'] = 'Barcode';
  $handler->display->display_options['fields']['field_bc']['element_label_colon'] = FALSE;
  /* Field: Content: Availability */
  $handler->display->display_options['fields']['field_availability']['id'] = 'field_availability';
  $handler->display->display_options['fields']['field_availability']['table'] = 'field_data_field_availability';
  $handler->display->display_options['fields']['field_availability']['field'] = 'field_availability';
  $handler->display->display_options['fields']['field_availability']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
  /* Field: Content: Date of Purchase */
  $handler->display->display_options['fields']['field_date_of_purchase']['id'] = 'field_date_of_purchase';
  $handler->display->display_options['fields']['field_date_of_purchase']['table'] = 'field_data_field_date_of_purchase';
  $handler->display->display_options['fields']['field_date_of_purchase']['field'] = 'field_date_of_purchase';
  $handler->display->display_options['fields']['field_date_of_purchase']['label'] = '';
  $handler->display->display_options['fields']['field_date_of_purchase']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_date_of_purchase']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date_of_purchase']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'books' => 'books',
  );
  /* Filter criterion: Content: Acc No. (field_acc_no_) */
  $handler->display->display_options['filters']['field_acc_no__value']['id'] = 'field_acc_no__value';
  $handler->display->display_options['filters']['field_acc_no__value']['table'] = 'field_data_field_acc_no_';
  $handler->display->display_options['filters']['field_acc_no__value']['field'] = 'field_acc_no__value';
  $handler->display->display_options['filters']['field_acc_no__value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_acc_no__value']['expose']['operator_id'] = 'field_acc_no__value_op';
  $handler->display->display_options['filters']['field_acc_no__value']['expose']['label'] = 'Acc No.';
  $handler->display->display_options['filters']['field_acc_no__value']['expose']['operator'] = 'field_acc_no__value_op';
  $handler->display->display_options['filters']['field_acc_no__value']['expose']['identifier'] = 'field_acc_no__value';
  $handler->display->display_options['filters']['field_acc_no__value']['expose']['remember_roles'] = array(
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
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'word';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
    16 => 0,
    17 => 0,
    18 => 0,
    20 => 0,
    27 => 0,
    28 => 0,
  );
  /* Filter criterion: Content: Source (field_source) */
  $handler->display->display_options['filters']['field_source_tid']['id'] = 'field_source_tid';
  $handler->display->display_options['filters']['field_source_tid']['table'] = 'field_data_field_source';
  $handler->display->display_options['filters']['field_source_tid']['field'] = 'field_source_tid';
  $handler->display->display_options['filters']['field_source_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_source_tid']['expose']['operator_id'] = 'field_source_tid_op';
  $handler->display->display_options['filters']['field_source_tid']['expose']['label'] = 'Source';
  $handler->display->display_options['filters']['field_source_tid']['expose']['operator'] = 'field_source_tid_op';
  $handler->display->display_options['filters']['field_source_tid']['expose']['identifier'] = 'field_source_tid';
  $handler->display->display_options['filters']['field_source_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
    16 => 0,
    17 => 0,
    18 => 0,
    20 => 0,
    27 => 0,
    28 => 0,
  );
  $handler->display->display_options['filters']['field_source_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_source_tid']['vocabulary'] = 'book_source';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/library/books';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Books';
  $handler->display->display_options['menu']['weight'] = '-1';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: PDF Page */
  $handler = $view->new_display('pdf', 'PDF Page', 'pdf_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'pdf_table';
  $handler->display->display_options['style_options']['info'] = array(
    'field_acc_no_' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'body_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'position' => array(
        'width' => '',
      ),
    ),
    'title' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 0,
        ),
      ),
      'body_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 0,
        ),
      ),
      'position' => array(
        'width' => '',
      ),
    ),
    'field_author1' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'body_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'position' => array(
        'width' => '',
      ),
    ),
    'field_author2' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'body_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'position' => array(
        'width' => '',
      ),
    ),
    'field_author3' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'body_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'position' => array(
        'width' => '',
      ),
    ),
    'field_category' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'body_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'position' => array(
        'width' => '',
      ),
    ),
    'field_date_of_purchase' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'body_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'position' => array(
        'width' => '',
      ),
    ),
    'field_language' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'body_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'position' => array(
        'width' => '',
      ),
    ),
    'field_page_no_' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'body_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'position' => array(
        'width' => '',
      ),
    ),
    'field_cupboard' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'body_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'position' => array(
        'width' => '',
      ),
    ),
    'field_shelf' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'body_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'position' => array(
        'width' => '',
      ),
    ),
    'field_bc' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'body_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 0,
            'i' => 0,
            'u' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '',
        ),
        'render' => array(
          'is_html' => 1,
        ),
      ),
      'position' => array(
        'width' => '',
      ),
    ),
  );
  $handler->display->display_options['style_options']['position'] = array(
    'last_writing_position' => 1,
    'x' => '',
    'y' => '',
    'width' => '',
    'row_height' => '',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Acc No. */
  $handler->display->display_options['fields']['field_acc_no_']['id'] = 'field_acc_no_';
  $handler->display->display_options['fields']['field_acc_no_']['table'] = 'field_data_field_acc_no_';
  $handler->display->display_options['fields']['field_acc_no_']['field'] = 'field_acc_no_';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  /* Field: Content: Author1 */
  $handler->display->display_options['fields']['field_author1']['id'] = 'field_author1';
  $handler->display->display_options['fields']['field_author1']['table'] = 'field_data_field_author1';
  $handler->display->display_options['fields']['field_author1']['field'] = 'field_author1';
  /* Field: Content: Author2 */
  $handler->display->display_options['fields']['field_author2']['id'] = 'field_author2';
  $handler->display->display_options['fields']['field_author2']['table'] = 'field_data_field_author2';
  $handler->display->display_options['fields']['field_author2']['field'] = 'field_author2';
  /* Field: Content: Author3 */
  $handler->display->display_options['fields']['field_author3']['id'] = 'field_author3';
  $handler->display->display_options['fields']['field_author3']['table'] = 'field_data_field_author3';
  $handler->display->display_options['fields']['field_author3']['field'] = 'field_author3';
  /* Field: Content: Category */
  $handler->display->display_options['fields']['field_category']['id'] = 'field_category';
  $handler->display->display_options['fields']['field_category']['table'] = 'field_data_field_category';
  $handler->display->display_options['fields']['field_category']['field'] = 'field_category';
  /* Field: Content: Date of Purchase */
  $handler->display->display_options['fields']['field_date_of_purchase']['id'] = 'field_date_of_purchase';
  $handler->display->display_options['fields']['field_date_of_purchase']['table'] = 'field_data_field_date_of_purchase';
  $handler->display->display_options['fields']['field_date_of_purchase']['field'] = 'field_date_of_purchase';
  $handler->display->display_options['fields']['field_date_of_purchase']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Language */
  $handler->display->display_options['fields']['field_language']['id'] = 'field_language';
  $handler->display->display_options['fields']['field_language']['table'] = 'field_data_field_language';
  $handler->display->display_options['fields']['field_language']['field'] = 'field_language';
  /* Field: Content: Page No. */
  $handler->display->display_options['fields']['field_page_no_']['id'] = 'field_page_no_';
  $handler->display->display_options['fields']['field_page_no_']['table'] = 'field_data_field_page_no_';
  $handler->display->display_options['fields']['field_page_no_']['field'] = 'field_page_no_';
  $handler->display->display_options['path'] = 'books_pdf';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['default_page_orientation'] = 'L';
  $export['books'] = $view;

  return $export;
}
