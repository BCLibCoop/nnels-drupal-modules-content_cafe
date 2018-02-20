<?php

/**
 * Implements hook_views_data().
 *
 * Each content cafe table will define a field and filter and the corresponding
 * handlers will set a flag which will then be interpretted by
 * hook_views_post_execute(). This hook will actually add the field data or
 * filter the results (or both) appropriately.
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
    'filter' => array(
      'help'    => t('Filter the results by whether a selected annotation exists or not.'),
      'label'   => t('Selected Annotation Exists'),
      'handler' => 'nnels_content_cafe_selected_annotation_views_filter_handler',
      'type'    => 'yes-no',
    ),
  );

  // node_content_cafe table
  // $data['node_content_cafe']['table']['group'] = t('Content Cafe Data');
  // $data['node_content_cafe']['table']['base']  = array(
  //   'field'  => 'nid',
  //   'title'  => t('Content Cafe Data'),
  //   'help'   => t('Data from the Content Cafe API.'),
  //   'weight' => -10,
  // );
  // $data['node_content_cafe']['table']['join']  = array(
  //   'node' => array(
  //     'left_field' => 'nid',
  //     'field'      => 'nid',
  //   ),
  // );
  // $data['node_content_cafe']['nid'] = array(
  //   'title' => t('NID'),
  //   'help' => t('The nid field of the node_content_cafe table.'),
  //   'relationship' => array(
  //     'base' => 'node',
  //     'base field' => 'nid',
  //     'handler' => 'views_handler_relationship',
  //     'label' => t('Default label for the relationship'),
  //     'title' => t('Title shown when adding the relationship'),
  //     'help' => t('More information on this relationship'),
  //   ),
  // );
  // $data['node_content_cafe']['isbn_id'] = array(
  //   'title'  => t('ISBN ID'),
  //   'help'   => t('The isbn_id field of the node_content_cafe table.'),
  //   'field'  => array(
  //     'handler'        => 'views_handler_field_numeric',
  //     'click sortable' => TRUE,
  //   ),
  //   'filter' => array(
  //     'handler' => 'views_handler_filter_numeric',
  //   ),
  //   'sort'   => array(
  //     'handler' => 'views_handler_sort',
  //   ),
  // );


  // content_cafe_isbn_annotation table
  // $data['content_cafe_isbn_annotation']['table']['group'] = t('Content Cafe Data');
  // $data['content_cafe_isbn_annotation']['table']['base']  = array(
  //   'field'  => 'isbn_id',
  //   'title'  => t('Content Cafe ISBN Annotation Bridge'),
  //   'help'   => t('Data from the Content Cafe API.'),
  //   'weight' => -10,
  // );
  // $data['content_cafe_isbn_annotation']['table']['join']  = array(
  //   'node_content_cafe' => array(
  //     'left_field' => 'isbn_id',
  //     'field'      => 'isbn_id',
  //   ),
  // );
  // $data['content_cafe_isbn_annotation']['isbn_id'] = array(
  //   'title' => t('ISBN ID'),
  //   'help'   => t('The isbn_id field of the content_cafe_isbn_annotation table.'),
  //   'field' => array(
  //     'click sortable' => TRUE,
  //   ),
  //   'argument' => array(
  //     'handler' => 'views_handler_field_numeric',
  //     'click sortable' => TRUE,
  //     'numeric' => TRUE,
  //   ),
  //   'filter' => array(
  //     'handler' => 'views_handler_filter_numeric',
  //   ),
  //   'sort' => array(
  //     'handler' => 'views_handler_sort',
  //   ),
  //   // 'relationship' => array(
  //   //   'handler' => 'views_handler_relationship',
  //   //   'base' => 'node_content_cafe',
  //   //   'base field' => 'isbn_id',
  //   //   'title' => t('Content test'),
  //   //   'label' => t('Get the actual content from a content revision.'),
  //   // ),
  // );
  // $data['content_cafe_isbn_annotation']['annotation_id'] = array(
  //   'title'  => t('Annotation ID'),
  //   'help'   => t('The annotation_id field of the content_cafe_isbn_annotation table.'),
  //   'field'  => array(
  //     'handler'        => 'views_handler_field_numeric',
  //     'click sortable' => TRUE,
  //     'numeric' => TRUE,
  //   ),
  //   'filter' => array(
  //     'handler' => 'views_handler_filter_numeric',
  //   ),
  //   'sort'   => array(
  //     'handler' => 'views_handler_sort',
  //   ),
  // );

  return $data;
}