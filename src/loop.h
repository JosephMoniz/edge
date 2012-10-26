#ifndef NODE_LOOP_H_
#define NODE_LOOP_H_ 1

#include "uv.h"

namespace node {
class Loop {
public:
  /**
   * This function returns the default loop instance
   *
   * @returns {node::Loop*} - The default loop instance
   */
  static node::Loop* getDefault();

  /**
   * This function deletes teh default loop instance
   *
   * @returns {void}
   */
  static void deleteDefault();

  // TODO: verify return value
  /**
   * This function runs the current loop until no more active events
   * are being processed
   *
   * @returns {int} - Non zero on failure zero on success
   */
  int run();

  /**
   * This funciton runs the current loop once and returns
   *
   * @returns {int} - Non zero on failure zero on success
   */
  int runOnce();

  /**
   * This funciton returns the underlying libuv loop reference
   *
   * @returns {uv_loop_t*} - The underlying libuv loop
   */
  uv_loop_t* getUVLoop();

 private:
  /**
   * This is a reference to the underlying libuv loop
   */
  uv_loop_t* _loop = nullptr;

  /**
   * Private constructor so you can't directly instantiate a
   * loop instance
   */
  Loop();

  /**
   * private copy constructor so you can't directly copy a loop instance
   */
  Loop(node::Loop const&){};

};
}

#endif
