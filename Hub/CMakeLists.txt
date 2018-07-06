project(Hub)

#find external packages for curl and ncurses

find_package(CURL REQUIRED)
find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

file(GLOB_RECURSE hub_src src/*.cpp)
add_executable(sensorsystem-hub ${hub_src})
target_link_libraries(sensorsystem-hub sensorsystem-networking ${CURL_LIBRARIES} ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} stdc++fs)
target_include_directories(sensorsystem-hub PRIVATE ${CMAKE_SOURCE_DIR}/Hub/include ${CURL_INCLUDE_DIRS} ${CURSES_INCLUDE_DIR})

install(TARGETS sensorsystem-hub DESTINATION bin COMPONENT Hub)

add_custom_target(Hub-install
    DEPENDS Networking-install
    COMMAND
        ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=Hub
        -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
    )
