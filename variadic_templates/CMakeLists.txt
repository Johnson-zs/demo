cmake_minimum_required(VERSION 3.5)

project(variadic_templates LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(variadic_templates_print print.cpp)
add_executable(variadic_templates_hashval hash_value.cpp)
add_executable(variadic_templates_tuple tuple.cpp)
