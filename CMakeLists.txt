cmake_minimum_required(VERSION 3.15)
project(curli C)

set(CMAKE_C_STANDARD 99)

add_executable(curli src/main.c src/helper.c src/init.c include/parser.c include/parser.h)
