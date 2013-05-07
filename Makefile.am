AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_LDFLAGS=-L/usr/local/lib -lcurl -lcrypto

lib_LTLIBRARIES = libpusherpp.la
libpusherpp_la_SOURCES = pusherpp/include/config.h pusherpp/include/CHTTPClient.hpp pusherpp/include/CHTTPClient.cpp pusherpp/CPusher.hpp pusherpp/CPusher.cpp pusherpp/CPusherReply.hpp pusherpp/CPusherReply.cpp pusherpp/include/CUtilities.hpp pusherpp/include/CUtilities.cpp
libpusherpp_la_LDFLAGS = -version-info $(SOVERSION)

libpusherpp_includedir = $(includedir)
nobase_libpusherpp_include_HEADERS = pusherpp/CPusher.hpp pusherpp/CPusherReply.hpp pusherpp/include/CHTTPClient.hpp pusherpp/include/CUtilities.hpp pusherpp/include/config.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pusherpp.pc

