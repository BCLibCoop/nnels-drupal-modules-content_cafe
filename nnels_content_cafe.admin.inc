<?php

/**
 * Settings Form.
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

  // Load all data for the 
  $isbns        = nnels_content_cafe_select_multiple_content_cafe_isbn_rows(array_keys($valid_isbns));
  $isbn_ids     = array_keys($isbns);
  $supplier_ids = array();
  $annotations = nnels_content_cafe_select_multiple_content_cafe_annotation_rows($isbn_ids, $supplier_ids);
  $biographies = nnels_content_cafe_select_multiple_content_cafe_biography_rows($isbn_ids, $supplier_ids);
  $excerpts    = nnels_content_cafe_select_multiple_content_cafe_excerpt_rows($isbn_ids);
  $flaps       = nnels_content_cafe_select_multiple_content_cafe_flap_rows($isbn_ids, $supplier_ids);
  // $jackets     = nnels_content_cafe_select_multiple_content_cafe_jacket_rows($isbn_ids, $supplier_ids);
  $tocs        = nnels_content_cafe_select_multiple_content_cafe_toc_rows($isbn_ids);
  $suppliers   = nnels_content_cafe_select_multiple_content_cafe_supplier_rows(array_keys($supplier_ids));

  $form['tabs'] = array(
    '#type' => 'vertical_tabs',
    '#tree' => TRUE,
  );

  // Annotations
  $form['tabs']['annotations'] = array(
    '#type' => 'fieldset',
    '#title' => 'Annotations',
    '#group' => 'tabs',
    '#weight' => 0,
  );
  $form['tabs']['annotations']['test_field'] = array(
    '#type' => 'textarea',
    '#title' => 'Test',
  );

  // Biographies
  $form['tabs']['biographies'] = array(
    '#type' => 'fieldset',
    '#title' => 'Biographies',
    '#group' => 'tabs',
    '#weight' => 1,
  );
  $form['tabs']['biographies']['test_field'] = array(
    '#type' => 'textarea',
    '#title' => 'Test',
  );
    
  // Excerpts
  $form['tabs']['excerpts'] = array(
    '#type' => 'fieldset',
    '#title' => 'Excerpts',
    '#group' => 'tabs',
    '#weight' => 1,
  );
  $form['tabs']['excerpts']['test_field'] = array(
    '#type' => 'textarea',
    '#title' => 'Test',
  );

  // Flaps
  $form['tabs']['flaps'] = array(
    '#type' => 'fieldset',
    '#title' => 'Flaps',
    '#group' => 'tabs',
    '#weight' => 1,
  );
  $form['tabs']['flaps']['test_field'] = array(
    '#type' => 'textarea',
    '#title' => 'Test',
  );
    
  // Jackets
  $form['tabs']['jackets'] = array(
    '#type' => 'fieldset',
    '#title' => 'Jackets',
    '#group' => 'tabs',
    '#weight' => 1,
  );
  $form['tabs']['jackets']['test_field'] = array(
    '#type' => 'textarea',
    '#title' => 'Test',
  );

  // TOC's
  $form['tabs']['tocs'] = array(
    '#type' => 'fieldset',
    '#title' => 'TOC\'s',
    '#group' => 'tabs',
    '#weight' => 1,
  );
  $form['tabs']['tocs']['test_field'] = array(
    '#type' => 'textarea',
    '#title' => 'Test',
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save data'),
  );

  return $form;
}

function nnels_content_cafe_refresh($nid) {
  return array();
}

function nnels_content_cafe_annotation_edit_form($form, &$form_state, $nid, $annotation_id) {
  return array();
}

function nnels_content_cafe_biography_edit_form($form, &$form_state, $nid, $biography_id) {
  return array();
}

function nnels_content_cafe_excerpt_edit_form($form, &$form_state, $nid, $excerpt_id) {
  return array();
}

function nnels_content_cafe_flap_edit_form($form, &$form_state, $nid, $flap_id) {
  return array();
}

function nnels_content_cafe_jacket_edit_form($form, &$form_state, $nid, $jacket_id) {
  return array();
}

function nnels_content_cafe_toc_edit_form($form, &$form_state, $nid, $toc_id) {
  return array();
}