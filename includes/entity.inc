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
  $vars['classes_glacier'] = theme_get_setting('classes_glacier');
  $vars['classes_default'] = theme_get_setting('classes_default');

  // Hide the content wrapper by default if the subject is empty.
  $vars['content_wrapper_hidden'] = empty($vars['title']);

  // Add title tag variable.
  $vars['title_tag'] = 'h2';

  // Set class variables to use in the glacier base classes.
  $vars['type_class'] = drupal_html_class($vars['elements']['#entity_type']);
  $vars['bundle_class'] = drupal_html_class($vars['elements']['#bundle']);
  $vars['view_mode_class'] = drupal_html_class($vars['elements']['#view_mode']);

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

  // Move Drupal default classes in a separate array.
  $vars['default_classes_array'] = $vars['classes_array'];
  $vars['classes_array'] = array();
  // Fallback class if glacier and Drupal default classes are disabled in the theme settings.
  $vars['fallback_classes_array'] = array('c-entity');
  // Add glacier classes.
  $vars['glacier_classes_array'] = array(
    'c-entity',
    'c-' . $vars['bundle_class'] . '-entity',
  );

  // Fallback title class if glacier and Drupal default classes are disabled in the theme settings.
  $vars['fallback_title_classes_array'] = array('c-entity__title');
  // Add default Drupal title classes.
  $vars['title_attributes_array']['class'] = isset($vars['title_attributes_array']['class']) ? $vars['title_attributes_array']['class'] : array();
  $vars['default_title_classes_array'] = $vars['title_attributes_array']['class'];
  unset($vars['title_attributes_array']['class']);
  $vars['title_classes_array'] = array();
  // Add glacier title classes.
  $vars['glacier_title_classes_array'] = array(
    'c-entity__title',
    'c-' . $vars['bundle_class'] . '-entity__title',
  );

  // Fallback content class if glacier and Drupal default classes are disabled in the theme settings.
  $vars['fallback_content_classes_array'] = array('c-block__content');
  // Add default Drupal content classes.
  $vars['content_attributes_array']['class'] = isset($vars['content_attributes_array']['class']) ? $vars['content_attributes_array']['class'] : array();
  $vars['default_content_classes_array'] = $vars['content_attributes_array']['class'];
  unset($vars['content_attributes_array']['class']);
  $vars['content_classes_array'] = array();
  // Add glacier content classes.
  $vars['glacier_content_classes_array'] = array(
    'c-entity__content',
    'c-' . $vars['bundle_class'] . '-entity__content',
  );
}
