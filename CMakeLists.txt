cmake_minimum_required(VERSION 3.0.0)

option(INSTALL_DEPENDENCIES "Set on to install external dependencies located in thirdparty" ON)



#install external dependencies if required
if(INSTALL_DEPENDENCIES)
    project(SUPERBUILD NONE)
    include(cmake/SuperBuild.cmake)
    return()
else()
    project(SensorSystem)
endif()

#useful variables
set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/thirdparty)

#set output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#add component subdirectories
add_subdirectory(thirdparty)
add_subdirectory(Networking)
add_subdirectory(SensorCore)
add_subdirectory(SensorPi)
add_subdirectory(Hub)