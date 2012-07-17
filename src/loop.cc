#include "loop.h"
#include "uv.h"

node::Loop() {
  this->_loop = uv_loop_new();
}

node::Loop* node::Loop::getDefault() {
  if (this->_instance == nullptr) {
    this->_instance = new node::Loop();
  }
  return this->_instance;
}

void node::Loop::deleteDefault() {
  uv_loop_delete(this->_loop);
  delete node::Loop::getDefault();
}

int node::Loop::run() {
  return uv_run(this->_loop);
}

int node::loop::runOnce() {
  return uv_run_once(this->_loop);
}
