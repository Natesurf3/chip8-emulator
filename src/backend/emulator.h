#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <thread>
#include <cstdint>
#include <string>
#include <cassert>

#include "./communicator/console_frontend/ext_keyboard.h"
#include "./communicator/console_frontend/ext_display.h"
#include "./process/chip8.h"

#include "./process/hexpat.h"
#include "./util/logger.h"
#include "./util/text.h"
#include "./util/tps_timer.h"
using namespace hexpat;
using namespace logger;
using namespace text;
using namespace tps_timer;

namespace emulator {
  static double tick_rate = 200;

  class Emulator {
  public:
    Emulator() {}

    void run() {
      Chip8Data data;
      HexList instr;
      ExtDisplay disp;
      ExtKeyboard keyb;
      TPSTimer tps = TPSTimer(1.0/tick_rate);

      //assert(data.ram.load_rom_binary("../resources/custom_rom/test_rom.ch8"));
      assert(data.ram.load_rom_binary("../../rom/curated_rom/PONG"));

      for(int tick_n = 0; tick_n <= 99999; tick_n++) {
        log("tick: ", tick_n);

        //---------- emulator tick internal --------------
        // grab instruction
        int cmnd[4];
        bool match = instr.try_match(cmnd, data.ram.get_instr(data.r.pc));
        //log
        data.log();
        log("\tcmnd: ", 4, cmnd);
        //execute instruction
        if(match) process(cmnd, data);
        else log("\tinstruction not processable");
        //tick
        data.tick(tps.dt);
        //------------------- end ------------------------
        disp.update(data);
        disp.communicate();
        //keyb.update(data);
        //keyb.communicate(tick_rate);
        flush_log();
        tps.delay_tick();
      }

      log("Emulator closed");
      log("Runtime: " + std::to_string(tps.runtime()) + " seconds.");
    }
  };
}
#endif
