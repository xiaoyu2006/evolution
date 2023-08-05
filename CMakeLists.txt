cmake_minimum_required(VERSION 3.10)

project(evolution VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCLUDE src)

file(GLOB_RECURSE SOURCE
    src/*.cxx
    src/*.hxx
)

include_directories(${INCLUDE})
add_executable(evolution ${SOURCE}
        src/ray.cxx
        src/ray.hxx)
