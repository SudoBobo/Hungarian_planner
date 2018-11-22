cmake_minimum_required(VERSION 3.10)
project(planner C)

set(CMAKE_C_STANDARD 11)

add_executable(planner_test test.c)
add_library(planner planner.c data_preparer.c data_preparer.h pure_hungarian.c pure_hungarian.h)
target_link_libraries(planner_test planner)