<?php

/**
 * Implements hook_views_data().
 */
function nnels_content_cafe_views_data() {
  $data['node_content_cafe']['table']['group'] = t('Content Cafe Data');
  $data['node_content_cafe']['table']['base']  = array(
    'field'  => 'nid',
    'title'  => t('Content Cafe Data'),
    'help'   => t('Data from the Content Cafe API.'),
    'weight' => -10,
  );
  $data['node_content_cafe']['table']['join']  = array(
    'node' => array(
      'left_field' => 'nid',
      'field'      => 'nid',
    ),
  );

  return $data;
}