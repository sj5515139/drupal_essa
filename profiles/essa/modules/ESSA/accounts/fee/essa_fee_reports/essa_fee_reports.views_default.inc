<?php
/**
 * @file
 * essa_fee_reports.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function essa_fee_reports_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'adjustment_report';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_adjustement';
  $view->human_name = 'Adjustment Report';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Adjustment Report';
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
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'bar';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'amount_1' => 'amount_1',
    'amount' => 'amount',
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'particulars' => 0,
    'month' => 0,
    'reason' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'adm_no' => '#2f7ed8',
    'first_name' => '#0d233a',
    'last_name' => '#8bbc21',
    'class' => '#910000',
    'section' => '#1aadce',
    'particulars' => '#492970',
    'month' => '#f28f43',
    'amount_1' => '#77a1e5',
    'amount' => '#c42525',
    'reason' => '#a6c96a',
  );
  /* Relationship: Fee Exemption: Admission No */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_adjustement';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Exemption: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_adjustement';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Exemption: UID */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'essa_2016_17_fees_student_adjustement';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Fee Exemption: Admission No */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_adjustement';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Exemption: Month */
  $handler->display->display_options['fields']['month']['id'] = 'month';
  $handler->display->display_options['fields']['month']['table'] = 'essa_2016_17_fees_student_adjustement';
  $handler->display->display_options['fields']['month']['field'] = 'month';
  /* Field: Fee Structure: Amount */
  $handler->display->display_options['fields']['amount_1']['id'] = 'amount_1';
  $handler->display->display_options['fields']['amount_1']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['amount_1']['field'] = 'amount';
  $handler->display->display_options['fields']['amount_1']['relationship'] = 'fee_id';
  $handler->display->display_options['fields']['amount_1']['label'] = 'Original Amount';
  /* Field: Fee Exemption: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'essa_2016_17_fees_student_adjustement';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['label'] = 'Amount Adjusted';
  /* Field: Fee Exemption: Reason */
  $handler->display->display_options['fields']['reason']['id'] = 'reason';
  $handler->display->display_options['fields']['reason']['table'] = 'essa_2016_17_fees_student_adjustement';
  $handler->display->display_options['fields']['reason']['field'] = 'reason';
  /* Field: Fees Edit Staff: Emp ID */
  $handler->display->display_options['fields']['emp_id']['id'] = 'emp_id';
  $handler->display->display_options['fields']['emp_id']['table'] = 'essa_2016_17_fees_staff';
  $handler->display->display_options['fields']['emp_id']['field'] = 'emp_id';
  $handler->display->display_options['fields']['emp_id']['relationship'] = 'uid';
  $handler->display->display_options['fields']['emp_id']['label'] = 'Fees Adjusted By';
  /* Field: Fees Edit Staff: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'essa_2016_17_fees_staff';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  /* Filter criterion: Fee Exemption: Admission No */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_adjustement';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'particulars' => 'particulars',
    'month' => 'month',
    'amount_1' => 'amount_1',
    'amount' => 'amount',
    'reason' => 'reason',
    'emp_id' => 'emp_id',
    'name' => 'emp_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'adm_no' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'month' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'amount_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'amount' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'reason' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'emp_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/adjustment-report';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Adjustment Report';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'admin/fees/reports/adjustment-report-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'admin/fees/reports/adjustment-report-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
    'block_1' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $export['adjustment_report'] = $view;

  $view = new view();
  $view->name = 'clone_of_fee_collection_summary';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_payment';
  $view->human_name = 'Fee Collection Detail';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Collection Detail';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
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
    'adm_no' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
    'particulars' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
    'payment_date' => array(
      'bef_format' => 'bef_datepicker',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'particulars' => 'particulars',
    'Mar_2016' => 'Mar_2016',
    'Mar_2016_payment_date' => 'Mar_2016_payment_date',
    'Mar_2016_payment_id' => 'Mar_2016_payment_id',
    'Apr_2016' => 'Apr_2016',
    'Apr_2016_payment_date' => 'Apr_2016_payment_date',
    'Apr_2016_payment_id' => 'Apr_2016_payment_id',
    'May_2016' => 'May_2016',
    'May_2016_payment_date' => 'May_2016_payment_date',
    'May_2016_payment_id' => 'May_2016_payment_id',
    'Jun_2016' => 'Jun_2016',
    'Jun_2016_payment_date' => 'Jun_2016_payment_date',
    'Jun_2016_payment_id' => 'Jun_2016_payment_id',
    'Jul_2016' => 'Jul_2016',
    'Jul_2016_payment_date' => 'Jul_2016_payment_date',
    'Jul_2016_payment_id' => 'Jul_2016_payment_id',
    'Aug_2016' => 'Aug_2016',
    'Aug_2016_payment_date' => 'Aug_2016_payment_date',
    'Aug_2016_payment_id' => 'Aug_2016_payment_id',
    'Sep_2016' => 'Sep_2016',
    'Sep_2016_payment_date' => 'Sep_2016_payment_date',
    'Sep_2016_payment_id' => 'Sep_2016_payment_id',
    'Oct_2016' => 'Oct_2016',
    'Oct_2016_payment_date' => 'Oct_2016_payment_date',
    'Oct_2016_payment_id' => 'Oct_2016_payment_id',
    'Nov_2016' => 'Nov_2016',
    'Nov_2016_payment_date' => 'Nov_2016_payment_date',
    'Nov_2016_payment_id' => 'Nov_2016_payment_id',
    'Dec_2016' => 'Dec_2016',
    'Dec_2016_payment_date' => 'Dec_2016_payment_date',
    'Dec_2016_payment_id' => 'Dec_2016_payment_id',
    'Jan_2017' => 'Jan_2017',
    'Jan_2017_payment_date' => 'Jan_2017_payment_date',
    'Jan_2017_payment_id' => 'Jan_2017_payment_id',
    'Feb_2017' => 'Feb_2017',
    'Feb_2017_payment_date' => 'Feb_2017_payment_date',
    'Feb_2017_payment_id' => 'Feb_2017_payment_id',
    'Mar_2017' => 'Mar_2017',
    'Mar_2017_payment_date' => 'Mar_2017_payment_date',
    'Mar_2017_payment_id' => 'Mar_2017_payment_id',
    'expression' => 'expression',
  );
  $handler->display->display_options['style_options']['default'] = 'adm_no';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_group_and_compress' => 'views_aggregator_group_and_compress',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_replace',
      'aggr_par_column' => 'Total',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => ' ',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2016_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2016_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Apr_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Apr_2016_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Apr_2016_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'May_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'May_2016_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'May_2016_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jun_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jun_2016_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jun_2016_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jul_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jul_2016_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jul_2016_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Aug_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Aug_2016_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Aug_2016_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Sep_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Sep_2016_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Sep_2016_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Oct_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Oct_2016_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Oct_2016_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Nov_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Nov_2016_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Nov_2016_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Dec_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Dec_2016_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Dec_2016_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jan_2017' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jan_2017_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jan_2017_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Feb_2017' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Feb_2017_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Feb_2017_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2017' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2017_payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2017_payment_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'expression' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  /* Relationship: Fee Student Payment: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Payment: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['Apr_2016_payment_id']['id'] = 'Apr_2016_payment_id';
  $handler->display->display_options['relationships']['Apr_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['Apr_2016_payment_id']['field'] = 'Apr_2016_payment_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['Aug_2016_payment_id']['id'] = 'Aug_2016_payment_id';
  $handler->display->display_options['relationships']['Aug_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['Aug_2016_payment_id']['field'] = 'Aug_2016_payment_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['Dec_2016_payment_id']['id'] = 'Dec_2016_payment_id';
  $handler->display->display_options['relationships']['Dec_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['Dec_2016_payment_id']['field'] = 'Dec_2016_payment_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['Feb_2017_payment_id']['id'] = 'Feb_2017_payment_id';
  $handler->display->display_options['relationships']['Feb_2017_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['Feb_2017_payment_id']['field'] = 'Feb_2017_payment_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['Jan_2017_payment_id']['id'] = 'Jan_2017_payment_id';
  $handler->display->display_options['relationships']['Jan_2017_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['Jan_2017_payment_id']['field'] = 'Jan_2017_payment_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['Jul_2016_payment_id']['id'] = 'Jul_2016_payment_id';
  $handler->display->display_options['relationships']['Jul_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['Jul_2016_payment_id']['field'] = 'Jul_2016_payment_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['Jun_2016_payment_id']['id'] = 'Jun_2016_payment_id';
  $handler->display->display_options['relationships']['Jun_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['Jun_2016_payment_id']['field'] = 'Jun_2016_payment_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['Mar_2016_payment_id']['id'] = 'Mar_2016_payment_id';
  $handler->display->display_options['relationships']['Mar_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['Mar_2016_payment_id']['field'] = 'Mar_2016_payment_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['Mar_2017_payment_id']['id'] = 'Mar_2017_payment_id';
  $handler->display->display_options['relationships']['Mar_2017_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['Mar_2017_payment_id']['field'] = 'Mar_2017_payment_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['May_2016_payment_id']['id'] = 'May_2016_payment_id';
  $handler->display->display_options['relationships']['May_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['May_2016_payment_id']['field'] = 'May_2016_payment_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['Nov_2016_payment_id']['id'] = 'Nov_2016_payment_id';
  $handler->display->display_options['relationships']['Nov_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['Nov_2016_payment_id']['field'] = 'Nov_2016_payment_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['Oct_2016_payment_id']['id'] = 'Oct_2016_payment_id';
  $handler->display->display_options['relationships']['Oct_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['Oct_2016_payment_id']['field'] = 'Oct_2016_payment_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['Sep_2016_payment_id']['id'] = 'Sep_2016_payment_id';
  $handler->display->display_options['relationships']['Sep_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['Sep_2016_payment_id']['field'] = 'Sep_2016_payment_id';
  /* Relationship: Fee Student Payment: Fee ID */
  $handler->display->display_options['relationships']['fee_id_1']['id'] = 'fee_id_1';
  $handler->display->display_options['relationships']['fee_id_1']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['fee_id_1']['field'] = 'fee_id';
  /* Field: Fee Student Payment: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['exclude'] = TRUE;
  /* Field: Fee Student Payment: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Mar_2016']['id'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Mar_2016']['field'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['label'] = 'Mar 2016';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Mar_2016_payment_date']['id'] = 'Mar_2016_payment_date';
  $handler->display->display_options['fields']['Mar_2016_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Mar_2016_payment_date']['field'] = 'Mar_2016_payment_date';
  $handler->display->display_options['fields']['Mar_2016_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['Mar_2016_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Mar_2016_payment_id']['id'] = 'Mar_2016_payment_id';
  $handler->display->display_options['fields']['Mar_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Mar_2016_payment_id']['field'] = 'Mar_2016_payment_id';
  $handler->display->display_options['fields']['Mar_2016_payment_id']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Apr_2016']['id'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Apr_2016']['field'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['label'] = 'Apr 2016';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Apr_2016_payment_date']['id'] = 'Apr_2016_payment_date';
  $handler->display->display_options['fields']['Apr_2016_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Apr_2016_payment_date']['field'] = 'Apr_2016_payment_date';
  $handler->display->display_options['fields']['Apr_2016_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['Apr_2016_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Apr_2016_payment_id']['id'] = 'Apr_2016_payment_id';
  $handler->display->display_options['fields']['Apr_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Apr_2016_payment_id']['field'] = 'Apr_2016_payment_id';
  $handler->display->display_options['fields']['Apr_2016_payment_id']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['May_2016']['id'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['May_2016']['field'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['label'] = 'May 2016';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['May_2016_payment_date']['id'] = 'May_2016_payment_date';
  $handler->display->display_options['fields']['May_2016_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['May_2016_payment_date']['field'] = 'May_2016_payment_date';
  $handler->display->display_options['fields']['May_2016_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['May_2016_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['May_2016_payment_id']['id'] = 'May_2016_payment_id';
  $handler->display->display_options['fields']['May_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['May_2016_payment_id']['field'] = 'May_2016_payment_id';
  $handler->display->display_options['fields']['May_2016_payment_id']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Jun_2016']['id'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Jun_2016']['field'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['label'] = 'Jun 2016';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Jun_2016_payment_date']['id'] = 'Jun_2016_payment_date';
  $handler->display->display_options['fields']['Jun_2016_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Jun_2016_payment_date']['field'] = 'Jun_2016_payment_date';
  $handler->display->display_options['fields']['Jun_2016_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['Jun_2016_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Jun_2016_payment_id']['id'] = 'Jun_2016_payment_id';
  $handler->display->display_options['fields']['Jun_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Jun_2016_payment_id']['field'] = 'Jun_2016_payment_id';
  $handler->display->display_options['fields']['Jun_2016_payment_id']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Jul_2016']['id'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Jul_2016']['field'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['label'] = 'Jul 2016';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Jul_2016_payment_date']['id'] = 'Jul_2016_payment_date';
  $handler->display->display_options['fields']['Jul_2016_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Jul_2016_payment_date']['field'] = 'Jul_2016_payment_date';
  $handler->display->display_options['fields']['Jul_2016_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['Jul_2016_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Jul_2016_payment_id']['id'] = 'Jul_2016_payment_id';
  $handler->display->display_options['fields']['Jul_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Jul_2016_payment_id']['field'] = 'Jul_2016_payment_id';
  $handler->display->display_options['fields']['Jul_2016_payment_id']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Aug_2016']['id'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Aug_2016']['field'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['label'] = 'Aug 2016';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Aug_2016_payment_date']['id'] = 'Aug_2016_payment_date';
  $handler->display->display_options['fields']['Aug_2016_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Aug_2016_payment_date']['field'] = 'Aug_2016_payment_date';
  $handler->display->display_options['fields']['Aug_2016_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['Aug_2016_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Aug_2016_payment_id']['id'] = 'Aug_2016_payment_id';
  $handler->display->display_options['fields']['Aug_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Aug_2016_payment_id']['field'] = 'Aug_2016_payment_id';
  $handler->display->display_options['fields']['Aug_2016_payment_id']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Sep_2016']['id'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Sep_2016']['field'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['label'] = 'Sep 2016';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Sep_2016_payment_date']['id'] = 'Sep_2016_payment_date';
  $handler->display->display_options['fields']['Sep_2016_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Sep_2016_payment_date']['field'] = 'Sep_2016_payment_date';
  $handler->display->display_options['fields']['Sep_2016_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['Sep_2016_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Sep_2016_payment_id']['id'] = 'Sep_2016_payment_id';
  $handler->display->display_options['fields']['Sep_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Sep_2016_payment_id']['field'] = 'Sep_2016_payment_id';
  $handler->display->display_options['fields']['Sep_2016_payment_id']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Oct_2016']['id'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Oct_2016']['field'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['label'] = 'Oct 2016';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Oct_2016_payment_date']['id'] = 'Oct_2016_payment_date';
  $handler->display->display_options['fields']['Oct_2016_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Oct_2016_payment_date']['field'] = 'Oct_2016_payment_date';
  $handler->display->display_options['fields']['Oct_2016_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['Oct_2016_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Oct_2016_payment_id']['id'] = 'Oct_2016_payment_id';
  $handler->display->display_options['fields']['Oct_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Oct_2016_payment_id']['field'] = 'Oct_2016_payment_id';
  $handler->display->display_options['fields']['Oct_2016_payment_id']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Nov_2016']['id'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Nov_2016']['field'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['label'] = 'Nov 2016';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Nov_2016_payment_date']['id'] = 'Nov_2016_payment_date';
  $handler->display->display_options['fields']['Nov_2016_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Nov_2016_payment_date']['field'] = 'Nov_2016_payment_date';
  $handler->display->display_options['fields']['Nov_2016_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['Nov_2016_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Nov_2016_payment_id']['id'] = 'Nov_2016_payment_id';
  $handler->display->display_options['fields']['Nov_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Nov_2016_payment_id']['field'] = 'Nov_2016_payment_id';
  $handler->display->display_options['fields']['Nov_2016_payment_id']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Dec_2016']['id'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Dec_2016']['field'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['label'] = 'Dec 2016';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Dec_2016_payment_date']['id'] = 'Dec_2016_payment_date';
  $handler->display->display_options['fields']['Dec_2016_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Dec_2016_payment_date']['field'] = 'Dec_2016_payment_date';
  $handler->display->display_options['fields']['Dec_2016_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['Dec_2016_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Dec_2016_payment_id']['id'] = 'Dec_2016_payment_id';
  $handler->display->display_options['fields']['Dec_2016_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Dec_2016_payment_id']['field'] = 'Dec_2016_payment_id';
  $handler->display->display_options['fields']['Dec_2016_payment_id']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Jan_2017']['id'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Jan_2017']['field'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['label'] = 'Jan 2017';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Jan_2017_payment_date']['id'] = 'Jan_2017_payment_date';
  $handler->display->display_options['fields']['Jan_2017_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Jan_2017_payment_date']['field'] = 'Jan_2017_payment_date';
  $handler->display->display_options['fields']['Jan_2017_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['Jan_2017_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Jan_2017_payment_id']['id'] = 'Jan_2017_payment_id';
  $handler->display->display_options['fields']['Jan_2017_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Jan_2017_payment_id']['field'] = 'Jan_2017_payment_id';
  $handler->display->display_options['fields']['Jan_2017_payment_id']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Feb_2017']['id'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Feb_2017']['field'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['label'] = 'Feb 2017';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Feb_2017_payment_date']['id'] = 'Feb_2017_payment_date';
  $handler->display->display_options['fields']['Feb_2017_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Feb_2017_payment_date']['field'] = 'Feb_2017_payment_date';
  $handler->display->display_options['fields']['Feb_2017_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['Feb_2017_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Feb_2017_payment_id']['id'] = 'Feb_2017_payment_id';
  $handler->display->display_options['fields']['Feb_2017_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Feb_2017_payment_id']['field'] = 'Feb_2017_payment_id';
  $handler->display->display_options['fields']['Feb_2017_payment_id']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Mar_2017']['id'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Mar_2017']['field'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['label'] = 'Mar 2017';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Mar_2017_payment_date']['id'] = 'Mar_2017_payment_date';
  $handler->display->display_options['fields']['Mar_2017_payment_date']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Mar_2017_payment_date']['field'] = 'Mar_2017_payment_date';
  $handler->display->display_options['fields']['Mar_2017_payment_date']['label'] = 'Payment Date';
  $handler->display->display_options['fields']['Mar_2017_payment_date']['exclude'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['Mar_2017_payment_id']['id'] = 'Mar_2017_payment_id';
  $handler->display->display_options['fields']['Mar_2017_payment_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['Mar_2017_payment_id']['field'] = 'Mar_2017_payment_id';
  $handler->display->display_options['fields']['Mar_2017_payment_id']['exclude'] = TRUE;
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['label'] = 'Total';
  $handler->display->display_options['fields']['expression']['precision'] = '0';
  $handler->display->display_options['fields']['expression']['format_plural_singular'] = '';
  $handler->display->display_options['fields']['expression']['expression'] = '[Mar_2016]+[Apr_2016]+[May_2016]+[Jun_2016]+[Jul_2016]+[Aug_2016]+[Sep_2016]+[Oct_2016]+[Nov_2016]+[Dec_2016]+[Jan_2017]+[Feb_2017]+[Mar_2017]';
  /* Sort criterion: Fee Payment History: Admission No. */
  $handler->display->display_options['sorts']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['sorts']['adm_no']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['sorts']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['sorts']['adm_no']['relationship'] = 'Apr_2016_payment_id';
  $handler->display->display_options['sorts']['adm_no']['expose']['label'] = 'Admission No.';
  /* Filter criterion: Fee Student Payment: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Payment History: Payment Date */
  $handler->display->display_options['filters']['payment_date']['id'] = 'payment_date';
  $handler->display->display_options['filters']['payment_date']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['filters']['payment_date']['field'] = 'payment_date';
  $handler->display->display_options['filters']['payment_date']['relationship'] = 'Apr_2016_payment_id';
  $handler->display->display_options['filters']['payment_date']['operator'] = 'between';
  $handler->display->display_options['filters']['payment_date']['exposed'] = TRUE;
  $handler->display->display_options['filters']['payment_date']['expose']['operator_id'] = 'payment_date_op';
  $handler->display->display_options['filters']['payment_date']['expose']['label'] = 'Payment Date';
  $handler->display->display_options['filters']['payment_date']['expose']['operator'] = 'payment_date_op';
  $handler->display->display_options['filters']['payment_date']['expose']['identifier'] = 'payment_date';
  $handler->display->display_options['filters']['payment_date']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'collection-detail';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'collection-detail-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'collection-detail-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: PDF Page */
  $handler = $view->new_display('pdf', 'PDF Page', 'pdf_1');
  $handler->display->display_options['enabled'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'pdf_table';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
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
    'adm_no' => array(
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
    'first_name' => array(
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
    'last_name' => array(
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
    'class' => array(
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
    'section' => array(
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
    'particulars' => array(
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
    'Mar_2016' => array(
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
    'Apr_2016' => array(
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
    'May_2016' => array(
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
    'Jun_2016' => array(
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
    'Jul_2016' => array(
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
    'Aug_2016' => array(
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
    'Sep_2016' => array(
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
    'Oct_2016' => array(
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
    'Nov_2016' => array(
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
    'Dec_2016' => array(
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
    'Jan_2017' => array(
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
    'Feb_2017' => array(
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
    'Mar_2017' => array(
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
    'expression' => array(
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
  $handler->display->display_options['path'] = 'collection-detail-pdf';
  $handler->display->display_options['default_page_orientation'] = 'L';
  $export['clone_of_fee_collection_summary'] = $view;

  $view = new view();
  $view->name = 'concession_detail';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_concession';
  $view->human_name = 'Concession Detail';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Concession Detail';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'name' => 'name',
    'amount' => 'amount',
    'percentage' => 'percentage',
  );
  $handler->display->display_options['style_options']['default'] = 'adm_no';
  $handler->display->display_options['style_options']['info'] = array(
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'amount' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'percentage' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  /* Relationship: Fee Student Concession: Admission No */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_concession';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Concession: IDs */
  $handler->display->display_options['relationships']['con_id']['id'] = 'con_id';
  $handler->display->display_options['relationships']['con_id']['table'] = 'essa_2016_17_fees_student_concession';
  $handler->display->display_options['relationships']['con_id']['field'] = 'con_id';
  /* Field: Fee Student Concession: Admission No */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_concession';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Concession: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'essa_2016_17_fees_concession';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'con_id';
  $handler->display->display_options['fields']['name']['label'] = 'Concession Type';
  /* Field: Fee Student Concession: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'essa_2016_17_fees_student_concession';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  /* Field: Fee Student Concession: Percentage */
  $handler->display->display_options['fields']['percentage']['id'] = 'percentage';
  $handler->display->display_options['fields']['percentage']['table'] = 'essa_2016_17_fees_student_concession';
  $handler->display->display_options['fields']['percentage']['field'] = 'percentage';
  /* Filter criterion: Fee Concession: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'essa_2016_17_fees_concession';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['relationship'] = 'con_id';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Concession Type';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );
  /* Filter criterion: Fee Student Concession: Admission No */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_concession';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/fees/reports/concession-detail';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Concession Detail';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['concession_detail'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_letter';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s Letter';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Fee Due Detail';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['skip_empty_pages'] = 0;
  $handler->display->display_options['style_plugin'] = 'tablesummarized';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'adm_no',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
    1 => array(
      'field' => 'nothing',
      'rendered' => 0,
      'rendered_strip' => 0,
    ),
    2 => array(
      'field' => 'nothing_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'class' => 'class',
    'particulars' => 'particulars',
    'Mar_2016' => 'Mar_2016',
    'Apr_2016' => 'Apr_2016',
    'May_2016' => 'May_2016',
    'Jul_2016' => 'Jul_2016',
    'Aug_2016' => 'Aug_2016',
    'Sep_2016' => 'Sep_2016',
    'Jun_2016' => 'Jun_2016',
    'Oct_2016' => 'Oct_2016',
    'Nov_2016' => 'Nov_2016',
    'Dec_2016' => 'Dec_2016',
    'Jan_2017' => 'Jan_2017',
    'Feb_2017' => 'Feb_2017',
    'Mar_2017' => 'Mar_2017',
    'expression' => 'expression',
    'last_name' => 'first_name',
    'section' => 'class',
    'nothing' => 'nothing',
    'nothing_1' => 'nothing_1',
  );
  $handler->display->display_options['style_options']['default'] = 'adm_no';
  $handler->display->display_options['style_options']['info'] = array(
    'adm_no' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'summarize' => 'none',
    ),
    'class' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 0,
      'summarize' => 'none',
    ),
    'particulars' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'summarize' => 'none',
    ),
    'Mar_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Apr_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'May_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Jul_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Aug_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Sep_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Jun_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Oct_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Nov_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Dec_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Jan_2017' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Feb_2017' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Mar_2017' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'expression' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'total',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'summarize' => 'none',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'summarize' => 'none',
    ),
    'nothing' => array(
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
      'summarize' => 'none',
    ),
    'nothing_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'summarize' => 'none',
    ),
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Mar_2016 */
  $handler->display->display_options['fields']['Mar_2016']['id'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Mar_2016']['field'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['separator'] = '';
  /* Field: Fee Student Due: Apr_2016 */
  $handler->display->display_options['fields']['Apr_2016']['id'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Apr_2016']['field'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['separator'] = '';
  /* Field: Fee Student Due: May_2016 */
  $handler->display->display_options['fields']['May_2016']['id'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['May_2016']['field'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['separator'] = '';
  /* Field: Fee Student Due: Jul_2016 */
  $handler->display->display_options['fields']['Jul_2016']['id'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jul_2016']['field'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['separator'] = '';
  /* Field: Fee Student Due: Aug_2016 */
  $handler->display->display_options['fields']['Aug_2016']['id'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Aug_2016']['field'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['separator'] = '';
  /* Field: Fee Student Due: Sep_2016 */
  $handler->display->display_options['fields']['Sep_2016']['id'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Sep_2016']['field'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['separator'] = '';
  /* Field: Fee Student Due: Jun_2016 */
  $handler->display->display_options['fields']['Jun_2016']['id'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jun_2016']['field'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['separator'] = '';
  /* Field: Fee Student Due: Oct_2016 */
  $handler->display->display_options['fields']['Oct_2016']['id'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Oct_2016']['field'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['separator'] = '';
  /* Field: Fee Student Due: Nov_2016 */
  $handler->display->display_options['fields']['Nov_2016']['id'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Nov_2016']['field'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['separator'] = '';
  /* Field: Fee Student Due: Dec_2016 */
  $handler->display->display_options['fields']['Dec_2016']['id'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Dec_2016']['field'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['separator'] = '';
  /* Field: Fee Student Due: Jan_2017 */
  $handler->display->display_options['fields']['Jan_2017']['id'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jan_2017']['field'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['separator'] = '';
  /* Field: Fee Student Due: Feb_2017 */
  $handler->display->display_options['fields']['Feb_2017']['id'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Feb_2017']['field'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['separator'] = '';
  /* Field: Fee Student Due: Mar_2017 */
  $handler->display->display_options['fields']['Mar_2017']['id'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Mar_2017']['field'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['separator'] = '';
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['label'] = 'Total';
  $handler->display->display_options['fields']['expression']['precision'] = '0';
  $handler->display->display_options['fields']['expression']['separator'] = '';
  $handler->display->display_options['fields']['expression']['expression'] = '[Mar_2016]+[Apr_2016]+[May_2016]+[Jun_2016]+[Jul_2016]+[Aug_2016]+[Sep_2016]+[Oct_2016]+[Nov_2016]+[Dec_2016]+[Jan_2017]+[Feb_2017]+[Mar_2017]';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<h1>St. Joseph\'s School</h1>
<br>
<h3 style = "text-align: LEFT;">Sub: Fee Defaulter</h3>
<h4 style = "text-align: LEFT;">Dear Parent,</h4>

<p style = "text-align: LEFT;">Your son [first_name] [last_name] with Adm. No([adm_no]), studying in Class([class] - [section]), is due for fees as given - </p>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'NULL';
  $handler->display->display_options['fields']['nothing_1']['exclude'] = TRUE;
  /* Field: PDF: Page Break */
  $handler->display->display_options['fields']['page_break']['id'] = 'page_break';
  $handler->display->display_options['fields']['page_break']['table'] = 'pdf';
  $handler->display->display_options['fields']['page_break']['field'] = 'page_break';
  $handler->display->display_options['fields']['page_break']['last_row'] = 0;
  $handler->display->display_options['fields']['page_break']['every_nth'] = '1';
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'fee-due-letter';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 1;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 1;
  $handler->display->display_options['style_options']['replace_newlines'] = 1;
  $handler->display->display_options['style_options']['newline_token'] = '1';
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['style_options']['keep_html'] = 1;
  $handler->display->display_options['path'] = 'fee-due-detail-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['segment_size'] = '500';

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'fee-due-detail-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: PDF Page */
  $handler = $view->new_display('pdf', 'PDF Page', 'pdf_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'pdf_table';
  $handler->display->display_options['path'] = 'fee-due-pdf';
  $export['defaulter_s_letter'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_april_2016_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(April,2016)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(April,2016)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'Apr_2016_1' => 'Apr_2016_1',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Apr_2016' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'Apr_2016' => '#77a1e5',
    'Apr_2016_1' => '#c42525',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: Apr_2016 */
  $handler->display->display_options['fields']['Apr_2016']['id'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Apr_2016']['field'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['Apr_2016']['label'] = 'Due Date';
  $handler->display->display_options['fields']['Apr_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Apr_2016']['second_date_format'] = 'long';
  /* Field: Fee Student Due: Apr_2016 */
  $handler->display->display_options['fields']['Apr_2016_1']['id'] = 'Apr_2016_1';
  $handler->display->display_options['fields']['Apr_2016_1']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Apr_2016_1']['field'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016_1']['label'] = 'Amount Due';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Student Due: Apr_2016 */
  $handler->display->display_options['filters']['Apr_2016']['id'] = 'Apr_2016';
  $handler->display->display_options['filters']['Apr_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['Apr_2016']['field'] = 'Apr_2016';
  $handler->display->display_options['filters']['Apr_2016']['operator'] = '!=';
  $handler->display->display_options['filters']['Apr_2016']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Apr_2016' => 'Apr_2016',
    'Apr_2016_1' => 'Apr_2016_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Apr_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Apr_2016_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail/defaulter-s-list-april-2016';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Defaulter\'s List(April, 2016)';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-april-2016-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-april-2016-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_april_2016_'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_august_2016_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(August,2016)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(August,2016)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'Aug_2016_1' => 'Aug_2016_1',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Aug_2016' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'Aug_2016' => '#77a1e5',
    'Aug_2016_1' => '#c42525',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: Aug_2016 */
  $handler->display->display_options['fields']['Aug_2016']['id'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Aug_2016']['field'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['Aug_2016']['label'] = 'Due Date';
  $handler->display->display_options['fields']['Aug_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Aug_2016']['second_date_format'] = 'long';
  /* Field: Fee Student Due: Aug_2016 */
  $handler->display->display_options['fields']['Aug_2016_1']['id'] = 'Aug_2016_1';
  $handler->display->display_options['fields']['Aug_2016_1']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Aug_2016_1']['field'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016_1']['label'] = 'Amount Due';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Student Due: Aug_2016 */
  $handler->display->display_options['filters']['Aug_2016']['id'] = 'Aug_2016';
  $handler->display->display_options['filters']['Aug_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['Aug_2016']['field'] = 'Aug_2016';
  $handler->display->display_options['filters']['Aug_2016']['operator'] = '!=';
  $handler->display->display_options['filters']['Aug_2016']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Aug_2016' => 'Aug_2016',
    'Aug_2016_1' => 'Aug_2016_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Aug_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Aug_2016_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail/defaulter-s-list-aug-2016';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Defaulter\'s List(August, 2016)';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-aug-2016-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-aug-2016-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_august_2016_'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_december_2016_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(December,2016)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(November,2016)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'Dec_2016_1' => 'Dec_2016_1',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Dec_2016' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'Dec_2016' => '#77a1e5',
    'Dec_2016_1' => '#c42525',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: Dec_2016 */
  $handler->display->display_options['fields']['Dec_2016']['id'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Dec_2016']['field'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['Dec_2016']['label'] = 'Due Date';
  $handler->display->display_options['fields']['Dec_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Dec_2016']['second_date_format'] = 'long';
  /* Field: Fee Student Due: Dec_2016 */
  $handler->display->display_options['fields']['Dec_2016_1']['id'] = 'Dec_2016_1';
  $handler->display->display_options['fields']['Dec_2016_1']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Dec_2016_1']['field'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016_1']['label'] = 'Amount Due';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Student Due: Dec_2016 */
  $handler->display->display_options['filters']['Dec_2016']['id'] = 'Dec_2016';
  $handler->display->display_options['filters']['Dec_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['Dec_2016']['field'] = 'Dec_2016';
  $handler->display->display_options['filters']['Dec_2016']['operator'] = '!=';
  $handler->display->display_options['filters']['Dec_2016']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Dec_2016' => 'Dec_2016',
    'Dec_2016_1' => 'Dec_2016_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Dec_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Dec_2016_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail/defaulter-s-list-dec-2016';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Defaulter\'s List(December, 2016)';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-dec-2016-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-dec-2016-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_december_2016_'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_feburary_2017_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(Feburary,2017)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(Feburary,2017)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'Feb_2017_1' => 'Feb_2017_1',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Feb_2017' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'Feb_2017' => '#77a1e5',
    'Feb_2017_1' => '#c42525',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: Feb_2017 */
  $handler->display->display_options['fields']['Feb_2017']['id'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Feb_2017']['field'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['Feb_2017']['label'] = 'Due Date';
  $handler->display->display_options['fields']['Feb_2017']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Feb_2017']['second_date_format'] = 'long';
  /* Field: Fee Student Due: Feb_2017 */
  $handler->display->display_options['fields']['Feb_2017_1']['id'] = 'Feb_2017_1';
  $handler->display->display_options['fields']['Feb_2017_1']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Feb_2017_1']['field'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017_1']['label'] = 'Amount Due';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Student Due: Feb_2017 */
  $handler->display->display_options['filters']['Feb_2017']['id'] = 'Feb_2017';
  $handler->display->display_options['filters']['Feb_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['Feb_2017']['field'] = 'Feb_2017';
  $handler->display->display_options['filters']['Feb_2017']['operator'] = '!=';
  $handler->display->display_options['filters']['Feb_2017']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Feb_2017' => 'Feb_2017',
    'Feb_2017_1' => 'Feb_2017_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Feb_2017' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Feb_2017_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail/defaulter-s-list-feb-2017';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Defaulter\'s List(Feburary, 2017)';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-feb-2017-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-feb-2017-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_feburary_2017_'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_january_2017_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(January,2017)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(January,2017)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'Jan_2017_1' => 'Jan_2017_1',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Jan_2017' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'Jan_2017' => '#77a1e5',
    'Jan_2017_1' => '#c42525',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: Jan_2017 */
  $handler->display->display_options['fields']['Jan_2017']['id'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Jan_2017']['field'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['Jan_2017']['label'] = 'Due Date';
  $handler->display->display_options['fields']['Jan_2017']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Jan_2017']['second_date_format'] = 'long';
  /* Field: Fee Student Due: Jan_2017 */
  $handler->display->display_options['fields']['Jan_2017_1']['id'] = 'Jan_2017_1';
  $handler->display->display_options['fields']['Jan_2017_1']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jan_2017_1']['field'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017_1']['label'] = 'Amount Due';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Student Due: Jan_2017 */
  $handler->display->display_options['filters']['Jan_2017']['id'] = 'Jan_2017';
  $handler->display->display_options['filters']['Jan_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['Jan_2017']['field'] = 'Jan_2017';
  $handler->display->display_options['filters']['Jan_2017']['operator'] = '!=';
  $handler->display->display_options['filters']['Jan_2017']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Jan_2017' => 'Jan_2017',
    'Jan_2017_1' => 'Jan_2017_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jan_2017' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jan_2017_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail/defaulter-s-list-jan-2017';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Defaulter\'s List(January, 2017)';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-jan-2017-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-jan-2017-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_january_2017_'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_july_2016_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(July,2016)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(July,2016)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'Jul_2016_1' => 'Jul_2016_1',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Jul_2016' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'Jul_2016' => '#77a1e5',
    'Jul_2016_1' => '#c42525',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: Jul_2016 */
  $handler->display->display_options['fields']['Jul_2016']['id'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Jul_2016']['field'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['Jul_2016']['label'] = 'Due Date';
  $handler->display->display_options['fields']['Jul_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Jul_2016']['second_date_format'] = 'long';
  /* Field: Fee Student Due: Jul_2016 */
  $handler->display->display_options['fields']['Jul_2016_1']['id'] = 'Jul_2016_1';
  $handler->display->display_options['fields']['Jul_2016_1']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jul_2016_1']['field'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016_1']['label'] = 'Amount Due';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Student Due: Jul_2016 */
  $handler->display->display_options['filters']['Jul_2016']['id'] = 'Jul_2016';
  $handler->display->display_options['filters']['Jul_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['Jul_2016']['field'] = 'Jul_2016';
  $handler->display->display_options['filters']['Jul_2016']['operator'] = '!=';
  $handler->display->display_options['filters']['Jul_2016']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Jul_2016' => 'Jul_2016',
    'Jul_2016_1' => 'Jul_2016_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jul_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jul_2016_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail/defaulter-s-list-july-2016';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Defaulter\'s List(July, 2016)';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-july-2016-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-july-2016-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_july_2016_'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_june_2016_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(June,2016)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(June,2016)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'Jun_2016_1' => 'Jun_2016_1',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Jun_2016' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'Jun_2016' => '#77a1e5',
    'Jun_2016_1' => '#c42525',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: Jun_2016 */
  $handler->display->display_options['fields']['Jun_2016']['id'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Jun_2016']['field'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['Jun_2016']['label'] = 'Due Date';
  $handler->display->display_options['fields']['Jun_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Jun_2016']['second_date_format'] = 'long';
  /* Field: Fee Student Due: Jun_2016 */
  $handler->display->display_options['fields']['Jun_2016_1']['id'] = 'Jun_2016_1';
  $handler->display->display_options['fields']['Jun_2016_1']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jun_2016_1']['field'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016_1']['label'] = 'Amount Due';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Student Due: Jun_2016 */
  $handler->display->display_options['filters']['Jun_2016']['id'] = 'Jun_2016';
  $handler->display->display_options['filters']['Jun_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['Jun_2016']['field'] = 'Jun_2016';
  $handler->display->display_options['filters']['Jun_2016']['operator'] = '!=';
  $handler->display->display_options['filters']['Jun_2016']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Jun_2016' => 'Jun_2016',
    'Jun_2016_1' => 'Jun_2016_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jun_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jun_2016_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail/defaulter-s-list-june-2016';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Defaulter\'s List(June, 2016)';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-june-2016-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-june-2016-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_june_2016_'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_march_2016_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(March,2016)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(March,2016)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'Mar_2016' => 'Mar_2016',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Mar_2016_1' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'Mar_2016_1' => '#77a1e5',
    'Mar_2016' => '#a12020',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['empty'] = 'No fee has to be collected for this month.';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: Mar_2016 */
  $handler->display->display_options['fields']['Mar_2016_1']['id'] = 'Mar_2016_1';
  $handler->display->display_options['fields']['Mar_2016_1']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Mar_2016_1']['field'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016_1']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['Mar_2016_1']['label'] = 'Due Date';
  $handler->display->display_options['fields']['Mar_2016_1']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Mar_2016_1']['second_date_format'] = 'long';
  /* Field: Fee Student Due: Mar_2016 */
  $handler->display->display_options['fields']['Mar_2016']['id'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Mar_2016']['field'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['label'] = 'Amount Due';
  /* Filter criterion: Fee Student Due: Mar_2016 */
  $handler->display->display_options['filters']['Mar_2016']['id'] = 'Mar_2016';
  $handler->display->display_options['filters']['Mar_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['Mar_2016']['field'] = 'Mar_2016';
  $handler->display->display_options['filters']['Mar_2016']['operator'] = '!=';
  $handler->display->display_options['filters']['Mar_2016']['value']['value'] = '0';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Mar_2016_1' => 'Mar_2016_1',
    'Mar_2016' => 'Mar_2016',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2016_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail/defaulter-s-list-march-2016';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Defaulter\'s List(March, 2016)';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-march-2016-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-march-2016-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_march_2016_'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_march_2017_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(March,2017)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(Feburary,2017)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'Mar_2017_1' => 'Mar_2017_1',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Mar_2017' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'Mar_2017' => '#77a1e5',
    'Mar_2017_1' => '#c42525',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: Mar_2017 */
  $handler->display->display_options['fields']['Mar_2017']['id'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Mar_2017']['field'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['Mar_2017']['label'] = 'Due Date';
  $handler->display->display_options['fields']['Mar_2017']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Mar_2017']['second_date_format'] = 'long';
  /* Field: Fee Student Due: Mar_2017 */
  $handler->display->display_options['fields']['Mar_2017_1']['id'] = 'Mar_2017_1';
  $handler->display->display_options['fields']['Mar_2017_1']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Mar_2017_1']['field'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017_1']['label'] = 'Amount Due';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Student Due: Mar_2017 */
  $handler->display->display_options['filters']['Mar_2017']['id'] = 'Mar_2017';
  $handler->display->display_options['filters']['Mar_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['Mar_2017']['field'] = 'Mar_2017';
  $handler->display->display_options['filters']['Mar_2017']['operator'] = '!=';
  $handler->display->display_options['filters']['Mar_2017']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Mar_2017' => 'Mar_2017',
    'Mar_2017_1' => 'Mar_2017_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2017' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2017_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'defaulter-s-list-mar-2017';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-mar-2017-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-mar-2017-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_march_2017_'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_may_2016_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(May,2016)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(May,2016)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'May_2016_1' => 'May_2016_1',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'May_2016' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'May_2016' => '#77a1e5',
    'May_2016_1' => '#c42525',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: May_2016 */
  $handler->display->display_options['fields']['May_2016']['id'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['May_2016']['field'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['May_2016']['label'] = 'Due Date';
  $handler->display->display_options['fields']['May_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['May_2016']['second_date_format'] = 'long';
  /* Field: Fee Student Due: May_2016 */
  $handler->display->display_options['fields']['May_2016_1']['id'] = 'May_2016_1';
  $handler->display->display_options['fields']['May_2016_1']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['May_2016_1']['field'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016_1']['label'] = 'Amount Due';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Student Due: May_2016 */
  $handler->display->display_options['filters']['May_2016']['id'] = 'May_2016';
  $handler->display->display_options['filters']['May_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['May_2016']['field'] = 'May_2016';
  $handler->display->display_options['filters']['May_2016']['operator'] = '!=';
  $handler->display->display_options['filters']['May_2016']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'May_2016' => 'May_2016',
    'May_2016_1' => 'May_2016_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'May_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'May_2016_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail/defaulter-s-list-may-2016';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Defaulter\'s List(May, 2016)';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-may-2016-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-may-2016-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_may_2016_'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_november_2016_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(November,2016)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(November,2016)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'Nov_2016_1' => 'Nov_2016_1',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Nov_2016' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'Nov_2016' => '#77a1e5',
    'Nov_2016_1' => '#c42525',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: Nov_2016 */
  $handler->display->display_options['fields']['Nov_2016']['id'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Nov_2016']['field'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['Nov_2016']['label'] = 'Due Date';
  $handler->display->display_options['fields']['Nov_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Nov_2016']['second_date_format'] = 'long';
  /* Field: Fee Student Due: Nov_2016 */
  $handler->display->display_options['fields']['Nov_2016_1']['id'] = 'Nov_2016_1';
  $handler->display->display_options['fields']['Nov_2016_1']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Nov_2016_1']['field'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016_1']['label'] = 'Amount Due';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Student Due: Nov_2016 */
  $handler->display->display_options['filters']['Nov_2016']['id'] = 'Nov_2016';
  $handler->display->display_options['filters']['Nov_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['Nov_2016']['field'] = 'Nov_2016';
  $handler->display->display_options['filters']['Nov_2016']['operator'] = '!=';
  $handler->display->display_options['filters']['Nov_2016']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Nov_2016' => 'Nov_2016',
    'Nov_2016_1' => 'Nov_2016_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Nov_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Nov_2016_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail/defaulter-s-list-nov-2016';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Defaulter\'s List(November, 2016)';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-nov-2016-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-nov-2016-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_november_2016_'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_october_2016_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(October,2016)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(October,2016)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'Oct_2016_1' => 'Oct_2016_1',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Oct_2016' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'Oct_2016' => '#77a1e5',
    'Oct_2016_1' => '#c42525',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: Oct_2016 */
  $handler->display->display_options['fields']['Oct_2016']['id'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Oct_2016']['field'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['Oct_2016']['label'] = 'Amount Due';
  $handler->display->display_options['fields']['Oct_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Oct_2016']['second_date_format'] = 'long';
  /* Field: Fee Student Due: Oct_2016 */
  $handler->display->display_options['fields']['Oct_2016_1']['id'] = 'Oct_2016_1';
  $handler->display->display_options['fields']['Oct_2016_1']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Oct_2016_1']['field'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016_1']['label'] = 'Amount Due';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Student Due: Oct_2016 */
  $handler->display->display_options['filters']['Oct_2016']['id'] = 'Oct_2016';
  $handler->display->display_options['filters']['Oct_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['Oct_2016']['field'] = 'Oct_2016';
  $handler->display->display_options['filters']['Oct_2016']['operator'] = '!=';
  $handler->display->display_options['filters']['Oct_2016']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Oct_2016' => 'Oct_2016',
    'Oct_2016_1' => 'Oct_2016_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Oct_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Oct_2016_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail/defaulter-s-list-oct-2016';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Defaulter\'s List(October, 2016)';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-oct-2016-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-oct-2016-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_october_2016_'] = $view;

  $view = new view();
  $view->name = 'defaulter_s_list_september_2016_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Defaulter\'s List(September,2016)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Defaulter\'s List(September,2016)';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'line';
  $handler->display->display_options['style_options']['title_position'] = 'in';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'Sep_2016_1' => 'Sep_2016_1',
    'fee_id' => 0,
    'particulars' => 0,
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Sep_2016' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'fee_id' => '#2f7ed8',
    'particulars' => '#0d233a',
    'adm_no' => '#8bbc21',
    'first_name' => '#910000',
    'last_name' => '#1aadce',
    'class' => '#492970',
    'section' => '#f28f43',
    'Sep_2016' => '#77a1e5',
    'Sep_2016_1' => '#c42525',
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Structure: Freq ID */
  $handler->display->display_options['relationships']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['relationships']['freq_id']['field'] = 'freq_id';
  $handler->display->display_options['relationships']['freq_id']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Frequencies: Sep_2016 */
  $handler->display->display_options['fields']['Sep_2016']['id'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Sep_2016']['field'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['relationship'] = 'freq_id';
  $handler->display->display_options['fields']['Sep_2016']['label'] = 'Due Date';
  $handler->display->display_options['fields']['Sep_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Sep_2016']['second_date_format'] = 'long';
  /* Field: Fee Student Due: Sep_2016 */
  $handler->display->display_options['fields']['Sep_2016_1']['id'] = 'Sep_2016_1';
  $handler->display->display_options['fields']['Sep_2016_1']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Sep_2016_1']['field'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016_1']['label'] = 'Amount Due';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Student Due: Sep_2016 */
  $handler->display->display_options['filters']['Sep_2016']['id'] = 'Sep_2016';
  $handler->display->display_options['filters']['Sep_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['Sep_2016']['field'] = 'Sep_2016';
  $handler->display->display_options['filters']['Sep_2016']['operator'] = '!=';
  $handler->display->display_options['filters']['Sep_2016']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Sep_2016' => 'Sep_2016',
    'Sep_2016_1' => 'Sep_2016_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Sep_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Sep_2016_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail/defaulter-s-list-sep-2016';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Defaulter\'s List(September, 2016)';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'defaulter-s-list-sep-2016-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'defaulter-s-list-sep-2016-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['defaulter_s_list_september_2016_'] = $view;

  $view = new view();
  $view->name = 'fee_due_detail';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Fee Due Detail';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Fee Due Detail';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
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
    'adm_no' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Mar_2016' => 'Mar_2016',
    'Apr_2016' => 'Apr_2016',
    'May_2016' => 'May_2016',
    'Jun_2016' => 'Jun_2016',
    'Jul_2016' => 'Jul_2016',
    'Aug_2016' => 'Aug_2016',
    'Sep_2016' => 'Sep_2016',
    'Oct_2016' => 'Oct_2016',
    'Nov_2016' => 'Nov_2016',
    'Dec_2016' => 'Dec_2016',
    'Jan_2017' => 'Jan_2017',
    'Feb_2017' => 'Feb_2017',
    'Mar_2017' => 'Mar_2017',
    'expression' => 'expression',
  );
  $handler->display->display_options['style_options']['default'] = 'fee_id';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Apr_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'May_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jun_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jul_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Aug_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Sep_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Oct_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Nov_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Dec_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jan_2017' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Feb_2017' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2017' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'expression' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Student Due: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['label'] = 'Adm No.';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Student Due: Mar_2016 */
  $handler->display->display_options['fields']['Mar_2016']['id'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Mar_2016']['field'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['label'] = 'Mar 2016';
  $handler->display->display_options['fields']['Mar_2016']['separator'] = '';
  /* Field: Fee Student Due: Apr_2016 */
  $handler->display->display_options['fields']['Apr_2016']['id'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Apr_2016']['field'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['label'] = 'Apr 2016';
  $handler->display->display_options['fields']['Apr_2016']['separator'] = '';
  /* Field: Fee Student Due: May_2016 */
  $handler->display->display_options['fields']['May_2016']['id'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['May_2016']['field'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['label'] = 'May 2016';
  $handler->display->display_options['fields']['May_2016']['separator'] = '';
  /* Field: Fee Student Due: Jun_2016 */
  $handler->display->display_options['fields']['Jun_2016']['id'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jun_2016']['field'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['label'] = 'Jun 2016';
  $handler->display->display_options['fields']['Jun_2016']['separator'] = '';
  /* Field: Fee Student Due: Jul_2016 */
  $handler->display->display_options['fields']['Jul_2016']['id'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jul_2016']['field'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['label'] = 'Jul 2016';
  $handler->display->display_options['fields']['Jul_2016']['separator'] = '';
  /* Field: Fee Student Due: Aug_2016 */
  $handler->display->display_options['fields']['Aug_2016']['id'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Aug_2016']['field'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['label'] = 'Aug 2016';
  $handler->display->display_options['fields']['Aug_2016']['separator'] = '';
  /* Field: Fee Student Due: Sep_2016 */
  $handler->display->display_options['fields']['Sep_2016']['id'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Sep_2016']['field'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['label'] = 'Sep 2016';
  $handler->display->display_options['fields']['Sep_2016']['separator'] = '';
  /* Field: Fee Student Due: Oct_2016 */
  $handler->display->display_options['fields']['Oct_2016']['id'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Oct_2016']['field'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['label'] = 'Oct 2016';
  $handler->display->display_options['fields']['Oct_2016']['separator'] = '';
  /* Field: Fee Student Due: Nov_2016 */
  $handler->display->display_options['fields']['Nov_2016']['id'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Nov_2016']['field'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['label'] = 'Nov 2016';
  $handler->display->display_options['fields']['Nov_2016']['separator'] = '';
  /* Field: Fee Student Due: Dec_2016 */
  $handler->display->display_options['fields']['Dec_2016']['id'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Dec_2016']['field'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['label'] = 'Dec 2016';
  $handler->display->display_options['fields']['Dec_2016']['separator'] = '';
  /* Field: Fee Student Due: Jan_2017 */
  $handler->display->display_options['fields']['Jan_2017']['id'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jan_2017']['field'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['label'] = 'Jan 2017';
  $handler->display->display_options['fields']['Jan_2017']['separator'] = '';
  /* Field: Fee Student Due: Feb_2017 */
  $handler->display->display_options['fields']['Feb_2017']['id'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Feb_2017']['field'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['label'] = 'Feb 2017';
  $handler->display->display_options['fields']['Feb_2017']['separator'] = '';
  /* Field: Fee Student Due: Mar_2017 */
  $handler->display->display_options['fields']['Mar_2017']['id'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Mar_2017']['field'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['label'] = 'Mar 2017';
  $handler->display->display_options['fields']['Mar_2017']['separator'] = '';
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['label'] = 'Total';
  $handler->display->display_options['fields']['expression']['precision'] = '0';
  $handler->display->display_options['fields']['expression']['expression'] = '[Mar_2016]+[Apr_2016]+[May_2016]+[Jun_2016]+[Jul_2016]+[Aug_2016]+[Sep_2016]+[Oct_2016]+[Nov_2016]+[Dec_2016]+[Jan_2017]+[Feb_2017]+[Mar_2017]';
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Fee ID */
  $handler->display->display_options['filters']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['filters']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['fee_id']['field'] = 'fee_id';
  $handler->display->display_options['filters']['fee_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['fee_id']['expose']['operator_id'] = 'fee_id_op';
  $handler->display->display_options['filters']['fee_id']['expose']['label'] = 'Fee ID';
  $handler->display->display_options['filters']['fee_id']['expose']['operator'] = 'fee_id_op';
  $handler->display->display_options['filters']['fee_id']['expose']['identifier'] = 'fee_id';
  $handler->display->display_options['filters']['fee_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'fee-due-detail-1';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'fee-due-detail-csv-1';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['segment_size'] = '100';

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'fee-due-detail-xls-1';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $export['fee_due_detail'] = $view;

  $view = new view();
  $view->name = 'fee_due_test';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Fee Due Test';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Fee Due Detail';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'tablesummarized';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'adm_no',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'class' => 'class',
    'particulars' => 'particulars',
    'Mar_2016' => 'Mar_2016',
    'Apr_2016' => 'Apr_2016',
    'May_2016' => 'May_2016',
    'Jul_2016' => 'Jul_2016',
    'Aug_2016' => 'Aug_2016',
    'Sep_2016' => 'Sep_2016',
    'Jun_2016' => 'Jun_2016',
    'Oct_2016' => 'Oct_2016',
    'Nov_2016' => 'Nov_2016',
    'Dec_2016' => 'Dec_2016',
    'Jan_2017' => 'Jan_2017',
    'Feb_2017' => 'Feb_2017',
    'Mar_2017' => 'Mar_2017',
    'expression' => 'expression',
    'last_name' => 'first_name',
    'section' => 'class',
  );
  $handler->display->display_options['style_options']['default'] = 'adm_no';
  $handler->display->display_options['style_options']['info'] = array(
    'adm_no' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'summarize' => 'none',
    ),
    'class' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 0,
      'summarize' => 'none',
    ),
    'particulars' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'summarize' => 'none',
    ),
    'Mar_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Apr_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'May_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Jul_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Aug_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Sep_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Jun_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Oct_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Nov_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Dec_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Jan_2017' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Feb_2017' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'Mar_2017' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'none',
    ),
    'expression' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'summarize' => 'total',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'summarize' => 'none',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'summarize' => 'none',
    ),
  );
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Due: Mar_2016 */
  $handler->display->display_options['fields']['Mar_2016']['id'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Mar_2016']['field'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['separator'] = '';
  /* Field: Fee Student Due: Apr_2016 */
  $handler->display->display_options['fields']['Apr_2016']['id'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Apr_2016']['field'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['separator'] = '';
  /* Field: Fee Student Due: May_2016 */
  $handler->display->display_options['fields']['May_2016']['id'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['May_2016']['field'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['separator'] = '';
  /* Field: Fee Student Due: Jul_2016 */
  $handler->display->display_options['fields']['Jul_2016']['id'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jul_2016']['field'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['separator'] = '';
  /* Field: Fee Student Due: Aug_2016 */
  $handler->display->display_options['fields']['Aug_2016']['id'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Aug_2016']['field'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['separator'] = '';
  /* Field: Fee Student Due: Sep_2016 */
  $handler->display->display_options['fields']['Sep_2016']['id'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Sep_2016']['field'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['separator'] = '';
  /* Field: Fee Student Due: Jun_2016 */
  $handler->display->display_options['fields']['Jun_2016']['id'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jun_2016']['field'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['separator'] = '';
  /* Field: Fee Student Due: Oct_2016 */
  $handler->display->display_options['fields']['Oct_2016']['id'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Oct_2016']['field'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['separator'] = '';
  /* Field: Fee Student Due: Nov_2016 */
  $handler->display->display_options['fields']['Nov_2016']['id'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Nov_2016']['field'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['separator'] = '';
  /* Field: Fee Student Due: Dec_2016 */
  $handler->display->display_options['fields']['Dec_2016']['id'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Dec_2016']['field'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['separator'] = '';
  /* Field: Fee Student Due: Jan_2017 */
  $handler->display->display_options['fields']['Jan_2017']['id'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jan_2017']['field'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['separator'] = '';
  /* Field: Fee Student Due: Feb_2017 */
  $handler->display->display_options['fields']['Feb_2017']['id'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Feb_2017']['field'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['separator'] = '';
  /* Field: Fee Student Due: Mar_2017 */
  $handler->display->display_options['fields']['Mar_2017']['id'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Mar_2017']['field'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['separator'] = '';
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['label'] = 'Total';
  $handler->display->display_options['fields']['expression']['precision'] = '0';
  $handler->display->display_options['fields']['expression']['separator'] = '';
  $handler->display->display_options['fields']['expression']['expression'] = '[Mar_2016]+[Apr_2016]+[May_2016]+[Jun_2016]+[Jul_2016]+[Aug_2016]+[Sep_2016]+[Oct_2016]+[Nov_2016]+[Dec_2016]+[Jan_2017]+[Feb_2017]+[Mar_2017]';
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/fees/reports/fee-due-detail';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Fee Due Detail';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 1;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 1;
  $handler->display->display_options['style_options']['replace_newlines'] = 1;
  $handler->display->display_options['style_options']['newline_token'] = '1';
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['style_options']['keep_html'] = 1;
  $handler->display->display_options['path'] = 'fee-due-detail-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['segment_size'] = '500';

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'fee-due-detail-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $export['fee_due_test'] = $view;

  $view = new view();
  $view->name = 'fee_frequency';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_frequency';
  $view->human_name = 'Fee Frequency';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Fee Frequency';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'freq_id' => 'freq_id',
    'freq_name' => 'freq_name',
    'Mar_2016' => 'Mar_2016',
    'Apr_2016' => 'Apr_2016',
    'May_2016' => 'May_2016',
    'Jun_2016' => 'Jun_2016',
    'Jul_2016' => 'Jul_2016',
    'Aug_2016' => 'Aug_2016',
    'Sep_2016' => 'Sep_2016',
    'Oct_2016' => 'Oct_2016',
    'Nov_2016' => 'Nov_2016',
    'Dec_2016' => 'Dec_2016',
    'Jan_2017' => 'Jan_2017',
    'Feb_2017' => 'Feb_2017',
    'Mar_2017' => 'Mar_2017',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'freq_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'freq_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Apr_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'May_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jun_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jul_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Aug_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Sep_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Oct_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Nov_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Dec_2016' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jan_2017' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Feb_2017' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2017' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  /* Field: Fee Frequencies: Frequency ID */
  $handler->display->display_options['fields']['freq_id']['id'] = 'freq_id';
  $handler->display->display_options['fields']['freq_id']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['freq_id']['field'] = 'freq_id';
  /* Field: Fee Frequencies: Frequency */
  $handler->display->display_options['fields']['freq_name']['id'] = 'freq_name';
  $handler->display->display_options['fields']['freq_name']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['freq_name']['field'] = 'freq_name';
  /* Field: Fee Frequencies: Mar_2016 */
  $handler->display->display_options['fields']['Mar_2016']['id'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Mar_2016']['field'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Mar_2016']['second_date_format'] = 'long';
  /* Field: Fee Frequencies: Apr_2016 */
  $handler->display->display_options['fields']['Apr_2016']['id'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Apr_2016']['field'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Apr_2016']['second_date_format'] = 'long';
  /* Field: Fee Frequencies: May_2016 */
  $handler->display->display_options['fields']['May_2016']['id'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['May_2016']['field'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['May_2016']['second_date_format'] = 'long';
  /* Field: Fee Frequencies: Jun_2016 */
  $handler->display->display_options['fields']['Jun_2016']['id'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Jun_2016']['field'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Jun_2016']['second_date_format'] = 'long';
  /* Field: Fee Frequencies: Jul_2016 */
  $handler->display->display_options['fields']['Jul_2016']['id'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Jul_2016']['field'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Jul_2016']['second_date_format'] = 'long';
  /* Field: Fee Frequencies: Aug_2016 */
  $handler->display->display_options['fields']['Aug_2016']['id'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Aug_2016']['field'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Aug_2016']['second_date_format'] = 'long';
  /* Field: Fee Frequencies: Sep_2016 */
  $handler->display->display_options['fields']['Sep_2016']['id'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Sep_2016']['field'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Sep_2016']['second_date_format'] = 'long';
  /* Field: Fee Frequencies: Oct_2016 */
  $handler->display->display_options['fields']['Oct_2016']['id'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Oct_2016']['field'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Oct_2016']['second_date_format'] = 'long';
  /* Field: Fee Frequencies: Nov_2016 */
  $handler->display->display_options['fields']['Nov_2016']['id'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Nov_2016']['field'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Nov_2016']['second_date_format'] = 'long';
  /* Field: Fee Frequencies: Dec_2016 */
  $handler->display->display_options['fields']['Dec_2016']['id'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Dec_2016']['field'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Dec_2016']['second_date_format'] = 'long';
  /* Field: Fee Frequencies: Jan_2017 */
  $handler->display->display_options['fields']['Jan_2017']['id'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Jan_2017']['field'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Jan_2017']['second_date_format'] = 'long';
  /* Field: Fee Frequencies: Feb_2017 */
  $handler->display->display_options['fields']['Feb_2017']['id'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Feb_2017']['field'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Feb_2017']['second_date_format'] = 'long';
  /* Field: Fee Frequencies: Mar_2017 */
  $handler->display->display_options['fields']['Mar_2017']['id'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['table'] = 'essa_2016_17_fees_frequency';
  $handler->display->display_options['fields']['Mar_2017']['field'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['Mar_2017']['second_date_format'] = 'long';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['fee_frequency'] = $view;

  $view = new view();
  $view->name = 'month_wise_collection';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_payment_history';
  $view->human_name = 'Month-Wise Collection';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Month-Wise Collection';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'collect fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'payment_date' => 'payment_date',
    'amount' => 'amount',
  );
  $handler->display->display_options['style_options']['default'] = 'payment_date';
  $handler->display->display_options['style_options']['info'] = array(
    'payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 1,
      'aggr' => array(
        'views_aggregator_group_and_compress' => 'views_aggregator_group_and_compress',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'amount' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  /* Field: Fee Payment History: Payment Date */
  $handler->display->display_options['fields']['payment_date']['id'] = 'payment_date';
  $handler->display->display_options['fields']['payment_date']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['fields']['payment_date']['field'] = 'payment_date';
  $handler->display->display_options['fields']['payment_date']['label'] = 'Month';
  $handler->display->display_options['fields']['payment_date']['date_format'] = 'm_y';
  $handler->display->display_options['fields']['payment_date']['second_date_format'] = 'long';
  /* Field: Fee Payment History: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['group_type'] = 'sum';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/fees/reports/month-wise-collection';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Month-wise Collection';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['enabled'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'month-wise-collection-csv';
  $handler->display->display_options['displays'] = array(
    'default' => 0,
    'page' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['enabled'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 1;
  $handler->display->display_options['path'] = 'month-wise-collection-xls';
  $handler->display->display_options['displays'] = array(
    'default' => 0,
    'page' => 0,
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $export['month_wise_collection'] = $view;

  $view = new view();
  $view->name = 'monthly_collection';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_payment_history';
  $view->human_name = 'Monthly collection';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Collection Summary';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'collect fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
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
    'payment_date' => array(
      'bef_format' => 'bef_datepicker',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
    'payment_date_1' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
    'adm_no' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'column';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'amount' => 'amount',
    'id' => 0,
    'adm_no' => 0,
    'class' => 0,
    'section' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'payment_date' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'id' => '#2f7ed8',
    'adm_no' => '#0d233a',
    'class' => '#8bbc21',
    'section' => '#910000',
    'first_name' => '#1aadce',
    'last_name' => '#492970',
    'payment_date' => '#f28f43',
    'amount' => '#0099a7',
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = 'NOTE';
  $handler->display->display_options['header']['area']['content'] = 'NOTE: Some fees may be adjusted on special orders of competent authority. In that case, total fee collected and total due may differ.';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* Relationship: Fee Payment History: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Payment History: UID */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Fee Payment History: Edit UID */
  $handler->display->display_options['relationships']['edit_uid']['id'] = 'edit_uid';
  $handler->display->display_options['relationships']['edit_uid']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['relationships']['edit_uid']['field'] = 'edit_uid';
  /* Field: Fee Payment History: ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = 'Receipt No.';
  /* Field: Fee Payment History: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['label'] = 'Adm No.';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Fee Payment History: Payment Date */
  $handler->display->display_options['fields']['payment_date']['id'] = 'payment_date';
  $handler->display->display_options['fields']['payment_date']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['fields']['payment_date']['field'] = 'payment_date';
  $handler->display->display_options['fields']['payment_date']['label'] = 'Date';
  $handler->display->display_options['fields']['payment_date']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['payment_date']['second_date_format'] = 'long';
  /* Field: Fee Payment History: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  /* Field: Fees Edit Staff: Emp ID */
  $handler->display->display_options['fields']['emp_id']['id'] = 'emp_id';
  $handler->display->display_options['fields']['emp_id']['table'] = 'essa_2016_17_fees_staff';
  $handler->display->display_options['fields']['emp_id']['field'] = 'emp_id';
  $handler->display->display_options['fields']['emp_id']['relationship'] = 'uid';
  $handler->display->display_options['fields']['emp_id']['label'] = 'Collected By';
  /* Field: Fees Edit Staff: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'essa_2016_17_fees_staff';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  /* Field: Fees Edit Staff: Emp ID */
  $handler->display->display_options['fields']['emp_id_1']['id'] = 'emp_id_1';
  $handler->display->display_options['fields']['emp_id_1']['table'] = 'essa_2016_17_fees_staff';
  $handler->display->display_options['fields']['emp_id_1']['field'] = 'emp_id';
  $handler->display->display_options['fields']['emp_id_1']['relationship'] = 'edit_uid';
  $handler->display->display_options['fields']['emp_id_1']['label'] = 'Last Edited By';
  /* Field: Fees Edit Staff: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'essa_2016_17_fees_staff';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'edit_uid';
  /* Filter criterion: Fee Payment History: Payment Date */
  $handler->display->display_options['filters']['payment_date']['id'] = 'payment_date';
  $handler->display->display_options['filters']['payment_date']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['filters']['payment_date']['field'] = 'payment_date';
  $handler->display->display_options['filters']['payment_date']['operator'] = 'between';
  $handler->display->display_options['filters']['payment_date']['exposed'] = TRUE;
  $handler->display->display_options['filters']['payment_date']['expose']['operator_id'] = 'payment_date_op';
  $handler->display->display_options['filters']['payment_date']['expose']['label'] = 'Payment Date';
  $handler->display->display_options['filters']['payment_date']['expose']['operator'] = 'payment_date_op';
  $handler->display->display_options['filters']['payment_date']['expose']['identifier'] = 'payment_date';
  $handler->display->display_options['filters']['payment_date']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['payment_date']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Payment History: Payment Date */
  $handler->display->display_options['filters']['payment_date_1']['id'] = 'payment_date_1';
  $handler->display->display_options['filters']['payment_date_1']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['filters']['payment_date_1']['field'] = 'payment_date';
  $handler->display->display_options['filters']['payment_date_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['payment_date_1']['expose']['operator_id'] = 'payment_date_1_op';
  $handler->display->display_options['filters']['payment_date_1']['expose']['label'] = 'Payment Date';
  $handler->display->display_options['filters']['payment_date_1']['expose']['operator'] = 'payment_date_1_op';
  $handler->display->display_options['filters']['payment_date_1']['expose']['identifier'] = 'payment_date_1';
  $handler->display->display_options['filters']['payment_date_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['payment_date_1']['group_info']['label'] = 'Payment Date';
  $handler->display->display_options['filters']['payment_date_1']['group_info']['identifier'] = 'payment_date_1';
  $handler->display->display_options['filters']['payment_date_1']['group_info']['remember'] = 1;
  $handler->display->display_options['filters']['payment_date_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Mar,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-03-01 00:00:00',
        'max' => '2016-03-31 00:00:00',
      ),
    ),
    2 => array(
      'title' => 'Apr,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-04-01 00:00:00',
        'max' => '2016-04-31 00:00:00',
      ),
    ),
    3 => array(
      'title' => 'May,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-05-01 00:00:00',
        'max' => '2016-05-31 00:00:00',
      ),
    ),
    4 => array(
      'title' => 'Jun,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-06-01 00:00:00',
        'max' => '2016-06-31 00:00:00',
      ),
    ),
    5 => array(
      'title' => 'Jul,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-07-01 00:00:00',
        'max' => '2016-07-31 00:00:00',
      ),
    ),
    6 => array(
      'title' => 'Aug,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-08-01 00:00:00',
        'max' => '2016-08-31 00:00:00',
      ),
    ),
    7 => array(
      'title' => 'Sep,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-09-01 00:00:00',
        'max' => '2016-09-31 00:00:00',
      ),
    ),
    8 => array(
      'title' => 'Oct,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-10-01 00:00:00',
        'max' => '2016-10-31 00:00:00',
      ),
    ),
    9 => array(
      'title' => 'Nov,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-11-01 00:00:00',
        'max' => '2016-11-31 00:00:00',
      ),
    ),
    10 => array(
      'title' => 'Dec,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-12-01 00:00:00',
        'max' => '2016-12-31 00:00:00',
      ),
    ),
    11 => array(
      'title' => 'Jan,2017',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2017-01-01 00:00:00',
        'max' => '2017-01-31 00:00:00',
      ),
    ),
    12 => array(
      'title' => 'Feb,2017',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2017-02-01 00:00:00',
        'max' => '2017-02-31 00:00:00',
      ),
    ),
    13 => array(
      'title' => 'Mar,2017',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2017-03-01 00:00:00',
        'max' => '2017-03-31 00:00:00',
      ),
    ),
  );
  /* Filter criterion: Fee Payment History: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'adm_no' => 'adm_no',
    'class' => 'class',
    'section' => 'class',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'payment_date' => 'payment_date',
    'amount' => 'amount',
    'emp_id' => 'emp_id',
    'name' => 'emp_id',
    'emp_id_1' => 'emp_id_1',
    'name_1' => 'emp_id_1',
  );
  $handler->display->display_options['style_options']['default'] = 'id';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'payment_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'amount' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'emp_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'emp_id_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'name_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/monthly-collection';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Collection Summary';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'monthly-collection-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'monthly-collection-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: PDF Page */
  $handler = $view->new_display('pdf', 'PDF Page', 'pdf_1');
  $handler->display->display_options['enabled'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'pdf_table';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'adm_no' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'class' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'section' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'first_name' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'last_name' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'payment_date' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'amount' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'x' => '10',
    'y' => '10',
    'width' => '200',
    'row_height' => '10',
  );
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<h1 style= "margin-left: 20px;"> Collection Summary Report<h1>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['path'] = 'monthly-collection-pdf';
  $handler->display->display_options['displays'] = array(
    'default' => 0,
    'page' => 0,
  );
  $handler->display->display_options['margin_left'] = '50';
  $handler->display->display_options['margin_top'] = '150';
  $handler->display->display_options['css_file'] = 'sites/all/themes/adminimal_theme/css/print.css';

  /* Display: monthly-collection-chart */
  $handler = $view->new_display('block', 'monthly-collection-chart', 'block_1');
  $handler->display->display_options['display_description'] = 'monthly-collection-chart';

  /* Display: Attachment 2 */
  $handler = $view->new_display('attachment', 'Attachment 2', 'attachment_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
    'block_1' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['monthly_collection'] = $view;

  $view = new view();
  $view->name = 'monthly_day_wise_collection';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_payment_history';
  $view->human_name = 'Monthly day-wise collection';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Day-Wise Collection Summary';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'collect fees';
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
    'payment_date' => array(
      'bef_format' => 'bef_datepicker',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
    'payment_date_1' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'column';
  $handler->display->display_options['style_options']['legend_position'] = 'top';
  $handler->display->display_options['style_options']['label_field'] = 'payment_date';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'amount' => 'amount',
    'payment_date' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'payment_date' => '#f28f43',
    'amount' => '#7c2294',
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  /* Relationship: Fee Payment History: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Field: Fee Payment History: Payment Date */
  $handler->display->display_options['fields']['payment_date']['id'] = 'payment_date';
  $handler->display->display_options['fields']['payment_date']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['fields']['payment_date']['field'] = 'payment_date';
  $handler->display->display_options['fields']['payment_date']['label'] = 'Date';
  $handler->display->display_options['fields']['payment_date']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['payment_date']['second_date_format'] = 'long';
  /* Field: SUM(Fee Payment History: Amount) */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['group_type'] = 'sum';
  /* Filter criterion: Fee Payment History: Payment Date */
  $handler->display->display_options['filters']['payment_date']['id'] = 'payment_date';
  $handler->display->display_options['filters']['payment_date']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['filters']['payment_date']['field'] = 'payment_date';
  $handler->display->display_options['filters']['payment_date']['operator'] = 'between';
  $handler->display->display_options['filters']['payment_date']['exposed'] = TRUE;
  $handler->display->display_options['filters']['payment_date']['expose']['operator_id'] = 'payment_date_op';
  $handler->display->display_options['filters']['payment_date']['expose']['label'] = 'Payment Date';
  $handler->display->display_options['filters']['payment_date']['expose']['operator'] = 'payment_date_op';
  $handler->display->display_options['filters']['payment_date']['expose']['identifier'] = 'payment_date';
  $handler->display->display_options['filters']['payment_date']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['payment_date']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Payment History: Payment Date */
  $handler->display->display_options['filters']['payment_date_1']['id'] = 'payment_date_1';
  $handler->display->display_options['filters']['payment_date_1']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['filters']['payment_date_1']['field'] = 'payment_date';
  $handler->display->display_options['filters']['payment_date_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['payment_date_1']['expose']['operator_id'] = 'payment_date_1_op';
  $handler->display->display_options['filters']['payment_date_1']['expose']['label'] = 'Payment Date';
  $handler->display->display_options['filters']['payment_date_1']['expose']['operator'] = 'payment_date_1_op';
  $handler->display->display_options['filters']['payment_date_1']['expose']['identifier'] = 'payment_date_1';
  $handler->display->display_options['filters']['payment_date_1']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['payment_date_1']['group_info']['label'] = 'Payment Date';
  $handler->display->display_options['filters']['payment_date_1']['group_info']['identifier'] = 'payment_date_1';
  $handler->display->display_options['filters']['payment_date_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Mar,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-03-01 00:00:00',
        'max' => '2016-03-31 00:00:00',
      ),
    ),
    2 => array(
      'title' => 'Apr,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-04-01 00:00:00',
        'max' => '2016-04-31 00:00:00',
      ),
    ),
    3 => array(
      'title' => 'May,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-05-01 00:00:00',
        'max' => '2016-05-31 00:00:00',
      ),
    ),
    4 => array(
      'title' => 'Jun,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-06-01 00:00:00',
        'max' => '2016-06-31 00:00:00',
      ),
    ),
    5 => array(
      'title' => 'Jul,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-07-01 00:00:00',
        'max' => '2016-07-31 00:00:00',
      ),
    ),
    6 => array(
      'title' => 'Aug,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-08-01 00:00:00',
        'max' => '2016-08-31 00:00:00',
      ),
    ),
    7 => array(
      'title' => 'Sep,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-09-01 00:00:00',
        'max' => '2016-09-31 00:00:00',
      ),
    ),
    8 => array(
      'title' => 'Oct,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-10-01 00:00:00',
        'max' => '2016-10-31 00:00:00',
      ),
    ),
    9 => array(
      'title' => 'Nov,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-11-01 00:00:00',
        'max' => '2016-11-31 00:00:00',
      ),
    ),
    10 => array(
      'title' => 'Dec,2016',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2016-12-01 00:00:00',
        'max' => '2016-12-31 00:00:00',
      ),
    ),
    11 => array(
      'title' => 'Jan,2017',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2017-01-01 00:00:00',
        'max' => '2017-01-31 00:00:00',
      ),
    ),
    12 => array(
      'title' => 'Mar,2017',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2017-03-01 00:00:00',
        'max' => '2017-03-31 00:00:00',
      ),
    ),
    13 => array(
      'title' => 'Feb,2017',
      'operator' => 'between',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '2017-02-01 00:00:00',
        'max' => '2017-02-31 00:00:00',
      ),
    ),
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'payment_date' => 'payment_date',
    'amount' => 'amount',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'payment_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'amount' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'admin/fees/reports/day-wise-collection';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Monthly day-wise Collection';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'day-wise-collection-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'day-wise-collection-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: PDF Page */
  $handler = $view->new_display('pdf', 'PDF Page', 'pdf_1');
  $handler->display->display_options['enabled'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'pdf_table';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'adm_no' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'class' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'section' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'first_name' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'last_name' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'payment_date' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'amount' => array(
      'header_style' => array(
        'text' => array(
          'font_size' => '',
          'font_family' => 'default',
          'font_style' => array(
            'b' => 'b',
            'u' => 'u',
            'i' => 0,
            'd' => 0,
            'o' => 0,
          ),
          'align' => NULL,
          'hyphenate' => NULL,
          'color' => '#6495ED',
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
    'x' => '10',
    'y' => '10',
    'width' => '200',
    'row_height' => '10',
  );
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<h1 style= "margin-left: 20px;"> Collection Summary Report<h1>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['path'] = 'monthly-collection-pdf';
  $handler->display->display_options['displays'] = array(
    'default' => 0,
    'page' => 0,
  );
  $handler->display->display_options['margin_left'] = '50';
  $handler->display->display_options['margin_top'] = '150';
  $handler->display->display_options['css_file'] = 'sites/all/themes/adminimal_theme/css/print.css';

  /* Display: monthly-collection-chart */
  $handler = $view->new_display('block', 'monthly-collection-chart', 'block_1');
  $handler->display->display_options['enabled'] = FALSE;
  $handler->display->display_options['display_description'] = 'monthly-collection-chart';

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
    'block_1' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;

  /* Display: Block 2 */
  $handler = $view->new_display('block', 'Block 2', 'block_2');
  $export['monthly_day_wise_collection'] = $view;

  $view = new view();
  $view->name = 'student_concession';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_concession';
  $view->human_name = 'Student Concession';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Student Concession';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
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
    'adm_no' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'amount' => 'amount',
    'percentage' => 'percentage',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'adm_no' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'amount' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'percentage' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  /* Relationship: Fee Student Concession: Admission No */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_concession';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Concession: IDs */
  $handler->display->display_options['relationships']['con_id']['id'] = 'con_id';
  $handler->display->display_options['relationships']['con_id']['table'] = 'essa_2016_17_fees_student_concession';
  $handler->display->display_options['relationships']['con_id']['field'] = 'con_id';
  /* Field: Fee Student Concession: Admission No */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_concession';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Concession: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'essa_2016_17_fees_concession';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'con_id';
  $handler->display->display_options['fields']['name']['label'] = 'Concession Type';
  /* Field: Fee Student Concession: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'essa_2016_17_fees_student_concession';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  /* Field: Fee Student Concession: Percentage */
  $handler->display->display_options['fields']['percentage']['id'] = 'percentage';
  $handler->display->display_options['fields']['percentage']['table'] = 'essa_2016_17_fees_student_concession';
  $handler->display->display_options['fields']['percentage']['field'] = 'percentage';
  /* Filter criterion: Fee Student Concession: Admission No */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_concession';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Concession: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'essa_2016_17_fees_concession';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['relationship'] = 'con_id';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Concession Type';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'student-concession';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $export['student_concession'] = $view;

  $view = new view();
  $view->name = 'student_wise_fee_collection';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_payment';
  $view->human_name = 'Student wise fee collection';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Student wise fee collection';
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
    'particulars' => array(
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
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'class' => 'class',
    'last_name' => 'first_name',
    'section' => 'class',
    'receipt_no' => 'receipt_no',
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'amount' => 'amount',
  );
  $handler->display->display_options['style_options']['default'] = 'adm_no';
  $handler->display->display_options['style_options']['info'] = array(
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'receipt_no' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'amount' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  /* Relationship: Fee Student Payment: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Payment: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Relationship: Fee Student Payment: Receipt No. */
  $handler->display->display_options['relationships']['receipt_no']['id'] = 'receipt_no';
  $handler->display->display_options['relationships']['receipt_no']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['relationships']['receipt_no']['field'] = 'receipt_no';
  /* Field: Fee Student Payment: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: Fee Student Payment: Receipt No. */
  $handler->display->display_options['fields']['receipt_no']['id'] = 'receipt_no';
  $handler->display->display_options['fields']['receipt_no']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['receipt_no']['field'] = 'receipt_no';
  /* Field: Fee Student Payment: Fee ID */
  $handler->display->display_options['fields']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['fee_id']['field'] = 'fee_id';
  $handler->display->display_options['fields']['fee_id']['exclude'] = TRUE;
  /* Field: Fee Structure: Particulars */
  $handler->display->display_options['fields']['particulars']['id'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['fields']['particulars']['field'] = 'particulars';
  $handler->display->display_options['fields']['particulars']['relationship'] = 'fee_id';
  /* Field: Fee Student Payment: Month */
  $handler->display->display_options['fields']['month']['id'] = 'month';
  $handler->display->display_options['fields']['month']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['month']['field'] = 'month';
  /* Field: Fee Payment History: Payment Date */
  $handler->display->display_options['fields']['payment_date']['id'] = 'payment_date';
  $handler->display->display_options['fields']['payment_date']['table'] = 'essa_2016_17_fees_payment_history';
  $handler->display->display_options['fields']['payment_date']['field'] = 'payment_date';
  $handler->display->display_options['fields']['payment_date']['relationship'] = 'receipt_no';
  $handler->display->display_options['fields']['payment_date']['date_format'] = 'dmy';
  $handler->display->display_options['fields']['payment_date']['second_date_format'] = 'long';
  /* Field: Fee Student Payment: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );
  /* Filter criterion: Fee Student Payment: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_payment';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/fees/reports/student-wise-fee-collection';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Student-wise Fee Collection';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'student-wise-fee-collection-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'student-wise-fee-collection-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $export['student_wise_fee_collection'] = $view;

  $view = new view();
  $view->name = 'student_wise_fee_due';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'essa_2016_17_fees_student_due';
  $view->human_name = 'Student wise fee due';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Student Wise Fee Due';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fees';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
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
    'adm_no' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
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
        ),
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
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'fee_id' => 'fee_id',
    'particulars' => 'particulars',
    'adm_no' => 'adm_no',
    'first_name' => 'first_name',
    'last_name' => 'first_name',
    'class' => 'class',
    'section' => 'class',
    'Mar_2016' => 'Mar_2016',
    'Apr_2016' => 'Apr_2016',
    'May_2016' => 'May_2016',
    'Jun_2016' => 'Jun_2016',
    'Jul_2016' => 'Jul_2016',
    'Aug_2016' => 'Aug_2016',
    'Sep_2016' => 'Sep_2016',
    'Oct_2016' => 'Oct_2016',
    'Nov_2016' => 'Nov_2016',
    'Dec_2016' => 'Dec_2016',
    'Jan_2017' => 'Jan_2017',
    'Feb_2017' => 'Feb_2017',
    'Mar_2017' => 'Mar_2017',
    'expression' => 'expression',
  );
  $handler->display->display_options['style_options']['default'] = 'adm_no';
  $handler->display->display_options['style_options']['info'] = array(
    'fee_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'particulars' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'adm_no' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'class' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'section' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Apr_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'May_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jun_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jul_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Aug_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Sep_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Oct_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Nov_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Dec_2016' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Jan_2017' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Feb_2017' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'Mar_2017' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'expression' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['column_aggregation']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['column_aggregation']['totals_row_position'] = array(
    1 => 0,
    2 => '2',
  );
  $handler->display->display_options['style_options']['column_aggregation']['precision'] = '2';
  /* Relationship: Fee Student Due: Admission No. */
  $handler->display->display_options['relationships']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['relationships']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['adm_no']['field'] = 'adm_no';
  /* Relationship: Fee Student Due: Fee ID */
  $handler->display->display_options['relationships']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['relationships']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['relationships']['fee_id']['field'] = 'fee_id';
  /* Field: Fee Student Due: Admission No. */
  $handler->display->display_options['fields']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['fields']['adm_no']['label'] = 'Adm No.';
  /* Field: Student Master Table: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['relationship'] = 'adm_no';
  $handler->display->display_options['fields']['first_name']['label'] = 'Name';
  /* Field: Student Master Table: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Student Master Table: Class */
  $handler->display->display_options['fields']['class']['id'] = 'class';
  $handler->display->display_options['fields']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['class']['field'] = 'class';
  $handler->display->display_options['fields']['class']['relationship'] = 'adm_no';
  /* Field: Student Master Table: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  /* Field: SUM(Fee Student Due: Mar_2016) */
  $handler->display->display_options['fields']['Mar_2016']['id'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Mar_2016']['field'] = 'Mar_2016';
  $handler->display->display_options['fields']['Mar_2016']['group_type'] = 'sum';
  $handler->display->display_options['fields']['Mar_2016']['label'] = 'Mar 2016';
  $handler->display->display_options['fields']['Mar_2016']['separator'] = '';
  /* Field: SUM(Fee Student Due: Apr_2016) */
  $handler->display->display_options['fields']['Apr_2016']['id'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Apr_2016']['field'] = 'Apr_2016';
  $handler->display->display_options['fields']['Apr_2016']['group_type'] = 'sum';
  $handler->display->display_options['fields']['Apr_2016']['label'] = 'Apr 2016';
  $handler->display->display_options['fields']['Apr_2016']['separator'] = '';
  /* Field: SUM(Fee Student Due: May_2016) */
  $handler->display->display_options['fields']['May_2016']['id'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['May_2016']['field'] = 'May_2016';
  $handler->display->display_options['fields']['May_2016']['group_type'] = 'sum';
  $handler->display->display_options['fields']['May_2016']['label'] = 'May 2016';
  $handler->display->display_options['fields']['May_2016']['separator'] = '';
  /* Field: SUM(Fee Student Due: Jun_2016) */
  $handler->display->display_options['fields']['Jun_2016']['id'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jun_2016']['field'] = 'Jun_2016';
  $handler->display->display_options['fields']['Jun_2016']['group_type'] = 'sum';
  $handler->display->display_options['fields']['Jun_2016']['label'] = 'Jun 2016';
  $handler->display->display_options['fields']['Jun_2016']['separator'] = '';
  /* Field: SUM(Fee Student Due: Jul_2016) */
  $handler->display->display_options['fields']['Jul_2016']['id'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jul_2016']['field'] = 'Jul_2016';
  $handler->display->display_options['fields']['Jul_2016']['group_type'] = 'sum';
  $handler->display->display_options['fields']['Jul_2016']['label'] = 'Jul 2016';
  $handler->display->display_options['fields']['Jul_2016']['separator'] = '';
  /* Field: SUM(Fee Student Due: Aug_2016) */
  $handler->display->display_options['fields']['Aug_2016']['id'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Aug_2016']['field'] = 'Aug_2016';
  $handler->display->display_options['fields']['Aug_2016']['group_type'] = 'sum';
  $handler->display->display_options['fields']['Aug_2016']['label'] = 'Aug 2016';
  $handler->display->display_options['fields']['Aug_2016']['separator'] = '';
  /* Field: SUM(Fee Student Due: Sep_2016) */
  $handler->display->display_options['fields']['Sep_2016']['id'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Sep_2016']['field'] = 'Sep_2016';
  $handler->display->display_options['fields']['Sep_2016']['group_type'] = 'sum';
  $handler->display->display_options['fields']['Sep_2016']['label'] = 'Sep 2016';
  $handler->display->display_options['fields']['Sep_2016']['separator'] = '';
  /* Field: SUM(Fee Student Due: Oct_2016) */
  $handler->display->display_options['fields']['Oct_2016']['id'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Oct_2016']['field'] = 'Oct_2016';
  $handler->display->display_options['fields']['Oct_2016']['group_type'] = 'sum';
  $handler->display->display_options['fields']['Oct_2016']['label'] = 'Oct 2016';
  $handler->display->display_options['fields']['Oct_2016']['separator'] = '';
  /* Field: SUM(Fee Student Due: Nov_2016) */
  $handler->display->display_options['fields']['Nov_2016']['id'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Nov_2016']['field'] = 'Nov_2016';
  $handler->display->display_options['fields']['Nov_2016']['group_type'] = 'sum';
  $handler->display->display_options['fields']['Nov_2016']['label'] = 'Nov 2016';
  $handler->display->display_options['fields']['Nov_2016']['separator'] = '';
  /* Field: SUM(Fee Student Due: Dec_2016) */
  $handler->display->display_options['fields']['Dec_2016']['id'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Dec_2016']['field'] = 'Dec_2016';
  $handler->display->display_options['fields']['Dec_2016']['group_type'] = 'sum';
  $handler->display->display_options['fields']['Dec_2016']['label'] = 'Dec 2016';
  $handler->display->display_options['fields']['Dec_2016']['separator'] = '';
  /* Field: SUM(Fee Student Due: Jan_2017) */
  $handler->display->display_options['fields']['Jan_2017']['id'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Jan_2017']['field'] = 'Jan_2017';
  $handler->display->display_options['fields']['Jan_2017']['group_type'] = 'sum';
  $handler->display->display_options['fields']['Jan_2017']['label'] = 'Jan 2017';
  $handler->display->display_options['fields']['Jan_2017']['separator'] = '';
  /* Field: SUM(Fee Student Due: Feb_2017) */
  $handler->display->display_options['fields']['Feb_2017']['id'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Feb_2017']['field'] = 'Feb_2017';
  $handler->display->display_options['fields']['Feb_2017']['group_type'] = 'sum';
  $handler->display->display_options['fields']['Feb_2017']['label'] = 'Feb 2017';
  $handler->display->display_options['fields']['Feb_2017']['separator'] = '';
  /* Field: SUM(Fee Student Due: Mar_2017) */
  $handler->display->display_options['fields']['Mar_2017']['id'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['fields']['Mar_2017']['field'] = 'Mar_2017';
  $handler->display->display_options['fields']['Mar_2017']['group_type'] = 'sum';
  $handler->display->display_options['fields']['Mar_2017']['label'] = 'Mar 2017';
  $handler->display->display_options['fields']['Mar_2017']['separator'] = '';
  /* Field: SUM(Global: Math expression) */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['group_type'] = 'sum';
  $handler->display->display_options['fields']['expression']['label'] = 'Total';
  $handler->display->display_options['fields']['expression']['precision'] = '0';
  $handler->display->display_options['fields']['expression']['expression'] = '[Mar_2016]+[Apr_2016]+[May_2016]+[Jun_2016]+[Jul_2016]+[Aug_2016]+[Sep_2016]+[Oct_2016]+[Nov_2016]+[Dec_2016]+[Jan_2017]+[Feb_2017]+[Mar_2017]';
  /* Filter criterion: Fee Student Due: Admission No. */
  $handler->display->display_options['filters']['adm_no']['id'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['adm_no']['field'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['operator'] = 'contains';
  $handler->display->display_options['filters']['adm_no']['exposed'] = TRUE;
  $handler->display->display_options['filters']['adm_no']['expose']['operator_id'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['label'] = 'Admission No.';
  $handler->display->display_options['filters']['adm_no']['expose']['operator'] = 'adm_no_op';
  $handler->display->display_options['filters']['adm_no']['expose']['identifier'] = 'adm_no';
  $handler->display->display_options['filters']['adm_no']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Student Master Table: Class */
  $handler->display->display_options['filters']['class']['id'] = 'class';
  $handler->display->display_options['filters']['class']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['class']['field'] = 'class';
  $handler->display->display_options['filters']['class']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['class']['exposed'] = TRUE;
  $handler->display->display_options['filters']['class']['expose']['operator_id'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['expose']['operator'] = 'class_op';
  $handler->display->display_options['filters']['class']['expose']['identifier'] = 'class';
  $handler->display->display_options['filters']['class']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['class']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['class']['group_info']['label'] = 'Class';
  $handler->display->display_options['filters']['class']['group_info']['identifier'] = 'class';
  
  $session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$fees_table = 'essa_'.$session_id.'_fees_structure';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	$i = 1;
	foreach($classes as $cl){
		$cl_filter[$i] = array(
			  'title' => $cl->class_id,
			  'operator' => '=',
			  'value' => $cl->class_id,
		);
		$i++;
	}
  
  $handler->display->display_options['filters']['class']['group_info']['group_items'] = $cl_filter;
  /* Filter criterion: Student Master Table: Section */
  $handler->display->display_options['filters']['section']['id'] = 'section';
  $handler->display->display_options['filters']['section']['table'] = 'essa_2016_17_master_student_table';
  $handler->display->display_options['filters']['section']['field'] = 'section';
  $handler->display->display_options['filters']['section']['relationship'] = 'adm_no';
  $handler->display->display_options['filters']['section']['exposed'] = TRUE;
  $handler->display->display_options['filters']['section']['expose']['operator_id'] = 'section_op';
  $handler->display->display_options['filters']['section']['expose']['label'] = 'Section';
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
  /* Filter criterion: Fee Structure: Particulars */
  $handler->display->display_options['filters']['particulars']['id'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['table'] = 'essa_2016_17_fees_structure';
  $handler->display->display_options['filters']['particulars']['field'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['relationship'] = 'fee_id';
  $handler->display->display_options['filters']['particulars']['operator'] = 'contains';
  $handler->display->display_options['filters']['particulars']['exposed'] = TRUE;
  $handler->display->display_options['filters']['particulars']['expose']['operator_id'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['label'] = 'Particulars';
  $handler->display->display_options['filters']['particulars']['expose']['operator'] = 'particulars_op';
  $handler->display->display_options['filters']['particulars']['expose']['identifier'] = 'particulars';
  $handler->display->display_options['filters']['particulars']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Fee Student Due: Fee ID */
  $handler->display->display_options['filters']['fee_id']['id'] = 'fee_id';
  $handler->display->display_options['filters']['fee_id']['table'] = 'essa_2016_17_fees_student_due';
  $handler->display->display_options['filters']['fee_id']['field'] = 'fee_id';
  $handler->display->display_options['filters']['fee_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['fee_id']['expose']['operator_id'] = 'fee_id_op';
  $handler->display->display_options['filters']['fee_id']['expose']['label'] = 'Fee ID';
  $handler->display->display_options['filters']['fee_id']['expose']['operator'] = 'fee_id_op';
  $handler->display->display_options['filters']['fee_id']['expose']['identifier'] = 'fee_id';
  $handler->display->display_options['filters']['fee_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'student-wise-fee-detail';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'student-wise-fee-detail-csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['segment_size'] = '100';

  /* Display: Data export 2 */
  $handler = $view->new_display('views_data_export', 'Data export 2', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'student-wise-fee-detail-xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'chart';
  $handler->display->display_options['style_options']['type'] = 'column';
  $handler->display->display_options['style_options']['label_field'] = 'adm_no';
  $handler->display->display_options['style_options']['data_fields'] = array(
    'expression' => 'expression',
    'adm_no' => 0,
    'first_name' => 0,
    'last_name' => 0,
    'class' => 0,
    'section' => 0,
    'Mar_2016' => 0,
    'Apr_2016' => 0,
    'May_2016' => 0,
    'Jun_2016' => 0,
    'Jul_2016' => 0,
    'Aug_2016' => 0,
    'Sep_2016' => 0,
    'Oct_2016' => 0,
    'Nov_2016' => 0,
    'Dec_2016' => 0,
    'Jan_2017' => 0,
    'Feb_2017' => 0,
    'Mar_2017' => 0,
  );
  $handler->display->display_options['style_options']['field_colors'] = array(
    'adm_no' => '#2f7ed8',
    'first_name' => '#0d233a',
    'last_name' => '#8bbc21',
    'class' => '#910000',
    'section' => '#1aadce',
    'Mar_2016' => '#492970',
    'Apr_2016' => '#f28f43',
    'May_2016' => '#77a1e5',
    'Jun_2016' => '#c42525',
    'Jul_2016' => '#a6c96a',
    'Aug_2016' => '#000000',
    'Sep_2016' => '#000000',
    'Oct_2016' => '#000000',
    'Nov_2016' => '#000000',
    'Dec_2016' => '#000000',
    'Jan_2017' => '#000000',
    'Feb_2017' => '#000000',
    'Mar_2017' => '#000000',
    'expression' => '#861760',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $handler->display->display_options['inherit_pager'] = TRUE;
  $export['student_wise_fee_due'] = $view;

  return $export;
}
