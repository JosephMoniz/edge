#ifndef NODE_PROCESS_STDOUT_H_
#define NODE_PROCESS_STDOUT_H_ 1

#include <functional>

#include "uv.h"

#include "eventemitter.h"

namespace node {
namespace process {
class StdoutClass : public EventEmitter {
public:

  StdoutClass();

  void write(const char *str);

  void write(std::string str);

  void write(uv_buf_t* buf);

  void write(void *data, size_t len);

  void end();

  void end(const char *str);

  void end(std::string str);

  void end(void *data, size_t len);

private:

  uv_tty_t _handle;

  static void _writeCb(uv_write_t* req, int status);

  static void _closeCb(uv_handle_t* req);

};

extern StdoutClass stdout;

}
}

#endif
