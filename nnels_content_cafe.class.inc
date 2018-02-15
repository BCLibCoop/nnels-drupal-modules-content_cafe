<?php

/**
 * NNELS Content Cafe API Class.
 */
class NNELSContentCafe {

  /**
   * @var string SIZE_SMALL constant.
   */
  const SIZE_SMALL  = 'S';

  /**
   * @var string SIZE_MEDIUM constant.
   */
  const SIZE_MEDIUM = 'M';

  /**
   * @var string SIZE_LARGE constant.
   */
  const SIZE_LARGE  = 'L';

  /**
   * @var string $api_url.
   */
  private $api_url;

  /**
   * @var string $api_username.
   */
  private $api_username;

  /**
   * @var string $api_password.
   */
  private $api_password;

  /**
   * @var bool $api_ready.
   */
  private $api_ready = FALSE;

  /**
   * @var resource $curl.
   */
  private $curl;

  /**
   * @var string $isbn.
   */
  private $isbn;

  /**
   * @var array $content.
   */
  private $content = array(
    'AvailableContent'     => FALSE,
    'AnnotationBrief'      => FALSE,
    'AnnotationDetail'     => FALSE,
    'BiographyBrief'       => FALSE,
    'BiographyDetail'      => FALSE,
    'DemandHistoryBrief'   => FALSE,
    'DemandHistoryDetail'  => FALSE,
    'DemandBrief'          => FALSE,
    'DemandDetail'         => FALSE,
    'ExcerptBrief'         => FALSE,
    'ExcerptDetail'        => FALSE,
    'FlapBrief'            => FALSE,
    'FlapDetail'           => FALSE,
    'InventoryBrief'       => FALSE,
    'InventoryDetail'      => FALSE,
    'JacketBrief'          => FALSE, // TRUE will equal a size
    'JacketDetail'         => FALSE, // TRUE will equal a size
    'MuzeVideoRelease'     => FALSE,
    'MuzeSimilarCinema'    => FALSE,
    'MuzePopularMusic'     => FALSE,
    'MuzeClassicalMusic'   => FALSE,
    'MuzeEssentialArtists' => FALSE,
    'ProductBrief'         => FALSE,
    'ProductDetail'        => FALSE,
    'ReviewBrief'          => FALSE,
    'ReviewDetail'         => FALSE,
    'TocBrief'             => FALSE,
    'TocDetail'            => FALSE,
  );

  /**
   * Constructor
   *
   * @param string $isbn
   *
   * @return object
   */
  public function __construct($isbn) {
    $this->isbn         = $isbn;
    $this->api_url      = variable_get('nnels_content_cafe_api_url', FALSE);
    $this->api_username = variable_get('nnels_content_cafe_api_username', FALSE);
    $this->api_password = variable_get('nnels_content_cafe_api_password', FALSE);
    if ($this->api_url && $this->api_username && $this->api_password) {
      $this->api_ready = TRUE;
      $this->curl_init();
    }
    else {
      if (!$this->api_url) {
        drupal_set_message(t('The API URL has not been set.'));
      }
      if (!$this->api_username) {
        drupal_set_message(t('The API Username has not been set.'));
      }
      if (!$this->api_password) {
        drupal_set_message(t('The API Password has not been set.'));
      }
    }
  }

  /**
   * Destructor
   *
   * @return void
   */
  public function __destruct() {
    if ($this->api_ready) {
      curl_close($this->curl);
    }
  }

  /**
   * Add Available Content to the API call.
   *
   * @return void
   */
  public function AddAvailableContent() {
    $this->content['AvailableContent'] = TRUE;
  }

  /**
   * Add Annotation Brief to the API call.
   *
   * @return void
   */
  public function AddAnnotationBrief() {
    $this->content['AnnotationBrief'] = TRUE;
  }

  /**
   * Add Annotation Detail to the API call.
   *
   * @return void
   */
  public function AddAnnotationDetail() {
    $this->content['AnnotationDetail'] = TRUE;
  }

  /**
   * Add Biography Brief to the API call.
   *
   * @return void
   */
  public function AddBiographyBrief() {
    $this->content['BiographyBrief'] = TRUE;
  }

  /**
   * Add Biography Detail to the API call.
   *
   * @return void
   */
  public function AddBiographyDetail() {
    $this->content['BiographyDetail'] = TRUE;
  }

  /**
   * Add Demand History Brief to the API call.
   *
   * @return void
   */
  public function AddDemandHistoryBrief() {
    $this->content['DemandHistoryBrief'] = TRUE;
  }

  /**
   * Add Demand History Detail to the API call.
   *
   * @return void
   */
  public function AddDemandHistoryDetail() {
    $this->content['DemandHistoryDetail'] = TRUE;
  }

  /**
   * Add Demand Brief to the API call.
   *
   * @return void
   */
  public function AddDemandBrief() {
    $this->content['DemandBrief'] = TRUE;
  }

  /**
   * Add Demand Detail to the API call.
   *
   * @return void
   */
  public function AddDemandDetail() {
    $this->content['DemandDetail'] = TRUE;
  }

  /**
   * Add Excerpt Brief to the API call.
   *
   * @return void
   */
  public function AddExcerptBrief() {
    $this->content['ExcerptBrief'] = TRUE;
  }

  /**
   * Add Excerpt Detail to the API call.
   *
   * @return void
   */
  public function AddExcerptDetail() {
    $this->content['ExcerptDetail'] = TRUE;
  }

  /**
   * Add Flap Brief to the API call.
   *
   * @return void
   */
  public function AddFlapBrief() {
    $this->content['FlapBrief'] = TRUE;
  }

  /**
   * Add Flap Detail to the API call.
   *
   * @return void
   */
  public function AddFlapDetail() {
    $this->content['FlapDetail'] = TRUE;
  }

  /**
   * Add Inventory Brief to the API call.
   *
   * @return void
   */
  public function AddInventoryBrief() {
    $this->content['InventoryBrief'] = TRUE;
  }

  /**
   * Add Inventory Detail to the API call.
   *
   * @return void
   */
  public function AddInventoryDetail() {
    $this->content['InventoryDetail'] = TRUE;
  }

  /**
   * Add Jacket Brief to the API call.
   *
   * @return void
   */
  public function AddJacketBrief($size) {
    $this->content['JacketBrief'] = $this->validate_size($size);
  }

  /**
   * Add Jacket Detail to the API call.
   *
   * @return void
   */
  public function AddJacketDetail($size) {
    $this->content['JacketDetail'] = $this->validate_size($size);
  }

  /**
   * Add Muze Video Release to the API call.
   *
   * @return void
   */
  public function AddMuzeVideoRelease() {
    $this->content['MuzeVideoRelease'] = TRUE;
  }

  /**
   * Add Muze Similar Cinema to the API call.
   *
   * @return void
   */
  public function AddMuzeSimilarCinema() {
    $this->content['MuzeSimilarCinema'] = TRUE;
  }

  /**
   * Add Muze Popular Music to the API call.
   *
   * @return void
   */
  public function AddMuzePopularMusic() {
    $this->content['MuzePopularMusic'] = TRUE;
  }

  /**
   * Add Muze Classical Music to the API call.
   *
   * @return void
   */
  public function AddMuzeClassicalMusic() {
    $this->content['MuzeClassicalMusic'] = TRUE;
  }

  /**
   * Add Muze Essential Artists to the API call.
   *
   * @return void
   */
  public function AddMuzeEssentialArtists() {
    $this->content['MuzeEssentialArtists'] = TRUE;
  }

  /**
   * Add Product Brief to the API call.
   *
   * @return void
   */
  public function AddProductBrief() {
    $this->content['ProductBrief'] = TRUE;
  }

  /**
   * Add Product Detail to the API call.
   *
   * @return void
   */
  public function AddProductDetail() {
    $this->content['ProductDetail'] = TRUE;
  }

  /**
   * Add Review Brief to the API call.
   *
   * @return void
   */
  public function AddReviewBrief() {
    $this->content['ReviewBrief'] = TRUE;
  }

  /**
   * Add Review Detail to the API call.
   *
   * @return void
   */
  public function AddReviewDetail() {
    $this->content['ReviewDetail'] = TRUE;
  }

  /**
   * Add TOC Brief to the API call.
   *
   * @return void
   */
  public function AddTOCBrief() {
    $this->content['TocBrief'] = TRUE;
  }

  /**
   * Add TOC Detail to the API call.
   *
   * @return void
   */
  public function AddTOCDetail() {
    $this->content['TocDetail'] = TRUE;
  }

  /**
   * XML Request
   *
   * @return string
   */
  public function Request() {
    $xml  = '<?xml version="1.0" encoding="utf-8"?>';
    $xml .= '<soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://www.w3.org/2003/05/soap-envelope">';
    $xml .= '<soap:Body>';
    $xml .= '<XmlClass xmlns="http://ContentCafe2.btol.com">';
    $xml .= '<ContentCafe DateTime="2018-01-23T09:00:00">';
    $xml .= '<RequestItems UserID="' . $this->api_username . '" Password="' . $this->api_password . '">';
    $xml .= '<RequestItem>';
    $xml .= '<Key Type="ISBN">' . $this->isbn . '</Key>';
    foreach ($this->content as $request => $status) {
      if ($status) {
        $xml .= '<Content';
        if (gettype($status) != 'boolean') {
          $xml .= ' Type="' . $status . '"';
          if ($request == 'JacketDetail') {
            $xml .= ' Encoding="URL"';
          }
        }
        $xml .= '>' . $request . '</Content>';
      }
    }
    $xml .= '</RequestItem>';
    $xml .= '</RequestItems>';
    $xml .= '</ContentCafe>';
    $xml .= '</XmlClass>';
    $xml .= '</soap:Body>';
    $xml .= '</soap:Envelope>';

    return $xml;
  }

  /**
   * Execute API Call.
   *
   * @return mixed
   */
  public function Execute() {
    $response = FALSE;

    if ($this->api_ready) {
      curl_setopt($this->curl, CURLOPT_POSTFIELDS, $this->Request());
      $response = curl_exec($this->curl);

      if ($response === FALSE) {
        drupal_set_message(t('API Error: @errno - @errmsg', array('@errno' => curl_errno($this->curl), '@errmsg' => curl_error($this->curl))));
      }
    }

    $this->reset_request();

    return $response;
  }

  /**
   * Validate the size parameter is one of the allowed values.
   *
   * @param string $size
   *
   * @return mixed
   */
  private function validate_size($size) {
    $valid_size = FALSE;

    switch($size) {
      case self::SIZE_SMALL:
      case self::SIZE_MEDIUM:
      case self::SIZE_LARGE:
        $valid_size = $size;
        break;
      default:
        drupal_set_message(t('The size parameter passed in does not match any of the expected values. "%size" was passed in, expected values are S, M, L.', array('%size' => $size)));
        break;
    }

    return $valid_size;
  }

  /**
   * Initialize the CURL resource.
   *
   * @return void
   */
  private function curl_init() {
    $this->curl = curl_init();

    curl_setopt($this->curl, CURLOPT_URL,            $this->api_url);
    curl_setopt($this->curl, CURLOPT_POST,           TRUE);
    curl_setopt($this->curl, CURLOPT_HTTPHEADER,     array('Content-Type: application/soap+xml'));
    curl_setopt($this->curl, CURLOPT_RETURNTRANSFER, TRUE);
  }

  /**
   * reset the request.
   *
   * @return void
   */
  private function reset_request() {
    foreach ($this->content as $request => $status) {
      $this->content[$request] = FALSE;
    }
  }
}