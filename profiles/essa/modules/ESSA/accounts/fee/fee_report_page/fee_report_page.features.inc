<?php
/**
 * @file
 * fee_report_page.features.inc
 */

/**
 * Implements hook_homebox().
 */
function fee_report_page_homebox() {
  $homeboxes = array();

  $homeboxes['fee_reports'] = array(
    'regions' => 1,
    'cache' => 1,
    'color' => 1,
    'colors' => array(
      0 => '#00CED1',
      1 => '#DC143C',
      2 => '#006400',
      3 => '#FFD700',
      4 => '#483D8B',
      5 => '#8A2BE2',
    ),
    'blocks' => array(
      'views_4c51c1fb3d1922c1b68a02ba7a8b376e' => array(
        'module' => 'views',
        'delta' => '4c51c1fb3d1922c1b68a02ba7a8b376e',
        'region' => 1,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -21,
      ),
      'views_fee_due_test-block_1' => array(
        'module' => 'views',
        'delta' => 'fee_due_test-block_1',
        'region' => 1,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -20,
      ),
      'views_ac4c3fda52b14cf627ffea05d734a2e5' => array(
        'module' => 'views',
        'delta' => 'ac4c3fda52b14cf627ffea05d734a2e5',
        'region' => 1,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -19,
      ),
    ),
    'widths' => array(),
    'title' => 'Reports',
    'path' => 'admin/fees/reports',
    'menu' => 1,
    'enabled' => 1,
    'auto_save' => 1,
    'full' => 0,
    'roles' => array(
      0 => 'authenticated user',
    ),
  );


  return $homeboxes;
}
