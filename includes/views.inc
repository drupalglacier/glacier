<?php
/**
 * @file
 * Views-related functions.
 */

/**
 * Implements template_preprocess_views_view().
 */
function glacier_preprocess_views_view(&$vars) {
  // Add setting variables.
  $vars['classes_glacier'] = theme_get_setting('classes_glacier');
  // We keep the default Views classes, regardless of theme setting,
  // if ajax is enabled in the view.
  $vars['classes_default'] = theme_get_setting('classes_default') || $vars['view']->use_ajax;

  // Hide the content wrapper by default if the subject is empty.
  $vars['content_wrapper_hidden'] = empty($vars['title']);

  // Set class variables to use in the glacier base classes.
  $vars['name_class'] = drupal_html_class($vars['view']->name);
  $vars['current_display_class'] = drupal_html_class($vars['view']->current_display);

  // Move Drupal default classes in a separate array.
  $vars['default_classes_array'] = $vars['classes_array'];
  // Add custom classes (entered in the UI) to the classes array.
  $vars['classes_array'] = explode(' ', $vars['css_class']);
  // Fallback class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_classes_array'] = array('c-view');
  // Add glacier classes.
  $vars['glacier_classes_array'] = array(
    'c-view',
    'c-view-' . $vars['name_class'],
    'c-view-' . $vars['name_class'] . '--' . $vars['current_display_class'],
  );

  // Fallback header class if glacier and Drupal
  // default classes are disabled in the theme settings.
  $vars['fallback_header_classes_array'] = array('c-view__header');
  // Add default Drupal header classes.
  $vars['default_header_classes_array'] = array('view-header');
  $vars['header_classes_array'] = array();
  // Add glacier header classes.
  $vars['glacier_header_classes_array'] = array(
    'c-view__header',
    'c-view-' . $vars['name_class'] . '__header',
  );

  // Fallback filters class if glacier and Drupaldefault
  // classes are disabled in the theme settings.
  $vars['fallback_filters_classes_array'] = array('c-view__filters');
  // Add default Drupal filters classes.
  $vars['default_filters_classes_array'] = array('view-filters');
  $vars['filters_classes_array'] = array();
  // Add glacier filters classes.
  $vars['glacier_filters_classes_array'] = array(
    'c-view__filters',
    'c-view-' . $vars['name_class'] . '__filters',
  );

  // Fallback attachment before class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_attachment_before_classes_array'] = array('c-view__attachment-before');
  // Add default Drupal attachment before classes.
  $vars['default_attachment_before_classes_array'] = array('attachment', 'attachment-before');
  $vars['attachment_before_classes_array'] = array();
  // Add glacier attachment before classes.
  $vars['glacier_attachment_before_classes_array'] = array(
    'c-view__attachment-before',
    'c-view-' . $vars['name_class'] . '__attachment-before',
  );

  // Fallback content class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_content_classes_array'] = array('c-view__content');
  // Add default Drupal content classes.
  $vars['default_content_classes_array'] = array('view-content');
  $vars['content_classes_array'] = array();
  // Add glacier content classes.
  $vars['glacier_content_classes_array'] = array(
    'c-view__content',
    'c-view-' . $vars['name_class'] . '__content',
  );
  // Add state classes.
  if (isset($vars['empty'])) {
    $vars['content_classes_array'][] = 'is-empty';
    $vars['default_content_classes_array'] = array('view-empty');
  }

  // Fallback pager class if glacier and Drupal default classes
  // are disabled in the theme settings.
  $vars['fallback_pager_classes_array'] = array('c-view__pager');
  // Add default Drupal pager classes.
  $vars['default_pager_classes_array'] = array('view-pager');
  $vars['pager_classes_array'] = array();
  // Add glacier pager classes.
  $vars['glacier_pager_classes_array'] = array(
    'c-view__pager',
    'c-view-' . $vars['name_class'] . '__pager',
  );

  // Fallback attachment after class if glacier and Drupal
  // defaultclasses are disabled in the theme settings.
  $vars['fallback_attachment_after_classes_array'] = array('c-view__attachment-after');
  // Add default Drupal attachment after classes.
  $vars['default_attachment_after_classes_array'] = array('attachment', 'attachment-after');
  $vars['attachment_after_classes_array'] = array();
  // Add glacier attachment after classes.
  $vars['glacier_attachment_after_classes_array'] = array(
    'c-view__attachment-after',
    'c-view-' . $vars['name_class'] . '__attachment-after',
  );

  // Fallback more class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_more_classes_array'] = array('c-view__more');
  // Add default Drupal more classes.
  $vars['default_more_classes_array'] = array('view-more');
  $vars['more_classes_array'] = array();
  // Add glacier more classes.
  $vars['glacier_more_classes_array'] = array(
    'c-view__more',
    'c-view-' . $vars['name_class'] . '__more',
  );

  // Fallback footer class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_footer_classes_array'] = array('c-view__footer');
  // Add default Drupal footer classes.
  $vars['default_footer_classes_array'] = array('view-footer');
  $vars['footer_classes_array'] = array();
  // Add glacier footer classes.
  $vars['glacier_footer_classes_array'] = array(
    'c-view__footer',
    'c-view-' . $vars['name_class'] . '__footer',
  );
}

/**
 * Implements template_preprocess_views_view_grid().
 */
function glacier_preprocess_views_view_grid(&$vars) {
  // Add setting variables.
  $vars['classes_glacier'] = theme_get_setting('classes_glacier');
  // We keep the default Views classes, regardless of theme setting,
  // if ajax is enabled in the view.
  $vars['classes_default'] = theme_get_setting('classes_default') || $vars['view']->use_ajax;

  // Fallback class if glacier and Drupal default classes
  // are disabled in the theme settings.
  $vars['fallback_classes_array'] = array('o-grid');
  // Add default Drupal classes.
  $vars['default_classes_array'] = array($vars['class']);
  $vars['classes_array'] = array();
  // Add glacier classes.
  $vars['glacier_classes_array'] = array(
    preg_replace(
      array('/views-view-grid/', '/ cols-(.*?)($|\s)/'),
      array('o-grid', ''),
      $vars['class']
    ),
  );

  foreach ($vars['column_classes'] as $key => $value) {
    $vars['column_classes'][$key] = preg_replace('/col-(.*?)($|\s)/', '', $vars['column_classes'][$key]);
  }
}

/**
 * Implements template_preprocess_views_view_unformatted().
 */
function glacier_preprocess_views_view_unformatted(&$vars) {
  // Add setting variables.
  $vars['classes_glacier'] = theme_get_setting('classes_glacier');
  // We keep the default Views classes, regardless of theme setting,
  // if ajax is enabled in the view.
  $vars['classes_default'] = theme_get_setting('classes_default') || $vars['view']->use_ajax;

  // Set class variables to use in the glacier base classes.
  $vars['name_class'] = drupal_html_class($vars['view']->name);

  // Add classes.
  $vars['classes_array'] = str_replace(
    array('views-row-', 'views-row'),
    array('is-', 'c-view__row c-view-' . $vars['name_class'] . '__row'),
    $vars['classes_array']
  );

  // Fix double hyphens (converted from double underscores).
  if (strpos(implode(' ', $vars['classes_array']), '--') !== FALSE) {
    foreach ($vars['classes_array'] as $k => $class_string) {
      $classes_array = explode(' ', $class_string);
      $classes_array = _glacier_fix_double_underscore_classes($classes_array);
      $vars['classes_array'][$k] = implode(' ', $classes_array);
    }
  }
}

/**
 * Implements template_preprocess_views_exposed_form().
 */
function glacier_preprocess_views_exposed_form(&$vars) {
  // Add setting variables.
  $vars['classes_glacier'] = theme_get_setting('classes_glacier');
  $vars['classes_default'] = theme_get_setting('classes_default');
}
