#ifndef NODE_NET_SERVER_H_
#define NODE_NET_SERVER_H_ 1

#include <map>
#include <functional>

#include "uv.h"

#include "eventemitter.h"

namespace node {
namespace net {
class Server : public EventEmitter {
public:
  /**
   *
   */
  Server();

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
  void close(std::function<void(void)> cb);

  /**
   *
   */
  void setMaxConnections(int max);

  /**
   *
   */
  int getMaxConnections();

  /**
   *
   */
  int getConcurrentConnections();

private:

  /**
   *
   */
  uv_tcp_t _handle;

  /**
   *
   */
  static void _onConnection(uv_stream_t* handle, int status);
};
}
}

#endif
