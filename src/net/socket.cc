#include <iostream>
#include <string.h>

#include "loop.h"
#include "net/socket.h"

node::net::Socket::Socket() {
  uv_tcp_init(node::Loop::getDefault()->getUVLoop(), &this->_handle);
  this->_handle.data = this;
}

node::net::Socket::~Socket() {
  //
}

void node::net::Socket::connect(int port) {
  this->connect(port, "127.0.0.1", nullptr);
}

void node::net::Socket::connect(int port, std::function<void(void)> f) {
  this->connect(port, "127.0.0.1", f);
}

void node::net::Socket::connect(int port, const char* host) {
  this->connect(port, host, nullptr);
}

void node::net::Socket::connect(int port, const char* host,
                                std::function<void(void)> f) {
  this->_addr = uv_ip4_addr(host, port);
  this->_connect.f = f;
  this->_connect.self = this;
  uv_tcp_connect(
    &this->_connect.connector,
    &this->_handle,
    this->_addr,
    node::net::Socket::_connectCb
  );
}

int node::net::Socket::getBufferSize() {
  // TODO: implement
  return 0;
}

void node::net::Socket::write(uv_buf_t* buf) {
  auto container = new node::net::SocketWriterData_t;
  uv_write(
    &container->writer,
    (uv_stream_t*)&this->_handle,
    buf,
    1,
    node::net::Socket::_writeCb
  );
}

void node::net::Socket::end() {
  uv_close((uv_handle_t*)&this->_handle, node::net::Socket::_closeCb);
}

void node::net::Socket::setTimeout(int timeout) {
  // TODO: implement
}

void node::net::Socket::setTimeout(int timeout, std::function<void(void)> f) {
  // TODO: implement
}

void node::net::Socket::setNoDelay(bool enabled) {
  uv_tcp_nodelay(&this->_handle, (int) enabled);
}

void node::net::Socket::setKeepAlive(bool enabled) {
  // TODO: implement
}

void node::net::Socket::setKeepAlive(bool enabled, int initialDelay) {
  uv_tcp_keepalive(&this->_handle, (int) enabled, initialDelay);
}

void node::net::Socket::_connectCb(uv_connect_t* req, int status) {
  auto data = (SocketConnectorData_t*) req;

  if (data->f != nullptr) {
    data->f();
  }
  data->self->_startRead();
}

void node::net::Socket::_writeCb(uv_write_t* req, int status) {
  delete req;
}

uv_buf_t node::net::Socket::_allocCb(uv_handle_t* handle,
                                     size_t suggested_size) {
  return uv_buf_init(new char[suggested_size], suggested_size);
}

void node::net::Socket::_readCb(uv_stream_t* stream, ssize_t nread,
                                uv_buf_t buf) {
  auto self = static_cast<node::net::Socket*>(stream->data);

  if (nread > 0) {
    self->emit("__data", static_cast<void*>(&buf));
  } else {
    uv_err_t error = uv_last_error(node::Loop::getDefault()->getUVLoop());
    if (error.code == UV_EOF) {
      uv_close((uv_handle_t*)stream, node::net::Socket::_closeCb);
    } else {
      self->emit("error", nullptr);
    }
  }
  delete buf.base;
}

void node::net::Socket::_closeCb(uv_handle_t* req) {
  auto self = static_cast<node::net::Socket*>(req->data);
  self->emit("end", nullptr);
}

bool node::net::Socket::_accept(uv_stream_t* handle) {
  int res;
  res = uv_accept(handle, (uv_stream_t*) &this->_handle);
  return !res;
}

void node::net::Socket::_startRead() {
  auto stream = (uv_stream_t*) &this->_handle;
  uv_read_start(
    stream,
    node::net::Socket::_allocCb,
    node::net::Socket::_readCb
  );
}
