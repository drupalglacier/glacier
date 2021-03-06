<?php
/**
 * @file
 * Default simple view template to display a list of rows.
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print trim($title); ?></h3>
<?php endif; ?>

<?php foreach ($rows as $id => $row): ?>
  <?php if ($classes_array[$id]): ?><div class="<?php print $classes_array[$id]; ?>"><?php endif; ?>
    <?php print $row; ?>
  <?php if ($classes_array[$id]): ?></div><?php endif; ?>
<?php endforeach; ?>
