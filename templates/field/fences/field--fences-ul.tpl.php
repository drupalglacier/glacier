<?php
/**
 * @file field--fences-ul.tpl.php
 * Wrap each field value in the <li> element and all of them in the <ul> element.
 *
 * @see http://developers.whatwg.org/grouping-content.html#the-ul-element
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
<?php if ($label_display == 'inline'): ?>
  <span class="<?php print $label_classes; ?> <?php print $prefix_utility; ?>display-inline"<?php print $title_attributes; ?>>
    <?php print $label; ?>:
  </span>
<?php elseif ($label_display == 'above'): ?>
  <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>>
    <?php print $label; ?>
  </div>
<?php endif; ?>

<ul class="<?php print $classes . ($label_display == 'inline' ? ' ' . $prefix_utility . 'display-inline' : ''); ?>"<?php print $attributes; ?>>
  <?php foreach ($items as $delta => $item): ?>
    <li class="<?php print $item_classes; ?>"<?php print $item_attributes[$delta]; ?>>
      <?php print render($item); ?>
    </li>
  <?php endforeach; ?>
</ul>
