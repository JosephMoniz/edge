/**
 * For the purposes of rapid development this file will be used as a sort
 * of ghetto unit testing
 */

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory>

#include "loop.h"
#include "timers.h"
#include "path.h"
#include "url.h"
#include "eventemitter.h"
#include "querystring.h"
#include "dns.h"
#include "net.h"
#include "http/server.h"
#include "http/client_stream.h"
#include "process/stdin.h"
#include "process/stdout.h"

#include "rx/observable.h"
#include "rx/observer.h"
#include "rx/subscription.h"
#include "rx/transformer.h"

int main(int argc, char **argv) {
  auto loop = edge::Loop::getDefault();

  edge::dns::resolve(
    "www.google.com",
    [](edge::SharedError error, edge::dns::SharedResponse response) {
      if (error != nullptr) {
        std::cout << error->getMessage() << std::endl;
        return;
      }
      for (auto ip : *response) {
        std::cout << ip << std::endl;
      }
    }
  );

  auto web = edge::http::Server();
  web.subscribe([](edge::http::SharedClientStream stream) {
    stream->setHeader("Content-Type", "text/plain");
    stream->end("Hello world!");
  });
  web.listen(5000);

  auto server = edge::net::Server();
  server.subscribe([](edge::net::SharedSocket socket) {
    socket->pipe(socket);
  });
  server.listen(8000);

  auto socket = edge::net::Socket();
  socket.connect(8000, [&]() {
    edge::process::stdin.pipe(socket).pipe(edge::process::stdout);
    edge::process::stdin.resume();
  });

  loop->run();

  /**

  /////// Testing out timers
  auto loop = edge::Loop::getDefault();

  edge::Timer timer;
  timer.start([]() {
    std::cout << "ping" << std::endl;
  }, 1000, 1000);

  loop->run();

  return 0;

  /////// Tests that don't depend on the event loop
  std::cout << "== Testing extname" << std::endl;
  std::cout << "lolwat.jpg: " << edge::Path::extname("lolwat.jpg") << std::endl;
  std::cout << "/a/wat.jpg: " << edge::Path::extname("/a/wat.jpg") << std::endl;
  std::cout << "lolwat.: " << edge::Path::extname("lolwat.") << std::endl;
  std::cout << "lolwat: " << edge::Path::extname("lolwat") << std::endl;
  std::cout << std::endl;

  std::cout << "== Testing basename" << std::endl;
  std::cout << "wat.jpg: " << edge::Path::basename("wat.jpg") << std::endl;
  std::cout << "/b/a.jpg: " << edge::Path::basename("/b/a.jpg") << std::endl;
  std::cout << "/b/wat/: " << edge::Path::basename("/b/wat/") << std::endl;
  std::cout << std::endl;

  std::cout << "== Testing basename w/ extension" << std::endl;
  std::cout << "a.jpg: " << edge::Path::basename("a.jpg", "jpg") << std::endl;
  std::cout << "/b/a.jpg: "
            << edge::Path::basename("/b/a.jpg", "jpg")
            << std::endl;
  std::cout << "/b/wat: "
            << edge::Path::basename("/b/wat", "jpg")
            << std::endl;
  std::cout << "/b/wat/: "
            << edge::Path::basename("/b/wat/", "jpg")
            << std::endl;
  std::cout << std::endl;

  std::cout << "== Testing dirname" << std::endl;
  std::cout << "wat.jpg: " << edge::Path::dirname("wat.jpg") << std::endl;
  std::cout << "/b/a.jpg: " << edge::Path::dirname("/b/a.jpg") << std::endl;
  std::cout << "/b/wat/: " << edge::Path::dirname("/b/wat/") << std::endl;
  std::cout << "/b/wat: " << edge::Path::dirname("/b/wat") << std::endl;
  std::cout << "/b/wat//: " << edge::Path::dirname("/b/wat//") << std::endl;
  std::cout << std::endl;

  std::cout << "== Testing normalize" << std::endl;
  std::cout << "wat.jpg: " << edge::Path::normalize("wat.jpg") << std::endl;
  std::cout << "/a/b/c/../d: "
            << edge::Path::normalize("/a/b/c/../d")
            << std::endl;
  std::cout << "a/b/c/../../d: "
            << edge::Path::normalize("a/b/c/../../d")
            << std::endl;
  std::cout << "/b/wat//: " << edge::Path::normalize("/b/wat//") << std::endl;
  std::cout << "/b///wat/: " << edge::Path::normalize("/b///wat/") << std::endl;
  std::cout << ": " << edge::Path::normalize("") << std::endl;
  std::cout << "/: " << edge::Path::normalize("/") << std::endl;
  std::cout << std::endl;

  std::cout << "== Testing join" << std::endl;
  std::cout << "join(\"wat\", \"lol\"): "
            << edge::Path::join({"wat", "lol"})
            << std::endl;
  std::cout << "join(\"/a\", \"///b\"): "
            << edge::Path::join({"/a", "///b"})
            << std::endl;
  std::cout << "join(\"/a\", \"b\", \"c\", \"..\", \"d\"): "
            << edge::Path::join({"/a", "b", "c", "..", "d"})
            << std::endl;
  std::cout << std::endl;

  std::cout << "== Testing event emitter" << std::endl;
  edge::EventEmitter emitter;
  std::cout << "test on(): ";
  emitter.on("test", [] (void *data) { std::cout << "in event" << std::endl; });
  emitter.emit("test", nullptr);
  std::cout << "test removeAllListeners(): ";
  emitter.removeAllListeners();
  emitter.emit("test", nullptr);
  std::cout << std::endl;
  std::cout << "testing once() 1st: ";
  emitter.once("test", [] (void *data) { std::cout << "once" << std::endl; });
  emitter.emit("test", (void*)"");
  std::cout << "testing once() 2nd: ";
  emitter.emit("test", nullptr);
  std::cout << std::endl;
  std::cout << "test removeAllListerners(\"test\"): ";
  emitter.on("test", [] (void *data) { std::cout << "in event" << std::endl; });
  emitter.removeAllListeners("test");
  emitter.emit("test", nullptr);
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "== Parsing query string" << std::endl;
  auto queryString = edge::QueryString::parse("key=value&works=true&works=yes");
  for (auto &pair : queryString) {
    for (auto &value : pair.second) {
      std::cout << pair.first << "=" << value << std::endl;
    }
  }
  std::cout << std::endl;

  std::cout << "== Testing stringify" << std::endl;
  std::cout << edge::QueryString::stringify(queryString) << std::endl;

  */
}
