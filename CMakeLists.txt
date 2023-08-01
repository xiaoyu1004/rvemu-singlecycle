cmake_minimum_required(VERSION 3.10)
project(rvemu-singlecycle)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE srcs ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${srcs})