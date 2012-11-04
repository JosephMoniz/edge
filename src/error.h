#ifndef EDGE_ERROR_H_
#define EDGE_ERROR_H_ 1

#include <string>
#include <memory>

namespace edge {
class Error {
public:

  /**
   *
   */
  Error(std::string message) : _message(message) {};

  /**
   *
   */
  Error(int code) : _code(code) {};

  /**
   *
   */
  Error(const char* message, int code) : _message(message), _code(code) {};

  /**
   *
   */
  std::string& getMessage();

  /**
   *
   */
  int getCode();

private:

  /**
   *
   */
  std::string _message;

  /*
   *
   */
  int _code;
};

/**
 *
 */
typedef std::shared_ptr<edge::Error> SharedError;

/**
 *
 */
SharedError make_error(std::string message);

/**
 *
 */
SharedError make_error(int code);

/**
 *
 */
SharedError make_error(const char* message, int code);

}

#endif
