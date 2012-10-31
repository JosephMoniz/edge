#include "writable.h"

void node::stream::Writable::write(void* data, size_t len) {
  uv_buf_t buf = { .base = (char*)data, .len = len };
  this->write(&buf);
}

void node::stream::Writable::write(const char* data) {
  this->write((void*)data, strlen(data));
}

void node::stream::Writable::write(std::string data) {
  this->write((void*)data.c_str(), data.length());
}

void node::stream::Writable::end(uv_buf_t* buf) {
  this->write(buf);
  this->end();
}

void node::stream::Writable::end(void* data, size_t len) {
  this->write(data, len);
  this->end();
}

void node::stream::Writable::end(const char* data) {
  this->write(data);
  this->end();
}

void node::stream::Writable::end(std::string data) {
  this->write(data);
  this->end();
}
