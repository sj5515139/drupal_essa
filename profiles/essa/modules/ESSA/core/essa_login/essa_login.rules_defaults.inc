<?php
/**
 * @file
 * essa_login.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function essa_login_default_rules_configuration() {
  $items = array();
  $items['rules_redirect_anonymous_user'] = entity_import('rules_config', '{ "rules_redirect_anonymous_user" : {
      "LABEL" : "Redirect anonymous user",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "init" : [] },
      "IF" : [
        { "user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "1" : "1" } }
          }
        },
        { "NOT text_matches" : { "text" : [ "site:current-page:url" ], "match" : "user\\/login" } },
        { "OR" : [
            { "NOT text_matches" : { "text" : [ "site:current-page:url" ], "match" : "user\\/password" } }
          ]
        }
      ],
      "DO" : [ { "redirect" : { "url" : "user\\/login" } } ]
    }
  }');
  return $items;
}
