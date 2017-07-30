cmake_minimum_required(VERSION 3.1)

project(concurrent)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include lib)
file(GLOB SOURCES "tests/*.cpp")

add_executable(concurrent ${SOURCES})

#http://derekmolloy.ie/hello-world-introductions-to-cmake/
