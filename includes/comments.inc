<?php
/**
 * @file
 * Comments-related functions.
 */

/**
 * Implements template_preprocess_comment_wrapper().
 */
function glacier_preprocess_comment_wrapper(&$vars) {
  // Add setting variables.
  $vars['classes_glacier'] = theme_get_setting('classes_glacier');
  $vars['classes_default'] = theme_get_setting('classes_default');

  // Add title tag variables.
  $vars['title_tag'] = 'h2';
  $vars['form_title_tag'] = 'h2';

  // Add a HTML id so it can be used as an anchor target.
  $vars['attributes_array']['id'] = 'comments';

  // Fallback class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_classes_array'] = array('c-comment');
  // Add default Drupal classes.
  $vars['attributes_array']['class'] = isset($vars['attributes_array']['class']) ? $vars['attributes_array']['class'] : array();
  $vars['default_classes_array'] = $vars['attributes_array']['class'];
  unset($vars['attributes_array']['class']);
  $vars['classes_array'] = array();
  // Add glacier classes.
  $vars['glacier_classes_array'] = array(
    'c-comment',
  );

  // Fallback title class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_title_classes_array'] = array('c-comment__main-title');
  // Add default Drupal title classes.
  $vars['title_attributes_array']['class'] = isset($vars['title_attributes_array']['class']) ? $vars['title_attributes_array']['class'] : array();
  $vars['default_title_classes_array'] = $vars['title_attributes_array']['class'];
  unset($vars['title_attributes_array']['class']);
  $vars['title_classes_array'] = array();
  // Add glacier title classes.
  $vars['glacier_title_classes_array'] = array(
    'c-comment__main-title',
  );

  // Fallback form title class if glacier and Drupal
  // default classes are disabled in the theme settings.
  $vars['fallback_form_title_classes_array'] = array('c-comment__form-title');
  // Add default Drupal form title classes.
  $vars['form_title_attributes_array']['class'] = isset($vars['form_title_attributes_array']['class']) ? $vars['form_title_attributes_array']['class'] : array();
  $vars['default_form_title_classes_array'] = $vars['form_title_attributes_array']['class'];
  unset($vars['form_title_attributes_array']['class']);
  $vars['form_title_classes_array'] = array();
  // Add glacier form title classes.
  $vars['glacier_form_title_classes_array'] = array(
    'c-comment__form-title',
  );
}

/**
 * Implements template_process_comment_wrapper().
 */
function glacier_process_comment_wrapper(&$vars) {
  // Flatten the attributes array.
  $vars['form_title_attributes'] = drupal_attributes($vars['form_title_attributes_array']);
}

/**
 * Implements template_preprocess_comment().
 */
function glacier_preprocess_comment(&$vars) {
  // Add setting variables.
  $vars['classes_glacier'] = theme_get_setting('classes_glacier');
  $vars['classes_default'] = theme_get_setting('classes_default');

  // Add title tag variable.
  $vars['title_tag'] = 'h2';

  $comment = $vars['elements']['#comment'];

  // Set user picture.
  $vars['user_picture'] = theme_get_setting('toggle_comment_user_picture') ? theme('user_picture', array('account' => $comment)) : '';

  // Move Drupal default classes in a separate array.
  $vars['default_classes_array'] = $vars['classes_array'];
  $vars['classes_array'] = array();
  // Fallback class if glacier and Drupal default classes
  // are disabled in the theme settings.
  $vars['fallback_classes_array'] = array('c-comment__comment');
  // Add glacier classes.
  $vars['glacier_classes_array'] = array(
    'c-comment__comment',
  );

  // Fallback title class if glacier and Drupal default
  // classes are disabled in the theme settings.
  $vars['fallback_title_classes_array'] = array('c-comment__title');
  // Add default Drupal title classes.
  $vars['title_attributes_array']['class'] = isset($vars['title_attributes_array']['class']) ? $vars['title_attributes_array']['class'] : array();
  $vars['default_title_classes_array'] = $vars['title_attributes_array']['class'];
  unset($vars['title_attributes_array']['class']);
  $vars['title_classes_array'] = array();
  // Add glacier title classes.
  $vars['glacier_title_classes_array'] = array(
    'c-comment__title',
  );

  // Fallback content class if glacier and Drupal
  // default classes are disabled in the theme settings.
  $vars['fallback_content_classes_array'] = array('c-comment__content');
  // Add default Drupal content classes.
  $vars['content_attributes_array']['class'] = isset($vars['content_attributes_array']['class']) ? $vars['content_attributes_array']['class'] : array();
  $vars['default_content_classes_array'] = $vars['content_attributes_array']['class'];
  unset($vars['content_attributes_array']['class']);
  $vars['content_classes_array'] = array();
  // Add glacier title classes.
  $vars['glacier_content_classes_array'] = array(
    'c-comment__content',
  );

  // Add sub component classes.
  // $vars['content']['links']['#attributes']['class'][] = 'c-nav--comment';

  // Format created date.
  $vars['datetime'] = format_date($vars['comment']->created, 'custom', 'c');
  $vars['date'] = format_date($vars['comment']->created, 'custom', 'F j, Y g:i a');
  $vars['created'] = '<time class="c-comment__created" datetime="' . $vars['datetime'] . '">' . $vars['date'] . '</time>';

  // Fix permalink class.
  $vars['permalink'] = preg_replace('/"permalink"/', '"c-comment__permalink"', $vars['permalink']);
}
