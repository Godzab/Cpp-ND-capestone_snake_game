cmake_minimum_required(VERSION 3.13)
project(snake)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
file(GLOB project_SRCS src/*.cpp) #src/*.h

add_executable(snake ${project_SRCS})

target_link_libraries(snake ${CURSES_LIBRARIES})

target_compile_options(snake PRIVATE -Wall -Wextra)
