cmake_minimum_required(VERSION 3.15)
project(curli C)

set(CMAKE_C_STANDARD 99)
add_executable(curli src/main.c
        src/helper.c src/init.c
        src/parser.c src/include/parser.h
        src/include/struct.h src/scheduler.c
        src/include/scheduler.h src/include/main.h)