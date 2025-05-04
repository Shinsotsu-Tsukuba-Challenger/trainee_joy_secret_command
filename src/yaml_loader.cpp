#include "yaml_loader.hpp"

#include <yaml-cpp/yaml.h>

#include <fstream>
#include <iostream>

std::string joystick_device_path;
std::vector<SecretCommand> load_commands(const std::string & filepath)
{
  std::vector<SecretCommand> commands;

  try {
    YAML::Node config = YAML::LoadFile(filepath);
    if (config["device"]) {
      joystick_device_path = config["device"].as<std::string>();
    } else {
      joystick_device_path = "/dev/input/js0";
    }
    for (const auto & node : config["secret_commands"]) {
      SecretCommand cmd;
      cmd.name = node["name"].as<std::string>();
      cmd.combo = node["combo"].as<std::vector<std::string>>();
      cmd.action = node["action"].as<std::string>();
      commands.push_back(cmd);
    }
  } catch (const std::exception & e) {
    std::cerr << "Failed to load YAML: " << e.what() << std::endl;
  }

  return commands;
}