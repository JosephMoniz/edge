#include "uv.h"

#include "readable.h"

node::stream::Readable::Readable() {
  this->_isPaused = false;
  this->on("__data", [=](void* data) {
    if (this->_isPaused) {
      auto buf = (uv_buf_t*) data;
      this->_buffer.insert(
        this->_buffer.end(),
        buf->base,
        &buf->base[buf->len]
      );
    } else {
      this->emit("data", data);
    }
  });
}


void node::stream::Readable::pause() {
  this->_isPaused = true;
}
void node::stream::Readable::resume() {
  this->_isPaused = false;
  if (this->_buffer.size()) {
    uv_buf_t buf = {
      .base = &(*(this->_buffer.begin())),
      .len = this->_buffer.size()
    };
    this->emit("data", (void*)&buf);
    this->_buffer.clear();
  }
}
