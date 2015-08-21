<?php

// DEPR //
function glacier_classes($classes, $default_classes = array(), $state_classes = array()) {
  $classes = is_array($classes) ? $classes : array($classes);
  $default_classes = is_array($default_classes) ? $default_classes : array($default_classes);
  $state_classes = is_array($state_classes) ? $state_classes : array($state_classes);
  return implode(' ', array_merge($default_classes, $classes, $state_classes));
}
// DEPR //

/**
 * Merge classes in consideration of the theme settings.
 *
 * If the output of glacier or drupal default classes is disabled
 * the relevant classes will not be merged in the final classes array.
 *
 * @param  array  $glacier_classes_array  glacier default classes (BEM syntax).
 * @param  array  $default_classes_array  Drupal default classes.
 * @param  mixed  $fallback_classes_array Fallback classes in case of glacier and drupal classes are disabled.
 * @return array                          A array of classes for theming
 */
function glacier_class_merge($glacier_classes_array = array(), $default_classes_array = array(), $fallback_classes_array = array()) {
  $add_glacier_classes = theme_get_setting('classes_glacier');
  $add_default_classes = theme_get_setting('classes_default');

  $glacier_classes_array = is_array($glacier_classes_array) ? $glacier_classes_array : array($glacier_classes_array);
  $default_classes_array = is_array($default_classes_array) ? $default_classes_array : array($default_classes_array);
  $fallback_classes_array = is_array($fallback_classes_array) ? $fallback_classes_array : array($fallback_classes_array);

  $classes_array = array();

  if ($add_glacier_classes) {
    $classes_array = $glacier_classes_array;
  }
  if ($add_default_classes) {
    $classes_array = array_merge($classes_array, $default_classes_array);
  }

  return !empty($classes_array) ? $classes_array : $fallback_classes_array;
}

/**
 * Helper function to alter $vars arrays.
 *
 * @param  array  &$vars
 * @param  array  $alterations A list of alterations to apply to $vars.
 * @param  array  $conditions  Conditions that must be met to apply the alterations.
 * @return mixed               void if no match or $vars type not supported / no return otherwise.
 */
function glacier_vars_alter(&$vars, $alterations = array(), $conditions = array()) {
  if (isset($vars['element'])) {
    $element = $vars['element'];
  } elseif (isset($vars['elements'])) {
    $element = $vars['elements'];
  } elseif (isset($vars['view'])) {
    $element = (array) $vars['view'];
  } else {
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
