<?php
/**
 * @file
 * notice_board.features.inc
 */

/**
 * Implements hook_views_api().
 */
function notice_board_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function notice_board_node_info() {
  $items = array(
    'notices' => array(
      'name' => t('Notices'),
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
