#include <iostream>

#include "./emulator.h"
using namespace emulator;

int main() {
  std::cout << (-5 % 2) << std::endl;
  Emulator em = Emulator();

  em.run();

  return 0;
}
