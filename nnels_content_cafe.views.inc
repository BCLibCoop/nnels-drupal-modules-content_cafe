<?php

/**
 * Implements hook_views_data().
 *
 * Each content cafe table will define a field and the corresponding handler
 * will set a flag which will then be interpreted by hook_views_post_execute().
 * This hook will attach the data to the view result.
 */
function nnels_content_cafe_views_data() {
  $data = array();

  // Selected Annotation.
  $data['node']['content_cafe_selected_annotation'] = array(
    'title' => t('Selected Annotation'),
    'field' => array(
      'help'    => t('The selected annotation for this node, from the Content Cafe API.'),
      'handler' => 'nnels_content_cafe_selected_annotation_views_field_handler',
    ),
  );

  return $data;
}