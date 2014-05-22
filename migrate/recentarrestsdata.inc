<?php

/**
 * @file
 * Migrates Recent Arrests nodes from D6.
 */
class RecentArrestsDataMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array(
      'field_arrest_city',
      'field_arresting_agency',
      'field_charges',
      'field_date_arrested'
    ));

    $this->addFieldMapping('field_recent_arrest_photo', 'field_recent_arrest_photo')
         ->sourceMigration('RecentArrestsFiles');
    $this->addFieldMapping('field_recent_arrest_photo:file_class')
         ->defaultValue('MigrateFileFid');
  }

  public function prepareRow($row) {
    // Respect parents filters.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Set authorship to user 1.
    $row->uid = 1;

    // Skip arrests older than 13 months.
    if (strtotime($row->field_date_arrested) < strtotime('-13 months')) {
      $this->queueMessage(
        'SKIPPED: source node ' . $row->nid . ' arrested in ' . format_date(strtotime($row->field_date_arrested)) . '.',
        MigrationBase::MESSAGE_INFORMATIONAL);
      return FALSE;
    }

    return TRUE;
  }
}
