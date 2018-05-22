#This is a patch file for the arduino core to compile it into a static lib using ExternalProject_Add
cmake_minimum_required(VERSION 3.5)
set(CMAKE_TOOLCHAIN_FILE ${MASTER_TOOLCHAIN_PATH})

project(ArduinoCore)

set(core_path ${CMAKE_CURRENT_LIST_DIR}/cores/arduino)
set(variant_path ${CMAKE_CURRENT_LIST_DIR}/variants/standard)
set(MCU atmega328p)
set(CPU_SPEED 16000000L)

file(GLOB_RECURSE ARDUINO_SRC
    ${core_path}/*.c
    ${core_path}/*.cpp
)

add_library(ArduinoCore STATIC ${ARDUINO_SRC})

target_compile_options(ArduinoCore PRIVATE
    -mmcu=${MCU}
    -DF_CPU=${CPU_SPEED}
    -Os
    -Wall
)

target_include_directories(ArduinoCore
    PRIVATE ${variant_path}
    PUBLIC ${core_path}
)