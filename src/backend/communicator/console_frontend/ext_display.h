#ifndef EXT_DISPLAY_H
#define EXT_DISPLAY_H
#include <iostream>
#include <cstdint>
#include "../../data/chip8_data.h"
#include "../../util/logger.h"

class ExtDisplay {
  bool surfaces[16][32][64] = {};
  size_t i = 0;
  size_t length = 0;
  size_t size = 16;


public:
  ExtDisplay() {}

  void update(Chip8Data data) {
    i = (i+size-1)%size;

    if(length < size)
      length ++;

    for(size_t y = 0; y < 32; y++)
      for(size_t x = 0; x < 64; x++)
        surfaces[i][y][x] = data.display.get(x, y);
  }

  void communicate() {
    std::string combination = "";
    for(size_t y = 0; y < 32; y++) {
      for(size_t x = 0; x < 64; x ++) {
        bool px = false;
        for(int t = 0; t < length && t < size; t+= 5)
          px |= surfaces[(i+t)%size][y][x];

        if(px) combination += "##";
        else combination += "  ";
      }
      combination += "\n";
    }
    logger::log(combination);
  }
};

#endif
