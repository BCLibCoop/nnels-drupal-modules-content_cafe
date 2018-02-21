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

  // Selected Biography.
  $data['node']['content_cafe_selected_biography'] = array(
    'title' => t('Selected Biography'),
    'field' => array(
      'help'    => t('The selected biography for this node, from the Content Cafe API.'),
      'handler' => 'nnels_content_cafe_selected_biography_views_field_handler',
    ),
  );

  // Selected Excerpt.
  $data['node']['content_cafe_selected_excerpt'] = array(
    'title' => t('Selected Excerpt'),
    'field' => array(
      'help'    => t('The selected excerpt for this node, from the Content Cafe API.'),
      'handler' => 'nnels_content_cafe_selected_excerpt_views_field_handler',
    ),
  );

  // Selected Flap.
  $data['node']['content_cafe_selected_flap'] = array(
    'title' => t('Selected Flap'),
    'field' => array(
      'help'    => t('The selected flap for this node, from the Content Cafe API.'),
      'handler' => 'nnels_content_cafe_selected_flap_views_field_handler',
    ),
  );

  // Selected Jacket.
  $data['node']['content_cafe_selected_jacket'] = array(
    'title' => t('Selected Jacket'),
    'field' => array(
      'help'    => t('The selected jacket for this node, from the Content Cafe API.'),
      'handler' => 'nnels_content_cafe_selected_jacket_views_field_handler',
    ),
  );

  // Selected TOC.
  $data['node']['content_cafe_selected_toc'] = array(
    'title' => t('Selected TOC'),
    'field' => array(
      'help'    => t('The selected toc for this node, from the Content Cafe API.'),
      'handler' => 'nnels_content_cafe_selected_toc_views_field_handler',
    ),
  );

  return $data;
}