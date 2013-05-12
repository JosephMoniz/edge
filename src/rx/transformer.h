#ifndef EDGE_RX_TRANSFORMER_H_
#define EDGE_RX_TRANSFORMER_H_ 1

#include <functional>
#include <memory>

#include "rx/observable.h"
#include "rx/observer.h"

using edge::rx::Observable;
using edge::rx::Observer;

namespace edge {
namespace rx {
template <class, S, class T>
class Transformer : public Observable<S>,
                    public Observer<T> {
public:

  /**
   *
   */
  virtual Observable<T> bind(Observable<S>* observable) = 0;

  /**
   *
   */
  virtual Observable<T> bind(shared_ptr<Observable<S>> observable) = 0;

};
}
}

#endif
