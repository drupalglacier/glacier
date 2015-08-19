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

  // Remove some default field classes.
  if (!$vars['classes_default']) {
    $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array(
      $vars['field_name_css'],
      'field-' . $vars['field_name_css'],
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

  // Add extra field class on field collections
  if ($vars['element']['#field_type'] == 'field_collection') {
    $vars['classes_array'][] = 'c-' . $vars['field_name_css'];
  }

  // Add default field label classes.
  $vars['label_classes_array'] = array();
  if ($vars['classes_default']) {
    $vars['label_classes_array'][] = 'field-label';
  }

  // Add default field item classes.
  $vars['item_classes_array'] = array();
  if ($vars['classes_default']) {
    $vars['item_classes_array'][] = 'field-item';
  }

  // Add bundle and view mode theme hook suggestions
  $vars['theme_hook_suggestions'][] = 'field--' . $vars['bundle_class'] . '--' . $vars['field_name_css'];
  $vars['theme_hook_suggestions'][] = 'field--' . $vars['view_mode_class'] . '--' . $vars['field_name_css'];
  $vars['theme_hook_suggestions'][] = 'field--' . $vars['bundle_class'] . '--' . $vars['view_mode_class'] . '--' . $vars['field_name_css'];
}
