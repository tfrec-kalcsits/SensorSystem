project(Networking)

add_library(sensorsystem-networking SHARED src/rf24radioreceiver.cpp src/rf24radiotransmitter.cpp)
add_dependencies(sensorsystem-networking RF24)
target_link_libraries(sensorsystem-networking ${RF24_lib})
target_include_directories(sensorsystem-networking PUBLIC src PRIVATE ${RF24_include})

install(TARGETS sensorsystem-networking DESTINATION lib COMPONENT Networking)

add_custom_target(Networking-install
    COMMAND
    ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=Networking
    -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
    )