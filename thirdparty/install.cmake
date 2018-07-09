message("installing RF24")
execute_process(COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/RF24 install)
