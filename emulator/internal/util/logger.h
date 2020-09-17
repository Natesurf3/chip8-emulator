#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <cstdint>
#include <string>

namespace logger {
  void log(const std::string str) {
    std::cout << str << std::endl;
  }
  void log(const std::string str, int n) {
    std::cout << str << n << std::endl;
  }

  void log(const std::string str, size_t len, const int *n) {
    std::string out = str+"{";
    for(int i = 0; i < len; i++) {
      out += std::to_string(n[i]);
      if(i != (len-1))
        out += ",";
    }
    out += "}";

    log(out);
  }

  void log(const std::string str, size_t len, const uint8_t *n) {
    std::string out = str+"{";
    for(int i = 0; i < len; i++) {
      out += std::to_string((int)n[i]);
      if(i != (len-1))
        out += ",";
    }
    out += "}";

    log(out);
  }
}

#endif
