<?php
/**
 * @file
 * Taxonomy-related functions.
 */

/**
 * Implements template_preprocess_taxonomy_term().
 */
function glacier_preprocess_taxonomy_term(&$vars) {
  // Add setting variables.
  $vars['classes_glacier'] = theme_get_setting('classes_glacier');
  $vars['classes_default'] = theme_get_setting('classes_default');

  // Hide the content wrapper by default if output is a page.
  $vars['content_wrapper_hidden'] = $vars['page'];

  // Add wrapper tag variable.
  $vars['wrapper_tag'] = 'div';
  if ($vars['view_mode'] == 'full') {
    $vars['wrapper_tag'] = 'article';
  }

  // Add title tag variable.
  $vars['title_tag'] = 'h2';

  // Set class variables to use in the glacier base classes.
  $vars['machine_name_class'] = drupal_html_class($vars['vocabulary_machine_name']);
  $vars['view_mode_class'] = drupal_html_class($vars['view_mode']);

  // Move Drupal default classes in a separate array.
  $vars['default_classes_array'] = $vars['classes_array'];
  $vars['classes_array'] = array();
  // Fallback class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_classes_array'] = array('c-taxonomy-term');
  // Add glacier classes.
  $vars['glacier_classes_array'] = array(
    'c-taxonomy-term',
    'c-taxonomy-term-' . $vars['machine_name_class'],
  );

  // Fallback title class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_title_classes_array'] = array('c-taxonomy-term__title');
  // Add default Drupal title classes.
  $vars['title_attributes_array']['class'] = isset($vars['title_attributes_array']['class']) ? $vars['title_attributes_array']['class'] : array();
  $vars['default_title_classes_array'] = $vars['title_attributes_array']['class'];
  unset($vars['title_attributes_array']['class']);
  $vars['title_classes_array'] = array();
  // Add glacier title classes.
  $vars['glacier_title_classes_array'] = array(
    'c-taxonomy-term__title',
    'c-taxonomy-term-' . $vars['machine_name_class'] . '__title',
  );

  // Fallback content class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_content_classes_array'] = array('c-taxonomy-term__content');
  // Add default Drupal content classes.
  $vars['content_attributes_array']['class'] = isset($vars['content_attributes_array']['class']) ? $vars['content_attributes_array']['class'] : array();
  $vars['default_content_classes_array'] = $vars['content_attributes_array']['class'];
  unset($vars['content_attributes_array']['class']);
  $vars['content_classes_array'] = array();
  // Add glacier content classes.
  $vars['glacier_content_classes_array'] = array(
    'c-taxonomy-term__content',
    'c-taxonomy-term-' . $vars['machine_name_class'] . '__content',
  );

  // Remove taxonomy description wrapper.
  if (isset($vars['content']['description'])) {
    unset($vars['content']['description']['#prefix']);
    unset($vars['content']['description']['#suffix']);
  }

  // Add theme hook suggestions based on view mode.
  $vars['theme_hook_suggestions'][] = 'taxonomy_term__' . $vars['view_mode'];
  $vars['theme_hook_suggestions'][] = 'taxonomy_term__' . $vars['view_mode'] . '__' . $vars['vocabulary_machine_name'];
}
