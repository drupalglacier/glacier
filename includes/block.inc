<?php
/**
 * @file
 * Block-related functions.
 */

/**
 * Implements hook_preprocess_block().
 */
function glacier_preprocess_block(&$vars) {
  $module = $vars['block']->module;
  $delta = $vars['block']->delta;

  // Add setting variables.
  $vars['classes_default'] = theme_get_setting('classes_default');

  // Add module and delta classes.
  $vars['module_class'] = drupal_html_class($module);
  $vars['delta_class'] = drupal_html_class($delta);

  // Add Aria Roles via attributes.
  switch ($module) {
    case 'system':
      switch ($delta) {
        case 'main':
          // Note: the "main" role goes in the page.tpl, not here.
          break;

        case 'help':
        case 'powered-by':
          $vars['attributes_array']['role'] = 'complementary';
          break;

        default:
          // Any other "system" block is a menu block.
          $vars['classes_array'][] = 'c-menu';
          $vars['attributes_array']['role'] = 'navigation';
          break;
      }
      break;

    case 'menu':
    case 'menu_block':
    case 'blog':
    case 'book':
    case 'comment':
    case 'forum':
    case 'shortcut':
    case 'statistics':
      $vars['attributes_array']['role'] = 'navigation';
      break;

    case 'search':
      $vars['attributes_array']['role'] = 'search';
      break;

    case 'locale':
      $vars['classes_array'][] = 'c-menu';
      $vars['attributes_array']['role'] = 'complementary';
      break;

    case 'help':
    case 'aggregator':
    case 'poll':
    case 'profile':
      $vars['attributes_array']['role'] = 'complementary';
      break;

    case 'node':
      switch ($vars['block']->delta) {
        case 'syndicate':
          $vars['attributes_array']['role'] = 'complementary';
          break;

        case 'recent':
          $vars['attributes_array']['role'] = 'navigation';
          break;
      }
      break;

    case 'user':
      switch ($vars['block']->delta) {
        case 'login':
          $vars['attributes_array']['role'] = 'form';
          break;

        case 'new':
        case 'online':
          $vars['attributes_array']['role'] = 'complementary';
          break;
      }
      break;
  }

  // Remove some default block classes.
  if (!$vars['classes_default']) {
    $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array(
      'block',
      'block-' . $vars['module_class'],
      'block-menu',
    )));
  }

  switch ($delta) {
    // Markup for blockify logo block.
    case 'blockify-logo':
      $vars['theme_hook_suggestions'][] = 'block__logo';

      $site_name = filter_xss_admin(variable_get('site_name', 'Drupal'));

      // Strip the base_path from the beginning of the logo path.
      $path = preg_replace('|^' . base_path() . '|', '', theme_get_setting('logo'));

      $image = array(
        '#theme' => 'image',
        '#path' => $path,
        '#alt' => t('!site_name Logo', array(
          '!site_name' => $site_name,
        )),
      );

      $path_svg = str_replace(array('.png', '.jpg', '.jpeg', '.gif'), '.svg', $path);
      $path_svg = str_replace('http://' . $_SERVER['HTTP_HOST'] . '/', '', $path_svg);
      if (file_exists($path_svg)) {
        $image['#path'] = base_path() . $path_svg;
        $image['#attributes'] = array('onerror' => 'this.src=\'' . $path . '\'');
      }

      $vars['logo'] = $image;
      $vars['site_name'] = $site_name;
      $vars['front_page'] = url();
      break;

    // Markup for blockify site name block.
    case 'blockify-site-name':
      $vars['theme_hook_suggestions'][] = 'block__site_name';

      $site_name = filter_xss_admin(variable_get('site_name', 'Drupal'));

      $vars['site_name'] = $site_name;
      $vars['front_page'] = url();
      break;

    // Markup for  blockify site slogan block.
    case 'blockify-site-slogan':
      $vars['theme_hook_suggestions'][] = 'block__site_slogan';

      $slogan = filter_xss_admin(variable_get('site_slogan', 'Drupal'));

      $vars['slogan'] = $slogan;
      break;

    // Markup for blockify page title block.
    case 'blockify-page-title':
      $vars['classes_array'][0] = 'c-page-title';
      $vars['theme_hook_suggestions'][] = 'block__page_title';

      $vars['title'] = drupal_get_title();
      break;
    
    case 'blockify-messages':
      $vars['theme_hook_suggestions'][] = 'block__messages';
      break;

    // Markup for blockify breadcrumbs block.
    case 'blockify-breadcrumb':
      $vars['theme_hook_suggestions'][] = 'block__breadcrumbs';

      $breadcrumbs = drupal_get_breadcrumb();

      $vars['breadcrumbs'] = theme('breadcrumb', $breadcrumbs);
      break;

    // Markup for blockify tabs block.
    case 'blockify-tabs':
      $vars['theme_hook_suggestions'][] = 'block__tabs';

      $primary = menu_primary_local_tasks();
      $secondary = menu_secondary_local_tasks();

      $tabs = array(
        'primary' => $primary,
        'secondary' => $secondary,
      );

      $tabs = theme('menu_local_tasks', $tabs);

      $vars['tabs'] = $tabs;
      break;

    // Markup for blockify actions block.
    case 'blockify-actions':
      $vars['theme_hook_suggestions'][] = 'block__actions';

      $actions = menu_local_actions();
      $vars['actions'] = $actions;
      break;

    // Markup for blockify feed icons block.
    case 'blockify-feed-icons':
      $vars['theme_hook_suggestions'][] = 'block__feed_icons';

      $icons = drupal_get_feeds();
      $vars['icons'] = $icons;
      break;
  }

  // Add defaul title classes.
  $vars['title_attributes_array']['class'] = isset($vars['title_attributes_array']['class']) ? $vars['title_attributes_array']['class'] : array();
  $vars['title_classes_array'] = $vars['title_attributes_array']['class'];
  unset($vars['title_attributes_array']['class']);

  // Add defaul content classes.
  $vars['content_attributes_array']['class'] = isset($vars['content_attributes_array']['class']) ? $vars['content_attributes_array']['class'] : array();
  $vars['content_classes_array'] = $vars['content_attributes_array']['class'];
  unset($vars['content_attributes_array']['class']);
}
