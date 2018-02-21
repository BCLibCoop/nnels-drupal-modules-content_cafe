<?php

/**
 * Validate ISBN
 *
 * This function also modifies the ISBN if it contains any non-numeric
 * characters.
 *
 * @param int $isbn
 *
 * @return bool
 */
function nnels_content_cafe_validate_isbn(&$isbn) {
  $valid = FALSE;

  // Clean the data - only digits.
  $isbn = preg_replace('/[^\d]/', '', $isbn);

  $isbn_length = strlen($isbn);
  if ($isbn_length == 10) {
    $numbers = str_split($isbn);
    $sum     = 0;
    $i       = 10;
    foreach ($numbers as $number) {
      $sum += ($number * $i);
      $i--;
    }
    $mod = $sum % 11;
    if ($mod == 0) {
      $valid = TRUE;
    }
  }
  elseif ($isbn_length == 13) {
    $numbers = str_split($isbn);
    $sum     = 0;
    $i       = 1;
    foreach ($numbers as $number) {
      $sum += ($number * $i);
      if ($i == 1) {
        $i = 3;
      }
      else {
        $i = 1;
      }
    }
    $mod = $sum % 10;
    if ($mod == 0) {
      $valid = TRUE;
    }
  }

  return $valid;
}

/**
 * Insert a row into the content_cafe_isbn table.
 *
 * @param string $isbn
 *
 * @return int
 */
function nnels_content_cafe_insert_content_cafe_isbn_row($isbn) {
  print "Insert into content_cafe_isbn\n";
  return db_insert('content_cafe_isbn')
    ->fields(
      array(
        'isbn' => $isbn,
      )
    )
    ->execute();
}

/**
 * Insert a row into the content_cafe_supplier table.
 *
 * @param string $supplier_code
 * @param string $supplier_name
 *
 * @return int
 */
function nnels_content_cafe_insert_content_cafe_supplier_row($supplier_code, $supplier_name) {
  print "Insert into content_cafe_supplier\n";
  return db_insert('content_cafe_supplier')
    ->fields(
      array(
        'supplier_code' => strtoupper($supplier_code),
        'supplier_name' => $supplier_name,
      )
    )
    ->execute();
}

/**
 * Insert a row into the content_cafe_annotation table.
 *
 * @param int $external_id
 * @param int $supplier_id
 * @param string $annotation
 *
 * @return int
 */
function nnels_content_cafe_insert_content_cafe_annotation_row($external_id, $supplier_id, $annotation) {
  print "Insert into content_cafe_annotation\n";
  return db_insert('content_cafe_annotation')
    ->fields(
      array(
        'external_id' => $external_id,
        'supplier_id' => $supplier_id,
        'annotation'  => $annotation,
      )
    )
    ->execute();
}

/**
 * Insert a row into the content_cafe_isbn_annotation table.
 *
 * @param int $isbn_id
 * @param int $annotation_id
 *
 * @return int
 */
function nnels_content_cafe_insert_content_cafe_isbn_annotation_row($isbn_id, $annotation_id) {
  print "Insert into content_cafe_isbn_annotation\n";
  return db_insert('content_cafe_isbn_annotation')
    ->fields(
      array(
        'isbn_id'       => $isbn_id,
        'annotation_id' => $annotation_id,
      )
    )
    ->execute();
}

/**
 * Insert a row into the content_cafe_biography table.
 *
 * @param int $external_id
 * @param int $supplier_id
 * @param string $biography
 *
 * @return int
 */
function nnels_content_cafe_insert_content_cafe_biography_row($external_id, $supplier_id, $biography) {
  print "Insert into content_cafe_biography\n";
  return db_insert('content_cafe_biography')
    ->fields(
      array(
        'external_id' => $external_id,
        'supplier_id' => $supplier_id,
        'biography'   => $biography,
      )
    )
    ->execute();
}

/**
 * Insert a row into the content_cafe_isbn_biography table.
 *
 * @param int $isbn_id
 * @param int $biography_id
 *
 * @return int
 */
function nnels_content_cafe_insert_content_cafe_isbn_biography_row($isbn_id, $biography_id) {
  print "Insert into content_cafe_isbn_biography\n";
  return db_insert('content_cafe_isbn_biography')
    ->fields(
      array(
        'isbn_id'      => $isbn_id,
        'biography_id' => $biography_id,
      )
    )
    ->execute();
}

/**
 * Insert a row into the content_cafe_excerpt table.
 *
 * @param int $external_id
 * @param string $excerpt
 *
 * @return int
 */
function nnels_content_cafe_insert_content_cafe_excerpt_row($external_id, $excerpt) {
  print "Insert into content_cafe_excerpt\n";
  return db_insert('content_cafe_excerpt')
    ->fields(
      array(
        'external_id' => $external_id,
        'excerpt'     => $excerpt,
      )
    )
    ->execute();
}

/**
 * Insert a row into the content_cafe_isbn_excerpt table.
 *
 * @param int $isbn_id
 * @param int $excerpt_id
 *
 * @return int
 */
function nnels_content_cafe_insert_content_cafe_isbn_excerpt_row($isbn_id, $excerpt_id) {
  print "Insert into content_cafe_isbn_excerpt\n";
  return db_insert('content_cafe_isbn_excerpt')
    ->fields(
      array(
        'isbn_id'    => $isbn_id,
        'excerpt_id' => $excerpt_id,
      )
    )
    ->execute();
}

/**
 * Insert a row into the content_cafe_flap table.
 *
 * @param int $external_id
 * @param int $supplier_id
 * @param string $flap
 *
 * @return int
 */
function nnels_content_cafe_insert_content_cafe_flap_row($external_id, $supplier_id, $flap) {
  print "Insert into content_cafe_flap\n";
  return db_insert('content_cafe_flap')
    ->fields(
      array(
        'external_id' => $external_id,
        'supplier_id' => $supplier_id,
        'flap'        => $flap,
      )
    )
    ->execute();
}

/**
 * Insert a row into the content_cafe_isbn_flap table.
 *
 * @param int $isbn_id
 * @param int $flap_id
 *
 * @return int
 */
function nnels_content_cafe_insert_content_cafe_isbn_flap_row($isbn_id, $flap_id) {
  print "Insert into content_cafe_isbn_flap\n";
  return db_insert('content_cafe_isbn_flap')
    ->fields(
      array(
        'isbn_id' => $isbn_id,
        'flap_id' => $flap_id,
      )
    )
    ->execute();
}

/**
 * Insert a row into the content_cafe_toc table.
 *
 * @param int $external_id
 * @param string $toc
 *
 * @return int
 */
function nnels_content_cafe_insert_content_cafe_toc_row($external_id, $toc) {
  print "Insert into content_cafe_toc\n";
  return db_insert('content_cafe_toc')
    ->fields(
      array(
        'external_id' => $external_id,
        'toc'         => $toc,
      )
    )
    ->execute();
}

/**
 * Insert a row into the content_cafe_isbn_toc table.
 *
 * @param int $isbn_id
 * @param int $toc_id
 *
 * @return int
 */
function nnels_content_cafe_insert_content_cafe_isbn_toc_row($isbn_id, $toc_id) {
  print "Insert into content_cafe_isbn_toc\n";
  return db_insert('content_cafe_isbn_toc')
    ->fields(
      array(
        'isbn_id' => $isbn_id,
        'toc_id'  => $toc_id,
      )
    )
    ->execute();
}

/**
 * Insert a row into the node_content_cafe table.
 *
 * @param int $nid
 * @param int $isbn_id
 *
 * @return int
 */
function nnels_content_cafe_insert_node_content_cafe_row($nid, $isbn_id) {
  print "Insert into node_content_cafe\n";
  return db_insert('node_content_cafe')
    ->fields(
      array(
        'nid'     => $nid,
        'isbn_id' => $isbn_id,
      )
    )
    ->execute();
}

/**
 * Select rows from the content_cafe_isbn table.
 *
 * @param array $isbns
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_isbn_rows($isbns) {
  $records = FALSE;

  if (count($isbns)) {
    $result = db_select('content_cafe_isbn', 'c')
      ->fields('c')
      ->condition('c.isbn', $isbns, 'IN')
      ->execute();
    
    if ($result->rowCount()) {
      $records = array();
      while ($record = $result->fetchObject()) {
        $records[$record->isbn_id] = $record->isbn;
      }
    }
  }

  return $records;
}

/**
 * Select a row from the content_cafe_isbn table.
 *
 * @param int $isbn
 *
 * @return mixed
 */
function nnels_content_cafe_select_content_cafe_isbn_row($isbn) {
  print "Select from content_cafe_isbn\n";
  $result = db_select('content_cafe_isbn', 'c')
    ->fields('c')
    ->condition('c.isbn', $isbn)
    ->execute();

  $record = FALSE;
  if ($result->rowCount()) {
    $record = $result->fetchObject();
  }

  return $record;
}

/**
 * Select a row from the content_cafe_supplier table.
 *
 * @param string $supplier_code
 *
 * @return mixed
 */
function nnels_content_cafe_select_content_cafe_supplier_row($supplier_code) {
  print "Select from content_cafe_supplier\n";
  $result = db_select('content_cafe_supplier', 's')
    ->fields('s')
    ->condition('s.supplier_code', strtoupper($supplier_code))
    ->execute();

  $record = FALSE;
  if ($result->rowCount()) {
    $record = $result->fetchObject();
  }

  return $record;
}

/**
 * Select multiple rows from the content_cafe_supplier table.
 *
 * @param array $supplier_ids
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_supplier_rows($supplier_ids) {
  $records = FALSE;

  if (count($supplier_ids)) {
    $result = db_select('content_cafe_supplier', 's')
      ->fields('s')
      ->condition('s.supplier_id', $supplier_ids, 'IN')
      ->execute();

    while ($record = $result->fetchObject()) {
      $records[$record->supplier_id] = $record;
    }
  }

  return $records;
}

/**
 * Select a row from the content_cafe_annotation table.
 *
 * @param int $external_id
 *
 * @return mixed
 */
function nnels_content_cafe_select_content_cafe_annotation_row($external_id) {
  $result = db_select('content_cafe_annotation', 'a')
    ->fields('a')
    ->condition('a.external_id', $external_id)
    ->execute();

  $record = FALSE;
  if ($result->rowCount()) {
    $record = $result->fetchObject();
  }

  return $record;
}

/**
 * Select rows from the content_cafe_annotation table.
 *
 * @param array $isbns
 * @param array $supplier_ids
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_annotation_rows($isbns, &$supplier_ids) {
  $records = FALSE;

  if (count($isbns)) {
    $query = db_select('content_cafe_isbn_annotation', 'i');
    $query->join('content_cafe_annotation', 'c', 'c.annotation_id = i.annotation_id');
    $query->fields('i');
    $query->fields('c');
    $query->condition('i.isbn_id', $isbns, 'IN');
    $result = $query->execute();
    
    if ($result->rowCount()) {
      $records  = array();
      $selected = FALSE;
      while ($record = $result->fetchObject()) {
        $records[$record->annotation_id]    = $record;
        $supplier_ids[$record->supplier_id] = TRUE;
        if ($record->selected) {
          $selected = TRUE;
        }
      }

      // Set the default selected value.
      if (!$selected) {
        reset($records);
        $records[key($records)]->selected = TRUE;
      }
    }
  }

  return $records;
}

/**
 * Select rows from the content_cafe_annotation table.
 *
 * @param array $nids
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_annotation_rows_by_nids($nids) {
  $records = FALSE;

  if (count($nids)) {
    $query = db_select('node_content_cafe', 'n');
    $query->join('content_cafe_isbn_annotation', 'i', 'i.isbn_id = n.isbn_id');
    $query->join('content_cafe_annotation', 'd', 'd.annotation_id = i.annotation_id');
    $query->fields('n');
    $query->fields('i');
    $query->fields('d');
    $query->condition('n.nid', $nids, 'IN');
    $result = $query->execute();

    if ($result->rowCount()) {

      // Gather the records by nid.
      $records = array();
      while ($record = $result->fetchObject()) {
        $records[$record->nid][$record->annotation_id] = $record;
      }

      // Determine if one of the records has been selected.
      foreach ($records as $nid => $nid_records) {
        $selected = FALSE;
        foreach ($nid_records as $id => $record) {
          if ($record->selected) {
            $selected = TRUE;
          }
        }

        // No records selected, set the default selected value.
        if (!$selected) {
          reset($nid_records);
          $nid_records[key($nid_records)]->selected = TRUE;
        }
      }
    }
  }

  return $records;
}

/**
 * Select all rows from the content_cafe_annotation table.
 *
 * @param bool $quick
 *
 * @return mixed
 */
function nnels_content_cafe_select_all_content_cafe_annotation_rows($quick = FALSE) {
  $records = FALSE;

  $query = db_select('node_content_cafe', 'n');
  $query->join('content_cafe_isbn_annotation', 'i', 'i.isbn_id = n.isbn_id');
  $query->join('content_cafe_annotation', 'd', 'd.annotation_id = i.annotation_id');
  $query->fields('n', array('nid'));
  if ($quick) {
    $query->fields('i', array('annotation_id'));
  }
  else {
    $query->fields('i', array('annotation_id', 'selected'));
    $query->fields('d');
  }
  $result = $query->execute();

  if ($result->rowCount()) {
    $records = array();
    while ($record = $result->fetchObject()) {
      if ($quick) {
        $records[$record->nid] = TRUE;
      }
      else {
        $records[$record->nid][$record->annotation_id] = $record;
      }
    }
  }

  return $records;
}

/**
 * Select a row from the content_cafe_biography table.
 *
 * @param int $external_id
 *
 * @return mixed
 */
function nnels_content_cafe_select_content_cafe_biography_row($external_id) {
  print "Select from content_cafe_biography\n";
  $result = db_select('content_cafe_biography', 'b')
    ->fields('b')
    ->condition('b.external_id', $external_id)
    ->execute();

  $record = FALSE;
  if ($result->rowCount()) {
    $record = $result->fetchObject();
  }

  return $record;
}

/**
 * Select rows from the content_cafe_biography table.
 *
 * @param array $isbns
 * @param array $supplier_ids
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_biography_rows($isbns, &$supplier_ids) {
  $records = FALSE;

  if (count($isbns)) {
    $query = db_select('content_cafe_isbn_biography', 'i');
    $query->join('content_cafe_biography', 'c', 'c.biography_id = i.biography_id');
    $query->fields('i');
    $query->fields('c');
    $query->condition('i.isbn_id', $isbns, 'IN');
    $result = $query->execute();
    
    if ($result->rowCount()) {
      $records  = array();
      $selected = FALSE;
      while ($record = $result->fetchObject()) {
        $records[$record->biography_id]    = $record;
        $supplier_ids[$record->supplier_id] = TRUE;
        if ($record->selected) {
          $selected = TRUE;
        }
      }

      // Set the default selected value.
      if (!$selected) {
        reset($records);
        $records[key($records)]->selected = TRUE;
      }
    }
  }

  return $records;
}

/**
 * Select rows from the content_cafe_biography table.
 *
 * @param array $nids
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_biography_rows_by_nids($nids) {
  $records = FALSE;

  if (count($nids)) {
    $query = db_select('node_content_cafe', 'n');
    $query->join('content_cafe_isbn_biography', 'i', 'i.isbn_id = n.isbn_id');
    $query->join('content_cafe_biography', 'd', 'd.biography_id = i.biography_id');
    $query->fields('n');
    $query->fields('i');
    $query->fields('d');
    $query->condition('n.nid', $nids, 'IN');
    $result = $query->execute();

    if ($result->rowCount()) {

      // Gather the records by nid.
      $records = array();
      while ($record = $result->fetchObject()) {
        $records[$record->nid][$record->biography_id] = $record;
      }

      // Determine if one of the records has been selected.
      foreach ($records as $nid => $nid_records) {
        $selected = FALSE;
        foreach ($nid_records as $id => $record) {
          if ($record->selected) {
            $selected = TRUE;
          }
        }

        // No records selected, set the default selected value.
        if (!$selected) {
          reset($nid_records);
          $nid_records[key($nid_records)]->selected = TRUE;
        }
      }
    }
  }

  return $records;
}

/**
 * Select all rows from the content_cafe_biography table.
 *
 * @param bool $quick
 *
 * @return mixed
 */
function nnels_content_cafe_select_all_content_cafe_biography_rows($quick = FALSE) {
  $records = FALSE;

  $query = db_select('node_content_cafe', 'n');
  $query->join('content_cafe_isbn_biography', 'i', 'i.isbn_id = n.isbn_id');
  $query->join('content_cafe_biography', 'd', 'd.biography_id = i.biography_id');
  $query->fields('n', array('nid'));
  if ($quick) {
    $query->fields('i', array('biography_id'));
  }
  else {
    $query->fields('i', array('biography_id', 'selected'));
    $query->fields('d');
  }
  $result = $query->execute();

  if ($result->rowCount()) {
    $records = array();
    while ($record = $result->fetchObject()) {
      if ($quick) {
        $records[$record->nid] = TRUE;
      }
      else {
        $records[$record->nid][$record->biography_id] = $record;
      }
    }
  }

  return $records;
}

/**
 * Select a row from the content_cafe_excerpt table.
 *
 * @param int $external_id
 *
 * @return mixed
 */
function nnels_content_cafe_select_content_cafe_excerpt_row($external_id) {
  print "Select from content_cafe_excerpt\n";
  $result = db_select('content_cafe_excerpt', 'e')
    ->fields('e')
    ->condition('e.external_id', $external_id)
    ->execute();

  $record = FALSE;
  if ($result->rowCount()) {
    $record = $result->fetchObject();
  }

  return $record;
}

/**
 * Select rows from the content_cafe_excerpt table.
 *
 * @param array $isbns
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_excerpt_rows($isbns) {
  $records = FALSE;

  if (count($isbns)) {
    $query = db_select('content_cafe_isbn_excerpt', 'i');
    $query->join('content_cafe_excerpt', 'c', 'c.excerpt_id = i.excerpt_id');
    $query->fields('i');
    $query->fields('c');
    $query->condition('i.isbn_id', $isbns, 'IN');
    $result = $query->execute();
    
    if ($result->rowCount()) {
      $records  = array();
      $selected = FALSE;
      while ($record = $result->fetchObject()) {
        $records[$record->excerpt_id] = $record;
        if ($record->selected) {
          $selected = TRUE;
        }
      }

      // Set the default selected value.
      if (!$selected) {
        reset($records);
        $records[key($records)]->selected = TRUE;
      }
    }
  }

  return $records;
}

/**
 * Select rows from the content_cafe_excerpt table.
 *
 * @param array $nids
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_excerpt_rows_by_nids($nids) {
  $records = FALSE;

  if (count($nids)) {
    $query = db_select('node_content_cafe', 'n');
    $query->join('content_cafe_isbn_excerpt', 'i', 'i.isbn_id = n.isbn_id');
    $query->join('content_cafe_excerpt', 'd', 'd.excerpt_id = i.excerpt_id');
    $query->fields('n');
    $query->fields('i');
    $query->fields('d');
    $query->condition('n.nid', $nids, 'IN');
    $result = $query->execute();

    if ($result->rowCount()) {

      // Gather the records by nid.
      $records = array();
      while ($record = $result->fetchObject()) {
        $records[$record->nid][$record->excerpt_id] = $record;
      }

      // Determine if one of the records has been selected.
      foreach ($records as $nid => $nid_records) {
        $selected = FALSE;
        foreach ($nid_records as $id => $record) {
          if ($record->selected) {
            $selected = TRUE;
          }
        }

        // No records selected, set the default selected value.
        if (!$selected) {
          reset($nid_records);
          $nid_records[key($nid_records)]->selected = TRUE;
        }
      }
    }
  }

  return $records;
}

/**
 * Select all rows from the content_cafe_excerpt table.
 *
 * @param bool $quick
 *
 * @return mixed
 */
function nnels_content_cafe_select_all_content_cafe_excerpt_rows($quick = FALSE) {
  $records = FALSE;

  $query = db_select('node_content_cafe', 'n');
  $query->join('content_cafe_isbn_excerpt', 'i', 'i.isbn_id = n.isbn_id');
  $query->join('content_cafe_excerpt', 'd', 'd.excerpt_id = i.excerpt_id');
  $query->fields('n', array('nid'));
  if ($quick) {
    $query->fields('i', array('excerpt_id'));
  }
  else {
    $query->fields('i', array('excerpt_id', 'selected'));
    $query->fields('d');
  }
  $result = $query->execute();

  if ($result->rowCount()) {
    $records = array();
    while ($record = $result->fetchObject()) {
      if ($quick) {
        $records[$record->nid] = TRUE;
      }
      else {
        $records[$record->nid][$record->excerpt_id] = $record;
      }
    }
  }

  return $records;
}

/**
 * Select a row from the content_cafe_flap table.
 *
 * @param int $external_id
 *
 * @return mixed
 */
function nnels_content_cafe_select_content_cafe_flap_row($external_id) {
  print "Select from content_cafe_flap\n";
  $result = db_select('content_cafe_flap', 'f')
    ->fields('f')
    ->condition('f.external_id', $external_id)
    ->execute();

  $record = FALSE;
  if ($result->rowCount()) {
    $record = $result->fetchObject();
  }

  return $record;
}

/**
 * Select rows from the content_cafe_flap table.
 *
 * @param array $isbns
 * @param array $supplier_ids
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_flap_rows($isbns, &$supplier_ids) {
  $records = FALSE;

  if (count($isbns)) {
    $query = db_select('content_cafe_isbn_flap', 'i');
    $query->join('content_cafe_flap', 'c', 'c.flap_id = i.flap_id');
    $query->fields('i');
    $query->fields('c');
    $query->condition('i.isbn_id', $isbns, 'IN');
    $result = $query->execute();
    
    if ($result->rowCount()) {
      $records  = array();
      $selected = FALSE;
      while ($record = $result->fetchObject()) {
        $records[$record->flap_id]    = $record;
        $supplier_ids[$record->supplier_id] = TRUE;
        if ($record->selected) {
          $selected = TRUE;
        }
      }

      // Set the default selected value.
      if (!$selected) {
        reset($records);
        $records[key($records)]->selected = TRUE;
      }
    }
  }

  return $records;
}

/**
 * Select rows from the content_cafe_flap table.
 *
 * @param array $nids
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_flap_rows_by_nids($nids) {
  $records = FALSE;

  if (count($nids)) {
    $query = db_select('node_content_cafe', 'n');
    $query->join('content_cafe_isbn_flap', 'i', 'i.isbn_id = n.isbn_id');
    $query->join('content_cafe_flap', 'd', 'd.flap_id = i.flap_id');
    $query->fields('n');
    $query->fields('i');
    $query->fields('d');
    $query->condition('n.nid', $nids, 'IN');
    $result = $query->execute();

    if ($result->rowCount()) {

      // Gather the records by nid.
      $records = array();
      while ($record = $result->fetchObject()) {
        $records[$record->nid][$record->flap_id] = $record;
      }

      // Determine if one of the records has been selected.
      foreach ($records as $nid => $nid_records) {
        $selected = FALSE;
        foreach ($nid_records as $id => $record) {
          if ($record->selected) {
            $selected = TRUE;
          }
        }

        // No records selected, set the default selected value.
        if (!$selected) {
          reset($nid_records);
          $nid_records[key($nid_records)]->selected = TRUE;
        }
      }
    }
  }

  return $records;
}

/**
 * Select all rows from the content_cafe_flap table.
 *
 * @param bool $quick
 *
 * @return mixed
 */
function nnels_content_cafe_select_all_content_cafe_flap_rows($quick = FALSE) {
  $records = FALSE;

  $query = db_select('node_content_cafe', 'n');
  $query->join('content_cafe_isbn_flap', 'i', 'i.isbn_id = n.isbn_id');
  $query->join('content_cafe_flap', 'd', 'd.flap_id = i.flap_id');
  $query->fields('n', array('nid'));
  if ($quick) {
    $query->fields('i', array('flap_id'));
  }
  else {
    $query->fields('i', array('flap_id', 'selected'));
    $query->fields('d');
  }
  $result = $query->execute();

  if ($result->rowCount()) {
    $records = array();
    while ($record = $result->fetchObject()) {
      if ($quick) {
        $records[$record->nid] = TRUE;
      }
      else {
        $records[$record->nid][$record->flap_id] = $record;
      }
    }
  }

  return $records;
}

/**
 * Select rows from the content_cafe_jacket table.
 *
 * @param array $isbns
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_jacket_rows($isbns) {
  $records = FALSE;

  if (count($isbns)) {
    $query = db_select('content_cafe_isbn_jacket', 'i');
    $query->join('content_cafe_jacket', 'c', 'c.jacket_id = i.jacket_id');
    $query->fields('i');
    $query->fields('c');
    $query->condition('i.isbn_id', $isbns, 'IN');
    $result = $query->execute();
    
    if ($result->rowCount()) {
      $records  = array();
      $selected = FALSE;
      while ($record = $result->fetchObject()) {
        $records[$record->jacket_id] = $record;
        if ($record->selected) {
          $selected = TRUE;
        }
      }

      // Set the default selected value.
      if (!$selected) {
        reset($records);
        $records[key($records)]->selected = TRUE;
      }
    }
  }

  return $records;
}

/**
 * Select rows from the content_cafe_jacket table.
 *
 * @param array $nids
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_jacket_rows_by_nids($nids) {
  $records = FALSE;

  if (count($nids)) {
    $query = db_select('node_content_cafe', 'n');
    $query->join('content_cafe_isbn_jacket', 'i', 'i.isbn_id = n.isbn_id');
    $query->join('content_cafe_jacket', 'd', 'd.jacket_id = i.jacket_id');
    $query->fields('n');
    $query->fields('i');
    $query->fields('d');
    $query->condition('n.nid', $nids, 'IN');
    $result = $query->execute();

    if ($result->rowCount()) {

      // Gather the records by nid.
      $records = array();
      while ($record = $result->fetchObject()) {
        $records[$record->nid][$record->jacket_id] = $record;
      }

      // Determine if one of the records has been selected.
      foreach ($records as $nid => $nid_records) {
        $selected = FALSE;
        foreach ($nid_records as $id => $record) {
          if ($record->selected) {
            $selected = TRUE;
          }
        }

        // No records selected, set the default selected value.
        if (!$selected) {
          reset($nid_records);
          $nid_records[key($nid_records)]->selected = TRUE;
        }
      }
    }
  }

  return $records;
}

/**
 * Select all rows from the content_cafe_jacket table.
 *
 * @param bool $quick
 *
 * @return mixed
 */
function nnels_content_cafe_select_all_content_cafe_jacket_rows($quick = FALSE) {
  $records = FALSE;

  $query = db_select('node_content_cafe', 'n');
  $query->join('content_cafe_isbn_jacket', 'i', 'i.isbn_id = n.isbn_id');
  $query->join('content_cafe_jacket', 'd', 'd.jacket_id = i.jacket_id');
  $query->fields('n', array('nid'));
  if ($quick) {
    $query->fields('i', array('jacket_id'));
  }
  else {
    $query->fields('i', array('jacket_id', 'selected'));
    $query->fields('d');
  }
  $result = $query->execute();

  if ($result->rowCount()) {
    $records = array();
    while ($record = $result->fetchObject()) {
      if ($quick) {
        $records[$record->nid] = TRUE;
      }
      else {
        $records[$record->nid][$record->jacket_id] = $record;
      }
    }
  }

  return $records;
}

/**
 * Select a row from the content_cafe_toc table.
 *
 * @param int $external_id
 *
 * @return mixed
 */
function nnels_content_cafe_select_content_cafe_toc_row($external_id) {
  print "Select from content_cafe_toc\n";
  $result = db_select('content_cafe_toc', 't')
    ->fields('t')
    ->condition('t.external_id', $external_id)
    ->execute();

  $record = FALSE;
  if ($result->rowCount()) {
    $record = $result->fetchObject();
  }

  return $record;
}

/**
 * Select rows from the content_cafe_toc table.
 *
 * @param array $isbns
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_toc_rows($isbns) {
  $records = FALSE;

  if (count($isbns)) {
    $query = db_select('content_cafe_isbn_toc', 'i');
    $query->join('content_cafe_toc', 'c', 'c.toc_id = i.toc_id');
    $query->fields('i');
    $query->fields('c');
    $query->condition('i.isbn_id', $isbns, 'IN');
    $result = $query->execute();
    
    if ($result->rowCount()) {
      $records  = array();
      $selected = FALSE;
      while ($record = $result->fetchObject()) {
        $records[$record->toc_id] = $record;
        if ($record->selected) {
          $selected = TRUE;
        }
      }

      // Set the default selected value.
      if (!$selected) {
        reset($records);
        $records[key($records)]->selected = TRUE;
      }
    }
  }

  return $records;
}

/**
 * Select rows from the content_cafe_toc table.
 *
 * @param array $nids
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_content_cafe_toc_rows_by_nids($nids) {
  $records = FALSE;

  if (count($nids)) {
    $query = db_select('node_content_cafe', 'n');
    $query->join('content_cafe_isbn_toc', 'i', 'i.isbn_id = n.isbn_id');
    $query->join('content_cafe_toc', 'd', 'd.toc_id = i.toc_id');
    $query->fields('n');
    $query->fields('i');
    $query->fields('d');
    $query->condition('n.nid', $nids, 'IN');
    $result = $query->execute();

    if ($result->rowCount()) {

      // Gather the records by nid.
      $records = array();
      while ($record = $result->fetchObject()) {
        $records[$record->nid][$record->toc_id] = $record;
      }

      // Determine if one of the records has been selected.
      foreach ($records as $nid => $nid_records) {
        $selected = FALSE;
        foreach ($nid_records as $id => $record) {
          if ($record->selected) {
            $selected = TRUE;
          }
        }

        // No records selected, set the default selected value.
        if (!$selected) {
          reset($nid_records);
          $nid_records[key($nid_records)]->selected = TRUE;
        }
      }
    }
  }

  return $records;
}

/**
 * Select all rows from the content_cafe_toc table.
 *
 * @param bool $quick
 *
 * @return mixed
 */
function nnels_content_cafe_select_all_content_cafe_toc_rows($quick = FALSE) {
  $records = FALSE;

  $query = db_select('node_content_cafe', 'n');
  $query->join('content_cafe_isbn_toc', 'i', 'i.isbn_id = n.isbn_id');
  $query->join('content_cafe_toc', 'd', 'd.toc_id = i.toc_id');
  $query->fields('n', array('nid'));
  if ($quick) {
    $query->fields('i', array('toc_id'));
  }
  else {
    $query->fields('i', array('toc_id', 'selected'));
    $query->fields('d');
  }
  $result = $query->execute();

  if ($result->rowCount()) {
    $records = array();
    while ($record = $result->fetchObject()) {
      if ($quick) {
        $records[$record->nid] = TRUE;
      }
      else {
        $records[$record->nid][$record->toc_id] = $record;
      }
    }
  }

  return $records;
}

/**
 * Select a row from the node_content_cafe table.
 *
 * @param int $nid
 * @param int $isbn_id
 *
 * @return mixed
 */
function nnels_content_cafe_select_node_content_cafe_row($nid, $isbn_id) {
  print "Select from node_content_cafe\n";
  $result = db_select('node_content_cafe', 's')
    ->fields('s')
    ->condition('s.nid', $nid)
    ->condition('s.isbn_id', $isbn_id)
    ->execute();

  $record = FALSE;
  if ($result->rowCount()) {
    $record = $result->fetchObject();
  }

  return $record;
}

/**
 * Select rows from the node_content_cafe table.
 *
 * @param int $nid
 *
 * @return mixed
 */
function nnels_content_cafe_select_multiple_node_content_cafe_rows($nid) {
  $result = db_select('node_content_cafe', 's')
    ->fields('s')
    ->condition('s.nid', $nid)
    ->execute();

  $records = FALSE;
  if ($result->rowCount()) {
    $records = array();
    while ($record = $result->fetchObject()) {
      $records[$record->isbn_id] = $record;
    }
  }

  return $records;
}

/**
 * Update a row in the content_cafe_annotation table.
 *
 * @param int $external_id
 * @param string $annotation
 *
 * @return void
 */
function nnels_content_cafe_update_content_cafe_annotation_row($external_id, $annotation) {
  db_update('content_cafe_annotation')
    ->fields(
      array(
        'annotation' => $annotation,
      )
    )
    ->condition('external_id', $external_id)
    ->execute();
}

/**
 * Update a row in the content_cafe_isbn_annotation table.
 *
 * @param int $annotation_id
 * @param bool $selected
 *
 * @return void
 */
function nnels_content_cafe_update_content_cafe_isbn_annotation_row($annotation_id, $selected) {
  db_update('content_cafe_isbn_annotation')
    ->fields(
      array(
        'selected' => (int)$selected,
      )
    )
    ->condition('annotation_id', $annotation_id)
    ->execute();
}

/**
 * Update a row in the content_cafe_biography table.
 *
 * @param int $external_id
 * @param string $biography
 *
 * @return void
 */
function nnels_content_cafe_update_content_cafe_biography_row($external_id, $biography) {
  db_update('content_cafe_biography')
    ->fields(
      array(
        'biography' => $biography,
      )
    )
    ->condition('external_id', $external_id)
    ->execute();
}

/**
 * Update a row in the content_cafe_isbn_biography table.
 *
 * @param int $biography_id
 * @param bool $selected
 *
 * @return void
 */
function nnels_content_cafe_update_content_cafe_isbn_biography_row($biography_id, $selected) {
  db_update('content_cafe_isbn_biography')
    ->fields(
      array(
        'selected' => (int)$selected,
      )
    )
    ->condition('biography_id', $biography_id)
    ->execute();
}

/**
 * Update a row in the content_cafe_excerpt table.
 *
 * @param int $external_id
 * @param string $excerpt
 *
 * @return void
 */
function nnels_content_cafe_update_content_cafe_excerpt_row($external_id, $excerpt) {
  db_update('content_cafe_excerpt')
    ->fields(
      array(
        'excerpt' => $excerpt,
      )
    )
    ->condition('external_id', $external_id)
    ->execute();
}

/**
 * Update a row in the content_cafe_isbn_excerpt table.
 *
 * @param int $excerpt_id
 * @param bool $selected
 *
 * @return void
 */
function nnels_content_cafe_update_content_cafe_isbn_excerpt_row($excerpt_id, $selected) {
  db_update('content_cafe_isbn_excerpt')
    ->fields(
      array(
        'selected' => (int)$selected,
      )
    )
    ->condition('excerpt_id', $excerpt_id)
    ->execute();
}

/**
 * Update a row in the content_cafe_flap table.
 *
 * @param int $external_id
 * @param string $flap
 *
 * @return void
 */
function nnels_content_cafe_update_content_cafe_flap_row($external_id, $flap) {
  db_update('content_cafe_flap')
    ->fields(
      array(
        'flap' => $flap,
      )
    )
    ->condition('external_id', $external_id)
    ->execute();
}

/**
 * Update a row in the content_cafe_isbn_jacket table.
 *
 * @param int $jacket_id
 * @param bool $selected
 *
 * @return void
 */
function nnels_content_cafe_update_content_cafe_isbn_jacket_row($jacket_id, $selected) {
  db_update('content_cafe_isbn_jacket')
    ->fields(
      array(
        'selected' => (int)$selected,
      )
    )
    ->condition('jacket_id', $jacket_id)
    ->execute();
}

/**
 * Update a row in the content_cafe_isbn_flap table.
 *
 * @param int $flap_id
 * @param bool $selected
 *
 * @return void
 */
function nnels_content_cafe_update_content_cafe_isbn_flap_row($flap_id, $selected) {
  db_update('content_cafe_isbn_flap')
    ->fields(
      array(
        'selected' => (int)$selected,
      )
    )
    ->condition('flap_id', $flap_id)
    ->execute();
}

/**
 * Update a row in the content_cafe_toc table.
 *
 * @param int $external_id
 * @param string $toc
 *
 * @return void
 */
function nnels_content_cafe_update_content_cafe_toc_row($external_id, $toc) {
  db_update('content_cafe_toc')
    ->fields(
      array(
        'toc' => $toc,
      )
    )
    ->condition('external_id', $external_id)
    ->execute();
}

/**
 * Update a row in the content_cafe_isbn_toc table.
 *
 * @param int $toc_id
 * @param bool $selected
 *
 * @return void
 */
function nnels_content_cafe_update_content_cafe_isbn_toc_row($toc_id, $selected) {
  db_update('content_cafe_isbn_toc')
    ->fields(
      array(
        'selected' => (int)$selected,
      )
    )
    ->condition('toc_id', $toc_id)
    ->execute();
}
