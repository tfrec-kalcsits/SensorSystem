export ROOTDIR = $(CURDIR)
SUBPROJECTS = Hub Networking

export RF24_INCLUDE = $(ROOTDIR)/thirdparty/RF24
export RF24_LIB = $(ROOTDIR)/thirdparty/RF24

export Networking_INCLUDE = $(ROOTDIR)/Networking/src
export Networking_LIB = $(ROOTDIR)/Networking

all: $(SUBPROJECTS)
.PHONY: all

$(SUBPROJECTS):
	$(MAKE) -C $@
.PHONY: $(SUBPROJECTS)

Hub: Networking

Networking: RF24
.PHONY: Networking

RF24:
	@cd $(ROOTDIR)/RF24 && ./configure --driver=SPIDEV && $(MAKE)
.PHONY: RF24

install: $(SUBPROJECTS)
	@for x in $^; do \
		$(MAKE) -C sub install; \
	done

clean:
	rm -rf *.o
	rm -rf *.so
.PHONY: clean

dist-clean: clean
	rm -f /usr/local/lib/libsensorsystem-networking.so
	rm -f /usr/local/bin/sensorsystem-hub