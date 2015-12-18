<?php
/**
 * @file
 * Main view template.
 */
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($header): ?>
    <div class="<?php print $header_classes; ?>">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($exposed): ?>
    <div class="<?php print $filters_classes; ?>">
      <?php print $exposed; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_before): ?>
    <div class="<?php print $attachment_before_classes; ?>">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <div class="<?php print $content_classes; ?>">
    <?php if ($rows): ?>
      <?php print $rows; ?>
    <?php elseif ($empty): ?>
      <?php print $empty; ?>
    <?php endif; ?>
  </div>

  <?php if ($pager): ?>
    <div class="<?php print $pager_classes; ?>">
      <?php print $pager; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="<?php print $attachment_after_classes; ?>">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <div class="<?php print $more_classes; ?>">
      <?php print $more; ?>
    </div>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="<?php print $footer_classes; ?>">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <?php print $feed_icon; ?>
  <?php endif; ?>
</div>
