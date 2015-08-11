<?php
/**
 * @file
 * This template handles the layout of the views exposed filter form.
 */
?>
<?php if (!empty($q)): ?>
  <?php
    // This ensures that, if clean URLs are off, the 'q' is added first so that
    // it shows up first in the URL.
    print $q;
  ?>
<?php endif; ?>
<?php if ($bem_only): ?>
  <?php foreach ($widgets as $id => $widget): ?>
    <div id="<?php print $widget->id; ?>" class="c-view__widget c-view__widget--<?php print $id; ?>">
      <?php if (!empty($widget->label)): ?>
        <label class="c-view__widget__label" for="<?php print $widget->id; ?>">
          <?php print $widget->label; ?>
        </label>
      <?php endif; ?>
      <?php if (!empty($widget->operator)): ?>
        <div class="c-view__widget__operator">
          <?php print $widget->operator; ?>
        </div>
      <?php endif; ?>
      <?php print $widget->widget; ?>
      <?php if (!empty($widget->description)): ?>
        <div class="c-view__widget__description">
          <?php print $widget->description; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endforeach; ?>
  <?php if (!empty($sort_by)): ?>
    <div class="c-view__widget c-view__widget--sort-by">
      <?php print $sort_by; ?>
    </div>
    <div class="c-view__widget c-view__widget--sort-order">
      <?php print $sort_order; ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($items_per_page)): ?>
    <div class="c-view__widget c-view__widget--items-per-page">
      <?php print $items_per_page; ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($offset)): ?>
    <div class="c-view__widget c-view__widget--offset">
      <?php print $offset; ?>
    </div>
  <?php endif; ?>
  <div class="c-view__widget c-view__widget--submit">
    <?php print $button; ?>
  </div>
  <?php if (!empty($reset_button)): ?>
    <div class="c-view__widget c-view__widget--reset">
      <?php print $reset_button; ?>
    </div>
  <?php endif; ?>
<?php else: ?>
  <div class="c-view__exposed-form">
    <?php foreach ($widgets as $id => $widget): ?>
      <div id="<?php print $widget->id; ?>-wrapper" class="c-view__widget view__widget--<?php print $id; ?>">
        <?php if (!empty($widget->label)): ?>
          <label class="c-view__widget__label" for="<?php print $widget->id; ?>">
            <?php print $widget->label; ?>
          </label>
        <?php endif; ?>
        <?php if (!empty($widget->operator)): ?>
          <div class="c-view__widget__operator">
            <?php print $widget->operator; ?>
          </div>
        <?php endif; ?>
        <?php print $widget->widget; ?>
        <?php if (!empty($widget->description)): ?>
          <div class="c-view__widget__description">
            <?php print $widget->description; ?>
          </div>
        <?php endif; ?>
      </div>
    <?php endforeach; ?>
    <?php if (!empty($sort_by)): ?>
      <div class="c-view__widget c-view__widget--sort-by">
        <?php print $sort_by; ?>
      </div>
      <div class="c-view__widget c-view__widget--sort-order">
        <?php print $sort_order; ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($items_per_page)): ?>
      <div class="c-view__widget view__widget--items-per-page">
        <?php print $items_per_page; ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($offset)): ?>
      <div class="c-view__widget c-view__widget--offset">
        <?php print $offset; ?>
      </div>
    <?php endif; ?>
    <div class="c-view__widget c-view__widget--submit">
      <?php print $button; ?>
    </div>
    <?php if (!empty($reset_button)): ?>
      <div class="c-view__widget c-view__widget--reset">
        <?php print $reset_button; ?>
      </div>
    <?php endif; ?>
  </div>
<?php endif; ?>
