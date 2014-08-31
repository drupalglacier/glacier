<?php

/**
 * Implements hook_form_alter().
 */
function STARTERKIT_form_search_block_form_alter(&$form, &$form_state, $form_id) {
  // HTML5 placeholder attribute
  $form['search_block_form']['#attributes']['placeholder'] = t('Your search term') . '...';
}

/**
 * Implements theme_menu_tree().
 *
 * Add controls to the main menu
 */
function STARTERKIT_menu_tree__main_menu(&$vars) {
  $controls    = '';
  $level_class = '';
  if (isset($vars['menu_level'])) {
    if ($vars['menu_level'] == 1) {
      $controls = '
        <div class="menu__controls">
          <label for="menu__checkbox" class="menu__toggle button button--s">&#9776; Menu</label>
        </div>
        <input id="menu__checkbox" class="menu__checkbox" name="menu__checkbox" type="checkbox">
      ';
    }
    $level_class = ' menu__list--level' . $vars['menu_level'];
  }
  return $controls . '<ul class="menu__list' . $level_class . '">' . $vars['tree'] . '</ul>';
}

/**
 * Implements template_preprocess_block().
 */
function STARTERKIT_preprocess_block(&$vars, $hook) {
  if ($vars['elements']['#block']->delta == 'main-menu') {
    $vars['classes_array'][] = 'menu--horizontal';
  }
}