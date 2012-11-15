#ifndef EDGE_NET_SERVER_H_
#define EDGE_NET_SERVER_H_ 1

#include <map>
#include <functional>

#include "uv.h"

#include "_types.h"
#include "eventemitter.h"
#include "socket.h"

namespace edge {
namespace net {

class Socket;

typedef std::function<void(edge::net::SharedSocket)> ServerConnectionCb;

class Server : public EventEmitter {
public:
  /**
   * This is a fairly basic constructor, it is responsible for setting
   * up the internal state for the listening socket.
   */
  Server();

  /**
   * This is a fairly basic constructor, it is responsible for setting
   * up the internal state for the listening socket.
   */
  Server(ServerConnectionCb cb);

  /**
   * This funciton starts the underlying socket listening on the supplied
   * port and once listening it emits the 'listening' event
   *
   * EXAMPLE:
   *  auto server = edge::net::createServer([](void *data) {
   *    auto socket = static_cast<edge::net::Socket*>(data);
   *    socket->end("payload");
   *  });
   *  server.listen(8080);
   *
   * @param {int} port - The port to listen on
   * @returns {bool}   - True on success false on failure
   */
  bool listen(int port);

  /**
   * This function starts the underlying socket listening on the supplied
   * port and once listening it emits the 'listening' event and calls the
   * supplied callback
   *
   * EXAMPLE:
   *  auto server = edge::net::createServer([](void *data) {
   *    auto socket = static_cast<edge::net::Socket*>(data);
   *    socket->end("payload");
   *  });
   *  server.listen(8080, [](void *) {
   *    edge::process::stdout.write("listening on port 8080\n");
   *  });
   *
   * @param {int} port      - The port ot listen on
   * @param {std::function} - The callback to run on listen
   * @returns {bool}        - True on success false on failure
   */
  bool listen(int port, std::function<void(void*)> cb);

  /**
   * This function starts the underlying socket listening on the supplied
   * port and host and once listening it emits the 'listening' event
   *
   * EXAMPLE:
   *  auto server = edge::net::createServer([](void *data) {
   *    auto socket = static_cast<edge::net::Socket*>(data);
   *    socket->end("payload");
   *  });
   *  server.listen(8080, "0.0.0.0");
   *
   * @param {int} port         - The port to listen on
   * @param {const char*} host - The host to listen on
   * @returns {bool}           - True on success false on failure
   */
  bool listen(int port, const char* host);

  /**
   * This function starts the underlying socket listening on the supplied
   * port and host and once listening it emits the 'listening' event and
   * calls the supplied callback
   *
   * EXAMPLE:
   *  auto server = edge::net::createServer([](void *data) {
   *    auto socket = static_cast<edge::net::Socket*>(data);
   *    socket->end("payload");
   *  });
   *  server.listen(8080, "0.0.0.0", [](void *) {
   *    edge::process::stdout.write("listening on  0.0.0.0:8080\n");
   *  });
   *
   * @param {int} port         - The port to listen on
   * @param {const char*} host - The host to listen o
   * @param {std::function}    - The callback to run on listen
   * @returns {bool}           - True on success false on failure
   */
  bool listen(int port, const char* host, std::function<void(void*)> cb);

  /**
   * This function starts the underlying socket listening on the supplied
   * port and host and once listening it emits the 'listening' event and
   * sets the length of the connection backlog queue
   *
   * EXAMPLE:
   *  auto server = edge::net::createServer([](void *data) {
   *    auto socket = static_cast<edge::net::Socket*>(data);
   *    socket->end("payload");
   *  });
   *  server.listen(8080, "0.0.0.0", 512);
   *
   * @param {int} port         - The port to listen on
   * @param {const char*} host - The host to listen on
   * @param {int} backlog      - The length of the backlog queue
   * @returns {bool}           - True on success false on failure
   */
  bool listen(int port, const char* host, int backlog);

  /**
   * This function starts the underlying socket listening on the supplied
   * port and host, sets the length of the connection backlog queue
   * and once listening it emits the 'listening' event and calls the supplied
   * callback
   *
   * EXAMPLE:
   *  auto server = edge::net::createServer([](void *data) {
   *    auto socket = static_cast<edge::net::Socket*>(data);
   *    socket->end("payload");
   *  });
   *  server.listen(8080, "0.0.0.0", 512, [](void *) {
   *    edge::process::stdout.write("listening on  0.0.0.0:8080\n");
   *  });
   *
   * @param {int} port         - The port to listen on
   * @param {const char*} host - The host to listen on
   * @param {int} backlog      - The length of the backlog queue
   * @param {std::function}    - The callback to run on listen
   * @returns {bool}           - True on success false on failure
   */
  bool listen(int port, const char* host, int backlog,
              std::function<void(void*)> cb);

  /**
   *
   */
  void close();

  /**
   *
   */
  void close(std::function<void(void)> cb);

  /**
   *
   */
  void setMaxConnections(int max);

  /**
   *
   */
  int getMaxConnections();

  /**
   *
   */
  int getConcurrentConnections();

private:

  /**
   * This is a reference to the listening socket
   */
  uv_tcp_t _handle;

  /**
   * This callback will be ran everytime a new connection is accepted
   */
  ServerConnectionCb _cb;

  /**
   * This is the callback that gets called everytime a connection
   * is received on the listening socket
   *
   * @param {uv_stream_t*} handle - This is the listening socket
   * @param {int} status          - The status code of the connection
   */
  static void _onConnection(uv_stream_t* handle, int status);
};
}
}

#endif
