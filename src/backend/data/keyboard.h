#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <cstdint>
#include <cassert>

class Keyboard {
public:
  bool state[16] = {}; // 0-9, A-F
  bool curr[16] = {}; // 0-9, A-F
  bool last[16] = {}; // 0-9, A-F
  Keyboard() {}

  bool get_curr(uint8_t ix) {
    if(ix >= 16) {
      assert(false); // TODO: better error system
    }
    return curr[ix];
  }

  bool get_last(uint8_t ix) {
    if(ix >= 16) {
      assert(false); // TODO: better error system
    }
    return last[ix];
  }

  void set_state(bool *next) {
    for(size_t i = 0; i < 16; i++) {
      state[i] = next[i];
    }
  }

  void tick() {
    for(size_t i = 0; i < 16; i++) {
      last[i] = curr[i];
      curr[i] = state[i];
    }
  }
};

#endif
