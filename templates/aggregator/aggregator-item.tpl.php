<?php
/**
 * @file
 * Theme implementation to format an individual feed item for display on the aggregator page.
 */
?>
<article class="c-feed-item">
  <header>
    <h3 class="c-feed-item__title">
      <a href="<?php print $feed_url; ?>"><?php print $feed_title; ?></a>
    </h3>

    <p class="c-feed-item__meta">
      <?php if ($source_url): ?>
        <a href="<?php print $source_url; ?>" class="c-feed-item__source"><?php print $source_title; ?></a> -
      <?php endif; ?>

      <time class="c-feed-item__date" datetime="<?php print $datetime; ?>"><?php print $source_date; ?></time>
    </p>
  </header>

  <?php if ($content): ?>
    <div class="c-feed-item__content">
      <?php print $content; ?>
    </div>
  <?php endif; ?>

  <?php if ($categories): ?>
    <footer>
      <p class="c-feed-item__categories">
        <strong><?php print t('Categories'); ?>:</strong> <?php print implode(', ', $categories); ?>
      </p>
    </footer>
  <?php endif; ?>
</article>
