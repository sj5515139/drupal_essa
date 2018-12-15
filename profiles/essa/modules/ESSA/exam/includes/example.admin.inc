<?php

/**
 * Callback function for menu item.
 */
function example_page() {
  $data = array(
    array('fruit' => 'apple', 'votes' => 16),
    array('fruit' => 'mango', 'votes' => 10),
    array('fruit' => 'banana', 'votes' => 34),
    array('fruit' => 'peach', 'votes' => 20),
    array('fruit' => 'orange', 'votes' => 15),
  );

  $options_pie = array(
    'title' => 'Favourite fruits',
    'fields' => array(
      'votes' => array(
        'label' => t('Votes'),
        'enabled' => TRUE,
      ),
    ),
    'xAxis' => array(
      'labelField' => 'fruit',
    ),
    'data' => $data,
    'type' => 'pie',
  );

  $options_column = array(
    'title' => 'Favourite fruits',
    'fields' => array(
      'votes' => array(
        'label' => t('Votes'),
        'enabled' => TRUE,
      ),
    ),
    'xAxis' => array(
      'labelField' => 'fruit',
    ),
    'data' => $data,
    'type' => 'column',
  );

  $build['pie'] =  array(
    '#theme' => 'visualization',
    '#options' => $options_pie,
  );

  $build['column'] =  array(
    '#theme' => 'visualization',
    '#options' => $options_column,
  );

  return $build;
}