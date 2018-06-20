CXXFLAGS = -std=c++1z -pthread
INCLUDES = -I./include
CURL = -lcurl
NCURSES = -lncurses
NETWORKING = -lsensorsystem-networking -lrf24
FILESYSTEM = -lstdc++fs
OBJECTS = dropboxstorage.o csvfilestorage.o wifiinternetdevice.o helperfunctions.o cursesui.o config.o measurement.o

OBJ_COMMAND = $(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

.PHONY: all clean install

all: sensorsystem-hub

install:
	cp ./sensorsystem-hub /usr/local/bin/
	mkdir ~/.sensorsystem-hub
	
clean:
	rm *.o
	rm ./sensorsystem-hub
	rm /usr/local/bin/sensorsystem-hub

sensorsystem-hub: $(OBJECTS) ./src/main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(FILESYSTEM) $(NETWORKING) $(NCURSES) $(CURL)

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
	
config.o: ./src/config.cpp ./include/hub/config.h
	$(OBJ_COMMAND)
	
measurement.o: ./src/measurement.cpp ./include/hub/measurement.h
	$(OBJ_COMMAND)
