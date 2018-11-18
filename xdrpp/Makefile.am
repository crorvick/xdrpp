AM_CPPFLAGS = $(LIBTIRPC_CFLAGS)
AM_CXXFLAGS = -std=c++11 -Wall -Werror
AM_LDFLAGS = $(LIBTIRPC_LDFLAGS)
lib_LTLIBRARIES = libxdrpp.la

libxdrpp_includedir = $(includedir)/xdrpp

libxdrpp_include_HEADERS = \
	base.hpp \
	deque.hpp \
	list.hpp \
	map.hpp \
	map_impl.hpp \
	multimap.hpp \
	pair.hpp \
	string.hpp \
	vec_impl.hpp \
	vector.hpp \
	xdrpp.hpp

libxdrpp_la_SOURCES = \
	string.cpp \
	vector.cpp \
	deque.cpp \
	list.cpp \
	pair.cpp \
	map.cpp \
	multimap.cpp \
	xdrpp.cpp
