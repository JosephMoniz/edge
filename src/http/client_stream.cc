#include <iostream>
#include "client_stream.h"

node::http::ClientStream::ClientStream(node::http::Server* server,
                                       node::net::Socket* socket) {
  auto self = this;
  http_parser_init(&this->_parser, HTTP_REQUEST);
  this->_parser.data = this;
  this->_server     = server;
  this->_socket     = socket;
  this->_statusCode = 200;
  socket->on("data", [self](void* data) {
    auto buf  = (uv_buf_t*) data;
    http_parser_execute(
      &self->_parser,
      &node::http::_settings,
      buf->base,
      buf->len
    );
  });
}

void node::http::ClientStream::writeContinue() {
  // TODO
}

void node::http::ClientStream::writeHead(int statusCode) {
  // TODO
}

void node::http::ClientStream::writeHead(int statusCode, const char* reason) {
  // TODO
}

void node::http::ClientStream::setHeader(const char* name, const char* value) {
  // TODO
}

const char* node::http::ClientStream::getHeader(const char* name) {
  return "";
}

void node::http::ClientStream::removeHeader(const char* name) {
  // TODO
}

void node::http::ClientStream::write(void* data, size_t len) {
  // TODO
}

void node::http::ClientStream::write(uv_buf_t* buf) {
  // TODO
}

void node::http::ClientStream::write(const char* data) {
  // TODO
}

void node::http::ClientStream::write(std::string data) {
  // TODO
}

void node::http::ClientStream::pause() {
  // TODO
}

void node::http::ClientStream::resume() {
  // TODO
}

void node::http::ClientStream::end() {
  // TODO
}

void node::http::ClientStream::end(void* data, size_t len) {
  // TODO
}

void node::http::ClientStream::end(uv_buf_t* buf) {
  // TODO
}

void node::http::ClientStream::end(const char* data) {
  // TODO
}

void node::http::ClientStream::end(std::string data) {
  // TODO
}

int node::http::ClientStream::_onMessageBegin(http_parser* parser) {
  auto self = static_cast<node::http::ClientStream*>(parser->data);
  self->url.clear();
  self->method.clear();
  self->httpVersion.clear();
  self->headers.clear();
  self->trailers.clear();
  self->_fieldTmp.clear();
  self->_tmp.clear();
  return 0;
}

int node::http::ClientStream::_onUrl(http_parser* parser, const char* at,
                                     size_t length) {
  auto self = static_cast<node::http::ClientStream*>(parser->data);
  self->url.append(at, length);
  return 0;
}

int node::http::ClientStream::_onHeaderField(http_parser* parser,
                                             const char* at, size_t length) {
  auto self = static_cast<node::http::ClientStream*>(parser->data);
  if (self->_hasHeaderValue) {
    self->_hasHeaderValue = false;
    self->headers[self->_fieldTmp] = self->_tmp;
    self->_fieldTmp.clear();
    self->_tmp.clear();
  }
  self->_fieldTmp.append(at, length);
  return 0;
}

int node::http::ClientStream::_onHeaderValue(http_parser* parser,
                                             const char* at, size_t length) {
  auto self = static_cast<node::http::ClientStream*>(parser->data);
  self->_hasHeaderValue = true;
  self->_tmp.append(at, length);
  return 0;
}

int node::http::ClientStream::_onHeadersComplete(http_parser* parser) {
  auto self = static_cast<node::http::ClientStream*>(parser->data);
  self->headers[self->_fieldTmp] = self->_tmp;
  self->_server->emit("connection", (void*)self);
  return 0;
}

int node::http::ClientStream::_onBody(http_parser* parser, const char* at,
                                      size_t length) {
  auto self    = static_cast<node::http::ClientStream*>(parser->data);
  uv_buf_t buf = { .base = (char*)at, .len = length };
  self->emit("data", (void*)&buf);
  return 0;
}

int node::http::ClientStream::_onMessageComplete(http_parser* parser) {
  auto self    = static_cast<node::http::ClientStream*>(parser->data);
  self->emit("end", nullptr);
  return 0;
}

http_parser_settings node::http::_settings = {
  .on_message_begin    = node::http::ClientStream::_onMessageBegin,
  .on_url              = node::http::ClientStream::_onUrl,
  .on_header_field     = node::http::ClientStream::_onHeaderField,
  .on_header_value     = node::http::ClientStream::_onHeaderValue,
  .on_headers_complete = node::http::ClientStream::_onHeadersComplete,
  .on_body             = node::http::ClientStream::_onBody,
  .on_message_complete = node::http::ClientStream::_onMessageComplete
};
