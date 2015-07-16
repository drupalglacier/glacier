<?php
/**
 * @file
 * Field collection-related functions.
 */

/**
 * Implements template_preprocess_field_collection_item().
 */
function glacier_preprocess_field_collection_item(&$vars) {
  // Add theme hook suggestions based on view mode.
  $vars['theme_hook_suggestions'][] = 'field_collection_item__' . $vars['view_mode'];
}

/**
 * Returns HTML for field collection items.
 */
function glacier_field_collection_view($vars) {
  // Don't output wrapper markup.
  return $vars['element']['#children'];
}
