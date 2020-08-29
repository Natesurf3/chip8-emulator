#include <iostream>

#include "./emulator/emulator.h"
using namespace emulator;

int main() {
  Emulator em = Emulator();

  em.run();

  return 0;
}
