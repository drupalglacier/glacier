<?php
/**
 * @file
 * Wrap each field value in the <pre> and <code> elements.
 *
 * @see http://developers.whatwg.org/grouping-content.html#the-pre-element
 * @see http://developers.whatwg.org/text-level-semantics.html#the-code-element
 */
?>
<?php if (!$label_hidden): ?>
  <div class="<?php print $label_classes; ?>"<?php print $title_attributes; ?>><?php print $label; ?></div>
<?php endif; ?>
<pre class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php foreach ($items as $delta => $item): ?>
    <code class="<?php print $item_classes; ?>"<?php print $item_attributes[$delta]; ?>>
      <?php print render($item); ?>
    </code>
  <?php endforeach; ?>
</pre>
