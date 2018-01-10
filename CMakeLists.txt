project(jhead C)

set(SRC exif.c gpsinfo.c iptc.c jhead.c jpgfile.c jpgqguess.c makernote.c paths.c)


add_library(jhead ${SRC})

add_executable(sample sample.c)
target_link_libraries(sample  jhead m)