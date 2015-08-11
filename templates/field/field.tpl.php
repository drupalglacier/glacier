<?php
/**
 * @file
 * Theme implementation to display a field.
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
<div class="<?php print $classes; ?>">
  <?php if ($element['#label_display'] == 'inline'): ?>
    <span class="<?php print $label_classes; ?> u-display-inline"<?php print $title_attributes; ?>>
      <?php print $label; ?>:
    </span>
  <?php elseif ($element['#label_display'] == 'above'): ?>
    <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>>
      <?php print $label; ?>
    </div>
  <?php endif; ?>

  <?php foreach ($items as $delta => $item): ?>
    <?php if (!$label_hidden): ?><div class="<?php print $item_classes; ?>"<?php print $attributes; ?>><?php endif; ?>
      <?php print render($item); ?>
    <?php if (!$label_hidden): ?></div><?php endif; ?>
  <?php endforeach; ?>
</div>
