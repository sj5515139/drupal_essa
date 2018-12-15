<?php
/**
 * @file
 * essa_alerts.quicktabs.inc
 */

/**
 * Implements hook_quicktabs_default_quicktabs().
 */
function essa_alerts_quicktabs_default_quicktabs() {
  $export = array();

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'essa_alerts';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 0;
  $quicktabs->title = 'ESSA Alerts';
  $quicktabs->tabs = array(
    0 => array(
      'bid' => 'views_delta_essa_alerts-block',
      'hide_title' => 1,
      'title' => 'High',
      'weight' => '-100',
      'type' => 'block',
    ),
    1 => array(
      'bid' => 'views_delta_essa_alerts-block_1',
      'hide_title' => 1,
      'title' => 'Medium',
      'weight' => '-99',
      'type' => 'block',
    ),
    2 => array(
      'bid' => 'views_delta_essa_alerts-block_2',
      'hide_title' => 1,
      'title' => 'Low',
      'weight' => '-98',
      'type' => 'block',
    ),
  );
  $quicktabs->renderer = 'quicktabs';
  $quicktabs->style = 'Zen';
  $quicktabs->options = array();

  // Translatables
  // Included for use with string extractors like potx.
  t('ESSA Alerts');
  t('High');
  t('Low');
  t('Medium');

  $export['essa_alerts'] = $quicktabs;

  return $export;
}
