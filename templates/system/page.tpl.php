<?php
/**
 * @file
 * Theme implementation to display a single Drupal page.
 */
?>
<?php if ($page['header'] || render($page['navigation'])): ?>
  <header class="c-main-header" role="banner">
    <?php print render($page['header']); ?>
    <?php print render($page['navigation']); ?>
  </header>
<?php endif; ?>

<?php if ($page['content']): ?>
  <main id="main" class="c-main-content" role="main" tabindex="-1">
    <?php print render($page['content']); ?>
  </main>
<?php endif; ?>

<?php if ($page['postscript']): ?>
  <div class="c-postscript">
    <?php print render($page['postscript']); ?>
  </div>
<?php endif; ?>

<?php if ($page['footer']): ?>
  <footer class="c-main-footer" role="contentinfo">
    <?php print render($page['footer']); ?>
  </footer>
<?php endif; ?>
