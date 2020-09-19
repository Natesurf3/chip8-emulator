#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <cstdint>
#include <string>

namespace logger {
  static std::string buffer = "";

  void flush_log() {
    std::cout << buffer << std::flush;
    buffer = "";
  }


  void log(const std::string str) {
    buffer += str + "\n";
  }
  void log(const std::string str, int n) {
    buffer += str + "\n" + std::to_string(n);
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
