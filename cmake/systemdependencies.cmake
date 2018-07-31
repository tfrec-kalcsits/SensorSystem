#This file fetches system dependencies for the projects. This includes:
# - wiringPi
# - libcurl
# - libncurses

find_package(CURL REQUIRED)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_library(wiringPi wiringPi)
find_library(wiringPiDev wiringPiDev)
