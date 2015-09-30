<?php
/**
 * @file
 * Display Suite media layout configuration.
 */

/**
 * Media layout.
 */
function ds_media() {
  return array(
    'label' => t('Media'),
    'regions' => array(
      'header' => t('Header'),
      'figure' => t('Figure'),
      'body' => t('Body'),
      'footer' => t('Footer'),
    ),
  );
}
