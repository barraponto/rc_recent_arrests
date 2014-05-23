<?php

/**
 * @file
 * Migrate API
 */

/**
 * Implements hook_migrate_api().
 */
function rc_recent_arrests_migrate_api() {
  return array(
    'api' => 2,
    'groups' => array(
      'rc_recent_arrests' => array(
        'title' => t('Recent Arrests'),
      ),
    ),
    'migrations' => array(
      'RecentArrestsData' => array(
        'class_name' => 'RecentArrestsDataMigration',
        'group_name' => 'rc_recent_arrests',
        'description' => t('Brings Recent Arrests data from D6 site.'),
        'source_version' => 6,
        'source_connection' => 'legacy',
        'source_type' => 'recent_arrests',
        'destination_type' => 'recent_arrests',
        'default_uid' => 1,
        'dependencies' => array(
          'RecentArrestsFiles',
        ),
      ),
      'RecentArrestsFiles' => array(
        'class_name' => 'RecentArrestsFilesMigration',
        'group_name' => 'rc_recent_arrests',
        'description' => t('Brings Recent Arrests files from D6 site.'),
        'source_version' => 6,
        'source_connection' => 'legacy',
        'source_dir' => variable_get('file_public_path', conf_path() . '/files') . '/recent-arrests',
        'default_uid' => 1,
      ),
    ),
  );
}
