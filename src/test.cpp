#include <iostream>
#include <cstdint>

void test_data_types();

int main() {
  std::cout << "Hello, test world!" << std::endl;
  test_data_types();
  return 0;
}

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
#include "./emulator/internal/data/chip8_data.h"
void test_data_types() {
  Chip8Data data;

  Register &r = data.r;
  Ram &ram = data.ram;
  Display &display = data.display;
  Keyboard &keys = data.keys;


  //------- stack -------
  r.st = 4;
  r.stack[4] = 99;
  std::cout << "stack[4] = 99;  ";
  std::cout << "stack[4] = " << r.stack[4] << ";" << std::endl;

  //------- ram -------
  ram[50] = 123;
  std::cout << "ram[50] = " << ram[50] << std::endl;


  //------- keys -------
  bool next[16] = {
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
  };
  for(int i = 0; i < 16; i++) {
    keys.curr[i] = (i>8);
  }
  keys.push_back(next);

  for(int i = 0; i < 16; i++) {
    std::cout << keys.curr[i] << ", ";
  }
  std::cout << std::endl;
  for(int i = 0; i < 16; i++) {
    std::cout << keys.last[i] << ", ";
  }
  std::cout << std::endl << "};" << std::endl;

  //------- display -------
  std::cout << "(" << (display[42]) << " == " << 0 << ") = true" << std::endl;
}
