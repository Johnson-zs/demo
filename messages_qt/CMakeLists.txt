cmake_minimum_required(VERSION 3.13.4)
project(messages_qt)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wl,--as-need -fPIE")

# Use Qt modules
set(QtFindModules Core Gui Widgets Concurrent Svg Network Sql X11Extras)

foreach(QtModule ${QtFindModules})
    find_package(Qt5 COMPONENTS ${QtModule} REQUIRED)

    # include qt module private include directors
    include_directories(${Qt5${QtModule}_PRIVATE_INCLUDE_DIRS})

    # can use target_link_libraries(xxx ${QtUseModules})
    list(APPEND QtUseModules "Qt5::${QtModule}")
    message("QtModule found ${QtModule} OK!")
endforeach()

include_directories(${PROJECT_SOURCE_DIR}/message)

add_subdirectory(${PROJECT_SOURCE_DIR}/testa)
add_subdirectory(${PROJECT_SOURCE_DIR}/testb)
add_subdirectory(${PROJECT_SOURCE_DIR}/message)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    testa
    testb
    ${QtUseModules}
    )
