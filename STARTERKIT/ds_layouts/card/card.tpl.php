<?php
/**
 * @file
 * card.tpl.php
 */
?>
<<?php print $layout_wrapper; ?> class="c-card <?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
  
  <?php if ($figure && $figure != '&nbsp;'): ?>
    <<?php print $figure_wrapper; ?> class="c-card__figure<?php print $figure_classes; ?>"><?php print $figure; ?></<?php print $figure_wrapper; ?>>
  <?php endif; ?>

  <?php if ($island && $island != '&nbsp;'): ?>
    <<?php print $island_wrapper; ?> class="o-island<?php print $island_classes; ?>"><?php print $island; ?></<?php print $island_wrapper; ?>>
  <?php endif; ?>
</<?php print $layout_wrapper; ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
