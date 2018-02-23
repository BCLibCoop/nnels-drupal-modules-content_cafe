<?php

/**
 * Implements hook_drush_command().
 */
function nnels_content_cafe_drush_command() {
  $commands = array();

  $commands['update-content-cafe'] = array(
    'description' => 'Update repository items with content cafe data (50 per run).',
  );

  $commands['update-content-cafe-all'] = array(
    'description' => 'Update repository items with content cafe data (all in one run).',
  );

  return $commands;
}

/**
 * Drush command logic.
 * drush_[COMMAND_NAME]().
 */
function drush_nnels_content_cafe_update_content_cafe() {

  // Since the image URL's are dynamic there is no indication what extension
  // they should have. Mime type is available in the response headers but 
  // drush does not define file_mimetype_mapping() during bootstrap (as it
  // should), so this file needs to be included.
  require_once DRUPAL_ROOT . '/includes/file.mimetypes.inc';

  nnels_content_cafe_update_content_cafe(TRUE);
}

/**
 * Drush command logic.
 * drush_[COMMAND_NAME]().
 */
function drush_nnels_content_cafe_update_content_cafe_all() {

  // Since the image URL's are dynamic there is no indication what extension
  // they should have. Mime type is available in the response headers but 
  // drush does not define file_mimetype_mapping() during bootstrap (as it
  // should), so this file needs to be included.
  require_once DRUPAL_ROOT . '/includes/file.mimetypes.inc';

  nnels_content_cafe_update_content_cafe();
}

/**
 * Update Content Cafe
 *
 * This is the main function called by both Drush functions.
 *
 * @param bool $limit
 *
 * @return void
 */
function nnels_content_cafe_update_content_cafe($limit = FALSE) {
  $existing = nnels_content_cafe_load_content_cafe_data();
  $results  = nnels_content_cafe_load_isbn_data();

  // Build a list of ISBN's per node array which will be used to fetch data
  // from the API. Validate the ISBN data at this point.
  $isbns = array();
  while ($row = $results->fetchObject()) {
    nnels_content_cafe_check_isbn($row->nid, $row->field_isbn_value, $isbns, $existing);
    nnels_content_cafe_check_isbn($row->nid, $row->field_isbn_audio_value, $isbns, $existing);
  }
  nnels_content_cafe_check_changed($isbns, $existing);

  // Fetch the data from the API.
  $calls = 0;
  foreach ($isbns as $nid => $nid_isbns) {
    foreach (array_keys($nid_isbns) as $isbn) {
      drush_print('Fetching data for ISBN Number: ' . $isbn);

      // If there is already ISBN data in the tables, associate this ISBN with
      // the node. If there is no data, fetch the data and store it all.
      $record = nnels_content_cafe_select_content_cafe_isbn_row($isbn);
      if ($record) {
        $isbn_id = $record->isbn_id;
      }
      else {
      
        // Retrieve data from the API.
        $data = nnels_content_cafe_retrieve_data($isbn);

        // Insert the data into the database.
        $isbn_id = nnels_content_cafe_process_data($nid, $isbn, $data, $existing);

        // Don't hammer the API.
        sleep(2);
        $calls++;
      }

      nnels_content_cafe_conditionally_insert_node_content_cafe_row($nid, $isbn_id);

      // Handling the limit in this way rather than with a database query because
      // of the dirty data which will polute the query results over time. This
      // method guarantees 50 API calls per run.
      if ($limit && $calls >= 50) {
        break 2;
      }
    }
  }
}

/**
 * Check ISBN
 *
 * Determine if the ISBN value should be added the queue. Validation and
 * duplication checking is done as well.
 *
 * @param int $nid
 * @param int $isbn
 * @param array $isbns
 * @param array $existing
 *
 * @return void
 */
function nnels_content_cafe_check_isbn($nid, $isbn, &$isbns, $existing) {
  if (!empty($isbn)) {

    // Validate the ISBN number.
    if (nnels_content_cafe_validate_isbn($isbn)) {

      // If there is already a record for this ISBN tied to this node, skip it.
      // This prevents unnecessary database calls and API calls and is required
      // because of the possibility of dirty data.
      if (!isset($existing[$nid][$isbn])) {
        $isbns[$nid][$isbn] = TRUE;
      }
    }
    else {
      drush_print('Invalid ISBN Number: ' . $isbn . ' assigned to node ' . $nid);
    }
  }
}

/**
 * Check for changed ISBN's
 *
 * If an ISBN is no longer attached to a node, but the data has the association
 * still, that association needs to be removed. This function scans for those
 * situations and removes the association.
 *
 * @param array $isbns
 * @param array $existing
 *
 * @return void
 */
function nnels_content_cafe_check_changed($isbns, &$existing) {
  foreach ($isbns as $nid => $nid_isbns) {
    if (isset($existing[$nid])) {
      foreach ($existing[$nid] as $isbn => $isbn_id) {
        if (!isset($nid_isbns[$isbn])) {
          nnels_content_cafe_delete_node_content_cafe_row($nid, $isbn_id);
        }
      }
    }
  }
}

/**
 * Load Content Cafe Data
 *
 * @return array
 */
function nnels_content_cafe_load_content_cafe_data() {
  $query = db_select('node_content_cafe', 'nc');
  $query->join('content_cafe_isbn', 'i', 'i.isbn_id = nc.isbn_id');
  $query->fields('nc', array('nid'));
  $query->fields('i');
  $result = $query->execute();

  $existing = array();
  while ($row = $result->fetchObject()) {
    $existing[$row->nid][$row->isbn] = $row->isbn_id;
  }

  return $existing;
}

/**
 * Load ISBN Data
 *
 * @return array
 */
function nnels_content_cafe_load_isbn_data() {
  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_isbn', 'fi', 'fi.entity_id = n.nid');
  $query->leftJoin('field_data_field_isbn_audio', 'fa', 'fa.entity_id = n.nid');
  $query->fields('n', array('nid'));
  $query->fields('fi', array('field_isbn_value'));
  $query->fields('fa', array('field_isbn_audio_value'));
  $query->condition('n.type', 'repository_item');
  $or = db_or();
  $or->isNotNull('fi.field_isbn_value');
  $or->isNotNull('fa.field_isbn_audio_value');
  $query->condition($or);

  return $query->execute();
}

/**
 * Retrieve Data from the API
 *
 * @param int $isbn
 *
 * @return string
 */
function nnels_content_cafe_retrieve_data($isbn) {
  $api = new NNELSContentCafe($isbn);
  $api->AddAnnotationDetail();
  $api->AddBiographyDetail();
  $api->AddExcerptDetail();
  $api->AddFlapDetail();
  $api->AddJacketDetail(NNELSContentCafe::SIZE_LARGE);
  $api->AddTocDetail();

  return $api->Execute();
}

/**
 * Process Data from the API
 *
 * @param int $nid
 * @param int $isbn
 * @param string $data
 * @param array $existing
 *
 * @return int
 */
function nnels_content_cafe_process_data($nid, $isbn, $data, &$existing) {
  $isbn_id = FALSE;

  if ($data) {

    // Convert CP1252 characters to their UTF-8 equivalent since simplexml does
    // not know how to handle it.
    $data = str_replace('&#x0;', '', $data);
    $data = str_replace('&#x1C;', '', $data);
    $data = str_replace('&#x1D;', '', $data);
    $data = str_replace('&#x5;', '', $data);
    $data = str_replace('&#x14;', '', $data);
    $data = str_replace('&#x18;', '', $data);
    $data = str_replace('&#x19;', '', $data);

    // Parse the XML.
    $xml = simplexml_load_string($data);
    if ($xml !== FALSE) {

      // Took a while to get here, but this is the way to parse the XML tree
      // since curl is being used rather than SOAP.
      $soap             = $xml->children('soap' , TRUE);
      $xml_start        = $soap->children();
      $xml_request_item = $xml_start->XmlClassResponse->ContentCafe;

      // Handle any errors that come back from the API.
      if (isset($xml_request_item->Error)) {
        drush_print('Error: ' . (string)$xml_request_item->Error . ' (' . $isbn . ")");
      }

      // No errors, insert the data.
      else {
        $isbn_id = nnels_content_cafe_insert_content_cafe_isbn_row($isbn);

        $xml_request_item = $xml_request_item->RequestItems->RequestItem;
  
        // Process all of the possible data returned.
        nnels_content_cafe_process_data_annotations($isbn_id, $xml_request_item);
        nnels_content_cafe_process_data_biographies($isbn_id, $xml_request_item);
        nnels_content_cafe_process_data_excerpts($isbn_id, $xml_request_item);
        nnels_content_cafe_process_data_flaps($isbn_id, $xml_request_item);
        nnels_content_cafe_process_data_jackets($isbn_id, $isbn, $xml_request_item);
        nnels_content_cafe_process_data_tocs($isbn_id, $xml_request_item);

        // It is possible that a single node has multiple ISBN's attached and
        // adding this here will prevent duplicate insert errors.
        $existing[$nid][$isbn] = TRUE;
      }
    }
  }

  return $isbn_id;
}

/**
 * Process Annotation Data from the API
 *
 * @param int $isbn_id
 * @param object $xml_request_item
 *
 * @return void
 */
function nnels_content_cafe_process_data_annotations($isbn_id, $xml_request_item) {
  $xml_annotation_items = $xml_request_item->AnnotationItems;
  if (isset($xml_annotation_items)) {
    foreach ($xml_annotation_items->children() as $xml_annotation_item) {
      $external_id = (string)$xml_annotation_item['ID'];
      $annotation  = nnels_content_cafe_select_content_cafe_annotation_row($external_id);
      if ($annotation) {
        nnels_content_cafe_insert_content_cafe_isbn_annotation_row($isbn_id, $annotation->annotation_id);
      }
      else {
        $supplier_code = (string)$xml_annotation_item->Supplier['Code'];
        $supplier_name = (string)$xml_annotation_item->Supplier;
        $supplier_id   = nnels_content_cafe_retrieve_supplier_id($supplier_code, $supplier_name);
        $annotation    = (string)$xml_annotation_item->Annotation;
        $annotation_id = nnels_content_cafe_insert_content_cafe_annotation_row($external_id, $supplier_id, $annotation);
        nnels_content_cafe_insert_content_cafe_isbn_annotation_row($isbn_id, $annotation_id);
      }
    }
  }
}

/**
 * Process Biography Data from the API
 *
 * @param int $isbn_id
 * @param object $xml_request_item
 *
 * @return void
 */
function nnels_content_cafe_process_data_biographies($isbn_id, $xml_request_item) {
  $xml_biography_items = $xml_request_item->BiographyItems;
  if (isset($xml_biography_items)) {
    foreach ($xml_biography_items->children() as $xml_biography_item) {
      $external_id = (string)$xml_biography_item['ID'];
      $biography   = nnels_content_cafe_select_content_cafe_biography_row($external_id);
      if ($biography) {
        nnels_content_cafe_insert_content_cafe_isbn_annotation_row($isbn_id, $biography->biography_id);
      }
      else {
        $supplier_code = (string)$xml_biography_item->Supplier['Code'];
        $supplier_name = (string)$xml_biography_item->Supplier;
        $supplier_id   = nnels_content_cafe_retrieve_supplier_id($supplier_code, $supplier_name);
        $biography     = (string)$xml_biography_item->Biography;
        $biography_id  = nnels_content_cafe_insert_content_cafe_biography_row($external_id, $supplier_id, $biography);
        nnels_content_cafe_insert_content_cafe_isbn_biography_row($isbn_id, $biography_id);
      }
    }
  }
}

/**
 * Process Excerpt Data from the API
 *
 * @param int $isbn_id
 * @param object $xml_request_item
 *
 * @return void
 */
function nnels_content_cafe_process_data_excerpts($isbn_id, $xml_request_item) {
  $xml_excerpt_items = $xml_request_item->ExcerptItems;
  if (isset($xml_excerpt_items)) {
    foreach ($xml_excerpt_items->children() as $xml_excerpt_item) {
      $external_id = (string)$xml_excerpt_item['ID'];
      $excerpt     = nnels_content_cafe_select_content_cafe_excerpt_row($external_id);
      if ($excerpt) {
        nnels_content_cafe_insert_content_cafe_isbn_excerpt_row($isbn_id, $excerpt->excerpt_id);
      }
      else {
        $excerpt    = (string)$xml_excerpt_item->Excerpt;
        $excerpt_id = nnels_content_cafe_insert_content_cafe_excerpt_row($external_id, $excerpt);
        nnels_content_cafe_insert_content_cafe_isbn_excerpt_row($isbn_id, $excerpt_id);
      }
    }
  }
}

/**
 * Process Flap Data from the API
 *
 * @param int $isbn_id
 * @param object $xml_request_item
 *
 * @return void
 */
function nnels_content_cafe_process_data_flaps($isbn_id, $xml_request_item) {
  $xml_flap_items = $xml_request_item->FlapItems;
  if (isset($xml_flap_items)) {
    foreach ($xml_flap_items->children() as $xml_flap_item) {
      $external_id = (string)$xml_flap_item['ID'];
      $flap        = nnels_content_cafe_select_content_cafe_flap_row($external_id);
      if ($flap) {
        nnels_content_cafe_insert_content_cafe_isbn_flap_row($isbn_id, $flap->flap_id);
      }
      else {
        $supplier_code = (string)$xml_flap_item->Supplier['Code'];
        $supplier_name = (string)$xml_flap_item->Supplier;
        $supplier_id   = nnels_content_cafe_retrieve_supplier_id($supplier_code, $supplier_name);
        $flap          = (string)$xml_flap_item->Flap;
        $flap_id       = nnels_content_cafe_insert_content_cafe_flap_row($external_id, $supplier_id, $flap);
        nnels_content_cafe_insert_content_cafe_isbn_flap_row($isbn_id, $flap_id);
      }
    }
  }
}

/**
 * Process Jacket Data from the API
 *
 * @param int $isbn_id
 * @param string $isbn
 * @param object $xml_request_item
 *
 * @return void
 */
function nnels_content_cafe_process_data_jackets($isbn_id, $isbn, $xml_request_item) {
  $xml_jacket_items = $xml_request_item->JacketItems;
  if (isset($xml_jacket_items)) {
    foreach ($xml_jacket_items->children() as $xml_jacket_item) {
      $external_id = (string)$xml_jacket_item['ID'];
      $jacket      = nnels_content_cafe_select_content_cafe_jacket_row($external_id);
      if ($jacket) {
        nnels_content_cafe_insert_content_cafe_isbn_jacket_row($isbn_id, $flap->flap_id);
      }
      else {
        $jacket_image_url = (string)$xml_jacket_item->Jacket;

        $curl = curl_init();

        curl_setopt($curl, CURLOPT_URL,            $jacket_image_url);
        curl_setopt($curl, CURLOPT_CONNECTTIMEOUT, 10);
        curl_setopt($curl, CURLOPT_TIMEOUT,        10);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
        
        $headers = array();
        curl_setopt($curl, CURLOPT_HEADERFUNCTION,
          function($curl, $header) use (&$headers)
          {
            $len = strlen($header);
            $header = explode(':', $header, 2);
            if (count($header) < 2) // ignore invalid headers
              return $len;

            $name = strtolower(trim($header[0]));
            if (!array_key_exists($name, $headers))
              $headers[$name] = [trim($header[1])];
            else
              $headers[$name][] = trim($header[1]);

            return $len;
          }
        );

        $response = curl_exec($curl);

        // Determine extension from the response headers.
        $mime_mapping = file_mimetype_mapping();
        $mime_types   = array_flip($mime_mapping['mimetypes']);
        $extensions   = array_flip($mime_mapping['extensions']);
        $extension_id = $mime_types[$headers['content-type'][0]];
        $extension    = $extensions[$extension_id];

        // Send the file to S3, replace existing and then update the database.
        $file      = file_save_data($response, 's3://book-covers/' . $isbn . '.' . $extension, FILE_EXISTS_REPLACE);
        file_usage_add($file, 'nnels_content_cafe', 'jacket', $isbn_id);
        $jacket_id = nnels_content_cafe_insert_content_cafe_jacket_row($external_id, $file->fid);
        nnels_content_cafe_insert_content_cafe_isbn_jacket_row($isbn_id, $jacket_id);
      }
    }
  }
}

/**
 * Process TOC Data from the API
 *
 * @param int $isbn_id
 * @param object $xml_request_item
 *
 * @return void
 */
function nnels_content_cafe_process_data_tocs($isbn_id, $xml_request_item) {
  $xml_toc_items = $xml_request_item->TocItems;
  if (isset($xml_toc_items)) {
    foreach ($xml_toc_items->children() as $xml_toc_item) {
      $external_id = (string)$xml_toc_item['ID'];
      $toc         = nnels_content_cafe_select_content_cafe_toc_row($external_id);
      if ($toc) {
        nnels_content_cafe_insert_content_cafe_isbn_toc_row($isbn_id, $toc->toc_id);
      }
      else {
        $toc    = (string)$xml_toc_item->Toc;
        $toc_id = nnels_content_cafe_insert_content_cafe_toc_row($external_id, $toc);
        nnels_content_cafe_insert_content_cafe_isbn_toc_row($isbn_id, $toc_id);
      }
    }
  }
}

/**
 * Retrieve Supplier ID from the database.
 *
 * @param string $supplier_code
 * @param string $supplier_name
 *
 * @return int
 */
function nnels_content_cafe_retrieve_supplier_id($supplier_code, $supplier_name) {
  static $suppliers = array();

  $id = NULL;
  if (isset($suppliers[strtoupper($supplier_code)])) {
    $id = $suppliers[strtoupper($supplier_code)];
  }
  else {
    $record = nnels_content_cafe_select_content_cafe_supplier_row($supplier_code);
    if ($record) {
      $id = $record->supplier_id;
    }
    else {
      $id = nnels_content_cafe_insert_content_cafe_supplier_row($supplier_code, $supplier_name);
    }
    $suppliers[strtoupper($supplier_code)] = $id;
  }

  return $id;
}

/**
 * Conditionally Insert Node Row
 *
 * @param int $nid
 * @param int $isbn_id
 *
 * @return void
 */
function nnels_content_cafe_conditionally_insert_node_content_cafe_row($nid, $isbn_id) {
  if (!nnels_content_cafe_select_node_content_cafe_row($nid, $isbn_id)) {
    nnels_content_cafe_insert_node_content_cafe_row($nid, $isbn_id);
  }
}
