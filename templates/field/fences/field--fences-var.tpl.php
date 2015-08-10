<?php
/**
 * @file field--fences-var.tpl.php
 * Wrap each field value in the <var> element.
 *
 * @see http://developers.whatwg.org/text-level-semantics.html#the-var-element
 */

$classes = glacier_classes(
  array(
    // $prefix_component . 'field',
    // $prefix_component . 'field--' . $field_name_css,
    // $prefix_component . 'field--' . $field_type_css,
    $prefix_component . $bundle_class . '__' . $field_name_css,
  ),
  $default_classes
);

$label_classes = glacier_classes(
  array(
    // $prefix_component . 'field--' . $field_name_css . '__label',
    // $prefix_component . 'field--' . $field_type_css . '__label',
    $prefix_component . $bundle_class . '__' . $field_name_css . '__label',
  ),
  $default_label_classes
);

$item_classes = glacier_classes(
  array(
    // $prefix_component . 'field--' . $field_name_css . '__item',
    // $prefix_component . 'field--' . $field_type_css . '__item',
    $prefix_component . $bundle_class . '__' . $field_name_css . '__item',
  ),
  $default_item_classes
);

?>
<?php if (!$wrapper_hidden): ?><div class="<?php print $classes; ?>"><?php endif; ?>
  <?php if ($label_display == 'inline'): ?>
    <span class="<?php print $label_classes; ?> <?php print $prefix_utility; ?>display-inline"<?php print $title_attributes; ?>>
      <?php print $label; ?>:
    </span>
  <?php elseif ($label_display == 'above'): ?>
    <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>>
      <?php print $label; ?>
    </div>
  <?php endif; ?>

  <?php foreach ($items as $delta => $item): ?>
    <var class="<?php print ($wrapper_hidden ? $classes : $item_classes) . ($label_display == 'inline' ? ' ' . $prefix_utility . 'display-inline' : ''); ?>"<?php print ($wrapper_hidden ? $attributes : $item_attributes[$delta]); ?>>
      <?php print render($item); ?>
    </var>
  <?php endforeach; ?>
<?php if (!$wrapper_hidden): ?></div><?php endif; ?>
