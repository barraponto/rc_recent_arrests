<?php

/**
 * @file
 * Migrates Recent Arrests nodes from D6.
 */
class RecentArrestsFilesMigration extends DrupalFile6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }

  public function prepareRow($row) {
    // Respect parents filters.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Set authorship to user 1.
    $row->uid = 1;

    $fids = &drupal_static(__METHOD__);

    // Get only the Recent Arrests fids.
    if (!isset($fids)) {
      $fids = array_map(
        function($row) {
          return $row->field_recent_arrest_photo_fid;
        },
        Database::getConnection('default', 'legacy')
          ->select('content_type_recent_arrests', 'ra_old')
          ->fields('ra_old', array('field_recent_arrest_photo_fid'))
          ->execute()
          ->fetchAll()
        );
    }

    // Else skip it.
    return in_array($row->fid, $fids);
  }
}
