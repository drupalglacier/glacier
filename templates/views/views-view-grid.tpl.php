<?php
/**
 * @file
 * Default simple view template to display a rows in a grid.
 */
?>
<?php if (!empty($title)) : ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<div class="<?php print $class; ?>"<?php print $attributes; ?>>
  <?php foreach ($rows as $row_number => $columns): ?>
    <?php foreach ($columns as $column_number => $item): ?>
      <?php if (!empty($item)): ?>
        <div class="<?php print $bem_prefix_object; ?>grid__item<?php print ($column_classes[$row_number][$column_number]) ? ' ' . $column_classes[$row_number][$column_number] : '' ?>">
          <?php print $item; ?>
        </div>
      <?php endif; ?>
    <?php endforeach; ?>
  <?php endforeach; ?>
</div>
