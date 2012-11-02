#ifndef EDGE_HTTP_SERVER_H_
#define EDGE_HTTP_SERVER_H_ 1

#include <functional>

#include "uv.h"

#include "eventemitter.h"
#include "client_stream.h"
#include "net.h"

namespace edge {
namespace http {

class ClientStream;

class Server : public EventEmitter {
public:
  /**
   *
   */
  Server();

  /**
   *
   */
  Server(std::function<void(edge::http::ClientStream*)> cb);

  /**
   *
   */
  bool listen(int port);

  /**
   *
   */
  bool listen(int port, std::function<void(void*)> cb);

  /**
   *
   */
  bool listen(int port, const char* host);

  /**
   *
   */
  bool listen(int port, const char* host, std::function<void(void*)> cb);

  /**
   *
   */
  bool listen(int port, const char* host, int backlog);

  /**
   *
   */
  bool listen(int port, const char* host, int backlog,
              std::function<void(void*)> cb);

  /**
   *
   */
  void close();

  /**
   *
   */
  void close(std::function<void()> cb);

private:
  /**
   *
   */
  edge::net::Server _server;

  /**
   *
   */
  std::function<void(edge::http::ClientStream*)> _cb;

  /**
   *
   */
  static void _onSocketConnection(edge::http::Server* self, void *data);

  /**
   *
   */
  static void _onConnection(void *data);
};
}
}

#endif
