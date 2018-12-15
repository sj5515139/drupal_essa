<?php
/**
 * @file
 * essa_print_setup.features.inc
 */

/**
 * Implements hook_default_config_pages_type().
 */
function essa_print_setup_default_config_pages_type() {
  $items = array();
  $items['print_module_path'] = entity_import('config_pages_type', '{
    "type" : "print_module_path",
    "label" : "Print Module Path",
    "weight" : "0",
    "data" : {
      "menu" : { "path" : "admin\\/config\\/system\\/essa_print", "type" : "6" },
      "context" : { "group" : {
          "config_pages:language" : 0,
          "config_pages:host" : 0,
          "config_pages:domain" : 0
        }
      }
    },
    "rdf_mapping" : []
  }');
  return $items;
}
