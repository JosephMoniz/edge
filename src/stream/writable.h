#ifndef EDGE_STREAM_WRITABLE_H_
#define EDGE_STREAM_WRITABLE_H_ 1

#include <string>

#include "uv.h"

namespace edge {
namespace stream {
template <class T>
class Writable {
public:

  /**
   *
   */
  virtual void write(T data) = 0;

  /**
   *
   */
  virtual void end() = 0;

  /**
   *
   */
  void end(T data) {
    this.write(data);
    this.end();
  }

};
}
}

#endif
