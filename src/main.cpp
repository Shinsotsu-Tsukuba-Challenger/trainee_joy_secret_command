#include "joystick_reader.hpp"
#include "yaml_loader.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>

int main()
{
  std::vector<std::string> search_paths = {
    "config/commands.yaml", "/usr/local/share/trainee_joy_secret_command/config/commands.yaml",
    "/usr/share/trainee_joy_secret_command/config/commands.yaml"};
  std::string config_path;
  for (const auto & path : search_paths) {
    std::ifstream file(path);
    if (file.good()) {
      config_path = path;
      break;
    }
  }
  if (config_path.empty()) {
    std::cerr << "Could not find commands.yaml in standard locations." << std::endl;
    return 1;
  }
  std::cout << "[INFO] Using config file: " << config_path << std::endl;
  auto commands = load_commands(config_path);

  std::cout << "Waiting for secret combo..." << std::endl;

  start_joystick_loop([&](const std::set<std::string> & pressed) {
    for (const auto & cmd : commands) {
      std::set<std::string> combo_set(cmd.combo.begin(), cmd.combo.end());
      if (pressed == combo_set) {
        std::cout << "Command triggered: " << cmd.name << std::endl;
        system(cmd.action.c_str());
      }
    }
  });

  return 0;
}
