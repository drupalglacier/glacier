<?php

/**
 * Implements theme_menu_tree().
 *
 * Add controls to the main menu
 */
function STARTERKIT_menu_tree__main_menu(&$vars) {
  $controls    = '';
  $level_class = '';
  $bem_prefix_component = theme_get_setting('bem_prefix_component');

  if (isset($vars['menu_level'])) {
    if ($vars['menu_level'] == 1) {
      $controls = '
        <div class="' . $bem_prefix_component . 'menu__controls">
          <label for="main-menu-checkbox" class="' . $bem_prefix_component . 'menu__toggle ' . $bem_prefix_component . 'button">&#9776; Menu</label>
        </div>
        <input id="main-menu-checkbox" class="' . $bem_prefix_component . 'menu__checkbox" name="main-menu-checkbox" type="checkbox">
      ';
    }
    $level_class = ' ' . $bem_prefix_component . 'menu__list--level' . $vars['menu_level'];
  }
  return $controls . '<ul class="' . $bem_prefix_component . 'menu__list' . $level_class . '">' . $vars['tree'] . '</ul>';
}

/**
 * Implements template_preprocess_block().
 */
function STARTERKIT_preprocess_block(&$vars, $hook) {
  if ($vars['elements']['#block']->delta == 'main-menu') {
    $vars['classes_array'][] = $bem_prefix_component . 'menu--horizontal';
    $vars['classes_array'][] = $bem_prefix_component . 'menu--horizontal-responsive';
    $vars['classes_array'][] = $bem_prefix_component . 'menu--horizontal-responsive--dropdown';
  }
}
