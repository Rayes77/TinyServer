cmake_minimum_required(VERSION 3.17)
project(TinyServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(TinyServer src/main.cpp src/EventLoop.cpp src/EventLoop.h src/Epoller.cpp src/Epoller.h src/Channel.cpp src/Channel.h src/Poller.cpp src/Poller.h src/TimerQueue.cpp src/TimerQueue.h src/Timer.cpp src/Timer.h src/EventLoopThead.cpp src/EventLoopThead.h)


find_package(Threads REQUIRED)
target_link_libraries(TinyServer Threads::Threads)