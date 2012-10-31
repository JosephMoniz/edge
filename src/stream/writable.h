#ifndef NODE_STREAM_WRITABLE_H_
#define NODE_STREAM_WRITABLE_H_ 1

#include <string>

#include "uv.h"

namespace node {
namespace stream {
class Writable {
public:

  /**
   * This function writes a uv_buf_t to the underlying TCP stream
   *
   * EXAMPLE:
   *  auto loop    = node::Loop::getDefault();
   *  auto socket  = node::net::Socket();
   *  uv_buf_t buf = { .base = "hi", .len = 2 };
   *  socket.connect(8080, [&]() {
   *    socket.write(&buf);
   *  });
   *  loop->run();
   *
   * @param {uv_buf_t*} buf - The uv_buf_t to write
   * @returns {void}
   */
  virtual void write(uv_buf_t* buf) = 0;

  /**
   * This function writes `len` bytes worth of data starting at
   * `data` to the underlying TCP stream
   *
   * EXAMPLE:
   *  auto loop    = node::Loop::getDefault();
   *  auto socket  = node::net::Socket();
   *  char* buffer = "hi";
   *  socket.connect(8080, [&]() {
   *    socket.write((void*)buffer, 2);
   *  });
   *  loop->run();
   *
   * @param {void*} data - The start of the data to write
   * @param {size_t} len - The ammount of data to write
   * @returns {void}
   */
  void write(void* data, size_t len);

  /**
   * This function writes a zero terminated string and writes
   * it to the underlying TCP stream.
   *
   * EXAMPLE:
   *  auto loop       = node::Loop::getDefault();
   *  auto socket     = node::net::Socket();
   *  const char* buf = "hi";
   *  socket.connect(8080, [&]() {
   *    socket.write(buf);
   *  });
   *  loop->run();
   *
   * @param {const char*} data - The zero terminated string to write
   * @returns {void}
   */
  void write(const char* data);

  /**
   * This function takes a std::string and writes it to the
   * underlying TCP stream.
   *
   * EXAMPLE:
   *  auto loop   = node::Loop::getDefault();
   *  auto socket = node::net::Socket();
   *  auto str    = std::string("hi");
   *  socket.connect(8080, [&]() {
   *    socket.write(str);
   *  });
   *  loop->run();
   *
   * @param {std::string} data - The std::string to write
   * @returns {void}
   */
  void write(std::string data);

  /**
   * This function closes the underlying TCP stream and emits
   * an 'end' event on completion
   *
   * EXAMPLE:
   *  auto loop   = node::Loop::getDefault();
   *  auto socket = node::net::Socket();
   *  socket.connect(8080, [&]() {
   *    socket.end();
   *  });
   *  loop->run();
   *
   * @returns {void}
   */
  virtual void end()  = 0;

  /**
   * This function takes a pointer to a uv_buf_t and writes it
   * to the underlying stream and then ends the stream
   *
   * EXAMPLE:
   *  auto loop    = node::Loop::getDefault();
   *  auto socket  = node::net::Socket();
   *  uv_buf_t buf = { .base = "hi", .len = 2 };
   *  socket.connect(8080, [&]() {
   *    socket.end(buf);
   *  });
   *  loop->run();
   *
   * @param {uv_buf_t*} buf - The uv_buf_t to write
   * @returns {void}
   */
  void end(uv_buf_t* buf);

  /**
   * This function writes `len` amount of bytes starting at `data`
   * to the underlying TCP stream then when the write is completed
   * it closes the TCP stream and emits an 'end' event on completion
   *
   * EXAMPLE:
   *  auto loop   = node::Loop::getDefault();
   *  auto socket = node::net::Socket();
   *  char* buf   = "hi";
   *  socket.connect(8080, [&]() {
   *    socket.end((void*) hi, 2);
   *  });
   *  loop->run();
   *
   * @param {void*} data - The start of the data to write
   * @param {size_t} len - The amount of bytes to write
   * @returns {void}
   */
  void end(void* data, size_t len);

  /**
   * This function takes a zero terminated string and writes it to the
   * underlying TCP stream then when the write is completed it closes
   * the TCP stream and emits an 'end' event on completion
   *
   * EXAMPLE:
   *  auto loop       = node::Loop::getDefault();
   *  auto socket     = node::net::Socket();
   *  const char* buf = "hi";
   *  socket.connect(8080, [&]() {
   *    socket.end(buf);
   *  });
   *  loop->run();
   *
   * @param {const char*} data - The zero terminated string to write
   * @returns {void}
   */
  void end(const char* data);

  /**
   * This function takes a std::string and writes it to the underlying
   * TCP stream then when the write is completed it cloces the TCP
   * stream and emits an 'end' event on completion
   *
   * EXAMPLE:
   *  auto loop   = node::Loop::getDefault();
   *  auto socket = node::net::Socket();
   *  auto str    = std::string("hi");
   *  socket.connect(8080, [&]() {
   *    socket.end(str);
   *  });
   *  loop->run();
   *
   * @param {std::string} data - The std::string to write
   * @returns {void}
   */
  void end(std::string data);


};
}
}

#endif
