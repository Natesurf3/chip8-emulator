#ifndef CHIP8_DATA_H
#define CHIP8_DATA_H

#include "./display.h"
#include "./keyboard.h"
#include "./ram.h"
#include "./register.h"

//  nibble r.st
//  byte r[16]
//  byte r.dtm
//  byte r.stm
//  byte r.rand()
//  pointer r.I
//  pointer r.pc
//  pointer r.stack[16]

//  byte ram[4096]

//  byte display[4*64] or bit display[32*64] ?

//  bit keys.curr[16]
//  bit keys.last[16]

// --conversions--
// chip8 types:
//  bit = 1 bit,
//  nibble = 4 bits,
//  byte = 8 bits,
//  pointer = 12 bits
//
// c++ representation:
//  bit -> uint8_t
//  nibble -> uint8_t,
//  byte -> uint8_t,
//  pointer -> uint16_t,
//
//  will just need to %0x1000000000000 and %0x10000


class Chip8Data {
public:
  Register r;
  Ram ram;
  Display display;
  Keyboard keys;

  void tick(double dt) {
    r.tick(dt);
  }

  Chip8Data() {};
};

#endif
