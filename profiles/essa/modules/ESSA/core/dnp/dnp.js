(function ($) {

/**
 * Move a block in the blocks table from one region to another via select list.
 *
 * This behavior is dependent on the tableDrag behavior, since it uses the
 * objects initialized in that behavior to update the row.
 */
Drupal.behaviors.termDrag = {
  attach: function (context, settings) {
    var table = $('#dnp', context);
    var tableDrag = Drupal.tableDrag.dnp; // Get the blocks tableDrag object.
    var rows = $('tr', table).length;

    // When a row is swapped, keep previous and next page classes set.
    tableDrag.row.prototype.onSwap = function (swappedRow) {
      $('tr.dnp-term-preview', table).removeClass('dnp-term-preview');
      $('tr.dnp-term-divider-top', table).removeClass('dnp-term-divider-top');
      $('tr.dnp-term-divider-bottom', table).removeClass('dnp-term-divider-bottom');

      if (settings.dnp.backStep) {
        for (var n = 0; n < settings.dnp.backStep; n++) {
          $(table[0].tBodies[0].rows[n]).addClass('dnp-term-preview');
        }
        $(table[0].tBodies[0].rows[settings.dnp.backStep - 1]).addClass('dnp-term-divider-top');
        $(table[0].tBodies[0].rows[settings.dnp.backStep]).addClass('dnp-term-divider-bottom');
      }

      if (settings.dnp.forwardStep) {
        for (var n = rows - settings.dnp.forwardStep - 1; n < rows - 1; n++) {
          $(table[0].tBodies[0].rows[n]).addClass('dnp-term-preview');
        }
        $(table[0].tBodies[0].rows[rows - settings.dnp.forwardStep - 2]).addClass('dnp-term-divider-top');
        $(table[0].tBodies[0].rows[rows - settings.dnp.forwardStep - 1]).addClass('dnp-term-divider-bottom');
      }
    };
  }
};

})(jQuery);
