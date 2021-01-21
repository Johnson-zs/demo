cmake_minimum_required(VERSION 3.1)

project(template_method)

aux_source_directory(. DIR_SRCS)

add_executable(${PROJECT_NAME} ${DIR_SRCS})
