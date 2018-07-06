project(Hub)

add_executable(sensorsystem-hub)
target_link_libraries(sensorsystem-hub sensorsystem-networking)
target_include_directories(${CMAKE_SOURCE_DIR}/Hub/include)

add_subdirectory(src)

install(TARGETS sensorsystem-hub DESTINATION bin COMPONENT Hub)

add_custom_target(Hub-install
    DEPENDS Networking-install
    COMMAND
        ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=Hub
        -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
    )