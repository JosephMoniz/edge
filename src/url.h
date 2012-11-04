#ifndef EDGE_URL_H_
#define EDGE_URL_H_ 1

#include <string>
#include <string.h>

namespace edge {
class Url {
public:

  /**
   * This string contains the entire URL that was passed in
   */
  std::string href;

  /**
   * This string contains the detected protocol in the url, typically
   * this will be http, https, etc
   */
  std::string protocol;

  /**
   * This string contains the host of the passed in url as well as the
   * port if one was specified.
   */
  std::string host;

  /**
   * This string contains the authorization portion of the url if one
   * was detected
   */
  std::string auth;

  /**
   * This string contains the port number specified in the url if on
   * was detected
   */
  std::string port;

  /**
   * This string contains the hostname of the url
   */
  std::string hostname;

  /**
   * This string contains the hash portion of the supplied url
   */
  std::string hash;

  /**
   * This string contains the query portion of the supplied url
   */
  std::string query;

  /**
   * This string contains the path of the url with the query and hash
   * excluded
   */
  std::string pathname;

  /**
   * This string contains the path with the query string
   */
  std::string path;

  /**
   *
   */
  Url(const char* url, size_t len);

  /**
   *
   */
  Url(const char* url) : Url(url, strlen(url)) {};

  /**
   *
   */
  Url(std::string url) : Url(url.c_str(), url.length()) {};

};
}

#endif
