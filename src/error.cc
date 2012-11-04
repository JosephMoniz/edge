#include "error.h"

std::string& edge::Error::getMessage() {
  return this->_message;
}

int edge::Error::getCode() {
  return this->_code;
}

edge::SharedError edge::make_error(std::string message) {
  return std::make_shared<edge::Error>(message);
}

edge::SharedError edge::make_error(int code) {
  return std::make_shared<edge::Error>(code);
}

edge::SharedError edge::make_error(const char* message, int code) {
  return std::make_shared<edge::Error>(message, code);
}
