#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>
#include <string>
#include <cassert>

#include "../external/console_header/ext_display.h"

#include "./process/chip8.h"

#include "./process/hexpat.h"
#include "./util/logger.h"
#include "./util/text.h"
using namespace hexpat;
using namespace logger;
using namespace text;

namespace emulator {
  using namespace std::chrono;
  using clock = steady_clock;
  using time = steady_clock::time_point;
  using seconds = duration<double>;

  class Emulator {
  public:
    Emulator() {}

    void run() {
      log("Start of Emulator");
      Chip8Data data;
      HexList instr;
      ExtDisplay disp;

      assert(data.ram.load_rom("../resources/test_rom.txt"));

      double dt = 1.0/40.0;
      clock::duration tick_duration =
          duration_cast<clock::duration>(seconds(dt));
      time start = clock::now();
      time last_tick = start;

      for(int tick_n = 0; tick_n <=2000; tick_n++) {
        log("tick: ", tick_n);

        //---------- emulator tick internal --------------
        uint16_t hex = data.ram.get_instr(data.r.pc);
        int cmnd[4];
        bool match = instr.try_match(cmnd, hex);
        if(true){
          std::cout << "\tpc_ln: " << (data.r.pc/2-255) << std::endl;
          std::cout << "\thex: " << u16_to_hex(hex) << std::endl;
          std::cout << "\t{r.i, r.dtm, r.stm}: {"
                    << (int)data.r.i << ", "
                    << (int)data.r.dtm << ", "
                    << (int)data.r.stm
                    << "}" << std::endl;

          std::cout << "\tcmnd: {";
          for(size_t i = 0; i < 4; i ++) {
            std::cout << cmnd[i];
            if(i != 3) std::cout << ", ";
          }
          std::cout << "}" << std::endl;
          std::cout << "\treg: {";
          for(size_t i = 0; i < 16; i ++) {
            std::cout << std::to_string((int)data.r[i]);
            if(i != 15) std::cout << ", ";
          }
          std::cout << "}" << std::endl;
        }

        if(match) process(cmnd, data);
        else std::cout << "\tinstruction not processable" << std::endl;



        data.tick(dt);

        disp.update(data);
        disp.communicate();
        //------------------- end ------------------------
        last_tick += tick_duration;
        std::this_thread::sleep_until(last_tick);
      }

      time stop = clock::now();
      double runtime = duration_cast<seconds>(stop-start).count();
      std::cout << "Emulator closed" << std::endl;
      std::cout << "Runtime: " << runtime << " seconds." << std::endl;
    }
  };
}
#endif
