#ifndef EDGE_NET_H_
#define EDGE_NET_H_ 1

#include <functional>

#include "net/server.h"
#include "net/socket.h"

namespace edge {
namespace net {

  /**
   * This is a convenience function for instantiating a new TCP server
   * and binding a 'connection' listener to it.
   *
   * @param {std::function} cb     - The callback to run received connections
   * @returns {edge::net::Server*} - The pointer to the heap allocated server
   */
  edge::net::Server* createServer(edge::net::ServerConnectionCb cb);

}
}

#endif
