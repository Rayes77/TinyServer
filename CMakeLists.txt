cmake_minimum_required(VERSION 3.17)
project(TinyServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(TinyServer src/main.cpp src/server/server.cpp
                src/server/server.h src/eventloop/epoller.cpp
                src/eventloop/epoller.h src/threadpool/threadpool.cpp
                src/threadpool/threadpool.h src/http/httpConnection.h
                src/http/httpConnection.cpp src/http/httpRequest.h
                src/http/httpRequest.cpp src/http/httpResponse.h
                src/http/httpResponse.cpp)


find_package(Threads REQUIRED)
target_link_libraries(TinyServer Threads::Threads)