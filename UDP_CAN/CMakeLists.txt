cmake_minimum_required (VERSION 3.0)

add_executable (UDP_CAN "main.cpp")
install(TARGETS UDP_CAN RUNTIME DESTINATION ${CMAKE_ROOT})