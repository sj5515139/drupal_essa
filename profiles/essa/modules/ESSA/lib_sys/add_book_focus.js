/*
 * @file
 * JavaScript for set_focus_on_ajax_form_rebuild.
 *
 * Uses jQuery .ajaxStart() and ajaxComplete() to set keyboard focus
 * and link/message color for file uploads and removals.
 */

(function($) {
  //Since we can't replace the callback function for file uploads and then use
  //ajax_command_invoke(), we set focus on the appropriate element after the
  //AJAX callback is complete, here.

  Drupal.behaviors.SetFocusAjaxFormRebuild = {
    attach: function(context, settings) {
      jQuery(document).ajaxComplete(function( event, xhr, settings ) {
        $( '#edit-acc-no' ).css( 'color', 'green' );
        $( '#edit-acc-no' ).focus();
        $( '#edit-acc-no' ).select();
      })
    }
  }
})(jQuery);
