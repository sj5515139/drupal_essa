<?php

/**
 * Theme function displays an image rendered using the specified style.
 *
 * @ingroup image_example
 */
function theme_school_master_image($variables) {
  $image = $variables['image'];
  $style = $variables['style'];

  // theme_image_style() is the primary method for displaying images using
  // one of the defined styles. The $variables array passed to the theme
  // contains the following two important values:
  // - 'style_name': the name of the image style to use when displaying the
  //   image.
  // - 'path': the $file->uri of the image to display.
  //
  // When given a style and an image path the function will first determine
  // if a derivative image already exists, in which case the existing image
  // will be displayed. If the derivative image does not already exist the
  // function returns an <img> tag with a specially crafted callback URL
  // as the src attribute for the tag. When accessed, the callback URL will
  // generate the derivative image and serve it to the browser.
  $output = theme('image_style',
    array(
      'style_name' => $style,
      'path' => $image->uri,
      'getsize' => FALSE,
    )
  );
  $output .= '<p>' . t('This image is being displayed using the image style %style_name.', array('%style_name' => $style)) . '</p>';
  return $output;
}
