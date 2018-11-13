<?php

/**
 * Settings Form.
 *
 * @return array
 */
function nnels_content_cafe_settings_form() {
  $form = array();

  $form['settings'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Settings'),
  );
  $form['settings']['nnels_content_cafe_api_url'] = array(
    '#type'          => 'textfield',
    '#title'         => t('API URL'),
    '#required'      => TRUE,
    '#default_value' => variable_get('nnels_content_cafe_api_url'),
  );
  $form['settings']['nnels_content_cafe_api_username'] = array(
    '#type'          => 'textfield',
    '#title'         => t('API Username'),
    '#required'      => TRUE,
    '#default_value' => variable_get('nnels_content_cafe_api_username'),
  );
  $form['settings']['nnels_content_cafe_api_password'] = array(
    '#type'          => 'textfield',
    '#title'         => t('API Password'),
    '#required'      => TRUE,
    '#default_value' => variable_get('nnels_content_cafe_api_password'),
  );

  return system_settings_form($form);
}

/**
 * Test Form.
 *
 * @return array
 */
function nnels_content_cafe_test_form() {
  $form = array();
  
  $form['test'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Run Tests'),
  );

  if (isset($_SESSION['nnels_content_cafe']['response'])) {
    $form['test']['request'] = array(
      '#type'          => 'textarea',
      '#title'         => t('API Request'),
      '#default_value' => $_SESSION['nnels_content_cafe']['request'],
    );
    $form['test']['response'] = array(
      '#type'          => 'textarea',
      '#title'         => t('API Response'),
      '#default_value' => $_SESSION['nnels_content_cafe']['response'],
    );
    unset($_SESSION['nnels_content_cafe']);
  }

  $form['test']['type'] = array(
    '#type'          => 'select',
    '#title'         => t('API Call Type'),
    '#options'       => array(
      'AvailableContent'       => t('Available Content'),
      t('Annotation')     => array(
        'AnnotationBrief'      => t('Annotation Brief'),
        'AnnotationDetail'     => t('Annotation Detail'),
      ),
      t('Biography')      => array(
        'BiographyBrief'       => t('Biography Brief'),
        'BiographyDetail'      => t('Biography Detail'),
      ),
      t('Demand History') => array(
        'DemandHistoryBrief'   => t('Demand History Brief'),
        'DemandHistoryDetail'  => t('Demand History Detail'),
      ),
      t('Demand')         => array(
        'DemandBrief'          => t('Demand Brief'),
        'DemandDetail'         => t('Demand Detail'),
      ),
      t('Excerpt')        => array(
        'ExcerptBrief'         => t('Excerpt Brief'),
        'ExcerptDetail'        => t('Excerpt Detail'),
      ),
      t('Flap')           => array(
        'FlapBrief'            => t('Flap Brief'),
        'FlapDetail'           => t('Flap Detail'),
      ),
      t('Inventory')      => array(
        'InventoryBrief'       => t('Inventory Brief'),
        'InventoryDetail'      => t('Inventory Detail'),
      ),
      t('Jacket')         => array(
        'JacketBrief'          => t('Jacket Brief'),
        'JacketDetail'         => t('Jacket Detail'),
      ),
      t('Muze')           => array(
        'MuzeVideoRelease'     => t('Muze Video Release'),
        'MuzeSimilarCinema'    => t('Muze Similar Cinema'),
        'MuzePopularMusic'     => t('Muze Popular Music'),
        'MuzeClassicalMusic'   => t('Muze Classical Music'),
        'MuzeEssentialArtists' => t('Muze Essential Artists'),
      ),
      t('Product')        => array(
        'ProductBrief'         => t('Product Brief'),
        'ProductDetail'        => t('Product Detail'),
      ),
      t('Review')         => array(
        'ReviewBrief'          => t('Review Brief'),
        'ReviewDetail'         => t('Review Detail'),
      ),
      t('TOC')            => array(
        'TocBrief'             => t('TOC Brief'),
        'TocDetail'            => t('TOC Detail'),
      ),
    ),
  );
  $form['test']['isbn'] = array(
    '#type'          => 'textfield',
    '#title'         => t('ISBN'),
    '#required'      => TRUE,
    '#default_value' => '9780789457868',
  );
  $form['test']['size'] = array(
    '#type'          => 'select',
    '#title'         => t('Size'),
    '#options'       => array(
      'S' => t('Small'),
      'M' => t('Medium'),
      'L' => t('Large'),
    ),
    '#states'        => array(
      'visible'      => array(
        ':input[name="type"]' => array(
          array('value' => 'JacketBrief'),
          array('value' => 'JacketDetail'),
        ),
      ),
    ),
  );
  $form['test']['submit'] = array(
    '#type'          => 'submit',
    '#value'         => 'Submit',
  );

  return $form;
}

/**
 * Test Form Submit.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return void
 */
function nnels_content_cafe_test_form_submit($form, $form_state) {
  $api = new NNELSContentCafe($form_state['values']['isbn']);

  switch ($form_state['values']['type']) {
    case 'AvailableContent':
      $api->AddAvailableContent();
      break;
    case 'AnnotationBrief':
      $api->AddAnnotationBrief();
      break;
    case 'AnnotationDetail':
      $api->AddAnnotationDetail();
      break;
    case 'BiographyBrief':
      $api->AddBiographyBrief();
      break;
    case 'BiographyDetail':
      $api->AddBiographyDetail();
      break;
    case 'DemandHistoryBrief':
      $api->AddDemandHistoryBrief();
      break;
    case 'DemandHistoryDetail':
      $api->AddDemandHistoryDetail();
      break;
    case 'DemandBrief':
      $api->AddDemandBrief();
      break;
    case 'DemandDetail':
      $api->AddDemandDetail();
      break;
    case 'ExcerptBrief':
      $api->AddExcerptBrief();
      break;
    case 'ExcerptDetail':
      $api->AddExcerptDetail();
      break;
    case 'FlapBrief':
      $api->AddFlapBrief();
      break;
    case 'FlapDetail':
      $api->AddFlapDetail();
      break;
    case 'InventoryBrief':
      $api->AddInventoryBrief();
      break;
    case 'InventoryDetail':
      $api->AddInventoryDetail();
      break;
    case 'JacketBrief':
      $api->AddJacketBrief($form_state['values']['size']);
      break;
    case 'JacketDetail':
      $api->AddJacketDetail($form_state['values']['size']);
      break;
    case 'MuzeVideoRelease':
      $api->AddMuzeVideoRelease();
      break;
    case 'MuzeSimilarCinema':
      $api->AddMuzeSimilarCinema();
      break;
    case 'MuzePopularMusic':
      $api->AddMuzePopularMusic();
      break;
    case 'MuzeClassicalMusic':
      $api->AddMuzeClassicalMusic();
      break;
    case 'MuzeEssentialArtists':
      $api->AddMuzeEssentialArtists();
      break;
    case 'ProductBrief':
      $api->AddProductBrief();
      break;
    case 'ProductDetail':
      $api->AddProductDetail();
      break;
    case 'ReviewBrief':
      $api->AddReviewBrief();
      break;
    case 'ReviewDetail':
      $api->AddReviewDetail();
      break;
    case 'TocBrief':
      $api->AddTocBrief();
      break;
    case 'TocDetail':
      $api->AddTocDetail();
      break;
  }
  $_SESSION['nnels_content_cafe'] = array(
    'request'  => $api->Request(),
    'response' => $api->Execute(),
  );
}

/**
 * Overview Form.
 *
 * @param array $form
 * @param array $form_state
 * @param int $nid
 *
 * @return array
 */
function nnels_content_cafe_overview_form($form, &$form_state, $nid) {
  $node = node_load($nid);
  drupal_set_title(t('Manage Content Cafe data for %node', array('%node' => $node->title)), PASS_THROUGH);

  // Load ISBN's associated with this node.
  $isbns       = field_get_items('node', $node,'field_isbn');
  $audio_isbns = field_get_items('node', $node,'field_isbn_audio');
  $valid_isbns = array();
  if ($isbns) {
    foreach ($isbns as $isbn) {
      if (nnels_content_cafe_validate_isbn($isbn['value'])) {
        $valid_isbns[$isbn['value']] = TRUE;
      }
      else {
        drupal_set_message(t('ISBN @isbn is invalid', array('@isbn' => $isbn['safe_value'])), 'warning');
      }
    }
  }
  if ($audio_isbns) {
    foreach ($audio_isbns as $isbn) {
      if (nnels_content_cafe_validate_isbn($isbn['value'])) {
        $valid_isbns[$isbn['value']] = TRUE;
      }
      else {
        drupal_set_message(t('Audio ISBN @isbn is invalid', array('@isbn' => $isbn['safe_value'])), 'warning');
      }
    }
  }

  // Load all data for the node.
  $isbns        = nnels_content_cafe_select_multiple_content_cafe_isbn_rows(array_keys($valid_isbns));
  $isbn_ids     = array_keys($isbns);
  $supplier_ids = array();
  $annotations  = nnels_content_cafe_select_multiple_content_cafe_annotation_rows($isbn_ids, $supplier_ids);
  $biographies  = nnels_content_cafe_select_multiple_content_cafe_biography_rows($isbn_ids, $supplier_ids);
  $excerpts     = nnels_content_cafe_select_multiple_content_cafe_excerpt_rows($isbn_ids);
  $flaps        = nnels_content_cafe_select_multiple_content_cafe_flap_rows($isbn_ids, $supplier_ids);
  $jackets      = nnels_content_cafe_select_multiple_content_cafe_jacket_rows($isbn_ids);
  $tocs         = nnels_content_cafe_select_multiple_content_cafe_toc_rows($isbn_ids);
  $suppliers    = nnels_content_cafe_select_multiple_content_cafe_supplier_rows(array_keys($supplier_ids));

  $form = array();

  $form['tabs'] = array(
    '#type' => 'vertical_tabs',
    '#tree' => TRUE,
  );

  // Annotations
  $form['tabs']['annotations'] = array(
    '#type'   => 'fieldset',
    '#title'  => 'Annotations',
    '#group'  => 'tabs',
    '#weight' => 0,
  );
  $form['tabs']['annotations']['table'] = nnels_content_cafe_overview_annotation_form($nid, $isbns, $annotations, $suppliers);

  // Biographies
  $form['tabs']['biographies'] = array(
    '#type'   => 'fieldset',
    '#title'  => 'Biographies',
    '#group'  => 'tabs',
    '#weight' => 1,
  );
  $form['tabs']['biographies']['table'] = nnels_content_cafe_overview_biography_form($nid, $isbns, $biographies, $suppliers);
    
  // Excerpts
  $form['tabs']['excerpts'] = array(
    '#type'   => 'fieldset',
    '#title'  => 'Excerpts',
    '#group'  => 'tabs',
    '#weight' => 1,
  );
  $form['tabs']['excerpts']['table'] = nnels_content_cafe_overview_excerpt_form($nid, $isbns, $excerpts);

  // Flaps
  $form['tabs']['flaps'] = array(
    '#type'   => 'fieldset',
    '#title'  => 'Flaps',
    '#group'  => 'tabs',
    '#weight' => 1,
  );
  $form['tabs']['flaps']['table'] = nnels_content_cafe_overview_flap_form($nid, $isbns, $flaps, $suppliers);
    
  // Jackets
  $form['tabs']['jackets'] = array(
    '#type'   => 'fieldset',
    '#title'  => 'Jackets',
    '#group'  => 'tabs',
    '#weight' => 1,
  );
  $form['tabs']['jackets']['table'] = nnels_content_cafe_overview_jacket_form($nid, $isbns, $jackets);

  // TOC's
  $form['tabs']['tocs'] = array(
    '#type'   => 'fieldset',
    '#title'  => 'TOC\'s',
    '#group'  => 'tabs',
    '#weight' => 1,
  );
  $form['tabs']['tocs']['table'] = nnels_content_cafe_overview_toc_form($nid, $isbns, $tocs);

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save data'),
  );

  return $form;
}

/**
 * Overview Form Submit.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return void
 */
function nnels_content_cafe_overview_form_submit($form, &$form_state) {
  $selected_annotation_id = $form_state['values']['tabs']['annotations']['table'];
  $selected_biography_id  = $form_state['values']['tabs']['biographies']['table'];
  $selected_excerpt_id    = $form_state['values']['tabs']['excerpts']['table'];
  $selected_flap_id       = $form_state['values']['tabs']['flaps']['table'];
  $selected_jacket_id     = $form_state['values']['tabs']['jackets']['table'];
  $selected_toc_id        = $form_state['values']['tabs']['tocs']['table'];

  $node = node_load($form_state['build_info']['args'][0]);
  drupal_set_title(t('Manage Content Cafe data for %node', array('%node' => $node->title)), PASS_THROUGH);

  // Load ISBN's associated with this node.
  $isbns       = field_get_items('node', $node,'field_isbn');
  $audio_isbns = field_get_items('node', $node,'field_isbn_audio');
  $valid_isbns = array();
  if ($isbns) {
    foreach ($isbns as $isbn) {
      if (nnels_content_cafe_validate_isbn($isbn['value'])) {
        $valid_isbns[$isbn['value']] = TRUE;
      }
    }
  }
  if ($audio_isbns) {
    foreach ($audio_isbns as $isbn) {
      if (nnels_content_cafe_validate_isbn($isbn['value'])) {
        $valid_isbns[$isbn['value']] = TRUE;
      }
    }
  }

  // Load all data for the node.
  $isbns        = nnels_content_cafe_select_multiple_content_cafe_isbn_rows(array_keys($valid_isbns));
  $isbn_ids     = array_keys($isbns);
  $supplier_ids = array();
  $annotations  = nnels_content_cafe_select_multiple_content_cafe_annotation_rows($isbn_ids, $supplier_ids);
  $biographies  = nnels_content_cafe_select_multiple_content_cafe_biography_rows($isbn_ids, $supplier_ids);
  $excerpts     = nnels_content_cafe_select_multiple_content_cafe_excerpt_rows($isbn_ids);
  $flaps        = nnels_content_cafe_select_multiple_content_cafe_flap_rows($isbn_ids, $supplier_ids);
  $jackets      = nnels_content_cafe_select_multiple_content_cafe_jacket_rows($isbn_ids);
  $tocs         = nnels_content_cafe_select_multiple_content_cafe_toc_rows($isbn_ids);
  $suppliers    = nnels_content_cafe_select_multiple_content_cafe_supplier_rows(array_keys($supplier_ids));

  // Update selected annotation.
  if ($annotations) {
    foreach ($annotations as $annotation_id => $annotation) {
      if ($annotation_id == $selected_annotation_id) {
        $annotation->selected = TRUE;
      }
      else {
        $annotation->selected = FALSE;
      }
      nnels_content_cafe_update_content_cafe_isbn_annotation_row($annotation_id, $annotation->selected);
    }
  }

  // Update selected biography.
  if ($biographies) {
    foreach ($biographies as $biography_id => $biography) {
      if ($biography_id == $selected_biography_id) {
        $biography->selected = TRUE;
      }
      else {
        $biography->selected = FALSE;
      }
      nnels_content_cafe_update_content_cafe_isbn_biography_row($biography_id, $biography->selected);
    }
  }

  // Update selected excerpt.
  if ($excerpts) {
    foreach ($excerpts as $excerpt_id => $excerpt) {
      if ($excerpt_id == $selected_excerpt_id) {
        $excerpt->selected = TRUE;
      }
      else {
        $excerpt->selected = FALSE;
      }
      nnels_content_cafe_update_content_cafe_isbn_excerpt_row($excerpt_id, $excerpt->selected);
    }
  }

  // Update selected flap.
  if ($flaps) {
    foreach ($flaps as $flap_id => $flap) {
      if ($flap_id == $selected_flap_id) {
        $flap->selected = TRUE;
      }
      else {
        $flap->selected = FALSE;
      }
      nnels_content_cafe_update_content_cafe_isbn_flap_row($flap_id, $flap->selected);
    }
  }

  // Update selected jacket.
  if ($jackets) {
    foreach ($jackets as $jacket_id => $jacket) {
      if ($jacket_id == $selected_jacket_id) {
        $jacket->selected = TRUE;
      }
      else {
        $jacket->selected = FALSE;
      }
      nnels_content_cafe_update_content_cafe_isbn_jacket_row($jacket_id, $jacket->selected);
    }
  }

  // Update selected toc.
  if ($tocs) {
    foreach ($tocs as $toc_id => $toc) {
      if ($toc_id == $selected_toc_id) {
        $toc->selected = TRUE;
      }
      else {
        $toc->selected = FALSE;
      }
      nnels_content_cafe_update_content_cafe_isbn_toc_row($toc_id, $toc->selected);
    }
  }

  drupal_set_message(t('Selected data saved successfully.'));
}

/**
 * Repository Item List.
 *
 * @return array
 */
function nnels_content_cafe_repository_item_list() {
  drupal_set_title('List of Repository Items with ISBN Numbers.');

  // Get all repository_item nodes with ISBN data. This needs to be paged
  // manually because of the multiple expensive joins that would be required
  // on the node_content_cafe table. Additional queries below will retrieve
  // that data and filter as required.
  $query = db_select('node', 'n');
  $query->join('node_content_cafe', 'c', 'c.nid = n.nid');
  $query->leftJoin('field_data_field_isbn', 'i', 'i.entity_id = n.nid');
  $query->leftJoin('field_data_field_isbn_audio', 'a', 'a.entity_id = n.nid');
  $query->fields('n', array('nid', 'title'));
  $query->condition('n.type', 'repository_item');
  $or = db_or();
  $or->isNotNull('i.field_isbn_value');
  $or->isNotNull('a.field_isbn_audio_value');
  $query->condition($or);
  $query->orderBy('n.title');
  $query->groupBy('n.nid');

  $result = $query->execute();

  // Get a list of nids.
  $nids = array();
  while ($row = $result->fetchObject()) {
    $nids[$row->nid] = $row->title;
  }

  // Get the content cafe data (ids only).
  $annotations = nnels_content_cafe_select_all_content_cafe_annotation_rows(TRUE);
  $biographies = nnels_content_cafe_select_all_content_cafe_biography_rows(TRUE);
  $excerpts    = nnels_content_cafe_select_all_content_cafe_excerpt_rows(TRUE);
  $flaps       = nnels_content_cafe_select_all_content_cafe_flap_rows(TRUE);
  $jackets     = nnels_content_cafe_select_all_content_cafe_jacket_rows(TRUE);
  $tocs        = nnels_content_cafe_select_all_content_cafe_toc_rows(TRUE);

  // Filter results.
  nnels_content_cafe_repository_item_list_filter_results('annotations', $nids, $annotations);
  nnels_content_cafe_repository_item_list_filter_results('biographies', $nids, $biographies);
  nnels_content_cafe_repository_item_list_filter_results('excerpts', $nids, $excerpts);
  nnels_content_cafe_repository_item_list_filter_results('flaps', $nids, $flaps);
  nnels_content_cafe_repository_item_list_filter_results('jackets', $nids, $jackets);
  nnels_content_cafe_repository_item_list_filter_results('tocs', $nids, $tocs);

  // Initialize the pager.
  $page  = pager_find_page();
  $limit = 50;
  $start = $page * $limit;
  pager_default_initialize(count($nids), $limit);

  // Extract the 50 records (max) for the table.
  $table_end   = $start + $limit;
  $array_index = 0;
  $rows        = array();
  foreach ($nids as $nid => $title) {
    if ($array_index >= $table_end) {
      break;
    }
    if ($array_index >= $start) {
      $row   = array();
      $row[] = l($title, 'node/' . $nid);
      $row[] = (isset($annotations[$nid]) ? '*' : '');
      $row[] = (isset($biographies[$nid]) ? '*' : '');
      $row[] = (isset($excerpts[$nid])    ? '*' : '');
      $row[] = (isset($flaps[$nid])       ? '*' : '');
      $row[] = (isset($jackets[$nid])     ? '*' : '');
      $row[] = (isset($tocs[$nid])        ? '*' : '');
      $row[] = l(
        t('Manage'),
        'node/' . $nid . '/content_cafe',
        array(
          'query' => array(
            'destination' => 'admin/config/nnels/repository_items',
          ),
        )
      );

      $rows[] = $row;
    }
    $array_index++;
  }

  $filter_form = drupal_get_form('nnels_content_cafe_repository_item_list_filter_form');

  $output  = drupal_render($filter_form);
  $output .= theme(
    'table',
    array(
      'header' => array(
        t('Title'),
        t('Annotation'),
        t('Bigraphy'),
        t('Excerpt'),
        t('Flap'),
        t('Jacket'),
        t('TOC'),
        t('Operations'),
      ),
      'rows'   => $rows,
      'empty'  => t('There are no repository items with attached content cafe data.'),
    )
  );
  $output .= theme('pager');

  return $output;
}

/**
 * Repository List Filter Form Filter Results.
 *
 * @param string $type
 * @param array $nids
 * @param array $data
 *
 * @return void
 */
function nnels_content_cafe_repository_item_list_filter_results($type, &$nids, $data) {
  if (isset($_SESSION['nnels_content_cafe'][$type])) {
    if ($_SESSION['nnels_content_cafe'][$type] > 0) {
      foreach ($nids as $nid => $title) {

        // With.
        if ($_SESSION['nnels_content_cafe'][$type] == 1) {
          if (!isset($data[$nid])) {
            unset($nids[$nid]);
          }
        }
        // Without.
        else {
          if (isset($data[$nid])) {
            unset($nids[$nid]);
          }
        }
      }
    }
  }
}

/**
 * Repository List Filter Form.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return array
 */
function nnels_content_cafe_repository_item_list_filter_form($form, &$form_state) {
  $form = array();

  $form['filter'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Filter'),
    '#collapsible'   => TRUE,
    '#collapsed'     => !isset($_SESSION['nnels_content_cafe']),
    '#tree'          => TRUE,
    '#attributes'    => array(
      'class' => array('container-inline'),
    ),
  );

  $form['filter']['annotations'] = array(
    '#type'          => 'select',
    '#title'         => t('With Annotations'),
    '#options'       => array(
      '0' => t('- Any -'),
      '1' => t('Yes'),
      '2' => t('No'),
    ),
    '#default_value' => (isset($_SESSION['nnels_content_cafe']['annotations']) ? $_SESSION['nnels_content_cafe']['annotations'] : 0),
  );

  $form['filter']['biographies'] = array(
    '#type'          => 'select',
    '#title'         => t('With Biographies'),
    '#options'       => array(
      '0' => t('- Any -'),
      '1' => t('Yes'),
      '2' => t('No'),
    ),
    '#default_value' => (isset($_SESSION['nnels_content_cafe']['biographies']) ? $_SESSION['nnels_content_cafe']['biographies'] : 0),
  );

  $form['filter']['excerpts'] = array(
    '#type'          => 'select',
    '#title'         => t('With Excerpts'),
    '#options'       => array(
      '0' => t('- Any -'),
      '1' => t('Yes'),
      '2' => t('No'),
    ),
    '#default_value' => (isset($_SESSION['nnels_content_cafe']['excerpts']) ? $_SESSION['nnels_content_cafe']['excerpts'] : 0),
  );

  $form['filter']['flaps'] = array(
    '#type'          => 'select',
    '#title'         => t('With Flaps'),
    '#options'       => array(
      '0' => t('- Any -'),
      '1' => t('Yes'),
      '2' => t('No'),
    ),
    '#default_value' => (isset($_SESSION['nnels_content_cafe']['flaps']) ? $_SESSION['nnels_content_cafe']['flaps'] : 0),
  );

  $form['filter']['jackets'] = array(
    '#type'          => 'select',
    '#title'         => t('With Jackets'),
    '#options'       => array(
      '0' => t('- Any -'),
      '1' => t('Yes'),
      '2' => t('No'),
    ),
    '#default_value' => (isset($_SESSION['nnels_content_cafe']['jackets']) ? $_SESSION['nnels_content_cafe']['jackets'] : 0),
  );

  $form['filter']['tocs'] = array(
    '#type'          => 'select',
    '#title'         => t('With TOCs'),
    '#options'       => array(
      '0' => t('- Any -'),
      '1' => t('Yes'),
      '2' => t('No'),
    ),
    '#default_value' => (isset($_SESSION['nnels_content_cafe']['tocs']) ? $_SESSION['nnels_content_cafe']['tocs'] : 0),
  );

  $form['filter']['submit'] = array(
    '#type'          => 'submit',
    '#value'         => t('Submit'),
    '#submit'        => array('nnels_content_cafe_repository_item_list_filter_form_button_submit'),
  );

  $form['filter']['reset'] = array(
    '#type'          => 'submit',
    '#value'         => t('Reset'),
    '#submit'        => array('nnels_content_cafe_repository_item_list_filter_form_button_reset'),
    '#access'        => isset($_SESSION['nnels_content_cafe']),
  );

  return $form;
}

/**
 * Repository List Filter Form Submit Button Submit.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return void
 */
function nnels_content_cafe_repository_item_list_filter_form_button_submit($form, &$form_state) {
  $_SESSION['nnels_content_cafe']['annotations'] = $form_state['values']['filter']['annotations'];
  $_SESSION['nnels_content_cafe']['biographies'] = $form_state['values']['filter']['biographies'];
  $_SESSION['nnels_content_cafe']['excerpts']    = $form_state['values']['filter']['excerpts'];
  $_SESSION['nnels_content_cafe']['flaps']       = $form_state['values']['filter']['flaps'];
  $_SESSION['nnels_content_cafe']['jackets']     = $form_state['values']['filter']['jackets'];
  $_SESSION['nnels_content_cafe']['tocs']        = $form_state['values']['filter']['tocs'];
}

/**
 * Repository List Filter Form Reset Button Submit.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return void
 */
function nnels_content_cafe_repository_item_list_filter_form_button_reset($form, &$form_state) {
  unset($_SESSION['nnels_content_cafe']);
}

/**
 * Repository Invalid ISBN List.
 *
 * @return array
 */
function nnels_content_cafe_repository_invalid_isbn_list() {
  drupal_set_title('List of Repository Items with Invalid ISBN Numbers.');

  // Get all repository_item nodes with ISBN data. This needs to be paged
  // manually because each record will need be validated.
  $query = db_select('node', 'n');
  $query->join('node_content_cafe', 'c', 'c.nid = n.nid');
  $query->leftJoin('field_data_field_isbn', 'i', 'i.entity_id = n.nid');
  $query->leftJoin('field_data_field_isbn_audio', 'a', 'a.entity_id = n.nid');
  $query->fields('n', array('nid', 'title'));
  $query->fields('i', array('field_isbn_value'));
  $query->fields('a', array('field_isbn_audio_value'));
  $query->condition('n.type', 'repository_item');
  $or = db_or();
  $or->isNotNull('i.field_isbn_value');
  $or->isNotNull('a.field_isbn_audio_value');
  $query->condition($or);
  $query->orderBy('n.title');
  $query->groupBy('n.nid');

  $result = $query->execute();

  // Get a list of nids.
  $nids = array();
  while ($row = $result->fetchObject()) {
    $isbn_valid       = (isset($row->field_isbn_value)       ? nnels_content_cafe_validate_isbn($row->field_isbn_value)       : TRUE);
    $isbn_audio_valid = (isset($row->field_isbn_audio_value) ? nnels_content_cafe_validate_isbn($row->field_isbn_audio_value) : TRUE);
    if (!$isbn_valid || !$isbn_audio_valid) {
      if ($isbn_valid) {
        $row->field_isbn_value = NULL;
      }
      if ($isbn_audio_valid) {
        $row->field_isbn_audio_value = NULL;
      }
      $nids[$row->nid] = $row;
    }
  }

  // Initialize the pager.
  $page  = pager_find_page();
  $limit = 50;
  $start = $page * $limit;
  pager_default_initialize(count($nids), $limit);

  // Extract the 50 records (max) for the table.
  $table_end   = $start + $limit;
  $array_index = 0;
  $rows        = array();
  foreach ($nids as $nid => $record) {
    if ($array_index >= $table_end) {
      break;
    }
    if ($array_index >= $start) {
      $row   = array();
      $row[] = l($record->title, 'node/' . $nid);
      $row[] = $record->field_isbn_value;
      $row[] = $record->field_isbn_audio_value;
      $row[] = l(
        t('Edit'),
        'node/' . $nid . '/edit',
        array(
          'query' => array(
            'destination' => 'admin/config/nnels/repository_items',
          ),
        )
      );

      $rows[] = $row;
    }
    $array_index++;
  }

  $output  = drupal_render($filter_form);
  $output .= theme(
    'table',
    array(
      'header' => array(
        t('Title'),
        t('Invalid ISBN'),
        t('Invalid Audio ISBN'),
        t('Operations'),
      ),
      'rows'   => $rows,
      'empty'  => t('There are no repository items with invalid ISBN numbers.'),
    )
  );
  $output .= theme('pager');

  return $output;
}

/**
 * Annotation Tableselect Form.
 *
 * @param int $nid
 * @param array $isbns
 * @param array $annotations
 * @param array $suppliers
 *
 * @return array
 */
function nnels_content_cafe_overview_annotation_form($nid, $isbns, $annotations, $suppliers) {
  $form = array(
    '#type'     => 'tableselect',
    '#header'   => array(
      'isbn'     => t('ISBN'),
      'supplier' => t('Supplier'),
      'edit'     => t('Operations'),
    ),
    '#options'  => array(),
    '#multiple' => FALSE,
    '#empty'    => t('There are no annotations for this repository item.'),
  );

  $selected = NULL;
  if ($annotations) {
    foreach ($annotations as $annotation_id => $annotation) {
      $form['#options'][$annotation_id] = array(
        'isbn'     => $isbns[$annotation->isbn_id],
        'supplier' => $suppliers[$annotation->supplier_id]->supplier_name,
        'edit'     => l('Edit/View', 'node/' . $nid . '/content_cafe/annotation/' . $annotation->external_id . '/edit'),
      );

      if ($annotation->selected) {
        $selected = $annotation_id;
      }
    }
  }

  $form['#default_value'] = $selected;

  return $form;
}

/**
 * Biography Tableselect Form.
 *
 * @param int $nid
 * @param array $isbns
 * @param array $biographies
 * @param array $suppliers
 *
 * @return array
 */
function nnels_content_cafe_overview_biography_form($nid, $isbns, $biographies, $suppliers) {
  $form = array(
    '#type'     => 'tableselect',
    '#header'   => array(
      'isbn'     => t('ISBN'),
      'supplier' => t('Supplier'),
      'edit'     => t('Operations'),
    ),
    '#options'  => array(),
    '#multiple' => FALSE,
    '#empty'    => t('There are no biographies for this repository item.'),
  );

  $selected = NULL;
  if ($biographies) {
    foreach ($biographies as $biography_id => $biography) {
      $form['#options'][$biography_id] = array(
        'isbn'     => $isbns[$biography->isbn_id],
        'supplier' => $suppliers[$biography->supplier_id]->supplier_name,
        'edit'     => l('Edit/View', 'node/' . $nid . '/content_cafe/biography/' . $biography->external_id . '/edit'),
      );

      if ($biography->selected) {
        $selected = $biography_id;
      }
    }
  }

  $form['#default_value'] = $selected;

  return $form;
}

/**
 * Excerpt Tableselect Form.
 *
 * @param int $nid
 * @param array $isbns
 * @param array $excerpts
 *
 * @return array
 */
function nnels_content_cafe_overview_excerpt_form($nid, $isbns, $excerpts) {
  $form = array(
    '#type'     => 'tableselect',
    '#header'   => array(
      'isbn'     => t('ISBN'),
      'edit'     => t('Operations'),
    ),
    '#options'  => array(),
    '#multiple' => FALSE,
    '#empty'    => t('There are no excerpts for this repository item.'),
  );

  $selected = NULL;
  if ($excerpts) {
    foreach ($excerpts as $excerpt_id => $excerpt) {
      $form['#options'][$excerpt_id] = array(
        'isbn'     => $isbns[$excerpt->isbn_id],
        'edit'     => l('Edit/View', 'node/' . $nid . '/content_cafe/excerpt/' . $excerpt->external_id . '/edit'),
      );

      if ($excerpt->selected) {
        $selected = $excerpt_id;
      }
    }
  }

  $form['#default_value'] = $selected;

  return $form;
}

/**
 * Flap Tableselect Form.
 *
 * @param int $nid
 * @param array $isbns
 * @param array $flaps
 * @param array $suppliers
 *
 * @return array
 */
function nnels_content_cafe_overview_flap_form($nid, $isbns, $flaps, $suppliers) {
  $form = array(
    '#type'     => 'tableselect',
    '#header'   => array(
      'isbn'     => t('ISBN'),
      'supplier' => t('Supplier'),
      'edit'     => t('Operations'),
    ),
    '#options'  => array(),
    '#multiple' => FALSE,
    '#empty'    => t('There are no flaps for this repository item.'),
  );

  $selected = NULL;
  if ($flaps) {
    foreach ($flaps as $flap_id => $flap) {
      $form['#options'][$flap_id] = array(
        'isbn'     => $isbns[$flap->isbn_id],
        'supplier' => $suppliers[$flap->supplier_id]->supplier_name,
        'edit'     => l('Edit/View', 'node/' . $nid . '/content_cafe/flap/' . $flap->external_id . '/edit'),
      );

      if ($flap->selected) {
        $selected = $flap_id;
      }
    }
  }

  $form['#default_value'] = $selected;

  return $form;
}

/**
 * Jacket Tableselect Form.
 *
 * @param int $nid
 * @param array $isbns
 * @param array $jackets
 *
 * @return array
 */
function nnels_content_cafe_overview_jacket_form($nid, $isbns, $jackets) {
  $form = array(
    '#type'     => 'tableselect',
    '#header'   => array(
      'isbn'     => t('ISBN'),
      'edit'     => t('Operations'),
    ),
    '#options'  => array(),
    '#multiple' => FALSE,
    '#empty'    => t('There are no jackets for this repository item.'),
  );

  $selected = NULL;
  if ($jackets) {
    foreach ($jackets as $jacket_id => $jacket) {
      $form['#options'][$jacket_id] = array(
        'isbn'     => $isbns[$jacket->isbn_id],
        'supplier' => $suppliers[$jacket->supplier_id]->supplier_name,
        'edit'     => l('Edit/View', 'node/' . $nid . '/content_cafe/jacket/' . $jacket->external_id . '/edit'),
      );

      if ($jacket->selected) {
        $selected = $jacket_id;
      }
    }
  }

  $form['#default_value'] = $selected;

  return $form;
}

/**
 * TOC Tableselect Form.
 *
 * @param int $nid
 * @param array $isbns
 * @param array $tocs
 *
 * @return array
 */
function nnels_content_cafe_overview_toc_form($nid, $isbns, $tocs) {
  $form = array(
    '#type'     => 'tableselect',
    '#header'   => array(
      'isbn'     => t('ISBN'),
      'edit'     => t('Operations'),
    ),
    '#options'  => array(),
    '#multiple' => FALSE,
    '#empty'    => t('There are no tocs for this repository item.'),
  );

  $selected = NULL;
  if ($tocs) {
    foreach ($tocs as $toc_id => $toc) {
      $form['#options'][$toc_id] = array(
        'isbn'     => $isbns[$toc->isbn_id],
        'edit'     => l('Edit/View', 'node/' . $nid . '/content_cafe/toc/' . $toc->external_id . '/edit'),
      );

      if ($toc->selected) {
        $selected = $toc_id;
      }
    }
  }

  $form['#default_value'] = $selected;

  return $form;
}

/**
 * Annotation Edit Form.
 *
 * @param array $form
 * @param array $form_state
 * @param int $nid
 * @param int $external_id
 *
 * @return array
 */
function nnels_content_cafe_annotation_edit_form($form, &$form_state, $nid, $external_id) {
  $node       = node_load($nid);
  $annotation = nnels_content_cafe_select_content_cafe_annotation_row($external_id);
  drupal_set_title(t('Edit annotation %id for %node.', array('%id' => $external_id, '%node' => $node->title)), PASS_THROUGH);

  $form = array();

  $form['annotation'] = array(
    '#type'          => 'text_format',
    '#title'         => t('Annotation'),
    '#default_value' => $annotation->annotation,
    '#required'      => TRUE,
  );

  $form['actions'] = array(
    '#type'          => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type'          => 'submit',
    '#value'         => t('Save changes'),
    '#suffix'        => l(t('Cancel'), 'node/' . $nid . '/content_cafe'),
  );

  return $form;
}

/**
 * Annotation Edit Form Submit.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return void
 */
function nnels_content_cafe_annotation_edit_form_submit($form, &$form_state) {
  $nid         = $form_state['build_info']['args'][0];
  $external_id = $form_state['build_info']['args'][1];
  $annotation  = $form_state['values']['annotation']['value'];
  nnels_content_cafe_update_content_cafe_annotation_row($external_id, $annotation);

  drupal_set_message(t('Annotation has been updated.'));
  $form_state['redirect'] = 'node/' . $nid . '/content_cafe';
}

/**
 * Biography Edit Form.
 *
 * @param array $form
 * @param array $form_state
 * @param int $nid
 * @param int $external_id
 *
 * @return array
 */
function nnels_content_cafe_biography_edit_form($form, &$form_state, $nid, $external_id) {
  $node      = node_load($nid);
  $biography = nnels_content_cafe_select_content_cafe_biography_row($external_id);
  drupal_set_title(t('Edit biography %id for %node.', array('%id' => $external_id, '%node' => $node->title)), PASS_THROUGH);

  $form = array();

  $form['biography'] = array(
    '#type'          => 'text_format',
    '#title'         => t('Biography'),
    '#default_value' => $biography->biography,
    '#required'      => TRUE,
  );

  $form['actions'] = array(
    '#type'          => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type'          => 'submit',
    '#value'         => t('Save changes'),
    '#suffix'        => l(t('Cancel'), 'node/' . $nid . '/content_cafe'),
  );

  return $form;
}

/**
 * Biography Edit Form Submit.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return void
 */
function nnels_content_cafe_biography_edit_form_submit($form, &$form_state) {
  $nid         = $form_state['build_info']['args'][0];
  $external_id = $form_state['build_info']['args'][1];
  $biography   = $form_state['values']['biography']['value'];
  nnels_content_cafe_update_content_cafe_biography_row($external_id, $biography);

  drupal_set_message(t('Biography has been updated.'));
  $form_state['redirect'] = 'node/' . $nid . '/content_cafe';
}

/**
 * Excerpt Edit Form.
 *
 * @param array $form
 * @param array $form_state
 * @param int $nid
 * @param int $external_id
 *
 * @return array
 */
function nnels_content_cafe_excerpt_edit_form($form, &$form_state, $nid, $external_id) {
  $node    = node_load($nid);
  $excerpt = nnels_content_cafe_select_content_cafe_excerpt_row($external_id);
  drupal_set_title(t('Edit excerpt %id for %node.', array('%id' => $external_id, '%node' => $node->title)), PASS_THROUGH);

  $form = array();

  $form['excerpt'] = array(
    '#type'          => 'text_format',
    '#title'         => t('Excerpt'),
    '#default_value' => $excerpt->excerpt,
    '#required'      => TRUE,
  );

  $form['actions'] = array(
    '#type'          => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type'          => 'submit',
    '#value'         => t('Save changes'),
    '#suffix'        => l(t('Cancel'), 'node/' . $nid . '/content_cafe'),
  );

  return $form;
}

/**
 * Excerpt Edit Form Submit.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return void
 */
function nnels_content_cafe_excerpt_edit_form_submit($form, &$form_state) {
  $nid         = $form_state['build_info']['args'][0];
  $external_id = $form_state['build_info']['args'][1];
  $excerpt     = $form_state['values']['excerpt']['value'];
  nnels_content_cafe_update_content_cafe_excerpt_row($external_id, $excerpt);

  drupal_set_message(t('Excerpt has been updated.'));
  $form_state['redirect'] = 'node/' . $nid . '/content_cafe';
}

/**
 * Flap Edit Form.
 *
 * @param array $form
 * @param array $form_state
 * @param int $nid
 * @param int $external_id
 *
 * @return array
 */
function nnels_content_cafe_flap_edit_form($form, &$form_state, $nid, $external_id) {
  $node = node_load($nid);
  $flap = nnels_content_cafe_select_content_cafe_flap_row($external_id);
  drupal_set_title(t('Edit flap %id for %node.', array('%id' => $external_id, '%node' => $node->title)), PASS_THROUGH);

  $form = array();

  $form['flap'] = array(
    '#type'          => 'text_format',
    '#title'         => t('Flap'),
    '#default_value' => $flap->flap,
    '#required'      => TRUE,
  );

  $form['actions'] = array(
    '#type'          => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type'          => 'submit',
    '#value'         => t('Save changes'),
    '#suffix'        => l(t('Cancel'), 'node/' . $nid . '/content_cafe'),
  );

  return $form;
}

/**
 * Flap Edit Form Submit.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return void
 */
function nnels_content_cafe_flap_edit_form_submit($form, &$form_state) {
  $nid         = $form_state['build_info']['args'][0];
  $external_id = $form_state['build_info']['args'][1];
  $flap        = $form_state['values']['flap']['value'];
  nnels_content_cafe_update_content_cafe_flap_row($external_id, $flap);

  drupal_set_message(t('Flap has been updated.'));
  $form_state['redirect'] = 'node/' . $nid . '/content_cafe';
}

/**
 * Jacket Edit Form.
 *
 * @param array $form
 * @param array $form_state
 * @param int $nid
 * @param int $external_id
 *
 * @return array
 */
function nnels_content_cafe_jacket_edit_form($form, &$form_state, $nid, $external_id) {
  $node   = node_load($nid);
  $jacket = nnels_content_cafe_select_content_cafe_jacket_row($external_id);
  drupal_set_title(t('Edit jacket %id for %node.', array('%id' => $external_id, '%node' => $node->title)), PASS_THROUGH);

  $form = array();
  //Check for bucket set (AmazonS3 module in-use)
  $bucket = variable_get("amazons3_bucket");
  $form['jacket'] = array(
    '#type'            => 'managed_file',
    '#title'           => t('Jacket'),
    '#default_value'   => $jacket->fid,
    '#required'        => TRUE,
    //Use the bucket in upload location
    '#upload_location' => 's3://' . $bucket . '/book-covers',
  );

  $form['actions'] = array(
    '#type'          => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type'          => 'submit',
    '#value'         => t('Save changes'),
    '#suffix'        => l(t('Cancel'), 'node/' . $nid . '/content_cafe'),
  );

  return $form;
}

/**
 * Jacket Edit Form Submit.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return void
 */
function nnels_content_cafe_jacket_edit_form_submit($form, &$form_state) {
  $nid         = $form_state['build_info']['args'][0];
  $external_id = $form_state['build_info']['args'][1];
  $fid         = $form_state['values']['jacket'];

  // Make sure a file was updated before processing.
  $jacket = nnels_content_cafe_select_content_cafe_jacket_row($external_id);
  if (!$jacket || ($jacket && $jacket->fid != $fid)) {

    // Remove old file.
    if ($jacket) {
      $jacket_old = file_load($jacket->fid);
      if ($jacket_old) {
        file_delete($jacket_old);
      }
    }

    // Make new file permenant.
    $jacket_new = file_load($fid);
    if ($jacket_new) {
      $jacket_new->status = FILE_STATUS_PERMENANT;
      file_save($jacket_new);
    }

    // Update the fid.
    nnels_content_cafe_update_content_cafe_jacket_row($external_id, $fid);
    drupal_set_message(t('Jacket has been updated.'));
  }

  $form_state['redirect'] = 'node/' . $nid . '/content_cafe';
}

/**
 * TOC Edit Form.
 *
 * @param array $form
 * @param array $form_state
 * @param int $nid
 * @param int $external_id
 *
 * @return array
 */
function nnels_content_cafe_toc_edit_form($form, &$form_state, $nid, $external_id) {
  $node = node_load($nid);
  $toc  = nnels_content_cafe_select_content_cafe_toc_row($external_id);
  drupal_set_title(t('Edit toc %id for %node.', array('%id' => $external_id, '%node' => $node->title)), PASS_THROUGH);

  $form = array();

  $form['toc'] = array(
    '#type'          => 'text_format',
    '#title'         => t('TOC'),
    '#default_value' => $toc->toc,
    '#required'      => TRUE,
  );

  $form['actions'] = array(
    '#type'          => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type'          => 'submit',
    '#value'         => t('Save changes'),
    '#suffix'        => l(t('Cancel'), 'node/' . $nid . '/content_cafe'),
  );

  return $form;
}

/**
 * TOC Edit Form Submit.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return void
 */
function nnels_content_cafe_toc_edit_form_submit($form, &$form_state) {
  $nid         = $form_state['build_info']['args'][0];
  $external_id = $form_state['build_info']['args'][1];
  $toc         = $form_state['values']['toc']['value'];
  nnels_content_cafe_update_content_cafe_toc_row($external_id, $toc);

  drupal_set_message(t('TOC has been updated.'));
  $form_state['redirect'] = 'node/' . $nid . '/content_cafe';
}
