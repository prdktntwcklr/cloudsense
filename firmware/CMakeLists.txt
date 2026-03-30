cmake_minimum_required(VERSION 3.28.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(cloudsense_firmware)    

add_subdirectory(drivers)

target_sources(app PRIVATE src/main.c)
