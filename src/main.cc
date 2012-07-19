/**
 * For the purposes of rapid development this file will be used as a sort
 * of ghetto unit testing
 */

#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "loop.h"
#include "timers.h"
#include "path.h"
#include "eventemitter.h"
#include "querystring.h"

int main(int argc, char **argv) {
  auto loop = node::Loop::getDefault();

  node::Timer timer;
  timer.start([](node::Timer* self, int status) {
    std::cout << "ping" << std::endl;
  }, 3000, 0);

  loop->run();

  return 0;

  /**
  std::cout << "== Testing extname" << std::endl;
  std::cout << "lolwat.jpg: " << node::Path::extname("lolwat.jpg") << std::endl;
  std::cout << "/a/wat.jpg: " << node::Path::extname("/a/wat.jpg") << std::endl;
  std::cout << "lolwat.: " << node::Path::extname("lolwat.") << std::endl;
  std::cout << "lolwat: " << node::Path::extname("lolwat") << std::endl;
  std::cout << std::endl;

  std::cout << "== Testing basename" << std::endl;
  std::cout << "wat.jpg: " << node::Path::basename("wat.jpg") << std::endl;
  std::cout << "/b/a.jpg: " << node::Path::basename("/b/a.jpg") << std::endl;
  std::cout << "/b/wat/: " << node::Path::basename("/b/wat/") << std::endl;
  std::cout << std::endl;

  std::cout << "== Testing basename w/ extension" << std::endl;
  std::cout << "a.jpg: " << node::Path::basename("a.jpg", "jpg") << std::endl;
  std::cout << "/b/a.jpg: "
            << node::Path::basename("/b/a.jpg", "jpg")
            << std::endl;
  std::cout << "/b/wat: "
            << node::Path::basename("/b/wat", "jpg")
            << std::endl;
  std::cout << "/b/wat/: "
            << node::Path::basename("/b/wat/", "jpg")
            << std::endl;
  std::cout << std::endl;

  std::cout << "== Testing dirname" << std::endl;
  std::cout << "wat.jpg: " << node::Path::dirname("wat.jpg") << std::endl;
  std::cout << "/b/a.jpg: " << node::Path::dirname("/b/a.jpg") << std::endl;
  std::cout << "/b/wat/: " << node::Path::dirname("/b/wat/") << std::endl;
  std::cout << "/b/wat: " << node::Path::dirname("/b/wat") << std::endl;
  std::cout << "/b/wat//: " << node::Path::dirname("/b/wat//") << std::endl;
  std::cout << std::endl;

  std::cout << "== Testing normalize" << std::endl;
  std::cout << "wat.jpg: " << node::Path::normalize("wat.jpg") << std::endl;
  std::cout << "/a/b/c/../d: "
            << node::Path::normalize("/a/b/c/../d")
            << std::endl;
  std::cout << "a/b/c/../../d: "
            << node::Path::normalize("a/b/c/../../d")
            << std::endl;
  std::cout << "/b/wat//: " << node::Path::normalize("/b/wat//") << std::endl;
  std::cout << "/b///wat/: " << node::Path::normalize("/b///wat/") << std::endl;
  std::cout << ": " << node::Path::normalize("") << std::endl;
  std::cout << "/: " << node::Path::normalize("/") << std::endl;
  std::cout << std::endl;

  std::cout << "== Testing join" << std::endl;
  std::cout << "join(\"wat\", \"lol\"): "
            << node::Path::join({"wat", "lol"})
            << std::endl;
  std::cout << "join(\"/a\", \"///b\"): "
            << node::Path::join({"/a", "///b"})
            << std::endl;
  std::cout << "join(\"/a\", \"b\", \"c\", \"..\", \"d\"): "
            << node::Path::join({"/a", "b", "c", "..", "d"})
            << std::endl;
  std::cout << std::endl;

  std::cout << "== Testing event emitter" << std::endl;
  node::EventEmitter emitter;
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
  auto queryString = node::QueryString::parse("key=value&works=true&works=yes");
  for (auto &pair : queryString) {
    for (auto &value : pair.second) {
      std::cout << pair.first << "=" << value << std::endl;
    }
  }
  std::cout << std::endl;

  std::cout << "== Testing stringify" << std::endl;
  std::cout << node::QueryString::stringify(queryString) << std::endl;

  */
}
