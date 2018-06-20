CXXFLAGS = -std=c++17
INCLUDES = -I./include
CURLFLAGS = -lcurl
CURSESFLAGS = -lncurses
OBJECTFILES = storage.o internet.o cursesui.o config.o measurement.o
NETWORKINGFLAGS = -lsensorsystem-networking -I/usr/local/include/sensorsystem -I/usr/local/include/RF24

all: sensorsystem-hub

sensorsystem-hub: ./src/main.cpp storage internet cursesui config measurement sensorsystem-networking
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(NETWORKINGFLAGS) ./src/main.cpp $(OBJECTFILES) -o $@

storage: ./src/storage/csvfilestorage.cpp ./src/storage/dropboxstorage.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(CURLFLAGS) -c ./src/storage/csvfilestorage.cpp -o csvfilestorage.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(CURLFLAGS) -c ./src/storage/dropboxstorage.cpp -o dropboxstorage.o
	
internet: ./src/internet/helperfunctions.cpp ./src/internet/wifiinternetdevice.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(CURLFLAGS) -c ./src/internet/helperfunctions.cpp -o helperfunctions.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(CURLFLAGS) -c ./src/internet/wifiinternetdevice.cpp -o wifiinternetdevice.o
	
	
cursesui: ./src/cursesui.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(CURSESFLAGS) -c $? -o $@.o
		
config: ./src/config.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(NETWORKINGFLAGS) -c $? -o $@.o
	
measurement: ./src/measurement.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $? -o $@.o
	
sensorsystem-networking:
	if [ ! -d ./dep/sensorsystem-networking ]; then git clone https://github.com/tfrec-kalcsits/SensorSystem-Networking.git; fi
	if [ ! -d ./dep/sensorsystem-networking ]; cd ./dep/sensorsystem-networking && make all && sudo make install; fi

clean:
	rm -r *.o
	rm

install: all
	cp ./sensorsystem-hub /usr/local/bin/
	mkdir ~/.sensorsystem-hub

dependencies:
	apt install libcurl4-openssl-dev libncurses5-dev
	

