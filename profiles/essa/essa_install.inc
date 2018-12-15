<?php

function _essa_install(&$context){
	$modules = array('school_master', 'payroll'); //Array of module names
  $enable_dependencies = TRUE; // Whether or not to enable dependant modules
  //module_enable($modules, $enable_dependencies);
	
	variable_set('file_private_path', 'sites/default/files');
	$context['message'] = st('Required modules installed.');
}