#ifndef EDGE_HTTP_REQUESTSTREAM_H_
#define EDGE_HTTP_REQUESTSTREAM_H_ 1

#include "uv.h"
#include "http_parser.h"

#include "stream/readable.h"

namespace edge {
namespace http {
class RequestStream : public edge::stream::Readable {
public:

  /**
   *
   */
  RequestStream(edge::http::Method method, const char* url);

private:

  /**
   *
   */
  edge::net::Socket _socket;

  /**
   *
   */
  const char* _methodToStr(edge::http::Method method);

};
}
}

#endif
