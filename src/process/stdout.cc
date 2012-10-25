#include <string.h>

#include "loop.h"
#include "stdout.h"

node::process::StdoutClass::StdoutClass() {
  uv_tty_init(node::Loop::getDefault()->getUVLoop(), &this->_handle, 1, 0);
  this->_handle.data = this;
}

void node::process::StdoutClass::write(const char *str) {
  this->write((void*)str, strlen(str));
}

void node::process::StdoutClass::write(std::string str) {
  this->write((void*)str.c_str(), str.length());
}

void node::process::StdoutClass::write(uv_buf_t* buf) {
  this->write(buf->base, buf->len);
}

void node::process::StdoutClass::write(void *data, size_t len) {
  uv_write_t* writer  = new uv_write_t;
  uv_buf_t buf        = { .base = (char*)data, .len = len };
  uv_write(
    writer,
    (uv_stream_t*)&this->_handle,
    &buf,
    1,
    node::process::StdoutClass::_writeCb
  );
}

void node::process::StdoutClass::end() {
  uv_close((uv_handle_t*)&this->_handle, node::process::StdoutClass::_closeCb);
}

void node::process::StdoutClass::end(const char *str) {
  this->write(str);
  this->end();
}

void node::process::StdoutClass::end(std::string str) {
  this->write(str);
  this->end();
}

void node::process::StdoutClass::end(void *data, size_t len) {
  this->write(data, len);
  this->end();
}

void node::process::StdoutClass::_writeCb(uv_write_t* req, int status) {
  delete req;
}

void node::process::StdoutClass::_closeCb(uv_handle_t* req) {
  node::process::StdoutClass* self = (node::process::StdoutClass*) req->data;
  self->emit("end", nullptr);
}

node::process::StdoutClass node::process::stdout;
