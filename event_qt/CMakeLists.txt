cmake_minimum_required(VERSION 3.13.4)
project(event_qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wl,--as-need -fPIE")

add_definitions(-DQT_NO_DEBUG_OUTPUT)
# Use Qt modules
set(QtFindModules Core Gui Widgets Concurrent)

foreach(QtModule ${QtFindModules})
    find_package(Qt5 COMPONENTS ${QtModule} REQUIRED)

    # include qt module private include directors
    include_directories(${Qt5${QtModule}_PRIVATE_INCLUDE_DIRS})

    # can use target_link_libraries(xxx ${QtUseModules})
    list(APPEND QtUseModules "Qt5::${QtModule}")
    message("QtModule found ${QtModule} OK!")
endforeach()

find_package(PkgConfig REQUIRED)
find_package(benchmark REQUIRED)

set(SRCS
    event/event.h
    event/event_p.h
    event/event.cpp
    event/eventhandler.h
    event/eventhandler.cpp
    event/eventcallproxy.h
    windoweventhandler.cpp
    windoweventhandler.h
    fileeventhandler.cpp
    fileeventhandler.h
    )

add_executable(${PROJECT_NAME}
        main.cpp
            ${SRCS}
    )

target_link_libraries(
    ${PROJECT_NAME}
    ${QtUseModules}
    )


add_executable(${PROJECT_NAME}_perf
            ${SRCS}
            benchmark.cpp
    )


target_link_libraries(
    ${PROJECT_NAME}_perf
    ${QtUseModules}
    benchmark::benchmark
    )
