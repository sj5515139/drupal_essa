<?php
/**
 *Page Callback / Creates list of classes in the school.
 */
function class_setup($form = array(), &$form_state){
	/*$form['help'] = array(
    '#type' => 'markup',
    '#markup' => '<h1> Create classes. </h1>',
  );*/
	$form['wp'] = array(
		'#type' => 'fieldset',
	);
	
	$default = array();
	
	$session_id = (string)variable_get('essa_sid');
	$class_list = 'essa_'.$session_id.'_class_list';
	$classes = db_query("
    SELECT * from {$class_list} order by weight;
  ");
	foreach($classes as $class){
		$default[] = $class->class_id;
	}
  
  $form['wp']['classes']=array(
    '#title' => 'Create classes for your school - ',
    '#type' => 'checkboxes',
    '#options' => drupal_map_assoc(array(t('Nursery'), t('Prep'), t('KG'), t('LKG'),t('UKG'),t('I'), t('II'), t('III'), t('IV'), t('V'), t('VI'), t('VII'), t('VIII'), t('IX'), t('X'), t('XI'), t('XII'))),
		'#default_value' => $default,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 *SUBMIT FUNCTION - sends data to DB and redirects to next step
 */
function class_setup_submit($form , &$form_state){
  
  // $session_id = (string)variable_get('essa_sid');
  // $class_list = 'essa_'.$session_id.'_class_list';
	// $sys_alert_table = 'essa_'.$session_id.'_system_alert';
	// global $user;
  
  // foreach($form_state['values']['classes'] as $k => $input){
		
		// $weight = find_weight_cl();
      // foreach($weight as $key => $value){
        // if($input == $key){
          // $w = $value;
        // }
      // }
    // if($input != '0'){
			// db_merge($class_list)
				// ->key(array('class_id' => $k))
        // -> fields(array(
          // 'class_id' => $k,
          // 'weight' => $w,
          // 'class_set_id' => '',
      // ))
      // ->execute();
			
			// $vid = taxonomy_vocabulary_machine_name_load('class_vocab');
			// if(_get_taxonomy_term_id_by_name_cl($input, $vid->vid) == false) {
        // taxonomy_term_save(
            // (object) array(
                // 'name' => $input,
                // 'vid' => $vid->vid,
								// 'weight' => $w,
            // )
        // );
			// }
    // }else{
			// db_query("DELETE FROM {$class_list} WHERE class_id = :d", array(':d' => $k));
			// db_query("DELETE FROM {taxonomy_term_data} WHERE name = :d", array(':d' => $k));
		// }
  // }
	
  // create_db_subject_tables_cl();
	// //*******Suraj********//
	// global $base_url;
	// $url = $base_url.'#overlay=admin/settings/classes/class-section';
	// drupal_set_message('Class list was updated successfully!!! Please <a href = "'.$url.'">manage section.</a>','status');
	// $created_date = date("Y-m-d H:i:s");
	// $strtodate = strtotime($created_date);
	// db_insert($sys_alert_table)
	// ->fields(array(
		// 'message' => 'Class List was updated.',
		// 'priority' => 'H',
		// 'module' => 'school_master',
		// 'source_url' => 'admin/settings/classes/class-setup',
		// 'timestamp' => $strtodate,
		// 'source_uid' => $user->uid,
	// ))
	// ->execute();
	// //*******Suraj********//
	
	// for new_session
	$options = variable_get('essa_session_setup_unmark');
	if(isset($options)){
		if(in_array('Class List', $options)){
			unset($options['Class List']);
			variable_set('essa_session_setup_unmark', $options);
			drupal_goto('form_redirect');
		}
	}
	
}

/**
 * Get taxonomy term ID by term name.
 * 
 * @param string $termname
 * @param integer $vid
 */
function _get_taxonomy_term_id_by_name_cl($termname, $vid) {
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
function create_db_subject_tables_cl(){
	
  // $schema['subject'] = array(
	  // 'description' => 'TODO: please describe this table!',
	  // 'fields' => array(
	    // 'id' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'serial',
	      // 'unsigned' => TRUE,
	      // 'not null' => TRUE,
	    // ),
			// 'sub_id' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'char',
	      // 'length' => '10',
	      // 'not null' => FALSE,
	    // ),
	    // 'sub_name' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'char',
	      // 'length' => '150',
	      // 'not null' => FALSE,
	    // ),
	    // 'type' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'varchar',
	      // 'length' => '20',
	      // 'not null' => FALSE,
	    // ),
			// 'teacher1' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'varchar',
	      // 'length' => '50',
	      // 'not null' => FALSE,
	    // ),
			// 'teacher1_emp_id' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'varchar',
	      // 'length' => '50',
	      // 'not null' => FALSE,
	    // ),
			// 'teacher2' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'varchar',
	      // 'length' => '50',
	      // 'not null' => FALSE,
	    // ),
			// 'teacher2_emp_id' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'varchar',
	      // 'length' => '50',
	      // 'not null' => FALSE,
	    // ),
			// 'teacher3' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'varchar',
	      // 'length' => '50',
	      // 'not null' => FALSE,
	    // ),
			// 'teacher3_emp_id' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'varchar',
	      // 'length' => '50',
	      // 'not null' => FALSE,
	    // ),
			// 'teacher4' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'varchar',
	      // 'length' => '50',
	      // 'not null' => FALSE,
	    // ),
			// 'teacher4_emp_id' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'varchar',
	      // 'length' => '50',
	      // 'not null' => FALSE,
	    // ),
			// 'teacher5' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'varchar',
	      // 'length' => '50',
	      // 'not null' => FALSE,
	    // ),
			// 'teacher5_emp_id' => array(
	      // 'description' => 'TODO: please describe this field!',
	      // 'type' => 'varchar',
	      // 'length' => '50',
	      // 'not null' => FALSE,
	    // ),
	  // ),
	  // 'primary key' => array('id', 'sub_id'),
	// );
  
  // $session_id = (string)variable_get('essa_sid');
  // $class_list = 'essa_'.$session_id.'_class_list';
  
  // $classes = db_query("
    // SELECT class_id from {$class_list} order by weight;
  // ");
  
  // foreach($classes as $class){
    // $name_of_table = 'essa_'.$session_id.'_subjects_'.clean_sub_string_cl($class->class_id);
    // if(!db_table_exists($name_of_table)){
			// db_create_table($name_of_table, $schema['subject']);
		// }
  // }
  
}
/**--------------------------------------------------------------------------------------------------------------------------------------------------------------
 *find_weights - to attach a weight for all class, to maintain the order of classes
 *--------------------------------------------------------------------------------------------------------------------------------------------------------------*/
function find_weight_cl(){
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
function clean_sub_string_cl($string) {
   $string = str_replace('-', '', $string); // Replaces all spaces with hyphens.
	 $string = str_replace(' ', '', $string);
   return preg_replace('/[^A-Za-z0-9\-]/', '', $string); // Removes special chars.
}