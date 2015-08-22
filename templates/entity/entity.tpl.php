<?php
/**
 * @file
 * Theme implementation to display a single entity.
 */
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$page): ?>
    <<?php print $title_tag; ?> class="<?php print $title_classes; ?>"<?php print $title_attributes; ?>>
      <?php if ($url): ?><a href="<?php print $url; ?>"><?php endif; ?><?php print $title; ?><?php if ($url): ?></a><?php endif; ?>
    </<?php print $title_tag; ?>>
  <?php endif; ?>
  <?php if ($content_wrapper_hidden): ?><div class="<?php print $content_classes; ?>"<?php print $content_attributes; ?>><?php endif; ?>
    <?php print render($content); ?>
  <?php if ($content_wrapper_hidden): ?></div><?php endif; ?>
</div>
