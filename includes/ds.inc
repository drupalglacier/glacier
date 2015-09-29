<?php
/**
 * @file
 * Display Suite related functions.
 */

/**
 * Implements hook_ds_pre_render_alter().
 */
function glacier_ds_pre_render_alter(&$layout_render_array, $context, &$vars) {
  // Remove empty array items.
  $vars['classes_array'] = array_filter($vars['classes_array']);
  // Remove default view mode class.
  $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array(
    'view-mode-' . $vars['view_mode_class'],
  )));
}
