<?php
/**
 * @file
 * HTML template functions.
 */

/**
 * Implements template_preprocess_maintenance_page().
 */
function glacier_preprocess_maintenance_page(&$vars, $hook) {
  // While markup for normal pages is split into page.tpl.php and html.tpl.php,
  // the markup for the maintenance page is all in the single
  // maintenance-page.tpl.php template. So, to have what's done in
  // glacier_preprocess_html() also happen on the maintenance page, it has to be
  // called here.
  glacier_preprocess_html($vars, $hook);
  glacier_preprocess_page($vars, $hook);

  // This preprocessor will also be used if the db is inactive. To ensure your
  // theme is used, add the following line to your settings.php file:
  // $conf['maintenance_theme'] = 'glacier';
  // Also, check $vars['db_is_active'] before doing any db queries.
}

/**
 * Implements template_process_maintenance_page().
 */
function glacier_process_maintenance_page(&$vars, $hook) {
  // When a variable is manipulated or added in preprocess_html or
  // preprocess_page, that same work is probably needed for the maintenance page
  // as well, so we can just re-use those functions to do that work here.
  glacier_process_html($vars, $hook);
}

/**
 * Implements template_preprocess_html().
 */
function glacier_preprocess_html(&$vars, $hook) {
  // Add theme variables.
  $vars['base_path'] = base_path();
  $vars['theme_path'] = drupal_get_path('theme', $GLOBALS['theme_key']);

  // Send X-UA-Compatible HTTP header to force IE to use the most recent
  // rendering engine or use Chrome's frame rendering engine if available.
  // This also prevents the IE compatibility mode button to appear when using
  // conditional classes on the html tag.
  if (is_null(drupal_get_http_header('X-UA-Compatible'))) {
    drupal_add_http_header('X-UA-Compatible', 'IE=edge,chrome=1');
  }

  // HTML element attributes.
  if (!isset($vars['html_attributes_array'])) {
    $vars['html_attributes_array'] = array();
  }

  $vars['html_attributes_array']['lang'] = $vars['language']->language;
  $vars['html_attributes_array']['dir'] = $vars['language']->dir;

  // Body element attributes.
  $vars['body_attributes_array'] = array();

  // Return early so the maintenance page does not call any of the code below.
  if ($hook != 'html') {
    return;
  }

  // Serialize RDF Namespaces into an RDFa 1.1 prefix attribute.
  if (isset($vars['rdf_namespaces'])) {
    $prefixes = array();
    foreach (explode("\n  ", ltrim($vars['rdf_namespaces'])) as $namespace) {
      // Remove xlmns: and ending quote and fix prefix formatting.
      $prefixes[] = str_replace('="', ': ', substr($namespace, 6, -1));
    }
    $vars['rdf_namespaces'] = ' prefix="' . implode(' ', $prefixes) . '"';
  }

  // Remove unwanted body classes.
  $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array(
    'html',
    'two-sidebars',
    'one-sidebar sidebar-first',
    'one-sidebar sidebar-second',
    'no-sidebars',
  )));
  $vars['classes_array'] = preg_grep('/^page-node/', $vars['classes_array'], PREG_GREP_INVERT);

  foreach ($vars['classes_array'] as $k => $class) {
    switch ($class) {
      case 'front':
      case 'not-front':
        $vars['classes_array'][$k] = 'is-' . $class;
        break;

      case 'logged-in':
      case 'not-logged-in':
        $vars['classes_array'][$k] = 'user-' . $class;
        break;
    }
  }

  if (!$vars['is_front']) {
    // Add path class.
    $path = drupal_get_path_alias($_GET['q']);
    $vars['classes_array'][] = drupal_html_class('path-' . $path);

    // Add section class.
    list($section) = explode('/', $path, 2);
    $arg = explode('/', $_GET['q']);
    if ($arg[0] == 'node' && isset($arg[1])) {
      if ($arg[1] == 'add') {
        $section = 'node-add';
      }
      elseif (isset($arg[2]) && is_numeric($arg[1]) && ($arg[2] == 'edit' || $arg[2] == 'delete')) {
        $section = 'node-' . $arg[2];
      }
    }
    $vars['classes_array'][] = drupal_html_class('section-' . $section);

    // Store the menu item since it has some useful information.
    $vars['menu_item'] = menu_get_item();

    // Add class for Views and Panel pages.
    if ($vars['menu_item']) {
      switch ($vars['menu_item']['page_callback']) {
        case 'views_page':
          $vars['classes_array'][] = 'page-views';
          break;

        case 'page_manager_blog':
        case 'page_manager_blog_user':
        case 'page_manager_contact_site':
        case 'page_manager_contact_user':
        case 'page_manager_node_add':
        case 'page_manager_node_edit':
        case 'page_manager_node_view_page':
        case 'page_manager_page_execute':
        case 'page_manager_poll':
        case 'page_manager_search_page':
        case 'page_manager_term_view_page':
        case 'page_manager_user_edit_page':
        case 'page_manager_user_view_page':
          $vars['classes_array'][] = 'page-panels';
          break;
      }
    }
  }

  // Deactivate automatic iOS / Android phone number detection.
  if (theme_get_setting('meta_format_detection')) {
    drupal_add_html_head(array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'format-detection',
        'content' => 'telephone=no',
      ),
    ), 'tel_detection');
  }

  // Viewport.
  if (theme_get_setting('meta_viewport')) {
    drupal_add_html_head(array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'viewport',
        'content' => 'width=device-width,initial-scale=1',
      ),
    ), 'viewport');
  }

  // Deactivate IE compatibility mode.
  if (theme_get_setting('meta_ie_compatibility')) {
    drupal_add_html_head(array(
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => 'X-UA-Compatible',
        'content' => 'IE=edge,chrome=1',
      ),
      '#weight' => '-9999',
    ), 'http_equiv');
  }

  // Add 'theme-color'
  if ($meta_theme_color = theme_get_setting('meta_theme_color')) {
    drupal_add_html_head(array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'theme-color',
        'content' => $meta_theme_color,
      ),
    ), 'theme_color');
  }
}

/**
 * Implements template_process_html().
 */
function glacier_process_html(&$vars, $hook) {
  // Flatten out html_and body_attributes.
  $vars['html_attributes'] = empty($vars['html_attributes_array']) ? '' : drupal_attributes($vars['html_attributes_array']);
  $vars['body_attributes'] = empty($vars['body_attributes_array']) ? '' : drupal_attributes($vars['body_attributes_array']);
}

/**
 * Implements hook_process_html_tag().
 */
function glacier_process_html_tag(&$vars) {
  $tag = &$vars['element'];

  if ($tag['#tag'] == 'script') {
    // Remove type="text/javascript"
    unset($tag['#attributes']['type']);
  }
  elseif ($tag['#tag'] == 'style' || $tag['#tag'] == 'link') {
    // Remove media="all" but leave others unaffected.
    if (isset($tag['#attributes']['media']) && $tag['#attributes']['media'] === 'all') {
      unset($tag['#attributes']['media']);
    }
    // Remove type="text/css"
    if (isset($tag['#attributes']['type']) && $tag['#attributes']['type'] == 'text/css') {
      unset($tag['#attributes']['type']);
    }
  }
}

/**
 * Implements hook_html_head_alter().
 */
function glacier_html_head_alter(&$head_elements) {
  // Simplify the meta tag for character encoding.
  if (isset($head_elements['system_meta_content_type']['#attributes']['content'])) {
    $head_elements['system_meta_content_type']['#attributes'] = array(
      'charset' => str_replace('text/html; charset=', '', $head_elements['system_meta_content_type']['#attributes']['content']),
    );
  }

  foreach ($head_elements as $k => $element) {
    if (strpos($k, 'generator') !== FALSE) {
      // Remove the Drupal generator tag, it's pointless.
      unset($head_elements[$k]);
    }
    elseif (strpos($k, 'fix_blocking_css_ie') !== FALSE) {
      // Remove empty conditional comment that is
      // added by advagg, we don't care about IE.
      unset($head_elements[$k]);
    }
    elseif (drupal_is_front_page() && (strpos($k, 'canonical') !== FALSE || strpos($k, 'shortlink') !== FALSE)) {
      // Remove the canonical and shortlink tags
      // they aren't necessary on the front page.
      unset($head_elements[$k]);
    }

    // Fix canonical urls for taxonomy terms when using the tvi module.
    if (strpos($k, 'canonical') !== FALSE && isset($element['#value'])) {
      if (isset($head_elements['metatag_shortlink'])) {
        $head_elements[$k]['#value'] = url(drupal_get_path_alias(str_replace('http://' . $_SERVER['SERVER_NAME'] . base_path(), '', $head_elements['metatag_shortlink']['#value'])), array('absolute' => TRUE));
      }
    }
  }
}
