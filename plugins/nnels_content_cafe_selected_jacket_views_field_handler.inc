<?php

/**
 * Selected Jacket field handler.
 */
class nnels_content_cafe_selected_jacket_views_field_handler extends views_handler_field {
  
  function option_definition() {
    $options = parent::option_definition();
  
    $options['image_style'] = array('default' => '');
    
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  
    $form['image_style'] = array(
      '#type'          => 'select',
      '#title'         => t('Image Style'),
      '#description'   => t('Select an image style to apply to the image.'),
      '#options'       => image_style_options(),
      '#default_value' => $this->options['image_style'],
      '#weight'        => -90,
    );
  }

  /**
   * Implements views_handler_field#query().
   */
  function query() {
    $this->field_selected_jacket = TRUE;
  }

  /**
   * Implements views_handler_field#render().
   */
  function render($value) {
    if( property_exists($value, 'content_cafe_selected_jacket') ) return
      $value->content_cafe_selected_jacket;
  }
}
