CXXFLAGS = -std=c++1z
LIBFLAGS = -shared -fPIC
OBJECTS = rf24radiotransmitter.o rf24radioreceiver.o
LIBS = $(RF24)/librf24.so
OBJ_CMD = $(CXX) $(CXXFLAGS) -c $<
REPO = ..
RF24_INCLUDE = $(REPO)/thirdparty
RF24_DIR = $(REPO)/thirdparty/RF24

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

.PHONY: all install
	
all: libsensorsystem-networking.so
	@$(ECHO) build complete

libsensorsystem-networking.so: $(OBJECTS) $(LIBS)
@$(ECHO) linking object files
@$(CXX) $(CXXFLAGS) $(LIBFLAGS) $(RF24_INCLUDE) $^ -o $@

rf24radiotransmitter.o: ./src/rf24radiotransmitter.cpp ./src/rf24radiotransmitter.h ./src/radiotransmitter.h ./src/packet.h ./src/byte.h $(RF24)/librf24.so*
	@$(ECHO) building $@
	@$(OBJ_CMD) $(RF24_INCLUDE)
	
rf24radioreceiver.o: ./src/rf24radioreceiver.cpp ./src/rf24radioreceiver.h ./src/radioreceiver.h ./src/packet.h ./src/byte.h $(RF24_DIR)/librf24.so*
	@$(ECHO) building $@
	@$(OBJ_CMD) $(RF24_INCLUDE)

$(RF24_DIR)/librf24.so*:
	@echo building RF24 library
	@cd $(RF24_DIR) && ./configure --driver=SPIDEV && make -s

install: all
	@$(ECHO) installing RF24 library
	@cd $(RF24_DIR) && make -s install
	@$(ECHO) installing headers to /usr/local/include/sensorsystem/networking
	@mkdir -p /usr/local/include/sensorsystem/networking
	@install -m 0644 ./src/*.h /usr/local/include/sensorsystem/networking/
	@$(ECHO) installing libs to /usr/local/lib
	@install -m 0755 ./libsensorsystem-networking.so /usr/local/lib/

