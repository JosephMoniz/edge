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

  socket->connect(8080, "127.0.0.1", [&](){
    socket->write("yo dog, i heard you like evented I/O\n");
    socket->on("data", [&](void *data) {
      uv_buf_t* buf = (uv_buf_t*)data;
      node::process::stdout.write(buf->base, buf->len);
    });
    socket->on("end", [&](void *data) {
      node::process::stdout.write("remote connection closed\n");
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