<?php
/**
 * @file
 * Glacier system functions.
 */

/**
 * Helper function to alter $vars arrays.
 *
 * @param array &$vars
 *   Default variables.
 * @param array $alterations
 *   A list of alterations to apply to $vars.
 * @param array $conditions
 *   Conditions that must be met to apply the alterations.
 */
function glacier_vars_alter(&$vars = array(), $alterations = array(), $conditions = array()) {
  if (isset($vars['element'])) {
    $element = $vars['element'];
  }
  elseif (isset($vars['elements'])) {
    $element = $vars['elements'];
  }
  elseif (isset($vars['view'])) {
    $element = (array) $vars['view'];
  }
  else {
    return;
  }

  $condition_array = $element;

  if (isset($element['#block'])) {
    $condition_array = (array) $element['#block'];
  }

  // Check conditions.
  foreach ($conditions as $condition_type => $value) {
    $value = is_array($value) ? $value : array($value);
    if (!isset($condition_array[$condition_type]) || !in_array($condition_array[$condition_type], $value)) {
      // Skip alterations if conditions aren't met.
      return;
    }
  }

  foreach ($alterations as $alteration_element => $alteration_value) {
    if (isset($vars[$alteration_element])) {
      $vars[$alteration_element] = is_array($alterations[$alteration_element]) ? array_merge($vars[$alteration_element], $alteration_value) : $alteration_value;
    }
  }
}

/**
 * Implements template_process().
 */
function glacier_process(&$vars, $hook) {
  // Set ARIA role "article" if the wrapper tag is "article".
  if (isset($vars['wrapper_tag']) && $vars['wrapper_tag'] == 'article') {
    $vars['attributes_array']['role'] = 'article';
  }

  // Merge classes in consideration of the theme settings.
  // If the output of glacier or drupal default classes is disabled
  // the relevant classes will not be merged in the final classes array.
  $classes_types = array(
    NULL,
    'title',
    'form_title',
    'content',
    'label',
    'item',
    'header',
    'filters',
    'attachment_before',
    'attachment_after',
    'pager',
    'more',
    'footer',
  );

  foreach ($classes_types as $classes_type) {
    $classes_key = (isset($classes_type) ? $classes_type . '_' : NULL) . 'classes';
    $classes_array_key = $classes_key . '_array';
    $glacier_classes_array_key = 'glacier_' . $classes_array_key;
    $default_classes_array_key = 'default_' . $classes_array_key;
    $fallback_classes_array_key = 'fallback_' . $classes_array_key;

    if (isset($vars[$classes_array_key])) {
      // Add the glacier classes to the classes array.
      if (isset($vars[$glacier_classes_array_key]) && isset($vars['classes_glacier']) && $vars['classes_glacier']) {
        $vars[$classes_array_key] = array_merge($vars[$glacier_classes_array_key], $vars[$classes_array_key]);
      }
      // Add the Drupal default classes to the classes array.
      if (isset($vars[$default_classes_array_key]) && isset($vars['classes_default']) && $vars['classes_default']) {
        $vars[$classes_array_key] = array_merge($vars[$classes_array_key], $vars[$default_classes_array_key]);
      }
      // Set the fallback classes if the classes array is empty.
      if (empty($vars[$classes_array_key]) && isset($vars[$fallback_classes_array_key])) {
        $vars[$classes_array_key] = $vars[$fallback_classes_array_key];
      }

      // Generate the classes string to use in tpl files.
      $vars[$classes_key] = implode(' ', $vars[$classes_array_key]);
    }
  }
}

/**
 * Fix double hyphens (converted from double underscores).
 */
function _glacier_fix_double_underscore_classes($classes_array = array()) {
  // If there is only one class it's safe to just convert
  // the double hyphens to underscores because a modifier class
  // always needs a base class, if there is no base class there
  // can't be a modifier class.
  if (count($classes_array) == 1) {
    return str_replace('--', '__', $classes_array);
  }

  // Search for a matching base class, convert hyphens if none is found.
  foreach ($classes_array as $k => $class) {
    if (strpos($class, '--') !== FALSE) {
      $test_class = preg_replace('/--(.*?)$/', '', $class);
      if (!in_array($test_class, $classes_array)) {
        $class = str_replace('--', '__', $class);
      }
    }
    $classes_array[$k] = $class;
  }
  return $classes_array;
}
