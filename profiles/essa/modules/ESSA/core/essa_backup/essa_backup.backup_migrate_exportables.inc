<?php
/**
 * @file
 * essa_backup.backup_migrate_exportables.inc
 */

/**
 * Implements hook_exportables_backup_migrate_schedules().
 */
function essa_backup_exportables_backup_migrate_schedules() {
  $export = array();

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'regular_backup';
  $item->name = 'Regular Backup';
  $item->source_id = 'db';
  $item->destination_id = 'untitled_destination';
  $item->copy_destination_id = '';
  $item->profile_id = 'default';
  $item->keep = 0;
  $item->period = 86400;
  $item->enabled = TRUE;
  $item->cron = 'builtin';
  $item->cron_schedule = '0 4 * * *';
  $export['regular_backup'] = $item;

  return $export;
}
