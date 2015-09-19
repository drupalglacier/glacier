<?php
/**
 * @file
 * Display Suite media layout configuration.
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
