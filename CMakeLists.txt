cmake_minimum_required(VERSION 3.0)

project(concurrent)

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

include_directories(include lib)
file(GLOB SOURCES "tests/*.cpp")

add_executable(concurrent ${SOURCES})

#http://derekmolloy.ie/hello-world-introductions-to-cmake/
