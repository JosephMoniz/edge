#include "net/server.h"
#include "server.h"
#include "client_stream.h"

edge::http::Server::Server(edge::http::ServerConnectionCb cb) :
  _server([=](edge::net::SharedSocket socket) {
    SharedClientStream stream = std::make_shared<edge::http::ClientStream>(
      this,
      socket
    );
    stream->_addCb([=]() { this->emit("__data", stream); });
    stream->once("close", [stream](uv_buf_t data) { });
  }) {
  if (cb != nullptr) {
    this->on("data", cb);
  }
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
