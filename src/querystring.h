#ifndef NODE_QUERY_STRING_H_
#define NODE_QUERY_STRING_H_ 1

#include <string>
#include <map>
#include <vector>

namespace node {

typedef std::map<std::string, std::vector<std::string>> QueryStringMap;

enum QueryStringState {
  QUERY_STRING_STATE_KEY = 0,
  QUERY_STRING_STATE_VALUE
};

class QueryString {
public:

  /**
   *
   */
  static node::QueryStringMap parse(std::string query);

  /**
   *
   */
  static std::string stringify(node::QueryStringMap query);

};
}

#endif
