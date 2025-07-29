cmake_minimum_required(VERSION 3.31)
project(EventPlanner)

set(CMAKE_CXX_STANDARD 20)

add_executable(EventPlanner main.cpp
        Event.cpp
        Event.h)
