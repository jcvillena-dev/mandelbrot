cmake_minimum_required(VERSION 3.7)
add_definitions(-std=c++17)
set(CMAKE_CXX_STANDARD 17)

project(Mandelbrot)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
set(CXX_FLAGS "-Wal")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS} -pthread")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(src include)
file(GLOB project_SRCS src/*.cpp)
add_executable(Mandelbrot ${project_SRCS})
target_link_libraries(Mandelbrot ${SDL2_LIBRARIES})
target_link_libraries(Mandelbrot ${CMAKE_THREAD_LIBS_INIT})
