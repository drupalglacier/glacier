<?php
/**
 * @file field--fences-menu.tpl.php
 * Wrap each field value in the <li> element and all of them in the <menu> element.
 *
 * @see http://developers.whatwg.org/interactive-elements.html#the-menu-element
 */

$classes = glacier_classes(
  array(
    // 'c-field',
    // 'c-field--' . $field_name_css,
    // 'c-field--' . $field_type_css,
    'c-' . $bundle_class . '__' . $field_name_css,
  ),
  $default_classes
);

$label_classes = glacier_classes(
  array(
    // 'c-field--' . $field_name_css . '__label',
    // 'c-field--' . $field_type_css . '__label',
    'c-' . $bundle_class . '__' . $field_name_css . '__label',
  ),
  $default_label_classes
);

$item_classes = glacier_classes(
  array(
    // 'c-field--' . $field_name_css . '__item',
    // 'c-field--' . $field_type_css . '__item',
    'c-' . $bundle_class . '__' . $field_name_css . '__item',
  ),
  $default_item_classes
);

?>
<?php if ($label_display == 'inline'): ?>
  <span class="<?php print $label_classes; ?> u-display-inline"<?php print $title_attributes; ?>>
    <?php print $label; ?>:
  </span>
<?php elseif ($label_display == 'above'): ?>
  <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>>
    <?php print $label; ?>
  </div>
<?php endif; ?>

<menu class="<?php print $classes . ($label_display == 'inline' ? ' ' . 'u-display-inline' : ''); ?>">
  <?php foreach ($items as $delta => $item): ?>
    <li class="<?php print $item_classes; ?>"<?php print $item_attributes[$delta]; ?>>
      <?php print render($item); ?>
    </li>
  <?php endforeach; ?>
</menu>
