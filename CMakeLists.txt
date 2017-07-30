cmake_minimum_required(VERSION 3.0)

project(concurrent)

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
file(GLOB SOURCES "*.cpp")

add_executable(concurrent ${SOURCES})
