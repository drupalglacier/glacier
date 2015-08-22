<?php
/**
 * @file
 * Theme implementation to provide an HTML container for comments.
 */

// Render the comments and form first to see if we need headings.
$comments = render($content['comments']);
$comment_form = render($content['comment_form']);

?>
<section class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if ($comments && $node->type != 'forum'): ?>
    <?php print render($title_prefix); ?>
    <<?php print render($title_tag); ?> class="<?php print $title_classes; ?>"<?php print $title_attributes ?>><?php print t('Comments'); ?></<?php print render($title_tag); ?>>
    <?php print render($title_suffix); ?>
  <?php endif; ?>
  <?php print $comments; ?>

  <?php if ($comment_form): ?>
    <div class="c-comment__form">
      <<?php print render($form_title_tag); ?> class="<?php print $form_title_classes; ?>"<?php print $form_title_attributes ?>><?php print t('Add new comment'); ?></<?php print render($form_title_tag); ?>>
      <?php print $comment_form; ?>
    </div>
  <?php endif; ?>
</section>
