#ifndef EDGE_HTTP_H_
#define EDGE_HTTP_H_ 1

#include <functional>

#include "http/server.h"
#include "http/client_stream.h"
#include "http/request_stream.h"

namespace edge {
namespace http {

  enum Method {
    GET = 0,
    POST,
    PUT,
    DELETE,
    HEAD,
    INVALID
  };

  /**
   *
   */
  edge::http::RequestStream* get(const char* url);

  /**
   *
   */
  edge::http::RequestStream* post(const char* url);

  /**
   *
   */
  edge::http::RequestStream* put(const char* url);

  /**
   *
   */
  edge::http::RequestStream* del(const char* url);

  /**
   *
   */
  edge::http::RequestStream* head(const char* url);

}
}


#endif
