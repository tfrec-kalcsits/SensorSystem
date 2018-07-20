project(SensorSystem)
cmake_minimum_required(VERSION 3.7)

#Max CXX standard in Version 3.7 is 14
set(CMAKE_CXX_STANDARD 14)

#set output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#Build dependencies
include(cmake/systemdependencies.cmake)

#add component subdirectories
add_subdirectory(thirdparty)
add_subdirectory(Networking)
add_subdirectory(SensorCore)
add_subdirectory(Hub)
