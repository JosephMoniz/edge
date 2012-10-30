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
   *
   */
  StdoutClass();

  /**
   *
   */
  void write(uv_buf_t* buf);

  /**
   *
   */
  void end();


private:

  uv_tty_t _handle;

  static void _writeCb(uv_write_t* req, int status);

  static void _closeCb(uv_handle_t* req);

};

extern StdoutClass stdout;

}
}

#endif
