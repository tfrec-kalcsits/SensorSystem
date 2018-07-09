project(SensorPi)

file(GLOB_RECURSE SENSOR_SRC src/*.cpp)

add_executable(sensorsystem-sensor ${SENSOR_SRC})
target_include_directories(sensorsystem-sensor PUBLIC include)
target_link_libraries(sensorsystem-sensor PRIVATE sensorsystem-networking sensorsystem-sensorcore ${wiringPi} ${wiringPiDev})
