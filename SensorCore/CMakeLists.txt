project(SensorCore)

file(GLOB_RECURSE SENSORCORE_SRC src/*.cpp)
add_library(sensorsystem-sensorcore STATIC ${SENSORCORE_SRC} ${TSL2561_OBJECT})
target_include_directories(sensorsystem-sensorcore PRIVATE ${TSL2561_INCLUDE} PUBLIC src)
target_link_libraries(sensorsystem-sensorcore PRIVATE ${wiringPi})
