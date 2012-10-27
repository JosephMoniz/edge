#include "net.h"

node::net::Server* node::net::createServer(node::net::ServerConnectionCb cb) {
  auto server = new node::net::Server(cb);
  return server;
}
