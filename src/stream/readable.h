#ifndef EDGE_STREAM_READABLE_H_
#define EDGE_STREAM_READABLE_H_ 1

#include <memory>
#include <vector>
#include <functional>

#include "uv.h"

#include "eventemitter.h"

namespace edge {
namespace stream {
template <class T>
class Readable : public edge::EventEmitter<T> {
public:

  /**
   * This constructor sets up a listener on the `__data` event which will
   * proxy data to a `data` event if the stream is unpaused otherwise it
   * will buffer the data until the stream is unpaused
   */
  Readable() {
    this->_isPaused = false;
    this->on("__data", [=](T data) {
      this->emit("data", data);
    });
  }

  /**
   * This is the virtual destructor that is required for disambiguation
   * of destructioin on iherited objects
   */
  virtual ~Readable() {
    // required evil
  }

  /**
   * This function pauses the underlying stream so that received data will
   * be buffered until the stream is unpaused by calling `resume()`
   *
   * @returns {void}
   */
  void pause() {
    this->_isPaused = true;
  }

  /**
   * This function resumes a paused stream and emits all the buffered data
   * as a `uv_buf_t` in a `data` event and clears the buffer when complete.
   * If no data is buffered then no `data` event will be fired
   *
   * @returns {void}
   */
  void resume() {
    this->_isPaused = false;
    if (this->_buffer.size()) {
      auto buf = uv_buf_init(
        (char*)&(*(this->_buffer.begin())),
        this->_buffer.size()
      );
      this->emit("data", buf);
      this->_buffer.clear();
    }
  }

  /**
   * This function takes a pointer to a writable stream and pipes all the data
   * receiveved by the underlying TCP socket directly to the passed in writable
   * stream
   *
   * EXAMPLE:
   *  auto loop   = edge::Loop::getDefault();
   *  auto socket = edge::net::Socket();
   *  socket.connect(8080, [&]() {
   *    socket.pipe(&edge::process::stdout);
   *  });
   *  loop->run();
   *
   * @param {WritableStream*} dest - The writable stream to pipe to
   * @returns {WritableStream*}    - The destination stream passed in
   */
  template <class WritableStream>
  auto pipe(WritableStream* dest) -> decltype(dest) {
    this->on("data", [dest](T data) {
      dest->write(data);
    });
    this->on("end", [dest](T data) {
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
   *  auto loop   = edge::Loop::getDefault();
   *  auto socket = edge::net::Socket();
   *  socket.connect(8080, [&]() {
   *    socket.pipe(edge::process::stdout);
   *  });
   *  loop->run();
   *
   * @param {WritableStream&} dest - The writable stream to pipe to
   * @returns {WritableStream&}    - The destination stream passed in
   */
  template <class WritableStream>
  auto pipe(WritableStream& dest) -> decltype(dest) {
    this->pipe(&dest);
    return dest;
  };

  /**
   * This function takes a shared pointer to a writable stream and pipes all
   * the data received by the underlying TCP socket directly to the passed in
   * writable stream.
   *
   * EXAMPLE:
   *  auto server = edge::net::createServer([](edge::net::SharedSocket socket) {
   *   socket->pipe(socket);
   *  });
   *  server->listen(8000);
   *
   * @param {WritableStream&} dest - The writable stream to pipe to
   * @returns {WritableStream&}    - The destination stream passed in
   */
  template <class WritableStream>
  auto pipe(std::shared_ptr<WritableStream> dest) -> decltype(dest) {
    this->pipe(*dest);
    return dest;
  };

  /**
   *
   */
  Readable<T>* subscribe(std::function<void(T)> subscriber) {
    this->on("data", [=](T data) { subscriber(data); });
    return this;
  }

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
