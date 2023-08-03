cmake_minimum_required (VERSION 3.8)

project ("28-2-simulation-of-the-station")

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(28-2-simulation-of-the-station "main.cpp" ${MY_INCLUDE_DIR}/train.h "train.cpp" ${MY_INCLUDE_DIR}/functions.h)

target_include_directories(28-2-simulation-of-the-station PUBLIC ${CMAKE_SOURCE_DIR}/include)