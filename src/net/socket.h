#ifndef NODE_SOCKET_SERVER_H_
#define NODE_SOCKET_SERVER_H_ 1

#include <functional>

#include "uv.h"

#include "eventemitter.h"

namespace node {
namespace net {
class Socket {
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
  int getBufferSize();

  /**
   *
   */
  void write(void* data, size_t len);

  /**
   *
   */
  void write(void* data, size_t len, std::funciton<void(void)> f);

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
  void pause();

  /**
   *
   */
  void resume();

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

};
}
}

#endif
