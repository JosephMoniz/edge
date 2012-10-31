#ifndef NODE_PROCESS_STDOUT_H_
#define NODE_PROCESS_STDOUT_H_ 1

#include <functional>

#include "uv.h"

#include "eventemitter.h"
#include "stream/writable.h"

namespace node {
namespace process {
class StdoutClass : public EventEmitter, public node::stream::Writable {
public:

  /**
   * Import the overloaded write methods from node::stream::Writable
   */
  using node::stream::Writable::write;

  /**
   * Import the overloaded end methods from node::stream::Writable
   */
  using node::stream::Writable::end;

  /**
   * This is a basic constructor responsible for setting up the intitial
   * state of the stdout stream
   */
  StdoutClass();

  /**
   * This function takes a uv_buf_t* and writes it to the underlying stream
   *
   * @param {uv_buf_t*} buf - The buffer to write to the stream
   * @returns {void}
   */
  void write(uv_buf_t* buf);

  /**
   * This function ends the stream and emits an `end` event when complete
   *
   * @returns {void}
   */
  void end();


private:

  /**
   * Thi is a handle to stdout
   */
  uv_tty_t _handle;

  /**
   * This callback gets ran on write completion
   *
   * @param {uv_write_t*} req - This is the reference to stdout
   * @param {int} status      - This is the current stream status
   * @returns {void}
   */
  static void _writeCb(uv_write_t* req, int status);

  /**
   * This callback gets ran when the stream is closed and will emit an
   * `end` event when done.
   *
   * @param {uv_handle_t*} req - This is the reference to stdout
   * @returns {void}
   */
  static void _closeCb(uv_handle_t* req);

};

extern StdoutClass stdout;

}
}

#endif
