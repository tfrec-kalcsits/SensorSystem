project(SensorPi-tests)

add_executable(lcdtest lcdtest.cpp)
target_include_directories(lcdtest PRIVATE ../include)
set_target_properties(lcdtest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)