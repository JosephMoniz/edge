#ifndef NODE_TIMER_H_
#define NODE_TIMER_H_ 1

#include <functional>

#include "uv.h"

namespace node {
class Timer {
public:
  /**
   * This is a basic constructor, responsible for initializing the
   * internal timer state
   */
  Timer();

  /**
   * This function starts the timer and will run the supplied callback
   * on the supplied timeout time and will repeat it on the supplied
   * repeat time. Times are supplied in miliseconds
   *
   * @param {std::function} cb - The callback to run on timer finish
   * @param {int64_t} timeout  - The time in the future to run the callback
   * @param {int64_t} repeat   - The interval to run the callback again
   * @returns {void}
   */
  void start(std::function<void()> cb, int64_t timeout, int64_t repeat);

  /**
   * This function stops the timer from running and issuing callbacks
   *
   * @returns {void}
   */
  void stop();

  /**
   * This function runs the timer one more time with the previously
   * defined timeout, interval and callback
   *
   * @returns {void}
   */
  void again();

  /**
   * This function sets the repeat interval of the timer
   *
   * @param {int64_t} repeat - The repeat interval in miliseconds
   * @returns {void}
   */
  void setRepeat(int64_t repeat);

  /**
   * This function gets the current repeat interval of the timer
   *
   * @returns {int64_t} - The current repeat interval in miliseconds
   */
  int64_t getRepeat();

  /**
   *
   */
  static node::Timer* setTimeout(std::function<void()> cb, int64_t timeout);

  /**
   *
   */
  static node::Timer* setInterval(std::function<void()> cb, int64_t interval);

 private:

  /**
   * This is the interanl timer reference
   */
  uv_timer_t _timer;

  /**
   * This is the internal reference for the timer callback
   */
  std::function<void()> _cb;

  /**
   * This is the callback that gets ran everytime the timer is
   * triggered
   *
   * @param {uv_timer_t*} handle - This is the timer reference
   * @param {int} status         - The status code of the timer
   * @returns {void}
   */
  static void _wrapper(uv_timer_t* handle, int status);
};
}

#endif
