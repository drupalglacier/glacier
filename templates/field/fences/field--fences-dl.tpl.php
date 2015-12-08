<?php
/**
 * @file
 * Wrap all field values in a single <dl> element.
 *
 * @see http://developers.whatwg.org/grouping-content.html#the-dl-element
 */
?>
<?php if (!$label_hidden): ?>
  <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>><?php print $label; ?></div>
<?php endif; ?>
<dl class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php foreach ($items as $delta => $item): ?>
    <?php print render($item); ?>
  <?php endforeach; ?>
</dl>
