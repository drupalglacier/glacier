<?php
/**
 * @file
 * Theme settings for the glacier theme.
 */

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function glacier_form_system_theme_settings_alter(&$form, &$form_state, $form_id = NULL) {
  // General "alters" use a form id. Settings should not be set here. The only
  // thing useful about this is if you need to alter the form for the running
  // theme and *not* the theme setting.
  // @see http://drupal.org/node/943212
  if (isset($form_id)) {
    return;
  }

  // Grab the current theme name.
  $theme = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : '';

  // Display recommended modules for this theme.
  $recommended_modules = glacier_recommended_modules();

  if (!empty($recommended_modules)) {
    $hide = theme_get_setting('hide_recommended_modules');

    $form['recommended_modules'] = array(
      '#type' => 'fieldset',
      '#title' => t('Recommended modules'),
      '#collapsible' => TRUE,
      '#collapsed' => $hide,
      '#description' => t('Modules marked as required should be download and enabled in order to get the most out of this theme.'),
      '#weight' => -1000,
      '#attributes' => array('class' => array('recommended-modules')),
      '#prefix' => '<div class="messages warning">',
      '#suffix' => '</div>',
    );

    $form['recommended_modules']['hide_recommended_modules'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide this warning by default.'),
      '#ajax' => array(
        'callback' => 'glacier_ajax_settings_save',
      ),
      '#default_value' => $hide,
    );

    foreach ($recommended_modules as $id => $module) {
      $form['recommended_modules'][$id] = array(
        '#type' => 'item',
        '#title' => l($module['name'], $module['link'], array('attributes' => array('target' => '_blank'))),
        '#description' => $module['description'],
        '#required' => $module['required'],
      );
    }
  }

  $form['options_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Theme specific settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['options_settings']['classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enable or disable the output of some class variations'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['options_settings']['classes']['classes_glacier'] = array(
    '#type' => 'checkbox',
    '#title' => t('Output glacier classes (BEM syntax).'),
    '#default_value' => theme_get_setting('classes_glacier'),
  );
  $form['options_settings']['classes']['classes_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Output Drupal default classes.'),
    '#description'   => t('Output core classes. Checking this will add a TON of classes everywhere, but it might fix problems caused by modules depending on those classes.'),
    '#default_value' => theme_get_setting('classes_default'),
  );
  $form['options_settings']['classes']['classes_first_last'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add first/last classes to menu items.'),
    '#default_value' => theme_get_setting('classes_first_last'),
  );

  $form['options_settings']['js_enhancement'] = array(
    '#type' => 'fieldset',
    '#title' => t('JS enhancements'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['options_settings']['js_enhancement']['js_enhancement_console'] = array(
    '#type' => 'checkbox',
    '#title' => t('Avoid "console" errors in browsers that lack a console.'),
    '#default_value' => theme_get_setting('js_enhancement_console'),
  );
  $form['options_settings']['js_enhancement']['js_enhancement_skiplink'] = array(
    '#type' => 'checkbox',
    '#title' => t('Normalize skiplink behaviour for all mandatory browsers.'),
    '#default_value' => theme_get_setting('js_enhancement_skiplink'),
  );

  $form['options_settings']['meta'] = array(
    '#type' => 'fieldset',
    '#title' => t('Meta enhancements'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['options_settings']['meta']['meta_format_detection'] = array(
    '#type' => 'checkbox',
    '#title' => t('Deactivate automatic iOS / Android phone number detection.'),
    '#default_value' => theme_get_setting('meta_format_detection'),
  );
  $form['options_settings']['meta']['meta_viewport'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add responsive viewport meta tag.'),
    '#default_value' => theme_get_setting('meta_viewport'),
  );
  $form['options_settings']['meta']['meta_ie_compatibility'] = array(
    '#type' => 'checkbox',
    '#title' => t('Deactivate IE compatibility mode.'),
    '#default_value' => theme_get_setting('meta_ie_compatibility'),
  );
  $form['options_settings']['meta']['meta_theme_color'] = array(
    '#type' => 'textfield',
    '#title' => t('theme-color'),
    '#description' => t('Browsers might color a web apps title bar with the specified "theme-color" value, or use it as a color highlight in a task switcher.'),
    '#attributes' => array('placeholder' => 'e.g. #efefef'),
    '#size' => 15,
    '#default_value' => theme_get_setting('meta_theme_color'),
  );
}

/**
 * Saves theme settings using ajax.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form. The arguments
 *   that drupal_get_form() was originally called with are available in the
 *   array $form_state['build_info']['args'].
 */
function glacier_ajax_settings_save($form = array(), $form_state = array()) {
  $theme = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : '';
  $theme_settings = variable_get('theme_' . $theme . '_settings', array());
  $trigger = $form_state['triggering_element']['#name'];

  $theme_settings[$trigger] = $form_state['input'][$trigger];

  if (empty($theme_settings[$trigger])) {
    $theme_settings[$trigger] = 0;
  }
  variable_set('theme_' . $theme . '_settings', $theme_settings);
}

/**
 * Returns an array of recommended modules.
 */
function glacier_recommended_modules() {
  $modules = array();

  if (!module_exists('glacier_system')) {
    $modules['glacier_system'] = array(
      'name' => t('Glacier System'),
      'description' => t('The glacier_system feature is the basis for a wide variety of features which make site building with Drupal faster an easier.'),
      'link' => 'https://github.com/maoberlehnerdrupal/glacier_system',
      'required' => TRUE,
    );
  }

  return $modules;
}
