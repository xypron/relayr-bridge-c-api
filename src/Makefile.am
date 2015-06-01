librelayrbridge_la_LDFLAGS = -version-info 1:0:1

library_includedir=$(includedir)

library_include_HEADERS = \
  bridge.h \
  bridgeconst.h \
  serial.h

lib_LTLIBRARIES = librelayrbridge.la
librelayrbridge_la_SOURCES = \
  bridge.c \
  crc.c \
  serial.c

bin_PROGRAMS = \
  demo

demo_SOURCES = demo.c

demo_LDADD = librelayrbridge.la

demo_LDFLAGS = -static

check:
	./demo$(EXEEXT) /dev/ttyUSB0
