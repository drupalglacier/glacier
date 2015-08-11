<?php
/**
 * @file field--fences-dl.tpl.php
 * Wrap all field values in a single <dl> element.
 *
 * @see http://developers.whatwg.org/grouping-content.html#the-dl-element
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

<dl class="<?php print $classes . ($label_display == 'inline' ? ' ' . 'u-display-inline' : ''); ?>"<?php print $attributes; ?>>
  <?php foreach ($items as $delta => $item): ?>
    <?php print render($item); ?>
  <?php endforeach; ?>
</dl>
