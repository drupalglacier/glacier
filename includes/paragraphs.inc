<?php
/**
 * @file
 * Paragraphs-related functions.
 */

function glacier_paragraphs_item_type_class_alter(&$vars, $hook) {
  return 'paragraph';
}