#ifndef EDGE_EVENT_EMITTER_H_
#define EDGE_EVENT_EMITTER_H_ 1

#include <string>
#include <map>
#include <vector>
#include <functional>

namespace edge {
class EventEmitter {
public:

  /**
   * This function binds the supplied `handler()` function to the supplied
   * `event` string such that whenever `emit()` is called on this object
   * with a matching `event` string the supplied `handler()` function wil
   * be executed
   *
   * EXAMPLE:
   *    edge::EventEmitter emitter;
   *    emitter.on("load", [](void *data) { std::cout << "loaded"; });
   *    emitter.emit("load", nullptr); // -> loaded
   *
   * @param {std::string} event          - The event to bind the handler to
   * @param {std::function<void(void*)>} - The handler to bind to the event
   * @returns {Void}
   */
    void on(std::string event, std::function<void(void*)> handler) {
      this->_events[event].push_back(handler);
    }

  /**
   * This function bind the supplied `handler()` function to the supplied
   * `event` string such that only on the next time `emit()` is called on
   * this object with a matching `event` string the supplied `handler()`
   * will be executed. Subsequenct calls to `emit()` on this object with
   * a matching `event` string will not trigger the supplied `handler()`
   * to be executed
   *
   * EXAMPLE:
   *    edge::EventEmitter emitter;
   *    emitter.once("loaded", [](void *data) { std::cout << "loaded"; });
   *    emitter.emit("loaded", nullptr); // -> loaded
   *    emitter.emit("loaded", nullptr); // ->
   *
   * @param {std::string} event          - The event to bind the handler to
   * @param {std::function<void(void*)>} - The handler to bind to the event
   * @returns {Void}
   */
  void once(std::string event, std::function<void(void*)> handler) {
    this->_once[event].push_back(handler);
  }

  /**
   * This function removes all binded handlers for all events of the
   * object that it is called on.
   *
   * EXAMPLE:
   *    edge::EventEmitter emitter;
   *    emitter.on("loaded", [](void *data) { std::cout << "loaded"; });
   *    emitter.emit("loaded", nullptr); // -> loaded
   *    emitter.removeAllListeners();
   *    emitter.emit("loaded", nullptr)  // ->
   *
   * @returns {Void}
   */
  void removeAllListeners() {
    this->_events.clear();
    this->_once.clear();
  }

  /**
   * This function removes all handlers that are bound to the supplied
   * event on the object that this function is called from.
   *
   * EXAMPLE:
   *    edge::EventEmitter emitter;
   *    emitter.on("loaded", [](void *data) { std::cout << "loaded"; });
   *    emitter.emit("loaded", nullptr); // -> loaded
   *    emitter.removeAllListeners("verified");
   *    emitter.emit("loaded", nullptr); // -> loaded
   *    emitter.removeAllListeners("loaded");
   *    emitter.emit("loaded", nullptr); // ->
   *
   * @param {std::string} event - The event to remove all handlers from
   * @returns {Void}
   */
  void removeAllListeners(std::string event) {
    this->_events[event].clear();
    this->_once[event].clear();
  }

  /**
   * This function executes all handlers bound to the supplied `event` and
   * passes them the supplied void*
   *
   * EXAMPLE:
   *    edge::EventEmitter emitter;
   *    emitter.on("load", [](void *data) { std::cout << "loaded"; });
   *    emitter.emit("load", nullptr); // -> loaded
   *
   * @param {std::string} event - The event to execute handlers for
   * @param {void *}            - The data pointer to pass to all handlers
   * @returns {Void}
   */
  void emit(std::string event, void *data) {
    auto handlers = this->_events[event];
    for (auto &handler : handlers) {
      handler(data);
    }
    auto oneTimers = this->_once[event];
    for (auto &oneTimer : oneTimers) {
      oneTimer(data);
    }
    this->_once.erase(event);
  }

private:
  std::map<std::string, std::vector<std::function<void(void*)>>> _events;
  std::map<std::string, std::vector<std::function<void(void*)>>> _once;
};
}

#endif
