cmake_minimum_required(VERSION 3.5)
project(course02lab05os)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp EmitterListener.cpp EmitterListener.h AbstractSocket.cpp Socket.cpp)
add_executable(course02lab05os ${SOURCE_FILES})