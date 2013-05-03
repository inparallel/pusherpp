AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_LDFLAGS=-L/usr/local/lib -lcurl -lcrypto

lib_LTLIBRARIES = libpusherpp.la
libpusherpp_la_SOURCES = pusherpp/include/config.h pusherpp/include/CHTTPClient.hpp pusherpp/include/CHTTPClient.cpp pusherpp/CPusher.hpp pusherpp/CPusher.cpp
libpusherpp_la_LDFLAGS = -version-info $(SOVERSION)

libpusherpp_includedir = $(includedir)
nobase_libpusherpp_include_HEADERS = pusherpp/CPusher.hpp pusherpp/include/CHTTPClient.hpp pusherpp/include/config.h

#libpusherpp_libincludedir = $(libdir)/pusherpp/include
#nodist_libpusherpp_libinclude_HEADERS = pusherpp/config.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pusherpp.pc

# For future use...

#lib_LTLIBRARIES = libpusherpp-@LIBVERSION@.la
#libpusherpp_@LIBVERSION@_la_SOURCES = pusherpp/CHTTPClient.hpp pusherpp/CHTTPClient.cpp pusherpp/CPusher.hpp pusherpp/CPusher.cpp
#libpusherpp_@LIBVERSION@_la_LDFLAGS = -version-info $(SOVERSION)

#libpusherpp_includedir = $(includedir)/libpusherpp-$(LIBVERSION)
#nobase_libpusherpp_include_HEADERS = pusherpp/CPusher.hpp pusherpp/CHTTPClient.hpp

#libpusherpp_libincludedir = $(libdir)/libpusherpp-$(LIBVERSION)/include
#nodist_libpusherpp_libinclude_HEADERS = pusherpp/config.h

#pkgconfigdir = $(libdir)/pkgconfig
#pkgconfig_DATA = pusherpp-$(LIBVERSION).pc
