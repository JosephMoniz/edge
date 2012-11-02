#include "loop.h"
#include "stdin.h"

edge::process::StdinClass::StdinClass() {
  uv_tty_init(edge::Loop::getDefault()->getUVLoop(), &this->_handle, 0, 1);
  this->_handle.data = this;
  this->pause();
  uv_read_start(
    (uv_stream_t*)&this->_handle,
    edge::process::StdinClass::_allocCb,
    edge::process::StdinClass::_readCb
  );
}

uv_buf_t edge::process::StdinClass::_allocCb(uv_handle_t* handle,
                                             size_t suggested_size) {
  return uv_buf_init(new char[suggested_size], suggested_size);
}

void edge::process::StdinClass::_readCb(uv_stream_t* stream, ssize_t nread,
                                        uv_buf_t buf) {
  edge::process::StdinClass* self = (edge::process::StdinClass*) stream->data;
  if (nread > 0) {
    self->emit("__data", (void*)&buf);
  } else {
    uv_err_t error = uv_last_error(edge::Loop::getDefault()->getUVLoop());
    if (error.code == UV_EOF) {
      uv_close((uv_handle_t*)stream, edge::process::StdinClass::_closeCb);
    } else {
      self->emit("error", nullptr);
    }
  }
  delete buf.base;
}

void edge::process::StdinClass::_closeCb(uv_handle_t* req) {
  edge::process::StdinClass* self = (edge::process::StdinClass*) req->data;
  self->emit("end", nullptr);
}


edge::process::StdinClass edge::process::stdin;
