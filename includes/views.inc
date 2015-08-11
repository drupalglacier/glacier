<?php
/**
 * @file
 * Views-related functions.
 */

/**
 * Implements hook_preprocess_views_view().
 */
function glacier_preprocess_views_view(&$vars) {
  // Modify classes to follow SMACSS naming convention.
  $tmp_classes_array = $vars['classes_array'];
  $vars['classes_array'] = array(
    'c-view',
    'c-' . $vars['view']->name,
    'c-' . $vars['view']->name . '--' . $vars['view']->current_display,
  );

  // We add back the default Views classes, regardless of SMACSS theme setting,
  // to make sure ajaxified views still work.
  $vars['classes_array'] = array_unique(array_merge($vars['classes_array'], $tmp_classes_array));
}

/**
 * Implements hook_preprocess_views_view_grid().
 */
function glacier_preprocess_views_view_grid(&$vars) {
  // Modify classes to follow SMACSS naming convention.
  $vars['class'] = preg_replace(
    array('/views-view-grid/', '/ cols-(.*?)($|\s)/'),
    array('o-grid', ''),
    $vars['class']
  );
  foreach ($vars['column_classes'] as $key => $value) {
    $vars['column_classes'][$key] = preg_replace('/col-(.*?)($|\s)/', '', $vars['column_classes'][$key]);
  }
}

/**
 * Implements hook_preprocess_views_view_unformatted().
 */
function glacier_preprocess_views_view_unformatted(&$vars) {
  foreach ($vars['classes_array'] as $k => $classes) {
    $vars['classes_array'][$k] = 'c-view__row';
  }
}

/**
 * Implements hook_preprocess_views_exposed_form().
 */
function glacier_preprocess_views_exposed_form(&$vars) {
  // Create variable for SMACSS theme setting.
  $vars['bem_only'] = theme_get_setting('bem_only');
}
