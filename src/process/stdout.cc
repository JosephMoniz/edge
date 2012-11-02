#include <string.h>

#include "loop.h"
#include "stdout.h"

edge::process::StdoutClass::StdoutClass() {
  uv_tty_init(edge::Loop::getDefault()->getUVLoop(), &this->_handle, 1, 0);
  this->_handle.data = this;
}

void edge::process::StdoutClass::write(uv_buf_t* buf) {
  uv_write_t* writer = new uv_write_t;
  uv_write(
    writer,
    (uv_stream_t*)&this->_handle,
    buf,
    1,
    edge::process::StdoutClass::_writeCb
  );
}

void edge::process::StdoutClass::end() {
  uv_close((uv_handle_t*)&this->_handle, edge::process::StdoutClass::_closeCb);
}

void edge::process::StdoutClass::_writeCb(uv_write_t* req, int status) {
  delete req;
}

void edge::process::StdoutClass::_closeCb(uv_handle_t* req) {
  edge::process::StdoutClass* self = (edge::process::StdoutClass*) req->data;
  self->emit("end", nullptr);
}

edge::process::StdoutClass edge::process::stdout;
