<?php

/**
 * Selected Flap field handler.
 */
class nnels_content_cafe_selected_flap_views_field_handler extends views_handler_field {

  /**
   * Implements views_handler_field#query().
   */
  function query() {
    $this->field_selected_flap = TRUE;
  }

  /**
   * Implements views_handler_field#render().
   */
  function render($value) {
    return $value->content_cafe_selected_flap;
  }
}
