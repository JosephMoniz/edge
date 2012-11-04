#include <iostream>
#include "loop.h"
#include "dns.h"

void edge::dns::resolve(const char* domain, edge::dns::Callback cb) {
  auto addrReq = new edge::dns::ResolveData;
  struct addrinfo hints;

  addrReq->cb = cb;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family   = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  uv_getaddrinfo(
    edge::Loop::getDefault()->getUVLoop(),
    &addrReq->req,
    edge::dns::_onResolve,
    domain,
    nullptr,
    &hints
  );
}

edge::dns::SharedResponse edge::dns::make_response() {
  return std::make_shared<std::vector<std::string>>();
}

void edge::dns::_onResolve(uv_getaddrinfo_t* req, int status,
                           struct addrinfo* res) {
  auto data = (edge::dns::ResolveData*) req;

  if (status) {
    data->cb(edge::make_error("failed resolving host"), nullptr);
    uv_freeaddrinfo(res);
    return;
  }

  char ip[INET6_ADDRSTRLEN];
  auto results = edge::dns::make_response();

  for (auto address = res; address; address = address->ai_next) {
    if (address->ai_family != AF_INET) { continue; }

    auto addr = (char*) &((struct sockaddr_in*) address->ai_addr)->sin_addr;
    uv_err_t err = uv_inet_ntop(
      address->ai_family,
      addr,
      ip,
      INET6_ADDRSTRLEN
    );

    if (err.code != UV_OK) { continue; }

    results->push_back(ip);
  }

  data->cb(nullptr, results);

  uv_freeaddrinfo(res);
}
