<?php
/**
 * @file
 * Entity-related functions.
 */

/**
 * Implements template_preprocess_entity().
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

  // Create entity type preprocess functions (e.g., field collections).
  $function = 'glacier_preprocess_' . $vars['entity_type'];
  if (function_exists($function)) {
    $function($vars, $hook);
  }

  // Move Drupal default classes in a separate array.
  $vars['default_classes_array'] = $vars['classes_array'];
  $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array(
    'entity',
    'entity-' . $vars['type_class'],
    $vars['type_class'] . '-' . $vars['bundle_class'],
  )));
  // Fallback class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_classes_array'] = array('c-entity');
  // Add glacier classes.
  $vars['glacier_classes_array'] = array(
    'c-entity',
    'c-' . $vars['type_class'] . '-' . $vars['bundle_class'],
  );

  // Fallback title class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_title_classes_array'] = array('c-entity__title');
  // Add default Drupal title classes.
  $vars['title_attributes_array']['class'] = isset($vars['title_attributes_array']['class']) ? $vars['title_attributes_array']['class'] : array();
  $vars['default_title_classes_array'] = $vars['title_attributes_array']['class'];
  unset($vars['title_attributes_array']['class']);
  $vars['title_classes_array'] = array();
  // Add glacier title classes.
  $vars['glacier_title_classes_array'] = array(
    'c-entity__title',
    'c-' . $vars['type_class'] . '-' . $vars['bundle_class'] . '__title',
  );

  // Fallback content class if glacier and Drupal
  // default classes are disabled in the theme settings.
  $vars['fallback_content_classes_array'] = array('c-entity__content');
  // Add default Drupal content classes.
  $vars['content_attributes_array']['class'] = isset($vars['content_attributes_array']['class']) ? $vars['content_attributes_array']['class'] : array();
  $vars['default_content_classes_array'] = $vars['content_attributes_array']['class'];
  unset($vars['content_attributes_array']['class']);
  $vars['content_classes_array'] = array();
  // Add glacier content classes.
  $vars['glacier_content_classes_array'] = array(
    'c-entity__content',
    'c-' . $vars['type_class'] . '-' . $vars['bundle_class'] . '__content',
  );
}
