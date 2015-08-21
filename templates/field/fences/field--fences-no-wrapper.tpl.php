<?php
/**
 * @file field--fences-no-wrapper.tpl.php
 * Render each field value with no wrapper element.
 */
?>
<?php if (!$label_hidden): ?>
  <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>><?php print $label; ?></div>
<?php endif; ?>
<?php foreach ($items as $delta => $item): ?>
  <?php if (!$item_wrapper_hidden): ?><div class="<?php print $item_classes; ?>"<?php print $item_attributes[$delta]; ?>><?php endif; ?>
    <?php print render($item); ?>
  <?php if (!$item_wrapper_hidden): ?></div><?php endif; ?>
<?php endforeach; ?>
