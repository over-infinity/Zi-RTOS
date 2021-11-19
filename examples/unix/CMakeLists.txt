# Copyright (c) 2021, Over-Infinity 

project(Sample_Uinix)
cmake_minimum_required(VERSION 3.0)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../..)

add_executable(${CMAKE_PROJECT_NAME} main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../core/zi.c)