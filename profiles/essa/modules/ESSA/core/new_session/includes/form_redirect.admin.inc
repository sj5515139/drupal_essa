<?php

function form_redirect_page($form, &$form_state){
	// drupal_goto('admin/settings/classes');
	$options = variable_get('essa_session_setup_unmark');
	//dsm($options);
	if(in_array('Class List', $options)){
		if($options['Class List'] == '0'){
			dsm('yes');
			// variable_set('essa_sid', '2017_18');
			// drupal_goto('admin/settings/classes/class-setup');
		}else{
			dsm('no');
			//variable_set('essa_sid', '2016_17');

			// module_load_include('inc', 'school_master', 'includes/class/class_setup.admin');
			// create_db_subject_tables_cl();
			// drupal_goto('new');
		}
	}
	// if(in_array('Class Teacher', $options)){
		// drupal_goto('admin/settings/classes');
	// }
	if($options == NULL){
		drupal_set_message('All settings are updated successfully.');		
	}
	
	return $form;
}