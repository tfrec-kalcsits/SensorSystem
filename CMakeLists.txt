#####################################################################################################################################
# CMAKE FILE FOR SensorSystem Networking library
# VERSION 0.1 Currently only supports compilation for arduino uno devices.
# Raspberry Pi and other Arduino support will be added soon.
#####################################################################################################################################

cmake_minimum_required(VERSION 3.5)
#The toolchain will be set to a custom arduino toolchain
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/cmake/ArduinoToolchain.cmake)
include(ExternalProject)

project(SensorSystem-Networking)

set(ARDUINO_PATH ${CMAKE_CURRENT_LIST_DIR}/thirdparty/arduinoCore-avr)
set(RF24_PATH ${CMAKE_CURRENT_LIST_DIR}/thirdparty/RF24)

#Find the source files for Arduino
file(GLOB_RECURSE ARDUINO_CORE_SRC
    ${ARDUINO_PATH}/cores/arduino/*.c
    ${ARDUINO_PATH}/cores/arduino/*.cpp
)

#RF24 requires SPI.h
set(SPI_PATH ${ARDUINO_PATH}/libraries/SPI/src)
set(SPI_SRC ${SPI_PATH}/SPI.cpp)

#source files for RF24
set(RF24_SRC ${RF24_PATH}/RF24.cpp)

#source files for SensorSystem-Networking
file(GLOB_RECURSE NETWORK_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp    
)

#start generating the static library
add_library(sensornetwork-networking STATIC
    ${ARDUINO_CORE_SRC}
    ${RF24_SRC}
    ${NETWORK_SOURCE}
    ${SPI_SRC}
)

target_include_directories(sensornetwork-networking
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src
        ${SPI_PATH}
    PUBLIC ${ARDUINO_PATH}/cores/arduino
        ${ARDUINO_PATH}/variants/standard
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${RF24_PATH}
)

target_compile_options(sensornetwork-networking PUBLIC
    -Os
    -mmcu=atmega328p
    -DF_CPU=16000000L
    -DARDUINO=10805
    -DARDUINO_AVR_UNO
    -DARDUINO_ARCH_AVR
    -std=c++11
)
