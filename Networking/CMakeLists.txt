project(Networking)

set(networking_src_dir ${CMAKE_SOURCE_DIR}/Networking/src)
add_library(sensorsystem-networking SHARED ${networking_src_dir}/rf24radioreceiver.cpp ${networking_src_dir}/rf24radiotransmitter.cpp)
target_link_libraries(sensorsystem-networking ${RF24})
target_include_directories(sensorsystem-networking PUBLIC ${networking_src_dir} PRIVATE ${RF24_include})

install(TARGETS sensorsystem-networking DESTINATION lib COMPONENT Networking)

add_custom_target(Networking-install
    COMMAND
    ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=Networking
    -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
    )
