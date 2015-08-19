<?php

function glacier_classes($classes, $default_classes = array(), $state_classes = array()) {
  $classes = is_array($classes) ? $classes : array($classes);
  $default_classes = is_array($default_classes) ? $default_classes : array($default_classes);
  $state_classes = is_array($state_classes) ? $state_classes : array($state_classes);
  return implode(' ', array_merge($default_classes, $classes, $state_classes));
}

function glacier_vars_alter(&$vars, $alterations, $conditions = array()) {
  $element = isset($vars['element']) ? $vars['element'] : $vars['elements'];

  // Check conditions.
  foreach ($conditions as $condition_type => $value) {
    if (!isset($element[$condition_type]) || $element[$condition_type] != $value) {
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
