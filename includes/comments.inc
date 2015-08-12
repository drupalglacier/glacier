<?php
/**
 * @file
 * Comments-related functions.
 */

/**
 * Implements hook_preprocess_comment_wrapper().
 */
function glacier_preprocess_comment_wrapper(&$vars) {
  // Add a HTML id so it can be used as an anchor target.
  $vars['attributes_array']['id'] = 'comments';

  // Add the component class.
  $vars['attributes_array']['class'] = isset($vars['attributes_array']['class']) ? $vars['attributes_array']['class'] : array();
  $vars['classes_array'] = $vars['attributes_array']['class'];
  unset($vars['attributes_array']['class']);

  // Add default title classes.
  $vars['title_attributes_array']['class'] = isset($vars['title_attributes_array']['class']) ? $vars['title_attributes_array']['class'] : array();
  $vars['title_classes_array'] = $vars['title_attributes_array']['class'];
  unset($vars['title_attributes_array']['class']);

  // Add default form title classes.
  $vars['form_title_attributes_array']['class'] = isset($vars['form_title_attributes_array']['class']) ? $vars['form_title_attributes_array']['class'] : array();
  $vars['form_title_classes_array'] = $vars['form_title_attributes_array']['class'];
  unset($vars['form_title_attributes_array']['class']);
}

/**
 * Implements hook_process_comment_wrapper().
 */
function glacier_process_comment_wrapper(&$vars) {
  // Flatten the attributes array.
  $vars['form_title_attributes'] = drupal_attributes($vars['form_title_attributes_array']);
}

/**
 * Implements hook_preprocess_comment().
 */
function glacier_preprocess_comment(&$vars) {
  $comment = $vars['elements']['#comment'];

  // Fix original classes.
  $vars['classes_array'] = preg_replace('/^comment-(?!-)/', 'c-comment--', $vars['classes_array']);

  // Set user picture.
  $vars['user_picture'] = theme_get_setting('toggle_comment_user_picture') ? theme('user_picture', array('account' => $comment)) : '';

  // Add default title classes.
  $vars['title_attributes_array']['class'] = isset($vars['title_attributes_array']['class']) ? $vars['title_attributes_array']['class'] : array();
  $vars['title_classes_array'] = $vars['title_attributes_array']['class'];
  unset($vars['title_attributes_array']['class']);

  // Add default content classes.
  $vars['content_attributes_array']['class'] = isset($vars['content_attributes_array']['class']) ? $vars['content_attributes_array']['class'] : array();
  $vars['content_classes_array'] = $vars['content_attributes_array']['class'];
  unset($vars['content_attributes_array']['class']);

  // Add sub component classes.
  $vars['content']['links']['#attributes']['class'][] = 'c-nav--comment';

  // Format created date.
  $vars['datetime'] = format_date($vars['comment']->created, 'custom', 'c');
  $vars['date'] = format_date($vars['comment']->created, 'custom', 'F j, Y g:i a');
  $vars['created'] = '<time class="c-comment__created" datetime="' . $vars['datetime'] . '">' . $vars['date'] . '</time>';

  // Fix permalink class.
  $vars['permalink'] = preg_replace('/"permalink"/', '"c-comment__permalink"', $vars['permalink']);
}
