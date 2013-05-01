#ifndef EDGE_HTTP_SERVER_H_
#define EDGE_HTTP_SERVER_H_ 1

#include <functional>
#include <memory>

#include "uv.h"

#include "stream/readable.h"
#include "eventemitter.h"
#include "client_stream.h"
#include "net.h"

namespace edge {
namespace http {

class ClientStream;

typedef std::shared_ptr<edge::http::ClientStream> SharedClientStream;
typedef std::function<void(edge::http::SharedClientStream)> ServerConnectionCb;

class Server : public edge::stream::Readable<SharedClientStream> {
public:
  /**
   *
   */
  Server() : Server(nullptr) {};

  /**
   *
   */
  Server(ServerConnectionCb cb);

  /**
   *
   */
  bool listen(int port);

  /**
   *
   */
  bool listen(int port, std::function<void(void*)> cb);

  /**
   *
   */
  bool listen(int port, const char* host);

  /**
   *
   */
  bool listen(int port, const char* host, std::function<void(void*)> cb);

  /**
   *
   */
  bool listen(int port, const char* host, int backlog);

  /**
   *
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
  void close(std::function<void()> cb);

private:
  /**
   *
   */
  edge::net::Server _server;

};
}
}

#endif
