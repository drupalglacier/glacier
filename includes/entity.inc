<?php
/**
 * @file
 * Entity-related functions.
 */

/**
 * Implements hook_preprocess_entity().
 */
function glacier_preprocess_entity(&$vars, $hook) {
  $type_class = drupal_html_class($vars['elements']['#entity_type']);
  $bundle_class = drupal_html_class($vars['elements']['#bundle']);
  $view_mode_class = drupal_html_class($vars['elements']['#view_mode']);
  $bem_only = theme_get_setting('bem_only');
  $bem_prefix_component = theme_get_setting('bem_prefix_component');

  // Create entity type preprocess functions (e.g., field collections).
  $function = 'glacier_preprocess_' . $vars['entity_type'];
  if (function_exists($function)) {
    $function($vars, $hook);
  }

  // Remove some default entity classes.
  if ($bem_only) {
    $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array(
      'entity',
      'entity-' . $type_class,
      $type_class . '-' . $bundle_class,
    )));
  }

  // Add default entity attributes.
  $vars['classes_array'][] = $bem_prefix_component . $type_class;
  $vars['classes_array'][] = $bem_prefix_component . $type_class . '--' . $bundle_class;
  $vars['classes_array'][] = $bem_prefix_component . $type_class . '--' . $view_mode_class;
  $vars['title_attributes_array']['class'][] = $bem_prefix_component . $type_class . '__title';
  $vars['content_attributes_array']['class'][] = $bem_prefix_component . $type_class . '__content';
}
