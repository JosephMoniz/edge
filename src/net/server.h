#ifndef NODE_NET_SERVER_H_
#define NODE_NET_SERVER_H_ 1

#include <map>
#include <functional>

#include "uv.h"

#include "eventemitter.h"

namespace node {
namespace net {
class Server {
public:
  /**
   *
   */
  Server();

  /**
   *
   */
  void listen(int port);

  /**
   *
   */
  void listen(int port, const char* host);

  /**
   *
   */
  void listen(int port, const char* host, int backlog);

  /**
   *
   */
  void close();

  /**
   *
   */
  void close(std::function cb);

  /**
   *
   */
  std::map<std::string, std::string> address();

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
};
}
}

#endif
