#ifndef NODE_PROCESS_STDIN_H_
#define NODE_PROCESS_STDIN_H_ 1

#include <functional>

#include "uv.h"

#include "stream/pipe.h"

namespace node {
namespace process {
class StdinClass : public node::stream::Pipe {
public:

  /**
   *
   */
  StdinClass();

private:

  /**
   *
   */
  uv_tty_t _handle;

  /**
   *
   */
  static uv_buf_t _allocCb(uv_handle_t* handle, size_t suggested_size);

  /**
   *
   */
  static void _readCb(uv_stream_t* stream, ssize_t nread, uv_buf_t buf);

  /**
   *
   */
  static void _closeCb(uv_handle_t* req);

};

extern StdinClass stdin;

}
}

#endif
