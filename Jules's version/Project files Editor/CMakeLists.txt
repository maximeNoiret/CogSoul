cmake_minimum_required(VERSION 3.30)
project(PacmanGame)

set(CMAKE_CXX_STANDARD 14)

include(ming/mingl.pri)

add_executable(PacmanGame
    "main.cpp")
