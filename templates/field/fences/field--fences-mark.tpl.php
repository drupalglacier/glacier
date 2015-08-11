<?php
/**
 * @file field--fences-mark.tpl.php
 * Wrap each field value in the <mark> element.
 *
 * @see http://developers.whatwg.org/text-level-semantics.html#the-mark-element
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
<?php if (!$wrapper_hidden): ?><div class="<?php print $classes; ?>"><?php endif; ?>
  <?php if ($label_display == 'inline'): ?>
    <span class="<?php print $label_classes; ?> u-display-inline"<?php print $title_attributes; ?>>
      <?php print $label; ?>:
    </span>
  <?php elseif ($label_display == 'above'): ?>
    <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>>
      <?php print $label; ?>
    </div>
  <?php endif; ?>

  <?php foreach ($items as $delta => $item): ?>
    <mark class="<?php print ($wrapper_hidden ? $classes : $item_classes) . ($label_display == 'inline' ? ' ' . 'u-display-inline' : ''); ?>"<?php print ($wrapper_hidden ? $attributes : $item_attributes[$delta]); ?>>
      <?php print render($item); ?>
    </mark>
  <?php endforeach; ?>
<?php if (!$wrapper_hidden): ?></div><?php endif; ?>
