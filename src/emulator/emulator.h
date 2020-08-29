#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <chrono>
#include <thread>

namespace emulator {
  using namespace std::chrono;

  using clock = steady_clock;
  using time = steady_clock::time_point;
  using seconds = duration<double>;

  class Emulator {

  public:
    Emulator() {
    }

    void run() {
      std::cout << "Start of Emulator" << std::endl;
      time start = clock::now();

      time tick_time = start;
      clock::duration tick_duration = \
          duration_cast<clock::duration>(seconds(1.0/100.0));

      int tick_iter = 0;
      while(true) {
        std::cout << "Start Tick " << tick_iter << std::endl;

        //---------- emulator tick internal --------------
        //do stuff
        //------------------- end ------------------------

        tick_time += tick_duration;
        std::this_thread::sleep_until(tick_time);
        tick_iter++;
      }

      time stop = clock::now();
      clock::duration runtime = stop-start;
      std::cout << "Emulator closed" << std::endl;
      std::cout << "Runtime: " << runtime.count() << " seconds." << std::endl;
    }
  };
}
#endif
