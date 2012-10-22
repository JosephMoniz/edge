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

  std::cout << "=== Connecting to echo server" << std::endl;
  socket->connect(8080, "127.0.0.1", [&](){
    std::cout << "in connect cb" << std::endl << std::endl;

    std::cout << "==== Testing writing from client socket" << std::endl;
    socket->write("yo dawg\n", [&](){
      std::cout << "in write cb" << std::endl << std::endl;

      std::cout << "==== Testing reading from client socket" << std::endl;
      socket->on("data", [&](void *data) {
          uv_buf_t* buf = (uv_buf_t*)data;
          std::cout << "<-- " << buf->base << std::endl;
      });
    });
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