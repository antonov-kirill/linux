cmake_minimum_required (VERSION 3.0)
message("OUTPUT_DIRECTORY: " ${OUTPUT_DIRECTORY})

file(GLOB CPPS "*.cpp")

add_executable (${PROJECT_NAME} ${CPPS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/UDP_CAN/inc ${CMAKE_SOURCE_DIR}/UDP_CAN/pugixml)

add_subdirectory(pugixml)
target_link_libraries(${PROJECT_NAME} PUGIXML)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
