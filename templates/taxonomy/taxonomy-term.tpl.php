<?php
/**
 * @file
 * Theme implementation to display a single taxonomy term.
 */
?>
<<?php print $wrapper_tag; ?> class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$page): ?>
    <<?php print $title_tag; ?> class="<?php print $title_classes; ?>"<?php print $title_attributes; ?>>
      <a href="<?php print $term_url; ?>"><?php print $term_name; ?></a>
    </<?php print $title_tag; ?>>
  <?php endif; ?>
  <?php if (!$content_wrapper_hidden): ?><div class="<?php print $content_classes; ?>"<?php print $content_attributes; ?>><?php endif; ?>
    <?php print render($content); ?>
  <?php if (!$content_wrapper_hidden): ?></div><?php endif; ?>
</<?php print $wrapper_tag; ?>>
