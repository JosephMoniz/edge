#include "loop.h"
#include "stdin.h"

node::process::StdinClass::StdinClass() {
  uv_tty_init(node::Loop::getDefault()->getUVLoop(), &this->_handle, 0, 1);
  this->_handle.data = this;
  uv_read_start(
    (uv_stream_t*)&this->_handle,
    node::process::StdinClass::_allocCb,
    node::process::StdinClass::_readCb
  );
}

uv_buf_t node::process::StdinClass::_allocCb(uv_handle_t* handle,
                                             size_t suggested_size) {
  return uv_buf_init(new char[suggested_size], suggested_size);
}

void node::process::StdinClass::_readCb(uv_stream_t* stream, ssize_t nread,
                                        uv_buf_t buf) {
  node::process::StdinClass* self = (node::process::StdinClass*) stream->data;
  if (nread > 0) {
    self->emit("data", (void*)&buf);
  } else {
    uv_err_t error = uv_last_error(node::Loop::getDefault()->getUVLoop());
    if (error.code == UV_EOF) {
      uv_close((uv_handle_t*)stream, node::process::StdinClass::_closeCb);
    } else {
      // TODO: emit error
    }
  }
  delete buf.base;
}

void node::process::StdinClass::_closeCb(uv_handle_t* req) {
  node::process::StdinClass* self = (node::process::StdinClass*) req->data;
  self->emit("end", nullptr);
}


node::process::StdinClass node::process::stdin;
