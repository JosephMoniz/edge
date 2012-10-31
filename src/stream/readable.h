#ifndef NODE_STREAM_PIPE_H_
#define NODE_STREAM_PIPE_H_ 1

#include <vector>

#include "eventemitter.h"

namespace node {
namespace stream {
class Readable : public node::EventEmitter {
public:

  /**
   * This constructor sets up a listener on the `__data` event which will
   * proxy data to a `data` event if the stream is unpaused otherwise it
   * will buffer the data until the stream is unpaused
   */
  Readable();

  /**
   * This function pauses the underlying stream so that received data will
   * be buffered until the stream is unpaused by calling `resume()`
   *
   * @returns {void}
   */
  void pause();

  /**
   * This function resumes a paused stream and emits all the buffered data
   * as a `uv_buf_t` in a `data` event and clears the buffer when complete.
   * If no data is buffered then no `data` event will be fired
   *
   * @returns {void}
   */
  void resume();

  /**
   * This function takes a pointer to a writable stream and pipes all the data
   * receiveved by the underlying TCP socket directly to the passed in writable
   * stream
   *
   * EXAMPLE:
   *  auto loop   = node::Loop::getDefault();
   *  auto socket = node::net::Socket();
   *  socket.connect(8080, [&]() {
   *    socket.pipe(&node::process::stdout);
   *  });
   *  loop->run();
   *
   * @param {WritableStream*} dest - The writable stream to pipe to
   * @returns {WritableStream*}    - The destination stream passed in
   */
  template <class WritableStream>
  WritableStream* pipe(WritableStream* dest) {
    this->on("data", [dest](void *data) {
      dest->write((uv_buf_t*) data);
    });
    this->on("end", [dest](void *data) {
      dest->end();
    });
    return dest;
  };

  /**
   * This function takes a reference to a writable stream and pipes all the
   * data received by the underlying TCP socket directly to the passed in
   * writable stream.
   *
   * EXAMPLE:
   *  auto loop   = node::Loop::getDefault();
   *  auto socket = node::net::Socket();
   *  socket.connect(8080, [&]() {
   *    socket.pipe(node::process::stdout);
   *  });
   *  loop->run();
   *
   * @param {WritableStream&} dest - The writable stream to pipe to
   * @returns {WritableStream&}    - The destination stream passed in
   */
  template <class WritableStream>
  WritableStream& pipe(WritableStream& dest) {
    this->pipe(&dest);
    return dest;
  };

private:

  /**
   * This is the vector we buffer data in when the stream is
   * in a paused state.
   */
  std::vector<char> _buffer;

  /**
   * This is the flag we use to indicate if were in a paused state or not
   */
  bool _isPaused;

};
}
}

#endif
