#ifndef EDGE_URL_H_
#define EDGE_URL_H_ 1

#include <string>
#include <string.h>

namespace edge {
class Url {
public:

  /**
   *
   */
  std::string href;

  /**
   *
   */
  std::string protocol;

  /**
   *
   */
  std::string host;

  /**
   *
   */
  std::string auth;

  /**
   *
   */
  std::string port;

  /**
   *
   */
  std::string hostname;

  /**
   *
   */
  std::string hash;

  /**
   *
   */
  std::string query;

  /**
   *
   */
  std::string pathname;

  /**
   *
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
