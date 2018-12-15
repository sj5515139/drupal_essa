<?php
/**
 * @file
 * essa_homepage_taskbar.features.inc
 */

/**
 * Implements hook_homebox().
 */
function essa_homepage_taskbar_homebox() {
  $homeboxes = array();
  $title = htmlspecialchars_decode('ESSA-Efficient and Simplified School Administration');;
  $homeboxes['home'] = array(
    'regions' => 5,
    'cache' => 0,
    'color' => 1,
    'colors' => array(
      0 => '#E4F0F8',
      1 => '#DC143C',
      2 => '#006400',
      3 => '#FFD700',
      4 => '#483D8B',
      5 => '#8A2BE2',
    ),
    'blocks' => array(
      'views_notice_board-block' => array(
        'module' => 'views',
        'delta' => 'notice_board-block',
        'region' => 3,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -25,
      ),
      'views_bulletin_board-block' => array(
        'module' => 'views',
        'delta' => 'bulletin_board-block',
        'region' => 2,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -25,
      ),
      'views_principal_s_message-block' => array(
        'module' => 'views',
        'delta' => 'principal_s_message-block',
        'region' => 1,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -25,
      ),
      'privatemsg_block_privatemsg_block_list' => array(
        'module' => 'privatemsg_block',
        'delta' => 'privatemsg_block_list',
        'region' => 5,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -24,
      ),
      'privatemsg_block_privatemsg_block_sent' => array(
        'module' => 'privatemsg_block',
        'delta' => 'privatemsg_block_sent',
        'region' => 4,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -24,
      ),
      'user_new' => array(
        'module' => 'user',
        'delta' => 'new',
        'region' => 1,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -24,
      ),
    ),
    'widths' => array(
      1 => 33,
      2 => 33,
      3 => 33,
      4 => 50,
      5 => 50,
    ),
    'title' => $title,
    'path' => 'home',
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

/**
 * Implements hook_taskbar_default_items().
 */
function essa_homepage_taskbar_taskbar_default_items() {
  $items = array();

  $items['Calendar'] = array(
    'name' => 'Calendar',
    'title' => 'Calendar',
    'provider' => 'block',
    'region' => 'center',
    'status' => 1,
    'weight' => -4,
    'settings' => array(
      'text' => 'Calendar',
      'description' => 'Calendar',
      'roles' => array(),
      'refresh' => FALSE,
      'ajax' => FALSE,
      'update' => FALSE,
      'ajax refresh' => 0,
      'module' => 'views',
      'delta' => 'calendar-block_1',
    ),
    'export_type' => 1,
  );

  $items['ESSA'] = array(
    'name' => 'ESSA',
    'title' => 'ESSA Notifications',
    'provider' => 'activity',
    'region' => 'right',
    'status' => 1,
    'weight' => -3,
    'settings' => array(
      'text' => 'Notifications',
      'source' => 'ESSA',
      'max items' => 5,
      'description' => 'ESSA Notifications',
      'roles' => array(),
      'refresh' => TRUE,
      'ajax' => FALSE,
      'update' => TRUE,
      'ajax refresh' => 100,
    ),
    'export_type' => 1,
  );

  $items['ESSA_message'] = array(
    'name' => 'ESSA_message',
    'title' => 'Messages',
    'provider' => 'activity',
    'region' => 'right',
    'status' => 1,
    'weight' => -4,
    'settings' => array(
      'text' => 'Messages',
      'source' => 'ESSA_message',
      'max items' => 15,
      'description' => 'Messages',
      'roles' => array(),
      'refresh' => FALSE,
      'ajax' => FALSE,
      'update' => FALSE,
      'ajax refresh' => 0,
    ),
    'export_type' => 1,
  );

  $items['Message'] = array(
    'name' => 'Message',
    'title' => 'Message',
    'provider' => 'block',
    'region' => '',
    'status' => 0,
    'weight' => -2,
    'settings' => array(
      'text' => 'Message',
      'description' => 'Message',
      'roles' => array(),
      'refresh' => FALSE,
      'ajax' => FALSE,
      'update' => FALSE,
      'ajax refresh' => 0,
      'module' => 'privatemsg',
      'delta' => 'privatemsg-menu',
    ),
    'export_type' => 1,
  );

  $items['Messages'] = array(
    'name' => 'Messages',
    'title' => 'Messages',
    'provider' => 'block',
    'region' => '',
    'status' => 0,
    'weight' => -1,
    'settings' => array(
      'text' => 'Messages',
      'description' => 'Messages',
      'roles' => array(),
      'refresh' => FALSE,
      'ajax' => FALSE,
      'update' => FALSE,
      'ajax refresh' => 0,
      'module' => 'privatemsg',
      'delta' => 'privatemsg-new',
    ),
    'export_type' => 1,
  );

  $items['Navigation'] = array(
    'name' => 'Navigation',
    'title' => 'Navigation',
    'provider' => 'block',
    'region' => 'left',
    'status' => 1,
    'weight' => -3,
    'settings' => array(
      'text' => 'Navigation',
      'description' => 'Navigation',
      'roles' => array(),
      'refresh' => FALSE,
      'ajax' => FALSE,
      'update' => FALSE,
      'ajax refresh' => 0,
      'module' => 'system',
      'delta' => 'navigation',
    ),
    'export_type' => 1,
  );

  $items['message_block'] = array(
    'name' => 'message_block',
    'title' => 'New Message',
    'provider' => 'block',
    'region' => 'center',
    'status' => 1,
    'weight' => -5,
    'settings' => array(
      'text' => 'New Message',
      'description' => 'New Message',
      'roles' => array(),
      'refresh' => FALSE,
      'ajax' => TRUE,
      'update' => FALSE,
      'ajax refresh' => 0,
      'module' => 'privatemsg_block',
      'delta' => 'privatemsg_block_new',
    ),
    'export_type' => 1,
  );

  return $items;
}
