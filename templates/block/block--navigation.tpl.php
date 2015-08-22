<?php
/**
 * @file
 * Theme implementation to display a single block.
 */
?>
<nav id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if ($block->subject): ?>
    <<?php print $title_tag; ?> class="<?php print $title_classes; ?>"<?php print $title_attributes; ?>><?php print $block->subject ?></<?php print $title_tag; ?>>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if (!$content_wrapper_hidden): ?><div class="<?php print $content_classes; ?>"<?php print $content_attributes; ?>><?php endif; ?>
    <?php print $content ?>
  <?php if (!$content_wrapper_hidden): ?></div><?php endif; ?>
</nav>
