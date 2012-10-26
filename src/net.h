#ifndef NODE_NET_H_
#define NODE_NET_H_ 1

#include <functional>

#include "net/server.h"
#include "net/socket.h"

namespace node {
namespace net {

  /**
   * This is a convenience function for instantiating a new TCP server
   * and binding a 'connection' listener to it.
   *
   * @param {std::function} cb     - The callback to run received connections
   * @returns {node::net::Server*} - The pointer to the heap allocated server
   */
  node::net::Server* createServer(std::function<void(void*)> cb);

}
}

#endif
