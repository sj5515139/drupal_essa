<?php
/**
 * @file
 * student_search.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function student_search_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'student_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_master_student_table';
  $view->human_name = 'Student Search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Student Search';
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
    'pager' => array(
      'bef_format' => 'default',
      'is_secondary' => 0,
      'secondary_label' => NULL,
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'adm_no' => array(
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
    'class' => array(
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
    'section' => array(
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
    'student_name' => array(
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
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10,20,30,40,50,60,70,80';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'uid' => 'uid',
    'adm_no' => 'adm_no',
    'roll_no' => 'roll_no',
    'first_name' => 'first_name',
    'middle_name' => 'middle_name',
    'last_name' => 'last_name',
    'class' => 'class',
    'section' => 'section',
    'gender' => 'gender',
    'father_name' => 'father_name',
    'mother_name' => 'mother_name',
    'doa' => 'doa',
    'dob' => 'dob',
    'ec1' => 'ec1',
    'ec2' => 'ec2',
    'ec3' => 'ec3',
    'ec4' => 'ec4',
    's_email' => 's_email',
    'student_name' => 'student_name',
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
    'adm_no' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'roll_no' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'middle_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'class' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'gender' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'father_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mother_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'doa' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'dob' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ec1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ec2' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ec3' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ec4' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    's_email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'student_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: essa_2016_17_master_student_table: uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['separator'] = '';
  /* Field: essa_2016_17_master_student_table: adm_no */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['label'] = 'Adm No';
  $handler->display->display_options['fields']['adm_no']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['adm_no']['alter']['path'] = 'user/[uid]';
  $handler->display->display_options['fields']['adm_no']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['adm_no']['alter']['target'] = ' _blank';
  /* Field: essa_2016_17_master_student_table: roll_no */
  $handler->display->display_options['fields']['roll_no']['id'] = 'roll_no';
  $handler->display->display_options['fields']['roll_no']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['roll_no']['field'] = 'roll_no';
  $handler->display->display_options['fields']['roll_no']['label'] = 'Roll No';
  /* Field: essa_2016_17_master_student_table: student_name */
  $handler->display->display_options['fields']['student_name']['id'] = 'student_name';
  $handler->display->display_options['fields']['student_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['student_name']['field'] = 'student_name';
  $handler->display->display_options['fields']['student_name']['label'] = 'Student Name';
  $handler->display->display_options['fields']['student_name']['element_label_colon'] = FALSE;
  /* Field: essa_2016_17_master_student_table: class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['label'] = 'Class';
  /* Field: essa_2016_17_master_student_table: section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  $handler->display->display_options['fields']['section']['label'] = '';
  $handler->display->display_options['fields']['section']['element_label_colon'] = FALSE;
  /* Field: essa_2016_17_master_student_table: gender */
  $handler->display->display_options['fields']['gender']['id'] = 'gender';
  $handler->display->display_options['fields']['gender']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['gender']['field'] = 'gender';
  $handler->display->display_options['fields']['gender']['label'] = 'Gender';
  /* Field: essa_2016_17_master_student_table: father_name */
  $handler->display->display_options['fields']['father_name']['id'] = 'father_name';
  $handler->display->display_options['fields']['father_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['father_name']['field'] = 'father_name';
  $handler->display->display_options['fields']['father_name']['label'] = 'Father Name';
  /* Field: essa_2016_17_master_student_table: mother_name */
  $handler->display->display_options['fields']['mother_name']['id'] = 'mother_name';
  $handler->display->display_options['fields']['mother_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['mother_name']['field'] = 'mother_name';
  $handler->display->display_options['fields']['mother_name']['label'] = 'Mother Name';
  /* Field: essa_2016_17_master_student_table: doa */
  $handler->display->display_options['fields']['doa']['id'] = 'doa';
  $handler->display->display_options['fields']['doa']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['doa']['field'] = 'doa';
  $handler->display->display_options['fields']['doa']['label'] = 'Date of Admission';
  /* Field: essa_2016_17_master_student_table: dob */
  $handler->display->display_options['fields']['dob']['id'] = 'dob';
  $handler->display->display_options['fields']['dob']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['dob']['field'] = 'dob';
  $handler->display->display_options['fields']['dob']['label'] = 'Date of Birth';
  /* Field: essa_2016_17_master_student_table: ec1 */
  $handler->display->display_options['fields']['ec1']['id'] = 'ec1';
  $handler->display->display_options['fields']['ec1']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['ec1']['field'] = 'ec1';
  $handler->display->display_options['fields']['ec1']['label'] = 'Contact Details';
  /* Field: essa_2016_17_master_student_table: ec2 */
  $handler->display->display_options['fields']['ec2']['id'] = 'ec2';
  $handler->display->display_options['fields']['ec2']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['ec2']['field'] = 'ec2';
  $handler->display->display_options['fields']['ec2']['label'] = '';
  $handler->display->display_options['fields']['ec2']['element_label_colon'] = FALSE;
  /* Field: essa_2016_17_master_student_table: ec3 */
  $handler->display->display_options['fields']['ec3']['id'] = 'ec3';
  $handler->display->display_options['fields']['ec3']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['ec3']['field'] = 'ec3';
  $handler->display->display_options['fields']['ec3']['label'] = '';
  $handler->display->display_options['fields']['ec3']['element_label_colon'] = FALSE;
  /* Field: essa_2016_17_master_student_table: ec4 */
  $handler->display->display_options['fields']['ec4']['id'] = 'ec4';
  $handler->display->display_options['fields']['ec4']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['ec4']['field'] = 'ec4';
  $handler->display->display_options['fields']['ec4']['label'] = '';
  $handler->display->display_options['fields']['ec4']['element_label_colon'] = FALSE;
  /* Field: essa_2016_17_master_student_table: s_email */
  $handler->display->display_options['fields']['s_email']['id'] = 's_email';
  $handler->display->display_options['fields']['s_email']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['s_email']['field'] = 's_email';
  $handler->display->display_options['fields']['s_email']['label'] = 'Email';
  /* Sort criterion: essa_2016_17_master_student_table: class */
  $handler->display->display_options['sorts']['class']['id'] = 'class';
  $handler->display->display_options['sorts']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['sorts']['class']['field'] = 'class';
  /* Sort criterion: essa_2016_17_master_student_table: section */
  $handler->display->display_options['sorts']['section']['id'] = 'section';
  $handler->display->display_options['sorts']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['sorts']['section']['field'] = 'section';
  /* Sort criterion: essa_2016_17_master_student_table: roll_no */
  $handler->display->display_options['sorts']['roll_no']['id'] = 'roll_no';
  $handler->display->display_options['sorts']['roll_no']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['sorts']['roll_no']['field'] = 'roll_no';
  /* Sort criterion: essa_2016_17_master_student_table: adm_no */
  $handler->display->display_options['sorts']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['sorts']['adm_no']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['sorts']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['sorts']['adm_no']['expose']['label'] = 'adm_no';
  /* Filter criterion: essa_2016_17_master_student_table: adm_no */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
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
  );
  /* Filter criterion: essa_2016_17_master_student_table: class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'LKG',
      'operator' => '=',
      'value' => 'LKG',
    ),
    2 => array(
      'title' => 'UKG',
      'operator' => '=',
      'value' => 'UKG',
    ),
    3 => array(
      'title' => 'I',
      'operator' => '=',
      'value' => 'I',
    ),
    4 => array(
      'title' => 'II',
      'operator' => '=',
      'value' => 'II',
    ),
    5 => array(
      'title' => 'III',
      'operator' => '=',
      'value' => 'III',
    ),
    6 => array(
      'title' => 'IV',
      'operator' => '=',
      'value' => 'IV',
    ),
    7 => array(
      'title' => 'V',
      'operator' => '=',
      'value' => 'V',
    ),
    8 => array(
      'title' => 'VI',
      'operator' => '=',
      'value' => 'VI',
    ),
    9 => array(
      'title' => 'VII',
      'operator' => '=',
      'value' => 'VII',
    ),
    10 => array(
      'title' => 'VIII',
      'operator' => '=',
      'value' => 'VIII',
    ),
    11 => array(
      'title' => 'IX',
      'operator' => '=',
      'value' => 'IX',
    ),
    12 => array(
      'title' => 'X',
      'operator' => '=',
      'value' => 'X',
    ),
  );
  /* Filter criterion: essa_2016_17_master_student_table: section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'section';
  $handler->display->display_options['filters']['section']['expose']['operator'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['identifier'] = 'section';
  $handler->display->display_options['filters']['section']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['section']['group_info']['label'] = 'Section';
  $handler->display->display_options['filters']['section']['group_info']['identifier'] = 'section';
  $handler->display->display_options['filters']['section']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'A',
      'operator' => '=',
      'value' => 'A',
    ),
    2 => array(
      'title' => 'B',
      'operator' => '=',
      'value' => 'B',
    ),
    3 => array(
      'title' => 'C',
      'operator' => '=',
      'value' => 'C',
    ),
    4 => array(
      'title' => 'D',
      'operator' => '=',
      'value' => 'D',
    ),
    5 => array(
      'title' => 'E',
      'operator' => '=',
      'value' => 'E',
    ),
    6 => array(
      'title' => 'F',
      'operator' => '=',
      'value' => 'F',
    ),
    7 => array(
      'title' => 'G',
      'operator' => '=',
      'value' => 'G',
    ),
    8 => array(
      'title' => 'H',
      'operator' => '=',
      'value' => 'H',
    ),
  );
  /* Filter criterion: essa_2016_17_master_student_table: student_name */
  $handler->display->display_options['filters']['student_name']['id'] = 'student_name';
  $handler->display->display_options['filters']['student_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['student_name']['field'] = 'student_name';
  $handler->display->display_options['filters']['student_name']['operator'] = 'contains';
  $handler->display->display_options['filters']['student_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['student_name']['expose']['operator_id'] = 'student_name_op';
  $handler->display->display_options['filters']['student_name']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['student_name']['expose']['operator'] = 'student_name_op';
  $handler->display->display_options['filters']['student_name']['expose']['identifier'] = 'student_name';
  $handler->display->display_options['filters']['student_name']['expose']['remember_roles'] = array(
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
  );
  /* Filter criterion: essa_2016_17_master_student_table: status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value']['value'] = '1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/students/student-search';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Search';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $export['student_search'] = $view;

  return $export;
}
