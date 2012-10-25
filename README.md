Node.cc
=======
Evented I/O for C++11. This is a heavy work in progress at the moment.

Working Examples
================
Client TCP sockets:
```c++
int main(int argc, char **argv) {
  auto loop   = node::Loop::getDefault();
  auto socket = std::make_shared<node::net::Socket>();

  socket->connect(8080, [&](){
    node::process::stdin.pipe(socket).pipe(node::process::stdout);
  });

  loop->run();
  return 0;
}
```

Timers:
```c++
int main(int argc, char **argv) {
  auto loop = node::Loop::getDefault();

  node::Timer timer;
  timer.start([](node::Timer* self, int status) {
    std::cout << "ping" << std::endl;
  }, 1000, 1000);

  loop->run();
  return 0;
}
```