cmake_minimum_required(VERSION 3.5)
project(editor)

set(CMAKE_CXX_STANDARD 14)

add_executable(graphic main.cpp document.h figures.h figures.cpp document.cpp controller.h controller.cpp)