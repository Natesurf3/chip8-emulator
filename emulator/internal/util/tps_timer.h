#ifndef TPS_TIMER_H
#define TPS_TIMER_H

#include <chrono>

// TPS stands for 'ticks per second'
// closely related to FPS

namespace tps_timer {
  using namespace std::chrono;
  using clock = steady_clock;
  using time = steady_clock::time_point;
  using seconds = duration<double>;

  class TPSTimer {
  public:
    clock::duration tick_duration;
    time start;
    time last_tick;
    double dt;

    TPSTimer(double dt) {
      tick_duration = duration_cast<clock::duration>(seconds(dt));
      start = clock::now();
      last_tick = start;
      this->dt = dt;
    }

    void delay_tick() {
      last_tick += tick_duration;
      std::this_thread::sleep_until(last_tick);
    }

    double runtime() {
      return duration_cast<seconds>(clock::now()-start).count();
    }
  };
}
#endif
