#ifndef EDGE_ASYNC_FUTURE
#define EDGE_ASYNC_FUTURE 1

#include <functional>
#include <memory>

#include "async/promise.h"

namespace edge {
namespace async {
template <class E, class V>
class Future : public edge::async::Promise<E, V> {
public:

  static Promise<E, V>* error(E error) {
    auto future = new Future<E, V>();
    future.reject(error);
    return this->promise();
  }

  static Promise<E, V>* value(V value) {
    auto future = new Future<E, V>();
    future.resolve(value);
    return this->promise();
  }

  static Promise<E, V>* sync(std::function<V()> computation) {
    return edge::async::Future::value(computation);
  }

  Promise<E, V>* promise() {
    return this;
  }

  void resolve(V value) {
    this->_value    = value;
    this->_resolved = edge::async::PROMISE_STATE_RESOLVED;
    this->emit("resolved", this->_resolved);
  }

  void reject(E error) {
    this->_error    = error;
    this->_resolved = edge::async::PROMISE_STATE_ERRORED;
    this->emit("resolved", this->_resolved);
  }

};
}
}

#endif
