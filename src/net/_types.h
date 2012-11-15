#ifndef EDGE_SOCKET__TYPES_H_
#define EDGE_SOCKET__TYPES_H_ 1

#include <memory>

#include "socket.h"

namespace edge {
namespace net {
  class Socket;
  typedef std::shared_ptr<edge::net::Socket> SharedSocket;
}
}

#endif
