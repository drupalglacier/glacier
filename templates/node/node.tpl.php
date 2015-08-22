<?php
/**
 * @file
 * Theme implementation to display a single node.
 */

hide($content['comments']);
hide($content['links']);

?>
<<?php print $wrapper_tag; ?> class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if (!$page && !empty($title)): ?>
    <<?php print $title_tag; ?> class="<?php print $title_classes; ?>"<?php print $title_attributes; ?>>
      <a href="<?php print $node_url; ?>" rel="bookmark"><?php print $title; ?></a>
    </<?php print $title_tag; ?>>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if (!$status): ?>
    <div class="<?php print 'c-' . $node_type_class; ?>__unpublished"><?php print t('Unpublished'); ?></div>
  <?php endif; ?>

  <?php if ($display_submitted): ?>
    <footer class="<?php print 'c-' . $node_type_class; ?>__submitted">
      <?php print $user_picture; ?>
      <p><?php print $submitted; ?></p>
    </footer>
  <?php endif; ?>

  <?php if (!$content_wrapper_hidden): ?><div class="<?php print $content_classes; ?>"<?php print $content_attributes; ?>><?php endif; ?>
    <?php print render($content); ?>
  <?php if (!$content_wrapper_hidden): ?></div><?php endif; ?>

  <?php print render($content['links']); ?>
  <?php print render($content['comments']); ?>
</<?php print $wrapper_tag; ?>>
