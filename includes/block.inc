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
  $module_class = drupal_html_class($module);
  $delta = $vars['block']->delta;
  $delta_class = drupal_html_class($delta);
  $classes_default = theme_get_setting('classes_default');
  $bem_block_classes = theme_get_setting('bem_block_classes');

  // Add new default block classes.
  if ($bem_block_classes) {
    $vars['classes_array'][] = 'c-block';
    $vars['classes_array'][] = 'c-block--' . drupal_html_class($module_class);
    $vars['title_attributes_array']['class'][] = 'c-block__title';
    $vars['content_attributes_array']['class'][] = 'c-block__content';
  }

  // Add Aria Roles via attributes.
  switch ($vars['block']->module) {
    case 'system':
      switch ($vars['block']->delta) {
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
  if ($bem_only) {
    $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array(
      'block',
      'block-' . $module_class,
      'block-menu',
    )));
  }

  // Add component classes
  $vars['classes_array'][] = 'c-' . drupal_html_class($delta_class);
  $vars['title_attributes_array']['class'][] ='c-' . drupal_html_class($delta_class) . '__title';
  $vars['content_attributes_array']['class'][] ='c-' . drupal_html_class($delta_class) . '__content';

  // Add attributes if using Clean Markup Blocks module.
  if (module_exists('clean_markup_blocks')) {
    if ($vars['block']->subject) {
      // Add title attributes to Clean Markup without overwriting classes.
      $vars['title_attributes_array']['class'] = array_merge($vars['title']['#attributes']['class'], $vars['title_attributes_array']['class']);
      $vars['title']['#attributes'] = array_merge($vars['title']['#attributes'], $vars['title_attributes_array']);

      // Remove unwanted classes.
      $vars['title']['#attributes']['class'] = array_values(array_diff($vars['title']['#attributes']['class'], array('title', 'block-title')));
    }

    if (is_array($vars['content'])) {
      // Add content attributes to Clean Markup.
      $vars['content']['#attributes'] = array_merge_recursive($vars['content']['#attributes'], $vars['content_attributes_array']);

      // Remove unwanted classes.
      if (!$classes_default) {
        $vars['content']['#attributes']['class'] = array_values(array_diff($vars['content']['#attributes']['class'], array(
          'content',
        )));
      }
    }
  }

  // Markup for blockify logo block.
  if ($delta == 'blockify-logo') {
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
  }

  // Markup for blockify site name block.
  elseif ($delta == 'blockify-site-name') {
    $vars['theme_hook_suggestions'][] = 'block__site_name';

    $site_name = filter_xss_admin(variable_get('site_name', 'Drupal'));

    $vars['site_name'] = $site_name;
    $vars['front_page'] = url();
  }

  // Markup for  blockify site slogan block.
  elseif ($delta == 'blockify-site-slogan') {
    $vars['theme_hook_suggestions'][] = 'block__site_slogan';

    $slogan = filter_xss_admin(variable_get('site_slogan', 'Drupal'));

    $vars['slogan'] = $slogan;
  }

  // Markup for blockify page title block.
  elseif ($delta == 'blockify-page-title') {
    $vars['classes_array'][0] = 'c-page-title';
    $vars['theme_hook_suggestions'][] = 'block__page_title';

    $vars['title'] = drupal_get_title();
  }
  elseif ($vars['block']->delta == 'blockify-messages') {
    $vars['theme_hook_suggestions'][] = 'block__messages';
  }

  // Markup for blockify breadcrumbs block.
  elseif ($delta == 'blockify-breadcrumb') {
    $vars['theme_hook_suggestions'][] = 'block__breadcrumbs';

    $breadcrumbs = drupal_get_breadcrumb();

    $vars['breadcrumbs'] = theme('breadcrumb', $breadcrumbs);
  }

  // Markup for blockify tabs block.
  elseif ($delta == 'blockify-tabs') {
    $vars['theme_hook_suggestions'][] = 'block__tabs';

    $primary = menu_primary_local_tasks();
    $secondary = menu_secondary_local_tasks();

    $tabs = array(
      'primary' => $primary,
      'secondary' => $secondary,
    );

    $tabs = theme('menu_local_tasks', $tabs);

    $vars['tabs'] = $tabs;
  }

  // Markup for blockify actions block.
  elseif ($delta == 'blockify-actions') {
    $vars['theme_hook_suggestions'][] = 'block__actions';

    $actions = menu_local_actions();
    $vars['actions'] = $actions;
  }

  // Markup for blockify feed icons block.
  elseif ($delta == 'blockify-feed-icons') {
    $vars['theme_hook_suggestions'][] = 'block__feed_icons';

    $icons = drupal_get_feeds();
    $vars['icons'] = $icons;
  }
}
