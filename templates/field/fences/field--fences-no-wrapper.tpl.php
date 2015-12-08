<?php
/**
 * @file
 * Render each field value with no wrapper element.
 */
?>
<?php if (!$label_hidden): ?>
  <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>><?php print $label; ?></div>
<?php endif; ?>
<?php foreach ($items as $delta => $item): ?>
  <?php print render($item); ?>
<?php endforeach; ?>
