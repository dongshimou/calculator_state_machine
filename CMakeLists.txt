cmake_minimum_required(VERSION 3.9)
project(calculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "g++")

add_executable(calculator
        Calculator/main.cpp
        Calculator/calculator.h
        Calculator/state_machine.h
        Calculator/tokenzied.hpp
        Calculator/cal.hpp)