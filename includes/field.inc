<?php
/**
 * @file
 * Field-related functions.
 */

/**
 * Implements template_preprocess_field().
 */
function glacier_preprocess_field(&$vars) {
  // Add setting variables.
  $vars['classes_glacier'] = theme_get_setting('classes_glacier');
  $vars['classes_default'] = theme_get_setting('classes_default');

  // Hide the item wrapper by default if the label is hidden
  // and the field is no multi value field.
  $vars['item_wrapper_hidden'] = $vars['label_hidden'] && count($vars['items']) <= 1;

  // Add label display variable.
  $vars['label_display'] = $vars['element']['#label_display'];

  // Set class variables to use in the glacier base classes.
  $vars['field_name_class'] = preg_replace('/^field-/', '', $vars['field_name_css']);
  $vars['field_type_class'] = drupal_html_class($vars['element']['#field_type']);
  $vars['bundle_class'] = drupal_html_class(preg_replace('/^field_/', '', $vars['element']['#bundle'])); // Remove 'field_' prefix from field collection (and possibly other) bundles.
  $vars['view_mode_class'] = drupal_html_class($vars['element']['#view_mode']);

  // Move Drupal default classes in a separate array.
  $vars['default_classes_array'] = $vars['classes_array'];
  $vars['classes_array'] = array();
  // Falback class if glacier and Drupal default classes are disabled in the theme settings.
  $vars['fallback_classes_array'] = array('c-field');
  // Add glacier classes.
  $vars['glacier_classes_array'] = array(
    'c-field',
    'c-field--' . $vars['field_name_class'],
    'c-field--' . $vars['field_type_class'],
    'c-' . $vars['bundle_class'] . '__' . $vars['field_name_class'],
  );
  // Add extra field class on field collections.
  if ($vars['element']['#field_type'] == 'field_collection') {
    $vars['glacier_classes_array'][] = 'c-' . $vars['field_name_class'];
  }

  // Falback label class if glacier and Drupal default classes are disabled in the theme settings.
  $vars['fallback_label_classes_array'] = array('c-field__label');
  // Add default Drupal label classes.
  $vars['default_label_classes_array'] = array('field-label');
  $vars['label_classes_array'] = array();
  // Add glacier label classes.
  $vars['glacier_label_classes_array'] = array(
    'c-field__label',
    'c-field--' . $vars['field_name_class'] . '__label',
    'c-field--' . $vars['field_type_class'] . '__label',
    'c-' . $vars['bundle_class'] . '__' . $vars['field_name_class'] . '__label',
  );
  // Add variables to control the output of a colon after the label.
  $vars['label_display_above_add_colon'] = FALSE;
  $vars['label_display_inline_add_colon'] = TRUE;
  // Add a utility class to display the field label inline.
  if ($vars['label_display'] == 'inline') {
    $vars['glacier_label_classes_array'][] = 'u-display-inline';
  }

  // Falback item class if glacier and Drupal default classes are disabled in the theme settings.
  $vars['fallback_item_classes_array'] = array('c-field__item');
  // Add default Drupal item classes.
  $vars['default_item_classes_array'] = array('field-item');
  $vars['item_classes_array'] = array();
  // Add glacier item classes.
  $vars['glacier_item_classes_array'] = array(
    'c-field__item',
    'c-field--' . $vars['field_name_class'] . '__item',
    'c-field--' . $vars['field_type_class'] . '__item',
    'c-' . $vars['bundle_class'] . '__' . $vars['field_name_class'] . '__item',
  );
  // Add a utility class to display the field item inline-block
  // if the label is displayed as inline element.
  if ($vars['label_display'] == 'inline') {
    $vars['glacier_item_classes_array'][] = 'u-display-inline-block';
  }
}

/**
 * Implements template_process_field().
 */
function glacier_process_field(&$vars, $hook) {
  if ($vars['label_display'] == 'inline' && $vars['label_display_inline_add_colon']) {
    // Add a colon to inline labels.
    $vars['label'] .= ':';
  } elseif ($vars['label_display'] == 'above' && $vars['label_display_above_add_colon']) {
    // Add a colon to above labels.
    $vars['label'] .= ':';
  }
}
