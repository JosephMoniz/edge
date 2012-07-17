#ifndef NODE_TIMER_H_
#define NODE_TIMER_H_ 1

#include <functional>

#include "uv.h"

namespace node {
class Timer {
public:
  /**
   *
   */
  Timer();

  /**
   *
   */
  int start(std::function<void(node::Timer*, int)> cb,
            int64_t timeout, int64_t repeat);

  /**
   *
   */
  int stop();

  /**
   *
   */
  int again();

  /**
   *
   */
  int setRepeat(int64_t repeat);

  /**
   *
   */
  int64_t getRepeat();

  /**
   *
   */
  void setData(void* data);

  /**
   *
   */
  void* getData();

 private:
  uv_timer_t _timer;
  void* data;
  std::function<void(node::Timer*, int)> _cb;

  /**
   *
   */
  void _wrapper(uv_timer_t* handle, int status);
};
}

#endif
