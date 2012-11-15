Edge
=======
Evented I/O for C++11. This is a heavy work in progress at the moment.

Working Examples
================

HTTP Server:
```c++
int main(int argc, char **argv) {
  auto loop = edge::Loop::getDefault();

  auto server = edge::http::Server([](edge::http::SharedClientStream stream) {
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
int main(int argc, char **argv) {
  auto loop = edge::Loop::getDefault();

  auto server = edge::net::Server([](edge::net::SharedSocket socket) {
    socket->pipe(socket);
  });
  server.listen(8000);

  loop->run();
  return 0;
}
```

TCP telnet clone (stdin -> socket -> stdout):
```c++
int main(int argc, char **argv) {
  auto loop   = edge::Loop::getDefault();
  auto socket = edge::net::Socket();

  socket.connect(8000, [&]() {
    edge::process::stdin.pipe(socket).pipe(edge::process::stdout);
    edge::process::stdin.resume();
  });

  loop->run();
}
```

HTTP server w/ chunked encoding
```c++
int main(int argc, char **argv) {
  auto loop = edge::Loop::getDefault();

  auto server = edge::http::Server([](edge::http::SharedClientStream stream) {
    stream->setHeader("Content-Type", "text/html");
    stream->write(
      "<html>"
      "  <head>"
      "    <title>node-cc</title>"
      "  </head>"
    );
    edge::Timer::setTimeout([=]() {
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

  loop->run();
  return 0;
}
```

Timers:
```c++
int main(int argc, char **argv) {
  auto loop = edge::Loop::getDefault();

  auto timer = edge::Timer::setInterval([]() {
    std::cout << "ping" << std::endl;
  }, 1000);

  loop->run();
  delete timer;
  return 0;
}
```