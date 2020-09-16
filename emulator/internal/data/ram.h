#ifndef RAM_H
#define RAM_H

#include <cassert>
#include <cstdint>
#include <iostream>
#include <fstream>
#include "./register.h"
#include "../util/text.h"
using namespace text;
// byte ram[4096]

class Ram {
  uint8_t __arr[4096] = {};

public:
  uint16_t font_sprite_addrs[16] = {0};

  uint8_t& operator[](std::size_t ix) { return __arr[ix]; }
  const uint8_t& operator[](std::size_t ix) const { return __arr[ix]; }

  Ram() {
    load_font();
  }

  bool load_rom(std::string fname) {
    std::cout << "loading:" << fname << std::endl;

    std::ifstream f(fname);
    std::string line;

    if(!f.good() || !f.is_open()) {
      std::cout << "COULD NOT LOAD ROM" << std::endl;
      return false;
    }

    for(size_t i = 0x200; std::getline(f, line), i<0x1000; i+=2) {
      std::string not_ignored = clean_str(line);
      if(not_ignored.length() == 0)
        continue;
      else if(not_ignored.length() != 4)
        assert(false);

      std::cout << "load: " << not_ignored << std::endl;
      __arr[i] = hex_to_uint8(not_ignored.substr(0,2));
      __arr[i+1] = hex_to_uint8(not_ignored.substr(2,4));



      std::cout << "\thex: "
          << u8_to_hex(__arr[i]) << u8_to_hex(__arr[i+1]) << std::endl;

      uint16_t hex = get_instr(i);
      std::cout << "\thex2: "
          << u16_to_hex(hex) << std::endl;
    }
    return true;
  }

  uint16_t get_instr(uint16_t pc) {
    uint16_t instr = __arr[pc];
    instr <<= 8;
    instr += __arr[pc+1];
    return instr;
  }

  void load_font() {
    uint8_t font[16*5] = {
    //0
      0xF0,
      0x90,
      0x90,
      0x90,
      0xF0,
    //1
      0x20,
      0x60,
      0x20,
      0x20,
      0x70,
    //2
      0xF0,
      0x10,
      0xF0,
      0x80,
      0xF0,
    //3
      0xF0,
      0x10,
      0xF0,
      0x10,
      0xF0,
    //4
      0x90,
      0x90,
      0xF0,
      0x10,
      0x10,
    //5
      0xF0,
      0x80,
      0xF0,
      0x10,
      0xF0,
    //6
      0xF0,
      0x80,
      0xF0,
      0x90,
      0xF0,
    //7
      0xF0,
      0x10,
      0x20,
      0x40,
      0x40,
    //8
      0xF0,
      0x90,
      0xF0,
      0x90,
      0xF0,
    //9
      0xF0,
      0x90,
      0xF0,
      0x10,
      0xF0,
    //A
      0xF0,
      0x90,
      0xF0,
      0x90,
      0x90,
    //B
      0xE0,
      0x90,
      0xE0,
      0x90,
      0xE0,
    //C
      0xF0,
      0x80,
      0x80,
      0x80,
      0xF0,
    //D
      0xE0,
      0x90,
      0x90,
      0x90,
      0xE0,
    //E
      0xF0,
      0x80,
      0xF0,
      0x80,
      0xF0,
    //F
      0xF0,
      0x80,
      0xF0,
      0x80,
      0x80
    };

    for(size_t i = 0; i < 16*5; i++) {
      __arr[0x000+i] = font[i];
    }
    for(size_t i = 0; i < 16; i++) {
      font_sprite_addrs[i] = 0x000 + i*5;
    }
  }
};

#endif
