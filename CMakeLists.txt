cmake_minimum_required(VERSION 3.10)
project(trainee_joy_secret_command)

set(CMAKE_CXX_STANDARD 17)
set(CONFIG_INSTALL_PATH share/${PROJECT_NAME})

find_package(yaml-cpp REQUIRED)

include_directories(include)

add_executable(trainee_joy_secret_command
    src/main.cpp
    src/joystick_reader.cpp
    src/yaml_loader.cpp
)

target_link_libraries(trainee_joy_secret_command yaml-cpp)

add_executable(joy_debug
    src/joy_debug.cpp
    src/joystick_reader.cpp
    src/yaml_loader.cpp
)

target_link_libraries(joy_debug yaml-cpp)

install(TARGETS trainee_joy_secret_command RUNTIME DESTINATION bin)
install(TARGETS joy_debug RUNTIME DESTINATION bin)
install(DIRECTORY config DESTINATION ${CONFIG_INSTALL_PATH})

install(PROGRAMS scripts/env_ros2 DESTINATION bin)