#include "loop.h"
#include "timers.h"

edge::Timer::Timer() {
  auto uv_loop = edge::Loop::getDefault()->getUVLoop();
  uv_timer_init(uv_loop, &this->_timer);
  this->_timer.data = this;
}

void edge::Timer::start(std::function<void()> cb,
                       int64_t timeout, int64_t repeat) {
  this->_cb = cb;
  uv_timer_start(&this->_timer, edge::Timer::_wrapper, timeout, repeat);
}

void edge::Timer::stop() {
  uv_timer_stop(&this->_timer);
}

void edge::Timer::again() {
  uv_timer_again(&this->_timer);
}

void edge::Timer::setRepeat(int64_t repeat) {
  uv_timer_set_repeat(&this->_timer, repeat);
}

int64_t edge::Timer::getRepeat() {
  return uv_timer_get_repeat(&this->_timer);
}

edge::Timer* edge::Timer::setTimeout(std::function<void()> cb,
                                     int64_t timeout) {
  auto timer = new edge::Timer();
  timer->start([=]() {
    cb();
    delete timer;
  }, timeout, 0);
  return timer;
}

edge::Timer* edge::Timer::setInterval(std::function<void()> cb,
                                      int64_t interval) {
  auto timer = new edge::Timer();
  timer->start(cb, interval, interval);
  return timer;
}

void edge::Timer::_wrapper(uv_timer_t* handle, int status) {
  edge::Timer* timer = static_cast<edge::Timer*>(handle->data);
  timer->_cb();
}
