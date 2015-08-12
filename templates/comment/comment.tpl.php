<?php
/**
 * @file
 * Theme implementation for comments.
 */

$classes = glacier_classes(
  array(),
  $classes_array
);

$title_classes = glacier_classes(
  array(
    'c-comment__title',
  ),
  $title_classes_array
);

$content_classes = glacier_classes(
  array(
    'c-comment__content',
  ),
  $content_classes_array
);

hide($content['links']);

?>
<article class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>

  <?php if ($new): ?>
    <mark class="c-comment__new"><?php print $new; ?></mark>
  <?php endif; ?>

  <h3 class="<?php print $title_classes; ?>"<?php print $title_attributes; ?>>
    <?php print $title; ?>
  </h3>

  <?php print render($title_suffix); ?>

  <footer>
    <?php print $user_picture; ?>
    <p class="c-comment__submitted">
      <cite class="c-comment__author"><?php print $author; ?></cite>
      <?php print $created; ?>
    </p>
    <?php print $permalink; ?>
  </footer>

  <div class="<?php print $content_classes; ?>"<?php print $content_attributes; ?>>
    <?php print render($content); ?>

    <?php if ($signature): ?>
    <aside class="c-comment__signature">
      <?php print $signature; ?>
    </aside>
    <?php endif; ?>
  </div>

  <?php print render($content['links']); ?>
</article>
