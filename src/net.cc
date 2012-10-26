#include "net.h"

node::net::Server* node::net::createServer(std::function<void(void*)> cb) {
  auto server = new node::net::Server();
  server->on("connection", cb);
  return server;
}
