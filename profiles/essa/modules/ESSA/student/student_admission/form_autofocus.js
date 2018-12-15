(function ($) {
Drupal.behaviors.student_admission = {
attach: function (context, settings) {
  
// This code will run, on load, even in overlay!!!!!!
$('.overlay-element html', context).ready(function () {
  $('#edit-search-box').focus();
});
}
};
})(jQuery);
