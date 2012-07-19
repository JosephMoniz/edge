#include "loop.h"

node::Loop::Loop() {
  this->_loop = uv_loop_new();
}

node::Loop* node::Loop::getDefault() {
  static node::Loop _instance;
  return &_instance;
}

void node::Loop::deleteDefault() {
  uv_loop_delete(node::Loop::getDefault()->_loop);
}

int node::Loop::run() {
  return uv_run(this->_loop);
}

int node::Loop::runOnce() {
  return uv_run_once(this->_loop);
}

uv_loop_t* node::Loop::getUVLoop() {
  return this->_loop;
}
