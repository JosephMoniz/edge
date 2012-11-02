#include "server.h"
#include "client_stream.h"

edge::http::Server::Server() {
  this->_cb = nullptr;
  this->_server.on("connection", [=](void* data) {
    edge::http::Server::_onSocketConnection(this, data);
  });
  this->on("connection", edge::http::Server::_onConnection);
}

edge::http::Server::Server(std::function<void(edge::http::ClientStream*)> cb) {
  this->_cb = cb;
  this->_server.on("connection", [=](void* data) {
    edge::http::Server::_onSocketConnection(this, data);
  });
  this->on("connection", edge::http::Server::_onConnection);
}

bool edge::http::Server::listen(int port) {
  return this->listen(port, "0.0.0.0", 512, nullptr);
}

bool edge::http::Server::listen(int port, std::function<void(void*)> cb) {
  return this->listen(port, "0.0.0.0", 512, cb);
}

bool edge::http::Server::listen(int port, const char* host) {
  return this->listen(port, host, 512, nullptr);
}

bool edge::http::Server::listen(int port, const char* host,
                                std::function<void(void*)> cb) {
  return this->listen(port, host, 512, cb);
}

bool edge::http::Server::listen(int port, const char* host, int backlog) {
  return this->listen(port, host, backlog, nullptr);
}

bool edge::http::Server::listen(int port, const char* host, int backlog,
                                std::function<void(void*)> cb) {
  return this->_server.listen(port, host, backlog, cb);
}

void edge::http::Server::close() {
  this->_server.close();
}

void edge::http::Server::close(std::function<void()> cb) {
  this->_server.close(cb);
}


void edge::http::Server::_onSocketConnection(edge::http::Server* self,
                                             void *data) {
  auto socket = static_cast<edge::net::Socket*>(data);
  new edge::http::ClientStream(self, socket);
}

void edge::http::Server::_onConnection(void *data) {
  auto stream = (edge::http::ClientStream*) data;
  auto self   = (edge::http::Server*) stream->_server;

  if (self->_cb != nullptr) {
    self->_cb(stream);
  }
}
