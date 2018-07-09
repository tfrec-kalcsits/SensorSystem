project(Networking)

add_library(sensorsystem-networking SHARED src/rf24radioreceiver.cpp src/rf24radiotransmitter.cpp)
target_link_libraries(sensorsystem-networking PRIVATE ${RF24_LIB})
target_include_directories(sensorsystem-networking PUBLIC src ${RF24_INCLUDE})

install(TARGETS sensorsystem-networking DESTINATION lib COMPONENT Networking)

add_custom_target(Networking-install
    COMMAND
    ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=Networking
    -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
    )
