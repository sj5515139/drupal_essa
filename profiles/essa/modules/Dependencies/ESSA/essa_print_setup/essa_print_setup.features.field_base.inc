<?php
/**
 * @file
 * essa_print_setup.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function essa_print_setup_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_path'.
  $field_bases['field_path'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_path',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
