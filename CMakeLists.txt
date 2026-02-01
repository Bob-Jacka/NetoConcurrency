cmake_minimum_required(VERSION 3.31)
project(NetoConcurrency)

set(CMAKE_CXX_STANDARD 20)

add_executable(NetoConcurrency
        #        firstTask/main.cpp

        libio.cppm
#        secondTask/main1.cpp
)

target_sources(NetoConcurrency
        PUBLIC
        FILE_SET all_my_modules TYPE CXX_MODULES FILES
        libio.cppm
)
