Node.cc
=======
Evented I/O for C++11. This is a heavy work in progress at the moment.

Working Examples
================

HTTP Server
```c++
int main(int argc, char **argv) {
  auto loop = node::Loop::getDefault();

  auto web = node::http::Server([](node::http::ClientStream* stream) {
    stream->end("Hello world!");
  });
  web.listen(80);

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
  });

  loop->run();
}
```

Timers:
```c++
int main(int argc, char **argv) {
  auto loop  = node::Loop::getDefault();
  auto timer = node::Timer();

  timer.start([]() {
    std::cout << "ping" << std::endl;
  }, 1000, 1000);

  loop->run();

  return 0;
}
```