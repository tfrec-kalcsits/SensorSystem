#Find all the third party libraries
find_library(RF24 NAMES rf24 PATHS ${THIRDPARTY_DIR}/RF24 NO_DEFAULT_PATH)
find_library(wiringPi NAMES wiringPi PATHS ${THIRDPARTY_DIR}/wiringPi/wiringPi NO_DEFAULT_PATH)
find_library(wiringPiDev NAMES wiringPiDev PATHS ${THIRDPARTY_DIR}/wiringPi/devLib NO_DEFAULT_PATH)
find_file(tsl2561 NAMES tsl2561.o PATHS ${THIRDPARTY_DIR}/tsl2561/src NO_DEFAULT_PATH)

#add necessary include paths
target_include_directories(${RF24} INTERFACE ${THIRDPARTY_DIR}/RF24)
target_include_directories(${wiringPi} INTERFACE ${THIRDPARTY_DIR}/wiringPi/wiringPi)
target_include_directories(${wiringPiDev} INTERFACE ${THIRDPARTY_DIR}/wiringPi/devLib)
set(tsl2561_include PATH ${THIRDPARTY_DIR}/tsl2561/src PARENT_SCOPE)