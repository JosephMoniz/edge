Edge
=======
Evented I/O for C++11. This is a heavy work in progress at the moment.

Working Examples
================

HTTP Server:
```c++
using edge::Loop;
using edge::http::Server;
using edge::http::SharedClientStream;

int main(int argc, char **argv) {
  auto loop = Loop::getDefault();

  auto server = Server([](SharedClientStream stream) {
    stream->setHeader("Content-Type", "text/plain");
    stream->end("Hello world!");
  });
  server.listen(5000);

  loop->run();
  return 0;
}
```

TCP echo server:
```c++
using edge::Loop;
using edge::net::Server;
using edge::net::SharedSocket;

int main(int argc, char **argv) {
  auto loop = Loop::getDefault();

  auto server = Server([](SharedSocket socket) {
    socket->pipe(socket);
  });
  server.listen(8000);

  loop->run();
  return 0;
}
```

TCP telnet clone (stdin -> socket -> stdout):
```c++
using edge::Loop;
using edge::net::Socket;
using edge::process::stdin;
using edge::process::stdout;

int main(int argc, char **argv) {
  auto loop   = Loop::getDefault();
  auto socket = Socket();

  socket.connect(8000, [&]() {
    stdin.pipe(socket).pipe(stdout);
    stdin.resume();
  });

  loop->run();
}
```

HTTP server w/ chunked encoding
```c++
using edge::Loop;
using edge::Timer;
using edge::http::Server;
using edge::http::SharedClientStream;

int main(int argc, char **argv) {
  auto loop = Loop::getDefault();

  auto server = Server([](SharedClientStream stream) {
    stream->setHeader("Content-Type", "text/html");
    stream->write(
      "<html>"
      "  <head>"
      "    <title>node-cc</title>"
      "  </head>"
    );
    Timer::setTimeout([=]() {
      stream->end(
        "  <body>"
        "    <h1>Hello from node-cc</h1>"
        "  </body>"
        "</html>"
      );
    }, 2000);
  });
  server.listen(80);

  loop->run();
  return 0;
}
```

DNS resolution:
```c++
using edge::Loop;
using edge::SharedError;
using edge::dns::SharedResponse;

int main(int argc, char **argv) {
  auto loop = Loop::getDefault();

  edge::dns::resolve(
    "www.google.com",
    [](SharedError error, SharedResponse response) {
      if (error != nullptr) {
        std::cout << error->getMessage() << std::endl;
        return;
      }
      for (auto ip : *response) {
        std::cout << ip << std::endl;
      }
    }
  );

  loop->run();
  return 0;
}
```

Timers:
```c++
using edge::Loop;
using edge::Timer;

int main(int argc, char **argv) {
  auto loop = Loop::getDefault();

  auto timer = Timer::setInterval([]() {
    std::cout << "ping" << std::endl;
  }, 1000);

  loop->run();
  delete timer;
  return 0;
}
```