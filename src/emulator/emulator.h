#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>

#include "./internal/cpu/hexpat.h"
using namespace hexpat;

namespace emulator {
  using namespace std::chrono;

  using clock = steady_clock;
  using time = steady_clock::time_point;
  using seconds = duration<double>;

  class Emulator {
    InstructionSet instr_set = InstructionSet();

    uint16_t fake_rom[16] = {
      0x22EF, 0xBFBD,
      0x6B0C, 0x6C3F,

      0x6D0C, 0xEFBF,
      0xBDEF, 0xBFBD,

      0xDAB6, 0xEFBF,
      0xBDEF, 0xBFBD,

      0x6E00, 0x22EF,
      0xBFBD, 0x6603,
    };

  public:
    Emulator() {
    }

    void run() {
      std::cout << "Start of Emulator" << std::endl;
      time start = clock::now();

      time tick_time = start;
      clock::duration tick_duration = \
          duration_cast<clock::duration>(seconds(1.0/100.0));

      int tick_n = 0;
      while(true) {
        std::cout << "Start Tick " << tick_n << std::endl;

        //---------- emulator tick internal --------------
        uint16_t instruction = fake_rom[tick_n%16];
        int ret[4];
        bool match = instr_set.try_match(ret, instruction);

        std::cout << "\t[";
        for(int i = 0; i < 4; i++)
          std::cout << ret[i] << ",";
        std::cout << "] " << match << std::endl;


        //------------------- end ------------------------

        tick_time += tick_duration;
        std::this_thread::sleep_until(tick_time);
        tick_n++;

        if(tick_n == 32) {
          break;
        }
      }

      time stop = clock::now();
      double runtime = duration_cast<seconds>(stop-start).count();
      std::cout << "Emulator closed" << std::endl;
      std::cout << "Runtime: " << runtime << " seconds." << std::endl;
    }
  };
}
#endif
