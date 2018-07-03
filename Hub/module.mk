hub_source := $(wildcard ./Hub/src/*.cpp) $(wildcard ./Hub/src/storage/*.cpp) $(wildcard ./Hub/src/internet/*.cpp)
hub_objects := $(call source_to_object, $(hub_source))

includes += -I./Hub/include
sources += $(hub_source)
executables += $(bin_dir)/sensorsystem-hub

$(bin_dir)/sensorsystem-hub: $(hub_objects) $(lib_dir)/libsensorsystem-networking.so
	$(CXX) $(includes) -std=c++1z -pthread -L$(lib_dir) -Wl,-rpath,'$$ORIGIN/../lib' -Wl,-z,origin -o $@ $(hub_objects) -lsensorsystem-networking -lcurl -lncurses -lstdc++fs
