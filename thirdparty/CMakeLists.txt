#Find all the third party libraries
find_library(RF24 rf24)
find_library(wiringPi wiringPi)
find_library(wiringPiDev wiringPiDev)
find_file(tsl2561 NAMES tsl2561.o PATHS ${THIRDPARTY_DIR}/tsl2561/src NO_DEFAULT_PATH)
message(${tsl2561})

#Set include paths
set(RF24_include ${THIRDPARTY_DIR}/RF24 PARENT_SCOPE)
set(wiringPi_include ${THIRDPARTY_DIR}/wiringPi/wiringPi PARENT_SCOPE)
set(wiringPiDev_include ${THIRDPARTY_DIR}/wiringPi/devLib PARENT_SCOPE)
set(tsl2561_include ${THIRDPARTY_DIR}/tsl2561/src PARENT_SCOPE)

