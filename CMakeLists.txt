project(xdrpp)

cmake_minimum_required(VERSION 2.6)

option(BUILD_SHARED_LIBS "Build shared library" ON)

add_definitions(${CMAKE_CXX_FLAGS} "-std=c++11")
add_definitions(${CMAKE_CXX_FLAGS} "-Wall")

add_subdirectory(xdrpp)
