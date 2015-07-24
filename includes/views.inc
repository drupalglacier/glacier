<?php
/**
 * @file
 * Views-related functions.
 */

/**
 * Implements hook_preprocess_views_view().
 */
function glacier_preprocess_views_view(&$vars) {
  $bem_prefix_component = theme_get_setting('bem_prefix_component');
  $vars['bem_prefix_component'] = $bem_prefix_component;

  // Modify classes to follow SMACSS naming convention.
  $tmp_classes_array = $vars['classes_array'];
  $vars['classes_array'] = array(
    $bem_prefix_component . 'view',
    $bem_prefix_component . $vars['view']->name,
    $bem_prefix_component . $vars['view']->name . '--' . $vars['view']->current_display,
  );

  // We add back the default Views classes, regardless of SMACSS theme setting,
  // to make sure ajaxified views still work.
  $vars['classes_array'] = array_unique(array_merge($vars['classes_array'], $tmp_classes_array));
}

/**
 * Implements hook_preprocess_views_view_grid().
 */
function glacier_preprocess_views_view_grid(&$vars) {
  $bem_prefix_object = theme_get_setting('bem_prefix_object');
  $vars['bem_prefix_object'] = $bem_prefix_object;

  // Modify classes to follow SMACSS naming convention.
  $vars['class'] = preg_replace(
    array('/views-view-grid/', '/ cols-(.*?)($|\s)/'),
    array($bem_prefix_object . 'grid', ''),
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
  $bem_prefix_component = theme_get_setting('bem_prefix_component');
  $vars['bem_prefix_component'] = $bem_prefix_component;

  foreach ($vars['classes_array'] as $k => $classes) {
    $vars['classes_array'][$k] = $bem_prefix_component . 'view__row';
  }
}

/**
 * Implements hook_preprocess_views_exposed_form().
 */
function glacier_preprocess_views_exposed_form(&$vars) {
  // Create variable for SMACSS theme setting.
  $vars['bem_only'] = theme_get_setting('bem_only');
  $vars['bem_prefix_component'] = theme_get_setting('bem_prefix_component');
}
