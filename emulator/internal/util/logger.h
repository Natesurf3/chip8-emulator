#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

namespace logger {
  void log(std::string str) {
    std::cout << str << std::endl;
  }
  void log(std::string str, int n) {
    std::cout << str << n << std::endl;
  }

  std::string int_arr_to_str(int *arr, size_t len) {
    std::string out = "[";
    for(int i = 0; i < len; i++) {
      out += std::to_string(arr[i]);
      if(i != (len-1))
        out += ",";
    }
    out += "]";
    return out;
  }
}

#endif
