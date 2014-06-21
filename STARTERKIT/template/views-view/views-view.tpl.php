<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
?>
<div class="<?php print $classes; ?>">
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($header): ?>
    <header class="view__header view--<?php print $css_name . '--' . $css_display; ?>__header">
      <?php print $header; ?>
    </header>
  <?php endif; ?>

  <?php if ($exposed): ?>
    <div class="view__filters view--<?php print $css_name . '--' . $css_display; ?>__filters">
      <?php print $exposed; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_before): ?>
    <div class="view__attachment view__attachment--before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <?php if ($rows): ?>
    <div class="view__content view--<?php print $css_name . '--' . $css_display; ?>__content">
      <?php print $rows; ?>
    </div>
  <?php elseif ($empty): ?>
    <div class="view__empty view--<?php print $css_name . '--' . $css_display; ?>__empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager): ?>
    <div class="view__pager view--<?php print $css_name . '--' . $css_display; ?>__pager">
      <?php print $pager; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="view__attachment view__attachment--after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <div class="view__more view--<?php print $css_name . '--' . $css_display; ?>__more">
      <?php print $more; ?>
    </div>
  <?php endif; ?>

  <?php if ($footer): ?>
    <footer class="view__footer view--<?php print $css_name . '--' . $css_display; ?>__footer">
      <?php print $footer; ?>
    </footer>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="view__feed-icon view--<?php print $css_name . '--' . $css_display; ?>__feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>
</div><?php /* class view */ ?>