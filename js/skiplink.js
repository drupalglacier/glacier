jQuery(function($) {
  var is_webkit = navigator.userAgent.toLowerCase().indexOf('webkit') > -1;
  var is_opera = navigator.userAgent.toLowerCase().indexOf('opera') > -1;

  if (is_webkit || is_opera) {
    $('.c-skiplink__link').each(function() {
      var $skip_link = $(this);
      var $target = $($skip_link.attr('href'));

      $target.attr('tabindex', '0');
      $skip_link.attr('onclick', 'document.getElementById(\'' + $target.attr('id') + '\').focus();');
    });
  }
});
