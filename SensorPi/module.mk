sensorpi_sources := $(wildcard ./SensorPi/src/*.cpp)
sensorpi_objects := $(call source_to_object, $(sensorpi_sources))

sources += $(sensorpi_sources)
includes += -I./SensorPi/include
executables += $(bin_dir)/sensorsystem-sensor

$(bin_dir)/sensorsystem-sensor: $(sensor_objects) $(lib_dir)/libsensorsystem-sensorcore.so $(lib_dir)/libsensorsystem-networking.so
	$(CXX) $(includes) -std=c++1z -L$(lib_dir) -Wl,-rpath,'$$ORIGIN/../lib' -Wl,-z,origin -o $@ $(sensorpi_objects) -lsensorsystem-networking -lsensorsystem-sensorcore