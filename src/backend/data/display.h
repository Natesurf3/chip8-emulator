#ifndef DISPLAY_H
#define DISPLAY_H
#include <cstdint>


class Display {
// buffer
  bool is_buffer = true;
  bool buffers[16][32][64] = {};
  size_t i = 0;
  size_t length = 0;
  size_t size = 16;
  int combination[32][64] = {};
  bool buffered_display[32][64] {};

// display
  bool __arr[32][64] = {}; // [height][width]

public:
  Display() {}

  bool get(size_t x, size_t y) {
    x %= 64; //if(x >= 64) x = 63;
    y %= 64; //if(y >= 32) y = 31;
    return __arr[y][x];
  }

  void set(size_t x, size_t y, bool value) {
    x %= 64; //if(x >= 64) x = 63;
    y %= 64; //if(y >= 32) y = 31;
      __arr[y][x] = value;
  }

  void tick() {
    if(is_buffer) {
      i = (i+size-1)%size;

      if(length < size)
        length ++;

      for(size_t y = 0; y < 32; y++) {
        for(size_t x = 0; x < 64; x++) {
          buffers[i][y][x] = __arr[y][x];
          combination[y][x] += (int)__arr[y][x];
        }
      }

      if(length == size) {
        size_t start = (i+15)%size;
        for(size_t y = 0; y < 32; y++)
          for(size_t x = 0; x < 64; x++)
            if(buffers[start][y][x])
              combination[y][x] --;
      }
    }
  }

  bool *get_display() {
    if(is_buffer) {
      for(size_t y = 0; y < 32; y++) {
        for(size_t x = 0; x < 64; x++) {
          buffered_display[y][x] = (combination[y][x] != 0);
        }
      }
      return (bool *)buffered_display;
    }
    else {
      return (bool *)__arr;
    }

  }
};
#endif
