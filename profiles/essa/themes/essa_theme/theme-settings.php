<?php

/**
 * @file
 * Theme setting callbacks for the Essa_theme theme.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
function essa_theme_form_system_theme_settings_alter(&$form, &$form_state) {

  // Get essa_theme theme path.
  global $base_url;
  $essa_theme_path = drupal_get_path('theme', 'essa_theme');
  $old_css_path = $essa_theme_path . '/css/custom.css';
  $custom_css_path = 'public://essa_theme-custom.css';
  $custom_css_dir = str_replace($base_url . '/', "", file_create_url($custom_css_path));
  $custom_css_url = file_create_url($custom_css_path);

  // Try to create the essa_theme-custom.css file automatically.
  if (!file_exists($custom_css_path)) {

    // Try to migrate from the old css.
    if (file_exists($old_css_path)) {
      file_unmanaged_copy($old_css_path, $custom_css_path, FILE_EXISTS_ERROR);
    }
    // Else create e new blank css file.
    else {
      file_unmanaged_save_data("", $custom_css_path, FILE_EXISTS_ERROR);
    }

  }

  // Notify user to remove his old css file.
  if (file_exists($old_css_path)) {
    drupal_set_message(t('Please delete the old @css_location file, as its no longer used.', array('@css_location file' => $old_css_path)), 'warning');
  }

  $form['essa_theme_custom'] = array(
    '#type' => 'fieldset',
    '#title' => t('Essa_theme Customization'),
    '#weight' => -10,
  );

  $form['skin'] = array(
    '#type' => 'fieldset',
    '#title' => t('Essa_theme skin'),
    '#weight' => -11,
  );

  // Create the select list.
  $form['skin']['essa_theme_theme_skin'] = array(
    '#type' => 'select',
    '#title' => t('Skin selection'),
    '#default_value' => theme_get_setting('essa_theme_theme_skin'),
    '#options' => array(
      'default' => t('Essa_theme Default'),
      //'dark' => t('Dark'),
      //'flat' => t('Flat'),
      'material' => t('Material (BETA version)'),
      'alternative' => t('Alternative'),
    ),
    '#description' => t('Select desired skin style. Note that this feature is in beta stage and there might be some issues.'),
    '#required' => FALSE,
  );

  $form['essa_theme_custom']['style_checkboxes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Style checkboxes and radio buttons in Webkit browsers.'),
    '#description' => t('Enabling this option will style checkbox and radio buttons for Webkit browsers like Google Chrome, Safari, Opera and their mobile versions.
     Enabling this option will <strong>not</strong> have any negative impact on older browsers that dont support pure CSS styling of checkboxes like Internet Explorer or Firefox.'),
    '#default_value' => theme_get_setting('style_checkboxes'),
  );

  $form['essa_theme_custom']['display_icons_config'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display icons in Configuration page'),
    '#default_value' => theme_get_setting('display_icons_config'),
  );

  $form['essa_theme_custom']['rounded_buttons'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use rounded buttons'),
    '#description' => t('Uncheck this setting if you dont like the rounded button styling for some action links'),
    '#default_value' => theme_get_setting('rounded_buttons'),
  );

  $form['essa_theme_custom']['sticky_actions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sticky form actions'),
    '#description' => t('This will make the form actions div fixed bottom positioning. So for example when you visit the node edit page you wont need to scroll down to save/preview/delete the node. The form action buttons will be sticky to the bottom of the screen.'),
    '#default_value' => theme_get_setting('sticky_actions'),
  );

  $form['essa_theme_custom']['avoid_custom_font'] = array(
    '#type' => 'checkbox',
    '#title' => t('Avoid using "Open Sans" font'),
    '#description' => t('(useful for languages that are not well supported by the "Open sans" font. Like Japanese for example)'),
    '#default_value' => theme_get_setting('avoid_custom_font'),
  );

  $form['essa_theme_custom']['use_custom_media_queries'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Custom Media Queries'),
    '#description' => t('You can override the mobile and tablet media queries from this option. Use it only if you know what media queries are and how to use them.'),
    '#default_value' => theme_get_setting('use_custom_media_queries'),
  );

  $form['essa_theme_custom']['media_queries'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Media Queries'),
    '#states' => array(
      // Hide the settings when the cancel notify checkbox is disabled.
      'visible' => array(
       ':input[name="use_custom_media_queries"]' => array('checked' => TRUE),
      ),
     ),
  );

  $form['essa_theme_custom']['media_queries']['media_query_mobile'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile media query'),
    '#description' => t('The media query to load the mobile.css styles.'),
    '#default_value' => theme_get_setting('media_query_mobile'),
  );

  $form['essa_theme_custom']['media_queries']['media_query_tablet'] = array(
    '#type' => 'textfield',
    '#title' => t('Tablet media query'),
    '#description' => t('The media query to load the tablet.css styles.'),
    '#default_value' => theme_get_setting('media_query_tablet'),
  );

  $form['essa_theme_custom']['custom_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use "essa_theme-custom.css"'),
    '#description' => t('Include essa_theme-custom.css file to override or add custom css code without subthememing/hacking Essa_theme Theme.'),
    '#default_value' => theme_get_setting('custom_css'),
  );

  $form['essa_theme_custom']['essa_theme_custom_check'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom CSS file check'),
    '#weight' => 50,
    '#states' => array(
      // Hide the settings when the cancel notify checkbox is disabled.
      'visible' => array(
       ':input[name="custom_css"]' => array('checked' => TRUE),
      ),
     ),
  );

  if (file_exists($custom_css_path)) {
    $form['essa_theme_custom']['essa_theme_custom_check']['custom_css_description'] = array(
      '#markup' => t('Custom CSS file Found in: !css', array('!css' => "<span class='css_path'>" . $custom_css_dir . "</span>")),
      '#prefix' => '<div class="messages status custom_css_found">',
      '#suffix' => '</div>',
    );
  }
  else {
    $form['essa_theme_custom']['essa_theme_custom_check']['custom_css_not_found'] = array(
      '#markup' => t('Custom CSS file not found. You must create the !css file manually.', array('!css' => "<span class='css_path'>" . $custom_css_dir . "</span>")),
      '#prefix' => '<div class="messages error custom_css_not_found">',
      '#suffix' => '</div>',
    );
  }
}
