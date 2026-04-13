cmake_minimum_required(VERSION 3.26)

project(RcCar C)

find_package(SDL3 REQUIRED)

add_executable(RcCar
    src/main.c
    src/serial.c
    src/steering.c
)

target_include_directories(RcCar PRIVATE
    inc
)

target_link_libraries(RcCar PRIVATE SDL3::SDL3)