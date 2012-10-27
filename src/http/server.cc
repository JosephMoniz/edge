#include "server.h"
#include "client_stream.h"

node::http::Server::Server() {
  auto self = this;
  this->_server.on("connection", [&self](void* data) {
    node::http::Server::_onConnection(self, data);
  });
}

node::http::Server::Server(std::function<void(void*)> cb) {
  auto self = this;
  this->on("connection", cb);
  this->_server.on("connection", [&self](void* data) {
    node::http::Server::_onConnection(self, data);
  });
}

bool node::http::Server::listen(int port) {
  return this->listen(port, "0.0.0.0", 512, nullptr);
}

bool node::http::Server::listen(int port, std::function<void(void*)> cb) {
  return this->listen(port, "0.0.0.0", 512, cb);
}

bool node::http::Server::listen(int port, const char* host) {
  return this->listen(port, host, 512, nullptr);
}

bool node::http::Server::listen(int port, const char* host,
                                std::function<void(void*)> cb) {
  return this->listen(port, host, 512, cb);
}

bool node::http::Server::listen(int port, const char* host, int backlog) {
  return this->listen(port, host, backlog, nullptr);
}

bool node::http::Server::listen(int port, const char* host, int backlog,
                                std::function<void(void*)> cb) {
  return this->_server.listen(port, host, backlog, cb);
}

void node::http::Server::close() {
  this->_server.close();
}

void node::http::Server::close(std::function<void(void*)> cb) {
  this->_server.close(cb);
}


void node::http::Server::_onConnection(node::http::Server* self, void *data) {
  auto socket = static_cast<node::net::Socket*>(data);
  auto stream = new node::http::ClientStream(self, socket);
  // DO NOT EMIT CONNECTION UNTIL ALL HEADERS ARE READ AND WERE
  // MOVING ONTO BODY CONTENTS
  //self->emit("connection");
}
