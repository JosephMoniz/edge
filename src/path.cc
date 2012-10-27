#include <iostream>
#include <string>
#include <algorithm>
#include <initializer_list>

#include <stdint.h>

#include "path.h"

std::string node::Path::normalize(std::string path) {
  bool isAbsolute      = path[0] == '/';
  bool trailingSlash   = *(path.end() - 1) == '/';
  auto it              = path.rbegin();
  uint32_t up          = 0;
  std::string resolved = "";

  while(it != path.rend()) {
    auto next = std::find(it, path.rend(), '/');

    // Drop double forward slashes
    if (next == it) {
      if (next != path.rend()) {
        it = next + 1;
      } else {
        it = next;
      }
      continue;
    }

    // Drop single dot directories
    if (next == it + 1 && std::equal(it, next, ".")) {
      if (next != path.rend()) {
        it = next + 1;
      } else {
        it = next;
      }
      continue;
    }

    // Drop double dot directories and increment the traversal height
    if (next == it + 2 && std::equal(it, next, "..")) {
      if (next != path.rend()) {
        it = next + 1;
      } else {
        it = next;
      }
      up++;
      continue;
    }

    // If the travaersal height is non zero, decrement it and
    // drop the current directory
    if (up) {
      if (next != path.rend()) {
        it = next + 1;
      } else {
        it = next;
      }
      up--;
      continue;
    }

    // Save the current directory to the resolved path
    if (next != path.rend()) { next++; }
    resolved.insert(resolved.end(), it, next);
    it = next;
  }

  // If the resolved path is zero length, set it
  // to the absoute or relative path
  if (!resolved.length()) {
    if (isAbsolute) {
      return std::string("/");
    } else {
      return std::string(".");
    }
  }

  // If we had a trailing slash lets add that back to the path
  if (resolved.length() && trailingSlash) {
    resolved.insert(resolved.begin(), '/');
  }

  return std::string(resolved.rbegin(), resolved.rend());
}

std::string node::Path::join(std::initializer_list<std::string> peices) {
  std::string resolved = "";

  for (auto &peice : peices) {
    resolved += peice;
    resolved += "/";
  }
  resolved.erase(resolved.end() - 1);

  return node::Path::normalize(resolved);
}

std::string node::Path::dirname(std::string path) {
  auto it = node::Path::_basenameIterator(path);
  if (it == path.begin()) {
    if (*it == '/') {
      return std::string("/");
    } else {
      return std::string(".");
    }
  } else {
    return std::string(path.begin(), it - 1);
  }
}

std::string node::Path::basename(std::string path) {
  return std::string(node::Path::_basenameIterator(path), path.end());
}

std::string node::Path::basename(std::string path, std::string ext) {
  auto it = node::Path::_basenameIterator(path);
  auto hasExtension = std::equal(ext.rbegin(), ext.rend(), path.rbegin());
  if (hasExtension) {
    return std::string(it, (path.rbegin() + ext.length()).base() - 1);
  } else {
    return std::string(it, path.end());
  }
}

std::string node::Path::extname(std::string path) {
  auto it = std::find(path.rbegin(), path.rend(), '.');
  if (it == path.rend()) {
    return "";
  } else {
    return std::string(it.base() - 1, path.end());
  }
}

std::string::iterator node::Path::_basenameIterator(std::string &path) {
  auto begin = path.rbegin();
  if (*begin == '/') { begin++; }
  return std::find(begin, path.rend(), '/').base();
}
