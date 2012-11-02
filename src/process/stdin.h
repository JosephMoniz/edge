#ifndef EDGE_PROCESS_STDIN_H_
#define EDGE_PROCESS_STDIN_H_ 1

#include <functional>

#include "uv.h"

#include "stream/readable.h"

namespace edge {
namespace process {
class StdinClass : public edge::stream::Readable {
public:

  /**
   * Basic constructor, responsible for setting up some intial
   * state so we read from stdin and puase the stream by default
   */
  StdinClass();

private:

  /**
   * This is the internal handle to the current tty
   */
  uv_tty_t _handle;

  /**
   * This callback gets ran before every read callback and is responsible
   * for allocating the correct read size
   *
   * @param {uv_handle_t*} handle   - The internal tty handle
   * @param {size_t} suggested_size - The suggested size to allocate
   * @returns {uv_buf_t}            - The allocated buffer and it's size
   */
  static uv_buf_t _allocCb(uv_handle_t* handle, size_t suggested_size);

  /**
   * This callback is responsible for post processing the read data of
   * the stdin stream. In the event that the stream is unpaused this will
   * emit a `data` event otherwise it will buffer the data
   *
   * @param {uv_stream_t*} stream - The stream data was read from
   * @param {ssize_t} nread       - The amount of data read in bytes
   * @param {uv_buf_t} buf        - The buffer containing the read data
   * @returns {void}
   */
  static void _readCb(uv_stream_t* stream, ssize_t nread, uv_buf_t buf);

  /**
   * This callback gets ran on close and will emit an `end` event
   *
   * @param {uv_handle_t*} req - This is the stream thats being closed
   * @returns {void}
   */
  static void _closeCb(uv_handle_t* req);

};

extern StdinClass stdin;

}
}

#endif
