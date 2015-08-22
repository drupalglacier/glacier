<?php
/**
 * @file field--fences-ol.tpl.php
 * Wrap each field value in the <li> element and all of them in the <ol> element.
 *
 * @see http://developers.whatwg.org/grouping-content.html#the-ol-element
 */
?>
<?php if (!$label_hidden): ?>
  <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>><?php print $label; ?></div>
<?php endif; ?>
<ol class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php foreach ($items as $delta => $item): ?>
    <li class="<?php print $item_classes; ?>"<?php print $item_attributes[$delta]; ?>>
      <?php print render($item); ?>
    </li>
  <?php endforeach; ?>
</ol>
