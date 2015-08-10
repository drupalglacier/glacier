<?php

function glacier_classes($classes, $default_classes = array(), $state_classes = array()) {
  $classes = is_array($classes) ? $classes : array($classes);
  $default_classes = is_array($default_classes) ? $default_classes : array($default_classes);
  $state_classes = is_array($state_classes) ? $state_classes : array($state_classes);
  return implode(' ', array_merge($default_classes, $classes, $state_classes));
}
