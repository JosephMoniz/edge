#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "eventemitter.h"

void node::EventEmitter::on(std::string event,
                            std::function<void(void*)> handler) {
  this->_events[event].push_back(handler);
}

void node::EventEmitter::once(std::string event,
                              std::function<void(void*)> handler) {
  this->_once[event].push_back(handler);
}

void node::EventEmitter::removeAllListeners() {
  this->_events.clear();
  this->_once.clear();
}
void node::EventEmitter::removeAllListeners(std::string event) {
  this->_events[event].clear();
  this->_once[event].clear();
}

void node::EventEmitter::emit(std::string event, void *data) {
  auto handlers = this->_events[event];
  for (auto &handler : handlers) {
    handler(data);
  }
  auto oneTimers = this->_once[event];
  for (auto &oneTimer : oneTimers) {
    oneTimer(data);
  }
  this->_once.erase(event);
}