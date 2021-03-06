<?php
/**
 * @file
 * Aggregator-related functions.
 */

/**
 * Implements template_preprocess_aggregator_item().
 */
function glacier_preprocess_aggregator_item(&$vars) {
  $item = $vars['item'];

  // Create datetime variable for <time> element.
  $vars['datetime'] = format_date($item->timestamp, 'custom', 'c');
}
