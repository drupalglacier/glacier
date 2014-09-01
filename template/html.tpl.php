<?php ob_start(); ?>
<!DOCTYPE html>
<html class="no-js" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>>
<head profile="<?php print $grddl_profile; ?>">
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $modernizr; ?>
  <?php print $respondjs; ?>
  <?php print $selectivizr; ?>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <nav class="skiplinks" role="navigation">
    <ul class="skiplinks__list">
      <li><a id="skiplinks__skiplink--main" href="#main-content" class="skiplinks__skiplink element-invisible u-focusable"><?php print t('Skip to main content'); ?></a></li>
    </ul>
  </nav>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
  <?php print $scripts; ?>
</body>
</html>
<?php $html = ob_get_contents(); ?>
<?php ob_end_clean(); ?>
<?php print glacier_html_minify($html); ?>