<?php

/**
 *Implements page callback function set_rp
 */
function set_rp($form = array(), &$form_state){
  $session_id = (string)variable_get('essa_sid');
	$certificate_table = 'essa_'.$session_id.'_certificate_templates';
	global $user;
  $form['cer_type'] = array(
    '#type' => 'value',
    '#value' => variable_get('certificate_template-'.$user->uid),
  );
	dsm(variable_get('certificate_class_'.$user->uid));
  if(variable_get('certificate_class_'.$user->uid) != NULL){
    $form['type'] = array(
      '#type' => 'value',
      '#value' => 'class'
    );
    $form['class'] = array(
      '#type' => 'value',
      '#value' => variable_get('certificate_class_'.$user->uid),
    );
    $form['section'] = array(
      '#type' => 'value',
      '#value' => variable_get('certificate_section_'.$user->uid)
    );
    $form['for_class'] = array(
      '#type' => 'markup',
      '#markup' => '<h2> Setting replacement values for - <b>'.variable_get('certificate_class_'.$user->uid).'-'.variable_get('certificate_section_'.$user->uid).'</b></h2>'
    );
    $certificates = db_query(
    	"SELECT * from $certificate_table where cer_id = :ci;", array(':ci' => variable_get('certificate_template-'.$user->uid))
    );
    foreach($certificates as $certificate){
      $label[1]['label'] = $certificate->rp_label1;
      $label[2]['label'] = $certificate->rp_label2;
      $label[3]['label'] = $certificate->rp_label3;
      $label[4]['label'] = $certificate->rp_label4;
      $label[5]['label'] = $certificate->rp_label5;
    }
    
    $default  = array();
    $student_table = 'essa_'.$session_id.'_master_student_table';
    $students = db_query(
    	"SELECT * from $student_table;"
    );
    foreach($students as $student){
      $certificate_rv_table = 'essa_'.$session_id.'_certificates_replacement_values';
      $replacement_values = db_query(
      	"SELECT * from $certificate_rv_table where adm_no = :an;", array(':an' => $student->adm_no)
      );
      foreach($replacement_values as $rv){
        $default[$student->adm_no][$student->adm_no]['1'] = $rv->rp_value1;
        $default[$student->adm_no][$student->adm_no]['2'] = $rv->rp_value2;
        $default[$student->adm_no][$student->adm_no]['3'] = $rv->rp_value3;
        $default[$student->adm_no][$student->adm_no]['4'] = $rv->rp_value4;
        $default[$student->adm_no][$student->adm_no]['5'] = $rv->rp_value5;
				if($rv->rp_value1 != NULL){
					$form['rp1'] = array(
						'#type' => 'textfield',
						'#title' =>  $label[1]['label'],
						'#size' => 30,
						'#default_value' => isset($default[$student->adm_no][$student->adm_no]['1'])? $default[$student->adm_no][$student->adm_no]['1']: NULL,
					);
				}
				if($rv->rp_value2 != NULL){
					$form['rp2'] = array(
						'#type' => 'textfield',
						'#title' =>  $label[2]['label'],
						'#size' => 30,
						'#default_value' => isset($default[$student->adm_no][$student->adm_no]['2'])? $default[$student->adm_no][$student->adm_no]['2']: NULL,
					);
				}
				if($rv->rp_value3 != NULL){
					$form['rp3'] = array(
						'#type' => 'textfield',
						'#title' =>  $label[3]['label'],
						'#size' => 30,
						'#default_value' => isset($default[$student->adm_no][$student->adm_no]['3'])? $default[$student->adm_no][$student->adm_no]['3']: NULL,
					);
				}
				if($rv->rp_value4 != NULL){
					$form['rp4'] = array(
						'#type' => 'textfield',
						'#title' =>  $label[4]['label'],
						'#size' => 30,
						'#default_value' => isset($default[$student->adm_no][$student->adm_no]['4'])? $default[$student->adm_no][$student->adm_no]['4']: NULL,
					);
				}
				if($rv->rp_value5 != NULL){
					$form['rp5'] = array(
						'#type' => 'textfield',
						'#title' =>  $label[5]['label'],
						'#size' => 30,
						'#default_value' => isset($default[$student->adm_no][$student->adm_no]['5'])? $default[$student->adm_no][$student->adm_no]['5']: NULL,
					);
				}
      }
			
      /*$row[$student->adm_no] = array(
      	'#tree' =>TRUE,
      	$student->adm_no => array(  //Generating unique array id for every form element
          'c1' =>array(
      		  '#type' => 'markup',
            '#markup' => '<h2>'.$student->adm_no.'</h2>',
      		),
      		'1' =>array(
      		  '#type' => 'textfield',
            '#size' => 30,
            '#default_value' => isset($default[$student->adm_no][$student->adm_no]['1'])? $default[$student->adm_no][$student->adm_no]['1']: NULL,
      		),
          '2' =>array(
      		  '#type' => 'textfield',
            '#size' => 30,
            '#default_value' => isset($default[$student->adm_no][$student->adm_no]['2'])? $default[$student->adm_no][$student->adm_no]['2']: NULL,
      		),
          '3' =>array(
      		  '#type' => 'textfield',
            '#size' => 30,
            '#default_value' => isset($default[$student->adm_no][$student->adm_no]['3'])? $default[$student->adm_no][$student->adm_no]['3']: NULL,
      		),
          '4' =>array(
      		  '#type' => 'textfield',
            '#size' => 30,
            '#default_value' => isset($default[$student->adm_no][$student->adm_no]['4'])? $default[$student->adm_no][$student->adm_no]['4']: NULL,
      		),
          '5' =>array(
      		  '#type' => 'textfield',
            '#size' => 30,
            '#default_value' => isset($default[$student->adm_no][$student->adm_no]['5'])? $default[$student->adm_no][$student->adm_no]['5']: NULL,
      		),
        ),
      );*/
    }
    
    //$form['rp_class_table'] = array(
    //  '#theme' => 'rp_class_table',
    //  'rows' => $row,
    //);
    
  }else{
    $form['type'] = array(
      '#type' => 'value',
      '#value' => 'student'
    );
    $form['adm_no'] = array(
      '#type' => 'value',
      '#value' => variable_get('certificate_adm_no-'.$user->uid),
    );
    
    $form['student'] = array(
      '#type' => 'markup',
      '#markup' => '<h2> Setting replacement values for - <b>'.variable_get('certificate_adm_no-'.$user->uid).'</b></h2>'
    );
    
    
    $certificates = db_query(
    	"SELECT * from $certificate_table where cer_id = :ci;", array(':ci' => variable_get('certificate_template-'.$user->uid))
    );
    foreach($certificates as $certificate){
			
		$certificate_rv_table = 'essa_'.$session_id.'_certificates_replacement_values';
    $replacement_values = db_query(
      "SELECT * from $certificate_rv_table where adm_no = :an;", array(':an' => variable_get('certificate_adm_no-'.$user->uid))
    );
		$adm_no = NULL;
    foreach($replacement_values as $rv){
      $default[1] = isset($rv->rp_value1)?$rv->rp_value1:NULL;
      $default[2] = isset($rv->rp_value2)?$rv->rp_value2:NULL;
      $default[3] = isset($rv->rp_value3)?$rv->rp_value3:NULL;
      $default[4] = isset($rv->rp_value4)?$rv->rp_value4:NULL;
      $default[5] = isset($rv->rp_value5)?$rv->rp_value5:NULL;
			$adm_no =	isset($rv->adm_no)?$rv->adm_no:NULL;
    }
			if($adm_no == variable_get('certificate_adm_no-'.$user->uid)){
				//dsm('1');
				if(isset($rv->rp_value1) != NULL){
					$form[1] = array(
						'#type' => 'textfield',
						'#title' => $certificate->rp_label1,
						'#default_value' => isset($default[1])? $default[1]: NULL,
					);
				}
				if(isset($rv->rp_value2) != NULL){
					$form[2] = array(
						'#type' => 'textfield',
						'#title' => $certificate->rp_label2,
						'#default_value' => isset($default[2])? $default[2]: NULL,
					);
				}
				if(isset($rv->rp_value3) != NULL){
					$form[3] = array(
						'#type' => 'textfield',
						'#title' => $certificate->rp_label3,
						'#default_value' => isset($default[3])? $default[3]: NULL,
					);
				}
				if(isset($rv->rp_value4) != NULL){
					$form[4] = array(
						'#type' => 'textfield',
						'#title' => $certificate->rp_label4,
						'#default_value' => isset($default[4])? $default[4]: NULL,
					);
				}
				if(isset($rv->rp_value5) != NULL){
					$form[5] = array(
						'#type' => 'textfield',
						'#title' => $certificate->rp_label5,
					);
				}
			}else{
				//dsm('2');
				if($certificate->rp_label1 != NULL){
					$form[1] = array(
						'#type' => 'textfield',
						'#title' => $certificate->rp_label1,
					);
				}
				if($certificate->rp_label2 != NULL){
					$form[2] = array(
						'#type' => 'textfield',
						'#title' => $certificate->rp_label2,
					);
				}
				if($certificate->rp_label3 != NULL){
					$form[3] = array(
						'#type' => 'textfield',
						'#title' => $certificate->rp_label3,
					);
				}
				if($certificate->rp_label4 != NULL){
					$form[4] = array(
						'#type' => 'textfield',
						'#title' => $certificate->rp_label4,
					);
				}
				if($certificate->rp_label5 != NULL){
					$form[5] = array(
						'#type' => 'textfield',
						'#title' => $certificate->rp_label5,
					);
				}
			}
			
    	
    }
  }
  
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  return($form);
}

function set_rp_submit($form, &$form_state){
 // dsm($form_state);
  $session_id = (string)variable_get('essa_sid');
	$certificate_rv_table = 'essa_'.$session_id.'_certificates_replacement_values';
  
  if($form_state['values']['type'] == 'class'){
    foreach($form_state['values'] as $value){
      if(is_array($value)){
        foreach($value as $key => $val){
          if(isset($val['1']) != NULL){
            db_merge($certificate_rv_table)
              ->key(array('cer_id' => $form_state['values']['cer_type'], 'adm_no' => $key))
            	->fields (array(
            	  'cer_id' => $form_state['values']['cer_type'],
                'adm_no' => $key,
                'class' => $form_state['values']['class'],
                'section' => $form_state['values']['section'],
                'rp_value1' => $val['1'],
            	)
            )	
            ->execute();
          }
          if(isset($val['2']) != NULL){
            db_merge($certificate_rv_table)
              ->key(array('cer_id' => $form_state['values']['cer_type'], 'adm_no' => $key))
            	->fields (array(
            	  'cer_id' => $form_state['values']['cer_type'],
                'adm_no' => $key,
                'class' => $form_state['values']['class'],
                'section' => $form_state['values']['section'],
                'rp_value2' => $val['2'],
            	)
            )	
            ->execute();
          }
          if(isset($val['3']) != NULL){
            db_merge($certificate_rv_table)
              ->key(array('cer_id' => $form_state['values']['cer_type'], 'adm_no' => $key))
            	->fields (array(
            	  'cer_id' => $form_state['values']['cer_type'],
                'adm_no' => $key,
                'class' => $form_state['values']['class'],
                'section' => $form_state['values']['section'],
                'rp_value3' => $val['3'],
            	)
            )	
            ->execute();
          }
          if(isset($val['4']) != NULL){
            db_merge($certificate_rv_table)
              ->key(array('cer_id' => $form_state['values']['cer_type'], 'adm_no' => $key))
            	->fields (array(
            	  'cer_id' => $form_state['values']['cer_type'],
                'adm_no' => $key,
                'class' => $form_state['values']['class'],
                'section' => $form_state['values']['section'],
                'rp_value4' => $val['4']
            	)
            )	
            ->execute();
          }
          if(isset($val['5']) != NULL){
            db_merge($certificate_rv_table)
              ->key(array('cer_id' => $form_state['values']['cer_type'], 'adm_no' => $key))
            	->fields (array(
            	  'cer_id' => $form_state['values']['cer_type'],
                'adm_no' => $key,
                'class' => $form_state['values']['class'],
                'section' => $form_state['values']['section'],
                'rp_value5' => $val['5']
            	)
            )	
            ->execute();
          }
        }
      }
    }
  }elseif($form_state['values']['type'] == 'student'){
    $student_table = 'essa_'.$session_id.'_master_student_table';
    $students = db_query(
    	"SELECT * from $student_table where adm_no = :an;", array(':an' => $form_state['values']['adm_no'])
    );
    foreach($students as $student){
      $class = $student->class;
      $section = $student->section;
    }
		
		if(isset($form_state['values'][1]) != NULL){
      db_merge($certificate_rv_table)
			->key(array('cer_id' => $form_state['values']['cer_type'], 'adm_no' => $form_state['values']['adm_no']))
    	->fields (array(
				'cer_id' => $form_state['values']['cer_type'],
       'adm_no' => $form_state['values']['adm_no'],
       'class' => $class,
       'section' => $section,
        'rp_value1' => $form_state['values'][1],
        )
      )	
      ->execute();
    }
		
		if(isset($form_state['values'][2]) != NULL){
      db_merge($certificate_rv_table)
			->key(array('cer_id' => $form_state['values']['cer_type'], 'adm_no' => $form_state['values']['adm_no']))
    	->fields (array(
				'cer_id' => $form_state['values']['cer_type'],
       'adm_no' => $form_state['values']['adm_no'],
       'class' => $class,
       'section' => $section,
        'rp_value2' => $form_state['values'][2],
        )
      )	
      ->execute();
    }
		
		if(isset($form_state['values'][3]) != NULL){
      db_merge($certificate_rv_table)
			->key(array('cer_id' => $form_state['values']['cer_type'], 'adm_no' => $form_state['values']['adm_no']))
    	->fields (array(
				'cer_id' => $form_state['values']['cer_type'],
       'adm_no' => $form_state['values']['adm_no'],
       'class' => $class,
       'section' => $section,
        'rp_value3' => $form_state['values'][3],
        )
      )	
      ->execute();
    }
    
		if(isset($form_state['values'][4]) != NULL){
      db_merge($certificate_rv_table)
			->key(array('cer_id' => $form_state['values']['cer_type'], 'adm_no' => $form_state['values']['adm_no']))
    	->fields (array(
				'cer_id' => $form_state['values']['cer_type'],
       'adm_no' => $form_state['values']['adm_no'],
       'class' => $class,
       'section' => $section,
			 'rp_value4' => $form_state['values'][4],
        )
      )	
      ->execute();
    }
		
		if(isset($form_state['values'][5]) != NULL){
      db_merge($certificate_rv_table)
			->key(array('cer_id' => $form_state['values']['cer_type'], 'adm_no' => $form_state['values']['adm_no']))
    	->fields (array(
				'cer_id' => $form_state['values']['cer_type'],
       'adm_no' => $form_state['values']['adm_no'],
       'class' => $class,
       'section' => $section,
       'rp_value5' => $form_state['values'][5],
        )
      )	
      ->execute();
    }
		
    //db_merge($certificate_rv_table)
    //  ->key(array('cer_id' => $form_state['values']['cer_type'], 'adm_no' => $form_state['values']['adm_no']))
    //  ->fields (array(
    //    'cer_id' => $form_state['values']['cer_type'],
    //    'adm_no' => $form_state['values']['adm_no'],
    //    'class' => $class,
    //    'section' => $section,
    //    'rp_value1' => $form_state['values'][1],
    //    'rp_value2' => $form_state['values'][2],
    //    'rp_value3' => $form_state['values'][3],
    //    'rp_value4' => $form_state['values'][4],
    //    'rp_value5' => $form_state['values'][5],
    //    )
    //  )	
    //->execute();
  }
	global $base_url;
	$form_state['redirect'] = $base_url.'/admin/certificates/generate_certificates/student-wise/';
}