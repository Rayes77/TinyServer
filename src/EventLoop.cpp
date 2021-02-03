/*
* @author:MutexCat
* @date  :2021/2/3
* @github:https://github.com/MutexCat
* @description:
*
*/


#include "EventLoop.h"

thread_local EventLoop* loopInThisThread;

void EventLoop::abortNotInLoopThreed() {
    std::abort();
}

EventLoop::EventLoop():
            thisThreadId(std::this_thread::get_id()),
            looping_(false),
            quit_(false){
    if (loopInThisThread){
        std::cerr<<"This thread already has a EventLoop.\n";
        std::abort();
    }else{
        loopInThisThread = this;
    }
}

EventLoop::~EventLoop() {
    assert(!looping_);
    loopInThisThread = NULL;
}

void EventLoop::loop() {
    assert(!looping_);
    assertInThread();
    looping_ = true;
    for (int i = 0; i < 5; ++i) {
        std::cout<<"process data\n";
    }
    looping_ = false;
}

EventLoop *EventLoop::getEventLoopOfCurrentThread() {
    return loopInThisThread;
}
