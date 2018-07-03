RF24_include_file_read = $(shell cat $(thirdparty_dir)/RF24/library.properties | grep version)
RF24_version := $(patsubst version=%,%,$(RF24_include_file_read))
RF24_libname := librf24.so.$(RF24_version)

includes += -I$(thirdparty_dir)/RF24
libraries += $(lib_dir)/$(RF24_libname)

$(lib_dir)/$(RF24_libname): RF24_ext
	@cp -u $(thirdparty_dir)/RF24/$(RF24_libname) $(lib_dir)/$(RF24_libname)

.PHONY: RF24_ext
RF24_ext: $(thirdparty_dir)/RF24_configured $(lib_dir)
	$(MAKE) -C $(thirdparty_dir)/RF24
	
$(thirdparty_dir)/RF24_configured:
	@cd $(thirdparty_dir)/RF24 && ./configure --driver=SPIDEV
	@touch $(thirdparty_dir)/RF24_configured
	
thirdparty-clean:
	$(MAKE) -C $(thirdparty_dir)/RF24 clean
