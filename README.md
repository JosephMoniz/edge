Node.cc
=======
Evented I/O for C++11. This is a heavy work in progress at the moment.

Working Examples
================

TCP echo server:
```c++
int main(int argc, char **argv) {
  auto loop = node::Loop::getDefault();

  auto server = node::net::createServer([&](void* data) {
    auto socket = static_cast<node::net::Socket*>(data);
    socket->pipe(socket);
  });
  server->listen(8000);

  loop->run();
  return 0;
}
```

TCP echo client (stdin -> socket -> stdout):
```c++
int main(int argc, char **argv) {
  auto loop = node::Loop::getDefault();

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
  auto loop = node::Loop::getDefault();

  node::Timer timer;
  timer.start([]() {
    std::cout << "ping" << std::endl;
  }, 1000, 1000);

  loop->run();

  return 0;
}
```