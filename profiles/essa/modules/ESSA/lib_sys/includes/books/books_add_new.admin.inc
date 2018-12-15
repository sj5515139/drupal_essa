<?php

function books_add_new($form, &$form_state){
	$form = array();
	
	$form['acc_no'] = array(
		'#type' => 'textfield',
		'#title' => 'Acc. no.',
		'#required' => TRUE,
		'#size' => 13,
		'#description' => '(Cannot be more than 13 characters)',
	);
	
	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => 'Title',
		'#required' => TRUE,
		'#attributes' => array('placeholder' => '(not more than 255 characters)'),
	);
	
	$form['desc'] = array(
		'#type' => 'textarea',
		'#title' => 'Description',
	);
	
	
	$form['date_of_purchase'] = array(
	  '#type' => 'date_popup',
		'#title' => t('Date of Purchase'),
	  '#date_format' => 'd/m/Y',
		'#required' => TRUE,
		//'#attributes' => array('placeholder' => 'From'),
	);
	
	$form['author'] = array(
		'#type' => 'textfield',
		'#title' => 'Author-1',
		'#required' => TRUE,
	);
	
	$form['fsa']['author1'] = array(
		'#type' => 'textfield',
		'#title' => 'Author-2',
	);
	
	$form['fsa']['author2'] = array(
		'#type' => 'textfield',
		'#title' => 'Author-3',
	);
	
	$form['publisher'] = array(
		'#type' => 'textfield',
		'#title' => 'Publisher',
	);
	
	$def_dt = date('d-m-Y');
	$form['pub_year'] = array(
		'#type' => 'date_select',
		'#title' => 'Year of Publication',
	  '#date_format' => 'Y',
		'#date_year_range' => '-50:+0',
		'#default_value' => date('d-m-Y'),
		//'#attributes' => array('placeholder' => 'From'),
	);
	
	$form['edition'] = array(
		'#type' => 'textfield',
		'#title' => 'Edition',
		'#size' => 25,
	);
	
	$form['reprint'] = array(
		'#type' => 'textfield',
		'#title' => 'Reprint',
	);
	
	$subj_options = array('--SELECT--');
	$vid = taxonomy_vocabulary_machine_name_load('book_subject');
	$subject_terms = taxonomy_get_tree($vid->vid, $parent = 0, $max_depth = NULL, $load_entities = FALSE);
	foreach($subject_terms as $terms){
		$subj_options[] = $terms->name;
	}
	//dsm($subject_terms);
	$form['subject'] = array(
		'#type' => 'select',
		'#title' => 'Subject',
		'#options' => drupal_map_assoc($subj_options),
	);
	
	$form['new_subject'] = array(
		'#type' => 'textfield',
		'#size' => 20,
		'#attributes' => array('placeholder' => 'Add New'),
	);
	
	$options = array('--SELECT--');
	$vid = taxonomy_vocabulary_machine_name_load('book_category');
	$category_terms = taxonomy_get_tree($vid->vid, $parent = 0, $max_depth = NULL, $load_entities = FALSE);
	foreach($category_terms as $terms){
		$options[] = $terms->name;
	}
	$form['category'] = array(
		'#type' => 'select',
		'#title' => 'Category',
		'#options' => drupal_map_assoc($options),
	);
	
	$form['new_category'] = array(
		'#type' => 'textfield',
		'#size' => 20,
		'#attributes' => array('placeholder' => 'Add New'),
	);
	
	$lang_options = array('--SELECT--');
	$vid = taxonomy_vocabulary_machine_name_load('book_lang');
	$lang_terms = taxonomy_get_tree($vid->vid, $parent = 0, $max_depth = NULL, $load_entities = FALSE);
	foreach($lang_terms as $terms){
		$lang_options[] = $terms->name;
	}
	$form['lang'] = array(
		'#type' => 'select',
		'#title' => 'Language',
		'#options' => drupal_map_assoc($lang_options),
	);
	
	$form['new_lang'] = array(
		'#type' => 'textfield',
		'#size' => 20,
		'#attributes' => array('placeholder' => 'Add New'),
	);
	
	$source_options = array('--SELECT--');
	$vid = taxonomy_vocabulary_machine_name_load('book_source');
	$source_terms = taxonomy_get_tree($vid->vid, $parent = 0, $max_depth = NULL, $load_entities = FALSE);
	foreach($source_terms as $terms){
		$source_options[] = $terms->name;
	}
	$form['source'] = array(
		'#type' => 'select',
		'#title' => 'Source',
		'#options' => drupal_map_assoc($source_options),
	);
	
	$form['new_source'] = array(
		'#type' => 'textfield',
		'#size' => 20,
		'#attributes' => array('placeholder' => 'Add New'),
	);
	
	$form['page_no'] = array(
		'#type' => 'textfield',
		'#title' => 'Page. no.',
	);
	
	$form['price'] = array(
		'#type' => 'textfield',
		'#title' => 'Price',
		'#required' => TRUE,
	);
	
	$cup_options = array('--SELECT--');
	$vid = taxonomy_vocabulary_machine_name_load('book_cupboard');
	$cup_terms = taxonomy_get_tree($vid->vid, $parent = 0, $max_depth = NULL, $load_entities = TRUE);
	foreach($cup_terms as $terms){
		$cupboards = db_query("
		  SELECT * from taxonomy_term_hierarchy where tid = :tid;", array(':tid' => $terms->tid)
		);
		foreach($cupboards as $cb){
			if($cb->parent == 0){
				$cup_options[] = $terms->name;
			}
		}
	}
	
	$form['cupboard'] = array(
		'#type' => 'select',
		'#title' => 'Cupboard',
		'#options' => drupal_map_assoc($cup_options),
		'#ajax' => array(
      'event' => 'change',
      'callback' => 'get_shelf_ajax',
      'wrapper' => 'shelf_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
	);
	
	$form['new_cupboard'] = array(
		'#type' => 'textfield',
		'#size' => 20,
		'#attributes' => array('placeholder' => 'Add New'),
	);
	
	$form['shelf_container'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "shelf_wrapper">',
		'#suffix' => '</div>',
	);
	
	if(!empty($form_state['values']['cupboard']) && !empty($form_state['values']['cupboard'])){
		$shelf_options = array('--SELECT--');
		$vid = taxonomy_vocabulary_machine_name_load('book_cupboard');
		$shelf_terms = taxonomy_get_tree($vid->vid, $parent = 0, $max_depth = NULL, $load_entities = TRUE);
		$get_cupboards_terms = db_query("
		  SELECT * from taxonomy_term_data where name = :name and vid = :vid;", array(':name' => $form_state['values']['cupboard'], ':vid' => $vid->vid)
		);
		foreach($get_cupboards_terms as $gct){
			$cupboard_tid = $gct->tid;
		}
		foreach($cup_terms as $terms){
			$shelves = db_query("
			  SELECT * from taxonomy_term_hierarchy where tid = :tid;", array(':tid' => $terms->tid)
			);
			foreach($shelves as $sh){
				if($sh->parent == $cupboard_tid){
					$shelf_options[] = $terms->name;
				}
			}
		}
		
		$form['shelf_container']['shelf'] = array(
			'#type' => 'select',
			'#title' => 'Shelf',
			'#options' => drupal_map_assoc($shelf_options),
		);
		
		$form['shelf_container']['new_shelf'] = array(
			'#type' => 'textfield',
			'#size' => 20,
			'#attributes' => array('placeholder' => 'Add New'),
		);
	}else{
		$shelf_options = array('--SELECT--');
		$form['shelf_container']['new_shelf'] = array(
			'#title' => 'Shelf',
			'#type' => 'textfield',
			'#size' => 20,
		);
	}
	
	
	
	$form['isbn'] = array(
		'#type' => 'textfield',
		'#title' => 'ISBN',
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	
	return $form;
}

/**
 *Implements ajax callback
 */
function get_shelf_ajax($form, &$form_state){
	return $form['shelf_container'];
}

/**
 *Implements submit function
 */
function books_add_new_submit($form, &$form_state){
	//dsm($form_state);
	
	//---------------------------------------Saving term to taxonomy for subjects--------------------------------
	if(!empty($form_state['values']['new_subject'])){
		$subject = ucwords($form_state['values']['new_subject']);
		$tid = taxonomy_get_term_by_name($subject);
		$vid = taxonomy_vocabulary_machine_name_load('book_subject');
		if(_get_taxonomy_term_id_by_name($subject, $vid->vid) == false) {
      taxonomy_term_save(
        (object) array(
          'name' => $subject,
          'vid' => $vid->vid,
				)
			);
		}
	}else{
		$subject = ucwords($form_state['values']['subject']);
	}
	
	if(isset($subject)){
		$tid = taxonomy_get_term_by_name($subject);
		foreach($tid as $id){
			$subj_tid = $id->tid;
		}
	}
	
	//---------------------------------------Saving term to taxonomy for category--------------------------------
	if(!empty($form_state['values']['new_category'])){
		$category = ucwords($form_state['values']['new_category']);
		$tid = taxonomy_get_term_by_name($category);
		$vid = taxonomy_vocabulary_machine_name_load('book_category');
		if(_get_taxonomy_term_id_by_name($category, $vid->vid) == false) {
      taxonomy_term_save(
        (object) array(
          'name' => $category,
          'vid' => $vid->vid,
				)
			);
		}
	}else{
		$category = ucwords($form_state['values']['category']);
	}
	
	if(isset($category)){
		$tid = taxonomy_get_term_by_name($category);
		foreach($tid as $id){
			$category_tid = $id->tid;
		}
	}
	
	//---------------------------------------Saving term to taxonomy for language--------------------------------
	if(!empty($form_state['values']['new_lang'])){
		$lang = ucwords($form_state['values']['new_lang']);
		$tid = taxonomy_get_term_by_name($category);
		$vid = taxonomy_vocabulary_machine_name_load('book_lang');
		if(_get_taxonomy_term_id_by_name($lang, $vid->vid) == false) {
      taxonomy_term_save(
        (object) array(
          'name' => $lang,
          'vid' => $vid->vid,
				)
			);
		}
	}else{
		$lang = ucwords($form_state['values']['lang']);
	}
	
	if(isset($lang)){
		$tid = taxonomy_get_term_by_name($lang);
		foreach($tid as $id){
			$lang_tid = $id->tid;
		}
	}
	
	//---------------------------------------Saving term to taxonomy for source--------------------------------
	if(!empty($form_state['values']['new_source'])){
		$source = ucwords($form_state['values']['new_source']);
		$tid = taxonomy_get_term_by_name($source);
		$vid = taxonomy_vocabulary_machine_name_load('book_source');
		if(_get_taxonomy_term_id_by_name($source, $vid->vid) == false) {
      taxonomy_term_save(
        (object) array(
          'name' => $source,
          'vid' => $vid->vid,
				)
			);
		}
	}else{
		$source = ucwords($form_state['values']['source']);
	}
	
	if(isset($source)){
		$tid = taxonomy_get_term_by_name($source);
		foreach($tid as $id){
			$source_tid = $id->tid;
		}
	}
	
	//---------------------------------------Saving term to taxonomy for cupboard--------------------------------
	if(!empty($form_state['values']['new_cupboard'])){
		$cupboard = $form_state['values']['new_cupboard'];
		$tid = taxonomy_get_term_by_name($cupboard);
		$vid = taxonomy_vocabulary_machine_name_load('book_cupboard');
		if(_get_taxonomy_term_id_by_name($cupboard, $vid->vid) == false) {
      taxonomy_term_save(
        (object) array(
          'name' => $cupboard,
          'vid' => $vid->vid,
				)
			);
		}
	}else{
		$cupboard = $form_state['values']['cupboard'];
	}
	
	if(isset($cupboard)){
		$tid = taxonomy_get_term_by_name($cupboard);
		foreach($tid as $id){
			$cupboard_tid = $id->tid;
		}
	}
	
	
	//---------------------------------------Saving term to taxonomy for cupboard--------------------------------
	if(!empty($form_state['values']['new_shelf'])){
		$shelf = $form_state['values']['new_shelf'];
		$tid = taxonomy_get_term_by_name($shelf);
		$vid = taxonomy_vocabulary_machine_name_load('book_cupboard');
		if(_get_taxonomy_term_id_by_name_parent($shelf, $cupboard_tid, $vid->vid) == false) {
      taxonomy_term_save(
        (object) array(
          'name' => $shelf,
					'parent' => $cupboard_tid,
          'vid' => $vid->vid,
				)
			);
		}
	}else{
		if(isset($form_state['values']['shelf'])){
			$shelf = $form_state['values']['shelf'];
		}else{
			$shelf = NULL;
		}
	}
	
	if(isset($shelf)){
		$tid = taxonomy_get_term_by_name($shelf, 'book_cupboard');
		foreach($tid as $id){
			$shelf_tid = $id->tid;
		}
	}
	
	$vocabulary = taxonomy_vocabulary_machine_name_load('book_availability');
	$terms = entity_load('taxonomy_term', FALSE, array('vid' => $vocabulary->vid));
	foreach($terms as $term){
		if($term->name == 'Available'){
			$available_tid = $term->tid;
		}
		if($term->name == 'Issued'){
			$issued_tid = $term->tid;
		}
	}
	
	$barnumber = $form_state['values']['acc_no'];
	// If the source message string is less than 12 characters long, we make 
  // it 12 characters
  if (strlen($barnumber) <= 12) {
    $barnumber = str_pad($barnumber, 12, "0", STR_PAD_LEFT);
  }

  // Calculate the checksum value for the message
  for ($i = 0; $i < strlen($barnumber); $i++) {
    if ($i % 2 == 0 ) {
      $csum_total = $csum_total + intval($barnumber{$i});
    }
    else {
      $csum_total = $csum_total + (3 * intval($barnumber{$i}));
    }
  }

  // Calculate the checksum digit
  if ($csum_total % 10 == 0) {
    $checksum_digit = '';
  }
  else {
    $checksum_digit = 10 - ($csum_total % 10);
  }

	$node = new stdClass();
	$node->type = 'books';
	node_object_prepare($node);
	$node->language = LANGUAGE_NONE;
	$node->uid = 1;
	$node->field_acc_no_['und'][0]['value'] = $form_state['values']['acc_no'];
	$node->title = $form_state['values']['title'];
	$node->field_body['und'][0]['value'] = $form_state['values']['desc'];
	$node->field_body['und'][0]['format'] = 'filtered_html';
	$node->field_date_of_purchase['und'][0]['value'] = $form_state['values']['date_of_purchase'];
	$node->field_author1['und'][0]['value'] = $form_state['values']['author'];
	$node->field_author2['und'][0]['value'] = $form_state['values']['author1'];
	$node->field_author3['und'][0]['value'] = $form_state['values']['author2'];
	$node->field_publisher['und'][0]['value'] = $form_state['values']['publisher'];
	$node->field_year['und'][0]['value'] = $form_state['values']['pub_year'];
	$node->field_edition['und'][0]['value'] = $form_state['values']['edition'];
	$node->field_reprint['und'][0]['value'] = $form_state['values']['reprint'];
	isset($subj_tid) ? $node->field_subject['und'][0]['tid'] = $subj_tid : NULL;
	isset($category_tid) ? $node->field_category['und'][0]['tid'] = $category_tid : NULL;
	isset($lang_tid) ? $node->field_language['und'][0]['tid'] = $lang_tid : NULL;
	isset($source_tid) ? $node->field_source['und'][0]['tid'] = $source_tid : NULL;
	$node->field_page_no_['und'][0]['value'] = $form_state['values']['page_no'];
	$node->field_price['und'][0]['value'] = $form_state['values']['price'];
	isset($cupboard_tid) ? $node->field_cupboard['und'][0]['tid'] = $cupboard_tid : NULL;
	isset($shelf_tid) ? $node->field_shelf['und'][0]['tid'] = $shelf_tid : NULL;
	$node->field_isbn['und'][0]['value'] = $form_state['values']['isbn'];
	$node->field_bc['und'][0]['value'] = $form_state['values']['acc_no'];
	$node->field_barcode_value['und']['0']['value'] = $barnumber . $checksum_digit;
	$node->field_availability['und'][0]['tid'] = $available_tid;
	$node = node_submit($node);
	
	node_save($node);
	dsm($node);
	dsm($form_state);
}

/*
 $barnumber = $form_state['values']['field_bc']['und'][0]['value'];
	// If the source message string is less than 12 characters long, we make 
  // it 12 characters
  if (strlen($barnumber) <= 12) {
    $barnumber = str_pad($barnumber, 12, "0", STR_PAD_LEFT);
  }

  // Calculate the checksum value for the message
  for ($i = 0; $i < strlen($barnumber); $i++) {
    if ($i % 2 == 0 ) {
      $csum_total = $csum_total + intval($barnumber{$i});
    }
    else {
      $csum_total = $csum_total + (3 * intval($barnumber{$i}));
    }
  }

  // Calculate the checksum digit
  if ($csum_total % 10 == 0) {
    $checksum_digit = '';
  }
  else {
    $checksum_digit = 10 - ($csum_total % 10);
  }
	
	
  variable_set('bc_no_ean', $barnumber . $checksum_digit);
 */
//get_shelf_ajax

/**
 * Get taxonomy term ID by term name.
 * 
 * @param string $termname
 * @param integer $vid
 */
function _get_taxonomy_term_id_by_name($termname, $vid) {
    return db_select('taxonomy_term_data', 't')
    ->fields('t', array('tid'))
    ->condition('t.name', $termname)
    ->condition('t.vid', $vid)
    ->execute()
    ->fetchField();
}

/**
 * Get taxonomy term ID by term name.
 * 
 * @param string $termname
 * @param integer $vid
 */
function _get_taxonomy_term_id_by_name_parent($termname, $tid, $vid) {
	$term_data = taxonomy_get_children($tid);
	$ch = array();
	if(empty($term_data)){
		return FALSE;
	}else{
		foreach($term_data as $data){
			$ch[] = $data->name;
		}
	}
	if(!in_array($termname, $ch)){
		return FALSE;
	}else{
		return TRUE;	
	}
}

/**
 
	$file_name = md5('take8');
	//dsm(variable_get('file_public_path', conf_path() . '/files'));d1f491a404d6854880943e5c3cd9ca25EAN-13.png
	dsm('19241140589c29eedbc218b7b4cd179fEAN-13.png');
	dsm(variable_get('file_public_path', conf_path() . '/files').'/barcodes/'.$file_name.'EAN-13.png');
	$form['file'] = array(
		'#type' => 'markup',
		'#markup' => '<img src="'.variable_get('file_public_path', conf_path() . '/files').'/barcodes/'.$file_name.'EAN-13.png'.'">'
	);
	
	$file_name = md5('take8');
	$form['file1'] = array(
		'#type' => 'markup',
		'#markup' => '<img src = "'.variable_get('file_public_path', conf_path() . '/files').'/barcodes/19241140589c29eedbc218b7b4cd179fEAN-13.png'.'">',
	);
	
	dsm('sites/default/files/barcodes/19241140589c29eedbc218b7b4cd179fEAN-13.png');
	///Applications/MAMP/htdocs/dps-ims/sites/default/files/barcodes
	$file_name = md5('take8');
	$form['file2'] = array(
		'#type' => 'markup',
		'#markup' => '<img src = "sites/default/files/boy.png">',
	);
	
	
	$image_options = array(
		'path' => variable_get('file_public_path', conf_path() . '/files').'/barcodes/'.$file_name.'EAN-13.png', 
		'alt' => 'Test alt',
		'title' => 'Test title',
		'attributes' => array('class' => 'some-img', 'id' => 'my-img'),
	);


 /*$image = theme('image', $image_options);
  $form['start']['image'] = array(
    '#markup' => $image,
  );
    print theme_image($image_options);
	*/
	