#ifndef NODE_EVENT_EMITTER_H_
#define NODE_EVENT_EMITTER_H_ 1

#include <string>
#include <map>
#include <vector>
#include <functional>

namespace node {
class EventEmitter {
public:

  /**
   * This function binds the supplied `handler()` function to the supplied
   * `event` string such that whenever `emit()` is called on this object
   * with a matching `event` string the supplied `handler()` function wil
   * be executed
   *
   * EXAMPLE:
   *    node::EventEmitter emitter;
   *    emitter.on("load", [](void *data) { std::cout << "loaded"; });
   *    emitter.emit("load", nullptr); // -> loaded
   *
   * @param {std::string} event          - The event to bind the handler to
   * @param {std::function<void(void*)>} - The handler to bind to the event
   * @returns {Void}
   */
  void on(std::string event, std::function<void(void*)> handler);

  /**
   * This function bind the supplied `handler()` function to the supplied
   * `event` string such that only on the next time `emit()` is called on
   * this object with a matching `event` string the supplied `handler()`
   * will be executed. Subsequenct calls to `emit()` on this object with
   * a matching `event` string will not trigger the supplied `handler()`
   * to be executed
   *
   * EXAMPLE:
   *    node::EventEmitter emitter;
   *    emitter.once("loaded", [](void *data) { std::cout << "loaded"; });
   *    emitter.emit("loaded", nullptr); // -> loaded
   *    emitter.emit("loaded", nullptr); // ->
   *
   * @param {std::string} event          - The event to bind the handler to
   * @param {std::function<void(void*)>} - The handler to bind to the event
   * @returns {Void}
   */
  void once(std::string event, std::function<void(void*)> handler);

  /**
   * This function removes all binded handlers for all events of the
   * object that it is called on.
   *
   * EXAMPLE:
   *    node::EventEmitter emitter;
   *    emitter.on("loaded", [](void *data) { std::cout << "loaded"; });
   *    emitter.emit("loaded", nullptr); // -> loaded
   *    emitter.removeAllListeners();
   *    emitter.emit("loaded", nullptr)  // ->
   *
   * @returns {Void}
   */
  void removeAllListeners();

  /**
   * This function removes all handlers that are bound to the supplied
   * event on the object that this function is called from.
   *
   * EXAMPLE:
   *    node::EventEmitter emitter;
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
  void removeAllListeners(std::string event);

  /**
   * This function executes all handlers bound to the supplied `event` and
   * passes them the supplied void*
   *
   * EXAMPLE:
   *    node::EventEmitter emitter;
   *    emitter.on("load", [](void *data) { std::cout << "loaded"; });
   *    emitter.emit("load", nullptr); // -> loaded
   *
   * @param {std::string} event - The event to execute handlers for
   * @param {void *}            - The data pointer to pass to all handlers
   * @returns {Void}
   */
  void emit(std::string event, void *data);

private:
  std::map<std::string, std::vector<std::function<void(void*)>>> _events;
  std::map<std::string, std::vector<std::function<void(void*)>>> _once;
};
}

#endif
