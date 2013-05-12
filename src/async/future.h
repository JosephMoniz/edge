#ifndef EDGE_ASYNC_FUTURE
#define EDGE_ASYNC_FUTURE 1

#include <functional>
#include <memory>

#include "eventemitter.h"

namespace edge {
namespace async {

enum FutureState {
  FUTURE_STATE_UNRESOLVED = 0,
  FUTURE_STATE_RESOLVED,
  FUTURE_STATE_ERRORED
};


template <class E, class V>
class Future {
public:

  /**
   *
   */
  Future() {
    this->_resolved = edge::async::Promise::FUTURE_STATE_UNRESOLVED;
  }

  /**
   *
   */
  static std::shared_ptr<Future<E, V>> error(E error) {
    auto future = new Future<E, V>();
    future.reject(error);
    return this->promise();
  }

  /**
   *
   */
  static std::shared_ptr<Future<E, V>> value(V value) {
    auto future = new Future<E, V>();
    future.resolve(value);
    return this->promise();
  }

  /**
   *
   */
  static std::shared_ptr<Future<E, V>> sync(std::function<V()> computation) {
    return edge::async::Future::value(computation());
  }

  /**
   *
   */
  void resolve(V value) {
    this->_value    = value;
    this->_resolved = edge::async::FUTURE_STATE_RESOLVED;
    this->emit("resolved", this->_resolved);
  }

  /**
   *
   */
  void reject(E error) {
    this->_error    = error;
    this->_resolved = edge::async::FUTURE_STATE_ERRORED;
    this->emit("resolved", this->_resolved);
  }

  /**
   *
   */
  template<E1, V1>
  Future<E1, V1> then(std::function<Promise<E1, V1>(V)> success) {
    if (this->_resolved == edge::async::FUTURE_STATE_UNRESOLVED) {
      this->on("resolved", [](edge::async::PromiseState state) {
        if (state == edge::async::FUTURE_STATE_RESOLVED) {
          success(this->_value);
        }
      });
    }
    if (this->_resolved == edge::async::FUTURE_STATE_RESOLVED) {
      success(this->_value);
    }
  }

  /**
   *
   */
  template<E1, V1>
  Future<E1, V1> fail(std::function<Promise<E1, V1>(E)> failure) {
    if (this->_resolved == edge::async::FUTURE_STATE_UNRESOLVED) {
      this->on("resolved", [](edge::async::PromiseState state) {
        if (state == edge::async::FUTURE_STATE_ERRORED) {
          failure(this->_value);
        }
      });
    }
    if (this->_resolved == edge::async::FUTURE_STATE_ERRORED) {
      failure(this->_value);
    }
  }

protected:

  /**
   *
   */
  edge::async::PromiseState _resolved;

  /**
   *
   */
  V _value;

  /**
   *
   */
  E _error;

  edge::EventEmitter<edge::async::FutureState> _emitter;

};
}
}

#endif
