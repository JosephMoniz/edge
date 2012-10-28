#include "server.h"
#include "client_stream.h"

node::http::Server::Server() {
  this->_cb = nullptr;
  this->_server.on("connection", [=](void* data) {
    node::http::Server::_onSocketConnection(this, data);
  });
  this->on("connection", node::http::Server::_onConnection);
}

node::http::Server::Server(std::function<void(node::http::ClientStream*)> cb) {
  this->_cb = cb;
  this->_server.on("connection", [=](void* data) {
    node::http::Server::_onSocketConnection(this, data);
  });
  this->on("connection", node::http::Server::_onConnection);
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

void node::http::Server::close(std::function<void()> cb) {
  this->_server.close(cb);
}


void node::http::Server::_onSocketConnection(node::http::Server* self,
                                             void *data) {
  auto socket = static_cast<node::net::Socket*>(data);
  new node::http::ClientStream(self, socket);
}

void node::http::Server::_onConnection(void *data) {
  auto stream = (node::http::ClientStream*) data;
  auto self   = (node::http::Server*) stream->_server;

  if (self->_cb != nullptr) {
    self->_cb(stream);
  }
}
