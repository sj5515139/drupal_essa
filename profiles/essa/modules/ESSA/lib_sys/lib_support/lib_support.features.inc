<?php
/**
 * @file
 * lib_support.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function lib_support_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function lib_support_node_info() {
  $items = array(
    'books' => array(
      'name' => t('Books'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
