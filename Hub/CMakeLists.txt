project(Hub)

file(GLOB_RECURSE HUB_SRC src/*.cpp)

add_executable(sensorsystem-hub ${HUB_SRC})
target_link_libraries(sensorsystem-hub PRIVATE sensorsystem-networking ${CURSES_LIBRARIES} ${CURL_LIBRARY} Threads::Threads stdc++fs)
target_include_directories(sensorsystem-hub PRIVATE include ${CURSES_INCLUDE_DIR} ${CURL_INCLUDE_DIR})

install(TARGETS sensorsystem-hub DESTINATION bin COMPONENT Hub)

if(INSTALL_DEFAULT_CONFIG)
	install(FILES data/sensorsystem-hub.ini DESTINATION /etc COMPONENT Hub
endif()

add_custom_target(Hub-install
    DEPENDS Networking-install
    COMMAND
        ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=Hub
        -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
    )
