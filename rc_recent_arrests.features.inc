<?php
/**
 * @file
 * rc_recent_arrests.features.inc
 */

/**
 * Implements hook_node_info().
 */
function rc_recent_arrests_node_info() {
  $items = array(
    'recent_arrests' => array(
      'name' => t('Recent Arrests'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
