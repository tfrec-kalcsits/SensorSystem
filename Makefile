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
	$(MAKE) -C thirdparty/RF24
.PHONY: RF24

install: $(SUBPROJECTS)
	@for sub in $^; do \
		$(MAKE) -C sub install; \
	done