#include "loop.h"
#include "server.h"
#include "socket.h"

edge::net::Server::Server() {
  uv_tcp_init(edge::Loop::getDefault()->getUVLoop(), &this->_handle);
  this->_handle.data = this;
}

edge::net::Server::Server(ServerConnectionCb cb) {
  uv_tcp_init(edge::Loop::getDefault()->getUVLoop(), &this->_handle);
  this->_handle.data = this;
  this->on("data", cb);
}

bool edge::net::Server::listen(int port) {
  return this->listen(port, "0.0.0.0", 512, nullptr);
}

bool edge::net::Server::listen(int port, std::function<void(void*)> cb) {
  return this->listen(port, "0.0.0.0", 512, cb);
}

bool edge::net::Server::listen(int port, const char* host) {
  return this->listen(port, host, 512, nullptr);
}

bool edge::net::Server::listen(int port, const char* host,
                               std::function<void(void*)> cb) {
  return this->listen(port, host, 512, cb);
}

bool edge::net::Server::listen(int port, const char* host, int backlog) {
  return this->listen(port, host, 512, nullptr);
}

bool edge::net::Server::listen(int port, const char* host, int backlog,
                               std::function<void(edge::net::Server*)> cb) {
  auto addr = uv_ip4_addr(host, port);
  int res;

  res = uv_tcp_bind(&this->_handle, addr);
  if (res != 0) {
    return false;
  }

  res = uv_listen(
    (uv_stream_t*)&this->_handle,
    backlog,
    edge::net::Server::_onConnection
  );
  if (res != 0) {
    return false;
  }

  if (cb != nullptr) {
    cb(this);
  }

  return true;
}

void edge::net::Server::close() {
  // TODO
}

void edge::net::Server::close(std::function<void(void)> cb) {
  // TODO
}

void edge::net::Server::setMaxConnections(int max) {
  // TODO
}

int edge::net::Server::getMaxConnections() {
  return 0;
}

int edge::net::Server::getConcurrentConnections() {
  return 0;
}

void edge::net::Server::_onConnection(uv_stream_t* handle, int status) {
  auto self = static_cast<edge::net::Server*>(handle->data);

  if (status != 0) {
    self->emit("error", nullptr);
    return;
  }

  auto socket = std::make_shared<edge::net::Socket>();
  auto result = socket->_accept(handle);
  if (!result) {
    self->emit("error", nullptr);
    return;
  }

  socket->_startRead();
  self->emit("__data", socket);
  socket->once("close", [socket](uv_buf_t data) {});
}
