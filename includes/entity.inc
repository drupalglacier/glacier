<?php
/**
 * @file
 * Entity-related functions.
 */

/**
 * Implements hook_preprocess_entity().
 */
function glacier_preprocess_entity(&$vars, $hook) {
  // Add setting variables.
  $vars['classes_default'] = theme_get_setting('classes_default');

  // Add type bundle and view mode classes.
  $vars['type_class'] = drupal_html_class($vars['elements']['#entity_type']);
  $vars['bundle_class'] = drupal_html_class($vars['elements']['#bundle']);
  $vars['view_mode_class'] = drupal_html_class($vars['elements']['#view_mode']);

  // Remove some default entity classes.
  if (!$vars['classes_default']) {
    $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array(
      'entity',
      'entity-' . $vars['type_class'],
      $vars['type_class'] . '-' . $vars['bundle_class'],
    )));
  }

  // Make it possible to alter the type, bundle and view mode class on a entity type basis.
  $function = 'glacier_' . $vars['entity_type'] . '_type_class_alter';
  if (function_exists($function)) {
    $vars['type_class'] = $function($vars, $hook);
  }

  $function = 'glacier_' . $vars['entity_type'] . '_bundle_class_alter';
  if (function_exists($function)) {
    $vars['bundle_class'] = $function($vars, $hook);
  }

  $function = 'glacier_' . $vars['entity_type'] . '_view_mode_class_alter';
  if (function_exists($function)) {
    $vars['view_mode_class'] = $function($vars, $hook);
  }

  // Create entity type preprocess functions (e.g., field collections).
  $function = 'glacier_preprocess_' . $vars['entity_type'];
  if (function_exists($function)) {
    $function($vars, $hook);
  }

  // Add defaul title classes.
  $vars['title_attributes_array']['class'] = isset($vars['title_attributes_array']['class']) ? $vars['title_attributes_array']['class'] : array();
  $vars['title_classes_array'] = $vars['title_attributes_array']['class'];
  unset($vars['title_attributes_array']['class']);

  // Add defaul content classes.
  $vars['content_attributes_array']['class'] = isset($vars['content_attributes_array']['class']) ? $vars['content_attributes_array']['class'] : array();
  $vars['content_classes_array'] = $vars['content_attributes_array']['class'];
  unset($vars['content_attributes_array']['class']);
}
