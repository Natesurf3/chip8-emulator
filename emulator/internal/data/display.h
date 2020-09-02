#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>

class Display {
  uint32_t __arr[64] = {};//top to bottom, (32x64 pixels)

public:
  uint32_t& operator[](std::size_t ix) { return __arr[ix]; }
  const uint32_t& operator[](std::size_t ix) const { return __arr[ix]; }

  Display() {}
};
#endif
