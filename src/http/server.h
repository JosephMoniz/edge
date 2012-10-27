#ifndef NODE_HTTP_SERVER_H_
#define NODE_HTTP_SERVER_H_ 1

#include <functional>

#include "uv.h"

#include "eventemitter.h"
#include "net.h"

namespace node {
namespace http {
class Server : public EventEmitter {
public:
  /**
   *
   */
  Server();

  /**
   *
   */
  Server(std::function<void(void*)> cb);

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
  node::net::Server _server;

  /**
   *
   */
  static void _onConnection(node::http::Server* self, void *data);
};
}
}

#endif
