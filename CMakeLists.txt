cmake_minimum_required(VERSION 2.8)

project(rester)

set(CMAKE_BUILD_TYPE Debug)

file(GLOB SRC_LIST src/*.cpp)
file(GLOB CLIB_LIST clib/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST} ${CLIB_LIST})
target_link_libraries(${PROJECT_NAME} pthread curl sqlite3)
