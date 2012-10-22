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
  // TODO: implment
  return 0;
}

// TODO: refactor if nullptr is aceptable as a std::function
void node::net::Socket::write(void* data, size_t len) {
  this->write(data, len, nullptr);
}

void node::net::Socket::write(void* data, size_t len,
                              std::function<void(void)> f) {
  auto container = new node::net::SocketWriterData_t;
  uv_buf_t buf = { .base = (char*)data, .len = len };
  container->f = f;
  uv_write(
    &container->writer,
    (uv_stream_t*)&this->_handle,
    &buf,
    1,
    node::net::Socket::_writeCb
  );
}

// TODO: refactor if nullptr is aceptable as a std::function
void node::net::Socket::write(const char* data) {
  this->write((void*)data, strlen(data));
}

void node::net::Socket::write(const char* data, std::function<void(void)> f) {
  this->write((void*)data, strlen(data), f);
}

void node::net::Socket::write(std::string data) {
  this->write((void*)data.c_str(), data.length());
}

void node::net::Socket::write(std::string data, std::function<void(void)> f) {
  this->write((void*)data.c_str(), data.length(), f);
}

void node::net::Socket::end() {
  uv_close((uv_handle_t*)&this->_handle, node::net::Socket::_closeCb);
}

void node::net::Socket::end(void* data, size_t len) {
  auto self = this;
  this->write(data, len, [&self]() {
    self->end();
  });
}

void node::net::Socket::end(const char* data) {
  this->end((void*)data, strlen(data));
}

void node::net::Socket::end(std::string data) {
  this->end((void*)data.c_str(), data.length());
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
  SocketConnectorData_t* data = (SocketConnectorData_t*) req;
  if (data->f != nullptr) {
    data->f();
  }

  uv_stream_t* stream = (uv_stream_t*)&data->self->_handle;
  uv_read_start(
    stream,
    node::net::Socket::_allocCb,
    node::net::Socket::_readCb
  );
}

void node::net::Socket::_writeCb(uv_write_t* req, int status) {
  SocketWriterData_t* data = (SocketWriterData_t*) req;
  if (data->f != nullptr) {
    data->f();
  }
  delete req;
}

uv_buf_t node::net::Socket::_allocCb(uv_handle_t* handle,
                                     size_t suggested_size) {
  return uv_buf_init(new char[suggested_size], suggested_size);
}

void node::net::Socket::_readCb(uv_stream_t* stream, ssize_t nread,
                                uv_buf_t buf) {
  node::net::Socket* self = (node::net::Socket*) stream->data;
  if (nread > 0) {
    self->emit("data", (void*)&buf);
  } else {
    uv_err_t error = uv_last_error(node::Loop::getDefault()->getUVLoop());
    if (error.code == UV_EOF) {
      uv_close((uv_handle_t*)stream, node::net::Socket::_closeCb);
    } else {
      // TODO: emit error
    }
  }
  delete buf.base;
}

void node::net::Socket::_closeCb(uv_handle_t* req) {
  // TODO: implement
}
