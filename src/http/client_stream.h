#ifndef NODE_HTTP_CLIENTSTREAM_H_
#define NODE_HTTP_CLIENTSTREAM_H_ 1

#include <functional>
#include <string>
#include <map>

#include "uv.h"

#include "eventemitter.h"
#include "net.h"

namespace node {
namespace http {
class ClientStream : public EventEmitter {
public:
  /**
   *
   */
  std::string method;

  /**
   *
   */
  std::string url;

  /**
   *
   */
  std::string httpVersion;

  /**
   *
   */
  std::map<std::string, std::string> headers;

  /**
   *
   */
  std::map<std::string, std::string> trailers;

  /**
   *
   */
  uint32_t statusCode;

  /**
   *
   */
  bool sendDate;

  /**
   *
   */
  ClientStream(node::http::Server* server, node::net::Socket* socket);

  /**
   *
   */
  void writeContinue();

  /**
   *
   */
  void writeHead(int statusCode);

  /**
   *
   */
  void writeHead(int statusCode, const char* reason);

  /**
   *
   */
  void setHeader(const char* name, const char* value);

  /**
   *
   */
  void getHeader(const char* name);

  /**
   *
   */
  void removeHeader(const char* name);

  /**
   *
   */
  void write(void* data, size_t len);

  /**
   *
   */
  void write(uv_buf_t* buf);

  /**
   *
   */
  void write(const char* data);

  /**
   *
   */
  void write(std::string data);

  /**
   *
   */
  void pause();

  /**
   *
   */
  void resume();

  /**
   *
   */
  void end();

  /**
   *
   */
  void end(void* data, size_t len);

  /**
   *
   */
  void end(const char* data);

  /**
   *
   */
  void end(std::string data);

  /**
   *
   */
  template <class WritableStream>
  WritableStream* pipe(WritableStream* dest) {
    this->on("data", [dest](void *data) {
      dest->write((uv_buf_t*) data);
    });
    this->on("end", [dest](void *data) {
      dest->end();
    });
    return dest;
  };

  /**
   *
   */
  template <class WritableStream>
  WritableStream& pipe(WritableStream& dest) {
    this->pipe(&dest);
    return dest;
  };

private:
  /**
   *
   */
  node::http::Server* _server;

  /**
   *
   */
  node::net::Socket* _socket;
};
}
}

#endif
