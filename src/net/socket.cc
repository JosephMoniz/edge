#include <string.h>

#include "loop.h"
#include "net/socket.h"

edge::net::Socket::Socket() {
  uv_tcp_init(edge::Loop::getDefault()->getUVLoop(), &this->_handle);
  this->_handle.data = this;
  this->_isClosed = true;
}

edge::net::Socket::~Socket() {
  //
}

void edge::net::Socket::connect(int port) {
  this->connect(port, "127.0.0.1", nullptr);
}

void edge::net::Socket::connect(int port, std::function<void(void)> f) {
  this->connect(port, "127.0.0.1", f);
}

void edge::net::Socket::connect(int port, const char* host) {
  this->connect(port, host, nullptr);
}

void edge::net::Socket::connect(int port, const char* host,
                                std::function<void(void)> f) {
  this->_addr = uv_ip4_addr(host, port);
  this->_connect.f = f;
  this->_connect.self = this;
  uv_tcp_connect(
    &this->_connect.connector,
    &this->_handle,
    this->_addr,
    edge::net::Socket::_connectCb
  );
}

int edge::net::Socket::getBufferSize() {
  // TODO: implement
  return 0;
}

void edge::net::Socket::write(uv_buf_t buf) {
  auto container = new edge::net::SocketWriterData_t;
  uv_write(
    &container->writer,
    (uv_stream_t*)&this->_handle,
    &buf,
    1,
    edge::net::Socket::_writeCb
  );
}

void edge::net::Socket::end() {
  if (!this->_isClosed) {
    this->_isClosed = true;
    uv_close((uv_handle_t*)&this->_handle, edge::net::Socket::_closeCb);
  }
}

void edge::net::Socket::setTimeout(int timeout) {
  // TODO: implement
}

void edge::net::Socket::setTimeout(int timeout, std::function<void(void)> f) {
  // TODO: implement
}

void edge::net::Socket::setNoDelay(bool enabled) {
  uv_tcp_nodelay(&this->_handle, (int) enabled);
}

void edge::net::Socket::setKeepAlive(bool enabled) {
  // TODO: implement
}

void edge::net::Socket::setKeepAlive(bool enabled, int initialDelay) {
  uv_tcp_keepalive(&this->_handle, (int) enabled, initialDelay);
}

void edge::net::Socket::_connectCb(uv_connect_t* req, int status) {
  auto data = (SocketConnectorData_t*) req;
  auto self = data->self;

  self->_isClosed = false;

  if (data->f != nullptr) {
    data->f();
  }
  self->_startRead();
}

void edge::net::Socket::_writeCb(uv_write_t* req, int status) {
  delete req;
}

uv_buf_t edge::net::Socket::_allocCb(uv_handle_t* handle,
                                     size_t suggested_size) {
  return uv_buf_init(new char[suggested_size], suggested_size);
}

void edge::net::Socket::_readCb(uv_stream_t* stream,
                                ssize_t nread,
                                uv_buf_t buf)
{
  auto self = static_cast<edge::net::Socket*>(stream->data);

  if (nread > 0) {
    buf.len = nread;
    self->emit("__data", buf);
  } else {
    uv_err_t error = uv_last_error(edge::Loop::getDefault()->getUVLoop());
    if (error.code == UV_EOF) {
      self->end();
    } else {
      self->emit("error", buf);
    }
  }
  delete buf.base;
}

void edge::net::Socket::_closeCb(uv_handle_t* req) {
  auto self = static_cast<edge::net::Socket*>(req->data);
  uv_buf_t buf;
  self->emit("end", buf);
  self->emit("close", buf);
}

bool edge::net::Socket::_accept(uv_stream_t* handle) {
  int res;
  res = uv_accept(handle, (uv_stream_t*) &this->_handle);
  this->_isClosed = false;
  return !res;
}

void edge::net::Socket::_startRead() {
  auto stream = (uv_stream_t*) &this->_handle;
  uv_read_start(
    stream,
    edge::net::Socket::_allocCb,
    edge::net::Socket::_readCb
  );
}
