/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/


#include "EventLoop.h"
#include "Channel.h"
#include "Epoller.h"
thread_local EventLoop* loopInThisThread = nullptr;

void EventLoop::loop() {
    assertInLoopThread();
    isLooping_ = true;
    //process looping

    while (!isQuite_){

    }

    isLooping_ = false;
}

void EventLoop::updateChannel(std::shared_ptr<Channel> channelSP) {

}

EventLoop::EventLoop():thisThreadId_(std::this_thread::get_id()),
                       isLooping_(false),
                       isQuite_(true){
    if (loopInThisThread){
        std::abort();
    }else {
        loopInThisThread = this;
    }

}

EventLoop::~EventLoop() {

}
