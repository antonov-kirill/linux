# CMakeList.txt : CMake project for CMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.0)
project(UDP_CAN VERSION 1.0.0 LANGUAGES C CXX)
message("CMakeLists.txt version: 1.0.0")

# Add source to this project's executable.
add_executable (UDP_CAN "main.cpp")

# TODO: Add tests and install targets if needed.

install(TARGETS UDP_CAN DESTINATION ../bin)