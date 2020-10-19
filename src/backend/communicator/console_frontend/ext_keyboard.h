#ifndef EXT_KEYBOARD_H
#define EXT_KEYBOARD_H
#include <iostream>
#include "../../data/chip8_data.h"
#include "../../util/logger.h"

class ExtKeyboard {
  bool is_key[16] = {};
  int key_timer[16] = {};


public:
  ExtKeyboard() {}

  void update(Chip8Data data) {
//    data.keys.push_back(is_key);
  }

  void communicate(double tick_rate) {
/** doesnt work
    int ticks = (int)(tick_rate/4);
    char c = getchar();

    if     (c >= '0' && c <= '9') key_timer[c-'0'] = ticks;
    else if(c >= 'a' && c <= 'f') key_timer[c-'a'] = ticks;
    else if(c >= 'A' && c <= 'F') key_timer[c-'A'] = ticks;


    for(size_t i = 0; i < 16; i++)
      if(is_key[i] = (key_timer[i]!=0))
        key_timer[i] -= 1;

    logger::log("\tkeys: ", 16, key_timer);
**/
  }
};

#endif
