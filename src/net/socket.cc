#include "net/socket.h"

node::net::Socket::Socket() {
  //
}

node::net::Socket::~Socket() {
  //
}

void node::net::Socket::connect(int port) {
  //
}

void node::net::Socket::connect(int port, const char* host) {
  //
}

int node::net::Socket::getBufferSize() {
  //
}

void node::net::Socket::write(void* data, size_t len) {
  //
}

void node::net::Socket::write(void* data, size_t len,
                              std::function<void(void)> f) {
  //
}

void node::net::Socket::write(const char* data) {
  //
}

void node::net::Socket::write(const char* data, std::function<void(void)> f) {
  //
}

void node::net::Socket::write(std::string data) {
  //
}

void node::net::Socket::write(std::string data, std::funciton<void(void)>) {
  //
}

void node::net::Socket::end() {
  //
}

void node::net::Socket::end(void* data, size_t len) {
  //
}

void node::net::Socket::end(const char* data) {
  //
}

void node::net::Socket::end(std::string data) {
  //
}

void node::net::Socket::destroy() {
  //
}

void node::net::Socket::resume() {
  //
}

void node::net::Socket::setTimeout(int timeout) {
  //
}

void node::net::Socket::setTimeout(int timeout, std::function<void()void> f) {
  //
}

void node::net::Socket::setNoDelay(bool enabled) {
  //
}

void node::net::Socket::setKeepAlive(bool enabled, int initialDelay) {
  //
}
