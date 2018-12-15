<?php


/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function essa_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = 'ESSA-Efficient & Simplified School Administration';
}

/**
 * Implements hook_install_tasks()
 */
function essa_install_tasks(&$install_state) {
  // Add our custom CSS file for the installation process
  drupal_add_css(drupal_get_path('profile', 'essa') . '/css/essa.css');
  $tasks=array();
  
	$tasks['school_setup_form']=array(
    'display_name' => st('Session Setup'),
    'type' => 'form',
		'display' => TRUE,
  );
	
	$tasks['enable_essa_module']=array(
    'display_name' => st('Install ESSA'),
    'type' => 'batch',
		'display' => FALSE,
  );
	
	$tasks['basic_info_form']=array(
    'display_name' => st('Basic Info'),
    'type' => 'form',
		'display' => TRUE,
  );
  
  return $tasks;
}

function enable_essa_module(){
  $operations = array();
      
  $operations[] = array('_essa_install', array());
	
  $batch = array(
    'title' => st('Preparing site'),
    'operations' => $operations,
    'file' => drupal_get_path('profile', 'essa') . '/essa_install.inc',
  );
  return $batch;  
}


/**
 * Implements hook_install_tasks_alter()
 * Hides messages for non english installs
 */
function essa_install_tasks_alter(&$tasks, $install_state)
{
  if (isset($tasks['school_setup_form'])) {
    $pos = array_search('school_setup_form', array_keys($tasks));
    if ($pos == '10') {
      $save = $tasks['school_setup_form'];
      unset($tasks['school_setup_form']);
      $first_array = array_splice($tasks, 0, 6);
      $tasks = array_merge($first_array, array('school_setup_form' => $save), $tasks);
    }
  }
	
	if (isset($tasks['enable_essa_module'])) {
    $pos = array_search('enable_essa_module', array_keys($tasks));
    if ($pos == '10') {
      $save = $tasks['school_setup_form'];
      unset($tasks['school_setup_form']);
      $first_array = array_splice($tasks, 0, 7);
      $tasks = array_merge($first_array, array('school_setup_form' => $save), $tasks);
    }
  }
	
	if (isset($tasks['basic_info_form'])) {
    $pos = array_search('basic_info_form', array_keys($tasks));
    if ($pos == '10') {
      $save = $tasks['school_setup_form'];
      unset($tasks['school_setup_form']);
      $first_array = array_splice($tasks, 0, 8);
      $tasks = array_merge($first_array, array('school_setup_form' => $save), $tasks);
    }
  }
}


function school_setup_form($form, &$form_state, &$install_state){
  $form['new_session'] = array(
    '#title' => 'Session',
    '#description' => 'This will create the session ID.(FORMAT eg: "2015_16").',
    '#type' => 'textfield',
    '#required' => TRUE,
  );
  
	$form['save'] = array(
	 '#type' => 'submit',
	 '#value' => 'Continue',
	);
	
	$form_state['build_info']['args']['install_state']=&$install_state;
  return $form;
}

function school_setup_form_submit($form, &$form_state){
  $string = $form_state['values']['new_session'];
  $string = str_replace(' ', '_', $string); // Replaces all spaces with hyphens.
  $string = str_replace('-', '_', $string);
  $string = preg_replace('/[^A-Za-z0-9\-]/', '_', $string); // Removes special chars.
  variable_set('essa_sid', $string);
  $session_id = $string;
}


function basic_info_form($form, &$form_state, &$install_state){
  $form['nameofschool'] = array(
	  '#title' => t('Name of School'),
	  '#type' => 'textfield',
	  '#required' => TRUE,
		'#default_value' => isset($name_of_school)? $name_of_school: NULL,
	);
	
	$form['establishment_year'] = array(
		'#type' => 'textfield',
		'#title' => t('Year of Establishment'),
		'#required' => TRUE,
		'#default_value' => isset($establishment_year)? $establishment_year: NULL,
	);
	
	$form['hostel'] = array(
		'#type' => 'radios',
		'#title' => t('Hostel Facility'),
		'#options' => drupal_map_assoc(array('YES', 'NO')),
		'#default_value' => isset($hostel)? $hostel: NULL,
	);
	
	$form['transport'] = array(
		'#type' => 'radios',
		'#title' => t('Transport Facility'),
		'#options' => drupal_map_assoc(array('YES', 'NO')),
		'#default_value' => isset($transport)? $transport: NULL,
	);
	
	$form['fy'] = array(
	  '#title' => t('Financial Year'),
	  '#type' => 'fieldset',
	);  
	  
	$form['fy']['financialyearstart'] = array(
	  '#type' => 'date_popup',
		'#title' => t('Start Date'),
	  '#date_format' => 'd/m/Y',
	  '#required' => TRUE,
		'#attributes' => array('placeholder' => 'From'),
		'#default_value' => isset($financialyearstart)? $financialyearstart: NULL,
	  );
	  
	$form['fy']['financialyearend'] = array(
	  '#type' => 'date_popup',
		'#title' => t('End Date'),
	  '#date_format' => 'd/m/Y',
	  '#required' => TRUE,
		'#attributes' => array('placeholder' => 'To'),
		'#default_value' => isset($financialyearend)? $financialyearend: NULL,
	  );

	$form['ay'] = array(
	  '#title' => t('Academic Year'),
	  '#type' => 'fieldset',  
	);  
	
	$form['ay']['academicyearstart'] = array(
	  '#type' => 'date_popup',
		'#title' => t('Start Date'),
	  '#date_format' => 'd/m/Y',
	  '#required' => TRUE,
	  '#attributes' => array('placeholder' => 'From'),
		'#default_value' => isset($academicyearstart)? $academicyearstart: NULL,
	  );
	
  $form['ay']['academicyearend'] = array(
	  '#type' => 'date_popup',
		'#title' => t('End Date'),
	  '#date_format' => 'd/m/Y',
	  '#required' => TRUE,
		'#attributes' => array('placeholder' => 'To'),
		'#default_value' => isset($academicyearend)? $academicyearend: NULL,
  );
	
	$form['wp'] = array(
		'#type' => 'fieldset',
	);
	$form['wp']['classes']=array(
    '#title' => 'Create classes for your school - ',
    '#type' => 'checkboxes',
    '#options' => drupal_map_assoc(array(t('Nursery'), t('Prep'), t('KG'), t('LKG'),t('UKG'),t('I'), t('II'), t('III'), t('IV'), t('V'), t('VI'), t('VII'), t('VIII'), t('IX'), t('X'), t('XI'), t('XII'))),
  );
	
	$form['save'] = array(
	 '#type' => 'submit',
	 '#value' => 'Continue',
	);
	
	$form_state['build_info']['args']['install_state']=&$install_state;
  return $form;
}

function basic_info_form_submit($form, &$form_state){
 $session_id = (string)variable_get('essa_sid');
  $basicinfo = 'essa_'.$session_id.'_basicinfo';
  
  $fe_id = db_merge($basicinfo)
		->key(array('nameofschool' => $form_state['values']['nameofschool']))
    ->fields (array(
			'nameofschool' => $form_state['values']['nameofschool'],
			'establishment_year' => $form_state['values']['establishment_year'],
			'hostel_facility' => $form_state['values']['hostel'],
			'transport_facility' => $form_state['values']['transport'],
			'financialyearstart' => $form_state['values']['financialyearstart'],
			'financialyearend' => $form_state['values']['financialyearend'],
			'academicyearstart' => $form_state['values']['academicyearstart'],
			'academicyearend' => $form_state['values']['academicyearend'],
		)
	)
	->execute();
	
	$session_id = (string)variable_get('essa_sid');
  $class_list = 'essa_'.$session_id.'_class_list';
  
  foreach($form_state['values']['classes'] as $k => $input){
		
		$weight = find_weight();
      foreach($weight as $key => $value){
        if($input == $key){
          $w = $value;
        }
      }
    if($input != '0'){
			db_merge($class_list)
				->key(array('class_id' => $k))
        -> fields(array(
          'class_id' => $k,
          'weight' => $w,
          'class_set_id' => '',
      ))
      ->execute();
			
			$vid = taxonomy_vocabulary_machine_name_load('class_vocab');
			if(_get_taxonomy_term_id_by_name_install($input, $vid->vid) == false) {
        taxonomy_term_save(
            (object) array(
                'name' => $input,
                'vid' => $vid->vid,
								'weight' => $w,
            )
        );
			}
    }else{
			db_query("DELETE FROM {$class_list} WHERE class_id = :d", array(':d' => $k));
			db_query("DELETE FROM {taxonomy_term_data} WHERE name = :d", array(':d' => $k));
		}
  }
	
	$modules = array('leave', 'staff_attendance', 'student_attendance', 'fee', 'essa_fee_reports', 'fee_report_page', 'certificates', 'time_table','payroll'); //Array of module names
	$enable_dependencies = TRUE; // Whether or not to enable dependant modules
	module_enable($modules, $enable_dependencies);
	variable_set('site_frontpage', 'home');
	
	create_db_subject_tables();
}

/**
 * Get taxonomy term ID by term name.
 * 
 * @param string $termname
 * @param integer $vid
 */
function _get_taxonomy_term_id_by_name_install($termname, $vid) {
    return db_select('taxonomy_term_data', 't')
    ->fields('t', array('tid'))
    ->condition('t.name', $termname)
    ->condition('t.vid', $vid)
    ->execute()
    ->fetchField();
}

/**--------------------------------------------------------------------------------------------------------------------------------------------------------------
 *create tables for each class to store the list of subjects taught is the class. create_db_subject_tables()
 *--------------------------------------------------------------------------------------------------------------------------------------------------------------*/
function create_db_subject_tables(){
  $schema['subject'] = array(
	  'description' => 'TODO: please describe this table!',
	  'fields' => array(
	    'id' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'serial',
	      'unsigned' => TRUE,
	      'not null' => TRUE,
	    ),
			'sub_id' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'char',
	      'length' => '10',
	      'not null' => FALSE,
	    ),
	    'sub_name' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'char',
	      'length' => '150',
	      'not null' => FALSE,
	    ),
	    'type' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'varchar',
	      'length' => '20',
	      'not null' => FALSE,
	    ),
			'teacher1' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'varchar',
	      'length' => '50',
	      'not null' => FALSE,
	    ),
			'teacher1_emp_id' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'varchar',
	      'length' => '50',
	      'not null' => FALSE,
	    ),
			'teacher2' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'varchar',
	      'length' => '50',
	      'not null' => FALSE,
	    ),
			'teacher2_emp_id' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'varchar',
	      'length' => '50',
	      'not null' => FALSE,
	    ),
			'teacher3' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'varchar',
	      'length' => '50',
	      'not null' => FALSE,
	    ),
			'teacher3_emp_id' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'varchar',
	      'length' => '50',
	      'not null' => FALSE,
	    ),
			'teacher4' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'varchar',
	      'length' => '50',
	      'not null' => FALSE,
	    ),
			'teacher4_emp_id' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'varchar',
	      'length' => '50',
	      'not null' => FALSE,
	    ),
			'teacher5' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'varchar',
	      'length' => '50',
	      'not null' => FALSE,
	    ),
			'teacher5_emp_id' => array(
	      'description' => 'TODO: please describe this field!',
	      'type' => 'varchar',
	      'length' => '50',
	      'not null' => FALSE,
	    ),
	  ),
	  'primary key' => array('id', 'sub_id'),
	);
  
  $session_id = (string)variable_get('essa_sid');
  $class_list = 'essa_'.$session_id.'_class_list';
  
  $classes = db_query("
    SELECT class_id from {$class_list} order by weight;
  ");
  
  foreach($classes as $class){
    $name_of_table = 'essa_'.$session_id.'_subjects_'.clean_sub_string($class->class_id);
    if(!db_table_exists($name_of_table)){
			db_create_table($name_of_table, $schema['subject']);
		}
  }
  
}
/**--------------------------------------------------------------------------------------------------------------------------------------------------------------
 *find_weights - to attach a weight for all class, to maintain the order of classes
 *--------------------------------------------------------------------------------------------------------------------------------------------------------------*/
function find_weight(){
  return array(
    'Nursery' => 0,
    'Prep' => 1,
    'KG' => 2,
    'LKG' => 3,
    'UKG' => 4,
    'I' => 5,
    'II' => 6,
    'III' => 7,
    'IV' => 8,
    'V' => 9,
    'VI' => 10,
    'VII' => 11,
    'VIII' => 12,
    'IX' => 13,
    'X' => 14,
    'XI' => 15,
    'XII' => 16,
  );
}

/**
 *Supporting function to clean_string the array id.
 */
function clean_sub_string($string) {
   $string = str_replace('-', '', $string); // Replaces all spaces with hyphens.
	 $string = str_replace(' ', '', $string);
   return preg_replace('/[^A-Za-z0-9\-]/', '', $string); // Removes special chars.
}

function section_creation_form($form, &$form_state){

}