#ifndef NODE_SOCKET_SERVER_H_
#define NODE_SOCKET_SERVER_H_ 1

#include <functional>

#include "uv.h"

#include "eventemitter.h"

namespace node {
namespace net {

class Socket;

typedef struct SocketWriterData_s {
  uv_write_t writer;
  std::function<void(void)> f;
} SocketWriterData_t;

typedef struct SocketConnectorData_s {
  uv_connect_t connector;
  std::function<void(void)> f;
  node::net::Socket* self;
} SocketConnectorData_t;

class Socket : public EventEmitter {
public:

  /**
   * This is a really simple constructor that just initializes
   * the internal TCP stream getting it ready for a connection
   */
  Socket();

  /**
   * Typical deconstructor responsible for some really basic
   * clean up tasks
   */
  ~Socket();

  /**
   * This establishes a client connection to the specified port
   * on the same machine
   *
   * @param {int} port - The port to connect to
   * @returns {void}
   */
  void connect(int port);

  /**
   * This establishes a client connection to the specified port
   * on the same machine and when a connection is established
   * the callback is executed
   *
   * @param {int} port      - The port to connect to
   * @param {std::function} - The callback to run on connection
   * @returns {void}
   */
  void connect(int port, std::function<void(void)> f);

  /**
   * This establishes a connection to the specified port on the
   * specified host
   *

   */
  void connect(int port, const char* host);

  /**
   * This establishes a connection to the specified port on the
   * specified host and when a connection is established the
   * callback is executed
   *
   * @param {int} port      - The port to connect to
   * @param {const char*}   - The host to connect to
   * @param {std::function} - The callback to run on connection
   * @returns {void}
   */
  void connect(int port, const char* host, std::function<void(void)> f);

  /**
   *
   */
  int getBufferSize();

  /**
   * This function writes `len` bytes worth of data starting at
   * `data` to the underlying TCP stream
   *
   * @param {void*} data - The start of the data to write
   * @param {size_t} len - The ammount of data to write
   * @returns {void}
   */
  void write(void* data, size_t len);

  /**
   * This function writes a uv_buf_t to the underlying TCP stream
   *
   * @param {uv_buf_t*} buf - The uv_buf_t to write
   * @returns {void}
   */
  void write(uv_buf_t* buf);

  /**
   * This function writes a zero terminated string and writes
   * it to the underlying TCP stream.
   *
   * @param {const char*} data - The zero terminated string to write
   * @returns {void}
   */
  void write(const char* data);

  /**
   * This function takes a std::string and writes it to the
   * underlying TCP stream.
   *
   * @param {std::string} data - The std::string to write
   * @returns {void}
   */
  void write(std::string data);

  /**
   * This function closes the underlying TCP stream and emits
   * an 'end' event on completion
   *
   * @returns {void}
   */
  void end();

  /**
   * This function writes `len` amount of bytes starting at `data`
   * to the underlying TCP stream then when the write is completed
   * it closes the TCP stream and emits an 'end' event on completion
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
   * @param {const char*} data - The zero terminated string to write
   * @returns {void}
   */
  void end(const char* data);

  /**
   * This function takes a std::string and writes it to the underlying
   * TCP stream then when the write is completed it cloces the TCP
   * stream and emits an 'end' event on completion
   *
   * @param {std::string} data - The std::string to write
   * @returns {void}
   */
  void end(std::string data);

  /**
   * This function takes a writable stream and pipes all the data
   * receiveved by the underlying TCP socket directly to the passed
   * in writable stream
   *
   * @param {WritableStream*} dest - The writable stream to pipe to
   * @returns {void}
   */
  template <class WritableStream>
  void pipe(WritableStream* dest);


  /**
   *
   */
  void setTimeout(int timeout);

  /**
   *
   */
  void setTimeout(int timeout, std::function<void(void)>);

  /**
   * This function toggles the TCP_NODELAY flag on the underyling TCP
   * stream. Boolean true enables is and boolean false disables it.
   *
   * @param {bool} enabled - enable if true disable if false
   * @returns {void}
   */
  void setNoDelay(bool enabled);

  /**
   *
   */
  void setKeepAlive(bool enabled);

  /**
   *
   */
  void setKeepAlive(bool enabled, int initialDelay);

private:
  /**
   * This is the TCP stream libuv handle
   */
  uv_tcp_t _handle;

  /**
   * This is our connection wrapper
   */
  SocketConnectorData_t _connect;

  /**
   * translated address of what were connected to
   */
  struct sockaddr_in _addr;

  /**
   * true if server false if client
   */
  bool _isServer;

  /**
   * true if connected false otherwise
   */
  bool _isConnected;

  /**
   * This is the internal callback that gets ran when a connection
   * is established. It sets up the read handlers on underlying
   * TCP stream.
   *
   * @param {uv_connect_t*} req - The connection context
   * @param {int} status        - The status code for the connection
   * @returns {void}
   */
  static void _connectCb(uv_connect_t* req, int status);

  /**
   * This is the internal callback that gets ran when a write
   * is completed. It's responsible for running any user supplied
   * callbacks that may have been passed in the write call
   *
   * @param {uv_write_t*} req - The write context
   * @param {int} status      - The status code for the write
   * @returns {void}
   */
  static void _writeCb(uv_write_t* req, int status);

  /**
   * This is the internal allocation callback that gets ran before every
   * read callback is ran. It is responsible for creating a buffer capable
   * of storing the read that will happen.
   *
   * @param {uv_handle_t*} handle   - The stream handle
   * @param {size_t} suggested_size - The suggested size to allocate
   * @returns {uv_buf_t}            - The allocated container
   */
  static uv_buf_t _allocCb(uv_handle_t* handle, size_t suggested_size);

  /**
   * This is internal read callback that is responsible for reading data
   * from the TCP stream and emitting it via 'data' events
   *
   * @param {uv_stream_t} stream - The TCP stream
   * @param {ssize_t} nread      - The number of bytes read
   * @param {uv_buf_t} buf       - The buffer containing the read data
   * @returns {void}
   */
  static void _readCb(uv_stream_t* stream, ssize_t nread, uv_buf_t buf);

  /**
   * This is the internal close callback that will get ran when the TCP
   * stream is closed and will emit an 'end' event when called
   *
   * @param {uv_handle_t} req - The stream handle
   * @returns {void}
   */
  static void _closeCb(uv_handle_t* req);
};
}
}

#endif
