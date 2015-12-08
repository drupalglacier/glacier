<?php
/**
 * @file
 * Display Suite 4 column template.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="<?php print $classes;?>">
  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <div class="o-grid o-grid--spaced">
    <?php if ($first && $first != '&nbsp;'): ?>
      <<?php print $first_wrapper ?> class="o-grid__item u-width--12 u-width--m--3<?php print $first_classes; ?>"><?php print $first; ?></<?php print $first_wrapper ?>>
    <?php endif; ?>

    <?php if ($second && $second != '&nbsp;'): ?>
      <<?php print $second_wrapper ?> class="o-grid__item u-width--12 u-width--m--3<?php print $second_classes; ?>"><?php print $second; ?></<?php print $second_wrapper ?>>
    <?php endif; ?>

    <?php if ($third && $third != '&nbsp;'): ?>
      <<?php print $third_wrapper ?> class="o-grid__item u-width--12 u-width--m--3<?php print $third_classes; ?>"><?php print $third; ?></<?php print $third_wrapper ?>>
    <?php endif; ?>

    <?php if ($fourth && $fourth != '&nbsp;'): ?>
      <<?php print $fourth_wrapper ?> class="o-grid__item u-width--12 u-width--m--3<?php print $fourth_classes; ?>"><?php print $fourth; ?></<?php print $fourth_wrapper ?>>
    <?php endif; ?>
  </div>
</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
