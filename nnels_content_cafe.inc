<?php

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
 * Select a row from the content_cafe_annotation table.
 *
 * @param int $external_id
 *
 * @return mixed
 */
function nnels_content_cafe_select_content_cafe_annotation_row($external_id) {
  print "Select from content_cafe_annotation\n";
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