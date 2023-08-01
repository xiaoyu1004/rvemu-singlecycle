cmake_minimum_required(VERSION 3.10)
project(rvemu-singlecycle)

set(srcs ${PROJECT_SOURCE_DIR}/src/main.cpp)
add_executable(${PROJECT_NAME} ${srcs})