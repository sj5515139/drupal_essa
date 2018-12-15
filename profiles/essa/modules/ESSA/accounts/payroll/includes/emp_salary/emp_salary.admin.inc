<?php

/**
 *Implements page callback function - emp_salary
 */
function emp_salary($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$emp_table = 'essa_'.$session_id.'_master_staff_table';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$emp_sal_table = 'essa_'.$session_id.'_pr_emp_sal';
	$x = '<i class = "fa fa-pencil"></i>';
	
	$form['emp_id_filter'] = array(
		'#type' => 'textfield',
		'#title' => 'Filter by Emp ID',
		'#autocomplete_path' => 'staff/autocomplete',
		'#size' => 35,
		'#ajax' => array(
      'event' => 'blur',
      'callback' => 'filter_emp',
      'wrapper' => 'payroll_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
	);
	
	$sel_options = array('--Select--');
	$sal_options = array('--Select--', 'UNASSIGNED');
	$sal_type = db_query("
		SELECT * from {$sal_table};"
	);	
	foreach($sal_type as $st){
		$sal_options[] = $st->title;
		$sel_options[] = $st->title;
	}
	
	$form['sal_id_filter'] = array(
		'#type' => 'select',
		'#title' => 'Filter by Salay Category',
		'#options' => drupal_map_assoc($sal_options),
		'#ajax' => array(
      'event' => 'change',
      'callback' => 'filter_emp',
      'wrapper' => 'payroll_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
	);
	
	if(!empty($form_state['values']['emp_id_filter'])){
		preg_match('#\((.*?)\)#', $form_state['values']['emp_id_filter'], $match);
		$empid = $match[1];
		
		$employee = db_query("
			SELECT * from {$emp_table} where emp_id = :ei;", array(':ei' => $empid)
		);
		foreach($employee as $emp){
			$total[$emp->emp_id] = 0;
			if($emp->type == 'Teaching'){
				$sal_grade = $emp->grade;
			}else{
				$sal_grade = $emp->nt_grade;
			}
			
			$sal_type = db_query("
				SELECT * from {$sal_table} where title = :t;", array(':t' => $sal_grade)
			);	
			foreach($sal_type as $st){
				$sal_id = $st->sal_id;
				$sal_title = $st->title;
			}
			
			$name = $emp->fname.' '.$emp->lname;
			$emp_row[$emp->emp_id] = array(
				'#tree' => TRUE,
				$emp->emp_id => array(
				  'c1' => array(
				    '#type' => 'markup',
				    '#markup' => '<h3>'. $emp->emp_id .'</h3>',
					),
					'c2' => array(
				    '#type' => 'markup',
				    '#markup' => '<h3>'. $name .'</h3>',
					),
					'c3' => array(
				    '#type' => 'markup',
				    '#markup' => '<h3>'. $sal_title .'</h3>',
					),
				),
			);
			
			$sal_heads = db_query("
				SELECT * from {$sal_detail_table};"
			);	
			foreach($sal_heads as $sh){
				$heads[] = $sh->sal_head;
			}
			$heads = array_unique($heads);
			
			foreach($heads as $head){
				$flag = 0;
				$emp_sal = db_query("
				  SELECT * from {$emp_sal_table} where emp_id = :ei and sal_head = :sh;", array(':ei' => $emp->emp_id, ':sh' => $head)
				);
				foreach($emp_sal as $es){
					if($es->sal_head != $head){
						$amount = NULL;	
					}else{
						$amount = $es->amount;
					}
				}
				
				$sal_detail = db_query("
				  SELECT * from {$sal_detail_table} where sal_id = :si and sal_head = :sh;", array(':si' => $sal_id, ':sh' => $head)
				);
				foreach($sal_detail as $sd){
					if($sd->is_deduction == 0){
						$flag = 0;
					}else{
						$flag = 1;
					}
				}
				
				if($flag == 0){
					$sal_col = array(
						'#type' => 'markup',
						'#markup' => '<h3>'. $amount .'</h3>',
					);
					
					$total[$emp->emp_id] = $total[$emp->emp_id] + $amount;
					array_push($emp_row[$emp->emp_id][$emp->emp_id], $sal_col);
				}else{
					$sal_col = array(
						'#type' => 'markup',
						'#markup' => '<h3 style = "color: RED">'. $amount .'</h3>',
					);
					
					$total[$emp->emp_id] = $total[$emp->emp_id] - $amount;
					array_push($emp_row[$emp->emp_id][$emp->emp_id], $sal_col);
				}
				$amount = NULL;
			}
			
			$total_col = array(
				'#type' => 'markup',
				'#markup' => '<h3><b>'.$total[$emp->emp_id].'</b></h3>',
			); 
			array_push($emp_row[$emp->emp_id][$emp->emp_id], $total_col);
			
			$edit_col = array(
				'#type' => 'submit',
				'#value' => 'Edit',
				'#submit' => array('edit_emp_sal'),
				'#name' => $emp->emp_id,
				//'#markup' => '<h3>'.l($x, 'admin/accounts/payroll/salary_structure/'.$st->sal_id, array('html' => TRUE)).'</h3>',
			);
			array_push($emp_row[$emp->emp_id][$emp->emp_id], $edit_col);
		}
	}elseif(isset($form_state['values']['sal_id_filter']) && $form_state['values']['sal_id_filter'] != '--Select--'){
		if($form_state['values']['sal_id_filter'] == 'UNASSIGNED'){
			$employee = db_query("
				SELECT * from {$emp_table} where status = 1;"
			);
			foreach($employee as $emp){
				$total[$emp->emp_id] = 0;
				if($emp->type == 'Teaching'){
					$sal_grade = $emp->grade;
				}else{
					$sal_grade = $emp->nt_grade;
				}
				
				$sal_type = db_query("
					SELECT * from {$sal_table} where title = :t;", array(':t' => $sal_grade)
				);	
				foreach($sal_type as $st){
					$sal_id = $st->sal_id;
					$sal_title = $st->title;
				}
				
				$name = $emp->fname.' '.$emp->lname;
				
				if($emp->grade == NULL && $emp->nt_grade == NULL){
					$emp_row[$emp->emp_id] = array(
						'#tree' => TRUE,
						$emp->emp_id => array(
						  'c1' => array(
						    '#type' => 'markup',
						    '#markup' => '<h3>'. $emp->emp_id .'</h3>',
							),
							'c2' => array(
						    '#type' => 'markup',
						    '#markup' => '<h3>'. $name .'</h3>',
							),
							'c3' => array(
						    '#type' => 'select',
						    '#options' => drupal_map_assoc($sel_options),
							),
						),
					);
					
					$sal_heads = db_query("
						SELECT * from {$sal_detail_table};"
					);	
					foreach($sal_heads as $sh){
						$heads[] = $sh->sal_head;
					}
					$heads = array_unique($heads);
					
					foreach($heads as $head){
						$flag = 0;
						$emp_sal = db_query("
						  SELECT * from {$emp_sal_table} where emp_id = :ei and sal_head = :sh;", array(':ei' => $emp->emp_id, ':sh' => $head)
						);
						foreach($emp_sal as $es){
							if($es->sal_head != $head){
								$amount = NULL;	
							}else{
								$amount = $es->amount;
							}
						}
						
						$sal_detail = db_query("
						  SELECT * from {$sal_detail_table} where sal_id = :si and sal_head = :sh;", array(':si' => $sal_id, ':sh' => $head)
						);
						foreach($sal_detail as $sd){
							if($sd->is_deduction == 0){
								$flag = 0;
							}else{
								$flag = 1;
							}
						}
						
						if($flag == 0){
							$sal_col = array(
								'#type' => 'markup',
								'#markup' => '<h3>'. $amount .'</h3>',
							);
							
							$total[$emp->emp_id] = $total[$emp->emp_id] + $amount;
							array_push($emp_row[$emp->emp_id][$emp->emp_id], $sal_col);
						}else{
							$sal_col = array(
								'#type' => 'markup',
								'#markup' => '<h3 style = "color: RED"></h3>',
							);
							
							$total[$emp->emp_id] = $total[$emp->emp_id] - $amount;
							array_push($emp_row[$emp->emp_id][$emp->emp_id], $sal_col);
						}
						$amount = NULL;
					}
					
					$total_col = array(
						'#type' => 'markup',
						'#markup' => '<h3><b></b></h3>',
					); 
					array_push($emp_row[$emp->emp_id][$emp->emp_id], $total_col);
					
					$edit_col = array(
						'#type' => 'markup',
						'#markup' => '<p></p>',
					);
					array_push($emp_row[$emp->emp_id][$emp->emp_id], $edit_col);
				}
			}
		}else{
			$employee = db_query("
				SELECT * from {$emp_table} where grade = :g or nt_grade = :g  and status = 1;", array(':g' => $form_state['values']['sal_id_filter'])
			);
			foreach($employee as $emp){
				$total[$emp->emp_id] = 0;
				if($emp->type == 'Teaching'){
					$sal_grade = $emp->grade;
				}else{
					$sal_grade = $emp->nt_grade;
				}
				
				$sal_type = db_query("
					SELECT * from {$sal_table} where title = :t;", array(':t' => $sal_grade)
				);	
				foreach($sal_type as $st){
					$sal_id = $st->sal_id;
					$sal_title = $st->title;
				}
				
				$name = $emp->fname.' '.$emp->lname;
				$emp_row[$emp->emp_id] = array(
					'#tree' => TRUE,
					$emp->emp_id => array(
					  'c1' => array(
					    '#type' => 'markup',
					    '#markup' => '<h3>'. $emp->emp_id .'</h3>',
						),
						'c2' => array(
					    '#type' => 'markup',
					    '#markup' => '<h3>'. $name .'</h3>',
						),
						'c3' => array(
					    '#type' => 'markup',
					    '#markup' => '<h3>'. $sal_title .'</h3>',
						),
					),
				);
				
				$sal_heads = db_query("
					SELECT * from {$sal_detail_table};"
				);	
				foreach($sal_heads as $sh){
					$heads[] = $sh->sal_head;
				}
				$heads = array_unique($heads);
				
				foreach($heads as $head){
					$flag = 0;
					$emp_sal = db_query("
					  SELECT * from {$emp_sal_table} where emp_id = :ei and sal_head = :sh;", array(':ei' => $emp->emp_id, ':sh' => $head)
					);
					foreach($emp_sal as $es){
						if($es->sal_head != $head){
							$amount = NULL;	
						}else{
							$amount = $es->amount;
						}
					}
					
					$sal_detail = db_query("
					  SELECT * from {$sal_detail_table} where sal_id = :si and sal_head = :sh;", array(':si' => $sal_id, ':sh' => $head)
					);
					foreach($sal_detail as $sd){
						if($sd->is_deduction == 0){
							$flag = 0;
						}else{
							$flag = 1;
						}
					}
					
					if($flag == 0){
						$sal_col = array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $amount .'</h3>',
						);
						
						$total[$emp->emp_id] = $total[$emp->emp_id] + $amount;
						array_push($emp_row[$emp->emp_id][$emp->emp_id], $sal_col);
					}else{
						$sal_col = array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "color: RED">'. $amount .'</h3>',
						);
						
						$total[$emp->emp_id] = $total[$emp->emp_id] - $amount;
						array_push($emp_row[$emp->emp_id][$emp->emp_id], $sal_col);
					}
					$amount = NULL;
				}
				
				$total_col = array(
					'#type' => 'markup',
					'#markup' => '<h3><b>'.$total[$emp->emp_id].'</b></h3>',
				); 
				array_push($emp_row[$emp->emp_id][$emp->emp_id], $total_col);
				
				$edit_col = array(
					'#type' => 'submit',
					'#value' => 'Edit',
					'#submit' => array('edit_emp_sal'),
					'#name' => $emp->emp_id,
					//'#markup' => '<h3>'.l($x, 'admin/accounts/payroll/salary_structure/'.$st->sal_id, array('html' => TRUE)).'</h3>',
				);
				array_push($emp_row[$emp->emp_id][$emp->emp_id], $edit_col);
			}
		}
	}else{
		$sal_grade = NULL;
		
		$employee = db_query("
			SELECT * from {$emp_table} where status = 1;"
		);
		foreach($employee as $emp){
			$total[$emp->emp_id] = 0;
			if($emp->type == 'Teaching'){
				$sal_grade = $emp->grade;
			}else{
				$sal_grade = $emp->nt_grade;
			}
			
			$sal_type = db_query("
				SELECT * from {$sal_table} where title = :t;", array(':t' => $sal_grade)
			);	
			foreach($sal_type as $st){
				$sal_id = $st->sal_id;
				$sal_title = $st->title;
			}
			
			$name = $emp->fname.' '.$emp->lname;
			
			if($emp->grade == NULL && $emp->nt_grade == NULL){
				$emp_row[$emp->emp_id] = array(
					'#tree' => TRUE,
					$emp->emp_id => array(
					  'c1' => array(
					    '#type' => 'markup',
					    '#markup' => '<h3>'. $emp->emp_id .'</h3>',
						),
						'c2' => array(
					    '#type' => 'markup',
					    '#markup' => '<h3>'. $name .'</h3>',
						),
						'c3' => array(
					    '#type' => 'select',
					    '#options' => drupal_map_assoc($sel_options),
						),
					),
				);
				
				$sal_heads = db_query("
					SELECT * from {$sal_detail_table};"
				);	
				foreach($sal_heads as $sh){
					$heads[] = $sh->sal_head;
				}
				$heads = array_unique($heads);
				
				foreach($heads as $head){
					$flag = 0;
					$emp_sal = db_query("
					  SELECT * from {$emp_sal_table} where emp_id = :ei and sal_head = :sh;", array(':ei' => $emp->emp_id, ':sh' => $head)
					);
					foreach($emp_sal as $es){
						if($es->sal_head != $head){
							$amount = NULL;	
						}else{
							$amount = $es->amount;
						}
					}
					
					$flag = 0;
					if($flag == 0){
						$sal_col = array(
							'#type' => 'markup',
							'#markup' => '<h3>'. ''.'</h3>',
						);
						
						//$total[$emp->emp_id] = $total[$emp->emp_id] + $amount;
						array_push($emp_row[$emp->emp_id][$emp->emp_id], $sal_col);
					}else{
						$sal_col = array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "color: RED"></h3>',
						);
						
						$total[$emp->emp_id] = $total[$emp->emp_id] - $amount;
						array_push($emp_row[$emp->emp_id][$emp->emp_id], $sal_col);
					}
					$amount = NULL;
				}
				
				$total_col = array(
					'#type' => 'markup',
					'#markup' => '<h3><b></b></h3>',
				); 
				array_push($emp_row[$emp->emp_id][$emp->emp_id], $total_col);
				
				$edit_col = array(
					'#type' => 'markup',
					'#markup' => '<p></p>',
				);
				array_push($emp_row[$emp->emp_id][$emp->emp_id], $edit_col);
			}else{
				$emp_row[$emp->emp_id] = array(
					'#tree' => TRUE,
					$emp->emp_id => array(
					  'c1' => array(
					    '#type' => 'markup',
					    '#markup' => '<h3>'. $emp->emp_id .'</h3>',
						),
						'c2' => array(
					    '#type' => 'markup',
					    '#markup' => '<h3>'. $name .'</h3>',
						),
						'c3' => array(
					    '#type' => 'markup',
					    '#markup' => '<h3>'. $sal_title .'</h3>',
						),
					),
				);
				
				$sal_heads = db_query("
					SELECT * from {$sal_detail_table};"
				);	
				foreach($sal_heads as $sh){
					$heads[] = $sh->sal_head;
				}
				$heads = array_unique($heads);
				
				foreach($heads as $head){
					$amount = NULL;	
					$flag = 0;
					$emp_sal = db_query("
					  SELECT * from {$emp_sal_table} where emp_id = :ei and sal_head = :sh;", array(':ei' => $emp->emp_id, ':sh' => $head)
					);
					foreach($emp_sal as $es){
						if($es->sal_head != $head){
							$amount = NULL;	
						}else{
							$amount = $es->amount;
						}
					}
					
					$sal_detail = db_query("
					  SELECT * from {$sal_detail_table} where sal_id = :si and sal_head = :sh;", array(':si' => $sal_id, ':sh' => $head)
					);
					foreach($sal_detail as $sd){
						if($sd->is_deduction == 0){
							$flag = 0;
						}else{
							$flag = 1;
						}
					}
					
					if($flag == 0){
						$sal_col = array(
							'#type' => 'markup',
							'#markup' => '<h3>'. $amount .'</h3>',
						);
						
						$total[$emp->emp_id] = $total[$emp->emp_id] + $amount;
						array_push($emp_row[$emp->emp_id][$emp->emp_id], $sal_col);
					}else{
						$sal_col = array(
							'#type' => 'markup',
							'#markup' => '<h3 style = "color: RED">'. $amount .'</h3>',
						);
						
						$total[$emp->emp_id] = $total[$emp->emp_id] - $amount;
						array_push($emp_row[$emp->emp_id][$emp->emp_id], $sal_col);
					}
					$amount = NULL;
				}
				
				$total_col = array(
					'#type' => 'markup',
					'#markup' => '<h3><b>'.$total[$emp->emp_id].'</b></h3>',
				); 
				array_push($emp_row[$emp->emp_id][$emp->emp_id], $total_col);
				
				$edit_col = array(
					'#type' => 'submit',
					'#value' => 'Edit',
					'#submit' => array('edit_emp_sal'),
					'#name' => $emp->emp_id,
					//'#markup' => '<h3>'.l($x, 'admin/accounts/payroll/salary_structure/'.$st->sal_id, array('html' => TRUE)).'</h3>',
				);
				array_push($emp_row[$emp->emp_id][$emp->emp_id], $edit_col);
			}
		}
	}
	
	$form['cnt'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "payroll_wrapper">',
		'#suffix' => '</div>',
	);
	
	$form['cnt']['emp_sal_table'] = array(
	  '#theme' => 'emp_sal_table',
		'rows' => $emp_row,
	);
	
	//dsm($emp_row);
	$form['ins'] = array(
		'#type' => 'markup',
		'#markup' => '<h4><b>NOTE: </b>Columns marked in <span style = "color:RED">RED</span> are deductions.</h4>',
	);
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
	
	return $form;
}

/**
 *Implements submit function.
 */
function emp_salary_submit($form, &$form_state){
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$emp_table = 'essa_'.$session_id.'_master_staff_table';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$emp_sal_table = 'essa_'.$session_id.'_pr_emp_sal';
	
	foreach($form_state['values'] as $key => $val){
		if(is_array($val)){
			foreach($val as $emp_id => $v){
				if($v['c3'] != '--Select--'){
					$employees = db_query("
					  SELECT * from {$emp_table} where emp_id = :ei;", array('ei' => $emp_id)
					);
					foreach($employees as $emp){
						$type = $emp->type;
						if($type == 'Teaching'){
							db_update($emp_table)
								->fields (array(
									'grade' => $v['c3'],
								))
							->condition('emp_id', $emp_id, '=')
							->execute();
						}else{
							db_update($emp_table)
								->fields (array(
									'nt_grade' => $v['c3'],
								))
							->condition('emp_id', $emp_id, '=')
							->execute();
						}
					}
				}
			}
		}
	}
	
	drupal_cron_run();
}

/**
 *Ajax Callback for filters.
 */
function filter_emp($form, &$form_state){
	return $form['cnt'];
}

/**
 *Submit function for edit sal link.
 */
function edit_emp_sal($form, &$form_state){
	global $user;
	variable_set('edit_emp_sal'.$user->uid, $form_state['triggering_element']['#name']);
	
	global $base_url;
	$url = $base_url.'/admin/accounts/payroll/emp_sal/#overlay=edit_emp_sal';
	$custom_url =  urldecode($url);
	$form_state['redirect'] = $custom_url;
}

/**
 *Theme function
 */
function theme_emp_sal_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
	$header = array(t('Emp Id'), t('Name'), t('Salary Type'));
	
	$session_id = (string)variable_get('essa_sid');
	$sal_table = 'essa_'.$session_id.'_pr_salary_structure';
	$emp_table = 'essa_'.$session_id.'_master_staff_table';
	$sal_detail_table = 'essa_'.$session_id.'_pr_salary_detail';
	$sal_heads = db_query("
		SELECT * from {$sal_detail_table};"
	);	
	foreach($sal_heads as $sh){
		$heads[] = $sh->sal_head;
	}
	$heads = array_unique($heads);
	
	$header = array_merge($header, $heads);
	$x= array('Total','');
  $header = array_merge($header, $x);
  
  // Setup the structure to be rendered and returned.
  $content = array(
    '#theme' => 'table',
    '#rows' => array(),
    '#header' => $header,
  );
  
  // Traverse each row.  @see element_chidren().
  foreach (element_children($rows) as $row_index) {
    $row = array();
    // Traverse each column in the row.  @see element_children().
    foreach (element_children($rows[$row_index]) as $col_index) {
      // Traverse each column in the row.  @see element_children().
      foreach (element_children($rows[$row_index][$col_index]) as $col_index1) {
      // Render the column form element.
        $row[] = drupal_render($rows[$row_index][$col_index][$col_index1]);
      }
    }
    // Add the row to the table.
    $content['#rows'][] = $row;
  }

  // Redner the table and return.
  return drupal_render($content);
}

/*
 
 $emp_sal = db_query("
		  SELECT * from {$emp_sal_table} where emp_id = :ei;", array(':ei' => $emp->emp_id)
		);
		foreach($emp_sal as $es){
			$sal_col = array(
				'#type' => 'markup',
				'#markup' => '<h3>'. $es->amount .'</h3>',
			);
			array_push($emp_row[$emp->emp_id][$emp->emp_id], $sal_col);
		}
 
 
 
 
 $emp_sal = db_query("
    SELECT * from {$emp_sal_table};
  ");
	foreach($emp_sal as $sal){
		$emp_id = $sal->emp_id;
		$employee = db_query("
		  SELECT * from {$emp_table} where emp_id = :ei;", array(':ei' => $emp_id)
		);
		foreach($employee as $emp){
			$name = $emp->fname.' '.$emp->lname;
		}
		
		$emp_row[$emp_id] = array(
			'#tree' => TRUE,
			$emp_id => array(
			  'c1' => array(
			    '#type' => 'markup',
			    '#markup' => '<h3>'. $emp_id .'</h3>',
				),
				'c2' => array(
			    '#type' => 'markup',
			    '#markup' => '<h3>'. $name .'</h3>',
				),
			),
		);
		
		$emp_sal_detail = db_query("
		  SELECT * from {$emp_sal_table} where emp_id = :ei;", array('ei' => $emp_id)
		);
		foreach($emp_sal_detail as $esd){
			$sal_col[$emp_id] = array(
				$esd->sal_head => array(
					'#type' => 'markup',
				  '#markup' => '<h3>'. $esd->amount .'</h3>',
				),
			);
			dsm($sal_col);			
		}
	}
	*/