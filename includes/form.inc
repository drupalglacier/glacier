<?php
/**
 * @file
 * Form-related functions.
 */

/**
 * Returns HTML for a form.
 */
function glacier_form($vars) {
  $element = $vars['element'];

  if (isset($element['#action'])) {
    $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
  }

  element_set_attributes($element, array('method', 'id'));

  if (empty($element['#attributes']['accept-charset'])) {
    $element['#attributes']['accept-charset'] = 'UTF-8';
  }

  $element['#attributes']['class'] = preg_replace_callback(
    array('/entityform/', '/entitytype-(.*?)(?=-form)/'),
    function ($match) {
      switch ($match[0]) {
        case 'entityform':
          return 'c-' . $match[0];

        default:
          return str_replace('_', '-', 'c-' . $match[1]);
      }
    },
    $element['#attributes']['class']
  );

  return '<form' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</form>';
}

/**
 * Implements hook_form_alter().
 */
function glacier_form_alter(&$form, &$form_state, $form_id) {
  // Move hidden build id and form id fields to the bottom.
  if (isset($form['form_build_id'])) {
    $form['form_build_id']['#weight'] = 9999;
  }
  if (isset($form['form_id'])) {
    $form['form_id']['#weight'] = 9999;
  }

  $form['#attributes']['class'] = array('c-form');
  // Add a spacing wrap utility class to add whitespace between form items.
  $form['#attributes']['class'][] = 'u-spacing-wrap';
}

/**
 * Returns HTML for a form element.
 */
function glacier_form_element($vars) {
  global $theme;

  $element = &$vars['element'];
  $element_type = !empty($element['#type']) ? $element['#type'] : '';
  $element_type_class = drupal_html_class($element_type);
  $element_name = !empty($element['#name']) ? $element['#name'] : '';
  $element_name_class = drupal_html_class($element_name);
  $classes_default = theme_get_setting('classes_default');

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $element['#attributes']['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $element['#attributes']['class'] = array('c-form__item');
  if (!empty($element['#type'])) {
    $element['#attributes']['class'][] = 'c-form__item--' . $element_type_class;

    // Add default core class if wanted.
    if ($classes_default) {
      $element['#attributes']['class'][] = 'form-type-' . $element_type_class;
    }
  }
  if (!empty($element['#name']) && $element_type_class !== $element_name_class) {
    $element['#attributes']['class'][] = 'c-form__item--' . $element_name_class;

    // Add default core class if wanted.
    if ($classes_default) {
      $element['#attributes']['class'][] = 'form-item-' . $element_name_class;
    }
  }

  // Add date-related classes.
  if (isset($element['#theme']) && $element['#theme'] == 'date_select_element') {
    $element['#attributes']['class'][] = 'form__item--date-select';
  }

  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'is-disabled';

    // Add default core class if wanted.
    if ($classes_default) {
      $element['#attributes']['class'][] = 'form-disabled';
    }
  }

  // Add class for required form items.
  if (isset($element['#required']) && $element['#required']) {
    $element['#attributes']['class'][] = 'is-required';
  }

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }

  // Set title display for a date field if todate is set.
  if (isset($element['#field']) && $element['#field']['settings']['todate']) {
    $element['#title_display'] = 'before';
    if (empty($vars['element']['#title'])) {
      $vars['element']['#title'] = t('from:');
    }
  }

  // Run custom form element alter function if the current theme implements one.
  $alter_function_name = $theme . '_form_element_alter';
  if (function_exists($alter_function_name)) {
    $alter_function_name($element);
  }

  // Add prefix and suffix.
  if (!$classes_default) {
    $prefix = isset($element['#field_prefix']) ? '<span class="c-form__prefix">' . $element['#field_prefix'] . '</span> ' : '';
    $suffix = isset($element['#field_suffix']) ? ' <span class="c-form__suffix">' . $element['#field_suffix'] . '</span>' : '';
  }
  else {
    $prefix = isset($element['#field_prefix']) ? '<span class="c-form__prefix field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
    $suffix = isset($element['#field_suffix']) ? ' <span class="c-form__suffix field-suffix">' . $element['#field_suffix'] . '</span>' : '';
  }

  $output = '<div' . drupal_attributes($element['#attributes']) . '>' . "\n";

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $vars);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $vars) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    if (!$classes_default) {
      $output .= '<div class="c-form__description u-font-size-s">' . $element['#description'] . "</div>\n";
    }
    else {
      $output .= '<div class="c-form__description description u-font-size-s">' . $element['#description'] . "</div>\n";
    }
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * Returns HTML for a form element label and required marker.
 */
function glacier_form_element_label($vars) {
  global $theme;
  $element = $vars['element'];

  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  // Don't output the label for certain types..
  if ($element['#type'] == 'radios' || $element['#type'] == 'checkboxes' || $element['#type'] == 'date') {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  $attributes = array();

  // Add default label class.
  $attributes['class'][] = 'c-form__label';

  // Add label position class.
  $attributes['class'][] = 'c-form__label--' . $vars['element']['#title_display'];

  // Style the label as class option to display inline with the element.
  if (theme_get_setting('classes_default') && $element['#title_display'] == 'after') {
    $attributes['class'] = 'option';
  }

  // Show label only to screen readers to avoid disruption in visual flows.
  if ($element['#title_display'] == 'invisible') {
    $attributes['class'][] = 'element-invisible';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // Run custom form element label attributes alter
  // function if the current theme implements one.
  $alter_function_name = $theme . '_form_element_label_attributes_alter';
  if (function_exists($alter_function_name)) {
    $alter_function_name($attributes);
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n";
}

/**
 * Returns HTML for a marker for required form elements.
 */
function glacier_form_required_marker($vars) {
  // This is also used in the installer, pre-database setup.
  $t = get_t();
  $attributes = array('class' => array('c-form__required-marker'));

  // Add default class if wanted.
  if (theme_get_setting('classes_default')) {
    $attributes['class'][] = 'form-required';
  }

  return '<span' . drupal_attributes($attributes) . '><span class="element-invisible">' . $t('This field is required.') . '</span></span>';
}

/**
 * Returns HTML for a button form element.
 */
function glacier_button($vars) {
  $element = $vars['element'];
  $element['#attributes']['type'] = $element['#button_type'];
  element_set_attributes($element, array('id', 'name', 'value'));
  $classes_default = theme_get_setting('classes_default');

  // Add button classes.
  $element['#attributes']['class'][] = 'c-button';

  // Adjust classes for reset buttons.
  if (isset($element['#id']) && $element['#id'] == 'edit-reset') {
    $element['#attributes']['class'][] = 'c-button--reset';
  }
  else {
    $element['#attributes']['class'][] = 'c-button--' . drupal_html_class($element['#button_type']);
  }

  // Add default class if wanted.
  if ($classes_default) {
    $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  }

  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'is-disabled';

    // Add default class if wanted.
    if ($classes_default) {
      $element['#attributes']['class'][] = 'form-button-disabled';
    }
  }

  $element['#attributes']['value'] = strip_tags($element['#value']);
  return '<button' . drupal_attributes($element['#attributes']) . '>' . $element['#value'] . '</button>';
}

/**
 * Returns HTML for a checkbox form element.
 */
function glacier_checkbox($vars) {
  $element = $vars['element'];
  $element['#attributes']['type'] = 'checkbox';
  element_set_attributes($element, array(
    0 => 'id',
    1 => 'name',
    '#return_value' => 'value',
  ));

  // Unchecked checkbox has #value of integer 0.
  if (!empty($element['#checked'])) {
    $element['#attributes']['checked'] = 'checked';
  }
  _glacier_form_set_class($element, array('c-form__checkbox'));

  return '<input' . drupal_attributes($element['#attributes']) . '>';
}

/**
 * Returns HTML for a set of checkbox form elements.
 */
function glacier_checkboxes($vars) {
  $element = $vars['element'];
  $attributes = array();

  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }

  $attributes['class'][] = 'c-form__fieldset';

  if (!empty($element['#attributes']['class'])) {
    $attributes['class'] = array_merge($attributes['class'], $element['#attributes']['class']);
  }

  if (isset($element['#attributes']['title'])) {
    $attributes['title'] = $element['#attributes']['title'];
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $legend = isset($element['#title']) ? '<legend class="c-form__legend">' . $element['#title'] . ' ' . $required . '</legend>' : '';

  return '<fieldset' . drupal_attributes($attributes) . '>' . $legend . (!empty($element['#children']) ? $element['#children'] : '') . '</fieldset>';
}

/**
 * Returns HTML to wrap child elements in a container.
 *
 * Implements theme_container().
 */
function glacier_container($vars) {
  $element = $vars['element'];

  // Special handling for form elements.
  if (isset($element['#array_parents'])) {
    // Assign an html ID.
    if (!isset($element['#attributes']['id'])) {
      $element['#attributes']['id'] = $element['#id'];
    }
    // Add the 'form-wrapper' class.
    array_unshift($element['#attributes']['class'], 'c-form__field');
  }

  $element['#attributes']['class'] = preg_replace('#^field-#', 'c-form__field--', $element['#attributes']['class']);

  // Add default class if wanted.
  if (theme_get_setting('classes_default')) {
    $element['#attributes']['class'][] = 'form-wrapper';
  }

  return '<div' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</div>';
}

/**
 * Returns HTML for a date selection form element.
 */
function glacier_date($vars) {
  $element = $vars['element'];

  $attributes = array();

  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }

  if (!empty($element['#attributes']['class'])) {
    $attributes['class'] = (array) $element['#attributes']['class'];
  }

  $attributes['class'][] = 'c-form__fieldset';

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $legend = isset($element['#title']) ? '<legend class="c-form__legend">' . $element['#title'] . ' ' . $required . '</legend>' : '';

  return '<fieldset' . drupal_attributes($attributes) . '>' . $legend . drupal_render_children($element) . '</fieldset>';
}

/**
 * Returns HTML for a start/end date combination on form.
 */
function glacier_date_combo($vars) {
  $element = $vars['element'];
  $field = field_info_field($element['#field_name']);
  $instance = field_info_instance($element['#entity_type'], $element['#field_name'], $element['#bundle']);
  $type = $element['value']['#type'];
  $classes_default = theme_get_setting('classes_default');

  $title = t($element['#title']) . ' ' . ($element['#delta'] > 0 ? intval($element['#delta'] + 1) : '');

  // Define wrapper attributes.
  $wrapper_attributes = array();
  $wrapper_attributes['class'] = array('form-item');
  $wrapper_attributes['class'][] = 'c-form__' . drupal_html_class($type);

  if ($element['#required']) {
    $wrapper_attributes['class'][] = 'is-required';
  }

  // Define fieldset attributes.
  $fieldset_attributes = array();

  if (isset($element['#id'])) {
    $fieldset_attributes['id'] = $element['#id'];
  }

  if (!empty($element['#attributes']['class'])) {
    $fieldset_attributes['class'] = (array) $element['#attributes']['class'];
  }

  $fieldset_attributes['class'][] = 'c-form__fieldset';

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  // Set markup for description.
  if (!$classes_default) {
    $description = !empty($element['#fieldset_description']) ? '<div class="c-form__description">' . $element['#fieldset_description'] . '</div>' : '';
  }
  else {
    $description = !empty($element['#fieldset_description']) ? '<div class="c-form__description description">' . $element['#fieldset_description'] . '</div>' : '';
  }

  $legend = isset($element['#title']) ? '<legend class="c-form__legend">' . $title . ' ' . $required . '</legend>' : '';

  return '<div' . drupal_attributes($wrapper_attributes) . '><fieldset' . drupal_attributes($fieldset_attributes) . '>' . $legend . $element['#children'] . '</fieldset>' . $description . '</div>';
}

/**
 * Returns HTML for a fieldset form element and its children.
 */
function glacier_fieldset($vars) {
  $element = $vars['element'];
  element_set_attributes($element, array('id'));
  $classes_default = theme_get_setting('classes_default');

  if (isset($element['#attributes']['class'])) {
    if (!is_array($element['#attributes']['class'])) {
      $element['#attributes']['class'] = array($element['#attributes']['class']);
    }
  }
  else {
    $element['#attributes']['class'] = array();
  }

  // Remove default collapsible classes.
  if (!$classes_default) {
    $element['#attributes']['class'] = array_values(array_diff($element['#attributes']['class'], array(
      'collapsible',
      'collapsed',
    )));
  }

  // Add custom collapsible classes.
  if (isset($element['#collapsible']) && $element['#collapsible']) {
    $element['#attributes']['class'][] = 'js-collapsible';
    $element['#attributes']['class'][] = 'is-collapsible';

    if ($element['#collapsed']) {
      $element['#attributes']['class'][] = 'is-collapsed';
    }
  }

  if (!$classes_default) {
    _glacier_form_set_class($element, array('c-form__fieldset'));
  }
  else {
    _form_set_class($element, array('c-form__fieldset', 'form-wrapper'));
  }

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
  if (!empty($element['#title'])) {
    // Always wrap fieldset legends in a SPAN for CSS positioning.
    if (!$classes_default) {
      $output .= '<legend class="c-form__fieldset-legend"><span class="c-form__fieldset-text">' . $element['#title'] . '</span></legend>';
    }
    else {
      $output .= '<legend class="c-form__fieldset-legend"><span class="c-__fieldset-text fieldset-legend">' . $element['#title'] . '</span></legend>';
    }
  }

  if (!$classes_default) {
    $output .= '<div class="c-form__fieldset-content">';
  }
  else {
    $output .= '<div class="c-form__fieldset-content fieldset-wrapper">';
  }

  if (!empty($element['#description'])) {
    if (!$classes_default) {
      $output .= '<div class="c-form__fieldset-description">' . $element['#description'] . '</div>';
    }
    else {
      $output .= '<div class="c-form__fieldset-description fieldset-description">' . $element['#description'] . '</div>';
    }
  }

  $output .= $element['#children'];

  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }

  $output .= '</div>';
  $output .= "</fieldset>\n";

  return $output;
}

/**
 * Returns HTML for a file upload form element.
 */
function glacier_file($vars) {
  $element = $vars['element'];
  $element['#attributes']['type'] = 'file';
  element_set_attributes($element, array('id', 'name', 'size'));

  _glacier_form_set_class($element, array('c-form__file'));

  return '<input' . drupal_attributes($element['#attributes']) . '>';
}

/**
 * Returns HTML for a password form element.
 */
function glacier_password($vars) {
  $element = $vars['element'];
  $element['#attributes']['type'] = 'password';
  $element['#attributes']['autocapitalize'] = 'off';
  $element['#attributes']['autocorrect'] = 'off';
  element_set_attributes($element, array('id', 'name', 'size', 'maxlength'));

  _glacier_form_set_class($element, array('c-form__text'));

  return '<input' . drupal_attributes($element['#attributes']) . '>';
}

/**
 * Returns HTML for a radio button form element.
 */
function glacier_radio($vars) {
  $element = $vars['element'];
  $element['#attributes']['type'] = 'radio';
  element_set_attributes($element, array(
    0 => 'id',
    1 => 'name',
    '#return_value' => 'value',
  ));

  if (isset($element['#return_value']) && $element['#value'] !== FALSE && $element['#value'] == $element['#return_value']) {
    $element['#attributes']['checked'] = 'checked';
  }
  _glacier_form_set_class($element, array('c-form__radio'));

  return '<input' . drupal_attributes($element['#attributes']) . '>';
}

/**
 * Returns HTML for a set of radio button form elements.
 */
function glacier_radios($vars) {
  $element = $vars['element'];
  $attributes = array();

  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }

  $attributes['class'] = 'c-form__fieldset';

  if (!empty($element['#attributes']['class'])) {
    $attributes['class'] .= ' ' . implode(' ', $element['#attributes']['class']);
  }

  if (isset($element['#attributes']['title'])) {
    $attributes['title'] = $element['#attributes']['title'];
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $legend = isset($element['#title']) ? '<legend class="c-form__legend">' . $element['#title'] . ' ' . $required . '</legend>' : '';

  return '<fieldset' . drupal_attributes($attributes) . '>' . $legend . (!empty($element['#children']) ? $element['#children'] : '') . '</fieldset>';
}

/**
 * Returns HTML for a select form element.
 */
function glacier_select($vars) {
  $element = $vars['element'];
  element_set_attributes($element, array('id', 'name', 'size'));

  _glacier_form_set_class($element, array('c-form__select'));

  return '<select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select>';
}

/**
 * Returns HTML for a table with radio buttons or checkboxes.
 */
function glacier_tableselect($vars) {
  $element = $vars['element'];
  $rows = array();
  $header = $element['#header'];
  if (!empty($element['#options'])) {
    // Generate a table row for each selectable item in #options.
    foreach (element_children($element) as $key) {
      $row = array();

      $row['data'] = array();
      if (isset($element['#options'][$key]['#attributes'])) {
        $row += $element['#options'][$key]['#attributes'];
      }
      // Render the checkbox / radio element.
      $row['data'][] = drupal_render($element[$key]);

      // As theme_table only maps header and row columns by order, create the
      // correct order by iterating over the header fields.
      foreach ($element['#header'] as $fieldname => $title) {
        $row['data'][] = $element['#options'][$key][$fieldname];
      }
      $rows[] = $row;
    }
    // Add an empty header or a "Select all" checkbox to provide room for the
    // checkboxes/radios in the first table column.
    if ($element['#js_select']) {
      // Add a "Select all" checkbox.
      drupal_add_js('misc/tableselect.js');
      array_unshift($header, array('class' => array('select-all')));
    }
    else {
      // Add an empty header when radio buttons are displayed or a "Select all"
      // checkbox is not desired.
      array_unshift($header, '');
    }
  }

  return theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'empty' => $element['#empty'],
    'attributes' => $element['#attributes'],
  ));
}

/**
 * Returns HTML for a textarea form element.
 */
function glacier_textarea($vars) {
  $element = $vars['element'];
  element_set_attributes($element, array(
    'id',
    'name',
    'cols',
    'rows',
  ));

  _glacier_form_set_class($element, array('c-form__textarea'));

  return '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
}

/**
 * Returns HTML for a textfield form element.
 */
function glacier_textfield($vars) {
  $element = $vars['element'];
  $element['#attributes']['type'] = 'text';
  $element['#attributes']['autocapitalize'] = 'off';
  $element['#attributes']['autocorrect'] = 'off';
  element_set_attributes($element, array(
    'id',
    'name',
    'value',
    'size',
    'maxlength',
  ));

  _glacier_form_set_class($element, array('c-form__text'));

  $extra = '';
  if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . '>';
  }

  $output = '<input' . drupal_attributes($element['#attributes']) . '>';

  return $output . $extra;
}

/**
 * Returns HTML for a image upload form element.
 */
function glacier_image_widget($vars) {
  $element = $vars['element'];
  $output = '';
  $output .= '<div class="c-image-widget image-widget form-managed-file">';

  if (isset($element['preview'])) {
    $output .= '<div class="c-image-widget__preview image-preview">';
    $output .= drupal_render($element['preview']);
    $output .= '</div>';
  }

  $output .= '<div class="c-image-widget__data image-widget-data">';
  if ($element['fid']['#value'] != 0) {
    $element['filename']['#markup'] .= ' <span class="c-image-widget__file-size">(' . format_size($element['#file']->filesize) . ')</span> ';
  }
  $output .= drupal_render_children($element);
  $output .= '</div>';
  $output .= '</div>';

  return $output;
}

/**
 * Sets a form element's class attribute.
 *
 * Adds 'is-required' and 'is-error' classes as needed.
 *
 * @param array $element
 *   The form element.
 * @param array $class
 *   Array of new class names to be added.
 */
function _glacier_form_set_class(&$element = array(), $class = array()) {
  $classes_default = theme_get_setting('classes_default');

  if (!empty($class)) {
    if (!isset($element['#attributes']['class'])) {
      $element['#attributes']['class'] = array();
    }
    $element['#attributes']['class'] = array_merge($element['#attributes']['class'], $class);
  }
  // This function is invoked from form element theme functions, but the
  // rendered form element may not necessarily have been processed by
  // form_builder().
  if (!empty($element['#required'])) {
    $element['#attributes']['class'][] = 'is-required';

    // Add default core class if wanted.
    if ($classes_default) {
      $element['#attributes']['class'][] = 'required';
    }
  }
  if (isset($element['#parents']) && form_get_error($element) !== NULL && !empty($element['#validated'])) {
    $element['#attributes']['class'][] = 'is-error';

    // Add default core class if wanted.
    if ($classes_default) {
      $element['#attributes']['class'][] = 'error';
    }
  }
}
