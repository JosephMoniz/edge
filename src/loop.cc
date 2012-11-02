#include "loop.h"

edge::Loop::Loop() {
  this->_loop = uv_loop_new();
}

edge::Loop* edge::Loop::getDefault() {
  static edge::Loop _instance;
  return &_instance;
}

void edge::Loop::deleteDefault() {
  uv_loop_delete(edge::Loop::getDefault()->getUVLoop());
}

int edge::Loop::run() {
  return uv_run(this->_loop);
}

int edge::Loop::runOnce() {
  return uv_run_once(this->_loop);
}

uv_loop_t* edge::Loop::getUVLoop() {
  return this->_loop;
}
