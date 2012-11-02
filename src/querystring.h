#ifndef EDGE_QUERY_STRING_H_
#define EDGE_QUERY_STRING_H_ 1

#include <string>
#include <map>
#include <vector>

namespace edge {

typedef std::map<std::string, std::vector<std::string>> QueryStringMap;

enum QueryStringState {
  QUERY_STRING_STATE_KEY = 0,
  QUERY_STRING_STATE_VALUE
};

class QueryString {
public:

  /**
   * This function takes an http post/get query string as a
   * std::string and parses it into a edge::QueryStringMap.
   * edge::QueryStringMap is simply a convenience alias for
   * a std::<std::string, std::vector<std::string>>. Keys in
   * the map are unique and values are always pushed onto the
   * value vector as std::strings.
   *
   * EXAMPLES:
   *  auto map = edge::QueryString::parse("key=value&test=val1&test=val2");
   *
   * @param {std::string} query      - The query string to parse
   * @returns {edge::QueryStringMap} - The resulting map of vectors of strings
   */
  static edge::QueryStringMap parse(std::string query);

  /**
   * This function takes a edge::QueryStringMap and returns it's
   * string representation as a std::string. Key value pairs will
   * be printed in order by key and keys with mutliple values in
   * their value vector will be printed in the order as they appear
   * in the vector.
   *
   * EXAMPLE:
   *  std::string original = "key=value&test=val1&test=val2";
   *  auto map = edge::QueryString::parse(original);
   *  auto query = edge::QueryString::stringify(map);
   *  (original === query) // -> true
   *
   * @param {edge::QueryStringMap} query - The map to stringify
   * @returns {std::string}              - The resulting query string
   */
  static std::string stringify(edge::QueryStringMap query);

};
}

#endif
