<?php
/**
 * @file field--fences-ins.tpl.php
 * Wrap each field value in the <ins> element.
 *
 * @see http://developers.whatwg.org/edits.html#the-ins-element
 */
?>
<ins class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>><?php print $label; ?></div>
  <?php endif; ?>
  <?php foreach ($items as $delta => $item): ?>
    <?php if (!$item_wrapper_hidden): ?><div class="<?php print $item_classes; ?>"<?php print $item_attributes[$delta]; ?>><?php endif; ?>
      <?php print render($item); ?>
    <?php if (!$item_wrapper_hidden): ?></div><?php endif; ?>
  <?php endforeach; ?>
</ins>
