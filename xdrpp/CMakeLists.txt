add_library(xdrpp
	deque.cpp
	list.cpp
	map.cpp
	multimap.cpp
	pair.cpp
	string.cpp
	vector.cpp
	xdrpp.cpp
)

pkg_check_modules(TIRPC libtirpc)

if(TIRPC_FOUND)
	target_include_directories(xdrpp PRIVATE ${TIRPC_INCLUDE_DIRS})
	target_compile_definitions(xdrpp PRIVATE HAVE_LIBTIRPC)
endif(TIRPC_FOUND)
