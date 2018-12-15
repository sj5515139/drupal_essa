<?php
/**
 * @file
 * principal_s_message.features.inc
 */

/**
 * Implements hook_views_api().
 */
function principal_s_message_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function principal_s_message_node_info() {
  $items = array(
    'principal_s_message' => array(
      'name' => t('Principal\'s Message'),
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
