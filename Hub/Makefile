CXXFLAGS = -std=c++1z -pthread -g
INCLUDES = -I./include
CURL = -lcurl
NCURSES = -lncurses
NETWORKING = -lsensorsystem-networking -lrf24
FILESYSTEM = -lstdc++fs
OBJECTS = dropboxstorage.o csvfilestorage.o wifiinternetdevice.o helperfunctions.o cursesui.o config.o measurement.o

OBJ_COMMAND = $(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

.PHONY: all clean install Networking

all: sensorsystem-hub

install: all
	install -m 0755 ./sensorsystem-hub /usr/local/bin/
	
clean:
	if [ -f *.o ];then rm *.o; fi
	rm ./sensorsystem-hub
	if [ -f /usr/local/bin/sensorsystem-hub ]; then rm /usr/local/bin/sensorsystem-hub; fi
	rm -rf ./dep

sensorsystem-hub: $(OBJECTS) ./src/main.cpp Networking
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJECTS) ./src/main.cpp $(FILESYSTEM) $(NETWORKING) $(NCURSES) $(CURL)

dropboxstorage.o: ./src/storage/dropboxstorage.cpp ./include/hub/storage/dropboxstorage.h ./include/hub/storage/remotestorage.h
	$(OBJ_COMMAND)

csvfilestorage.o: ./src/storage/csvfilestorage.cpp ./include/hub/storage/csvfilestorage.h ./include/hub/storage/filestorage.h
	$(OBJ_COMMAND)
	
wifiinternetdevice.o: ./src/internet/wifiinternetdevice.cpp ./include/hub/internet/wifiinternetdevice.h ./include/hub/internet/wifiinternetdevice.h
	$(OBJ_COMMAND)
	
helperfunctions.o: ./src/internet/helperfunctions.cpp ./include/hub/internet/helperfunctions.h
	$(OBJ_COMMAND)

cursesui.o: ./src/cursesui.cpp ./include/hub/cursesui.h
	$(OBJ_COMMAND)
	
config.o: ./src/config.cpp ./include/hub/config.h Networking
	$(OBJ_COMMAND)
	
measurement.o: ./src/measurement.cpp ./include/hub/measurement.h
	$(OBJ_COMMAND)

Networking:
	if [ ! -d ./dep ]; then\
		git clone https://github.com/tfrec-kalcsits/SensorSystem-Networking.git ./dep/SensorSystem-Networking; \
		cd ./dep/SensorSystem-Networking && make all && sudo make install; \
	fi
