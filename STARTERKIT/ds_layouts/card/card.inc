<?php
/**
 * @file
 * Display Suite card layout configuration.
 */

/**
 * Card layout.
 */
function ds_card() {
  return array(
    'label' => t('Card'),
    'regions' => array(
      'figure' => t('Figure'),
      'island' => t('Island'),
    ),
  );
}
