#include <string>
#include <map>
#include <vector>
#include <functional>

namespace node {
class EventEmitter {
public:

  /**
   *
   */
  void on(std::string event, std::function<void(void*)> handler);

  /**
   *
   */
  void once(std::string event, std::function<void(void*)> handler);

  /**
   *
   */
  void removeAllListeners();

  /**
   *
   */
  void removeAllListeners(std::string event);

  /**
   *
   */
  void emit(std::string event, void *data);

private:
  std::map<std::string, std::vector<std::function<void(void*)>>> _events;
  std::map<std::string, std::vector<std::function<void(void*)>>> _once;
};
}
