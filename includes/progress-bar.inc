<?php
/**
 * @file
 * Progress barrelated functions.
 */

/**
 * Returns HTML for a progress bar.
 */
function glacier_progress_bar($vars) {
  $output = '<div id="progress" class="c-progress">';
  $output .= '<div class="c-progress__track"><div class="progress__bar" style="width: ' . $vars['percent'] . '%"></div></div>';
  $output .= '<div class="c-progress__percentage">' . $vars['percent'] . '%</div>';
  $output .= '<div class="c-progress__description">' . $vars['message'] . '</div>';
  $output .= '</div>';

  return $output;
}
