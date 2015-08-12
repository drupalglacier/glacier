<?php
/**
 * @file
 * Theme implementation to provide an HTML container for comments.
 */

$classes = glacier_classes(
  array(
    'c-comments',
  ),
  $classes_array
);

$title_classes = glacier_classes(
  array(
    'c-comments__title',
  ),
  $title_classes_array
);

$form_title_classes = glacier_classes(
  array(
    'c-comments__title',
    'c-comments__title--form',
  ),
  $form_title_classes_array
);

// Render the comments and form first to see if we need headings.
$comments = render($content['comments']);
$comment_form = render($content['comment_form']);

?>
<section class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if ($comments && $node->type != 'forum'): ?>
    <?php print render($title_prefix); ?>
    <h2 class="<?php print $title_classes; ?>"<?php print $title_attributes ?>><?php print t('Comments'); ?></h2>
    <?php print render($title_suffix); ?>
  <?php endif; ?>

  <?php print $comments; ?>

  <?php if ($comment_form): ?>
    <h2 class="<?php print $form_title_classes; ?>"<?php print $form_title_attributes ?>><?php print t('Add new comment'); ?></h2>
    <?php print $comment_form; ?>
  <?php endif; ?>
</section>
