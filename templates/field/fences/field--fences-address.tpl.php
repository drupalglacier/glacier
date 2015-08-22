<?php
/**
 * @file field--fences-address.tpl.php
 * Wrap each field value in the <address> element.
 *
 * @see http://developers.whatwg.org/sections.html#the-address-element
 */
?>
<address class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>><?php print $label; ?></div>
  <?php endif; ?>
  <?php foreach ($items as $delta => $item): ?>
    <?php if (!$item_wrapper_hidden): ?><div class="<?php print $item_classes; ?>"<?php print $item_attributes[$delta]; ?>><?php endif; ?>
      <?php print render($item); ?>
    <?php if (!$item_wrapper_hidden): ?></div><?php endif; ?>
  <?php endforeach; ?>
</address>
