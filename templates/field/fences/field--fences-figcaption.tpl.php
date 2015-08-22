<?php
/**
 * @file field--fences-figcaption.tpl.php
 * Wrap all field values in a single <figcaption> element.
 *
 * @see http://developers.whatwg.org/grouping-content.html#the-figcaption-element
 *
 * Only one figcaption is allowed per figure element, so multiple field values
 * are placed within a single figcaption.
 */
?>
<figcaption class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>><?php print $label; ?></div>
  <?php endif; ?>
  <?php foreach ($items as $delta => $item): ?>
    <?php if (!$item_wrapper_hidden): ?><div class="<?php print $item_classes; ?>"<?php print $item_attributes[$delta]; ?>><?php endif; ?>
      <?php print render($item); ?>
    <?php if (!$item_wrapper_hidden): ?></div><?php endif; ?>
  <?php endforeach; ?>
</figcaption>
