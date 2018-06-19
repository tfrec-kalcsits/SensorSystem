CXXFLAGS = -std=c++17 -shared
SOURCES = ./src/rf24radioreceiver.cpp ./src/rf24radiotransmitter.cpp

	
all: libsensorsystem-networking.so

install: all
	mkdir -p /usr/local/include/sensorsystem/networking
	cp ./src/*.h /usr/local/include/sensorsystem/networking/
	cp ./libsensorsystem-networking.so /usr/local/lib/

clean:
	if [ -d ./dep ]; then rm -rf ./dep; fi
	rm ./libsensorsystem-networking.so

libsensorsystem-networking.so: RF24
	$(CXX) $(CXXFLAGS) $(SOURCES) -I/usr/local/include/RF24 -lrf24 -o $@

RF24:
	if [ ! -d ./dep/RF24 ]; then git clone https://github.com/nRF24/RF24.git ./dep/RF24; fi
	if[ ! -d ./dep/RF24 ]; then cd ./dep/RF24 && make all && sudo make install; fi
