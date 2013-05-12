#ifndef EDGE_RX_OBSERVER_H_
#define EDGE_RX_OBSERVER_H_ 1

namespace edge {
namespace rx {
template <class T>
class Observer {
public:

  /**
   *
   */
  virtual void onNext(T data) = 0;

  /**
   *
   */
  virtual void onError() = 0;

  /**
   *
   */
  virtual void onCompleted() = 0;

};
}
}

#endif
