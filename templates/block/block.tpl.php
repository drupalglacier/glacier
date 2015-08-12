<?php
/**
 * @file
 * Theme implementation to display a single block.
 */

$classes = glacier_classes(
  array(
    // 'c-block',
    // 'c-block--' . $module_class,
    // 'c-block--' . $delta_class,
    'c-' . $delta_class,
  ),
  $classes_array
);

$title_classes = glacier_classes(
  array(
    // 'c-block__title',
    'c-' . $delta_class . '__title',
  ),
  $title_classes_array
);

$content_classes = glacier_classes(
  array(
    // 'c-block__content',
    'c-' . $delta_class . '__content',
  ),
  $content_classes_array
);

?>
<div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if ($block->subject): ?>
    <h2 class="<?php print $title_classes; ?>"<?php print $title_attributes; ?>><?php print $block->subject ?></h2>
  <?php endif;?>
  <?php print render($title_suffix); ?>

  <?php /*<div class="<?php print $content_classes; ?>"<?php print $content_attributes; ?>>*/ ?>
    <?php print $content ?>
  <?php /*</div>*/ ?>
</div>
