<?php
/**
 * @file
 * Breadcrumb-related functions.
 */

/**
 * Returns HTML for the breadcrumb trail.
 */
function glacier_breadcrumb($vars) {
  $smacss_prefix_component = theme_get_setting('smacss_prefix_component');

  if (!empty($vars['breadcrumb'])) {
    $output = '<nav class="' . $smacss_prefix_component . 'breadcrumb" role="navigation">';
    $output .= '<h2 class="' . $smacss_prefix_component . 'breadcrumb__title">' . t('You are here') . '</h2>';
    $output .= '<ol class="' . $smacss_prefix_component . 'breadcrumb__list"><li class="' . $smacss_prefix_component . 'breadcrumb__item">';
    $output .= implode('</li><li class="' . $smacss_prefix_component . 'breadcrumb__item">', $vars['breadcrumb']);
    $output .= '</li></ol></nav>';

    return $output;
  }

  return '';
}
