<?php
/**
 *Implements page callback books_barcode.
 */
function books_barcode($form = array(), &$form_state){
	/*
	$file_name = md5('10600');
	//dsm(variable_get('file_public_path', conf_path() . '/files'));d1f491a404d6854880943e5c3cd9ca25EAN-13.png
	dsm(variable_get('file_public_path', conf_path() . '/files').'/barcodes/'.$file_name.'EAN-13.png');
	
	$image_options = array(
		'path' => variable_get('file_public_path', conf_path() . '/files').'/barcodes/'.$file_name.'EAN-13.png', 
		'alt' => 'Test alt',
		'title' => 'Test title',
		'attributes' => array('class' => 'some-img', 'id' => 'my-img'),
	);
	print theme_image($image_options);
	*/
	
	$path_print = db_query("
		SELECT * from field_data_field_path;"
	);
	foreach($path_print as $path){
		$path_to_print_module = $path->field_path_value;
	}
	if($path_to_print_module == NULL){
		dsm('sd');
	}
	$session_id = (string)variable_get('essa_sid');
	$books_table = 'essa_'.$session_id.'_lib_books';
	
	$options = array();
	$books =  db_query(
		"SELECT * from node where type = 'books';"
	);
	foreach($books as $book){
		$bk = node_load($book->nid);
		if(isset($bk->field_acc_no_['und'][0]['value'])){
			$options[] = $bk->field_acc_no_['und'][0]['value'];
		}
	}
	sort($options);
	$form['acc_no'] = array(
		'#type' => 'select',
		'#multiple' => TRUE,
		'#options' => drupal_map_assoc($options),
		'#size' => 30,
		'#title' => 'Select accession numbers to generate barcodes'
	);
	
	$form['ps'] = array(
		'#type' => 'fieldset',
	);
	
	$page_size_def = variable_get('barcode_page_size');
	$form['ps']['page_size'] = array(
		'#type' => 'select',
		'#title' => 'Page Size',
		'#options' => drupal_map_assoc(array('A4', 'Letter', 'Legal', 'Custom')),
		'#value' => isset($page_size_def)? $page_size_def: 'A4',
		'#ajax' => array(
		  'event' => 'change',
		  'callback' => 'get_custom_page_size',
			'wrapper' => 'page_size',
		  'method' => 'replace',
		  'effect' => 'fade',
		),
	);
	
	if($page_size_def == 'Custom'){
		$form['ps']['ct'] = array(
			'#type' => 'fieldset',
			'#prefix' => '<div id = "page_size">',
			'#suffix' => '</div>',
		);
			
		$width_def = variable_get('barcode_width');
		$form['ps']['ct']['cwidth'] = array(
			'#type' => 'textfield',
			'#title' => 'Width(in inches)',
			'#size' => 3,
			'#value' => isset($width_def)? $width_def: NULL,
		);
			
		$height_def = variable_get('barcode_height');
		$form['ps']['ct']['cheight'] = array(
			'#type' => 'textfield',
			'#title' => 'Height(in inches)',
			'#size' => 3,
			'#value' => isset($height_def)? $height_def: NULL,
		);
	}
	if(isset($form_state['input']['page_size']) && $form_state['input']['page_size'] == 'Custom'){
		dsm($form_state['values']['page_size']);
		$form['ps']['t'] = array(
			'#type' => 'fieldset',
			'#prefix' => '<div id = "page_size">',
			'#suffix' => '</div>',
		);
			
		$width_def = variable_get('barcode_width');
		$form['ps']['t']['width'] = array(
			'#type' => 'textfield',
			'#title' => 'Width(in inches)',
			'#size' => 3,
			'#value' => isset($width_def)? $width_def: NULL,
		);
			
		$height_def = variable_get('barcode_height');
		$form['ps']['t']['height'] = array(
			'#type' => 'textfield',
			'#title' => 'Height(in inches)',
			'#size' => 3,
			'#value' => isset($height_def)? $height_def: NULL,
		);
	}else{
		$form['ps']['t'] = array(
			'#type' => 'container',
			'#prefix' => '<div id = "page_size">',
			'#suffix' => '</div>',
		);
	}
		
	$page_orientation_def = variable_get('barcode_page_orientation');
	$form['ps']['page_orientation'] = array(
		'#type' => 'select',
		'#title' => 'Page Orientation',
		'#options' => drupal_map_assoc(array('Portrait', 'Landscape')),
		'#value' => !is_null($page_orientation_def)? $page_orientation_def: 'Portrait',
	);
		
	$form['ps']['note'] = array(
		'#type' => 'markup',
		'#markup' => '<h3>All margins are in inches</h3>',
	);
		
	for($i = 0; $i < 10; $i++){
		for($j = 0; $j < 10; $j++){
			$val[] = $i.'.'.$j;
		}	
	}
		
	$page_margin_top_def = variable_get('barcode_page_margin_top');
	$form['ps']['page_margin_top'] = array(
		'#type' => 'select',
		'#title' => 'Page Margin(Top)',
		'#options' => drupal_map_assoc($val),
		'#value' => !is_null($page_margin_top_def)? $page_margin_top_def: '0.1',
	);
		
	$page_margin_right_def = variable_get('barcode_page_margin_right');
	$form['ps']['page_margin_right'] = array(
		'#type' => 'select',
		'#title' => 'Page Margin(Right)',
		'#options' => drupal_map_assoc($val),
		'#value' => !is_null($page_margin_right_def)? $page_margin_right_def: '0.1',
	);
		
	$page_margin_bottom_def = variable_get('barcode_page_margin_bottom');
	$form['ps']['page_margin_bottom'] = array(
		'#type' => 'select',
		'#title' => 'Page Margin(Bottom)',
		'#options' => drupal_map_assoc($val),
		'#value' => !is_null($page_margin_bottom_def)? $page_margin_bottom_def: '0.1',
	);
		
	$page_margin_left_def = variable_get('barcode_page_margin_left');
	$form['ps']['page_margin_left'] = array(
		'#type' => 'select',
		'#title' => 'Page Margin(Left)',
		'#options' => drupal_map_assoc($val),
		'#value' => !is_null($page_margin_left_def)? $page_margin_left_def: '0.1',
	);
		
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Print',
	);
	return $form;
}

/**
 *Implements submit function
 */
function books_barcode_submit($form, &$form_state){
	variable_set('barcode_page_format', $form_state['input']['page_format']);
	variable_set('barcode_page_size', $form_state['input']['page_size']);
	if(isset($form_state['input']['cwidth'])){variable_set('barcode_width', $form_state['input']['cwidth']);}
	if(isset($form_state['input']['cheight'])){variable_set('barcode_height', $form_state['input']['cheight']);}
	if(isset($form_state['input']['width'])){variable_set('barcode_width', $form_state['input']['width']);}
	if(isset($form_state['input']['height'])){variable_set('barcode_height', $form_state['input']['height']);}
	variable_set('barcode_page_orientation', $form_state['input']['page_orientation']);
	variable_set('barcode_page_margin_top', $form_state['input']['page_margin_top']);
	variable_set('barcode_page_margin_right', $form_state['input']['page_margin_right']);
	variable_set('barcode_page_margin_bottom', $form_state['input']['page_margin_bottom']);
	variable_set('barcode_page_margin_left', $form_state['input']['page_margin_left']);
	variable_set('barcode_save_settings', $form_state['input']['save_settings']);
	
	
	if($form_state['input']['page_size'] == 'A4'){
		if($form_state['input']['page_orientation'] == 'Portrait'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 8.3 - ((float)$right + (float)$left);			
		}else{
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 11.7 - ((float)$top + (float)$bottom);
		}
	}elseif($form_state['input']['page_size'] == 'Letter' || $form_state['input']['page_size'] == 'Legal'){
		if($form_state['input']['page_orientation'] == 'Portrait' && $form_state['input']['page_size'] == 'Letter'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 8.5 - ((float)$right + (float)$left);
		}elseif($form_state['input']['page_orientation'] != 'Portrait' && $form_state['input']['page_size'] == 'Letter'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 11.0 - ((float)$top + (float)$bottom);
		}elseif($form_state['input']['page_orientation'] == 'Portrait' && $form_state['input']['page_size'] == 'Legal'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 8.5 - ((float)$top + (float)$bottom);
		}elseif($form_state['input']['page_orientation'] != 'Portrait' && $form_state['input']['page_size'] == 'Legal'){
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = 14.0 - ((float)$top + (float)$bottom);
		}
	}elseif($form_state['input']['page_size'] == 'Custom'){
		if($form_state['input']['page_orientation'] == 'Portrait'){
			if(isset($form_state['input']['cwidth'])){$cerw = $form_state['input']['cwidth'];}
			if(isset($form_state['input']['width'])){$cerw = $form_state['input']['width'];}
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = $cerw - ((float)$right + (float)$left);
		}else{
			if(isset($form_state['input']['cheight'])){$cerh = $form_state['input']['cheight'];}
			if(isset($form_state['input']['height'])){$cerh = $form_state['input']['height'];}
			$top = $form_state['input']['page_margin_top'];
			$right = $form_state['input']['page_margin_right'];
			$bottom = $form_state['input']['page_margin_bottom'];
			$left = $form_state['input']['page_margin_left'];
			$width = $cerh - ((float)$top + (float)$bottom);
		}
	}
	
	if($form_state['input']['page_size'] == 'Custom'){
		if(isset($form_state['input']['width']) && isset($form_state['input']['height'])){
			$w = $form_state['input']['width'] * 72;
			$h = $form_state['input']['height'] * 72;
			$page_size = array(0,0, $w, $h);	
		}else{
			$w = $form_state['input']['cwidth'] * 72;
			$h = $form_state['input']['cheight'] * 72;
			$page_size = array(0,0, $w, $h);	
		
		}
	}else{
		$page_size = $form_state['input']['page_size'];
	}
	
	if($form_state['input']['page_orientation'] == 'Portrait'){
		$po = 'portrait';
	}else{
		$po = 'landscape';
	}
	
	//$width = 8.3 - ((float)$right + (float)$left);
	
	$output = '<html>';
	$output .= '<head>';
	$output .= '<style>';
	$output .= '
		table{
			table-layout: fixed;
			width: '.$width.'in;
		}
		img{
			width: 80%;
			margin-left: 10%;
		}
		th{
			background: 	#708090;
			color: WHITE;
		}
		td{
			padding: 10px;
			height: 3.3cm;
		}
		#cer_footer{
			position: absolute;
			bottom:0.5cm;
			page-break-after: always;
		}
		@page { margin: '.$top.'in '.$right.'in '.$bottom.'in '.$left.'in; }
	</style></head>';
	
	$output .= '<body>';
	
	$count = 0;
	$barcode_count = 0;
	foreach($form_state['values']['acc_no'] as $acc_no){
		$file_name = md5($acc_no);
		$path = variable_get('file_public_path', conf_path() . '/files').'/barcodes/'.$file_name.'EAN-13.png';
		if($barcode_count == 0){
			$output .= '<table>';
			//dsm($acc_no);
		}
		if($count == 0){
			$output .= '<tr style = "page-break-before: always;">';
			$count = 0;
		}
		$output .= '<td>';
		$output .= '<img src='.$path.'>';
		$output .= '<p style = "margin-left: 25%;">'.'Acc No.'.$acc_no.'</p>';
		$output .= '</td>';
		
		$count++;
		$barcode_count++;
		if($count == 3){
			$output .= '</tr>';
			$count = 0;
		}
		if($barcode_count == 24){
			$output .= '</table>';
			$output .= '<div id = "cer_footer"></div>';
			$barcode_count = 0;
		}
	}
	
	$output .= '</body>';
	$output .= '</html>';
	
	
	
	$path_print = db_query("
		SELECT * from field_data_field_path;"
	);
	foreach($path_print as $path){
		$path_to_print_module = $path->field_path_value;
	}
	require_once($path_to_print_module);
	
	$content = $output;
	$dompdf = new DOMPDF;
	$dompdf->load_html($content);
	$dompdf->set_paper($page_size, $po);
	$dompdf->render();
	// This does not save the pdf field and instead it opens a dialog box asking whether you have to save the pdf or not
	$dompdf->stream("barcodes.pdf");
	
	global $base_url;
	$url = $base_url.'/admin/library/books/barcode';
	$custom_url =  (urldecode(url($_url)));
	$form_state['redirect'] = $custom_url;
	
}

/**
 *Implements ajax callback function - get_page_settings
 */
function get_custom_page_size(&$form, &$form_state){
	return $form['ps']['t'];
	dsm('yes');
}