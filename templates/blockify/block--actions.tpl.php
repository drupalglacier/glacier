<?php
/**
 * @file
 * Theme implementation to display a blockify actions block.
 */
?>
<?php if (!empty($actions)): ?>
  <ul class="<?php print $classes; ?>">
    <?php print render($actions); ?>
  </ul>
<?php endif; ?>
