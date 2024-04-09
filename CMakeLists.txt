cmake_minimum_required(VERSION 3.26)
project(LFaf)

set(CMAKE_CXX_STANDARD 20)

add_executable(LFaf main.cpp
        Source/RegularLanguage.cpp
        LfafH/RegularLanguage.h
)
