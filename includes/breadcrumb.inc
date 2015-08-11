<?php
/**
 * @file
 * Breadcrumb-related functions.
 */

/**
 * Returns HTML for the breadcrumb trail.
 */
function glacier_breadcrumb($vars) {
  if (!empty($vars['breadcrumb'])) {
    $output = '<nav class="c-breadcrumb" role="navigation">';
    $output .= '<h2 class="c-breadcrumb__title">' . t('You are here') . '</h2>';
    $output .= '<ol class="c-breadcrumb__list"><li class="c-breadcrumb__item">';
    $output .= implode('</li><li class="c-breadcrumb__item">', $vars['breadcrumb']);
    $output .= '</li></ol></nav>';

    return $output;
  }

  return '';
}
