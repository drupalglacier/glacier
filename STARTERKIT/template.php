<?php

/**
 * Implements theme_menu_tree().
 */
// function STARTERKIT_menu_tree__main_menu(&$vars) {
//   // Add controls to the main menu.
//   $controls = '';
//   $level_class = '';
//   if (isset($vars['menu_level'])) {
//     if ($vars['menu_level'] == 1) {
//       $controls = '
//         <div class="c-menu__controls">
//           <label for="main-menu-checkbox" class="c-menu__toggle c-button">&#9776; Menu</label>
//         </div>
//         <input id="main-menu-checkbox" class="c-menu__checkbox" name="main-menu-checkbox" type="checkbox">
//       ';
//     }
//     $level_class = ' c-menu__list--level' . $vars['menu_level'];
//   }
//   return $controls . '<ul class="c-menu__list' . $level_class . '">' . $vars['tree'] . '</ul>';
// }

/**
 * Implements template_preprocess_block().
 */
// function STARTERKIT_preprocess_block(&$vars, $hook) {
//   switch ($vars['elements']['#block']->delta) {
//     case 'main-menu':
//       $vars['classes_array'][] = 'c-menu--horizontal-responsive';
//       $vars['classes_array'][] = 'c-menu--horizontal-responsive--dropdown';
//       break;
//   }
// }

/**
 * Implements hook_preprocess_field().
 */
// function STARTERKIT_preprocess_field(&$vars, $hook) {
//   // Define patterns that should be removed from the field css class name
//   // you can use this to remove prefixes (like the bundle name) from the field class name.
//   // 
//   // $patterns = array(
//   //   '/^' . $vars['bundle_class'] . '-/',
//   //   '/^' . 'custom-prefix-/',
//   // );
//   // $vars['field_name_css'] = preg_replace($patterns, '', $vars['field_name_css']);
  
//   // Add bundle and view mode theme hook suggestions.
//   // $vars['theme_hook_suggestions'][] = 'field--' . $vars['bundle_class'] . '--' . $vars['field_name_class'];
//   // $vars['theme_hook_suggestions'][] = 'field--' . $vars['view_mode_class'] . '--' . $vars['field_name_class'];
//   // $vars['theme_hook_suggestions'][] = 'field--' . $vars['bundle_class'] . '--' . $vars['view_mode_class'] . '--' . $vars['field_name_class'];
// }
