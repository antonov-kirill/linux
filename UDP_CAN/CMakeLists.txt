cmake_minimum_required (VERSION 3.0)
message("OUTPUT_DIRECTORY: " ${OUTPUT_DIRECTORY})

file(GLOB CPPS "*.cpp")

add_executable (${PROJECT_NAME} ${CPPS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/UDP_CAN/inc ${CMAKE_SOURCE_DIR}/UDP_CAN/pugixml)

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/UDP_CAN/pugixml/libpugixml.a)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

add_custom_command(	TARGET ${PROJECT_NAME} 
					POST_BUILD
					COMMENT "Post-build copying config.xml..."
					COMMAND echo "salam")
					#${CMAKE_COMMAND} -E 
					#copy ${CMAKE_CURRENT_SOURCE_DIR}/UDP_CAN/config.xml ${OUTPUT_DIRECTORY})
