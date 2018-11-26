cmake_minimum_required(VERSION 3.10)
project(planner)

set(CMAKE_C_STANDARD 11)

set(MAIN_PROJECT_SRC_LIST main)
# Other stuff

add_executable(planner_test test.c)
add_subdirectory(planner_lib)
target_link_libraries(planner_test planner_lib)