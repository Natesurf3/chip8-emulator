#ifndef EXT_DISPLAY_H
#define EXT_DISPLAY_H
#include <iostream>
#include <cstdint>
#include "../../internal/data/chip8_data.h"
#include "../../internal/util/logger.h"

static const uint32_t first_bit = 1 << 31; // selector for first bit


class ExtDisplay {
  std::string surface;

public:
  ExtDisplay() {}

  void update(Chip8Data data) {
    surface = "";

    for(size_t y = 0; y < 32; y++) {
      for(size_t x = 0; x < 64; x++) {
        if(data.display.get(x, y))
          surface += "##";
        else
          surface += "  ";
      }
      surface += '\n';
    }
  }

  void communicate() {
    logger::log(surface);
  }
};

#endif
