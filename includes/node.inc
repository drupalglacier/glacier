<?php
/**
 * @file
 * Node-related functions.
 */

/**
 * Implements hook_preprocess_node().
 */
function glacier_preprocess_node(&$vars) {
  $bem_only = theme_get_setting('bem_only');
  $bem_prefix_component = theme_get_setting('bem_prefix_component');
  $node_type_class = drupal_html_class($vars['node']->type);
  $view_mode_class = drupal_html_class($vars['view_mode']);

  // Add BEM prefix component variable
  $vars['bem_prefix_component'] = $bem_prefix_component;

  // Remove some default node classes.
  if ($bem_only) {
    $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array(
      'node-' . $node_type_class,
      'node-' . $view_mode_class,
      'node-promoted',
      'node-sticky',
      'node-unpublished',
    )));
  }

  // Add default node attributes.
  $vars['classes_array'][] = $bem_prefix_component . 'node--' . $node_type_class;
  $vars['title_attributes_array']['class'][] = $bem_prefix_component . 'node__title';
  $vars['content_attributes_array']['class'][] = $bem_prefix_component . 'node__content';

  // Add default core attributes if wanted.
  if (!$bem_only) {
    $vars['title_attributes_array']['class'][] = 'title node-title';
    $vars['content_attributes_array']['class'][] = 'content';
  }

  // Change attributes for view modes.
  if (isset($vars['view_mode'])) {
    $vars['classes_array'][] = $bem_prefix_component . 'node--' . $view_mode_class;
  }

  // Add promoted class.
  if ($vars['promote']) {
    $vars['classes_array'][] = 'is-promoted';
  }

  // Add sticky class.
  if ($vars['sticky']) {
    $vars['classes_array'][] = 'is-sticky';
  }

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

  // Create unpublished variable and add unpublished class.
  $vars['unpublished'] = '';
  if (!$vars['status']) {
    $vars['unpublished'] = '<div class="' . $bem_prefix_component . 'node__unpublished">' . t('Unpublished') . '</div>';
    $vars['classes_array'][] = 'is-unpublished';
  }

  // Add classes array to attributes array.
  $vars['attributes_array']['class'] = $vars['classes_array'];

  // Add theme hook suggestions based on view mode.
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['view_mode'];
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['type']  . '__' . $vars['view_mode'];
}
