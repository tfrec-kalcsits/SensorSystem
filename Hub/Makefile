CXXFLAGS = -std=c++1z -pthread
EXTLIBS = -lcurl -lncurses -lstdc++fs
OBJECTS = dropboxstorage.o csvfilestorage.o wifiinternetdevice.o helperfunctions.o cursesui.o config.o measurement.o
INCLUDES = -I./include -I$(RF24_INCLUDE) -I$(Networking_INCLUDE)
OBJCMD = $(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

all: sensorsystem-hub
.PHONY: all
@$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJECTS) ./src/main.cpp $(Networking_LIB) $(RF24_LIB) $(EXTLIBS)
sensorsystem-hub: $(OBJECTS)

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

install: all
	install -m 0755 ./sensorsystem-hub /usr/local/bin