project(SensorPi)

file(GLOB_RECURSE SENSORPI_SRC src/*.cpp)
add_executable(sensorsystem-sensor ${SENSORPI_SRC})
target_include_directories(sensorsystem-sensor PRIVATE include)
target_link_libraries(sensorsystem-sensor sensorsystem-networking sensorsystem-sensorcore ${wiringPi} ${wiringPiDev})

install(TARGETS sensorsystem-sensor DESTINATION bin COMPONENT Sensor)
install(FILES data/sensorsystem-sensor.ini DESTINATION /etc/sensorsystem-sensor.ini COMPONENT Sensor)
