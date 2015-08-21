<?php

function glacier_classes($classes, $default_classes = array(), $state_classes = array()) {
  $classes = is_array($classes) ? $classes : array($classes);
  $default_classes = is_array($default_classes) ? $default_classes : array($default_classes);
  $state_classes = is_array($state_classes) ? $state_classes : array($state_classes);
  return implode(' ', array_merge($default_classes, $classes, $state_classes));
}

function glacier_vars_alter(&$vars, $alterations, $conditions = array()) {
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
