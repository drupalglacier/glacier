<?php
/**
 * @file
 * Returns the HTML for the basic html structure of a single Drupal page.
 */
?>
<!DOCTYPE html>
<html class="no-js"<?php print $html_attributes . $rdf_namespaces; ?>>
  <head>
    <?php print $head; ?>
    <title><?php print $head_title; ?></title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
    <?php print $styles; ?>
    <?php print $scripts; ?>
  </head>
  <body class="<?php print $classes; ?>"<?php print $body_attributes; ?>>
    <div class="skiplinks">
      <a href="#main" class="skiplinks__link element-focusable"><?php print t('Skip to main content'); ?></a>
    </div>
    <?php print $page_top; ?>
    <?php print $page; ?>
    <?php print $page_bottom; ?>
  </body>
</html>
