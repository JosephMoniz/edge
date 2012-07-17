#include "timer.h"

node::Timer() {
  auto node_loop = node::Loop::getDefault();
  auto uv_loop = node_loop->getUVLoop();
  uv_timer_init(uv_loop, &this->_timer);
  this->_timer.data = this;
}

int node::Timer::start(std::function<void(node::Timer*, int)> cb,
                       int64_t timeout, int64_t repeat) {
  this->_cb = cb;
  return uv_timer_start(this->_wrapper, timeout, repeat);
}

int node::Timer::stop() {
  return uv_timer_stop(&this->_timer);
}

int node::Timer::again() {
  return uv_timer_again(&this->_timer);
}

int node::Timer::setRepeat(int64_t repeat) {
  return uv_timer_set_repeat(&this->_timer, repeat);
}

int node::Timer::getRepeat() {
  return uv_timer_get_repeat(&this->_timer);
}

void node::Timer::setData(void* data) {
  this->_data = data;
}

void* node::Timer::getData() {
  return this->_data;
}

void node::Timer::_wrapper(uv_timer_t* handle, int status) {
  node::Timer* timer = handle->data;
  timer->_cb(timer, status)
}
