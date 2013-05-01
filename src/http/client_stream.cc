#include <sstream>
#include <iomanip>

#include "string.h"

#include "client_stream.h"

edge::http::ClientStream::ClientStream(edge::http::Server* server,
                                       edge::net::SharedSocket socket) {
  http_parser_init(&this->_parser, HTTP_REQUEST);
  this->_parser.data     = this;
  this->_server          = server;
  this->_socket          = socket;
  socket->on("data", [=](uv_buf_t data) {
    http_parser_execute(
      &this->_parser,
      &edge::http::_settings,
      data.base,
      data.len
    );
  });
  socket->on("close", [=](uv_buf_t data) {
      this->emit("close", data);
  });
}

void edge::http::ClientStream::writeContinue() {
  // TODO
}

void edge::http::ClientStream::writeHead(int statusCode) {
  this->writeHead(statusCode, "OK");
}

void edge::http::ClientStream::writeHead(int statusCode, const char* reason) {
  if (this->_headersWritten) { return; }
  auto contentLength = this->_headers.find("Content-Length");
  if (contentLength == this->_headers.end()) {
    this->_headers["Transfer-Encoding"] = "chunked";
    this->_isChunkedEncoding = true;
  }
  std::stringstream ss(std::stringstream::in | std::stringstream::out);
  ss << "HTTP/1.1 " << statusCode << " " << reason << "\r\n";
  for (auto& pair : this->_headers) {
    ss << pair.first << ": " << pair.second << "\r\n";
  }
  ss << "\r\n";
  auto str = ss.str();
  uv_buf_t heading = { .base = (char*)str.c_str(), .len = str.length() };
  this->_socket->write(heading);
  this->_headersWritten = true;
}

void edge::http::ClientStream::setHeader(const char* name, const char* value) {
  this->_headers[name] = value;
}

const char* edge::http::ClientStream::getHeader(const char* name) {
  auto header = this->_headers.find(name);
  if (header == this->_headers.end()) {
    return nullptr;
  } else {
    return header->second.c_str();
  }
}

void edge::http::ClientStream::removeHeader(const char* name) {
  auto header = this->_headers.find(name);
  if (header != this->_headers.end()) {
    this->_headers.erase(header);
  }
}

void edge::http::ClientStream::write(uv_buf_t buf) {
  if (!this->_headersWritten) {
    this->writeHead(200, "OK");
  }
  std::stringstream ss(std::stringstream::in | std::stringstream::out);
  ss << std::hex << buf.len << "\r\n";
  auto str = ss.str();
  uv_buf_t chunk_size = { .base = (char*)str.c_str(), .len = str.length() };
  uv_buf_t ending     = { .base = (char*)"\r\n", .len = 2 };
  this->_socket->write(chunk_size);
  this->_socket->write(buf);
  this->_socket->write(ending);
}

void edge::http::ClientStream::write(const char* buf) {
  uv_buf_t data = { .base = (char*)buf, .len = strlen(buf) };
  this->write(data);
}

void edge::http::ClientStream::write(const std::string& buf) {
  uv_buf_t data = { .base = (char*)buf.c_str(), .len = buf.length() };
  this->write(data);
}

void edge::http::ClientStream::end() {
  if (this->_isChunkedEncoding) {
    uv_buf_t ending = { .base = (char*)"0\r\n\r\n", .len = 5 };
    this->_socket->write(ending);
    this->_socket->end();
  }
}

void edge::http::ClientStream::end(const char* buf) {
  this->write(buf);
  this->end();
}

void edge::http::ClientStream::end(const std::string& buf) {
  this->write(buf);
  this->end();
}

int edge::http::ClientStream::_onMessageBegin(http_parser* parser) {
  auto self = static_cast<edge::http::ClientStream*>(parser->data);
  self->url.clear();
  self->method.clear();
  self->httpVersion.clear();
  self->headers.clear();
  self->trailers.clear();
  self->_fieldTmp.clear();
  self->_tmp.clear();
  self->_headersWritten  = false;
  self->statusCode       = 200;
  return 0;
}

int edge::http::ClientStream::_onUrl(http_parser* parser, const char* at,
                                     size_t length) {
  auto self = static_cast<edge::http::ClientStream*>(parser->data);
  self->url.append(at, length);
  return 0;
}

int edge::http::ClientStream::_onHeaderField(http_parser* parser,
                                             const char* at, size_t length) {
  auto self = static_cast<edge::http::ClientStream*>(parser->data);
  if (self->_hasHeaderValue) {
    self->_hasHeaderValue = false;
    self->headers[self->_fieldTmp] = self->_tmp;
    self->_fieldTmp.clear();
    self->_tmp.clear();
  }
  self->_fieldTmp.append(at, length);
  return 0;
}

int edge::http::ClientStream::_onHeaderValue(http_parser* parser,
                                             const char* at, size_t length) {
  auto self = static_cast<edge::http::ClientStream*>(parser->data);
  self->_hasHeaderValue = true;
  self->_tmp.append(at, length);
  return 0;
}

int edge::http::ClientStream::_onHeadersComplete(http_parser* parser) {
  auto self = static_cast<edge::http::ClientStream*>(parser->data);
  self->headers[self->_fieldTmp] = self->_tmp;
  self->_cb();
  return 0;
}

int edge::http::ClientStream::_onBody(http_parser* parser, const char* at,
                                      size_t length) {
  auto self    = static_cast<edge::http::ClientStream*>(parser->data);
  uv_buf_t buf = { .base = (char*)at, .len = length };
  self->emit("__data", buf);
  return 0;
}

int edge::http::ClientStream::_onMessageComplete(http_parser* parser) {
  auto self = static_cast<edge::http::ClientStream*>(parser->data);
  uv_buf_t buf;
  self->emit("end", buf);
  return 0;
}

void edge::http::ClientStream::_addCb(std::function<void(void)> cb) {
  this->_cb = cb;
}

http_parser_settings edge::http::_settings = {
  .on_message_begin    = edge::http::ClientStream::_onMessageBegin,
  .on_url              = edge::http::ClientStream::_onUrl,
  .on_header_field     = edge::http::ClientStream::_onHeaderField,
  .on_header_value     = edge::http::ClientStream::_onHeaderValue,
  .on_headers_complete = edge::http::ClientStream::_onHeadersComplete,
  .on_body             = edge::http::ClientStream::_onBody,
  .on_message_complete = edge::http::ClientStream::_onMessageComplete
};
