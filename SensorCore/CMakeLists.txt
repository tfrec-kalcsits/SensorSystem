project(SensorCore)

file(GLOB_RECURSE SENSORCORE_SRC src/*.cpp)
add_library(sensorsystem-sensorcore STATIC ${SENSORCORE_SRC})
add_dependencies(sensorsystem-sensorcore wiringPi tsl2561)
target_include_directories(sensorsystem-sensorcore PRIVATE ${tsl2561_include} ${wiringPi_include} ${wiringPiDev_include} PUBLIC src)
target_link_libraries(sensorsystem-sensorcore PRIVATE ${wiringPi_lib})