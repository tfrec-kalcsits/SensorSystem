project(SensorCore)
set(SensorCore_src_dir ${CMAKE_SOURCE_DIR}/SensorCore/src)
set(sensorcore_sources ${SensorCore_src_dir}/i2cerror.cpp ${SensorCore_src_dir}/mlxsensor.cpp ${SensorCore_src_dir}/tslsensor.cpp ${tsl2561})
add_library(sensorsystem-sensorcore STATIC ${sensorcore_sources} ${tsl2561})
target_include_directories(sensorsystem-sensorcore PRIVATE ${tsl2561_include} ${wiringPi_include} PUBLIC ${SensorCore_src_dir})
target_link_libraries(sensorsystem-sensorcore ${wiringPi})

install(TARGETS sensorsystem-sensorcore DESTINATION lib COMPONENT Sensor)
