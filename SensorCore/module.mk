sensorcore_sources := $(wildcard ./SensorCore/src/*.cpp)
sensorcore_objects := $(call source_to_object,$(sensorcore_sources))

includes += -I./SensorCore/src
sources += sensorcore_sources

$(lib_dir)/libsensorsystem-sensorcore.so: $(sensorcore_objects) $(lib_dir)/$(wiringPi_libname)
	$(CXX) -shared -fPIC -o $@ $(sensorcore_objects) -L$(lib_dir) -lwiringPi
