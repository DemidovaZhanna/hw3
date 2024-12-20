cmake_minimum_required(VERSION 3.29)
project(hw3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(inc test)

set(MINISAT_DIR "${CMAKE_SOURCE_DIR}/third_party/minisat")
add_subdirectory(${MINISAT_DIR} ${CMAKE_BINARY_DIR}/minisat_build)

add_executable(hw3 main.cpp inc/3SAT.h
        test/test.h
        inc/combined3SAT.h)

target_link_libraries(hw3 PRIVATE MiniSat::libminisat)

target_include_directories(hw3 PRIVATE ${MINISAT_DIR}/minisat/core)

