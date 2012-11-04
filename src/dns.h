#ifndef EDGE_DNS_H_
#define EDGE_DNS_H_ 1

#include <functional>
#include <memory>
#include <vector>
#include <string>

#include "uv.h"

#include "error.h"

namespace edge {
namespace dns {

  typedef std::shared_ptr<std::vector<std::string>> SharedResponse;
  typedef std::function<void(edge::SharedError,
                             edge::dns::SharedResponse)> Callback;
  typedef struct ResolveData_s {
    uv_getaddrinfo_t req;
    edge::dns::Callback cb;
  } ResolveData;

  /**
   *
   */
  void resolve(const char* domain, edge::dns::Callback cb);

  /**
   *
   */
  SharedResponse make_response();

  /**
   *
   */
  void _onResolve(uv_getaddrinfo_t* req, int status,
                         struct addrinfo* res);

}
}

#endif
