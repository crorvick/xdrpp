cmake_minimum_required(VERSION 3.8)

project(xdrpp)

find_package(PkgConfig REQUIRED)

option(BUILD_SHARED_LIBS "Build shared library" ON)

add_definitions(${CMAKE_CXX_FLAGS} "-std=c++11")
add_definitions(${CMAKE_CXX_FLAGS} "-Wall")
add_definitions(${CMAKE_CXX_FLAGS} "-Werror")

add_subdirectory(xdrpp)
