#ifndef CHIP8_DATA_H
#define CHIP8_DATA_H

#include "./display.h"
#include "./keyboard.h"
#include "./ram.h"
#include "./register.h"

#include "../util/logger.h"

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

  void log() {
    int a[3] = {r.i, r.dtm, r.stm};
    logger::log("\tpc_ln: ", r.pc/2-255);
    logger::log("\t{r.i, r.dtm, r.stm}: ", 3, a);
    logger::log("\treg: ", 16, (uint8_t *)r.__arr);
  }
};

#endif
