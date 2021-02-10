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
    isQuite_ = false;
    //process looping

    while (!isQuite_){
        resultChannel_.clear();
        epoller_->loop(resultChannel_,savedError_);
        for(auto beg = resultChannel_.begin();
            beg != resultChannel_.end();beg++){
            (*beg)->handleEvent();
        }
    }

    isLooping_ = false;
}

void EventLoop::updateChannel(Channel* channel) {
    epoller_->updateChannel(channel);
}

EventLoop::EventLoop():thisThreadId_(std::this_thread::get_id()),
                       isLooping_(false),
                       epoller_(std::make_unique<Epoller>(this)){
    if (loopInThisThread){
        std::abort();
    }else {
        loopInThisThread = this;
    }

}

EventLoop::~EventLoop() {
    loopInThisThread = nullptr;
}

void EventLoop::quit() {
    isQuite_ = true;
}
