#include <string>
#include <map>
#include <vector>

#include "querystring.h"

edge::QueryStringMap edge::QueryString::parse(std::string query) {
  QueryStringMap map;
  std::string accumulatorKey;
  std::string accumulatorValue;
  edge::QueryStringState state = QUERY_STRING_STATE_KEY;

  for (auto &c : query) {
    switch(state) {
    case QUERY_STRING_STATE_KEY:
      if (c == '=') {
        state = QUERY_STRING_STATE_VALUE;
      } else {
        accumulatorKey += c;
      }
      break;
    case QUERY_STRING_STATE_VALUE:
      if (c == '&') {
        map[accumulatorKey].push_back(accumulatorValue);
        accumulatorKey.clear();
        accumulatorValue.clear();
        state = QUERY_STRING_STATE_KEY;
      } else {
        accumulatorValue += c;
      }
      break;
    }
  }

  if (accumulatorKey.length()) {
    map[accumulatorKey].push_back(accumulatorValue);
  }

  return map;
}

std::string edge::QueryString::stringify(edge::QueryStringMap query) {
  std::string resolved = "";

  for (auto &pair : query) {
    for (auto &value : pair.second) {
      resolved += pair.first;
      resolved += "=";
      resolved += value;
      resolved += "&";
    }
  }
  if (resolved.length()) { resolved.erase(resolved.end() - 1); }

  return resolved;
}
