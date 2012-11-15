#ifndef EDGE_HTTP_CLIENTSTREAM_H_
#define EDGE_HTTP_CLIENTSTREAM_H_ 1

#include <functional>
#include <string>
#include <map>

#include "uv.h"
#include "http_parser.h"

#include "stream/readable.h"
#include "stream/writable.h"
#include "server.h"
#include "net.h"

namespace edge {
namespace http {

class Server;

class ClientStream : public edge::stream::Readable,
                     public edge::stream::Writable {

friend edge::http::Server;

public:

  /**
   * Import the overloaded write methods from edge::stream::Writable
   */
  using edge::stream::Writable::write;

  /**
   * Import the overloaded end methods from edge::stream::Writable
   */
  using edge::stream::Writable::end;

  /**
   *
   */
  std::string method;


  /**
   * This is the url of the received request
   */
  std::string url;

  /**
   * This is the http version of the incoming request
   */
  std::string httpVersion;

  /**
   * These are the incoming headers, not to be confused with the
   * out going response headers
   */
  std::map<std::string, std::string> headers;

  /**
   * These are the incoming trailers, not to be confused with the
   * out going response trailers
   */
  std::map<std::string, std::string> trailers;

  /**
   * This is the status code of the response
   */
  uint32_t statusCode;

  /**
   * If this is true we will send the Date header in the response
   * otherwise we'll ommit the Date header
   */
  bool sendDate;

  /**
   * Typical constructor, sets up some initial state and gets the
   * ball rolling
   */
  ClientStream(edge::http::Server* server, edge::net::SharedSocket socket);

  /**
   *
   */
  void writeContinue();

  /**
   * This function takes an HTTP response status code as an argument
   * and renders the HTTP header portion of the response and sends
   * it to the client with the default reason of "OK"
   *
   * @param {int} statusCode - The status code to respond with
   * @returns {void}
   */
  void writeHead(int statusCode);

  /**
   * This function takes an HTTP response status code and a reason
   * as a const char* and renders the HTTP header portion of the
   * response and sends it to the client
   *
   * @param {int} statusCode     - The status code to respond with
   * @param {const char*} reason - The HTTP response reason
   * @returns {void}
   */
  void writeHead(int statusCode, const char* reason);

  /**
   * This function takes a header name and header value as it's
   * arguments and sets the specified header to the specified
   * value.
   *
   * @param {const char*} name  - The name of the header to set
   * @param {const char*} value - The value of the header to set
   * @returns {void}
   */
  void setHeader(const char* name, const char* value);

  /**
   * This function takes a header name and returns it's current
   * value as a const char* if it exists otherwise nullptr
   *
   * @param {const char*} name - The name of the header to fetch
   * @returns {const char*}    - The value or nullptr
   */
  const char* getHeader(const char* name);

  /**
   * This function takes a header name and removes it from the
   * headers to be sent
   *
   * @param {const char*} name - The name of the header to remove
   * @returns {void}
   */
  void removeHeader(const char* name);

  /**
   * This function takes a uv_buf_t* and writes it to the underyling
   * stream. If the headers haven't been written to the client yet
   * the will be.
   *
   * @param {uv_buf_t*} buf - The data to write to the stream
   * @returns {void}
   */
  void write(uv_buf_t* buf);

  /**
   * This function closes the underlying tcp stream. If HTTP headers have
   * not yet be written they will and a sane HTTP response will be sent
   * to the client.
   *
   * @returns {void}
   */
  void end();

  /**
   * This callback is ran every time we begin parsing a new HTTP request
   *
   *
   */
  static int _onMessageBegin(http_parser* parser);

  /**
   *
   */
  static int _onUrl(http_parser* parser, const char* at, size_t length);

  /**
   *
   */
  static int _onHeaderField(http_parser* parser, const char* at, size_t length);

  /**
   *
   */
  static int _onHeaderValue(http_parser* parser, const char* at, size_t length);

  /**
   *
   */
  static int _onHeadersComplete(http_parser* parser);

  /**
   *
   */
  static int _onBody(http_parser* parser, const char* at, size_t length);

  /**
   *
   */
  static int _onMessageComplete(http_parser* parser);

private:
  /**
   *
   */
  edge::http::Server* _server;

  /**
   *
   */
  edge::net::SharedSocket _socket;

  /**
   *
   */
  std::map<std::string, std::string> _headers;

  /**
   *
   */
  std::string _fieldTmp;

  /**
   *
   */
  std::string _tmp;

  /**
   *
   */
  bool _hasHeaderValue;

  /**
   *
   */
  bool _headersWritten;

  /**
   *
   */
  bool _isChunkedEncoding;

  /**
   *
   */
  http_parser _parser;

};

extern http_parser_settings _settings;

}
}

#endif
