<?php
/**
 * @file
 * Node-related functions.
 */

/**
 * Implements template_preprocess_node().
 */
function glacier_preprocess_node(&$vars) {
  // Add setting variables.
  $vars['classes_glacier'] = theme_get_setting('classes_glacier');
  $vars['classes_default'] = theme_get_setting('classes_default');

  // Hide the content wrapper by default if the subject is empty.
  $vars['content_wrapper_hidden'] = $vars['page'] || empty($vars['title']);

  // Add wrapper tag variable.
  $vars['wrapper_tag'] = 'div';
  if ($vars['view_mode'] == 'full') {
    $vars['wrapper_tag'] = 'article';
  }

  // Add title tag variable.
  $vars['title_tag'] = 'h2';

  // Set class variables to use in the glacier base classes.
  $vars['node_type_class'] = drupal_html_class($vars['node']->type);
  $vars['view_mode_class'] = drupal_html_class($vars['view_mode']);

  // Move Drupal default classes in a separate array.
  $vars['default_classes_array'] = $vars['classes_array'];
  $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array(
    'node',
    'node-' . $vars['node_type_class'],
    'node-' . $vars['view_mode_class'],
    'node-promoted',
    'node-sticky',
    'node-unpublished',
  )));
  // Fallback class if glacier and Drupal default classes are disabled in the theme settings.
  $vars['fallback_classes_array'] = array('c-node');
  // Add glacier classes.
  $vars['glacier_classes_array'] = array(
    'c-node',
    'c-node-' . $vars['node_type_class'],
  );
  // Add state classes.
  if ($vars['promote']) {
    // Add promoted class.
    $vars['glacier_classes_array'][] = 'is-promoted';
  }
  if ($vars['sticky']) {
    // Add sticky class.
    $vars['glacier_classes_array'][] = 'is-sticky';
  }
  if (!$vars['status']) {
    // Add unpublished class.
    $vars['glacier_classes_array'][] = 'is-unpublished';
  }
  
  // Fallback title class if glacier and Drupal default classes are disabled in the theme settings.
  $vars['fallback_title_classes_array'] = array('c-node__title');
  // Add default Drupal title classes.
  $vars['title_attributes_array']['class'] = isset($vars['title_attributes_array']['class']) ? $vars['title_attributes_array']['class'] : array();
  $vars['default_title_classes_array'] = $vars['title_attributes_array']['class'];
  unset($vars['title_attributes_array']['class']);
  $vars['title_classes_array'] = array();
  // Add glacier title classes.
  $vars['glacier_title_classes_array'] = array(
    'c-node__title',
    'c-node-' . $vars['node_type_class'] . '__title',
  );

  // Fallback content class if glacier and Drupal default classes are disabled in the theme settings.
  $vars['fallback_content_classes_array'] = array('c-node__content');
  // Add default Drupal content classes.
  $vars['content_attributes_array']['class'] = isset($vars['content_attributes_array']['class']) ? $vars['content_attributes_array']['class'] : array();
  $vars['default_content_classes_array'] = $vars['content_attributes_array']['class'];
  unset($vars['content_attributes_array']['class']);
  $vars['content_classes_array'] = array();
  // Add glacier content classes.
  $vars['glacier_content_classes_array'] = array(
    'c-node__content',
    'c-node-' . $vars['node_type_class'] . '__content',
  );

  // Create submitted info using time element.
  $vars['datetime'] = format_date($vars['created'], 'custom', 'c');
  $vars['date'] = format_date($vars['created'], 'custom', 'F j, Y');
  if (variable_get('node_submitted_' . $vars['node']->type, TRUE)) {
    $vars['submitted'] = t('!datetime by !username',
      array(
        '!datetime' => '<time class="c-node__date" datetime="' . $vars['datetime'] . '" pubdate="pubdate">' . $vars['date'] . '</time>',
        '!username' => $vars['name'],
      )
    );
  }
  else {
    $vars['submitted'] = '';
  }

  // Add theme hook suggestions based on view mode.
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['view_mode'];
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['type']  . '__' . $vars['view_mode'];
}
