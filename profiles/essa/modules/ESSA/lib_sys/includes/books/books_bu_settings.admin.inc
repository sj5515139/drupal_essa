<?php
/**
 *Implements page call back suntion - books_bu_settings
 */
function books_bu_settings($form, &$form_state){
	$form = array();
	
	$options['NULL'] = 'None';
	for($i=0;$i<20;$i++){
		$options[$i] = $i;
	}
	
	$def = variable_get('essa_lib_default');
	if($def == 1){
		$form['acc_no'] = array(
			'#type' => 'select',
			'#title' => 'Acc. No.',
			'#options' => $options,
			'#default_value' => 0,
		);
	
		$form['title'] = array(
			'#type' => 'select',
			'#title' => 'Title',
			'#options' => $options,
			'#default_value' => 1,
		);
	
		$form['desc'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Description',
			'#default_value' => 2,
		);
	
		$form['dop'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Date of Purchase',
			'#default_value' => 3,
		);
		
		$form['author1'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Author1',
			'#default_value' => 4,
		);
	
		$form['author2'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Author2',
			'#default_value' => 5,
		);
		
		$form['author3'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Author3',
			'#default_value' => 6,
		);
	
		$form['publisher'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Publisher',
			'#default_value' => 7,
		);
	
		$form['yop'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Year of Publication',
			'#default_value' => 8,
		);
	
		$form['edition'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Edition',
			'#default_value' => 9,
		);
	
		$form['reprint'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Reprint',
			'#default_value' => 10,
		);
	
		$form['subject'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Subject',
			'#default_value' => 11,
		);
	
		$form['category'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Category',
			'#default_value' => 12,
		);
	
		$form['lang'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Language',
			'#default_value' => 13,
		);
	
		$form['source'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Source',
			'#default_value' => 14,
		);
	
		$form['page_no'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Page No',
			'#default_value' => 15,
		);
	
		$form['price'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'price',
			'#default_value' => 16,
		);
	
		$form['cupboard'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Cupboard',
			'#default_value' => 17,
		);
	
		$form['shelf'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Shelf',
			'#default_value' => 18,
		);
		
		$form['isbn'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'ISBN',
			'#default_value' => 19,
		);
	}else{
		$acc_no = variable_get('essa_lib_acc_no');
		$form['acc_no'] = array(
			'#type' => 'select',
			'#title' => 'Acc. No.',
			'#options' => $options,
			'#default_value' => isset($acc_no)?$acc_no:NULL,
		);
	
		$title = variable_get('essa_lib_title');
		$form['title'] = array(
			'#type' => 'select',
			'#title' => 'Title',
			'#options' => $options,
			'#default_value' => isset($title)?$title:NULL,
		);
		
		$desc = variable_get('essa_lib_desc');
		$form['desc'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Description',
			'#default_value' => isset($desc)?$desc:NULL,
		);
		
		$dop = variable_get('essa_lib_date_of_purchase');
		$form['dop'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Date of Purchase',
			'#default_value' => isset($dop)?$dop:NULL,
		);
		
		$author1 = variable_get('essa_lib_author1');
		$form['author1'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Author1',
			'#default_value' => isset($author1)?$author1:NULL,
		);
		
		$author2 = variable_get('essa_lib_author2');
		$form['author2'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Author2',
			'#default_value' => isset($author2)?$author2:NULL,
		);
		
		$author3 = variable_get('essa_lib_author3');
		$form['author3'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Author3',
			'#default_value' => isset($author3)?$author3:NULL,
		);
		
		$pub = variable_get('essa_lib_publisher');
		$form['publisher'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Publisher',
			'#default_value' => isset($pub)?$pub:NULL,
		);
		
		$year_of_publication = variable_get('essa_lib_year_of_publication');
		$form['yop'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Year of Publication',
			'#default_value' => isset($year_of_publication)?$year_of_publication:NULL,
		);
		
		$ed = variable_get('essa_lib_edition');
		$form['edition'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Edition',
			'#default_value' => isset($ed)?$ed:NULL,
		);
		
		$reprint = variable_get('essa_lib_reprint');
		$form['reprint'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Reprint',
			'#default_value' => isset($reprint)?$reprint:NULL,
		);
		
		$sub = variable_get('essa_lib_subject');
		$form['subject'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Subject',
			'#default_value' => isset($sub)?$sub:NULL,
		);
		
		$cat = variable_get('essa_lib_category');
		$form['category'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Category',
			'#default_value' => isset($cat)?$cat:NULL,
		);
		
		$lang = variable_get('essa_lib_lang');
		$form['lang'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Language',
			'#default_value' => isset($lang)?$lang:NULL,
		);
		
		$source = variable_get('essa_lib_source');
		$form['source'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Source',
			'#default_value' => isset($source)?$source:NULL,
		);
		
		$pn = variable_get('essa_lib_page_no');
		$form['page_no'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Page No',
			'#default_value' => isset($pn)?$pn:NULL,
		);
		
		$pr = variable_get('essa_lib_price');
		$form['price'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Price',
			'#default_value' => isset($pr)?$pr:NULL,
		);
		
		$cb = variable_get('essa_lib_cupboard');
		$form['cupboard'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Cupboard',
			'#default_value' => isset($cb)?$cb:NULL,
		);
		
		$sh = variable_get('essa_lib_shelf');
		$form['shelf'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'Shelf',
			'#default_value' => isset($sh)?$sh:NULL,
		);
		
		$isbn = variable_get('essa_lib_isbn');
		$form['isbn'] = array(
			'#type' => 'select',
			'#options' => $options,
			'#title' => 'ISBN',
			'#default_value' => isset($isbn)?$isbn:NULL,
		);
	}
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
	);
	
	$form['set_none'] = array(
		'#type' => 'submit',
		'#value' => 'Flush Defaults',
		'#submit' => array('set_none'),
	);
	
	$form['set_default'] = array(
		'#type' => 'submit',
		'#value' => 'Set Defaults',
		'#submit' => array('set_default'),
	);
	return $form;
}

function set_default(){
	variable_set('essa_lib_default', 1);
}

function set_none(){
	variable_set('essa_lib_default', 0);
	variable_set('essa_lib_acc_no', NULL);
	variable_set('essa_lib_title', NULL);
	variable_set('essa_lib_desc', NULL);
	variable_set('essa_lib_date_of_purchase', NULL);
	variable_set('essa_lib_author1', NULL);
	variable_set('essa_lib_author2', NULL);
	variable_set('essa_lib_author3', NULL);
	variable_set('essa_lib_publisher', NULL);
	variable_set('essa_lib_year_of_publication', NULL);
	variable_set('essa_lib_edition', NULL);
	variable_set('essa_lib_reprint', NULL);
	variable_set('essa_lib_subject', NULL);
	variable_set('essa_lib_category', NULL);
	variable_set('essa_lib_lang', NULL);
	variable_set('essa_lib_source', NULL);
	variable_set('essa_lib_page_no', NULL);
	variable_set('essa_lib_price', NULL);
	variable_set('essa_lib_cupboard', NULL);
	variable_set('essa_lib_shelf', NULL);
	variable_set('essa_lib_isbn', NULL);
		
}

/**
 *Implements validate suntion - books_bu_settings
 */
function books_bu_settings_validate($form, &$form_state){
	if($form_state['values']['acc_no'] == 'NULL' && $form_state['triggering_element']['#value'] == 'Save'){
		form_set_error('acc_no', 'Accession no. can\'t be "None".');
	}
	
	if($form_state['values']['title'] == 'NULL'  && $form_state['triggering_element']['#value'] == 'Save'){
		form_set_error('title', 'Title can\'t be "None".');
	}
	
	$arr = array();
	foreach($form_state['input'] as $k => $val){
		$arr[$k] = $val;
	}
	$count = array_count_values($arr);
	variable_set('essa_lib_error', 0);
	foreach($count as $v => $c){
		if($v != 'NULL'){
			if($c > 1){
				dsm($v);
				variable_set('essa_lib_error', 1);
			}
		}
	}
	
	
}

/**
 *Implements submit suntion - books_bu_settings
 */
function books_bu_settings_submit($form, &$form_state){
	if(variable_get('essa_lib_error') == 0){
		variable_set('essa_lib_acc_no', $form_state['values']['acc_no']);
		variable_set('essa_lib_title', $form_state['values']['title']);
		variable_set('essa_lib_desc', $form_state['values']['desc']);
		variable_set('essa_lib_date_of_purchase', $form_state['values']['dop']);
		variable_set('essa_lib_author1', $form_state['values']['author1']);
		variable_set('essa_lib_author2', $form_state['values']['author2']);
		variable_set('essa_lib_author3', $form_state['values']['author3']);
		variable_set('essa_lib_publisher', $form_state['values']['publisher']);
		variable_set('essa_lib_year_of_publication', $form_state['values']['yop']);
		variable_set('essa_lib_edition', $form_state['values']['edition']);
		variable_set('essa_lib_reprint', $form_state['values']['reprint']);
		variable_set('essa_lib_subject', $form_state['values']['subject']);
		variable_set('essa_lib_category', $form_state['values']['category']);
		variable_set('essa_lib_lang', $form_state['values']['lang']);
		variable_set('essa_lib_source', $form_state['values']['source']);
		variable_set('essa_lib_page_no', $form_state['values']['page_no']);
		variable_set('essa_lib_price', $form_state['values']['price']);
		variable_set('essa_lib_cupboard', $form_state['values']['cupboard']);
		variable_set('essa_lib_shelf', $form_state['values']['shelf']);
		variable_set('essa_lib_isbn', $form_state['values']['isbn']);
		variable_set('essa_lib_default', 0);
		drupal_set_message('Settings for bulk upload was saved successfullly.','status');
	}else{
		drupal_set_message('You cannot match two fields to same column.', 'error');
	}
}