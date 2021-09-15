cmake_minimum_required(VERSION 3.13.4)

project(message)

set(SRCS
    message.h
    message.cpp
    messagehelper.h
    invokehelper.h
    )

add_library(${PROJECT_NAME} SHARED
            ${SRCS}
    )

target_link_libraries(
    ${PROJECT_NAME}
    ${QtUseModules}
    )
