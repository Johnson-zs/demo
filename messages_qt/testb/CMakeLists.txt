cmake_minimum_required(VERSION 3.13.4)

project(testb)

set(SRCS
    testb.cpp
    testb.h
    )

add_library(${PROJECT_NAME}
            ${SRCS}
    )

target_link_libraries(
    ${PROJECT_NAME}
    message
    ${QtUseModules}
    )
