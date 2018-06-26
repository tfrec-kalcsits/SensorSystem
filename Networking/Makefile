LIBFLAGS = -shared -fPIC
OBJECTS = rf24radiotransmitter.o rf24radioreceiver.o

all: libsensorsystem-networking.so
.PHONY: all

libsensorsystem-networking.so: $(OBJECTS)

rf24radiotransmitter.o: ./src/rf24radiotransmitter.cpp ./src/rf24radiotransmitter.h ./src/radiotransmitter.h
	$(CXX) -c $<

rf24radioreceiver.o: ./src/rf24radioreceiver.cpp ./src/rf24radioreceiver.h ./src/radioreceiver.h ./src/packet.h ./src/byte.h
	$(CXX) -c $<

install: all
	$MAKE -C $(ROOTDIR)/thirdparty/RF24 install
	install -m 0755 ./libsensorsystem-networking.so /usr/local/lib/