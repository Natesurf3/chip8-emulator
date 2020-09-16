#ifndef REGISTER_H
#define REGISTER_H

#include <cstdint>
#include <random>
static std::random_device rd;


//  nibble r.st
//  byte r.dtm
//  byte r.stm
//  pointer r.i
//  pointer r.pc
//  pointer r.stack[16]

//  byte r[16]
//  byte r.rand()

class Register {
  double t_remainder = 0; // for timers
  uint8_t __arr[16] = {};

  std::mt19937 rng = std::mt19937(rd());
  std::uniform_int_distribution<uint8_t> rand_u8 = std::uniform_int_distribution<uint8_t>(0, 255);

public:
  uint8_t st = 0;
  uint8_t dtm = 0;
  uint8_t stm = 0;
  uint16_t i = 0;
  uint16_t pc = 0x200;
  uint16_t stack[16] = {};

  uint8_t& operator[](std::size_t ix) { return __arr[ix]; }
  const uint8_t& operator[](std::size_t ix) const { return __arr[ix]; }


  uint8_t rand() {
    return rand_u8(rng);
  }

  void tick(double dt) {
    t_remainder += dt;

    while(t_remainder >= 1) {
      t_remainder -= 1;
      if(dtm != 0) {
        dtm -= 1;
      }
      if(stm != 0) {
        stm -= 1;
      }
    }

    pc = (pc+2)%0x1000;

  }

  Register() {}
};

#endif
