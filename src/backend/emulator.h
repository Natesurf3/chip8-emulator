#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <thread>
#include <cstdint>
#include <string>
#include <cassert>

#include "./communicator/console_frontend/ext_keyboard.h"
#include "./communicator/console_frontend/ext_display.h"
#include "./communicator/communicator.h"

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
  double tick_rate = 600;
  double msg_rate = 20;

  int mode = 0;
  int tick_n = 0;

  Chip8Data data;
  HexList instr;

  Communicator com;
  double send_carry = 0;

  class Emulator {
  public:
    Emulator() {}

    void frame_tick() {
      // grab instruction
      int cmnd[4];
      bool match = instr.try_match(cmnd, data.ram.get_instr(data.r.pc));

      //log
      log("tick: ", tick_n);
      data.log();
      log("\tcmnd: ", 4, cmnd);

      //execute instruction
      if(match) process(cmnd, data);
      else log("\tinstruction not processable");
      data.tick(1.0/tick_rate);
      tick_n += 1;
    }

    void run() {
      //assert(data.ram.load_rom_binary("../resources/custom_rom/test_rom.ch8"));

      while(true) {
        send_carry += msg_rate / tick_rate;
        if(send_carry >= 1) {
          send_carry -= 1;

          InMessage in = com.recv();
          OutMessage out = OutMessage();

          if(in.is_state) {
            if(in.state == "start") {
              mode = 1;
              assert(data.ram.load_rom_binary(in.start_path));
            }
            if(in.state == "stop") {
              mode = 0;
              data.reset();
              log("Emulator closed");
            }
          }
          if(in.is_frame) {
            out.set_frame(false, data.display.get_display(), (data.r.stm != 0));
            data.keys.set_state(in.keystate);
            data.keys.tick();
          }
          com.send(out);
          flush_log();
        }
        if(mode == 1) {
          frame_tick();
        }
        else if(mode == 0) {
          // wait for mode == 1
        }
      }

      //log("Runtime: " + std::to_string(tps.runtime()) + " seconds.");
    }
  };
}
#endif
