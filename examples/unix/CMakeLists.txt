# Copyright (c) 2021, Over-Infinity 

project(HelloWorld)
cmake_minimum_required(VERSION 3.0)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../..)

add_executable(hello_world main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../core/zi.c)