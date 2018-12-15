<?php

/**
 * @file
 * Builds placeholder replacement tokens for dnp terms and vocabularies.
 */

/**
 * Implements hook_token_info().
 */
function dnp_token_info() {
  $types['term'] = array(
    'name' => t("dnp terms"),
    'description' => t("Tokens related to dnp terms."),
    'needs-data' => 'term',
  );
  $types['vocabulary'] = array(
    'name' => t("Vocabularies"),
    'description' => t("Tokens related to dnp vocabularies."),
    'needs-data' => 'vocabulary',
  );

  // dnp term related variables.
  $term['tid'] = array(
    'name' => t("Term ID"),
    'description' => t("The unique ID of the dnp term."),
  );
  $term['name'] = array(
    'name' => t("Name"),
    'description' => t("The name of the dnp term."),
  );
  $term['description'] = array(
    'name' => t("Description"),
    'description' => t("The optional description of the dnp term."),
  );
  $term['node-count'] = array(
    'name' => t("Node count"),
    'description' => t("The number of nodes tagged with the dnp term."),
  );
  $term['url'] = array(
    'name' => t("URL"),
    'description' => t("The URL of the dnp term."),
  );

  // dnp vocabulary related variables.
  $vocabulary['vid'] = array(
    'name' => t("Vocabulary ID"),
    'description' => t("The unique ID of the dnp vocabulary."),
  );
  $vocabulary['name'] = array(
    'name' => t("Name"),
    'description' => t("The name of the dnp vocabulary."),
  );
  $vocabulary['description'] = array(
    'name' => t("Description"),
    'description' => t("The optional description of the dnp vocabulary."),
  );
  $vocabulary['node-count'] = array(
    'name' => t("Node count"),
    'description' => t("The number of nodes tagged with terms belonging to the dnp vocabulary."),
  );
  $vocabulary['term-count'] = array(
    'name' => t("Term count"),
    'description' => t("The number of terms belonging to the dnp vocabulary."),
  );

  // Chained tokens for taxonomies
  $term['vocabulary'] = array(
    'name' => t("Vocabulary"),
    'description' => t("The vocabulary the dnp term belongs to."),
    'type' => 'vocabulary',
  );
  $term['parent'] = array(
    'name' => t("Parent term"),
    'description' => t("The parent term of the dnp term, if one exists."),
    'type' => 'term',
  );

  return array(
    'types' => $types,
    'tokens' => array(
      'term' => $term,
      'vocabulary' => $vocabulary,
    ),
  );
}

/**
 * Implements hook_tokens().
 */
function dnp_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $sanitize = !empty($options['sanitize']);

  if ($type == 'term' && !empty($data['term'])) {
    $term = $data['term'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'tid':
          $replacements[$original] = $term->tid;
          break;

        case 'name':
          $replacements[$original] = $sanitize ? check_plain($term->name) : $term->name;
          break;

        case 'description':
          $replacements[$original] = $sanitize ? check_markup($term->description, $term->format, '', TRUE) : $term->description;
          break;

        case 'url':
          $uri = entity_uri('dnp_term', $term);
          $replacements[$original] = url($uri['path'], array_merge($uri['options'], array('absolute' => TRUE)));
          break;

        case 'node-count':
          $query = db_select('dnp_index');
          $query->condition('tid', $term->tid);
          $query->addTag('term_node_count');
          $count = $query->countQuery()->execute()->fetchField();
          $replacements[$original] = $count;
          break;

        case 'vocabulary':
          $vocabulary = dnp_vocabulary_load($term->vid);
          $replacements[$original] = check_plain($vocabulary->name);
          break;

        case 'parent':
          if ($parents = dnp_get_parents($term->tid)) {
            $parent = array_pop($parents);
            $replacements[$original] = check_plain($parent->name);
          }
          break;
      }
    }

    if ($vocabulary_tokens = token_find_with_prefix($tokens, 'vocabulary')) {
      $vocabulary = dnp_vocabulary_load($term->vid);
      $replacements += token_generate('vocabulary', $vocabulary_tokens, array('vocabulary' => $vocabulary), $options);
    }

    if (($vocabulary_tokens = token_find_with_prefix($tokens, 'parent')) && $parents = dnp_get_parents($term->tid)) {
      $parent = array_pop($parents);
      $replacements += token_generate('term', $vocabulary_tokens, array('term' => $parent), $options);
    }
  }

  elseif ($type == 'vocabulary' && !empty($data['vocabulary'])) {
    $vocabulary = $data['vocabulary'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'vid':
          $replacements[$original] = $vocabulary->vid;
          break;

        case 'name':
          $replacements[$original] = $sanitize ? check_plain($vocabulary->name) : $vocabulary->name;
          break;

        case 'description':
          $replacements[$original] = $sanitize ? filter_xss($vocabulary->description) : $vocabulary->description;
          break;

        case 'term-count':
          $query = db_select('dnp_term_data');
          $query->condition('vid', $vocabulary->vid);
          $query->addTag('vocabulary_term_count');
          $count = $query->countQuery()->execute()->fetchField();
          $replacements[$original] = $count;
          break;

        case 'node-count':
          $query = db_select('dnp_index', 'ti');
          $query->addExpression('COUNT(DISTINCT ti.nid)');
          $query->leftJoin('dnp_term_data', 'td', 'ti.tid = td.tid');
          $query->condition('td.vid', $vocabulary->vid);
          $query->addTag('vocabulary_node_count');
          $count = $query->execute()->fetchField();
          $replacements[$original] = $count;
          break;
      }
    }
  }

  return $replacements;
}
