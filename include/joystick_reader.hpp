#pragma once

#include <functional>
#include <set>
#include <string>

void start_joystick_loop(std::function<void(const std::set<std::string> &)> on_buttons_changed);
std::string button_to_name(int button_number);