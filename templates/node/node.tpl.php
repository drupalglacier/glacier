<?php
/**
 * @file
 * Theme implementation to display a single node.
 */

$classes = glacier_classes(
  array(
    // 'c-node',
    // 'c-node--' . $node_type_class,
    // 'c-node--' . $view_mode_class,
    'c-' . $node_type_class,
  ),
  $default_classes,
  $state_classes
);

$title_classes = glacier_classes(
  array(
    // 'c-node__title',
    'c-' . $node_type_class . '__title',
  ),
  $default_title_classes
);

$content_classes = glacier_classes(
  array(
    // 'c-node__content',
    'c-' . $node_type_class . '__content',
  ),
  $default_content_classes
);

hide($content['comments']);
hide($content['links']);

?>
<article class="<?php print $classes; ?>" role="article"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if (!$page && !empty($title)): ?>
    <h2 class="<?php print $title_classes; ?>"<?php print $title_attributes; ?>>
      <a href="<?php print $node_url; ?>" rel="bookmark"><?php print $title; ?></a>
    </h2>
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

  <div class="<?php print $content_classes; ?>"<?php print $content_attributes; ?>>
    <?php print render($content); ?>
  </div>

  <?php print render($content['links']); ?>
  <?php print render($content['comments']); ?>
</article>
