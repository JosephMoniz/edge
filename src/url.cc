#include <iostream>
#include <string>
#include <algorithm>

#include "url.h"

edge::Url::Url(const char* url, size_t len) {
  auto protocolEnd = "://";
  auto urlEnd      = &url[len];

  this->href.assign(url, urlEnd);

  auto protocolIt = std::search(url, urlEnd, protocolEnd, &protocolEnd[3]);
  auto afterProtocolIt = url;
  if (protocolIt != urlEnd) {
    afterProtocolIt = protocolIt + 3;
    this->protocol.assign(url, protocolIt);
  }

  auto beforePathIt = std::find(afterProtocolIt, urlEnd, '/');
  auto afterAuthIt  = std::find(afterProtocolIt, beforePathIt, '@');
  if (afterAuthIt != beforePathIt) {
    this->auth.assign(afterProtocolIt, afterAuthIt++);
  } else {
    afterAuthIt = afterProtocolIt;
  }

  auto beforePortIt = std::find(afterAuthIt, beforePathIt, ':');
  if (beforePortIt != beforePathIt) {
    this->port.assign(&beforePortIt[1], beforePathIt);
  }
  this->host.assign(afterAuthIt, beforePathIt);
  this->hostname.assign(afterAuthIt, beforePortIt);

  auto beforeHashIt = std::find(beforePathIt, urlEnd, '#');
  this->path.assign(beforePathIt, beforeHashIt);
  if (beforeHashIt != urlEnd) {
    this->hash.assign(&beforeHashIt[1], urlEnd);
  }

  auto beforeQueryIt = std::find(beforePathIt, beforeHashIt, '?');
  if (beforeQueryIt != beforeHashIt) {
    this->query.assign(&beforeQueryIt[1], beforeHashIt);
  }
  this->pathname.assign(beforePathIt, beforeQueryIt);
}
