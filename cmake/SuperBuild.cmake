include(ExternalProject)

set(DEPENDENCIES ep_wiringPi ep_wiringPiDevLib ep_tsl2561 ep_RF24)
set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/thirdparty)

ExternalProject_Add(ep_wiringPi
    SOURCE_DIR ${THIRDPARTY_DIR}/wiringPi/wiringPi
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND make -C ${THIRDPARTY_DIR}/wiringPi/wiringPi
    INSTALL_COMMAND ""
    )

ExternalProject_Add(ep_wiringPiDevLib
    DEPENDS ep_wiringPi
    SOURCE_DIR ${THIRDPARTY_DIR}/wiringPi/devLib
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND make -C ${THIRDPARTY_DIR}/wiringPi/devLib
    INSTALL_COMMAND ""
    )

ExternalProject_Add(ep_tsl2561
    SOURCE_DIR ${THIRDPARTY_DIR}/tsl2561/src
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND make -C ${THIRDPARTY_DIR}/tsl2561/src
    INSTALL_COMMAND ""
    )

ExternalProject_Add(ep_RF24
    SOURCE_DIR ${THIRDPARTY_DIR}/tsl2561/src
    CONFIGURE_COMMAND ${THIRDPARTY_DIR}/RF24/configure --driver=SPIDEV
    BUILD_IN_SOURCE 1
    BUILD_COMMAND make ${THIRDPARTY_DIR}/RF24
    INSTALL_COMMAND ""
    )

ExternalProject_Add(ep_SensorSystem
    DEPENDS ${DEPENDENCIES}
    SOURCE_DIR ${PROJECT_SOURCE_DIR}
    CMAKE_ARGS -DINSTALL_DEPENDENCIES=OFF
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}
    )