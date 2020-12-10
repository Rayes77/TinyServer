cmake_minimum_required(VERSION 3.17)
project(TinyServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(TinyServer src/main.cpp src/Server.h src/Server.cpp src/utils.cpp src/utils.h)


find_package(Threads REQUIRED)
target_link_libraries(TinyServer Threads::Threads)