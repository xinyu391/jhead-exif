cmake_minimum_required(VERSION 3.1)
project(jhead C)

set(SRC exif.c gpsinfo.c iptc.c jhead.c jpgfile.c jpgqguess.c makernote.c paths.c stream_func.c)

add_definitions(" -O3 -Wall ")
add_library(jhead ${SRC})

add_executable(sample sample.c)
target_link_libraries(sample  jhead)
target_link_libraries(sample  m)