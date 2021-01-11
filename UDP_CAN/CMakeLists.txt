cmake_minimum_required (VERSION 3.0)
message("OUTPUT_DIRECTORY: " ${OUTPUT_DIRECTORY})

file(GLOB CPPS "*.cpp")

add_executable (${PROJECT_NAME} ${CPPS})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
