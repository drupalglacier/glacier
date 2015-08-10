<?php
/**
 * @file
 * Field-related functions.
 */

/**
 * Implements hook_preprocess_field().
 */
function glacier_preprocess_field(&$vars) {
  // Add setting variables.
  $vars['classes_default'] = theme_get_setting('classes_default');
  $vars['prefix_component'] = theme_get_setting('prefix_component');
  $vars['prefix_utility'] = theme_get_setting('prefix_utility');

  // Remove some default field classes.
  if (!$vars['classes_default']) {
    $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array(
      $vars['field_name_css'],
      'field-name-' . $vars['field_name_css'],
      'field-type-' . $vars['field_type_css'],
      'field-label-above',
      'field-label-hidden',
      'field-label-inline',
      'inline',
    )));
  }

  // Add bundle class variable.
  $bundle_name = preg_replace('/^field_/', '', $vars['element']['#bundle']); // Remove 'field_' prefix from field collection bundles.
  $vars['bundle_class'] = drupal_html_class($bundle_name);

  // Add label display variable.
  $vars['label_display'] = $vars['element']['#label_display'];

  // Add wrapper hidden variable.
  $vars['wrapper_hidden'] = FALSE;
  if ($vars['label_hidden']) {
    $vars['wrapper_hidden'] = TRUE;
  }

  // Remove 'field-' prefix from field name css.
  $vars['field_name_css'] = preg_replace('/^field-/', '', $vars['field_name_css']);

  // Add default classes.
  $vars['default_classes'] = $vars['classes_array'];

  // Add default field label classes.
  $vars['default_label_classes'] = array();
  if ($vars['classes_default']) {
    $vars['default_label_classes'][] = 'field-label';
  }

  // Add default field item classes.
  $vars['default_item_classes'] = array();
  if ($vars['classes_default']) {
    $vars['default_label_classes'][] = 'field-item';
  }
}
