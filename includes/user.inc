<?php
/**
 * @file
 * User-related functions.
 */

/**
 * Implements template_preprocess_user_profile().
 */
function glacier_preprocess_user_profile(&$vars) {
  // Add attributes.
  $vars['attributes_array']['role'][] = 'article';
  $vars['attributes_array']['class'][] = 'user-profile';
}

/**
 * Implements template_preprocess_user_profile_category().
 */
function glacier_preprocess_user_profile_category(&$vars) {
  // Add title & list classes.
  $vars['title_attributes_array']['class'][] = 'user-profile-category__title';
  $vars['attributes_array']['class'][] = 'user-profile-category__list';
}
