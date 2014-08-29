<?php

/**
 * @file
 * Contains functions to alter Drupal's markup for the glacier base theme.
 *
 * IMPORTANT WARNING: DO NOT MODIFY THIS FILE.
 *
 * The glacier base theme is designed to be easily extended by its sub-themes. You
 * shouldn't modify this or any of the CSS or PHP files in the root glacier/ folder.
 */

/**
 * Implements theme_button().
 *
 * Use the more flexible <button> instead of <input type="submit">
 */
function glacier_button($vars) {
  $element = $vars['element'];
  $element['#attributes']['type'] = 'submit';
  // Sets HTML attributes based on element properties.
  element_set_attributes($element, array('id', 'name', 'value'));
  // Add classes
  $element['#attributes']['class'][] = 'button';
  $element['#attributes']['class'][] = 'form__' . $element['#button_type'];
  // check if button is disabled
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'button--disabled';
  }
  // Get the value and set as content for the <button>
  return '<button' . drupal_attributes($element['#attributes']) . '>' . $element['#value'] . '</button>';
}

/**
 * Implements template_preprocess_html().
 */
function glacier_preprocess_html(&$vars) {
  // Include libraries
  $libraries = theme_get_setting('libraries');
  // modernizr
  $vars['modernizr'] = '';
  if ($libraries['modernizr']) {
    $vars['modernizr'] = '<script src="' . base_path() . libraries_get_path('modernizr') . '/modernizr.min.js"></script>';
  }
  // respondjs
  $vars['respondjs'] = '';
  if ($libraries['respondjs']) {
    $vars['respondjs'] = '
      <!--[if lt IE 9]>
        <script src="' . base_path() . libraries_get_path('respondjs') . '/dest/respond.min.js"></script>
      <![endif]-->
    ';
  }
  // selectivizr
  $vars['selectivizr'] = '';
  if ($libraries['selectivizr']) {
    $vars['selectivizr'] = '
      <!--[if (gte IE 6)&(lte IE 8)]>
        <script src="' . base_path() . libraries_get_path('selectivizr') . '/selectivizr-min.js"></script>
      <![endif]-->
    ';
  }

  // Optimize classes
  foreach ($vars['classes_array'] as $k => $v) {
    // Remove page-node- class from body
    if ($v == 'page-node-') {
      unset($vars['classes_array'][$k]);
      continue;
    }
    // Transform classes to BEM style
    if (strpos($v, 'page-node-') !== FALSE) {
      $vars['classes_array'][$k] = str_replace('page-node-', 'page-node--', $v);
    }
    elseif (strpos($v, 'node-type-') !== FALSE) {
      $vars['classes_array'][$k] = str_replace('node-type-', 'node-type--', $v);
    }
  }
}

/**
 * Implements template_preprocess_page().
 */
function glacier_preprocess_page(&$vars, $hook) {
  // Include libraries
  $libraries = theme_get_setting('libraries');
  // normalize.css
  if ($libraries['normalize']) {
    drupal_add_css(libraries_get_path('normalize') . '/normalize.css', array('every_page' => TRUE));
  }
  // Font Awesome
  if ($libraries['font_awesome']) {
    drupal_add_css(libraries_get_path('font-awesome') . '/css/font-awesome.min.css', array('every_page' => TRUE));
  }

  // Add webfonts defined in template.info file
  $webfont_counter = 1;
  $webfonts = theme_get_setting('fonts');
  if (is_array($webfonts)) {
    foreach ($webfonts as $webfont) {
      drupal_add_html_head(array(
        '#tag' => 'link',
        '#attributes' => array(
          'href' => $webfont,
          'rel' => 'stylesheet',
        )
      ), 'webfont_' . $webfont_counter);
      $webfont_counter++;
    }
  }

  // Deactivate automatic iOS / Android phone number detection
  drupal_add_html_head(array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'format-detection',
      'content' => 'telephone=no',
    )
  ), 'tel_detection');

  // Viewport
  drupal_add_html_head(array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width,initial-scale=1',
    )
  ), 'viewport');

  // Deactivate IE compatibility mode
  drupal_add_html_head(array(
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'X-UA-Compatible',
      'content' => 'IE=edge,chrome=1',
    ),
    '#weight' => '-9999',
  ), 'http_equiv');

  // Item widths for content and sidebars
  $grid = theme_get_setting('grid');
  $content_item = $grid['columns'];
  // Substract sidebar1 width
  if(!empty($vars['page']['sidebar1'])) {
    $content_item = $content_item - $grid['sidebar1'];
  }
  // Substract sidebar2 width
  if(!empty($vars['page']['sidebar2'])) {
    $content_item = $content_item - $grid['sidebar2'];
  }
  // Set grid item widths
  $vars['page']['content_item'] = $content_item;
  $vars['page']['sidebar1_item'] = $grid['sidebar1'];
  $vars['page']['sidebar2_item'] = $grid['sidebar2'];
}

/**
 * Implements hook_html_head_alter().
 */
function glacier_html_head_alter(&$head) {
  // Simplify the meta tag for character encoding
  if (isset($head['system_meta_content_type']['#attributes']['content'])) {
    $head['system_meta_content_type']['#attributes'] = array(
      'charset' => str_replace('text/html; charset=', '', $head['system_meta_content_type']['#attributes']['content'])
    );
  }

  // Fix problems with wrong paths on the front page
  // https://drupal.org/node/1316006
  if (drupal_is_front_page()) {
    // Remove the canonical and shortlink tags
    // they aren't necessary on the front page
    foreach ($head as $k => $v) {
      if (strpos($k, 'canonical') !== FALSE || strpos($k, 'shortlink') !== FALSE) {
        unset($head[$k]);
      }
    }
    // Set the about path to the front page
    if (isset($head['rdf_node_comment_count'])) {
      $head['rdf_node_comment_count']['#attributes']['about'] = '/';
    }
    if (isset($head['rdf_node_title'])) {
      $head['rdf_node_title']['#attributes']['about'] = '/';
    }
  }

  // Remove the useless generator metatag, sorry Drupal
  foreach ($head as $k => $v) {
    if (strpos($k, 'metatag_generator') !== FALSE) {
      unset($head[$k]);
    }
  }
}

/**
 * Implements hook_css_alter().
 */
function glacier_css_alter(&$css) {
  // Whitelist
  $whitelist = theme_get_setting('css_whitelist');
  // Blocked files
  $blocked_files = array();
  // Better grouping and whitelisting
  uasort($css, 'drupal_sort_css_js');
  $i = 0;
  foreach ($css as $file => $value) {
    if (is_array($whitelist) && !in_array($file, $whitelist)) {
      unset($css[$file]);
      $blocked_files[] = $file;
      continue;
    }

    // Enable a better grouping mechanism
    if (theme_get_setting('css_normalize')) {
      // Repair groups
      // Only two groups are allowed
      // Group 100 for "every_page" assets
      // Group 0 for page specific assets
      $css[$file]['group'] = $css[$file]['every_page'] ? 100 : 0;
      // Set weight
      $css[$file]['weight'] = $i++;
    }
  }
  if (!empty($blocked_files) && theme_get_setting('css_whitelist_show_blocked_files')) {
    drupal_set_message('<strong>Blocked css files</strong><br />' . implode('<br />', $blocked_files), 'warning', FALSE);
  }

  // Switch style.css with style.min.css
  // if CSS aggregating is activated
  if (variable_get('preprocess_css')) {
    global $theme;
    $path_to_theme  = drupal_get_path('theme', $theme);
    $style_path     = $path_to_theme . '/css/style.css';
    $style_path_min = $path_to_theme . '/css/style.min.css';
    // Add minified version of the main stylesheet
    $css[$style_path_min] = $css[$style_path];
    $css[$style_path_min]['data'] = $style_path_min;
    // Remove the unminified version
    unset($css[$style_path]);
  }
}

/**
 * Implements hook_js_alter().
 */
function glacier_js_alter(&$js) {
  // Whitelist
  $whitelist = theme_get_setting('js_whitelist');
  // Blocked files
  $blocked_files = array();
  // Better grouping and whitelisting
  uasort($js, 'drupal_sort_css_js');
  $i = 0;
  foreach ($js as $file => $value) {
    if (is_array($whitelist) && !in_array($file, $whitelist) && strpos($file, 'languages') === FALSE) {
      unset($js[$file]);
      $blocked_files[] = $file;
      continue;
    }

    // Enable a better grouping mechanism
    if (theme_get_setting('js_normalize')) {
      // Repair groups
      // only two groups are allowed
      // group -100 for "every_page" assets
      // group 0 for page specific assets
      $js[$file]['group'] = $js[$file]['every_page'] ? -100 : 0;
      // Set scope for all files to footer
      $js[$file]['scope'] = 'footer';
      // Set weight
      $js[$file]['weight'] = $i++;
      // Preprocess everything
      $js[$file]['preprocess'] = TRUE;
    }
  }
  if (!empty($blocked_files) && theme_get_setting('js_whitelist_show_blocked_files')) {
    drupal_set_message('<strong>Blocked js files</strong><br />' . implode('<br />', $blocked_files), 'warning', FALSE);
  }
}

/**
 * Implements template_preprocess_views_view().
 */
function glacier_preprocess_views_view(&$vars) {
  // BEM style classes for the pager
  $vars['pager'] = str_replace(
    array(
      'element-invisible',
      '<div class="item-list">',
      '</div>',
      ' first',
      ' last',
      'pager-current',
      'pager-previous',
      'pager-next',
      'pager-first',
      'pager-last',
      'pager-ellipsis',
      'pager-item',
    ),
    array(
      'visuallyhidden',
      '',
      '',
      '',
      '',
      'pager__item pager__item--current',
      'pager__item pager__item--previous',
      'pager__item pager__item--next',
      'pager__item pager__item--first',
      'pager__item pager__item--last',
      'pager__item pager__item--ellipsis',
      'pager__item',
    ),
    $vars['pager']
  );

  // Check if a grid class is attached to the view
  if ($matches = preg_grep('#(.*)grid(.*)#', $vars['classes_array'])) {
    // Temporary remove all manually added classes
    // and generate an array of the classes string
    unset($vars['classes_array'][key($matches)]);
    $view_classes = explode(' ', array_shift($matches));

    // Extract all grid classes and remove the
    // grid classes from the general classes array
    $grid_classes = preg_grep('#(.*)grid(.*)#', $view_classes);
    foreach ($grid_classes as $k => $grid_class) {
      unset($view_classes[$k]);
    }

    // Add the general classes back to the
    // view classes array and add the grid classes
    $vars['classes_array'] = array_merge($vars['classes_array'], $view_classes);
    $vars['grid_classes'] = ' ' . implode(' ', $grid_classes);

    // Use a dedicated tpl for views with grid classes
    $vars['theme_hook_suggestions'][] = 'views_view__grid';
  }

  // Only use dashes for class names
  $view_name = str_replace('_', '-', $vars['view']->name);
  $view_display = str_replace('_', '-', $vars['view']->current_display);
  // BEM style class names
  $old_class_pattern = array(
    'view-',
    '--' . $view_name,
    '--display-id',
    '-id-',
    '_',
    'view--dom',
  );
  $new_class_pattern = array(
    'view--',
    '--' . $view_name . '--' . $view_display,
    '--display',
    '-',
    '-',
    'view-dom-id',
  );
  foreach ($vars['classes_array'] as $k => $class) {
    $vars['classes_array'][$k] = str_replace($old_class_pattern, $new_class_pattern, $class);
  }
  $vars['css_display'] = $view_display;
}

/**
 * Implements template_preprocess_views_view_unformatted().
 */
function glacier_preprocess_views_view_unformatted(&$vars) {
  // Only use dashes for class names
  $view_name = str_replace('_', '-', $vars['view']->name);
  $view_display = str_replace('_', '-', $vars['view']->current_display);
  // BEM style class names
  $old_class_pattern = array(
    'views-',
    'row-',
    'grid--',
  );
  $new_class_pattern = array(
    'view__',
    'row--',
    'grid__',
  );
  foreach ($vars['classes_array'] as $k => $class) {
    $vars['classes_array'][$k] = str_replace($old_class_pattern, $new_class_pattern, $class);
  }
  // Add BEM style unique class
  $vars['classes_array'][] = 'view--' . $view_name . '--' . $view_display . '__row';
}

/**
 * Implements template_preprocess_views_view_fields().
 */
function glacier_preprocess_views_view_fields(&$vars) {
  // BEM style class names
  $old_class_pattern = array(
    '-field-title',
    '-field-body',
    '-field-field',
    'views-field',
    'views',
  );
  $new_class_pattern = array(
    '__field--title',
    '__field--body',
    '__field--field',
    'view__field',
    'view',
  );
  foreach ($vars['fields'] as $k => $field) {
    $vars['fields'][$k]->wrapper_prefix = str_replace($old_class_pattern, $new_class_pattern, $field->wrapper_prefix);
    // Only use dashes for class names
    $field_name = str_replace('_', '-', $k);
    // Field label
    $vars['fields'][$k]->label_html = str_replace(
      'class="views-label views-label-',
      'class="field__label field__label--',
      $field->label_html
    );
    // Field content
    $vars['fields'][$k]->content = str_replace(
      'class="field-content"',
      'class="view__field__content view__field--' . $field_name . '__content"',
      $field->content
    );
    // Optimizations if field template is used
    if (isset($vars['fields'][$k]->handler->options['field_api_classes']) && $vars['fields'][$k]->handler->options['field_api_classes']) {
      // Display the field label inside the field wrapper
      if (!empty($vars['fields'][$k]->label_html)) {
        $vars['fields'][$k]->content = glacier_str_replace('>', '>' . $vars['fields'][$k]->label_html, $vars['fields'][$k]->content);
        $vars['fields'][$k]->label_html = '';
      }
      // Display links inside the field wrapper
      if (strpos($vars['fields'][$k]->content, '<a ') === 0) {
        preg_match('#\<a(.*?)\>#', $vars['fields'][$k]->content, $link);
        $link = $link[0];
        $vars['fields'][$k]->content = trim(str_replace(array($link, '</a>'), '', $vars['fields'][$k]->content));
        $vars['fields'][$k]->content = glacier_str_replace('>', '>' . $link, $vars['fields'][$k]->content);
        $vars['fields'][$k]->content = glacier_str_replace('<', '</a><', $vars['fields'][$k]->content, $pos = 'last');
      }
      // Add field formatter class
      if (isset($field->handler->options['settings']['field_formatter_class'])) {
        $vars['fields'][$k]->content = glacier_str_replace(
          '">',
          ' ' . $field->handler->options['settings']['field_formatter_class'] . '">',
          $vars['fields'][$k]->content
        );
      }
    }
  }
}

/**
 * Implements template_preprocess_field().
 */
function glacier_preprocess_field(&$vars, $hook) {
  // BEM Style field classes
  $bem_field_name = str_replace(
    array('field_', '_'),
    array('field-', '-'),
    $vars['element']['#field_name']
  );
  $bem_field_type = str_replace(
    '_',
    '-',
    $vars['element']['#field_type']
  );
  $vars['classes_array'][] = 'field--' . $bem_field_name;
  $vars['classes_array'][] = 'field--type-' . $bem_field_type;
  if (isset($vars['element']['#entity_type'])) {
    $vars['classes_array'][] = 'field--' . $vars['element']['#entity_type'] . '-' . $vars['element']['#bundle'] . '--' . $bem_field_name;
  }
}

/**
 * Implements theme_field().
 *
 * BEM style class names
 */
function glacier_field($vars) {
  $output = '';
  // Render the label, if it's not hidden.
  if (!$vars['label_hidden']) {
    $output .= '<div class="field__label"' . $vars['title_attributes'] . '>' . $vars['label'] . ':&nbsp;</div>';
  }
  // Render the items.
  $output .= '<div class="field__items"' . $vars['content_attributes'] . '>';
  foreach ($vars['items'] as $delta => $item) {
    $classes = 'field__item ' . ($delta % 2 ? 'odd' : 'even');
    $output .= '<div class="' . $classes . '"' . $vars['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
  }
  $output .= '</div>';
  // Render the top-level DIV.
  $output = '<div class="' . $vars['classes'] . '"' . $vars['attributes'] . '>' . $output . '</div>';
  return $output;
}

/**
 * Implements template_process_html_tag().
 */
function glacier_process_html_tag(&$vars) {
  $tag = &$vars['element'];
  if ($tag['#tag'] === 'style' || $tag['#tag'] === 'script') {
    // Remove redundant type attribute and CDATA comments.
    unset($tag['#attributes']['type'], $tag['#value_prefix'], $tag['#value_suffix']);
    // Remove media="all" but leave others unaffected.
    if (isset($tag['#attributes']['media']) && $tag['#attributes']['media'] === 'all') {
      unset($tag['#attributes']['media']);
    }
  }
}

/**
 * Implements theme_menu_link().
 */
function glacier_menu_link(&$vars) {
  $element = $vars['element'];
  $sub_menu = '';

  // li elements
  foreach ($element['#attributes']['class'] as $k => $class) {
    // Modify existing classes
    switch ($class) {
      case 'leaf':
      case 'first':
      case 'last':
        unset($element['#attributes']['class'][$k]);
        break;

      case 'expanded':
        $element['#attributes']['class'][$k] = 'menu__item--expanded';
        break;

      case 'active-trail':
        $element['#attributes']['class'][$k] = 'menu__item--trail';
        break;
    }
  }
  // Add extra classes / id
  $menu_item_id = 'menu__item--' . $element['#original_link']['mlid'];
  $element['#attributes']['id'][] = $menu_item_id;
  $element['#attributes']['class'][] = 'menu__item';
  $element['#attributes']['class'][] = 'menu__item--level' . $element['#original_link']['depth'];
  $element['#attributes']['class'][] = $menu_item_id;
  if ($element['#href'] == '<front>' && drupal_is_front_page()) {
    // Add trail class to front page item
    $element['#attributes']['class'][] = 'menu__item--trail';
  }

  // a or span (nolink) elements
  if (isset($element['#localized_options']['attributes']['class'])) {
    foreach ($element['#localized_options']['attributes']['class'] as $k => $class) {
      // Modify existing classes
      switch ($class) {
        case 'active-trail':
          unset($vars['element']['#localized_options']['attributes']['class'][$k]);
          break;
      }
    }
  }
  else {
    $element['#localized_options']['attributes']['class'] = array();
  }
  // Add extra classes / id
  $menu_link_id = 'menu__link--' . $element['#original_link']['mlid'];
  $element['#localized_options']['attributes']['id'][] = $menu_link_id;
  $element['#localized_options']['attributes']['class'][] = 'menu__link';
  $element['#localized_options']['attributes']['class'][] = 'menu__link--level' . $element['#original_link']['depth'];
  $element['#localized_options']['attributes']['class'][] = $menu_link_id;

  // Sub menu
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  // Output
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return str_replace(
    array('active-trail ', '"active', ' active'),
    array('', '"is-active', ' is-active'),
    '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . '</li>'
  );
}

/**
 * Implements template_preprocess_menu_tree().
 */
function glacier_preprocess_menu_tree(&$vars) {
  // Add a level variable to the menu
  if (preg_match('#menu__item--level([0-9])#', $vars['tree'], $match)) {
    $vars['menu_level'] = $match[1];
  }
}

/**
 * Implements menu_tree().
 */
function glacier_menu_tree(&$vars) {
  // Add BEM style classes and a level class
  $level_class = '';
  if (isset($vars['menu_level'])) {
    $level_class = ' menu__list--level' . $vars['menu_level'];
  }
  return '<ul class="menu__list' . $level_class . '">' . $vars['tree'] . '</ul>';
}

/**
 * Implements template_preprocess_block().
 */
function glacier_preprocess_block(&$vars, $hook) {
  $vars['html_tag'] = 'div';

  // Use a template with no wrapper for the page's main content.
  if ($vars['block_html_id'] == 'block-system-main') {
    $vars['theme_hook_suggestions'][] = 'block__no_wrapper';
  }

  // BEM style id and class names
  $vars['block_html_id'] = str_replace(
    array('block-' . str_replace('_', '-', $vars['block']->module . '-' . $vars['block']->delta)),
    array('block--' . str_replace('_', '-', $vars['block']->delta)),
    $vars['block_html_id']
  );
  foreach ($vars['classes_array'] as $k => $class) {
    $vars['classes_array'][$k] = str_replace('block-', 'block--', $class);
  }
  $vars['classes_array'][] = $vars['block_html_id'];
  // Add additional classes
  $vars['title_attributes_array']['class'][] = 'title';
  $vars['title_attributes_array']['class'][] = 'title--block';
  $vars['title_attributes_array']['class'][] = $vars['block_html_id'] . '__title';

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
          $vars['classes_array'][] = 'menu';
          $vars['attributes_array']['role'] = 'navigation';
          $vars['html_tag'] = 'nav';
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
      $vars['html_tag'] = 'nav';
      break;

    case 'search':
      $vars['attributes_array']['role'] = 'search';
      break;

    case 'help':
    case 'aggregator':
    case 'locale':
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
          $vars['html_tag'] = 'nav';
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
}

/**
 * HTML minifier
 *
 * http://stackoverflow.com/questions/5312349/minifying-final-html-output-using-regular-expressions-with-codeigniter
 */
// Set PCRE recursion limit to sane value = STACKSIZE / 500
// ini_set("pcre.recursion_limit", "524"); // 256KB stack. Win32 Apache
ini_set('pcre.recursion_limit', '16777');  // 8MB stack. *nix

function glacier_html_minify($html) {
  if (theme_get_setting('html_minify')) {
    $re = '%# Collapse whitespace everywhere but in blacklisted elements.
        (?>             # Match all whitespans other than single space.
          [^\S ]\s*     # Either one [\t\r\n\f\v] and zero or more ws,
        | \s{2,}        # or two or more consecutive-any-whitespace.
        ) # Note: The remaining regex consumes no text at all...
        (?=             # Ensure we are not in a blacklist tag.
          [^<]*+        # Either zero or more non-"<" {normal*}
          (?:           # Begin {(special normal*)*} construct
            <           # or a < starting a non-blacklist tag.
            (?!/?(?:textarea|pre|script)\b)
            [^<]*+      # more non-"<" {normal*}
          )*+           # Finish "unrolling-the-loop"
          (?:           # Begin alternation group.
            <           # Either a blacklist start tag.
            (?>textarea|pre|script)\b
          | \z          # or end of file.
          )             # End alternation group.
        )  # If we made it here, we are not in a blacklist tag.
        %Six';

    $html = preg_replace($re, " ", $html);

    if ($html === null) {
      exit("PCRE Error! File too big.\n");
    }
  }

  return $html;
}

/**
 * Replace either the first or the last occurrence of the search string with the replacement string
 * @param  string $search  The value being searched for, otherwise known as the needle. An array may be used to designate multiple needles.
 * @param  string $replace The replacement value that replaces found search values. An array may be used to designate multiple replacements.
 * @param  string $subject The string or array being searched and replaced on, otherwise known as the haystack.
 * @param  string $pos     The occurrence which should be replaced - "first" or "last"
 * @return string
 */
function glacier_str_replace($search = '', $replace = '', $subject = '', $pos = 'first') {
  switch ($pos) {
    case 'last':
      $pos = strrpos($subject, $search);
      break;

    default:
      $pos = strpos($subject, $search);
      break;
  }
  if($pos !== FALSE) {
    $subject = substr_replace($subject, $replace, $pos, strlen($search));
  }
  return $subject;
}