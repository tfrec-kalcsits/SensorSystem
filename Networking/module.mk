networking_source = $(wildcard ./Networking/src/*.cpp)
networking_objects = $(call source_to_object, $(networking_source))

sources += $(networking_source)
includes += -I./Networking/src
libraries += $(lib_dir)/libsensorsystem-networking.so

$(lib_dir)/libsensorsystem-networking.so: $(lib_dir)/$(RF24_libname) $(networking_objects)
	$(CXX) -shared -fPIC -o $@ $(networking_objects) $(lib_dir)/$(RF24_libname)
