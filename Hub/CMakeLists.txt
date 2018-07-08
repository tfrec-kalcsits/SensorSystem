project(Hub)

#Find CURL and NCurses, both needed by sensorsystem-hub
set(CURSES_USE_NCURSES TRUE)
find_package(CURL REQUIRED)
find_package(Curses REQUIRED)

file(GLOB_RECURSE HUB_SRC src/*.cpp)

add_executable(sensorsystem-hub ${HUB_SRC})
target_link_libraries(sensorsystem-hub PRIVATE sensorsystem-networking ${CURSES_LIBRARIES})
target_include_directories(sensorsystem-hub PRIVATE include ${CURSES_INCLUDE_DIR})

install(TARGETS sensorsystem-hub DESTINATION bin COMPONENT Hub)

add_custom_target(Hub-install
    DEPENDS Networking-install
    COMMAND
        ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=Hub
        -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
    )