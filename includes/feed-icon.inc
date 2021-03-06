<?php
/**
 * @file
 * Feed icon-related functions.
 */

/**
 * Returns HTML for the RSS feed icon.
 */
function glacier_feed_icon($vars) {
  $text = t('Subscribe to @feed-title', array('@feed-title' => $vars['title']));

  return l($text, $vars['url'], array('html' => TRUE, 'attributes' => array('class' => array('c-feed-icon'))));
}
