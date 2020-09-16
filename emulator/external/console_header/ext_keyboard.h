#ifndef EXT_KEYBOARD_H
#define EXT_KEYBOARD_H
#include <iostream>
#include <ctypes>
#include "../internal/data/chip8_data.h"

class ExtKeyboard {
  bool keys[16] = {};

public:
  ExtKeyboard() {}

  void update(Chip8Data data) {
    data.keys.push_back(keys);
  }

  void communicate() {
    std::stdin.sync();

    char chs[1];
    int len = std::stdin.readsome(chs, 1);
    if(len != 0) {
      for(size_t i = 0; i < 16; i++) {
        keys[i] = false;
      }
      char c = chs[0];
      if(c >= '0' && c <= '9') {
        keys[c-'0'] = true;
      }
      if(c >= 'a' && c <= 'f') {
        keys[c-'a'] = true;
      }
    }
  }
};

#endif
