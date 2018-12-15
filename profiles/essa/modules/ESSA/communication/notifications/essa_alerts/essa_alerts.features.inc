<?php
/**
 * @file
 * essa_alerts.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function essa_alerts_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "quicktabs" && $api == "quicktabs") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function essa_alerts_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_taskbar_default_items().
 */
function essa_alerts_taskbar_default_items() {
  $items = array();

  $items['alerts'] = array(
    'name' => 'alerts',
    'title' => 'Alerts',
    'provider' => 'block',
    'region' => 'right',
    'status' => 1,
    'weight' => -5,
    'settings' => array(
      'text' => 'Alerts',
      'description' => 'alerts',
      'roles' => array(),
      'refresh' => FALSE,
      'ajax' => FALSE,
      'update' => FALSE,
      'ajax refresh' => 0,
      'module' => 'quicktabs',
      'delta' => 'essa_alerts',
    ),
    'export_type' => 2,
  );

  return $items;
}
