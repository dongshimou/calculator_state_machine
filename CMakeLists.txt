cmake_minimum_required(VERSION 3.9)
project(calculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculator
        Calculator/main.cpp
        Calculator/calculator.h
        Calculator/state_machine.h

        )