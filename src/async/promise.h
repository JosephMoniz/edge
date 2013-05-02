#ifndef EDGE_ASYNC_PROMISE
#define EDGE_ASYNC_PROMISE 1

#include <functional>
#include <vectory>

#include "eventemitter.h"

namespace edge {
namespace async {

enum PromiseState {
  PROMISE_STATE_UNRESOLVED = 0,
  PROMISE_STATE_RESOLVED,
  PROMISE_STATE_ERRORED
};

template <class E, class V>
class Promise : public edge::EventEmitter<edge::async::PromiseState> {
public:

  Promise() {
    this->_resolved = edge::async::Promise::PROMISE_STATE_UNRESOLVED;
  }

  template<E1, V1>
  Promise<E1, V1> then(std::function<Promise<E1, V1>(V)> success) {
    if (this->_resolved == edge::async::PROMISE_STATE_UNRESOLVED) {
      this->on("resolved", [](edge::async::PromiseState state) {
        if (state == edge::async::PROMISE_STATE_RESOLVED) {
          success(this->_value);
        }
      });
    }
    if (this->_resolved == edge::async::PROMISE_STATE_RESOLVED) {
      success(this->_value);
    }
  }

  template<E1, V1>
  Promise<E1, V1> fail(std::function<Promise<E1, V1>(E)> failure) {
    if (this->_resolved == edge::async::PROMISE_STATE_UNRESOLVED) {
      this->on("resolved", [](edge::async::PromiseState state) {
        if (state == edge::async::PROMISE_STATE_ERRORED) {
          failure(this->_value);
        }
      });
    }
    if (this->_resolved == edge::async::PROMISE_STATE_ERRORED) {
      failure(this->_value);
    }
  }

protected:

  edge::async::PromiseState _resolved;

  V _value;

  E _error;

};
}
}

#endif
