<?php
/**
 * @file
 * Display Suite media-rev layout configuration.
 */

/**
 * Reversed media layout.
 */
function ds_media_rev() {
  return array(
    'label' => t('Media reversed'),
    'regions' => array(
      'header' => t('Header'),
      'body' => t('Body'),
      'figure' => t('Figure'),
      'footer' => t('Footer'),
    ),
  );
}
