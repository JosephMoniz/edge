Node.cc
=======
Evented I/O for C++11. This is a heavy work in progress at the moment.

Working Examples
================

HTTP Server:
```c++
int main(int argc, char **argv) {
  auto loop = node::Loop::getDefault();

  auto server = node::http::Server([](node::http::ClientStream* stream) {
    stream->setHeader("Content-Type", "text/plain");
    stream->end("Hello world!");
  });
  server.listen(80);

  loop->run();
  return 0;
}
```

HTTP server w/ chunked encoding
```c++
int main(int argc, char **argv) {
  auto loop = node::Loop::getDefault();

  auto server = node::http::Server([](node::http::ClientStream* stream) {
    stream->setHeader("Content-Type", "text/html");
    stream->write(
      "<html>"
      "  <head>"
      "    <title>node-cc</title>"
      "  </head>"
    );
    node::Timer::setTimeout([=]() {
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

TCP echo server:
```c++
int main(int argc, char **argv) {
  auto loop = node::Loop::getDefault();

  auto server = node::net::createServer([](node::net::Socket* socket) {
    socket->pipe(socket);
  });
  server->listen(8000);

  loop->run();
  return 0;
}
```

TCP telnet clone (stdin -> socket -> stdout):
```c++
int main(int argc, char **argv) {
  auto loop   = node::Loop::getDefault();
  auto socket = node::net::Socket();

  socket.connect(8000, [&]() {
    node::process::stdin.pipe(socket).pipe(node::process::stdout);
    node::process::stdin.resume();
  });

  loop->run();
}
```

Timers:
```c++
int main(int argc, char **argv) {
  auto loop = node::Loop::getDefault();

  auto timer = node::Timer::setInterval([]() {
    std::cout << "ping" << std::endl;
  }, 1000);

  loop->run();
  delete timer;
  return 0;
}
```