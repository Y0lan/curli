cmake_minimum_required(VERSION 3.15)
project(curli C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(curli src/main.c
        src/helper.c src/init.c
        src/parser.c src/include/parser.h
        src/include/struct.h src/scheduler.c
        src/include/scheduler.h src/include/main.h)
target_link_libraries( curli ${CMAKE_THREAD_LIBS_INIT} )
