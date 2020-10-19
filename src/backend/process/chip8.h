#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <cassert>
#include "../data/chip8_data.h"
// chip8 types:
//  bit = 1 bit,
//  nibble = 4 bits,
//  byte = 8 bits,
//  pointer = 12 bits
//
// c++ representation:
//  bit -> uint6_t
//  nibble -> uint8_t,
//  byte -> uint8_t,
//  pointer -> uint16_t,
//
//  will just need to %0x1000000000000 and %0x10000

uint8_t B_MAX = 0x2;
uint8_t N_MAX = 0x10;
uint16_t BY_MAX = 0x100;
uint16_t P_MAX = 0x1000;

int shift_mode = 1;
int i_mode = 1;
int rand_mode = 1;

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

void process(int *cmd, Chip8Data &data) {
  int opcode = cmd[0];
  int x = cmd[1];
  int y = cmd[2];
  int z = cmd[3];

  Register &r = data.r;
  Ram &ram = data.ram;
  Display &display = data.display;
  Keyboard &keys = data.keys;


  switch(opcode) {
    case 2:
      for(size_t dx = 0; dx < 64; dx++) {
        for(size_t dy = 0; dy < 32; dy++) {
          display.set(dx, dy, 0);
        }
      }
    break;
    case 3:
      r.st = (r.st-1+N_MAX)%N_MAX;
      r.pc = r.stack[r.st]; //bug fixed
    break;
    case 4:
      r.pc = x-2;
    break;
    case 5:
      r.stack[r.st] = r.pc;
      r.st = (r.st+1)%N_MAX;
      r.pc = x-2;
    break;
    case 6:
      if(r[x] == y) r.pc = r.pc+2;
    break;
    case 7:
      if(r[x] != y) r.pc = r.pc+2;
    break;
    case 8:
      if(r[x] == r[y]) r.pc = r.pc+2;
    break;
    case 9:
      r[x] = y;
    break;
    case 10:
      r[x] = r[x]+y;
    break;
    case 11:
      r[x] = r[y];
    break;
    case 12:
      r[x] = r[x]|r[y];
    break;
    case 13:
      r[x] = r[x]&r[y];
    break;
    case 14:
      r[x] = r[x]^r[y];
    break;
    case 15: {
      uint16_t sum = r[x]; sum += r[y];
      r[0xF] = (sum >= BY_MAX);
      r[x] = (uint8_t)sum;
    }
    break;
    case 16:
      r[0xF] = (r[x] >= r[y]);
      r[x] = r[x]-r[y];
    break;
    case 17:
      if(shift_mode == 0) {
        r[0xF] = r[y] & 0x1;
        r[x] = (r[y] >> 1);
      }
      else {
        r[0xF] = r[x] & 0x1;
        r[x] = (r[x] >> 1);
      }
    break;
    case 18:
      r[0xF] = (r[y] >= r[x]);
      r[x] = r[y]-r[x];
    break;
    case 19:
      if(shift_mode == 0) {
        r[0xF] = (r[y] >> 7) & 0x1;
        r[x] = (r[y] << 1);
      }
      else {
        r[0xF] = (r[x] >> 7) & 0x1;
        r[x] = (r[x] << 1);
      }
    break;
    case 20:
      if(r[x] != r[y]) r.pc = r.pc+2;
    break;
    case 21:
      r.i = x;
    break;
    case 22:
      r.pc = x + r[0] - 2;
    break;
    case 23:
      if(rand_mode == 1) {
        uint8_t v;
        while( (v=r.rand()) >= y) {}
        r[x] = v;
      }
      else if(rand_mode == 0) {
        r[x] = y & r.rand();
      }
      else {
        assert(false);
      }
    break;
    case 24: {
      r[0xF] = 0;
      for(size_t dy = 0; dy < z; dy++) {
        uint8_t byte = ram[(r.i+dy)%P_MAX];

        for(size_t dx = 0; dx < 8; dx++) {
          bool bit = (byte>>(7-dx))&0b1;
          bool pixel = display.get(r[x]+dx, r[y]+dy);
          r[0xF] |= bit&pixel;
          display.set(r[x]+dx, r[y]+dy, bit^pixel);
        }
      }
    }
    break;
    case 25:
      if(keys.get_curr(r[x]) == true) {
        r.pc = r.pc+2;
      }
    break;
    case 26:
      if(keys.get_curr(r[x]) != true) {
        r.pc = r.pc+2;
      }
    break;
    case 27:
      r[x] = r.dtm;
    break;
    case 28: {
      for(size_t i = 0; i < 16; i++) {
        if(keys.get_curr(i) == true && keys.get_last(i) == false) {
          r[x] = i;
          r.pc += 2;
          break;
        }
      }
      r.pc -= 2;
    }
    break;
    case 29:
      r.dtm = r[x];
    break;
    case 30:
      r.stm = r[x];
    break;
    case 31:
      r.i = (r.i+r[x])%P_MAX;
    break;
    case 32:
      r.i = ram.get_font_sprite_addr(r[x]);
    break;
    case 33:
      ram[r.i+0] = (r[x]/100)%10;
      ram[r.i+1] = (r[x]/10)%10;
      ram[r.i+2] = (r[x]/1)%10;
    break;
    case 34:
      for(size_t i = 0; i <= x && i < 16; i++) {
        ram[r.i+i] = r[i];
      }
      if(i_mode == 0) r.i += x;
    break;
    case 35:
      for(size_t i = 0; i <= x && i < 16; i++) {
        r[i] = ram[r.i+i];
      }
      if(i_mode == 0) r.i += x;
    break;
    default:
      assert(false); // TODO: better error system
    break;
  }
}
#endif
