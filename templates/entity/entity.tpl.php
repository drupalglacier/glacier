<?php
/**
 * @file
 * Theme implementation to display a single entity.
 */

$classes = glacier_classes(
  array(
    // 'c-entity',
    // 'c-entity--' . $type_class,
    // 'c-entity--' . $bundle_class,
    // 'c-entity--' . $view_mode_class,
    'c-' . $bundle_class,
  ),
  $classes_array
);

$title_classes = glacier_classes(
  array(
    // 'c-entity__title',
    'c-' . $bundle_class . '__title',
  ),
  $title_classes_array
);

$content_classes = glacier_classes(
  array(
    // 'c-entity__content',
    'c-' . $bundle_class . '__content',
  ),
  $content_classes_array
);

?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$page): ?>
    <h2 class="<?php print $title_classes; ?>"<?php print $title_attributes; ?>>
      <?php if ($url): ?>
        <a href="<?php print $url; ?>"><?php print $title; ?></a>
      <?php else: ?>
        <?php print $title; ?>
      <?php endif; ?>
    </h2>
  <?php endif; ?>

  <div class="<?php print $content_classes; ?>"<?php print $content_attributes; ?>>
    <?php print render($content); ?>
  </div>
</div>