#ifndef RAM_H
#define RAM_H

#include <cassert>
#include <cstdint>
#include <iostream>
#include <fstream>
#include "./register.h"

#include "../util/text.h"
#include "../util/logger.h"
using namespace text;
using namespace logger;

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
    log("loading:" + fname);

    std::ifstream f(fname);
    std::string line;

    if(!f.good() || !f.is_open()) {
      log("COULD NOT LOAD ROM");
      return false;
    }

    for(size_t i = 0x200; std::getline(f, line), i<0x1000; i+=2) {
      std::string not_ignored = clean_str(line);
      if(not_ignored.length() == 0)
        continue;
      else if(not_ignored.length() != 4)
        assert(false);

      __arr[i] = hex_to_uint8(not_ignored.substr(0,2));
      __arr[i+1] = hex_to_uint8(not_ignored.substr(2,4));

      log("load: " + not_ignored + " == " + u16_to_hex(get_instr(i)));
    }
    return true;
  }

  bool load_rom_binary(std::string fname) {
    log("loading binary:" + fname);
    std::ifstream f(fname, std::ifstream::binary);
    char next[1];

    if(!f.good() || !f.is_open()) {
      log("COULD NOT LOAD ROM");
      return false;
    }

    for(size_t i = 0x200; f.read(next, 1) && i<0x1000; i++) {
      __arr[i] = (uint8_t)next[0];
      log("load bin: " + std::to_string((int)__arr[i]) + " == " + u16_to_hex(get_instr(i)));
    }
    return true;
  }

  uint16_t get_instr(uint16_t pc) {
    return (__arr[pc]<<8) + __arr[pc+1];
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
