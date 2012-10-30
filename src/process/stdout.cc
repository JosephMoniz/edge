#include <string.h>

#include "loop.h"
#include "stdout.h"

node::process::StdoutClass::StdoutClass() {
  uv_tty_init(node::Loop::getDefault()->getUVLoop(), &this->_handle, 1, 0);
  this->_handle.data = this;
}

void node::process::StdoutClass::write(uv_buf_t* buf) {
  uv_write_t* writer = new uv_write_t;
  uv_write(
    writer,
    (uv_stream_t*)&this->_handle,
    buf,
    1,
    node::process::StdoutClass::_writeCb
  );
}

void node::process::StdoutClass::end() {
  uv_close((uv_handle_t*)&this->_handle, node::process::StdoutClass::_closeCb);
}

void node::process::StdoutClass::_writeCb(uv_write_t* req, int status) {
  delete req;
}

void node::process::StdoutClass::_closeCb(uv_handle_t* req) {
  node::process::StdoutClass* self = (node::process::StdoutClass*) req->data;
  self->emit("end", nullptr);
}

node::process::StdoutClass node::process::stdout;
