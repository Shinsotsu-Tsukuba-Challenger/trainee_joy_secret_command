#include "joystick_reader.hpp"

#include <fcntl.h>
#include <linux/joystick.h>
#include <unistd.h>

#include <iostream>
#include <map>

extern std::string joystick_device_path;

std::string button_to_name(int button_number)
{
  static std::map<int, std::string> button_map = {{0, "A"},    {1, "B"},     {2, "X"},
                                                  {3, "Y"},    {4, "L"},     {5, "R"},
                                                  {6, "BACK"}, {7, "START"}, {8, "Logicool"}};
  auto it = button_map.find(button_number);
  if (it != button_map.end()) {
    return it->second;
  } else {
    std::string unknown = "UNKNOWN(" + std::to_string(button_number) + ")";
    std::cerr << "[WARN] Unmapped button number: " << button_number << std::endl;
    return unknown;
  }
}

void start_joystick_loop(std::function<void(const std::set<std::string> &)> on_buttons_changed)
{
  int fd = open(joystick_device_path.c_str(), O_RDONLY | O_NONBLOCK);
  if (fd < 0) {
    std::cerr << "Failed to open joystick device: " << joystick_device_path << std::endl;
    return;
  }

  js_event js;
  std::set<std::string> pressed_buttons;

  while (true) {
    ssize_t bytes = read(fd, &js, sizeof(js));
    if (bytes == sizeof(js_event)) {
      js.type &= ~JS_EVENT_INIT;

      if (js.type == JS_EVENT_BUTTON) {
        std::string name = button_to_name(js.number);

        if (js.value)
          pressed_buttons.insert(name);
        else
          pressed_buttons.erase(name);

        on_buttons_changed(pressed_buttons);
      }
    }
    usleep(1000);
  }

  close(fd);
}