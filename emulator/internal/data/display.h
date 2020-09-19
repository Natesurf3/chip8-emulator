#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>

class Display {
  bool __arr[32][64] = {};//[height][width]

public:
  bool get(size_t x, size_t y) {
    return __arr[y][x];
  }
  bool set(size_t x, size_t y, bool value) {
    return __arr[y][x] = value;
  }

  Display() {}
};
#endif
