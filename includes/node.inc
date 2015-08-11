<?php
/**
 * @file
 * Node-related functions.
 */

/**
 * Implements hook_preprocess_node().
 */
function glacier_preprocess_node(&$vars) {
  // Add setting variables.
  $vars['classes_default'] = theme_get_setting('classes_default');

  // Add node type and view mode classes.
  $vars['node_type_class'] = drupal_html_class($vars['node']->type);
  $vars['view_mode_class'] = drupal_html_class($vars['view_mode']);

  // Remove some default node classes.
  if (!$vars['classes_default']) {
    $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array(
      'node',
      'node-' . $vars['node_type_class'],
      'node-' . $vars['view_mode_class'],
      'node-promoted',
      'node-sticky',
      'node-unpublished',
    )));
  }

  // Add default classes.
  $vars['default_classes'] = $vars['classes_array'];

  // Add state classes.
  $vars['state_classes'] = array();
  if ($vars['promote']) {
    // Add promoted class.
    $vars['state_classes']['promoted'] = 'is-promoted';
  }
  if ($vars['sticky']) {
    // Add sticky class.
    $vars['state_classes']['sticky'] = 'is-sticky';
  }
  if (!$vars['status']) {
    // Add unpublished class.
    $vars['state_classes']['unpublished'] = 'is-unpublished';
  }
  
  // Add defaul title classes.
  $vars['title_attributes_array']['class'] = isset($vars['title_attributes_array']['class']) ? $vars['title_attributes_array']['class'] : array();
  $vars['default_title_classes'] = $vars['title_attributes_array']['class'];
  unset($vars['title_attributes_array']['class']);

  // Add defaul content classes.
  $vars['content_attributes_array']['class'] = isset($vars['content_attributes_array']['class']) ? $vars['content_attributes_array']['class'] : array();
  $vars['default_content_classes'] = $vars['content_attributes_array']['class'];
  unset($vars['content_attributes_array']['class']);

  // Create submitted info using time element.
  $vars['datetime'] = format_date($vars['created'], 'custom', 'c');
  $vars['date'] = format_date($vars['created'], 'custom', 'F j, Y');
  if (variable_get('node_submitted_' . $vars['node']->type, TRUE)) {
    $vars['submitted'] = t('!datetime by !username',
      array(
        '!datetime' => '<time class="node__date" datetime="' . $vars['datetime'] . '" pubdate="pubdate">' . $vars['date'] . '</time>',
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
