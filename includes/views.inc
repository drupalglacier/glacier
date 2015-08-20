<?php
/**
 * @file
 * Views-related functions.
 */

/**
 * Implements template_preprocess_views_view().
 */
function glacier_preprocess_views_view(&$vars) {
  // Modify classes to follow SMACSS naming convention.
  $tmp_classes_array = $vars['classes_array'];
  $vars['classes_array'] = array(
    'c-view',
    'c-view-' . $vars['view']->name,
    'c-view-' . $vars['view']->name . '--' . $vars['view']->current_display,
  );
  // We add back the default Views classes, regardless of SMACSS theme setting,
  // to make sure ajaxified views still work.
  $vars['classes_array'] = array_unique(array_merge($vars['classes_array'], $tmp_classes_array));

  // Header classes.
  $vars['header_classes_array'] = array(
    'c-view__header',
    'c-view-' . $vars['view']->name . '__header',
  );

  // Filters classes.
  $vars['filters_classes_array'] = array(
    'c-view__filters',
    'c-view-' . $vars['view']->name . '__filters',
  );

  // Attachment before classes.
  $vars['attachment_before_classes_array'] = array(
    'c-view__attachment-before',
    'c-view-' . $vars['view']->name . '__attachment-before',
  );

  // Content classes.
  $vars['content_classes_array'] = array(
    'c-view__content',
    'c-view-' . $vars['view']->name . '__content',
  );
  if (isset($vars['empty'])) {
    $vars['content_classes_array'][] = 'is-empty';
  }

  // Pager classes.
  $vars['pager_classes_array'] = array(
    'c-view__pager',
    'c-view-' . $vars['view']->name . '__pager',
  );

  // Attachment after classes.
  $vars['attachment_after_classes_array'] = array(
    'c-view__attachment-after',
    'c-view-' . $vars['view']->name . '__attachment-after',
  );

  // Filters classes.
  $vars['more_classes_array'] = array(
    'c-view__more',
    'c-view-' . $vars['view']->name . '__more',
  );

  // Filters classes.
  $vars['footer_classes_array'] = array(
    'c-view__footer',
    'c-view-' . $vars['view']->name . '__footer',
  );
}

/**
 * Implements template_process_views_view().
 */
function glacier_process_views_view(&$vars) {
  // Flatten the classes to a string for the template file.
  $vars['header_classes'] = implode(' ', $vars['header_classes_array']);
  $vars['filters_classes'] = implode(' ', $vars['filters_classes_array']);
  $vars['attachment_before_classes'] = implode(' ', $vars['attachment_before_classes_array']);
  $vars['content_classes'] = implode(' ', $vars['content_classes_array']);
  $vars['pager_classes'] = implode(' ', $vars['pager_classes_array']);
  $vars['attachment_after_classes'] = implode(' ', $vars['attachment_after_classes_array']);
  $vars['more_classes'] = implode(' ', $vars['more_classes_array']);
  $vars['footer_classes'] = implode(' ', $vars['footer_classes_array']);
}

/**
 * Implements template_preprocess_views_view_grid().
 */
function glacier_preprocess_views_view_grid(&$vars) {
  // Modify classes to follow SMACSS naming convention.
  $vars['classes'] = preg_replace(
    array('/views-view-grid/', '/ cols-(.*?)($|\s)/'),
    array('o-grid', ''),
    $vars['class']
  );
  foreach ($vars['column_classes'] as $key => $value) {
    $vars['column_classes'][$key] = preg_replace('/col-(.*?)($|\s)/', '', $vars['column_classes'][$key]);
  }
}

/**
 * Implements template_preprocess_views_view_unformatted().
 */
function glacier_preprocess_views_view_unformatted(&$vars) {
  $vars['classes_array'] = str_replace(
    array('views-row-', 'views-row'),
    array('is-', 'c-view__row c-view-' . $vars['view']->name . '__row'),
    $vars['classes_array']
  );
}

/**
 * Implements template_preprocess_views_exposed_form().
 */
function glacier_preprocess_views_exposed_form(&$vars) {
  $vars['classes_default'] = theme_get_setting('classes_default');
}
