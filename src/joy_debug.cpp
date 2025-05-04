#include "joystick_reader.hpp"

#include <iostream>
#include <set>

int main()
{
  std::cout << "[joy_debug] Listening to joystick buttons..." << std::endl;

  start_joystick_loop([](const std::set<std::string> & pressed) {
    std::cout << "Pressed buttons: ";
    for (const auto & btn : pressed) {
      std::cout << btn << " ";
    }
    std::cout << std::endl;
  });

  return 0;
}