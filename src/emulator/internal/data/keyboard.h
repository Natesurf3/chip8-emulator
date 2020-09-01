#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard {
public:
  bool curr[16] = {}; // 0-9, A-F
  bool last[16] = {}; // 0-9, A-F

  void push_back(bool *next) {
    for(size_t i = 0; i < 16; i++) {
      last[i] = curr[i];
      curr[i] = next[i];
    }
  }

  Keyboard() {}
};

#endif
