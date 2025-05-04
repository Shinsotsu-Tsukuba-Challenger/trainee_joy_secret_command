#pragma once

#include <string>
#include <vector>

extern std::string joystick_device_path;

struct SecretCommand {
    std::string name;
    std::vector<std::string> combo;
    std::string action;
};

std::vector<SecretCommand> load_commands(const std::string& filepath);