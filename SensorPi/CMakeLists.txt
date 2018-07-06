project(SensorPi)
file(GLOB_RECURSE sensorpi_source src/*.cpp)
add_executable(sensorsystem-sensor ${sensorpi_source})
target_include_directories(sensorsystem-sensor PUBLIC ${CMAKE_SOURCE_DIR}/SensorPi/include PRIVATE ${wiringPi_include} ${wiringPiDev_include})
target_link_libraries(sensorsystem-sensor sensorsystem-networking sensorsystem-sensorcore ${wiringPi} ${wiringPiDev})

install(TARGETS sensorsystem-sensor
		RUNTIME DESTINATION bin
		COMPONENT Sensor
		)
	
add_custom_target(Sensor-install
	DEPENDS Networking-install
	COMMAND
	${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=Sensor
	-P ${CMAKE_BINARY_DIR}/cmake_install.cmake
	)
