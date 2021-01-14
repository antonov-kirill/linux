cmake_minimum_required (VERSION 3.0)
project(UDP_CAN VERSION 1.0.0 LANGUAGES C CXX)
message("CMakeLists.txt version: 1.0.5")

set(OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_subdirectory(UDP_CAN)
