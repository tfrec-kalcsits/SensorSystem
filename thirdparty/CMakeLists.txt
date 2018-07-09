<<<<<<< HEAD
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
=======
project(thirdparty)

#build RF24 lib at configure time
message("building dependency RF24")
execute_process(COMMAND make -C ${CMAKE_CURRENT_LIST_DIR}/RF24)
#set variables to be used by program
set(RF24_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/RF24" PARENT_SCOPE)
set(RF24_LIB ${CMAKE_CURRENT_LIST_DIR}/RF24/librf24.so.1.3.1 PARENT_SCOPE})


#build tsl2561
message("building dependency tsl2561")
execute_process(COMMAND make -C ${CMAKE_CURRENT_LIST_DIR}/tsl2561/src)
#set variables for object file and include directory
set(TSL2561_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/tsl2561/src/ PARENT_SCOPE)
set(TSL2561_OBJECT ${CMAKE_CURRENT_LIST_DIR}/tsl2561/src/tsl2561.o PARENT_SCOPE)

#install rules
install(FILES ${RF24_lib} DESTINATION lib})



>>>>>>> 59d37b81b583b56235018f53d3bd5c60c3fe58d3

