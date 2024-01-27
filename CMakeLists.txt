cmake_minimum_required(VERSION 3.0)
project(ldvc_mem_examples)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(src)

file(GLOB EXAMPLE_SOURCES "examples/*.cpp")

foreach(EXAMPLE_SRC ${EXAMPLE_SOURCES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SRC} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SRC} src/ldvc_sysinfo.cpp src/ldvc_io.cpp)
endforeach()
