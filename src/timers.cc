#include "loop.h"
#include "timers.h"

node::Timer::Timer() {
  auto uv_loop = node::Loop::getDefault()->getUVLoop();
  uv_timer_init(uv_loop, &this->_timer);
  this->_timer.data = this;
}

void node::Timer::start(std::function<void()> cb,
                       int64_t timeout, int64_t repeat) {
  this->_cb = cb;
  uv_timer_start(&this->_timer, node::Timer::_wrapper, timeout, repeat);
}

void node::Timer::stop() {
  uv_timer_stop(&this->_timer);
}

void node::Timer::again() {
  uv_timer_again(&this->_timer);
}

void node::Timer::setRepeat(int64_t repeat) {
  uv_timer_set_repeat(&this->_timer, repeat);
}

int64_t node::Timer::getRepeat() {
  return uv_timer_get_repeat(&this->_timer);
}

node::Timer* node::Timer::setTimeout(std::function<void()> cb,
                                     int64_t timeout) {
  auto timer = new node::Timer();
  timer->start([=]() {
    cb();
    delete timer;
  }, timeout, 0);
  return timer;
}

node::Timer* node::Timer::setInterval(std::function<void()> cb,
                                      int64_t interval) {
  auto timer = new node::Timer();
  timer->start(cb, interval, interval);
  return timer;
}

void node::Timer::_wrapper(uv_timer_t* handle, int status) {
  node::Timer* timer = static_cast<node::Timer*>(handle->data);
  timer->_cb();
}
