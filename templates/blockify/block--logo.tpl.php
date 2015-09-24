<?php
/**
 * @file
 * Theme implementation to display a blockify logo block.
 */
?>
<span class="c-site-logo <?php print $classes; ?>">
  <a class="c-site-logo__link" href="<?php print $front_page; ?>" rel="home">
    <?php print render($logo); ?>
  </a>
</span>
