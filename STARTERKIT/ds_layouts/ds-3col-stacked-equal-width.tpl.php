<?php
/**
 * @file
 * Display Suite 3 column stacked template.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="<?php print $classes;?>">
  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if ($header && $header != '&nbsp;'): ?>
    <<?php print $header_wrapper ?> class="c-header<?php print $header_classes; ?>"><?php print $header; ?></<?php print $header_wrapper ?>>
  <?php endif; ?>

  <div class="o-grid o-grid--spaced">
    <?php if ($left && $left != '&nbsp;'): ?>
      <<?php print $left_wrapper ?> class="o-grid__item u-width--12 u-width--m--4<?php print $left_classes; ?>"><?php print $left; ?></<?php print $left_wrapper ?>>
    <?php endif; ?>

    <?php if ($middle && $middle != '&nbsp;'): ?>
      <<?php print $middle_wrapper ?> class="o-grid__item u-width--12 u-width--m--4<?php print $middle_classes; ?>"><?php print $middle; ?></<?php print $middle_wrapper ?>>
    <?php endif; ?>

    <?php if ($right && $right != '&nbsp;'): ?>
      <<?php print $right_wrapper ?> class="o-grid__item u-width--12 u-width--m--4<?php print $right_classes; ?>"><?php print $right; ?></<?php print $right_wrapper ?>>
    <?php endif; ?>
  </div>

  <?php if ($footer && $footer != '&nbsp;'): ?>
    <<?php print $footer_wrapper ?> class="c-footer<?php print $footer_classes; ?>"><?php print $footer; ?></<?php print $footer_wrapper ?>>
  <?php endif; ?>
</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
