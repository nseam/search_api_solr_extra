/**
 * @file
 * Solr_devel module helpers.
 */

(function($) {

    Drupal.behaviors.SearchAPISOLRextraDebug = {
        attach: function(context, settings) {
            $("div.search-api-solr-extra-debug").not(".expanded").find("div.search-api-solr-extra-debug-content").hide();
            $("div.search-api-solr-extra-debug div.search-api-solr-extra-debug-title").click(function() {
                if (!$(this).parent().children("div.search-api-solr-extra-debug-content").is(":visible")) {
                    $(this).parent().addClass("expanded");
                } else {
                    $(this).parent().removeClass("expanded");
                }
                $(this).parent().children("div.search-api-solr-extra-debug-content").toggle();
            })

            $("div.search-api-solr-extra-debug .krumo-expand").addClass("krumo-opened");
            $("div.search-api-solr-extra-debug .krumo-nest").show();

            $("div.messages > ul > li > *").insertAfter("#messages .messages");

            $("div.messages > ul > li").each(function() {
                if ($(this)[0].childNodes.length == 0) {
                    $(this).remove();
                }
            })

            if ($("div.messages > ul").children().length == 0) {
                $("div.messages").remove();
            }
        }
    };

})(jQuery);