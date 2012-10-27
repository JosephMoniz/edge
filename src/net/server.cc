#include "loop.h"
#include "server.h"
#include "socket.h"

node::net::Server::Server() {
  uv_tcp_init(node::Loop::getDefault()->getUVLoop(), &this->_handle);
  this->_handle.data = this;
  this->_cb = nullptr;
}

node::net::Server::Server(ServerConnectionCb cb) {
  uv_tcp_init(node::Loop::getDefault()->getUVLoop(), &this->_handle);
  this->_handle.data = this;
  this->_cb = cb;
}

bool node::net::Server::listen(int port) {
  return this->listen(port, "0.0.0.0", 512, nullptr);
}

bool node::net::Server::listen(int port, std::function<void(void*)> cb) {
  return this->listen(port, "0.0.0.0", 512, cb);
}

bool node::net::Server::listen(int port, const char* host) {
  return this->listen(port, host, 512, nullptr);
}

bool node::net::Server::listen(int port, const char* host,
                               std::function<void(void*)> cb) {
  return this->listen(port, host, 512, cb);
}

bool node::net::Server::listen(int port, const char* host, int backlog) {
  return this->listen(port, host, 512, nullptr);
}

bool node::net::Server::listen(int port, const char* host, int backlog,
                               std::function<void(void*)> cb) {
  auto addr = uv_ip4_addr(host, port);
  int res;

  res = uv_tcp_bind(&this->_handle, addr);
  if (res != 0) {
    return false;
  }

  res = uv_listen(
    (uv_stream_t*)&this->_handle,
    backlog,
    node::net::Server::_onConnection
  );
  if (res != 0) {
    return false;
  }

  if (cb != nullptr) {
    this->on("listening", cb);
  }

  this->emit("listening", (void*)this);

  return true;
}

void node::net::Server::close() {
  // TODO
}

void node::net::Server::close(std::function<void(void)> cb) {
  // TODO
}

void node::net::Server::setMaxConnections(int max) {
  // TODO
}

int node::net::Server::getMaxConnections() {
  return 0;
}

int node::net::Server::getConcurrentConnections() {
  return 0;
}

void node::net::Server::_onConnection(uv_stream_t* handle, int status) {
  auto self = static_cast<node::net::Server*>(handle->data);

  if (status != 0) {
    self->emit("error", nullptr);
    return;
  }

  auto socket = new node::net::Socket();
  auto result = socket->_accept(handle);
  if (!result) {
    self->emit("error", nullptr);
    return;
  }

  socket->_startRead();
  if (self->_cb != nullptr) {
    self->_cb(socket);
  }
  self->emit("connection", (void*)socket);
}
