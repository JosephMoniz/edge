#include "net.h"

edge::net::Server* edge::net::createServer(edge::net::ServerConnectionCb cb) {
  auto server = new edge::net::Server(cb);
  return server;
}
