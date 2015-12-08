<?php
/**
 * @file
 * Display Suite 3 column 25/50/25 template.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="<?php print $classes;?>">
  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <div class="o-grid o-grid--spaced">
    <?php if ($left && $left != '&nbsp;'): ?>
      <<?php print $left_wrapper ?> class="o-grid__item u-width--12 u-width--m--3<?php print $left_classes;?>"><?php print $left; ?></<?php print $left_wrapper ?>>
    <?php endif; ?>

    <?php if ($middle && $middle != '&nbsp;'): ?>
      <<?php print $middle_wrapper ?> class="o-grid__item u-width--12 u-width--m--6<?php print $middle_classes;?>"><?php print $middle; ?></<?php print $middle_wrapper ?>>
    <?php endif; ?>

    <?php if ($right && $right != '&nbsp;'): ?>
      <<?php print $right_wrapper ?> class="o-grid__item u-width--12 u-width--m--3<?php print $right_classes;?>"><?php print $right; ?></<?php print $right_wrapper ?>>
    <?php endif; ?>
  </div>
</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
