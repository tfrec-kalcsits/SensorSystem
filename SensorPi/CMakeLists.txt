project(SensorPi)

file(GLOB_RECURSE SENSOR_SRC src/*.cpp)

add_executable(sensorsystem-sensor ${SENSOR_SRC})
add_dependencies(sensorsystem-sensor wiringPi wiringPiDev)
target_include_directories(sensorsystem-sensor PUBLIC include PRIVATE ${wiringPi_include} ${wiringPiDev_include})
target_link_libraries(sensorsystem-sensor PRIVATE sensorsystem-sensorcore ${wiringPi_lib} ${wiringPiDev_lib})