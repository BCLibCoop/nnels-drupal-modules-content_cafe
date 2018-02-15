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
