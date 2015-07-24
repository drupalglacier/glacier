<?php
/**
 * @file
 * Main view template.
 */
?>
<div class="<?php print $classes; ?>">
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($header): ?>
    <div class="<?php print $bem_prefix_component; ?>view__header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($exposed): ?>
    <div class="<?php print $bem_prefix_component; ?>view__filters">
      <?php print $exposed; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_before): ?>
    <div class="<?php print $bem_prefix_component; ?>view__attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <?php if ($rows): ?>
    <div class="<?php print $bem_prefix_component; ?>view__content">
      <?php print $rows; ?>
    </div>
  <?php elseif ($empty): ?>
    <div class="<?php print $bem_prefix_component; ?>view__content is-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager): ?>
    <?php print $pager; ?>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="<?php print $bem_prefix_component; ?>view__attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <div class="<?php print $bem_prefix_component; ?>view__more">
      <?php print $more; ?>
    </div>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="<?php print $bem_prefix_component; ?>view__footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <?php print $feed_icon; ?>
  <?php endif; ?>
</div>
