<?php
/**
 * @file
 * essa_print_setup.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function essa_print_setup_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'config_pages-print_module_path-field_path'.
  $field_instances['config_pages-print_module_path-field_path'] = array(
    'bundle' => 'print_module_path',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'config_pages',
    'field_name' => 'field_path',
    'label' => 'Path',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Path');

  return $field_instances;
}
