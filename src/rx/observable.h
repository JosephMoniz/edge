#ifndef EDGE_RX_OBSERVABLE_H_
#define EDGE_RX_OBSERVABLE_H_ 1

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "rx/observer.h"

using std::function;
using std::map;
using std::shared_ptr;
using edge::rx::Observer;

namespace edge {
namespace rx {
template <class T>
class Observable {
public:

  /**
   *
   */
  void subscribe(Observer<T>* subscriber) {
    this->_pointers[++this->_id] = subscriber;
  }

  /**
   *
   */
  void subscribe(shared_ptr<Observer<T>> subscriber) {
    this->_sharedPointers[++this->_id] = subscriber;
  }

  /**
   *
   */
  void write(T data) {
    if (this->_completed) { return; }

    for (auto observer : this->_pointers) {
      observer->onNext(data);
    }

    for (auto observer : this->_sharedPointers) {
      observer->onNext(data);
    }
  }

  /**
   *
   */
  void error() {
    if (this->_completed) { return; }

    for (auto observer : this->_pointers) {
      observer->second->onError();
    }

    for (auto observer : this->_sharedPointers) {
      observer->second->onError();
    }

    this->_completed = true;
  }

  /**
   *
   */
  void end() {
    if (this->_completed) { return; }

    for (auto observer : this->_pointers) {
      observer->onEnd();
    }

    for (auto observer : this->_sharedPointers) {
      observer->onEnd();
    }

    this->_completed = true;
  }

  /**
   *
   */
  Observable<S> transform(Transformer<T>* transformer) {
    //
  }

  /**
   *
   */
  Observable<S> transform(shared_ptr<Transformer<T>> transformer) {
    //
  }

private:

  int _id;

  bool _completed;

  map<int, Observer<T>*> _pointers;

  map<int, shared_ptr<Observer<T>>> _sharedPointers;

};
}
}

#endif
