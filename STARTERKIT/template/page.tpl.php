<header id="cmp--header" class="cmp cmp--header" role="banner">
  <div class="container">
    <div class="grid">
      <?php if ($logo): ?>
        <div class="grid__item--12 grid__item--s--3">
          <a id="logo--main" class="logo logo--main a--block" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
            <img class="logo__img logo--main__img" src="<?php print $logo; ?>" alt="<?php print t('Logo'); ?>">
          </a>
        </div>
      <?php endif; ?>

      <?php if (render($page['navigation'])): ?>
        <div class="grid__item--12 grid__item--s--9">
          <div id="region--navigation" class="region region--navigation">
            <?php print render($page['navigation']); ?>
          </div>
        </div>
      <?php endif; ?>
    </div>

    <?php if (render($page['header'])): ?>
      <div id="region--header" class="region region--header">
        <?php print render($page['header']); ?>
      </div>
    <?php endif; ?>
  </div>
</header>

<?php if (drupal_is_front_page()): ?>
  <div id="cmp--slideshow" class="cmp cmp--slideshow">
    <div class="container">
      <div id="region--slideshow" class="region region--slideshow aspect-ratio aspect-ratio--slideshow">
        <div id="region--slideshow__holder" class="region--slideshow__holder aspect-ratio__inner">
          <div id="region--slideshow__holder__inner" class="region--slideshow__holder__inner">
            <div class="slideshow-loader"></div>
          </div>
        </div>
      </div>
    </div>
  </div>
<?php endif; ?>

<div id="cmp--content" class="cmp cmp--content">
  <div class="container">
    <div class="grid">
      <div class="grid__item--12 grid__item--s--<?php print $page['content_item']; ?>">
        <main id="content--main" class="content--main" role="main">
          <a id="main-content"></a>

          <?php print render($tabs); ?>

          <?php print render($title_prefix); ?>
          <?php if ($title): ?>
            <h1 id="title--main" class="title title--main"><?php print $title; ?></h1>
          <?php endif; ?>
          <?php print render($title_suffix); ?>

          <?php print $messages; ?>

          <?php if (render($page['highlighted'])): ?>
            <div id="region--highlighted" class="region region--highlighted">
              <?php print render($page['highlighted']); ?>
            </div>
          <?php endif; ?>

          <?php if ($action_links): ?>
            <ul id="action-links" class="action-links"><?php print render($action_links); ?></ul>
          <?php endif; ?>

          <div id="region--content" class="region region--content">
            <?php print render($page['content']); ?>
          </div>
        </main>
      </div>

      <?php if (render($page['sidebar1'])): ?>
        <div class="grid__item--12 grid__item--s--<?php print $page['sidebar1_item']; ?>">
          <aside id="region--sidebar1" class="region region--sidebar region--sidebar1">
            <?php print render($page['sidebar1']); ?>
          </aside>
        </div>
      <?php endif; ?>

      <?php if (render($page['sidebar2'])): ?>
        <div class="grid__item--12 grid__item--s--<?php print $page['sidebar2_item']; ?>">
          <aside id="region--sidebar2" class="region region--sidebar region--sidebar2">
            <?php print render($page['sidebar2']); ?>
          </aside>
        </div>
      <?php endif; ?>
    </div>
  </div>
</div>

<?php if (render($page['teaser'])): ?>
  <div id="cmp--teaser" class="cmp cmp--teaser">
    <div class="container">
      <div id="region--teaser" class="region region--teaser">
        <?php print render($page['teaser']); ?>
      </div>
    </div>
  </div>
<?php endif; ?>

<?php if (render($page['misc1']) || render($page['misc2']) || render($page['misc3']) || render($page['misc4'])): ?>
  <div id="cmp--misc" class="cmp cmp--misc">
    <div class="container">
      <div class="grid cmp--misc__grid">
        <?php if (render($page['misc1'])): ?>
          <div class="grid__item--6 grid__item--m--3">
            <div id="region--misc1" class="region region--misc region--misc1">
              <?php print render($page['misc1']); ?>
            </div>
          </div>
        <?php endif; ?>

        <?php if (render($page['misc2'])): ?>
          <div class="grid__item--6 grid__item--m--3">
            <div id="region--misc2" class="region region--misc region--misc2">
              <?php print render($page['misc2']); ?>
            </div>
          </div>
        <?php endif; ?>

        <?php if (render($page['misc3'])): ?>
          <div class="grid__item--6 grid__item--m--3">
            <div id="region--misc3" class="region region--misc region--misc3">
              <?php print render($page['misc3']); ?>
            </div>
          </div>
        <?php endif; ?>

        <?php if (render($page['misc4'])): ?>
          <div class="grid__item--6 grid__item--m--3">
            <div id="region--misc4" class="region region--misc region--misc4">
              <?php print render($page['misc4']); ?>
            </div>
          </div>
        <?php endif; ?>
      </div>
    </div>
  </div>
<?php endif; ?>

<?php if (render($page['footer'])): ?>
  <footer id="cmp--footer" class="cmp cmp--footer" role="contentinfo">
    <div class="container">
      <div id="region--footer" class="region region--footer">
        <?php print render($page['footer']); ?>
      </div>
    </div>
  </footer>
<?php endif; ?>