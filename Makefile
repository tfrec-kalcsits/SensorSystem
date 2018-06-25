CXXFLAGS = -std=c++1z
LIBFLAGS = -shared -fPIC
OBJECTS = rf24radiotransmitter.o rf24radioreceiver.o
OBJ_CMD = $(CXX) $(CXXFLAGS) -c $<
RF24 = -lRF24

ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL = all
%:
        @$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      ECHO="COUNTTHIS" | grep -c "COUNTTHIS")
endif

N := x
C = $(words $N)$(eval N := x $N)
ECHO = echo "`expr " [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
endif

.PHONY: all install clean RF24
	
all: libsensorsystem-networking.so
	@$(ECHO) build complete

install: all
	@$(ECHO) installing headers to /usr/local/include/sensorsystem/networking
	@mkdir -p /usr/local/include/sensorsystem/networking
	@install -m 0644 ./src/*.h /usr/local/include/sensorsystem/networking/
	@$(ECHO) installing libs to /usr/local/lib
	@install -m 0755 ./libsensorsystem-networking.so /usr/local/lib/

clean:
	if [ -d ./dep ]; then rm -rf ./dep; fi
	rm ./libsensorsystem-networking.so
	rm -rf /usr/local/include/sensorsystem/networking
	rm -rf /usr/local/lib/libsensorsystem-networking.so
	
RF24:
	@$(ECHO) installing RF24 library
	@if [ ! -d ./dep/RF24 ]; then git clone https://github.com/nRF24/RF24.git ./dep/RF24; fi
	@$(ECHO) building RF24 library
	@if [ ! -d ./dep/RF24 ]; then cd ./dep/RF24 && ./configure --driver=SPIDEV && make -silent all && sudo make -silent install; fi

rf24radiotransmitter.o: ./src/rf24radiotransmitter.cpp ./src/rf24radiotransmitter.h ./src/radiotransmitter.h ./src/packet.h ./src/byte.h RF24
	@$(ECHO) building $@
	@$(OBJ_CMD) $(RF24)
	
rf24radioreceiver.o: ./src/rf24radioreceiver.cpp ./src/rf24radioreceiver.h ./src/radioreceiver.h ./src/packet.h ./src/byte.h RF24
	@$(ECHO) building $@
	@$(OBJ_CMD) $(RF24)

libsensorsystem-networking.so: $(OBJECTS)
	@$(ECHO) linking object files
	@$(CXX) $(CXXFLAGS) $(LIBFLAGS) $^ -o $@

