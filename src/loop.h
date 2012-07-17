#ifndef NODE_LOOP_H_
#define NODE_LOOP_H_ 1

#include <string>
#include <map>
#include <vector>

namespace node {
class Loop {
public:

  /**
   *
   */
  static node::Loop* getDefault();

  /**
   *
   */
  static void deleteDefault();

  /**
   *
   */
  int run();

  /**
   *
   */
  int runOnce();

 private:

  Logger();

  Logger(Logger const&) { };

  Logger& operator=(Logger const&) { };

  static node::Loop* _instance = nullptr;
  uv_loop_t* _loop;

};
}

#endif
