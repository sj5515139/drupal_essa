<?php

/**
 *Implements page call back function - books_bu
 */
function books_bu($form = array(), &$form_state){
	$form['browser'] = array(
    '#type' => 'fieldset',
    '#title' => t('Browser Upload'),
    '#description' => t("Upload a CSV file. Please follow the upload configuration."),
  );

  $file_size = t('Maximum file size: !size MB.', array('!size' => file_upload_max_size()));

  $form['browser']['file_upload'] = array(
    '#type' => 'file',
    '#title' => t('CSV File'),
    '#size' => 40,
    '#description' => t('Select the CSV file to be imported. ') . $file_size,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
	
	return $form;
}

function books_bu_validate($form, &$form_state) {
  // attempt to save the uploaded file
  $validators = array('file_validate_extensions' => array('csv'));
  $file = file_save_upload('file_upload', $validators);

  // check file uploaded OK
  if (!$file) {
    form_set_error('file_upload', t('A file must be uploaded or selected from FTP updates.'));
  }
  else if($file->filemime != 'text/csv') {
    form_set_error('file_upload', t('The file must be of CSV type only.'));
  }
  else {
    // set files to form_state, to process when form is submitted
    $form_state['values']['file_upload'] = $file;
  }
}

function books_bu_submit($form, &$form_state){
	$session = variable_get('essa_sid');
  $books_table = 'essa_'.$session.'_lib_books';
  $line_max = variable_get('user_import_line_max', 1000);
	ini_set('auto_detect_line_endings', true);
	$filepath = $form_state['values']['file_upload']->destination;
	$handle = @fopen($filepath, "r");
	$flag = true;
	$num = 0;
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
	
	while(! feof($handle)){
		if($flag) {
		  $csv = fgetcsv($handle);
		  $flag = false; continue;
		}
		$csv = fgetcsv($handle);
    
		$acc_no = variable_get('essa_lib_acc_no');
		$title = variable_get('essa_lib_title');
		$desc = variable_get('essa_lib_desc');
		$dop = variable_get('essa_lib_date_of_purchase');
		$author1 = variable_get('essa_lib_author1');
		$author2 = variable_get('essa_lib_author2');
		$author3 = variable_get('essa_lib_author3');
		$publisher = variable_get('essa_lib_publisher');
		$yop = variable_get('essa_lib_year_of_publication');
		$edition = variable_get('essa_lib_edition');
		$reprint = variable_get('essa_lib_reprint');
		$subj = variable_get('essa_lib_subject');
		$categ = variable_get('essa_lib_category');
		$language = variable_get('essa_lib_lang');
		$source_no = variable_get('essa_lib_source');
		$page_no = variable_get('essa_lib_page_no');
		$price = variable_get('essa_lib_price');
		$cup = variable_get('essa_lib_cupboard');
		$shelf_no = variable_get('essa_lib_shelf');
		$isbn = variable_get('essa_lib_isbn');
		
		$barnumber = $csv[$acc_no];
		// If the source message string is less than 12 characters long, we make 
		// it 12 characters
		if (strlen($barnumber) <= 12) {
		  $barnumber = str_pad($barnumber, 12, "0", STR_PAD_LEFT);
		}
		$csum_total = 0;
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
		  $checksum_digit = 0;
		}
		else {
		  $checksum_digit = 10 - ($csum_total % 10);
		}
		$bar_val = $barnumber . $checksum_digit;
		
		$in_acc_no = isset($csv[$acc_no]) ? $csv[$acc_no] : NULL;
		$in_title = isset($csv[$title]) ? $csv[$title] : NULL;
		$in_desc = isset($csv[$acc_no]) ? $csv[$desc] : NULL;
		$in_dop = isset($csv[$dop]) ? $csv[$dop] : NULL;
		$in_author1 = isset($csv[$author1]) ? $csv[$author1] : NULL;
		$in_author2 = isset($csv[$author2]) ? $csv[$author3] : NULL;
		$in_author3 = isset($csv[$author3]) ? $csv[$author3] : NULL;
		$in_publisher = isset($csv[$publisher]) ? $csv[$publisher] : NULL;
		$in_yop = isset($csv[$yop]) ? $csv[$yop] : NULL;
		$in_edition = isset($csv[$edition]) ? $csv[$edition] : NULL;
		$in_reprint = isset($csv[$reprint]) ? $csv[$reprint] : NULL;
		$in_subj = isset($csv[$subj]) ? $csv[$subj] : NULL;
		$in_categ = isset($csv[$categ]) ? $csv[$categ] : NULL;
		$in_lang = isset($csv[$language]) ? $csv[$language] : NULL;
		$in_source = isset($csv[$source_no]) ? $csv[$source_no] : NULL;
		$in_page_no = isset($csv[$page_no]) ? $csv[$page_no] : NULL;
		$in_price = isset($csv[$price]) ? $csv[$price] : NULL;
		$in_cup = isset($csv[$cup]) ? $csv[$cup] : NULL;
		$in_shelf = isset($csv[$shelf_no]) ? $csv[$shelf_no] : NULL;
		$in_isbn = isset($csv[$isbn]) ? $csv[$isbn] : NULL;
			//---------------------------------------Saving term to taxonomy for subjects--------------------------------
		if(isset($csv[$subj])){
			$subject = ucwords($csv[$subj]);
			$tid = taxonomy_get_term_by_name($subject);
			$vid = taxonomy_vocabulary_machine_name_load('book_subject');
			if($csv[$subj] != ''){
				if(_get_taxonomy_term_id_by_name($subject, $vid->vid) == false) {
				  taxonomy_term_save(
				    (object) array(
				      'name' => $subject,
				      'vid' => $vid->vid,
						)
					);
				}
				$tid = taxonomy_get_term_by_name($subject);
				foreach($tid as $id){
					$subj_tid = $id->tid;
				}
			}
		}
		
		//---------------------------------------Saving term to taxonomy for category--------------------------------
		if(isset($csv[$categ])){
			$category = ucwords($csv[$categ]);
			$tid = taxonomy_get_term_by_name($category);
			$vid = taxonomy_vocabulary_machine_name_load('book_category');
			if($csv[$categ] != ''){
				if(_get_taxonomy_term_id_by_name($category, $vid->vid) == false) {
				  taxonomy_term_save(
				    (object) array(
				      'name' => $category,
				      'vid' => $vid->vid,
						)
					);
				}
				$tid = taxonomy_get_term_by_name($category);
				foreach($tid as $id){
					$category_tid = $id->tid;
				}
			}
		}
		
		//---------------------------------------Saving term to taxonomy for language--------------------------------
		if(isset($csv[$language])){
			$lang = ucwords($csv[$language]);
			$tid = taxonomy_get_term_by_name($category);
			$vid = taxonomy_vocabulary_machine_name_load('book_lang');
			if($csv[$language] != ''){
				if(_get_taxonomy_term_id_by_name($lang, $vid->vid) == false) {
				  taxonomy_term_save(
				    (object) array(
				      'name' => $lang,
				      'vid' => $vid->vid,
						)
					);
				}
				$tid = taxonomy_get_term_by_name($lang);
				foreach($tid as $id){
					$lang_tid = $id->tid;
				}
			}
		}
		
		//---------------------------------------Saving term to taxonomy for source--------------------------------
		if(isset($csv[$source_no])){
			$source = ucwords($csv[$source_no]);
			$tid = taxonomy_get_term_by_name($source);
			$vid = taxonomy_vocabulary_machine_name_load('book_source');
			if($csv[$source_no] != ''){
				if(_get_taxonomy_term_id_by_name($source, $vid->vid) == false) {
				  taxonomy_term_save(
				    (object) array(
				      'name' => $source,
				      'vid' => $vid->vid,
						)
					);
				}
				$tid = taxonomy_get_term_by_name($source);
				foreach($tid as $id){
					$source_tid = $id->tid;
				}
			}
		}
		
		//---------------------------------------Saving term to taxonomy for cupboard--------------------------------
		if(isset($csv[$cup])){
			$cupboard = $csv[$cup];
			$tid = taxonomy_get_term_by_name($cupboard);
			$vid = taxonomy_vocabulary_machine_name_load('book_cupboard');
			if($csv[$cup] != ''){
				if(_get_taxonomy_term_id_by_name($cupboard, $vid->vid) == false) {
					taxonomy_term_save(
					  (object) array(
					    'name' => $cupboard,
					    'vid' => $vid->vid,
						)
					);
				}
				$tid = taxonomy_get_term_by_name($cupboard);
				foreach($tid as $id){
					$cupboard_tid = $id->tid;
				}
			}
		}
		
		
		//---------------------------------------Saving term to taxonomy for cupboard--------------------------------
		if(isset($csv[$shelf_no])){
			$shelf = $csv[$shelf_no];
			$tid = taxonomy_get_term_by_name($shelf);
			$vid = taxonomy_vocabulary_machine_name_load('book_cupboard');
			if($csv[$shelf_no] != ''){
				if(_get_taxonomy_term_id_by_name_parent($shelf, $cupboard_tid, $vid->vid) == false) {
				  taxonomy_term_save(
				    (object) array(
				      'name' => $shelf,
							'parent' => $cupboard_tid,
				      'vid' => $vid->vid,
						)
					);
				}
				$tid = taxonomy_get_term_by_name($shelf, 'book_cupboard');
				foreach($tid as $id){
					$shelf_tid = $id->tid;
				}
			}
		}
		
		$nid = db_select('field_data_field_acc_no_', 't')
		  ->fields('t', array('entity_id'))
		  ->condition('t.field_acc_no__value', $in_acc_no)
		  ->execute()
		  ->fetchField();
		if($nid != NULL){
			$node = node_load($nid);
			$node->type = 'books';
			node_object_prepare($node);
			$node->language = LANGUAGE_NONE;
			$node->uid = 1;
			$node->field_acc_no_['und'][0]['value'] = $in_acc_no;
			$node->title = $in_title;
			$node->field_body['und'][0]['value'] = $in_desc;
			$node->field_body['und'][0]['format'] = 'filtered_html';
			$dop_in = date('Y-m-d', strtotime($in_dop));
			$node->field_date_of_purchase['und'][0]['value'] = $dop_in;
			$node->field_author1['und'][0]['value'] = $in_author1;
			$node->field_author2['und'][0]['value'] = $in_author2;
			$node->field_author3['und'][0]['value'] = $in_author3;
			$node->field_publisher['und'][0]['value'] = $in_publisher;
			$node->field_year['und'][0]['value'] = $in_yop;
			$node->field_edition['und'][0]['value'] = $in_edition;
			$node->field_reprint['und'][0]['value'] = $in_reprint;
			isset($subj_tid) ? $node->field_subject['und'][0]['tid'] = $subj_tid : NULL;
			isset($category_tid) ? $node->field_category['und'][0]['tid'] = $category_tid : NULL;
			isset($lang_tid) ? $node->field_language['und'][0]['tid'] = $lang_tid : NULL;
			isset($source_tid) ? $node->field_source['und'][0]['tid'] = $source_tid : NULL;
			$node->field_page_no_['und'][0]['value'] = $in_page_no;
			$node->field_price['und'][0]['value'] = $in_price;
			isset($cupboard_tid) ? $node->field_cupboard['und'][0]['tid'] = $cupboard_tid : NULL;
			isset($shelf_tid) ? $node->field_shelf['und'][0]['tid'] = $shelf_tid : NULL;
			$node->field_isbn['und'][0]['value'] = $in_isbn;
			$node->field_bc['und'][0]['value'] = $in_acc_no;
			$node->field_barcode_value['und'][0]['value'] = $bar_val;
			$node->field_availability['und'][0]['tid'] = $available_tid;
			$node = node_submit($node);
			
			node_save($node);
		}else{
			$node = new stdClass();
			$node->type = 'books';
			node_object_prepare($node);
			$node->language = LANGUAGE_NONE;
			$node->uid = 1;
			$node->field_acc_no_['und'][0]['value'] = $in_acc_no;
			$node->title = $in_title;
			$node->field_body['und'][0]['value'] = $in_desc;
			$node->field_body['und'][0]['format'] = 'filtered_html';
			$dop_in = date('Y-m-d', strtotime($in_dop));
			$node->field_date_of_purchase['und'][0]['value'] = $dop_in;
			$node->field_author1['und'][0]['value'] = $in_author1;
			$node->field_author2['und'][0]['value'] = $in_author2;
			$node->field_author3['und'][0]['value'] = $in_author3;
			$node->field_publisher['und'][0]['value'] = $in_publisher;
			$node->field_year['und'][0]['value'] = $in_yop;
			$node->field_edition['und'][0]['value'] = $in_edition;
			$node->field_reprint['und'][0]['value'] = $in_reprint;
			isset($subj_tid) ? $node->field_subject['und'][0]['tid'] = $subj_tid : NULL;
			isset($category_tid) ? $node->field_category['und'][0]['tid'] = $category_tid : NULL;
			isset($lang_tid) ? $node->field_language['und'][0]['tid'] = $lang_tid : NULL;
			isset($source_tid) ? $node->field_source['und'][0]['tid'] = $source_tid : NULL;
			$node->field_page_no_['und'][0]['value'] = $in_page_no;
			$node->field_price['und'][0]['value'] = $in_price;
			isset($cupboard_tid) ? $node->field_cupboard['und'][0]['tid'] = $cupboard_tid : NULL;
			isset($shelf_tid) ? $node->field_shelf['und'][0]['tid'] = $shelf_tid : NULL;
			$node->field_isbn['und'][0]['value'] = $in_isbn;
			$node->field_bc['und'][0]['value'] = $in_acc_no;
			$node->field_barcode_value['und'][0]['value'] = $bar_val;
			$node->field_availability['und'][0]['tid'] = $available_tid;
			$node = node_submit($node);
			
			node_save($node);
			
		}
		$num++;
	}
	drupal_cron_run();
	dsm('No. of rows processed = '. $num);
}

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