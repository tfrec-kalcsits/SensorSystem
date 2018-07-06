project(Networking)

set(networking_src_dir ${CMAKE_SOURCE_DIR}/Networking/src)
add_library(sensorsystem-networking SHARED ${CMAKE_SOURCE_DIR}/rf24radioreceiver.cpp ${CMAKE_SOURCE_DIR}/rf24radiotransmitter.cpp)
target_link_libraries(sensorsystem-networking ${RF24})
target_include_directories(sensorsystem-networking ${networking_src_dir})

install(TARGETS sensorsystem-networking ${RF24} DESTINATION lib COMPONENT Networking)

add_custom_target(Networking-install
    COMMAND
    ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=Networking
    -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
    )