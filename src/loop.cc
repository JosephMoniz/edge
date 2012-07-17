#include "loop.h"

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

int node::Loop::runOnce() {
  return uv_run_once(this->_loop);
}

uv_loopt_t* node::Loop::getUVLoop() {
  return this->_loop;
}
