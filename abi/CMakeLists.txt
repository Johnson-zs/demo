cmake_minimum_required(VERSION 3.13.4)
project(abi)

set(CMAKE_CXX_STANDARD 17)

add_executable(abi main.cpp FileOld.cpp FileOld.h FileNew.cpp FileNew.h)
