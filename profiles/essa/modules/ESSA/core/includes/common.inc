<?php

/**
 * @file
 * Common functions that many Drupal modules will need to reference.
 *
 * The functions that are critical and need to be available even when serving
 * a cached page are instead located in bootstrap.inc.
 */

/**
 * @defgroup php_wrappers PHP wrapper functions
 * @{
 * Functions that are wrappers or custom implementations of PHP functions.
 *
 * Certain PHP functions should not be used in Drupal. Instead, Drupal's
 * replacement functions should be used.
 *
 * For example, for improved or more secure UTF8-handling, or RFC-compliant
 * handling of URLs in Drupal.
 *
 * For ease of use and memorizing, all these wrapper functions use the same name
 * as the original PHP function, but prefixed with "drupal_". Beware, however,
 * that not all wrapper functions support the same arguments as the original
 * functions.
 *
 * You should always use these wrapper functions in your code.
 *
 * Wrong:
 * @code
 *   $my_substring = substr($original_string, 0, 5);
 * @endcode
 *
 * Correct:
 * @code
 *   $my_substring = drupal_substr($original_string, 0, 5);
 * @endcode
 *
 * @}
 */

/**
 * Return status for saving which involved creating a new item.
 */
define('SAVED_NEW', 1);

/**
 * Return status for saving which involved an update to an existing item.
 */
define('SAVED_UPDATED', 2);

/**
 * Return status for saving which deleted an existing item.
 */
define('SAVED_DELETED', 3);

/**
 * The default group for system CSS files added to the page.
 */
define('CSS_SYSTEM', -100);

/**
 * The default group for module CSS files added to the page.
 */
define('CSS_DEFAULT', 0);

/**
 * The default group for theme CSS files added to the page.
 */
define('CSS_THEME', 100);

/**
 * The default group for JavaScript and jQuery libraries added to the page.
 */
define('JS_LIBRARY', -100);

/**
 * The default group for module JavaScript code added to the page.
 */
define('JS_DEFAULT', 0);

/**
 * The default group for theme JavaScript code added to the page.
 */
define('JS_THEME', 100);

/**
 * Error code indicating that the request exceeded the specified timeout.
 *
 * @see drupal_http_request()
 */
define('HTTP_REQUEST_TIMEOUT', -1);

/**
 * @defgroup block_caching Block Caching
 * @{
 * Constants that define each block's caching state.
 *
 * Modules specify how their blocks can be cached in their hook_block_info()
 * implementations. Caching can be turned off (DRUPAL_NO_CACHE), managed by the
 * module declaring the block (DRUPAL_CACHE_CUSTOM), or managed by the core
 * Block module. If the Block module is managing the cache, you can specify that
 * the block is the same for every page and user (DRUPAL_CACHE_GLOBAL), or that
 * it can change depending on the page (DRUPAL_CACHE_PER_PAGE) or by user
 * (DRUPAL_CACHE_PER_ROLE or DRUPAL_CACHE_PER_USER). Page and user settings can
 * be combined with a bitwise-binary or operator; for example,
 * DRUPAL_CACHE_PER_ROLE | DRUPAL_CACHE_PER_PAGE means that the block can change
 * depending on the user role or page it is on.
 *
 * The block cache is cleared in cache_clear_all(), and uses the same clearing
 * policy than page cache (node, comment, user, taxonomy added or updated...).
 * Blocks requiring more fine-grained clearing might consider disabling the
 * built-in block cache (DRUPAL_NO_CACHE) and roll their own.
 *
 * Note that user 1 is excluded from block caching.
 */

/**
 * The block should not get cached.
 *
 * This setting should be used:
 * - For simple blocks (notably those that do not perform any db query), where
 *   querying the db cache would be more expensive than directly generating the
 *   content.
 * - For blocks that change too frequently.
 */
define('DRUPAL_NO_CACHE', -1);

/**
 * The block is handling its own caching in its hook_block_view().
 *
 * This setting is useful when time based expiration is needed or a site uses a
 * node access which invalidates standard block cache.
 */
define('DRUPAL_CACHE_CUSTOM', -2);

/**
 * The block or element can change depending on the user's roles.
 *
 * This is the default setting for blocks, used when the block does not specify
 * anything.
 */
define('DRUPAL_CACHE_PER_ROLE', 0x0001);

/**
 * The block or element can change depending on the user.
 *
 * This setting can be resource-consuming for sites with large number of users,
 * and thus should only be used when DRUPAL_CACHE_PER_ROLE is not sufficient.
 */
define('DRUPAL_CACHE_PER_USER', 0x0002);

/**
 * The block or element can change depending on the page being viewed.
 */
define('DRUPAL_CACHE_PER_PAGE', 0x0004);

/**
 * The block or element is the same for every user and page that it is visible.
 */
define('DRUPAL_CACHE_GLOBAL', 0x0008);

/**
 * @} End of "defgroup block_caching".
 */

/**
 * Adds content to a specified region.
 *
 * @param $region
 *   Page region the content is added to.
 * @param $data
 *   Content to be added.
 */
function drupal_add_region_content($region = NULL, $data = NULL) {
  static $content = array();

  if (isset($region) && isset($data)) {
    $content[$region][] = $data;
  }
  return $content;
}

/**
 * Gets assigned content for a given region.
 *
 * @param $region
 *   A specified region to fetch content for. If NULL, all regions will be
 *   returned.
 * @param $delimiter
 *   Content to be inserted between imploded array elements.
 */
function drupal_get_region_content($region = NULL, $delimiter = ' ') {
  $content = drupal_add_region_content();
  if (isset($region)) {
    if (isset($content[$region]) && is_array($content[$region])) {
      return implode($delimiter, $content[$region]);
    }
  }
  else {
    foreach (array_keys($content) as $region) {
      if (is_array($content[$region])) {
        $content[$region] = implode($delimiter, $content[$region]);
      }
    }
    return $content;
  }
}

/**
 * Gets the name of the currently active installation profile.
 *
 * When this function is called during Drupal's initial installation process,
 * the name of the profile that's about to be installed is stored in the global
 * installation state. At all other times, the standard Drupal systems variable
 * table contains the name of the current profile, and we can call
 * variable_get() to determine what one is active.
 *
 * @return $profile
 *   The name of the installation profile.
 */
function drupal_get_profile() {
  global $install_state;

  if (isset($install_state['parameters']['profile'])) {
    $profile = $install_state['parameters']['profile'];
  }
  else {
    $profile = variable_get('install_profile', 'standard');
  }

  return $profile;
}


/**
 * Sets the breadcrumb trail for the current page.
 *
 * @param $breadcrumb
 *   Array of links, starting with "home" and proceeding up to but not including
 *   the current page.
 */
function drupal_set_breadcrumb($breadcrumb = NULL) {
  $stored_breadcrumb = &drupal_static(__FUNCTION__);

  if (isset($breadcrumb)) {
    $stored_breadcrumb = $breadcrumb;
  }
  return $stored_breadcrumb;
}

/**
 * Gets the breadcrumb trail for the current page.
 */
function drupal_get_breadcrumb() {
  $breadcrumb = drupal_set_breadcrumb();

  if (!isset($breadcrumb)) {
    $breadcrumb = menu_get_active_breadcrumb();
  }

  return $breadcrumb;
}

/**
 * Returns a string containing RDF namespace declarations for use in XML and
 * XHTML output.
 */
function drupal_get_rdf_namespaces() {
  $xml_rdf_namespaces = array();

  // Serializes the RDF namespaces in XML namespace syntax.
  if (function_exists('rdf_get_namespaces')) {
    foreach (rdf_get_namespaces() as $prefix => $uri) {
      $xml_rdf_namespaces[] = 'xmlns:' . $prefix . '="' . $uri . '"';
    }
  }
  return count($xml_rdf_namespaces) ? "\n  " . implode("\n  ", $xml_rdf_namespaces) : '';
}

/**
 * Adds output to the HEAD tag of the HTML page.
 *
 * This function can be called as long as the headers aren't sent. Pass no
 * arguments (or NULL for both) to retrieve the currently stored elements.
 *
 * @param $data
 *   A renderable array. If the '#type' key is not set then 'html_tag' will be
 *   added as the default '#type'.
 * @param $key
 *   A unique string key to allow implementations of hook_html_head_alter() to
 *   identify the element in $data. Required if $data is not NULL.
 *
 * @return
 *   An array of all stored HEAD elements.
 *
 * @see theme_html_tag()
 */
function drupal_add_html_head($data = NULL, $key = NULL) {
  $stored_head = &drupal_static(__FUNCTION__);

  if (!isset($stored_head)) {
    // Make sure the defaults, including Content-Type, come first.
    $stored_head = _drupal_default_html_head();
  }

  if (isset($data) && isset($key)) {
    if (!isset($data['#type'])) {
      $data['#type'] = 'html_tag';
    }
    $stored_head[$key] = $data;
  }
  return $stored_head;
}

/**
 * Returns elements that are always displayed in the HEAD tag of the HTML page.
 */
function _drupal_default_html_head() {
  // Add default elements. Make sure the Content-Type comes first because the
  // IE browser may be vulnerable to XSS via encoding attacks from any content
  // that comes before this META tag, such as a TITLE tag.
  $elements['system_meta_content_type'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'Content-Type',
      'content' => 'text/html; charset=utf-8',
    ),
    // Security: This always has to be output first.
    '#weight' => -1000,
  );
  // Show Drupal and the major version number in the META GENERATOR tag.
  // Get the major version.
  list($version, ) = explode('.', VERSION);
  $elements['system_meta_generator'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'Generator',
      'content' => 'Drupal ' . $version . ' (http://drupal.org)',
    ),
  );
  // Also send the generator in the HTTP header.
  $elements['system_meta_generator']['#attached']['drupal_add_http_header'][] = array('X-Generator', $elements['system_meta_generator']['#attributes']['content']);
  return $elements;
}

/**
 * Retrieves output to be displayed in the HEAD tag of the HTML page.
 */
function drupal_get_html_head() {
  $elements = drupal_add_html_head();
  drupal_alter('html_head', $elements);
  return drupal_render($elements);
}

/**
 * Adds a feed URL for the current page.
 *
 * This function can be called as long the HTML header hasn't been sent.
 *
 * @param $url
 *   An internal system path or a fully qualified external URL of the feed.
 * @param $title
 *   The title of the feed.
 */
function drupal_add_feed($url = NULL, $title = '') {
  $stored_feed_links = &drupal_static(__FUNCTION__, array());

  if (isset($url)) {
    $stored_feed_links[$url] = theme('feed_icon', array('url' => $url, 'title' => $title));

    drupal_add_html_head_link(array(
      'rel' => 'alternate',
      'type' => 'application/rss+xml',
      'title' => $title,
      // Force the URL to be absolute, for consistency with other <link> tags
      // output by Drupal.
      'href' => url($url, array('absolute' => TRUE)),
    ));
  }
  return $stored_feed_links;
}

/**
 * Gets the feed URLs for the current page.
 *
 * @param $delimiter
 *   A delimiter to split feeds by.
 */
function drupal_get_feeds($delimiter = "\n") {
  $feeds = drupal_add_feed();
  return implode($feeds, $delimiter);
}

/**
 * @defgroup http_handling HTTP handling
 * @{
 * Functions to properly handle HTTP responses.
 */

/**
 * Processes a URL query parameter array to remove unwanted elements.
 *
 * @param $query
 *   (optional) An array to be processed. Defaults to $_GET.
 * @param $exclude
 *   (optional) A list of $query array keys to remove. Use "parent[child]" to
 *   exclude nested items. Defaults to array('q').
 * @param $parent
 *   Internal use only. Used to build the $query array key for nested items.
 *
 * @return
 *   An array containing query parameters, which can be used for url().
 */
function drupal_get_query_parameters(array $query = NULL, array $exclude = array('q'), $parent = '') {
  // Set defaults, if none given.
  if (!isset($query)) {
    $query = $_GET;
  }
  // If $exclude is empty, there is nothing to filter.
  if (empty($exclude)) {
    return $query;
  }
  elseif (!$parent) {
    $exclude = array_flip($exclude);
  }

  $params = array();
  foreach ($query as $key => $value) {
    $string_key = ($parent ? $parent . '[' . $key . ']' : $key);
    if (isset($exclude[$string_key])) {
      continue;
    }

    if (is_array($value)) {
      $params[$key] = drupal_get_query_parameters($value, $exclude, $string_key);
    }
    else {
      $params[$key] = $value;
    }
  }

  return $params;
}

/**
 * Splits a URL-encoded query string into an array.
 *
 * @param $query
 *   The query string to split.
 *
 * @return
 *   An array of URL decoded couples $param_name => $value.
 */
function drupal_get_query_array($query) {
  $result = array();
  if (!empty($query)) {
    foreach (explode('&', $query) as $param) {
      $param = explode('=', $param, 2);
      $result[$param[0]] = isset($param[1]) ? rawurldecode($param[1]) : '';
    }
  }
  return $result;
}

/**
 * Parses an array into a valid, rawurlencoded query string.
 *
 * This differs from http_build_query() as we need to rawurlencode() (instead of
 * urlencode()) all query parameters.
 *
 * @param $query
 *   The query parameter array to be processed, e.g. $_GET.
 * @param $parent
 *   Internal use only. Used to build the $query array key for nested items.
 *
 * @return
 *   A rawurlencoded string which can be used as or appended to the URL query
 *   string.
 *
 * @see drupal_get_query_parameters()
 * @ingroup php_wrappers
 */
function drupal_http_build_query(array $query, $parent = '') {
  $params = array();

  foreach ($query as $key => $value) {
    $key = ($parent ? $parent . '[' . rawurlencode($key) . ']' : rawurlencode($key));

    // Recurse into children.
    if (is_array($value)) {
      $params[] = drupal_http_build_query($value, $key);
    }
    // If a query parameter value is NULL, only append its key.
    elseif (!isset($value)) {
      $params[] = $key;
    }
    else {
      // For better readability of paths in query strings, we decode slashes.
      $params[] = $key . '=' . str_replace('%2F', '/', rawurlencode($value));
    }
  }

  return implode('&', $params);
}

/**
 * Prepares a 'destination' URL query parameter for use with drupal_goto().
 *
 * Used to direct the user back to the referring page after completing a form.
 * By default the current URL is returned. If a destination exists in the
 * previous request, that destination is returned. As such, a destination can
 * persist across multiple pages.
 *
 * @return
 *   An associative array containing the key:
 *   - destination: The path provided via the destination query string or, if
 *     not available, the current path.
 *
 * @see current_path()
 * @see drupal_goto()
 */
function drupal_get_destination() {
  $destination = &drupal_static(__FUNCTION__);

  if (isset($destination)) {
    return $destination;
  }

  if (isset($_GET['destination'])) {
    $destination = array('destination' => $_GET['destination']);
  }
  else {
    $path = $_GET['q'];
    $query = drupal_http_build_query(drupal_get_query_parameters());
    if ($query != '') {
      $path .= '?' . $query;
    }
    $destination = array('destination' => $path);
  }
  return $destination;
}

/**
 * Parses a URL string into its path, query, and fragment components.
 *
 * This function splits both internal paths like @code node?b=c#d @endcode and
 * external URLs like @code https://example.com/a?b=c#d @endcode into their
 * component parts. See
 * @link http://tools.ietf.org/html/rfc3986#section-3 RFC 3986 @endlink for an
 * explanation of what the component parts are.
 *
 * Note that, unlike the RFC, when passed an external URL, this function
 * groups the scheme, authority, and path together into the path component.
 *
 * @param string $url
 *   The internal path or external URL string to parse.
 *
 * @return array
 *   An associative array containing:
 *   - path: The path component of $url. If $url is an external URL, this
 *     includes the scheme, authority, and path.
 *   - query: An array of query parameters from $url, if they exist.
 *   - fragment: The fragment component from $url, if it exists.
 *
 * @see drupal_goto()
 * @see l()
 * @see url()
 * @see http://tools.ietf.org/html/rfc3986
 *
 * @ingroup php_wrappers
 */
function drupal_parse_url($url) {
  $options = array(
    'path' => NULL,
    'query' => array(),
    'fragment' => '',
  );

  // External URLs: not using parse_url() here, so we do not have to rebuild
  // the scheme, host, and path without having any use for it.
  if (strpos($url, '://') !== FALSE) {
    // Split off everything before the query string into 'path'.
    $parts = explode('?', $url);
    $options['path'] = $parts[0];
    // If there is a query string, transform it into keyed query parameters.
    if (isset($parts[1])) {
      $query_parts = explode('#', $parts[1]);
      parse_str($query_parts[0], $options['query']);
      // Take over the fragment, if there is any.
      if (isset($query_parts[1])) {
        $options['fragment'] = $query_parts[1];
      }
    }
  }
  // Internal URLs.
  else {
    // parse_url() does not support relative URLs, so make it absolute. E.g. the
    // relative URL "foo/bar:1" isn't properly parsed.
    $parts = parse_url('http://example.com/' . $url);
    // Strip the leading slash that was just added.
    $options['path'] = substr($parts['path'], 1);
    if (isset($parts['query'])) {
      parse_str($parts['query'], $options['query']);
    }
    if (isset($parts['fragment'])) {
      $options['fragment'] = $parts['fragment'];
    }
  }
  // The 'q' parameter contains the path of the current page if clean URLs are
  // disabled. It overrides the 'path' of the URL when present, even if clean
  // URLs are enabled, due to how Apache rewriting rules work.
  if (isset($options['query']['q'])) {
    $options['path'] = $options['query']['q'];
    unset($options['query']['q']);
  }

  return $options;
}

/**
 * Encodes a Drupal path for use in a URL.
 *
 * For aesthetic reasons slashes are not escaped.
 *
 * Note that url() takes care of calling this function, so a path passed to that
 * function should not be encoded in advance.
 *
 * @param $path
 *   The Drupal path to encode.
 */
function drupal_encode_path($path) {
  return str_replace('%2F', '/', rawurlencode($path));
}

/**
 * Sends the user to a different page.
 *
 * This issues an on-site HTTP redirect. The function makes sure the redirected
 * URL is formatted correctly.
 *
 * Usually the redirected URL is constructed from this function's input
 * parameters. However you may override that behavior by setting a
 * destination in either the $_REQUEST-array (i.e. by using
 * the query string of an URI) This is used to direct the user back to
 * the proper page after completing a form. For example, after editing
 * a post on the 'admin/content'-page or after having logged on using the
 * 'user login'-block in a sidebar. The function drupal_get_destination()
 * can be used to help set the destination URL.
 *
 * Drupal will ensure that messages set by drupal_set_message() and other
 * session data are written to the database before the user is redirected.
 *
 * This function ends the request; use it instead of a return in your menu
 * callback.
 *
 * @param $path
 *   (optional) A Drupal path or a full URL, which will be passed to url() to
 *   compute the redirect for the URL.
 * @param $options
 *   (optional) An associative array of additional URL options to pass to url().
 * @param $http_response_code
 *   (optional) The HTTP status code to use for the redirection, defaults to
 *   302. The valid values for 3xx redirection status codes are defined in
 *   @link http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.3 RFC 2616 @endlink
 *   and the
 *   @link http://tools.ietf.org/html/draft-reschke-http-status-308-07 draft for the new HTTP status codes: @endlink
 *   - 301: Moved Permanently (the recommended value for most redirects).
 *   - 302: Found (default in Drupal and PHP, sometimes used for spamming search
 *     engines).
 *   - 303: See Other.
 *   - 304: Not Modified.
 *   - 305: Use Proxy.
 *   - 307: Temporary Redirect.
 *
 * @see drupal_get_destination()
 * @see url()
 */
function drupal_goto($path = '', array $options = array(), $http_response_code = 302) {
  // A destination in $_GET always overrides the function arguments.
  // We do not allow absolute URLs to be passed via $_GET, as this can be an attack vector.
  if (isset($_GET['destination']) && !url_is_external($_GET['destination'])) {
    $destination = drupal_parse_url($_GET['destination']);
    $path = $destination['path'];
    $options['query'] = $destination['query'];
    $options['fragment'] = $destination['fragment'];
  }

  // In some cases modules call drupal_goto(current_path()). We need to ensure
  // that such a redirect is not to an external URL.
  if ($path === current_path() && empty($options['external']) && url_is_external($path)) {
    // Force url() to generate a non-external URL.
    $options['external'] = FALSE;
  }

  drupal_alter('drupal_goto', $path, $options, $http_response_code);

  // The 'Location' HTTP header must be absolute.
  $options['absolute'] = TRUE;

  $url = url($path, $options);

  header('Location: ' . $url, TRUE, $http_response_code);

  // The "Location" header sends a redirect status code to the HTTP daemon. In
  // some cases this can be wrong, so we make sure none of the code below the
  // drupal_goto() call gets executed upon redirection.
  drupal_exit($url);
}

/**
 * Delivers a "site is under maintenance" message to the browser.
 *
 * Page callback functions wanting to report a "site offline" message should
 * return MENU_SITE_OFFLINE instead of calling drupal_site_offline(). However,
 * functions that are invoked in contexts where that return value might not
 * bubble up to menu_execute_active_handler() should call drupal_site_offline().
 */
function drupal_site_offline() {
  drupal_deliver_page(MENU_SITE_OFFLINE);
}

/**
 * Delivers a "page not found" error to the browser.
 *
 * Page callback functions wanting to report a "page not found" message should
 * return MENU_NOT_FOUND instead of calling drupal_not_found(). However,
 * functions that are invoked in contexts where that return value might not
 * bubble up to menu_execute_active_handler() should call drupal_not_found().
 */
function drupal_not_found() {
  drupal_deliver_page(MENU_NOT_FOUND);
}

/**
 * Delivers an "access denied" error to the browser.
 *
 * Page callback functions wanting to report an "access denied" message should
 * return MENU_ACCESS_DENIED instead of calling drupal_access_denied(). However,
 * functions that are invoked in contexts where that return value might not
 * bubble up to menu_execute_active_handler() should call
 * drupal_access_denied().
 */
function drupal_access_denied() {
  drupal_deliver_page(MENU_ACCESS_DENIED);
}

/**
 * Performs an HTTP request.
 *
 * This is a flexible and powerful HTTP client implementation. Correctly
 * handles GET, POST, PUT or any other HTTP requests. Handles redirects.
 *
 * @param $url
 *   A string containing a fully qualified URI.
 * @param array $options
 *   (optional) An array that can have one or more of the following elements:
 *   - headers: An array containing request headers to send as name/value pairs.
 *   - method: A string containing the request method. Defaults to 'GET'.
 *   - data: A string containing the request body, formatted as
 *     'param=value&param=value&...'; to generate this, use http_build_query().
 *     Defaults to NULL.
 *   - max_redirects: An integer representing how many times a redirect
 *     may be followed. Defaults to 3.
 *   - timeout: A float representing the maximum number of seconds the function
 *     call may take. The default is 30 seconds. If a timeout occurs, the error
 *     code is set to the HTTP_REQUEST_TIMEOUT constant.
 *   - context: A context resource created with stream_context_create().
 *
 * @return object
 *   An object that can have one or more of the following components:
 *   - request: A string containing the request body that was sent.
 *   - code: An integer containing the response status code, or the error code
 *     if an error occurred.
 *   - protocol: The response protocol (e.g. HTTP/1.1 or HTTP/1.0).
 *   - status_message: The status message from the response, if a response was
 *     received.
 *   - redirect_code: If redirected, an integer containing the initial response
 *     status code.
 *   - redirect_url: If redirected, a string containing the URL of the redirect
 *     target.
 *   - error: If an error occurred, the error message. Otherwise not set.
 *   - headers: An array containing the response headers as name/value pairs.
 *     HTTP header names are case-insensitive (RFC 2616, section 4.2), so for
 *     easy access the array keys are returned in lower case.
 *   - data: A string containing the response body that was received.
 *
 * @see http_build_query()
 */
function drupal_http_request($url, array $options = array()) {
  // Allow an alternate HTTP client library to replace Drupal's default
  // implementation.
  $override_function = variable_get('drupal_http_request_function', FALSE);
  if (!empty($override_function) && function_exists($override_function)) {
    return $override_function($url, $options);
  }

  $result = new stdClass();

  // Parse the URL and make sure we can handle the schema.
  $uri = @parse_url($url);

  if ($uri == FALSE) {
    $result->error = 'unable to parse URL';
    $result->code = -1001;
    return $result;
  }

  if (!isset($uri['scheme'])) {
    $result->error = 'missing schema';
    $result->code = -1002;
    return $result;
  }

  timer_start(__FUNCTION__);

  // Merge the default options.
  $options += array(
    'headers' => array(),
    'method' => 'GET',
    'data' => NULL,
    'max_redirects' => 3,
    'timeout' => 30.0,
    'context' => NULL,
  );

  // Merge the default headers.
  $options['headers'] += array(
    'User-Agent' => 'Drupal (+http://drupal.org/)',
  );

  // stream_socket_client() requires timeout to be a float.
  $options['timeout'] = (float) $options['timeout'];

  // Use a proxy if one is defined and the host is not on the excluded list.
  $proxy_server = variable_get('proxy_server', '');
  if ($proxy_server && _drupal_http_use_proxy($uri['host'])) {
    // Set the scheme so we open a socket to the proxy server.
    $uri['scheme'] = 'proxy';
    // Set the path to be the full URL.
    $uri['path'] = $url;
    // Since the URL is passed as the path, we won't use the parsed query.
    unset($uri['query']);

    // Add in username and password to Proxy-Authorization header if needed.
    if ($proxy_username = variable_get('proxy_username', '')) {
      $proxy_password = variable_get('proxy_password', '');
      $options['headers']['Proxy-Authorization'] = 'Basic ' . base64_encode($proxy_username . (!empty($proxy_password) ? ":" . $proxy_password : ''));
    }
    // Some proxies reject requests with any User-Agent headers, while others
    // require a specific one.
    $proxy_user_agent = variable_get('proxy_user_agent', '');
    // The default value matches neither condition.
    if ($proxy_user_agent === NULL) {
      unset($options['headers']['User-Agent']);
    }
    elseif ($proxy_user_agent) {
      $options['headers']['User-Agent'] = $proxy_user_agent;
    }
  }

  switch ($uri['scheme']) {
    case 'proxy':
      // Make the socket connection to a proxy server.
      $socket = 'tcp://' . $proxy_server . ':' . variable_get('proxy_port', 8080);
      // The Host header still needs to match the real request.
      $options['headers']['Host'] = $uri['host'];
      $options['headers']['Host'] .= isset($uri['port']) && $uri['port'] != 80 ? ':' . $uri['port'] : '';
      break;

    case 'http':
    case 'feed':
      $port = isset($uri['port']) ? $uri['port'] : 80;
      $socket = 'tcp://' . $uri['host'] . ':' . $port;
      // RFC 2616: "non-standard ports MUST, default ports MAY be included".
      // We don't add the standard port to prevent from breaking rewrite rules
      // checking the host that do not take into account the port number.
      $options['headers']['Host'] = $uri['host'] . ($port != 80 ? ':' . $port : '');
      break;

    case 'https':
      // Note: Only works when PHP is compiled with OpenSSL support.
      $port = isset($uri['port']) ? $uri['port'] : 443;
      $socket = 'ssl://' . $uri['host'] . ':' . $port;
      $options['headers']['Host'] = $uri['host'] . ($port != 443 ? ':' . $port : '');
      break;

    default:
      $result->error = 'invalid schema ' . $uri['scheme'];
      $result->code = -1003;
      return $result;
  }

  if (empty($options['context'])) {
    $fp = @stream_socket_client($socket, $errno, $errstr, $options['timeout']);
  }
  else {
    // Create a stream with context. Allows verification of a SSL certificate.
    $fp = @stream_socket_client($socket, $errno, $errstr, $options['timeout'], STREAM_CLIENT_CONNECT, $options['context']);
  }

  // Make sure the socket opened properly.
  if (!$fp) {
    // When a network error occurs, we use a negative number so it does not
    // clash with the HTTP status codes.
    $result->code = -$errno;
    $result->error = trim($errstr) ? trim($errstr) : t('Error opening socket @socket', array('@socket' => $socket));

    // Mark that this request failed. This will trigger a check of the web
    // server's ability to make outgoing HTTP requests the next time that
    // requirements checking is performed.
    // See system_requirements().
    variable_set('drupal_http_request_fails', TRUE);

    return $result;
  }

  // Construct the path to act on.
  $path = isset($uri['path']) ? $uri['path'] : '/';
  if (isset($uri['query'])) {
    $path .= '?' . $uri['query'];
  }

  // Only add Content-Length if we actually have any content or if it is a POST
  // or PUT request. Some non-standard servers get confused by Content-Length in
  // at least HEAD/GET requests, and Squid always requires Content-Length in
  // POST/PUT requests.
  $content_length = strlen($options['data']);
  if ($content_length > 0 || $options['method'] == 'POST' || $options['method'] == 'PUT') {
    $options['headers']['Content-Length'] = $content_length;
  }

  // If the server URL has a user then attempt to use basic authentication.
  if (isset($uri['user'])) {
    $options['headers']['Authorization'] = 'Basic ' . base64_encode($uri['user'] . (isset($uri['pass']) ? ':' . $uri['pass'] : ':'));
  }

  // If the database prefix is being used by SimpleTest to run the tests in a copied
  // database then set the user-agent header to the database prefix so that any
  // calls to other Drupal pages will run the SimpleTest prefixed database. The
  // user-agent is used to ensure that multiple testing sessions running at the
  // same time won't interfere with each other as they would if the database
  // prefix were stored statically in a file or database variable.
  $test_info = &$GLOBALS['drupal_test_info'];
  if (!empty($test_info['test_run_id'])) {
    $options['headers']['User-Agent'] = drupal_generate_test_ua($test_info['test_run_id']);
  }

  $request = $options['method'] . ' ' . $path . " HTTP/1.0\r\n";
  foreach ($options['headers'] as $name => $value) {
    $request .= $name . ': ' . trim($value) . "\r\n";
  }
  $request .= "\r\n" . $options['data'];
  $result->request = $request;
  // Calculate how much time is left of the original timeout value.
  $timeout = $options['timeout'] - timer_read(__FUNCTION__) / 1000;
  if ($timeout > 0) {
    stream_set_timeout($fp, floor($timeout), floor(1000000 * fmod($timeout, 1)));
    fwrite($fp, $request);
  }

  // Fetch response. Due to PHP bugs like http://bugs.php.net/bug.php?id=43782
  // and http://bugs.php.net/bug.php?id=46049 we can't rely on feof(), but
  // instead must invoke stream_get_meta_data() each iteration.
  $info = stream_get_meta_data($fp);
  $alive = !$info['eof'] && !$info['timed_out'];
  $response = '';

  while ($alive) {
    // Calculate how much time is left of the original timeout value.
    $timeout = $options['timeout'] - timer_read(__FUNCTION__) / 1000;
    if ($timeout <= 0) {
      $info['timed_out'] = TRUE;
      break;
    }
    stream_set_timeout($fp, floor($timeout), floor(1000000 * fmod($timeout, 1)));
    $chunk = fread($fp, 1024);
    $response .= $chunk;
    $info = stream_get_meta_data($fp);
    $alive = !$info['eof'] && !$info['timed_out'] && $chunk;
  }
  fclose($fp);

  if ($info['timed_out']) {
    $result->code = HTTP_REQUEST_TIMEOUT;
    $result->error = 'request timed out';
    return $result;
  }
  // Parse response headers from the response body.
  // Be tolerant of malformed HTTP responses that separate header and body with
  // \n\n or \r\r instead of \r\n\r\n.
  list($response, $result->data) = preg_split("/\r\n\r\n|\n\n|\r\r/", $response, 2);
  $response = preg_split("/\r\n|\n|\r/", $response);

  // Parse the response status line.
  $response_status_array = _drupal_parse_response_status(trim(array_shift($response)));
  $result->protocol = $response_status_array['http_version'];
  $result->status_message = $response_status_array['reason_phrase'];
  $code = $response_status_array['response_code'];

  $result->headers = array();

  // Parse the response headers.
  while ($line = trim(array_shift($response))) {
    list($name, $value) = explode(':', $line, 2);
    $name = strtolower($name);
    if (isset($result->headers[$name]) && $name == 'set-cookie') {
      // RFC 2109: the Set-Cookie response header comprises the token Set-
      // Cookie:, followed by a comma-separated list of one or more cookies.
      $result->headers[$name] .= ',' . trim($value);
    }
    else {
      $result->headers[$name] = trim($value);
    }
  }

  $responses = array(
    100 => 'Continue',
    101 => 'Switching Protocols',
    200 => 'OK',
    201 => 'Created',
    202 => 'Accepted',
    203 => 'Non-Authoritative Information',
    204 => 'No Content',
    205 => 'Reset Content',
    206 => 'Partial Content',
    300 => 'Multiple Choices',
    301 => 'Moved Permanently',
    302 => 'Found',
    303 => 'See Other',
    304 => 'Not Modified',
    305 => 'Use Proxy',
    307 => 'Temporary Redirect',
    400 => 'Bad Request',
    401 => 'Unauthorized',
    402 => 'Payment Required',
    403 => 'Forbidden',
    404 => 'Not Found',
    405 => 'Method Not Allowed',
    406 => 'Not Acceptable',
    407 => 'Proxy Authentication Required',
    408 => 'Request Time-out',
    409 => 'Conflict',
    410 => 'Gone',
    411 => 'Length Required',
    412 => 'Precondition Failed',
    413 => 'Request Entity Too Large',
    414 => 'Request-URI Too Large',
    415 => 'Unsupported Media Type',
    416 => 'Requested range not satisfiable',
    417 => 'Expectation Failed',
    500 => 'Internal Server Error',
    501 => 'Not Implemented',
    502 => 'Bad Gateway',
    503 => 'Service Unavailable',
    504 => 'Gateway Time-out',
    505 => 'HTTP Version not supported',
  );
  // RFC 2616 states that all unknown HTTP codes must be treated the same as the
  // base code in their class.
  if (!isset($responses[$code])) {
    $code = floor($code / 100) * 100;
  }
  $result->code = $code;

  switch ($code) {
    case 200: // OK
    case 201: // Created
    case 202: // Accepted
    case 203: // Non-Authoritative Information
    case 204: // No Content
    case 205: // Reset Content
    case 206: // Partial Content
    case 304: // Not modified
      break;
    case 301: // Moved permanently
    case 302: // Moved temporarily
    case 307: // Moved temporarily
      $location = $result->headers['location'];
      $options['timeout'] -= timer_read(__FUNCTION__) / 1000;
      if ($options['timeout'] <= 0) {
        $result->code = HTTP_REQUEST_TIMEOUT;
        $result->error = 'request timed out';
      }
      elseif ($options['max_redirects']) {
        // Redirect to the new location.
        $options['max_redirects']--;
        $result = drupal_http_request($location, $options);
        $result->redirect_code = $code;
      }
      if (!isset($result->redirect_url)) {
        $result->redirect_url = $location;
      }
      break;
    default:
      $result->error = $result->status_message;
  }

  return $result;
}

/**
 * Splits an HTTP response status line into components.
 *
 * See the @link http://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html status line definition @endlink
 * in RFC 2616.
 *
 * @param string $respone
 *   The response status line, for example 'HTTP/1.1 500 Internal Server Error'.
 *
 * @return array
 *   Keyed array containing the component parts. If the response is malformed,
 *   all possible parts will be extracted. 'reason_phrase' could be empty.
 *   Possible keys:
 *   - 'http_version'
 *   - 'response_code'
 *   - 'reason_phrase'
 */
function _drupal_parse_response_status($response) {
  $response_array = explode(' ', trim($response), 3);
  // Set up empty values.
  $result = array(
    'reason_phrase' => '',
  );
  $result['http_version'] = $response_array[0];
  $result['response_code'] = $response_array[1];
  if (isset($response_array[2])) {
    $result['reason_phrase'] = $response_array[2];
  }
  return $result;
}

/**
 * Helper function for determining hosts excluded from needing a proxy.
 *
 * @return
 *   TRUE if a proxy should be used for this host.
 */
function _drupal_http_use_proxy($host) {
  $proxy_exceptions = variable_get('proxy_exceptions', array('localhost', '127.0.0.1'));
  return !in_array(strtolower($host), $proxy_exceptions, TRUE);
}

/**
 * @} End of "HTTP handling".
 */

/**
 * Strips slashes from a string or array of strings.
 *
 * Callback for array_walk() within fix_gpx_magic().
 *
 * @param $item
 *   An individual string or array of strings from superglobals.
 */
function _fix_gpc_magic(&$item) {
  if (is_array($item)) {
    array_walk($item, '_fix_gpc_magic');
  }
  else {
    $item = stripslashes($item);
  }
}

/**
 * Strips slashes from $_FILES items.
 *
 * Callback for array_walk() within fix_gpc_magic().
 *
 * The tmp_name key is skipped keys since PHP generates single backslashes for
 * file paths on Windows systems.
 *
 * @param $item
 *   An item from $_FILES.
 * @param $key
 *   The key for the item within $_FILES.
 *
 * @see http://php.net/manual/features.file-upload.php#42280
 */
function _fix_gpc_magic_files(&$item, $key) {
  if ($key != 'tmp_name') {
    if (is_array($item)) {
      array_walk($item, '_fix_gpc_magic_files');
    }
    else {
      $item = stripslashes($item);
    }
  }
}

/**
 * Fixes double-escaping caused by "magic quotes" in some PHP installations.
 *
 * @see _fix_gpc_magic()
 * @see _fix_gpc_magic_files()
 */
function fix_gpc_magic() {
  static $fixed = FALSE;
  if (!$fixed && ini_get('magic_quotes_gpc')) {
    array_walk($_GET, '_fix_gpc_magic');
    array_walk($_POST, '_fix_gpc_magic');
    array_walk($_COOKIE, '_fix_gpc_magic');
    array_walk($_REQUEST, '_fix_gpc_magic');
    array_walk($_FILES, '_fix_gpc_magic_files');
  }
  $fixed = TRUE;
}

/**
 * @defgroup validation Input validation
 * @{
 * Functions to validate user input.
 */

/**
 * Verifies the syntax of the given e-mail address.
 *
 * This uses the
 * @link http://php.net/manual/filter.filters.validate.php PHP e-mail validation filter. @endlink
 *
 * @param $mail
 *   A string containing an e-mail address.
 *
 * @return
 *   TRUE if the address is in a valid format.
 */
function valid_email_address($mail) {
  return (bool)filter_var($mail, FILTER_VALIDATE_EMAIL);
}

/**
 * Verifies the syntax of the given URL.
 *
 * This function should only be used on actual URLs. It should not be used for
 * Drupal menu paths, which can contain arbitrary characters.
 * Valid values per RFC 3986.
 * @param $url
 *   The URL to verify.
 * @param $absolute
 *   Whether the URL is absolute (beginning with a scheme such as "http:").
 *
 * @return
 *   TRUE if the URL is in a valid format.
 */
function valid_url($url, $absolute = FALSE) {
  if ($absolute) {
    return (bool)preg_match("
      /^                                                      # Start at the beginning of the text
      (?:ftp|https?|feed):\/\/                                # Look for ftp, http, https or feed schemes
      (?:                                                     # Userinfo (optional) which is typically
        (?:(?:[\w\.\-\+!$&'\(\)*\+,;=]|%[0-9a-f]{2})+:)*      # a username or a username and password
        (?:[\w\.\-\+%!$&'\(\)*\+,;=]|%[0-9a-f]{2})+@          # combination
      )?
      (?:
        (?:[a-z0-9\-\.]|%[0-9a-f]{2})+                        # A domain name or a IPv4 address
        |(?:\[(?:[0-9a-f]{0,4}:)*(?:[0-9a-f]{0,4})\])         # or a well formed IPv6 address
      )
      (?::[0-9]+)?                                            # Server port number (optional)
      (?:[\/|\?]
        (?:[\w#!:\.\?\+=&@$'~*,;\/\(\)\[\]\-]|%[0-9a-f]{2})   # The path and query (optional)
      *)?
    $/xi", $url);
  }
  else {
    return (bool)preg_match("/^(?:[\w#!:\.\?\+=&@$'~*,;\/\(\)\[\]\-]|%[0-9a-f]{2})+$/i", $url);
  }
}

/**
 * @} End of "defgroup validation".
 */

/**
 * Registers an event for the current visitor to the flood control mechanism.
 *
 * @param $name
 *   The name of an event.
 * @param $window
 *   Optional number of seconds before this event expires. Defaults to 3600 (1
 *   hour). Typically uses the same value as the flood_is_allowed() $window
 *   parameter. Expired events are purged on cron run to prevent the flood table
 *   from growing indefinitely.
 * @param $identifier
 *   Optional identifier (defaults to the current user's IP address).
 */
function flood_register_event($name, $window = 3600, $identifier = NULL) {
  if (!isset($identifier)) {
    $identifier = ip_address();
  }
  db_insert('flood')
    ->fields(array(
      'event' => $name,
      'identifier' => $identifier,
      'timestamp' => REQUEST_TIME,
      'expiration' => REQUEST_TIME + $window,
    ))
    ->execute();
}

/**
 * Makes the flood control mechanism forget an event for the current visitor.
 *
 * @param $name
 *   The name of an event.
 * @param $identifier
 *   Optional identifier (defaults to the current user's IP address).
 */
function flood_clear_event($name, $identifier = NULL) {
  if (!isset($identifier)) {
    $identifier = ip_address();
  }
  db_delete('flood')
    ->condition('event', $name)
    ->condition('identifier', $identifier)
    ->execute();
}

/**
 * Checks whether a user is allowed to proceed with the specified event.
 *
 * Events can have thresholds saying that each user can only do that event
 * a certain number of times in a time window. This function verifies that the
 * current user has not exceeded this threshold.
 *
 * @param $name
 *   The unique name of the event.
 * @param $threshold
 *   The maximum number of times each user can do this event per time window.
 * @param $window
 *   Number of seconds in the time window for this event (default is 3600
 *   seconds, or 1 hour).
 * @param $identifier
 *   Unique identifier of the current user. Defaults to their IP address.
 *
 * @return
 *   TRUE if the user is allowed to proceed. FALSE if they have exceeded the
 *   threshold and should not be allowed to proceed.
 */
function flood_is_allowed($name, $threshold, $window = 3600, $identifier = NULL) {
  if (!isset($identifier)) {
    $identifier = ip_address();
  }
  $number = db_query("SELECT COUNT(*) FROM {flood} WHERE event = :event AND identifier = :identifier AND timestamp > :timestamp", array(
    ':event' => $name,
    ':identifier' => $identifier,
    ':timestamp' => REQUEST_TIME - $window))
    ->fetchField();
  return ($number < $threshold);
}

/**
 * @defgroup sanitization Sanitization functions
 * @{
 * Functions to sanitize values.
 *
 * See http://drupal.org/writing-secure-code for information
 * on writing secure code.
 */

/**
 * Strips dangerous protocols (e.g. 'javascript:') from a URI.
 *
 * This function must be called for all URIs within user-entered input prior
 * to being output to an HTML attribute value. It is often called as part of
 * check_url() or filter_xss(), but those functions return an HTML-encoded
 * string, so this function can be called independently when the output needs to
 * be a plain-text string for passing to t(), l(), drupal_attributes(), or
 * another function that will call check_plain() separately.
 *
 * @param $uri
 *   A plain-text URI that might contain dangerous protocols.
 *
 * @return
 *   A plain-text URI stripped of dangerous protocols. As with all plain-text
 *   strings, this return value must not be output to an HTML page without
 *   check_plain() being called on it. However, it can be passed to functions
 *   expecting plain-text strings.
 *
 * @see check_url()
 */
function drupal_strip_dangerous_protocols($uri) {
  static $allowed_protocols;

  if (!isset($allowed_protocols)) {
    $allowed_protocols = array_flip(variable_get('filter_allowed_protocols', array('ftp', 'http', 'https', 'irc', 'mailto', 'news', 'nntp', 'rtsp', 'sftp', 'ssh', 'tel', 'telnet', 'webcal')));
  }

  // Iteratively remove any invalid protocol found.
  do {
    $before = $uri;
    $colonpos = strpos($uri, ':');
    if ($colonpos > 0) {
      // We found a colon, possibly a protocol. Verify.
      $protocol = substr($uri, 0, $colonpos);
      // If a colon is preceded by a slash, question mark or hash, it cannot
      // possibly be part of the URL scheme. This must be a relative URL, which
      // inherits the (safe) protocol of the base document.
      if (preg_match('![/?#]!', $protocol)) {
        break;
      }
      // Check if this is a disallowed protocol. Per RFC2616, section 3.2.3
      // (URI Comparison) scheme comparison must be case-insensitive.
      if (!isset($allowed_protocols[strtolower($protocol)])) {
        $uri = substr($uri, $colonpos + 1);
      }
    }
  } while ($before != $uri);

  return $uri;
}

/**
 * Strips dangerous protocols from a URI and encodes it for output to HTML.
 *
 * @param $uri
 *   A plain-text URI that might contain dangerous protocols.
 *
 * @return
 *   A URI stripped of dangerous protocols and encoded for output to an HTML
 *   attribute value. Because it is already encoded, it should not be set as a
 *   value within a $attributes array passed to drupal_attributes(), because
 *   drupal_attributes() expects those values to be plain-text strings. To pass
 *   a filtered URI to drupal_attributes(), call
 *   drupal_strip_dangerous_protocols() instead.
 *
 * @see drupal_strip_dangerous_protocols()
 */
function check_url($uri) {
  return check_plain(drupal_strip_dangerous_protocols($uri));
}

/**
 * Applies a very permissive XSS/HTML filter for admin-only use.
 *
 * Use only for fields where it is impractical to use the
 * whole filter system, but where some (mainly inline) mark-up
 * is desired (so check_plain() is not acceptable).
 *
 * Allows all tags that can be used inside an HTML body, save
 * for scripts and styles.
 */
function filter_xss_admin($string) {
  return filter_xss($string, array('a', 'abbr', 'acronym', 'address', 'article', 'aside', 'b', 'bdi', 'bdo', 'big', 'blockquote', 'br', 'caption', 'cite', 'code', 'col', 'colgroup', 'command', 'dd', 'del', 'details', 'dfn', 'div', 'dl', 'dt', 'em', 'figcaption', 'figure', 'footer', 'h1', 'h2', 'h3', 'h4', 'h5', 'h6', 'header', 'hgroup', 'hr', 'i', 'img', 'ins', 'kbd', 'li', 'mark', 'menu', 'meter', 'nav', 'ol', 'output', 'p', 'pre', 'progress', 'q', 'rp', 'rt', 'ruby', 's', 'samp', 'section', 'small', 'span', 'strong', 'sub', 'summary', 'sup', 'table', 'tbody', 'td', 'tfoot', 'th', 'thead', 'time', 'tr', 'tt', 'u', 'ul', 'var', 'wbr'));
}

/**
 * Filters HTML to prevent cross-site-scripting (XSS) vulnerabilities.
 *
 * Based on kses by Ulf Harnhammar, see http://sourceforge.net/projects/kses.
 * For examples of various XSS attacks, see: http://ha.ckers.org/xss.html.
 *
 * This code does four things:
 * - Removes characters and constructs that can trick browsers.
 * - Makes sure all HTML entities are well-formed.
 * - Makes sure all HTML tags and attributes are well-formed.
 * - Makes sure no HTML tags contain URLs with a disallowed protocol (e.g.
 *   javascript:).
 *
 * @param $string
 *   The string with raw HTML in it. It will be stripped of everything that can
 *   cause an XSS attack.
 * @param $allowed_tags
 *   An array of allowed tags.
 *
 * @return
 *   An XSS safe version of $string, or an empty string if $string is not
 *   valid UTF-8.
 *
 * @see drupal_validate_utf8()
 */
function filter_xss($string, $allowed_tags = array('a', 'em', 'strong', 'cite', 'blockquote', 'code', 'ul', 'ol', 'li', 'dl', 'dt', 'dd')) {
  // Only operate on valid UTF-8 strings. This is necessary to prevent cross
  // site scripting issues on Internet Explorer 6.
  if (!drupal_validate_utf8($string)) {
    return '';
  }
  // Store the text format.
  _filter_xss_split($allowed_tags, TRUE);
  // Remove NULL characters (ignored by some browsers).
  $string = str_replace(chr(0), '', $string);
  // Remove Netscape 4 JS entities.
  $string = preg_replace('%&\s*\{[^}]*(\}\s*;?|$)%', '', $string);

  // Defuse all HTML entities.
  $string = str_replace('&', '&amp;', $string);
  // Change back only well-formed entities in our whitelist:
  // Decimal numeric entities.
  $string = preg_replace('/&amp;#([0-9]+;)/', '&#\1', $string);
  // Hexadecimal numeric entities.
  $string = preg_replace('/&amp;#[Xx]0*((?:[0-9A-Fa-f]{2})+;)/', '&#x\1', $string);
  // Named entities.
  $string = preg_replace('/&amp;([A-Za-z][A-Za-z0-9]*;)/', '&\1', $string);

  return preg_replace_callback('%
    (
    <(?=[^a-zA-Z!/])  # a lone <
    |                 # or
    <!--.*?-->        # a comment
    |                 # or
    <[^>]*(>|$)       # a string that starts with a <, up until the > or the end of the string
    |                 # or
    >                 # just a >
    )%x', '_filter_xss_split', $string);
}

/**
 * Processes an HTML tag.
 *
 * @param $m
 *   An array with various meaning depending on the value of $store.
 *   If $store is TRUE then the array contains the allowed tags.
 *   If $store is FALSE then the array has one element, the HTML tag to process.
 * @param $store
 *   Whether to store $m.
 *
 * @return
 *   If the element isn't allowed, an empty string. Otherwise, the cleaned up
 *   version of the HTML element.
 */
function _filter_xss_split($m, $store = FALSE) {
  static $allowed_html;

  if ($store) {
    $allowed_html = array_flip($m);
    return;
  }

  $string = $m[1];

  if (substr($string, 0, 1) != '<') {
    // We matched a lone ">" character.
    return '&gt;';
  }
  elseif (strlen($string) == 1) {
    // We matched a lone "<" character.
    return '&lt;';
  }

  if (!preg_match('%^<\s*(/\s*)?([a-zA-Z0-9\-]+)([^>]*)>?|(<!--.*?-->)$%', $string, $matches)) {
    // Seriously malformed.
    return '';
  }

  $slash = trim($matches[1]);
  $elem = &$matches[2];
  $attrlist = &$matches[3];
  $comment = &$matches[4];

  if ($comment) {
    $elem = '!--';
  }

  if (!isset($allowed_html[strtolower($elem)])) {
    // Disallowed HTML element.
    return '';
  }

  if ($comment) {
    return $comment;
  }

  if ($slash != '') {
    return "</$elem>";
  }

  // Is there a closing XHTML slash at the end of the attributes?
  $attrlist = preg_replace('%(\s?)/\s*$%', '\1', $attrlist, -1, $count);
  $xhtml_slash = $count ? ' /' : '';

  // Clean up attributes.
  $attr2 = implode(' ', _filter_xss_attributes($attrlist));
  $attr2 = preg_replace('/[<>]/', '', $attr2);
  $attr2 = strlen($attr2) ? ' ' . $attr2 : '';

  return "<$elem$attr2$xhtml_slash>";
}

/**
 * Processes a string of HTML attributes.
 *
 * @return
 *   Cleaned up version of the HTML attributes.
 */
function _filter_xss_attributes($attr) {
  $attrarr = array();
  $mode = 0;
  $attrname = '';

  while (strlen($attr) != 0) {
    // Was the last operation successful?
    $working = 0;

    switch ($mode) {
      case 0:
        // Attribute name, href for instance.
        if (preg_match('/^([-a-zA-Z]+)/', $attr, $match)) {
          $attrname = strtolower($match[1]);
          $skip = ($attrname == 'style' || substr($attrname, 0, 2) == 'on');
          $working = $mode = 1;
          $attr = preg_replace('/^[-a-zA-Z]+/', '', $attr);
        }
        break;

      case 1:
        // Equals sign or valueless ("selected").
        if (preg_match('/^\s*=\s*/', $attr)) {
          $working = 1; $mode = 2;
          $attr = preg_replace('/^\s*=\s*/', '', $attr);
          break;
        }

        if (preg_match('/^\s+/', $attr)) {
          $working = 1; $mode = 0;
          if (!$skip) {
            $attrarr[] = $attrname;
          }
          $attr = preg_replace('/^\s+/', '', $attr);
        }
        break;

      case 2:
        // Attribute value, a URL after href= for instance.
        if (preg_match('/^"([^"]*)"(\s+|$)/', $attr, $match)) {
          $thisval = filter_xss_bad_protocol($match[1]);

          if (!$skip) {
            $attrarr[] = "$attrname=\"$thisval\"";
          }
          $working = 1;
          $mode = 0;
          $attr = preg_replace('/^"[^"]*"(\s+|$)/', '', $attr);
          break;
        }

        if (preg_match("/^'([^']*)'(\s+|$)/", $attr, $match)) {
          $thisval = filter_xss_bad_protocol($match[1]);

          if (!$skip) {
            $attrarr[] = "$attrname='$thisval'";
          }
          $working = 1; $mode = 0;
          $attr = preg_replace("/^'[^']*'(\s+|$)/", '', $attr);
          break;
        }

        if (preg_match("%^([^\s\"']+)(\s+|$)%", $attr, $match)) {
          $thisval = filter_xss_bad_protocol($match[1]);

          if (!$skip) {
            $attrarr[] = "$attrname=\"$thisval\"";
          }
          $working = 1; $mode = 0;
          $attr = preg_replace("%^[^\s\"']+(\s+|$)%", '', $attr);
        }
        break;
    }

    if ($working == 0) {
      // Not well formed; remove and try again.
      $attr = preg_replace('/
        ^
        (
        "[^"]*("|$)     # - a string that starts with a double quote, up until the next double quote or the end of the string
        |               # or
        \'[^\']*(\'|$)| # - a string that starts with a quote, up until the next quote or the end of the string
        |               # or
        \S              # - a non-whitespace character
        )*              # any number of the above three
        \s*             # any number of whitespaces
        /x', '', $attr);
      $mode = 0;
    }
  }

  // The attribute list ends with a valueless attribute like "selected".
  if ($mode == 1 && !$skip) {
    $attrarr[] = $attrname;
  }
  return $attrarr;
}

/**
 * Processes an HTML attribute value and strips dangerous protocols from URLs.
 *
 * @param $string
 *   The string with the attribute value.
 * @param $decode
 *   (deprecated) Whether to decode entities in the $string. Set to FALSE if the
 *   $string is in plain text, TRUE otherwise. Defaults to TRUE. This parameter
 *   is deprecated and will be removed in Drupal 8. To process a plain-text URI,
 *   call drupal_strip_dangerous_protocols() or check_url() instead.
 *
 * @return
 *   Cleaned up and HTML-escaped version of $string.
 */
function filter_xss_bad_protocol($string, $decode = TRUE) {
  // Get the plain text representation of the attribute value (i.e. its meaning).
  // @todo Remove the $decode parameter in Drupal 8, and always assume an HTML
  //   string that needs decoding.
  if ($decode) {
    if (!function_exists('decode_entities')) {
      require_once DRUPAL_ROOT . '/includes/unicode.inc';
    }

    $string = decode_entities($string);
  }
  return check_plain(drupal_strip_dangerous_protocols($string));
}

/**
 * @} End of "defgroup sanitization".
 */

/**
 * @defgroup format Formatting
 * @{
 * Functions to format numbers, strings, dates, etc.
 */

/**
 * Formats an RSS channel.
 *
 * Arbitrary elements may be added using the $args associative array.
 */
function format_rss_channel($title, $link, $description, $items, $langcode = NULL, $args = array()) {
  global $language_content;
  $langcode = $langcode ? $langcode : $language_content->language;

  $output = "<channel>\n";
  $output .= ' <title>' . check_plain($title) . "</title>\n";
  $output .= ' <link>' . check_url($link) . "</link>\n";

  // The RSS 2.0 "spec" doesn't indicate HTML can be used in the description.
  // We strip all HTML tags, but need to prevent double encoding from properly
  // escaped source data (such as &amp becoming &amp;amp;).
  $output .= ' <description>' . check_plain(decode_entities(strip_tags($description))) . "</description>\n";
  $output .= ' <language>' . check_plain($langcode) . "</language>\n";
  $output .= format_xml_elements($args);
  $output .= $items;
  $output .= "</channel>\n";

  return $output;
}

/**
 * Formats a single RSS item.
 *
 * Arbitrary elements may be added using the $args associative array.
 */
function format_rss_item($title, $link, $description, $args = array()) {
  $output = "<item>\n";
  $output .= ' <title>' . check_plain($title) . "</title>\n";
  $output .= ' <link>' . check_url($link) . "</link>\n";
  $output .= ' <description>' . check_plain($description) . "</description>\n";
  $output .= format_xml_elements($args);
  $output .= "</item>\n";

  return $output;
}

/**
 * Formats XML elements.
 *
 * @param $array
 *   An array where each item represents an element and is either a:
 *   - (key => value) pair (<key>value</key>)
 *   - Associative array with fields:
 *     - 'key': element name
 *     - 'value': element contents
 *     - 'attributes': associative array of element attributes
 *     - 'encoded': TRUE if 'value' is already encoded
 *
 * In both cases, 'value' can be a simple string, or it can be another array
 * with the same format as $array itself for nesting.
 *
 * If 'encoded' is TRUE it is up to the caller to ensure that 'value' is either
 * entity-encoded or CDATA-escaped. Using this option is not recommended when
 * working with untrusted user input, since failing to escape the data
 * correctly has security implications.
 */
function format_xml_elements($array) {
  $output = '';
  foreach ($array as $key => $value) {
    if (is_numeric($key)) {
      if ($value['key']) {
        $output .= ' <' . $value['key'];
        if (isset($value['attributes']) && is_array($value['attributes'])) {
          $output .= drupal_attributes($value['attributes']);
        }

        if (isset($value['value']) && $value['value'] != '') {
          $output .= '>' . (is_array($value['value']) ? format_xml_elements($value['value']) : (!empty($value['encoded']) ? $value['value'] : check_plain($value['value']))) . '</' . $value['key'] . ">\n";
        }
        else {
          $output .= " />\n";
        }
      }
    }
    else {
      $output .= ' <' . $key . '>' . (is_array($value) ? format_xml_elements($value) : check_plain($value)) . "</$key>\n";
    }
  }
  return $output;
}

/**
 * Formats a string containing a count of items.
 *
 * This function ensures that the string is pluralized correctly. Since t() is
 * called by this function, make sure not to pass already-localized strings to
 * it.
 *
 * For example:
 * @code
 *   $output = format_plural($node->comment_count, '1 comment', '@count comments');
 * @endcode
 *
 * Example with additional replacements:
 * @code
 *   $output = format_plural($update_count,
 *     'Changed the content type of 1 post from %old-type to %new-type.',
 *     'Changed the content type of @count posts from %old-type to %new-type.',
 *     array('%old-type' => $info->old_type, '%new-type' => $info->new_type));
 * @endcode
 *
 * @param $count
 *   The item count to display.
 * @param $singular
 *   The string for the singular case. Make sure it is clear this is singular,
 *   to ease translation (e.g. use "1 new comment" instead of "1 new"). Do not
 *   use @count in the singular string.
 * @param $plural
 *   The string for the plural case. Make sure it is clear this is plural, to
 *   ease translation. Use @count in place of the item count, as in
 *   "@count new comments".
 * @param $args
 *   An associative array of replacements to make after translation. Instances
 *   of any key in this array are replaced with the corresponding value.
 *   Based on the first character of the key, the value is escaped and/or
 *   themed. See format_string(). Note that you do not need to include @count
 *   in this array; this replacement is done automatically for the plural case.
 * @param $options
 *   An associative array of additional options. See t() for allowed keys.
 *
 * @return
 *   A translated string.
 *
 * @see t()
 * @see format_string()
 */
function format_plural($count, $singular, $plural, array $args = array(), array $options = array()) {
  $args['@count'] = $count;
  if ($count == 1) {
    return t($singular, $args, $options);
  }

  // Get the plural index through the gettext formula.
  $index = (function_exists('locale_get_plural')) ? locale_get_plural($count, isset($options['langcode']) ? $options['langcode'] : NULL) : -1;
  // If the index cannot be computed, use the plural as a fallback (which
  // allows for most flexiblity with the replaceable @count value).
  if ($index < 0) {
    return t($plural, $args, $options);
  }
  else {
    switch ($index) {
      case "0":
        return t($singular, $args, $options);
      case "1":
        return t($plural, $args, $options);
      default:
        unset($args['@count']);
        $args['@count[' . $index . ']'] = $count;
        return t(strtr($plural, array('@count' => '@count[' . $index . ']')), $args, $options);
    }
  }
}

/**
 * Parses a given byte count.
 *
 * @param $size
 *   A size expressed as a number of bytes with optional SI or IEC binary unit
 *   prefix (e.g. 2, 3K, 5MB, 10G, 6GiB, 8 bytes, 9mbytes).
 *
 * @return
 *   An integer representation of the size in bytes.
 */
function parse_size($size) {
  $unit = preg_replace('/[^bkmgtpezy]/i', '', $size); // Remove the non-unit characters from the size.
  $size = preg_replace('/[^0-9\.]/', '', $size); // Remove the non-numeric characters from the size.
  if ($unit) {
    // Find the position of the unit in the ordered string which is the power of magnitude to multiply a kilobyte by.
    return round($size * pow(DRUPAL_KILOBYTE, stripos('bkmgtpezy', $unit[0])));
  }
  else {
    return round($size);
  }
}

/**
 * Generates a string representation for the given byte count.
 *
 * @param $size
 *   A size in bytes.
 * @param $langcode
 *   Optional language code to translate to a language other than what is used
 *   to display the page.
 *
 * @return
 *   A translated string representation of the size.
 */
function format_size($size, $langcode = NULL) {
  if ($size < DRUPAL_KILOBYTE) {
    return format_plural($size, '1 byte', '@count bytes', array(), array('langcode' => $langcode));
  }
  else {
    $size = $size / DRUPAL_KILOBYTE; // Convert bytes to kilobytes.
    $units = array(
      t('@size KB', array(), array('langcode' => $langcode)),
      t('@size MB', array(), array('langcode' => $langcode)),
      t('@size GB', array(), array('langcode' => $langcode)),
      t('@size TB', array(), array('langcode' => $langcode)),
      t('@size PB', array(), array('langcode' => $langcode)),
      t('@size EB', array(), array('langcode' => $langcode)),
      t('@size ZB', array(), array('langcode' => $langcode)),
      t('@size YB', array(), array('langcode' => $langcode)),
    );
    foreach ($units as $unit) {
      if (round($size, 2) >= DRUPAL_KILOBYTE) {
        $size = $size / DRUPAL_KILOBYTE;
      }
      else {
        break;
      }
    }
    return str_replace('@size', round($size, 2), $unit);
  }
}

/**
 * Formats a time interval with the requested granularity.
 *
 * @param $interval
 *   The length of the interval in seconds.
 * @param $granularity
 *   How many different units to display in the string.
 * @param $langcode
 *   Optional language code to translate to a language other than
 *   what is used to display the page.
 *
 * @return
 *   A translated string representation of the interval.
 */
function format_interval($interval, $granularity = 2, $langcode = NULL) {
  $units = array(
    '1 year|@count years' => 31536000,
    '1 month|@count months' => 2592000,
    '1 week|@count weeks' => 604800,
    '1 day|@count days' => 86400,
    '1 hour|@count hours' => 3600,
    '1 min|@count min' => 60,
    '1 sec|@count sec' => 1
  );
  $output = '';
  foreach ($units as $key => $value) {
    $key = explode('|', $key);
    if ($interval >= $value) {
      $output .= ($output ? ' ' : '') . format_plural(floor($interval / $value), $key[0], $key[1], array(), array('langcode' => $langcode));
      $interval %= $value;
      $granularity--;
    }

    if ($granularity == 0) {
      break;
    }
  }
  return $output ? $output : t('0 sec', array(), array('langcode' => $langcode));
}

/**
 * Formats a date, using a date type or a custom date format string.
 *
 * @param $timestamp
 *   A UNIX timestamp to format.
 * @param $type
 *   (optional) The format to use, one of:
 *   - 'short', 'medium', or 'long' (the corresponding built-in date formats).
 *   - The name of a date type defined by a module in hook_date_format_types(),
 *     if it's been assigned a format.
 *   - The machine name of an administrator-defined date format.
 *   - 'custom', to use $format.
 *   Defaults to 'medium'.
 * @param $format
 *   (optional) If $type is 'custom', a PHP date format string suitable for
 *   input to date(). Use a backslash to escape ordinary text, so it does not
 *   get interpreted as date format characters.
 * @param $timezone
 *   (optional) Time zone identifier, as described at
 *   http://php.net/manual/timezones.php Defaults to the time zone used to
 *   display the page.
 * @param $langcode
 *   (optional) Language code to translate to. Defaults to the language used to
 *   display the page.
 *
 * @return
 *   A translated date string in the requested format.
 */
function format_date($timestamp, $type = 'medium', $format = '', $timezone = NULL, $langcode = NULL) {
  // Use the advanced drupal_static() pattern, since this is called very often.
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['timezones'] = &drupal_static(__FUNCTION__);
  }
  $timezones = &$drupal_static_fast['timezones'];

  if (!isset($timezone)) {
    $timezone = date_default_timezone_get();
  }
  // Store DateTimeZone objects in an array rather than repeatedly
  // constructing identical objects over the life of a request.
  if (!isset($timezones[$timezone])) {
    $timezones[$timezone] = timezone_open($timezone);
  }

  // Use the default langcode if none is set.
  global $language;
  if (empty($langcode)) {
    $langcode = isset($language->language) ? $language->language : 'en';
  }

  switch ($type) {
    case 'short':
      $format = variable_get('date_format_short', 'm/d/Y - H:i');
      break;

    case 'long':
      $format = variable_get('date_format_long', 'l, F j, Y - H:i');
      break;

    case 'custom':
      // No change to format.
      break;

    case 'medium':
    default:
      // Retrieve the format of the custom $type passed.
      if ($type != 'medium') {
        $format = variable_get('date_format_' . $type, '');
      }
      // Fall back to 'medium'.
      if ($format === '') {
        $format = variable_get('date_format_medium', 'D, m/d/Y - H:i');
      }
      break;
  }

  // Create a DateTime object from the timestamp.
  $date_time = date_create('@' . $timestamp);
  // Set the time zone for the DateTime object.
  date_timezone_set($date_time, $timezones[$timezone]);

  // Encode markers that should be translated. 'A' becomes '\xEF\AA\xFF'.
  // xEF and xFF are invalid UTF-8 sequences, and we assume they are not in the
  // input string.
  // Paired backslashes are isolated to prevent errors in read-ahead evaluation.
  // The read-ahead expression ensures that A matches, but not \A.
  $format = preg_replace(array('/\\\\\\\\/', '/(?<!\\\\)([AaeDlMTF])/'), array("\xEF\\\\\\\\\xFF", "\xEF\\\\\$1\$1\xFF"), $format);

  // Call date_format().
  $format = date_format($date_time, $format);

  // Pass the langcode to _format_date_callback().
  _format_date_callback(NULL, $langcode);

  // Translate the marked sequences.
  return preg_replace_callback('/\xEF([AaeDlMTF]?)(.*?)\xFF/', '_format_date_callback', $format);
}

/**
 * Returns an ISO8601 formatted date based on the given date.
 *
 * Callback for use within hook_rdf_mapping() implementations.
 *
 * @param $date
 *   A UNIX timestamp.
 *
 * @return string
 *   An ISO8601 formatted date.
 */
function date_iso8601($date) {
  // The DATE_ISO8601 constant cannot be used here because it does not match
  // date('c') and produces invalid RDF markup.
  return date('c', $date);
}

/**
 * Translates a formatted date string.
 *
 * Callback for preg_replace_callback() within format_date().
 */
function _format_date_callback(array $matches = NULL, $new_langcode = NULL) {
  // We cache translations to avoid redundant and rather costly calls to t().
  static $cache, $langcode;

  if (!isset($matches)) {
    $langcode = $new_langcode;
    return;
  }

  $code = $matches[1];
  $string = $matches[2];

  if (!isset($cache[$langcode][$code][$string])) {
    $options = array(
      'langcode' => $langcode,
    );

    if ($code == 'F') {
      $options['context'] = 'Long month name';
    }

    if ($code == '') {
      $cache[$langcode][$code][$string] = $string;
    }
    else {
      $cache[$langcode][$code][$string] = t($string, array(), $options);
    }
  }
  return $cache[$langcode][$code][$string];
}

/**
 * Format a username.
 *
 * This is also the label callback implementation of
 * callback_entity_info_label() for user_entity_info().
 *
 * By default, the passed-in object's 'name' property is used if it exists, or
 * else, the site-defined value for the 'anonymous' variable. However, a module
 * may override this by implementing hook_username_alter(&$name, $account).
 *
 * @see hook_username_alter()
 *
 * @param $account
 *   The account object for the user whose name is to be formatted.
 *
 * @return
 *   An unsanitized string with the username to display. The code receiving
 *   this result must ensure that check_plain() is called on it before it is
 *   printed to the page.
 */
function format_username($account) {
  $name = !empty($account->name) ? $account->name : variable_get('anonymous', t('Anonymous'));
  drupal_alter('username', $name, $account);
  return $name;
}

/**
 * @} End of "defgroup format".
 */

/**
 * Generates an internal or external URL.
 *
 * When creating links in modules, consider whether l() could be a better
 * alternative than url().
 *
 * @param $path
 *   (optional) The internal path or external URL being linked to, such as
 *   "node/34" or "http://example.com/foo". The default value is equivalent to
 *   passing in '<front>'. A few notes:
 *   - If you provide a full URL, it will be considered an external URL.
 *   - If you provide only the path (e.g. "node/34"), it will be
 *     considered an internal link. In this case, it should be a system URL,
 *     and it will be replaced with the alias, if one exists. Additional query
 *     arguments for internal paths must be supplied in $options['query'], not
 *     included in $path.
 *   - If you provide an internal path and $options['alias'] is set to TRUE, the
 *     path is assumed already to be the correct path alias, and the alias is
 *     not looked up.
 *   - The special string '<front>' generates a link to the site's base URL.
 *   - If your external URL contains a query (e.g. http://example.com/foo?a=b),
 *     then you can either URL encode the query keys and values yourself and
 *     include them in $path, or use $options['query'] to let this function
 *     URL encode them.
 * @param $options
 *   (optional) An associative array of additional options, with the following
 *   elements:
 *   - 'query': An array of query key/value-pairs (without any URL-encoding) to
 *     append to the URL.
 *   - 'fragment': A fragment identifier (named anchor) to append to the URL.
 *     Do not include the leading '#' character.
 *   - 'absolute': Defaults to FALSE. Whether to force the output to be an
 *     absolute link (beginning with http:). Useful for links that will be
 *     displayed outside the site, such as in an RSS feed.
 *   - 'alias': Defaults to FALSE. Whether the given path is a URL alias
 *     already.
 *   - 'external': Whether the given path is an external URL.
 *   - 'language': An optional language object. If the path being linked to is
 *     internal to the site, $options['language'] is used to look up the alias
 *     for the URL. If $options['language'] is omitted, the global $language_url
 *     will be used.
 *   - 'https': Whether this URL should point to a secure location. If not
 *     defined, the current scheme is used, so the user stays on HTTP or HTTPS
 *     respectively. TRUE enforces HTTPS and FALSE enforces HTTP, but HTTPS can
 *     only be enforced when the variable 'https' is set to TRUE.
 *   - 'base_url': Only used internally, to modify the base URL when a language
 *     dependent URL requires so.
 *   - 'prefix': Only used internally, to modify the path when a language
 *     dependent URL requires so.
 *   - 'script': The script filename in Drupal's root directory to use when
 *     clean URLs are disabled, such as 'index.php'. Defaults to an empty
 *     string, as most modern web servers automatically find 'index.php'. If
 *     clean URLs are disabled, the value of $path is appended as query
 *     parameter 'q' to $options['script'] in the returned URL. When deploying
 *     Drupal on a web server that cannot be configured to automatically find
 *     index.php, then hook_url_outbound_alter() can be implemented to force
 *     this value to 'index.php'.
 *   - 'entity_type': The entity type of the object that called url(). Only
 *     set if url() is invoked by entity_uri().
 *   - 'entity': The entity object (such as a node) for which the URL is being
 *     generated. Only set if url() is invoked by entity_uri().
 *
 * @return
 *   A string containing a URL to the given path.
 */
function url($path = NULL, array $options = array()) {
  // Merge in defaults.
  $options += array(
    'fragment' => '',
    'query' => array(),
    'absolute' => FALSE,
    'alias' => FALSE,
    'prefix' => ''
  );

  if (!isset($options['external'])) {
    $options['external'] = url_is_external($path);
  }

  // Preserve the original path before altering or aliasing.
  $original_path = $path;

  // Allow other modules to alter the outbound URL and options.
  drupal_alter('url_outbound', $path, $options, $original_path);

  if (isset($options['fragment']) && $options['fragment'] !== '') {
    $options['fragment'] = '#' . $options['fragment'];
  }

  if ($options['external']) {
    // Split off the fragment.
    if (strpos($path, '#') !== FALSE) {
      list($path, $old_fragment) = explode('#', $path, 2);
      // If $options contains no fragment, take it over from the path.
      if (isset($old_fragment) && !$options['fragment']) {
        $options['fragment'] = '#' . $old_fragment;
      }
    }
    // Append the query.
    if ($options['query']) {
      $path .= (strpos($path, '?') !== FALSE ? '&' : '?') . drupal_http_build_query($options['query']);
    }
    if (isset($options['https']) && variable_get('https', FALSE)) {
      if ($options['https'] === TRUE) {
        $path = str_replace('http://', 'https://', $path);
      }
      elseif ($options['https'] === FALSE) {
        $path = str_replace('https://', 'http://', $path);
      }
    }
    // Reassemble.
    return $path . $options['fragment'];
  }

  // Strip leading slashes from internal paths to prevent them becoming external
  // URLs without protocol. /example.com should not be turned into
  // //example.com.
  $path = ltrim($path, '/');

  global $base_url, $base_secure_url, $base_insecure_url;

  // The base_url might be rewritten from the language rewrite in domain mode.
  if (!isset($options['base_url'])) {
    if (isset($options['https']) && variable_get('https', FALSE)) {
      if ($options['https'] === TRUE) {
        $options['base_url'] = $base_secure_url;
        $options['absolute'] = TRUE;
      }
      elseif ($options['https'] === FALSE) {
        $options['base_url'] = $base_insecure_url;
        $options['absolute'] = TRUE;
      }
    }
    else {
      $options['base_url'] = $base_url;
    }
  }

  // The special path '<front>' links to the default front page.
  if ($path == '<front>') {
    $path = '';
  }
  elseif (!empty($path) && !$options['alias']) {
    $language = isset($options['language']) && isset($options['language']->language) ? $options['language']->language : '';
    $alias = drupal_get_path_alias($original_path, $language);
    if ($alias != $original_path) {
      $path = $alias;
    }
  }

  $base = $options['absolute'] ? $options['base_url'] . '/' : base_path();
  $prefix = empty($path) ? rtrim($options['prefix'], '/') : $options['prefix'];

  // With Clean URLs.
  if (!empty($GLOBALS['conf']['clean_url'])) {
    $path = drupal_encode_path($prefix . $path);
    if ($options['query']) {
      return $base . $path . '?' . drupal_http_build_query($options['query']) . $options['fragment'];
    }
    else {
      return $base . $path . $options['fragment'];
    }
  }
  // Without Clean URLs.
  else {
    $path = $prefix . $path;
    $query = array();
    if (!empty($path)) {
      $query['q'] = $path;
    }
    if ($options['query']) {
      // We do not use array_merge() here to prevent overriding $path via query
      // parameters.
      $query += $options['query'];
    }
    $query = $query ? ('?' . drupal_http_build_query($query)) : '';
    $script = isset($options['script']) ? $options['script'] : '';
    return $base . $script . $query . $options['fragment'];
  }
}

/**
 * Returns TRUE if a path is external to Drupal (e.g. http://example.com).
 *
 * If a path cannot be assessed by Drupal's menu handler, then we must
 * treat it as potentially insecure.
 *
 * @param $path
 *   The internal path or external URL being linked to, such as "node/34" or
 *   "http://example.com/foo".
 *
 * @return
 *   Boolean TRUE or FALSE, where TRUE indicates an external path.
 */
function url_is_external($path) {
  $colonpos = strpos($path, ':');
  // Some browsers treat \ as / so normalize to forward slashes.
  $path = str_replace('\\', '/', $path);
  // If the path starts with 2 slashes then it is always considered an external
  // URL without an explicit protocol part.
  return (strpos($path, '//') === 0)
    // Leading control characters may be ignored or mishandled by browsers, so
    // assume such a path may lead to an external location. The \p{C} character
    // class matches all UTF-8 control, unassigned, and private characters.
    || (preg_match('/^\p{C}/u', $path) !== 0)
    // Avoid calling drupal_strip_dangerous_protocols() if there is any slash
    // (/), hash (#) or question_mark (?) before the colon (:) occurrence - if
    // any - as this would clearly mean it is not a URL.
    || ($colonpos !== FALSE
      && !preg_match('![/?#]!', substr($path, 0, $colonpos))
      && drupal_strip_dangerous_protocols($path) == $path);
}

/**
 * Formats an attribute string for an HTTP header.
 *
 * @param $attributes
 *   An associative array of attributes such as 'rel'.
 *
 * @return
 *   A ; separated string ready for insertion in a HTTP header. No escaping is
 *   performed for HTML entities, so this string is not safe to be printed.
 *
 * @see drupal_add_http_header()
 */
function drupal_http_header_attributes(array $attributes = array()) {
  foreach ($attributes as $attribute => &$data) {
    if (is_array($data)) {
      $data = implode(' ', $data);
    }
    $data = $attribute . '="' . $data . '"';
  }
  return $attributes ? ' ' . implode('; ', $attributes) : '';
}

/**
 * Converts an associative array to an XML/HTML tag attribute string.
 *
 * Each array key and its value will be formatted into an attribute string.
 * If a value is itself an array, then its elements are concatenated to a single
 * space-delimited string (for example, a class attribute with multiple values).
 *
 * Attribute values are sanitized by running them through check_plain().
 * Attribute names are not automatically sanitized. When using user-supplied
 * attribute names, it is strongly recommended to allow only white-listed names,
 * since certain attributes carry security risks and can be abused.
 *
 * Examples of security aspects when using drupal_attributes:
 * @code
 *   // By running the value in the following statement through check_plain,
 *   // the malicious script is neutralized.
 *   drupal_attributes(array('title' => t('<script>steal_cookie();</script>')));
 *
 *   // The statement below demonstrates dangerous use of drupal_attributes, and
 *   // will return an onmouseout attribute with JavaScript code that, when used
 *   // as attribute in a tag, will cause users to be redirected to another site.
 *   //
 *   // In this case, the 'onmouseout' attribute should not be whitelisted --
 *   // you don't want users to have the ability to add this attribute or others
 *   // that take JavaScript commands.
 *   drupal_attributes(array('onmouseout' => 'window.location="http://malicious.com/";')));
 * @endcode
 *
 * @param $attributes
 *   An associative array of key-value pairs to be converted to attributes.
 *
 * @return
 *   A string ready for insertion in a tag (starts with a space).
 *
 * @ingroup sanitization
 */
function drupal_attributes(array $attributes = array()) {
  foreach ($attributes as $attribute => &$data) {
    $data = implode(' ', (array) $data);
    $data = $attribute . '="' . check_plain($data) . '"';
  }
  return $attributes ? ' ' . implode(' ', $attributes) : '';
}

/**
 * Formats an internal or external URL link as an HTML anchor tag.
 *
 * This function correctly handles aliased paths and adds an 'active' class
 * attribute to links that point to the current page (for theming), so all
 * internal links output by modules should be generated by this function if
 * possible.
 *
 * However, for links enclosed in translatable text you should use t() and
 * embed the HTML anchor tag directly in the translated string. For example:
 * @code
 * t('Visit the <a href="@url">settings</a> page', array('@url' => url('admin')));
 * @endcode
 * This keeps the context of the link title ('settings' in the example) for
 * translators.
 *
 * @param string $text
 *   The translated link text for the anchor tag.
 * @param string $path
 *   The internal path or external URL being linked to, such as "node/34" or
 *   "http://example.com/foo". After the url() function is called to construct
 *   the URL from $path and $options, the resulting URL is passed through
 *   check_plain() before it is inserted into the HTML anchor tag, to ensure
 *   well-formed HTML. See url() for more information and notes.
 * @param array $options
 *   An associative array of additional options. Defaults to an empty array. It
 *   may contain the following elements.
 *   - 'attributes': An associative array of HTML attributes to apply to the
 *     anchor tag. If element 'class' is included, it must be an array; 'title'
 *     must be a string; other elements are more flexible, as they just need
 *     to work in a call to drupal_attributes($options['attributes']).
 *   - 'html' (default FALSE): Whether $text is HTML or just plain-text. For
 *     example, to make an image tag into a link, this must be set to TRUE, or
 *     you will see the escaped HTML image tag. $text is not sanitized if
 *     'html' is TRUE. The calling function must ensure that $text is already
 *     safe.
 *   - 'language': An optional language object. If the path being linked to is
 *     internal to the site, $options['language'] is used to determine whether
 *     the link is "active", or pointing to the current page (the language as
 *     well as the path must match). This element is also used by url().
 *   - Additional $options elements used by the url() function.
 *
 * @return string
 *   An HTML string containing a link to the given path.
 *
 * @see url()
 */
function l($text, $path, array $options = array()) {
  global $language_url;
  static $use_theme = NULL;

  // Merge in defaults.
  $options += array(
    'attributes' => array(),
    'html' => FALSE,
  );

  // Append active class.
  if (($path == $_GET['q'] || ($path == '<front>' && drupal_is_front_page())) &&
      (empty($options['language']) || $options['language']->language == $language_url->language)) {
    $options['attributes']['class'][] = 'active';
  }

  // Remove all HTML and PHP tags from a tooltip. For best performance, we act only
  // if a quick strpos() pre-check gave a suspicion (because strip_tags() is expensive).
  if (isset($options['attributes']['title']) && strpos($options['attributes']['title'], '<') !== FALSE) {
    $options['attributes']['title'] = strip_tags($options['attributes']['title']);
  }

  // Determine if rendering of the link is to be done with a theme function
  // or the inline default. Inline is faster, but if the theme system has been
  // loaded and a module or theme implements a preprocess or process function
  // or overrides the theme_link() function, then invoke theme(). Preliminary
  // benchmarks indicate that invoking theme() can slow down the l() function
  // by 20% or more, and that some of the link-heavy Drupal pages spend more
  // than 10% of the total page request time in the l() function.
  if (!isset($use_theme) && function_exists('theme')) {
    // Allow edge cases to prevent theme initialization and force inline link
    // rendering.
    if (variable_get('theme_link', TRUE)) {
      drupal_theme_initialize();
      $registry = theme_get_registry(FALSE);
      // We don't want to duplicate functionality that's in theme(), so any
      // hint of a module or theme doing anything at all special with the 'link'
      // theme hook should simply result in theme() being called. This includes
      // the overriding of theme_link() with an alternate function or template,
      // the presence of preprocess or process functions, or the presence of
      // include files.
      $use_theme = !isset($registry['link']['function']) || ($registry['link']['function'] != 'theme_link');
      $use_theme = $use_theme || !empty($registry['link']['preprocess functions']) || !empty($registry['link']['process functions']) || !empty($registry['link']['includes']);
    }
    else {
      $use_theme = FALSE;
    }
  }
  if ($use_theme) {
    return theme('link', array('text' => $text, 'path' => $path, 'options' => $options));
  }
  // The result of url() is a plain-text URL. Because we are using it here
  // in an HTML argument context, we need to encode it properly.
  return '<a href="' . check_plain(url($path, $options)) . '"' . drupal_attributes($options['attributes']) . '>' . ($options['html'] ? $text : check_plain($text)) . '</a>';
}

/**
 * Delivers a page callback result to the browser in the appropriate format.
 *
 * This function is most commonly called by menu_execute_active_handler(), but
 * can also be called by error conditions such as drupal_not_found(),
 * drupal_access_denied(), and drupal_site_offline().
 *
 * When a user requests a page, index.php calls menu_execute_active_handler(),
 * which calls the 'page callback' function registered in hook_menu(). The page
 * callback function can return one of:
 * - NULL: to indicate no content.
 * - An integer menu status constant: to indicate an error condition.
 * - A string of HTML content.
 * - A renderable array of content.
 * Returning a renderable array rather than a string of HTML is preferred,
 * because that provides modules with more flexibility in customizing the final
 * result.
 *
 * When the page callback returns its constructed content to
 * menu_execute_active_handler(), this function gets called. The purpose of
 * this function is to determine the most appropriate 'delivery callback'
 * function to route the content to. The delivery callback function then
 * sends the content to the browser in the needed format. The default delivery
 * callback is drupal_deliver_html_page(), which delivers the content as an HTML
 * page, complete with blocks in addition to the content. This default can be
 * overridden on a per menu router item basis by setting 'delivery callback' in
 * hook_menu() or hook_menu_alter(), and can also be overridden on a per request
 * basis in hook_page_delivery_callback_alter().
 *
 * For example, the same page callback function can be used for an HTML
 * version of the page and an Ajax version of the page. The page callback
 * function just needs to decide what content is to be returned and the
 * delivery callback function will send it as an HTML page or an Ajax
 * response, as appropriate.
 *
 * In order for page callbacks to be reusable in different delivery formats,
 * they should not issue any "print" or "echo" statements, but instead just
 * return content.
 *
 * Also note that this function does not perform access checks. The delivery
 * callback function specified in hook_menu(), hook_menu_alter(), or
 * hook_page_delivery_callback_alter() will be called even if the router item
 * access checks fail. This is intentional (it is needed for JSON and other
 * purposes), but it has security implications. Do not call this function
 * directly unless you understand the security implications, and be careful in
 * writing delivery callbacks, so that they do not violate security. See
 * drupal_deliver_html_page() for an example of a delivery callback that
 * respects security.
 *
 * @param $page_callback_result
 *   The result of a page callback. Can be one of:
 *   - NULL: to indicate no content.
 *   - An integer menu status constant: to indicate an error condition.
 *   - A string of HTML content.
 *   - A renderable array of content.
 * @param $default_delivery_callback
 *   (Optional) If given, it is the name of a delivery function most likely
 *   to be appropriate for the page request as determined by the calling
 *   function (e.g., menu_execute_active_handler()). If not given, it is
 *   determined from the menu router information of the current page.
 *
 * @see menu_execute_active_handler()
 * @see hook_menu()
 * @see hook_menu_alter()
 * @see hook_page_delivery_callback_alter()
 */
function drupal_deliver_page($page_callback_result, $default_delivery_callback = NULL) {
  if (!isset($default_delivery_callback) && ($router_item = menu_get_item())) {
    $default_delivery_callback = $router_item['delivery_callback'];
  }
  $delivery_callback = !empty($default_delivery_callback) ? $default_delivery_callback : 'drupal_deliver_html_page';
  // Give modules a chance to alter the delivery callback used, based on
  // request-time context (e.g., HTTP request headers).
  drupal_alter('page_delivery_callback', $delivery_callback);
  if (function_exists($delivery_callback)) {
    $delivery_callback($page_callback_result);
  }
  else {
    // If a delivery callback is specified, but doesn't exist as a function,
    // something is wrong, but don't print anything, since it's not known
    // what format the response needs to be in.
    watchdog('delivery callback not found', 'callback %callback not found: %q.', array('%callback' => $delivery_callback, '%q' => $_GET['q']), WATCHDOG_ERROR);
  }
}

/**
 * Packages and sends the result of a page callback to the browser as HTML.
 *
 * @param $page_callback_result
 *   The result of a page callback. Can be one of:
 *   - NULL: to indicate no content.
 *   - An integer menu status constant: to indicate an error condition.
 *   - A string of HTML content.
 *   - A renderable array of content.
 *
 * @see drupal_deliver_page()
 */
function drupal_deliver_html_page($page_callback_result) {
  // Emit the correct charset HTTP header, but not if the page callback
  // result is NULL, since that likely indicates that it printed something
  // in which case, no further headers may be sent, and not if code running
  // for this page request has already set the content type header.
  if (isset($page_callback_result) && is_null(drupal_get_http_header('Content-Type'))) {
    drupal_add_http_header('Content-Type', 'text/html; charset=utf-8');
  }

  // Send appropriate HTTP-Header for browsers and search engines.
  global $language;
  drupal_add_http_header('Content-Language', $language->language);

  // By default, do not allow the site to be rendered in an iframe on another
  // domain, but provide a variable to override this. If the code running for
  // this page request already set the X-Frame-Options header earlier, don't
  // overwrite it here.
  $frame_options = variable_get('x_frame_options', 'SAMEORIGIN');
  if ($frame_options && is_null(drupal_get_http_header('X-Frame-Options'))) {
    drupal_add_http_header('X-Frame-Options', $frame_options);
  }

  // Menu status constants are integers; page content is a string or array.
  if (is_int($page_callback_result)) {
    // @todo: Break these up into separate functions?
    switch ($page_callback_result) {
      case MENU_NOT_FOUND:
        // Print a 404 page.
        drupal_add_http_header('Status', '404 Not Found');

        watchdog('page not found', check_plain($_GET['q']), NULL, WATCHDOG_WARNING);

        // Check for and return a fast 404 page if configured.
        drupal_fast_404();

        // Keep old path for reference, and to allow forms to redirect to it.
        if (!isset($_GET['destination'])) {
          // Make sure that the current path is not interpreted as external URL.
          if (!url_is_external($_GET['q'])) {
            $_GET['destination'] = $_GET['q'];
          }
        }

        $path = drupal_get_normal_path(variable_get('site_404', ''));
        if ($path && $path != $_GET['q']) {
          // Custom 404 handler. Set the active item in case there are tabs to
          // display, or other dependencies on the path.
          menu_set_active_item($path);
          $return = menu_execute_active_handler($path, FALSE);
        }

        if (empty($return) || $return == MENU_NOT_FOUND || $return == MENU_ACCESS_DENIED) {
          // Standard 404 handler.
          drupal_set_title(t('Page not found'));
          $return = t('The requested page "@path" could not be found.', array('@path' => request_uri()));
        }

        drupal_set_page_content($return);
        $page = element_info('page');
        print drupal_render_page($page);
        break;

      case MENU_ACCESS_DENIED:
        // Print a 403 page.
        drupal_add_http_header('Status', '403 Forbidden');
        watchdog('access denied', check_plain($_GET['q']), NULL, WATCHDOG_WARNING);

        // Keep old path for reference, and to allow forms to redirect to it.
        if (!isset($_GET['destination'])) {
          // Make sure that the current path is not interpreted as external URL.
          if (!url_is_external($_GET['q'])) {
            $_GET['destination'] = $_GET['q'];
          }
        }

        $path = drupal_get_normal_path(variable_get('site_403', ''));
        if ($path && $path != $_GET['q']) {
          // Custom 403 handler. Set the active item in case there are tabs to
          // display or other dependencies on the path.
          menu_set_active_item($path);
          $return = menu_execute_active_handler($path, FALSE);
        }

        if (empty($return) || $return == MENU_NOT_FOUND || $return == MENU_ACCESS_DENIED) {
          // Standard 403 handler.
          drupal_set_title(t('Access denied'));
          $return = t('You are not authorized to access this page.');
        }

        print drupal_render_page($return);
        break;

      case MENU_SITE_OFFLINE:
        // Print a 503 page.
        drupal_maintenance_theme();
        drupal_add_http_header('Status', '503 Service unavailable');
        drupal_set_title(t('Site under maintenance'));
        print theme('maintenance_page', array('content' => filter_xss_admin(variable_get('maintenance_mode_message',
          t('@site is currently under maintenance. We should be back shortly. Thank you for your patience.', array('@site' => variable_get('site_name', 'Drupal')))))));
        break;
    }
  }
  elseif (isset($page_callback_result)) {
    // Print anything besides a menu constant, assuming it's not NULL or
    // undefined.
    print drupal_render_page($page_callback_result);
  }

  // Perform end-of-request tasks.
  drupal_page_footer();
}

/**
 * Performs end-of-request tasks.
 *
 * This function sets the page cache if appropriate, and allows modules to
 * react to the closing of the page by calling hook_exit().
 */
function drupal_page_footer() {
  global $user;

  module_invoke_all('exit');

  // Commit the user session, if needed.
  drupal_session_commit();

  if (variable_get('cache', 0) && ($cache = drupal_page_set_cache())) {
    drupal_serve_page_from_cache($cache);
  }
  else {
    ob_flush();
  }

  _registry_check_code(REGISTRY_WRITE_LOOKUP_CACHE);
  drupal_cache_system_paths();
  module_implements_write_cache();
  drupal_file_scan_write_cache();
  system_run_automated_cron();
}

/**
 * Performs end-of-request tasks.
 *
 * In some cases page requests need to end without calling drupal_page_footer().
 * In these cases, call drupal_exit() instead. There should rarely be a reason
 * to call exit instead of drupal_exit();
 *
 * @param $destination
 *   If this function is called from drupal_goto(), then this argument
 *   will be a fully-qualified URL that is the destination of the redirect.
 *   This should be passed along to hook_exit() implementations.
 */
function drupal_exit($destination = NULL) {
  if (drupal_get_bootstrap_phase() == DRUPAL_BOOTSTRAP_FULL) {
    if (!defined('MAINTENANCE_MODE') || MAINTENANCE_MODE != 'update') {
      module_invoke_all('exit', $destination);
    }
    drupal_session_commit();
  }
  exit;
}

/**
 * Forms an associative array from a linear array.
 *
 * This function walks through the provided array and constructs an associative
 * array out of it. The keys of the resulting array will be the values of the
 * input array. The values will be the same as the keys unless a function is
 * specified, in which case the output of the function is used for the values
 * instead.
 *
 * @param $array
 *   A linear array.
 * @param $function
 *   A name of a function to apply to all values before output.
 *
 * @return
 *   An associative array.
 */
function drupal_map_assoc($array, $function = NULL) {
  // array_combine() fails with empty arrays:
  // http://bugs.php.net/bug.php?id=34857.
  $array = !empty($array) ? array_combine($array, $array) : array();
  if (is_callable($function)) {
    $array = array_map($function, $array);
  }
  return $array;
}

/**
 * Attempts to set the PHP maximum execution time.
 *
 * This function is a wrapper around the PHP function set_time_limit().
 * When called, set_time_limit() restarts the timeout counter from zero.
 * In other words, if the timeout is the default 30 seconds, and 25 seconds
 * into script execution a call such as set_time_limit(20) is made, the
 * script will run for a total of 45 seconds before timing out.
 *
 * If the current time limit is not unlimited it is possible to decrease the
 * total time limit if the sum of the new time limit and the current time spent
 * running the script is inferior to the original time limit. It is inherent to
 * the way set_time_limit() works, it should rather be called with an
 * appropriate value every time you need to allocate a certain amount of time
 * to execute a task than only once at the beginning of the script.
 *
 * Before calling set_time_limit(), we check if this function is available
 * because it could be disabled by the server administrator. We also hide all
 * the errors that could occur when calling set_time_limit(), because it is
 * not possible to reliably ensure that PHP or a security extension will
 * not issue a warning/error if they prevent the use of this function.
 *
 * @param $time_limit
 *   An integer specifying the new time limit, in seconds. A value of 0
 *   indicates unlimited execution time.
 *
 * @ingroup php_wrappers
 */
function drupal_set_time_limit($time_limit) {
  if (function_exists('set_time_limit')) {
    $current = ini_get('max_execution_time');
    // Do not set time limit if it is currently unlimited.
    if ($current != 0) {
      @set_time_limit($time_limit);
    }
  }
}

/**
 * Returns the path to a system item (module, theme, etc.).
 *
 * @param $type
 *   The type of the item (i.e. theme, theme_engine, module, profile).
 * @param $name
 *   The name of the item for which the path is requested.
 *
 * @return
 *   The path to the requested item or an empty string if the item is not found.
 */
function drupal_get_path($type, $name) {
  return dirname(drupal_get_filename($type, $name));
}

/**
 * Returns the base URL path (i.e., directory) of the Drupal installation.
 *
 * base_path() adds a "/" to the beginning and end of the returned path if the
 * path is not empty. At the very least, this will return "/".
 *
 * Examples:
 * - http://example.com returns "/" because the path is empty.
 * - http://example.com/drupal/folder returns "/drupal/folder/".
 */
function base_path() {
  return $GLOBALS['base_path'];
}

/**
 * Adds a LINK tag with a distinct 'rel' attribute to the page's HEAD.
 *
 * This function can be called as long the HTML header hasn't been sent, which
 * on normal pages is up through the preprocess step of theme('html'). Adding
 * a link will overwrite a prior link with the exact same 'rel' and 'href'
 * attributes.
 *
 * @param $attributes
 *   Associative array of element attributes including 'href' and 'rel'.
 * @param $header
 *   Optional flag to determine if a HTTP 'Link:' header should be sent.
 */
function drupal_add_html_head_link($attributes, $header = FALSE) {
  $element = array(
    '#tag' => 'link',
    '#attributes' => $attributes,
  );
  $href = $attributes['href'];

  if ($header) {
    // Also add a HTTP header "Link:".
    $href = '<' . check_plain($attributes['href']) . '>;';
    unset($attributes['href']);
    $element['#attached']['drupal_add_http_header'][] = array('Link',  $href . drupal_http_header_attributes($attributes), TRUE);
  }

  drupal_add_html_head($element, 'drupal_add_html_head_link:' . $attributes['rel'] . ':' . $href);
}

/**
 * Adds a cascading stylesheet to the stylesheet queue.
 *
 * Calling drupal_static_reset('drupal_add_css') will clear all cascading
 * stylesheets added so far.
 *
 * If CSS aggregation/compression is enabled, all cascading style sheets added
 * with $options['preprocess'] set to TRUE will be merged into one aggregate
 * file and compressed by removing all extraneous white space.
 * Preprocessed inline stylesheets will not be aggregated into this single file;
 * instead, they are just compressed upon output on the page. Externally hosted
 * stylesheets are never aggregated or compressed.
 *
 * The reason for aggregating the files is outlined quite thoroughly here:
 * http://www.die.net/musings/page_load_time/ "Load fewer external objects. Due
 * to request overhead, one bigger file just loads faster than two smaller ones
 * half its size."
 *
 * $options['preprocess'] should be only set to TRUE when a file is required for
 * all typical visitors and most pages of a site. It is critical that all
 * preprocessed files are added unconditionally on every page, even if the
 * files do not happen to be needed on a page. This is normally done by calling
 * drupal_add_css() in a hook_init() implementation.
 *
 * Non-preprocessed files should only be added to the page when they are
 * actually needed.
 *
 * @param $data
 *   (optional) The stylesheet data to be added, depending on what is passed
 *   through to the $options['type'] parameter:
 *   - 'file': The path to the CSS file relative to the base_path(), or a
 *     stream wrapper URI. For example: "modules/devel/devel.css" or
 *     "public://generated_css/stylesheet_1.css". Note that Modules should
 *     always prefix the names of their CSS files with the module name; for
 *     example, system-menus.css rather than simply menus.css. Themes can
 *     override module-supplied CSS files based on their filenames, and this
 *     prefixing helps prevent confusing name collisions for theme developers.
 *     See drupal_get_css() where the overrides are performed. Also, if the
 *     direction of the current language is right-to-left (Hebrew, Arabic,
 *     etc.), the function will also look for an RTL CSS file and append it to
 *     the list. The name of this file should have an '-rtl.css' suffix. For
 *     example, a CSS file called 'mymodule-name.css' will have a
 *     'mymodule-name-rtl.css' file added to the list, if exists in the same
 *     directory. This CSS file should contain overrides for properties which
 *     should be reversed or otherwise different in a right-to-left display.
 *   - 'inline': A string of CSS that should be placed in the given scope. Note
 *     that it is better practice to use 'file' stylesheets, rather than
 *     'inline', as the CSS would then be aggregated and cached.
 *   - 'external': The absolute path to an external CSS file that is not hosted
 *     on the local server. These files will not be aggregated if CSS
 *     aggregation is enabled.
 * @param $options
 *   (optional) A string defining the 'type' of CSS that is being added in the
 *   $data parameter ('file', 'inline', or 'external'), or an array which can
 *   have any or all of the following keys:
 *   - 'type': The type of stylesheet being added. Available options are 'file',
 *     'inline' or 'external'. Defaults to 'file'.
 *   - 'basename': Force a basename for the file being added. Modules are
 *     expected to use stylesheets with unique filenames, but integration of
 *     external libraries may make this impossible. The basename of
 *     'modules/node/node.css' is 'node.css'. If the external library "node.js"
 *     ships with a 'node.css', then a different, unique basename would be
 *     'node.js.css'.
 *   - 'group': A number identifying the group in which to add the stylesheet.
 *     Available constants are:
 *     - CSS_SYSTEM: Any system-layer CSS.
 *     - CSS_DEFAULT: (default) Any module-layer CSS.
 *     - CSS_THEME: Any theme-layer CSS.
 *     The group number serves as a weight: the markup for loading a stylesheet
 *     within a lower weight group is output to the page before the markup for
 *     loading a stylesheet within a higher weight group, so CSS within higher
 *     weight groups take precendence over CSS within lower weight groups.
 *   - 'every_page': For optimal front-end performance when aggregation is
 *     enabled, this should be set to TRUE if the stylesheet is present on every
 *     page of the website for users for whom it is present at all. This
 *     defaults to FALSE. It is set to TRUE for stylesheets added via module and
 *     theme .info files. Modules that add stylesheets within hook_init()
 *     implementations, or from other code that ensures that the stylesheet is
 *     added to all website pages, should also set this flag to TRUE. All
 *     stylesheets within the same group that have the 'every_page' flag set to
 *     TRUE and do not have 'preprocess' set to FALSE are aggregated together
 *     into a single aggregate file, and that aggregate file can be reused
 *     across a user's entire site visit, leading to faster navigation between
 *     pages. However, stylesheets that are only needed on pages less frequently
 *     visited, can be added by code that only runs for those particular pages,
 *     and that code should not set the 'every_page' flag. This minimizes the
 *     size of the aggregate file that the user needs to download when first
 *     visiting the website. Stylesheets without the 'every_page' flag are
 *     aggregated into a separate aggregate file. This other aggregate file is
 *     likely to change from page to page, and each new aggregate file needs to
 *     be downloaded when first encountered, so it should be kept relatively
 *     small by ensuring that most commonly needed stylesheets are added to
 *     every page.
 *   - 'weight': The weight of the stylesheet specifies the order in which the
 *     CSS will appear relative to other stylesheets with the same group and
 *     'every_page' flag. The exact ordering of stylesheets is as follows:
 *     - First by group.
 *     - Then by the 'every_page' flag, with TRUE coming before FALSE.
 *     - Then by weight.
 *     - Then by the order in which the CSS was added. For example, all else
 *       being the same, a stylesheet added by a call to drupal_add_css() that
 *       happened later in the page request gets added to the page after one for
 *       which drupal_add_css() happened earlier in the page request.
 *   - 'media': The media type for the stylesheet, e.g., all, print, screen.
 *     Defaults to 'all'.
 *   - 'preprocess': If TRUE and CSS aggregation/compression is enabled, the
 *     styles will be aggregated and compressed. Defaults to TRUE.
 *   - 'browsers': An array containing information specifying which browsers
 *     should load the CSS item. See drupal_pre_render_conditional_comments()
 *     for details.
 *
 * @return
 *   An array of queued cascading stylesheets.
 *
 * @see drupal_get_css()
 */
function drupal_add_css($data = NULL, $options = NULL) {
  $css = &drupal_static(__FUNCTION__, array());
  $count = &drupal_static(__FUNCTION__ . '_count', 0);

  // If the $css variable has been reset with drupal_static_reset(), there is
  // no longer any CSS being tracked, so set the counter back to 0 also.
  if (count($css) === 0) {
    $count = 0;
  }

  // Construct the options, taking the defaults into consideration.
  if (isset($options)) {
    if (!is_array($options)) {
      $options = array('type' => $options);
    }
  }
  else {
    $options = array();
  }

  // Create an array of CSS files for each media type first, since each type needs to be served
  // to the browser differently.
  if (isset($data)) {
    $options += array(
      'type' => 'file',
      'group' => CSS_DEFAULT,
      'weight' => 0,
      'every_page' => FALSE,
      'media' => 'all',
      'preprocess' => TRUE,
      'data' => $data,
      'browsers' => array(),
    );
    $options['browsers'] += array(
      'IE' => TRUE,
      '!IE' => TRUE,
    );

    // Files with a query string cannot be preprocessed.
    if ($options['type'] === 'file' && $options['preprocess'] && strpos($options['data'], '?') !== FALSE) {
      $options['preprocess'] = FALSE;
    }

    // Always add a tiny value to the weight, to conserve the insertion order.
    $options['weight'] += $count / 1000;
    $count++;

    // Add the data to the CSS array depending on the type.
    switch ($options['type']) {
      case 'inline':
        // For inline stylesheets, we don't want to use the $data as the array
        // key as $data could be a very long string of CSS.
        $css[] = $options;
        break;
      default:
        // Local and external files must keep their name as the associative key
        // so the same CSS file is not be added twice.
        $css[$data] = $options;
    }
  }

  return $css;
}

/**
 * Returns a themed representation of all stylesheets to attach to the page.
 *
 * It loads the CSS in order, with 'module' first, then 'theme' afterwards.
 * This ensures proper cascading of styles so themes can easily override
 * module styles through CSS selectors.
 *
 * Themes may replace module-defined CSS files by adding a stylesheet with the
 * same filename. For example, themes/bartik/system-menus.css would replace
 * modules/system/system-menus.css. This allows themes to override complete
 * CSS files, rather than specific selectors, when necessary.
 *
 * If the original CSS file is being overridden by a theme, the theme is
 * responsible for supplying an accompanying RTL CSS file to replace the
 * module's.
 *
 * @param $css
 *   (optional) An array of CSS files. If no array is provided, the default
 *   stylesheets array is used instead.
 * @param $skip_alter
 *   (optional) If set to TRUE, this function skips calling drupal_alter() on
 *   $css, useful when the calling function passes a $css array that has already
 *   been altered.
 *
 * @return
 *   A string of XHTML CSS tags.
 *
 * @see drupal_add_css()
 */
function drupal_get_css($css = NULL, $skip_alter = FALSE) {
  if (!isset($css)) {
    $css = drupal_add_css();
  }

  // Allow modules and themes to alter the CSS items.
  if (!$skip_alter) {
    drupal_alter('css', $css);
  }

  // Sort CSS items, so that they appear in the correct order.
  uasort($css, 'drupal_sort_css_js');

  // Provide the page with information about the individual CSS files used,
  // information not otherwise available when CSS aggregation is enabled. The
  // setting is attached later in this function, but is set here, so that CSS
  // files removed below are still considered "used" and prevented from being
  // added in a later AJAX request.
  // Skip if no files were added to the page or jQuery.extend() will overwrite
  // the Drupal.settings.ajaxPageState.css object with an empty array.
  if (!empty($css)) {
    // Cast the array to an object to be on the safe side even if not empty.
    $setting['ajaxPageState']['css'] = (object) array_fill_keys(array_keys($css), 1);
  }

  // Remove the overridden CSS files. Later CSS files override former ones.
  $previous_item = array();
  foreach ($css as $key => $item) {
    if ($item['type'] == 'file') {
      // If defined, force a unique basename for this file.
      $basename = isset($item['basename']) ? $item['basename'] : drupal_basename($item['data']);
      if (isset($previous_item[$basename])) {
        // Remove the previous item that shared the same base name.
        unset($css[$previous_item[$basename]]);
      }
      $previous_item[$basename] = $key;
    }
  }

  // Render the HTML needed to load the CSS.
  $styles = array(
    '#type' => 'styles',
    '#items' => $css,
  );

  if (!empty($setting)) {
    $styles['#attached']['js'][] = array('type' => 'setting', 'data' => $setting);
  }

  return drupal_render($styles);
}

/**
 * Sorts CSS and JavaScript resources.
 *
 * Callback for uasort() within:
 * - drupal_get_css()
 * - drupal_get_js()
 *
 * This sort order helps optimize front-end performance while providing modules
 * and themes with the necessary control for ordering the CSS and JavaScript
 * appearing on a page.
 *
 * @param $a
 *   First item for comparison. The compared items should be associative arrays
 *   of member items from drupal_add_css() or drupal_add_js().
 * @param $b
 *   Second item for comparison.
 *
 * @see drupal_add_css()
 * @see drupal_add_js()
 */
function drupal_sort_css_js($a, $b) {
  // First order by group, so that, for example, all items in the CSS_SYSTEM
  // group appear before items in the CSS_DEFAULT group, which appear before
  // all items in the CSS_THEME group. Modules may create additional groups by
  // defining their own constants.
  if ($a['group'] < $b['group']) {
    return -1;
  }
  elseif ($a['group'] > $b['group']) {
    return 1;
  }
  // Within a group, order all infrequently needed, page-specific files after
  // common files needed throughout the website. Separating this way allows for
  // the aggregate file generated for all of the common files to be reused
  // across a site visit without being cut by a page using a less common file.
  elseif ($a['every_page'] && !$b['every_page']) {
    return -1;
  }
  elseif (!$a['every_page'] && $b['every_page']) {
    return 1;
  }
  // Finally, order by weight.
  elseif ($a['weight'] < $b['weight']) {
    return -1;
  }
  elseif ($a['weight'] > $b['weight']) {
    return 1;
  }
  else {
    return 0;
  }
}

/**
 * Default callback to group CSS items.
 *
 * This function arranges the CSS items that are in the #items property of the
 * styles element into groups. Arranging the CSS items into groups serves two
 * purposes. When aggregation is enabled, files within a group are aggregated
 * into a single file, significantly improving page loading performance by
 * minimizing network traffic overhead. When aggregation is disabled, grouping
 * allows multiple files to be loaded from a single STYLE tag, enabling sites
 * with many modules enabled or a complex theme being used to stay within IE's
 * 31 CSS inclusion tag limit: http://drupal.org/node/228818.
 *
 * This function puts multiple items into the same group if they are groupable
 * and if they are for the same 'media' and 'browsers'. Items of the 'file' type
 * are groupable if their 'preprocess' flag is TRUE, items of the 'inline' type
 * are always groupable, and items of the 'external' type are never groupable.
 * This function also ensures that the process of grouping items does not change
 * their relative order. This requirement may result in multiple groups for the
 * same type, media, and browsers, if needed to accommodate other items in
 * between.
 *
 * @param $css
 *   An array of CSS items, as returned by drupal_add_css(), but after
 *   alteration performed by drupal_get_css().
 *
 * @return
 *   An array of CSS groups. Each group contains the same keys (e.g., 'media',
 *   'data', etc.) as a CSS item from the $css parameter, with the value of
 *   each key applying to the group as a whole. Each group also contains an
 *   'items' key, which is the subset of items from $css that are in the group.
 *
 * @see drupal_pre_render_styles()
 * @see system_element_info()
 */
function drupal_group_css($css) {
  $groups = array();
  // If a group can contain multiple items, we track the information that must
  // be the same for each item in the group, so that when we iterate the next
  // item, we can determine if it can be put into the current group, or if a
  // new group needs to be made for it.
  $current_group_keys = NULL;
  // When creating a new group, we pre-increment $i, so by initializing it to
  // -1, the first group will have index 0.
  $i = -1;
  foreach ($css as $item) {
    // The browsers for which the CSS item needs to be loaded is part of the
    // information that determines when a new group is needed, but the order of
    // keys in the array doesn't matter, and we don't want a new group if all
    // that's different is that order.
    ksort($item['browsers']);

    // If the item can be grouped with other items, set $group_keys to an array
    // of information that must be the same for all items in its group. If the
    // item can't be grouped with other items, set $group_keys to FALSE. We
    // put items into a group that can be aggregated together: whether they will
    // be aggregated is up to the _drupal_css_aggregate() function or an
    // override of that function specified in hook_css_alter(), but regardless
    // of the details of that function, a group represents items that can be
    // aggregated. Since a group may be rendered with a single HTML tag, all
    // items in the group must share the same information that would need to be
    // part of that HTML tag.
    switch ($item['type']) {
      case 'file':
        // Group file items if their 'preprocess' flag is TRUE.
        // Help ensure maximum reuse of aggregate files by only grouping
        // together items that share the same 'group' value and 'every_page'
        // flag. See drupal_add_css() for details about that.
        $group_keys = $item['preprocess'] ? array($item['type'], $item['group'], $item['every_page'], $item['media'], $item['browsers']) : FALSE;
        break;
      case 'inline':
        // Always group inline items.
        $group_keys = array($item['type'], $item['media'], $item['browsers']);
        break;
      case 'external':
        // Do not group external items.
        $group_keys = FALSE;
        break;
    }

    // If the group keys don't match the most recent group we're working with,
    // then a new group must be made.
    if ($group_keys !== $current_group_keys) {
      $i++;
      // Initialize the new group with the same properties as the first item
      // being placed into it. The item's 'data' and 'weight' properties are
      // unique to the item and should not be carried over to the group.
      $groups[$i] = $item;
      unset($groups[$i]['data'], $groups[$i]['weight']);
      $groups[$i]['items'] = array();
      $current_group_keys = $group_keys ? $group_keys : NULL;
    }

    // Add the item to the current group.
    $groups[$i]['items'][] = $item;
  }
  return $groups;
}

/**
 * Default callback to aggregate CSS files and inline content.
 *
 * Having the browser load fewer CSS files results in much faster page loads
 * than when it loads many small files. This function aggregates files within
 * the same group into a single file unless the site-wide setting to do so is
 * disabled (commonly the case during site development). To optimize download,
 * it also compresses the aggregate files by removing comments, whitespace, and
 * other unnecessary content. Additionally, this functions aggregates inline
 * content together, regardless of the site-wide aggregation setting.
 *
 * @param $css_groups
 *   An array of CSS groups as returned by drupal_group_css(). This function
 *   modifies the group's 'data' property for each group that is aggregated.
 *
 * @see drupal_group_css()
 * @see drupal_pre_render_styles()
 * @see system_element_info()
 */
function drupal_aggregate_css(&$css_groups) {
  $preprocess_css = (variable_get('preprocess_css', FALSE) && (!defined('MAINTENANCE_MODE') || MAINTENANCE_MODE != 'update'));

  // For each group that needs aggregation, aggregate its items.
  foreach ($css_groups as $key => $group) {
    switch ($group['type']) {
      // If a file group can be aggregated into a single file, do so, and set
      // the group's data property to the file path of the aggregate file.
      case 'file':
        if ($group['preprocess'] && $preprocess_css) {
          $css_groups[$key]['data'] = drupal_build_css_cache($group['items']);
        }
        break;
      // Aggregate all inline CSS content into the group's data property.
      case 'inline':
        $css_groups[$key]['data'] = '';
        foreach ($group['items'] as $item) {
          $css_groups[$key]['data'] .= drupal_load_stylesheet_content($item['data'], $item['preprocess']);
        }
        break;
    }
  }
}

/**
 * #pre_render callback to add the elements needed for CSS tags to be rendered.
 *
 * For production websites, LINK tags are preferable to STYLE tags with @import
 * statements, because:
 * - They are the standard tag intended for linking to a resource.
 * - On Firefox 2 and perhaps other browsers, CSS files included with @import
 *   statements don't get saved when saving the complete web page for offline
 *   use: http://drupal.org/node/145218.
 * - On IE, if only LINK tags and no @import statements are used, all the CSS
 *   files are downloaded in parallel, resulting in faster page load, but if
 *   @import statements are used and span across multiple STYLE tags, all the
 *   ones from one STYLE tag must be downloaded before downloading begins for
 *   the next STYLE tag. Furthermore, IE7 does not support media declaration on
 *   the @import statement, so multiple STYLE tags must be used when different
 *   files are for different media types. Non-IE browsers always download in
 *   parallel, so this is an IE-specific performance quirk:
 *   http://www.stevesouders.com/blog/2009/04/09/dont-use-import/.
 *
 * However, IE has an annoying limit of 31 total CSS inclusion tags
 * (http://drupal.org/node/228818) and LINK tags are limited to one file per
 * tag, whereas STYLE tags can contain multiple @import statements allowing
 * multiple files to be loaded per tag. When CSS aggregation is disabled, a
 * Drupal site can easily have more than 31 CSS files that need to be loaded, so
 * using LINK tags exclusively would result in a site that would display
 * incorrectly in IE. Depending on different needs, different strategies can be
 * employed to decide when to use LINK tags and when to use STYLE tags.
 *
 * The strategy employed by this function is to use LINK tags for all aggregate
 * files and for all files that cannot be aggregated (e.g., if 'preprocess' is
 * set to FALSE or the type is 'external'), and to use STYLE tags for groups
 * of files that could be aggregated together but aren't (e.g., if the site-wide
 * aggregation setting is disabled). This results in all LINK tags when
 * aggregation is enabled, a guarantee that as many or only slightly more tags
 * are used with aggregation disabled than enabled (so that if the limit were to
 * be crossed with aggregation enabled, the site developer would also notice the
 * problem while aggregation is disabled), and an easy way for a developer to
 * view HTML source while aggregation is disabled and know what files will be
 * aggregated together when aggregation becomes enabled.
 *
 * This function evaluates the aggregation enabled/disabled condition on a group
 * by group basis by testing whether an aggregate file has been made for the
 * group rather than by testing the site-wide aggregation setting. This allows
 * this function to work correctly even if modules have implemented custom
 * logic for grouping and aggregating files.
 *
 * @param $element
 *   A render array containing:
 *   - '#items': The CSS items as returned by drupal_add_css() and altered by
 *     drupal_get_css().
 *   - '#group_callback': A function to call to group #items to enable the use
 *     of fewer tags by aggregating files and/or using multiple @import
 *     statements within a single tag.
 *   - '#aggregate_callback': A function to call to aggregate the items within
 *     the groups arranged by the #group_callback function.
 *
 * @return
 *   A render array that will render to a string of XHTML CSS tags.
 *
 * @see drupal_get_css()
 */
function drupal_pre_render_styles($elements) {
  // Group and aggregate the items.
  if (isset($elements['#group_callback'])) {
    $elements['#groups'] = $elements['#group_callback']($elements['#items']);
  }
  if (isset($elements['#aggregate_callback'])) {
    $elements['#aggregate_callback']($elements['#groups']);
  }

  // A dummy query-string is added to filenames, to gain control over
  // browser-caching. The string changes on every update or full cache
  // flush, forcing browsers to load a new copy of the files, as the
  // URL changed.
  $query_string = variable_get('css_js_query_string', '0');

  // For inline CSS to validate as XHTML, all CSS containing XHTML needs to be
  // wrapped in CDATA. To make that backwards compatible with HTML 4, we need to
  // comment out the CDATA-tag.
  $embed_prefix = "\n<!--/*--><![CDATA[/*><!--*/\n";
  $embed_suffix = "\n/*]]>*/-->\n";

  // Defaults for LINK and STYLE elements.
  $link_element_defaults = array(
    '#type' => 'html_tag',
    '#tag' => 'link',
    '#attributes' => array(
      'type' => 'text/css',
      'rel' => 'stylesheet',
    ),
  );
  $style_element_defaults = array(
    '#type' => 'html_tag',
    '#tag' => 'style',
    '#attributes' => array(
      'type' => 'text/css',
    ),
  );

  // Loop through each group.
  foreach ($elements['#groups'] as $group) {
    switch ($group['type']) {
      // For file items, there are three possibilites.
      // - The group has been aggregated: in this case, output a LINK tag for
      //   the aggregate file.
      // - The group can be aggregated but has not been (most likely because
      //   the site administrator disabled the site-wide setting): in this case,
      //   output as few STYLE tags for the group as possible, using @import
      //   statement for each file in the group. This enables us to stay within
      //   IE's limit of 31 total CSS inclusion tags.
      // - The group contains items not eligible for aggregation (their
      //   'preprocess' flag has been set to FALSE): in this case, output a LINK
      //   tag for each file.
      case 'file':
        // The group has been aggregated into a single file: output a LINK tag
        // for the aggregate file.
        if (isset($group['data'])) {
          $element = $link_element_defaults;
          $element['#attributes']['href'] = file_create_url($group['data']);
          $element['#attributes']['media'] = $group['media'];
          $element['#browsers'] = $group['browsers'];
          $elements[] = $element;
        }
        // The group can be aggregated, but hasn't been: combine multiple items
        // into as few STYLE tags as possible.
        elseif ($group['preprocess']) {
          $import = array();
          foreach ($group['items'] as $item) {
            // A theme's .info file may have an entry for a file that doesn't
            // exist as a way of overriding a module or base theme CSS file from
            // being added to the page. Normally, file_exists() calls that need
            // to run for every page request should be minimized, but this one
            // is okay, because it only runs when CSS aggregation is disabled.
            // On a server under heavy enough load that file_exists() calls need
            // to be minimized, CSS aggregation should be enabled, in which case
            // this code is not run. When aggregation is enabled,
            // drupal_load_stylesheet() checks file_exists(), but only when
            // building the aggregate file, which is then reused for many page
            // requests.
            if (file_exists($item['data'])) {
              // The dummy query string needs to be added to the URL to control
              // browser-caching. IE7 does not support a media type on the
              // @import statement, so we instead specify the media for the
              // group on the STYLE tag.
              $import[] = '@import url("' . check_plain(file_create_url($item['data']) . '?' . $query_string) . '");';
            }
          }
          // In addition to IE's limit of 31 total CSS inclusion tags, it also
          // has a limit of 31 @import statements per STYLE tag.
          while (!empty($import)) {
            $import_batch = array_slice($import, 0, 31);
            $import = array_slice($import, 31);
            $element = $style_element_defaults;
            // This simplifies the JavaScript regex, allowing each line
            // (separated by \n) to be treated as a completely different string.
            // This means that we can use ^ and $ on one line at a time, and not
            // worry about style tags since they'll never match the regex.
            $element['#value'] = "\n" . implode("\n", $import_batch) . "\n";
            $element['#attributes']['media'] = $group['media'];
            $element['#browsers'] = $group['browsers'];
            $elements[] = $element;
          }
        }
        // The group contains items ineligible for aggregation: output a LINK
        // tag for each file.
        else {
          foreach ($group['items'] as $item) {
            $element = $link_element_defaults;
            // We do not check file_exists() here, because this code runs for
            // files whose 'preprocess' is set to FALSE, and therefore, even
            // when aggregation is enabled, and we want to avoid needlessly
            // taxing a server that may be under heavy load. The file_exists()
            // performed above for files whose 'preprocess' is TRUE is done for
            // the benefit of theme .info files, but code that deals with files
            // whose 'preprocess' is FALSE is responsible for ensuring the file
            // exists.
            // The dummy query string needs to be added to the URL to control
            // browser-caching.
            $query_string_separator = (strpos($item['data'], '?') !== FALSE) ? '&' : '?';
            $element['#attributes']['href'] = file_create_url($item['data']) . $query_string_separator . $query_string;
            $element['#attributes']['media'] = $item['media'];
            $element['#browsers'] = $group['browsers'];
            $elements[] = $element;
          }
        }
        break;
      // For inline content, the 'data' property contains the CSS content. If
      // the group's 'data' property is set, then output it in a single STYLE
      // tag. Otherwise, output a separate STYLE tag for each item.
      case 'inline':
        if (isset($group['data'])) {
          $element = $style_element_defaults;
          $element['#value'] = $group['data'];
          $element['#value_prefix'] = $embed_prefix;
          $element['#value_suffix'] = $embed_suffix;
          $element['#attributes']['media'] = $group['media'];
          $element['#browsers'] = $group['browsers'];
          $elements[] = $element;
        }
        else {
          foreach ($group['items'] as $item) {
            $element = $style_element_defaults;
            $element['#value'] = $item['data'];
            $element['#value_prefix'] = $embed_prefix;
            $element['#value_suffix'] = $embed_suffix;
            $element['#attributes']['media'] = $item['media'];
            $element['#browsers'] = $group['browsers'];
            $elements[] = $element;
          }
        }
        break;
      // Output a LINK tag for each external item. The item's 'data' property
      // contains the full URL.
      case 'external':
        foreach ($group['items'] as $item) {
          $element = $link_element_defaults;
          $element['#attributes']['href'] = $item['data'];
          $element['#attributes']['media'] = $item['media'];
          $element['#browsers'] = $group['browsers'];
          $elements[] = $element;
        }
        break;
    }
  }

  return $elements;
}

/**
 * Aggregates and optimizes CSS files into a cache file in the files directory.
 *
 * The file name for the CSS cache file is generated from the hash of the
 * aggregated contents of the files in $css. This forces proxies and browsers
 * to download new CSS when the CSS changes.
 *
 * The cache file name is retrieved on a page load via a lookup variable that
 * contains an associative array. The array key is the hash of the file names
 * in $css while the value is the cache file name. The cache file is generated
 * in two cases. First, if there is no file name value for the key, which will
 * happen if a new file name has been added to $css or after the lookup
 * variable is emptied to force a rebuild of the cache. Second, the cache file
 * is generated if it is missing on disk. Old cache files are not deleted
 * immediately when the lookup variable is emptied, but are deleted after a set
 * period by drupal_delete_file_if_stale(). This ensures that files referenced
 * by a cached page will still be available.
 *
 * @param $css
 *   An array of CSS files to aggregate and compress into one file.
 *
 * @return
 *   The URI of the CSS cache file, or FALSE if the file could not be saved.
 */
function drupal_build_css_cache($css) {
  $data = '';
  $uri = '';
  $map = variable_get('drupal_css_cache_files', array());
  // Create a new array so that only the file names are used to create the hash.
  // This prevents new aggregates from being created unnecessarily.
  $css_data = array();
  foreach ($css as $css_file) {
    $css_data[] = $css_file['data'];
  }
  $key = hash('sha256', serialize($css_data));
  if (isset($map[$key])) {
    $uri = $map[$key];
  }

  if (empty($uri) || !file_exists($uri)) {
    // Build aggregate CSS file.
    foreach ($css as $stylesheet) {
      // Only 'file' stylesheets can be aggregated.
      if ($stylesheet['type'] == 'file') {
        $contents = drupal_load_stylesheet($stylesheet['data'], TRUE);

        // Build the base URL of this CSS file: start with the full URL.
        $css_base_url = file_create_url($stylesheet['data']);
        // Move to the parent.
        $css_base_url = substr($css_base_url, 0, strrpos($css_base_url, '/'));
        // Simplify to a relative URL if the stylesheet URL starts with the
        // base URL of the website.
        if (substr($css_base_url, 0, strlen($GLOBALS['base_root'])) == $GLOBALS['base_root']) {
          $css_base_url = substr($css_base_url, strlen($GLOBALS['base_root']));
        }

        _drupal_build_css_path(NULL, $css_base_url . '/');
        // Anchor all paths in the CSS with its base URL, ignoring external and absolute paths.
        $data .= preg_replace_callback('/url\(\s*[\'"]?(?![a-z]+:|\/+)([^\'")]+)[\'"]?\s*\)/i', '_drupal_build_css_path', $contents);
      }
    }

    // Per the W3C specification at http://www.w3.org/TR/REC-CSS2/cascade.html#at-import,
    // @import rules must proceed any other style, so we move those to the top.
    $regexp = '/@import[^;]+;/i';
    preg_match_all($regexp, $data, $matches);
    $data = preg_replace($regexp, '', $data);
    $data = implode('', $matches[0]) . $data;

    // Prefix filename to prevent blocking by firewalls which reject files
    // starting with "ad*".
    $filename = 'css_' . drupal_hash_base64($data) . '.css';
    // Create the css/ within the files folder.
    $csspath = 'public://css';
    $uri = $csspath . '/' . $filename;
    // Create the CSS file.
    file_prepare_directory($csspath, FILE_CREATE_DIRECTORY);
    if (!file_exists($uri) && !file_unmanaged_save_data($data, $uri, FILE_EXISTS_REPLACE)) {
      return FALSE;
    }
    // If CSS gzip compression is enabled, clean URLs are enabled (which means
    // that rewrite rules are working) and the zlib extension is available then
    // create a gzipped version of this file. This file is served conditionally
    // to browsers that accept gzip using .htaccess rules.
    if (variable_get('css_gzip_compression', TRUE) && variable_get('clean_url', 0) && extension_loaded('zlib')) {
      if (!file_exists($uri . '.gz') && !file_unmanaged_save_data(gzencode($data, 9, FORCE_GZIP), $uri . '.gz', FILE_EXISTS_REPLACE)) {
        return FALSE;
      }
    }
    // Save the updated map.
    $map[$key] = $uri;
    variable_set('drupal_css_cache_files', $map);
  }
  return $uri;
}

/**
 * Prefixes all paths within a CSS file for drupal_build_css_cache().
 */
function _drupal_build_css_path($matches, $base = NULL) {
  $_base = &drupal_static(__FUNCTION__);
  // Store base path for preg_replace_callback.
  if (isset($base)) {
    $_base = $base;
  }

  // Prefix with base and remove '../' segments where possible.
  $path = $_base . $matches[1];
  $last = '';
  while ($path != $last) {
    $last = $path;
    $path = preg_replace('`(^|/)(?!\.\./)([^/]+)/\.\./`', '$1', $path);
  }
  return 'url(' . $path . ')';
}

/**
 * Loads the stylesheet and resolves all @import commands.
 *
 * Loads a stylesheet and replaces @import commands with the contents of the
 * imported file. Use this instead of file_get_contents when processing
 * stylesheets.
 *
 * The returned contents are compressed removing white space and comments only
 * when CSS aggregation is enabled. This optimization will not apply for
 * color.module enabled themes with CSS aggregation turned off.
 *
 * @param $file
 *   Name of the stylesheet to be processed.
 * @param $optimize
 *   Defines if CSS contents should be compressed or not.
 * @param $reset_basepath
 *   Used internally to facilitate recursive resolution of @import commands.
 *
 * @return
 *   Contents of the stylesheet, including any resolved @import commands.
 */
function drupal_load_stylesheet($file, $optimize = NULL, $reset_basepath = TRUE) {
  // These statics are not cache variables, so we don't use drupal_static().
  static $_optimize, $basepath;
  if ($reset_basepath) {
    $basepath = '';
  }
  // Store the value of $optimize for preg_replace_callback with nested
  // @import loops.
  if (isset($optimize)) {
    $_optimize = $optimize;
  }

  // Stylesheets are relative one to each other. Start by adding a base path
  // prefix provided by the parent stylesheet (if necessary).
  if ($basepath && !file_uri_scheme($file)) {
    $file = $basepath . '/' . $file;
  }
  // Store the parent base path to restore it later.
  $parent_base_path = $basepath;
  // Set the current base path to process possible child imports.
  $basepath = dirname($file);

  // Load the CSS stylesheet. We suppress errors because themes may specify
  // stylesheets in their .info file that don't exist in the theme's path,
  // but are merely there to disable certain module CSS files.
  $content = '';
  if ($contents = @file_get_contents($file)) {
    // Return the processed stylesheet.
    $content = drupal_load_stylesheet_content($contents, $_optimize);
  }

  // Restore the parent base path as the file and its childen are processed.
  $basepath = $parent_base_path;
  return $content;
}

/**
 * Processes the contents of a stylesheet for aggregation.
 *
 * @param $contents
 *   The contents of the stylesheet.
 * @param $optimize
 *   (optional) Boolean whether CSS contents should be minified. Defaults to
 *   FALSE.
 *
 * @return
 *   Contents of the stylesheet including the imported stylesheets.
 */
function drupal_load_stylesheet_content($contents, $optimize = FALSE) {
  // Remove multiple charset declarations for standards compliance (and fixing Safari problems).
  $contents = preg_replace('/^@charset\s+[\'"](\S*?)\b[\'"];/i', '', $contents);

  if ($optimize) {
    // Perform some safe CSS optimizations.
    // Regexp to match comment blocks.
    $comment     = '/\*[^*]*\*+(?:[^/*][^*]*\*+)*/';
    // Regexp to match double quoted strings.
    $double_quot = '"[^"\\\\]*(?:\\\\.[^"\\\\]*)*"';
    // Regexp to match single quoted strings.
    $single_quot = "'[^'\\\\]*(?:\\\\.[^'\\\\]*)*'";
    // Strip all comment blocks, but keep double/single quoted strings.
    $contents = preg_replace(
      "<($double_quot|$single_quot)|$comment>Ss",
      "$1",
      $contents
    );
    // Remove certain whitespace.
    // There are different conditions for removing leading and trailing
    // whitespace.
    // @see http://php.net/manual/regexp.reference.subpatterns.php
    $contents = preg_replace('<
      # Strip leading and trailing whitespace.
        \s*([@{};,])\s*
      # Strip only leading whitespace from:
      # - Closing parenthesis: Retain "@media (bar) and foo".
      | \s+([\)])
      # Strip only trailing whitespace from:
      # - Opening parenthesis: Retain "@media (bar) and foo".
      # - Colon: Retain :pseudo-selectors.
      | ([\(:])\s+
    >xS',
      // Only one of the three capturing groups will match, so its reference
      // will contain the wanted value and the references for the
      // two non-matching groups will be replaced with empty strings.
      '$1$2$3',
      $contents
    );
    // End the file with a new line.
    $contents = trim($contents);
    $contents .= "\n";
  }

  // Replaces @import commands with the actual stylesheet content.
  // This happens recursively but omits external files.
  $contents = preg_replace_callback('/@import\s*(?:url\(\s*)?[\'"]?(?![a-z]+:)(?!\/\/)([^\'"\()]+)[\'"]?\s*\)?\s*;/', '_drupal_load_stylesheet', $contents);
  return $contents;
}

/**
 * Loads stylesheets recursively and returns contents with corrected paths.
 *
 * This function is used for recursive loading of stylesheets and
 * returns the stylesheet content with all url() paths corrected.
 */
function _drupal_load_stylesheet($matches) {
  $filename = $matches[1];
  // Load the imported stylesheet and replace @import commands in there as well.
  $file = drupal_load_stylesheet($filename, NULL, FALSE);

  // Determine the file's directory.
  $directory = dirname($filename);
  // If the file is in the current directory, make sure '.' doesn't appear in
  // the url() path.
  $directory = $directory == '.' ? '' : $directory .'/';

  // Alter all internal url() paths. Leave external paths alone. We don't need
  // to normalize absolute paths here (i.e. remove folder/... segments) because
  // that will be done later.
  return preg_replace('/url\(\s*([\'"]?)(?![a-z]+:|\/+)([^\'")]+)([\'"]?)\s*\)/i', 'url(\1' . $directory . '\2\3)', $file);
}

/**
 * Deletes old cached CSS files.
 */
function drupal_clear_css_cache() {
  variable_del('drupal_css_cache_files');
  file_scan_directory('public://css', '/.*/', array('callback' => 'drupal_delete_file_if_stale'));
}

/**
 * Callback to delete files modified more than a set time ago.
 */
function drupal_delete_file_if_stale($uri) {
  // Default stale file threshold is 30 days.
  if (REQUEST_TIME - filemtime($uri) > variable_get('drupal_stale_file_threshold', 2592000)) {
    file_unmanaged_delete($uri);
  }
}

/**
 * Prepares a string for use as a CSS identifier (element, class, or ID name).
 *
 * http://www.w3.org/TR/CSS21/syndata.html#characters shows the syntax for valid
 * CSS identifiers (including element names, classes, and IDs in selectors.)
 *
 * @param $identifier
 *   The identifier to clean.
 * @param $filter
 *   An array of string replacements to use on the identifier.
 *
 * @return
 *   The cleaned identifier.
 */
function drupal_clean_css_identifier($identifier, $filter = array(' ' => '-', '_' => '-', '/' => '-', '[' => '-', ']' => '')) {
  // Use the advanced drupal_static() pattern, since this is called very often.
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['allow_css_double_underscores'] = &drupal_static(__FUNCTION__ . ':allow_css_double_underscores');
  }
  $allow_css_double_underscores = &$drupal_static_fast['allow_css_double_underscores'];
  if (!isset($allow_css_double_underscores)) {
    $allow_css_double_underscores = variable_get('allow_css_double_underscores', FALSE);
  }

  // Preserve BEM-style double-underscores depending on custom setting.
  if ($allow_css_double_underscores) {
    $filter['__'] = '__';
  }

  // By default, we filter using Drupal's coding standards.
  $identifier = strtr($identifier, $filter);

  // Valid characters in a CSS identifier are:
  // - the hyphen (U+002D)
  // - a-z (U+0030 - U+0039)
  // - A-Z (U+0041 - U+005A)
  // - the underscore (U+005F)
  // - 0-9 (U+0061 - U+007A)
  // - ISO 10646 characters U+00A1 and higher
  // We strip out any character not in the above list.
  $identifier = preg_replace('/[^\x{002D}\x{0030}-\x{0039}\x{0041}-\x{005A}\x{005F}\x{0061}-\x{007A}\x{00A1}-\x{FFFF}]/u', '', $identifier);

  return $identifier;
}

/**
 * Prepares a string for use as a valid class name.
 *
 * Do not pass one string containing multiple classes as they will be
 * incorrectly concatenated with dashes, i.e. "one two" will become "one-two".
 *
 * @param $class
 *   The class name to clean.
 *
 * @return
 *   The cleaned class name.
 */
function drupal_html_class($class) {
  // The output of this function will never change, so this uses a normal
  // static instead of drupal_static().
  static $classes = array();

  if (!isset($classes[$class])) {
    $classes[$class] = drupal_clean_css_identifier(drupal_strtolower($class));
  }
  return $classes[$class];
}

/**
 * Prepares a string for use as a valid HTML ID and guarantees uniqueness.
 *
 * This function ensures that each passed HTML ID value only exists once on the
 * page. By tracking the already returned ids, this function enables forms,
 * blocks, and other content to be output multiple times on the same page,
 * without breaking (X)HTML validation.
 *
 * For already existing IDs, a counter is appended to the ID string. Therefore,
 * JavaScript and CSS code should not rely on any value that was generated by
 * this function and instead should rely on manually added CSS classes or
 * similarly reliable constructs.
 *
 * Two consecutive hyphens separate the counter from the original ID. To manage
 * uniqueness across multiple Ajax requests on the same page, Ajax requests
 * POST an array of all IDs currently present on the page, which are used to
 * prime this function's cache upon first invocation.
 *
 * To allow reverse-parsing of IDs submitted via Ajax, any multiple consecutive
 * hyphens in the originally passed $id are replaced with a single hyphen.
 *
 * @param $id
 *   The ID to clean.
 *
 * @return
 *   The cleaned ID.
 */
function drupal_html_id($id) {
  // If this is an Ajax request, then content returned by this page request will
  // be merged with content already on the base page. The HTML IDs must be
  // unique for the fully merged content. Therefore, initialize $seen_ids to
  // take into account IDs that are already in use on the base page.
  $seen_ids_init = &drupal_static(__FUNCTION__ . ':init');
  if (!isset($seen_ids_init)) {
    // Ideally, Drupal would provide an API to persist state information about
    // prior page requests in the database, and we'd be able to add this
    // function's $seen_ids static variable to that state information in order
    // to have it properly initialized for this page request. However, no such
    // page state API exists, so instead, ajax.js adds all of the in-use HTML
    // IDs to the POST data of Ajax submissions. Direct use of $_POST is
    // normally not recommended as it could open up security risks, but because
    // the raw POST data is cast to a number before being returned by this
    // function, this usage is safe.
    if (empty($_POST['ajax_html_ids'])) {
      $seen_ids_init = array();
    }
    else {
      // This function ensures uniqueness by appending a counter to the base id
      // requested by the calling function after the first occurrence of that
      // requested id. $_POST['ajax_html_ids'] contains the ids as they were
      // returned by this function, potentially with the appended counter, so
      // we parse that to reconstruct the $seen_ids array.
      if (isset($_POST['ajax_html_ids'][0]) && strpos($_POST['ajax_html_ids'][0], ',') === FALSE) {
        $ajax_html_ids = $_POST['ajax_html_ids'];
      }
      else {
        // jquery.form.js may send the server a comma-separated string as the
        // first element of an array (see http://drupal.org/node/1575060), so
        // we need to convert it to an array in that case.
        $ajax_html_ids = explode(',', $_POST['ajax_html_ids'][0]);
      }
      foreach ($ajax_html_ids as $seen_id) {
        // We rely on '--' being used solely for separating a base id from the
        // counter, which this function ensures when returning an id.
        $parts = explode('--', $seen_id, 2);
        if (!empty($parts[1]) && is_numeric($parts[1])) {
          list($seen_id, $i) = $parts;
        }
        else {
          $i = 1;
        }
        if (!isset($seen_ids_init[$seen_id]) || ($i > $seen_ids_init[$seen_id])) {
          $seen_ids_init[$seen_id] = $i;
        }
      }
    }
  }
  $seen_ids = &drupal_static(__FUNCTION__, $seen_ids_init);

  $id = strtr(drupal_strtolower($id), array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));

  // As defined in http://www.w3.org/TR/html4/types.html#type-name, HTML IDs can
  // only contain letters, digits ([0-9]), hyphens ("-"), underscores ("_"),
  // colons (":"), and periods ("."). We strip out any character not in that
  // list. Note that the CSS spec doesn't allow colons or periods in identifiers
  // (http://www.w3.org/TR/CSS21/syndata.html#characters), so we strip those two
  // characters as well.
  $id = preg_replace('/[^A-Za-z0-9\-_]/', '', $id);

  // Removing multiple consecutive hyphens.
  $id = preg_replace('/\-+/', '-', $id);
  // Ensure IDs are unique by appending a counter after the first occurrence.
  // The counter needs to be appended with a delimiter that does not exist in
  // the base ID. Requiring a unique delimiter helps ensure that we really do
  // return unique IDs and also helps us re-create the $seen_ids array during
  // Ajax requests.
  if (isset($seen_ids[$id])) {
    $id = $id . '--' . ++$seen_ids[$id];
  }
  else {
    $seen_ids[$id] = 1;
  }

  return $id;
}

/**
 * Provides a standard HTML class name that identifies a page region.
 *
 * It is recommended that template preprocess functions apply this class to any
 * page region that is output by the theme (Drupal core already handles this in
 * the standard template preprocess implementation). Standardizing the class
 * names in this way allows modules to implement certain features, such as
 * drag-and-drop or dynamic Ajax loading, in a theme-independent way.
 *
 * @param $region
 *   The name of the page region (for example, 'page_top' or 'content').
 *
 * @return
 *   An HTML class that identifies the region (for example, 'region-page-top'
 *   or 'region-content').
 *
 * @see template_preprocess_region()
 */
function drupal_region_class($region) {
  return drupal_html_class("region-$region");
}

/**
 * Adds a JavaScript file, setting, or inline code to the page.
 *
 * The behavior of this function depends on the parameters it is called with.
 * Generally, it handles the addition of JavaScript to the page, either as
 * reference to an existing file or as inline code. The following actions can be
 * performed using this function:
 * - Add a file ('file'): Adds a reference to a JavaScript file to the page.
 * - Add inline JavaScript code ('inline'): Executes a piece of JavaScript code
 *   on the current page by placing the code directly in the page (for example,
 *   to tell the user that a new message arrived, by opening a pop up, alert
 *   box, etc.). This should only be used for JavaScript that cannot be executed
 *   from a file. When adding inline code, make sure that you are not relying on
 *   $() being the jQuery function. Wrap your code in
 *   @code (function ($) {... })(jQuery); @endcode
 *   or use jQuery() instead of $().
 * - Add external JavaScript ('external'): Allows the inclusion of external
 *   JavaScript files that are not hosted on the local server. Note that these
 *   external JavaScript references do not get aggregated when preprocessing is
 *   on.
 * - Add settings ('setting'): Adds settings to Drupal's global storage of
 *   JavaScript settings. Per-page settings are required by some modules to
 *   function properly. All settings will be accessible at Drupal.settings.
 *
 * Examples:
 * @code
 *   drupal_add_js('misc/collapse.js');
 *   drupal_add_js('misc/collapse.js', 'file');
 *   drupal_add_js('jQuery(document).ready(function () { alert("Hello!"); });', 'inline');
 *   drupal_add_js('jQuery(document).ready(function () { alert("Hello!"); });',
 *     array('type' => 'inline', 'scope' => 'footer', 'weight' => 5)
 *   );
 *   drupal_add_js('http://example.com/example.js', 'external');
 *   drupal_add_js(array('myModule' => array('key' => 'value')), 'setting');
 * @endcode
 *
 * Calling drupal_static_reset('drupal_add_js') will clear all JavaScript added
 * so far.
 *
 * If JavaScript aggregation is enabled, all JavaScript files added with
 * $options['preprocess'] set to TRUE will be merged into one aggregate file.
 * Preprocessed inline JavaScript will not be aggregated into this single file.
 * Externally hosted JavaScripts are never aggregated.
 *
 * The reason for aggregating the files is outlined quite thoroughly here:
 * http://www.die.net/musings/page_load_time/ "Load fewer external objects. Due
 * to request overhead, one bigger file just loads faster than two smaller ones
 * half its size."
 *
 * $options['preprocess'] should be only set to TRUE when a file is required for
 * all typical visitors and most pages of a site. It is critical that all
 * preprocessed files are added unconditionally on every page, even if the
 * files are not needed on a page. This is normally done by calling
 * drupal_add_js() in a hook_init() implementation.
 *
 * Non-preprocessed files should only be added to the page when they are
 * actually needed.
 *
 * @param $data
 *   (optional) If given, the value depends on the $options parameter, or
 *   $options['type'] if $options is passed as an associative array:
 *   - 'file': Path to the file relative to base_path().
 *   - 'inline': The JavaScript code that should be placed in the given scope.
 *   - 'external': The absolute path to an external JavaScript file that is not
 *     hosted on the local server. These files will not be aggregated if
 *     JavaScript aggregation is enabled.
 *   - 'setting': An associative array with configuration options. The array is
 *     merged directly into Drupal.settings. All modules should wrap their
 *     actual configuration settings in another variable to prevent conflicts in
 *     the Drupal.settings namespace. Items added with a string key will replace
 *     existing settings with that key; items with numeric array keys will be
 *     added to the existing settings array.
 * @param $options
 *   (optional) A string defining the type of JavaScript that is being added in
 *   the $data parameter ('file'/'setting