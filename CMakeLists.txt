cmake_minimum_required(VERSION 3.17)
project(TinyServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(TinyServer src/main.cpp src/HttpServer.cpp src/HttpServer.h src/EventLoop.cpp src/EventLoop.h src/Channel.cpp src/Channel.h src/base/Socket.cpp src/base/Socket.h src/base/Buffer.cpp src/base/Buffer.h src/HttpConn.cpp src/HttpConn.h src/base/Timer.cpp src/base/Timer.h src/Acceptor.cpp src/Acceptor.h src/Epoller.cpp src/Epoller.h src/EventLoopThread.cpp src/EventLoopThread.h src/base/nocopyable.h src/base/copyable.h src/test/test1.cpp)


find_package(Threads REQUIRED)
target_link_libraries(TinyServer Threads::Threads)