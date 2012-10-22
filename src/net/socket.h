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
   *
   */
  Socket();

  /**
   *
   */
  ~Socket();

  /**
   *
   */
  void connect(int port);

  /**
   *
   */
  void connect(int port, const char* host);

  /**
   *
   */
  void connect(int port, const char* host, std::function<void(void)> f);

  /**
   *
   */
  int getBufferSize();

  /**
   *
   */
  void write(void* data, size_t len);

  /**
   *
   */
  void write(void* data, size_t len, std::function<void(void)> f);

  /**
   *
   */
  void write(const char* data);

  /**
   *
   */
  void write(const char* data, std::function<void(void)> f);

  /**
   *
   */
  void write(std::string data);

  /**
   *
   */
  void write(std::string data, std::function<void(void)> f);

  /**
   *
   */
  void end();

  /**
   *
   */
  void end(void* data, size_t len);

  /**
   *
   */
  void end(const char* data);

  /**
   *
   */
  void end(std::string data);

  /**
   *
   */
  void destroy();

  /**
   *
   */
  void setTimeout(int timeout);

  /**
   *
   */
  void setTimeout(int timeout, std::function<void(void)>);

  /**
   *
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

  /**
   *
   */
  std::map<std::string, std::string> address();

private:
  /**
   *
   */
  uv_tcp_t _handle;
  /**
   *
   */
  SocketConnectorData_t _connect;
  /**
   *
   */
  struct sockaddr_in _addr;
  /**
   *
   */
  bool _isServer;
  /**
   *
   */
  bool _isConnected;

  /**
   *
   */
  static void _connectCb(uv_connect_t* req, int status);

  /**
   *
   */
  static void _writeCb(uv_write_t* req, int status);

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
}
}

#endif
