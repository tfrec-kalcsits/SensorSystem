modules := Networking Hub SensorCore SensorPi

source_to_object = $(subst .c,.o, $(filter %.c, $1)) \
				   $(subst .cpp,.o, $(filter %.cpp, $1))

libraries :=
executables :=
sources :=
includes :=

objects = $(call source_to_object, $(sources))
dependencies = $(objects:.o=.d)

lib_dir := ./lib
bin_dir := ./bin
thirdparty_dir := $(CURDIR)/thirdparty

all:

include $(thirdparty_dir)/thirdparty.mk $(addsuffix /module.mk,$(modules))
-include $(dependencies)

.PHONY: all
all: $(libraries) $(executables)

%.o: %.cpp
	$(CXX) -c -MMD -MP $(includes) -o $@ $<
	
$(libraries)s: $(lib_dir)
$(executables): $(bin_dir)

$(lib_dir) $(bin_dir) lib/:
	@mkdir -p $@
	
	
clean: thirdparty-clean
	@rm -f $(objects) $(dependencies)
	@rm -rf $(lib_dir)
	@rm -rf $(bin_dir)

