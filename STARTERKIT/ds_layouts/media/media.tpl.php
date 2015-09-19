<?php
/**
 * @file
 * card.tpl.php
 */
?>
<<?php print $layout_wrapper; ?> class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
  
  <?php if ($header && $header != '&nbsp;'): ?>
    <<?php print $header_wrapper; ?> class="c-header<?php print $header_classes; ?>"><?php print $header; ?></<?php print $header_wrapper; ?>>
  <?php endif; ?>
  <div class="o-media o-media--mobile-reset">
    <?php if ($figure && $figure != '&nbsp;'): ?>
      <<?php print $figure_wrapper; ?> class="o-media__figure<?php print $figure_classes; ?>"><?php print $figure; ?></<?php print $figure_wrapper; ?>>
    <?php endif; ?>

    <?php if ($body && $body != '&nbsp;'): ?>
      <<?php print $body_wrapper; ?> class="o-media__body<?php print $body_classes; ?>"><?php print $body; ?></<?php print $body_wrapper; ?>>
    <?php endif; ?>
  </div>
  <?php if ($footer && $footer != '&nbsp;'): ?>
    <<?php print $footer_wrapper; ?> class="c-footer<?php print $footer_classes; ?>"><?php print $footer; ?></<?php print $footer_wrapper; ?>>
  <?php endif; ?>
</<?php print $layout_wrapper; ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
