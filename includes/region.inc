<?php
/**
 * @file
 * Region template functions.
 */

/**
 * Implements template_preprocess_region().
 */
function glacier_preprocess_region(&$vars) {
  // Remove extraneous region class.
  array_shift($vars['classes_array']);

  switch ($vars['region']) {
    // Remove classes for these regions.
    case 'page_top':
    case 'page_bottom':
      $vars['classes_array'] = array();
      break;
  }
}
