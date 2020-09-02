#ifndef RAM_H
#define RAM_H

#include <cstdint>

// byte ram[4096]

class Ram {
  uint8_t __arr[4096] = {};

public:
  uint16_t font_sprite_addrs[16] = {};

  uint8_t& operator[](std::size_t ix) { return __arr[ix]; }
  const uint8_t& operator[](std::size_t ix) const { return __arr[ix]; }

  Ram() {}
};

#endif
