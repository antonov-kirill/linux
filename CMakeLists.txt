# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.7.2)

project ("UDP_CAN")

# Include sub-projects.
add_subdirectory ("UDP_CAN")

install(TARGETS UDP_CAN DESTINATION bin)
