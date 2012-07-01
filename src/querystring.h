#include <string>
#include <map>
#include <vector>

#include "any.h"

namespace node {
class QueryString {
public:

  static std::string normalize(std::string path);
  // todo make variadic
  static std::string join(std::string p1, std::string p2);
  // todo make variadic
  static std::string dirname(std::string path);
  static std::string basename(std::string path);
  static std::string basename(std::string path, std::string ext);
  static std::string extname(std::string path);

};
}
