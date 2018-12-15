<?php
/**
 * @file
 * menu_pages.features.inc
 */

/**
 * Implements hook_homebox().
 */
function menu_pages_homebox() {
  $homeboxes = array();

  $homeboxes['accounts'] = array(
    'regions' => 3,
    'cache' => 0,
    'color' => 0,
    'colors' => array(),
    'blocks' => array(),
    'widths' => array(),
    'title' => 'Accounts',
    'path' => 'admin/accounts',
    'menu' => 1,
    'enabled' => 1,
    'auto_save' => 1,
    'full' => 0,
    'roles' => array(),
  );

  $homeboxes['payroll_page'] = array(
    'regions' => 3,
    'cache' => 0,
    'color' => 0,
    'colors' => array(),
    'blocks' => array(),
    'widths' => array(),
    'title' => 'Payroll',
    'path' => 'admin/accounts/payroll',
    'menu' => 1,
    'enabled' => 1,
    'auto_save' => 1,
    'full' => 0,
    'roles' => array(
      0 => 'authenticated user',
    ),
  );

  $homeboxes['staff_page'] = array(
    'regions' => 3,
    'cache' => 0,
    'color' => 0,
    'colors' => array(),
    'blocks' => array(),
    'widths' => array(),
    'title' => 'Staff',
    'path' => 'admin/staff',
    'menu' => 1,
    'enabled' => 1,
    'auto_save' => 1,
    'full' => 0,
    'roles' => array(
      0 => 'Class Teacher',
      1 => 'Fee Manager',
      2 => 'Leave Moderator',
      3 => 'Payroll Manager',
      4 => 'Principal',
      5 => 'Staff',
      6 => 'Student Moderator',
      7 => 'Teacher',
      8 => 'Time Table Incharge',
      9 => 'Transport Head',
    ),
  );

  $homeboxes['student_page'] = array(
    'regions' => 3,
    'cache' => 0,
    'color' => 0,
    'colors' => array(),
    'blocks' => array(),
    'widths' => array(),
    'title' => 'Student',
    'path' => 'admin/students',
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
