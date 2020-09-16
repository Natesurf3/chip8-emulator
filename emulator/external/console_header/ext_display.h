#ifndef EXT_DISPLAY_H
#define EXT_DISPLAY_H
#include <iostream>
#include <cstdint>
#include "../../internal/data/chip8_data.h"

static const uint32_t first_bit = 1 << 31; // selector for first bit


class ExtDisplay {
  std::string surface;

public:
  ExtDisplay() {}

  void update(Chip8Data data) {
    surface = "";

    for(size_t y = 0; y < 64; y++) {
      uint32_t row = data.display[y];
      for(uint32_t sel = first_bit; sel != 0; sel>>=1) {
        bool bit = row&sel;
        if(bit)
          surface += "##";
        else
          surface += "  ";
      }
      surface += '\n';
    }
  }

  void communicate() {
    std::cout << surface << std::endl;
  }
};

#endif
